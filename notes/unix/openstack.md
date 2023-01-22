<!-- TOC -->

- [OpenStack面板常用功能](#openstack面板常用功能)
- [OpenStackClient](#openstackclient)
	- [配置OpenStack認證](#配置openstack認證)
	- [OpenStackClient配置文件](#openstackclient配置文件)

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
    auth:
      ...
    region_name: RegionOne
  集群名稱3:
  ...
```

對於在配置文件中記錄的集群信息，需要添加`--os-cloud`參數指定集群名稱進行訪問：

```
$ openstack --os-cloud 集群名稱 ...
```
