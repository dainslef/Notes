<!-- TOC -->

- [OpenStack面板常用功能](#openstack面板常用功能)
- [OpenStackClient](#openstackclient)
	- [配置OpenStack認證](#配置openstack認證)
	- [OpenStackClient配置文件](#openstackclient配置文件)
- [Kolla Ansible](#kolla-ansible)
	- [Debian Stable部署流程](#debian-stable部署流程)
	- [升級OpenStack版本](#升級openstack版本)
	- [Cinder（存儲配置）](#cinder存儲配置)
	- [Octavia（負載均衡器配置）](#octavia負載均衡器配置)
	- [Kolla Ansible部署問題](#kolla-ansible部署問題)
		- [Python依賴](#python依賴)
		- [網卡IP地址](#網卡ip地址)
		- [清理部署環境](#清理部署環境)
		- [RabbitMQ部署問題](#rabbitmq部署問題)

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
將路徑中`https://docs.openstack.org/kolla-ansible/latest/user/quickstart.html`
中的`latest`替換為部署目標版本的版本代號。

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
# python3 -m venv /opt/openstack/openstack-venv-2023.1
# source /opt/openstack/openstack-venv-2023.1/bin/activate.fish
```

之後安裝Ansible（需要注意Ansible版本，不能直接使用最新版本，
不同版本Kolla依賴的Ansible版本也有所差異，參考對應版本的部署文檔，當前以`2023.1`版本為例）：

```
# pip install -U pip
# pip install "ansible>=6,<8"
```

安裝Kolla Ansible（使用的Kolla分支需要匹配OpenStack的部署目標版本）：

```html
<!-- 對應Master，當前開發版 -->
# pip install git+https://opendev.org/openstack/kolla-ansible@master

<!-- 對應 OpenStack Zed 版本，其它版本類似，需要使用Kolla Ansible的對應分支 -->
# pip install git+https://opendev.org/openstack/kolla-ansible@stable/zed
<!-- Zedz之後的版本使用年月份作爲版本名稱 -->
# pip install git+https://opendev.org/openstack/kolla-ansible@stable/2023.1
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
# kolla-ansible -i ./all-in-one deploy --tags 組建名稱 <!-- 可單獨部署部分內容 -->

<!-- 部署操作順利完成後，執行後置部署操作 -->
# kolla-ansible -i ./all-in-one post-deploy <!-- 會在 /etc/kolla 路徑下生成 admin-openrc.sh 以及clouds.yaml 文件 -->
```

`kolla-genpwd`生成密碼需要`/etc/kolla/password.yml`文件已存在，password.yml文件中，
`keystone_admin_password`配置控制Horizon網管頁面以及openstack命令行工具的密碼；
`database_password`配置控制數據庫密碼。

集群部署完成後，常用管理操作：

```html
# kolla-ansible -i ./all-in-one stop <!-- 關閉服務容器 -->
# kolla-ansible -i ./all-in-one deploy-containers <!-- 啟動集群容器 -->
```

## 升級OpenStack版本
Kolla Ansible支持版本升級，基本升級流程：

1. 升級前首先創建新的venv環境
1. 參考新版本的安裝文檔，在新的venv環境中安裝ansible和kolla-ansible軟件包
1. 對比`globals.yml`、`passwords.yml`等配置，合併新版本的配置變化
（注意passwords文件中若存在新增項則應為新增項生成密碼後加入）
1. 按照部署模式對比inventory配置（all-in-one/multinode）
1. 部署新的依賴

	```html
	# kolla-ansible install-deps <!-- 安裝/升級新的依賴 -->
	# kolla-ansible -i ./all-in-one bootstrap-servers
	# kolla-ansible -i ./all-in-one prechecks <!-- 升級部署前執行檢查 -->
	```

1. 執行`upgrade`操作

	```
	# kolla-ansible -i ./all-in-one upgrade
	```

根據實際組件的版本差異和部署情況，可能部分組件會存在升級失敗的情況，
此時可嘗試手動對比配置、清理相關容器Docker卷等操作，
如果清理配置、容器後仍升級失敗，則可考慮單獨重新deploy該問題組件。

## Cinder（存儲配置）
Kolla默認配置中未開啟存儲功能，開啟存儲需要在globals.yml中啟用`enable_cinder`配置：

```yaml
enable_cinder: "yes"
enable_cinder_backend_lvm: "yes" # Cinder支持多種後端，LVM是最簡單的實現，適合all-in-one模式下使用
```

使用Cinder LVM後端需要創建名為`cinder-volumes`的LVM Volume Group，
否則會在prechecks階段得到下列錯誤：

```
...
TASK [cinder : Checking LVM volume group exists for Cinder] ************************************************************
fatal: [localhost]: FAILED! => {"changed": false, "cmd": ["vgs", "cinder-volumes"], "delta": "0:00:00.060885", "end": "2023-05-15 12:53:14.532086", "failed_when_result": true, "msg": "non-zero return code", "rc": 5, "start": "2023-05-15 12:53:14.471201", "stderr": "  Volume group \"cinder-volumes\" not found\n  Cannot process volume group cinder-volumes", "stderr_lines": ["  Volume group \"cinder-volumes\" not found", "  Cannot process volume group cinder-volumes"], "stdout": "", "stdout_lines": []}
...
```

創建cinder-volumes卷組：

```
# pvcreate 磁盤塊設備
# vgcreate cinder-volumes PV塊設備
```

## Octavia（負載均衡器配置）
啟用負載均衡器需要在globals.yml中啟用相關配置：

```yaml
enable_octavia: yes # 默認Horizon會根據Octavia配置開啟前端面板
```

部署Octavia需要首先生成相關證書文件：

```
# kolla-ansible -i ./all-in-one octavia-certificates
```

之後進行部署：

```
# kolla-ansible -i ./all-in-one deploy --tags octavia
```

## Kolla Ansible部署問題
記錄部分部署中存在的問題。

### Python依賴
Debian發行版中，需要使用包管理器安裝`python3-docker`、`python3-dbus`等軟件包
（確保系統Python環境中存在python3-docker、python3-dbus等模塊），
使用venv中的pip安裝無法通過prechecks。

### 網卡IP地址
需要相關網卡的地址與配置文件中**完全對應**，若相關網卡存在多個IP地址，
需要保證首IP的地址為配置文件中配置的地址，否則部署流程會出現各種異常。

### 清理部署環境
清理Kolla Ansible部署，除了刪除所有容器（`docker ps | xargs docker rm -f`），
還需要刪除對應的卷（`docker volume ls | xargs docker volume rm`），
Docker卷存儲了之前集群的數據，並不會刪除，
在重複部署時會繼續使用這些的容器卷，進而造成各類錯誤。

如mariadb容器繼續使用之前的卷會導致數據庫的密碼不匹配：

```
TASK [mariadb : Creating haproxy mysql user] ***************************************************************************************************************************
fatal: [localhost]: FAILED! => {"changed": false, "msg": "unable to connect to database, check login_user and login_password are correct or /var/lib/ansible/.my.cnf has the credentials. Exception message: (1045, \"Access denied for user 'root'@'staczek' (using password: YES)\")"}
```

參考[Bug #1812927](https://bugs.launchpad.net/kolla-ansible/+bug/1812927)。

若管理網絡地址發生變化，需要生成roles配置：

```
# kolla-ansible install-deps
```

否則會造成部分組件安裝檢查失敗，
如[Bug #1946506](https://bugs.launchpad.net/kolla-ansible/+bug/1946506)。

### RabbitMQ部署問題
RabbitMQ服務需要保證`/etc/hosts`文件中正確填寫管理網卡IP到主機名的映射，
否則部署RabbitMQ時會出現下列錯誤：

```
RUNNING HANDLER [rabbitmq : Waiting for rabbitmq to start on first node] ********************************************* fatal: [localhost]: FAILED! => {"changed": true, "cmd": "docker exec rabbitmq rabbitmqctl wait /var/lib/rabbitmq/mnesia/rabbitmq.pid", "delta": "0:00:00.380240", "end": "2019-09-16 10:40:17.794725", "msg": "non-zero return code", "rc": 126, "start": "2019-09-16 10:40:17.414485", "stderr": "", "stderr_lines": [], "stdout": "cannot exec in a stopped state: unknown", "stdout_lines": ["cannot exec in a stopped state: unknown"]}
```

同時RabbitMQ容器不停重啟，並輸出下列錯誤信息：

```
...
ERROR: epmd error for host openStack: address (cannot connect to host/port)
...
```

詳細問題參見[官方BUG Track](https://bugs.launchpad.net/kolla-ansible/+bug/1855935)。
