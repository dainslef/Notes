<!-- TOC -->

- [基本安裝流程](#基本安裝流程)
	- [解壓鏡像](#解壓鏡像)
	- [修改全局編譯配置和USE標記](#修改全局編譯配置和use標記)
	- [修改portage源](#修改portage源)
	- [添加環境變量](#添加環境變量)
	- [配置DNS](#配置dns)
	- [進入gentoo環境](#進入gentoo環境)
	- [編譯內核](#編譯內核)
	- [調整內核配置](#調整內核配置)
	- [安裝內核](#安裝內核)
- [emerge 包管理器](#emerge-包管理器)
	- [equery](#equery)
	- [包組列表](#包組列表)
	- [多版本包管理（slot機制）](#多版本包管理slot機制)
	- [overlay](#overlay)
- [其他配置](#其他配置)
	- [內核模塊](#內核模塊)
	- [軟件包flags](#軟件包flags)
	- [軟件包Masked](#軟件包masked)
	- [軟件包配置衝突](#軟件包配置衝突)
	- [openRC](#openrc)
	- [MySQL初始化](#mysql初始化)
	- [修改主機名](#修改主機名)
	- [安裝JDK](#安裝jdk)

<!-- /TOC -->



# 基本安裝流程
首先，需要下載最近版本的鏡像和portage樹。

## 解壓鏡像
創建一個空的分區
掛到`/mnt`上，解壓鏡像到此：

```html
$ tar jvxf [鏡像路徑] -C /mnt <!-- j參數 -->
```

將portage樹鏡像解壓到`/mnt/usr`目錄：

```
$ tar jvxf [portage樹目錄] -C /mnt/usr
```

## 修改全局編譯配置和USE標記
修改`/mnt/etc/portage/make.conf`，修改部分參數：

```sh
USE="X dbus kde -gnome -systemd -gstreamer"	# 如果是gnome桌面就"-kde"
MAKEOPTS="-j5" # 編譯參數，爲cpu核數加1
INPUT_DEVICES="evdev synaptics"
VIDEO_CARDS="radeon intel"
CFLAGS="-O2 -pipe -march=native"
GENTOO_MIRRORS="http://mirrors.ustc.edu.cn/gentoo" # 鏡像目錄
LINGUAS="zh_CN"
PYTHON_TARGETS="python3_4 python2_7"
PYTHON_SINGLE_TARGET="python3_4" # 設置默認的python環境
```

## 修改portage源
創建`/mnt/etc/portage/repos.conf/gentoo.conf`文件，加入portage樹源：
(該文件的父目錄亦不存在，需要一同創建)

```ini
[gentoo]
location = /usr/portage
sync-type = rsync
sync-uri = rsync://mirrors.ustc.edu.cn/gentoo-portage
auto-sync = yes
```

## 添加環境變量
編輯`/mnt/etc/environment`，給新環境設置一些必要的環境變量(否則許多命令會提示找不到)：

```sh
LANG="en_US.utf8"
LC_ALL="en_US.UTF-8"
PATH=$PATH:/bin:/sbin:/usr/bin:/usr/sbin
```

## 配置DNS
複製當前機器的dns信息：

```
# cp /etc/resolv.conf /mnt/etc/resolv.conf
```

## 進入gentoo環境
Gentoo沒有提供類似`arch-chroot`之類的工具，因此在chroot之前需要手動綁定必要分區的位置：

```
# mount -t proc none /mnt/proc
# mount --rbind /sys /mnt/sys
# mount --rbind /dev /mnt/dev
```

之後才能正常進入chroot環境：

```html
<!--
若當前環境shell並非bash，
則需要顯式指定chroot shell爲bash，
否則會提示shell不存在(stage3中僅包含bash)
-->
# chroot /mnt /bin/bash

<!-- 重新加載環境變量 -->
# source /etc/environment
```

## 編譯內核
進入Gentoo的chroot環境後，安裝內核源碼：

```
# emerge gentoo-sources
```

轉到內核源碼目錄`/usr/src/linux`，配置內核選項：

```
# make menuconfig
```

## 調整內核配置
查看機器pci信息：

```
00:00.0 Host bridge: Intel Corporation Haswell-ULT DRAM Controller (rev 09)
00:02.0 VGA compatible controller: Intel Corporation Haswell-ULT Integrated Graphics Controller (rev 09)
00:03.0 Audio device: Intel Corporation Haswell-ULT HD Audio Controller (rev 09)
00:14.0 USB controller: Intel Corporation 8 Series USB xHCI HC (rev 04)
00:16.0 Communication controller: Intel Corporation 8 Series HECI #0 (rev 04)
00:1b.0 Audio device: Intel Corporation 8 Series HD Audio Controller (rev 04)
00:1c.0 PCI bridge: Intel Corporation 8 Series PCI Express Root Port 3 (rev e4)
00:1c.3 PCI bridge: Intel Corporation 8 Series PCI Express Root Port 4 (rev e4)
00:1c.4 PCI bridge: Intel Corporation 8 Series PCI Express Root Port 5 (rev e4)
00:1d.0 USB controller: Intel Corporation 8 Series USB EHCI #1 (rev 04)
00:1f.0 ISA bridge: Intel Corporation 8 Series LPC Controller (rev 04)
00:1f.2 SATA controller: Intel Corporation 8 Series SATA Controller 1 [AHCI mode] (rev 04)
00:1f.3 SMBus: Intel Corporation 8 Series SMBus Controller (rev 04)
01:00.0 Ethernet controller: Broadcom Corporation NetXtreme BCM57786 Gigabit Ethernet PCIe (rev 01)
01:00.1 SD Host controller: Broadcom Corporation BCM57765/57785 SDXC/MMC Card Reader (rev 01)
02:00.0 Network controller: Qualcomm Atheros QCA9565 / AR9565 Wireless Network Adapter (rev 01)
03:00.0 Display controller: Advanced Micro Devices, Inc. [AMD/ATI] Opal XT [Radeon R7 M265] (rev ff)
```

部分重要的內核選項：


- 處理器：(Intel CPU可關閉AMD CPU特性)

	```html
	Processor type and features  ——>
		[ ] Enable MPS table <!-- 支持ACPI的電腦都不選 -->
		[ ] Support for extended (non-PC) x86 platforms <!-- 關閉PC平臺以外的支持 -->
		Processor family (Core 2/newer Xeon)
		[ ] Linux guest support  ---- <!-- 安裝在虛擬機裏才需要 -->
		[*] Multi-core scheduler support <!-- 開啓多核心支持 -->
		[*] SMT (Hyperthreading) scheduler support <!-- SMT超線程開啓 -->
		[*] Intel Low Power Subsystem Support <!-- haswell以上可選 -->
		[ ] kexec system call
		[ ] Build a relocatable kernel
		[*] EFI runtime service support <!-- EFI主板開啓 -->
		[ ] EFI stub support <!-- 用不到 -->
		Preemption Model --->
			(X) Preemptible Kernel (Low-Latency Desktop) <!-- 低延時模式 -->
	```

- 設備驅動相關：

	```html
	Device Drivers  --->
		[ ] Multiple devices driver support (RAID and LVM)  ---- <!-- 關閉磁盤陣列 -->
		Graphics support  --->
			[ ] Bootup logo		//關了，啓動動畫沒用
			[*] Laptop Hybrid Graphics - GPU switching support <!-- 雙顯卡切換支持 -->
			Direct Rendering Manager  --->
				<*> Direct Rendering Manager
				<*> Intel 8xx/9xx/G3x/G4x/HD Graphics
			Frame buffer Devices  --->
				[*] Simple framebuffer support
		<*> Serial ATA and Parallel ATA drivers (libata)  --->
			[ ] ATA SFF support (for legacy IDE and PATA) <!-- 關了，老式硬盤才需要 -->
		[*] Network device support  ---> <!-- 取消除了自身硬件之外的全部選項 -->
			[*] Ethernet driver support  ---> <!-- 選擇有線驅動 -->
				[*] Broadcom devices (NEW)
				<*> Broadcom Tigon3 support <!-- BCM57786的驅動是這個 -->
			[*] Wireless LAN  ---> <!-- 選擇無線驅動 -->
				Atheros Wireless Cards  --->
					 [*] Atheros bluetooth coexistence support
					 <*> Atheros 802.11n wireless cards support
					 [*] Atheros ath9k PCI/PCIe bus support (NEW)
		Input device support  --->
			[ ] Touchscreens  ---- <!-- 非觸摸屏電腦關閉觸屏支持 -->
			[ ] Miscellaneous devices  ----
			[ ] Joysticks/Gamepads  ----
			(1366)  Horizontal screen resolution
			(768)   Vertical screen resolution <!-- 設置分辨率 -->
		[*] USB support  --->
			<*> xHCI HCD (USB 3.0) support <!-- 打開USB3.0支持 -->
		<*> MMC/SD/SDIO card support  --->
			<*> USB SD Host Controller (USHC) support
		[ ] LED Support  ---- <!-- 關閉LED驅動 -->
	```

- 電源管理和ACPI：

	```html
	Power management and ACPI options  --->
		[*] Suspend to RAM and standby <!-- 睡眠功能 -->
		[*] Hibernation (aka 'suspend to disk') <!-- 休眠功能 -->
		[ ] Power Management Debug Support <!-- 不需要調試電源 -->
		[*] ACPI (Advanced Configuration and Power Interface) Support  --->
			<*> Battery <!-- 筆記本開啓電池相關支持 -->
			<*> Smart Battery System
		CPU Frequency scaling  --->
			Default CPUFreq governor (ondemand)  --->
				(X) ondemand
			< > 'userspace' governor for userspace frequency scaling <!-- 關閉userspace調度器 -->
			x86 CPU frequency scaling drivers  --->
				[*] Intel P state control
	```

- 文件系統(記得開啓vfat、NTFS支持，另文件系統不建議編譯成模塊)：

	```html
	File systems --->
		<*> FUSE (Filesystem in Userspace) support <!-- 無此選項掛載Win分區會失敗 -->
		CD-ROM/DVD Filesystems  --->
			<*> ISO 9660 CDROM file system support
			<*> UDF file system support <!-- 刻盤可能會用到 -->
		DOS/FAT/NT Filesystems  --->
			<*> MSDOS fs support
			<*> VFAT (Windows-95) fs support
			<*> NTFS file system support <!-- NTFS文件系統支持不打開無法掛載win分區 -->
		-*- Native language support  --->
			<*> Simplified Chinese charset (CP936, GB2312) <!-- fat32的原生中文支持 -->
	```

- 可執行文件：

	```html
	Executable file formats / Emulations  --->
		[ ] IA32 Emulation <!-- 不需要32位模擬 -->
	```

- 虛擬化：

	```html
	[*] Virtualization  --->
		<*> Kernel-based Virtual Machine (KVM) support
			<*> KVM for Intel processors support <!-- VirtualBox使用該特性 -->
	```

- 內核安全與內核調試：

	```html
	Kernel hacking  --->
	Security options  ---> <!-- 關閉非必選項-->
	```

## 安裝內核
確認配置無誤之後，執行make指令開始根據makefile進行編譯。

編譯內核之後複製鏡像：

```
# cp arch/x86/boot/bzImage /boot/kernel-[版本號]-gentoo
```

之後安裝內核模塊：

```
# make modules_install
```

根據桌面環境選擇默認的配置文件集：

```
# eselect profile list
[1]   default/linux/amd64/13.0
[2]   default/linux/amd64/13.0/selinux
[3]   default/linux/amd64/13.0/desktop
[4]   default/linux/amd64/13.0/desktop/gnome
[5]   default/linux/amd64/13.0/desktop/gnome/systemd
[6]   default/linux/amd64/13.0/desktop/kde
[7]   default/linux/amd64/13.0/desktop/kde/systemd
```

openRC服務下更換顯示管理器，編輯`/etc/conf.d/xdm`文件，
將`DISPLAYMANAGER="xdm"`改爲安裝的顯示管理器：

```html
# rc-update add xdm default <!-- 默認登錄到顯示管理器 -->
```

加入藍牙模塊自啓動：

```html
# rc-update add bluetooth <!-- 沒寫運行級別會默認加入default運行級別 -->
```



# emerge 包管理器
Gentoo使用`emerge`作爲包管理器，常用指令：

```html
# emerge --sync <!-- 同步portage樹 -->
# emerge -e world <!-- 更換全局USE之後重新編譯所有包 -->
# emerge -u system <!-- 升級系統軟件 -->
# emerge -u world <!-- 升級整個系統 -->
# emerge -auvDN world <!-- 完整升級系統 -->
# emerge -pv [包名] <!-- 查看某個包的可用USE -->
# emerge --udpate --newuse [包名] <!-- 更新USE之後安裝包刷新依賴關係 -->
# emerge --depclean <!-- 清理無用依賴 -->
# emerge -a <!-- 執行操作前詢問 -->
# eclean distfiles <!-- 清理包文件(請先 emerge gentoolkit) -->
$ qfile [文件名/路徑名] <!-- 查看文件屬於哪個包 -->
```

emerge常用參數：

```
-p pretend 預覽
-a ask 先予詢問
-c clean 清理系統
-C unmerge 卸載，與emerge相反
--depclean 深度清理，移除與系統無關的包
-h help 幫助文件
-v verbose 詳細內容
-s search 查找
-S searchdesc 從文件名和描述中查找，效率低
-u update 升級軟件包
-U upgradeonly 僅僅升級，不降級軟件包
-D deep 計算整個系統的依賴關係
-e emptytree 清空依賴樹，重新構建某個包/系統整個依賴樹
-1 oneshot 一次性安裝，不將其信息加入系統目錄樹
-o onlydeps 只安裝其依賴關係，而不安裝軟件本身
-t tree 顯示其目錄樹信息
-k usepkg 使用二進制包
-K usepkgonly 只使用二進制包
-f fetchonly 僅下載安裝包
--sync 從指定的rsync站點更新portage樹，先前所作所有portage樹更改均失效
-N newuse 使用新的USE FLAG，如有必要，需重新編譯
-n noreplace 更新system，但先前安裝的軟件不予覆蓋
```

## equery
查詢系統內已安裝的包的信息需要安裝額外的工具`app-portage/gentoolkit`，
該包含有eclean、equery等工具。

```html
$ equery list [包名] <!-- 列出對應包名的包安裝了哪些版本 -->
$ equery files [包名] <!-- 查看包裏有哪些文件 -->
$ equery belongs [文件路徑] <!-- 查看文件屬於哪個包 -->
$ equery depends [包名] <!-- 查看某個包的依賴 -->
$ equery uses [包名] <!-- 查看一個已經安裝的包使用了哪些USE -->
```

## 包組列表
系統默認的包組有`system`和`world`，system列表爲系統成員組件，不可更改(由選擇的profile決定)；
world包組成員列表記錄在`/var/lib/portage/world`文件中，可自行更改。
相關包及其依賴包被保護，其餘包被視爲孤立包，執行清理依賴命令時孤立包會被移除。

一般手動執行安裝某個包時，該包的包名會被加入`/var/lib/portage/world`文件
(即主動安裝的包不會被清理，除非主動移除)。
使用`--oneshot`指令安裝的包不會被加入world列表中。

## 多版本包管理（slot機制）
對於Python，JDK等多版本共存軟件，使用select命令選取一個默認版本：

```
# eselect [軟件名] set [軟件版本]
```

例如使用Python2.7爲默認版本：

```html
# eselect python set python2.7 <!-- 版本必須是在環境變量定義下可尋的二進制文件名 -->
```

使用help參數可以查看詳情：

```
$ eselect help
```

## overlay
overlay倉庫類似於`Arch Linux`中的`AUR`倉庫，用來提供一些官方源中未包含的軟件包。

安裝overlay：

```html
# emerge -av layman
# cat /var/lib/layman/make.conf >> /etc/portage/make.conf <!-- 將第三方portage添加到庫中 -->
# layman -a gentoo-zh <!-- 加入國人倉庫 -->
```

常用命令：

```html
# layman -L <!-- 獲取overlay列表，並列出 -->
# layman -a XXX <!-- 添加XXX overlay -->
# layman -d XXX <!-- 刪除XXX overlay -->
# layman -s XXX <!-- 更新XXX overlay -->
# layman -S <!-- 更新所有 overlay -->
```



# 其他配置
不同於一般發行版，Gentoo有需要需要注意的特殊知識。

## 內核模塊
內核模塊被安裝在`/lib/modules/$(uname -r)`目錄中。
使用如下命令查看可用的內核模塊：

```
# find /lib/modules/`uname -r` -type f -iname '*.o' -or -iname '*.ko'
```

使用默認的openRC服務管理，將查詢到的內核模塊名按需加入`/etc/conf.d/modules`中，
可以使模塊開機自啓動(後綴名`*.ko`可省略)。
配置文件中的內核模塊不能寫alisa名稱，而是要寫清模塊文件的名字。
如果使用systemd作爲服務管理，則將需要開機啓動的模塊寫入`/etc/modprobe.d/`中的任意文件。

## 軟件包flags
全局USE標記在`/etc/portage/make.conf`中。
每個軟件單獨設定USE標記在`/etc/portage/package.use`裏。
其他標記如`PYTHON_TARGETS`，`PYTHON_SINGLE_TARGET`等也可以加入`make.conf`(全局)，
頁可寫入`package.use`(單個包有效)。

## 軟件包Masked
包被Masked的原因很多，因爲許可證被Masked，
需要將接受的許可證級別的寫在`/etc/portage/package.license`中，
部分軟件穩定性不達標會被Masked，若需要安裝，
則將對應的包名和穩定性級別加入`/etc/portage/package.accept_keywords`中。
若安裝很多穩定性級別不夠的包，一一加入較為不便，
可在`/etc/portage/make.conf`中使用全局關鍵字`ACCEPT_KEYWORDS="~amd64"`，
通常不推薦此選項，這會降低系統穩定性。

## 軟件包配置衝突
有時包更新帶來新的配置文件便會產生文件衝突，
新加入的配置文件會以`.cfg00xx_[原配置文件名]`命名，
查找此類衝突配置文件可使用指令：

```
# find /etc -name '*._cfg*'
```

比較文件內容後，自行決定取捨。

## openRC
Gentoo默認使用`openRC`管理服務，常用指令：

```html
# rc-update -a 服務名稱 default <!-- 添加一個服務(add) -->
# rc-update -d 服務名稱 default <!-- 移除一個服務(delete) -->
# rc-update <!-- 列出服務樹(已設置自啓動的服務) -->
# rc-update -v <!-- 列出服務樹(包括未設置自啓動的服務) -->
# rc-status <!-- 查看用戶添加啓動的服務 -->
# rc-status 運行級別 <!-- 查看某個運行級別中的服務 -->
# rc-status -s <!-- 顯示所有服務的狀態 -->
```

openRC系統的服務模塊位於`/etc/conf.d`目錄下，可以根據需求自行添加。

## MySQL初始化
默認情況下，安裝完MySQL/MariaDB數據庫並未進行初始化配置，
此時服務無法啓動，需要手動進行初始化：

```html
# emerge --config dev-db/mariadb <!-- 初始化mysql配置 -->
```

之後就可以啓動msyql服務：

```
# /etc/init.d/mysql start
```

## 修改主機名
與其它systemd發行版不同，主機名配置位於`/etc/conf.d/hostname`。

## 安裝JDK
默認源中似乎沒有OpenJDK，但是可以安裝OracleJDK，安裝包需要自己從Oracle官網下載。
下載完成後，移動到`/usr/portage/distfiles`文件夾中，
注意修改文件權限爲`664`，文件屬主和用戶組都改爲`portage`。
然後在安裝源裏的OracleJDK包。
