<!-- TOC -->

- [dotnet CLI commands](#dotnet-cli-commands)
	- [創建項目](#創建項目)
	- [包管理](#包管理)

<!-- /TOC -->



# dotnet CLI commands
`dotnet`命令行接口(command-line interface (CLI))，可運行在Windows、macOS、Linux等主流平台上，
提供一些必要的指令諸如構建項目、安裝/刪除/發布應用/包。

常用指令包括：

- `new` 創建項目
- `restore` 恢復項目依賴
- `build` 構建項目
- `publish` 發布項目，將項目及其依賴項發布到指定路徑或部署到一個宿主系統中
- `run` 執行項目
- `test` 執行測試
- `pack` 將項目打包為NuGet包
- `migrate` 從舊版本項目中遷移
- `clean` 清理項目先前的構建輸出，包括中間文件(obj)，以及最終輸出(bin)
- `sln` 提供解決方案管理功能

詳細內容可參考[微軟官方文檔](https://docs.microsoft.com/en-us/dotnet/core/tools/)。

## 創建項目
使用`dotnet new`系列指令可從模板中創建.Net Core項目，指令語法：

```
$ dotnet new <TEMPLATE> [--dry-run] [--force] [-i|--install {PATH|NUGET_ID}]
    [-lang|--language {"C#"|"F#"|VB}] [-n|--name <OUTPUT_NAME>]
    [--nuget-source <SOURCE>] [-o|--output <OUTPUT_DIRECTORY>]
    [-u|--uninstall] [--update-apply] [--update-check] [Template options]

$ dotnet new <TEMPLATE> [-l|--list] [--type <TYPE>]

$ dotnet new -h|--help
```

dotnet提供了一系列的項目模板，使用`dotnet new -l`可查看當前提供項目模板：

```
$ dotnet new -l
Usage: ...

Templates                                         Short Name               Language          Tags
----------------------------------------------------------------------------------------------------------------------------------
Console Application                               console                  [C#], F#, VB      Common/Console
Class library                                     classlib                 [C#], F#, VB      Common/Library
...
ASP.NET Core Empty                                web                      [C#], F#          Web/Empty
ASP.NET Core Web App (Model-View-Controller)      mvc                      [C#], F#          Web/MVC
ASP.NET Core Web App                              webapp                   [C#]              Web/MVC/Razor Pages
ASP.NET Core with Angular                         angular                  [C#]              Web/MVC/SPA
ASP.NET Core with React.js                        react                    [C#]              Web/MVC/SPA
ASP.NET Core with React.js and Redux              reactredux               [C#]              Web/MVC/SPA
Razor Class Library                               razorclasslib            [C#]              Web/Razor/Library/Razor Class Library
ASP.NET Core Web API                              webapi                   [C#], F#          Web/WebAPI
ASP.NET Core gRPC Service                         grpc                     [C#]              Web/gRPC
dotnet gitignore file                             gitignore                                  Config
global.json file                                  globaljson                                 Config
NuGet Config                                      nugetconfig                                Config
Dotnet local tool manifest file                   tool-manifest                              Config
Web Config                                        webconfig                                  Config
Solution File                                     sln                                        Solution
Protocol Buffer File                              proto                                      Web/gRPC
```

以模板`mvc`為例，創建一個使用F#語言的MVC項目：

```
$ dotnet new mvc --language F# -o TestMVC
The template "ASP.NET Core Web App (Model-View-Controller)" was created successfully.
This template contains technologies from parties other than Microsoft, see https://aka.ms/aspnetcore/3.1-third-party-notices for details.

Processing post-creation actions...
Running 'dotnet restore' on TestMVC/TestMVC.fsproj...
  Determining projects to restore...
  Restored /Users/dainslef/TestMVC/TestMVC.fsproj (in 7.01 sec).

Restore succeeded.
```

## 包管理
dotnet提供了nuget的部分包管理功能，指令語法如下：

```c
// 添加依賴包
$ dotnet add [<PROJECT>] package <PACKAGE_NAME>
    [-f|--framework <FRAMEWORK>] [--interactive]
    [-n|--no-restore] [--package-directory <PACKAGE_DIRECTORY>]
    [-s|--source <SOURCE>] [-v|--version <VERSION>]

$ dotnet add package -h|--help

// 移除依賴包
$ dotnet remove [<PROJECT>] package <PACKAGE_NAME>

$ dotnet remove package -h|--help
```

將NuGet包`Newtonsoft.Json`安裝到當前項目中：

```
$ dotnet add package Newtonsoft.Json
  Determining projects to restore...
  Writing /var/folders/xr/pvslfmfn1_jffzjzr1gj1vbw0000gn/T/tmpmmenkA.tmp
info : Adding PackageReference for package 'Newtonsoft.Json' into project '/Users/dainslef/Downloads/Codes/TestMVC/TestMVC.fsproj'.
info : Restoring packages for /Users/dainslef/Downloads/Codes/TestMVC/TestMVC.fsproj...
info :   GET https://api.nuget.org/v3-flatcontainer/newtonsoft.json/index.json
info :   OK https://api.nuget.org/v3-flatcontainer/newtonsoft.json/index.json 315ms
info :   GET https://api.nuget.org/v3-flatcontainer/newtonsoft.json/12.0.3/newtonsoft.json.12.0.3.nupkg
info :   OK https://api.nuget.org/v3-flatcontainer/newtonsoft.json/12.0.3/newtonsoft.json.12.0.3.nupkg 728ms
info : Installing Newtonsoft.Json 12.0.3.
info : Package 'Newtonsoft.Json' is compatible with all the specified frameworks in project '/Users/dainslef/Downloads/Codes/TestMVC/TestMVC.fsproj'.
info : PackageReference for package 'Newtonsoft.Json' version '12.0.3' added to file '/Users/dainslef/Downloads/Codes/TestMVC/TestMVC.fsproj'.
info : Committing restore...
info : Writing assets file to disk. Path: /Users/dainslef/Downloads/Codes/TestMVC/obj/project.assets.json
log  : Restored /Users/dainslef/Downloads/Codes/TestMVC/TestMVC.fsproj (in 5.53 sec).
```

安裝包後，會在項目定義文件的`<ItemGroup />`標籤段中添加定義：

```xml
...
<ItemGroup>
  <PackageReference Include="Newtonsoft.Json" Version="12.0.3" />
</ItemGroup>
...
```

若需要移除該包，執行指令：

```
$ dotnet remove package Newtonsoft.Json
info : Removing PackageReference for package 'Newtonsoft.Json' from project '/Users/dainslef/Downloads/Codes/TestMVC/TestMVC.fsproj'.
```

執行包移除指令後，項目定義文件中對應包所屬的`<PackageReference />`區段會被移除。
