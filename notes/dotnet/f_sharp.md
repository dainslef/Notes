<!-- TOC -->

- [Entry Point (入口點/函數)](#entry-point-入口點函數)

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
