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
