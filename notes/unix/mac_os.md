<!-- TOC -->

- [macOS 層次結構](#macos-層次結構)
- [常用功能](#常用功能)
	- [常用快捷鍵](#常用快捷鍵)
	- [常用命令行指令](#常用命令行指令)
	- [常用軟件](#常用軟件)
	- [托盤圖標](#托盤圖標)
	- [特殊目錄](#特殊目錄)
	- [文件系統](#文件系統)
		- [掛載 NTFS 讀寫](#掛載-ntfs-讀寫)
- [與常規PC的不同之處](#與常規pc的不同之處)
	- [Darwin 與 GNU/Linux 的差異](#darwin-與-gnulinux-的差異)
	- [NVRAM](#nvram)
	- [重置 NVRAM](#重置-nvram)
	- [禁用翻蓋自啓](#禁用翻蓋自啓)
- [包管理](#包管理)
	- [Homebrew](#homebrew)
		- [配置與安裝](#配置與安裝)
		- [基本指令](#基本指令)
		- [路徑信息](#路徑信息)
		- [安裝參數](#安裝參數)
		- [bottled](#bottled)
		- [依賴查詢](#依賴查詢)
		- [Homebrew Taps](#homebrew-taps)
		- [Homebrew Cask](#homebrew-cask)
		- [Homebrew Services](#homebrew-services)
		- [配置國內源](#配置國內源)
- [macOS下的軟件格式](#macos下的軟件格式)
	- [Bundle](#bundle)
	- [pkg](#pkg)
	- [軟件路徑](#軟件路徑)
- [常見問題](#常見問題)
	- [切換分辨率/語言時，登陸界面的分辨率/語言依然不變](#切換分辨率語言時登陸界面的分辨率語言依然不變)
	- [更改默認應用程序](#更改默認應用程序)
	- [在BootCamp安裝的Windows中調整分區，重啓後Mac分區在啓動頁中消失](#在bootcamp安裝的windows中調整分區重啓後mac分區在啓動頁中消失)
	- [引導 Linux](#引導-linux)
	- [重置 Launchpad](#重置-launchpad)
	- [設置 Xcode 路徑](#設置-xcode-路徑)
	- [簽名 GDB](#簽名-gdb)
	- [安裝 mysql/mariadb](#安裝-mysqlmariadb)
	- [完整刪除 JDK](#完整刪除-jdk)
	- [刪除 GarageBand](#刪除-garageband)
	- [MacBook 合蓋無法正常休眠](#macbook-合蓋無法正常休眠)

<!-- /TOC -->



# macOS 層次結構
`macOS`基於`Darwin`(對應`GNU/Linux`)。

- `Darwin`包含內核`XNU`(對應`Linux Kernel`)以及shell環境(對應`GNU Tools`)。
- `XNU`內核由微內核`Mach`和`BSD`層以及一些其它組件(主要爲驅動層`IoKit`)構成。
- `Mach`微內核提供了基本的硬件抽象，提供了一套獨有的`Mach Trap`(`Mach`系統調用)。
- `BSD`層提供了文件系統抽象以及`POSIX`調用。
- `macOS`在文件佈局以及配置方式上與傳統的Linux發行版**有較大不同**。



# 常用功能
記錄macOS的常用快捷鍵、工具指令。

## 常用快捷鍵
- 鎖屏: `Control + Shift + Power`
- 全屏截圖: `Shift + Command + 3`
- 指定位置截圖: `Shift + Command + 4`
- 指定窗口截圖: `Shift + Command + 4`然後將光標放在需要截圖的窗口上，按`Space`確認
- 保存: `Command + S`
- 全選: `Command + A`
- 行首/行尾: `Control + A/E`(終端內)
- Home/End/PageDown/PageUp: `Fn + Left/Right/Down/Up`
- 複製/粘貼文件: `Command + C/V`
- 剪切文件: `Option + Command + V`
- 切換程序: `Command + Tab`
- 切換當前程序的窗口: `Command + \`
- 退出程序: `Command + Q`
- 關閉當前窗口: `Command + W`
- 最小化窗口: `Command + M`
- 立即息屏進入睡眠: `Command + Alt + Power`

## 常用命令行指令
`macOS`中的一些配置項沒有提供圖形化的配置方式，需要通過命令行進行配置。

- 主機信息相關

	設置主機名稱：

	```
	# scutil --set HostName [主機名]
	```

	設置主機共享名稱：

	```
	# scutil --set ComputerName [主機共享名稱]
	```

- 通知中心相關

	設置通知中心點的通知停留時間：

	```
	$ defaults write com.apple.notificationcenterui bannerTime [數值] //控單位爲秒
	```

	恢復默認的通知停留時間：

	```
	$ defaults delete com.apple.notificationcenterui bannerTime //默認爲一直顯示
	```

- 顯示/取消顯示隱藏文件：

	```
	$ defaults write com.apple.finder AppleShowAllFiles YES/NO //重新登陸賬戶後生效
	```

## 常用軟件
- `The Unarchiver` 解壓軟件
- `VLC` 多媒體播放器
- `AppCleaner` APP卸載工具
- `MacDown` 所見即所得的Markdown編輯工具
- `Xcode` 集成開發環境
- `iTerm2` 終端模擬器，相比自帶終端擁有更多高級特性

## 托盤圖標
`macOS`下托盤圖標可以使用`Command + 鼠標左鍵`點選，拖動進行排序。

鎖屏托盤圖標無法直接在系統設置中調出，需要打開`Keychain Access.app`，
在`Reference`中勾選`Show keychain status in menu bar`選項。

## 特殊目錄
系統中特定功能相關的路徑介紹。

| 路徑 | 功能 |
| :- | :- |
| /System/Library/Fonts | 系統默認字體目錄 |
| /Library/Fonts | 系統可選字體目錄 |
| /Volumes | 系統默認掛載目錄 |
| ~/Library/Fonts | 用戶字體目錄 |
| ~/Library/Caches | 緩存目錄 |
| ~/Library/Application Support | 用戶程序文件、配置目錄 |
| /Library/Application Support | 系統程序配置目錄 |
| ~/Library/Preferences | 用戶程序配置目錄 |
| ~/Library/Saved Application State | 用戶程序狀態目錄 |
| ~/Library/VirtualBox | VirtualBox的配置文件目錄，刪除則VirtualBox恢復初始狀態，需要重新添加虛擬機 |

刪除一個應用後，通常需要檢查Library路徑下的`Caches`、`Preferences`、`Application Support`、`Saved Application State`等路徑，清理軟件的殘餘配置。

## 文件系統
`macOS`默認文件系統爲`HFS+`，此類文件系統同時支持區分大小寫(`Case-Sensitive`)和忽略大小寫兩種類型，在格式化時可以進行選擇。
若選擇了區分大小寫形式的`HFS+`文件系統，則部分軟件將無法安裝(如`PhotoShop`等)。

文件系統類型在安裝了macOS之後除了重裝系統之外無法更改，需要**慎重選擇**。

### 掛載 NTFS 讀寫
默認情況下，`macOS`以**只讀**形式掛載`NTFS`文件系統，但`macOS`本身實現了對`NTFS`文件系統的寫入功能，
創建`/etc/fstab`文件，在其中添加掛載選項：

```
LABEL=[label_name] none ntfs rw,auto,nobrowse
```

- `label_name`爲分區的名稱。
- `rw`參數表示以**讀寫**的方式掛載分區。
- `nobrowse`參數表示分區不直接顯示在Finder中，`rw`參數必須與`nobrowse`參數搭配，否則無法掛載`NTFS`分區。

使用`open`指令可以在`Finder.app`中查看設置了`nobrowse`屬性的分區：

```
$ open /Volumes
```



# 與常規PC的不同之處
Mac機與常規的PC有較大的差異，需要一個適應過程。

基本操作差異:

1. 缺少一些常用按鍵，且**按鍵邏輯不統一**：

	- 沒有`Home`、`End`、`PageDown`、`PageUp`等按鍵，需要通過`Fn`搭配**方向鍵**等組合鍵才能實現行首、行尾、翻頁等操作。
	- 在部分編輯器以及終端中，跳轉到**行首/行尾**需要通過`Control + A/E`等按鍵完成。
	- 在部分開發環境中，行首行尾的快捷鍵不使用系統方案，而由程序自身定義(如在`Eclipse`中，行首/行尾爲`Command + 方向鍵左/右`)。

1. `Finder.app`缺少必備的功能：

	- `Finder.app`右鍵菜單中沒有創建文件的選項，甚至新建文件都需要使用`touch`指令。
	- `Finder.app`右鍵菜單沒有剪切功能，通過組合鍵能實現類似效果。

1. 主要按鍵名稱與`PC`機不同：

	- `Windows/Linux`中以`Control`作爲組合鍵觸發的一些快捷操作在`macOS`中全部使用`Command`鍵進行觸發。
	- `Windows/Linux`中的`Alt`鍵在`macOS`中名稱爲`Option`鍵。

## Darwin 與 GNU/Linux 的差異
`Darwin`提供的`Unix`環境基於`FreeBSD`，與傳統`GNU/Linux`有較大差異。

1. `Darwin`爲混合內核架構，`Linux`爲宏內核架構。
1. `Linux`中普通用戶UID從`1000`開始，`macOS`中UID從`500`開始。
1. 家目錄與Linux/BSD中不同，macOS中的`/home`目錄默認爲**空**，用戶家目錄的位置爲`/Users`。
1. `root`用戶家目錄與Linux中不同，位於`/var/root`。
1. `Darwin`沒有用於展示系統運行狀態的`/proc`目錄。
1. `Darwin`沒有默認的包管理器。
1. `Darwin`的`PATH`環境變量記錄在文件`/etc/paths`中。
1. `Darwin`的微內核`Mach`使用`Mach-O`作爲二進制格式，而傳統的`Linux/Unix`使用`EFL`作爲二進制格式。
1. `Darwin`中動態鏈接庫後綴名爲`dylib`，傳統`Unix`中一般爲`so`，靜態庫後綴名與傳統`Unix`相同，皆爲`a`。
1. `Darwin`不使用GNU工具鏈，默認工具鏈爲FreeBSD工具鏈。
1. `macOS`採用`Aqua`作爲GUI實現，傳統`Unix`使用`X11`。



## NVRAM
`NVRAM`全稱`Non-volatile random-access memory`(非易失性隨機訪問存儲器)，用於在關機狀態下保存信息。
Mac使用NVRAM存儲音量、顯示屏分辨率、啓動磁盤選擇、時區，內核崩潰轉儲等信息。

在`macOS`中使用`nvram`指令操作NVRAM相關功能：

```
nvram: (usage: no such option as -h)
nvram [-x] [-p] [-f filename] [-d name] [-c] name[=value] ...
	-x         use XML format for printing or reading variables
	           (must appear before -p or -f)
	-p         print all firmware variables
	-f         set firmware variables from a text file
	-d         delete the named variable
	-c         delete all variables
	name=value set named variable
	name       print variable
Note that arguments and options are executed in order.
```

## 重置 NVRAM
啓動配置異常時，可嘗試重置NVRAM。
開機時按下組合鍵`Option + Command P + R`，按住組合鍵20秒後可鬆開。
在此期間Mac可能看似在重新啓動。

## 禁用翻蓋自啓
從`New MacBook`和`MacBook Pro 2016`開始，MacBook會在翻蓋後自動開機。
可通過修改NVRAM參數關閉此特性：

```
# nvram AutoBoot=%00
```

禁用翻蓋自動開機特性後，翻蓋後機器會短暫地在屏幕顯示電量信息。

恢復翻蓋自動開機特性：

```
# nvram AutoBoot=%03
```



# 包管理
`Homebrew`是`macOS`當下最流行、最主流的包管理器；`MacPorts`來自於`FreeBSD`，亦是優秀的包管理器。

二者之間的差異：

- Homebrew基於`Git`，是輕量級的包管理器，傾向於最大化利用macOS自帶的Unix組件。
- MacPorts是FreeBSD中`Ports`系統的移植，使用源碼編譯軟件，不依賴原有macOS中的軟件包，而是獨立構建出一套環境。
- Homebrew中軟件包多數以二進制形式提供，默認安裝路徑爲`usr/local`。
- MacPorts編譯的軟件包一般安裝在`/opt`目錄下。

## Homebrew
Homebrew使用`Ruby`語言實現。

與傳統的包管理器不同，使用Homebrew並不需要使用`root`用戶，管理員權限用戶即可。
Homebrew將軟件包安裝在`/usr/local`目錄下，在macOS中該目錄默認情況下爲**空**，因此當用戶不再需要使用Homebrew時，只需完整刪除`/usr/local`目錄下的所有內容即可。(需要注意，某些非Bundle形式安裝的軟件亦會將一些內容安裝在`/usr/local`目錄下，如`VirtualBox`。若安裝了此類軟件，清理`/usr/local`目錄時需要仔細辨別)

默認情況下，在macOS中，`/usr/local`的所有者爲`root`，用戶組爲`wheel`，安裝Homebrew時，安裝腳本會將該目錄所有者會更改爲**當前管理員用戶**，並將用戶組改爲`admin`。

### 配置與安裝
Homebrew採用`Ruby`語言開發，`macOS`中默認已經集成了Ruby環境。
Homebrew需要用到Git等工具，在安裝Homebrew之前需要先安裝**Xcode命令行**工具(或者直接完整安裝Xcode)。

之後在終端內執行：

```sh
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

### 基本指令
Homebrew基本操作與其它包管理器類似：

- `$ brew update` 更新源
- `$ brew ugrade` 升級包
- `$ brew info [package_name]` 顯示指定包的信息
- `$ brew install [package_name]` 安裝指定包
- `$ brew switch [package_name] [version]` 若安裝了多個版本的包，切換指定包的使用版本
- `$ brew dockor` 檢測可能存在的問題，並給出修復提示
- `$ brew prune` 移除無效的符號鏈接

與Linux下的常規包管理器不同，Homebrew在安裝、卸載包時，不會有多餘的確認提示，輸入指令後立即執行。

### 路徑信息
`homebrew`倉庫中的包安裝後文件保存在`/usr/local/Cellar`路徑下。
`caskroom`倉庫中的包安裝後文件保存在`/usr/local/Caskroom`路徑下。

`homebrew`倉庫默認的包緩存路徑爲`~/Library/Caches/Homebrew`。
`caskroom`倉庫默認的包緩存路徑爲`~/Library/Caches/Homebrew/Cask`。

可使用指令查看`Homebrew`的相關路徑：

- `$ brew --cache` 查看緩存路徑
- `$ brew --repo` 查看`Hombrew`安裝路徑

在緩存中的包重複安裝無需重新下載。
由於國內網絡問題，直接通過`brew`指令安裝包有時會頻繁下載失敗。
可直接使用其它下載工具從符合要求的源地址下載包文件放置於對應緩存路徑下，進行離線安裝。

對於帶有頭文件的包(如`boost、gcc`等)，會在`/usr/local/include`目錄下創建符號鏈接，
指向`/usr/local/Cellar`目錄中的具體包內容。

### 安裝參數
Homebrew使用`brew install`指令安裝包時可以附加額外選項，用於定製包的依賴。
每個包擁有不同的依賴項，使用`brew info`指令查看`Options`說明。

以`neofetch`爲例，brew info輸出信息如下：

```
$ brew info neofetch
neofetch: ...
...
==> Dependencies
Recommended: screenresolution ✘, imagemagick ✘
==> Options
--without-imagemagick
	Build without imagemagick support
--without-screenresolution
	Build without screenresolution support
--HEAD
	Install HEAD version
```

neofetch需要兩個可選依賴包`screenresolution`、`imagemagick`，默認安裝時會同時安裝依賴包。
使用參數`--without-imagemagick --without-screenresolution`安裝可忽略依賴。

### bottled
Homebrew對於常用的包如`gcc、gdb、python3、qt`等均提供了**預編譯包**(`bottled`)，
但部分包默認安裝時會優先選擇從源碼編譯(如`gcc`、`python`)，可在安裝時使用`--force-bottle`參數強制安裝預編譯的包：

```
$ brew install [軟件包] --force-bottle
```

`--force-bottle`參數與其它安裝參數不同，不會記錄到安裝信息中，
默認使用源碼編譯的包即使強制安裝預編譯包在下次升級時依舊會從源碼編譯。
要使源碼編譯包在升級時安裝預編譯包，則在使用升級指令時也需要添加--force-bottle參數：

```
$ brew upgrade --force-bottle
```

需要注意，bottled版本的gcc在編譯時需要手動指定`sys_root`參數，否則會出現找不到頭文件的情況。
以`GCC 7.2.0`和`XCode 8.3.3`爲例：

```
$ cc-7 [源碼文件]... --sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk
```

### 依賴查詢
Hombrew在軟件包的安裝信息中並不記錄**安裝原因**，即無法區分一個軟件包是主動安裝還是作爲其它軟件包的依賴而安裝。
使用brew remove卸載軟件包時，不會卸載該軟件包的依賴包，即使這些依賴包沒有再被其它安裝的軟件包依賴。

查看所有不被其它已安裝軟件包依賴的包：

```
$ brew leaves
```

通過brew leaves指令的輸出結果中篩選出不是主動安裝的軟件包進行卸載，以此達到清理無用依賴的目的。

其它依賴管理相關指令：

```sh
# 查看指定軟件包的依賴
$ brew deps [軟件包名稱]

# 顯示指定軟件包被哪些軟件包依賴
$ brew uses [軟件包名稱]
# 顯示指定軟件包被哪些已安裝的軟件包依賴
$ brew uses --installed [軟件包名稱]
```

### Homebrew Taps
使用`brew tap/untap`相關指令管理Homebrew啓用的倉庫。
倉庫信息位於`$(brew --repo)/Library/Taps`路徑下，常用指令：

- `$ brew tap` 列出已啓用的倉庫
- `$ brew tap [repo_name]` 啓用指定名稱的倉庫
- `$ brew tap --list-official` 列出官方提供的倉庫
- `$ brew untap [repo_name]` 禁用指令名稱的倉庫

### Homebrew Cask
使用`brew cask`指令可以安裝macOS專屬的Bundle封裝應用。
常用指令：

- `$ brew cask install [app_name]` 安裝應用
- `$ brew cask uninstall [app_name]` 移除某個應用
- `$ brew cask reinstall [app_name]` 重新安裝應用(重新安裝時會安裝應用最新版本，用於升級應用)
- `$ brew cask outdated` 顯示具有新版本的應用
- `$ brew cask list` 列出已在本地安裝的應用
- `$ brew cask search [app_name]` 搜索應用
- `$ brew cask info [app_name]` 查看某個應用的詳細信息

使用`brew cask`安裝的應用位於`/Application`路徑下。
安裝常用應用：

```
$ brew install appcleaner filezilla intellij-idea onedrive teamviewer visual-studio-code blender flash-npapi java qq the-unarchiver vlc docker google-chrome lantern qt-creator virtualbox
```

`brew cask`沒有提供升級所有應用的指令，可以組合使用以下指令達到類似效果：

```
$ brew cask outdated | xargs brew cask reinstall
```

部分應用打包時並未寫明確切的版本號(如`google-chrome`)，此類應用升級需要執行重新安裝指令：

```
$ brew reinstall [需要更新的應用名稱]
```

默認的`Homebrew Cask`倉庫`caskroom/cask`僅保存最新版的應用，若需要同時安裝多個版本(如`Java SDK`)，
則需要開啓`caskroom/versions`倉庫。
執行指令：

```
$ brew tap caskroom/versions
```

`caskroom/versions`倉庫保存了常見應用的長期維護版本，如`Java SDK`的`java6/java8`，`FireFox`的`firefox-beta/firefox-esr`。

### Homebrew Services
對於使用`Homebrew`安裝的包，若包提供了服務，則可以使用`brew services`指令進行服務狀態管理。
常用指令：

- `$ brew services list` 列出可用服務
- `$ brew services run [service_name]` 啓動服務
- `$ brew services start [service_name]` 啓動服務並設置服務開機自啓
- `$ brew services stop [service_name]` 停止服務並移除服務開機自啓
- `$ brew services restart [service_name]` 重啓服務
- `$ brew services cleanup` 清理未被使用的服務

### 配置國內源
默認情況下，Homebrew訪問`GitHub`來更新包數據，速度較慢，可使用國內源替代，推薦使用中科大源`USTC`源。

- 替換更新數據源：

	替換`Homebrew`源，在`$(brew --repo)`路徑下執行：

	```
	$ git remote set-url origin https://mirrors.ustc.edu.cn/brew.git
	```

	替換`homebrew/core`更新源，在`$(brew --repo)/Library/Taps/homebrew/homebrew-core`路徑下執行：

	```
	$ git remote set-url origin https://mirrors.ustc.edu.cn/homebrew-core.git
	```

	替換`caskroom/cask`更新源，在`$(brew --repo)/Library/Taps/caskroom/homebrew-cask`路徑下執行：

	```
	$ git remote set-url origin https://mirrors.ustc.edu.cn/homebrew-cask.git
	```

- 替換`Bottles`源：

	Homebrew在Bottles源中提供了常用包的預編譯二進制包。
	在默認Shell的**配置文件**中設置`HOMEBREW_BOTTLE_DOMAIN`環境變量：

	```
	export HOMEBREW_BOTTLE_DOMAIN=https://mirrors.ustc.edu.cn/homebrew-bottles
	```

- 恢復官方源：

	執行以下指令：

	```
	$ cd "$(brew --repo)"
	$ git remote set-url origin https://github.com/Homebrew/brew.git
	$ cd "$(brew --repo)"/Library/Taps/homebrew/homebrew-core
	$ git remote set-url origin https://github.com/Homebrew/homebrew-core.git
	$ cd "$(brew --repo)"/Library/Taps/caskroom/homebrew-cask
	$ git remote set-url origin https://github.com/caskroom/homebrew-cask.git
	```



# macOS下的軟件格式
在macOS中，軟件包常以`dmg`格式的鏡像封存，而安裝軟件的方式分爲`Bundle`以及`pkg`形式。

## Bundle
在macOS中最常見的軟件包是以`Bundle`的形式存在的，`Bundle`是一個以`.app`爲後綴的**目錄**，
外觀爲可執行程序的圖標，封裝了程序執行所需的一些必要資源以及真正的可執行文件。

`dmg`鏡像中若直接包含`Bundle`，則將其複製到`/Application`或`~/Application`目錄下即可(推薦存放在用戶的`Application`目錄下)。
常規的`Bundle`程序所有者爲**當前用戶**。

## pkg
一些大型的軟件包如Adobe系列、Office系列等的dmg鏡像中保存的是pkg格式的安裝包，雙擊進行安裝，步驟與Windows系統下的安裝流程類似。

通過pkg安裝的軟件最終也會在`/Application`目錄下創建軟件的Bundle，但通過此種方式安裝的軟件往往會在系統的其它目錄創建程序所需的額外文件。

通過pkg安裝的軟件所有者一般爲`root`，不能隨意移動到`~/Application`路徑下。

## 軟件路徑
默認情況下，`Bundle`形式的軟件一般存在於`/Application`目錄或`~/Application`目錄下。
`macOS`的系統默認`Bundle`應用存放在`/Application`目錄下，一些以`pkg`形式安裝或通過`AppStore`安裝的應用也在該目錄下。

默認情況下`~/Application`目錄不存在，需要自行創建。
用戶自行安裝的Bundle應用推薦存放在`~/Application`目錄下，避免與系統程序混淆。



# 常見問題
記錄一些常見問題的解決方案。

## 切換分辨率/語言時，登陸界面的分辨率/語言依然不變
可以嘗試更改登錄界面的選項。
或嘗試以下指令:

```
# languagesetup
```

登陸界面的分辨率/語言未發生變化是由於登陸界面的數據未更新，使用`root`權限執行`languagesetup`重設語言即會刷新登陸界面信息。

## 更改默認應用程序
1. 使用`Command + i`查看一個文件的詳細信息。
1. 在`Open With:`條目中可以選擇打開此文件使用的默認程序，修改爲需要的程序。
1. 選擇`Change All...`將所有此類文件全部修改爲自定義的程序。

## 在BootCamp安裝的Windows中調整分區，重啓後Mac分區在啓動頁中消失
發生此種情況的原因是Windows下的一些分區管理工具將Mac分區的分區`Type UUID`改成了Windows的`Type UUID`，只需將分區類型ID改回來即可恢復Mac分區。

具體解決方法：

- 使用`Windows`自帶的`diskpart`分區工具更改`Type UUID`。

	在`CMD`下執行以下指令：

	- `> diskpart` 進入diskpart分區工具
	- `> list disk` 列出所有磁盤
	- `> select disk [磁盤號]` 指定正在使用的磁盤
	- `> list partition` 列出所選磁盤中的所有分區
	- `> select partition [分區號]` 指明macOS所在的分區號
	- `> set id=48465300-0000-11AA-AA11-00306543ECAC` 設置分區的`Type UUID`

- 在`Linux/Unix`系統中，亦可使用`parted`工具進行分區類型ID變更。

	在分區標識中去掉`msdata`(Windows分區標誌)：

	```
	# parted [磁盤路徑] print all //查看所有磁盤信息，確認分區編號
	# parted [磁盤路徑] set [分區號] msdata on/off //移除msdata分區標誌
	```

## 引導 Linux
使用默認的bootloader可以直接引導Linux系統。
需要創建一個`100MB`左右的分區(其實可以更小)，在分區的中創建`System/Library/CoreServices`目錄：

```
$ mkdir -p /Volumes/[啓動分區名稱]/System/Library/CoreServices
```

並在該目錄中放入`Linux`的`efi`啓動文件。
同時創建系統描述文件：

```
$ nano /Volumes/[啓動分區名稱]/System/Library/CoreServices/SystemVersion.plist
```

在描述文件中添加以下內容：

```xml
<?xml version="1.0" encoding="utf-8"?>
<plist version="1.0">
<dict>
	<key>ProductBuildVersion</key>
	<string></string>
	<key>ProductName</key>
	<string>Linux</string>
	<key>ProductVersion</key>
	<string>Arch Linux</string>
</dict>
</plist>
```

然後使用macOS系統的啓動管理器`bless`來創建啓動項，執行指令：

```
# bless --folder=/Volumes/[啓動分區名稱]/System/Library/CoreServices/ --file=/Volumes/[啓動分區名稱]/System/Library/CoreServices/boot.efi --setBoot
```

## 重置 Launchpad
`Launchpad`中數據保存在`~/Library/Application Support/Dock`路徑下，若Launchpad圖標出現異常(如已刪除軟件圖標依然存在)，可以嘗試清空其中的數據。
刪除該目錄之後，`Launchpad`會在下次開機之後重置圖標佈局，恢復成默認的樣式(Apple自帶的軟件佔一頁，用戶自行安裝的軟件從第二頁開始)。

## 設置 Xcode 路徑
`Xcode`中包含了一系列命令行工具如`clang`、`git`等，Homebrew的安裝也依賴於這些命令行工具。
默認情況下，安裝Xcode同時會自動配置相關路徑信息。

查看Xcode命令行路徑：

```
$ xcode-select -p
```

對於從AppStore安裝Xcode的用戶，會得到以下輸出：

```
/Applications/Xcode.app/Contents/Developer
```

若用戶移動了`Xcode.app`的位置，則需要重新設定Xcode的路徑，否則會出現找不到命令行工具的情況。
使用`xcode-select`設定Xcode的安裝位置：

```
# xcode-select --switch [Xcode.app路徑]/Contents/Developer
```

若該變了Xcode.app的位置，即使使用`xcode-select`重新設定Xocde.app的路徑，通過`Homebrew`安裝的編譯器(如`gcc`)依然會出現找不到頭文件的情況，此時需要重新安裝包。

## 簽名 GDB
新版的macOS系統中，`clang`作爲默認編譯器取代了`gcc`，`lldb`作爲默認編譯器取代了`gdb`。
默認配置下，使用Homebrew安裝的`gdb`調試器**不能**在普通用戶下正常調試代碼，
需要對其進行**簽名**後才能使其正常調試代碼。

簽名步驟：

1. 使用`KeyChain Access.app`創建一個證書(`certificate`)。
1. 證書的`Certificate Type`要設爲`Code Signing`。
1. 證書的`KeyChain`要設爲`System`，`Trust`列表中的`CodeSigning`屬性要設置爲`Always Trust`。

成功創建了證書之後，使用`codesign`命令對`gdb`進行簽名：

```
$ codesign -s [證書名稱] [gdb安裝路徑]
```

證書需要在系統重啓之後纔會生效。
需要注意的是，每次gdb包升級，都需要重新使用證書對其進行簽名，否則不能正常調試代碼。

## 安裝 mysql/mariadb
通過Homebrew安裝的mysql/mariadb使用時不需要root權限。

- mariadb/mysql數據庫的操作指令相同，因此mariadb與mysql軟件包相互衝突。
- mariadb/mysql數據庫存儲位置相同，路徑爲`/usr/local/var/mysql`。
- mariadb/mysql配置文件相同，路徑爲`/usr/local/etc/my.cnf`。

mariadb/mysql使用`mysql.server`指令管理服務：

- `$ mysql.server start` 啓動服務
- `$ mysql.server stop` 停止服務

亦可通過`brew services`相關指令管理管理服務。

## 完整刪除 JDK
`JDK`需要自行手工刪除，相關文件位於以下路徑：

1. `/Library/Java/JavaVirtualMachines/*`
1. `/Library/Internet Plug-Ins/JavaAppletPlugin.plugin`
1. `/Library/PreferencePanes/JavaControlPanel.prefPane`

刪除JDK時需要手動移除這些目錄、文件。
安裝新版本的JDK時，舊版本JDK不會自動卸載，相關文件依然位於`/Library/Java/JavaVirtualMachines`路徑下，
文件夾名稱即爲對應的JDK版本，手動刪除不需要的版本即可。

完整移除JDK還需刪除以下配置：

1. `/Library/Preferences/com.oracle.java.Helper-Tool.plist`
1. `/Library/LaunchDaemons/com.oracle.java.Helper-Tool.plist`
1. `/Library/LaunchAgents/com.oracle.java.Java-Updater.plist`

## 刪除 GarageBand
macOS預裝了音頻編輯軟件`GarageBand`，卸載時需要刪除以下路徑的內容：

1. `/Applications/GarageBand.app`
1. `/Library/Application Support/GarageBand`
1. `/Library/Application Support/Logic`
1. `/Library/Audio/Apple Loops`

僅刪除`GarageBand.app`，在`System Information`中的`Music Creation`類別中依舊會顯示包含大量空間佔用。

## MacBook 合蓋無法正常休眠
MacBook可能會因爲`tcpkeepalive`配置問題導致合蓋時WIFI不關閉，進而機器不進入休眠狀態，
導致合蓋後電量消耗過大(一晚15%電量左右，正常休眠一晚消耗1% ~ 3%電量)。

使用`pmset`工具查看、管理電源配置：

```c
// 列出使用的電源配置
$ pmset -g custom
Battery Power:
 lidwake              1
 autopoweroff         1
 autopoweroffdelay    28800
 standbydelay         10800
 standby              1
 ttyskeepawake        1
 hibernatemode        3
 powernap             0
 gpuswitch            2
 hibernatefile        /var/vm/sleepimage
 displaysleep         2
 sleep                1
 tcpkeepalive         1
 halfdim              1
 acwake               0
 lessbright           1
 disksleep            10
AC Power:
 lidwake              1
 autopoweroff         1
 autopoweroffdelay    28800
 standbydelay         10800
 standby              1
 ttyskeepawake        1
 hibernatemode        3
 powernap             1
 gpuswitch            2
 hibernatefile        /var/vm/sleepimage
 displaysleep         30
 womp                 1
 networkoversleep     0
 sleep                0
 tcpkeepalive         1
 halfdim              1
 acwake               0
 disksleep            10
```

輸出結果中，`Battery Power`代表電池供電時的電源管理策略；`AC Power`代表電源供電時的電源管理策略。

tcpkeepalive選項值爲`1`代表改特性已啓用，啓用該特性會導致合蓋WIFI不關閉，進而休眠失敗。
禁用tcpkeepalive特性：

```c
// 禁用電池供電時的tcpkeepalive特性
# pmset -b tcpkeepalive 0

// 禁用電源供電時的tcpkeepalive特性
# pmset -c tcpkeepalive 0

// 禁用所有電源策略下的tcpkeepalive特性
# pmset -a tcpkeepalive 0
```

禁用tcpkeepalive特性需要以root權限執行pmset指令。
禁用tcpkeepalive特性時終端會輸出以下信息，提示部分功能如`Find My Mac`會受到影響：

```
Warning: This option disables TCP Keep Alive mechanism when sytem is sleeping. This will result in some critical features like 'Find My Mac' not to function properly.
```

需要注意，在`System Reference`的`Energy Saver`中選擇`Restore Defaults`將電源管理策略重置爲默認值時，
tcpkeepalive配置也會被重置爲默認值(`1`)，會重新導致休眠失敗。
