<!-- TOC -->

- [概述](#概述)
- [安裝與配置](#安裝與配置)
	- [Stackage](#stackage)
	- [Stack Path](#stack-path)
	- [安裝 GHC](#安裝-ghc)
	- [配置 Mirrors](#配置-mirrors)
	- [包管理](#包管理)
	- [環境清理](#環境清理)
- [啓動與使用](#啓動與使用)
	- [創建項目](#創建項目)
	- [項目結構](#項目結構)
- [構建配置](#構建配置)
	- [Cabal 構建配置](#cabal-構建配置)
		- [模塊定義](#模塊定義)
		- [可執行文件定義](#可執行文件定義)
		- [測試定義](#測試定義)
		- [數據文件定義](#數據文件定義)
	- [hpack 構建配置](#hpack-構建配置)
	- [Paths_xxx 模塊](#paths_xxx-模塊)
- [問題註記](#問題註記)
	- [Revision Mismatch](#revision-mismatch)
	- [HDBC-mysql](#hdbc-mysql)

<!-- /TOC -->



# 概述
`Stack`是新一代的Haskell構建工具。

Stack集成了以下功能：

- 創建標準的Haksell項目模板。
- 獲取最新的GHC編譯器。
- 管理項目依賴。
- 構建項目。



# 安裝與配置
Stack支持各大主流平臺，根據平臺在頁面`https://www.stackage.org/stack/`選擇下載二進制包。

- **Linux/Unix**系統：

	各類Unix可以使用對應發行版的包管理器安裝`Stack`。

	```
	# apt install stack //Debian
	# pacman -S stack //Arch Linux
	$ brew install haskell-stack //macOS
	```

- **Wdinwos**系統：

	1. 在`https://www.stackage.org/stack/windows-x86_64`下載`Stack`。
	1. 配置`STACK_ROOT`環境變量。
	1. 將`%STACK_ROOT%`加入`PATH`環境變量中。

## Stackage
`Stackage`是穩定的Haskell包，官方站點爲`https://www.stackage.org`。
Stackage根據不同的GHC版本形成不同的`Stackage LTS`版本，
stack在構建工程時通過LTS版本確定編譯器以及對應依賴包的版本關係。

LTS版本配置：

- **全局**LTS版本由`$stack-root/global-project/stack.yaml`文件指定。
- 項目中使用的LTS版本由項目根路徑下的`stack.yaml`文件指定。

通過指定`resolver`配置項設定stack使用的LTS版本：

```yaml
# 支持以下形式的語法：
# resolver: lts-3.5
# resolver: nightly-2015-09-21
# resolver: ghc-7.10.2
# resolver: ghcjs-0.1.0_ghc-7.10.2
# resolver:
#  name: custom-snapshot
#  location: "./custom-snapshot.yaml"
resolver: lts-11.13
```

`resolver`配置項可以是LTS版本號、nightly版本日期或GHC編譯器版本號。<br>
全局的resolver配置決定了在項目目錄外使用`stack ghc`、`stack ghci`等指令時調用的GHC版本。

## Stack Path
使用`stack path`指令可查看stack相關路徑信息：

```
$ stack path
```

Stack部分路徑說明：

| 名稱 | 含義 |
| :- | :- |
| stack-path | stack根路徑 |
| programs | GHC、MSYS2等的安裝路徑 |
| snapshot-pkg-db | 已安裝的Stackage包數據信息路徑 |

Stack默認根路徑：

- Windows： `~\AppData\Roaming\stack`
- Linux/macOS: `~/.stack`

可使用`STACK_ROOT`環境變量設置stack使用的根路徑。

## 安裝 GHC
Stack可以簡便地安裝、配置`GHC`編譯器。

使用`stack setup`指令，stack會自動下載配置最新穩定版本的GHC編譯器。

```
$ stack setup
```

GHC編譯器默認安裝位置：

- Windows: `~\AppData\Local\Programs\stack\[平臺類型]\ghc-[版本號]`
- Linux/macOS： `~/.stack/programs/[平臺類型]/ghc-[版本號]`

Windows下，GHC編譯器需要依賴`MSYS2`，使用`stack setup`安裝GHC時會自動附帶安裝MSYS2環境。<br>
若已經配置了MSYS2環境，則執行指令時使用`--skip-msys`則可跳過安裝MSYS2環境的步驟：

```
> stack setup --skip-msys
```

可通過修改`$stack-root\config.yaml`中的頂層配置`local-programs-path`來指定GHC、MSYS2的安裝路徑：

```yaml
...
local-programs-path: 路徑...
...
```

可通過修改`$stack-root/global-project/stack.yaml`中的頂層配置`resolver`字段設置全局的LTS版本，
進而控制GHC編譯器的版本：

```yaml
...
resolver: lts-xx.xx
...
```

## 配置 Mirrors
Stackage和Hackage默認的鏡像源在國內均被**牆**，需要替換源後才能正常使用。
國內推薦使用`TUNA`源(清華大學鏡像源)或`USTC`源(中科大鏡像源)。

以中科大源爲例，編輯`$stack-root\config.yaml`，在文件中添加：

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

## 包管理
使用`stack install [Stackage包名]`可在全局安裝某個Stackage包。

對於包含Binary工具的Stackage包，在macOS/Linux中默認會被安裝到`~/.local/bin`路徑下，
在Windows中默認會被安裝到`~\AppData\Roaming\local\bin`路徑下。

通過修改配置`$stack-root\config.yaml`可改變Binary的安裝配置：

```yaml
...
local-bin-path: 路徑...
...
```

截止到`stack 1.7.1`，Stack仍未提供卸載指定Stackage包的功能，刪除指定包需要手動清理所有相關路徑。

Stack判斷一個包是否安裝是根據本地的`snapshot-pkg-db`中的信息決定的，
該路徑下爲每個已安裝的Stackage包創建了conf文件記錄安裝信息，使用`stack path --snapshot-pkg-db`指令查看該路徑信息。

## 環境清理
Stack在構建項目時，會首先查看項目構建配置中使用的LTS版本，若目標LTS版本對應的編譯器、依賴庫等未下載，會首先下載編譯器和依賴。
每個大版本的LTS通常都會對應不同的GHC版本，不同的GHC版本會擁有不同的依賴庫，當本地存在太多LTS版本時，STACK_ROOT目錄會變得十分臃腫。
Stack並未提供清理不再需要的LTS版本相關功能，當切換到新的LTS版本時，舊的LTS版本對應的編譯器、依賴庫等均需要手動刪除。

可使用`find`工具在STACK_ROOT下查找舊的LTS相關路徑，進行刪除：

```c
$ find ~/.stack -name '*GHC編譯器版本*' -exec rm -r \{\} \; //查找GHC編譯器相關路徑，進行刪除
$ find ~/.stack -name '*LTS版本號*' -exec rm -r \{\} \; //查找LTS相關路徑，進行刪除
```

具體的路徑相關信息，可使用前文介紹的`stack path`指令進行查看。



# 啓動與使用
直接執行`stack`指令會輸出幫助信息。

`stack`常見指令如下：

- `build` 構建項目
- `ghci` 進入交互式`GHC`解釋器
- `ghc` 調用`GHC`編譯器
- `list-dependencies` 列出項目依賴
- `new` 新建模版項目
- `templates` 查看可用的模版
- `install` 主動安裝包
- `exec` 執行程序
- `test` 執行測試
- `clean` 清理構建緩存

## 創建項目
使用`stack new`創建項目：

```
$ stack new [項目名稱] [模版名稱]
```

項目名稱中**不能**帶有**下劃線**。可使用`stack templates`指令列出所有可用的模版。
**模版名稱**可省略，省略模版參數時將使用默認模版`new-template`。

## 項目結構
Stack項目默認目錄結構如下：

```sh
項目名稱
├── README.md # 項目說明
├── LICENSE # 項目許可證
├── 項目名稱.cabal # 項目構建定義
├── Setup.hs
├── stack.yaml
├── app # main 模塊
│    ├── Xxx.hs
│    └── ...
├── src # 庫模塊源碼
│    ├── Xxx.hs
│    └── ...
└── .stack-work # 項目構建產生的文件
     ├── dist
     │    └── ...
     └── install
          └── ...
```

新創建的項目沒有`.stack-work`，項目構建時會自動生成該目錄。



# 構建配置
Stack支持兩類構建配置：

- `項目名稱.cabal` cabal格式的構建配置
- `package.yaml` hpack項目定義的構建配置，使用標準yaml語法

兩種配置功能相同，僅需提供一種即可。
cabal格式的構建配置來自於Cabal構建工具，出現較早，使用自創語法；
hpack格式的構建配置更加現代化，使用標準yaml語法。

## Cabal 構建配置
在Stack項目根目錄下創建`項目名稱.cabal`文件，定義項目的構建配置。

Cabal配置項可查看[官方文檔](https://www.haskell.org/cabal)。
基本的配置結構：

```yaml
name:                項目名稱
version:             版本號
homepage:            項目主頁
license:             授權協議
license-file:        LICENSE
author:              Author name here
maintainer:          example@example.com
copyright:           2017 Author name here
category:            Web
build-type:          Simple
extra-source-files:  README.md
cabal-version:       >=1.10

executable ...
  ... -- 可執行文件相關定義

library
  ... -- 模塊相關定義

test-suite ...
  .. -- 測試相關定義

source-repository head
  type:     git
  location: 倉庫地址
```

常用配置項如下：

- `hs-source-dirs` 定義`Haskell`的源碼路徑
- `build-depends` 定義依賴模塊，可使用比較運算符控制依賴模塊的版本
- `default-language` 設定使用的語言標準
- `ghc-options` 設置`GHC`的編譯選項

### 模塊定義
Haskell中`module`與`Java`中`package`概念類似，模塊路徑需要與磁盤中的物理路徑對應。

`library`配置段定義了導出模塊的信息。<br>
模塊源碼路徑添加在`hs-source-dirs`配置項中，模塊和模塊路徑需要使用大寫字母開頭。<br>
需要導出的模塊寫在`exposed-modules`配置項中，未寫在改配置項中的模塊不能被外部和主模塊調用。

模塊定義示例：

```yaml
library
  hs-source-dirs:      庫源碼路徑
  exposed-modules:     導出模塊
  build-depends:       base >= 4.7 && < 5
  default-language:    Haskell2010
```

### 可執行文件定義
`executable`配置段定義了構建生成的可執行程序。

`executable`後添加生成可執行文件的名稱，默認的名稱爲`[項目名稱]-exe`，名稱可以自定義。
一個項目可以生成多個可執行文件(定義多個`executable`配置段)。
輸出的可執行文件需要在`main-is`配置項中指明主模塊所處的源碼文件。

可執行文件定義示例：

```yaml
executable 可執行文件名稱
  hs-source-dirs:      主模塊源碼路徑
  main-is:             主模塊對應源碼文件
  ghc-options:         -threaded -rtsopts -with-rtsopts=-N
  build-depends:       base
                     , 依賴項 ...
  default-language:    Haskell2010
```

使用`stack build`指令後，會在`[項目根路徑]/.stack-work/install/[CPU架構]-[操作系統]/lts-[LTS版本號]/[GHC版本號]/bin`路徑下生成可執行文件。
使用`stack exec [執行文件名稱]`執行生成的文件。

### 測試定義
`test-suite`配置段定義了測試相關內容。

`test-suite`後添加測試名稱，默認名稱爲`[項目名稱]-test`，名稱可以自定義。
一個項目可定義多組測試(定義多個`test-suite`配置段)。
在`main-is`配置項中指定執行測試的源碼文件，測試源碼文件需要包含`main`方法。

測試定義示例：

```yaml
test-suite 測試名稱
  type:                測試類型 -- 默認值爲 exitcode-stdio-1.0
  hs-source-dirs:      測試源碼路徑
  main-is:             測試源碼文件
  build-depends:       base
                     , 測試依賴 ...
  ghc-options:         -threaded -rtsopts -with-rtsopts=-N
  default-language:    Haskell2010
```

使用`stack test`指令執行測試：

```c
$ stack test //執行所有測試
$ stack test :[測試名稱] //執行指定名稱的測試
```

測試名稱前需要添加**冒號**。
當測試目標爲空時，會按定義順序執行項目中的**所有**測試。

### 數據文件定義
在全局的`data-dir/data-files`配置段中添加關於運行時使用的數據、資源、配置文件相關定義。

- `data-dir`

	`data-dir`配置段定義數據文件所在的路徑，僅能設定**單個**路徑。
	使用`data-dir`配置段，則所有數據文件以`data-dir`配置中的路徑爲前綴。
	如下所示：

	```yaml
	data-dir: xxx
	-- 正確，從路徑 "項目根目錄/xxx" 路徑下搜索配置文件

	data-dir: xxx1, xxx2
	-- 錯誤，不支持設置多個路徑
	```

- `data-files`

	`data-files`配置段添加指定的數據文件。

	支持使用通配符匹配某一類型的文件，如`*.xml`、`*.json`，**不能**使用`*`通配符匹配所有文件。
	默認以**項目根路徑**爲起始路徑，若數據文件位於子路徑下，需要完整的相對路徑，如`conf1/xxx1.xml`、`conf2/xxx2.json`。
	多個數據文件使用`,`符號作爲分隔符。

	若設定了`data-dir`配置段，則以`項目根路徑/data-dir配置路徑`做爲起始路徑。

正確設定了數據文件相關配置，則使用`stack build`構建工程時，會在`[項目根路徑]/.stack-work/install/[CPU架構]-[操作系統]/lts-[LTS版本]/[GHC版本]/share/[CPU架構]-[操作系統]/[項目名稱]-[項目版本]`路徑下生成對應的數據文件。

假設存在以下項目目錄：

```
項目名稱
├── ...
├── app
├── src
├── conf # 配置文件路徑
│    ├── xxx.json
│    └── xxx.xml
└── .stack-work
```

對應Cabal配置如下：

```yaml
data-dir: conf
data-files: xxx.json, xxx.xml
```

構建後會在目標路徑下直接生成數據文件。

亦可不使用`data-dir`配置段，直接使用完整相對路徑，配置定義如下：

```yaml
data-files: conf/xxx.json, conf/xxx.xml
```

構建後會在目標路徑下生成`conf`路徑，並生成數據文件。

## hpack 構建配置
在Stack項目根目錄下創建`package.yaml`文件，定義項目的構建配置。
stack工具構建項目時，會解析package.yaml文件，自動生成`項目名稱.cabal`文件做爲真正的構建配置。

hpack配置項可查看[GitHub主頁](https://github.com/sol/hpack)。
基本配置結構：

```yaml
name: 項目名稱
version: 項目版本
license: BSD3
license-file: LICENSE
author: Dainslef
maintainer: dainslef@outlook.com
copyright: 2017 Author name here
category: Web
build-type: Simple
extra-source-files: README.md

executables:
  ... # 可執行文件定義

library:
  ... # 庫定義

tests:
  ... # 測試定義
```

hpack格式的定義多數配置項與原有cabal配置相同，但配置使用標準yaml語法，
因此`executables`、`tests`等配置段中每個子單元使用單獨的層次。
示例：

```yaml
executables:
  可執行文件1: # 定義可執行文件，類似cabal中的 "executable 可執行文件1"
    source-dirs: 主模塊源碼路徑
    main: 主模塊對應源碼文件
    dependencies:
      - base >= 版本號 && <= 版本號
      - ... # 其它依賴項
    ghc-options:
      - -threaded
      - -rtsopts
      - -with-rtsopts=-N
  可執行文件2:
    ... # 類似

tests:
  測試1: # 定義測試，類似cabal中的 ”test-suite 測試1“
    source-dirs: 測試源碼路徑
    main: 測試源碼文件
    dependencies: [base, ...]
    other-modules: []
    ghc-options: [-threaded, -rtsopts, -with-rtsopts=-N]
```

hpack配置中沒有`default-language`配置項，默認使用`Haskell2010`(`Haskell98`標準已過時)。

hpack的測試用例配置中，`other-modules`配置項默認包含所有測試源碼，
會導致使用`stack test :測試單元`指令執行指定測試時，非測試用例代碼也會參與編譯、構建，
需要顯式將`other-modules`配置項置爲`[]`，避免不必要的編譯。

## Paths_xxx 模塊
stack構建項目時，會自動生成一個名稱爲`Paths_[項目名稱]`的模塊。
該模塊提供了項目的**版本**與**路徑**信息。

模塊導出接口如下：

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

- `version` 包含項目版本版本號和版本名稱
- `getBinDir` 項目可執行文件所在的路徑
- `getDataDir` 獲取數據文件所在的路徑
- `getDataFileName` 使用相對路徑獲取指定數據文件的絕對路徑

在項目中使用`Paths_[項目名稱]`模塊需要在`library`配置段中添加`other-modules`配置項：

```yaml
library
  hs-source-dirs:      src
  ...
  other-modules:       Paths_xxx
```

若未添加`other-modules`配置項，則構建項目時會產生未定義符號錯誤：

```
Undefined symbols for architecture x86_64:
...
```



# 問題註記
記錄使用stack中遇到的問題。

## Revision Mismatch
當Stackage鏡像源未完全同步官方源時，部分包可能MD5校驗未通過，出現`Revision Mismatch`錯誤。
對於`Revision Mismatch`錯誤，默認行爲是直接退出。

在`$stack-root/config.yaml`中添加配置：

```yaml
ignore-revision-mismatch: true
```

使用該配置則啓動GHC時會忽略`Revision Mismatch`錯誤。

## HDBC-mysql
HDBC-mysql包需要依賴部分C庫，如`libz`、`libssl`、`libmysqlclient`等。
直接使用stack安裝時會得到錯誤信息：

```
setup: Missing dependencies on foreign libraries:
* Missing C libraries: z, ssl, mysqlclient
This problem can usually be solved by installing the system packages that
provide these libraries (you may need the "-dev" versions). If the libraries
are already installed but in a non-standard location then you can use the
flags --extra-include-dirs= and --extra-lib-dirs= to specify where they are.
```

在macOS平臺下，使用Homebrew安裝對應依賴：

```c
/*
	MariaDB 提供了 libmysqlclient 依賴，
	同時 MariaDB 依賴於 openssl，安裝 MariaDB 時會自行安裝該依賴
*/
$ brew install mariadb
```

通過Homebrew安裝的openssl對應的庫文件不在標準路徑下，而是位於`/usr/local/opt/openssl/lib`路徑下，
使用Stack安裝HDBC-mysql需要額外指定該路徑：

```
$ stack install HDBC-mysql --extra-lib-dirs=/usr/local/opt/openssl/lib
```
