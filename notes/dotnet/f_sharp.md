<!-- TOC -->

- [Entry Point (入口點/函數)](#entry-point-入口點函數)
- [F# Interactive (F#交互式環境)](#f-interactive-f交互式環境)
- [Function (函數)](#function-函數)

<!-- /TOC -->



# Entry Point (入口點/函數)
F#項目中，使用特性`[<EntryPoint>]`標註一個函數，使之成為入口函數。

```fs
[<EntryPoint>]
let main args = ...
```

與C#不同，F#中的入口函數對函數名稱無要求，僅函數簽名需要滿足：

```fs
string array -> int
```



# F# Interactive (F#交互式環境)
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
