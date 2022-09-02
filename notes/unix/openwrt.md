<!-- TOC -->

- [mtd](#mtd)
- [Breed](#breed)
	- [Breed Web UI](#breed-web-ui)
- [OpenWrt基本配置](#openwrt基本配置)
	- [opkg包管理器](#opkg包管理器)
		- [軟件源配置](#軟件源配置)
		- [基本包管理操作](#基本包管理操作)
		- [檢查軟件包安裝狀態](#檢查軟件包安裝狀態)
		- [強制安裝軟件包](#強制安裝軟件包)
	- [關閉倉庫證書校驗](#關閉倉庫證書校驗)
	- [切換默認Shell](#切換默認shell)
	- [Dropbear SSH](#dropbear-ssh)
	- [服務管理](#服務管理)
	- [語言設置](#語言設置)
	- [存儲與文件系統](#存儲與文件系統)

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
```

opkg升級所有軟件包：

```
# opkg list-upgradable | cut -f 1 -d ' ' | xargs -r opkg upgrade
```

在OpenWRT中，升級所有軟件包的操作有一定危險性，
當當使用自編譯固件時，應儘量避免使用該功能，
自行編譯的固件可能與官方源的軟件包不兼容（例如部分軟件包的動態鏈接庫不匹配）。

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

Dropbear僅提供了SSH遠程服務，並未提供SFTP功能，相關功能依舊需要安裝`openssh-sftp-server`：

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
luci-i18n-base-ar - git-21.282.73955-9987b39 - Translation for luci-base - العربية (Arabic)
luci-i18n-base-bg - git-21.282.73955-9987b39 - Translation for luci-base - български (Bulgarian)
luci-i18n-base-bn - git-21.282.73955-9987b39 - Translation for luci-base - বাংলা (Bengali)
luci-i18n-base-ca - git-21.282.73955-9987b39 - Translation for luci-base - Català (Catalan)
luci-i18n-base-cs - git-21.282.73955-9987b39 - Translation for luci-base - Čeština (Czech)
luci-i18n-base-de - git-21.282.73955-9987b39 - Translation for luci-base - Deutsch (German)
luci-i18n-base-el - git-21.282.73955-9987b39 - Translation for luci-base - Ελληνικά (Greek)
luci-i18n-base-en - git-21.282.73955-9987b39 - Translation for luci-base - English
luci-i18n-base-es - git-21.282.73955-9987b39 - Translation for luci-base - Español (Spanish)
luci-i18n-base-fi - git-21.282.73955-9987b39 - Translation for luci-base - Suomi (Finnish)
luci-i18n-base-fr - git-21.282.73955-9987b39 - Translation for luci-base - Français (French)
luci-i18n-base-he - git-21.282.73955-9987b39 - Translation for luci-base - עִבְרִית (Hebrew)
luci-i18n-base-hi - git-21.282.73955-9987b39 - Translation for luci-base - हिंदी (Hindi)
luci-i18n-base-hu - git-21.282.73955-9987b39 - Translation for luci-base - Magyar (Hungarian)
luci-i18n-base-it - git-21.282.73955-9987b39 - Translation for luci-base - Italiano (Italian)
luci-i18n-base-ja - git-21.282.73955-9987b39 - Translation for luci-base - 日本語 (Japanese)
luci-i18n-base-ko - git-21.282.73955-9987b39 - Translation for luci-base - 한국어 (Korean)
luci-i18n-base-mr - git-21.282.73955-9987b39 - Translation for luci-base - Marāṭhī (Marathi)
luci-i18n-base-ms - git-21.282.73955-9987b39 - Translation for luci-base - Bahasa Melayu (Malay)
luci-i18n-base-nl - git-21.282.73955-9987b39 - Translation for luci-base - Nederlands (Dutch)
luci-i18n-base-no - git-21.282.73955-9987b39 - Translation for luci-base - Norsk (Norwegian)
luci-i18n-base-pl - git-21.282.73955-9987b39 - Translation for luci-base - Polski (Polish)
luci-i18n-base-pt - git-21.282.73955-9987b39 - Translation for luci-base - Português (Portuguese)
luci-i18n-base-pt-br - git-21.282.73955-9987b39 - Translation for luci-base - Português do Brasil (Brazilian Portuguese)
luci-i18n-base-ro - git-21.282.73955-9987b39 - Translation for luci-base - Română (Romanian)
luci-i18n-base-ru - git-21.282.73955-9987b39 - Translation for luci-base - Русский (Russian)
luci-i18n-base-sk - git-21.282.73955-9987b39 - Translation for luci-base - Slovenčina (Slovak)
luci-i18n-base-sv - git-21.282.73955-9987b39 - Translation for luci-base - Svenska (Swedish)
luci-i18n-base-tr - git-21.282.73955-9987b39 - Translation for luci-base - Türkçe (Turkish)
luci-i18n-base-uk - git-21.282.73955-9987b39 - Translation for luci-base - Українська (Ukrainian)
luci-i18n-base-vi - git-21.282.73955-9987b39 - Translation for luci-base - Tiếng Việt (Vietnamese)
luci-i18n-base-zh-cn - git-21.282.73955-9987b39 - Translation for luci-base - 简体中文 (Chinese Simplified)
luci-i18n-base-zh-tw - git-21.282.73955-9987b39 - Translation for luci-base - 繁體中文 (Chinese Traditional)
...
```

## 存儲與文件系統
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
