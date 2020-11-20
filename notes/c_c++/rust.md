<!-- TOC -->

- [概述](#概述)
	- [開發環境](#開發環境)
	- [工具鏈](#工具鏈)
		- [cargo](#cargo)
		- [rustup](#rustup)

<!-- /TOC -->



# 概述
[`Rust`](https://www.rust-lang.org/)是Molizza推出的系統編程語言，
專注於性能(performance)、可靠性(reliability)、生產力(productivity)。

## 開發環境
Rust官方推薦的開發環境是[`Visual Studio Code`](https://code.visualstudio.com/)搭配官方[Rust](https://github.com/rust-lang/vscode-rust)插件。

VSCode的Rust插件雖為官方插件，但其默認後端`RLS(Rust Language Server)`()目前開發並不活躍，
功能較為簡陋，性能較差，部分BUG一直未修復。
而下一代的[`rust-analyzer`](https://github.com/rust-analyzer/rust-analyzer)目前處於活躍開發中，
功能更加完備，對新特性支持較好，推薦使用。

## 工具鏈
Rust提供了一系列完備的工具鏈用於簡化開發流程。

### cargo
`cargo`類似Scala的Sbt、Haskell的Cabal等工具，負責Rust項目依賴管理和項目構建。
Rust中包被稱為`crate`，cargo提供了中心倉庫`https://crates.io/`，包含了數以萬計的Rust包。

使用cargo全局安裝指定包：

```c
$ cargo install [包名]
```

部分提供工具的包會在`~/.cargo/bin`下添加工具的可執行文件。

### rustup
[`rustup`](https://rustup.rs/)是Rust官方推出的編譯套件管理工具，
可以方便地進行Rust編譯器套件的更新、升級、版本切換、多版本管理等功能。

主流的Unix軟件倉庫中均已包含rustup，可直接安裝：

```c
# pacman -S rustup // Arch系
$ brew install rustup // macOS Homebrew
```

常用的rustup操作：

```c
// 工具鏈管理相關
$ rustup toolchain install/unistall <channel> // 安裝/移除指定工具鏈，channel 可以是 stable|beta|nightly|<version>
$ rustup toolchain list // 列出安裝的工具鏈，以macOS下安裝默認最新穩定版工具鏈為例，應為 stable-x86_64-apple-darwin (default)

// 工具鏈組件管理相關，包括cargo、rls、標準庫源碼、調試器等
$ rustup component add/remove <component> // 添加/移除當前套件的某個組件
```
