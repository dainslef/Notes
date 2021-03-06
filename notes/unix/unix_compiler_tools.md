<!-- TOC -->

- [編譯流程](#編譯流程)
	- [Preproceessing (預處理)](#preproceessing-預處理)
	- [Compilation (編譯)](#compilation-編譯)
	- [Assembly (彙編)](#assembly-彙編)
	- [Linking (鏈接)](#linking-鏈接)
- [編譯器](#編譯器)
	- [基本編譯操作](#基本編譯操作)
	- [庫文件](#庫文件)
	- [符號信息](#符號信息)
	- [反彙編](#反彙編)
	- [otool](#otool)
	- [頭文件/庫文件路徑](#頭文件庫文件路徑)
	- [優化級別](#優化級別)
	- [其它編譯器參數](#其它編譯器參數)
- [Objective-C 編譯](#objective-c-編譯)
	- [環境安裝](#環境安裝)
	- [編譯參數](#編譯參數)

<!-- /TOC -->



# 編譯流程
編譯器處理代碼主要分爲以下幾個階段：

1. `Preprocessing` 預處理
1. `Compilation` 編譯
1. `Assembly` 彙編
1. `Linking` 鏈接

## Preproceessing (預處理)
主要處理包括以下過程：

1. 將所有的`#define`刪除，並且展開所有的宏定義
1. 處理所有的條件預編譯指令，比如`#if`、`#ifdef`、`#elif`、`#else`、`#endif`等
1. 處理`#include`預編譯指令，將被包含的文件插入到該預編譯指令的位置
1. 刪除所有**註釋**`//`和`/* */`
1. 添加**行號**和**文件標識**，以便編譯時產生調試用的行號及編譯錯誤警告行號
1. 保留所有的`#pragma`編譯器指令，因爲編譯器需要使用它們

預處理之後得到`*.i`的源碼文件。

## Compilation (編譯)
編譯過程就是把預處理完的文件進行一系列的**詞法分析**、**語法分析**、**語義分析**及優化後生成相應的彙編代碼。

編譯之後得到`*.s`的彙編源碼文件。

## Assembly (彙編)
彙編器是將彙編代碼轉變成機器可以執行的命令，每一個彙編語句幾乎都對應一條機器指令。
彙編相對於編譯過程較簡單，根據彙編指令和機器指令的對照表一一翻譯。

彙編之後得到`*.o`的**目標文件**，內容爲**機器碼**，不能以普通文本形式的查看(用文本編輯器查看則內容爲亂碼)。
`Linux/Unix`環境下的彙編器爲`as`。

## Linking (鏈接)
鏈接程序運行需要的目標文件，以及所依賴的其它庫文件，最後生成可執行文件。
`Linux/Unix`環境下的鏈接器爲`ld`。



# 編譯器
在`Unix`環境下，常用的編譯器爲`gcc/clang`。二者的提供類似的命令行接口。

## 基本編譯操作
編譯源碼的基本命令(一次性執行預處理、編譯、彙編、鏈接等所有過程，直接得到可執行文件)：

```c
$ cc [c源碼文件] //cc爲c語言編譯器
$ c++ [c++源碼文件] //c++爲c++編譯器
```

不同的操作系統中對`cc`編譯器的實現**不同**。
通常cc/c++指令是一個軟鏈接，指向系統默認的編譯器，即使用cc/c++編譯器實際調用的是操作系統的默認編譯器：

- 在`Linux`中，`cc`軟鏈接指向`gcc`編譯器。
- 在`FreeBSD/macOS`中，`cc`軟鏈接指向`clang`編譯器。
- 在`Solaris`中，`cc`指令不再是軟鏈接，而是`Solaris`特有的商業閉源編譯器。

編譯完成後編譯器會生成一個名爲`a.out`的二進制可執行文件，運行程序：

```
$ ./a.out
```

若需要指定生成可執行文件的名稱，則需要使用`-o`參數：

```
$ cc [源碼文件] -o [指定執行文件的名稱]
```

若僅需要編譯器進行預處理，則需要使用`-E`參數：

```c
$ cc -E [源碼文件]

// 通常編譯器會將預處理的結果直接輸出到終端上，若需要將預處理結果輸出到文件中，使用 -o 參數(保存預處理後代碼的文件一般用`*.i`做後綴名)
$ cc -E [源碼文件] -o [預處理結果文件名(*.i)]
```

若需要得到編譯器生成的彙編代碼可以使用`-S`參數：

```c
$ cc -S [源碼文件]

// 默認情況下生成 AT&T 風格的彙編，若需要生成 Intel 風格的彙編可以使用參數 -masm
$ cc -S -masm=intel [源碼文件]
```

若不需要直接生成可執行文件，僅生成`*.o`格式的目標文件，則需使用`-c`參數：

```
$ cc -c [源碼文件]
```

默認編譯器**不會**在生成的執行文件中添加調試標記，若需要在生成的二進制文件中保留調試標記，需要使用`-g`參數：

```
$ cc -g [源碼文件]
```

使用`-g`參數生成的可執行文件會包含調試標記，可供`gdb`等調試器使用：

```
$ gdb [生成的可執行文件]
```

使用`-s`參數則生成可執行文件中的不包含符號表(不包含符號表的可執行文件體積更小，適合在發佈軟件時使用)：

```
$ cc -s [源碼文件]
```

使用`-D`參數可在編譯時添加宏定義，搭配`#ifdef/ifndef`等條件宏指令可實現在編譯時改變程序邏輯的效果。
假設有源碼文件`test.c`，內容如下所示：

```c
#include <stdio.h>

int main(void)
{

#ifdef __TEST__
	printf("Use macro __TEST__.");
#else
	printf("Dont't use macro.");
#endif

	return 0;
}
```

使用指令`cc test.c`編譯，輸出結果：

```
Dont't use macro.
```

使用指令`cc -D__TEST__ test.c`編譯，輸出結果：

```
Use macro __TEST__.
```

## 庫文件
在Unix環境中，系統的庫文件一般存放在`/lib`、`/lib64`、`/usr/lib`等路徑下，庫文件分爲以下兩種類型：

- **動態鏈接庫**，後綴名爲`so`意爲`share object`(共享對象)。
- **靜態庫**，後綴名爲`a`意爲`archive`(檔案文件)。

在Unix環境中，庫的命名方式一般爲`lib+[庫名]`，如動態庫名稱爲`libssl.so`，則鏈接時的庫名稱爲`ssl`。
使用`ldd`命令可以查看可執行文件鏈接了哪些動態鏈接庫：

```
$ ldd [可執行文件]
```

- 鏈接庫文件

	在編譯時如果需要使用鏈接庫，需要`-l`參數直接加**庫名**而不需要寫完整的庫文件名字：

	```
	$ cc [源碼文件] -l[庫名]
	```

	若庫的位置不在環境變量中，則需要用`-L`參數指定庫所在路徑：

	```
	$ cc [源碼文件] -L[庫所在路徑] -l[庫名]
	```

	若源碼中引用的頭文件位置不在環境變量中，則需要用`-I`參數手動指定頭文件所在路徑：

	```
	$ cc [源碼文件] -I[頭文件路徑]
	```

	編譯器在鏈接庫時優先使用動態鏈接庫，若需使用靜態鏈接，使用`-static`參數強制編譯器使用靜態庫：

	```
	$ cc -static [源碼文件] -l[庫名]
	```

	連接目標文件(*.o)和庫時使用`ld`命令：

	```
	$ ld [目標文件] -l[庫名]
	```

- 生成庫文件

	動態鏈接庫可以由編譯器生成：

	```
	$ cc -shared -fPIC [源碼文件] -o [生成動態庫的名字]
	```

	靜態庫使用`ar`指令創建。
	需要先將源碼編譯成目標文件，再使用`ar`命令：

	```
	$ ar crs [生成靜態庫的名稱] [目標文件]
	```

	也可使用`libtool`工具生成動態庫和靜態庫。

- 庫文件環境變量

	如果一個程序使用了非系統提供的動態鏈接庫，需要將自己的動態鏈接庫位置加入環境變量中，否則在運行程序時會提示找不到	動態鏈接庫。

	與`Windows`不同，`Linux/Unix`系統默認情況下不會在可執行文件所處的路徑中尋找動態鏈接庫。
	若需要可執行文件加載當前路徑下的動態庫，則需要將當前路徑加入`LD_LIBRARY_PATH`環境變量中：

	```
	$ export LD_LIBRARY_PATH=./
	```

	需要注意的是，該命令會在`logout`之後失效，長期使用可已考慮寫入`.xprofile`或`.profile`文件中。
	靜態鏈接庫由於在編譯階段已經將庫文件包含在可執行文件中，故不會出現類似問題。

## 符號信息
使用`nm`命令可以顯示二進制文件的符號信息(符號表)：

```
$ nm [可執行文件]
```

`nm`指令的常用參數：

- `-A` 在每個符號信息的前面打印所在對象文件名稱
- `-C` 輸出解碼過的符號名稱，能夠以易於理解的方式顯示`C++`函數名
- `-D` 打印動態符號
- `-l` 使用對象文件中的調試信息打印出所在源文件及行號
- `-n` 按照地址/符號值來排序
- `-u` 打印出那些未定義的符號

常見的符號類型：

- `A` 該符號的值在今後的鏈接中將不再改變
- `B` 該符號放在BSS段中，通常是那些未初始化的全局變量
- `D` 該符號放在普通的數據段中，通常是那些已經初始化的全局變量
- `T` 該符號放在代碼段中，通常是那些全局非靜態函數
- `U` 該符號未定義過，需要自其他對象文件中鏈接進來
- `W` 未明確指定的弱鏈接符號，同鏈接的其他對象文件中有它的定義就用上，否則就用一個系統特別指定的默認值

## 反彙編
在Linux下，使用`objdump`工具可以對`ELF`二進制文件進行反彙編。
以ArchLinux爲例，安裝objdump：

```
# pacman -S binutils
```

`objdump`工具的常見參數：

- `-a` 查看檔案文件(`*.a`靜態庫)的詳細信息
- `-C` 將底層符號名解碼成用戶級名稱，讓`C++`函數名以能夠被理解的方式顯示出來
- `-d` 查看二進制文件的反彙編代碼
- `-D` 查看二進制文件的反彙編代碼，包括所有`section`
- `-g` 顯示調試信息
- `-e` 顯示調試信息，生成的信息格式與`ctags`兼容
- `-r` 顯示文件的重定位入口，只能用於靜態庫
- `-R` 顯示文件的動態重定位入口，用於動態鏈接庫和可執行文件
- `-s` 以16進制形式查看可執行文件內容

## otool
在macOS下，二進制格式爲`Mach-O`，macOS沒有提供`objdump`、`ldd`等工具。

使用`otool`工具代替`objdump`進行反彙編：

```
$ otool -Vt [二進制文件]
```

使用`otool`工具代替`ldd`顯示文件鏈接了哪些動態庫：

```
$ otool -L [二進制文件]
```

## 頭文件/庫文件路徑
編譯時gcc會自動包含一些常規系統頭文件路徑，如`/usr/include`；以及一些常規的系統庫路徑，如`/usr/lib`。

若需要追加包含自定義頭文件路徑，應使用`-I`編譯參數；
追加包含自定庫文件路徑，應使用`-L`編譯參數。

若需要添加系統頭文件路徑，可設置以下環境變量：

- `C_INCLUDE_PATH` `gcc`附加頭文件路徑
- `CPLUS_INCLUDE_PATH` `g++`附加頭文件路徑
- `LD_LIBRARY_PATH` 附加庫文件路徑

gcc/g++會將對應環境變量下的路徑視爲附加的系統頭文件/庫文件路徑，不必每次使用`-I/-L`參數顯式添加。

使用`--sysroot`參數可以重設頭文件/庫文件的邏輯根目錄，使用此參數，默認的頭文件/庫文件路徑均會隨之改變。
如設定`--sysroot=dir`，則默認頭文件路徑變爲`dir/usr/include`，默認庫文件路徑變爲`dir/usr/lib`。

## 優化級別
在編譯程序時，可以爲程序添加代碼優化選項來提升程序的運行效率。

gcc/clang有`O1`、`O2`、`O3`三個代碼優化級別，`O1`最低，`O3`優化最高。
使用優化選項能大幅度提升生成二進制文件的執行效率，但會使得生成的程序難以調試。
故一般只在程序完成測試之後進入發佈階段纔會啓用編譯優化選項。

## 其它編譯器參數
其它常用的編譯器參數如下：

- `-W` 警告選項，常用的是`-Wall`，開啓所有警告。
- `-M` 將文件依賴關係輸出到標準輸出，輸出的文件依賴可以被構建工具`make`使用。
	1. `-M` 默認會輸出所有的頭文件路徑，包括`#include<>`和`#include""`。
	1. `-MM` 僅輸出`#include""`的頭文件路徑。
	1. `-MD` 將依賴關係輸出重定向到依賴關係文件`[文件名].d`，通常與`-M`或`-MM`一同使用。



# Objective-C 編譯
主流的編譯器同樣支持`Objective-C`語言，Objective-C語言的源碼爲`*.m`。

## 環境安裝
要讓編譯器順利的編譯`Objective-C`的源碼，需要安裝對應開發庫，在Linux系統中是`GNUstep`庫。

使用gcc編譯`Objective-C`源碼，需要安裝gcc的`Objective-C`支持包`gcc-objc`。
以`ArchLinux`爲例，安裝`Objective-C`開發環境：

```
# pacman -S gcc-objc gnustep-core
```

## 編譯參數
編譯Objective-C源碼相對編譯C/C++源碼而言要更復雜，需要使用更多的編譯器參數。

使用`gnustep-config --objc-flags`指令會自動生成編譯Objective-C源碼需要的編譯器參數，將指令的結果插入gcc編譯指令的參數中。
通常情況下，需要鏈接`libgnustep-base`、`libobjc`等庫，若源碼使用了GUI庫還需要鏈接`libgnustep-gui`庫。

gcc編譯`Objective-C`源碼指令：

```
$ gcc $(gnustep-config --objc-flags) -lobjc -lgnustep-base [源碼文件]
```

由於`gnustep-config`默認與`GNU編譯器`組搭配，故其生成的編譯參數並不完全適用於clang編譯器。
需要手動指定編譯參數以符合clang編譯器的要求，根據編譯器輸出的異常信息將`gnustep-config`指令生成的參數中不符合要求的參數剔除，
並加入其他需要的編譯器參數。

clang編譯`Objective-C`源碼指令(以`Archlinux x64`和`gcc 4.9.2`爲例)：

```
$ clang -fconstant-string-class=NSConstantString -lgnustep-base -lobjc -I/usr/lib/gcc/x86_64-unknown-linux-gnu/[gcc-version]/include [源碼文件]
```
