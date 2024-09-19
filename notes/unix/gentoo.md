<!-- TOC -->

- [基本安裝流程](#基本安裝流程)
    - [解壓並切換至Stage環境](#解壓並切換至stage環境)
    - [配置Portage](#配置portage)
    - [配置portage參數](#配置portage參數)
    - [配置内核](#配置内核)
        - [編譯内核](#編譯内核)
        - [安裝編譯內核](#安裝編譯內核)
    - [安裝引導器](#安裝引導器)
- [包管理](#包管理)
    - [emerge](#emerge)
    - [portage-utils](#portage-utils)
    - [gentoolkit](#gentoolkit)
    - [package.use](#packageuse)
    - [equery](#equery)
    - [包組列表](#包組列表)
    - [多版本包管理（slot機制）](#多版本包管理slot機制)
    - [overlay](#overlay)
- [OpenRC](#openrc)
- [其他配置](#其他配置)
    - [內核模塊](#內核模塊)
    - [軟件包Masked](#軟件包masked)
    - [軟件包配置衝突](#軟件包配置衝突)
    - [MySQL初始化](#mysql初始化)
    - [修改主機名](#修改主機名)
    - [安裝JDK](#安裝jdk)

<!-- /TOC -->



# 基本安裝流程
安裝Gentoo需要準備安裝介質，參考[Gentoo Wiki](https://wiki.gentoo.org/wiki/Handbook:AMD64/Installation/Media)，
可使用Gentoo Live CD或直接使用其它已經存在的Linux環境。

安裝流程參考[Gentoo Handbook](https://wiki.gentoo.org/wiki/Handbook:AMD64)。

Gentoo將系統環境的打包文件稱爲`Stage File`，跟据不同完善程度，從Stage 1至Stage 4，
從[Gentoo Downloads](https://www.gentoo.org/downloads/)頁面下載Stage Archives，
Genntoo默認提供的環境為Stage 3，包括OpenRC與systemd等版本。

## 解壓並切換至Stage環境
創建一個空的分區，挂載至`/mnt`路徑，解Stage Archives至此：

```html
# tar xvf Stage3歸檔文件 -C /mnt
```

之後複製當前系統的DNS配置至目標分區：

```html
<!-- 複製DNS配置保證後續chroot到新環境后域名解析正常 -->
# cp /etc/resolv.conf /mnt/etc
```

重綁定文件系統，之後chroot到Gentoo Stage環境：

```html
<!--
綁定必要文件系統

Genntoo并未提供類似arch-chroot的工具，需要手動逐一綁定必要文件系統
-->
# mount -t proc none /mnt/proc
# mount --rbind /sys /mnt/sys
# mount --rbind /dev /mnt/dev
# mount --bind /run /mnt/run
# mount --make-rslave /mnt/sys
# mount --make-rslave /mnt/dev
# mount --make-slave /mnt/run

<!--
chroot到Gentoo Stage環境。

若當前環境shell並非bash，
則需要顯式指定chroot shell爲bash，
否則會提示shell不存在(stage3中僅包含bash)
-->
# chroot /mnt /bin/bash
```

## 配置Portage
同步Portage倉庫：

```
# emerge-webrsync
```

更新軟件源：

```
# emerge --sync
```

查看與選擇合適的Profile：

```
# eselect profile list
# eselect profile set 配置編號
```

## 配置portage參數
編輯`/etc/portage/make.conf`文件，該文件用於配置系統構建（内核、軟件包編譯）的全局編譯參數，
通常使用默認配置即可。

常見配置項説明：

```sh
# 參數j(jobs)表示并行任務數目，l(load-average)表示系統負載
# 默認會通過nproc設置該參數，為充分利用資源，可略高於系統配置
MAKEOPTS="-j3 -l4"

# 配置USE標記，可控制軟件包開啓/關閉某些特性
# 例如，對於服務端，可關閉GUI相關標記
# USE="-X -alsa -gtk -gnome -qt -kde"
USE="xxx -xxx"
```

Gentoo在2023年底正式提供二進制源，參考
[Gentoo goes Binary!](https://www.gentoo.org/news/2023/12/29/Gentoo-binary.html)，
啓用二進制源在make.conf中添加：

```sh
# Appending getbinpkg to the list of values within the FEATURES variable
FEATURES="${FEATURES} getbinpkg"
# Require signatures
FEATURES="${FEATURES} binpkg-request-signature"
```

二進制源配置位於`/etc/portage/binrepos.conf/gentoobinhost.conf`。

啓用二進制源后，使用二進制源提供的預編譯包替換當前系統：

```html
<!--
-g/--getbinpkg 參數表示使用二進制包
-g參數實現了-k/--usepkg參數，會在可用時優先使用二進制包
-->
# emerge -auvgDN @world
```

## 配置内核
Gentoo提供了預編譯内核`sys-kernel/gentoo-kernel-bin`，
無特殊需求可直接使用該內核，節省大量編譯內核的時間。

```
# emerge -a sys-kernel/gentoo-kernel-bin
```

### 編譯内核
需要定制内核功能可源碼編譯内核，安裝內核源碼：

```
# emerge gentoo-sources
```

轉到內核源碼目錄`/usr/src/linux`，配置內核選項：

```
# make menuconfig
```

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

### 安裝編譯內核
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

## 安裝引導器
内核配置完成后，安裝GRUB引導器：

```
# emerge -a grub
```

Gentoo下GRUB默認使用`/boot/efi`路徑作爲ESP挂載點，
挂載ESP分區至該路徑下。生成GRUB配置，並安裝引導文件：

```html
<!-- 生成GRUB配置 -->
# grub-mkconfig -o /boot/grub/grub.cfg

<!-- 安裝Gentoo引導文件 -->
# grub-install
<!-- Gentoo生成引導文件時不會自動生成默認引導文件EFI/BOOT/BOOTAA64.EFI，需要手動生成 -->
# grub-install --removable
```


# 包管理
Gentoo使用`emerge`作爲包管理器，以及其它輔助工具如
`app-portage/portage-utils`、`app-portage/gentoolkit`、`app-portage/eix`等。

## emerge
`emerge`是Gentoo的默認包管理器，包含在默認環境中，常用參數説明：

```
-p pretend 預覽
-a ask 先予詢問
-c clean 清理系統
-C unmerge 卸載，與emerge相反
--deselect 將指定軟件包從world包組中除名（但不立即移除，執行--depclean時才移除）
--depclean 計算當前系統依賴，清理不被需要的軟件包
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

常用操作説明：

```html
# emerge --sync <!-- 同步portage樹 -->
# emerge -e world <!-- 更換全局USE之後重新編譯所有包 -->
# emerge -u system <!-- 更新系統軟件 -->
# emerge -u world <!-- 更新整個系統 -->
# emerge -auvDN system world <!-- 完整更新系統 -->

# emerge -pv 包名 <!-- 查看某個包的可用USE -->
# emerge --udpate --newuse 包名 <!-- 更新USE之後安裝包刷新依賴關係 -->
# emerge --depclean <!-- 清理無用依賴 -->
# emerge -a <!-- 執行操作前詢問 -->

<!-- 查看系統構建信息 -->
$ emerge --info
$ emerge --info 包名 <!-- 查看系統構建信息以及指定已安裝軟件包的構建標記 -->
```

## portage-utils
`app-portage/portage-utils`提供了emerge缺失的部分高級包管理功能，
包括qlist、qfile、qdepends、qkeyword等工具。

該套件由C語言實現，默認已安裝在系統中。

```html
$ qlist 包名 <!-- 查看包裏有哪些文件 -->
$ qfile 文件名/路徑名 <!-- 查看文件屬於哪個包 -->
```

## gentoolkit
`app-portage/gentoolkit`提供了emerge缺失的部分高級包管理功能，
包括equery、eclean、ekeyword等工具。

該套件由Python實現，默認不包含在系統中，需要自行安裝。

```html
$ equery list 包名 <!-- 列出對應包名的包安裝了哪些版本 -->
$ equery files 包名 <!-- 查看包裏有哪些文件 -->
$ equery belongs 文件路徑 <!-- 查看文件屬於哪個包 -->
$ equery depends 包名 <!-- 查看某個包的依賴 -->
$ equery uses 包名 <!-- 查看一個已經安裝的包使用了哪些USE -->

# eclean distfiles <!-- 清理包文件 -->
```

## package.use
[package.use](https://wiki.gentoo.org/wiki//etc/portage/package.use)
用於控制具體軟件包的標記，可以為目錄或單個文件。

全局USE標記在`/etc/portage/make.conf`中；
每個軟件單獨設定USE標記在`/etc/portage/package.use`中。

基本語法如下：

```sh
軟件包 啓用標簽 -禁用標簽
```

## equery
查詢系統內已安裝的包的信息需要安裝額外的工具`app-portage/gentoolkit`，
該包含有eclean、equery等工具。

```html
$ equery list 包名 <!-- 列出對應包名的包安裝了哪些版本 -->
$ equery files 包名 <!-- 查看包裏有哪些文件 -->
$ equery belongs 文件路徑 <!-- 查看文件屬於哪個包 -->
$ equery depends 包名 <!-- 查看某個包的依賴 -->
$ equery uses 包名 <!-- 查看一個已經安裝的包使用了哪些USE -->
```

## 包組列表
系統默認的包組有`system`和`world`，system列表爲系統成員組件，不可更改（由選擇的profile決定）；
world包組成員列表記錄在`/var/lib/portage/world`文件中，可自行更改。
相關包及其依賴包被保護，其餘包被視爲孤立包，執行清理依賴命令時孤立包會被移除。

一般手動執行安裝某個包時，該包的包名會被加入world文件（即主動安裝的包不會被清理，除非主動移除）。
使用`--oneshot`指令安裝的包不會被加入world列表中。

## 多版本包管理（slot機制）
對於Python，JDK等多版本共存軟件，使用select命令選取一個默認版本：

```
# eselect 軟件名 set 軟件版本
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



# OpenRC
[`OpenRC`](https://wiki.gentoo.org/wiki/OpenRC)是Gentoo默認的服務管理機制。

常用指令：

```html
# rc-update add 服務名稱 <!-- 添加一個服務 -->
# rc-update del 服務名稱 <!-- 移除一個服務 -->
# rc-update <!-- 列出服務樹(已設置自啓動的服務) -->
# rc-update -v <!-- 列出服務樹(包括未設置自啓動的服務) -->

# rc-service 服務名稱 start
# rc-service 服務名稱 restart
# rc-service 服務名稱 stop

# rc-status <!-- 查看用戶添加啓動的服務 -->
# rc-status 運行級別 <!-- 查看某個運行級別中的服務 -->
# rc-status -s <!-- 顯示所有服務的狀態 -->
```

openRC系統的服務模塊位於`/etc/conf.d`目錄下，可以根據需求自行添加。



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
