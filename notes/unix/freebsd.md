<!-- TOC -->

- [概述](#概述)
	- [與 Linux 的比較](#與-linux-的比較)
- [安裝與配置](#安裝與配置)
	- [UEFI引導](#uefi引導)
	- [GRUB2引導](#grub2引導)
- [網絡](#網絡)
	- [網卡配置](#網卡配置)
	- [無線網絡配置](#無線網絡配置)
- [服務管理](#服務管理)
- [包管理](#包管理)
	- [pkg](#pkg)
	- [Ports](#ports)
	- [安裝系統更新](#安裝系統更新)
	- [系統版本升級](#系統版本升級)
- [Jails（容器）](#jails容器)
	- [OCI](#oci)
- [GUI](#gui)
	- [Display Manager](#display-manager)
- [磁盤分區管理](#磁盤分區管理)
	- [調整分區和文件系統大小](#調整分區和文件系統大小)
	- [proc文件系統](#proc文件系統)
	- [掛載導入zfs分區](#掛載導入zfs分區)
- [limits](#limits)
	- [文件描述符數目限制](#文件描述符數目限制)
- [常用工具指令](#常用工具指令)
	- [PCI設備](#pci設備)
	- [chroot](#chroot)
	- [查看端口狀態](#查看端口狀態)
	- [查看時間與設置時區](#查看時間與設置時區)

<!-- /TOC -->



# 概述
`FreeBSD`是**開源**、**自由**的`Unix Like`操作系統。
FreeBSD繼承自`BSD`(`Berkeley Software Distribution`)系列，
是正統的Unix分支，由於法律原因，FreeBSD不能稱爲Unix；
但內核中部分使用了FreeBSD的macOS(Darwin/XNU)，獲得了`UNIX 03`認證。

相比Linux，FreeBSD更加貼近傳統Unix的設計理念。

## 與 Linux 的比較
授權協議差異：

- Linux使用`GPLv2`許可證，許可證兼容性較差，內核二次開發需要繼續開源代碼，
直接導致一些使用其它許可證的開源技術無法併入Linux內核，如`ZFS`文件系統
- FreeBSD使用`BSD`許可證，許可證寬鬆，有多家公司基於FreeBSD進行商業性的二次開發，
如`Apple`的`macOS`、`Sony`的`Play Station 3/4`等

開發模式差異：

- Linux項目僅僅包含內核開發，開發迭代較快，
上游工具鏈由不同的團隊維護，同時有衆多基於Linux內核的**發行版**
- FreeBSD項目是完整的操作系統，包含內核、設備驅動、工具鏈、文檔等，
整個系統均由同一團隊維護，因而具有較高的一致性，但開發迭代較慢，衍生發行版也較少

社區規模差異：

- Linux商業宣傳優秀，社會關注度高，開發團隊龐大，對於新硬件、新技術有較好支持
- FreeBSD關注度和商業宣傳不如Linux，開發團隊規模較小，開發進度較慢，對新硬件的支持較爲緩慢



# 安裝與配置
[FreeBSD官網](http://ftp.freebsd.org/pub/FreeBSD)提供了鏡像下載。
`ISO-IMAGES`目錄下即爲正式發佈版本的鏡像，選擇匹配的CPU架構和版本即可。

鏡像命名規則如下：

```
FreeBSD-[版本號]-RELEASE-[CPU架構]-[鏡像類型].img/iso
```

鏡像類型分爲以下幾類：

- `bootonly` 後綴名爲`iso`，僅供啓動引導使用
- `disc1` 後綴名爲`iso`，基本鏡像，包含基本軟件包
- `dvd1` 後綴名爲`iso`，包含大量常用軟件包
- `memstick` 後綴名`img`，刻錄使用鏡像，包含基本軟件包
- `memstick-mini` 後綴名`img`，刻錄使用鏡像，包含核心軟件包，最小化安裝使用

後綴名`iso`的鏡像用於虛擬機啓動，後綴名`img`的鏡像用於刻盤安裝。
刻錄鏡像使用`dd`指令，並需要添加部分參數，以`amd64`架構的`memstick-mini`鏡像爲例，刻錄指令如下：

```
# dd if='FreeBSD-[版本]-RELEASE-amd64-memstick-mini.img' of='/dev/[磁盤id]' bs=1M conv=sync
```

## UEFI引導
`FreeBSD 10`開始引入UEFI啓動支持，FreeBSD 10運行在UEFI模式下需要下載獨立的帶有`uefi`名稱的鏡像版本。
以`FreeBSD 10.3`爲例，對應的amd64刻錄鏡像名稱爲`FreeBSD-10.3-RELEASE-amd64-uefi-memstick.img`。
從`FreeBSD 11`開始，鏡像均支持UEFI啓動，不再區分是否帶有uefi。

使用`efibootmgr`可為手動生成引導菜單：

```html
<!-- 掛載ESP分區到 /boot/efi -->
# mount -t msdos ESP分區 /boot/efi

<!-- 複製引導efi到ESP分區 -->
# mkdir -p /boot/efi/ESP/FreeBSD/
$ cp /boot/loader.efi /boot/efi/ESP/FreeBSD/loader.efi

<!-- 創建引導項 -->
# efibootmgr -acl /boot/efi/EFI/FreeBSD/loader.efi -L FreeBSD
```

更多efibootmgr說明可參考[FreeBSD手冊](https://www.freebsd.org/cgi/man.cgi?query=efibootmgr)。
注意**不要**在chroot環境下使用efibootmgr創建引導項，chroot環境下生成的引導efi路徑可能不爭取。

## GRUB2引導
在`grub.conf`文件中爲FreeBSD創建啓動項，指定FreeBSD啓動文件`boot1.efi`的位置，配置如下：

```
menuentry 'FreeBSD' {
    insmod part_gpt
    insmod fat
    set root='hd0,gpt1'
    chainloader /EFI/FreeBSD/boot1.efi # FreeBSD efi文件的實際路徑
}
```

使用`boot1.efi`文件引導FreeBSD相比直接通過GRUB2啓動**BSD內核**的方式更加簡單，無需複雜的引導配置。



# 網絡
FreeBSD中使用傳統的`ifconfig`工具管理網絡，FreeBSD並不支持Linux的新一代網絡工具鏈`iproute2`。

## 網卡配置
FreeBSD中網卡配置直接寫在`/etc/rc.conf`中：

```sh
# 配置DHCP
ifconfig_網卡名稱="DHCP"

# 配置固定地址
ifconfig_網卡名稱="x.x.x.x/x" # 數值形式子網
ifconfig_網卡名稱="inet x.x.x.x/x" # 同上
ifconfig_網卡名稱="inet x.x.x.x netmask x.x.x.x" # 點分十進制子網

# 配置多個IP
ifconfig_網卡名稱_alias0="x.x.x.x/x" # 其它寫法與之前配置類似，不再贅述

# 設置默認網關
defaultrouter="x.x.x.x"
```

## 無線網絡配置
命令行環境下配置無線網絡推薦使用`wpa_supplicant`工具。
需要自行在`/etc`路徑下創建`wpa_supplicant.conf`。
配置模版如下所示：

```sh
network={
	# scan_ssid=1 # 當連接隱藏的無線熱點時需要額外添加該參數
	ssid="無線網ssid"
	psk="密碼"
}
```

無限設備需要寫入`/etc/rc.conf`中，配置規則：

```html
wlans_無線設備名稱="無線網絡接口名稱" <!-- FreeBSD中無線網絡接口名稱通常使用 wlan0 -->
ifconfig_無線網絡接口名稱="WPA DHCP"
```

無線設備名稱使用sysctl指令查詢，示例：

```
$ sysctl net.wlan.devices
sysctl net.wlan.devices: iwm0
```

可知無線設備為`iwm0`，則對應無線配置為：

```
wlans_iwm0="wlan0"
ifconfig_wlan0="WPA DHCP"
```

之後啓動網絡服務：

```
# service netif start
```

連接未加密的無線網絡，不需要使用`wpa_supplicant.conf`，直接在`/etc/rc.conf`中添加：

```
wlans_iwm0="wlan0"
ifconfig_wlan0="ssid [無線網ssid] DHCP"
```



# 服務管理
FreeBSD採用傳統的BSD風格的init系統，服務項在`/etc/rc.d`目錄下。
可以使用service命令來管理服務：

```html
# service -l <!-- 列出所有服務 -->
# service 服務名稱 onestart/onerestart/onestop <!-- 啟動/重啟/關閉服務 -->
# service 服務名稱 enable/disable <!-- 啟用/禁用開機服務自啟動 -->
```

開機自啓動的服務，以及一些系統配置存放在`/etc/rc.conf`文件中。
例如，需要開機自啓動SSH服務則可以將`sshd_enable="YES"`加入`rc.conf`文件中。

亦可使用`sysrc`工具開啟/關閉服務自啟動：

```html
<!-- 使用sysrc亦會在 /etc/rc.conf 文件中生成對應服務配置項 -->
# sysrc 服務名稱_enable=YES
# sysrc 服務名稱_enable=NO
```

常見服務配置：

```shell
hostname="MacBook" # 主機名稱
ifconfig_em0="DHCP" # 網絡DHCP
ifconfig_em0_ipv6="inet6 accept_rtadv" # ipv6
sshd_enable="YES" # ssh服務
ntpd_enable="YES" # 時間同步服務
powerd_enable="YES" # 電源管理服務
dumpdev="AUTO" # 內核錯誤轉儲服務
```



# 包管理
FreeBSD同時提供了基於源碼編譯軟件包的`Ports`系統和基於預編譯二進制包的`pkg`包管理。

## pkg
`FreeBSD 10`之後引入了新的`pkg`工具用於管理軟件包，常用指令類似與`yum/apt/dnf`：

```html
# pkg search 軟件包名稱

<!-- 安裝刪除軟件包 -->
# pkg install 軟件包名稱
# pkg remove 軟件包名稱 <!-- 移除指定軟件包 -->
# pkg autoremove 軟件包名稱 <!-- 清理不需要的依賴 -->

<!-- 升級系統已經安裝的所有軟件包 -->
# pkg upgrade

<!-- 查看已安裝的軟件包信息 -->
$ pkg info <!-- 查詢所有已安裝的軟件包 -->
$ pkg info 軟件包名稱 <!-- 查詢某個已安裝軟件包的具體信息（包括軟件包的版本、來源、安裝選項等） -->

<!-- 依賴查詢理 -->
$ pkg info -d 軟件包名稱 <!-- 查詢指定已安裝軟件包的依賴信息 -->
$ pkg all-depends 軟件包名稱 <!-- 查找指定已安裝軟件包的依賴 -->
$ pkg rall-depends 軟件包名稱 <!-- 遞歸查找軟件包的所有依賴 -->
$ pkg required-depends 軟件包名稱 <!-- 查詢指定軟件包被哪些其它包依賴 -->

<!-- 展示手動安裝的軟件包 -->
# pkg prime-list
# pkg prime-origins <!-- 包含軟件包port路徑 -->
# pkg query -e '%a = 0' %o <!-- 直接通過屬性進行查詢 -->

<!-- 修改軟件包安裝原因 -->
# pkg set -A 1 軟件包名稱 <!-- 設置軟件包為自動安裝（可被pkg autoremove清理） -->
# pkg set -A 0 軟件包名稱 <!-- 設置軟件包為手動安裝 -->
```

## Ports
`Ports`系統提供了官方源內所有軟件包的**源碼樹**，編譯安裝前能夠定製編譯參數，控制依賴項。
Ports源碼樹位於`/usr/ports`目錄之，首次使用前需要初始化Ports樹，執行：

```
# portsnap fetch extract
```

之後更新Ports樹執行：

```
# portsnap update
```

編譯Ports樹下某個軟件包的源碼只需進入對應的源碼目錄中，執行以下步驟：

1. `make config` 進入交互式界面，配置編譯依賴
1. `make` 執行編譯操作
1. `make install` 編譯完成後執行安裝操作
1. `make clean` 安裝完成後清理編譯生成的臨時文件

使用源碼編譯的軟件包安裝後同樣受到`pkg`包管理器的管理。

## 安裝系統更新
FreeBSD使用`freebsd-update`獲取和安裝系統補丁：

```html
<!-- 獲取當前版本系統的更新，更新拉取完成後會進入文件變化的預覽介面，使用 q 鍵退出預覽 -->
# freebsd-update fetch

<!-- 安裝系統更新 -->
# freebsd-update install
```

## 系統版本升級
FreeBSD並非**滾動發行版**，系統有明確的版本劃分，
升級系統版本同樣使用更新工具`freebsd-update`。

升級系統到指定版本，執行指令：

```
# freebsd-update -r 目標系統版本 upgrade
```

當前支持的系統列表可從[FreeBSD官網](https://www.freebsd.org/releases/)查詢。

以`FreeBSD 10.1`正式版為例，執行指令：

```
# freebsd-update -r 10.1-RELEASE upgrade
```

之後系統會開始下載升級所需要的補丁，下載完成之後，執行更新指令：

```
# freebsd-update install
```



# Jails（容器）
FreeBSD的容器機制稱為[`Jails`](https://docs.freebsd.org/en/books/handbook/jails/)，
是最早的容器技術實現之一，早在2000年左右（FreeBSD 4.x）便已發布。

Jails基於`chroot(2)`的概念，變更進程的root目錄，進而創建與原系統隔離的安全環境。
進程在chroot後的環境中不能訪問外部的文件和其它資源。

Jails擴展了傳統chroot的功能，傳統chroot僅限制chroot環境中進程的訪問的文件，
而其它系統資源、系統用戶、進程列表、網絡子系統等均與原系統共享，
Jails通過虛擬化對文件系統、用戶、網絡的訪問擴展了安全模型。

## OCI
[OCI](https://opencontainers.org)是行業的容器規範，Linux下主流的OCI實現是runc，
FreeBSD亦有開發者實現了[runj](https://github.com/samuelkarp/runj)，基於Jails初步實現了OCI規範。

主流容器運行時[containerd](https://containerd.io)對FreeBSD也提供了初步支持，
搭配nerdctl命令行工具可基本實現Docker容器的操作體驗，
但目前containerd的FreeBSD支持（FreeBSD 13.x版本）處於早期狀態，諸多關鍵特性缺失：

- 容器無法使用網絡（缺少CNI支持）
- 不支持compose
- 不支持build

具體可參考nerdctl中對於FreeBSD支持的
[說明](https://github.com/containerd/nerdctl/blob/main/docs/freebsd.md)。



# GUI
FreeBSD在啟用X Window Server之前需要首先安裝`drm-kmod`：

```
# pkg install drm-kmod
```

並在`/etc/rc.conf`中進行配置：

```shell
kld_list="i915kms" # Intel顯卡使用 i915kms ，AMD顯卡參照安裝時的提示
```

啟用X Window的用戶需要添加到`video`用戶組中：

```
# pw groupmod video -m 用戶名
```

之後的步驟與配置Linux X Window類似，安裝根據顯卡xf86系列驅動：

```html
# pkg install xf86-video-intel <!-- AMD 為 xf86-video-ati -->
# pkg install xf86-input-libinput <!-- 鍵盤觸摸板驅動 -->
```

## Display Manager
與Linux環境下類似，常見DM包括：

- GDM，Gnome項目提供
- SDDM，通常搭配KDE桌面
- LightDM，其它桌面/WM使用

若使用LightDM，則需要配套安裝`lightdm-gtk-greeter`，否則無法啟動。
DM服務默認不會開機自啟動，需要自啟動則在`/etc/rc.conf`中啟用對應DM：

```shell
lightdm_enable="YES" # LightDM
sddm_enable="YES" # SDDM
```



# 磁盤分區管理
FreeBSD中使用`fdisk`、`gpart`等工具管理磁盤。
使用`geom`、`diskinfo`等工具查看磁盤、分區信息。

FreeBSD中磁盤設備的命名規則也與Linux不同，
Linux下多塊磁盤按照`/dev/sda,sdb,sdc,...`命名，
磁盤內的分區(以sda為例)按照`/dev/sda1,sda2,sda3,...`命名；
FreeBSD中則按照`/dev/ada0,ada1,ada2,...`命名，
磁盤內的分區(以ada0為例)按照`/dev/ada0p1,ada0p2,ada0p3,...`命名。

Linux下磁盤設備為`block special`，FreeBSD中磁盤設備為`character special`。

fdisk工具與Linux下類似，但參數略有不同，且對GPT分區支持較差。
gpart類似Linux下的parted工具，用於GPT分區的操作：

```
$ gpart show
=>      34  31277165  ada3  GPT  (14G)
        34      1024     1  bios-boot  (512k)
      1058         6        - free -  (3.0k)
      1064  31275184     2  freebsd-zfs  (14G)
  31276248       951        - free -  (475k)

=>         34  11721045101  ada0  GPT  (5.5T)
           34           94        - free -  (47k)
          128      4194304     1  freebsd-swap  (2.0G)
      4194432  11716850696     2  freebsd-zfs  (5.5T)
  11721045128            7        - free -  (3.5k)

=>         34  11721045101  ada1  GPT  (5.5T)
           34           94        - free -  (47k)
          128      4194304     1  freebsd-swap  (2.0G)
      4194432  11716850696     2  freebsd-zfs  (5.5T)
  11721045128            7        - free -  (3.5k)

...
```

diskinfo工具則用於展示更詳盡的磁盤信息：

```
$ diskinfo -v ada1
ada1
	512         	# sectorsize
	6001175126016	# mediasize in bytes (5.5T)
	11721045168 	# mediasize in sectors
	4096        	# stripesize
	0           	# stripeoffset
	11628021    	# Cylinders according to firmware.
	16          	# Heads according to firmware.
	63          	# Sectors according to firmware.
	HGST HDN726060ALE614	# Disk descr.
	K1JVDUGD    	# Disk ident.
	No          	# TRIM/UNMAP support
	7200        	# Rotation rate in RPM
	Not_Zoned   	# Zone Mode
```

## 調整分區和文件系統大小
調整分區大小：

```html
<!-- 使用分區後的所有可用空間 -->
# gpart resize -i 分區編號 設備名稱
<!-- 擴展分區到指定大小 -->
# gpart resize -i 分區編號 -s 分區大小 設備名稱
```

調整分區大小後調整文件系統大小：

```html
# growfs 分區塊設備路徑 <!-- UFS -->
# zpool online -e 存儲池名稱 分區塊設備名稱 <!-- ZFS -->
```

## proc文件系統
FreeBSD雖支持proc文件系統，但默認並不開啟，
開啟proc文件系統可在fstab中添加掛載點：

```
proc /proc procfs rw 0 0
```

FreeBSD的proc文件系統結構與Linux中基本類似，
但相對Linux而言較為簡陋，提供的信息較少。

## 掛載導入zfs分區
查看存在的zfs pools：

```
# zpool import
```

確認名稱後導入並查看：

```
# zpool import 指定pool名稱
$ zpool list
```

若能查看到pool信息，則可進行掛載操作：

```html
<!-- 需要顯式指定文件系統為zfs -->
# mount -t zfs 指定pool名稱 掛載點
```



# limits
FreeBSD存在類似Linux下ulimit的資源限制，使用`limits`查看當前用戶的資源限制：

```
$ limits -a
Resource limits (current):
  cputime              infinity secs
  filesize             infinity kB
  datasize             33554432 kB
  stacksize              524288 kB
  coredumpsize         infinity kB
  memoryuse            infinity kB
  memorylocked         infinity kB
  maxprocesses             5734
  openfiles              512000
  sbsize               infinity bytes
  vmemoryuse           infinity kB
  pseudo-terminals     infinity
  swapuse              infinity kB
  kqueues              infinity
  umtxp                infinity
```

limits指令的常見用法：

```html
$ limits -a <!-- 查看全部類型的限制 -->
$ limits -H <!-- 查看硬限制 -->
$ limits -U 用戶名 <!-- 查看指定用戶的限制 -->
$ limits -P 進程號 <!-- 查看指定進程的限制 -->
```

使用命令行修改資源限制僅對當前環境生效，若永久生效需要修改`/etc/login.conf`配置文件；
該文件配置內容示例：

```
default:\
	...
	:filesize=unlimited:\
	:coredumpsize=unlimited:\
	:openfiles=unlimited:\
	:maxproc=unlimited:\
	...

root:\
	:ignorenologin:\
	:memorylocked=unlimited:\
	:tc=default:

...
```

`default`為默認配置，根據用戶名可設置每個用戶的獨立配置。

## 文件描述符數目限制
查看當前環境的文件描述符數目限制：

```
$ limits -n
Resource limits (current):
  openfiles              512000
```

`openfiles`（文件描述符數目限制）不僅由`/etc/login.conf`配置，
還受到`/etc/sysctl.conf`中的內核配置約束，相關配置項如下所示：

```ini
kern.maxfiles = ...
kern.maxfilesperproc = ...
```

`kern.maxfiles`控制內核允許打開的文件描述符總數；
`kern.maxfilesperproc`控制單個進程允許打開的文件描述符數目；
limits配置大於內核配置時，以內核配置為準。

FreeBSD系統中默認login.conf中配置了`openfiles=unlimited`，即不限制打開的文件描述符數目，
因此內核配置中的`kern.maxfilesperproc`即為單進程實際打開的文件描述符數目限制。



# 常用工具指令
FreeBSD下大量工具指令與Linux中不同。

## PCI設備
Linux下使用`lspci`查看PCI設備，FreeBSD中則使用`pciconf`：

```html
$ pciconf -h
usage: pciconf -l [-bcv]
       pciconf -a selector
       pciconf -r [-b | -h] selector addr[:addr2]
       pciconf -w [-b | -h] selector addr value

$ pciconf -l
hostb0@pci0:0:0:0:  class=0x060000 card=0x00000000 chip=0x12378086 rev=0x02 hdr=0x00
isab0@pci0:0:1:0:  class=0x060100 card=0x00000000 chip=0x70008086 rev=0x00 hdr=0x00
atapci0@pci0:0:1:1:  class=0x01018a card=0x00000000 chip=0x71118086 rev=0x01 hdr=0x00
vgapci0@pci0:0:2:0:  class=0x030000 card=0x00000000 chip=0xbeef80ee rev=0x00 hdr=0x00
em0@pci0:0:3:0:   class=0x020000 card=0x001e8086 chip=0x100e8086 rev=0x02 hdr=0x00
none0@pci0:0:4:0:  class=0x088000 card=0x00000000 chip=0xcafe80ee rev=0x00 hdr=0x00
none1@pci0:0:7:0:  class=0x068000 card=0x00000000 chip=0x71138086 rev=0x08 hdr=0x00
atapci1@pci0:0:13:0:  class=0x010601 card=0x00000000 chip=0x28298086 rev=0x02 hdr=0x00

$ pciconf -lv <!-- 查看完整信息 -->
hostb0@pci0:0:0:0: class=0x060000 card=0x00000000 chip=0x12378086 rev=0x02 hdr=0x00
    vendor     = 'Intel Corporation'
    device     = '82440/1FX 440FX (Natoma) System Controller'
    class      = bridge
    subclass   = HOST-PCI
isab0@pci0:0:1:0: class=0x060100 card=0x00000000 chip=0x70008086 rev=0x00 hdr=0x00
    vendor     = 'Intel Corporation'
    device     = 'PIIX3 PCI-to-ISA Bridge (Triton II) (82371SB)'
    class      = bridge
    subclass   = PCI-ISA
atapci0@pci0:0:1:1: class=0x01018a card=0x00000000 chip=0x71118086 rev=0x01 hdr=0x00
    vendor     = 'Intel Corporation'
    device     = 'PIIX4/4E/4M IDE Controller (82371AB/EB/MB)'
    class      = mass storage
    subclass   = ATA
...
```

## chroot
FreeBSD中chroot操作比Linux更加簡便，無須重新綁定`/proc`、`/sys`等關鍵路徑，
只需目標路徑是有效的跟路徑即可正常chroot。

默認操作下，chroot後`/dev`路徑下只有`/dev/null`，
要使devfs正常工作需要在chroot前掛載devfs到chroot掛載點的dev路徑上：

```
# mount -t devfs devfs 掛載點/dev
```

## 查看端口狀態
FreeBSD中查看端口使用`sockstat`工具：

```
# sockstat -l
USER     COMMAND    PID   FD PROTO  LOCAL ADDRESS         FOREIGN ADDRESS
root     sshd       1016  3  tcp6   *:22                  *:*
root     sshd       1016  4  tcp4   *:22                  *:*
...
```

## 查看時間與設置時區
FreeBSD中查看時間操作與Linux中類似，使用`date`指令：

```
$ date
Mon Oct 17 22:21:40 CST 2022
```

FreeBSD中提供了時區配置工具`tzsetup`，執行該指令後會出現TUI窗口：

```
$ tzsetup
```

在菜單列表中選取目標時區即可。
