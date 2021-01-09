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

使用了`?`標記的參數實際類型將從`'a`變為`'a option`，在調用方法時，該參數位置對應可不傳參，
未傳參時對應參數位置得到值為`None`。

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
