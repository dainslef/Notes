<!-- TOC -->

- [OpenWRT的安裝和升級](#openwrt的安裝和升級)
	- [系統安裝](#系統安裝)
	- [系統升級](#系統升級)
- [Breed](#breed)
	- [Breed Web UI](#breed-web-ui)
	- [Redmi Router AC2100](#redmi-router-ac2100)
- [OpenWrt基本配置](#openwrt基本配置)
	- [opkg包管理器](#opkg包管理器)
		- [opkg軟件源](#opkg軟件源)
		- [基本包管理操作](#基本包管理操作)
		- [常用軟件包](#常用軟件包)
		- [禁止/恢復軟件包升級](#禁止恢復軟件包升級)
		- [軟件包安裝狀態](#軟件包安裝狀態)
		- [強制安裝軟件包](#強制安裝軟件包)
		- [強制覆蓋文件](#強制覆蓋文件)
		- [未配置的安裝包](#未配置的安裝包)
	- [切換默認Shell](#切換默認shell)
	- [Dropbear SSH](#dropbear-ssh)
	- [服務管理](#服務管理)
	- [語言設置](#語言設置)
	- [無線網絡功能配置](#無線網絡功能配置)
	- [系統日誌](#系統日誌)
	- [內核日誌](#內核日誌)
- [UCI](#uci)
	- [UCI基本操作](#uci基本操作)
- [LuCI](#luci)
	- [實用LuCI插件](#實用luci插件)
	- [LuCI頁面緩存問題](#luci頁面緩存問題)
- [文件系統與存儲機制](#文件系統與存儲機制)
	- [存儲掛載](#存儲掛載)
		- [掛載USB存儲](#掛載usb存儲)
		- [掛載SD卡存儲](#掛載sd卡存儲)
		- [使用文件作為SWAP](#使用文件作為swap)
	- [OverlayFS](#overlayfs)
		- [使用OverlayFS作為exroot（擴展根分區）](#使用overlayfs作為exroot擴展根分區)
		- [OverlayFS的工作機制](#overlayfs的工作機制)
		- [OverlayFS與系統升級的兼容性](#overlayfs與系統升級的兼容性)
		- [OverlayFS與Docker的兼容性](#overlayfs與docker的兼容性)
- [OpenWRT Clash](#openwrt-clash)
	- [luci-app-clash](#luci-app-clash)
	- [OpenClash](#openclash)
- [OpenWRT衍生固件](#openwrt衍生固件)
	- [ImmortalWrt](#immortalwrt)
	- [FriendlyWrt](#friendlywrt)
		- [修改FriendlyWrt的Overlay配置](#修改friendlywrt的overlay配置)
		- [Docker服務未自啟動](#docker服務未自啟動)
- [構建OpenWRT官方固件](#構建openwrt官方固件)
- [構建GL.iNET廠家固件](#構建glinet廠家固件)
	- [內核版本配置](#內核版本配置)
- [USB WIFI](#usb-wifi)

<!-- /TOC -->



# OpenWRT的安裝和升級
在[OpenWRT官方下載頁面](https://downloads.openwrt.org)可下載官方固件。
OpenWRT對各路由器機型的支持參考[OpenWRT Wiki](https://openwrt.org/toh/start)。

## 系統安裝
`mtd`是路由器刷機使用的固件寫入工具，用於向路由器中刷寫操作系統。

路由器的分區信息寫在`/proc/mtd`文件中，不同機型不同固件會有不同的分區信息，示例：

```html
<!-- Mi Router 4C, Official Firmware  -->
$ cat /proc/mtd
dev:    size   erasesize  name
mtd0: 01000000 00010000 "ALL"
mtd1: 00020000 00010000 "Bootloader"
mtd2: 00010000 00010000 "Config"
mtd3: 00010000 00010000 "Factory"
mtd4: 00010000 00010000 "crash"
mtd5: 00010000 00010000 "cfg_bak"
mtd6: 00100000 00010000 "overlay"
mtd7: 00c60000 00010000 "OS1"
mtd8: 00b00000 00010000 "rootfs"
mtd9: 00200000 00010000 "disk"

<!-- Redmi Router AC2100, Official Firmware  -->
$ cat /proc/mtd
dev:    size   erasesize  name
mtd0: 07f80000 00020000 "ALL"
mtd1: 00080000 00020000 "Bootloader"
mtd2: 00040000 00020000 "Config"
mtd3: 00040000 00020000 "Bdata"
mtd4: 00040000 00020000 "Factory"
mtd5: 00040000 00020000 "crash"
mtd6: 00040000 00020000 "crash_syslog"
mtd7: 00040000 00020000 "cfg_bak"
mtd8: 00400000 00020000 "kernel0"
mtd9: 00400000 00020000 "kernel1"
mtd10: 01a00000 00020000 "rootfs0"
mtd11: 01a00000 00020000 "rootfs1"
mtd12: 02600000 00020000 "overlay"
mtd13: 01b80000 00020000 "obr"
mtd14: 00c1c000 0001f000 "ubi_rootfs"
mtd15: 021e8000 0001f000 "data"

<!-- Redmi Router AC2100, OpenWrt Firmware  -->
$ cat /proc/mtd
dev:    size   erasesize  name
mtd0: 00080000 00020000 "Bootloader"
mtd1: 00040000 00020000 "Config"
mtd2: 00040000 00020000 "Bdata"
mtd3: 00040000 00020000 "factory"
mtd4: 00040000 00020000 "crash"
mtd5: 00040000 00020000 "crash_syslog"
mtd6: 00040000 00020000 "reserved0"
mtd7: 00400000 00020000 "kernel_stock"
mtd8: 00400000 00020000 "kernel"
mtd9: 07580000 00020000 "ubi"
```

使用mtd將固件寫入目標分區：

```
# mtd -r write 固件路徑 分區名稱
```

使用mtd工具刷機，通常應使用factory固件，
而非OpenWRT系統升級時使用的sysupgrade固件。

使用mtd重置系統：

```
# mtd erase rootfs_data
```

## 系統升級
在LuCI的`System - Backup / Flash Firmware`介面選擇`Flash new firmware image`菜單進行系統升級；
亦可使用`sysupgrade`工具進行系統升級：

```html
<!-- 系統升級，升級鏡像通常名稱中包含sysupgrade字樣 -->
# sysupgrade 升級參數 升級鏡像

<!-- 配置備份參數 -->
# sysupgrade 備份參數 備份文件
```

使用sysupgrade升級系統時，需要注意所使用升級固件的mtd分區佈局，
分區佈局需要與最初安裝系統時使用的factory固件兼容。否則會造成路由器變磚。

sysupgrade主要參數：

| 參數 | 說明 |
| :- | :- |
| -n | 升級不保留任何配置 |
| -c | 保留 `/etc` 目錄下的所有變化配置 |
| -v | 輸出更詳細的操作日誌 |
| -b | 創建備份 |
| -r | 恢復備份 |
| -l | 列出備份 |

OpenWRT的系統升級會清空整個根文件系統（根據配置項可保留`/etc`下的配置），
升級後的系統所有用戶安裝的軟件包會清空，若升級時選擇保留配置，
則保留`/etc`路徑下的內容，系統以及用戶軟件包的配置將會保留。
若保留配置，則多數系統配置如Wifi、密碼、防火牆、ssh等配置可直接應用到新環境中，
用戶軟件包也可在升級後重新安裝繼續使用保留的配置。

為避免潛在的軟件包升級不兼容，亦可僅保留核心配置`/etc/config`路徑。

需要注意，系統升級前若修改了`/etc/passwd`設置了非預裝的shell作為默認shell，
則升級前應修改回默認的`/bin/ash`，否則升級後因為軟件包重置、shell不存在，而導致ssh無法連接。




# Breed
[Breed](https://breed.hackpascal.net/)是由[hackpascal](https://github.com/hackpascal)
開發的閉源Bootloader固件，俗稱「不死鳥」，能夠提供各類增强功能。

Breed主要特性：

- 實時刷機進度。
- Web刷機模式。
- Telnet，免TTL進入Breed命令行。

刷機方式與刷入OpenWrt等固件操作類似：

1. 獲取SSH登入權限
1. 進入命令行，查看ROM分區佈局`cat /proc/mtd`
1. 使用`mtd`工具刷機，Breed固件應刷入`Bootloader`分區

## Breed Web UI
通常當路由器啟動失敗，會自動進入Breed；
或者按住路由器復位鍵直至系統狀態指示燈閃爍後會重啟進入Breed。

進入Breed後，使用計算機網口與路由器的任意LAN口連接，
計算機的網口設置DHCP（通常會被分配地址`192.168.1.2`），
打開瀏覽器，訪問頁面`http://192.168.1.1`，即可進入Breed Web UI。

在Breed Web UI中，刷機使用的固件應為`initramfs-kernel.bin`固件，
而非OpenWRT升級使用的`squashfs-sysupgrade.bin`固件。

## Redmi Router AC2100
紅米路由器AC2100可使用紅米路由器3G的[Breed固件](https://breed.hackpascal.net/breed-mt7621-xiaomi-r3g.bin)，
Breed環境變量配置中需要添加`xiaomi.r3g.bootfw`字段，值為`2`，否則Breed無法正常引導OpenWRT系統。

在Breed中使用升級`initramfs-kernel.bin`固件OpenWRT啟動後後若出現下列提示：

```
System running in recovery (initramfs) mode.
No changes to settings will be stored and are lost after rebooting.
This mode should only be used to install a firmware upgrade.
```

則應進入OpenWRT系統中，使用sysupgrade指令重新刷入`squashfs-sysupgrade.bin`固件：

```
# sysupgrade -n openwrt-ramips-mt7621-xiaomi_redmi-router-ac2100-squashfs-sysupgrade.bin
```

問題詳情可參考[GitHub Issues](https://github.com/openwrt/openwrt/issues/10010)。



# OpenWrt基本配置
[`OpenWrt`](https://openwrt.org/)是當下最流行的Linux嵌入式路由系統。

## opkg包管理器
[Opkg package manager](https://openwrt.org/docs/guide-user/additional-software/opkg)
是OpenWrt系統內置的包管理器。

### opkg軟件源
opkg包管理器的軟件源配置文件為`/etc/opkg/distfeeds.conf`。

官方OpenWRT軟件源配置結構如下：

```
src/gz openwrt_core https://downloads.openwrt.org/openwrt/releases/openwrt版本號/targets/芯片廠家/芯片架構/packages
src/gz openwrt_base https://downloads.openwrt.org/openwrt/releases/openwrt版本號/packages/cpu架構/base
src/gz openwrt_luci https://downloads.openwrt.org/openwrt/releases/openwrt版本號/packages/cpu架構/luci
src/gz openwrt_packages https://downloads.openwrt.org/openwrt/releases/openwrt版本號/packages/cpu架構/packages
src/gz openwrt_routing https://downloads.openwrt.org/openwrt/releases/openwrt版本號/packages/cpu架構/routing
src/gz openwrt_telephony https://downloads.openwrt.org/openwrt/releases/openwrt版本號/packages/cpu架構/telephony
```

其中`openwrt_core`倉庫提供內核模塊，與Linux內核版本以及特定芯片型號相關，
而其它倉庫中的軟件包則不依賴Linux內核版本以及芯片型號，通常僅需CPU架構相同即可使用。

本地源配置：

```
src/gz xxx_local_mirror file:///xxx/xxx...
```

替換軟件源為牆國軟件源：

```html
<!-- 替換為牆國USTC源 -->
# sed -i 's/downloads.openwrt.org/mirrors.ustc.edu.cn\/openwrt/g' /etc/opkg/distfeeds.conf

<!-- 替換為牆國TUNA源 -->
# sed -i 's_downloads.openwrt.org_mirrors.tuna.tsinghua.edu.cn/openwrt_' /etc/opkg/distfeeds.conf
```

USTC源通常更新較慢，TUNA源更新更及時。

對於部分非官方倉庫（如GL.iNET的廠家倉庫），默認配置下更新源會得到證書校驗失敗的錯誤：

```
root@OpenWrt:~# opkg update
Downloading https://fw.gl-inet.cn/releases/v21.02-SNAPSHOT/kmod-4.0/arm_cortex-a7/ip60xx/Packages.gz
Updated list of available packages in /var/opkg-lists/glinet_core
Downloading https://fw.gl-inet.cn/releases/v21.02-SNAPSHOT/kmod-4.0/arm_cortex-a7/ip60xx/Packages.sig
Signature check failed.
Remove wrong Signature file.
...
```

對於非官方倉庫，應關閉簽名校驗，編輯`/etc/opkg.conf`，註釋證書校驗相關內容：

```sh
# option check_signature
```

### 基本包管理操作
OpenWRT提供的opkg包管理器被設計運行在嵌入式環境中，
因此遠比傳統的包管理器更加輕量級，功能也更加簡陋。

基本操作：

```html
<!-- 查詢軟件包 -->
# opkg list "*軟件包關鍵字*"
<!-- 查詢已安裝的軟件包 -->
# opkg list-installed "*軟件包關鍵字*"

<!-- 安裝軟件包 -->
# opkg install 軟件包名稱
# opkg install --force-depends 軟件包名稱 <!-- 強制安裝軟件包 -->
# opkg install --noaction 軟件包名稱 <!-- 模擬安裝過程 -->

<!-- 移除軟件包 -->
# opkg remove 軟件包名稱
# opkg remove --autoremove 軟件包名稱 <!-- 移除軟件包（同時移除軟件包的孤兒依賴） -->

<!-- 列出軟件包內容 -->
# opkg files 軟件包名稱
```

opkg並未直接提供升級所有軟件包功能，可利用管道操作組合指令實現：

```
# opkg list-upgradable | cut -f 1 -d ' ' | xargs -r opkg upgrade --force-overwrite
```

在OpenWRT中，升級所有軟件包的操作有一定危險性，
當當使用自編譯固件時，應儘量避免使用該功能，
自行編譯的固件可能與官方源的軟件包不兼容（例如部分軟件包的動態鏈接庫不匹配）。

### 常用軟件包
記錄常用的軟件包：

```html
# opkg install
<!-- 常用程序，所有設備均安裝 -->
fish file lsblk htop iperf3 tcpdump nmap-full screen
luci-app-adblock luci-app-ddns luci-app-nlbwmon luci-app-ttyd
<!-- 帶有USB接口的設備可作為下載服務器 -->
luci-app-aria2 ariang luci-app-samba4 kmod-fs-exfat kmod-usb-storage-uas usbutils rsync
<!-- 有SD卡插槽，需要手動配置Overlay的設備可安裝 -->
block-mount fdisk

<!--
VIM編輯器，busybox自帶的vi功能簡陋，多數VIM常用指令都未實現，
OpenWRT中vim分為三個版本vim/vim-full/vim-fuller，
其中vim為tiny-build，關閉了大多數VIM特性，建議使用vim-full(normal-build)或更完整的vim-fuller(big-build)
-->
vim-full
<!-- 存儲空間足夠的設備可安裝全功能版本的VIM -->
vim-fuller

<!-- OpenWRT2020 主題 -->
luci-theme-openwrt-2020

<!-- ImmortalWRT 以及部分國產固件可直接從軟件源中安裝 OpenClash -->
luci-app-openclash
<!-- ImmortalWRT 不需要安裝溫度檢測器，UI直接提供處理器溫度展示，其它系統需要安裝用於查看處理器溫度 -->
lm-sensors

<!-- ARM64 架構的設備可安裝 Docker -->
luci-app-dockerman
```

MT762x系列芯片若未識別出SD卡，則可嘗試安裝SD卡驅動（SD卡正常識別則無需安裝）：

```
# opkg install kmod-sdhci-mt7620
```

### 禁止/恢復軟件包升級
可通過設置軟件包flag為`hold`禁止軟件包升級：

```
# opkg flag hold 軟件包名稱
```

設置flag為`user`可恢復軟件包升級：

```
# opkg flag user 軟件包名稱
```

### 軟件包安裝狀態
系統中已安裝的軟件包信息存儲在`/rom/usr/lib/opkg/status`文件中，
軟件包信息示例：

```
# cat /rom/usr/lib/opkg/status
...
Package: luci-app-firewall
Version: git-22.089.67741-3856d50
Depends: libc, firewall
Status: install user installed
Architecture: all
Installed-Time: 1650113974
Auto-Installed: yes
...
```

查找所有手動安裝的軟件包（ash語法）：

```ash
$ for i in `opkg list-installed | sed 's/ - .*//'`; do if !(cat /rom/usr/lib/opkg/status | grep -q "Package: $i") && !(opkg whatdepends $i | grep -q "depends on $i"); then echo $i; fi; done
```

查找所有手動安裝的軟件包（fish語法，添加自動修改安裝原因功能）：

```fish
#! /usr/bin/fish

set package_status /usr/lib/opkg/status
set rom_package_status /rom$package_status
if [ -e $rom_package_status ]
	set rom_packages (cat $rom_package_status)
end

# Transform the package status contents, and save package info to a list.
for package_info in (cat $package_status | tr '\n' ';' | sed 's/;;/\n/g')
	if not string match -q "*Auto-Installed: yes*" $package_info
		# Find packages which are not auto installed.
		set package_name (string match -r "(?<=Package: )[\w\.-]+" $package_info)
		# Check if package not in rom (pre-installed).
		if not string match -q "*Package: $package_name*" $rom_packages
			if not opkg whatdepends $package_name | grep -q "depends on $package_name" # Check the package depends result code.
				set package_used_info "clean"
			else
				set package_used_info "used by others"
				# Add the current package info to a package list.
				set dependency_packages $dependency_packages $package_name
			end
			echo "$package_name($package_used_info)"
		end
	end
end

# Check if packages which need change the installed reason exist.
if set -q dependency_packages
	echo -e "=====================================================================\n"
	echo -e "Packages which can change the installed resaon:\n$dependency_packages\n"
	read -p 'echo "Do you need to change packge install reason? (yes/NO) "' need_change_install_resaon
	# Check the user input.
	if [ $need_change_install_resaon = yes ]; or [ $need_change_install_resaon = y ]
		for dependency_package in $dependency_packages
			# Find the packge line number in the file "/usr/lib/opkg/status".
			set line_number (cat /usr/lib/opkg/status | grep -nE "^Package: $dependency_package\$" | awk -F':' '{print $1}')
			set insert_line_number (math $line_number + 1)
			# Check if the line number is valid.
			if string match -qr '^[0-9]+$' $insert_line_number
				echo "Change package [$dependency_package](line $insert_line_number) install resaon to Auto-Installed."
				sed "$insert_line_number i Auto-Installed: yes" -i /usr/lib/opkg/status
			else
				echo Find invalid line number, skip the install reason change operation!
			end
		end
	end
end
```

### 強制安裝軟件包
當使用自編譯鏡像時，安裝內核模塊會出現依賴不滿足的錯誤，
因為即使源碼、配置無任何改動，自編譯鏡像的內核版本與倉庫中內核模塊依賴信息中的小版本也號不相符，
具體參見[OpenWRT官方文檔](https://openwrt.org/faq/cannot_satisfy_dependencies)。

錯誤示例：

```html
<!-- 安裝內核模塊，提示內核版本不滿足依賴要求 -->
# opkg install kmod-fs-exfat
Installing kmod-fs-exfat (4.14.90+2017-06-20-de4c760b-1) to root...
Downloading http://fw.gl-inet.cn/releases/v18.06.5/kmod-3.8/siflower/sf19a28_nand/kmod-fs-exfat_4.14.90%2b2017-06-20-de4c760b-1_mips_siflower.ipk
Collected errors:
 * satisfy_dependencies_for: Cannot satisfy the following dependencies for kmod-fs-exfat:
 * 	kernel (= 4.14.90-1-8e7f05250007b3b96947722cb34fb82f) *
 * opkg_install_cmd: Cannot install package kmod-fs-exfat.

<!-- 查看內核版本信息，可知內核小版本號不滿足要求 -->
# opkg info kernel
Package: kernel
Version: 4.14.90-1-36a80e72295637cf4e383d8ee24054dd
Depends: libc
Status: install user installed
Architecture: mips_siflower
Installed-Time: 1661108424
```

解決方案是直接編譯需要的模塊，或安裝時使用`--force-depends`參數強制安裝：

```
# opkg install --force-depends kmod-fs-exfat
Installing kmod-fs-exfat (4.14.90+2017-06-20-de4c760b-1) to root...
Downloading http://fw.gl-inet.cn/releases/v18.06.5/kmod-3.8/siflower/sf19a28_nand/kmod-fs-exfat_4.14.90%2b2017-06-20-de4c760b-1_mips_siflower.ipk
Configuring kmod-fs-exfat.
Collected errors:
 * satisfy_dependencies_for: Cannot satisfy the following dependencies for kmod-fs-exfat:
 * 	kernel (= 4.14.90-1-8e7f05250007b3b96947722cb34fb82f) *

# opkg info kmod-fs-exfat
Package: kmod-fs-exfat
Version: 4.14.90+2017-06-20-de4c760b-1
Depends: kernel (= 4.14.90-1-8e7f05250007b3b96947722cb34fb82f), kmod-nls-base
Status: install user installed
Section: kernel
Architecture: mips_siflower
Size: 51043
Filename: kmod-fs-exfat_4.14.90+2017-06-20-de4c760b-1_mips_siflower.ipk
Description: Kernel module for ExFAT Filesytems
Installed-Time: 1661238557
```

強制安裝依舊會輸出依賴不滿足的告警信息，但軟件包已安裝成功。

儘管內核模塊版本不匹配可使用強制安裝解決依賴不滿足的問題，
但若存在大量內核模塊需要安裝時操作較為繁瑣，應考慮使用修改內核軟件包版本信息的方式。

### 強制覆蓋文件
部分軟件包會出現文件衝突，例如：

```
# opkg info libnl-tiny1
Package: libnl-tiny1
Version: 2020-08-05-c291088f-2
Depends: libc
Provides: libnl-tiny
Status: install user installed
Architecture: aarch64_cortex-a53
Installed-Time: 1657334765

# opkg info libnl-tiny2022-05-17
Package: libnl-tiny2022-05-17
Version: 2022-05-17-b5b2ba09-1
Depends: libc
Provides: libnl-tiny
Status: install ok not-installed
Section: libs
Architecture: aarch64_cortex-a53
Size: 17681
Filename: libnl-tiny2022-05-17_2022-05-17-b5b2ba09-1_aarch64_cortex-a53.ipk
Description: This package contains a stripped down version of libnl

# opkg upgrade libnl-tiny2022-05-17
Installing libnl-tiny2022-05-17 (2022-05-17-b5b2ba09-1) to root...
Collected errors:
 * check_data_file_clashes: Package libnl-tiny2022-05-17 wants to install file /usr/lib/libnl-tiny.so
	But that file is already provided by package  * libnl-tiny1
 * check_data_file_clashes: Package libnl-tiny2022-05-17 wants to install file /usr/lib/libnl-tiny.so
	But that file is already provided by package  * libnl-tiny1
 * check_data_file_clashes: Package libnl-tiny2022-05-17 wants to install file /usr/lib/libnl-tiny.so
	But that file is already provided by package  * libnl-tiny1
 * check_data_file_clashes: Package libnl-tiny2022-05-17 wants to install file /usr/lib/libnl-tiny.so
	But that file is already provided by package  * libnl-tiny1
opkg: exited with status 255; aborting
```

系統內存在兩個不同軟件包均提供`/usr/lib/libnl-tiny.so`，會導致另一個軟件包安裝/升級失敗，
通常可採用刪除其中一個軟件包的方式解決（如`dnsmasq`和`dnsmasq-full`、`tcpdump`和`tcpdump-full`等），
若產生文件衝突的軟件包同時被依賴，則需要使用`--force-overwrite`參數強制覆蓋文件，繞過依賴錯誤。

### 未配置的安裝包
當安裝流程中出現錯誤，會導致部分軟件包處於未配置（部分安裝）狀態：

```html
<!-- 狀態為 install ok not-installed，無Installed-Time屬性，僅標記而未實際安裝 -->
# opkg info kmod-ikconfig
Package: kmod-ikconfig
Version: 5.4.203-1
Depends: kernel (= 5.4.203-1-5379bb746f374ca43bbbef0b8a9c7bab)
Status: install ok not-installed
Section: kernel
Architecture: aarch64_cortex-a53
Size: 41972
Filename: kmod-ikconfig_5.4.203-1_aarch64_cortex-a53.ipk
Description: Kernel configuration via /proc/config.gz

# opkg install kmod-ikconfig
Installing kmod-ikconfig (5.4.203-1) to root...
Downloading https://mirrors.vsean.net/openwrt/releases/21.02.1/targets/sunxi/cortexa53/packages/kmod-ikconfig_5.4.203-1_aarch64_cortex-a53.ipk
Configuring kmod-ikconfig.

<!-- 重新安裝後狀態為 install user installed，出現Installed-Time屬性，已完成安裝 -->
# opkg info kmod-ikconfig
Package: kmod-ikconfig
Version: 5.4.203-1
Depends: kernel (= 5.4.203-1-5379bb746f374ca43bbbef0b8a9c7bab)
Status: install user installed
Section: kernel
Architecture: aarch64_cortex-a53
Size: 41972
Filename: kmod-ikconfig_5.4.203-1_aarch64_cortex-a53.ipk
Description: Kernel configuration via /proc/config.gz
Installed-Time: 1664909591
```

## 切換默認Shell
OpenWrt中默認使用ash，功能較弱，可通過包管理器安裝fish：

```
# opkg install fish
```

OpenWrt使用Busybox提供輕量級的系統環境，因此並未提供chsh用於切換shell，
可手動修改`/etc/passwd`文件修改指定用戶的shell：

```html
<!-- 將原先的 /bin/ash 改為 /usr/bin/fish -->
root:x:0:0:root:/root:/usr/bin/fish
...
```

需要保證使用的shell已加入`/etc/shells`文件中。

## Dropbear SSH
OpenWRT並未使用主流的SSH實現（OpenSSH），
而選用了更加輕量級的[`Dropbear SSH`](https://matt.ucc.asn.au/dropbear/dropbear.html)。
Dropbear的軟件體積和資源消耗相比OpenSSH低得多，更加適合OpenWRT的應用場景。

Dropbear的SFTP功能需在編譯時開啟，部分固件的Dropbear僅並未提供該功能，
此時可安裝`openssh-sftp-server`：

```
# opkg install openssh-sftp-server
```

從`OpenSSH 9.0`版本開始，scp默認使用`SFTP`協議，但Dropbear並不支持；
使用`OpenSSH 9.0`之後的scp向Dropbear提供的服務傳輸文件時，會得到下列錯誤：

```
$ scp xxx root@OpenWRT:/xxx
ash: /usr/libexec/sftp-server: not found
scp: Connection closed
```

可通過在路由中安裝`openssh-sftp-server`解決該問題；
亦可在客戶端使用scp指令時添加`-O`參數，此時scp將使用傳統模式工作：

```
$ scp -O xxx root@OpenWRT:/xxx
```

該問題可參見[OpenWRT官方論壇](https://forum.openwrt.org/t/ash-usr-libexec-sftp-server-not-found-when-using-scp/125772)
中的相關討論。

## 服務管理
OpenWRT使用傳統SysV init風格腳本管理，服務腳本位於`/etc/init.d`路徑下。
服務腳本提供統一格式的操作指令，以Dropbear SSH為例：

```html
Syntax: /etc/init.d/dropbear [command]

Available commands:
	start           Start the service
	stop            Stop the service
	restart         Restart the service
	reload          Reload configuration files (or restart if service does not implement reload)
	enable          Enable service autostart
	disable         Disable service autostart
	enabled         Check if service is started on boot
	killclients     Kill dropbear processes except servers and yourself
	running         Check if service is running
	status          Service status
	trace           Start with syscall trace
```

使用`enable`服務指令開啟服務自啟動會在`/etc/rc.d`路徑下創建對應服務的**符號鏈接**；
使用`disable`服務指令關閉服務自啟動則會對應移除`/etc/rc.d`路徑下的符號鏈接。

與其它 OpenWRT還提供了`service`指令管理服務：

```
# serivce 服務名稱 start/stop/restart/status
```

在`OpenWRT 21.02`及之前版本中，service指令僅是ash中的alisa，不可在其它shell中使用，
自`OpenWRT 22.03`版本開始，service指令為獨立腳本，位於`/sbin/service`，可在其它shell中使用。

服務管理亦可在LuCI頁面的`System - Startup`頁面中配置。

## 語言設置
LuCI介面語言在配置`/etc/config/luci`中：

```
...
config internal 'languages'
	option en 'English'
	option jp '日本語'
	option zh_tw '台湾語'
	option zh_cn 'シナ語'
...
```

除英文外，其它語言需要安裝對應語言包，語言相關包以`luci-i18n`為前綴：

```
# opkg list 'luci-i18n*'
...
luci-i18n-base-en - git-21.282.73955-9987b39 - Translation for luci-base - English
...
luci-i18n-base-fr - git-21.282.73955-9987b39 - Translation for luci-base - Français (French)
...
luci-i18n-base-ja - git-21.282.73955-9987b39 - Translation for luci-base - 日本語 (Japanese)
...
luci-i18n-base-zh-cn - git-21.282.73955-9987b39 - Translation for luci-base - 简体中文 (Chinese Simplified)
luci-i18n-base-zh-tw - git-21.282.73955-9987b39 - Translation for luci-base - 繁體中文 (Chinese Traditional)
...
```

卸載語言包不會移除對應語言的配置項，需要手動移除對應配置。

## 無線網絡功能配置
部分不直接支持無線網絡的設備中，固件未繼承無線網絡功能，需要手動安裝相關軟件包。
使用AP模式（Access Point）模式需要`hostapd`，
而連接/創建WPA系列的加密熱點需要`wpa_supplicant`。

在OpenWRT中，可安裝此類功能對應的軟件包，亦可直接安裝`wpad`，
wpad整合了AP和加密功能需要的工具：

```
# opkg install wpad

# opkg files wpad
Package wpad (2022-01-16-cff80b4f-13.1) is installed on root and has the following files:
/usr/sbin/wpad
/usr/sbin/hostapd
/usr/sbin/wpa_supplicant
```

## 系統日誌
系統日誌是OpenWRT中的調試/監控手段。
OpenWRT的日誌系統詳細說明參見[OpenWRT Wiki](https://openwrt.org/docs/guide-user/base-system/log.essentials)。

標準的日誌功能使用`logd`實現，查看日誌服務狀態：

```
# service log status
```

默認將日誌存儲在**內存**中，
因此默認不存在`/var/log/syslog`文件。
讀取日誌使用`logread`指令：

```html
<!-- 列出所有系統日誌 -->
$ logread

<!-- 按照指定標籤過濾系統日誌 -->
$ logread -e 標籤

<!-- 持續輸出新系統日誌到終端 -->
$ logread -f
```

系統日誌配置位於`/etc/config/system`中，
可通過配置寫入日誌到磁盤文件中：

```
config system
	...
	option log_file '/var/log/syslog'
	...
```

修改配置後需要重啟日誌相關服務使其生效：

```
# service log restart
# service system restart
```

## 內核日誌
OpenWRT查看內核日誌與標準Linux類似：

```
$ dmesg
```



# UCI
[`Unified Configuration Interface(UCI)`](https://openwrt.org/docs/guide-user/base-system/uci)
是OpenWRT的核心配置接口；OpenWRT使用中心化的配置管理方式，
系統中的所有核心配置均位於`/etc/config`路徑下，通過UCI配置接口來進行管理。

核心配置說明：

| 配置路徑 | 配置功能 |
| :- | :- |
| /etc/config/system | 核心系統配置 |
| /etc/config/network | 接口、交換機、路由配置 |
| /etc/config/wireless | 無線網絡配置 |
| /etc/config/fstab | 掛載點配置（需要block-mount軟件包） |

多數OpenWRT軟件源中提供的第三方軟件包也已適配了UCI配置接口。

## UCI基本操作
UCI中的配置項均以`Key = Value`的格式呈現，Key的結構為`a.b.c...`，
查看系統配置：

```html
<!-- 查看當前系統的所有配置 -->
# uci show

<!-- 查看特定的配置項 -->
# uci show 配置前綴
```

設置系統配置：

```html
# uci set 配置鍵=配置值

<!-- 列出當前修改的配置內容 -->
# uci changes

<!-- 與其它交換機、路由器系統類似，配置需要提交才會保存 -->
# uci commit

<!-- 撤銷尚未提交的改動 -->
# uci revert
```



# LuCI
[LuCI](https://openwrt.org/docs/guide-user/luci/luci.essentials)為OpenWRT提供了易於使用的Web管理UI，
較新版本的OpenWRT默認均已搭載了LuCI（除了部分RAM小於32MB的設備）。

LuCI的配置項位於`/etc/config/luci`中。

## 實用LuCI插件
LuCI插件通常使用`luci-app-*`風格命名。

常用插件說明：

| 插件名稱 | 說明 |
| :- | :- |
| luci-app-ttyd | Web終端 |
| luci-app-samba4 | Samba存儲的Web頁面 |
| luci-app-adblock | 廣告攔截器 |
| luci-app-aria2 | 下載引擎 |
| luci-app-ddns | DDNS客戶端 |
| luci-app-nlbwmon | 基於Netlink的流量統計插件，以圖表的形式統計流量數據 |
| luci-app-dockerman | Docker容器管理器 |
| luci-theme-openwrt-2020 | 新版OpenWRT主題 |

## LuCI頁面緩存問題
安裝新組件時，可能會出現LuCI頁面不展示新增組件的情況，重新登出登入刷新頁面無效
（例如，在不帶無線網絡功能的NanoPi R4S固件中，安裝`wpad`和相關網絡驅動後，
LuCI頁面中的`Netwok - Wireless`選項依舊未出現）。

解決此類問題需要清空LuCI頁面緩存，緩存相關內容：

```
$ ls /tmp
...
luci-indexcache.REijbCDPVD1Bo3fSx9KSo..lua
luci-indexcache.UpzsmQTTuMZQLJFrSiwgj0.json
luci-modulecache/
...
```

刪除即可：

```
# rm /tmp/luci-*
```



# 文件系統與存儲機制
多數OpenWRT鏡像默認未集成存儲相關工具，安裝常用工具：

```html
<!-- 安裝 lsblk fdisk -->
# opkg install fdisk lsblk
```

使用掛載文件系統需要安裝啟用對應的內核模塊：

```html
<!-- ext4文件系統 -->
# opkg install e2fsprogs <!-- mkfs.ext4 等 -->
# opkg install kmod-fs-ext4

<!-- f2fs文件系統 -->
# opkg install f2fs-tools <!-- mkfs.f2fs 等 -->
# opkg install kmod-fs-f2fs
```

內核模塊`kmod-fs-ntfs`對NTFS文件系統支持較差，
使用內核模塊掛載NTFS會出現目錄顯示不全、無法被Samba共享等問題，
推薦使用`ntfs-3g`，能正常展示NTFS文件系統內容：

```
# opkg install ntfs-3g
```

## 存儲掛載
通過`block-mount`軟件包實現自動掛載存儲：

```
# opkg install block-mount
```

存儲掛載相關配置詳情可參考[OpenWRT官方文檔](https://openwrt.org/docs/techref/block_mount)。

安裝block-mount軟件包後，luci介面中會出現`System - Mount Points`菜單，
可在該頁面中設置文件系統掛載配置；
block-mount軟件包亦會生成`/etc/config/fstab`配置文件，
亦可在該配置中手動加入掛載配置。

掛載配置語法：

```sh
config global
	...
	# 配置文件系統和swap是否自動掛載
	# 啟用該選項後，mount配置自動設置 option enabled '1'
	option auto_swap '1'
	option auto_mount '1'
	...

config mount # 掛載普通分區
	option target '/xxx/xxx' # 設置掛載點
	option uuid 'xxx_uuid' # 通過UUID掛載分區
	option enabled '1' # 設置該掛載項是否使用（0：否，1：是，下同）
	option enabled_fsck '1' # 配置是否檢查後掛載文件系統

config mount
	option target '/xxx/xxx' # 設置掛載點
	option device '/dev/xxx' # 通過設備名稱掛載分區

config swap # 掛載swap分區
	option uuid 'xxx_uuid'
...
```

block-mount軟件包提供了`block`工具可查看各個分區的狀態、掛載、文件系統等信息：

```
# block info
/dev/mtdblock6: UUID="2118722505" VERSION="1" TYPE="ubi"
/dev/ubiblock0_0: UUID="86b6559c-7bba04fb-5f6ce299-53272fd0" VERSION="4.0" MOUNT="/rom" TYPE="squashfs"
/dev/ubi0_1: UUID="85f078b9-7bf6-4f4d-a9f1-2fe9d12fcfc1" VERSION="w4r0" MOUNT="/overlay" TYPE="ubifs"
/dev/sda1: UUID="0000001800000048" TYPE="ntfs"
...
```

block工具在fish下存在BUG，不會輸出任何信息。

### 掛載USB存儲
對於具有USB接口的設備，可通過USB接口連接外置硬盤等設備將OpenWRT路由用作NAS。
相關說明可參考[OpenWRT官方文檔](https://openwrt.org/docs/guide-user/storage/usb-drives)。

應安裝USB存儲內核模塊，否則無法識別USB存儲設備：

```html
<!-- uas 模塊包含多數現代 USB 3.0 移動硬盤設備的支持 -->
# opkg install kmod-usb-storage-uas
```

### 掛載SD卡存儲
對於具有SD卡槽的設備，需要安裝對應的內核模塊，否則無法識別設備：

```
# opkg install kmod-sdhci
```

部分設備可能需要安裝特定芯片的內核模塊，如使用`mt7620`芯片組的設備：

```
# opkg install kmod-sdhci-mt7620
```

安裝對應的內核模塊後，SD卡設備即會出現，通常為`/dev/mmcblk*`。

### 使用文件作為SWAP
對於內存較小但存儲較大的設備，可在本地創建文件作為swap，將其設置為loop設備，然後掛載swap分區。

安裝相關內核模塊和工具：

```html
<!--
kmod-loop 提供loop設備
losetup 用於將將swap文件配置為loop設備
 -->
# opkg install kmod-loop losetup
```

創建並掛載swap分區：

```html
<!--
示例，在 /mnt/swap 路徑下創建64MB大小的swap文件，實際大小為 bs * count
dd if=/dev/zero of=/mnt/swap bs=1M count=64
-->
# dd if=/dev/zero of=swap文件路徑 bs=單位 count=數目 <!-- 創建用作swap分區的文件 -->

# mkswap swap文件路徑 <!-- 創建swap文件系統 -->
# losetup /dev/loop0 swap文件路徑 <!-- 將swap文件設置為loop設備 -->
# swapon /dev/loop0 <!--開啟swap分區 -->
```

要使系統在啟動時自動啟用swap則應將對應操作加入`/etc/rc.local`中：

```sh
# Enable swap.
losetup /dev/loop0 swap文件路徑
swapon /dev/loop0
```

## OverlayFS
[OverlayFS](https://en.wikipedia.org/wiki/OverlayFS)是Linux下實現的一種**聯合文件系統**，
可將多各文件系統整合、疊加為一個。

### 使用OverlayFS作為exroot（擴展根分區）
對於支持SD卡/USB等外置存儲的設備，可將外置存儲作為設備的exroot（擴展根分區），
參考[OpenWRT官方文檔](https://openwrt.org/docs/guide-user/additional-software/extroot_configuration)。

掛載外置存儲設備（以SD卡設備為例），拷貝現有overlay文件系統的內容到新分區：

```
# mount /dev/mmcblk0p1 /mnt
# cp -r /overlay/upper /mnt
```

使用`block info`查看用作overlay分區設備，
之後編輯`/etc/config/fstab`，添加新的overlay分區的掛載信息：

```
...
config mount
	option device '/dev/xxx...'
	option target '/overlay'
	option enabled '1'
	option enabled_fsck '1'
```

之後重啟路由器即可。

### OverlayFS的工作機制
在OpenWRT中，會先掛載根路徑，並以此啟動系統，之後掛載OverlayFS，
OverlayFS會疊加在原先的根分區上，組合並覆蓋原先文件系統的內容，
之後系統根據組合後的新文件系統重新加載OpenWRT。

OverlayFS的掛載需要將`block-mount`安裝在原先的根分區中，
在原先的根分區中正確配置`/etc/config/fstab`，保證基礎系統能正確掛載OverlayFS。

### OverlayFS與系統升級的兼容性
在OpenWRT系統升級後，原先的OverlayFS無法繼續作為exroot直接使用，
在內核啟動階段，會得到下列錯誤信息：

```
...
[   15.288606] BTRFS: device fsid a0a91f5d-caaa-4b75-84f0-9d7d5d39d03c devid 1 transid 2777 /dev/mmcblk0p2 scanned by block (608)
[   15.303212] BTRFS info (device mmcblk0p2): flagging fs with big metadata feature
[   15.310616] BTRFS info (device mmcblk0p2): using free space tree
[   15.316647] BTRFS info (device mmcblk0p2): has skinny extents
[   15.352849] BTRFS info (device mmcblk0p2): enabling ssd optimizations
[   15.370100] block: extroot: UUID mismatch (root: d7449c47-e8e73a77-ff8e465b-f8fc502b, overlay: 7964a8e1-d046b75a-49cd2de4-ecf28bff)
...
```

提示分區的UUID不匹配，導致掛載exroot失敗。

OpenWRT的OverlayFS會將底層分區UUID寫在`etc/.extroot-uuid`文件中，掛載OverlayFS時進行校驗。
若升級後的系統與之前的系統兼容（OpenWRT小版本升級），
則移除該文件或相關路徑，即可繼續使用之前的OverlayFS。

實際使用過程中，視OverlayFS中安裝的軟件包而異，即使是兼容的小版本升級，
修改`.extroot-uuid`成功掛載了OverlayFS作為exroot，
依舊可能會出現其它小問題，如lan網橋DHCP失敗等。

### OverlayFS與Docker的兼容性
Docker的`data-root`若配置在OpenWRT的OverlayFS，
且OverlayFS的Upper文件系統使用ext4/xfs等傳統文件系統時，
會出現兼容性問題，Docker初始化時出現下列異常信息：

```
WARN[0000] containerd config version `1` has been deprecated and will be removed in containerd v2.0, please switch to version `2`, see https://github.com/containerd/containerd/blob/main/docs/PLUGINS.md#version-header
WARN[2022-09-25T05:31:47.499935622Z] failed to load plugin io.containerd.snapshotter.v1.devmapper  error="devmapper not configured"
WARN[2022-09-25T05:31:47.501471245Z] could not use snapshotter devmapper in metadata plugin  error="devmapper not configured"
ERRO[2022-09-25T05:31:47.505957948Z] failed to initialize a tracing processor "otlp"  error="no OpenTelemetry endpoint: skip plugin"
ERRO[2022-09-25T05:31:47.558108176Z] failed to mount overlay: invalid argument     storage-driver=overlay2
ERRO[2022-09-25T05:31:47.558431050Z] exec: "fuse-overlayfs": executable file not found in $PATH  storage-driver=fuse-overlayfs
ERRO[2022-09-25T05:31:47.570146703Z] AUFS was not found in /proc/filesystems       storage-driver=aufs
ERRO[2022-09-25T05:31:47.572906449Z] failed to mount overlay: invalid argument     storage-driver=overlay
ERRO[2022-09-25T05:31:47.573019324Z] Failed to built-in GetDriver graph devicemapper /root/docker
WARN[2022-09-25T05:31:47.718922187Z] Could not load necessary modules for IPSEC rules: protocol not supported
...
```

出現改異常後，Docker創建容器時出現錯誤：

```
# docker create -i --name ubuntu ubuntu
Error response from daemon: operation not supported
```

出該該錯誤的原因是，Docker在ext4/xfs等傳統文件系統上會使用overlay存儲驅動掛載data-root路徑，
若data-root路徑若已在OverlayFS中，則多層疊加overlay會導致錯誤。

解決方案可以是將data-root遷移到非OverlayFS存儲中，
或者OverlayFS存儲使用zfs/btrfs等支持快照的現代文件系統
（Docker對於zfs/btrfs等文件系統，會使用對應的专属存儲驅動，而非通用overlay驅動）。



# OpenWRT Clash
Clash是一款功能強大的代理工具，支持幾乎所有的主流代理協議（SS、SSR、VMESS、Trojan等）。

Clash內核需要與處理器架構匹配，常見CPU架構：

| CPU | 系列 | 架構 |
| :- | :- | :- |
| MediaTek MT7621A/N | mipsel_24kc | linux-mipsle-softfloat |
| SF19A28 | mips_siflower | linux-mipsle-hardfloat |
| Qualcomm IPQ6000 | ipq60xx | linux-armv7 (32bit OS) |

## luci-app-clash
[luci-app-clash](https://github.com/frainzy1477/luci-app-clash)是luci的Clash插件，
提供了Clash的管理面板，目前項目已停止維護，但核心功能依舊可以正常使用。

luci-app-clash未被官方庫包含，
需要從[luci-app-clash release](https://github.com/frainzy1477/luci-app-clash/releases)頁面中下載。
下載luci-app-clash的ipk文件後，執行安裝：

```
# opkg install ./luci-app-clash_版本號_all.ipk
```

luci-app-clash使用的Clash內核需要自行下載，普通內核應放置在`/etc/clash/clash`路徑下，
premium內核應放置在`/etc/clash/dtun/clash`路徑下。

## OpenClash
[`OpenClash`](https://github.com/vernesong/OpenClash)基於luci-app-clash開發，
提供了更多功能，目前項目依舊在活躍更新中。

OpenClash目前（OpenWRT 21.02.3）中並未被官方庫包含，
需要從[OpenWRT OpenClash Release](https://github.com/vernesong/OpenClash/releases)頁面中手動下載。
下載OpenClash的ipk文件後，執行安裝：

```
# opkg install ./luci-app-openclash_版本號_all.ipk
```

默認配置下安裝openclash會出現依賴文件衝突：

```
Collected errors:
 * check_data_file_clashes: Package dnsmasq-full wants to install file /etc/hotplug.d/ntp/25-dnsmasqsec
	But that file is already provided by package  * dnsmasq
 * check_data_file_clashes: Package dnsmasq-full wants to install file /etc/init.d/dnsmasq
	But that file is already provided by package  * dnsmasq
 * check_data_file_clashes: Package dnsmasq-full wants to install file /usr/lib/dnsmasq/dhcp-script.sh
	But that file is already provided by package  * dnsmasq
 * check_data_file_clashes: Package dnsmasq-full wants to install file /usr/sbin/dnsmasq
	But that file is already provided by package  * dnsmasq
 * check_data_file_clashes: Package dnsmasq-full wants to install file /usr/share/acl.d/dnsmasq_acl.json
	But that file is already provided by package  * dnsmasq
 * check_data_file_clashes: Package dnsmasq-full wants to install file /usr/share/dnsmasq/dhcpbogushostname.conf
	But that file is already provided by package  * dnsmasq
 * check_data_file_clashes: Package dnsmasq-full wants to install file /usr/share/dnsmasq/rfc6761.conf
	But that file is already provided by package  * dnsmasq
 * opkg_install_cmd: Cannot install package luci-app-openclash.
```

原因是OpenWRT默認安裝了`dnsmasq`，但openclash依賴`dnsmasq-full`，二者存在文件衝突。
解決方案是將預裝的dnsmasq卸載：

```
# opkg remove --autoremove dnsmasq
```

安裝openclash後打開luci頁面會出現錯誤：

```
/usr/lib/lua/luci/controller/openclash.lua:100: module 'luci.cbi.datatypes' not found:
	no field package.preload['luci.cbi.datatypes']
	no file './luci/cbi/datatypes.lua'
	no file '/usr/share/lua/luci/cbi/datatypes.lua'
	no file '/usr/share/lua/luci/cbi/datatypes/init.lua'
	no file '/usr/lib/lua/luci/cbi/datatypes.lua'
	no file '/usr/lib/lua/luci/cbi/datatypes/init.lua'
	no file './luci/cbi/datatypes.so'
	no file '/usr/lib/lua/luci/cbi/datatypes.so'
	no file '/usr/lib/lua/loadall.so'
	no file './luci.so'
	no file '/usr/lib/lua/luci.so'
	no file '/usr/lib/lua/loadall.so'
stack traceback:
	[C]: in function 'require'
	/usr/lib/lua/luci/controller/openclash.lua:100: in main chunk
	[C]: in function 'require'
	/usr/lib/lua/luci/dispatcher.lua:1131: in function 'createindex'
	/usr/lib/lua/luci/dispatcher.lua:1232: in function 'createtree'
	/usr/lib/lua/luci/dispatcher.lua:635: in function 'menu_json'
	/usr/lib/lua/luci/dispatcher.lua:884: in function 'dispatch'
	/usr/lib/lua/luci/dispatcher.lua:479: in function </usr/lib/lua/luci/dispatcher.lua:478>
```

安裝`luci-compat`包即可解決該問題：

```
# opkg install luci-compat
```

若已安裝`luci-app-aria2`或`luci-app-dockerman`則無需手動安裝該依賴
（OpenWRT 22.03開始luci-app-aria2已不再依賴luci-compat，需要手動安裝），
luci-compat會作為該插件的依賴安裝。



# OpenWRT衍生固件
OpenWRT擁有眾多第三方修改版本。

## ImmortalWrt
[`ImmortalWrt`](https://github.com/immortalwrt/immortalwrt)
是牆國特色的OpenWRT衍生版本，添加了部分新增功能，以及更多的設備支持；
ImmortalWrt倉庫中提供了更多硬件驅動和部分牆國常用但未被包含在官方倉庫中的包（OpenClash等）。

ImmortalWrt固件可從[官方下載頁面](https://downloads.immortalwrt.org)下載，
或者使用[ImmortalWrt Firmware Selector](https://firmware-selector.immortalwrt.org/)。

ImmortalWrt基於OpenWRT官方分支開發，但僅在大版本上保持一致，小版本號為自己定義，並使用獨立的軟件源。
ImmortalWrt版本通常會落後於官方版本一個大版本以上，僅在官方版本足夠穩定時才跟進。

## FriendlyWrt
`FriendlyWrt`是[`FRIENDLY ELEC`](https://friendlyelec.com/)公司為旗下設備提供的定製版OpenWRT，
通常預裝在其設備中。

FriendlyWrt繼承了大量插件，固件大小動輒數G, 相比原生OpenWRT要臃腫得多。
FriendlyWrt在UI與軟件倉庫上與官方版本類似，但提供了更新版本的內核、以及更多設備的驅動。

FriendlyWrt版本號直接對齊OpenWRT官方版本，除內核模塊外並直接使用官方源的軟件倉庫。
FriendlyWrt通常使用與官方版本不同的內核，因此獨立提供內核模塊倉庫，
內核模塊倉庫以本地源的形式提供，存放在`/opt/packages`路徑中，
對應倉庫配置如下(以NanoPi R4SE，FriendlyWrt 22.03.0版本為例)：

```
src/gz friendlywrt_packages file://opt/packages
```

`friendlywrt_packages`對應替換官方源的`openwrt_core`倉庫。

FriendlyWrt的overlay配置與官方OpenWRT存在一定差異，
FriendlyWrt默認不使用`/etc/config/fstab`來配置overlay，
而是直接將label為userdata的分區視為overlay，
同時overlay直接掛載到根節點，且不使用`/rom`和`/overlay`路徑
（官方OpenWRT常見的overlay方式是lowerdata掛載到`/rom`，upperdata掛載到`/overlay`下）。

### 修改FriendlyWrt的Overlay配置
默認FriendlyWrt的分區結構（以`NanoPi R4SE`為例）：

```
root@FriendlyWrt:~# lsblk
NAME         MAJ:MIN RM  SIZE RO TYPE MOUNTPOINTS
mmcblk2      179:0    0 29.1G  0 disk
├─mmcblk2p1  179:1    0    4M  0 part
├─mmcblk2p2  179:2    0    4M  0 part
├─mmcblk2p3  179:3    0    4M  0 part
├─mmcblk2p4  179:4    0    4M  0 part
├─mmcblk2p5  179:5    0   16M  0 part
├─mmcblk2p6  179:6    0   40M  0 part
├─mmcblk2p7  179:7    0   48M  0 part
├─mmcblk2p8  179:8    0  620M  0 part
└─mmcblk2p9  179:9    0 28.4G  0 part /opt/docker
                                      /
mmcblk2boot0 179:32   0    4M  1 disk
mmcblk2boot1 179:64   0    4M  1 disk
```

解決方案是刪除`userdata`分區（/dev/mmcblk2p9），
然後重新創建分區，並在`/etc/config/fstab`中按掛載方式進行配置。

```
root@FriendlyWrt:~# lsblk
NAME         MAJ:MIN RM  SIZE RO TYPE MOUNTPOINTS
mmcblk2      179:0    0 29.1G  0 disk
├─mmcblk2p1  179:1    0    4M  0 part
├─mmcblk2p2  179:2    0    4M  0 part
├─mmcblk2p3  179:3    0    4M  0 part
├─mmcblk2p4  179:4    0    4M  0 part
├─mmcblk2p5  179:5    0   16M  0 part
├─mmcblk2p6  179:6    0   40M  0 part
├─mmcblk2p7  179:7    0   48M  0 part
├─mmcblk2p8  179:8    0  620M  0 part /rom
├─mmcblk2p9  179:9    0    1G  0 part [SWAP]
└─mmcblk2p10 179:10   0 27.4G  0 part /overlay
mmcblk2boot0 179:32   0    4M  1 disk
mmcblk2boot1 179:64   0    4M  1 disk
```

默熱FriendlyWrt中未創建`/rom`目錄，需要手動創建，而`/srv`、`/lib64`等目錄不需要，可以移除。

### Docker服務未自啟動
FriendlyWrt自帶的Docker在更換文件系統做Overlay後可能會出現無法自啟動的問題，
解決方案是移除原先的`/opt/docker`路徑，之後重啟路由器即可。



# 構建OpenWRT官方固件
首先拉取OpenWRT源碼，設置需要構建的版本：

```html
<!-- 從官方倉庫拉取 OpenWRT 源碼 -->
$ git clone https://git.openwrt.org/openwrt/openwrt.git

<!-- 切換到倉庫目錄 -->
$ cd openwrt

<!-- 切換到需要構建的目標版本，以 21.02.3 版本為例 -->
$ git checkout v21.02.3
```

之後更新軟件包內容：

```html
$ ./scripts/feeds update -a <!-- 拉取軟件包 -->
$ ./scripts/feeds install -a <!-- 安裝軟件包 -->
```

之後即可使用`make`工具構建鏡像。
執行`make menuconfig`會進入編譯配置對話框，可選擇和更改構建配置，配置默認保存在`./.config`中。

通常配置構建選項應使用官方配置作為參考。
從[官方地址](https://downloads.openwrt.org/)下載設備的官方配置，
進行定製修改(設備信息可從OpenWRT的Wiki頁面中查到)：

```html
<!-- 以 Xiaomi Router 4C，21.02.3 版本為例 -->
$ curl https://downloads.openwrt.org/releases/21.02.3/targets/ramips/mt76x8/config.buildinfo -o .config
```

執行make後，會檢查系統工具鏈，根據提示安裝缺失的工具鏈/庫即可。
以`ubuntu-minimal`環境為例，需要安裝下列依賴：

```
# apt install curl g++ gawk libncurses-dev rsync unzip zlib1g-dev
```

若使用root用戶編譯，需要設置環境變量，否則編譯過程會因為安全警告中斷：

```
# export FORCE_UNSAFE_CONFIGURE=1
```

make構建OpenWRT的部分常用參數：

- `-j核心數` 多核CPU可指定數值與CPU線程數相符，以提升編譯速率
- `V=sc` 輸出編譯日誌內容，便於排查編譯錯誤

編譯完成後，生成的固件位於`./bin/targets`路徑下的相關目錄中（由設備型號決定），
以`Xiaomi Router 4C`為例：

```
$ cd ./bin/targets/ramips/mt76x8/
```

清理構建生成的內容（重複構建時遇到錯誤可嘗試使用該指令清理之前構建的緩存）：

```
$ make dirclean
```



# 構建GL.iNET廠家固件
[`GL.iNET`](https://www.gl-inet.com)是一家直接基於OpenWRT開發的路由器廠家，
該廠家的路由器直接提供OpenWRT源碼，可自行編譯固件。

不同型號編譯固件流程不盡相同，但基本流程類似：

```html
<!-- 拉取固件倉庫源碼 -->
$ git clone https://github.com/gl-inet/gl-infra-builder.git
$ cd gl-infra-builder

<!-- 生成固件構建配置，不同型號對應不同配置 -->
$ python3 setup.py -c configs/xxx

<!-- 執行 setup.py 後會生成設備相關路徑，切換到對應設備源碼路徑 -->
$ cd xxx

<!-- 在設備源碼路徑中通過 target 生成構建配置，支持的target可在profiles路徑中找到 -->
$ ./scripts/gen_config.py luci target_xxx

<!-- 執行構建操作 -->
$ make -j核心數
```

在執行`python3 setup.py -c xxx.yml`操作時，需要設置git的帳號和郵箱：

```
$ git config --global user.email "xxx"
$ git config --global user.name "xxx"
```

否則會導致git倉庫拉取不完全，進而後續的`./scripts/gen_config.py`腳本無法找到。

## 內核版本配置
使用開源代碼編譯出的固件內核VERMAGIC與官方kmod庫中的內核依賴版本不匹配，導致內核模塊無法正常安裝。
該問題可通過修改`include/kernel.mk`中的`LINUX_VERMAGIC`，顯式指定該值與kmod庫中版本相匹配即可。

```make
LINUX_VERMAGIC:=5c79df825364eed582b9e6554972c148 # 指定 LINUX_VERMAGIC 變量
ifneq (,$(findstring uml,$(BOARD)))
  LINUX_KARCH=um
else ifneq (,$(findstring $(ARCH) , aarch64 aarch64_be ))
```

相關內容可參考[GL.iNET官方論壇](https://forum.gl-inet.com/t/axt1800-which-distfeeds-conf-kmod-repo-should-i-use-for-self-compiled-firmware/23907)
中對應問題的相關討論。



# USB WIFI
對於當下主流的軟路由方案（RK3328-R2S/R2C、RK3399-R4S/R4SE、RK3568-R5S等），
通常並不提供WIFI功能，若需要在此類方案的設備中使用WIFI，則需要使用USB WIFI網卡。

常用固件對USB WIFI的支持如下：

| 網卡型號 | 設備ID | OpenWRT支持（22.03） | ImmortalWRT支持（21.02） | FriendlyWrt支持（22.03） | AP支持 | 驅動包名 | 速率 | 品牌產品 | 補充說明 |
| :- | :- | :- | :- | :- | :- | :- | :- | :- | :- |
| RTL8723BU | 0bda:b720 | Y | Y | Y | N | kmod-rtl8xxxu | bgn 150M | CF-723B | 價格20+RMB，帶藍牙，體積小，但驅動支持極差，所有固件中均不包含專屬驅動，無法開啟AP模式 |
| RTL8188CU | 0bda:8176 | Y | Y | Y | Y / N | kmod-rtl8192cu / kmod-rtl8xxxu | bgnn 150M | / | 價格10+RMB，各大版本支持較好，且體積小，與RTL8192CU共用驅動 |
| RTL8188EU | 0bda:8179 | Y | Y | Y | Y / N | kmod-rtl8188eu / kmod-rtl8xxxu | bgnn 150M | CF-WU810N | 價格10+RMB，EU系列當前驅動支持較差，僅在ImmortalWRT中存在專屬驅動，其它固件中驅動不支持AP；體積小，與RTL8188CU相同 |
| RTL8192CU | / | Y | Y | Y | Y / N | kmod-rtl8192cu / kmod-rtl8xxxu | bgn 300M | / | 價格10+RMB，各大版本支持較好，體積比RTL8188CU稍大 |
| RTL8192EU | 0bda:818b | Y | Y | Y | Y / N | kmod-rtl8192eu / kmod-rtl8xxxu | bgn 300M | / | 價格10+RMB，EU系列當前驅動支持較差，僅在ImmortalWRT中存在專屬驅動，其它固件中驅動不支持AP；體積與RTL8192CU相同 |
| RTL8811CU | 0bda:c811 | N | Y | Y | Y | kmod-rtl8821cu | bgnac 650M | CF-811AC | 價格30+RMB，體積小，性價比高，與RTL8821CU共用驅動 |
| RTL8821CU | / | N | Y | Y | Y | kmod-rtl8821cu | bgnac 650M | CF-813BC | 價格40+RMB，體積中，帶藍牙 |
| RTL8812BU | 0bda:b812 | N | ? | Y | Y | kmod-rtl88x2bu | bgnac 1200M | CF-812AC | 價格40+RMB，體積小，兼容性一般，使用ImmortalWRT驅動存在問題 |
| MT7601U | 148f:7601 | Y | Y | Y | N / Y | kmod-mt7601u / kmod-mt7601u-ap | bgn 150M | CF-W710N | 價格10+RMB，體積小，官方驅動不支持AP模式，僅在ImmortalWRT存在支持AP模式的專屬驅動 |
| AR9721 | 040d:3801 | Y | Y | Y | Y | kmod-ath9k-htc | bgn 150M | / | 價格10+RMB，驅動支持完善，體積稍大 |

官方OpenWRT對USB WIFI網卡的支持有限，若需要完善的USB WIFI支持，應使用ImmortalWRT。
`kmod-rtl8xxxu`驅動幾乎支持大多數RTL81xx系列網卡，但功能不夠完善，不支持AP模式，
若需要使用AP模式，應考慮存在專屬驅動的網卡。
