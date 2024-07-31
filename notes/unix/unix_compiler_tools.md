<!-- TOC -->

- [編譯流程](#編譯流程)
    - [Preproceessing（預處理）](#preproceessing預處理)
    - [Compilation（編譯）](#compilation編譯)
    - [Assembly（彙編）](#assembly彙編)
    - [Linking（鏈接）](#linking鏈接)
- [編譯器](#編譯器)
    - [基本編譯操作](#基本編譯操作)
    - [庫文件](#庫文件)
    - [靜態鏈接與動態鏈接](#靜態鏈接與動態鏈接)
    - [符號信息](#符號信息)
    - [頭文件/庫文件路徑](#頭文件庫文件路徑)
    - [警告級別](#警告級別)
    - [優化級別](#優化級別)
    - [其它編譯器參數](#其它編譯器參數)
    - [Objective-C編譯](#objective-c編譯)
        - [安裝Objective-C庫](#安裝objective-c庫)
        - [Objective-C編譯參數](#objective-c編譯參數)
- [反編譯](#反編譯)
    - [otool](#otool)
    - [radare2](#radare2)
- [Make](#make)
    - [Make基本語法](#make基本語法)
    - [Make自動變量](#make自動變量)
    - [Make推斷依賴關係](#make推斷依賴關係)
- [CMake](#cmake)
    - [CMake基本使用](#cmake基本使用)
    - [CMakeLists.txt](#cmakeliststxt)
    - [CMake生成項目構建信息](#cmake生成項目構建信息)
- [GDB](#gdb)
    - [交互式使用GDB](#交互式使用gdb)
    - [GDB基本操作](#gdb基本操作)
    - [調試子進程](#調試子進程)
    - [設置源碼目錄](#設置源碼目錄)
    - [調試核心轉儲](#調試核心轉儲)

<!-- /TOC -->



# 編譯流程
編譯器處理代碼主要分為以下幾個階段：

1. `Preprocessing` 預處理
1. `Compilation` 編譯
1. `Assembly` 彙編
1. `Linking` 鏈接

## Preproceessing（預處理）
主要處理包括以下過程：

1. 將所有的`#define`刪除，並且展開所有的宏定義
1. 處理所有的條件預編譯指令，比如`#if`、`#ifdef`、`#elif`、`#else`、`#endif`等
1. 處理`#include`預編譯指令，將被包含的文件插入到該預編譯指令的位置
1. 刪除所有**註釋**`//`和`/* */`
1. 添加**行號**和**文件標識**，以便編譯時產生調試用的行號及編譯錯誤警告行號
1. 保留所有的`#pragma`編譯器指令，因為編譯器需要使用它們

預處理之後得到`*.i`的源碼文件。

## Compilation（編譯）
編譯過程就是把預處理完的文件進行一系列的**詞法分析**、**語法分析**、**語義分析**及優化後生成相應的彙編代碼。

編譯之後得到`*.s`的彙編源碼文件。

## Assembly（彙編）
彙編器是將彙編代碼轉變成機器可以執行的命令，每一個彙編語句幾乎都對應一條機器指令。
彙編相對於編譯過程較簡單，根據彙編指令和機器指令的對照表一一翻譯。

彙編之後得到`*.o`的**目標文件**，內容為**機器碼**，
不能以普通文本形式的查看（用文本編輯器查看則內容為亂碼）。
`Linux/Unix`環境下的彙編器為`as`。

## Linking（鏈接）
鏈接程序運行需要的目標文件，以及所依賴的其它庫文件，最後生成可執行文件。
`Linux/Unix`環境下的鏈接器為`ld`。



# 編譯器
在`Unix`環境下，常用的編譯器為`gcc/clang`。二者的提供類似的命令行接口。

## 基本編譯操作
編譯源碼的基本命令（一次性執行預處理、編譯、彙編、鏈接等所有過程，直接得到可執行文件）：

```html
$ cc C語言源碼文件 <!-- cc為C語言編譯器 -->
$ c++ C++源碼文件 <!-- c++為C++編譯器 -->
```

不同的操作系統中對`cc`編譯器的實現**不同**。
通常cc/c++指令是一個軟鏈接，指向系統默認的編譯器，
即使用cc/c++編譯器實際調用的是操作系統的默認編譯器：

- 在`Linux`中，`cc`軟鏈接指向`gcc`編譯器。
- 在`FreeBSD/macOS`中，`cc`軟鏈接指向`clang`編譯器。
- 在`Solaris`中，`cc`指令不再是軟鏈接，而是`Solaris`特有的商業閉源編譯器。

編譯完成後編譯器會生成一個名為`a.out`的二進制可執行文件，運行程序：

```
$ ./a.out
```

若需要指定生成可執行文件的名稱，則需要使用`-o`參數：

```
$ cc 源碼文件 -o 可執行文件
```

若僅需要編譯器進行預處理，則需要使用`-E`參數：

```html
$ cc -E 源碼文件

<!--
通常編譯器會將預處理的結果直接輸出到終端上，若需要將預處理結果輸出到文件中，
使用 -o 參數（保存預處理後代碼的文件一般用`*.i`做後綴名）
-->
$ cc -E 源碼文件 -o 預處理結果文件（*.i）
```

若需要得到編譯器生成的彙編代碼可以使用`-S`參數：

```html
$ cc -S 源碼文件

<!-- 默認生成 AT&T 風格的彙編，若需要生成Intel風格的彙編可以使用參數 -masm -->
$ cc -S -masm=intel 源碼文件
```

若不需要直接生成可執行文件，僅生成`*.o`格式的目標文件，則需使用`-c`參數：

```
$ cc -c 源碼文件
```

默認編譯器**不會**在生成的執行文件中添加調試標記，
若需要在生成的二進制文件中保留調試標記，需要使用`-g`參數：

```
$ cc -g 源碼文件
```

使用`-g`參數生成的可執行文件會包含調試標記，可供`gdb`等調試器使用：

```
$ gdb 可執行文件
```

使用`-s`參數則生成可執行文件中的不包含符號表
（不包含符號表的可執行文件體積更小，適合在發佈軟件時使用）：

```
$ cc -s 源碼文件
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
在Unix環境中，系統的庫文件一般存放在`/lib`、`/lib64`、`/usr/lib`等路徑下，庫文件分為以下兩種類型：

- **動態鏈接庫**，後綴名為`so`意為`share object`(共享對象)。
- **靜態庫**，後綴名為`a`意為`archive`(檔案文件)。

在Unix環境中，庫的命名方式一般為`lib庫名`，如動態庫名稱為`libssl.so`，則鏈接時的庫名稱為`ssl`。
使用`ldd`命令可以查看可執行文件鏈接了哪些動態鏈接庫：

```
$ ldd 可執行文件
```

使用`ldconfig`可查詢系統當前安裝了哪些庫：

```
$ ldconfig -p
```

- 鏈接庫文件

	在編譯時如果需要使用鏈接庫，需要`-l`參數直接加**庫名**而不需要寫完整的庫文件名字：

	```
	$ cc 源碼文件 -l庫名
	```

	若庫的位置不在環境變量中，則需要用`-L`參數指定庫所在路徑：

	```
	$ cc 源碼文件 -L庫所在目錄 -l庫名
	```

	若源碼中引用的頭文件位置不在環境變量中，則需要用`-I`參數手動指定頭文件所在路徑：

	```
	$ cc 源碼文件 -I頭文件路徑
	```

	編譯器在鏈接庫時優先使用動態鏈接庫，若需使用靜態鏈接，使用`-static`參數強制編譯器使用靜態庫：

	```
	$ cc -static 源碼文件 -l庫名
	```

	連接目標文件(*.o)和庫時使用`ld`命令：

	```
	$ ld 目標文件 -l庫名
	```

- 生成庫文件

	動態鏈接庫可以由編譯器生成：

	```
	$ cc -shared -fPIC 源碼文件 -o 生成動態庫
	```

	靜態庫使用`ar`指令創建。
	需要先將源碼編譯成目標文件，再使用`ar`命令：

	```
	$ ar crs 生成靜態庫 目標文件
	```

	也可使用`libtool`工具生成動態庫和靜態庫。

- 庫文件環境變量

	若程序使用了非系統提供的動態鏈接庫，需要將自己的動態鏈接庫位置加入環境變量中，
	否則在運行程序時會提示找不到動態鏈接庫。

	與Windows不同，Linux/Unix系統默認不會在可執行文件所處的路徑中尋找動態鏈接庫。
	若需要可執行文件加載當前路徑下的動態庫，則需要將當前路徑加入`LD_LIBRARY_PATH`環境變量中：

	```
	$ export LD_LIBRARY_PATH=./
	```

	需要注意的是，該命令會在`logout`之後失效，長期使用可已考慮寫入`.xprofile`或`.profile`文件中。
	靜態鏈接庫由於在編譯階段已經將庫文件包含在可執行文件中，故不會出現類似問題。

## 靜態鏈接與動態鏈接
動態鏈接和靜態鏈接程序的比較：

| 類別 | 優勢 | 劣勢 |
| :- | :- | :- |
| 動態鏈接 | 使用外部動態鏈接庫，程序自身體積較小 | 部署不便，對環境依賴較高 |
| 靜態鏈接 | 僅依賴操作系統，無其它額外依賴，部署方便 | 所有依賴庫代碼靜態編譯到程序中，程序自身體積較大 |

Linux平臺下編譯器採用**動態鏈接**，多數發行版使用`Glibc`作為C標準庫的實現，
而Glibc因為設計上的原因，使用靜態鏈接存在諸多問題，
詳情參考[StackOverflow](https://stackoverflow.com/questions/57476533/why-is-statically-linking-glibc-discouraged)
上的相關討論。

Linux平臺下靜態鏈接推薦使用[`musl libc`](https://musl.libc.org/)，
musl相比Glibc實現簡單、直觀、輕量，適合作靜態鏈接使用。

各大Linux發行版通常源中已包含musl，使用發行版內置包管理器安裝即可：

```html
# apt install musl-tools <!-- 大便系-->
# pacman -S musl <!-- Arch系 -->
# nix-env -i musl <!-- Nix -->
```

musl軟件包提供了主要編譯工具鏈的腳本封裝：

```
$ musl-gcc
$ musl-clang
$ musl-ldd
```

使用musl提供的工具編譯代碼會使用musl替換Glibc：

```html
$ musl-gcc test.c
$ file a.out
a.out: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib/ld-musl-x86_64.so.1, not stripped
<!-- musl-gcc 編譯生成的二進制使用標準 ldd 查看動態鏈接庫會產生錯誤 -->
$ ldd a.out
./a.out: error while loading shared libraries: /usr/lib/x86_64-linux-gnu/libc.so: invalid ELF header
<!-- 應使用 musl-ldd 方可正常展示動態鏈接庫 -->
$ musl-ldd a.out
	/lib/ld-musl-x86_64.so.1 (0x7fab864c4000)
	libc.so => /lib/ld-musl-x86_64.so.1 (0x7fab864c4000)
```

## 符號信息
使用`nm`命令可以顯示二進制文件的符號信息（符號表）：

```
$ nm 可執行文件
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

## 頭文件/庫文件路徑
編譯時gcc會自動包含一些常規系統頭文件路徑，如`/usr/include`；以及一些常規的系統庫路徑，如`/usr/lib`。

若需要追加包含自定義頭文件路徑，應使用`-I`編譯參數；
追加包含自定庫文件路徑，應使用`-L`編譯參數。

若需要添加系統頭文件路徑，可設置以下環境變量：

- `C_INCLUDE_PATH` `gcc`附加頭文件路徑
- `CPLUS_INCLUDE_PATH` `g++`附加頭文件路徑
- `LD_LIBRARY_PATH` 附加庫文件路徑

gcc/g++會將對應環境變量下的路徑視為附加的系統頭文件/庫文件路徑，不必每次使用`-I/-L`參數顯式添加。

使用`--sysroot`參數可以重設頭文件/庫文件的邏輯根目錄，使用此參數，默認的頭文件/庫文件路徑均會隨之改變。
如設定`--sysroot=dir`，則默認頭文件路徑變為`dir/usr/include`，默認庫文件路徑變為`dir/usr/lib`。

## 警告級別
編譯器可通過參數開啟更多檢查和告警信息：

- `-Wall` 啟用大部分通用告警與檢查（如未被使用的字段、函數等）
- `-Wextra` 啟用未被-Wall開啟的額外檢查
- `-pedantic` 強制遵循ISO C/C++標準，對於非標準用法告警

## 優化級別
在編譯程序時，可以為程序添加代碼優化選項來提升程序的運行效率。

gcc/clang有`O1`、`O2`、`O3`三個代碼優化級別，`O1`最低，`O3`優化最高。
使用優化選項能大幅度提升生成二進制文件的執行效率，但會使得生成的程序難以調試。
故一般只在程序完成測試之後進入發佈階段才會啟用編譯優化選項。

## 其它編譯器參數
其它常用的編譯器參數如下：

- `-M` 將文件依賴關係輸出到標準輸出，輸出的文件依賴可以被構建工具`make`使用。
	1. `-M` 默認會輸出所有的頭文件路徑，包括`#include<>`和`#include""`。
	1. `-MM` 僅輸出`#include""`的頭文件路徑。
	1. `-MD` 將依賴關係輸出重定向到依賴關係文件`[文件名].d`，通常與`-M`或`-MM`一同使用。

## Objective-C編譯
主流的編譯器同樣支持`Objective-C`語言，Objective-C語言的源碼為`*.m`。

### 安裝Objective-C庫
要讓編譯器順利的編譯Objective-C的源碼，需要安裝對應開發庫，在Linux系統中是`GNUstep`庫。

使用gcc編譯Objective-C源碼，需要安裝gcc的Objective-C支持包`gcc-objc`。
以Arch Linux為例，安裝Objective-C開發環境：

```
# pacman -S gcc-objc gnustep-core
```

### Objective-C編譯參數
編譯Objective-C源碼相對編譯C/C++源碼而言要更復雜，需要使用更多的編譯器參數。

使用`gnustep-config --objc-flags`指令會自動生成編譯Objective-C源碼需要的編譯器參數，
將指令的結果插入gcc編譯指令的參數中。通常情況下，需要鏈接`libgnustep-base`、`libobjc`等庫，
若源碼使用了GUI庫還需要鏈接`libgnustep-gui`庫。

gcc編譯Objective-C源碼指令：

```
$ gcc $(gnustep-config --objc-flags) -lobjc -lgnustep-base 源碼文件
```

由於gnustep-config默認與**GNU編譯器**組搭配，
故其生成的編譯參數並不完全適用於clang編譯器。
需要手動指定編譯參數以符合clang編譯器的要求，
根據編譯器輸出的異常信息將gnustep-config指令生成的參數中不符合要求的參數剔除，
並加入其他需要的編譯器參數。

clang編譯Objective-C源碼指令，以`Archlinux x64`和`gcc 4.9.2`為例：

```
$ clang -fconstant-string-class=NSConstantString -lgnustep-base -lobjc -I/usr/lib/gcc/x86_64-unknown-linux-gnu/gcc版本/include 源碼文件
```



# 反編譯
在Linux下，使用`objdump`工具可以對`ELF`二進制文件進行反彙編。
以ArchLinux為例，安裝objdump：

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
在macOS下，二進制格式為`Mach-O`，macOS沒有提供`objdump`、`ldd`等工具。

使用`otool`工具代替`objdump`進行反彙編：

```
$ otool -Vt 二進制文件
```

使用`otool`工具代替`ldd`顯示文件鏈接了哪些動態庫：

```
$ otool -L 二進制文件
```

## radare2
[radare2](https://github.com/radareorg/radare2)是Unix平臺的反向工程框架，
提供對程序的分析、模擬、調試、修改、反彙編等功能的集成。

radare2安裝後的指令名為`r2`或`radare2`。
與gdb類似，執行radare2工具後會進入交互會話，
radare2的會話指令為單字母組合，使用`?`顯示當前可用的指令：

```html
$ r2
> ? <!-- 列出當前可用的指令 -->
> x? <!-- 列出x指令可用的子指令 -->
```

常用功能：

```
$ r2 /bin/ls   # open the binary in read-only mode
> aaa          # same as r2 -A, analyse the binary
> afl          # list all functions (try aflt, aflm)
> px 32        # print 32 byte hexdump current block
> s sym.main   # seek to the given offset (by flag name, number, ..)
> f~foo        # filter flags with ~grep (same as |grep)
> iS;is        # list sections and symbols (same as rabin2 -Ss)
> pdf; agf     # print function and show control-flow-graph in ascii-art
> oo+;w hello  # reopen in rw mode and write a string in the current offset
> ?*~...       # interactive filter all command help messages
> q            # quit
```



# Make
在Unix环境下通常使用make工具来构建项目/工程，make工具通過解析makefie文件執行編譯流程。

## Make基本語法
makefile文件的基本格式为：

```
target(目标文件): dependency(依赖文件),....
	command(执行指令)
```

`target`代表最终生成的目标文件（有一些常见的伪目标比如all、clean、.PHONY）。
`dependency`代表生成目标文件所需要用到的源文件（依赖文件）。
`command`代表为了生成目标文件所需要执行的指令，该指令也可以是shell脚本指令。

每次使用make指令时，make工具会对比目标文件与依赖文件的改动时间，
若目标文件不存在或是改动时间在依赖文件之前的话，会执行命令，再次生成目标文件。
make工具會自上向下分析makefile关系，即第一个目标文件满足新旧关系，便不会在向下执行剩余的语句，
因此，第一个目标文件需要设定为整个工程的最终生成文件。若工程有多个最终生成文件，则可以使用伪目标all。
使用make工具时如果不添加参数，则将第一个目标文件作为最终生成文件，
若需要指定进行某一步的make操作，则应使用`make 目标名`的方式来指定进行某一步make过程。

makefile中注释跟Bash脚本一样，采用`#`进行单行注释。
默认情况下，makefile中执行的指令内容会显示在终端上，
在要执行的指令前加上`@`符号可以关闭该指令内容在终端的显示。

对于经常使用的长指令或是重复目标文件可以采用定义变量的形式：

```make
c++ = g++ -std=c++11
a.out: example.o
	$(c++) example.o # 展开后相当与 g++ -std=c++11 example.o
example.o: example.cc
	$(c++) -c example.cc
```

makefile中的最终目标也可以是伪目标，如伪目标all代表所有目标的目标。
一个makefile如果要编译多个不相关程序，则可将这多个程序作为all目标的依赖，如下所示：

```make
all: app1 app2
app1: ...
app2: ...
```

可以在编译时分别使用`make app1`以及`make app2`来编译独立的部分。

## Make自動變量
像shell脚本一样使用`$(变量名)`的形式来使用变量的内容（$符号后的括号不可省略）。
makefile中有一些常用自动变量：

```
$@	目标文件
$^	所有的依赖文件
$<	第一个依赖文件
$*	指代匹配符 % 匹配的部分
```

makefile的通配符与Bash一致，主要有星号`*`、问号`？`等；
例如，`*.o`表示所有后缀名为o的文件。

Make命令允许对文件名，进行类似正则运算的匹配，主要用到的匹配符是%。
示例，假定当前目录下有`f1.c`和`f2.c`两个源码文件，需要将它们编译为对应的对象文件。

```
%.o: %.c
```

等同于下面的写法：

```
f1.o: f1.c
f2.o: f2.c
```

常用内置函数：

```make
# wildcard，将匹配file表达式的文件展开成列表，语法：
$(wildcard file)
# foreach，将变量var中的内容逐一遍历，语法：
$(foreach n, $(var), $(n))
```

## Make推斷依賴關係
makefile可以一定程度上自动推导依赖关系，
如存在一个目标文件`abc`，会自动依赖目標`abc.o`，
而一个`abc.o`的目标，会自动依赖源碼`abc.c`。

Unix環境下的C/C++编译器大多带有推断make关系的功能，
例如gcc可以使用`-M`参数来推断源文件的make关系：

```html
$ cc -M 源码文件 <!-- 推断所有的依赖关系，包括系统目录下头文件 -->
$ cc -MM 源码文件 <!-- 推断系统目录头文件之外的依赖关系 -->
$ cc -MM -I头文件路径 源码文件 <!-- 若包含了系统目录外的头文件，则需要使用-I参数指明包含目录，否则会造成依赖推断报错 -->
```

可以将文件的依赖关系保存到文件中：

```html
$ cc -MD 源码文件 <!-- 将源码文件的依赖输出以文本的形式输出到"源码名称.d"文件中 -->
$ cc -MM -MD 源码文件 <!-- 默认导出的依赖会包含系统头文件，避免导出系统头文件依赖同样需要使用-MM参数 -->
```



# CMake
[`CMake`](https://cmake.org/)是現代C/C++項目的構建、測試、打包工具。
CMake相比傳統make工具功能更加強大，配置編寫更加簡單。

## CMake基本使用
對於CMake項目，使用`cmake`指令指定項目路徑生成構建信息：

```html
<!--
項目頂層目錄下需要存在CMakeLists.txt文件
CMakeLists.txt文件中指令的源碼相對路徑即以項目目錄作為基準
-->
$ cmake 項目目錄

<!--
默認cmake指令會在項目目錄下生成構建信息相關文件/目錄，包括：
CMakeCache.txt
Makefile
cmake_install.cmake
CMakeFiles (目錄)

若不希望cmake生成的構建信息混雜在項目路徑下，則可單獨指定構建信息的生成路徑
使用 -B 參數指定構建信息生成路徑
-->
$ cmake 項目目錄 -B 構建信息生成路徑
$ cmake 項目目錄 -D構建屬性=值 -D... -B 構建信息生成路徑
$ cmake 項目目錄 -D構建屬性="值1;值2;..." -D... -B 構建信息生成路徑
```

CMake提供一些預定義屬性用於控制常見的編譯部署行為：

- `CMAKE_C_FLAGS` 控制C編譯參數
- `CMAKE_CXX_FLAGS` 控制C++編譯參數
- `CMAKE_INSTALL_PREFIX` 控制部署路徑
- `CMAKE_INSTALL_INCLUDEDIR` 單獨控制頭文件的部署路徑
- `CMAKE_INSTALL_BINDIR` 控制二進制文件的部署路徑
- `CMAKE_INSTALL_LIBDIR` 控制庫文件的部署路徑
- `PROJECT_SOURCE_DIR` 項目源碼路徑
- `PROJECT_BINARY_DIR` 項目構建路徑

正確生成構建信息後，開始構建項目：

```html
$ cmake --build 構建信息路徑

<!-- 使用多綫程并行編譯 -->
$ cmake --build 構建信息路徑 -j 綫程數目
$ cmake --build 構建信息路徑 --parallel 綫程數目
```

若項目定義了install目標，則構建完成后，可執行安裝：

```html
$ cmake --install 構建信息路徑
```

## CMakeLists.txt
CMake的構建定義文件為`CMakeLists.txt`，作用類似於makefile，
CMake通過分析該文件生成makefile進行項目構建。

CMakeLists.txt基本結構：

```cmake
# 設置最低CMake版本，需要寫在文件起始位置，否則會產生Warning
cmake_minimum_required(VERSION 3.10)

# 設置項目名稱
project(project-xxx-name VERSION 版本號)

# 設置C/C++標準
set(CMAKE_CXX_STANDARD 17)

# 設置頭文件路徑
include_directories(SYSTEM /usr/include/xxx ...)

# 設置庫文件路徑
link_directories(/path/to/libraries ...)

# 添加源碼路徑（aux_source_directory()函數不再推薦使用）
# 可使用 ${CMAKE_CURRENT_SOURCE_DIR} 得到項目目錄的絕對路徑
file(GLOB SRC1 src1/*.cc) # file()函數GLOB模式匹配收集匹配的文件
file(GLOB_RECURSE SRC2 src2/*.pp) # GLOB_RECURSE模式遞歸匹配文件
...

# 定義編譯生成的可執行文件
add_executable(${PROJECT_NAME} ${SRC1} ${SRC2} ...)
add_executable(test_exec ${SRC1} ${SRC2} ...)
...

# 添加其它CMake管理的子項目
add_subdirectory(xxx_subpath)
...

# 添加其它庫（源碼引入）
add_library(xxx_lib STATIC ${XXXLIB}) # 靜態庫，多文件
set_target_properties(xxx_lib PROPERTIES LINKER_LANGUAGE CXX)
add_library(xxx_dynamic_lib SHARED ${XXXLIB}) # 動態庫
add_library(xxx_src_lib STATIC xxx_src_file.cpp) # 單文件
...

# 鏈接庫
target_link_libraries(test_exec 庫名1 庫名2 ...) # 鏈接動態庫
target_link_libraries(test_exec xxx_lib)
target_link_libraries(test_exec -lpthread -ldl -lrt ...)
target_link_libraries(test_exec libxxx1.a libxxx2.a ...) # 鏈接靜態庫
...

# 添加全局編譯器參數
add_compile_options(...)
# 對指定目標添加編譯器參數
target_compile_options(test_exec PUBLIC/PRIVATE/INTERFACE ...)
...

# 打印輸出信息
message(...)
message(STATUS ...) # 可使用預定義的格式
```

## CMake生成項目構建信息
CMake支持將構建定義中的版本信息等輸出到文件中。

編寫模板文件，將構建信息定義為宏：

```h
// 文件名 version.h.in
#pragma once

#define PROJECT_VERSION "@PROJECT_VERSION@"
#define PROJECT_VERSION_MAJOR "@PROJECT_VERSION_MAJOR@"
#define PROJECT_VERSION_MINOR "@PROJECT_VERSION_MINOR@"
#define PROJECT_VERSION_PATCH "@PROJECT_VERSION_PATCH@"
#define BUILD_TIME "@BUILD_TIME@"
```

在CMakeLists.txt中添加下列內容：

```cmake
# 設置項目名稱與版本，版本號推薦使用 x.x.x 形式
project(項目名稱 VERSION 版本號)

# 記錄項目構建時間到 BUILD_TIME 變量中
string(TIMESTAMP BUILD_TIME "%Y%m%d-%H%M%S")

# 設置模板路徑與生成的源碼路徑
configure_file(
  "${PROJECT_SOURCE_DIR}/src/xxx/version.h.in"
  "${PROJECT_BINARY_DIR}/generate/version.h"
)
# 包含源碼生成路徑
include_directories("${PROJECT_BINARY_DIR}/generate")
```

使用VSCode的CMake插件，啟動構建後可自動生成源碼，並在編輯器中索引到生成的源碼文件。



# GDB
GDB是Linux最常用的調適器。

## 交互式使用GDB
GDB默認情況下是一個純CLI調試器，可以使用`-tui`參數使gdb提供一個基於CLI的簡單的交互式界面：

```
$ gdb -tui 可執行文件
```

## GDB基本操作
基本操作如下：

- `r(run)` 開始執行程序
- `n(next)` 執行下一條語句（不會進入子函數）
- `s(step)` 單步調試(會進入子函數內部)
- `c(continue)` 繼續執行程序（直到下一個斷點）
- `l(list)` 查看當前程序運行位置附近的代碼片段
- `b(break)` 設置斷點
- `p(print)` 顯示變量/函數等信息
- `i(info)` 可搭配不同指令顯示具體的狀態信息（斷點,顯示等）
- `d(delete)` 刪除設置（斷點,顯示信息等）
- `q(quit)` 退出gdb
- `bt(backtrace)` 顯示函數堆棧

`break`用於下斷點：

- `break [行號]`
- `break [函數名]`
- `break [地址]`

如果存在多個源碼文件，則需要使用源碼文件名顯式指定要下斷點的文件：

```
(gdb) break 源碼文件名:行號/函數名/地址
```

gdb支持條件斷點：

```
(gdb) break 行號/函數名/地址 if 條件
```

在判斷條件中甚至可以直接調用標準庫內的函數。

`display`讓每次運行暫停時都顯示指定的信息。可顯示變量/函數等信息。

一次顯示多個變量的信息：

```
(gdb) display/print {變量1, 變量2, 變量3......}
```

`delete`刪除已經存在的設置信息。

```
(gdb) delete 數據類型 號碼
```

舉例：

```html
(gdb) delete breakpoint 1 <!-- 刪除1號斷點 -->
```

`info`可以用於查看一些信息，常見的有：

- `info b` 顯示斷點信息
- `info locals` 顯示當前函數的局部變量信息
- `info threads` 顯示線程信息
- `info files` 顯示二進制文件的區段信息

`until`用於跳出循環，`finish`用於結束當前函數。

`ptype`用於輸出變量類型信息，對於結構類型（類）變量，能夠顯示出整個結構體/類的定義。

`checkpoint`指令可以在調試過程中將當前位置添加為檢查點。
當需要多次調試同一段代碼時，調試器能夠從檢查點位置恢復運行，而不必重啟整個進程。

查看當前檢查點信息：

```
(gdb) info checkpoints
```

從指定的檢查點恢復運行：

```
(gdb) restart 檢查點編號
```

## 調試子進程
默認情況下，gdb在程序調用fork()之後調試的是父進程，如果需要手動指定調試的進程，使用：

```
(gdb) set follow-fork-mode [parent | child]
```

## 設置源碼目錄
在調試時使用`dir`指令可以添加臨時的源碼目錄：

```
(gdb) dir 路徑
```

## 調試核心轉儲
程序崩潰時產生的轉儲文件亦可使用`gdb`調試：

```
$ gdb 可執行文件 對應錯誤轉儲文件
```
