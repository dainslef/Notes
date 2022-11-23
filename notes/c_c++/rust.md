<!-- TOC -->

- [概述](#概述)
	- [開發環境](#開發環境)
	- [工具鏈](#工具鏈)
		- [Cargo](#cargo)
		- [rustup](#rustup)
		- [rustfmt](#rustfmt)
	- [REPL](#repl)
- [靜態構建](#靜態構建)
	- [musl-gcc](#musl-gcc)
- [單元測試](#單元測試)
	- [async函數單元測試](#async函數單元測試)
- [智能指針](#智能指針)
	- [Rc / Box / Arc](#rc--box--arc)
	- [Cell / RefCell](#cell--refcell)

<!-- /TOC -->



# 概述
[`Rust`](https://www.rust-lang.org/)是Molizza推出的系統編程語言，
專注於性能(performance)、可靠性(reliability)、生產力(productivity)。

## 開發環境
Rust官方推薦的開發環境是[`Visual Studio Code`](https://code.visualstudio.com/)
搭配[rust-analyzer](https://marketplace.visualstudio.com/items?itemName=rust-lang.rust-analyzer)插件。
官方VSCode插件[Rust](https://github.com/rust-lang/vscode-rust)已較長時間未更新，不再推薦使用。

VSCode的Rust插件雖為官方插件，
但其默認後端[`RLS(Rust Language Server)`](https://github.com/rust-lang/rls)目前開發並不活躍，
功能較為簡陋，性能較差，部分BUG一直未修復。
而下一代的[`rust-analyzer`](https://github.com/rust-analyzer/rust-analyzer)目前處於活躍開發中，
功能更加完備，對新特性支持較好，推薦使用。

## 工具鏈
Rust提供了一系列完備的工具鏈用於簡化開發流程。

### Cargo
`Cargo`類似Scala的Sbt、Haskell的Cabal等工具，負責Rust項目依賴管理和項目構建。
Rust中包被稱為`crate`，Cargo提供了中心倉庫`https://crates.io/`，包含了數以萬計的Rust包。

使用Cargo全局安裝指定包：

```
$ cargo install 包名
```

部分提供工具的包會在`~/.cargo/bin`下添加工具的可執行文件，若需要直接使用這些cargo安裝的工具，
則需要將該目錄加入**環境變量**中。

Cargo的常用指令：

```html
$ cargo init <!-- 在當前初始化新項目 -->
$ cargo init 項目根路徑 <!-- 在指定路徑初始化新項目 -->

$ cargo build <!-- 構建項目 -->
$ cargo run <!-- 執行項目的可執行文件 -->
$ cargo test <!-- 執行項目的測試 -->
```

完成初始化後，項目根路徑下會生成`Cargo.toml`文件，用戶描述項目配置：

```toml
[package]
name = "項目名稱"
version = "版本號"
edition = "2021"
authors = ["dainslef <dainslef@outlook.com>"]

# See more keys and their definitions at https://doc.rust-lang.org/cargo/reference/manifest.html

[dependencies]
依賴項 = "版本號"
依賴項 = { version = "版本號", features = ["開啟的特性"], ... }
...
```

版本號可以是具體的數值，亦可使用`*`表示使用最新版本。
首次使用構建項目時，Cargo會生成`Cargo.toml.lock`文件，
該文件中會記錄解析出的具體版本號。

與Sbt等構建工具不同，在Cargo中依賴項的關聯依賴在項目中**不可見**，
有且只有**顯式導入**的依賴才可訪問。

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



# 靜態構建
Rust在Linux平臺上的默認Target為`x86_64-unknown-linux-gnu`，
其對Linux環境的依賴已經較小，通常僅依賴libc、librt等必要庫，但並非像Golang那樣純靜態二進制。

Rust可以通過musl生成類似Golang的純靜態二進制文件，
添加對應Target，並使用該Target進行構建即可：

```
$ rustup target add x86_64-unknown-linux-musl
$ cargo build --target x86_64-unknown-linux-musl
```

使用`x86_64-unknown-linux-musl`構建生成的文件位於`$PROJECT/x86_64-unknown-linux-musl`路徑下。

## musl-gcc
部分使用CFFI的Rust庫需要用到C編譯器的對應musl版本（musl-gcc），
需要在系統中安裝musl工具鏈：

```html
# apt install musl-tools <!-- 大便系 -->
$ nix-env -i musl <!-- Nix -->
```

在NixOS中，musl軟件包默認未導出編譯器執行文件`musl-gcc`到環境變量中，
需要手動查找musl軟件包路徑，並添加到PATH環境變量中。
示例：

```html
<!-- 查找musl對應dev包在nix-store下的路徑 -->
$ find /nix/store -name '*-musl-*-dev'
/nix/store/0w1v9bcz7vs9462a8q240czgi7hnn8qn-musl-1.2.3-dev
<!-- 找到路徑後將該路徑添加到 $PATH 中 -->
$ export PATH=$PATH:/nix/store/0w1v9bcz7vs9462a8q240czgi7hnn8qn-musl-1.2.3-dev/bin
<!-- 之後即可使用 musl-gcc -->
$ musl-gcc
gcc (GCC) 11.3.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```



# 單元測試
Rust內置了對單元測試的支持。

使用`#[test]`特性標註一個函數，則該函數即為單元測試：

```rs
#[test]
fn xxx_test() {
  // Test code...
}
```

使用Cargo執行單元測試：

```html
$ cargo test -- 單元測試函數完整路徑
<!-- 默認執行測試會忽略函數內的標準輸出，添加 --nocapture 參數展示標註輸出 -->
$ cargo test -- --nocapture 單元測試函數完整路徑
```

## async函數單元測試
使用異步運行時的函數不可直接使用`#[test]`特性標註，
而是應使用對應運行時提供的特性，以tokio為例，應使用`#[tokio::test]`特性：

```rs
#[tokio::test]
async fn xxx_test() {
  // Aysnc code...
}
```



# 智能指針
作為無GC的現代編程語言，Rust提供了智能指針進行內存管理。

## Rc / Box / Arc
Rc/Box/Arc是Rust的智能指針類型，
對應C++中的`std::shared_ptr`(Rc)和`std::unique_ptr`(Box)。
Rc/Arc共享所有權，支持複製指針；Box獨佔所有權，不可複製，僅支持移動對象。

Box默認即實現了線程安全相關的trait（Send + Sync），
而Rc沒有，Rc存在單獨的線程安全版本（Arc）。

使用智能指針會將對象創建在堆上，棧上僅保留固定大小的指針對象。
當對象在編譯期大小不確定，或對象生命週期需要超越當前棧的生命週期時，需要使用智能指針。

典型場景示例：

```rust
/**
一個對象需要共享給兩個線程使用，若使用棧變量，
則一個對象無法移動到兩個線程中（所有權衝突），
此時將對象存儲在Arc智能指針中，拷貝指針即可實現共享對象。
*/
fn example() {
  let data = std::sync::Arc::new("test".to_string());
  let cloned_data = data.clone();
  std::thread::spawn(move || println!("{data}"));
  std::thread::spawn(move || println!("{cloned_data}"));
}
```

## Cell / RefCell
`std::cell`mod下提供了對於可變內存區域的抽象。
Cell/RefCell通常作為智能指針類型(Rc/Box)的泛型參數使用(如`Rc<RefCell<T>>`)，
由於rust中智能指針默認持有對象不可變，因此需要在持有的對象自身添加一層抽象，
用於提供對象的可變操作(替換指針指向的內容)。

Cell類型提供了對內部持有對象進行整體安全替換(`Cell::replace()`)、
交換兩個Cell對象的內容(`Cell::swap()`)的能力。

RefCell類型提供了對內部持有對象進行安全地只讀引用(`RefCell::borrow()`)、
讀寫引用(`RefCell::borrow_mut()`)的能力。
borrow()系列方法會在運行期間進行動態檢查，違反讀寫鎖規則時拋出異常，保證讀寫安全。

Cell/RefCell均可通過`as_ptr()`方法獲取raw pointer，
以使用unsafe在某些特殊情形下(如鏈表、二叉樹)繞過rust的所有權檢查。

Cell/RefCell類型不是線程安全的，因此未實現Sync特質；
若需要保證線程安全，需要搭配Mutex、RwLock等鎖類型。
