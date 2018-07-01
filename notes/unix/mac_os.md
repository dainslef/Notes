- [macOS 层次结构](#macos-层次结构)
	- [常用功能](#常用功能)
	- [常用快捷键](#常用快捷键)
	- [常用命令行指令](#常用命令行指令)
	- [常用软件](#常用软件)
	- [托盘图标](#托盘图标)
	- [特殊目录](#特殊目录)
	- [文件系统](#文件系统)
		- [挂载 NTFS 读写](#挂载-ntfs-读写)
- [与常规PC的不同之处](#与常规pc的不同之处)
	- [Darwin 与 GNU/Linux 的差异](#darwin-与-gnulinux-的差异)
	- [NVRAM](#nvram)
	- [重置 NVRAM](#重置-nvram)
	- [禁用翻盖自启](#禁用翻盖自启)
- [包管理](#包管理)
	- [Homebrew](#homebrew)
		- [配置与安装](#配置与安装)
		- [基本指令](#基本指令)
		- [路径信息](#路径信息)
		- [安装参数](#安装参数)
		- [bottled](#bottled)
		- [Homebrew Taps](#homebrew-taps)
		- [Homebrew Cask](#homebrew-cask)
		- [Homebrew Services](#homebrew-services)
		- [配置国内源](#配置国内源)
- [macOS下的软件格式](#macos下的软件格式)
	- [Bundle](#bundle)
	- [pkg](#pkg)
	- [软件路径](#软件路径)
- [常见问题](#常见问题)
	- [切换分辨率/语言时，登陆界面的分辨率/语言依然不变](#切换分辨率语言时登陆界面的分辨率语言依然不变)
	- [更改默认应用程序](#更改默认应用程序)
	- [在BootCamp安装的Windows中调整分区，重启后Mac分区在启动页中消失](#在bootcamp安装的windows中调整分区重启后mac分区在启动页中消失)
	- [引导 Linux](#引导-linux)
	- [重置 Launchpad](#重置-launchpad)
	- [设置 Xcode 路径](#设置-xcode-路径)
	- [签名 GDB](#签名-gdb)
	- [安装 mysql/mariadb](#安装-mysqlmariadb)
	- [完整删除 JDK](#完整删除-jdk)
	- [删除 GarageBand](#删除-garageband)



# macOS 层次结构
`macOS`基于`Darwin`(对应`GNU/Linux`)。

- `Darwin`包含内核`XNU`(对应`Linux Kernel`)以及shell环境(对应`GNU Tools`)。
- `XNU`内核由微内核`Mach`和`BSD`层以及一些其它组件(主要为驱动层`IoKit`)构成。
- `Mach`微内核提供了基本的硬件抽象，提供了一套独有的`Mach Trap`(`Mach`系统调用)。
- `BSD`层提供了文件系统抽象以及`POSIX`调用。
- `macOS`在文件布局以及配置方式上与传统的Linux发行版**有较大不同**。



## 常用功能
记录macOS的常用快捷键、工具指令。

## 常用快捷键
- 锁屏: `Control + Shift + Power`
- 全屏截图: `Shift + Command + 3`
- 指定位置截图: `Shift + Command + 4`
- 指定窗口截图: `Shift + Command + 4`然后将光标放在需要截图的窗口上，按`Space`确认
- 保存: `Command + S`
- 全选: `Command + A`
- 行首/行尾: `Control + A/E`(终端内)
- Home/End/PageDown/PageUp: `Fn + Left/Right/Down/Up`
- 复制/粘贴文件: `Command + C/V`
- 剪切文件: `Option + Command + V`
- 切换程序: `Command + Tab`
- 切换当前程序的窗口: `Command + \`
- 退出程序: `Command + Q`
- 关闭当前窗口: `Command + W`
- 最小化窗口: `Command + M`
- 立即息屏进入睡眠: `Command + Alt + Power`

## 常用命令行指令
`macOS`中的一些配置项没有提供图形化的配置方式，需要通过命令行进行配置。

- 主机信息相关

	设置主机名称：

	```
	# scutil --set HostName [主机名]
	```

	设置主机共享名称：

	```
	# scutil --set ComputerName [主机共享名称]
	```

- 通知中心相关

	设置通知中心点的通知停留时间：

	```
	$ defaults write com.apple.notificationcenterui bannerTime [数值] //控单位为秒
	```

	恢复默认的通知停留时间：

	```
	$ defaults delete com.apple.notificationcenterui bannerTime //默认为一直显示
	```

- 显示/取消显示隐藏文件：

	```
	$ defaults write com.apple.finder AppleShowAllFiles YES/NO //重新登陆账户后生效
	```

## 常用软件
- `The Unarchiver` 解压软件
- `VLC` 多媒体播放器
- `AppCleaner` APP卸载工具
- `MacDown` 所见即所得的Markdown编辑工具
- `Xcode` 集成开发环境
- `iTerm2` 终端模拟器，相比自带终端拥有更多高级特性

## 托盘图标
`macOS`下托盘图标可以使用`Command + 鼠标左键`点选，拖动进行排序。

锁屏托盘图标无法直接在系统设置中调出，需要打开`Keychain Access.app`，在`Reference`中勾选`Show keychain status in menu bar`选项。

## 特殊目录
- `/System/Library/Fonts` 系统默认字体目录
- `/Library/Fonts` 系统可选字体目录
- `/Volumes` 系统默认挂载目录
- `~/Library/Fonts` 用户字体目录
- `~/Library/Caches` 缓存目录
- `~/Library/Application Support` 用户程序文件、配置目录
- `/Library/Application Support` 系统程序配置目录
- `~/Library/Preferences` 用户程序配置目录
- `~/Library/Saved Application State` 用户程序状态目录
- `~/Library/VirtualBox` VirtualBox的配置文件目录，删除则VirtualBox恢复初始状态，需要重新添加虚拟机

## 文件系统
`macOS`默认文件系统为`HFS+`，此类文件系统同时支持区分大小写(`Case-Sensitive`)和忽略大小写两种类型，在格式化时可以进行选择。  
若选择了区分大小写形式的`HFS+`文件系统，则部分软件将无法安装(如`PhotoShop`等)。

文件系统类型在安装了macOS之后除了重装系统之外无法更改，需要**慎重选择**。

### 挂载 NTFS 读写
默认情况下，`macOS`以**只读**形式挂载`NTFS`文件系统，但`macOS`本身实现了对`NTFS`文件系统的写入功能，创建`/etc/fstab`文件，在其中添加挂载选项：

```
LABEL=[label_name] none ntfs rw,auto,nobrowse
```

- `label_name`为分区的名称。
- `rw`参数表示以**读写**的方式挂载分区。
- `nobrowse`参数表示分区不直接显示在Finder中，`rw`参数必须与`nobrowse`参数搭配，否则无法挂载`NTFS`分区。

使用`open`指令可以在`Finder.app`中查看设置了`nobrowse`属性的分区：

```
$ open /Volumes
```



# 与常规PC的不同之处
Mac机与常规的PC有较大的差异，需要一个适应过程。

基本操作差异:

1. 缺少一些常用按键，且**按键逻辑不统一**：

	- 没有`Home`、`End`、`PageDown`、`PageUp`等按键，需要通过`Fn`搭配**方向键**等组合键才能实现行首、行尾、翻页等操作。
	- 在部分编辑器以及终端中，跳转到**行首/行尾**需要通过`Control + A/E`等按键完成。
	- 在部分开发环境中，行首行尾的快捷键不使用系统方案，而由程序自身定义(如在`Eclipse`中，行首/行尾为`Command + 方向键左/右`)。

1. `Finder.app`缺少必备的功能：

	- `Finder.app`右键菜单中没有创建文件的选项，甚至新建文件都需要使用`touch`指令。
	- `Finder.app`右键菜单没有剪切功能，通过组合键能实现类似效果。

1. 主要按键名称与`PC`机不同：

	- `Windows/Linux`中以`Control`作为组合键触发的一些快捷操作在`macOS`中全部使用`Command`键进行触发。
	- `Windows/Linux`中的`Alt`键在`macOS`中名称为`Option`键。

## Darwin 与 GNU/Linux 的差异
`Darwin`提供的`Unix`环境基于`FreeBSD`，与传统`GNU/Linux`有较大差异。

1. `Darwin`为混合内核架构，`Linux`为宏内核架构。
1. `Linux`中普通用户UID从`1000`开始，`macOS`中UID从`500`开始。
1. 家目录与Linux/BSD中不同，macOS中的`/home`目录默认为**空**，用户家目录的位置为`/Users`。
1. `root`用户家目录与Linux中不同，位于`/var/root`。
1. `Darwin`没有用于展示系统运行状态的`/proc`目录。
1. `Darwin`没有默认的包管理器。
1. `Darwin`的`PATH`环境变量记录在文件`/etc/paths`中。
1. `Darwin`的微内核`Mach`使用`Mach-O`作为二进制格式，而传统的`Linux/Unix`使用`EFL`作为二进制格式。
1. `Darwin`中动态链接库后缀名为`dylib`，传统`Unix`中一般为`so`，静态库后缀名与传统`Unix`相同，皆为`a`。
1. `Darwin`不使用GNU工具链，默认工具链为FreeBSD工具链。
1. `macOS`采用`Aqua`作为GUI实现，传统`Unix`使用`X11`。



## NVRAM
`NVRAM`全称`Non-volatile random-access memory`(非易失性随机访问存储器)，用于在关机状态下保存信息。  
Mac使用NVRAM存储音量、显示屏分辨率、启动磁盘选择、时区，内核崩溃转储等信息。

在`macOS`中使用`nvram`指令操作NVRAM相关功能：

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
启动配置异常时，可尝试重置NVRAM。  
开机时按下组合键`Option + Command P + R`，按住组合键20秒后可松开。  
在此期间Mac可能看似在重新启动。

## 禁用翻盖自启
从`New MacBook`和`MacBook Pro 2016`开始，MacBook会在翻盖后自动开机。  
可通过修改NVRAM参数关闭此特性：

```
# nvram AutoBoot=%00
```

禁用翻盖自动开机特性后，翻盖后机器会短暂地在屏幕显示电量信息。

恢复翻盖自动开机特性：

```
# nvram AutoBoot=%03
```



# 包管理
`Homebrew`是`macOS`当下最流行、最主流的包管理器。  
`MacPorts`来自于`FreeBSD`，亦是优秀的包管理器。

二者之间的差异：

- `Homebrew`基于Git，是轻量级的包管理器，倾向于最大化利用`macOS`自带的Unix组件。
- `MacPorts`是`FreeBSD`中`Ports`系统的移植，使用源码编译软件，不依赖原有macOS中的软件包，而是独立构建出一套环境。
- `Homebrew`中软件包多数以二进制形式提供，默认安装路径为`usr/local`。
- `MacPorts`编译的软件包一般安装在`/opt`目录下。

## Homebrew
`Homebrew`使用`Ruby`语言实现。

与传统的包管理器不同，使用Homebrew并不需要使用`root`用户，管理员权限用户即可。  
`Homebrew`将软件包安装在`/usr/local`目录下，在macOS中该目录默认情况下为**空**，因此当用户不再需要使用Homebrew时，只需完整删除`/usr/local`目录下的所有内容即可。(需要注意，某些非Bundle形式安装的软件亦会将一些内容安装在`/usr/local`目录下，如`VirtualBox`。若安装了此类软件，清理`/usr/local`目录时需要仔细辨别)

默认情况下，在`macOS`中，`/usr/local`的所有者为`root`，用户组为`wheel`，安装Homebrew时，安装脚本会将该目录所有者会更改为**当前管理员用户**，并将用户组改为`admin`。

### 配置与安装
`Homebrew`采用`Ruby`语言开发，`macOS`中默认已经集成了`Ruby`开发环境。  
`Homebrew`需要用到`Git`等`CLI`工具，在安装`Homebrew`之前需要先安装**Xcode命令行**工具(或者直接完整安装Xcode)。

之后在终端内执行：

```
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

### 基本指令
`Homebrew`基本操作与其它包管理器类似：

- `$ brew update` 更新源
- `$ brew ugrade` 升级包
- `$ brew info [package_name]` 显示指定包的信息
- `$ brew install [package_name]` 安装指定包
- `$ brew leaves` 查看没有被其它包依赖的包
- `$ brew deps [package_name]` 显示指定包的依赖
- `$ brew uses [package_name]` 显示指定包被哪些包依赖
- `$ brew switch [package_name] [version]` 若安装了多个版本的包，切换指定包的使用版本
- `$ brew dockor` 检测可能存在的问题，并给出修复提示
- `$ brew prune` 移除无效的符号链接

与Linux下的常规包管理器不同，Homebrew在安装、卸载包时，不会有多余的确认提示，输入指令后立即执行。

### 路径信息
`homebrew`仓库中的包安装后文件保存在`/usr/local/Cellar`路径下。  
`caskroom`仓库中的包安装后文件保存在`/usr/local/Caskroom`路径下。

`homebrew`仓库默认的包缓存路径为`~/Library/Caches/Homebrew`。  
`caskroom`仓库默认的包缓存路径为`~/Library/Caches/Homebrew/Cask`

可使用指令查看`Homebrew`的相关路径：

- `$ brew --cache` 查看缓存路径
- `$ brew --repo` 查看`Hombrew`安装路径

在缓存中的包重复安装无需重新下载。  
由于国内网络问题，直接通过`brew`指令安装包有时会频繁下载失败。  
可直接使用其它下载工具从符合要求的源地址下载包文件放置于对应缓存路径下，进行离线安装。

对于带有头文件的包(如`boost、gcc`等)，会在`/usr/local/include`目录下创建符号链接，指向`/usr/local/Cellar`目录中的具体包内容。

### 安装参数
`Homebrew`使用`brew install`指令安装包时可以附加额外选项，用于定制包的依赖。  
每个包拥有不同的依赖项，使用`brew info`指令查看`Options`说明。

以`neofetch`为例，`brew info`输出信息如下：

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

`neofetch`需要两个可选依赖包`screenresolution`、`imagemagick`，默认安装时会同时安装依赖包。  
使用参数`--without-imagemagick --without-screenresolution`安装可忽略依赖。

### bottled
Homebrew对于常用的包如`gcc、gdb、python3、qt`等均提供了**预编译包**(`bottled`)，但部分包默认安装时会优先选择从源码编译(如`gcc`、`python`)，可在安装时使用`--force-bottle`参数强制安装预编译的包：

```
$ brew install [软件包] --force-bottle
```

--force-bottle参数与其它安装参数不同，不会记录到安装信息中，
默认使用源码编译的包即使强制安装预编译包在下次升级时依旧会从源码编译。
要使源码编译包在升级时安装预编译包，则在使用升级指令时也需要添加--force-bottle参数：

```
$ brew upgrade --force-bottle
```

需要注意，`bottled`版本的`gcc`在编译时需要手动指定`sys_root`参数，否则会出现找不到头文件的情况。  
以`GCC 7.2.0`和`XCode 8.3.3`为例：

```
$ cc-7 [源码文件]... --sysroot=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.12.sdk
```

### Homebrew Taps
使用`brew tap/untap`相关指令管理`Homebrew`启用的仓库。  
仓库信息位于`$(brew --repo)/Library/Taps`路径下。  
常用指令：

- `$ brew tap` 列出已启用的仓库
- `$ brew tap [repo_name]` 启用指定名称的仓库
- `$ brew tap --list-official` 列出官方提供的仓库
- `$ brew untap [repo_name]` 禁用指令名称的仓库

### Homebrew Cask
使用`brew cask`指令可以安装`macOS`专属的`Bundle`封装应用。  
常用指令：

- `$ brew cask install [app_name]` 安装应用
- `$ brew cask uninstall [app_name]` 移除某个应用
- `$ brew cask reinstall [app_name]` 重新安装应用(重新安装时会安装应用最新版本，用于升级应用)
- `$ brew cask outdated` 显示具有新版本的应用
- `$ brew cask list` 列出已在本地安装的应用
- `$ brew cask search [app_name]` 搜索应用
- `$ brew cask info [app_name]` 查看某个应用的详细信息

使用`brew cask`安装的应用位于`/Application`路径下。  
安装常用应用：

```
$ brew install appcleaner filezilla intellij-idea onedrive teamviewer visual-studio-code blender flash-npapi java qq the-unarchiver vlc docker google-chrome lantern qt-creator virtualbox
```

`brew cask`没有提供升级所有应用的指令，可以组合使用以下指令达到类似效果：

```
$ brew cask outdated | xargs brew cask reinstall
```

部分应用打包时并未写明确切的版本号(如`google-chrome`)，此类应用升级需要执行重新安装指令：

```
$ brew reinstall [需要更新的应用名称]
```

默认的`Homebrew Cask`仓库`caskroom/cask`仅保存最新版的应用，若需要同时安装多个版本(如`Java SDK`)，则需要开启`caskroom/versions`仓库。  
执行指令：

```
$ brew tap caskroom/versions
```

`caskroom/versions`仓库保存了常见应用的长期维护版本，如`Java SDK`的`java6/java8`，`FireFox`的`firefox-beta/firefox-esr`。

### Homebrew Services
对于使用`Homebrew`安装的包，若包提供了服务，则可以使用`brew services`指令进行服务状态管理。  
常用指令：

- `$ brew services list` 列出可用服务
- `$ brew services run [service_name]` 启动服务
- `$ brew services start [service_name]` 启动服务并设置服务开机自启
- `$ brew services stop [service_name]` 停止服务并移除服务开机自启
- `$ brew services restart [service_name]` 重启服务
- `$ brew services cleanup` 清理未被使用的服务

### 配置国内源
默认情况下，Homebrew访问`GitHub`来更新包数据，速度较慢，可使用国内源替代，推荐使用中科大源`USTC`源。

- 替换更新数据源：

	替换`Homebrew`源，在`$(brew --repo)`路径下执行：

	```
	$ git remote set-url origin https://mirrors.ustc.edu.cn/brew.git
	```

	替换`homebrew/core`更新源，在`$(brew --repo)/Library/Taps/homebrew/homebrew-core`路径下执行：
	
	```
	$ git remote set-url origin https://mirrors.ustc.edu.cn/homebrew-core.git
	```

	替换`caskroom/cask`更新源，在`$(brew --repo)/Library/Taps/caskroom/homebrew-cask`路径下执行：

	```
	$ git remote set-url origin https://mirrors.ustc.edu.cn/homebrew-cask.git
	```

- 替换`Bottles`源：

	`Homebrew`在`Bottles`源中提供了常用包的预编译二进制包。  
	在默认`Shell`的**配置文件**中设置`HOMEBREW_BOTTLE_DOMAIN`环境变量：
	
	```
	export HOMEBREW_BOTTLE_DOMAIN=https://mirrors.ustc.edu.cn/homebrew-bottles
	```

- 恢复官方源：

	执行以下指令：

	```
	$ cd "$(brew --repo)"
	$ git remote set-url origin https://github.com/Homebrew/brew.git
	$ cd "$(brew --repo)"/Library/Taps/homebrew/homebrew-core
	$ git remote set-url origin https://github.com/Homebrew/homebrew-core.git
	$ cd "$(brew --repo)"/Library/Taps/caskroom/homebrew-cask
	$ git remote set-url origin https://github.com/caskroom/homebrew-cask.git
	```



# macOS下的软件格式
在`macOS`中，软件包常以`dmg`格式的镜像封存，而安装软件的方式分为`Bundle`以及`pkg`形式。

## Bundle
在`macOS`中最常见的软件包是以`Bundle`的形式存在的，`Bundle`是一个以`.app`为后缀的**目录**，
外观为可执行程序的图标，封装了程序执行所需的一些必要资源以及真正的可执行文件。

`dmg`镜像中若直接包含`Bundle`，则将其复制到`/Application`或`~/Application`目录下即可(推荐存放在用户的`Application`目录下)。  
常规的`Bundle`程序所有者为**当前用户**。

## pkg
一些大型的软件包如Adobe系列、Office系列等的dmg镜像中保存的是pkg格式的安装包，双击进行安装，步骤与Windows系统下的安装流程类似。

通过pkg安装的软件最终也会在`/Application`目录下创建软件的Bundle，但通过此种方式安装的软件往往会在系统的其它目录创建程序所需的额外文件。

通过pkg安装的软件所有者一般为`root`，不能随意移动到`~/Application`路径下。

## 软件路径
默认情况下，`Bundle`形式的软件一般存在于`/Application`目录或`~/Application`目录下。  
`macOS`的系统默认`Bundle`应用存放在`/Application`目录下，一些以`pkg`形式安装或通过`AppStore`安装的应用也在该目录下。

默认情况下`~/Application`目录不存在，需要自行创建。  
用户自行安装的Bundle应用推荐存放在`~/Application`目录下，避免与系统程序混淆。



# 常见问题
记录一些常见问题的解决方案。

## 切换分辨率/语言时，登陆界面的分辨率/语言依然不变
可以尝试更改登录界面的选项。  
或尝试以下指令:

```
# languagesetup
```

登陆界面的分辨率/语言未发生变化是由于登陆界面的数据未更新，使用`root`权限执行`languagesetup`重设语言即会刷新登陆界面信息。

## 更改默认应用程序
1. 使用`Command + i`查看一个文件的详细信息。
1. 在`Open With:`条目中可以选择打开此文件使用的默认程序，修改为需要的程序。
1. 选择`Change All...`将所有此类文件全部修改为自定义的程序。

## 在BootCamp安装的Windows中调整分区，重启后Mac分区在启动页中消失
发生此种情况的原因是Windows下的一些分区管理工具将Mac分区的分区`Type UUID`改成了Windows的`Type UUID`，只需将分区类型ID改回来即可恢复Mac分区。

具体解决方法：

- 使用`Windows`自带的`diskpart`分区工具更改`Type UUID`。

	在`CMD`下执行以下指令：

	- `> diskpart` 进入diskpart分区工具
	- `> list disk` 列出所有磁盘
	- `> select disk [磁盘号]` 指定正在使用的磁盘
	- `> list partition` 列出所选磁盘中的所有分区
	- `> select partition [分区号]` 指明macOS所在的分区号
	- `> set id=48465300-0000-11AA-AA11-00306543ECAC` 设置分区的`Type UUID`

- 在`Linux/Unix`系统中，亦可使用`parted`工具进行分区类型ID变更。

	在分区标识中去掉`msdata`(Windows分区标志)：

	```
	# parted [磁盘路径] print all //查看所有磁盘信息，确认分区编号
	# parted [磁盘路径] set [分区号] msdata on/off //移除msdata分区标志
	```

## 引导 Linux
使用默认的bootloader可以直接引导Linux系统。  
需要创建一个`100MB`左右的分区(其实可以更小)，在分区的中创建`System/Library/CoreServices`目录：

```
$ mkdir -p /Volumes/[启动分区名称]/System/Library/CoreServices
```

并在该目录中放入`Linux`的`efi`启动文件。  
同时创建系统描述文件：

```
$ nano /Volumes/[启动分区名称]/System/Library/CoreServices/SystemVersion.plist
```

在描述文件中添加以下内容：

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

然后使用`macOS`系统的启动管理器`bless`来创建启动项，执行指令：

```
# bless --folder=/Volumes/[启动分区名称]/System/Library/CoreServices/ --file=/Volumes/[启动分区名称]/System/Library/CoreServices/boot.efi --setBoot
```

## 重置 Launchpad
`Launchpad`中数据保存在`~/Library/Application Support/Dock`路径下，若`Launchpad`图标出现异常(如已删除软件图标依然存在)，可以尝试清空其中的数据。  
删除该目录之后，`Launchpad`会在下次开机之后重置图标布局，恢复成默认的样式(Apple自带的软件占一页，用户自行安装的软件从第二页开始)。

## 设置 Xcode 路径
`Xcode`中包含了一系列命令行工具如`clang`、`git`等，Homebrew的安装也依赖于这些命令行工具。  
默认情况下，安装`Xcode`同时会自动配置相关路径信息。

查看`Xcode`命令行路径：

```
$ xcode-select -p
```

对于从`AppStore`安装`Xcode`的用户，会得到以下输出：

```
/Applications/Xcode.app/Contents/Developer
```

若用户移动了`Xcode.app`的位置，则需要重新设定`Xcode`的路径，否则会出现找不到命令行工具的情况。  
使用`xcode-select`设定`Xcode`的安装位置：

```
# xcode-select --switch [Your Xcode Path]/Xcode.app/Contents/Developer
```

若该变了`Xcode.app`的位置，即使使用`xcode-select`重新设定`Xocde.app`的路径，通过`Homebrew`安装的编译器(如`gcc`)依然会出现找不到头文件的情况，此时需要重新安装包。

## 签名 GDB
新版的`macOS`系统中，`clang`作为默认编译器取代了`gcc`，`lldb`作为默认编译器取代了`gdb`。  
默认情况下，使用`Homebrew`安装的`gdb`调试器**不能**在普通用户下正常调试代码，需要对其进行**签名**后才能使其正常调试代码：

1. 使用`KeyChain Access.app`创建一个证书(`certificate`)。
1. 证书的`Certificate Type`要设为`Code Signing`。
1. 证书的`KeyChain`要设为`System`，`Trust`列表中的`CodeSigning`属性要设置为`Always Trust`。

成功创建了证书之后，使用`codesign`命令对`gdb`进行签名：

```
$ codesign -s [证书名称] [gdb安装路径]
```

证书需要在系统重启之后才会生效。  
需要注意的是，每次gdb包升级，都需要重新使用证书对其进行签名，否则不能正常调试代码。

## 安装 mysql/mariadb
通过Homebrew安装的mysql/mariadb使用时不需要root权限。

mariadb/mysql数据库的操作指令相同，因此mariadb与mysql软件包相互冲突。  
mariadb/mysql数据库存储位置相同，路径为`/usr/local/var/mysql`。  
mariadb/mysql配置文件相同，路径为`/usr/local/etc/my.cnf`。

mariadb/mysql使用`mysql.server`指令管理服务：

- `$ mysql.server start` 启动服务
- `$ mysql.server stop` 停止服务

亦可通过`brew services`相关指令管理管理服务。

## 完整删除 JDK
`JDK`需要自行手工删除，相关文件位于以下路径：

1. `/Library/Java/JavaVirtualMachines/*`
1. `/Library/Internet Plug-Ins/JavaAppletPlugin.plugin`
1. `/Library/PreferencePanes/JavaControlPanel.prefPane`

删除`JDK`时需要手动移除这些目录、文件。  
安装新版本的`JDK`时，旧版本`JDK`不会自动卸载，相关文件依然位于`/Library/Java/JavaVirtualMachines`路径下，
文件夹名称即为对应的`JDK`版本，手动删除不需要的版本即可。

完整移除`JDK`还需删除以下配置：

1. `/Library/Preferences/com.oracle.java.Helper-Tool.plist`
1. `/Library/LaunchDaemons/com.oracle.java.Helper-Tool.plist`
1. `/Library/LaunchAgents/com.oracle.java.Java-Updater.plist`

## 删除 GarageBand
`macOS`预装了音频编辑软件`GarageBand`，卸载时需要删除以下路径的内容：

1. `/Applications/GarageBand.app`
1. `/Library/Application Support/GarageBand`
1. `/Library/Application Support/Logic`
1. `/Library/Audio/Apple Loops`

仅删除`GarageBand.app`，在`System Information`中的`Music Creation`类别中依旧会显示包含大量空间占用。
