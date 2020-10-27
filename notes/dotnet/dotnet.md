<!-- TOC -->

- [dotnet CLI commands](#dotnet-cli-commands)
	- [創建項目](#創建項目)
	- [包管理](#包管理)
- [Testing (測試)](#testing-測試)
	- [編寫測試](#編寫測試)
	- [執行測試](#執行測試)
- [MSBuild](#msbuild)
	- [基本結構](#基本結構)

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



# Testing (測試)
dotnet工具支持.Net下的主流測試框架如`NUnit`、`xUnit`、`MSTest`等主流測試框架。

以MSTest為例，在項目中使用MSTest首先需要安裝相關依賴：

```
$ dotnet add package MSTest.TestAdapter
$ dotnet add package MSTest.TestFramework
```

測試代碼通常需要在解決方案中創建獨立的測試項目，以F#項目為例，使用了MSTest測試框架後，
會自動在項目中生成`Microsoft.NET.Test.Sdk.Program.fs`，
該文件定義了`[<EntryPoint>]`，導致項目不能存在其它的入口點，因而需要房在獨立的項目中。

## 編寫測試
以F#項目和MSTest為例，測試代碼需要是類型的成員方法(不能是函數/靜態方法)，
測試入口類使用`[<TestClass>]`標註，測試方法使用`[<TestMethod>]`標註：

```fs
[<TestClass>]
type Test() = // 需要提供空參的默認構造函數

    // 測試方法簽名需要為 unit -> unit
    [<TestMethod>]
    member _.TestXxx() =
        ...
        |> ignore
```

測試方法可以帶有參數，同時將參數寫在`[<DataRow(...)>]`特性中並用以標注方法：

```fs
[<TestMethod>]
[<DataRow(10, 10)>]
[<DataRow(1, 1)>]
[<DataRow(-1, -1)>]
[<DataRow(-1, 2)>]
[<DataRow(2, -1)>]
member _.TestPattern2(x: int, y: int) = ...

[<TestMethod>]
[<DataRow(-1, -1, "Test")>]
member _.TestPattern3(x: int, y: int, message: string) = ...
```

`[<DataRow(...)>]`特性中使用的參數需要為基本類型(字面量類型，Literal Types)，
若需要測試的內容為自定義類型，則可使用`[<DynamicData(...)>]`特性標注測試方法，
該特性允許將測試類的一個靜態屬性/方法返回的內容作為測試方法的輸入值，
作為測試方法輸入值的靜態屬性/方法返回值類型需要為`IEnumerable<obj []>`，
每一組待測試的參數都放在一個數組中，實例：

```fs
[<TestClass>]
type Test() =

    [<TestMethod>]
    [<DynamicData("Data", DynamicDataSourceType.Property)>]
    // DynamicData特性指定作為輸入參數的靜態屬性/方法名稱，並指定類型DynamicDataSourceType.Property/Method
    member _.TestPattern1(p: Point) = ...

    static member Data =
        seq {
            Point(10, 10)
            Point(1, 1)
            Point(-1, -1, c = "Test")
            Point(-1, 2)
            Point(2, -1)
            Point()
        }
        |> Seq.map (fun v -> [| v :> obj |])
        // map 通過函數轉換為 obj [] 類型
        // seq 類型實現了IEnumerable接口
```

## 執行測試
使用`dotnet test`指令執行測試，指令語法：

```
$ dotnet test [<PROJECT> | <SOLUTION> | <DIRECTORY> | <DLL>]
    [-a|--test-adapter-path <ADAPTER_PATH>] [--blame] [--blame-crash]
    [--blame-crash-dump-type <DUMP_TYPE>] [--blame-crash-collect-always]
    [--blame-hang] [--blame-hang-dump-type <DUMP_TYPE>]
    [--blame-hang-timeout <TIMESPAN>]
    [-c|--configuration <CONFIGURATION>]
    [--collect <DATA_COLLECTOR_NAME>]
    [-d|--diag <LOG_FILE>] [-f|--framework <FRAMEWORK>]
    [--filter <EXPRESSION>] [--interactive]
    [-l|--logger <LOGGER>] [--no-build]
    [--nologo] [--no-restore] [-o|--output <OUTPUT_DIRECTORY>]
    [-r|--results-directory <RESULTS_DIR>] [--runtime <RUNTIME_IDENTIFIER>]
    [-s|--settings <SETTINGS_FILE>] [-t|--list-tests]
    [-v|--verbosity <LEVEL>] [[--] <RunSettings arguments>]

$ dotnet test -h|--help
```

在執行測試中，默認不會顯示標準輸出，若需要顯示標準輸出，則應設置日誌級別：

```
$ dotnet test --logger "console;verbosity=detailed"
```

默認會執行項目中所有的測試用例，可以選擇過濾或指定執行某些測試用例：

| Expressio | Result |
| :- | :- |
| dotnet test --filter Method | Runs tests whose FullyQualifiedName contains Method. Available in vstest 15.1+. |
| dotnet test --filter Name~TestMethod1 | Runs tests whose name contains TestMethod1. |
| dotnet test --filter ClassName=MSTestNamespace.UnitTest1 | Runs tests that are in class MSTestNamespace.UnitTest1. Note: The ClassName value should have a namespace, so ClassName=UnitTest1 won't work. |
| dotnet test --filter FullyQualifiedName!=MSTestNamespace.UnitTest1.TestMethod1 | Runs all tests except MSTestNamespace.UnitTest1.TestMethod1. |
| dotnet test --filter TestCategory=CategoryA | Runs tests that are annotated with [TestCategory("CategoryA")]. |
| dotnet test --filter Priority=2 | Runs tests that are annotated with [Priority(2)]. |



# MSBuild
`MSBuild(Microsoft Build Engine)`是微軟的構建平台，通過提供XML格式的工程文件來控制構建過程。
`Visual Studio`使用了MSBuild，但MSBuild不依賴VS。
在項目中執行`msbuild.exe`可以在沒有VS安裝的環境下開始項目構建任務。

VS使用MSBuild來加載和構建被管理的項目，當從IDE中執行項目構建時，
VS的項目文件(如.csproj, .vbproj, .vcxproj等)包含的MSBuild XML代碼會被執行。

關於MSBuild的詳細介紹，可參考[微軟官方文檔](https://docs.microsoft.com/en-us/visualstudio/msbuild/msbuild)。

## 基本結構
以一個`F# .Net Core`命令行項目為例，新創建項目生成的項目定義(`.fsproj`)為：

```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>netcoreapp3.1</TargetFramework>
  </PropertyGroup>
  <ItemGroup>
    <Compile Include="Program.fs" />
  </ItemGroup>
</Project>
```

在.Net Core項目中，幾個比較重要的標籤為：

- `<Project Sdk="..." />`

	`<Project/>`標籤將整個構建配置包含在內，`Sdk`屬性定義項目使用的SDK。
	命令行項目使用SDK為`Microsoft.NET.Sdk`；WEB項目使用SDK為`Microsoft.NET.Sdk.Web`。

	SDK還可以單獨定義在標籤中：

	```xml
	<Project>
	  <Sdk Name="Microsoft.NET.Sdk" />
	  ...
	</Project>
	```

- `<PropertyGroup />`

	`<PropertyGroup />`標籤裡定義了項目使用的一些屬性值。
	.Net Core項目默認定義了`OutputType`(輸出二進制格式，通常為Exe)和`TargetFramework`(指定.Net Core的版本)。

- `<ItemGroup />`

	`<ItemGroup />`標籤定義輸入構建系統的構建資源，通常是文件。
	該標籤內可添加幾類資源：

	```xml
	<ItemGroup>
	  <Compile Include="xxx.fs" /> <!-- 包含源碼文件 -->
	  <Compile Include="xxxDir/*" /> <!-- 包含指定目錄(單層目錄) -->
	  <Compile Include="xxxDir/**" /> <!-- 包含指定目錄(遞歸包含子目錄) -->
	  <EmbeddedResource Include="xxxDir/*" /> <!-- 設置項目的資源路徑/文件 -->
	  <PackageReference Include="Newtonsoft.Json" Version="12.0.3" /> <!-- 包含NuGet包依賴 -->

	  <Compile Remove="xxx.xx" /> <!-- 移除指定內容 -->
	</ItemGroup>
	```

	使用`*`可匹配指定路徑下當前目錄層級的所有資源，
	使用`**`可遞歸匹配指定路徑下所有子路徑內的所有資源。

	除了使用`Include`屬性包含內容，亦可使用`Remove`屬性排除指定內容。
