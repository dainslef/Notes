<!-- TOC -->

- [MSYS2](#msys2)
	- [下載與安裝](#下載與安裝)
	- [配置倉庫與源](#配置倉庫與源)
	- [包管理](#包管理)
	- [設置中文LC](#設置中文lc)
	- [pacman-key/msys2-keyring更新錯誤](#pacman-keymsys2-keyring更新錯誤)
- [POSIX](#posix)
	- [Microsoft POSIX subsystem](#microsoft-posix-subsystem)
	- [Windows Services for UNIX](#windows-services-for-unix)
	- [Windows Linux Subsystem](#windows-linux-subsystem)
		- [LXSS](#lxss)
		- [WSL](#wsl)
		- [WSL2](#wsl2)
- [Linux Subsystem 與 MSYS2 比較](#linux-subsystem-與-msys2-比較)
- [Wine](#wine)
	- [安裝和配置Wine](#安裝和配置wine)
	- [中文字體問題](#中文字體問題)
	- [Wine64](#wine64)
	- [Bottles](#bottles)

<!-- /TOC -->



# MSYS2
`MSYS2`基於`Cygwin`，解決了Cygwin包升級、管理不便的問題。
MSYS2採用`ArchLinux`的`pacman`作爲包管理器，能夠方便、簡單地升級、管理已安裝的軟件包。

## 下載與安裝
從`http://www.msys2.org/`頁面下載安裝包。
官方頁面提供了包含安裝器的版本，安裝完成後即可使用。

MSYS2亦提供了免安裝版本，從以下地址下載：

```
https://mirrors.ustc.edu.cn/msys2/distrib/msys2-x86_64-latest.tar.xz
```

下載完成後解壓文件，將`[解壓路徑]/bin`目錄加入`PATH`即可。

## 配置倉庫與源
倉庫與源的配置與`ArchLinux`類似。

倉庫配置文件爲`/etc/pacman.conf`。
MSYS2共提供了三個倉庫：

- 基於`Cygwin`的`msys`倉庫
- 基於`Mingw`的`mingw32`、`mingw64`倉庫

軟件源配置文件爲`/etc/pacman.d/mirrorlist.*`，`*`對應倉庫的名稱，每個倉庫擁有一個源配置。
由於GFW，官方源不穩定，推薦使用中科大的源，在源配置中添加：

```sh
Server = https://mirrors.ustc.edu.cn/msys2/msys/$arch # mirrorlist.msys
Server = http://mirrors.ustc.edu.cn/msys2/mingw/i686 # mirrorlist.mingw32
Server = http://mirrors.ustc.edu.cn/msys2/mingw/x86_64 # mirrorlist.mingw64
```

## 包管理
`pacman`移植自ArchLinux，操作指令與ArchLinux完全相同。

安裝一些常用的包：

```
> pacman -S nano gcc gdb grep gawk make python ruby git diffutils ctags wget whois nasm sqlite tree
//vim、tar、python2、binutils、openssh 會作爲依賴自動安裝
```

安裝`man`手冊：

```
> pacman -S man-pages-posix //安裝Unix API的文檔man手冊
```

刪除一些用不到的默認包：

```
> pacman -Rsnc flex gawk bash-completion catgets bsdtar rebase pkgfile pax-git repman-git pcre tzcode lndir crypt bsdcpio filesystem util-linux mintty
```

`msys`倉庫中的包會被安裝在`/usr`目錄下。
`mingw*`倉庫中的包會被安裝在`/mingw*`目錄下。

## 設置中文LC
MSYS2中默認的語言環境是`C`，需要自行設置正確的`locale`，設置方式類似於Linux。
在Windows的環境變量設置里加入個人環境變量，對應MSYS2工具會從Windows系統的環境變量中讀取信息。

添加如下環境變量：

- 環境變量名稱： `LC_ALL`
- 環境變量值： `zh_CN.UTF-8`

## pacman-key/msys2-keyring更新錯誤
在啓用了Linux Subsystem的系統中，Linux Subsystem提供的bash優先級高於MSYS2提供的bash。
在更新`msys2-keyring`時，會調用更新腳本`pacman-key`，該腳本默認使用bash執行，
若等使用Linux Subsystem提供的bash會因環境不匹配而導致執行失敗。

`pacman`指令會因爲密鑰庫更新失敗不能正常地更新倉庫信息。
解決方案是安裝`zsh`，將pacman-key腳本的執行Shell切換到`zsh`。
編輯`[MSYS根路徑]/usr/bin/pacman-key`文件，原內容：

```bash
#!/usr/bin/env bash
...
```

修改爲：

```bash
#!/usr/bin/env zsh
...
```

之後重新執行pacman-key再次初始化密鑰庫即可正常更新pacman倉庫數據：

```
$ pacman-key --init
$ pacman-key --populate
```



# POSIX
Windows在不同時期曾以不同形式支持了部分POSIX特性。

## Microsoft POSIX subsystem
Windows NT初版開始提供了[`Microsoft POSIX subsystem`](https://en.wikipedia.org/wiki/Microsoft_POSIX_subsystem)，
該POSIX子系統實現了`POSIX 1`標準（IEEE Std 1003.1-1990）。
因爲POSIX交互環境相關内容在`POSIX 2`中才標準化，
故Windows的POSIX子系統并未提供任何POSIX Shell以及Unix命令行工具。

## Windows Services for UNIX
自`Windows XP`/`Windows Server 2003`開始，POSIX子系統被
[`Windows Services for UNIX (SFU)`](https://en.wikipedia.org/wiki/Windows_Services_for_UNIX)替代。
SFU後續亦停止更新，Windows 10之後開始引入WSL，作爲新的Windows POSIX子系統。

## Windows Linux Subsystem
在`Windows 10`週年更新`Version 1607`中引入了`Linux Subsystem`(簡稱`LXSS`)，
之後`Version 1709`中正式發布定名`Windows Subsystem for Linux`(簡稱`WSL`)。

### LXSS
啓用LXSS需要執行以下步驟：

1. `設置`中啓用`開發人員模式`。
1. `啓用或關閉Windows功能`中勾選`適用於Linux的Windows子系統`。
1. 在CMD中輸入bash指令，按照提示即可進入子系統安裝步驟。

LXSS的安裝路徑爲`[用戶目錄]/AppData/Local/Lxss`。
默認資源管理器配置下，該目錄不可見，需取消勾選`隱藏受保護的操作系統文件(推薦)`選項方可顯示此目錄。

在LXSS中，Windows分區會被掛載到`/mnt`路徑下。

LXSS使用`lxrun`工具管理環境：

```html
> lxrun /install <!-- 安裝子系統 -->
> lxrun /uninstall <!-- 移除子系統，默認情況下保留`/home`和`/root`目錄，指令搭配`/full`參數則執行完全卸載 -->
> lxrun /update <!-- 更新子系統的包索引 -->
> lxrun /setdefaultuser <!-- 配置子系統用戶 -->
```

### WSL
從`Windows Version 1709`(2017秋季創意者更新)開始，LXSS正式脫離Beta版本，正式名稱為WSL。
從1709版本開始，應用商店中直接提供WSL發行版應用下載。
同時，WSL也不僅限於`Ubuntu`發行版，還提供了`openSUSE`和`SUSE Linux Enterprise Server`。

在1709中lxrun工具依然保留，但已不推薦使用，提示該工具已被廢棄。
應用商店中提供的WSL不在`[用戶目錄]/AppData/Local/Lxss`路徑下。

1709中的WSL新特性：

- WSL系統發行版部分直接以應用商店APP的形式存在，安裝卸載更加方便。
- 支持在bash中直接執行`*.exe`可執行文件。
- 環境變量中添加Windows的PATH，位於PATH中的Windows工具亦可直接調用。

WSL基於API轉發，詳細實現機制參考博客[Windows for Linux Nerds](https://blog.jessfraz.com/post/windows-for-linux-nerds/)，
以及[微軟官方文檔](https://docs.microsoft.com/en-us/archive/blogs/wsl/windows-subsystem-for-linux-overview)。

### WSL2
WSL基於API轉發的實現存在一系列問題：

- 文件系統性能(file system performance)
- 完整的系統調用兼容性(full system call compatibility)

為了改善這些問題，微軟提出了基於虛擬化技術的WSL2。
WSL2需要`Windows Version 1903`或更高的版本。

關於WSL/WSL2的對比，參見[微軟官方文檔](https://docs.microsoft.com/en-us/windows/wsl/compare-versions)。

WSL2不在作爲Windows Features提供（Windows Features中的WSL依舊存在，但不必開啓），
而是直接以應用形式提供（不在綁定系統，便於快速更新）；
lxrun工具現在亦已被移除，現在使用`wsl`指令進行管理WSL環境：

```html
> wsl --help
> wsl --status <!-- 查看當前WSL狀態 -->
> wsl --update <!-- 更新WSL -->
> wsl --shutdown <!-- 關閉WSL虛擬機 -->

> wsl -l/--list
> wsl -d/--distribution <!-- 進入指定發行版 -->
```

WSL2的各類發行版均運行在微軟的`Common Base Linux Mariner`上，
進入該環境，執行：

```
> wsl --system
```

通過應用商店安裝的WSL環境，在刪除WSL APP后，對應發行版的文件系統存儲依舊會保留，
完全移除指定發行版的文件系統存儲，執行：

```
> wsl --unregister 發行版名稱
```

[WSL version 0.67.6](https://devblogs.microsoft.com/commandline/systemd-support-is-now-available-in-wsl/)
開始支持systemd，應用商店中的Ubuntu發行版已直接開啓了systemd支持，
其它發行版可手動創建`/etc/wsl.conf`配置文件，添加下列内容：

```ini
[boot]
systemd=true
```

之後重啓WSL虛擬機，重新進入WSL環境即可。



# Linux Subsystem 與 MSYS2 比較
`Linux Subsystem`與`Msys`等有着本質區別：

- `MSYS2`是傳統的Unix工具鏈的Windows版本移植，工具均爲Windows二進制格式(`PE32/PE32+`)的程序。
- `Linux Subsystem`是運行在Windows內核上的完整Linux子系統，軟件包均爲原生Linux二進制格式(`ELF`)程序。

`Linux Subsystem`優劣

- 優勢：

	`Linux Subsystem`是**完整的**`Linux`發行版(`Bulid 14393.10`內置的子系統基於`Ubuntu 14.04`)。
	`Linux Subsystem`直接使用Ubuntu官方源，能夠使用幾乎所有Ubuntu軟件包。

- 劣勢：

	`Linux Subsystem`需要使用`Bash Launcher`進入獨立的Linux環境。
	`Linux Subsystem`環境與Windows環境相互獨立存在，
	早期的LXSS幾乎與宿主的Windows系統幾乎不存在任何交互；
	1709版本之後有部分改進，WSL的Linux Shell可訪問Windows程序，但依舊存在較多限制。
	`Linux Subsystem`下的Unix工具如同Linux原生程序一樣區分大小寫、不支持Windows格式的路徑。

`Msys2`優劣

- 優勢：

	`MSYS2`將傳統Unix工具直接編譯爲`Windows PE32/PE32+`可執行格式，可直接在`CMD`中調用。
	`MSYS2`移植的Unix工具能夠直接支持Windows格式的路徑，與現有的Windows環境無縫交互。
	`MSYS2`環境全在一個目錄中，可直接拷貝到其它機器中使用，無需重複配置，開箱即用。

- 劣勢：

	`MSYS2`源中移植到Windows平臺的Unix工具數目有限。



# Wine
[Wine](https://www.winehq.org/)是POSIX兼容系統（Linux、macOS、*BSD等）下的一套Windows應用兼容層。
Wine的實現類似於反向的WSL1，將Windows API調用轉換爲POSIX調用，相比傳統的虛擬機方式，
API轉換的實現通常具備更好的性能和更低的內存佔用。

## 安裝和配置Wine
Wine在多數主流發行版中可直接安裝：

```html
# pacman -S wine <!-- Arch系-->
# brew install wine-stable <!-- macOS -->
```

Wine會在`~/.wine`路徑下創建Windows環境需要的文件和配置，
`~/.wine/drive_c`子路徑對應Windows系統下的C盤，目錄結構相同。

Wine常用指令：

```html
<!--
Wine同時支持使用Windows風格或Unix風格的路徑啓動程序
wine "C:\Program Files\Tencent\WeChat\WeChat.exe"
wine ~/.wine/drive_c/Program\ Files/Tencent/WeChat/WeChat.exe
-->
$ wine windows可執行程序

<!-- 常用內置程序 -->
$ wine regedit <!-- 註冊表 -->
$ wine uninstaller <!-- 程序卸載面板 -->

$ winecfg <!-- 調整環境配置、主題風格等 -->
```

## 中文字體問題
默認配置下，Wine未集成中文字體，執行需要顯示中文字體的軟件時，中文字體會變成口口。
該問題有以下解決方案：

- 複製原版字體

	從原版Windows系統中複製`ms*`以及`sim*`系列字體到`~/.wine/drive_c/windows/Fonts`路徑下即可。
	字體示例：

	```
	$ ls
	msgothic.ttc  msjhl.ttc  msmincho.ttc  msyhl.ttc  msyi.ttf     simhei.ttf  simsunb.ttf
	msjhbd.ttc    msjh.ttc   msyhbd.ttc    msyh.ttc   simfang.ttf  simkai.ttf  simsun.ttc
	```

- 修改註冊表指定自定義字體

	需要將自定義的中文字體存放在`~/.wine/drive_c/windows/Fonts`路徑下；
	之後編寫如下所示的註冊表(`*.reg`)文件，指定字體名稱（字體文件名稱，以文泉驛微米黑字體爲例）：

	```
	REGEDIT4

	[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\FontLink\SystemLink]
	"Lucida Sans Unicode"="wqy-microhei.ttc"
	"Microsoft Sans Serif"="wqy-microhei.ttc"
	"MS Sans Serif"="wqy-microhei.ttc"
	"Tahoma"="wqy-microhei.ttc"
	"Tahoma Bold"="wqy-microhei.ttc"
	"SimSun"="wqy-microhei.ttc"
	"Arial"="wqy-microhei.ttc"
	"Arial Black"="wqy-microhei.ttc"
	```

	其中`wqy-microhei.ttc`可替換爲其它合適的中文字體。

## Wine64
多數發行版默認提供的Wine版本爲32位，32位的Wine可執行16/32位的Windows程序；
運行64位Windows程序需要wine64，wine64亦可執行32位Windows程序，但需要配置額外的32位依賴庫。

當前wine64的成熟度和穩定性不如wine。

## Bottles
[Bottles](https://usebottles.com/)是GTK實現的Wine前端，為Wine提供了友好的操作介面。
Bottles支持管理多組Wine環境，配置和數據位於`~/.local/share/bottles`路徑下。
