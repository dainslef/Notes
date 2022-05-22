<!-- TOC -->

- [MSYS2](#msys2)
	- [下載與安裝](#下載與安裝)
	- [配置倉庫與源](#配置倉庫與源)
	- [包管理](#包管理)
	- [設置中文LC](#設置中文lc)
	- [pacman-key/msys2-keyring更新錯誤](#pacman-keymsys2-keyring更新錯誤)
- [Windows Linux Subsystem](#windows-linux-subsystem)
	- [LXSS](#lxss)
	- [WSL](#wsl)
	- [WSL2](#wsl2)
- [Linux Subsystem 與 MSYS2 比較](#linux-subsystem-與-msys2-比較)
- [Wine](#wine)
	- [安裝和配置Wine](#安裝和配置wine)

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



# Windows Linux Subsystem
在`Windows 10`週年更新`Version 1607`中引入了`Linux Subsystem`(簡稱`LXSS`)，
之後`Version 1709`中正式發布定名`Windows Subsystem for Linux`(簡稱`WSL`)。

## LXSS
啓用LXSS需要執行以下步驟：

1. `設置`中啓用`開發人員模式`。
1. `啓用或關閉Windows功能`中勾選`適用於Linux的Windows子系統`。
1. 在CMD中輸入bash指令，按照提示即可進入子系統安裝步驟。

LXSS的安裝路徑爲`[用戶目錄]/AppData/Local/Lxss`路徑下。
默認的資源管理器配置下，該目錄不可見，需要取消勾選`隱藏受保護的操作系統文件(推薦)`選項才能顯示此目錄。

在LXSS中，Windows下的分區會被掛載到`/mnt`路徑下。

LXSS使用`lxrun`工具進行管理：

```html
> lxrun /install <!-- 安裝子系統 -->
> lxrun /uninstall <!-- 移除子系統，默認情況下保留`/home`和`/root`目錄，指令搭配`/full`參數則執行完全卸載 -->
> lxrun /update <!-- 更新子系統的包索引 -->
> lxrun /setdefaultuser <!-- 配置子系統用戶 -->
```

## WSL
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

## WSL2
WSL基於API轉發的實現存在一系列問題：

- 文件系統性能(file system performance)
- 完整的系統調用兼容性(full system call compatibility)

為了改善這些問題，微軟提出了基於虛擬化技術的WSL2。
WSL2需要`Windows Version 1903`或更高的版本。

關於WSL/WSL2的對比，參見[微軟官方文檔](https://docs.microsoft.com/en-us/windows/wsl/compare-versions)。



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
