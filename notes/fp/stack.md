<!-- TOC -->

- [*Stack* 简介](#stack-简介)
- [安装与配置 *Stack*](#安装与配置-stack)
	- [配置 *Mirrors*](#配置-mirrors)
	- [配置 *GHC*](#配置-ghc)

<!-- /TOC -->



## *Stack* 简介
`Stack`是新一代的`Haskell`构建工具。

`Stack`集成了以下功能：

- 创建标准的`Haksell`项目模板。
- 获取最新的`GHC`编译器。
- 管理项目依赖。
- 构建项目。



## 安装与配置 *Stack*
`Stack`支持各大主流平台。

- **Linux/Unix**系统：

	使用发行版自带的包管理器安装`Stack`。

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

### 配置 *GHC*
通过`Stack`可以简便地安装`GHC`编译器。  
使用`stack setup`指令，`Stack`会自动下载配置最新稳定版本的`GHC`编译器。

```
$ stack setup
```

在`Windows`系统下，`GHC`编译器需要依赖`MSYS2`。  
使用`stack setup`安装`GHC`时会自动附带安装`MSYS2`环境。  
若已经配置了`MSYS2`环境，则执行指令时使用`--skip-msys`则可跳过安装`MSYS2`环境的步骤。  
如下所示：

```
> stack setup --skip-msys
```
