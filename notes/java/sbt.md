<!-- TOC -->

- [簡介](#簡介)
	- [安裝與配置](#安裝與配置)
	- [更換倉庫](#更換倉庫)
- [啓動與使用](#啓動與使用)
	- [Giter8 模版](#giter8-模版)
	- [關於 No Scala version specified or detected 錯誤](#關於-no-scala-version-specified-or-detected-錯誤)
- [項目結構](#項目結構)
	- [默認路徑](#默認路徑)
- [構建配置](#構建配置)
	- [指定 sbt 版本](#指定-sbt-版本)
	- [自定義源碼路徑](#自定義源碼路徑)
	- [多項目構建](#多項目構建)
	- [處理構建衝突](#處理構建衝突)
- [依賴管理](#依賴管理)
	- [常用依賴](#常用依賴)
- [編譯參數](#編譯參數)
- [sbt-buildinfo](#sbt-buildinfo)
- [sbt-assembly](#sbt-assembly)
	- [打包參數](#打包參數)
	- [合併策略](#合併策略)
	- [執行構建](#執行構建)
- [Lightbend Activator (已廢棄)](#lightbend-activator-已廢棄)
	- [安裝與配置](#安裝與配置-1)
	- [基本操作](#基本操作)
	- [後記](#後記)

<!-- /TOC -->



# 簡介
`sbt`全稱`Simple Build Tool`，是Scala項目的標準構建工具，類似於Java的`Maven`或Groovy的`Gradle`。

與其它Java構建工具類似，sbt的核心功能如下：

- 項目的自動化構建、打包。
- 項目依賴自動化管理。
- 提供統一的工程結構。
- 提供交互式的`sbt shell`。

## 安裝與配置
主流Linux發行版的倉庫中，一般都包含sbt，可以使用發行版的包管理器安裝，以`ArchLinux`爲例：

```
# pacman -S sbt
```

在Windows環境下，可以從官網`http://www.scala-sbt.org/download.html`中下載。
下載完成之後解壓並將目錄下的`bin`目錄加入`PATH`中。

如果已經安裝了`Activator`，則無需再安裝sbt，Activator中已經包含了sbt。

## 更換倉庫
鑒於牆內的網絡狀況，通常sbt的默認倉庫鏡像無法連接或速度較慢，
可通過修改`~/.sbt/repositories`文件自定義鏡像倉庫，文件格式：

```ini
[repositories]
  local
  my-ivy-proxy-releases: http://repo.company.com/ivy-releases/, [organization]/[module]/(scala_[scalaVersion]/)(sbt_[sbtVersion]/)[revision]/[type]s/[artifact](-[classifier]).[ext]
  my-maven-proxy-releases: http://repo.company.com/maven-releases/
```

sbt支持Ivy/Maven鏡像倉庫，Ivy倉庫在牆內使用較少，沒有主流的牆內鏡像，Maven推薦使用阿里雲倉庫：

```ini
[repositories]
  local
  my-maven-proxy-releases: https://maven.aliyun.com/repository/public/
```



# 啓動與使用
在任意目錄下輸入sbt指令，即可進入`sbt shell`，sbt會將當前路徑作爲sbt項目的**根目錄**。

終端會輸入如下信息：

```
[info] Set current project to sbt (in build file:xxx...)
>
```

若路徑爲有效的sbt項目路徑，則在`sbt shell`中輸入`run`指令會嘗試編譯源碼執行項目。

舊版的sbt中(`sbt 0.7.x`之前)，在`sbt shell`中輸入`run`指令會在路徑下生成完整的sbt項目結構，
但新版的sbt已**不提供**此特性(可使用`sbt new`指令創建項目)。

常見指令如下：

- `compile` 編譯項目
- `update` 更新依賴
- `test` 運行測試用例
- `run` 運行項目
- `clean` 清理項目緩存
- `package` 將項目打包
- `project` 顯示子項目/切換到子項目
- `console` 進入Scala REPL
- `reload` 重新加載項目的`build.sbt`構建配置

sbt指令在`sbt shell`內使用，部分指令也可作爲參數跟在sbt指令之後直接在命令行中使用。

sbt支持持續構建模式，使用`~ 指令`可監控文件變化，在項目的文件發生修改後自動執行指定構建指令。
在持續構建模式下輸入回車退出該模式。

在sbt指令直接使用時若帶有參數需要用引號包圍指令與參數，如`sbt project`：

```
$ sbt project //顯示所有子項目
$ sbt "project 項目名稱" //切換到指定子項目
```

sbt指令後可直接跟上**多個**指令參數，使用`;`符號分隔指令：

```
$ sbt "project 項目名稱"; clean; compile //先切換到指定子項目，執行清理操作，之後再編譯項目
```

## Giter8 模版
`Giter8`是由`Nathan Hamblen`在`2010`年開始發起的模版項目，目前由`foundweekends`項目維護。
在`sbt 0.13.13`版本後，可使用`sbt new`指令創建基於`Giter8`模版的項目：

```
$ sbt new [Giter8模版名稱]
```

使用`sbt new`指令新建模板項目，根據模板類型，會交互式地要求輸入一些項目信息。
之後會在`當前目錄/項目名稱`路徑下生成指定模板的目錄結構。

`Lightbend`系列的各項技術均提供了基於`Giter8`的官方項目模版，常用模版名稱如下：

- `scala/scala-seed.g8` 普通Scala項目模版
- `akka/akka-scala-seed.g8` Akka項目模版
- `playframework/play-scala-seed.g8` PlayFramework項目模版

## 關於 No Scala version specified or detected 錯誤
當sbt版本升級後，若`~/.ivy2/cache`路徑下存在舊版sbt的jar包，則在終端執行`sbt`指令時，可能會出現以下錯誤輸出：

```
Error during sbt execution: No Scala version specified or detected
```

出現錯誤的原因是存在舊版本的sbt包緩存，解決方案是移除`~/.sbt`和`~/.ivy2/cache/org.scala-sbt`目錄。
執行以下指令：

```sh
$ rm ~/.sbt ~/.ivy2/cache/org.scala-sbt
```



# 項目結構
sbt項目結構與`Maven`項目類似。
一個基本的sbt項目具有以下目錄結構：

```
項目名稱
├── build.sbt # 構建定義
├── project
│    ├── plugins.sbt # 添加sbt插件
│    └── build.properties # 構建規則與參數
└── src # 源碼目錄
     ├── main
     │    ├── resources
     │    └── scala
     │         ├── Xxx.scala
     │         ├── Xxx.scala
     │         └── ...
     └── test
          ├── resources
          └── scala
               ├── Xxx.scala
               ├── Xxx.scala
               └── ...
```

新創建的項目沒有`target`目錄，在`sbt shell`中執行了`run`後會生成`target`和`project/target`目錄。
`target`目錄中包含的所有內容均由編譯系統生成，將項目目錄加入版本控制時需要忽略這些目錄。

## 默認路徑
在sbt項目中，直接使用**相對路徑**訪問目錄/文件，則默認起始路徑爲項目的**根路徑**(即與`build.sbt`文件在統一路徑下)。

在項目**根目錄**下創建文件`temp.txt`：

```scala
import scala.reflect.io.File

object Main extends App {
  // 文件生成在根目錄下，路徑爲 [項目名稱]/temp.txt
  File("temp.txt").createFile(false)
}
```

- 使用**項目相對路徑**訪問資源目錄

	sbt項目中的`src/main`與`src/test`下都存在`resources`目錄。
	`resources`路徑下的文件可以根據項目的相對路徑來訪問。
	假設`src/main/resources`路徑下存在文件`temp.txt`，打印文件內容：

	```scala
	import scala.reflect.io.File

	object Main extends App {
	  // 使用項目相對路徑
	  File("src/main/resources/temp.txt").lines foreach println
	}
	```

- 訪問輸出路徑下的資源文件

	在項目構建時，`resources`目錄下的文件會被複制到輸出路徑下，並保留子目錄結構。
	從輸出目錄獲取資源文件可以使用`Class`類型的`getResource()`方法：

	```java
	public java.net.URL getResource(String name);
	```

	`getResource()`方法返回的路徑爲`URL`類型，可以使用`getFile()`方法將其轉換爲文件路徑字符串。
	`getResource()`方法接收的路徑參數可以爲**相對路徑**或**絕對路徑**。

	當參數爲**絕對路徑**時，參數路徑會以輸出路徑爲起點。
	假設`src/main/resources`路徑下存在文件`temp.txt`，則打印該文件內容：

	```scala
	import scala.reflect.io.File

	object Main extends App {
	  File(getClass.getResource("/temp.txt").getFile).lines foreach println
	}
	```

	當參數爲**相對路徑**時，參數路徑會以**當前類所屬包**的輸出路徑爲起點。

- JAR資源文件

	與項目構建時類似，將項目打包爲JAR包後，`resources`目錄下的文件會被複制到JAR包內部的**根目錄**。
	運行JAR包時，起始相對目錄的位置爲JAR所處的路徑，**不能**通過`src/main/resources/***`相對路徑訪問資源目錄下的文件。

	JAR包內部文件應使用`getResource()`方法來獲取路徑，且應使用`URL`的形式表示，直接使用文本路徑不能被正確識別。
	JAR包內部的`URL`路徑格式爲`jar:file:...`。



# 構建配置
sbt項目根目錄下的`build.sbt`定義了項目的構建配置。`project`目錄下也可以添加`*.scala`構建定義。
可以在這些文件中設定項目的名稱、版本信息、構建規則、依賴等配置。`build.sbt`文件遵循Scala語法。

一個簡單的`build.sbt`文件內容如下所示：

```scala
name := "項目名稱"
version := "項目版本號"
scalaVersion := "Scala編譯器版本號"

libraryDependencies ++= Seq(
  "xx" % "xx" % "xx", //項目Java依賴
  ...
   "xx" % "xx" %% "xx", //項目Scala依賴
  ...
)

scalacOptions ++= Seq(
  "-xxx", //編譯器選項
  ...
)

enablePlugins(Xxx) //啓用插件
```

`sbt shell`僅在**啓動時**讀取構建配置。
若在`sbt shell`開啓之後`build.sbt`文件發生了修改，則已經開啓的`sbt shell`依舊使用之前的構建配置。
若需要已開啓的`sbt shell`使用新的構建配置，則應在`sbt shell`中使用`reload`指令重新加載構建配置。

## 指定 sbt 版本
sbt允許在項目中指定項目構建所需的sbt版本，而非直接使用啓動的sbt launcher中內置的sbt版本。
創建`project/build.properties`文件，在其中添加內容：

```scala
sbt.version = X.X.X //填寫 sbt 版本號，如 0.13.16
```

在啓動構建任務時，會查找指定sbt版本的依賴包是否存在，不存在則在下載依賴包後執行構建任務。

## 自定義源碼路徑
sbt項目默認源碼路徑爲`項目根目錄/src`。

修改默認源碼路徑，在`build.sbt`中添加：

```scala
// 默認Scala源碼路徑
scalaSource in Compile := file("...")
// 默認Scala測試源碼路徑
scalaSource in Test := file("...")

// 默認Java源碼路徑
javaSource in Compile := file("...")
// 默認Java測試源碼路徑
javaSource in Test := file("...")
```

若需要管理默認路徑之外的源碼，在`build.sbt`中添加：

```scala
// 獲取源碼絕對路徑，並構建 File 實例
def sourceDir(dir: String) = file(s"${file(".").getAbsolutePath}/$dir")

// 自定義源碼路徑需要修改 unmanagedSourceDirectories 配置項
unmanagedSourceDirectories in Compile ++= Seq(
  sourceDir("子目錄1"),
  sourceDir("子目錄2"),
  ...
)
```

## 多項目構建
sbt支持多項目構建，一個項目中可包含多個子項目。
每個子項目均可包含獨立、完整的構建配置。

使用sbt環境中預定義的`project`方法指定子項目的路徑：

```scala
// 子項目的根路徑爲當前路徑下的 xxx 子路徑
// 子項目名稱 ChildProject (變量名稱)
lazy val ChildProject = project in file("xxx")
```

`project`方法構建的實例類型爲`sbt.Project`，代表子項目的構建定義，實例名稱會作爲子項目的`ID`。
若`project in file("xxx")`中的路徑信息`xxx`爲`.`(項目當前路徑)時，獲取的實例代表默認項目的構建定義。
`sbt.Project`類型定義了一系列控制構建配置的方法：

```scala
package sbt

sealed trait Project extends AnyRef with ProjectDefinition[ProjectReference] {
  ...
  def in(dir : java.io.File): Project //設置構建定義的對應路徑
  def configs(cs: librarymanagement.Configuration*): Project
  def dependsOn(deps: ClasspathDep[ProjectReference]*): Project //設置項目依賴
  def settings(ss: Def.SettingsDefinition*): Project //設置項目通用配置
  def enablePlugins(ns: Plugins*): Project //啓用指定 sbt 插件
  def disablePlugins(ps: AutoPlugin*) : Project //禁用指定 sbt 插件
  ...
}
```

使用`settings()`方法向項目中添加通用定義：

```scala
childProject
  .settings(
    libraryDependencies ++= Seq(
      ...
    ),
    scalacOptions ++= Seq(
      ...
    ),
    ...)
```

所有能在父級項目中設定的配置都可以添加在子項目的`settings()`方法中。

使用`enablePlugins()/disablePlugins()`方法啓用/禁用sbt插件。
使用`dependsOn()`方法設定依賴項目，子項目能引用依賴項目的代碼，並自動引入依賴項目的`libraryDependencies`。

`sbt.Project`類型的主要方法均返回自身實例，支持**鏈式調用**。
常見的配置結構，如下所示：

```scala
val root = project in file(".") //父項目配置
  .settings(
    ...
  )
  ...

val child = (project in file("xxx"))  //子項目配置
  .dependsOn(root) //設定依賴項目
  .enablePlugins(xxx) //啓用插件
  .settings( //模塊配置項
    name := "xxx",
    version := "xxx",
    scalaVersion := "2.12.x"
    libraryDependencies ++= Seq(
      ... //jar包依賴
    ),
    scalacOptions ++= Seq(
      ... //編譯器配置
    ),
    ...
  )
```

## 處理構建衝突
JAR打包時將多個JAR包依賴引入同一個包時，若依賴的JAR包含相對路徑相同的目錄、文件，則可能產生衝突。

如`com.typesafe.slick:slick`和`com.typesafe.akka:akka-actor`包中的根路徑下均包含`reference.conf`配置文件，
該配置記錄了模塊運行時必要的默認配置。
若打包時同時依賴這兩個包，則生成的JAR中`reference.conf`文件只會保留一份。
運行時`akka-actor`或`slick`可能會因爲缺少默認配置異常退出。

解決衝突文件的簡單方案是在項目`resource`路徑下手動創建衝突文件，手動合併來自不同包的衝突文件內容。
`sbt-assembly`插件提供了更完善的打包機制，支持自定義各類衝突文件的合併策略。



# 依賴管理
通過設定`build.sbt`文件中的`libraryDependencies`變量向項目中添加**託管依賴**。

`libraryDependencies`配置項是類型爲`sbt.SettingKey[scala.Seq[sbt.ModuleID]]`的**字段**。
每一項依賴由`sbt.ModuleID`類型定義，一個具體的依賴項格式如下所示：

```scala
// 普通依賴，通常適用於Java依賴包
groupID % artifactID % revision
// 在指定配置下的依賴
groupID % artifactID % revision % configuration
// 測試時使用的依賴，在打包時會忽略該依賴項，一般用於測試庫如 JUnit/Scala Test 等
groupID % artifactID % revision % Test
// 對於開放源碼的庫，可以指定在添加依賴時同時下載庫源碼和Java DOC
groupID % artifactID % revision % withSource() withJavadoc()
```

對於多數使用Scala開發的項目，項目的`artifactID`命名上通常會以使用Scala版本號作爲結尾(`Scala`編譯器相關模塊除外，
如`scala-reflect`、`scala-compiler`等)。

在添加`Scala`項目依賴時，使用`%%`操作符連接`groupID`和`artifactID`，則會將當前Scala版本號追加到`artifactID`上：

```scala
groupID %% artifactID % revision
```

等價於：

```scala
groupID % artifactID_[Scala版本] % revision
```

以`Scala 2.12`的`Akka 2.4.17`爲例，依賴信息爲：

```scala
"com.typesafe.akka" %% "akka-actor" % "2.4.17" //省略Scala版本信息
"com.typesafe.akka" % "akka-actor_2.12" % "2.4.17" //兩種表示方式等價
```

`sbt.SettingKey`類型重載了`+=`和`++=`運算符：

- `+=`運算符用於添加單項依賴，如：

	```scala
	libraryDependencies += groupID % artifactID % revision
	```

- `++=`運算符用於添加多個依賴序列，如：

	```scala
	libraryDependencies ++= Seq(
	  groupID0 % artifactID0 % revision0,
	  groupID1 % artifactID1 % revision1,
	  ...
	)
	```

## 常用依賴
`sbt`依賴的描述信息與`Maven`相同，`sbt`允許直接添加`Maven`倉庫的依賴，包的信息可以在**Maven中心倉庫**搜索到，地址爲`http://search.maven.org/`。

一些常用包的`GroupId`和`ArtifactId`信息如下：

| 包介紹 | GroupId | ArtifactId |
| :- | :- | :- |
| MySQL JDBC Driver | mysql | mysql-connector-java |
| Scala Reflect | org.scala-lang | scala-reflect |
| Scala Swing | org.scala-lang.modules | scala-swing_[Scala版本號] |
| Scala Test | org.scalatest | scalatest_[Scala版本號] |
| ScalaFx | org.scalafx | scalafx_[Scala版本號]
| Slick | com.typesafe.slick | slick_[Scala版本號] |
| Akka | com.typesafe.akka | akka-actor_[Scala版本號] |



# 編譯參數
通過設定`build.sbt`文件中的`scalacOptions`變量可以控制`scalac`編譯器的編譯參數。
設定了編譯參數後，執行`compile`指令時會採用設定的編譯參數進行編譯。

所有`scalac`支持的命令行參數都可添加，如下所示：

```scala
scalacOptions ++= Seq(
  "-feature",
  "-language:implicitConversions"
  "..."
)
```

Scala中的部分語言特性需要使用參數`-language:xxx`來開啓：

- 使用`-language:help`參數顯示所有可使用的語言特性參數。
- 使用`-language:_`參數可以開啓所有的語言特性。



# sbt-buildinfo
`sbt`未提供訪問`build.sbt`中項目構建信息的接口，使用`sbt-buildinfo`插件可以在項目中訪問構建信息。
在sbt項目中的`project/plugins.sbt`中添加：

```scala
addSbtPlugin("com.eed3si9n" % "sbt-buildinfo" % "版本號")
```

在項目構建配置文件`build.sbt`中啓用`sbt-buildinfo`插件：

```scala
enablePlugins(BuildInfoPlugin)
```

`sbt-buildinfo`插件的原理是利用`build.sbt`中的項目構建信息在項目構建時生成額外的源碼，
並以**單例對象**的形式將構建信息提供給項目源碼進行訪問。

啓用`sbt-buildinfo`插件後會增加插件相關的配置項。
將`build.sbt`中的`name、version、scalaVersion、sbtVersion`等配置項傳入`sbt-buildinfo`插件的`buildInfoKeys`配置項，
通過`buildInfoPackage`配置項設定生成單例的包路徑。

在`build.sbt`文件中配置`sbt-buildinfo`插件，實例如下：

```scala
// sbt項目構建信息
name := "xxx"
version := "xxx"
scalaVersion := "2.12.3"
sbtVersion := "0.13.16"

// 啓用 sbt-buildinfo 插件
enablePlugins(BuildInfoPlugin)

// 設定構建信息
buildInfoKeys := Seq(name, version, scalaVersion, sbtVersion)
buildInfoPackage := "xxx.yyy.zzz" //將構建信息生成到 xxx.yyy.zzz 包路徑中
```

`sbt-buildinfo`插件生成的單例對象結構如下所示：

```scala
case object BuildInfo {
  /** The value is "xxx". */
  val name: String = "xxx"
  /** The value is "xxx". */
  val version: String = "xxx"
  /** The value is "2.12.2". */
  val scalaVersion: String = "2.12.3"
  /** The value is "0.13.15". */
  val sbtVersion: String = "0.13.15"
  override val toString: String = {
    "name: %s, version: %s, scalaVersion: %s, sbtVersion: %s" format (
      name, version, scalaVersion, sbtVersion
    )
  }
}
```



# sbt-assembly
`sbt-assembly`插件用於將項目的所有依賴打包到一個JAR包中。

在sbt項目的`project/plugins.sbt`中引入插件：

```scala
addSbtPlugin("com.eed3si9n" % "sbt-assembly" % "版本號")
```

## 打包參數
在bulid.sbt中可設定打包時的主要參數：

- `assemblyJarName in assembly := "xxx.jar"` 設定生成的JAR包名稱，默認名稱爲`項目名稱-assembly-日期.jar`
- `test in assembly := {}` 設定要打包的測試內容，默認打包時會包含測試代碼，改字段置空則不打包測試代碼
- `mainClass in assembly := Some("xxx.xxx.Main")` 設定JAR的主類

## 合併策略
sbt-assembly提供了完善的機制用於處理打包流程中的文件衝突：

- `MergeStrategy.deduplicate` 默認合併策略
- `MergeStrategy.first` 保留首個文件
- `MergeStrategy.last` 保留最後的文件
- `MergeStrategy.singleOrError` 文件衝突時退出
- `MergeStrategy.concat` 拼接衝突的文件
- `MergeStrategy.rename` 根據所屬的jar包重命名衝突的文件
- `MergeStrategy.discard` 丟棄文件

在`build.sbt`中添加文件合併邏輯，常見的合併操作如下所示：

```scala
// 合併規則
assemblyMergeStrategy in assembly := {
  case "reference.conf" => MergeStrategy.concat //匹配指定文件
  case PathList("aaa", "bbb", _*)  => MergeStrategy.first //匹配局部路徑 aaa/bbb/* 下的文件
  case f if Assembly.isConfigFile(f) => MergeStrategy.concat //匹配配置文件
  case f if f endsWith ".xsb" => MergeStrategy.last //匹配指定後綴的文件
  case f => (assemblyMergeStrategy in assembly).value(f) //使用默認合併規則
}
```

`sbt-assembly 0.14.6`版本的默認合併規則如下所示：

```scala
val defaultMergeStrategy: String => MergeStrategy = {
  case x if Assembly.isConfigFile(x) =>
    MergeStrategy.concat
  case PathList(ps @ _*) if Assembly.isReadme(ps.last) || Assembly.isLicenseFile(ps.last) =>
    MergeStrategy.rename
  case PathList("META-INF", xs @ _*) =>
    (xs map {_.toLowerCase}) match {
      case ("manifest.mf" :: Nil) | ("index.list" :: Nil) | ("dependencies" :: Nil) =>
        MergeStrategy.discard
      case ps @ (x :: xs) if ps.last.endsWith(".sf") || ps.last.endsWith(".dsa") =>
        MergeStrategy.discard
      case "plexus" :: xs =>
        MergeStrategy.discard
      case "services" :: xs =>
        MergeStrategy.filterDistinctLines
      case ("spring.schemas" :: Nil) | ("spring.handlers" :: Nil) =>
        MergeStrategy.filterDistinctLines
      case _ => MergeStrategy.deduplicate
    }
  case _ => MergeStrategy.deduplicate
}
```

## 執行構建
啓用了sbt-assembly插件後，在sbt項目的根路徑下使用`sbt assembly`指令(或在`sbt shell`中執行`assembly`指令)可執行打包操作。
若包含子項目，需要使用`project 項目名稱`切換到對應項目中再執行`assembly`構建指令。

在命令行中直接執行sbt構建指定項目：

```
$ sbt "project 項目名稱"; assembly
```

sbt-assembly插件提供的衝突合併策略僅在使用`sbt assembly`指令打包時生效。
使用`IDEA`提供的打包工具，合併策略不會生效。



# Lightbend Activator (已廢棄)
`Activator`提供了成套的`Scala`開發環境，相當於：

```
Scala編譯器 + sbt + Play Framework + Akka + 項目模版 + 基於Play的WEB端項目管理
```

`Activator`內置了sbt，可以直接使用`Activator`管理、構建sbt項目。

## 安裝與配置
多數Linux發行版**沒有**將Activator添加到倉庫中，因而無論是Linux/Windows環境下，都需要從官網下載Activator。

配置Activator方式與sbt類似。
從`http://www.lightbend.com/activator/download`下載完整版的`Activator`，解壓後將`bin`目錄加入`PATH`環境變量中即可。

## 基本操作
在普通目錄中輸入`activator`指令會在瀏覽器中打開Activator的幫助頁面。

在sbt項目目錄中輸入`activator`指令會進入`sbt shell`。

其它常見的指令：

- `$ activator ui` 進入WEB端的Activator界面
- `$ activator shell` 進入sbt交互shell
- `$ activator list-templates` 列出模版列表

Activator中帶有大量的預定義項目模版，使用模版創建項目：

```
$ activator new [項目名稱] [模版名稱]
```

Activator同樣支持與sbt相同的指令。

## 後記
在`2017-4-24`的`Lightbend`官方新聞(`https://www.lightbend.com/blog/introducing-a-new-way-to-get-started-with-lightbend-technologies-and-saying-goodbye-to-activator`)中，宣佈在`2017-5-24`停止對Activator的支持。
新聞中指出了Activator在以下的情形存在缺陷：

- 將Activator良好地運行在多樣的機器類型上。
- 將Activator可靠地運行在多樣的網絡環境上。
- 處理雙重要求：`保持更新`與`從不更新`。

鑑於Activator無法良好地實現以上要求，Lightbend停止了對Activator的支持並提供了以下替代方案：

- 基於Web下載的`Project Starter`：

	在頁面`http://developer.lightbend.com/start/`中直接創建項目模版並將其下載到本地。

- 使用新增的`sbt new`指令：

	`Giter8`項目提供了Lightbend各類技術對應的項目模版，使用`sbt new [Giter8模版名稱]`創建對應的項目模版。
