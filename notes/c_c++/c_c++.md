<!-- TOC -->

- [內存區](#內存區)
    - [數值變量初始化](#數值變量初始化)
    - [全局變量/全局靜態變量初始化順序](#全局變量全局靜態變量初始化順序)
    - [局部靜態變量初始化順序](#局部靜態變量初始化順序)
- [C/C++中函數定義的區別](#cc中函數定義的區別)
- [`static`關鍵字](#static關鍵字)
    - [static（C++）](#staticc)
- [`const`關鍵字](#const關鍵字)
    - [const用於變量初始化](#const用於變量初始化)
    - [const變量作爲數組長度](#const變量作爲數組長度)
- [運算精度](#運算精度)
- [8進制與16進制](#8進制與16進制)
- [sizeof 運算符](#sizeof-運算符)
- [列表初始化](#列表初始化)
    - [數組初始化](#數組初始化)
    - [designated initializers (C99)](#designated-initializers-c99)
    - [二維數組初始化](#二維數組初始化)
    - [類/結構體列表初始化 (C++98)](#類結構體列表初始化-c98)
    - [統一初始化 (C++11)](#統一初始化-c11)
    - [std::initializer_list<T> (C++11)](#stdinitializer_listt-c11)
- [結構體對齊](#結構體對齊)
    - [指定結構體對齊大小](#指定結構體對齊大小)
- [變長參數](#變長參數)
    - [自定義變長參數函數](#自定義變長參數函數)
    - [通過地址獲取變長參數內容](#通過地址獲取變長參數內容)
    - [變長參數宏](#變長參數宏)
- [自增自減運算符的優先級](#自增自減運算符的優先級)
- [編譯器自動生成的成員函數](#編譯器自動生成的成員函數)
    - [控制默認生成的成員函數](#控制默認生成的成員函數)
- [繼承](#繼承)
- [指針運算](#指針運算)
    - [數組名的含義](#數組名的含義)
    - [指針數組與數組指針](#指針數組與數組指針)
- [C++對象模型](#c對象模型)
    - [成員函數](#成員函數)
    - [虛函數](#虛函數)
- [參數默認值](#參數默認值)
- [函數定義嵌套](#函數定義嵌套)
- [lvalue reference (左值引用) / rvalue reference (右值引用)](#lvalue-reference-左值引用--rvalue-reference-右值引用)
    - [rvalue reference (右值引用)](#rvalue-reference-右值引用)
    - [universal reference (通用引用)](#universal-reference-通用引用)
    - [reference collapsing (引用摺疊)](#reference-collapsing-引用摺疊)
    - [move semantics (移動語義)](#move-semantics-移動語義)
    - [std::move()](#stdmove)
    - [std::forward](#stdforward)
    - [注意事項](#注意事項)
    - [成員函數的引用限定](#成員函數的引用限定)
- [引用與指針](#引用與指針)
- [函數指針](#函數指針)
    - [成員指針](#成員指針)
- [template (模板)](#template-模板)
    - [模版編譯](#模版編譯)
    - [模版定義與聲明分離](#模版定義與聲明分離)
    - [模版的高級用法](#模版的高級用法)
    - [模版形參默認值](#模版形參默認值)
    - [模板與重載](#模板與重載)
    - [模版特化](#模版特化)
    - [模版遞歸](#模版遞歸)
    - [變長模版 (C++11)](#變長模版-c11)
    - [禁止特定類型的模板參數](#禁止特定類型的模板參數)
- [_Generic (C11)](#_generic-c11)
- [assert (斷言)](#assert-斷言)
    - [斷言宏](#斷言宏)
    - [靜態斷言 (C11)](#靜態斷言-c11)
    - [靜態斷言 (C++11)](#靜態斷言-c11)
- [auto 類型推導](#auto-類型推導)
    - [Lambda](#lambda)
    - [複用 Lambda](#複用-lambda)
    - [變量捕獲](#變量捕獲)
    - [C++14 中的 Lambda 新特性](#c14-中的-lambda-新特性)
- [STL 容器](#stl-容器)
    - [迭代器](#迭代器)
    - [序列式容器](#序列式容器)
    - [關聯式容器](#關聯式容器)
- [Smart Pointer (智能指針)](#smart-pointer-智能指針)
    - [智能指針的一般性用法](#智能指針的一般性用法)
    - [智能指針的轉型](#智能指針的轉型)
    - [改變做爲形參傳入的智能指針所指向的內容](#改變做爲形參傳入的智能指針所指向的內容)
- [std::bind()](#stdbind)
    - [bind() 綁定普通函數](#bind-綁定普通函數)
    - [bind() 綁定非靜態成員函數](#bind-綁定非靜態成員函數)
- [boost::signals2](#boostsignals2)
    - [定義信號](#定義信號)
    - [連接槽函數](#連接槽函數)
    - [取消連接](#取消連接)
    - [獲取信號返回值](#獲取信號返回值)
- [Boost 時間庫](#boost-時間庫)
    - [獲取當前時間](#獲取當前時間)
    - [獲取時間間隔](#獲取時間間隔)
- [std::chrono (標準時間庫)](#stdchrono-標準時間庫)
    - [std::chrono::duration](#stdchronoduration)
    - [std::time_point](#stdtime_point)
    - [時鐘類型](#時鐘類型)
    - [基本用法示例](#基本用法示例)
- [C/C++中一些編碼中遇到的錯誤](#cc中一些編碼中遇到的錯誤)
    - [multiple definition of](#multiple-definition-of)
    - [在 switch 的 case 語句中定義局部變量](#在-switch-的-case-語句中定義局部變量)
- [常用的C標準庫函數](#常用的c標準庫函數)
    - [memset()](#memset)
    - [memcpy()](#memcpy)
    - [strcpy() 函數](#strcpy-函數)
    - [setjmp() / longjmp()](#setjmp--longjmp)
    - [sigsetjmp() / siglongjmp()](#sigsetjmp--siglongjmp)
    - [getopt() / getopt_long()](#getopt--getopt_long)
- [一些關鍵字、特殊值的含義/用法](#一些關鍵字特殊值的含義用法)
    - [explicit 關鍵字](#explicit-關鍵字)
    - [restrict 關鍵字](#restrict-關鍵字)
    - [mutable 關鍵字](#mutable-關鍵字)
    - [volatile 關鍵字](#volatile-關鍵字)
    - [using 關鍵字](#using-關鍵字)
    - [移位運算符](#移位運算符)
    - [npos 成員](#npos-成員)
- [常見錯誤](#常見錯誤)
    - [error: jump to case label](#error-jump-to-case-label)
    - [warning: `...` will be initialized after [-Wreorder] ...](#warning--will-be-initialized-after--wreorder-)

<!-- /TOC -->



# 內存區
C/C++中，內存分爲5個區，分別是**堆區**，**棧區**，**靜態區**，**文字常量區**，**程序代碼區**。

| 名稱 | 含義 |
| :- | :- |
| stack（棧區） | 由編譯器自動分配釋放，存放函數的參數值，局部變量的值等。其操作方式類似於數據結構中的棧，地址由高到低。 |
| 堆區(heap) | 由`malloc`/`new`分配的空間，地址由低向高增長，需要程序員手動釋放(`free`/`delete`)，否則程序結束時可能由OS回收。堆區與數據結構中的堆不同，分配方式類似於鏈表。 |
| 全局/靜態變量區(static) | 全局變量和靜態變量存儲在此區域，已初始化的全局變量和靜態變量在一塊區域，未初始化的全局變量和未初始化的靜態變量在相鄰的另一塊區域，程序結束後由系統釋放。 |
| 文字常量區 | 常量字符串存放在此區域，程序結束後由系統釋放。 |
| 程序代碼區 | 存放函數體的二進制代碼。 |

舉例：

```c
int a = 0; // 全局初始化區
char* p1; // 全局未初始化區

int main()
{
    int b; // 棧區
    char s[] = "abc"; // 棧區
    char* p2; // 棧區
    char* p3 = "123456"; // "123456"在常量區，p3在棧區
    static int c = 0; // 全局/靜態已初始化區
    p2 = (char*) malloc(10); // malloc分配得來得10字節的區域就在堆區
    strcpy(p1, "123456"); // "123456"放在常量區，編譯器可能會將它與p3所指向的"123456"優化到一塊區域
    return 0;
}
```

## 數值變量初始化
C/C++對於全局/靜態區域定義的未賦初值數值類型字段會自動初始化為`0`，
但對於棧區的局部變量字段則為未定義行為：

```c
static int a; // 全局未初始化區，自動初始化為0
int b; // 全局未初始化區，自動初始化為0

int main()
{
    int i; // 棧區，未定義行為
    static int j; // 全局未初始化區，首次進入函數自動初始化為0
    return 0;
}
```

## 全局變量/全局靜態變量初始化順序
C/C++在在一個編譯單元內遵循下列初始化順序：

1. Zero Initialization（零值初始化，C/C++通用）

    所有未顯式賦初值的全局變量/全局靜態變量進行零值初始化。

2. Static Initialization（靜態初始化，C/C++通用）

    以給定的常量表達式初始化顯式設定初值的全局變量/全局靜態變量；
    該初始化發生在所有代碼執行之前。

3. Dynamic Initialization（動態初始化，僅C++）

    C++支持動態初始化，全局變量/全局靜態變量可通過代碼塊（構造函數/全局函數/非常量表達式等）進行初始化；
    全局初始化發生在main函數執行之前。

    C語言**不支持**動態初始化，僅可使用compile-time constant（編譯時常量）進行初始化。

全局初始化順序保證：

- 在一個編譯單元內，按照定義順序進行初始化
- 在不同編譯單元間，初始化順序**無保證**，
動態初始化時依賴其它編譯單元的全局變量，為**未定義行為**，可能導致錯誤

## 局部靜態變量初始化順序
局部靜態變量初始化發生在函數首次調用時。

與全局變量/全局靜態變量的初始化的限制類似，
C語言僅支持使用常量表達式初始化局部靜態變量，
C++支持使用代碼塊初始化靜態局部變量（動態初始化）。

自`C++11`開始，局部靜態變量會保證**線程安全**
（多線程同時嘗試初始化同一局部靜態變量時，保證僅初始化一次）。
該特性可被用於實現支持懶加載的**單例模式**：

```c++
template <class T>
T& singleton()
{
    static T t;
    return t;
}
```

對於需要複雜構造參數的類型，亦可使用Lambda表達式特性編寫複雜初始化邏輯：

```c++
Xxx& singleton()
{
    static Xxx x{[]{
        ...
        return ...
    }};
    return xxx;
}
```



# C/C++中函數定義的區別
C語言不支持**函數重載**而C++支持，導致C/C++對無參函數的意義有不同的解釋。

參數名：

- 在C語言中，函數的定義中，參數**不能**只寫參數類型而沒有參數名。
- 在C++中，函數的定義裏，參數**允許**只寫參數類型而沒有參數名。

空參列表含義：

- 在C語言中，`function()`參數表爲空代表這個函數可以接收**任意個**參數，
而`function(void)`才代表函數不接收參數，因此，對於任意參數的函數，
都可以用空參數表的形式做函數聲明（C語言不支持函數重載，一個函數名對應的函數實現只會有一個）。
- 在C++中，`function()`參數表爲空與`function(void)`意義相同，
都表示該函數**不接收任何參數**。而且C++支持**函數重載**，
一個函數名根據參數不同可以有多個實現，因此，在C++中函數聲明必須與函數定義的原型**完全相同**。



# `static`關鍵字
C語言中的`static`功能近似於OOP語言中的private，
被修飾的內容僅在編譯單元內部可訪問，不可被鏈接的其它目標訪問。

static修飾函數內的**局部變量**，則成爲**靜態**局部變量，
靜態局部變量**不在**棧區分配內存而是在**全局變量區**中分配空間；
靜態局部變量在首次調用所在函數時進行初始化，
靜態局部變量不會隨着函數運行結束而被**自動釋放**，下次執行該函數，
該函數內部的靜態局部變量不會重新分配空間，因此依舊使用上次函數執行結束時的值；
該特性可被用於實現**單例模式**。

static用在源碼文件中，修飾**函數/全局變量**，
表示不導出該函數/全局變量的符號（即該內容僅限源碼文件對應的編譯單元內部使用）。

應避免在頭文件中使用static定義全局變量和函數，
會導致不同編譯單元內擁有看似名稱相同但實際獨立的全局變量/函數，
不同編譯單元內的頭文件static全局變量修改對其它編譯單元無效。

頭文件static全局變量問題示例：

頭文件`test.h`：

```c
#pragma once

static int fuckccp = 1984;

void do_fuckccp();
```

源碼文件`test.c`：

```c
#include "test.h"
#include <stdio.h>

void do_fuckccp()
{
    printf("Before fuckccp: %d\n", fuckccp);
    fuckccp = 8964;
    printf("After fuckccp: %d\n", fuckccp);
}
```

源碼文件`main.c`：

```c
#include "test.h"
#include <stdio.h>

int main()
{
    do_fuckccp();
    printf("Main fuckccp: %d\n", fuckccp);
    return 0;
}
```

編譯輸出（macOS Sonoma 14.4.1 x86_64 && Apple clang version 15.0.0）：

```
$ cc test.h test.c main.c
$ ./a.out
Before fuckccp: 1984
After fuckccp: 8964
Main fuckccp: 1984
```

由輸出結果可知，調用其它編譯單元的函數對頭文件中的全局靜態變量的修改對本編譯單元無效。

## static（C++）
在C++中，除了繼承自C的static用法，還可以用於修飾類的成員，
表示**靜態成員**，靜態成員只能初始化一次，全局僅有一個實體。

靜態成員不依賴於類的實例而存在，無需進行類實例化即可直接通過類名進行訪問。
一個類無論有多少實例，這些實例的靜態成員均指向同一塊內存區域
（即同一個類的靜態成員靜態成員變量實際上是同一個）。

靜態成員之間能夠相互訪問，沒有this指針，靜態成員函數不能訪問非靜態成員函數和非靜態數據成員。
由於沒有this指針的額外開銷，因此靜態成員函數與類的普通成員函數相比速度上會有少許的增長。

靜態成員函數在類內聲明時使用static關鍵字，在類外定義時不再使用static關鍵字。
靜態成員變量必須在類外初始化，在類中的靜態成員變量定義僅等同於聲明，
若靜態成員變量沒有在類外進行初始化，引用時會出現**未定義引用**錯誤。
普通靜態成員變量不能進行類內初始化，只有`const static`（常靜態成員變量）才能進行類內初始化。

靜態成員變量初始化的格式爲：

```cpp
數據類型 類名::靜態成員變量名; // 使用默認構造器
數據類型 類名::靜態成員變量名(參數...); // 顯式使用構造函數初始化靜態變量
數據類型 類名::靜態成員變量名{參數...}; // 統一初始化，使用構造函數初始化靜態變量
數據類型 類名::靜態成員變量名 = 值; // 靜態成員變量的初始化需要在全局區域，不能在函數體/類內
```

類的靜態成員變量有兩種訪問形式：

```cpp
類實例名.靜態成員變量名;
類名::靜態成員變量名;
```

類的靜態成員變量在邏輯上依然受到類的訪問權限的制約，
`private`、`protected`的靜態成員變量依然無法在類外訪問，但可以在類外賦初值。

注意事項：

- 普通類的靜態成員變量在類內僅僅是**聲明**了該變量，要使用該成員變量還需要在全局區域進行定義。
該定義**不能**寫在頭文件中，否則一旦該頭文件被**多個**源碼文件包含，
鏈接時會出現`multiple definition of ***`（多重定義）錯誤。
- **靜態成員變量定義不能寫在頭文件中**的規則僅僅對於普通類有效，對於**模板類**則不再適用。
模板類的靜態成員定義同樣需要寫在頭文件內。
模板類的編譯模型與常規代碼不同，在定義時並不實際生成代碼，
只有在被其它代碼引用時編譯器纔會爲其生成對應的模板代碼，
因而模板類在頭文件中定義靜態成員不存在多重定義問題。
同時大多數編譯器**不支持**`export`分離模板定義模型（如`g++`、`clang++`等），
因此模板類的定義**必須**寫在頭文件內（**模板特化**情形除外）。

示例：

頭文件`test.h`：

```cpp
#pragma once

class A
{
public:
	static int a;
	static int b;
};

int A::a = 1; // 錯誤，普通類頭文件內進行靜態成員定義造成多重定義錯誤

template <class T>
class B
{
public:
	static int a;
	static int b;
	static int c;
	static int d;
};

template <class T>
int B<T>::a; // 正確，在頭文件中定義模板類的靜態成員
```

源碼文件`test.cc`：

```cpp
#include "test.h"

int A::b = 2; // 正確，普通類的靜態成員在代碼文件中定義，而非頭文件

template <class T>
int B<T>::b = 2; // 錯誤，模板類的靜態成員在代碼文件中定義由於模板編譯模型無法找到，提示"未定義的引用"

template <>
int B<int>::c = 3; // 正確，模板特化定義可以寫在源碼文件中

template <>
int B<int>::d; // 錯誤，模板特化定義必須使用顯式定義（使用賦值操作符/構造函數等）
```

入口源碼文件`main.cc`：

```cpp
#include "test.h"

#include <iostream>

using namespace std;

int main(void)
{
	cout << A::a << endl;
	cout << A::b << endl;

	cout << B<int>::a << endl;
	cout << B<int>::b << endl;
	cout << B<int>::c << endl;
	cout << B<int>::d << endl;

	return 0;
}
```

編譯輸出(G++ 6.1.1 && ArchLinux x64)：

```
/tmp/ccSLIJuT.o:(.data+0x0): multiple definition of `A::a'
/tmp/ccAkJrHZ.o:(.data+0x0): first defined here
/tmp/ccAkJrHZ.o: In function `main':
main.cc:(.text+0x63): undefined reference to `B<int>::b'
main.cc:(.text+0xa1): undefined reference to `B<int>::d'
collect2: error: ld returned 1 exit status
```



# `const`關鍵字
const關鍵字用於表示字段不可變。

## const用於變量初始化
在C語言中，const變量在定義時可以不初始化，編譯器會自動爲其初始化爲一個默認值。
在C++中，const變量在定義的同時必須顯式地初始化，定義沒有初始化的const變量將無法通過編譯。

在C++98中，const變量在類中定義時，則初始化需要放在構造函數的初始化列表中。
在C++11中，成員變量初始化可以直接在類中進行，const成員變量也一樣可以在類中初始化。

## const變量作爲數組長度
對於以下代碼：

```cpp
const int length = 10;
int array[length];
```

在部分C語言編譯器中會報錯，但在C++中正確。
`C99`開始支持變量作爲數組長度定義，但不是所有編譯器都支持這個特（GCC能夠支持）。
`ANSI C`中，數組的長度只能由常量定義，即使`const`變量的值不會發生變化，但仍然**不是**常量。



# 運算精度
在`C/C++`運算中，需要注意精度的轉換的時機，如下表達式：

```c
double num = 1 / 3;
printf("%f\n", num);
```

輸出結果(GCC 5.3.0 && ArchLinux x64)：

```
0.000000
```

- 進行除法運算的兩個操作數皆爲**整型**，`1 / 3`的結果爲`0`，運算結束之後轉換爲**雙精度浮點型**，精度提升，
但提升是以整型計算的結果`0`作爲原始值的，因而提升之後的結果爲`0.000000`。
- 對於結果可能爲浮點數的運算，至少需要一個操作數爲浮點型才能保證運算結果正確。



# 8進制與16進制
在C/C++中，表示8進制與16進制數值需要在數值前加前綴：

- 表示**8進制**數值，在數值前加`0`：

	示例：

	```c
	int num0 = 011; // 等於10進制數 "9"
	// int num1 = 089; // 編譯報錯，8進制數中不能出現大於等於 "8" 的數值
	```

- 表示**16進制**數值，在數值前加`0x`：

	示例：

	```c
	int num0 = 0x11; // 等於10進制數 "17"
	int num1 = 0xab; // 等於10進制數 "171"
	// int num2 = 0xgh; // 編譯報錯，16進制數中不能出現大於等於"f"的數值
	```

C/C++中，**沒有**提供表示2進制數值字面量的方式。



# sizeof 運算符
`sizeof`運算符**不是**函數，在**編譯時**生效。
指針與數組的區別之一就是使用sizeof返回的大小不同：

- 對於數組而言，雖然數組名可以代表數組的首地址，
`sizeof`對於指針返回的大小總是`8`(64bit OS)或是`4`(32bit OS)。
- 將**數組名**作爲參數返回的是`數組類型 * 元素個數`的大小。

示例：

```cpp
#include <stdio.h>

int main(void)
{
	char* str = "12345";
	char chars[5] = "12345";
	printf("%d %d\n", sizeof(str), sizeof(chars));
	return 0;
}
```

輸出結果：(GCC 4.9.1 && ArchLinux x64)

```
8 5
```

由結果可知，`str`的類型爲`char*`，是指針，大小爲`8`，`chars`類型爲`char[]`，大小爲`5 * 1 = 5`。



# 列表初始化
在C/C++中允許直接使用花括號進行初始化。

## 數組初始化
在C/C++中，使用花括號可以在數組定義時進行初始化，示例：

```c
type array_name[] = { value0, value1, ... }; //由初始化內容決定數組長度
type array_name[size] = { value0, value1, ... }; //指定數組長度
```

## designated initializers (C99)
在`C99`中，擴充了花括號初始化數組的功能，允許指定範圍進行初始化(`designated initializers`)，
但C++中沒有引入此特性，以下代碼只能在**C編譯器**下編譯通過：

```c
// 實際數組內容爲" 1,1,1,1,2,2,0,3,3,3 "，沒有初始化的部分依然爲默認值
int nums[10] =
{
	[0 ... 3] = 1,
	[4 ... 5] = 2,
	[7 ... 9] = 3
};

struct Student
{
	int class;
	int grade;
};

// 指定範圍初始化用在結構體中，數組長度由初始化語句推斷爲6
struct Student students[] =
{
	[0 ... 3].class = 1,
	[4 ... 5].grade = 2
};
```

## 二維數組初始化
在C/C++中，多維數組可以直接使用花括號初始化。
二維數組的定義示例：

```c
類型 數組名[行數][列數];
```

二維數組在定義同時初始化則可以省略第一維的大小(只需要設置列大小)。
示例：

```c
類型 數組名[][列數] = { /*初始化內容*/ };
```

多維數組在初始化時可以按行初始化（嵌套花括號），也可以直接順序初始化（只使用一次花括號）。
示例：

```c
// 四種方式結果完全相同
char s0[][3] = { "abc", "def" }; // 實際大小爲[2][3]
char s1[][3] = { 'a', 'b', 'c', 'd', 'e', 'f' };
char s2[2][3] = { {'a', 'b', 'c'}, "def" }; // 按行初始化
char s3[2][3] = { '1', '2', '3', '4', '5', '6' }; // 順序初始化
```

## 類/結構體列表初始化 (C++98)
對於`class`和`struct`而言，在`C++98`中，若成員變量皆爲**公有成員**且**未手動定義**構造函數時，
可以使用列表進行初始化，示例：

```cpp
struct S
{
	int num1;
	int num2;
	int num3;
};

class C
{
public:
	int num1;
	int num2;
	int num3;
};

int main(void)
{
	S s = { 1, 2, 3 };
	C c = { 1, 2, 3 };

	return 0;
}
```

帶有**非公有變量**的結構/類不能使用列表初始化，帶有自定義構造函數的結構/類也不能使用列表初始化：

```cpp
struct S
{
	// 編譯時報錯，提示"error: in C++98 ‘s’ must be initialized by constructor, not by ‘{...}’"
	S(int num1, int num2, int num3) : num1(num1), num2(num2), num3(num3) {};

	int num1, num2, num3;
};

class C
{
public:
	int num1;

// 編譯報錯，錯誤信息：
// error: could not convert ‘{1, 2, 3}’ from ‘<brace-enclosed initializer list>’ to ‘C’
protected:
	int num2;

private:
	int num3;
};

int main(void)
{
	S s = { 1, 2, 3 };
	C c = { 1, 2, 3 };

	return 0;
}
```

## 統一初始化 (C++11)
在C++11中，新增了**統一初始化**特性，帶有非公有成員和自定義構造函數的類同樣可以使用列表初始化，
只需要列表參數與構造函數相匹配即可：

```cpp
// C++11標準下編譯成功
// C++98標準下編譯出錯，錯誤信息：
// error: in C++98 ‘s’ must be initialized by constructor, not by ‘{...}’
struct S
{
	S(int num1, int num2) : num1(num1), num2(num2), num3(num2) {}

	int num1;

protected:
	int num2;

private:
	int num3;
};

int main(void)
{
	S s = { 1, 2 };
	return 0;
}
```

統一初始化特性還可以用在動態分配數組上，並且用於賦值的等號也可以省略：

```cpp
int a[3] { 1, 2, 3 };
int* b = new int[3] { 1, 2, 3 };
```

STL中多數容器都已支持了列表初始化：

```cpp
std::vector<int> v { 1, 2, 3 };
std::map<int, int> m { {1, 6}, {2, 6}, {3, 6} };
```

即使是單個變量，也可以使用列表初始化：

```cpp
int a { 100 };
```

在函數參數中使用列表能夠防止精度下降：

```cpp
auto func = [](int a) {};

// 正常
func(100.0);
// 編譯報錯，錯誤信息：
// error: narrowing conversion of ‘1.0e+2’ from ‘double’ to ‘int’ inside { } [-Wnarrowing]
func({ 100.0 });
```

在C++11中，使用了**類內初始化**特性的類若未顯式定義有參構造函數，則**不能**使用統一初始化特性：

```cpp
#include <iostream>

using namespace std;

struct Test
{
	int num = 0;
	string name = "";
};

int main(void)
{
	Test t { 2333, "2333" };
	return 0;
}
```

`GCC 7.2.0`版本下，使用`g++ -std=c++11`編譯，得到如下錯誤輸出：

```
init.cc: In function 'int main()':
init.cc:13:24: error: no matching function for call to 'Test::Test(<brace-enclosed initializer list>)'
  Test t { 2333, "2333" };
                        ^
init.cc:5:8: note: candidate: constexpr Test::Test()
 struct Test
        ^~~~
init.cc:5:8: note:   candidate expects 0 arguments, 2 provided
init.cc:5:8: note: candidate: Test::Test(const Test&)
init.cc:5:8: note:   candidate expects 1 argument, 2 provided
init.cc:5:8: note: candidate: Test::Test(Test&&)
init.cc:5:8: note:   candidate expects 1 argument, 2 provided
```

`C++ 14`中則無此限制，使用`g++ -std=c++14`編譯，正常編譯通過。

## std::initializer_list<T> (C++11)
自定義類型可以通過使用`std::initializer_list<T>`類型做爲構造方法參數來支持**變長**的統一初始化參數表：

```cpp
#include <iostream>
#include <initializer_list>

template <class T>
class Init
{
public:
	Init(const std::initializer_list<T>& l)
	{
		for (const T& i : l)
			std::cout << i << " ";
		std::cout << std::endl;
	}
};

int main(void)
{
	Init<int> { 1 };
	Init<int> { 1, 2, 3 };
	Init<std::string> { "One", "Two", "Three" };
	return 0;
}
```

輸出結果：

```
1
1 2 3
One Two Three
```

當存在多個符合初始化列表簽名的構造方法時，優先調用使用`std::initializer_list<T>`類型做爲參數的構造方法：

```cpp
#include <iostream>
#include <initializer_list>

class Init0
{
public:
	Init0(int num0, int num1)
	{
		std::cout << "Init0: Call for normal..." << std::endl;
	}
};

class Init1
{
public:
	Init1(const std::initializer_list<int>& l)
	{
		std::cout << "Init1: Call for initializer_list..." << std::endl;
	}
	Init1(int num0, int num1)
	{
		std::cout << "Init1: Call for normal..." << std::endl;
	}
};

int main(void)
{
	Init0 { 1, 2 }; //可用統一初始化語法調用普通構造方法
	Init1 { 1, 2 }; //當存在接收std::initializer_list<T>參數的構造方法時，統一初始化語法優先調用該構造方法

	return 0;
}
```

輸出結果：

```
Init0: Call for normal...
Init1: Call for initializer_list...
```



# 結構體對齊
出於性能考慮，多數編譯器會對結構體內的成員變量進行大小對齊。
由於結構體對齊，結構體的大小與變量大小之和有時並不相等。
在`GCC/Clang`等編譯器中，默認結構體按照內部的**最大**的成員變量的長度來進行對齊。

即使結構體內的變量長度未達到最大成員的長度，也會佔有該大小的空間。
多個小長度的成員能夠共存在同一片對齊區域內。但若出現了最大長度的成員變量，則下一個成員重新對齊。

示例：

```cpp
struct A
{
	int a;
	char b;
};
```

結構體`A`大小爲`8`。
`A`按照最大的成員變量的類型`int`的長度進行對齊，變量`b`雖然只有`1`個字節，
但實際佔用`4`個字節的大小，因而結構體的大小爲`8`個字節。

```cpp
struct B
{
	int a;
	char b;
	char c;
};
```

結構體`B`大小依舊爲`8`。
`B`中成員變量`b`按照`int`型的`4`個字節進行對齊，但並未將4個字節的空間完全使用，故變量`c`繼續使用這`4`個字節的空間。

```cpp
struct C
{
	char b;
	int a;
	char c;
};
```

結構體`C`的大小爲`12`。
變量`b`按照`int`型的`4`個字節進行對齊，但下一個變量`a`也爲`int`型，需要佔用`4`個字節，`b`的剩餘空間不夠使用，
`a`變量便會再佔用`4`個字節的空間，而由於`a`變量是完全使用對齊空間的，下一個變量`c`則需要重新分配對齊空間，
又佔用`4`個字節的空間，故結構體`C`的大小爲`4 + 4 + 4 = 12`。

## 指定結構體對齊大小
在一些特殊的場景下(如結構體需要轉換爲字節流時)，需要使用緊湊內存佈局，
不需要爲性能而強制對齊結構體，此時可以指定結構體的對齊方式。

`GCC/Clang/MSVC`等編譯器均支持預處理指令`#pragma pack(n)`，該指令可指定結構體對齊數值：

```c
#pragma pack(1) // 結構體大小按1對齊

struct A
{
	int a;
	char b;
}; // 結構體大小爲5

#pragma pack(2) // 結構體大小按2對齊

struct B
{
	int a;
	char b;
}; // 結構體大小爲6

#pragma pack() // 無數值時表示後續內容恢復默認對齊方式
```

`GCC/Clang`編譯器支持在結構體定義後追加擴展指令`__attribute__ ((packed))`，可取消結構體對齊：

```c
// 編譯器爲 GCC/Clang
struct A
{
	int a;
	char b;
} __attribute__((packed)); // 結構體大小爲5
```

`MSVC`編譯器支持在結構體定義前使用專屬編譯器指令`__declspec(align(n))`，
可部分調整編譯器的對齊大小，但不能小於默認對齊大小：

```c
// 編譯器爲 MSVC

__declspec(align(16)) // 對齊大小數值必須爲2的冪
struct A
{
	int a;
	char b;
}; // 結構體大小16，對齊大小被提升至16

__declspec(align(1)) // 對齊大小小於默認對齊大小，不生效
struct A
{
	int a;
	char b;
}; // 結構體大小8，設置的對齊大小未生效
```



# 變長參數
C語言不支持**函數重載**，但是依然可以定義變長參數函數，使用`...`符號代表可變參數表。
不能定義一個參數僅爲`...`的函數，一個函數如果接受變長參數，則至少需要有一個確定參數。

典型的變長參數函數定義：

```c
type function(type arg, ...);
```

標準庫中存在大量變長參數函數，如打印輸出函數`printf()`就可以接收變長參數。

## 自定義變長參數函數
自行編寫變長參數函數可以使用`stdarg.h`頭文件中提供的宏，示例：

```c
#include <stdarg.h>
void va_start(va_list ap, argN);
void va_copy(va_list dest, va_list src);
type va_arg(va_list ap, type);
void va_end(va_list ap);
```

使用方法：

1. 先要創建`va_list`變量用於記錄位置，然後使用`va_start()`宏初始化`va_list`變量，參數`argN`爲函數第一個參數。
1. 通過`va_arg()`獲取當前`va_list`的下一個參數值，`type`爲下一個參數的類型。每次運行這個宏，`va_list`會隨之下移一個位置。
1. 當所有變量都讀出之後可以關閉`va_list`，使用`va_end()`宏。

示例：

```c
#include <stdio.h>
#include <stdarg.h>

int get(int s, ...)
{
	va_list arg;
	va_start(arg, s); //初始化arg
	printf("%d ", va_arg(arg, int)); //第一次運行宏得到第二個參數的值
	printf("%d ", va_arg(arg, int)); //第二次運行宏得到第三個參數的值
	va_end(arg);
	return 0;
}

int main(void)
{
	get(5, 30, 40);
	return 0;
}
```

## 通過地址獲取變長參數內容
除了使用`stdarg.h`頭文件中所提供的宏來獲取變長參數內容之外，還可以直接以取地址的方式來獲取變長參數的內容。

在C語言中，函數的參數壓棧的順序是**從右向左**，而棧底爲高地址，棧頂低地址，因此靠後的參數先進棧爲高地址，靠前的參數後進棧爲低地址。
與結構體對齊類似，參數在壓棧過程中編譯器會對其進行內存對齊，因此在計算變長參數的偏移地址時需要考慮參數類型的對齊情況。

在不同平臺下，變量類型所佔字節數是不同的：

- 在`Windows x86`中，`int`、`char`、`float`、`long`、`指針`以及爲未指定類型的整數等，以4個字節對齊。
`double`、`long long`以及未指定類型的小數等以8個字節對齊。
- 在`Unix x86_64`中，除了`long double`之外，大部分類型都以8個字節對齊。

示例：

```c
#include <stdio.h>

void get(float a, ...)
{
	printf("%f %c %d\n", a, *(char*)(&a + 1), *(int*)(&a + 2));
}

int main(void)
{
	get(9.9, 'b', 888);
	return 0;
}
```

輸出結果：(VS 2013 && Windows 8.1 x64)

```
9.900000 b 888
```

輸出結果：(GCC 5.1.0 && ArchLinux x64)

```
9.900000   98
```

從結果不難看出，Unix環境下輸出的參數內容產生了偏差，是由於數據不同平臺數據類型長度不同，內存對齊方式不同導致的。
要使Unix環境下能夠顯示參數，修改`printf()`函數中的內容：

```c
printf("%f %c %d\n", a, *(char*)((long*)&a + 1), *((long*)&a + 2));
```

即可在`Unix x86_64`環境下正常輸出結果。

## 變長參數宏
`C99`中規定了宏可以像函數一樣擁有可變參數表。
使用`...`代表可變參數表，使用`__VA_ARGS__`代表傳入的參數內容。

以標準庫中的`printf()`函數爲例，爲`printf()`函數定義具有可變參數的宏，示例：

```c
#define PRINTF(str, ...) printf(str, __VA_ARGS__) //MSVC中允許空的可變參數表，GCC中不允許
```

對於`GCC/Clang`等編譯器，支持如下擴展語法：

```c
#define PRINTF(str, args...) printf(str, args) //不支持非空可變參數表
```

可變參數可被命名，直接通過名稱獲取可變參數。

可變參數不可爲空，否則編譯出錯。
若允許空的可變參數表，獲取可變參數表時名稱前添加`##`操作符(在可變參數非空時才進行宏連接)：

```c
// 支持可空可變參數表
#define PRINTF(str, args...) printf(str, ##args) //GCC/Clang
#define PRINTF(str, ...) printf(str, ##__VA_ARGS__) //MSVC/GCC/Clang
```



# 自增自減運算符的優先級
自增自減運算符根據出現位置的不同，可能在語句之前或語句之後執行，且對整個語句生效(部分編譯器約定不同，比如`Clang`)。

例如：

```c
int a = 0;
printf("%d %d\n", a, ++a);
```

輸出結果爲：

```
1 1	(GCC 4.9.2 && ArchLinux x64)
0 1	(Clang 3.5.1 && ArchLinux x64)
```

在`Clang`中會給出警告：`warning: unsequenced modification and access to 'a'`，即無序地修改和存取變量a。

```c
int a[5] = { 1, 2, 3, 4, 5 };
int b[5] = { 0 };
int* c = a;
int* d = b;
while (*d++ = *c++);
for (int i = 0; i < 5; i++)
	printf("%d ", b[i]);
```

輸出結果：

```
1 2 3 4 5
```

GCC與Clang輸出相同，但在Clang中會給出警告，
`warning: using the result of an assignment as a condition without parentheses [-Wparentheses]`，
即僅使用了條件任務而沒有使用括號(未使用循環體)。

`while (*d++ = *c++);`的作用是複製數組內容。
先將指針`c`指向的內容取出即`*c`，複製到指針d指向的內容即`*d`，然後執行自增運算符，左右的指針都自增1位，
同時指向數組下一個元素，然後while語句判斷`*d`的內容。
由於在C/C++中，非0數值均被視爲true，故循環可繼續執行，直到數組結束，指針指向空內容爲止。

用`while (*d++ = *c++);`進行復制內容時需要注意，如果複製的內容中含有0，則複製會提前結束。
此類語句還可以用來複制**字符數組**，字符串以`\0`結尾，複製到字符串結尾自動停止。



# 編譯器自動生成的成員函數
一個沒有任何內容的空類並不爲空，編譯器會自動爲其增加成員：

1. 空構造函數。
1. 複製構造函數。
1. 空析構函數。
1. 重載等號爲複製對象。
1. 取址運算符重載(一對，帶`const`/不帶`const`)。

這些函數只有在第一次被調用時，纔會被編譯器創建。
所有自動生成的成員函數都是`inline`和`public`的。

在C++11中，若類未定義自己的複製構造函數，則還會生成默認的**移動構造函數**和並重載等號爲**移動賦值運算符**。

若自行定義了複製構造函數而未定義移動構造函數，則使用右值對象做參數實例化時，
會調用複製構造函數(`const左值引用`能夠綁定在右值對象上，但如果存在移動構造函數則會優先匹配接收右值的移動構造函數)。

默認情況下，由編譯器生成的默認複製構造函數以及重載等號都是**淺複製**，
即對於指針變量，只會複製指針中保存的地址，而不會複製指針指向的內存區域。
若需要深複製，則需要自行實現這些函數以改變複製行爲。

一個空類：

```cpp
class Empty { };
```

實際上等價於：

```cpp
class Empty
{
public:
	Empty(); //默認的空構造函數
	Empty(const Empty&); //複製構造函數
	Empty(Empty&&); //C++11，移動構造函數
	~Empty(); //默認的析構函數
	Empty* operator&(); //重載取地址運算符
	const Empty* operator&() const; //帶const的取址運算符
	Empty& operator=(const Empty&); //重載等號爲對象內容複製
	Empty& operator=(Empty&&); //C++11，重載等號爲移動對象
};
```

## 控制默認生成的成員函數
在C++11中，引入了`delete`、`default`關鍵字，用於控制默認成員函數的生成。

`delete`用於禁止合成某類默認成員函數：

```cpp
class Test
{
public:
	Test() = delete; //禁止默認的構造函數
	Test(const Test&) = delete; //禁止默認的複製構造函數
	... 其它類似
};
```

在類定義時，若手動定義了有參構造函數，則編譯器不會再爲之合成默認的無參構造函數。
若需要保留默認的無參構造函數，則使用`default`關鍵字，示例：

```cpp
class Test
{
public:
	Test(int) {};
	Test() = default; //使用default關鍵字合成默認無參構造函數
};
```

在某些情況下，由編譯器生成的空參構造函數相比編碼者手動編寫的更加高效。



# 繼承
C++中的繼承分爲公有繼承`public`、保護繼承`protected`以及私有繼承`private`，不顯式指定繼承方式時默認爲**私有繼承**。

- **公有繼承**繼承父類的可繼承成員的同時**不改變**這些成員在子類中的訪問權限，
但**保護繼承**、**私有繼承**會將繼承來的成員限制在子類中的訪問權限。
- 公有繼承類似於其他高級語言(Java/C#)中的繼承，**只有**公有繼承能夠表達出其他語言中的繼承關係(子類來源於父類)。
- 私有繼承與保護繼承的類可以正常實現一些OOP特性如`override`、`虛函數`等，但其子類實例**不**支持**向上轉型**。
- C++在發生**重寫**行爲時，**不強制**要求子類的重寫函數訪問權限要大於等於父類，在發生**向上轉型**時，
父類的虛函數如果被子類重寫，則調用子類的實現，不受子類的重寫函數的訪問權限影響(即使子類重寫函數是私有的，父類實例一樣調用子類重寫的實現)。

示例：

```cpp
// 私有繼承
#include <iostream>

using namesapce std;

class A
{
public:
	virtual int get() { return 100; }
};

class B : A
{
private:
	int get() { return A::get() + 100; }
};

int main(void)
{
	A* a = new B; //報錯，提示 " 'A' is an inaccessible base of 'B' "
	return 0;
}

// 向上轉型訪問子類私有實現
#include <iostream>

using namesapce std;

class A
{
public:
	virtual int get() { return 100; }
};

class B : public A
{
private:
	int get() { return A::get() + 100; }
};

int main(void)
{
	A* a = new B;
	cout << a->get() << endl; //正確，調用子類實現，輸出200
	cout << B().get() << endl; //錯誤，提示"within this context"
	return 0;
}
```



# 指針運算
在C/C++中，對指針進行加減運算時，並不是直接對地址的大小加上數值得到新的地址，
而是原地址加上由`操作數 * 指針所指向的內容的類型大小`得到的偏移量計算出的地址。

示例：

```c
#include <stdio.h>

int main(void)
{
	long* a = (long*)0x1; //內存地址賦值給指針之前需要進行強制類型轉換，否則編譯器不知道內存的類型
	printf("%p\n", a + 1); //打印指針使用%p，會以"0x...."的格式輸出
	int b[] = { 1, 2, 3 };
	printf("%d, %d", *(b + 1), *((int*)(&b + 1) - 1));
	return 0;
}
```

輸出結果：(GCC 4.9.2 && ArchLinux x64)

```
0x9
2, 3
```

由例子中不難看出，`a + 1`代表的地址不是簡單地將`a`的地址`0x1`加上`1`，
而是`a`的地址加上指針所指向的數據類型`long`的大小(8個字節)乘以操作數`1`得到的值`0x9`。
對於數組`b`，單獨使用數組名稱代表的是數組首元素的地址`&b[0]`，`b + 1`代表的是`b[0]`的下一個元素`b[1]`，
而`&b`代表的是整個數組的首地址，雖然二者`b == &b`的值相同，但意義完全不同，`&b + 1`代表的是b的整個數組結束後的下一個位置。

## 數組名的含義
對於數組名而言，在`sizeof`和**指針加減**兩種操作中分別有不同的含義。

- 使用`sizeof`操作符時，數組名代表**整個數組**，如果用數組名作爲參數，則返回的值爲`數組包含的類型的大小 * 數組數量`。
- 進行地址加減操作時，數組名錶示的是**數組第一個元素的地址**，`數組名 + 1`實際上代表**數組第二個元素的地址**，
而`&數組名`才代表整個數組的**起始地址**，`&數組名 + 1`代表數組**結束**之後的下一個位置。

## 指針數組與數組指針
指針數組是包含多個指針的**數組變量**，語法格式如下：

```c
// []操作符優先級比*操作符高，先於變量名結合，因而變量爲數組類型，數組的內容爲指針
type* point_array[size];
```

數組指針是指向一個數組的**指針變量**，語法格式如下：

```c
// 使用括號令*操作符先於變量名結合，因而變量爲指針類型，指針指向的內容爲數組
type (*array_point)[size];
```

如下代碼所示：

```c
#include <stdio.h>

int main(void)
{
	int num_1 = 1, num_2 = 2, num_3 = 3;

	int array[] = { num_1, num_2, num_3 };
	int* point_array[] = { &num_1, &num_2, &num_3 }; //指針數組
	int (*array_point)[] = &array; //數組指針

	return 0;
}
```



# C++對象模型
在C++中，沒有虛函數的情況下，只有**非靜態數據成員**存儲在類內，
其它的**靜態數據成員、靜態成員函數、非靜態成員函數**都存儲在全局區，增加這些成員**不會**引起類大小的變化。

在有虛函數且多重繼承的情況下，多個父類按照其聲明順序依次排列，而每個類的區域內部先是一個虛表指針(vptr)，
然後是普通成員變量，子類與第一個繼承的父類共用一個虛表，子類的普通成員緊跟在最後一個父類的普通成員之後。

類的成員函數和靜態成員變量實際是全局的，因此類的實例中並不包含這些內容，
使用sizeof計算類的大小時也不會把這些內容計算進去，通過地址訪問類的成員進行地址計算時需要忽略這些成員的大小。

## 成員函數
C++中，普通成員函數(包括靜態成員函數，但虛函數除外)並不是直接存放在類中的，而是像普通的全局函數一樣存放。
成員函數在經過C++編譯器處理後，函數名會被改寫，而函數名就指明瞭該函數的類歸屬以及參數信息。

普通成員函數僅僅是邏輯上存在於類中，成員函數的實際實現並不依賴於類。
空類大小爲1，但向空類中添加任意個普通成員函數，類大小仍然是1。

存在虛函數的情況下，類中會保存有一個虛表指針`vptr`，用於保存類中虛函數的地址，向空類中添加一個**虛函數**，
則類的大小變爲單倍指針大小(虛表指針大小)，增加虛函數的個數，類大小不改變。

## 虛函數
C++中只有虛函數才能被子類重寫`override`，非虛函數會被子類的同名函數隱藏(無論函數原型是否完全相同)。
C++中使用`virtual`關鍵字定義虛函數，虛函數可以只有函數定義而沒有函數實現，沒有函數實現的虛函數稱爲純虛函數，
C++中使用`= 0`或`= nullptr`(C++11新增語法)來表示一個虛函數爲純虛函數(類似於Java和C#中的`abstract`方法)。
擁有一個或以上純虛函數的類稱爲抽象類，抽象類不能被實例化，也不能在構造函數的內容中使用，但C++11之後可以用在構造函數的初始化序列中。

一個函數不能既是虛函數又是靜態函數(`static`和`virtual`關鍵字不能共存)，靜態函數是全局的，無需實例化就能被調用，
不能夠被重寫，不能實現向上轉型調用子類同名方法實現。

虛函數通過一張虛函數表來實現。類實例的最前位置有一個虛表指針`vptr`，指向一張虛函數表，
虛函數表中按聲明順序存放了所有該類的虛成員函數的地址，可以通過該表中的地址調用對應的函數實現。
虛函數表的最後位置多加了一個節點作爲虛函數表的結束標誌，
在VS中，結束標誌是`NULL`，在gcc中用0表示虛函數表結束，用1表示接下來的位置還有別的虛函數表。

在**單繼承無重寫**的情況下，子類對象和父類對象的虛函數按照聲明順序出現在虛函數表中，
子類的虛函數在表中的位置處於父類虛函數之後。
在**單繼承且向上轉型**的情況下，如果父類虛函數被子類重寫，
則父類對象中的虛函數表中存放的虛函數地址會被替換成子類的對應函數地址，以此實現運行時多態。
在**多重繼承**的情況下，子類的對象會按照聲明中的順序生成多個父類虛函數表，子類的成員虛函數放置於**首個父類**的虛函數表中。
多個虛函數表之間不是直接相連的，而是按照繼承順序下的該類中的成員內容完全結束之後纔會開始下一個類的虛函數表。

示例：

```cpp
#include <iostream>

using namespace std;

// 類A有兩個虛函數和一個成員變量，由於內存對齊，類A的大小爲16(虛表大小8，變量對齊到8)
class A
{
	virtual int get(int);
	virtual int get();
	char a = 'A';
};

// 單一繼承的情況
class B : A
{
	virtual int get1();
};

class C
{
	char c = 'C';
	virtual int get();
};

// 多重繼承的情況
class D : A, C
{
	char d = 'D';
	virtual int get2();
};

// 單一繼承併發生override的情況
class E : public A
{
	int get();
};

int A::get(int)
{
	cout << "A::get(int)" << endl;
	return 0;
}

int A::get()
{
	cout << "A::get()" << endl;
	return 0;
}

int B::get1()
{
	cout << "B::get1()" << endl;
	return 0;
}

int C::get()
{
	cout << "C::get()" << endl;
	return 0;
}

int D::get2()
{
	cout << "D::get2()" << endl;
	return 0;
}

int E::get()
{
	cout << "E::get()" << endl;
	return 0;
}

int main(void)
{
	A* a = new E;
	B b;
	D d;

	// 在64bit的Linux中，普通指針的大小爲8B，故需要轉換爲一個佔有8個字節的類型來保存內容，否則可能會發生截斷
	cout << "調用類A的get(int)函數 ";
	((int (*)())*(long*)*(long*)&d)();
	cout << "調用類A的get()函數 ";
	((int (*)())*((long*)*(long*)&d + 1))();
	cout << "調用類D的get2()函數 ";
	((int (*)())*((long*)*(long*)&d + 2))();

	cout << "類A的變量a的值 " << (char)*((long*)&d + 1) << endl;
	cout << "類C的變量a的值 " << *(char*)((long*)&d + 3) << endl;

	// 類D繼承於類A和C，D的虛函數添加到了類A虛表的末尾，因而類D中的變量a處於類C中的變量a的下一個位置
	cout << "類D的變量a的值 " << *((char*)((long*)&d + 3) + 1) << endl;

	cout << "調用類B的get1()函數 ";
	((int (*)())*((long*)*(long*)&b + 2))();
	cout << "調用類C的get()函數 ";
	((int (*)())*(long*)*((long*)&d + 2))();
	cout << "調用類A的get(int)函數 ";
	((int (*)())*((long*)*(long*)&*a))();

	cout << "向上轉型使用A類指針調用類E的get()函數 ";
	((int (*)())*((long*)*(long*)&*a + 1))();

	return 0;
}
```

輸出結果：(GCC 4.9.2 && ArchLinux x64)

```
調用類A的get(int)函數 A::get(int)
調用類A的get()函數 A::get()
調用類D的get2()函數 D::get2()
類A的變量a的值 A
類C的變量a的值 C
類D的變量a的值 D
調用類B的get1()函數 B::get1()
調用類C的get()函數 C::get()
調用類A的get(int)函數 A::get(int)
向上轉型使用A類指針調用類E的get()函數 E::get()
```

輸出結果分析：

`D`類繼承於`A``C`兩個類，生成類兩張虛表，`D`的虛函數`get2`的地址保存在`A`的虛函數表中，位於虛函數表的最後一個位置。

`A`類的大小爲16，`A`類的內容結束後就是`C`的內容，因此`C`的虛表指針地址爲`類實例起始地址 + 16`即`&d + 16`，
用8個字節的`long`型做轉換可以寫成`(long*)&d + 2`，而`D`類自己的變量`a`地址位於類`C`結束位置的下一個位置(類`D`的虛函數在`A`末尾，
故沒有單獨虛表)，同時又因爲類`D`沒有單獨的虛表，則根據結構體長度對齊的原則，類`D`的變量`a`會緊接着類`C`的變量`a`，
即`(char*)((long*)&d + 3) + 1`。

`E`類繼承與`A`，只有一張虛表，通過向上轉型得到的實例`a`中，`E`的`get()`重寫了父類`A`的虛函數`get()`，
`(long*)*(long*)&*a`是虛函數表的首地址，存放是`A`類的第一個成員虛函數`get(int)`，
`(long*)*(long*)&*a + 1`是虛函數表中的第二個內容的地址，地址中存放的原本是類A的第二個虛函數`get()`，
但在向上轉型的實例中，被替換成了子類`E`的`get()`函數的地址。

在多重繼承時，如果繼承的多個父類中都有符合子類函數簽名的虛函數，則子類會將所有符合條件的虛表中的父類虛函數指針替換成子類的函數指針。

在`VS`中運行此段代碼，只會輸出前兩個結果，因爲在VSC編譯器下，多個虛表之間不直接相連，
在類成員結束之後並未直接開始下一個虛表，而是隔着一些特殊的字段並用0進行填充，不能通過直接加減類實例地址來得到下一個虛表地址。



# 參數默認值
C++允許在定義函數是給函數的參數設定**默認值**，在調用這個函數時，如果沒有給出對應參數的值，就會使用默認的參數值。

- 在調用具有默認參數的函數時，如果使用參數了一個參數的默認值，則其它帶有默認值的參數也應該使用默認值，
若不準備使用參數的默認值，則所有帶默認值的參數的默認值都不應該被使用。
- 帶有默認值的函數參數需要連續出現，即一旦有一個參數開始有默認值，
之後的參數都需要有默認值(即帶有默認值的參數與無默認值的參數不能夠交錯出現)。
- 參數的默認值只能在函數的聲明或定義的其中一處指定，不能兩處都指定。
- 參數默認值在定義中指定時，需要注意定義必須寫在該函數被調用前默認參數才能生效，否則依然按照聲明中的無默認值格式調用。
- 帶有默認參數的函數在定義時需要注意不能與重載函數相沖突。
- 函數默認值只在有函數被常規調用時纔有效，如果使用函數指針調用函數則函數默認值無效。

示例：

```cpp
int got(int a = 3);

int got(int a = 3) //編譯報錯，默認參數只能出現在定義或是聲明中的其中一處
{
	return a;
}

int get(int b = 3, int a) //編譯報錯，一旦有一個參數帶有默認值，後面的參數都應擁有默認值
{
	return b;
}

int get(int b = 3)
{
	return b;
}

int get()
{
	return a;
}

int main(void)
{
	get(); //編譯報錯，有兩個函數都符合要求。
	int (*p)(int) = got;
	p(); //編譯報錯，參數過少。
	p(100); //正常。
	return 0;
}
```



# 函數定義嵌套
在C/C++標準中，函數定義必須完全平行、相互獨立，函數定義的內部不能嵌套另一個函數的定義。

`GNU C`擴充了C的語法，在`GCC`中嵌套函數定義是**允許**的行爲(只有`gcc`！`clang`、`clang++`、`g++`並不允許嵌套函數定義！)
以下的代碼在`GCC`中可以順利編譯並得到執行結果：

```c
#include <stdio.h>

int got(int num)
{
	int got(int num)
	{
		return num;
	}
	return got(num);
}

int main(void)
{
	printf("%d\n", got(100));
	return 0;
}
```

輸出結果：(GCC 5.1.0 && ArchLinux x64)

```
100
```



# lvalue reference (左值引用) / rvalue reference (右值引用)
在C++中，`左值(lvalue)`代表**持久性**的對象，`右值(rvalue)`代表**短暫**的對象。
左值可以被**取地址**，右值不能被取地址。
右值在語句結束前沒有綁定一個引用，則會被丟棄。

引用綁定規則：

- **非const左值引用**(`T&`)可以綁定到非const左值。
- **const左值引用**(`const T&`)可以綁定到任意左值和任意右值(無論是否const)。
- **非const右值引用**(`T&&`)可以綁定到非const右值。
- **const右值引用**(`const T&&`)可以綁定到任意右值(無論是否const)。

## rvalue reference (右值引用)
在C++11中加入了**右值引用**的概念。
使用`類型&&`表示引用綁定一個來自**右值**的引用，示例：

```cpp
int&& = 23333;
```

右值引用僅能綁定右值，而右值在語句結束前沒有綁定引用會被銷燬，因而右值可以被安全地**轉移**。

## universal reference (通用引用)
`類型&&`並不總是表示一個**右值引用**，在類型由推斷得到時，表示**通用引用**。
**通用引用**能綁定到任意左值/右值，編譯器根據實際傳入的值類型決定引用類型。

常見的通用引用有如下情形：

- `auto declaration` (auto聲明)

	`auto&&`能綁定任意左值/右值，示例：

	```cpp
	auto&& num0 = 2333; //綁定右值，推斷爲 int&&
	auto&& num1 = num0; //綁定左值，推斷爲 int&
	```

- `function template parameters` (模版函數參數)

	模版函數的參數爲`T&&`形式時，會根據實際傳入參數推斷引用類型，示例：

	```cpp
	template <class T>
	void ref(T&&) { } //模版參數表爲 T&& 形式時，爲通用引用

	int main(void)
	{
		const int& r_ref = 2333;
		int&& l_ref = 2333;

		ref(r_ref); //右值引用 => 左值 => 模版參數類型 T&
		ref(l_ref); //const左值引用 => 左值 => 模版參數類型 T&
		ref(2333); //右值 => 模版參數類型 T&&

		return 0;
	}
	```

	模版函數的返回值爲`T&&`形式並不構成通用引用，示例：

	```cpp
	template <class T>
	T&& ref(T&& t)
	{
		return t;
	}

	int main(void)
	{
		ref(2333);
		return 0;
	}
	```

	編譯出錯，提示：(clang-802.0.42 && macOS 10.12.6)

	```
	ref.cc:4:9: error: rvalue reference to type 'int' cannot bind to lvalue of 	type 'int'
	        return t;
	               ^
	ref.cc:9:2: note: in instantiation of function template specialization 	'ref<int>' requested here
	        ref(2333);
	        ^
	1 error generated.
	```

	模版類的成員函數參數表中帶有`T&&`形式的模版參數時，並不是通用引用。
	模版類在構造時模版參數已經確定，並不由推導得到，示例：

	```cpp
	template <class T>
	class Ref
	{
	public:
		void ref(T&&) { } //使用 int 作爲模版參數時，參數表已被確定爲 void ref(int&&) 故僅能接受右值參數
	};

	int main(void)
	{
		const int& r_ref = 2333;
		int&& l_ref = 2333;

		Ref<int>().ref(r_ref); //編譯報錯，參數類型不匹配(需要右值)
		Ref<int>().ref(l_ref); //編譯報錯，參數類型不匹配(需要右值)
		Ref<int>().ref(2333); //編譯通過

		return 0;
	}
	```

	編譯出錯，提示：(clang-802.0.42 && macOS 10.12.6)

	```
	ref.cc:13:17: error: binding value of type 'const int' to reference to type 'int' drops 'const' qualifier
	        Ref<int>().ref(r_ref);
	                       ^~~~~
	ref.cc:5:14: note: passing argument to parameter here
	        void ref(T&&) { }
	                    ^
	ref.cc:14:17: error: rvalue reference to type 'int' cannot bind to lvalue of 	type 'int'
	        Ref<int>().ref(l_ref);
	                       ^~~~~
	ref.cc:5:14: note: passing argument to parameter here
	        void ref(T&&) { }
	                    ^
	2 errors generated.
	```

## reference collapsing (引用摺疊)
對於參數即爲引用類型的模版函數，若傳入模版參數時使用引用形式的模版參數，則會產生**引用摺疊**。
示例：

```cpp
template <class T>
void test(T& t) { }

test<int&>(...);
```

調用函數時使用`int&`作爲模版參數參數，則理論上參數類型爲`int& + &`，即`int`類型引用的引用(`Reference to Reference`)。
而`C++`不允許`Reference to Reference`，編譯器會將引用進行疊加。
引用疊加遵循以下規則：

```cpp
T& + T => T&
T& + T& => T&
T& + T&& => T&
T&& + T => T&&
T&& + T& => T&
T&& + T&& => T&&
```

實例代碼：

```cpp
#include <iostream>

using namespace std;

template <class T>
void test_(T& t)
{
	cout << "T&" << endl;
}

template <class T>
void test__(T&& t)
{
	cout << "T&&" << endl;
}

int main(void)
{
	int num = 2333;

	test_<int>(num); // T& + T => T& 接收左值
	test_<int&>(num); // T& + T& => T& 接收左值
	test_<int&&>(num); // T& + T&& => T& 接收左值

	test__<int>(2333); // T&& + T => T&& 接收右值
	test__<int&>(num); // T&& + T& => T& 接收左值
	test__<int&&>(2333); // T&& + T&& => T&& 接收右值

	return 0;
}
```

## move semantics (移動語義)
在C++11之前，通過原有對象構造新對象僅有一種方式，即**複製構造函數**，示例：

```cpp
class Type
{
	Type(const Type&);
}
```

複製構造函數中傳入參數爲**const左值引用**(`const 類型&`)，const左值引用綁定的對象可能爲右值，也可能爲左值，
因而無法確定參數對象的生命週期。
在複製構造函數中，爲了實現真正的對象拷貝(深複製)，若原對象中存在指針成員，需要重新申請內存，
並拷貝原對象的指針成員所指向的堆內存。

在C++11之後，新增了**移動語義**。
對於使用**右值**構造對象的場景，可以定義**移動構造函數**：

```cpp
class Type
{
	Type(T&&);
};
```

移動構造函數中傳入參數爲**右值引用**(`T&&`)，右值引用綁定的參數一定爲右值，因而參數的生命週期僅到語句結束，可以被安全地**移動**。
在移動構造函數中，原對象中的所有內容皆可被安全地**轉移**，不必深拷貝，原對象中的指針成員直接複製地址即可。

C++11之前缺少表示右值的方法，無法區分原對象來自左值或是右值，進而無法確定原對象的生命週期。
對於所有原對象，出於安全考慮，都需要**深複製**整個對象，在原對象爲**右值**時，會帶來不必要的開銷。
C++11之後引入了右值引用和移動語義，以右值構建對象時，若對象類型同時定義了複製構造函數和移動構造函數，
會**優先匹配**該類型的移動構造函數，避免複製整個對象帶來的不必要的開銷。

## std::move()
右值引用自身爲**左值**，將右值引用直接作爲參數傳遞時會被作爲左值對待，示例：

```cpp
#include <iostream>

using namespace std;

void ref(int&)
{
	cout << "Left reference." << endl;
}

void ref(int&&)
{
	cout << "Right reference." << endl;
}

int main(void)
{
	int&& r_ref = 2333;
	ref(r_ref);

	return 0;
}
```

輸出結果：(clang-802.0.42 && macOS 10.12.6)

```
Left reference.
```

在傳遞右值引用時需要將其還原爲`右值`才能真正觸發移動構造函數。
C++11提供了`std::move()`函數用於將右值引用轉換爲右值，以`GCC 7.1`爲例，實現如下：

```cpp
/**
 *  @brief  Convert a value to an rvalue.
 *  @param  __t  A thing of arbitrary type.
 *  @return The parameter cast to an rvalue-reference to allow moving it.
*/
template<typename _Tp>
  constexpr typename std::remove_reference<_Tp>::type&&
  move(_Tp&& __t) noexcept
  { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
```

上述實例使用`std::move()`轉移右值引用，即可被真正被視爲右值，示例：

```cpp
#include <iostream>

using namespace std;

void ref(int&)
{
	cout << "Left reference." << endl;
}

void ref(int&&)
{
	cout << "Right reference." << endl;
}

int main(void)
{
	int&& r_ref = 2333;
	ref(std::move(r_ref));

	return 0;
}
```

輸出結果：(clang-802.0.42 && macOS 10.12.6)

```
Right reference.
```

## std::forward
`std::move()`會無視傳入值的左右值類型統一轉換爲右值。
對於需要保留參數左右值類型的場景，應使用`std::forward()`。以`GCC 7.1`爲例，實現如下：

```cpp
template<typename _Tp>
  inline _Tp&&
  forward(typename std::remove_reference<_Tp>::type& __t)
  { return static_cast<_Tp&&>(__t); }

template<typename _Tp>
  inline _Tp&&
  forward(typename std::remove_reference<_Tp>::type&& __t)
  {
    static_assert(!std::is_lvalue_reference<_Tp>::value, "template argument"
    " substituting _Tp is an lvalue reference type");
    return static_cast<_Tp&&>(__t);
  }
```

`std::forward()`傳入左值時返回左值引用類型，傳入右值時返回右值引用類型。
使用`std::forward()`，示例：

```cpp
#include <iostream>

using namespace std;

void ref(int&)
{
	cout << "Left reference." << endl;
}

void ref(int&&)
{
	cout << "Right reference." << endl;
}

int main(void)
{
	int n = 2333;
	int& l_ref = n;
	ref(std::forward<int&>(l_ref));
	ref(std::forward<int&&>(2333));

	return 0;
}
```

輸出結果：

```
Left reference.
Right reference.
```

`std::forward()`在調用時需要寫明模板參數類型，否則無法通過編譯。
可以藉助**通用引用**規則編寫模板函數進行封裝：

```cpp
#include <iostream>

using namespace std;

void ref(int&)
{
	cout << "Left reference." << endl;
}

void ref(int&&)
{
	cout << "Right reference." << endl;
}

template <class T>
void call_ref(T&& t)
{
	ref(std::forward<T>(t));
}

int main(void)
{
	int n = 2333;
	int& l_ref = n;
	call_ref(l_ref);
	call_ref(2333);

	return 0;
}
```

輸出結果：

```
Left reference.
Right reference.
```

`std::forward()`能夠根據參數左右值類型智能地轉化出合適的引用類型，這個特性被稱爲`perfect forwarding`(完美轉發)。

## 注意事項
無論左值引用或是右值引用本身都是左值，因此雖然不能直接對右值取地址，但可以對右值引用取地址。

引用一但綁定就不可更改，因此引用與指針不同，
指針分爲`const 類型名* 指針名`(指向const內容的指針)和`類型名* const 指針名`(自身保存地址不可變的const指針)，
而引用本身一定是不可變的，因此只有`const 類型名& 引用名`(綁定const值的引用)，而沒有真正的const引用，
`類型名& const 引用名`這樣的定義編譯報錯。

舉例：

```cpp
const int& a = 1; // 正確，const左值引用可以綁定到右值
int&& b = 1; // 正確，非const右值引用可以綁定到右值

int& x = 1; // 錯誤，非const左值引用不能綁定到右值
int& x = a; // 錯誤，非const左值引用不能綁定到const左值
int& x = b; // 正確，非const左值引用可以綁定到非const左值
const int& x = std::move(a); // 正確，const左值引用可以綁定到const右值
const int& x = std::move(b); // 正確，const左值引用可以綁定到非const右值
int&& x = std::move(a); // 錯誤，非const右值引用不能綁定到const右值
int&& x = std::move(b); // 正確，非const右值引用可以綁定到非const右值
const int&& x = std::move(a); // 正確，const右值引用可以綁定到非const右值
const int&& x = std::move(b); // 正確，const右值引用可以綁定到非const右值
```

## 成員函數的引用限定
C++11之後，可以在類的成員函數定義之後添加左值引用(&)或右值引用(&&)符號。

- 成員函數的引用限定用於限制函數調用者的值類型(左值/右值)。
- 成員函數若帶有左值引用限定符，則只有對象爲左值時才能被調用。
- 成員函數若帶有右值引用限定符，則只有對象爲右值時才能被調用。
- 一個類中允許存在函數簽名完全相同，而分別帶有左值限定符和右值限定符的兩個成員函數(不會造成定義衝突，根據對象的值類型只會有一個被調用)。
- 一旦定義了一個帶有引用限定符的成員函數，則不能定義與該成員函數簽名完全相同的無引用限定符版本。
- 引用限定符只能用於普通成員函數，而不能加在靜態成員函數之後(靜態成員可以不通過實例訪問，因此左值/右值限定沒有意義)。

如下代碼所示：

```cpp
#include <iostream>

using namespace std;

class Test
{
public:
	void show() & { cout << "&" << endl; }
	void show() && { cout << "&&" << endl; }
	//void show() { /* code */ } //錯誤，定義了帶有引用限定符的成員函數，則不能再定義該函數的無引用限定符版本
	//static void show() & { /* code */ } //錯誤，靜態成員函數不能帶有引用限定符
	virtual test() const & final {} //當引用限定符與後置const、final等關鍵字一同使用時需要注意位置
};

int main(void)
{
	Test t;
	t.show(); //左值對象調用的函數爲"void show() &"
	Test().show(); //右值對象調用的函數爲"void show() &&"
	return 0;
}
```

輸出結果：(GCC 5.3.0 && ArchLinux x64)

```
&
&&
```



# 引用與指針
C++中，引用同樣可以綁定在指針類型上。
語法格式如下：

```cpp
// 左值引用綁定指針
類型名*& 引用名 = 變量名;
類型名* const& 引用名 = const右值/非const右值/變量名;

// 右值引用綁定指針
類型名*&& 引用名 = 非const右值;
類型名* const&& 引用名 = const右值/非const右值;
```

一般來說，帶`const`限定的變量可以接收非`const`變量的值，反之則不可。
舉例：

```cpp
int a = 0;
const int b = 0;
int* c = &a;
//int* d = &b; //錯誤，const變量的地址應該有指向const變量的指針保存
const int* d = &b;
const int* e = &a; //正確，非const變量的地址也可以由指向const變量的指針保存
int* const f = &a; //正確，const指針
//int* g = f; //錯誤，const指針不能傳遞給非const指針
const int* const g = f; //正確，const指針可以傳遞給指向const變量的const指針

int*& x = c; //非const左值引用綁定非const指針變量(非const左值)
int*&& x = &a; //右值引用直接綁定到非const地址(非const右值)
int* const& x = &a; //const左值引用綁定到非const地址(非const右值)
const int* const& x = std::move(d); //const左值引用綁定到指向const值的指針的右值，第一個const代表引用綁定的指針所指向的值是帶有const的
const int* const&& x = std::move(e); //const右值引用綁定到指向const值的指針的右值
int* const&& x = std::move(f); //const右值引用綁定到const指針的右值
const int*&& x = std::move(d); //非const右值引用綁定到指向const值的指針的右值
const int* const& x = std::move(g);
const int* const&& x = std::move(g); //對於指向const變量的const指針的右值可以使用const左值引用或const右值引用來綁定，第一個const不能省略！
```



# 函數指針
函數指針保存一個函數的地址，是指向函數的指針。
對於函數而言，函數名稱即爲函數的地址，可直接賦值給函數指針。函數指針亦可直接使用函數語法調用。

函數相關指針語法：

- 一般函數指針

	```cpp
	// 定義
	返回類型 (*指針名)(參數類型) = 函數名;

	// 使用
	指針名(參數);
	```

- 返回函數指針的函數

	```cpp
	// 定義
	所指向函數的返回類型 (*函數名(函數參數表))(所指向函數的參數表);

	// 使用
	符合所指向函數的函數原型的函數指針 = 函數名(實參);
	```

函數指針語法較爲複雜，可使用`typedef`/`#define`等語法簡化函數指針的表達：

- 使用`typedef`關鍵字來定義函數指針。函數簽名被定義爲一個類型。
- 使用`#define`宏來定義指針，宏只做簡單的內容替換(需要注意運算符優先級)。

示例：

```cpp
int getNum(int a)
{
	reuturn a;
}

// 直接定義函數指針
int (*p1)(int) = getNum;

// 使用typedef關鍵字定義類型
typedef int (*P2)(int);
P2 p2 = getNum;

// 使用宏定義函數指針
#define P3(p) int (*p)(int)
P3(p3) = getNum;
```

## 成員指針
**成員指針**是指向類內成員函數的一類特殊的函數指針。
普通函數指針/靜態成員函數指針爲單倍指針大小，而成員指針在不同的C++實現中存在不同的大小：

- 在g++/clang++中，成員指針爲雙倍普通指針大小
- 在VS中，成員指針根據繼承方式的不同可能出現單倍大小、雙倍大小、三倍大小甚至四倍大小的指針

成員指針相關語法：

- C++普通成員函數指針

	```cpp
	// 定義
	返回類型 (類名::*指針名)(參數表) = &類名::函數名;

	// 使用
	(類實例名.*指針名)(實參);
	```

- C++靜態成員函數指針(類似於普通函數指針)

	```cpp
	// 定義
	返回類型 (*指針名)(參數表) = &類名::函數名;
	返回類型 (*指針名)(參數表) = &(類名::函數名)

	// 使用
	指針名(實參);
	(*指針名)(實參);
	```

示例：

```cpp
#include <iostream>

using namespace std;

class A
{
public:
	int m = 100;
	int getNum(int);
	static int getZero(int);
};

int A::getNum(int num)
{
	return num;
}

int A::getZero(int)
{
	return 0;
}

int getOne(int)
{
	return 1;
}

int main()
{
	A a;
	P p = getOne;
	T(s) = A::getZero;
	int (A::*x)(int) = &A::getNum;
	cout << p(0) << " " << s(0) << " " << (a.*x)(123) << endl;
	cout << sizeof(p) << " " << sizeof(s) << " " << sizeof(x) << endl;
	return 0;
}
```

輸出結果：(gcc 4.9.1 & ArchLinux 64bit)

```
1 0 123
8 8 16
```

輸出結果：(VS 2013 & Windows 8.1 64bit)

```
1 0 123
8 8 8
```

補充：

函數的函數名代表該函數的地址，可以直接傳遞給符合要求(函數簽名對應)的函數指針變量，
可以像使用原函數一樣使用函數指針(非靜態成員函數指針除外)。
C++標準規定，非靜態成員函數不是左值，因此非靜態成員函數不存在表達式中從函數左值到指針右值的隱式轉換，
非靜態成員函數指針必須通過`&`運算符顯式獲得。

標準的成員指針語法是`&類名::成員名`，VS還允許`&(類名::普通成員名)`，
但這樣的方式在更爲規範的編譯器(例如g++/clang++)中會報錯(g++/clang++將`類名::普通成員名`視爲直接訪問非靜態變量，因此報錯)。

g++/clang++等編譯環境不支持虛繼承的情況下，從子類創建虛基類的成員函數指針，但VS支持這個特性；
因此g++/clang++中的函數指針始終爲雙倍大小，而VS中可能會隨着繼承方式的變化而變化。
VS中多倍函數指針大小的詳情：

- 單倍指針

	對於非派生類、單繼承類，類成員函數指針保存的就是成員函數的內存起始地址。

- 雙倍指針

	對於多重繼承類，類成員函數指針保存的是成員函數的內存起始地址與this指針調整值。(GCC/Clang對於所有函數指針採用此類處理方式)
	因爲對於多繼承類的類成員函數指針，可能對應於該類自身的成員函數，或者最左基類的成員函數，這兩種情形都不需要調整this指針。
	如果類成員函數指針保存的其他的非最左基類的成員函數的地址，
	根據C++標準，非最左基類實例的開始地址與派生類實例的開始地址肯定不同，所以需要調整this指針，使其指向非最左基類實例。

- 三倍指針

	對於多重繼承且虛繼承的類，類成員函數指針保存的就是成員函數的內存起始地址、this指針調整值、虛基類調整值在虛基表(vbtable)中的位置共計3項。
	以常見的"菱形虛繼承"爲例。最派生類多重繼承了兩個類，稱爲左父類、右父類；兩個父類共享繼承了一個虛基類。
	派生類的成員函數指針可能保存了這四個類的成員函數的內存地址。
	如果成員函數指針保存了派生類或左父類的成員函數地址，則不需要調整this指針值。
	如果如果成員函數指針保存了右父類的成員函數地址，則this指針值要加上一個偏移值，指向右父類實例的地址。
	如果成員函數指針保存了虛基類的成員函數地址，由於C++類繼承的複雜多態性質，
	必須到派生類虛基表的相應條目查出虛基類地址的偏移值，依此來調整this指針指向虛基類。

- 四倍指針

	C++標準允許一個僅僅是聲明但沒有定義的類(forward declaration)的成員函數指針，
	可以被定義、被調用。這種情況下，實際上對該類一無所知。這稱作未知類型(unknown)的成員函數指針。
	該類的成員函數指針需要留出4項數據位置，分別用於保存成員函數的內存起始地址、this指針調整值、
	虛基表到類的開始地址的偏移值(vtordisp)、虛基類調整值在虛基表(vbtable)中的位置，共計4項。



# template (模板)
`泛型`在C++中的實現被稱爲**模版**`template`，模版可以用在類和函數中。模板是C++中編譯時多態的一類形式。

- 當模版用在函數中時，調用模版函數時可以不顯式指定模版類型，編譯器會根據調用函數的參數類型進行自動推導。
此外，不能給一個模版類型指定兩種不同的類型。
- 當模板函數在接收特定參數時如果與已有的普通函數的原型相同，則會優先調用普通函數的實現。

示例：

```cpp
#include <iostream>

using namesapce std;

template <class T>
T get(T t, T c)
{
	return t;
}

int main(void)
{
	// 正確，顯式指定模版函數的模版類型爲int
	cout << get<int>(123, 123) << endl;

	// 正確，根據調用函數時傳入的參數推導出模版類型爲int
	cout << get(123, 123) << endl;

	// 錯誤，沒有顯式指定模版類型時，對於同一個類型傳入模版的參數必須類型完全相同，
	// 而 get(123, 12.3) 會讓編譯器推導爲 get(int, double)
	//cout << get(123, 12.3) << endl;

	// 正確，如果在調用模版函數時顯式指定了模版類型，則對於同一個模版類型可以使用兼容的參數類型(不一定要完全相同)，
	// 編譯器會自動進行隱式的強制類型轉換
	cout << get<int>(123, 12.3) << endl;

	return 0;
}
```

模板可以應用於整個類或類內的某個函數：

- 當模版用在類中時，則該類在實例化時必須顯式指定模版的類型。
- 當模版用在類內部的某個成員函數中時，帶有模版函數的類實例化方式與普通類無異，
而該類的成員模版函數使用方式類似於普通模版函數，可以不顯式地指定模版類型而讓編譯器來推導。

## 模版編譯
C++模版屬於**編譯時多態**，模版代碼在編譯時即生成完畢。

- 當編譯器遇到模版定義時，**不**直接生成代碼，而是在實例化了一個模版的特定版本時纔會根據模版實參類型生成特定的代碼。
- 爲了在編譯時生成特定的模版代碼，編譯器需要模版函數/模版類成員函數的**定義**，而不僅僅是聲明。
- 模版類成員函數/模版函數的定義與聲明需要在**同一個**文件中，**默認情況下**，
模版函數/模版成員函數**不支持**定義與聲明拆分在**不同**的文件中。

## 模版定義與聲明分離
受限於模板機制的實現，C++中的模版類成員函數/模版函數**不能**拆分到不同文件中。

若預先知道模版會使用哪些具體的模板參數並以此進行實例化，則可以在源碼文件中**顯式實例化特定類型的模版**，
則該類型的模版函數便會在編譯到該源碼文件時生成，以此來實現模版定義與聲明分離。

示例：

文件`test.h`:

```cpp
template <class T>
class Test
{
public:
	T get();

	template <class V>
	V get(V v);
};
```

文件`test.cc`:

```cpp
#include "test.h"

// 顯式聲明特定類型的模版
template class Test<int>;
// 對於模板類的模板成員函數，則需要爲模板類指定模板參數
template int Test<int>::get(int num);

template <class T>
T Test<T>::get()
{
	return 100;
}

template <class T>
template <class S>
S Test<T>::get(S s)
{
	return s;
}
```

文件`main.cc`:

```cpp
#include "test.h"
#include <iostream>

using namespace std;

int main(void)
{
	cout << Test<int>().get() << endl; //正確
	cout << Test<double>().get() << endl; //編譯報錯，提示 undefined reference to `Test<double>::get()'
	cout << Test<int>().get(100) << endl; //正確
	cout << Test<int>().get(100.0) << endl; //編譯報錯，提示 undefined reference to `double Test<int>::get<double>(double)'
	cout << Test<double>().get(100) << endl; //編譯報錯，提示 undefined reference to `int Test<double>::get<int>(int)'
	return 0;
}
```

模板類內的成員模板函數函數定義較爲複雜，需要同時指定類的模板參數以及自身的模板參數。

## 模版的高級用法
- C++的模版能夠接收類型形參和部分非類型形參，模版的非類型形參只能是整形、指針和引用，比如`int a`可以作爲模版的形參，
但`double a`、`string a`則不可以，而`double* a`、`string* a`則可以，對象的引用和指針是符合要求的。
- 調用非類型模板形參的實參必須是一個常量表達式，即他必須能在編譯時計算出結果。
需要注意的是，任何局部對象，局部變量，局部對象的地址，局部變量的地址都不是一個常量表達式，都不能用作非類型模板形參的實參。
- 全局指針類型，全局變量，全局對象也不是一個常量表達式，不能用作非類型模板形參的實參。
- 全局變量的地址或引用，全局對象的地址或引用`const`類型變量是常量表達式，可以用作非類型模板形參的實參。
- `sizeof`表達式的結果是一個常量表達式，也能用作非類型模板形參的實參。
- 模版函數如果使用了非類型形參，則在調用該模版函數時必須顯式指定模版實參，因爲編譯器只能推導模版類型，非類型的模版參數需要顯式地指定。

## 模版形參默認值
- C++11之前可以爲**模版類**的**類型形參**提供默認值，但**不能**爲**模板函數**的**類型形參**提供默認值。
模板函數和模板類都**可以**爲模板的**非類型形參**提供默認值。
- C++11之後，無論模版函數或是模版類的類型形參和非類型形參都可以擁有默認值(`g++ 4.9.2`和`vs 2013`測試通過)。
- 模版形參默認值的用法類似於函數參數形參默認值，即從第一個有默認值的形參開始，之後的形參都應擁有默認值，並且形參默認值在聲明或定義只需要出現一處即可。
- 即使一個模版類的所有模版形參都擁有默認值，全部採用默認參數來實例化這個模版類時類名之後依然需要有一對空的尖括號`>`來表示實例化的是一個模版類。

## 模板與重載
C++中模板是在編譯時根據實例化時使用的**模版參數**編譯成對應的函數。
C++作爲編譯性語言，模板是在編譯期實現的，屬於編譯時多態的一種。

- 類模板與重載

	對於模板類而言，如果一個模板類成員函數(無論是否靜態)在確定了類型之後與原有的成員函數原型發生衝突則在編譯時就會報錯。
	若模板類成員函數在使用某種類型時**可能**與已有的函數原型發生衝突，但只要沒使用該類型，就能通過編譯。
	如下代碼所示：

	文件`test.h`

	```cpp
	template <class T>
	class Test
	{
	public:
		T get(T t1, T t2) { return t1 + t2; }
		int get(int num1, int num2) { return num1 + num2 + 1; }
	};
	```

	文件`test.cc`

	```cpp
	#include "test.h"

	int main(void)
	{
		Test<int> t; //編譯報錯，提示"error: ‘int Test<T>::get(int, int) [with T = int]’ cannot be overloaded"
	}
	```

	當`Test`類使用`int`型作爲模板實例化類型時，與原有函數原型發生衝突。

- 成員函數模板與重載

	對於成員函數模板而言，**允許**成員模板函數與原有的類內成員函數具有**完全相同**的函數原型。
	調用時，默認優先調用普通成員函數，但可以通過顯式寫明模板參數的形式調用成員模板函數。
	示例：

	文件`test.h`

	```cpp
	class Test
	{
	public:
		template <class T>
		T get(T t1, T t2) { return t1 + t2; }
		int get(int num1, int num2) { return num1 + num2 + 1; }
	};
	```

	文件`test.cc`

	```cpp
	#include "test.h"
	#include <iostream>

	using namesapce std;

	int main(void)
	{
		Test t; //帶有成員模板函數的類實例化方式與普通類完全相同
		cout << t.get(100, 100) << endl; //輸出201，默認調用非模板函數
		cout << t.get<int>(100, 100) << endl; //輸出200，顯式指定模板參數時調用模板函數
	}
	```

## 模版特化
C++支持`模版特化`，即對於特定的模版參數類型可以指定其實現。
如有以下模版類，有兩個模版參數`T`和`S`：

```cpp
template <class T, class S>
class Template
{
	/* code */
};
```

可以指定其模版類型爲某種類型時的類定義，如需要特化模版皆爲參數爲`int`型時的類定義可以寫成：

```cpp
template <>
class Template<int, int>
{
	/* code */
};
```

特化時顯式指定`所有`模版參數的類型被稱爲`完全特化`，類模版還支持`偏特化`，即只指定一部分的模版類型參數：

```cpp
template <class T>
class Template<T, int>
{
	/* code */
};
```

類`Temp`的後一個模版參數的類型被顯式指定爲`int`，而模版參數`T`依然由用戶指定。
除了`模版類`之外，C++中模版函數也同樣支持**模版特化**。

如以下模版函數：

```cpp
template <class T, class S>
T func(T t, S s)
{
	/* code */
}
```

若需要特化其模版參數全爲`int`型，則可以寫成：

```cpp
template <>
int func<int, int>(int t, int s)
{
	/* code */
}
```

模版類型參數也可省略，寫成：

```cpp
template <>
int func(int t, int s)
{
	/* code */
}
```

需要注意，模版函數**不支持**`偏特化`，即以下的寫法**不能**通過編譯：

```cpp
template <class T>
T func<T, int>(T t, int s) //error
{
	/* code */
}
```

C++不允許模版函數偏特化，`偏特化`的模版函數在編譯時會報錯，提示`error: function template partial specialization is not allowed`。

## 模版遞歸
C++中，模版函數與模版類皆可正常進行遞歸展開，模版遞歸需要使用**模版特化**作爲遞歸結束標誌，防止模版被無限展開。

使用遞歸模版函數計算**斐波那契數列**：

```cpp
#include <iostream>

template <int num>
int fibonacci()
{
	return fibonacci<num - 1>() + fibonacci<num - 2>();
}

template <>
int fibonacci<0>()
{
	return 0;
}

template <>
int fibonacci<1>()
{
	return 1;
}

int main(void)
{
	std::cout << fibonacci<10>() << std::endl;
	return 0;
}
```

由於模版展開是在**編譯時**進行的，利用模版遞歸特性可以讓一些計算在編譯時發生，提升代碼效率。

利用模版在編譯時計算**斐波那契數列**：

```cpp
#include <iostream>

template <int num>
class Fibonacci
{
public:
	// 利用靜態變量保存計算結果，靜態變量值在編譯時計算完成
	// 也可以使用"const static"變量，初始化代碼可以直接寫在類的內部
	static int value;
};

template <int num>
int Fibonacci<num>::value = Fibonacci<num - 1>::value + Fibonacci<num - 2>::value;

template <>
class Fibonacci<0>
{
public:
	static int value;
};
int Fibonacci<0>::value = 0;

template <>
class Fibonacci<1>
{
public:
	static int value;
};
int Fibonacci<1>::value = 1;

int main(void)
{
	// 使用g++能正常輸出結果：55，但clang++並沒有在編譯時確定靜態變量的值，輸出結果：0
	// 靜態成員變量value的值在編譯時已經確定，不在運行時計算，更高效
	std::cout << Fibonacci<10>::value << std::endl;
	return 0;
}
```

## 變長模版 (C++11)
C++11加入了**變長模版**特性，使用`template <typename... T>`或`template <class... T>`來表示有數目不定的模版參數。
定義變長模版變量寫成`T... arg_name`，調用變長模版變量也要在參數名稱後加上引號，寫成`arg_name...`。
使用`sizeof...`操作符可以計算模版參數包的個數(**不是**類型大小)。
通過模版類型的**自動推導**，變長的模版參數包可以使用**遞歸**的方式逐一取出參數。

示例，計算一個變長序列之和：

```cpp
#include <iostream>

using namespace std;

//定義模版函數的推導終止點，防止無限遞歸
template <class T>
T sum(const T& t)
{
	return t;
}

template <class T, class... Args>
T sum(const T& t, const Args&... args)
{
	return sum(args...) + t;
}

int main(void)
{
	cout << sum(100) << endl;
	cout << sum(100, 200) << endl;
	cout << sum(100, 200, 300) << endl;
	cout << sum(100, 200, 300, 400) << endl;
	return 0;
}
```

輸出結果：

```
100
300
600
1000
```

## 禁止特定類型的模板參數
C++11之後，可以禁止接受某種類型做爲模板參數，使用`delete`關鍵字將模板函數的某種實現標記爲**刪除**的，示例：

```cpp
template <class T>
T test(T&& t)
{
	return t;
}

template <>
int test(int&& num) = delete;

test<int>(100); //錯誤，提示"無法引用，函數xxx是已刪除的函數"
```



# _Generic (C11)
在C11中，引入了新關鍵字`_Generic`，使用`_Generic`可以一定程度上實現**泛型**功能(不過功能上遠遠不能與C++的模板機制相比)。

`_Generic`語法如下：

```c
_Generic(expr, type_1: expr_1, type_2: expr_2, ..., default: expr_default)
```

- `expr`爲一個表達式。
- `type_1`、`type_2`爲類型。
- `expr_1`、`expr_2`爲對應類型的返回表達式。

若`expr`表達式的類型與之後類型列表中的某種類型匹配時，`_Generic()`語句會將匹配的類型的表達式作爲語句結果，
若`expr`表達式與類型列表中所有類型都不匹配，則使用`default`對應的表達式作爲語句結果。

基本用法示例：

```c
#define G(x) _Generic(x, int: 100, double: 200.0)

int a = 0;
double b = 0.0;

printf("%d\n", G(a)); //打印 100
printf("%f\n", G(b)); //打印 200.000000
```

`default`可以不設定，但編譯時若`expr`沒有匹配的類型則會**報錯**。

```c
#define G(x) _Generic(x, int: 100, double: 200.0)

float s = 0;

printf("%d\n", G(s)); //報錯 error: ‘_Generic’ selector of type ‘float’ is not compatible with any association
```

使用`_Generic`可以一定程度上實現模版函數：

```c
#include <stdio.h>

struct T
{
	int data;
};

_Bool max_int(const int num_1, const int num_2)
{
	printf("call max_int\n");
	return num_1 > num_2;
}

_Bool max_double(const double num_1, const double num_2)
{
	printf("call max_double\n");
	return num_1 > num_2;
}

_Bool max_T(const struct T t_1, const struct T t_2)
{
	printf("call max_T\n");
	return t_1.data > t_2.data;
}

// 若x大於y，返回1，否則返回0
#define MAX(x, y) \
	_Generic(x, int: max_int, double: max_double, struct T: max_T)(x, y)

int main(int argc, char** argv)
{
	// MAX宏根據不同的具體參數類型選擇不同的實現
	if (MAX(200, 100))
		printf("True\n");

	if (MAX(200.0, 100.0))
		printf("True\n");

	// 傳統的宏能夠實現基礎類型的比較，但對於自定義結構類型無能爲力
	if (MAX((struct T){ 200 }, (struct T){ 100 }))
		printf("True\n");

	return 0;
}
```

輸出結果：(GCC 6.1.1 && ArchLinux x64)

```
call max_int
True
call max_double
True
call max_T
True
```



# assert (斷言)
**斷言**是調試中常用的一種宏，常用於**條件檢查**。

## 斷言宏
**斷言**是一種**預處理宏**，其定義位於頭文件`assert.h`中，不同平臺的實際定義不盡相同，但表達式結構類似，示例：

```cpp
assert(expr);
```

`assert`接受一個表達式作爲條件，表達式爲真(非0)時，程序正常執行，表達式爲假(值爲0)，assert輸出信息並終止程序的執行。

## 靜態斷言 (C11)
C11中引入了**靜態斷言**關鍵字`_Static_assert`，與普通的斷言不同，**靜態斷言**不是宏，而是一個語言級別的**關鍵字**。
靜態斷言在編譯時生效，接受常量表達式，若接收的常量表達式值爲假，則在編譯階段直接報錯。

`_Static_assert`關鍵字用法示例：

```cpp
_Static_assert(expr, error_str);
```

若`expr`表達式爲假，則`error_str`則作爲編譯錯誤信息被輸出。

## 靜態斷言 (C++11)
C++11中同樣引入了**靜態斷言**關鍵字`static_assert`，用法與C11中的`_Static_assert`相同。

- 使用靜態斷言實現範型約束

	**靜態斷言**搭配標準庫中的模版類`std::is_base_of<Base, Der>`，
	能夠實現類似`Java`、`C#`等高級語言中的範型約束效果。
	示例：

	```cpp
	#include <iostream>

	using namespace std;

	class Base { };

	class Der : public Base { };

	class Private : Base { };

	class Other { };

	int main(void)
	{
		// Right
		static_assert(is_base_of<Base, Der>::value, "Need class Base.");

		// Right
		static_assert(is_base_of<Base, Private>::value, "Need class Base.");

		// error: static_assert failed "Need class Base."
		static_assert(is_base_of<Base, Other>::value, "Need class Base.");

		return 0;
	}
	```

	通過靜態成員`std::is_base_of<Base, Der>::value`來判定作爲參數的兩個類是否存在繼承關係。
	類`Base`與`Der`存在繼承關係，因而編譯通過，但類`Other`與`Base`不存在繼承關係，因而編譯報錯。

	需要注意的是，**私有繼承**雖然不支持轉型操作，但繼承關係依然存在，能夠通過繼承關係檢測。



# auto 類型推導
C++11中，標準重新定義了`auto`關鍵字的作用，auto關鍵字現在用於推導變量的類型。

使用auto推導類型時，需要注意：

1. `auto`默認得到目標變量的值複製。
1. `auto&`得到目標變量的引用，只能綁定到左值上。
1. `const auto&`得到目標變量的const引用，可以綁定任何值，但得到的內容爲const，不可修改。
1. `const auto&&`得到const右值引用，只能綁定右值。
1. `auto&&`得到目標變量的**通用引用**`universal reference`，能夠綁定到**任何值**，同時**不帶有**const限制。

`auto&&`與普用右值引用不同，普通右值引用只能綁定到右值上，示例：

```cpp
int a = 0;
auto&& b = 0; //綁定右值
auto&& c = a; //綁定左值
c = 1;
cout << a << endl; //打印輸出："1"，c爲a的引用，而不是值複製
cout << &a << " " << &c << endl; //打印輸出結果相同，c和a爲同一塊地址，即同一個變量
```



## Lambda
C++11中引入了Lambda表達式，語法格式爲：

```cpp
[當前作用域變量捕獲方式](參數表) { 函數體; }; //標準形式
[當前作用域變量捕獲方式] { 函數體; }; //無需參數的形式
[當前作用域變量捕獲方式](參數表) -> 返回類型 { 函數體; }; //顯式指定返回值的形式
```

需要注意的是，與普通函數相同，如果需要表達式有返回值則需要在函數體中使用`return`語句返回值。
與Java/C#等語言不同，C++中的Lambda**不能**省略參數類型，也不能在函數體只有一句的時候省略函數體外的花括號。

## 複用 Lambda
如果需要重複使用一個Lambda，可將其構造爲函數對象`std::function`：

```cpp
std::function<返回類型(參數表)> 函數對象名 = [當前作用域變量引用方式](參數表) { 函數體; };
```

需要注意的是，函數對象是一個**類實例**，不是函數指針，但如果一個Lambda沒有捕獲任何變量，則可以與函數指針進行轉化。

`std::function`重載了`bool`運算符，可用於判斷函數對象是否有效：

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main(void)
{
	function<void()> func;
	cout << (func ? "true" : "false") << endl; //輸出"false"
	func = [] {};
	cout << (func ? "true" : "false") << endl; //輸出"true"
	return 0;
}
```

## 變量捕獲
Lambda可以捕獲當前作用域中的變量(閉包)，`[=]`表示當前作用域的變量全部取值傳遞，`[&]`表示當前作用域的變量全部取引用傳遞。

可以只設置需要的變量，並設置不同的傳遞方式，如`[a, &b, c]`表示變量`a`和`c`爲值傳遞，`b`爲引用傳遞。
可以在傳遞所用變量的基礎上分別設定指定變量的傳遞方式，如`[=, &a]`表示除了`a`之外的變量全部爲值傳遞，
`a`爲引用傳遞，而`[&, a]`表示除`a`外的所有變量爲引用傳遞，`a`爲值傳遞。
設置全局傳遞方式的操作符要放在設置單個變量的操作符之前，類似`[&a, =]`、`[b, &]`的寫法無法通過編譯。

採用值傳遞方式捕獲的變量帶有`const`屬性。

Lambda表達式的參數可以是**引用**或**指針**，作爲**返回值**時**不能**爲引用傳遞，但依然可以爲指針類型。
對於沒有捕獲變量的Lambda，可以直接轉化爲原生的函數指針。
Lambda與普通函數最大的區別在與Lamdba可以捕獲當前作用域中的變量，而函數不可以。
一但Lambda沒有捕獲當前作用域中的變量，則該Lambda便可以轉化爲一個普通函數，即可以使用原生函數指針表示。

示例：

```cpp
#include <iostream>
#include <functional>

using namespace std;

int main(void)
{
	int a = 1;
	int b = 2;
	function<int(int, int)> test = // 可以直接使用auto類型推斷
			[=, &a](int x, int y) { return a = x + y + b; };
	test(1, 1);
	cout << a << endl;

	// 未捕獲變量的Lambda可以轉化爲函數指針
	int (*get_num)(int) = [](int num) { return num; };
	cout << "Run lambda function point:" << get_num(100) << endl;

	return 0;
}
```

輸出結果：(GCC 5.1.0 && ArchLinux x64)

```
4
Run lambda function point: 100
```

## C++14 中的 Lambda 新特性
C++14中，加入了模版Lambda，支持在Lambda使用**表達式**捕獲作用域中的變量，
且沒有捕獲變量的Lambda可以與函數指針進行轉化(不是`std::function`)。

- C++11中，Lambda中的參數必須顯式指定參數的類型，C++14中，參數的類型可以使用`auto`關鍵字，
編譯器會對所有的被使用的該表達式進行參數類型推斷，然後根據使用的參數類型編譯出對應的Lambda實例。
- C++11中，對變量的捕獲包括值捕獲和左值引用捕獲兩種，C++14中，Lambda中支持使用**表達式**捕獲，
通過簡單的表達式進行一些捕獲值初始化`lambda capture initializers`，
或是對捕獲變量重命名(設置全局傳遞方式的操作符依然要放在最前面)。

示例：

```cpp
#include <iostream>

using namespace std;

int main(void)
{
	// 模版Lambda表達式
	auto lambda1 = [](auto num) { return num; };
	cout << "Use int as args: " << lambda1(100) << endl;
	cout << "Use string as args: " << lambda1("string") << endl;

	// Lambda表達式支持表達式捕獲
	int a = 100, b = 200, c = 300;

	// 以捕獲值的方式捕獲變量a，並用a的值加上50並命名爲num1，然後將b的引用命名爲num2
	auto lambda2 = [=, num1 = a + 50, &num2 = b]() { num2 = num1 + c; };
	lambda2();
	cout << "After run lambda2, the value b is: " << b << endl;

	// 捕獲變量名稱可以與原始變量相同(局部變量掩蓋原則)
	// 捕獲表達式中可以使用C++11中引入的統一初始化語法
	// lambda2與lambda3等價
	auto lambda3 = [=, a{ a + 50 }, &b = b] { b = a + c; };
	lambda3();
	cout << "After run lambda3, the value b is: " << b << endl;

	return 0;
}
```

輸出結果：(GCC 5.2.0 && ArchLinux x64)

```
Use int as args: 100
Use string as args: string
After run lambda2, the value b is: 450
After run lambda2, the value b is: 450
```



# STL 容器
容器`Containers`是用來存儲和管理數據的數據結構。容器一般分爲序列式容器`Sequence Containers`和關聯式容器`Associative Containers`。

- 常用的**序列式容器**有`vector(向量)`、`list`(雙向鏈表)、`deque`(雙向隊列)。
- 常用的**關聯式容器**有`set`(集合)、`map`(映射)、`multiset`(多重集合)、`multimap`(多重映射)。

以上的7中容器對象都有以下成員方法：

```cpp
bool empty() const; //判斷容器是否爲空
size_type max_size(); //返回容器最大能存儲的元素個數
size_type size(); //返回容器中當前已經存儲的元素的數量
void swap(contain_type &container); //交換當前容器對象與container容器對象中的內容
void clear(); //清空容器中的內容
iterator erase(iterator position); //擦除指定迭代器位置的內容
iterator erase(iterator first, iterator last); //擦除[first, end)位置的內容
```

## 迭代器
各類容器中都內置了迭代器，可通過以下函數創建迭代器：

```cpp
iterator begin(); //返回一個指向首元素的迭代器
iterator end();
iterator rbegin(); //返回一個指向首元素的迭代器，逆序遍歷
iterator rend();
```

在C++11之後，可以使用新的`std::begin()`和`std::end()`函數來創建迭代器。
以`vector`爲例，創建和使用迭代器：

```cpp
vector<int> vector_int; //創建容器對象
vector<int>::iterator iterator_int; //創建迭代器對象
iterator_int = vector_int.begin(); //初始化迭代器
iterator_int = std::begin(vector_int); //C++11風格的迭代器初始化
++iterator_int; //迭代器向下移動一個位置
--iterator_int; //迭代器返回上一個位置
*iterator_int; //取出迭代器在當前位置的內容
cin >> *iterator_int; //向迭代器指代的位置中輸入內容
std::advance(iterator_int, num); //像iterator_int增加指定的偏移量
```

## 序列式容器
序列式容器中元素的次序與元素的值無關，只與元素插入的順序有關。

序列式容器都有以下常用成員函數：

```cpp
void pop_back(); //刪除容器尾部的最後一個元素
void push_back(const T& x); //在容器尾部添加一個元素
reference front(); //返回容器內首個元素的引用(可以通過此函數修改元素的值)
reference back(); //返回容器最末元素的引用
iterator insert(iterator position, const T& x);
void insert(iterator position, size_type n, const T& x);
template <class InputIterator>
void insert(iterator position, InputIterator first, InputIterator last);
```

序列式容器都提供了以下構造函數，以`vector`爲例：

```cpp
vector();
vector(size_type num, const TYPE& val); //使用num個值爲val的元素初始化vector
vector(const vector& from);
vector(input_iterator start, input_iterator end); //使用某個已存在的vector的[start, end)來構建一個新的vector
```

- *vector* 容器特點

	`vector`容器是數組式的容器類型。
	`vector`容器中存儲的數據元素被放在一塊連續的內存中。
	`vector`容器支持**隨機存取**，可以通過數組式的下標(即`[]`操作符)進行元素訪問、修改。

	`vector`容器雖支持`insert()`等函數來進行插入操作，
	但由於內部採用線性結構，因而`insert()`函數在頭部或是中間插入元素時需要進行大量複製操作，
	插入效率很低，在執行頭部、中部刪除元素操作時也同樣效率低。

- *list* 容器特點

	`list`容器採用**雙向鏈表**實現。
	`list`容器存儲的元素所處的內存空間不連續。
	由於鏈表的特性，元素之間是通過指針相連的，因而`list`容器在任意位置插入和刪除元素時效率都很高。

	`list`容器**不支持**隨機存取，不可使用`[]`操作符訪問元素，同時相比`vector`容器消耗的內存更多。
	`list`容器有着一些`vector`沒有的方法，比如`pop_front()`、`push_front(const T &x)`、`remove(const T &value)`等。
	使用`remove()`方法可以移除容器中所有值爲`value`的元素。

- *deque* 容器特點

	`deque`容器爲**雙向隊列**。
	`deque`兼顧了`list`和`vector`的優點，能夠方便地增加、刪除元素，也能夠使用`[]`操作符隨機存取元素。
	`deque`的缺點是需要消耗較高的內存。

## 關聯式容器
關聯式容器通過鍵值`key`來存取元素，元素次序與插入順序**無關**。

- 關聯式容器**不提供**`front()`、`back()`、`push_front/push_back(const T&)`、`pop_front/pop_back()`之類的操作。
- 關聯式容器可以進行比較，需要定義`<`操作符，所有作爲關聯式容器`key`的類型都必須重載`<`運算符，其它操作符不作要求。
- 關聯式容器提供`clear()`和`erase()`函數，但返回值爲`void`而不是下一個元素的迭代器。

常見的關聯式容器特點：

- *set*、*multiset* 容器特點

	`set/multiset`容器保存鍵值，對應數學概念中的`集合`。
	`set/multiset`的實現採用的平衡二叉搜索樹，插入、查詢、刪除等操作時間複雜度均爲`O(lgN)`。
	`set`不允許重複值，但`multiset`允許重複值。

- *map*、*multimap* 容器特點

	`map/multimap`容器同時保存鍵值和實際值，每一個元素都是一個`pair<key, value>`類型。
	`map`容器不允許相同鍵值`key`的元素，但`multimap`允許。
	`map`容器可以使用數組下標形式(`[]`操作符)來獲取指定鍵值的元素中的實際值。
	`multimap`由於鍵值可以重複，一個鍵值可以對應多個實際值，因而不能採用下標的形式獲取實際值。

	`pair`類型中有兩個成員，`first`和`second`，分別保存鍵值和實際數據。
	通過訪問`first`和`second`兩個成員可以獲取鍵值和實際數據。
	使用`find()`函數可以查找某個鍵值，返回一個迭代器，通過遍歷該迭代器可以獲取某個鍵值的所有對應值。

	可以通過`lower_bound()`、`upper_bound()`等函數獲取迭代器，用於遍歷元素。
	與`STL`的迭代器相同，`lower_bound()`返回指向參數鍵值的第一個元素位置的迭代器，
	而`upper_bound()`返回指向參數鍵值最後一個元素的下一個元素位置的迭代器。

`map`使用注意事項：

- 對於`map`等關聯式容器來說，key若爲指針類型，則將指針的值(指針包含的地址)作爲鍵值，而非指針所指向的內容。
因而兩個內容相同的不同數組對`map`而言就是兩個不同的鍵值。
- 並非所有類型均可作爲key，作爲key的類型必須重載`<`運算符，否則會出現編譯錯誤：
`二進制“<”: 沒有找到接受“xxx”類型的左操作數的運算符(或沒有可接受的轉換)`
- 一些類型已經默認重載了`<`運算符如`std::string`、`QString`等，可以直接作爲key使用。
- 當訪問容器的索引越界時，**不會**像其它高級語言如C#、Java一樣拋出異常，而是返回對應類型的零值。



# Smart Pointer (智能指針)
C++中除了手動使用`new`、`delete`操作符來進行動態內存管理之外，還可以使用智能指針管理動態內存，使用智能指針管理的動態內存會在不被需要時自動釋放。

`Boost`庫中提供了六種智能指針用來管理動態內存，分別是`shared_ptr`、`shared_array`、`scoped_ptr`、`scoped_array`、`weak_ptr`、`intrusive_ptr`，定義在`/usr/include/boost/smart_ptr/`路徑下對應名稱的頭文件中。

在C++11中，`boost`庫中的`shared_ptr`、`weak_ptr`被納入了標準庫，定義在`/usr/include/c++/版本號/memory`頭文件中。
C++11之前，標準庫中可以使用`auto_ptr`智能指針，在C++11之後，標準庫中增添了`shared_ptr`、`unique_ptr`、`weak_ptr`等智能指針。
原先的`auto_ptr`已經不推薦使用。

需要注意的是，`Boost`庫與標準庫中的同名類是不能相互轉換的(即`std::shared_ptr`不能轉換爲`boost::shared_ptr`)。

## 智能指針的一般性用法
智能指針重載了`->`操作符，使開發者可以使用此操作符訪問智能指針保存的對象的公有成員，對於智能指針自身的成員，依然使用`.`操作符訪問。
以`shared_ptr`爲例：

```cpp
shared_ptr<T> ptr; //創建一個空的、尚未初始化的動態指針
shared_ptr<T> ptr(new T(args)); //創建智能指針對象並開闢內存進行初始化，無參數時調用默認的構造函數
shared_ptr<T> ptr(T* t); //由指針t所指向的動態內存綁定到智能指針(如果t爲空指針，則智能指針綁定空內容)
ptr->...; //訪問智能指針指向的動態內存對象的公有成員
ptr.reset(); //重置智能指針
```

智能指針重載了`operate bool()`支持使用布爾運算形式展示指針是否爲空。
智能指針重載了`operate ==()`支持與其它智能指針以及`nullptr`進行比較。

示例：

```cpp
shared_ptr<T> ptr0;
shared_ptr<T> ptr1(new T(args));
ptr0 ? true : false; // false
ptr1 ? true : false; // true
ptr0 == nullptr ? true : false; // true
ptr0 == nullptr ? true : false; // false
```

標準庫中的各類智能指針特性：

- `std::auto_ptr`(已過時)

	一塊動態內存只能綁定一個`auto_ptr`，若將一個綁定了動態內存的`auto_ptr`複製給另一個`auto_ptr`則動態內存的所有權會被轉移到新的`auto_ptr`上，
	舊的`auto_ptr`不再指向原先的動態內存。

- `std::unique_ptr`

	來自於`boost::scoped_ptr`，類似於`auto_ptr`，但`unique_ptr`的限制更多，
	一塊動態內存只能綁定一個`unique_ptr`，同時`unique_ptr`不能進行復制。

- `std::shared_ptr`

	來自於`boost::shared_ptr`，基於**引用計數**的共享智能指針。
	一塊動態內存可以被多個`shared_ptr`綁定。
	每增加一個智能指針的綁定，則引用計數加1，當引用計數爲0時釋放指向的動態內存。
	`shared_ptr`的內存管理完全交由編譯器完成，不能手動釋放`shared_ptr`管理的動態內存(沒有`release()`成員函數)。

	`shared_ptr`使用`make_shared<T>(args)`函數進行構造。
	使用`reset()`成員函數會將當前智能指針管理的動態內存引用計數減1，如果引用計數爲0則釋放動態內存。
	`shared_ptr`的`reset()`成員函數可以帶有參數，參數可以是`new`構造函數或是對象指針，
	作用是將原先的託管對象引用計數減1然後管理新的對象(新對象引用計數加1)。

- `std::weak_ptr`

	來自於`boost::weak_ptr`，爲了解決`shared_ptr`中的**循環引用**問題而引入的**弱引用**智能指針。
	`weak_ptr`不能單獨綁定一塊動態內存(即不能新建動態內存初始化`weak_ptr`)，而是由`shared_ptr`轉化而來。

`shared_ptr/weak_ptr`使用：

- `weak_ptr`可以使用構造函數與`shared_ptr`相互轉換(即以已有的`shared_ptr`對象爲參數構造`weak_ptr`對象)，
一塊動態內存被`weak_ptr`智能指針綁定或是綁定該動態內存的`weak_ptr`被銷燬不會增加/減少原有的`shared_ptr`的引用計數。
- `shared_ptr`和`weak_ptr`都沒有`release()`成員函數，即不能手動釋放動態內存。`weak_ptr`不能直接調用指向對象的成員函數，
調用指向對象的成員函數之前需要先使用`weak_ptr`自身的`lock()`方法將自身轉變爲`shared_ptr`，然後再調用指向對象的成員函數。

## 智能指針的轉型
C++的類型轉換操作符`dynamic_cast<>()`、`static_cast<>()`、`const_cast<>()`**不能**用於智能指針對象的轉換，
智能指針實際是一個包含了指針的容器對象，並不能簡單地轉換爲普通指針類型。
將智能指針對象進行轉型需要使用`dynamic_pointer_cast<>()`、`static_pointer_cast<>()`、`const_pointer_cast<>()`，
其中的模版參數爲目標對象的類型(不是指針類型)。

## 改變做爲形參傳入的智能指針所指向的內容
當智能指針做爲形參時，如果需要改變指針指向的內容，則需要像普通指針一樣，
將新的內容賦值到`*智能指針對象`上(此項操作需要智能指針已被初始化且被分配了足夠的內存)。

如果智能指針是`shared_ptr`，則還需要考慮到智能指針保存內容的生命週期。

若傳入尚未初始化的智能指針，需要在函數內對其進行初始化，且還要保證外部能使用這個指針，此時需要傳遞智能指針的引用或地址，
保證函數內部能訪問到原始的智能指針，否則進行的操作都是對形參複製的智能指針進行的，不會改變外部的智能指針未被初始化的狀態。

例如：

```cpp
#include <iostream>
#include <memory>
#include <stdio.h>

using namespace std;

void init(shared_ptr<int> temp) //如果需要函數改變傳入的未初始化的智能指針，正確的方法是傳入引用或是傳入智能指針的地址(指針)
{
	shared_ptr<int> num(new int);
	*num = 100;
	temp = num;
}

int main(void)
{
	shared_ptr<int> temp;
	init(temp);
	cout << *temp << endl; //錯誤，運行init()函數之後，外部的智能指針temp實際上並未發生變化，依然處於未初始化狀態，試圖訪問其內容會報錯
	system("pause");
	return 0;
}
```

輸出結果：(VS 2015 && Windows10 x64)

```
報錯，提示訪問空指針(0x0000000)。
```



# std::bind()
C++11中引入該函數，來源於`boost::bind()`，作用是通過設定原有函數的某些參數值爲固定值來生成具有新參數表的函數(類似`Python`中的部分應用函數)，
`bind()`本質上是一個`call_adapter`。
`bind()`既可以綁定當前類的成員函數，也可以綁定全局函數/靜態函數或是其他類的具有訪問權限的成員函數。

## bind() 綁定普通函數

```cpp
bind(func_name, args...);
```

`bind()`用於綁定一般的函數(可直接訪問的函數，比如全局函數，其他類的可訪問靜態成員函數)時第一個參數爲需要綁定的函數名，
後面的參數爲綁定函數的參數表，可以向參數表中加入對應類型的常量，
不需要綁定常量的參數可以用參數佔位符`std::placeholders::_1`、`std::placeholders::_2`...或者`boost::_1`、`boost::_2`...)替代。

## bind() 綁定非靜態成員函數

```cpp
bind(&class_name::func_name, 對象實例/對象指針/智能指針, args...);
```

- `bind()`用於綁定非靜態成員函數時，需要通過類實例進行訪問，第二個參數需要爲綁定函數所在類的實例、指針或是智能指針。
- `bind()`綁定當前類的成員函數可以直接傳遞`this`指針。

實例代碼：

```cpp
#include <iostream>
#include <functional>
#include <memory>

using namespace std;

int get0(int a)
{
	return a;
}

class A
{
public:
	A(int num) : num(num) {};
	int get(int, int);
	int num;
};

int A::get(int a, int b)
{
	return num = a;
}

int main(void)
{
	A a1(888);
	A* a2 = new A(888);
	shared_ptr<A> a3 = make_shared<A>(888);

	function<int()> p0 = bind(get0, 100);
	function<int(int)> p1 = bind(A::get, a1, 1, placeholders::_1);
	function<int(int)> p2 = bind(A::get, a2, 2, placeholders::_1);
	auto p3 = bind(A::get, a3, 3, placeholders::_1);
	auto p4 = bind(A::get, ref(a1), 1, placeholders::_1);

	cout << p0() << endl;
	cout << p1(0) << " p1()調用後num的值：";
	cout << a1.num << endl;
	cout << p2(0) << " p2()調用後num的值：";
	cout << a2->num << endl;
	cout << p3(0) << " p3()調用後num的值：";
	cout << a3->num << endl;
	cout << p4(0) << " p4()調用後num的值：";
	cout << a1.num << endl;

	delete a2;

	return 0;
}
```

輸出結果：(GCC 5.1.0 && ArchLinux x64)

```
100
1 p1()調用後num的值：888
2 p2()調用後num的值：2
3 p3()調用後num的值：3
1 p4()調用後num的值：1
```

將類實例作爲參數進行綁定的時候，對類實例進行的是值傳遞，即複製一個類對象，
因此調用`bind()`生成之後的函數對象不會對原先的類實例進行修改(但傳遞類指針、類智能指針的時候，只是複製對象地址，類內存是同一塊，因此修改會同步)。
若需要在`bind()`是進行對象引用傳遞，則可以使用`std::ref()`、`std::cref()`函數。



# boost::signals2
使用`Boost`庫中的`signals2`可以實現近似C#中**委託**的效果，使用`signals2`需要包含頭文件`/usr/include/boost/signals2.hpp`。
`Boost`庫中的`boost::signals2`相比原先的`boost::signals`而言是**線程安全**的，原先的`boost::signals`現在已被廢棄。

## 定義信號
定義信號使用`boost::signals2::signal<>`，模板參數爲需要連接的函數的函數原型。
若需要連接的函數的原型爲`void func(int, int)`，則定義信號時應該寫成`boost::signals2::signal<void(int, int)>`。

`boost::signals2::signal`是**不可複製**的類型。

## 連接槽函數
連接槽函數使用`connect()`成員函數，該函數有兩個重載，定義如下：

```cpp
connection connect(const slot_type& slot, connect_position position = at_back);
connection connect(const group_type& group, const slot_type& slot, connect_position position = at_back);
```

- 連接槽函數時改變簽名

	被連接的槽函數必須要符合信號定義時的模板參數中的函數原型，必須函數原型參數個數完全相同且類型兼容(由於綁定槽函數時是傳遞槽函數的地址，
	因此函數默認參數被忽略，因而參數個數必須完全相同)。
	若需要綁定的函數參數表與信號定義的參數表數目不同，可以採用`std::bind()`生成具有新參數表的函數進行連接。

	若需要連接的槽函數爲一個類的非靜態成員函數，則也需要通過`std::bind()`將非靜態成員函數綁定一個類實例之後再進行連接，
	否則會連接失敗(沒有實例無法訪問非靜態成員函數)。

	若被連接的槽函數有多個重載，則需要進行強制類型轉換來轉換爲無歧義函數指針才能進行連接。

- `connect()`組別

	使用`connect()`函數的第二個重載進行槽函數連接時，可以在第一個參數的位置設置槽函數的組別，
	組別可以是一個整型數值(可以爲負數)，不同組別之間的槽函數按照組號由小到大的順序執行。

- `connect()`優先級

	`connect()`成員函數的最後一個參數用於設定槽函數的組內優先級，默認情況下取值爲`boost::signals2::at_back`，
	多個槽函數連接時返回值爲最後一個連接的槽函數的返回值，需要優先執行的槽函數可以設定爲`boost::signals2::at_front`。

## 取消連接
取消連接使用`disconnect()`成員函數，該函數有兩個重載，定義如下：

```cpp
void disconnect(const group_type& group); //斷開指定組別的所有槽的連接
void disconnect(const T& slot); //斷開指定槽
```

還可以一次性斷開所有槽：

```cpp
void disconnect_all_slots();
```

需要注意的是，每次連接槽函數成功之後都會返回一個`boost::signals2::connection`對象，
通過調用該對象的`disconnect()`函數也能實現指定槽函數連接的斷開。

## 獲取信號返回值
信號的返回值是由合併器`combiner`管理的，在定義信號對象時，會調用`boost`默認的合併器類管理返回值，
如果需要使用自定義合成器類，則定義需要寫成`boost::signals2::signal<func(type), combiner<type>>`。

定義完信號之後，可以像調用普通函數一樣調用信號對象，所有被信號連接的槽函數都將會被觸發(重載`()`操作符)，同時返回的一個合併器類的對象。

默認的合併器類只保存最後一次被觸發的槽函數的返回值，使用`*`操作符或是`value()`成員函數可以獲得合併器中保存的值。

實例代碼：

```cpp
#include <boost/signals2.hpp>
#include <iostream>

using namespace std;

class A
{
public:
	boost::signals2::signal<int(int)> sig;
};

class B
{
public:
	int slot1(int, char);
	int slot1(int, int, int);
	int slot2(double, int);
};

int B::slot1(int, char)
{
	cout << "This is slot1(int, char)." << endl;
	return 100;
}

int B::slot1(int, int, int)
{
	cout << "This is slot1(int, int, int)." << endl;
	return 200;
}

int B::slot2(double, int)
{
	cout << "This is slot2." << endl;
	return 300;
}

int main(void)
{
	A a;
	B b;

	a.sig.connect(1, boost::bind(&B::slot1, b, _1, 'a'));
	boost::signals2::connection link =
		a.sig.connect(1, boost::bind(&B::slot1, b, _1, 1, 2),
		boost::signals2::at_front);
	a.sig.connect(2, boost::bind(&B::slot2, b, 1.0, _1));

	cout << *a.sig(0) << endl;
	cout << "\nDisconnect slot1(int, int, int)." << endl;

	link.disconnect(); //取消槽函數slot1(int, int, int)的連接

	cout << a.sig(1).value() << endl; //調用value()成員函數獲取合併器返回值
	return 0;
}
```

輸出結果：(GCC 5.1.0 && ArchLinux x64)：

```
This is slot1(int, int, int).
This is slot1(int, char).
This is slot2.
300

Disconnect slot1(int, int, int).
This is slot1(int, char).
This is slot2.
300
```



# Boost 時間庫
`boost`時間庫提供了跨平臺的時間解決方案，相關頭文件爲`/usr/include/boost/date_time/posix_time/posix_time.hpp`。

## 獲取當前時間
時間使用`boost::posix_time::ptime`類型表示。

- 使用`boost::posix_time::second_clock/microsec_clock::universal_time()`可以獲取當前`UTC`時間的秒數/微秒數。
- 使用`boost::posix_time::second_clock/microsec_clock::local_time()`可以獲取當前本地時間的秒數/微秒數。
- 使用`boost::posix_time::to_iso_string()`可以以獲取的`boost::posix_time::ptime`作爲參數，然後輸出爲標準的字符串`std::string`來表示時間。

## 獲取時間間隔
- `boost::posix_time::ptime`類重載了減號，兩個`boost::posix_time::ptime`對象可以相減得到類型爲`boost::posix_time::time_duration`的時間間隔。
- `boost::posix_time::time_duration`可以使用`total_microseconds()`、`total_milliseconds()`、`total_nanoseconds()`、`total_seconds()`分別獲取時間間隔對應的微秒/毫秒/納秒/秒等作爲單位的時間表示。



# std::chrono (標準時間庫)
`std::chrono`是C++11中引入的標準時間庫，來自於`boost::chrono`。

`std::chrono`中主要包含以下內容：

- `std::chrono::duration`用於表示一段**時間間隔**。
- `std::chrono::time_point`用於表示某一個**時間點**。
- `std::chrono::system_clock`用於表示系統時鐘。
- `std::chrono::steady_clock`遞增時鐘(不會因爲時鐘修改而減少值)。

## std::chrono::duration
`std::chrono::duration`在`GCC 6.2.1`的定義如下：

```cpp
template<typename _Rep, typename _Period = ratio<1>>
struct duration;
```

- `_Rep`爲時間的數值類型，可以爲`int`、`double`等常見的數值類型。
- `_Period`爲時間的**單位**，以**秒**作爲換算基準，使用`std::ratio`類型表示。

時間間隔相關類型定義：

- 類型`std::radio`

	`std::ratio`類型用於描述換算比，基本定義如下：

	```cpp
	template<intmax_t _Num, intmax_t _Den = 1>
	struct ratio
	{
		...
	};
	```

	模板參數均爲數值，`_Num`爲分子，`_Den`爲分母。
	`std::ratio<1, 1>`表示`1/1`即`1`，`std::ratio<200, -1>`表示`200/-1`即`-200`。

- 時間單位

	標準庫時間以秒爲換算基礎(即將**秒**定義爲`std::radio<1, 1>`)，定義了其它標準時間單位：

	```cpp
	/// nanoseconds
	typedef duration<int64_t, nano> nanoseconds;
	/// microseconds
	typedef duration<int64_t, micro> microseconds;
	/// milliseconds
	typedef duration<int64_t, milli> milliseconds;
	/// seconds
	typedef duration<int64_t> seconds;
	/// minutes
	typedef duration<int64_t, ratio<60>> minutes;
	/// hours
	typedef duration<int64_t, ratio<3600>> hours;
	```

	其中，`nano`、`micro`、`milli`的定義在`radio`頭文件中：

	```cpp
	typedef ratio<1, 1000000000> nano;
	typedef ratio<1, 1000000> micro;
	typedef ratio<1, 1000> milli;
	```

- 時間轉換

	不同的時間單位之間相互轉換使用`std::chrono::duration_cast()`函數，該函數定義如下：

	```cpp
	/// duration_cast
	template<typename _ToDur, typename _Rep, typename _Period>
	constexpr typename enable_if<__is_duration<_ToDur>::value, _ToDur>::type
	duration_cast(const duration<_Rep, _Period>& __d)
	{
		...
	}
	```

	模板參數`_ToDur`表示需要轉換成的目標時間單位，`_Rep`、`_Period`用於表示被轉換時間的單位。
	簡單的用法示例：

	```cpp
	#include <iostream>
	#include <chrono>

	int main(void)
	{
		std::chrono::hours hour(1); //一個小時的時間間隔
		std::chrono::minutes mintue = std::chrono::duration_cast<std::chrono::minutes>(hour); //轉換爲分鐘
		std::cout << "Hour: " << hour.count() << std::endl;
		std::cout << "Mintue: " << mintue.count() << std::endl;

		return 0;
	}
	```

	輸出結果：(GCC 6.2.1 && ArchLinux x64)

	```
	Hour: 1
	Mintue: 60
	```

## std::time_point
`std::chrono::time_point`表示某一個時間點，基本定義如下：

```cpp
template<typename _Clock, typename _Dur>
struct time_point
{
	...
};
```

模版參數`_Dur`爲時間的單位(帶有模版參數的具體`std::chrono::duration`)，`_Clock`定義了時間點使用的**時鐘類型**。

- `std::chrono::time_point`可以與時間間隔`std::chrono::duration`進行加減運算，得到新的時間點。
- 時間點同樣擁有`time_point_cast()`用於在不同單位的時間點之間進行轉換，模板參數、使用方法與`std::chrono::duration`的對應函數類似。

## 時鐘類型
時鐘類型中定義了時間的相關單位，不同的時鐘類型有着不同的精確度。

- 時鐘類型有`std::chrono::system_clock`、`std::chrono::steady_clock`、`std::chrono::high_resolution_clock`等。
- 在Linux下，`std::chrono::system_clock`的`std::chrono::duration`爲`std::chrono::nanoseconds`，即系統時間精確到**納秒**。
- `std::chrono::high_resolution_clock`代表當前系統中最高精確度的時鐘，在Linux下，該類型爲`std::chrono::system_clock`的別名。

標準時鍾`std::chrono::system_clock`具有以下常用方法：

- `std::chrono::system_clock::now()`可以獲得當前時間的時間點(`std::chrono::time_point`類型)。
- `std::chrono::system_clock::to_time_t()`/`std::chrono::system_clock::from_time_t()`函數將`std::chrono::time_point`與`POSIX`中定義的時間類型`time_t`相互轉換(`time_t`類型可進一步使用`localtime()/asctime()/ctime()`等函數進一步轉換得到可讀的時間)。

## 基本用法示例
以指定格式輸出系統時間，並進行簡單的時間運算。

```cpp
#include <iostream>
#include <chrono>

using namespace std;

int main(void)
{
	// 獲取當前系統時間
	chrono::time_point<chrono::system_clock, chrono::nanoseconds> now = chrono::system_clock::now();

	// 轉換爲POSIX標準單位
	time_t time_now = chrono::system_clock::to_time_t(now);

	// 輸出時間內容
	tm* st_tm = localtime(&time_now);
	cout << "Year: " << st_tm->tm_year << endl;
	cout << "Month: " << st_tm->tm_mon << endl;
	cout << "Hour: " << st_tm->tm_hour << endl;
	cout << "Minute: " << st_tm->tm_min << endl;

	// 以標準格式打印當前時間
	cout << "\nAsctime: " << std::ctime(&time_now) << endl;

	// 當前時間添加一小時時間間隔
	chrono::time_point<chrono::system_clock, chrono::nanoseconds> now_after_hour = now + chrono::hours(1);
	time_t time_after_hour = chrono::system_clock::to_time_t(now_after_hour);

	// 輸出添加間隔後的時間
	cout << "After one hour: " << ctime(&time_after_hour) << endl;

	// 反向計算間隔，並以分鐘爲單位輸出
	cout << "Minutes: " << chrono::duration_cast<chrono::minutes>(now_after_hour - now).count() << endl;

	return 0;
}
```

輸出結果：

```
Year: 116
Month: 8
Hour: 17
Minute: 57

Asctime: Thu Sep 22 17:57:05 2016

After one hour: Thu Sep 22 18:57:05 2016

Minutes: 60
```



# C/C++中一些編碼中遇到的錯誤

## multiple definition of
在頭文件中定義全局變量，若該頭文件被多次包含，會出現**多重定義**錯誤，
即使你在頭文件的定義中正確地使用了`#ifndef #define #endif`或是`#pragma once`宏。

正確的定義全局變量的方法是將定義寫在代碼文件中，然後在頭文件裏用`extern`關鍵字添加聲明即可。

`#ifndef #define #endif`宏只能保證**編譯階段**代碼段不被重複包含，但變量定義是對每個源文件均有效，
源文件編譯得到的目標文件裏每一個都含有該變量的定義，雖然編譯時不會報錯，
但當目標文件連接時，多個目標文件中包含相同變量定義會產生多重定義衝突。

在C++中，若全局變量定義在某個命名空間中，則源碼中的定義和頭文件中的`extern`聲明需要位於相同命名空間中。

舉例：

```cpp
// 頭文件 xxx.h
namespace A
{
	extern int a;
}

// 代碼文件 xxx.cc
namespace A
{
	int a = 0;
}
```

## 在 switch 的 case 語句中定義局部變量
在C語言中，不允許在`switch`的`case`語句內直接定義局部變量，以下語句是錯誤的：

```cpp
int a = 0;
switch (a)
{
case 0:
	int b = 0;
	break;
}
```

無法通過編譯，C語言編譯器會提示`crosses initialization of 'int b'`。
以上語句在C++編譯器中也會給出同樣的錯誤。

但C++中允許另一種寫法：

```cpp
int a = 0;
switch (a)
{
case 0:
	int b;
	b = 0;
	break;
}
```

將定義與賦值拆開可以通過C++編譯器，但依舊會在C編譯器中報錯。
出現此種情況是因爲在C/C++中，case標籤不具有獨立的作用域，同時在不使用break語句的情況下，
case標籤中的變量定義語句根據傳入值的不同不一定會被執行，變量不一定會被定義，因而在C/C++中不允許這樣的行爲。
正確的做法是在需要在case標籤內容中定義變量時使用`{}`來構建一個獨立作用域，使變量定義對其它case標籤不可見。
示例：

```cpp
int a = 0;
switch (a)
{
case 0:
	{
		int b = 0;
		break;
	}
}
```

以上代碼可以在C/C++編譯器中編譯通過。



# 常用的C標準庫函數
在C++中，爲標準C庫頭文件提供了對應的C++版本，示例：

| C標準庫頭文件 | C++標準庫頭文件 | 主要功能 |
| :-: | :-: | :- |
| stdio.h | cstdio | IO函數，如`printf()`、`scanf()`等 |
| string.h | cstring | 字符處理函數，如`strcmp()`、`strlen()`等 |
| stddef.h | cstddef | 基礎類型定義 |
| stdlib.h | cstdlib | 數值轉換(`atoi()`等)、內存分配(`malloc()`、`free()`等)，系統功能(`exit()`、`system()`等) |
| stdint.h | cstdint | 擴展的整形定義，如`uint8_t`、`uint64_t/`等 |
| time.h | ctime | 時間函數，如`ctime()`、`asctime()`、`localtime()`等 |
| math.h | cmath | 數學函數，如`abs()`、`sin()`、`cos()`等 |

## memset()
初始化內存塊常使用`memset()`函數，函數定義爲：

```c
#include <string.h>
void* memset(void* s, int c, size_t n);
```

作用是將指針`s`所指向的區域的前`n`位用`ASC`碼值`c`填充。
注意`c`的取值爲`ASC`碼值，即如果`c`取`0`，則指針`s`所指向的區域的前`n`爲全部用空白填充(相當於全是`\0`)，如果`c`取`49`，
則相當於用數字`1`來填充，依此類推。

## memcpy()
拷貝內存常用`memcpy()`函數，函數定義爲：

```c
#include <string.h>
void *memcpy(void *dest, const void *src, size_t n);
```

從指針`src`指向的內容中複製`n`個字節到`dest`指針指向的內容。
函數返回值是一個指向`dest`指向內容的指針。

## strcpy() 函數
複製字符數組常用`strcpy()`函數，函數定義爲：

```c
#include <string.h>
char* stpcpy(char* restrict s1, const char* restrict s2);
```

將指針`s2`指向的內容複製到`s1`指向的區域。
函數返回指針複製內容後的指針`s1`，返回值的作用是使該函數能夠更連貫地用於表達式。

## setjmp() / longjmp()
使用`goto`語句只能在函數內部進行跳轉，使用`setjmp()/longjmp()`函數能夠實現**跨函數跳轉**。
`setjmp()/longjmp()`常用在**錯誤處理**中，程序在各個位置的異常都可以跳轉回一個統一的位置進行錯誤處理。

函數定義如下：

```c
#include <setjmp.h>
int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);
```

- `env`參數保存函數局部棧數據，用於之後的狀態恢復。
- `val`參數用於指定`longjmp()`調用後，從`setjmp()`函數恢復時的返回值。

通過調用`setjmp()`函數設置恢復點，調用`setjmp()`函數之後，會將當前局部環境信息寫入`env`變量中用於之後的恢復操作。
首次調用`setjmp()`函數返回值爲`0`，之後調用`longjmp()`函數可跳轉到上次調用`setjmp()`的位置，
`longjmp()`函數中的參數`val`爲`setjmp()`返回值。
在`setjmp()`調用後，直到從`longjmp()`函數返回期間，信號會一直被**阻塞**。

示例：

```c
#include <stdio.h>
#include <setjmp.h>

jmp_buf env; //env變量用於保存函數棧信息

void func(void)
{
	printf("Call func()\n");
	longjmp(env, 1); //跳轉回setjmp()的位置，setjmp()的返回值爲-1
	printf("After longjmp()\n"); //longjmp()之後的代碼沒有執行
}

int main(void)
{
	switch(setjmp(env)) //跨函數跳轉
	{
	case 0:
		printf("First\n");
		func();
		break;
	case 1:
		printf("Second\n");
		break;
	}

	return 0;
}
```

運行結果：(GCC 5.4.0 && ArchLinux x64)

```
First
Call func()
Second
```

## sigsetjmp() / siglongjmp()
`POSIX`對於使用在**信號處理函數**內部使用`longjmp()`跳轉回`setjmp()`位置時是否恢復信號狀態**未定義**。
在不同的Unix中，從`longjmp()`跳轉回`setjmp()`位置時可能恢復信號處理和信號屏蔽，也可能**不恢復**。
實測在`Linux`中**不會**恢復信號狀態。

`POSIX`提供了`sigsetjmp()/siglongjmp()`用於在**信號處理函數**內部進行跳轉。

```c
#include <setjmp.h>
int sigsetjmp(sigjmp_buf env, int savesigs);
void siglongjmp(sigjmp_buf env, int val);
```

- `savesigs`參數用於設置是否保存信號狀態，取`0`時不保存信號數據，取**非零**保存信號狀態。

若**不保存**信號狀態，則從信號處理函數內跳轉回`setjmp()`位置時，原有的信號處理函數綁定、信號屏蔽字都會恢復默認值。

示例：

```c
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

jmp_buf env; //env變量用於保存函數棧信息

void deal_signal(int sig_num)
{
	printf("Deal signal!\n");
	siglongjmp(env, 1);
}

int main(void)
{
	signal(SIGINT, deal_signal);

	switch(sigsetjmp(env, 0)) //不保存信號數據則跳轉回此處時原先註冊的信號處理函數失效
	{
	case 0:
		printf("First\n");
		break;
	case 1:
		printf("Second\n");
		break;
	}

	sleep(5);

	return 0;
}
```

運行結果(GCC 5.3.0 && ArchLinux x64)：

```
First
^CDeal signal!
Second
^C^C^C^C
```

第一次發送`SIGINT`信號觸發了`deal_signal()`函數，從信號處理函數`deal_signal()`內部跳轉回`sigsetjmp()`位置時，
由於之前**未設置**保存信號數據，因而再次接收到信號`SIGINT`時，`deal_signal()`函數不再觸發，直到程序結束。

若保存信號數據(`setjmp()`的`savesig`參數爲`1`時)，函數輸出結果爲：

```
First
^CDeal signal!
Second
^CDeal signal!
Second
......
```

可以看出，保存信號數據的情況下，`SIGINT`信號無論多少次發送都會正常跳轉會`sigsetjmp()`位置。

## getopt() / getopt_long()
`getopt()/getopt_long()`用於處理命令行參數。定義如下：

```c
#include <unistd.h>
int getopt(int argc, char* const argv[], const char* optstring);

extern char* optarg;
extern int optind, opterr, optopt;

#include <getopt.h>
int getopt_long(int argc, char* const argv[],
		const char* optstring, const struct option* longopts, int* longindex);
int getopt_long_only(int argc, char* const argv[], const char* optstring,
		const struct option* longopts, int* longindex);
```

使用`getopt()`函數處理單字符參數，如`-v/-x/-h`等：

- `argc/argv`參數爲從`main()`函數中傳入的命令行參數信息。
- `optstring`參數爲接收參數的字符數組。

`optstring`參數按以下規則解析：

- 一個字符表示接收一個對應參數，如`"vxh"`表示接收參數格式`-v -x -h`。
- 字符後添加單冒號表示參數帶有內容，如`"h:"`表示接收參數格式`-h xxx`、`-hxxx`，若參數未添加內容則不被識別(如`-h`)。
- 字符後添加雙冒號表示參數帶有可選的參數內容，如`"h::"`表示接收參數格式`-h xxx`、`-hxxx`或`-h`，不強制要求參數帶有內容。

若參數帶有內容，參數的內容會被寫入全局變量`optarg`中(變量聲明在頭文件`getopt.h`中)。
每次執行`getopt()`函數僅會獲取一個參數，獲取多個參數需要循環執行`getopt()`函數。
通過全局變量`optind`決定獲取參數的位置，`getopt()`函數內部會修改`optind`的值。

執行成功時，`getopt()`函數返回匹配到的參數字符(`ASCII`值)，失敗時返回`-1`。

實例代碼如下：

```c
#include <getopt.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	char arg = 0;
	while ((arg = getopt(argc, argv, "ab:c::")) > 0)
	{
		switch (arg)
		{
		case 'a':
			printf("Receive arg: -a\n");
			break;
		case 'b':
			printf("Receive arg: -b, content: %s\n", optarg);
			break;
		case 'c':
			printf("Receive arg: -c, content: %s\n", optarg);
			break;
		}
	}

	return 0;
}
```

編譯測試：

```
$ cc test.c -o test_arg

$ test_arg -a
Receive arg: -a

$ test_arg -b
test_arg: option requires an argument -- b

$ test_arg -bssss
Receive arg: -b, content: ssss

$ test_arg -b ssss
Receive arg: -b, content: ssss

$ test_arg -c
Receive arg: -c, content: (null)

$ test_arg -cssss
Receive arg: -c, content: ssss

$ test_arg -a -bbbbb -ccccc
Receive arg: -a
Receive arg: -b, content: bbbb
Receive arg: -c, content: cccc
```

`getopt()`僅支持單字符參數，`getopt_long()`支持長參數，如`--version --help`等：

- `argc/argv/optstring`等參數與`getopt()`函數中功能類似。
- `longopts`參數爲長指令的描述結構數組。
- `longindex`參數爲匹配到的指令在`longopts`數組中位置(傳入地址，匹配到長指令時索引值寫入該地址，
如匹配到短指令或未匹配到指令，則不設置該參數)。

`longopts`參數的類型爲`struct option`，定義在`getopt.h`文件中：

```c
struct option
{
	const char* name;
	int has_arg;
	int* flag;
	int val;
};
```

- `name`成員爲長參數的名稱，不包含`--`部分。
- `has_arg`成員標識參數是否帶有參數內容，`getopt.h`頭文件中定義了以下行爲：
	- `no_argument` 不包含參數
	- `required_argument` 要求參數內容
	- `optional_argument` 可選參數內容
- `flag`成員用於決定函數的返回行爲，取值`nullptr`時函數返回`val`成員的值，否則函數返回`0`，並將`val`內容寫入該地址。
- `val`成員在`flag`取值`nullptr`時做爲函數的返回值。

示例：

```c
#include <getopt.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int arg, index, flag = -1;

	struct option opts[] =
	{
		{ "aaa", no_argument, NULL, 'a' },
		{ "bbb", required_argument, NULL, 'b' },
		{ "ccc", optional_argument, NULL, 'c' },
		{ "23", no_argument, &flag, 2333 }
	};

	while ((arg = getopt_long(argc, argv, "ab:c::", (struct option*)&opts, &index)) >= 0)
	{
		switch (arg)
		{
		case 'a':
			printf("Receive arg: -a, index: %d\n", index);
			break;
		case 'b':
			printf("Receive arg: -b, content: %s, index: %d\n", optarg, index);
			break;
		case 'c':
			printf("Receive arg: -c, content: %s, index: %d\n", optarg, index);
			break;
		case 0:
			printf("Receive arg: --23, index: %d, flag: %d\n", index, flag);
			break;
		}
	}

	return 0;
}
```

編譯測試：

```
$ cc test.c -o test_arg

$ test_arg -b
test_arg: option requires an argument -- b

$ test_arg -b=2333
Receive arg: -b, content: =2333, index: -1

$ test_arg -b 2333
Receive arg: -b, content: 2333, index: -1

$ test_arg --bbb
test_arg: option requires an argument -- bbb

$ test_arg --bbb=2333
Receive arg: -b, content: 2333, index: 1

$ test_arg --bbb 2333
Receive arg: -b, content: 2333, index: 1

$ test_arg --23
Receive arg: --23, index: 3, flag: 2333
```



# 一些關鍵字、特殊值的含義/用法

## explicit 關鍵字
C++中的關鍵字`explicit`作用是防止構造函數隱式轉換的發生。

默認情況下，在C++中，使用`類名 實例名 = 參數`的形式創建一個類的實例。
當`參數`剛好符合類的構造函數參數要求，此時編譯器會隱式的調用這個類的構造函數來創建類的實例。
但有些情況下，需要避免這種隱式轉換的發生，這時，在類的構造函數聲明時，
在在構造函數名之前加上`explicit`關鍵字即可避免隱式轉換髮生。

採用`explicit`關鍵字聲明的構造函數只能夠被顯式地調用。

## restrict 關鍵字
`C99`中新引入了關鍵字`restrict`，restrict關鍵字用在指針的定義中，格式爲`變量類型* restrict 指針名`，
作用是是告知編譯器該指針是指針所指向區域的**唯一**訪問方式，
所有修改該指針指向內容的操作都只能通過該指針進行，而**不能**通過其它變量或指針來修改。

restrict關鍵字不會改變指針的用法，但會讓編譯器更加安全高效準確地優化代碼，
使用restrict關鍵字定義的指針的指向不應進行改動。restrict關鍵字只在支持`C99`以上的C編譯器中使用，
C++**無**該關鍵字。

## mutable 關鍵字
`mutable`關鍵字用於定義一個易變的變量，只能用於修飾類的非靜態數據成員，語法格式上與`const`類似。
普通成員變量在`const`修飾的成員函數中不可修改，
但使用了`mutable`關鍵字定義的變量，即使是在const成員函數中，依然可被修改。

C語言**無**該關鍵字。

## volatile 關鍵字
`volatile`用在變量數據可能會被意外修改的場景，
使用volatile關鍵字修飾的變量能避免被編譯器優化。

一些應用場景包括：

1. 驅動開發，申請的內存地址可能會被外部硬件改變
1. Unix信號，信號處理函數中修改的變量

volatile修飾的變量**不能**保證多線程下的數據安全，
多線程下的數據安全需要加鎖、原子類型等常規手段保證。

## using 關鍵字
`using`用於簡化處於命名空間中的內容的使用。如：

```cpp
using namespace std;
using std::string;
using namespace 命名空間名稱;
using 命名空間名稱::類型名稱/變量名稱;
```

using用於定義類型的別名(類似於typedef)。如：

```cpp
using List = std::list<int>; //等價於 typedef class std::list<int> List;
using point = int (*a)(int, int);
```

using用於定義模板類型的部分有參別名(typedef不能定義部分參數化模版類型)。如：

```cpp
template <class T>
using Map = std::map<int, T>;
```

using用於在子類隱藏了父類的函數時，使子類能夠使用父類原先被隱藏的函數。如：

```cpp
using 父類類名::被隱藏函數的函數名;
```

## 移位運算符
移位運算符的作用是將一個數的對應二進制值左移或右移指定的位數。

```cpp
int a = 1;
int b = a << 10; //b = 1024
int c = b >> 5; //c = 32
```

`a`的二進制值也是1，將十進制的1的二進制值左移10位則結果爲`1 * 2 ^ 10`，即1024。
1024的二進制值右移5位結果爲`1 * 2 ^ 5`，即32。

## npos 成員
多數C++標準容器都提供了`npos`成員，`npos`用來表示不會被取到的下標，類型爲`容器類型::size_type`，
一般取值爲`-1`(實際值取決於編譯器的具體實現)。

使用容器提供的`find()`成員函數查找內容時，如果目標內容沒有被找到，則返回`容器類型::npos`。



# 常見錯誤

## error: jump to case label
對於`switch`語句，每個`case`子句不具有獨立作用域，在`case`子句中定義局部變量需要使用花括號建立獨立作用域。
若未未使用花括號建立獨立作用域且`case`子句內創建的變量不同，則出現此警告。

## warning: `...` will be initialized after [-Wreorder] ...
在構造方法中使用初始化列表，若初始化列表中參數順序與類定義中出現的順序不同，則出現此警告。
