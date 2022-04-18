<!-- TOC -->

- [基本語法](#基本語法)
- [自動變量](#自動變量)
- [推斷依賴關係](#推斷依賴關係)
- [基本使用](#基本使用)

<!-- /TOC -->



# Make
在Unix环境下通常使用make工具来构建项目/工程，make工具通過解析makefie文件執行編譯流程。

## 基本語法
makefile文件的基本格式为：

```
target(目标文件): dependency(依赖文件),....
	command(执行指令)
```

`target`代表最终生成的目标文件(有一些常见的伪目标比如all、clean、.PHONY)。
`dependency`代表生成目标文件所需要用到的源文件(依赖文件)。
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

## 自動變量
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

## 推斷依賴關係
makefile可以一定程度上自动推导依赖关系，
如存在一个目标文件`abc`，会自动依赖目標`abc.o`，而一个`abc.o`的目标，会自动依赖源碼`abc.c`。

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

## 基本使用
CMake的構建定義文件為`CMakeLists.txt`，作用類似於makefile，
CMake通過分析CMakeLists.txt生成makefile進行項目構建。

基本的CMakeLists.txt結構：

```cmake
# Set the mini version of CMake
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(ProjectNameXXX)

# Set the C/CPP standard
set(CMAKE_CXX_STANDARD 17)

# Include the system header file path
include_directories(SYSTEM /usr/include/xxx ...)

# Add the source paths
aux_source_directory(./src SRC1)
aux_source_directory(./tools SRC2)
aux_source_directory(./libxxx_src XXXLIB)
...

# Add the executable
add_executable(test_exec ./main.cc ${SRC1} ${SRC2} ...)
...

# Set up the custom library
add_library(xxx_lib STATIC ${XXXLIB})
set_target_properties(xxx_lib PROPERTIES LINKER_LANGUAGE CXX)
...

# Link library
target_link_libraries(test_exec xxx_lib)
target_link_libraries(test_exec -lpthread -ldl -lrt ...)
...
```

編寫CMakeLists.txt完成後，使用`cmake`指令指定項目路徑生成構建信息：

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
```

正確生成構建信息後，開始構建項目：

```
$ cmake --build 構建信息路徑
```
