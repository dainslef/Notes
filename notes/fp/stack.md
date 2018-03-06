<!-- TOC -->

- [*Stack* 简介](#stack-简介)
- [安装与配置](#安装与配置)
	- [配置 *GHC*](#配置-ghc)
	- [*Stackage*](#stackage)
	- [配置 *Mirrors*](#配置-mirrors)
	- [关于 *Revision Mismatch* 错误](#关于-revision-mismatch-错误)
- [启动与使用](#启动与使用)
	- [创建项目](#创建项目)
	- [项目结构](#项目结构)
- [构建配置](#构建配置)
	- [模块定义](#模块定义)
	- [可执行文件定义](#可执行文件定义)
	- [测试定义](#测试定义)
	- [数据文件定义](#数据文件定义)
	- [*Paths_xxx* 模块](#paths_xxx-模块)

<!-- /TOC -->



## *Stack* 简介
`Stack`是新一代的`Haskell`构建工具。

`Stack`集成了以下功能：

- 创建标准的`Haksell`项目模板。
- 获取最新的`GHC`编译器。
- 管理项目依赖(由`Cabal`实现)。
- 构建项目(由`Cabal`实现)。



## 安装与配置
`Stack`支持各大主流平台，根据平台在页面`https://www.stackage.org/stack/`选择下载二进制包。

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

### 配置 *GHC*
通过Stack可以简便地安装`GHC`编译器。  
使用`stack setup`指令，`Stack`会自动下载配置最新稳定版本的`GHC`编译器。

```
$ stack setup
```

在`Linux/macOS`系统下，`GHC`编译器默认安装位置为：

```
~/.stack/programs/[平台类型]/ghc-[版本号]
```

在`Windows`系统下，`GHC`编译器默认安装位置为：

```
~\AppData\Local\Programs\stack\x86_64-windows\ghc-[版本号]
```

在`Windows`系统下，`GHC`编译器需要依赖`MSYS2`。  
使用`stack setup`安装`GHC`时会自动附带安装`MSYS2`环境。  
若已经配置了`MSYS2`环境，则执行指令时使用`--skip-msys`则可跳过安装`MSYS2`环境的步骤。  
如下所示：

```
> stack setup --skip-msys
```

### *Stackage*
`Stackage`是稳定的Haskell包，官方站点为`https://www.stackage.org`。

Stackage根据不同的GHC版本形成不同的`Stackage LTS`版本，
stack在构建工程时通过LTS版本确定编译器以及对应依赖包的版本关系。

全局LTS版本由`~/.stack/global-project/stack.yaml`文件指定。  
项目中使用的LTS版本由项目根路径下的`stack.yaml`文件指定。  
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
resolver: lts-10.7
```

全局的LTS版本决定了在工程目录外使用`stack ghc`、`stack ghci`等指令时调用的GHC版本。  

### 配置 *Mirrors*
`Stackage`和`Hackage`默认的镜像源在国内均被**墙**，需要替换源后才能正常使用。  
国内推荐使用`TUNA`源(清华大学镜像源)。

在`Linux/Unix/macOS`中，编辑`~/.stack/config.yaml`；  
在`Windows`中，编辑`%STACK_ROOT%\config.yaml`。  
在`config.yaml`文件中添加：

```yaml
# Stackage 镜像
setup-info: "http://mirrors.tuna.tsinghua.edu.cn/stackage/stack-setup.yaml"
urls:
  latest-snapshot: http://mirrors.tuna.tsinghua.edu.cn/stackage/snapshots.json
  lts-build-plans: http://mirrors.tuna.tsinghua.edu.cn/stackage/lts-haskell/
  nightly-build-plans: http://mirrors.tuna.tsinghua.edu.cn/stackage/stackage-nightly/

# Hackage 镜像
package-indices:
  - name: Tsinghua
    download-prefix: http://mirrors.tuna.tsinghua.edu.cn/hackage/package/
    http: http://mirrors.tuna.tsinghua.edu.cn/hackage/00-index.tar.gz
```

### 关于 *Revision Mismatch* 错误
当`Stackage`镜像源未完全同步官方源时，部分包可能`MD5`校验未通过，出现`Revision Mismatch`错误。  
对于`Revision Mismatch`错误，默认行为是直接退出。

在`~/.satck/config.yaml`中添加配置：

```yaml
ignore-revision-mismatch: true
```

使用该配置则启动GHC时会忽略`Revision Mismatch`错误。



## 启动与使用
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

### 创建项目
使用`stack new`创建项目：

```
$ stack new [项目名称] [模版名称]
```

项目名称中**不能**带有**下划线**。  
可使用`stack templates`指令列出所有可用的模版。  
**模版名称**可省略，省略模版参数时将使用默认模版`new-template`。

### 项目结构
`Stack`项目默认目录结构如下：

```
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



## 构建配置
`Stack`项目根目录下的`项目名称.cabal`文件定义了项目的构建配置。  
基本的配置结构如下所示：

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

library
  ... -- 模块相关定义

executable ...
  ... -- 可执行文件相关定义

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
`Haskell`中`module`与`Java`中`package`概念类似，模块路径需要与磁盘中的物理路径对应。  
`library`配置段定义了导出模块的信息。

模块源码路径添加在`hs-source-dirs`配置项中，模块和模块路径需要使用大写字母开头。  
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

使用`stack test :[测试名称]`执行指定测试。  
测试名称前需要添加**冒号**。

当测试目标为空时，会按定义顺序执行项目中的**所有**测试。

### 数据文件定义
在全局的`data-dir/data-files`配置段中添加关于运行时使用的数据、资源、配置文件相关定义。

- `data-dir`

	`data-dir`配置段定义数据文件所在的路径，仅能设定**单个**路径。  
	使用`data-dir`配置段，则所有数据文件以`data-dir`配置中的路径为前缀。  
	如下所示：

	```
	data-dir: xxx
	-- 正确，从路径 "项目根目录/xxx" 路径下搜索配置文件
	```

	```
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

若存在以下`Stack`项目目录：

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

对应`Cabal`配置如下：

```
data-dir: conf
data-files: xxx.json, xxx.xml
```

构建后会在目标路径下直接生成数据文件。

亦可不使用`data-dir`配置段，直接使用完整相对路径，配置定义如下：

```
data-files: conf/xxx.json, conf/xxx.xml
```

构建后会在目标路径下生成`conf`路径，并生成数据文件。

### *Paths_xxx* 模块
`Stack`构建项目时，会自动生成一个名称为`Paths_[项目名称]`的模块。  
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
  other-modules:       Paths_test_socket
```

若未添加`other-modules`配置项，则构建项目时会产生未定义符号错误：

```
Undefined symbols for architecture x86_64:
...
```
