<!-- TOC -->

- [概述](#概述)
	- [與 Linux 的比較](#與-linux-的比較)
- [安裝與配置](#安裝與配置)
	- [UEFI引導](#uefi引導)
	- [GRUB2引導](#grub2引導)
- [無線網絡配置](#無線網絡配置)
- [服務管理](#服務管理)
- [包管理](#包管理)
	- [pkg](#pkg)
	- [Ports](#ports)
	- [系統版本升級](#系統版本升級)
- [GUI](#gui)
	- [Display Manager](#display-manager)
- [常用工具指令](#常用工具指令)
	- [PCI設備](#pci設備)
	- [磁盤分區管理](#磁盤分區管理)
	- [掛載導入zfs分區](#掛載導入zfs分區)
	- [chroot](#chroot)

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



# 無線網絡配置
命令行環境下配置無線網絡推薦使用`wpa_supplicant`工具。
需要自行在`/etc`路徑下創建`wpa_supplicant.conf`。
配置模版如下所示：

```shell
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

```
# service [服務名稱] [start | stop | status]
```

開機自啓動的服務，以及一些系統配置存放在`/etc/rc.conf`文件中。
例如，需要開機自啓動SSH服務則可以將`sshd_enable="YES"`加入`rc.conf`文件中。

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
# pkg install 軟件包名稱
# pkg search 軟件包名稱
# pkg remove 軟件包名稱
# pkg autoremove 軟件包名稱
# pkg info <!-- 查詢所有已安裝的軟件包 -->
# pkg info 軟件包名稱 <!-- 查詢某個軟件包的具體信息(包括軟件包的文件組成，依賴關係，來源等) -->
# pkg query -e '%a = 0' %o <!-- 展示手動安裝的軟件包 -->
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

## 系統版本升級
FreeBSD並非**滾動發行版**，系統有明確的版本劃分，升級系統版本需要使用升級工具`freebsd-update`。
升級到指定版本，執行指令：

```
# freebsd-update -r [版本號-發佈狀態] upgrade
```

以`FreeBSD 10.1`正式版，執行指令：

```
# freebsd-update -r 10.1-RELEASE upgrade
```

之後系統會開始下載升級所需要的補丁，下載完成之後，執行更新指令：

```
# /usr/sbin/freebsd-update install
```



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

## 磁盤分區管理
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

## chroot
FreeBSD中chroot操作比Linux更加簡便，無須重新綁定`/proc`、`/sys`等關鍵路徑，
只需目標路徑是有效的跟路徑即可正常chroot。

默認操作下，chroot後`/dev`路徑下只有`/dev/null`，
要使devfs正常工作需要在chroot前掛載devfs到chroot掛載點的dev路徑上：

```
# mount -t devfs devfs 掛載點/dev
```
