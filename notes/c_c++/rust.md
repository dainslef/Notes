<!-- TOC -->

- [概述](#概述)
	- [開發環境](#開發環境)
	- [工具鏈](#工具鏈)
		- [cargo](#cargo)
		- [rustup](#rustup)
		- [rustfmt](#rustfmt)
	- [REPL](#repl)
- [智能指針](#智能指針)
	- [Rc / Box](#rc--box)
	- [Cell / RefCell](#cell--refcell)

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

部分提供工具的包會在`~/.cargo/bin`下添加工具的可執行文件，若需要直接使用這些cargo安裝的工具，
則需要將該目錄加入**環境變量**中。

### rustup
[`rustup`](https://rustup.rs/)是Rust官方推出的編譯套件管理工具，
可以方便地進行Rust編譯器套件的更新、升級、版本切換、多版本管理等功能。

主流的Unix軟件倉庫中均已包含rustup，可直接安裝：

```html
# pacman -S rustup <!-- Arch系 -->
$ brew install rustup <!-- macOS Homebrew -->
```

常用的rustup操作：

```html
<!-- 工具鏈管理相關 -->
$ rustup toolchain install/unistall <channel> <!-- 安裝/移除指定工具鏈，channel 可以是 stable|beta|nightly|<version> -->
$ rustup toolchain list <!-- 列出安裝的工具鏈，以macOS下安裝默認最新穩定版工具鏈為例，應為 stable-x86_64-apple-darwin (default) -->

<!-- 工具鏈組件管理相關，包括cargo、rls、標準庫源碼、調試器等 -->
$ rustup component add/remove <component> <!-- 添加/移除當前套件的某個組件 -->
```

### rustfmt
[`rustfmt`](https://rust-lang.github.io/rustfmt/)是Rust官方推出的代碼格式化工具，
默認會按照社區規範對代碼進行格式化，統一代碼風格。
該工具支持多種格式化風格配置，支持的配置項可在項目官網查詢。

格式化代碼時，可將自定義的格式化配置直接添加到命令行中，使用`--config`參數：

```html
<!-- 格式化源碼，以兩格空格作為對齊縮進方式 -->
$ rustfmt --config tab_spaces=2 xxx.rs
```

VSCode搭配rust-analyzer插件使用時，rust-analyzer格式化代碼時會調用rustfmt，
rustfmt默認會按照社區風格格式化代碼，VSCode自身配置的Rust代碼縮進方式不會生效，
要使rustfmt按照期望的方式格式化代碼，需要在VSCode中指定rust-analyzer的rustfmt配置項：

```json
"rust-analyzer.rustfmt.extraArgs": [
	"--config",
	"tab_spaces=2"
],
```

## REPL
Rust目前沒有官方的REPL實現，目前流行的REPL實現是Google提供的[`evcxr`](https://github.com/google/evcxr)。

evcxr可以直接通過cargo進行安裝：

```c
$ cargo install evcxr_repl
```

安裝完成後，若已正確配置環境變量，則可直接通過命令行進入Rust REPL：

```
$ evcxr
Welcome to evcxr. For help, type :help
>> println!("Hello World!");
Hello World!
>>
```

evcxr項目還提供了對Jupyter Notebook的支持：

```html
$ cargo install evcxr_jupyter <!-- 安裝 evcxr_jupyter 工具 -->
$ evcxr_jupyter --install <!-- 使用 evcxr_jupyter 安裝 Jupyter Kernel -->
Writing /Users/dainslef/Library/Jupyter/kernels/rust/kernel.json
Writing /Users/dainslef/Library/Jupyter/kernels/rust/logo-32x32.png
Writing /Users/dainslef/Library/Jupyter/kernels/rust/logo-64x64.png
Writing /Users/dainslef/Library/Jupyter/kernels/rust/logo-LICENSE.md
Installation complete
$ jupyter kernelspec list <!-- 查看 Jupyter Kernel，新增了 rust kernel -->
Available kernels:
  .net-csharp        /Users/dainslef/Library/Jupyter/kernels/.net-csharp
  .net-fsharp        /Users/dainslef/Library/Jupyter/kernels/.net-fsharp
  .net-powershell    /Users/dainslef/Library/Jupyter/kernels/.net-powershell
  rust               /Users/dainslef/Library/Jupyter/kernels/rust
  python3            /usr/local/share/jupyter/kernels/python3
```



# 智能指針
作為無GC的現代編程語言，Rust提供了智能指針進行內存管理。

## Rc / Box
Rc/Box是Rust中最常用的智能指針類型(不提供線程安全保證)，
對應C++中的`std::shared_ptr`(RC)和`std::unique_ptr`(Box)。

## Cell / RefCell
`std::cell`mod下提供了對於可變內存區域的抽象。
Cell/RefCell通常作為智能指針類型(Rc/Box)的泛型參數使用(如`Rc<RefCell<T>>`)，
由於rust中智能指針默認持有對象不可變，因此需要在持有的對象自身添加一層抽象，
用於提供對象的可變操作(替換指針指向的內容)。

Cell類型提供了對內部持有對象進行整體安全替換(`Cell::replace()`)、
交換兩個Cell對象的內容(`Cell::swap()`)的能力。

RefCell類型提供了對內部持有對象進行安全地只讀引用(`RefCell::borrow()`)、
讀寫引用(`RefCell::borrow_mut()`)的能力。
borrow()系列方法會在運行期間進行動態檢查，違反讀寫鎖規則時拋出異常，
保證讀寫安全。

Cell/RefCell均可通過`as_ptr()`方法獲取raw pointer，
以使用unsafe在某些特殊情形下(如鏈表、二叉樹)繞過rust的所有權檢查。

Cell/RefCell類型不是線程安全的，因此未實現Sync特質；
若需要保證線程安全，需要搭配Mutex、RwLock等鎖類型。
