<!-- TOC -->

- [概述](#概述)
	- [開發環境](#開發環境)
	- [F# Interactive (F#交互式環境)](#f-interactive-f交互式環境)
	- [與主流語言的語法差異](#與主流語言的語法差異)
- [Function (函數)](#function-函數)
	- [可選參數](#可選參數)
	- [參數默認值](#參數默認值)
	- [Entry Point (入口點/函數)](#entry-point-入口點函數)
- [Pattern Matching (模式匹配)](#pattern-matching-模式匹配)
	- [Constant Patterns (常量模式)](#constant-patterns-常量模式)
	- [Identifier Patterns (標識符匹配)](#identifier-patterns-標識符匹配)
	- [Active Patterns (活動模式)](#active-patterns-活動模式)
	- [`as` / `when`](#as--when)
	- [`&` / `|`](#--)
- [Namespaces & Modules](#namespaces--modules)
	- [命名空間](#命名空間)
	- [模塊](#模塊)
- [let & val](#let--val)
- [Collections (集合類型)](#collections-集合類型)
- [Computation Expressions (計算表達式)](#computation-expressions-計算表達式)
	- [計算表達式語法](#計算表達式語法)
	- [內置計算表達式](#內置計算表達式)
	- [自定義計算表達式](#自定義計算表達式)
- [Type Providers](#type-providers)

<!-- /TOC -->



# 概述
F#是微軟推出、運行在.NET平台的函數式語言，F#的最初設計源於ML語族的OCaml語言。

## 開發環境
F#現在已經集成在[.NET Core SDK](https://dotnet.microsoft.com/download/visual-studio-sdks)中，
從官方下載SDK即可使用F#。

F#的官方IDE是微軟提供的[`Visual Studio`](https://visualstudio.microsoft.com/)。
其它廠商/社區提供的開發環境包括[`JetBrains Rider`](https://www.jetbrains.com/rider/)，
[`Visual Studio Code`](https://code.visualstudio.com/)的[`Ionide`](https://ionide.io/)插件。

## F# Interactive (F#交互式環境)
F#同樣提供了類似Haskell、Scala的交互式環境：

```
$ dotnet fsi
```

在F#的交互式環境中，使用`#`標記特殊指令，使用`;;`結束語句，查看常用指令：

```
> #help;;

  F# Interactive directives:

    #r "file.dll";;        Reference (dynamically load) the given DLL
    #I "path";;            Add the given search path for referenced DLLs
    #load "file.fs" ...;;  Load the given file(s) as if compiled and referenced
    #time ["on"|"off"];;   Toggle timing on/off
    #help;;                Display help
    #quit;;                Exit

  F# Interactive command line options:

      See 'dotnet fsi --help' for options
```

## 與主流語言的語法差異
F#繼承了大部分OCaml的設計，與主流語言存在一些差異。

- 相等性比較運算符為`=`/`<>`，而不是其它語言中常見的`==`/`!=`。

	```fs
	> if 1 = 1 then true else false;;
	val it : bool = true

	> if 1 <> 1 then true else false;;
	val it : bool = false
	```

- 逗號`,`語法高度一致，始終用與構成元組。

	在列表生成式中：

	```fs
	> 1, 2, 3;;
	val it : int * int * int = (1, 2, 3)

	> [1, 2, 3];;
	val it : (int * int * int) list = [(1, 2, 3)]
	```

	C#中的多參數函數在F#中亦被視作參數為一個多值元組。

	在模式匹配、let綁定等場景下進行元組匹配不用像其它函數式語言那樣使用小括號：

	```fs
	> match 1, 2, 3 with
	- | a, b, c -> printfn $"{a}, {b}, {c}"
	- ;;
	1, 2, 3
	val it : unit = ()

	> let a, b = 1 + 2, "abc" + "cde"
	- ;;
	val b : string = "abccde"
	val a : int = 3
	```

- 位運算符與主流語言不同。

	邏輯與`&&&`、或`|||`、非`~~~`、異或`^^^`。

	```fs
	> 1 &&& 2;;
	val it : int = 0

	> 1 ||| 2;;
	val it : int = 3

	> 1 ^^^ 2;;
	val it : int = 3

	> ~~~1;;
	val it : int = -2
	```

	左移位`<<<`，右移位`>>>`。

	```fs
	> 1 <<< 1;;
	val it : int = 2

	> 1 >>> 1;;
	val it : int = 0
	```



# Function (函數)
F#中的函數支持Haskell風格的單參數柯里化風格，也支持C#的多參數風格(將參數表視為一個元組)。

詳情可參考[微軟官方文檔](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/parameters-and-arguments)。

函數定義風格實例：

```fs
// 元組風格，對應C#中的函數參數表
member this.SomeMethod(param1, param2) = ...
// 柯里化風格
let function1 param1 param2 = ...

// 兩種風格亦可組合使用
let function2 param1 (param2a, param2b) param3 = ...
```

在使用柯里化風格的函數定義時，相當於每接收一個參數就返回一個新函數然後繼續接收參數，
直到接收完了所有定義的參數：

```fs
> let add a b c = a + b + c;;
val add : a:int -> b:int -> c:int -> int

> add 1;;
val it : (int -> int -> int) = <fun:it@33-4>

> add 1 2;;
val it : (int -> int) = <fun:it@35-5>

> add 1 2 3;;
val it : int = 6
```

## 可選參數
F#在類型方法上可使用`?`語法將一個參數標記為可選參數：

```fs
type DuplexType =
    | Full
    | Half

type Connection(?rate0 : int, ?duplex0 : DuplexType, ?parity0 : bool) =
    let duplex = defaultArg duplex0 Full
    let parity = defaultArg parity0 false
    let mutable rate = match rate0 with
                        | Some rate1 -> rate1
                        | None -> match duplex with
                                  | Full -> 9600
                                  | Half -> 4800
    do printfn "Baud Rate: %d Duplex: %A Parity: %b" rate duplex parity

let conn1 = Connection(duplex0 = Full)
let conn2 = Connection(duplex0 = Half)
let conn3 = Connection(300, Half, true)
let conn4 = Connection()
let conn5 = Connection(?duplex0 = Some(Full))

let optionalDuplexValue : option<DuplexType> = Some(Half)
let conn6 = Connection(?duplex0 = optionalDuplexValue)
```

使用了`?`標記的參數實際類型將從`'a`變為`'a option`，
在調用方法時，該參數位置對應可不傳參，未傳參時對應參數位置得到值為`None`。

只有類型的成員方法、構造方法參數可使用此語法，在函數上使用該語法會得到錯誤：

```fs
> let add (?a: int) (?b: int) = a + b;;

  let add (?a: int) (?b: int) = a + b;;
  ---------^^

/Users/dainslef/stdin(57,10): error FS0718: Optional arguments are only permitted on type members
```

## 參數默認值
還可以使用`System.Runtime.InteropServices`命名空間下的特性將參數標記為可選參數，並為參數提供默認值。

```fs
open System.Threading
open System.Runtime.InteropServices
type C =
    static member Foo([<Optional; DefaultParameterValue(CancellationToken())>] ct: CancellationToken) =
        printfn "%A" ct
```

被`System.Runtime.InteropServices.OptionalAttribute`特性標註的可選參數不會改變簽名中的實際類型。
由`System.Runtime.InteropServices.DefaultParameterValueAttribute`特性為可選參數顯式提供默認值。

## Entry Point (入口點/函數)
F#項目中，使用特性`[<EntryPoint>]`標註一個函數，使之成為入口函數。

```fs
[<EntryPoint>]
let main args = ...
```

與C#不同，F#中的入口函數對函數名稱無要求，僅函數簽名需要滿足：

```fs
string array -> int
```



# Pattern Matching (模式匹配)
**模式匹配**是函數式語言中常見的基礎功能，F#同樣提供了強大的模式匹配功能，
詳細可參考[微軟官方文檔](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/pattern-matching)。

## Constant Patterns (常量模式)
常量模式包括數值、字符、文本字面量、常量枚舉等。

```fs
[<Literal>] // 使用Literal特性，字段可用於模式匹配中
let Three = 3

let filter123 x =
    match x with
    // 常量模式匹配
    | 1 | 2 | Three -> printfn "Found 1, 2, or 3!"
    // 變量模式
    | var1 -> printfn "%d" var1

for x in 1..10 do filter123 x
```

## Identifier Patterns (標識符匹配)
對與聯合類型(union type)的每一個用例(case)可按照類型的定義進行匹配：

```fs
// 匹配標準庫內的 'a option 類型
let printOption (data : int option) =
    match data with
    | Some var1  -> printfn "%d" var1
    | None -> ()

// 自定義聯合類型
type PersonName =
    | FirstOnly of string
    | LastOnly of string
    | FirstLast of string * string

// 按照自定義類型的結構進行匹配並解構
let constructQuery personName =
    match personName with
    | FirstOnly(firstName) -> printf "May I call you %s?" firstName
    | LastOnly(lastName) -> printf "Are you Mr. or Ms. %s?" lastName
    | FirstLast(firstName, lastName) -> printf "Are you %s %s?" firstName lastName
```

若聯合類型使用了命名字段(named fields)，則解構時可以等號(=)將指定字段解構到變量中：

```fs
// 定義命名聯合類型
type Shape =
    | Rectangle of height : float * width : float
    | Circle of radius : float

let matchShape shape =
    match shape with
    | Rectangle(height = h) -> printfn "Rectangle with length %f" h
    | Circle(r) -> printfn "Circle with radius %f" r // 解構時的名稱綁定是可選的
```

當需要顯式解構多個字段時，使用`;`進行分隔：

```fs
match shape with
| Rectangle(height = h; width = w) -> printfn "Rectangle with height %f and width %f" h w
| _ -> ()
```

## Active Patterns (活動模式)
**活動模式**能夠針對特定類型提供自定義的解構邏輯。

`(|XXX|XXX|)`語法稱為香蕉剪輯(banana clips)，定義用於匹配的模式，
函數的輸入內容為需要結構的目標對象，返回類型需要為香蕉剪輯中定義的模式。
函數創建的內容稱為模式識別器(active recognizer)：

```fs
let (|Pattern1|Pattern2|Pattern3|) target =
    if ... then Pattern1(...)
    elif ... then Pattern2(...)
    else Pattern3
```

定義活動模式時，無須需要一次定義所有模式識別器，還可以定義部分活動模式(partial active patterns)，
用於匹配滿足某些條件的輸入數據，在該模式未匹配成功時繼續匹配其它模式。
部分活動模式香蕉剪輯以`(|_|)`結尾，返回類型為`option`類型。

```fs
let (|PartialPattern|_|) target = if ... then Some(...) else None
```

定義活動模式的函數至少需要接收一個參數用於表示被匹配的目標，
當活動模式函數擁有多個參數時，被稱為參數活動模式(parameterized active pattern)，
最後一個參數表示被匹配的目標，其它參數在編寫模式時傳入：

```fs
let (|ParameterizedPattern|_|) arg1 arg2 target = if ... then Some(...) else None

// 除了用於匹配的參數外，其餘參數在匹配模式時傳入
match target with
| ParameterizedPattern arg1 arg2 ... -> ...
| ParameterizedPattern argXxx argXxx ... -> ...
| ...
```

完整的活動模式用法實例：

```fs
type Point(?a: int, ?b: int, ?c: string) =
    member val X = a |> Option.defaultValue 0 with get, set
    member val Y = b |> Option.defaultValue 0 with get, set
    member _.Message = c |> Option.defaultValue ""

// (||) 語法稱為香蕉剪輯(banana clips)，定義用於匹配的模式，函數的返回類型需要為香蕉剪輯中定義的模式
// 函數創建的內容稱為模式識別器(active recognizer)
let (|Pattern1|Pattern2|Pattern3|) (p: Point) =
    if p.X < 0 then Pattern1(p.X)
    elif p.Y < 0 then Pattern2(p.Y)
    else Pattern3

// 定義部分活動模式，香蕉剪輯以(|_|)結尾，返回類型為option類型
let (|PartialPattern1|_|) (p: Point) =
    if p.X > 0 && p.Y > 0 then Some((p.X, p.Y)) else None

let (|PartialPattern2|_|) (p: Point) =
    if not <| isNull p.Message && p.Message.Length <> 0
    then Some(p.Message)
    else None

// 參數活動匹配
let (|ParameterizedPattern|_|) ((x: int, y: int) as v) (p: Point) =
    if p.X = x && p.Y = y then Some((v, p)) else None

// 使用定義的模式
let printPoint (p: Point) =
    match p with
    | ParameterizedPattern (10, 10) p -> printfn "ParameterizedPattern: Value: %A" p
    | PartialPattern1 (x, y) -> printfn "PartialPattern1: X: %d, Y: %d" x y
    | PartialPattern2 message -> printfn "PartialPattern2: Message: %s" message
    | Pattern1 v
    | Pattern2 v -> printfn "Pattern1|Patterns2: Value: %d" v
    | Pattern3 -> printfn "Pattern3"

open Microsoft.VisualStudio.TestTools.UnitTesting

[<TestClass>]
type Test() =

    [<TestMethod>]
    member _.TestPattern() =
        [ Point(10, 10)
          Point(1, 1)
          Point(-1, -1, c = "Test")
          Point(-1, 2)
          Point(2, -1)
          Point() ]
        |> List.map printPoint
        |> ignore
```

輸出結果：

```
ParameterizedPattern: Value: ((10, 10), FSharpPractice.Pattern+Point)
PartialPattern1: X: 1, Y: 1
PartialPattern2: Message: Test
Pattern1|Patterns2: Value: -1
Pattern1|Patterns2: Value: -1
Pattern3
```

## `as` / `when`
F#在模式匹配中可以使用`when`關鍵字提供類似Haskell、Scala中的守衛(guard)功能：

```fs
let function1 x =
    match x with
    | (var1, var2) when var1 > var2 -> printfn "%d is greater than %d" var1 var2
    | (var1, var2) when var1 < var2 -> printfn "%d is less than %d" var1 var2
    | (var1, var2) -> printfn "%d equals %d" var1 var2

function1 (1, 2)
function1 (2, 1)
function1 (0, 0)
```

`as`關鍵字提供了類似Haskell、Scala中的`@`綁定功能，為匹配到的值綁定一個新的變量名稱：

```fs
let (var1, var2) as tuple1 = (1, 2)
printfn "%d %d %A" var1 var2 tuple1
```

## `&` / `|`
模式匹配中同樣可以使用邏輯運算符(`&`、`|`)連接多個模式：

```fs
// 邏輯或操作符
let detectZeroOR point =
    match point with
    | (0, 0) | (0, _) | (_, 0) -> printfn "Zero found."
    | _ -> printfn "Both nonzero."
detectZeroOR (0, 0)
detectZeroOR (1, 0)
detectZeroOR (0, 10)
detectZeroOR (10, 15)

// 邏輯與操作符
let detectZeroAND point =
    match point with
    | (0, 0) -> printfn "Both values zero."
    | (var1, var2) & (0, _) -> printfn "First value is 0 in (%d, %d)" var1 var2
    | (var1, var2)  & (_, 0) -> printfn "Second value is 0 in (%d, %d)" var1 var2
    | _ -> printfn "Both nonzero."
detectZeroAND (0, 0)
detectZeroAND (1, 0)
detectZeroAND (0, 10)
detectZeroAND (10, 15)
```



# Namespaces & Modules
F#中存在兩類代碼的組織結構，分別是`Namespaces`(命名空間)和`Modules`(模塊)。
相關概念可參考[微軟官方文檔](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/namespaces)
以及[Wiki](https://en.wikibooks.org/wiki/F_Sharp_Programming/Modules_and_Namespaces)。

## 命名空間
命名空間是C#中的概念，命名空間的名稱首字母必須大寫。
在命名空間僅能包含類型(`type`)和模塊(`module`)定義，
其它操作(定義字段、函數、執行普通語句等)均會編譯錯誤，示例：

```fs
namespace Aaa.Bbb.Ccc

type TypeXxx =
    ... // OK

module ModuleXxx =
    ... // OK

let xxx = ... // Error!
do ... // Error!
...
```

一個文件內可以定義多個命名空間，定義內部命名空間時同樣需要使用完整路徑：

```fs
namespace Aaa.Bbb.Ccc
...

namespace Aaa.Bbb.Ccc.Ddd.Eee // 不能簡寫為 Ddd.Eee
...
```

當需要將內容直接定義在全局命名空間中時，使用global關鍵字：

```fs
namespace global
...
```

當模塊/命名空間名稱產生衝突時，可顯式使用global關鍵字從根路徑訪問命名空間以解決衝突：

```fs
global.System.Console.WriteLine "Hello World!"
```

命名空間中默認不允許類型的遞歸定義，若需要開啟類型遞歸定義支持，
則需要使用`namespace rec`定義支持遞歸的命名空間。

```fs
namespace rec FSharpPractice.Lang

// Recursive Type, need "namespace rec"
type A =
    | A of A
    | B of B

type B =
    | A of A
    | B of B
```

在遞歸命名空間中，open語句有所限制，需要置於所有定義內容之前，否則會得到錯誤：

```
In a recursive declaration group, 'open' declarations must come first in each moduleF# Compiler(3200)
```

## 模塊
模塊(`module`)的概念來自OCaml，是F#中組織代碼的標準方式，模塊中內容無限制。

語法：

```fs
// Top-level module declaration.
module [accessibility-modifier] [qualified-namespace.]module-name
declarations
// Local module declaration.
module [accessibility-modifier] module-name =
    declarations
```

當是使用頂層模塊定義(Top-level module declaration)是，可以使用多級名稱，
此時最後一級名稱為模塊名稱，之前的名稱為命名空間名稱：

```fs
module Aaa.Bbb.Ccc.Ddd.Eee // 實際模塊名稱為
```

等價於：

```fs
namespace Aaa.Bbb.Ccc.Ddd

module Eee = ...
```

從`F# 4.1`開始，模塊內也支持遞歸類型定義，使用`module rec`定義允許遞歸定義的模塊。



# let & val
關鍵字`let`、`val`用於定義字段/函數，二者的用法和使用場景比較：

- `let`、`let mutable`

	let關鍵字最為常用，用於定義值/函數。
	在模塊頂層中使用時訪問權限為`public`；在類型內部使用時為訪問權限為`private`
	(相當於C#中的私有成員字段/私有成員方法)。
	let定義的字段/函數需要立即初始化。

- `val`、`val mutable`

	val只能用在類型內部，訪問權限為`public`，
	val定義的字段不能在定義處初始化，而是需要在構造器中初始化(基礎類型可使用`[<DefaultValue>]`特性)。
	val搭配member關鍵字可用於定義**自動屬性**。

更多使用場景區別可參考[Stack Overflow](https://stackoverflow.com/questions/24840948/when-should-i-use-let-member-val-and-member-this)上的討論。



# Collections (集合類型)
F#作為函數式語言，同樣提供了豐富的集合類型：

| 類型 | 描述 | 構造語法 |
| :- | :- | :- |
| list | 一系列有序、不可變的同類型元素，由鏈表實現 | `[1..10]` |
| array | 固定大小、從零開始、連續數據的可變集合 | `[|1..10|]` |
| seq | 序列用於數據集巨大、有序，但不必同時使用所有元素的情形，每個元素計算僅在需要時進行(惰性計算)。序列類型是`System.Collections.Generic.IEnumerable<'T>`的別名，所有實現該接口的類型均可作為序列使用 | `seq { 1..10 }` |
| Map | 不可變的字典類型，元素通過key來訪問 | `Map [(k1, v1), (k2, v2)]` |
| Set | 不可變的集合類型，基於二叉樹，元素需要實現`System.IComparable`接口 | `set [1..10]` |

詳細可參考[微軟官方文檔](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/fsharp-collection-types)。
官方給出了各個集合的常見操作的時間複雜度。

與.NET中提供的集合庫(`System.Collections.Generic`命名空間下)不同，
F#擁有的集合庫按照函數式風格設計，而非面向對象風格。
除了數組類型擁有可變元素，其它集合類型在修改集合時會產生新的集合，而不是在原先存在的集合上進行修改。

序列、數組、列表支持類似的初始化語法：

```fs
> [1; 2; 3];;
val it : int list = [1; 2; 3]

// 使用換行語法則不必使用分號
> [1
-  2
-  3];;
val it : int list = [1; 2; 3]

> [|1; 2; 3|];;
val it : int [] = [|1; 2; 3|]

> seq { 1; 2; 3 };;
val it : seq<int> = seq [1; 2; 3]
```

序列、數組、列表同樣支持範圍操作符(`..`)進行初始化：

```fs
> [1..5];;
val it : int list = [1; 2; 3; 4; 5]

// 使用範圍操作符時可以設定步進間隔(間隔寫在中間)
> [1..2..5];;
val it : int list = [1; 3; 5]

// 利用步進間隔逆序初始化
> [5..-1..1];;
val it : int list = [5; 4; 3; 2; 1]

> [|1..5|];;
val it : int [] = [|1; 2; 3; 4; 5|]

> seq { 1..5 };;
val it : seq<int> = seq [1; 2; 3; 4; ...]
```

序列、數組、列表還可使用for語句生成，類似Haskell、Python中的列表生成式：

```fs
> [for i in 1..10 -> 2 * i];;
val it : int list = [2; 4; 6; 8; 10; 12; 14; 16; 18; 20]

> [for i in 1..10 do 2 * i];;
val it : int list = [2; 4; 6; 8; 10; 12; 14; 16; 18; 20]

// F# 4.7 之前，do 語句需要顯式 yield
> [for i in 1..10 do yield 2 * i];;
val it : int list = [2; 4; 6; 8; 10; 12; 14; 16; 18; 20]

// yield 內容同樣可以是集合類型
> [for i in 1..10 -> [i-1..i]];;
val it : int list list =
  [[0; 1]; [1; 2]; [2; 3]; [3; 4]; [4; 5]; [5; 6]; [6; 7]; [7; 8]; [8; 9];
   [9; 10]]

// 使用 yield! 將輸出的集合拼接到一個集合中，類似 flatMap 算子
> [for i in 1..10 do yield! [i-1..i]];;
val it : int list =
  [0; 1; 1; 2; 2; 3; 3; 4; 4; 5; 5; 6; 6; 7; 7; 8; 8; 9; 9; 10]
```

對於列表類型，還支持一些額外的操作符：

```fs
> let list1 = [1..5];;
val list1 : int list = [1; 2; 3; 4; 5]

// 向列表的頭部追加元素
> let list2 = 99 :: list;;
val list2 : int list = [99; 1; 2; 3; 4; 5]

// 拼接兩個列表
> list1 @ list2;;
val it : int list = [1; 2; 3; 4; 5; 99; 1; 2; 3; 4; 5]

// 列表可使用 :: 操作符進行模式匹配
> match list1 with
- | head :: tail -> printfn "head: %A, tail: %A" head tail
- | [] -> printfn "Empty"
- ;;
head: 1, tail: [2; 3; 4; 5]
val it : unit = ()
```



# Computation Expressions (計算表達式)
F#中的計算表達式為編寫可排序和組合的計算提供了便利的語法，使之可用於控制流構造和綁定。
根據計算表達式類型的不同，可用於表達諸如`monads`、`monoids`、
`monad transformers`、`applicative functors`等概念。
與Haskell等語言不同，F#中並未給上述的函數式概念提供統一的抽象，
而是基於**宏(macros)**貨其它**元編程(metaprogramming)**來實現便利的、上下文相關的語法。

計算存在多種形式，最常見、易於理解和修改的計算形式是單線程執行，
但並非所有的計算都如同單線程執行一般直觀，例如：

- Non-deterministic computations (非確定性計算)
- Asynchronous computations (異步計算)
- Effectful computations (存在副作用的計算)
- Generative computations (生成器計算)

通常來說，這些上下文敏感的計算必須置於程序的某個特定位置。
編寫上下文敏感的代碼是具有挑戰性的，在沒有抽象機制阻止時，計算很容易被洩漏到計算上下文之外。
自行編寫這些抽象機制是具有挑戰性的，而F#提供了**計算表達式**，以通用的方式來實現此類內容。

計算表達式提供了統一的語法和抽象模型用於編碼上下文敏感的計算。
每個計算表達式基於`builder`類型，builder類型定義了在計算表達式中允許的操作。

相關內容可參考[微軟官方文檔](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/computation-expressions)。

## 計算表達式語法
計算表達式的基本語法：

```fs
builder-expr { cexper }
```

`builder-expr`是定義計算表達式的構造器類型名稱(the name of a builder type)，
`cexper`是計算表達式的表達式主體。

計算表達式中可用的操作包括：

```fs
expr { let! ... }
expr { do! ... }
expr { yield ... }
expr { yield! ... }
expr { return ... }
expr { return! ... }
expr { match! ... }
```

每個計算表達式中的操作只有在使用的buider type中定義了才允許使用，
唯一的例外是`match!`操作，該操作為`let!`的語法糖。
builder type是一個定義了特殊方法的對象，這些方法決定了計算表達式的行為。

- `let!`

	`let!`關鍵字綁定了對另一個計算表達式調用的結果：

	```fs
	let doThingsAsync url =
	    async {
	        let! data = getDataAsync url
	        ...
	    }
	```

	若使用let綁定對另一個計算表達式的結果，得到的不是計算結果，而是一個對未實現(unrealized)調用的綁定。

	let!綁定由builder type中的`Bind(x, f)`成員進行定義。

- `do!`

	`do!`關鍵字用於執行返回值為類unit類型的計算表達式：

	```fs
	let doThingsAsync data url =
	    async {
	        do! submitData data url
	        ...
	    }
	```

	對於異步工作流，執行的表達式返回類型為`Async<unit>`，對於其它計算表達式，類型為`CExpType<unit>`。

	do!由由builder type中的`Bind(x, f)`成員進行定義，其中f的類型為unit。

- `yield`

	`yield`關鍵字用於從計算表達式中返回一個值。
	標準庫中被seq計算表達式用於實現`IEnumerable<T>`：

	```fs
	let squares =
	seq {
	    for i in 1..10 do
	        yield i * i
	}

	for sq in squares do
	    printfn "%d" sq
	```

	在多數場景下，yield關鍵字可被省略，上述例子可被簡寫為：

	```fs
	let squares =
	seq {
	    for i in 1..10 -> i * i
	}

	for sq in squares do
	    printfn "%d" sq
	```

	一些複雜的計算表達式可能會yield多個不同值，並伴隨不同條件，同樣可以省略yield關鍵字：

	```fs
	> let isRight = false;;
	val isRight : bool = false

	> seq {
	-     "A"
	-     "B"
	-     if isRight then "C"
	-     "D"
	- };;
	val it : seq<string> = seq ["A"; "B"; "D"]

	> seq {
	-     "A"
	-     "B"
	-     if isRight then
	-          "C"
	-          "D"
	- };;
	val it : seq<string> = seq ["A"; "B"]
	```

- `yield!`

	`yield!`關鍵字作用與yield類似，但被返回的值需要為集合類型，yield!會將集合內容展開返回：

	```fs
	let squares =
	    seq {
	        for i in 1..3 -> i * i
	    }

	let cubes =
	    seq {
	        for i in 1..3 -> i * i * i
	    }

	let squaresAndCubes =
	    seq {
	        yield! squares
	        yield! cubes
	    }

	printfn "%A" squaresAndCubes // Prints - 1; 4; 9; 1; 8; 27
	```

	執行yield!語句會將目標內容一一展開並返回值。

	yield!關鍵字由builder type中的`YieldFrom(x)`成員定義，參數`x`需要為集合類型。

	與yield不同，yield!必須顯式使用，yield!在計算表達式中的行為不是隱式的。

- `return`

	`return`關鍵字將一個值包裝在類型中，與yield不同，yield通常可以多次生成值，
	return通常用於「完成」計算表達式(但在實際使用中，return也可以實現為允許多次生成值)：

	```fs
	let req = // 'req' is of type is 'Async<data>'
	    async {
	        let! data = fetch url
	        return data
	    }

	// 'result' is of type 'data'
	let result = Async.RunSynchronously req
	```

	return由builder type的`Return(x)`成員定義，參數`x`為需要被包裝的對象。

- `return!`

	`return!`關鍵字作用相當於`let! + return`，可直接在計算表達式中返回另一個計算表達式的生成值：

	```fs
	let req = // 'req' is of type 'Async<data>'
	    async {
	        return! fetch url
	    }

	// 'result' is of type 'data'
	let result = Async.RunSynchronously req
	```

	return!由builder type的`ReturnFrom(x)`成員定義，參數`x`為需要被包裝的對象。

## 內置計算表達式
F#核心庫提供了三類內置的計算表達式：

- 序列表達式(Sequence Expressions)
- 異步表達式(Asynchronous Workflows)
- 查詢表達式(Query Expressions)

## 自定義計算表達式
通過定義一個包含特定方法的builder class，用戶可以定義自己的計算表達式。

以下是可以在buider class中定義並被使用的特殊方法：

| Metho | Typical signature(s) | Description |
| :- | :- | :- |
| Bind | M<'T> * ('T -> M<'U>) -> M<'U> | Called for let! and do! in computation expressions. |
| Delay | (unit -> M<'T>) -> M<'T> | Wraps a computation expression as a function. |
| Return | 'T -> M<'T> | Called for return in computation expressions. |
| ReturnFrom | M<'T> -> M<'T> | Called for return! in computation expressions. |
| Run | M<'T> -> M<'T> or M<'T> -> 'T | Executes a computation expression. |
| Combine | M<'T> * M<'T> -> M<'T> or M<unit> * M<'T> -> M<'T> | Called for sequencing in computation expressions. |
| For | seq<'T> * ('T -> M<'U>) -> M<'U> or seq<'T> * ('T -> M<'U>) -> seq<M<'U>> | Called for for...do expressions in computation expressions. |
| TryFinally | M<'T> * (unit -> unit) -> M<'T> | Called for try...finally expressions in computation expressions. |
| TryWith | M<'T> * (exn -> M<'T>) -> M<'T> | Called for try...with expressions in computation expressions. |
| Using | 'T * ('T -> M<'U>) -> M<'U> when 'T :> IDisposable | Called for use bindings in computation expressions. |
| While	| (unit -> bool) * M<'T> -> M<'T> | Called for while...do expressions in computation expressions. |
| Yield	| 'T -> M<'T> | Called for yield expressions in computation expressions. |
| YieldFrom | M<'T> -> M<'T> | Called for yield! expressions in computation expressions. |
| Zero | unit -> M<'T> | Called for empty else branches of if...then expressions in computation expressions. |
| Quote | Quotations.Expr<'T> -> Quotations.Expr<'T> | Indicates that the computation expression is passed to the Run member as a quotation. It translates all instances of a computation into a quotation. |

多數buider class中的方法使用並返回`M<'T>`類型，該類型通常是被計算操作組合的特定類型，
如用於異步工作流的`Async<'T>`和用於序列工作流的`Seq<'T>`。

編譯器會將計算表達式中的內容轉換為對buider class實例的方法調用：

| Expression | Translation |
| :- | :- |
| { let binding in cexpr } | let binding in {| cexpr |} |
| { let! pattern = expr in cexpr } | builder.Bind(expr, (fun pattern -> {| cexpr |})) |
| { do! expr in cexpr }	| builder.Bind(expr, (fun () -> {| cexpr |})) |
| { yield expr } | builder.Yield(expr) |
| { yield! expr } | builder.YieldFrom(expr) |
| { return expr } | builder.Return(expr) |
| { return! expr } | builder.ReturnFrom(expr) |
| { use pattern = expr in cexpr } | builder.Using(expr, (fun pattern -> {| cexpr |})) |
| { use! value = expr in cexpr } | builder.Bind(expr, (fun value -> builder.Using(value, (fun value -> { cexpr })))) |
| { if expr then cexpr0 } | if expr then { cexpr0 } else builder.Zero() |
| { if expr then cexpr0 else cexpr1 } | if expr then { cexpr0 } else { cexpr1 } |
| { match expr with | pattern_i -> cexpr_i } | match expr with | pattern_i -> { cexpr_i } |
| { for pattern in expr do cexpr } | builder.For(enumeration, (fun pattern -> { cexpr })) |
| { for identifier = expr1 to expr2 do cexpr } | builder.For(enumeration, (fun identifier -> { cexpr })) |
| { while expr do cexpr } | builder.While(fun () -> expr, builder.Delay({ cexpr })) |
| { try cexpr with | pattern_i -> expr_i } | builder.TryWith(builder.Delay({ cexpr }), (fun value -> match value with | pattern_i -> expr_i | exn -> reraise exn))) |
| { try cexpr finally expr } | builder.TryFinally(builder.Delay( { cexpr }), (fun () -> expr)) |
| { cexpr1; cexpr2 } | builder.Combine({ cexpr1 }, { cexpr2 }) |
| { other-expr; cexpr } | expr; { cexpr } |
| { other-expr } | expr; builder.Zero() |

一個自定義的builder class不需要全部實現這些方法，未實現的方法對應操作在計算表達式中不可用。
例如，開發者需要在計算表達式中使用`use`關鍵字，就應該在builder中實現`Using()`方法。

通常，一個計算表達式的工作流程為：

1. 將計算表達式內的語句翻譯為對應方法，傳入Delay中。
2. 在Delay中處理表達式方法的包裝函數，調用生成結果。
3. 判斷是否存在多個語句，存在多個語句時將各個語句的結果使用定義的Combine成員方法進行連結。

方法調用組合：

```fs
buider.Delay(fun () ->
    buider.Combine(
        builder.Delay(fun () -> {| cexpr1 |}),
        builder.Delay(fun () -> {| cexpr2 |})))
...
```

示例，定義生成列表的buider type，提供於seq類似的語法：

```fs
module FSharpPractice.Lang.ComputationExprssion

type CustomBuilder() =

    // record the method call of this compute expression
    let log method v =
        printfn "Call { %s }: %A" method v
        v

    // record the call stack of the Delay member
    let mutable count = 0

    member _.Zero() = log "Zero" []

    member _.Return v = log "Return" [ v ]

    // can't use free point style
    member _.ReturnFrom v = log "Return" v

    member _.Yield v = log "Yield" [ v ]

    member _.YieldFrom v = log "YieldFrom" v

    member _.Combine(v1, v2) =
        sprintf "Combine, left: %A, right: %A" v1 v2
        |> log
        <| List.append v1 v2

    member _.Delay f =
        let deploy = sprintf "Deploy%d" count
        printfn "Start %s ..." deploy // record the start call stack
        count <- count + 1

        let v = log deploy <| f ()
        printfn "End %s" deploy // record the end call stack
        count <- count - 1

        v

open Microsoft.VisualStudio.TestTools.UnitTesting

[<TestClass>]
type Test() =

    [<TestMethod>]
    member _.TestComputationExprssion() =

        let builder = CustomBuilder()

        printfn "------------- Result1: %A ------------- \n"
        <| builder { "Test1" }

        printfn "------------- Result2: %A ------------- \n"
        <| builder {
            "Test2(1)"
            if false then "Test2(2)"
            yield! [ "Test2(3)" ]
           }

        printfn "------------- Result3: %A ------------- \n"
        <| builder {
            1
            return 2
            yield! [ 3; 4 ]
            return! []
            return! [ 5; 6 ]
            return 777
           }
```

輸出結果：

```
Start Deploy0 ...
Call { Yield }: ["Test1"]
Call { Deploy0 }: ["Test1"]
End Deploy0
------------- Result1: ["Test1"] -------------

Start Deploy0 ...
Call { Yield }: ["Test2(1)"]
Start Deploy1 ...
Call { Zero }: []
Start Deploy2 ...
Call { YieldFrom }: ["Test2(3)"]
Call { Deploy2 }: ["Test2(3)"]
End Deploy2
Call { Combine, left: [], right: ["Test2(3)"] }: ["Test2(3)"]
Call { Deploy1 }: ["Test2(3)"]
End Deploy1
Call { Combine, left: ["Test2(1)"], right: ["Test2(3)"] }: ["Test2(1)"; "Test2(3)"]
Call { Deploy0 }: ["Test2(1)"; "Test2(3)"]
End Deploy0
------------- Result2: ["Test2(1)"; "Test2(3)"] -------------

Start Deploy0 ...
Call { Yield }: [1]
Start Deploy1 ...
Call { Return }: [2]
Start Deploy2 ...
Call { YieldFrom }: [3; 4]
Start Deploy3 ...
Call { Return }: []
Start Deploy4 ...
Call { Return }: [5; 6]
Start Deploy5 ...
Call { Return }: [777]
Call { Deploy5 }: [777]
End Deploy5
Call { Combine, left: [5; 6], right: [777] }: [5; 6; 777]
Call { Deploy4 }: [5; 6; 777]
End Deploy4
Call { Combine, left: [], right: [5; 6; 777] }: [5; 6; 777]
Call { Deploy3 }: [5; 6; 777]
End Deploy3
Call { Combine, left: [3; 4], right: [5; 6; 777] }: [3; 4; 5; 6; 777]
Call { Deploy2 }: [3; 4; 5; 6; 777]
End Deploy2
Call { Combine, left: [2], right: [3; 4; 5; 6; 777] }: [2; 3; 4; 5; 6; 777]
Call { Deploy1 }: [2; 3; 4; 5; 6; 777]
End Deploy1
Call { Combine, left: [1], right: [2; 3; 4; 5; 6; 777] }: [1; 2; 3; 4; 5; 6; 777]
Call { Deploy0 }: [1; 2; 3; 4; 5; 6; 777]
End Deploy0
------------- Result3: [1; 2; 3; 4; 5; 6; 777] -------------
```



# Type Providers
`Type Providers`為F#提供了動態生成類型的能力，
type providers根據外部輸入內容由F#編譯器生成`Provided Types`。

詳情可參考[微軟官方文檔](https://docs.microsoft.com/en-us/dotnet/fsharp/tutorials/type-providers/)。

type providers分為兩類：

- `Generative Type Providers`

	generative type providers生成的類型能夠作為.NET類型寫入程序集中；
	用戶可以從其它程序集中使用這些代碼；但這要求數據源的類型化形式能夠被.NET的類型系統所表示。

- `Erasing Type Providers`

	erasing type providers生成的類型僅能夠被所屬的項目和程序集使用。
	這些生成的類型是暫時性的，不會被寫入程序集，也不能被其它程序集的代碼所訪問。
	這些類型能夠包含延遲成員(delayed members)，允許用戶使用來自無限信息空間中的provided types。
	在使用一個大型、互聯數據集的較小子集時有用。

常用的type providers：

- [`FSharp.Data`](https://fsharp.github.io/FSharp.Data) 包括JSON、XML、CSV和HTML格式的type providers
- [`SQLProvider`](https://fsprojects.github.io/SQLProvider) 以對象映射的方式提供對關係型數據庫的強類型訪問，通過數據源進行F# LINQ查詢
- [`FSharp.Data.SqlClient`](https://fsprojects.github.io/FSharp.Data.SqlClient) 提供對T-SQL的編譯時檢查

以`FSharp.Data.JsonProvider`為例：

```fs
open FSharp.Data
open Microsoft.VisualStudio.TestTools.UnitTesting

// 根據傳入的JSON文本生成了不同的類型
type PersonInfo = JsonProvider<"""{ "name":"Winne", "age": 67 }""">
type PersonInfos = JsonProvider<"""[{ "name":"Mr.Shithole", "age": 67 }]""">

[<TestClass>]
type Test() =

    [<TestMethod>]
    member _.TestJsonProvider() =
        let personInfo =
            PersonInfo.Parse """{ "name": "Xitele", "age": 67, "sex": "unknown" }"""

        let personInfos =
            PersonInfos.Parse
                """[{ "name": "the Emperor QingFeng", "age": 67 }, { "name":"King Gesar", "age": 67 }]"""

        // 將JSON的結構映射到了類型中，JSON的結構直接對應生成了類型的字段
        printfn "%A" personInfo
        printfn "Name: %s, Age: %d" personInfo.Name personInfo.Age

        printfn "%A" personInfos
        for (i, info) in personInfos |> Array.indexed do
            printfn "[%d] Name: %s, Age: %d" i info.Name info.Age
```
