<!-- TOC -->

- [概述](#概述)
- [安装与配置](#安装与配置)
	- [Stackage](#stackage)
	- [Stack Path](#stack-path)
	- [包管理](#包管理)
	- [安装 GHC](#安装-ghc)
	- [配置 Mirrors](#配置-mirrors)
- [启动与使用](#启动与使用)
	- [创建项目](#创建项目)
	- [项目结构](#项目结构)
- [构建配置](#构建配置)
	- [Cabal 构建配置](#cabal-构建配置)
		- [模块定义](#模块定义)
		- [可执行文件定义](#可执行文件定义)
		- [测试定义](#测试定义)
		- [数据文件定义](#数据文件定义)
	- [hpack 构建配置](#hpack-构建配置)
	- [Paths_xxx 模块](#paths_xxx-模块)
- [问题注记](#问题注记)
	- [Revision Mismatch](#revision-mismatch)
	- [HDBC-mysql](#hdbc-mysql)

<!-- /TOC -->



# 概述
`Stack`是新一代的Haskell构建工具。

Stack集成了以下功能：

- 创建标准的Haksell项目模板。
- 获取最新的GHC编译器。
- 管理项目依赖。
- 构建项目。



# 安装与配置
Stack支持各大主流平台，根据平台在页面`https://www.stackage.org/stack/`选择下载二进制包。

- **Linux/Unix**系统：

	各类Unix可以使用对应发行版的包管理器安装`Stack`。

	```
	# apt install stack //Debian
	# pacman -S stack //Arch Linux
	$ brew install haskell-stack //macOS
	```

- **Wdinwos**系统：

	1. 在`https://www.stackage.org/stack/windows-x86_64`下载`Stack`。
	1. 配置`STACK_ROOT`环境变量。
	1. 将`%STACK_ROOT%`加入`PATH`环境变量中。

## Stackage
`Stackage`是稳定的Haskell包，官方站点为`https://www.stackage.org`。
Stackage根据不同的GHC版本形成不同的`Stackage LTS`版本，
stack在构建工程时通过LTS版本确定编译器以及对应依赖包的版本关系。

LTS版本配置：

- **全局**LTS版本由`$stack-root/global-project/stack.yaml`文件指定。
- 项目中使用的LTS版本由项目根路径下的`stack.yaml`文件指定。

通过指定`resolver`配置项设定stack使用的LTS版本：

```yaml
# 支持以下形式的语法：
# resolver: lts-3.5
# resolver: nightly-2015-09-21
# resolver: ghc-7.10.2
# resolver: ghcjs-0.1.0_ghc-7.10.2
# resolver:
#  name: custom-snapshot
#  location: "./custom-snapshot.yaml"
resolver: lts-11.13
```

`resolver`配置项可以是LTS版本号、nightly版本日期或GHC编译器版本号。<br>
全局的resolver配置决定了在项目目录外使用`stack ghc`、`stack ghci`等指令时调用的GHC版本。

## Stack Path
使用`stack path`指令可查看stack相关路径信息：

```
$ stack path
```

Stack部分路径说明：

| 名称 | 含义 |
| :- | :- |
| stack-path | stack根路径 |
| programs | GHC、MSYS2等的安装路径 |
| snapshot-pkg-db | 已安装的Stackage包数据信息路径 |

Stack默认根路径：

- Windows： `~\AppData\Roaming\stack`
- Linux/macOS: `~/.stack`

可使用`STACK_ROOT`环境变量设置stack使用的根路径。

## 包管理
使用`stack install [Stackage包名]`可在全局安装某个Stackage包。
截止到`stack 1.7.1`，Stack仍未提供卸载指定Stackage包的功能，删除指定包需要手动清理所有相关路径。

Stack判断一个包是否安装是根据本地的`snapshot-pkg-db`中的信息决定的，
该路径下为每个已安装的Stackage包创建了conf文件记录安装信息，使用`stack path --snapshot-pkg-db`指令查看该路径信息。

## 安装 GHC
Stack可以简便地安装、配置`GHC`编译器。

使用`stack setup`指令，stack会自动下载配置最新稳定版本的GHC编译器。

```
$ stack setup
```

GHC编译器默认安装位置：

- Windows: `~\AppData\Local\Programs\stack\[平台类型]\ghc-[版本号]`
- Linux/macOS： `~/.stack/programs/[平台类型]/ghc-[版本号]`

Windows下，GHC编译器需要依赖`MSYS2`，使用`stack setup`安装GHC时会自动附带安装MSYS2环境。<br>
若已经配置了MSYS2环境，则执行指令时使用`--skip-msys`则可跳过安装MSYS2环境的步骤：

```
> stack setup --skip-msys
```

可通过修改`$stack-root\config.yaml`中的顶层配置`local-programs-path`来指定GHC、MSYS2的安装路径。<br>
可通过修改`$stack-root/global-project/stack.yaml`中的顶层配置`resolver`来指定全局的GHC版本。

## 配置 Mirrors
Stackage和Hackage默认的镜像源在国内均被**墙**，需要替换源后才能正常使用。
国内推荐使用`TUNA`源(清华大学镜像源)或`USTC`源(中科大镜像源)。

以中科大源为例，编辑`$stack-root\config.yaml`，在`config.yaml`文件中添加：

```yaml
# Hackage
package-indices:
  - name: USTC
    download-prefix: https://mirrors.ustc.edu.cn/hackage/package/
    http: https://mirrors.ustc.edu.cn/hackage/01-index.tar.gz

# Stackage
setup-info: "http://mirrors.ustc.edu.cn/stackage/stack-setup.yaml"
urls:
  latest-snapshot: http://mirrors.ustc.edu.cn/stackage/snapshots.json
  lts-build-plans: http://mirrors.ustc.edu.cn/stackage/lts-haskell/
  nightly-build-plans: http://mirrors.ustc.edu.cn/stackage/stackage-nightly/
```



# 启动与使用
直接执行`stack`指令会输出帮助信息。

`stack`常见指令如下：

- `build` 构建项目
- `ghci` 进入交互式`GHC`解释器
- `ghc` 调用`GHC`编译器
- `list-dependencies` 列出项目依赖
- `new` 新建模版项目
- `templates` 查看可用的模版
- `install` 主动安装包
- `exec` 执行程序
- `test` 执行测试
- `clean` 清理构建缓存

## 创建项目
使用`stack new`创建项目：

```
$ stack new [项目名称] [模版名称]
```

项目名称中**不能**带有**下划线**。可使用`stack templates`指令列出所有可用的模版。
**模版名称**可省略，省略模版参数时将使用默认模版`new-template`。

## 项目结构
Stack项目默认目录结构如下：

```sh
项目名称
├── README.md # 项目说明
├── LICENSE # 项目许可证
├── 项目名称.cabal # 项目构建定义
├── Setup.hs
├── stack.yaml
├── app # main 模块
│    ├── Xxx.hs
│    └── ...
├── src # 库模块源码
│    ├── Xxx.hs
│    └── ...
└── .stack-work # 项目构建产生的文件
     ├── dist
     │    └── ...
     └── install
          └── ...
```

新创建的项目没有`.stack-work`，项目构建时会自动生成该目录。



# 构建配置
Stack支持两类构建配置：

- `项目名称.cabal` cabal格式的构建配置
- `package.yaml` hpack项目定义的构建配置，使用标准yaml语法

两种配置功能相同，仅需提供一种即可。
cabal格式的构建配置来自于Cabal构建工具，出现较早，使用自创语法；
hpack格式的构建配置更加现代化，使用标准yaml语法。

## Cabal 构建配置
在Stack项目根目录下创建`项目名称.cabal`文件，定义项目的构建配置。

Cabal配置项可查看[官方文档](https://www.haskell.org/cabal)。
基本的配置结构：

```yaml
name:                项目名称
version:             版本号
homepage:            项目主页
license:             授权协议
license-file:        LICENSE
author:              Author name here
maintainer:          example@example.com
copyright:           2017 Author name here
category:            Web
build-type:          Simple
extra-source-files:  README.md
cabal-version:       >=1.10

executable ...
  ... -- 可执行文件相关定义

library
  ... -- 模块相关定义

test-suite ...
  .. -- 测试相关定义

source-repository head
  type:     git
  location: 仓库地址
```

常用配置项如下：

- `hs-source-dirs` 定义`Haskell`的源码路径
- `build-depends` 定义依赖模块，可使用比较运算符控制依赖模块的版本
- `default-language` 设定使用的语言标准
- `ghc-options` 设置`GHC`的编译选项

### 模块定义
Haskell中`module`与`Java`中`package`概念类似，模块路径需要与磁盘中的物理路径对应。

`library`配置段定义了导出模块的信息。<br>
模块源码路径添加在`hs-source-dirs`配置项中，模块和模块路径需要使用大写字母开头。<br>
需要导出的模块写在`exposed-modules`配置项中，未写在改配置项中的模块不能被外部和主模块调用。

模块定义示例：

```yaml
library
  hs-source-dirs:      库源码路径
  exposed-modules:     导出模块
  build-depends:       base >= 4.7 && < 5
  default-language:    Haskell2010
```

### 可执行文件定义
`executable`配置段定义了构建生成的可执行程序。

`executable`后添加生成可执行文件的名称，默认的名称为`[项目名称]-exe`，名称可以自定义。
一个项目可以生成多个可执行文件(定义多个`executable`配置段)。
输出的可执行文件需要在`main-is`配置项中指明主模块所处的源码文件。

可执行文件定义示例：

```yaml
executable 可执行文件名称
  hs-source-dirs:      主模块源码路径
  main-is:             主模块对应源码文件
  ghc-options:         -threaded -rtsopts -with-rtsopts=-N
  build-depends:       base
                     , 依赖项 ...
  default-language:    Haskell2010
```

使用`stack build`指令后，会在`[项目根路径]/.stack-work/install/[CPU架构]-[操作系统]/lts-[LTS版本号]/[GHC版本号]/bin`路径下生成可执行文件。
使用`stack exec [执行文件名称]`执行生成的文件。

### 测试定义
`test-suite`配置段定义了测试相关内容。

`test-suite`后添加测试名称，默认名称为`[项目名称]-test`，名称可以自定义。
一个项目可定义多组测试(定义多个`test-suite`配置段)。
在`main-is`配置项中指定执行测试的源码文件，测试源码文件需要包含`main`方法。

测试定义示例：

```yaml
test-suite 测试名称
  type:                测试类型 -- 默认值为 exitcode-stdio-1.0
  hs-source-dirs:      测试源码路径
  main-is:             测试源码文件
  build-depends:       base
                     , 测试依赖 ...
  ghc-options:         -threaded -rtsopts -with-rtsopts=-N
  default-language:    Haskell2010
```

使用`stack test`指令执行测试：

```c
$ stack test //执行所有测试
$ stack test :[测试名称] //执行指定名称的测试
```

测试名称前需要添加**冒号**。
当测试目标为空时，会按定义顺序执行项目中的**所有**测试。

### 数据文件定义
在全局的`data-dir/data-files`配置段中添加关于运行时使用的数据、资源、配置文件相关定义。

- `data-dir`

	`data-dir`配置段定义数据文件所在的路径，仅能设定**单个**路径。
	使用`data-dir`配置段，则所有数据文件以`data-dir`配置中的路径为前缀。
	如下所示：

	```yaml
	data-dir: xxx
	-- 正确，从路径 "项目根目录/xxx" 路径下搜索配置文件

	data-dir: xxx1, xxx2
	-- 错误，不支持设置多个路径
	```

- `data-files`

	`data-files`配置段添加指定的数据文件。

	支持使用通配符匹配某一类型的文件，如`*.xml`、`*.json`，**不能**使用`*`通配符匹配所有文件。
	默认以**项目根路径**为起始路径，若数据文件位于子路径下，需要完整的相对路径，如`conf1/xxx1.xml`、`conf2/xxx2.json`。
	多个数据文件使用`,`符号作为分隔符。

	若设定了`data-dir`配置段，则以`项目根路径/data-dir配置路径`做为起始路径。

正确设定了数据文件相关配置，则使用`stack build`构建工程时，会在`[项目根路径]/.stack-work/install/[CPU架构]-[操作系统]/lts-[LTS版本]/[GHC版本]/share/[CPU架构]-[操作系统]/[项目名称]-[项目版本]`路径下生成对应的数据文件。

假设存在以下项目目录：

```
项目名称
├── ...
├── app
├── src
├── conf # 配置文件路径
│    ├── xxx.json
│    └── xxx.xml
└── .stack-work
```

对应Cabal配置如下：

```yaml
data-dir: conf
data-files: xxx.json, xxx.xml
```

构建后会在目标路径下直接生成数据文件。

亦可不使用`data-dir`配置段，直接使用完整相对路径，配置定义如下：

```yaml
data-files: conf/xxx.json, conf/xxx.xml
```

构建后会在目标路径下生成`conf`路径，并生成数据文件。

## hpack 构建配置
在Stack项目根目录下创建`package.yaml`文件，定义项目的构建配置。
stack工具构建项目时，会解析package.yaml文件，自动生成`项目名称.cabal`文件做为真正的构建配置。

hpack配置项可查看[GitHub主页](https://github.com/sol/hpack)。

## Paths_xxx 模块
stack构建项目时，会自动生成一个名称为`Paths_[项目名称]`的模块。
该模块提供了项目的**版本**与**路径**信息。

模块导出接口如下：

```hs
module Paths_xxx (
  version,
  getBinDir,
  getLibDir,
  getDynLibDir,
  getDataDir,
  getLibexecDir,
  getDataFileName,
  getSysconfDir
) where

version :: Version
getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getDataFileName :: FilePath -> IO FilePath
```

- `version` 包含项目版本版本号和版本名称
- `getBinDir` 项目可执行文件所在的路径
- `getDataDir` 获取数据文件所在的路径
- `getDataFileName` 使用相对路径获取指定数据文件的绝对路径

在项目中使用`Paths_[项目名称]`模块需要在`library`配置段中添加`other-modules`配置项：

```yaml
library
  hs-source-dirs:      src
  ...
  other-modules:       Paths_xxx
```

若未添加`other-modules`配置项，则构建项目时会产生未定义符号错误：

```
Undefined symbols for architecture x86_64:
...
```



# 问题注记
记录使用stack中遇到的问题。

## Revision Mismatch
当Stackage镜像源未完全同步官方源时，部分包可能MD5校验未通过，出现`Revision Mismatch`错误。
对于`Revision Mismatch`错误，默认行为是直接退出。

在`$stack-root/config.yaml`中添加配置：

```yaml
ignore-revision-mismatch: true
```

使用该配置则启动GHC时会忽略`Revision Mismatch`错误。

## HDBC-mysql
HDBC-mysql包需要依赖部分C库，如`libz`、`libssl`、`libmysqlclient`等。
直接使用stack安装时会得到错误信息：

```
setup: Missing dependencies on foreign libraries:
* Missing C libraries: z, ssl, mysqlclient
This problem can usually be solved by installing the system packages that
provide these libraries (you may need the "-dev" versions). If the libraries
are already installed but in a non-standard location then you can use the
flags --extra-include-dirs= and --extra-lib-dirs= to specify where they are.
```

在macOS平台下，使用Homebrew安装对应依赖：

```c
/*
	MariaDB 提供了 libmysqlclient 依赖，
	同时 MariaDB 依赖于 openssl，安装 MariaDB 时会自行安装该依赖
*/
$ brew install mariadb
```

通过Homebrew安装的openssl对应的库文件不在标准路径下，而是位于`/usr/local/opt/openssl/lib`路径下，
使用Stack安装HDBC-mysql需要额外指定该路径：

```
$ stack install HDBC-mysql --extra-lib-dirs=/usr/local/opt/openssl/lib
```
