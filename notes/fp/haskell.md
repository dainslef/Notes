<!-- TOC -->

- [*Haskell* 开发环境](#haskell-开发环境)
	- [*GHC* 常用功能](#ghc-常用功能)

<!-- /TOC -->



## *Haskell* 开发环境
`Haskell`的主流编译器是`GHC`，即`Glasgow Haskell Compiler`。

- **Linux/Unix**系统：

	使用发行版自带的包管理器安装`GHC`。

	`Debian`系发行版

	```
	# apt install ghc
	```

	`Arch`系发行版

	```
	# pacman -S ghc
	```

	`macOS`

	```
	$ brew install ghc
	```

- **Widnows**系统：

	在`https://www.haskell.org/platform/windows.html`下载`Haskell Platform`。  
	`Haskell Platform`包含了`GHC`编译器、`Cabal`构建工具等。

还可以使用`Stack`来配置`GHC`编译器。

### *GHC* 常用功能
`Haskell`源码后缀为`*.hs`，使用`ghc`指令编译`Haskell`代码：

```
$ ghc *.hs
```

`GHC`编译器会直接将`Haskell`源码编译为对应平台的二进制文件。

使用`ghci`会进入交互式`REPL`。  
`ghci`提供了交互式的`GHC`环境，可以直接输入代码并立即获得反馈。  
如下所示：

```hs
$ ghci
Configuring GHCi with the following packages:
GHCi, version 8.0.2: http://www.haskell.org/ghc/  :? for help
Prelude> print "Hello World"
"Hello World"
Prelude> :quit
Leaving GHCi.
```
