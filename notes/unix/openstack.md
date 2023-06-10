<!-- TOC -->

- [OpenStack面板常用功能](#openstack面板常用功能)
- [OpenStackClient](#openstackclient)
	- [配置OpenStack認證](#配置openstack認證)
	- [OpenStackClient配置文件](#openstackclient配置文件)
- [Kolla Ansible](#kolla-ansible)
	- [Debian Stable部署流程](#debian-stable部署流程)

<!-- /TOC -->



# OpenStack面板常用功能
OpenStack的常用功能菜單。

| 菜單 | 功能描述 |
| :- | :- |
| Project - Compute - Overview | 當前項目的資源配額 |
| Identity - Projects - Modify Quotas | 修改當前項目配額 |
| Admin - Compute - Hypervisors | 集群所有節點實際資源分佈 |



# OpenStackClient
OpenStack提供了命令行管理工具[OpenStackClient](https://docs.openstack.org/python-openstackclient/latest/)，
該工具由Python實現，可直接使用`pip`安裝：

```
$ pip install python-openstackclient
```

安裝完成後即可使用`openstack`指令。

## 配置OpenStack認證
OpenStackClient可從環境變量中讀取認證信息，以kolla-ansible部署為例，
部署完畢後會生成`admin-openrc.sh`，記載了當前集群使用的認證信息，內容示例：

```
export OS_PROJECT_DOMAIN_NAME=...
export OS_USER_DOMAIN_NAME=...
export OS_PROJECT_NAME=...
export OS_TENANT_NAME=...
export OS_USERNAME=...
export OS_PASSWORD=...
export OS_AUTH_URL=http://...
export OS_INTERFACE=internal
export OS_IDENTITY_API_VERSION=../
export OS_REGION_NAME=RegionOne
export OS_AUTH_PLUGIN=password
```

加載該配置中的環境變量即可訪問OpenStack集群。

## OpenStackClient配置文件
OpenStackClient亦支持從配置文件中讀取認證信息，
詳情可參考[官方文檔](https://docs.openstack.org/python-openstackclient/latest/configuration/index.html#configuration-files)

OpenStackClient支持下列配置路徑，按照查找優先級，依次為：

- `./clouds.yaml`
- `~/.config/openstack/clouds.yaml`
- `/etc/openstack/clouds.yaml`

配置結構與環境變量相對應：

```yaml
clouds:
  集群名稱1: # 支持定義多個環境
    auth:
      auth_url: http://...
      project_name: ...
      user_domain_name: ...
      project_domain_name: ...
      username: ...
      password: ...
    region_name: RegionOne
  集群名稱2:
    ...
  集群名稱3:
    ...
```

對於在配置文件中記錄的集群信息，需要添加`--os-cloud`參數指定集群名稱進行訪問：

```
$ openstack --os-cloud 集群名稱 ...
```



# Kolla Ansible
[kolla-ansible](https://docs.openstack.org/kolla-ansible/latest/)是目前主流的OpenStack集群部署方式之一，
將OpenStack組件以Docker容器的形式部署到服務器中。

基本部署流程參考[QuickStart教程](https://docs.openstack.org/kolla-ansible/latest/user/quickstart.html)。
Kolla Ansible部署流程視使用版本而異，部署時需要訪問對應版本的文檔，
將路徑中`https://docs.openstack.org/kolla-ansible/latest/user/quickstart.html`中的`latest`替換為部署目標版本的版本代號。

使用Kolla Ansible之前，需要選定正確的發行版，Kolla Ansible僅官方支持下列發行版：

- Debian，僅Stable版本
- Ubuntu，僅LTS版本
- Roky
- CentOS

Kolla Ansible實際支持的版本參見官方
[`Kolla Images Support Matrix`](https://docs.openstack.org/kolla/latest/support_matrix.html)。

## Debian Stable部署流程
以當前的Debian係發行版為例，首先安裝Python venv，並進入虛擬環境：

```html
<!-- 安裝 venv，創建並進入虛擬環境 -->
# apt install python3-venv
# python3 -m venv /opt/openstack-venv
# source /opt/openstack-venv/bin/activate.fish
```

之後安裝Ansible（需要注意Ansible版本，不能直接使用最新版本，
不同版本Kolla依賴的Ansible版本也有所差異，參考對應版本的部署文檔，當前以`Zed`版本為例）：

```
# pip install -U pip
# pip install "ansible>=4,<6"
```

安裝Kolla Ansible（使用的Kolla分支需要匹配OpenStack的部署目標版本）：

```html
<!-- 對應Master，當前開發版 -->
# pip install git+https://opendev.org/openstack/kolla-ansible@master

<!-- 對應 OpenStack Zed 版本，其它版本類似，需要使用Kolla Ansible的對應分支 -->
# pip install git+https://opendev.org/openstack/kolla-ansible@stable/zed
...
```

複製默認配置：

```html
# mkdir -p /etc/kolla
# cp /opt/openstack-venv/share/kolla-ansible/etc_examples/kolla/* /etc/kolla
# cp /opt/openstack-venv/share/kolla-ansible/ansible/inventory/all-in-one . <!-- 使用all-in-one安裝-->
```

編輯配置文件`/etc/kolla/globals.yml`，核心配置內容：

```yml
...
kolla_base_distro: "ubuntu" # 設置鏡像基於的發行版，基於Ubuntu的鏡像通常經過較為充分的測試，同時體積較小，推薦選用
openstack_release: "zed" # 指定部署的OpenStack版本，默認的master為開發中版本，不穩定，不推薦使用
...
network_interface: "網卡設備" # 管理網
kolla_internal_vip_address: "x.x.x.x" # VIP地址
neutron_external_interface: "網卡設備" # 虛擬機業務網
...
```

默認配置中節點啟用`enable_openstack_core`配置，會使用下列組件：

```
glance, keystone, neutron, nova, heat, horizon
```

修改配置完成後，執行檢查和部署操作：

```html
# kolla-ansible install-deps <!-- 生成各類roles配置（～/.ansible/collections/ansible_collections/openstack/kolla） -->
# kolla-genpwd <!-- 生成密碼（/etc/kolla/password.yml文件） -->

# kolla-ansible -i ./all-in-one bootstrap-servers <!-- 安裝依賴軟件包 -->
# kolla-ansible -i ./all-in-one prechecks <!-- 部署檢查 -->

<!-- 順利通過檢查後可執行部署操作 -->
# kolla-ansible -i ./all-in-one deploy

<!-- 部署操作順利完成後，執行後置部署操作 -->
# kolla-ansible -i ./all-in-one post-deploy <!-- 會在 /etc/kolla 路徑下生成 admin-openrc.sh 文件 -->
```

`kolla-genpwd`生成密碼需要`/etc/kolla/password.yml`文件已存在，password.yml文件中，
`keystone_admin_password`配置決定Horizon網管頁面以及openstack命令行工具的密碼。

集群部署完成後，常用管理操作：

```html
# kolla-ansible -i ./all-in-one stop <!-- 關閉服務容器 -->
# kolla-ansible -i ./all-in-one deploy-containers <!-- 啟動集群容器 -->
```
