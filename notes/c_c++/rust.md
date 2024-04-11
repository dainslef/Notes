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
	- [openssl](#openssl)
- [單元測試](#單元測試)
	- [async函數單元測試](#async函數單元測試)
	- [error: test failed, to rerun pass `-p xxx --bin xxx`](#error-test-failed-to-rerun-pass--p-xxx---bin-xxx)
- [Struct（結構體）](#struct結構體)
	- [結構體對齊](#結構體對齊)
	- [PhantomData](#phantomdata)
- [Trait（特質）](#trait特質)
	- [Trait基本語法](#trait基本語法)
	- [Trait衝突](#trait衝突)
	- [Coherence / Orphan Rule（Trait限制）](#coherence--orphan-ruletrait限制)
	- [Dynamically Dispatched / Staic Dispatched](#dynamically-dispatched--staic-dispatched)
	- [Associated Types](#associated-types)
	- [Generic Associated Types](#generic-associated-types)
- [Enum（枚舉）](#enum枚舉)
	- [strum庫（枚舉功能增強）](#strum庫枚舉功能增強)
- [訪問權限](#訪問權限)
	- [模塊權限](#模塊權限)
	- [結構體字段權限](#結構體字段權限)
	- [宏訪問權限](#宏訪問權限)
- [標準庫](#標準庫)
	- [std::collections](#stdcollections)
		- [HashMap/BTreeMap](#hashmapbtreemap)
- [智能指針](#智能指針)
	- [Rc / Box / Arc](#rc--box--arc)
	- [Cell / RefCell](#cell--refcell)
- [全局變量](#全局變量)
	- [const_item_mutation](#const_item_mutation)
	- [Lazy類型（單例）](#lazy類型單例)
- [格式化輸出](#格式化輸出)
	- [字符串插值](#字符串插值)
- [錯誤處理](#錯誤處理)
	- [Option](#option)
	- [Result](#result)
		- [Result::expect()](#resultexpect)
		- [std::error::Error](#stderrorerror)
	- [anyhow](#anyhow)
		- [anyhow基本使用](#anyhow基本使用)
		- [anyhow! bail!](#anyhow-bail)
		- [anyhow Content](#anyhow-content)
	- [thiserror](#thiserror)
	- [Panic](#panic)
		- [std::panic::catch_unwind](#stdpaniccatch_unwind)
		- [C-unwind ABI](#c-unwind-abi)

<!-- /TOC -->



# 概述
[`Rust`](https://www.rust-lang.org/)是Molizza推出的系統編程語言，
專注於性能（performance）、可靠性（reliability）、生產力（productivity）。

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
authors = ["用戶名 <郵箱>"]

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

Cargo支持針對不同編譯器target設置不同配置：

```toml
[target.平台目標.配置項]
...
```

以Linux平台下的MUSL為例，定製MUSL使用的依賴：

```toml
[target.x86_64-unknown-linux-musl.dependencies]
依賴項 = "版本號"
依賴項 = { version = "版本號", features = ["開啟的特性"], ... }
...
```

若出現相同的配置，target中的配置會覆蓋原配置。

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
Rust目前沒有官方的REPL實現，目前流行的REPL實現是Google提供的
[`evcxr`](https://github.com/google/evcxr)。

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

## openssl
[`openssl`](https://github.com/sfackler/rust-openssl)
Rust中的openssl是C語言openssl庫的binding，是多數Rust庫中常見的C依賴庫。

使用MUSL靜態鏈接openssl時，建議開啟`vendored`特性：

```toml
# Custom dependencies under different targets.
[target.x86_64-unknown-linux-musl.dependencies]
# Use openssl "vendored" feature for MUSL.
openssl = { version = "*", features = ["vendored"] }
```

使用該特性openssl會獨立構建，否則需要依賴系統環境的openssl庫，
使用系統環境的openssl在與MUSL靜態鏈接時可能會產生各種符號衝突，
以Debian發行版為例，系統的openssl使用GCC編譯，使用MUSL鏈接時會出現部分函數找不到符號表。



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

## error: test failed, to rerun pass `-p xxx --bin xxx`
當測試中包含`std::process::exit()`調用時會產生該異常：

```rs
#[test]
fn exit_test() {
  std::process::exit(-1);
}
```

輸出結果：

```
running 1 test
error: test failed, to rerun pass `-p xxx --bin xxx`

Caused by:
  process didn't exit successfully: `xxx exit_test --exact --nocapture` (exit status: 255)

 *  The terminal process "cargo 'test', '--package', 'xxx', '--bin', 'xxx', '--', 'exit_test', '--exact', '--nocapture'" terminated with exit code: 255.
 *  Terminal will be reused by tasks, press any key to close it.
```



# Struct（結構體）
`Struct（結構體）`是Rust中定義數據結構的方式，於C/C++語言中的同名概念類似。

Rust中結構體存在以下與C語言類似，與C++不同的特徵：

- Rust中的結構體不支持繼承

Rust中結構體存在以下與C++類似，與C不同的特徵：

- 結構體支持定義成員方法
- 結構體支持泛型參數（類似於C++中的模板）
- 結構體和成員字段支持設置訪問權限

## 結構體對齊
類似C/C++中的`#pragma pack(n)`語法，自`Rust 1.25`開始，實現了
[`RFC1358`](https://github.com/rust-lang/rfcs/blob/master/text/1358-repr-align.md)，
提供了`#[repr(align(n))]`語法用於結構體對齊。

示例：

```rs
struct Number(i32);

assert_eq!(std::mem::align_of::<Number>(), 4);
assert_eq!(std::mem::size_of::<Number>(), 4);

#[repr(align(16))]
struct Align16(i32);

assert_eq!(std::mem::align_of::<Align16>(), 16);
assert_eq!(std::mem::size_of::<Align16>(), 16);
```

## PhantomData
Rust中的結構體不支持定義未使用的泛型參數，否則會報錯：

```rs
>> struct Test<T>();
               ^ unused parameter
parameter `T` is never used
help: consider removing `T`, referring to it in a field, or using a marker such as `PhantomData`
help: if you intended `T` to be a const parameter, use `const T: usize` instead
```

根據錯誤信息提示，可使用`std::marker::PhantomData`類型提供一個佔位符：

```rs
>> use std::marker::PhantomData;
>> struct Test<T>(PhantomData<T>);
>> use std::mem::size_of;
>> size_of::<Test<String>>()
0
```

`size_of()`輸出結果為0，可知PhantomData類型僅為佔位符，並不佔用實際空間。



# Trait（特質）
`Trait（特質）`概念類似於Haskell中的Type Class，對標OOP語言中的Interface。
由於Rust不支持繼承、重載，因此Trait系統是Rust語言中實現多態的主要方式。

## Trait基本語法
使用`trait`關鍵字定義Trait，使用`impl`關鍵字為既有類型實現Trait：

```rs
trait XxxTrait {
  // this指針的表示方式與impl相同
  fn trait_method_xxx(self);
}

impl XxxTrait for XxxStruct {
  fn trait_method_xxx(self) {
    ...
  }
}

// 使用trait
...
let xxx_struct: XxxStruct = ...;
xxx_struct.trait_method_xxx();
...
```

Trait亦支持繼承：

```rs
trait XxxBaseTrait {
  fn base_trait_method_xxx(self);
}

// XxxTrait在impl時需要同時實現XxxTrait和XxxBaseTrait定義的抽象方法
trait XxxTrait: XxxBaseTrait {
  fn trait_method_xxx(self);
}

trait XxxOtherTrait {
  fn other_trait_method_xxx(self);
}

// Trait可以多重繼承
trait XxxMultiExtendTrait: XxxTrait + XxxOtherTrait {
  fn multi_trait_method_xxx(self);
}
```

## Trait衝突
在Rust中，並未限制為一個類型實現多個方法簽名可能衝突的Trait，
當一個Trait試圖訪問衝突的方法時，會產生編譯錯誤：

```rs
trait A {
  fn test(&self) -> String;
}

trait B {
  fn test(&self) -> String;
}

struct Test<'a>(&'a str);

impl A for Test<'_> {
  fn test(&self) -> String {
    self.0.to_string() + " (A)"
  }
}

impl B for Test<'_> {
  fn test(&self) -> String {
    self.0.to_string() + " (B)"
  }
}

#[test]
fn test_trait() {
  let t = Test("test");
  println!("Print: {}", t.test());
}
```

錯誤信息：

```
error[E0034]: multiple applicable items in scope
...
note: candidate #1 is defined in an impl of the trait `A` for the type `Test<'_>`
...
note: candidate #2 is defined in an impl of the trait `B` for the type `Test<'_>`
...
For more information about this error, try `rustc --explain E0034`.
```

對於接收self指針的方法，可通過對象類型推斷需要使用的Trait重載，
因此直接使用`trait類型::衝突方法(對象)`調用可消除歧義；
對於沒有self指針的普通方法，則需要通過`<類型 as Trait類型>::衝突方法()`的語法消除歧異。

## Coherence / Orphan Rule（Trait限制）
雖然Rust中的Trait概念上來自Haskell的Type Class，
但並不能如Haskell中的Type Class一般為任意類型實現任意Trait，
需要Trait或類型二者之一為用戶定義，該限制被稱為`coherence`（一致性）或`orphan rule`（孤兒規則）；
詳情參考[Rust Book](https://doc.rust-lang.org/book/ch10-02-traits.html#implementing-a-trait-on-a-type)。

例如，不能為`Vec<T>`實現`ToString`特質，因為這兩者都定義在標準庫而非用戶代碼中，示例：

```rs
impl<T> ToString for Vec<T> {
  fn to_string(&self) -> String {
    "xxx".into()
  }
}
```

錯誤信息：

```
only traits defined in the current crate can be implemented for types defined outside of the crate
define and implement a trait or new type insteadrustcClick for full compiler diagnostic
...: `Vec` is not defined in the current crate
```

為外部類型實現外部Trait需要外部Trait帶有泛型參數，且泛型參數使用本地類型。

示例，為自定義類型實現標準庫中的trait`Into`：

```rs
struct UserTrait(usize);

impl Into<UserTrait> for usize {
  fn into(self) -> UserTrait {
    UserTrait(self)
  }
}
```

## Dynamically Dispatched / Staic Dispatched
Trait同時支持staic dispatched（靜態派發）和dynamically dispatched（動態派發）。

靜態派發在編譯時確定類型，調用靜態派發trait方法等價於調用普通函數；
動態派發則使用trait object，運行時確定類型，動態派發trait方法近似於C++的虛函數，
調用需要查找虛表得到函數指針，相對開銷較大。

早期Rust使用泛型約束表示靜態派發，直接使用Trait類型表示動態派發：

```rs
// 動態派發
fn f_dynamic(t: &Trait) { ... }

// 靜態派發
fn f_static<T: Trait>(t: &T) { ... }
```

[Rust 1.26](https://blog.rust-lang.org/2018/05/10/Rust-1.26.html)
開始支持`impl Trait`特性，靜態派發使用impl Trait，動態派發使用dyn Trait
（舊的直接使用Trait類型表示動態派發的語法作廢），使語法更加統一、直觀。

Rust 1.26之後的新語法：

```rs
// 動態派發
fn f_dynamic(t: &dyn Trait) { ... }

// 靜態派發
fn f_static(t: &impl Trait) { ... }
```

## Associated Types
[Associated Types](https://doc.rust-lang.org/book/ch19-03-advanced-traits.html#specifying-placeholder-types-in-trait-definitions-with-associated-types)
提供了類型佔位符特性，語法：

```rs
trait XxxTrait {
  type XxxAssociatedType;

  // Associated Types 可添加泛型約束
  type XxxAssociatedType1: XxxTrait;
  type XxxAssociatedType1: XxxTrait1 + XxxTrait2;
  ...
}

// 在為某類型實現帶有 Associated Types 的特質時，需要指明 Associated Types 的實際類型
impl XxxTrait for Xxx {
  type XxxAssociatedType = ...;
  ...
}
```

例如，Rust標準庫中的否定操作符特質定義中便使用了Associated Types特性：

```rs
pub trait Not {
  type Output;
  fn not(self) -> Self::Output;
}

// 以內置bool類型為例，實現如下
impl const Not for bool {
  type Output = bool;
  #[inline]
  fn not(self) -> bool { !self }
}
```

與在Trait中添加泛型參數相比，Trait與每個不同的泛型參數均可構成互不衝突的impl實現，
但使用Associated Types則意味著一個類型僅能impl時僅能擁有一種實現（Trait類型只有一個）。

示例：

```rs
trait TraitWithGeneric<T> {
  ...
}

// 可提供任意多的泛型參數作為impl實現
impl TraitWithGeneric<Xxx1> for Xxx {
  ...
}
impl TraitWithGeneric<Xxx2> for Xxx {
  ...
}

...

trait TraitWithAssociatedType {
  type AssociatedType;
  ...
}

// 無泛型參數，一個目標類型僅能實現一個impl
impl TraitWithAssociatedType for Xxx {
  type AssociatedType = ...; // AssociatedType僅能提供一種類型
  ...
}
```

## Generic Associated Types
自[`Rust 1.65`](https://blog.rust-lang.org/2022/11/03/Rust-1.65.0.html)版本開始，
Rust的Trait支持Generic Associated Types，
參考[官方博客](https://blog.rust-lang.org/2022/10/28/gats-stabilization.html)。

Rust當前並不支持`Higher Kinded Types`（高階類型），例如無法定義一個接收泛型參數的泛型類型：

```rs
// 該代碼不合法，無法通過編譯
trait CsutomListAdd<C<V>> {
  fn add(self, _: V) -> C<V>;
}
```

在Rust引入Generic Associated Types後能夠一定程度實現部分需要HKT才能實現的特性，
使用GAT定義出更具體的類型約束，限定結果為包含一個泛型參數的泛型類型：

```rs
// 合法代碼
trait CsutomListAdd {
  type V;
  type C<V>;
  fn add(self, _: Self::V) -> Self::C<Self::V>;
}
```



# Enum（枚舉）
Rust中的枚舉類型實際是Algebraic Data Types（ADT，代數數據類型），
除了具備C/C++中提供枚舉值的基本功能，還可以添加類型構造器並用於模式匹配。

使用參考[Rust Reference](https://doc.rust-lang.org/reference/items/enumerations.html)。

枚舉最基本的使用與C/C++中類似，僅包含`unit variants`，稱為`unit-only enum`，
枚舉對象會從零開始自動複製，或者使用等號手動複製，示例：

```rs
>> enum Enum {
  Zero,
  One,
  Two,
  Three,
  Five = 5,
}

>> Enum::Zero as i32 // 枚舉可直接轉換為基本數值類型
0
>> Enum::Five as usize
5
```

枚舉添加構造器可攜帶或不攜帶參數名稱，示例：

```rs
>> enum Animal {
  Pig,
  Dog(String, f64),
  Cat { name: String, weight: f64 },
}

>> let mut a = Animal::Dog("Cocoa".to_string(), 37.2);
>> a = Animal::Cat { name: "Spotty".to_string(), weight: 2.7 };

>> Animal::Cat as i32
[E0533] Error: expected value, found struct variant `Animal::Cat`
   ╭─[command:1:1]
   │
 1 │ Animal::Cat as i32
   │ ─────┬─────
   │      ╰─────── not a value
───╯
```

上述例子中，Animal::Dog稱為`enum variant`（枚舉變體），
而Animal::Cat稱為`struct-like enum variant`（類結構體枚舉變體）。

包含枚舉變體的枚舉類型不再能夠直接轉換為基本數值類型，強制轉換代碼無法通過編譯。
雖然無法直接將枚舉變體轉換為基本數值類型，但可通過unsafe的指針操作強制進行轉換：

```rs
>> impl Animal {
  fn value(&self) -> u8 {
      unsafe { *(self as *const Self as *const u8) }
  }
}

>> Animal::Dog("FuckCCP!".into(), 89.64).value()
1
```

枚舉轉換為數值被稱作[`discriminant`](https://doc.rust-lang.org/std/mem/fn.discriminant.html)。

可將數值轉換操作編寫為trait，供其它枚舉類型使用：

```rs
/// Enum variant can't transform to a primitive value directly.
/// Transform to a primitive value via unsafe pointer casting.
pub trait EnumValue {
  type Repr: Copy; // Target type need implement the Copy trait.

  /// Transform enum variant to a primitive value.
  fn value(&self) -> Self::Repr {
    // SAFETY: Because `Self` is marked `repr(Repr)`, its layout is a `repr(C)` `union`
    // between `repr(C)` structs, each of which has the `Repr` discriminant as its first
    // field, so we can read the discriminant without offsetting the pointer.
    unsafe { *(self as *const Self as *const Self::Repr) }
  }
}
```

## strum庫（枚舉功能增強）
使用[`strum`](https://github.com/Peternator7/strum)庫可用於增強系統枚舉功能，
在項目Cargo.toml中引入依賴：

```toml
[dependencies]
strum = { version = "*", features = ["derive"] } # 開啟 derive 特性
```

枚舉通過添加`#[derive(strum::Display)]`屬性為枚舉提供到文本的轉換：

```rs
#[derive(strum::Display)]
pub enum Language {
  Chinese,
  Taiwanese,
}

#[test]
fn enum_test() {
  println!("Language: {}", Language::Chinese);
  println!("Language: {}", Language::Taiwanese);
}
```

輸出結果：

```
Language: Chinese
Language: Taiwanese
```

使用strum庫提供的相關屬性可定製枚舉的文本轉換規則：

```rs
#[derive(strum::Display)]
#[strum(serialize_all = "snake_case")] // 可按照給定配置將枚舉名稱轉換為其它命名風格
pub enum Language {
  #[strum(to_string = "chinazi")] // 手動指定特定枚舉項的顯示文本
  Chinese,
  Japanese,
  Taiwanese,
  TaiwaneseAndJapanese,
}
```

此外，strum庫還提供了一系列derive：

- `derive(strum::EnumString)`（實現`std::str::FromStr`，用於從文本轉換為枚舉）
- `derive(strum::FromRepr)`（實現枚舉數值到枚舉類型的轉換）
- `derive(strum::EnumIter)`（實現枚舉項的迭代）



# 訪問權限
與主流語言類似，Rust支持設置模塊、函數、結構體、字段的訪問權限。
Rust中權限分為三類：

- `pub` 公有權限
- `pub(crate)` 模塊內部公有
- 私有（默認）

由於Rust不支持繼承，因此不存在傳統OOP語言中的`protect`（保護權限）。

## 模塊權限
模塊權限修飾用在`mod`關鍵字之前：

- 公有模塊的內容才能被其它外部模塊訪問。
- 私有模塊的內容對其子模塊可見。

## 結構體字段權限
早期Rust的實現中，結構體字段不具有獨立權限，
[rfcs/0001-private-fields](https://rust-lang.github.io/rfcs/0001-private-fields.html)
定義了結構體字段的權限機制（默認**私有**權限）。

## 宏訪問權限
早期版本的Rust中宏不可定義訪問權限，僅能使用專屬語法導入/導出。
從`Rust 1.33`開始，宏可在定義的模塊內使用`use`關鍵字導出，類似普通內容，
use前可使用權限字段修飾。

示例：

```rs
macro_rules! xxx {
  ...
}
// 宏導出需要在宏定義之後
use xxx; // 使用use關鍵字導出宏（默認內部訪問）
pub(crate) use xxx; // 可定義為模塊內部公有訪問


#[macro_export] // 對於使用pub修飾的宏導出，宏定義需要添加 #[macro_export]
macro_rules! xxxx {
  ...
}
pub use xxxx; // 使用pub導出外部
```



# 標準庫
Rust提供了功能強大的標準庫，從`Rust 1.6`開始，標準庫分爲兩部分：

- `libcore` 平臺無關的核心庫，無操作系統依賴（如libc等），命名空間爲`core::`。
- `libstd` 完整標準庫，命名空間爲`std::`，基於libcore，提供諸如**內存分配、IO、併發**等功能。

libstd包含libcore中的所有內容，對於二者重合的部分，libstd僅僅將命名空間由core導出到std。

## std::collections
`std::collections`包含Rust的各種集合類型。

### HashMap/BTreeMap
Rust中的Map類型未提供多值初始化的構造器或宏（類似Vec類型的`vec![]`宏），
但可通過元組數組進行構建：

```rs
>> let data: BTreeMap<usize, usize> = vec![(1, 1), (2, 2), (3, 3)].into_iter().collect();
>> data
{1: 1, 2: 2, 3: 3}
```

自`Rust 1.56`開始，Map類型支持`std_collections_from_array`特性，
提供了數組類型到Map類型的From特質，因此可以直接將數組轉換為對應Map類型：

```rs
>> let data: BTreeMap<usize, usize> = [(1, 1), (2, 2), (3, 3)].into();
>> data
{1: 1, 2: 2, 3: 3}
```



# 智能指針
作為無GC的現代編程語言，Rust提供了智能指針進行內存管理。

## Rc / Box / Arc
Rc/Box/Arc是Rust的智能指針類型，
對應C++中的`std::shared_ptr`（Rc）和`std::unique_ptr`（Box）。
Rc/Arc共享所有權，支持複製指針；Box獨佔所有權，不可複製，僅支持移動對象。

Box默認即實現了線程安全相關的trait（Send + Sync），
而Rc沒有，Rc存在單獨的線程安全版本（Arc）。

使用智能指針會將對象創建在堆上，棧上僅保留固定大小的指針對象。
當對象在編譯期大小不確定，或對象生命週期需要超越當前棧的生命週期時，需要使用智能指針。

典型場景示例：

```rs
/**
一個對象需要共享給兩個線程使用，若使用棧變量，
則一個對象無法移動到兩個線程中（所有權衝突），
此時將對象存儲在Arc智能指針中，拷貝指針即可實現共享對象。
*/
fn example() {
  let data = std::sync::Arc::new("test".to_string());
  let cloned_data = data.clone();
  std::thread::spawn(move || println!("Data: {data}"));
  std::thread::spawn(move || println!("Cloneed data: {cloned_data}"));
}
```

## Cell / RefCell
`std::cell`mod下提供了對於可變內存區域的抽象。
Cell/RefCell通常作為智能指針類型（Rc/Box）的泛型參數使用（如`Rc<RefCell<T>>`），
由於rust中智能指針默認持有對象不可變，因此需要在持有的對象自身添加一層抽象，
用於提供對象的可變操作（替換指針指向的內容）。

Cell類型提供了對內部持有對象進行整體安全替換（`Cell::replace()`）、
交換兩個Cell對象的內容（`Cell::swap()`）的能力。

RefCell類型提供了對內部持有對象進行安全地只讀引用（`RefCell::borrow()`）、
讀寫引用（`RefCell::borrow_mut()`）的能力。
borrow()系列方法會在運行期間進行動態檢查，違反讀寫鎖規則時拋出異常，保證讀寫安全。

Cell/RefCell均可通過`as_ptr()`方法獲取raw pointer，
以使用unsafe在某些特殊情形下（如鏈表、二叉樹）繞過rust的所有權檢查。

Cell/RefCell類型不是線程安全的，因此未實現Sync特質；
若需要保證線程安全，需要搭配Mutex、RwLock等鎖類型。



# 全局變量
Rust中使用`static`/`const`關鍵字定義全局變量，
static定義一個**地址恆定**的值，則const定義一個**常量**。

相同點：

- const/static定義的值均具有與程序相等的最長生命週期（`'static`）。
- 在整個程序中，const/static定義的字段僅存在一個實例。
- const/static字段只能接受常量或const函數進行初始化。
- const/static字段均使用大寫下劃線命名法。

不同點：

- const字段會被內聯優化，因此不具備恆定地址；static字段地址不會變化，也不會被內聯。
- const字段不可修改；static字段則可搭配mut關鍵字，支持在unsafe塊中修改字段的值。

示例：

```rs
const C_N: i32 = 5;
static S_N: i32 = 5;

// 定義可變值
static S_M: i32 = 5;
// 在unsafe中修改值
unsafe {
  S_M += 1;
}
```

## const_item_mutation
Rust中const字段不具備恆定地址，在定義一個內部可變的const字段時會得到
[`const-item-mutation`](https://doc.rust-lang.org/rustc/lints/listing/warn-by-default.html#const-item-mutation)
錯誤。

const字段在調用時會被**內聯**，調用時會創建臨時值，訪問的只是臨時值的地址，
因此修改不會印象原const值的內容，此類場景應使用static字段代替const字段。

示例：

```rs
const CONST_DATA: Vec<usize> = vec![];
static mut STATIC_DATA: Vec<usize> = vec![];

fn main() {
  println!("CONST_DATA: {CONST_DATA:?}");
  CONST_DATA.push(100);
  println!("CONST_DATA: {CONST_DATA:?}");

  unsafe {
    println!("STATIC_DATA: {STATIC_DATA:?}");
    STATIC_DATA.push(100);
    println!("STATIC_DATA: {STATIC_DATA:?}");
  }
}
```

編譯時警告信息：

```
warning: taking a mutable reference to a `const` item
    --> test.rs:6:3
     |
6    |   CONST_DATA.push(100);
     |   ^^^^^^^^^^^^^^^^^^^^
     |
     = note: `#[warn(const_item_mutation)]` on by default
     = note: each usage of a `const` item creates a new temporary
     = note: the mutable reference will refer to this temporary, not the original `const` item
note: mutable reference created due to call to this method
    --> /home/dainslef/.rustup/toolchains/stable-x86_64-unknown-linux-gnu/lib/rustlib/src/rust/library/alloc/src/vec/mod.rs:1727:5
     |
1727 |     pub fn push(&mut self, value: T) {
     |     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
note: `const` item defined here
    --> test.rs:1:1
     |
1    | const CONST_DATA: Vec<usize> = vec![];
     | ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

warning: 1 warning emitted
```

輸出結果：(rustc 1.61.0 (fe5b13d68 2022-05-18) && NixOS)

```
CONST_DATA: []
CONST_DATA: []
STATIC_DATA: []
STATIC_DATA: [100]
```

## Lazy類型（單例）
Rust標準庫中早期並未提供Lazy類型的直接支持，
早期多使用[`lazy_static`](https://crates.io/crates/lazy_static)庫；
之後逐漸被[`once_cell`](https://github.com/matklad/once_cell)庫取代，
once_cell相比lazy_static，不使用宏，而是直接使用Lambda進行初始化操作，更加簡潔明瞭。
之後once_cell被吸收進標準庫，但目前（`Rust 1.66`）仍處於Nightly狀態。

once_cell中的Lazy類型分為線程安全/非安全版本，且在標準庫中的類型名稱有所變化：

- `once_cell::sync::Lazy`，線程安全版本，在標準庫中為`std::sync::LazyLock`
- `once_cell::unsync::Lazy`，非線程安全版本，在標準庫中為`std::cell::LazyCell`

基本操作如下：

```rs
use once_cell::sync::Lazy;

static HASHMAP: Lazy<String> = Lazy::new(|| { "FuckCCP!".into() });
```

Lazy類型簽名為`Lazy<T, F = fn() -> T>`，構造器定義為：

```rs
impl<T, F> Lazy<T, F> {
  ...
  /// Creates a new lazy value with the given initializing
  /// function.
  pub const fn new(f: F) -> Lazy<T, F> {
      Lazy { cell: OnceCell::new(), init: Cell::new(Some(f)) }
  }
  ...
}
```

構造器僅能接收無参普通函數，並不能接收閉包；
Lazy的new()函數為const函數，但作為參數的構造器函數並無限制，函數返回值可以為普通類型。



# 格式化輸出
Rust中格式化輸出相關內容位於[`std::fmt`](https://doc.rust-lang.org/std/fmt/)。

常用格式化方式如下：

- `{}` 需要目標實現`std::fmt::Display`特質
- `{:?}` 需要目標實現`std::fmt::Debug`特質
- `{:#?}` 需要目標實現`std::fmt::Debug`特質，美化輸出（輸出內容換行、縮緊）

格式化可用於`format!`、`println!`等標準庫中的宏，以及日誌庫`log`，示例：

```rs
format!("Hello");                 // => "Hello"
format!("Hello, {}!", "world");   // => "Hello, world!"
format!("The number is {}", 1);   // => "The number is 1"
format!("{:?}", (3, 4));          // => "(3, 4)"
format!("{value}", value=4);      // => "4"
let people = "Rustaceans";
format!("Hello {people}!");       // => "Hello Rustaceans!"
format!("{} {}", 1, 2);           // => "1 2"
format!("{:04}", 42);             // => "0042" with leading zeros
format!("{:#?}", (100, 200));     // => "(
                                  //       100,
                                  //       200,
                                  //     )"
```

## 字符串插值
自[`Rust 1.58`](https://blog.rust-lang.org/2022/01/13/Rust-1.58.0.html)開始，
Rust部分支持字符串插值特性。

與傳統語言的字符串插值實現不同，Rust中的插值特性被稱為`Captured Identifiers`，
僅支持在格式化輸出相關的宏（`println!`、`format!`等）中使用，而非直接支持任意位置的字符串插值。

Rust的插值特性示例：

```rs
>> let t = "test";
>> println!("test: {t}");
>> test: test
// 不支持在插值語句中使用表達式，僅能直接捕獲字段
>> println!("test: {t.to_string()}");
                      expected `}` in format string
                   ^ because of this opening brace
invalid format string: expected `'}'`, found `'.'`

>> #[derive(Debug)] struct Test(String);
>> let t = Test("test".into());
// 僅能輸出實現了Display特質的變量，實現Debug特質的類型不可直接使用該語法輸出
>> println!("test: {t}");
                   ^^^ `Test` cannot be formatted with the default formatter
`Test` doesn't implement `std::fmt::Display`
help: the trait `std::fmt::Display` is not implemented for `Test`
// 實現Debug特質的類型需要在插值字段之後添加與酒語法類似的格式化字符
>> println!("test: {t:?}");
test: Test("test")
```

Rust的插值特性不支持表達式插值：

```rs
>> let n = 1;
>> println!("n: {n}");
>> n: 1
>> println!("n + 1: {n + 1}");
                        expected `}` in format string
                    ^ because of this opening brace
invalid format string: expected `'}'`, found `'+'`
```



# 錯誤處理
Rust中將程序運行中的異常、錯誤劃分為幾類，分別對應不同的處理方式：
（參考[The Rustonomicon](https://doc.rust-lang.org/nomicon/unwinding.html)）

- `Option` 用於某些值可能不存在的場景
- `Result` 用於原因明確可處理的錯誤
- `panic!` 用於無法處理的錯誤

對於Option/Result類型，Rust中提供了語法糖
[`?`操作符](https://doc.rust-lang.org/rust-by-example/std/result/question_mark.html)，
可簡化值檢查的相關表達。

`?`操作符目前僅支持標準庫中的Option/Result類型，
未來版本可通過實現[`std::ops::Try`](https://doc.rust-lang.org/std/ops/trait.Try.html)
添加自定義類型的實現（目前尚未Stable）。

## Option
Option表示可能不存在的值，Rust默認類型**不可**為空值，Safe模式下所有可空的類型都要顯式標註，
相比傳統語言隱式可空，Rust的處理方式更加安全。

Rust中的Option類型概念來自Scala、Haskell等函數式語言，用法類似。

## Result
Rust不使用傳統OOP語言的異常機制傳遞錯誤，
而是使用函數風格的`Result<T, E>`結構來直接描述可能產生錯誤的結果，
T代表正常返回值，E代表產生的錯誤。

### Result::expect()
Option和Result均提供了expect()方法，用於提取包裝的值，
當目標值不存在時，panic當前線程，並打印錯誤信息。

anyhow庫提供了更好的提取方式，不panic線程而是重新生成一致的anyhow錯誤，
參考[anyhow Content](#anyhow-content)。

### std::error::Error
Rust中提供了標準異常特質[std::error::Error](https://doc.rust-lang.org/std/error/trait.Error.html)，
規範了異常結構需要實現的方法。

默認Rust會關閉異常的調用棧信息，可設置環境變量`RUST_BACKTRACE`為`1`開啟異常調用棧。

## anyhow
Result機制的一大缺陷是不同第三方庫通常提供不同的錯誤類型，多數場景下需要手動轉換，較爲不便。
[`anyhow`](https://github.com/dtolnay/anyhow)可將任意Result類型轉化爲anyhow提供的anyhow::Result類型。

`anyhow::Result`的定義為：

```rs
pub type Result<T, E = Error> = core::result::Result<T, E>;
```

anyhow::Result是標準庫中Result的別名，但錯誤類型綁定為`anyhow::Error`結構體，
anyhow::Error結構體實現了`std::error::Error`特質。

### anyhow基本使用
將函數的返回值替換為`anyhow::Result<...>`，
則其它Error實現了`std::error::Error`的Result類型均可使用`?`操作符轉換：

```rs
use anyhow::Result;

fn get_cluster_info() -> Result<ClusterMap> {
  let config = std::fs::read_to_string("cluster.json")?;
  let map: ClusterMap = serde_json::from_str(&config)?;
  Ok(map)
}
```

anyhow內置了`std::backtrace`支持，可獲取錯誤信息堆棧，方便定位錯誤產生的原始位置。

### anyhow! bail!
anyhow提供了兩個常用宏，`anyhow!`用於生成`anyhow::Error`類型的錯誤信息，可放置在`anyhow::Result`中：

```rs
anyhow::Err(anyhow!("Find xxx error ..."))
```

`bail!`宏用於立即返回錯誤：

```rs
bail!("Find xxx error ...");

// 等價於
return Err(anyhow!("Find xxx error ..."));
```

### anyhow Content
anyhow為標準庫的`Option`和`Result`類型實現了
[Content](https://docs.rs/anyhow/latest/anyhow/trait.Context.html#)
特質，可用於Option/Result結果的內容提取，提取失敗時設置錯誤訊息：

```rs
#[test]
fn test_error() {
  use anyhow::{Context, Ok};

  fn error1() -> anyhow::Result<()> {
    let some: Option<usize> = None;
    let _ = some.context(format!("Error1: {some:?}"))?; // 設置錯誤訊息
    Ok(())
  }

  fn error2() -> anyhow::Result<()> {
    let some: Option<usize> = None;
    let _ = some.with_context(|| format!("Error2: {some:?}"))?;
    Ok(())
  }

  let (e1, e2) = (error1(), error2());
  println!("{e1:?}");
  println!("{e2:?}");
}
```

執行測試，並輸出結果：

```
$ cargo test -- --nocapture test_error
running 1 test
Err(Error1: None)
Err(Error2: None)
test common::test_error ... ok
```

## thiserror
[`thiserror`](https://github.com/dtolnay/thiserror)
用於為自定義結構實現標準異常特質，常與anyhow搭配使用。

thiserror提供了derive實現`thiserror::Error`，
為結構體添加`#[derive(thiserror::Error)]`即可使結構體實現`std::error::Error`，
使結構體可與anyhow組合使用。

## Panic
[Panic](https://doc.rust-lang.org/book/ch09-03-to-panic-or-not-to-panic.html)
在Rust中用於一些無法恢復的錯誤。

可在`Cargo.toml`中配置panic的行為（通過dev/release兩種profile分別設置不同場景下的行為）：

- unwind（默認行為），此時僅中斷觸發panic的線程，子線程的panic可被父線程處理，主線程panic則程序中止。
- abort，觸發panic直接中斷整個進程。

示例：

```toml
# Cargo.toml
[profile]
dev.panic = "abort"
release.panic = "unwind"
```

### std::panic::catch_unwind
[`std::panic::catch_unwind`](https://doc.rust-lang.org/std/panic/fn.catch_unwind.html)
用於設置指定線程panic後的處理邏輯。

### C-unwind ABI
[Rust 1.71](https://blog.rust-lang.org/2023/07/13/Rust-1.71.0.html)
中穩定了`C-unwind ABI`，可在觸發panic時向其它語言提供異常信息而非直接終止程序。

相關內容詳見[RFC2945](https://github.com/rust-lang/rfcs/blob/master/text/2945-c-unwind-abi.md)。
