<!-- TOC -->

- [概述](#概述)
	- [開發環境](#開發環境)
	- [F# Interactive (F#交互式環境)](#f-interactive-f交互式環境)
	- [與主流語言的語法差異](#與主流語言的語法差異)
- [Function (函數)](#function-函數)
	- [可選參數](#可選參數)
	- [參數默認值](#參數默認值)
	- [Entry Point (入口點/函數)](#entry-point-入口點函數)

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
