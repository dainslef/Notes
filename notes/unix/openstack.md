<!-- TOC -->

- [OpenStack面板常用功能](#openstack面板常用功能)
- [OpenStackClient](#openstackclient)
    - [配置OpenStack認證](#配置openstack認證)
    - [OpenStackClient配置文件](#openstackclient配置文件)
- [Kolla Ansible](#kolla-ansible)
    - [Debian Stable部署流程](#debian-stable部署流程)
    - [Kolla Ansible鏡像](#kolla-ansible鏡像)
    - [升級OpenStack版本](#升級openstack版本)
        - [Kolla Ansible 2024.2](#kolla-ansible-20242)
    - [Cinder（存儲配置）](#cinder存儲配置)
    - [Octavia（負載均衡器配置）](#octavia負載均衡器配置)
    - [Kolla Ansible部署問題](#kolla-ansible部署問題)
        - [Python依賴](#python依賴)
        - [網卡IP地址](#網卡ip地址)
        - [清理指定組件](#清理指定組件)
        - [清理部署環境](#清理部署環境)
        - [RabbitMQ部署問題](#rabbitmq部署問題)
        - [恢復MariaDB數據庫](#恢復mariadb數據庫)
- [Horizon](#horizon)
    - [VIP](#vip)
    - [部署Horizon開發環境](#部署horizon開發環境)
    - [編寫Horizon插件](#編寫horizon插件)
- [問題記錄](#問題記錄)
    - [虛擬機綁定浮動IP無法選取分配端口](#虛擬機綁定浮動ip無法選取分配端口)
    - [虛擬機配置的VIP無法通信](#虛擬機配置的vip無法通信)
    - [虛擬機進入Error狀態](#虛擬機進入error狀態)
    - [InstanceNotFound: Instance xxx-xxx-... could not be found.](#instancenotfound-instance-xxx-xxx--could-not-be-found)

<!-- /TOC -->



# OpenStack面板常用功能
OpenStack的常用功能菜單。

| 菜單 | 功能描述 |
| :- | :- |
| Project - Compute - Overview | 當前項目的資源配額 |
| Identity - Projects - Modify Quotas | 修改當前項目配額 |
| Admin - Compute - Hypervisors | 集群所有節點實際資源分佈 |
| Admin - Compute - Flavors | 管理虛擬機規格 |



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

Kolla Ansible的官方鏡像托管在紅帽的鏡像平臺[Quay.io](https://quay.io/organization/openstack.kolla)中，
部分版本的用Kolla Ansible在發佈時鏡像可能未同步更新（如2024.2初版），
升級版本前需檢查對應版本的Docker鏡像是否已更新到托管平臺。

## Debian Stable部署流程
以Debian Stable版本與Kolla Ansible部署OpenStack All in One，
選用netinst.iso鏡像並配置最小化依賴，保留下列軟件包即可：

```
# apt install 7zip apparmor apt-file bind9-dnsutils btop btrfs-progs build-essential cmake curl docker.io ethtool fish git grub-efi-amd64 iproute2 iputils-ping locales lvm2 manpages-dev ncat network-manager nmap openssh-server parted pciutils python3-venv screen sysbench systemd-timesyncd tzdata usbutils vim wpasupplicant
```

以當前的Debian係發行版為例，首先安裝Python venv，並進入虛擬環境：

```html
<!-- 安裝 venv，創建並進入虛擬環境 -->
# apt install python3-venv
# python3 -m venv /opt/openstack/openstack-venv-版本號
# source /opt/openstack/openstack-venv-版本號/bin/activate.fish
```

之後安裝Ansible（需要注意Ansible版本，不能直接使用最新版本，
不同版本Kolla依賴的Ansible版本也有所差異，參考對應版本的部署文檔）。
實際Ansible不必直接安裝，安裝kolla-ansible時通常會自動安裝合適版本的Ansible作為依賴。

以`2023.1`版本為例，安裝Ansible：

```
# pip install -U pip
# pip install "ansible>=6,<8"
```

安裝Kolla Ansible（使用的Kolla分支需要匹配OpenStack的部署目標版本）：

```html
<!-- 穩定版本 -->
# pip install git+https://opendev.org/openstack/kolla-ansible@stable/版本號
<!-- 對應 OpenStack Zed 版本，其它版本類似，需要使用Kolla Ansible的對應分支 -->
# pip install git+https://opendev.org/openstack/kolla-ansible@stable/zed
<!-- Zed之後的版本使用年月份作爲版本名稱 -->
# pip install git+https://opendev.org/openstack/kolla-ansible@stable/2023.1
...
<!-- 對應Master，當前開發版 -->
# pip install git+https://opendev.org/openstack/kolla-ansible@master
```

複製默認配置：

```html
# mkdir -p /etc/kolla

<!-- 配置文件包括 globals.yml 和 passwords.yml  -->
# cp /opt/openstack/openstack-venv-版本/share/kolla-ansible/etc_examples/kolla/* /etc/kolla

<!-- 使用all-in-one安裝-->
# cp /opt/openstack/openstack-venv-版本/share/kolla-ansible/ansible/inventory/all-in-one .
```

編輯配置文件`/etc/kolla/globals.yml`，核心配置內容：

```yml
...
kolla_base_distro: "ubuntu" # 設置鏡像基於的發行版，基於Ubuntu的鏡像通常經過較為充分的測試，同時體積較小，推薦選用
openstack_release: "20xx.x" # 指定部署的OpenStack版本，默認的master為開發中版本，不穩定，不推薦使用
...
network_interface: "網卡設備" # 管理網
kolla_internal_vip_address: "x.x.x.x" # VIP地址，若禁用haproxy/proxysql，則填寫管理網網卡地址
neutron_external_interface: "網卡設備" # 虛擬機業務網
enable_haproxy: "no" # 是否啓用HAProxy，默認啓用，All in One部署無需開啟
enable_proxysql: "no" # 是否啓用ProxySQL，默認啓用，All in One部署無需開啟
...
enable_skyline: "yes" # Skyline是下一代OpenStack管理面板，推薦啓用
...
kolla_container_engine: "podman" # 容器引擎，支持docker或podman
...
# 存儲配置部分查看Cinder相關段落
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

<!-- 檢查並安裝依賴軟件包，創建/etc/hosts域名映射，禁用防火墻、配置docker等 -->
# kolla-ansible bootstrap-servers -i ./all-in-one

<!-- 部署檢查 -->
# kolla-ansible prechecks -i ./all-in-one

<!-- 順利通過檢查後可執行部署操作 -->
# kolla-ansible deploy -i ./all-in-one
# kolla-ansible deploy -i ./all-in-one --tags 組件名稱 <!-- 可單獨部署部分內容 -->

<!-- 部署操作順利完成後，執行後置部署操作 -->
# kolla-ansible post-deploy -i ./all-in-one <!-- 會在 /etc/kolla 路徑下生成 admin-openrc.sh 以及clouds.yaml 文件 -->
```

`kolla-genpwd`生成密碼需要`/etc/kolla/password.yml`文件已存在，password.yml文件中，
`keystone_admin_password`配置控制Horizon/Skyline網管頁面以及openstack命令行工具的密碼；
`database_password`配置控制數據庫密碼。

`bootstrap-servers`操作不是必要的，相關的軟件包安裝、環境配置可以手動執行；
2024.2版本之後的kolla-ansible工具改為了Python實現，部分依賴轉移到了venv環境中，
但bootstrap-servers依舊在系統環境安裝依賴，導致依賴配置不正確，且安裝了大量不必要依賴；
手動配置步驟：

- 添加host主機名映射
- 在venv環境中安裝Python依賴

    ```html
    <!--
    需要環境中安裝依賴用於編譯dbus-python：
    apt install build-essential cmake python3-dev pkg-config libdbus-1-dev libglib2.0-dev
    -->
    # pip install dbus-python

    <!-- 對於docker容器引擎，需要在venv中安裝docker包 -->
    # pip install podman

    <!-- 對於podman容器引擎，需要在venv中安裝podman包 -->
    # pip install podman
    ```

-  手動配置docker，

    創建`/etc/docker/daemon.json`，關閉docker網橋、IP轉發功能，並添加日誌限制：

    ```json
    {
        "bridge": "none",
        "ip-forward": false,
        "iptables": false,
        "log-opts": {
            "max-file": "5",
            "max-size": "50m"
        }
    }
    ```

集群部署完成後，常用管理操作：

```html
# kolla-ansible stop -i ./all-in-one  <!-- 關閉服務容器 -->
# kolla-ansible deploy-containers -i ./all-in-one <!-- 啟動集群容器 -->
```

## Kolla Ansible鏡像
Kolla Ansible在部署時會根據部署與發行版配置拉取對應的OpenStack組件鏡像，
鏡像tag命名規則為：

```
OpenStack版本-操作系統-操作系統版本
```

示例，`OpenStack 2024.2`版本，使用`Ubuntu 24.04`基礎鏡像，則鏡像tag為：

```
2024.2-ubuntu-noble
```

組件鏡像託管在[RED HAT Quay.io](https://quay.io/organization/openstack.kolla)。
在同一個OpenStack大版本內，鏡像也會定期更新，單獨更新鏡像可手動pull對應鏡像之後重新配置組件：

```
# kolla-ansible reconfigure -i ./all-in-one -t 組件名稱
```

## 升級OpenStack版本
Kolla Ansible支持版本升級，基本升級流程：

1. 升級前首先創建新的venv環境
1. 參考新版本的安裝文檔，在新的venv環境中安裝ansible和kolla-ansible軟件包
1. 對比`globals.yml`、`passwords.yml`等配置，合併新版本的配置變化
（注意passwords文件中若存在新增項則應為新增項生成密碼後加入）
1. 按照部署模式對比inventory配置（`all-in-one`或`multinode`）
1. 部署新的依賴

    ```html
    # kolla-ansible install-deps <!-- 安裝/升級新的依賴 -->
    # kolla-ansible bootstrap-servers -i ./all-in-one
    # kolla-ansible prechecks -i ./all-in-one <!-- 升級部署前執行檢查 -->
    ```

1. 執行`upgrade`操作

    ```
    # kolla-ansible upgrade -i ./all-in-one
    ```

根據實際組件的版本差異和部署情況，可能部分組件會存在升級失敗的情況，
此時可嘗試手動對比配置、清理相關容器Docker卷等操作，
如果清理配置、容器後仍升級失敗，則可考慮單獨重新deploy該問題組件。

### Kolla Ansible 2024.2
從`kolla-ansible 2024.2`版本開始kolla-ansible存在較大變化，
不再使用bash脚本實現，改爲Python脚本實現，部分參數結構存在變化，
如`-i`參數現在應放在特定操作之後（舊版本-i參數放在操作之前）：

```
# kolla-ansible prechecks -i ./all-in-one
# kolla-ansible deploy -i ./all-in-one
# kolla-ansible upgrade -i ./all-in-one
```

早期版本中部分Python API依賴需要通過系統包管理器安裝如`docker`、`dbus-python`等，
自2024.2版本開始系統包管理器安裝的依賴無法識別，需要改爲統一使用pip安裝：

```html
# pip install docker dbus-python
```

在Debian發行版中，使用pip安裝dbus-python可能需要編譯，
需要額外使用apt安裝下列依賴才能正常完成編譯流程：

```
# apt install build-essential cmake python3-dev pkg-config libdbus-1-dev libglib2.0-dev
```

部署完成後這些依賴不再需要，可以移除（但升級OpenStack版本時需要再次安裝）。

2024.2版本中，Nova/Cinder/Glance等數據庫同樣存在一定變化，
升級後可能會出現下列問題：

- 無法啓動虛擬機（iscsid服務錯誤，找不到磁盤）
- 無法創建鏡像（Cinder/Glance數據庫結構變化，添加了SWAP等配置）

## Cinder（存儲配置）
Kolla默認配置中未開啟存儲功能，開啟存儲需要在globals.yml中啟用`enable_cinder`配置：

```yaml
enable_cinder: "yes"
enable_cinder_backend_lvm: "yes" # Cinder支持多種後端，LVM是最簡單的實現，適合all-in-one模式下使用
```

使用Cinder LVM後端需要安裝lvm軟件包：

```
# apt install lvm2
```

使用Cinder LVM後端還需要在LVM中創建名為`cinder-volumes`的Volume Group（卷組），
用於存放虛擬機磁盤（卷）：

```
# pvcreate 磁盤塊設備
# vgcreate cinder-volumes PV塊設備1,PV塊設備2...
```

否則會在prechecks階段得到下列錯誤：

```
...
TASK [cinder : Checking LVM volume group exists for Cinder] ************************************************************
fatal: [localhost]: FAILED! => {"changed": false, "cmd": ["vgs", "cinder-volumes"], "delta": "0:00:00.060885", "end": "2023-05-15 12:53:14.532086", "failed_when_result": true, "msg": "non-zero return code", "rc": 5, "start": "2023-05-15 12:53:14.471201", "stderr": "  Volume group \"cinder-volumes\" not found\n  Cannot process volume group cinder-volumes", "stderr_lines": ["  Volume group \"cinder-volumes\" not found", "  Cannot process volume group cinder-volumes"], "stdout": "", "stdout_lines": []}
...
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

### 清理指定組件
從部署中清理指定組件，需要刪除對應組件的相關內容：

- 容器
- 容器卷
- 組件配置目錄（`/etc/kolla/組件名稱`）
- 組件日誌目錄（`/var/log/kolla/組件名稱`）
- 數據庫中對應組件的Schema

清理相關組件的上述內容後，編輯globals.yml，取消對應組件的相關配置（enable_xxx等），
之後reconfigure集群。

### 清理部署環境
完整清理Kolla Ansible部署環境，除了刪除所有容器，還需要刪除對應的卷，
以及生成的配置和日誌和對應的MariaDB數據庫：

```html
<!-- 移除全部容器 -->
# docker ps -a --format "{{.Names}}" | xargs docker rm -f
<!-- 移除全部卷 -->
# docker volume ls --format "{{.Name}}" | xargs docker volume rm

<!-- 移除配置文件（保留配置和密碼文件如globals.yml以及passwords.yml） -->
# rm -rf /etc/kolla/*
<!-- 移除日誌 -->
# rm -rf /var/log/kolla/*
```

Docker卷存儲了之前集群的數據，並不會刪除。
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

### 恢復MariaDB數據庫
OpenStack部署多個計算節點時，數據庫組件MariaDB會以集群模式（Galera Cluster）運行，
集群掉電重啟後可能會出現同步異常導致數據庫容器反覆重啟。

首先需要確認數據的主節點，查看MariaDB的WSREP同步信息（在mariadb.log中會定期輸出），通常結構如下：

```
...
2024-08-13 10:32:26 0 [Warning] WSREP: Quorum: No node with complete state:

    Version      : 4
    Flags        : 0x1
    Protocols    : 0 / 8 / 3
    State        : NON-PRIMARY
    Desync count : 0
    Prim state   : NON-PRIMARY
    Prim UUID    : 00000000-0000-0000-0000-000000000000
    Prim  seqno  : -1
    First seqno  : -1
    Last  seqno  : 40342010
    Prim JOINED  : 0
    State UUID   : 4704f897-591c-11ef-8fcb-5f019917158e
    Group UUID   : dfb9d6d3-a91c-11ed-8b26-9a72676f2337
    Name         : 'nmssuperf03'
    Incoming addr: '10.21.22.13:3306'

    Version      : 4
    Flags        : 00
    Protocols    : 0 / 8 / 3
    State        : NON-PRIMARY
    Desync count : 0
    Prim state   : NON-PRIMARY
    Prim UUID    : 00000000-0000-0000-0000-000000000000
    Prim  seqno  : -1
    First seqno  : -1
    Last  seqno  : 40342010
    Prim JOINED  : 0
    State UUID   : 4704f897-591c-11ef-8fcb-5f019917158e
    Group UUID   : dfb9d6d3-a91c-11ed-8b26-9a72676f2337
    Name         : 'nmssuperf02'
    Incoming addr: '10.21.22.12:3306'

    Version      : 4
    Flags        : 0x2
    Protocols    : 0 / 8 / 3
    State        : NON-PRIMARY
    Desync count : 0
    Prim state   : SYNCED
    Prim UUID    : 41a589ae-591c-11ef-9eb5-72d652d8a8e4
    Prim  seqno  : 19
    First seqno  : -1
    Last  seqno  : 40341907
    Prim JOINED  : 1
    State UUID   : 4704f897-591c-11ef-8fcb-5f019917158e
    Group UUID   : dfb9d6d3-a91c-11ed-8b26-9a72676f2337
    Name         : 'nmssuperf01'
    Incoming addr: '10.21.22.11:3306'
```

通常`Last  seqno`數值最大的節點即為數據最新的節點。

之後開始下列恢復步驟：

1. 選擇數據最新的計算節點作為恢復節點，停止該節點的MariaDB容器
1. 編輯`/var/lib/docker/volumes/mariadb/_data/grastate.dat`文件，
將`safe_to_bootstrap`值修改為`1`
1. 編輯`/etc/kolla/mariadb/config.json`文件，
將`"command": "/usr/bin/mariadbd-safe"`修改為
`"command":"/usr/bin/mysqld_safe --wsrep-new-cluster"`
1. 之後重啟該節點的MariaDB容器
1. 觀察其它計算節點的MariaDB容器恢復正常運行，
若狀態正常則將之前修改的`/etc/kolla/mariadb/config.json`文件恢復默認內容。

使用docker logs指令並不能直接查看到MariaDB數據庫服務的運行日誌，
服務運行日誌位於`/var/lib/docker/volumes/kolla_logs/_data/mariadb/mariadb.log`文件
（可使用Kolla的符號鏈接路徑`/var/log/kolla/mariadb/mariadb.log`）。



# Horizon
[Horizon](https://docs.openstack.org/horizon/latest/)是OpenStack管理面板的官方實現。

## VIP
Kolla Ansible默認啟用了VIP配置，All in One部署時不需要VIP，
可禁用VIP（禁用enable_haproxy/enable_proxysql）；
若繼續使用VIP，則訪問Horizon管理面板時需要使用VIP地址。

直接使用管理網地址依舊可以訪問Horizon管理面板，
但部分功能可能會出現各類錯誤（如Glance服務鏡像上傳問題）。

## 部署Horizon開發環境
構建Horizon的開發環境，參考
[Horizon貢獻者Quickstart](https://docs.openstack.org/horizon/latest/contributor/quickstart.html)。

首先確認目標環境的OpenStack版本，從[Horizon官方倉庫](https://github.com/openstack/horizon)中
拉取對應分支的代碼，從`setup.cfg`中查看該Horizon版本支持的Python版本，準備對應版本的Python環境。

Horizon運行需要`gettext`工具，默認配置還會啟用用`memcached`作為緩存（未運行memcached會出現錯誤訊息
[`RuntimeError("Unable to create a new session key.")`](https://stackoverflow.com/questions/6869198/how-can-i-prevent-runtimeerrorunable-to-create-a-new-session-key)），
以Debian係發行版為例，安裝上述軟件包，並運行memcached：

```
# apt install gettext memcached
$ memcached &
```

使用pip安裝`tox`工具：

```
$ pip install -U pip tox
```

使用tox在OpenStack源碼根路徑下執行：

```html
$ tox -e runserver <!-- 默認監聽 127.0.0.1:8000 -->
$ tox -e runserver -- 0.0.0.0:8000 <!-- 自定義地址 -->
```

Horizon使用Django框架開發，因此遵循其文件佈局和配置方法。

## 編寫Horizon插件
插件編寫可參考官方[Horizon插件教程](https://docs.openstack.org/horizon/latest/contributor/tutorials/plugin.html)，
以及[Horizon面板構建教程](https://docs.openstack.org/horizon/latest/contributor/tutorials/dashboard.html)。

Horizon的組件按層級分為：

1. Dashboard，頂層菜單，如`Project/Admin/Identity...`
1. Panel Group，面板組，如`Project - Compute/Volumes/Network...`
1. Panel，面板，如`Project - Compute - Overview/Instances/Images...`
1. Tab，面板標籤頁，如`Project - Network - Network Topology - Topology/Graph`



# 問題記錄
記錄一些OpenStack中遇到的問題。

## 虛擬機綁定浮動IP無法選取分配端口
檢查虛擬機所在的網絡是否為共享網絡，若非共享網絡則需配置為共享網絡。

浮動IP網絡與虛擬機網絡之間需要創建虛擬路由器，
浮动IP所在的網絡設置為網關，並開啟SNAT。

## 虛擬機配置的VIP無法通信
需要在虛擬機的接口配置中添加VIP的綁定地址對：

```
Project -> Compute -> Instances -> 目標網絡接口 -> Allowed Address Pairs
```

在地址對中填寫VIP地址和接口的Mac地址；
或者直接關閉接口安全選項（不推薦）。

## 虛擬機進入Error狀態
當虛擬機部分操作失敗時會進入Error狀態，此時無法啟動虛擬機，
通常進入Error狀態並不意味著虛擬機被損壞，可通過指令重置虛擬機狀態後重啟虛擬機：

```
$ openstack server set --state active 虛擬機ID
$ openstack server reboot 虛擬機ID
```

通常虛擬機在重啟後會恢復正常。

## InstanceNotFound: Instance xxx-xxx-... could not be found.
當虛擬機遷移失敗等操作造成虛擬機數據庫中部分數據失效時可能會產生該錯誤信息。

首先可嘗試重置虛擬機狀態後重啟虛擬機，若重啟虛擬機後依舊出現相同錯誤，
則可嘗試使用創建虛擬機時使用的鏡像Rebuild虛擬機，菜單路徑：

```
Admin - Compute - Instances - 虛擬機 - Rebuild Instance
```

若虛擬機硬盤數據正常，則通常可恢復。
