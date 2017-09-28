<!-- TOC -->

- [*Stack* 简介](#stack-简介)
- [安装与配置](#安装与配置)
	- [配置 *Mirrors*](#配置-mirrors)
	- [配置 *GHC*](#配置-ghc)
- [启动与使用](#启动与使用)
	- [创建项目](#创建项目)
- [项目结构](#项目结构)
- [构建配置](#构建配置)
	- [模块定义](#模块定义)
	- [可执行文件定义](#可执行文件定义)

<!-- /TOC -->



## *Stack* 简介
`Stack`是新一代的`Haskell`构建工具。

`Stack`集成了以下功能：

- 创建标准的`Haksell`项目模板。
- 获取最新的`GHC`编译器。
- 管理项目依赖。
- 构建项目。



## 安装与配置
`Stack`支持各大主流平台，根据平台在页面`https://www.stackage.org/stack/`选择下载二进制包。

- **Linux/Unix**系统：

	各类`Unix`系统可以使用对应发行版的包管理器安装`Stack`。

	`Debian`系发行版

	```
	# apt install stack
	```

	`Arch`系发行版

	```
	# pacman -S stack
	```

	`macOS`

	```
	$ brew install haskell-stack
	```

- **Wdinwos**系统：

	1. 在`https://www.stackage.org/stack/windows-x86_64`下载`Stack`。
	1. 配置`STACK_ROOT`环境变量。
	1. 将`%STACK_ROOT%`加入`PATH`环境变量中。

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

在`Linux/macOS`系统下，`Stack`会将

### 配置 *GHC*
通过`Stack`可以简便地安装`GHC`编译器。  
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



## 项目结构
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

test-suite 测试模块名称
  type:                exitcode-stdio-1.0
  hs-source-dirs:      test
  main-is:             测试源码文件
  build-depends:       base
                     , 测试依赖 ...
  ghc-options:         -threaded -rtsopts -with-rtsopts=-N
  default-language:    Haskell2010

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

`executable`后添加生成可执行文件的名称，默认的名称为`[项目名称]-exe`，名称可以自行修改。  
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

使用`stack build`指令后，会在`.stack-work/install/...`路径下生成可执行文件。  
使用`stack exec [执行文件名称]`执行生成的文件。
