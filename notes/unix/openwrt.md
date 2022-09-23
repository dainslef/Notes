<!-- TOC -->

- [mtd](#mtd)
- [Breed](#breed)
	- [Breed Web UI](#breed-web-ui)
	- [Redmi Router AC2100](#redmi-router-ac2100)
- [OpenWrt基本配置](#openwrt基本配置)
	- [opkg包管理器](#opkg包管理器)
		- [軟件源配置](#軟件源配置)
		- [基本包管理操作](#基本包管理操作)
		- [升級系統軟件包](#升級系統軟件包)
		- [禁止/恢復軟件包升級](#禁止恢復軟件包升級)
		- [檢查軟件包安裝狀態](#檢查軟件包安裝狀態)
		- [強制安裝軟件包](#強制安裝軟件包)
	- [關閉倉庫證書校驗](#關閉倉庫證書校驗)
	- [切換默認Shell](#切換默認shell)
	- [Dropbear SSH](#dropbear-ssh)
	- [服務管理](#服務管理)
	- [語言設置](#語言設置)
	- [文件系統](#文件系統)
	- [存儲掛載](#存儲掛載)
		- [掛載USB存儲](#掛載usb存儲)
		- [掛載SD卡存儲](#掛載sd卡存儲)
		- [擴展根分區](#擴展根分區)
		- [使用文件作為SWAP](#使用文件作為swap)

<!-- /TOC -->



# mtd
`mtd`是路由器刷機使用的固件寫入工具。

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

使用mtd重置系統：

```
# mtd erase rootfs_data
```



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

### 軟件源配置
opkg包管理器的軟件源配置文件為`/etc/opkg/distfeeds.conf`，
替換軟件源為牆國USTC源：

```
# sed -i 's/downloads.openwrt.org/mirrors.ustc.edu.cn\/openwrt/g' /etc/opkg/distfeeds.conf
```

### 基本包管理操作
OpenWRT提供的opkg包管理器被設計運行在嵌入式環境中，
因此遠比傳統的包管理器更加輕量級，功能也更加簡陋。

基本操作：

```html
<!-- 查詢軟件包 -->
# opkg list '*軟件包名稱*'
<!-- 安裝軟件包 -->
# opkg install 軟件包名稱
<!-- 移除軟件包（同時移除軟件包的孤兒依賴） -->
# opkg remove --autoremove 軟件包名稱
<!-- 列出軟件包內容 -->
# opkg files 軟件包名稱
```

### 升級系統軟件包
opkg並未直接提供升級所有軟件包功能，可利用管道操作組合指令實現：

```
# opkg list-upgradable | cut -f 1 -d ' ' | xargs -r opkg upgrade
```

在OpenWRT中，升級所有軟件包的操作有一定危險性，
當當使用自編譯固件時，應儘量避免使用該功能，
自行編譯的固件可能與官方源的軟件包不兼容（例如部分軟件包的動態鏈接庫不匹配）。

### 禁止/恢復軟件包升級
可通過設置軟件包flag為`hold`禁止軟件包升級：

```
# opkg flag hold 軟件包名稱
```

設置flag為`user`可恢復軟件包升級：

```
# opkg flag user 軟件包名稱
```

### 檢查軟件包安裝狀態
系統中已安裝的軟件包信息存儲在`/rom/usr/lib/opkg/status`文件中，
軟件包信息示例：

```
# cat /rom/usr/lib/opkg/status
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
$ for i in `opkg list-installed |sed 's/ - .*//'`; do if !(cat /rom/usr/lib/opkg/status | grep -q "Package: $i") && !(opkg whatdepends $i | grep -q "depends on $i"); then echo $i; fi; done
```

查找所有手動安裝的軟件包（fish語法）：

```fish
#! /usr/bin/fish

set rom_packages (cat /rom/usr/lib/opkg/status)

for package_info in (cat /usr/lib/opkg/status | tr '\n' ';' | sed 's/;;/\n/g')
	if not [ (string match "*Auto-Installed: yes*" $package_info) ]
		# Find packages which are not auto installed.
		set package_name (string match -r "(?<=Package: )[\w-]+" $package_info)
		# Check if package not in rom (pre-installed).
		string match -q "*Package: "$package_name"*" $rom_packages
		if [ $status = 1 ]
			opkg whatdepends $package_name | grep -q "depends on $package_name"
			set not_used_by_others ([ $status = 1 ] && echo clean || echo used by others)
			echo $package_name"("$not_used_by_others")"
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

## 關閉倉庫證書校驗
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
相關功能依舊需要安裝`openssh-sftp-server`：

```
# opkg install openssh-sftp-server
```

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

## 文件系統
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
	option enabled '1' # 配置文件系統自動掛載（0：否，1：是，下同）
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

### 擴展根分區
對於支持SD卡/USB等外置存儲的設備，可將外置存儲作為設備的根分區，
參考[OpenWRT官方文檔](https://openwrt.org/docs/guide-user/additional-software/extroot_configuration)。

掛載外置存儲設備（以SD卡設備為例），拷貝現有overlay文件系統的內容到新分區：

```
# mount /dev/mmcblk0p1 /mnt
# cp -r /overlay/upper /mnt
```

使用`block info`查看用作overlay分區的UUID，
之後編輯`/etc/config/fstab`，添加新的overlay分區的掛載信息：

```
...
config 'mount'
	option uuid 'xxx_uuid...'
	option target '/overlay'
```

之後重啟路由器即可。

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
