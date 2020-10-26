<!-- TOC -->

- [Entry Point (入口點/函數)](#entry-point-入口點函數)
- [F# Interactive (F#交互式環境)](#f-interactive-f交互式環境)

<!-- /TOC -->



# Entry Point (入口點/函數)
F#項目中，使用特性`[<EntryPoint>]`標註一個函數，使之成為入口函數。

```fsharp
[<EntryPoint>]
let main args = ...
```

與C#不同，F#中的入口函數對函數名稱無要求，僅函數簽名需要滿足：

```fsharp
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
