<!-- TOC -->

- [*sbt* 简介](#sbt-简介)
- [安装与配置](#安装与配置)
- [启动与使用](#启动与使用)
	- [使用 *Giter8* 模版](#使用-giter8-模版)
	- [关于 *No Scala version specified or detected* 错误](#关于-no-scala-version-specified-or-detected-错误)
- [项目结构](#项目结构)
	- [默认路径](#默认路径)
- [构建配置](#构建配置)
	- [指定 *sbt* 版本](#指定-sbt-版本)
	- [自定义源码路径](#自定义源码路径)
	- [多项目构建](#多项目构建)
	- [处理构建冲突](#处理构建冲突)
- [依赖管理](#依赖管理)
	- [常用依赖](#常用依赖)
- [编译参数](#编译参数)
- [*sbt-buildinfo*](#sbt-buildinfo)
- [*sbt-assembly*](#sbt-assembly)
	- [打包参数](#打包参数)
	- [合并策略](#合并策略)
	- [执行构建](#执行构建)
- [*Lightbend Activator* (已废弃)](#lightbend-activator-已废弃)
	- [安装与配置](#安装与配置-1)
	- [基本操作](#基本操作)
	- [后记](#后记)

<!-- /TOC -->



## *sbt* 简介
`sbt`全称`Simple Build Tool`，是`Scala`项目的标准构建工具，类似于`Java`的`Maven`或`Groovy`的`Gradle`。

与其它`Java`构建工具类似，`sbt`的核心功能如下：

- 项目的自动化构建、打包。
- 项目依赖自动化管理。
- 提供统一的工程结构。
- 提供交互式的`sbt shell`。



## 安装与配置
主流`Linux`发行版的仓库中，一般都包含`sbt`，可以使用发行版的包管理器安装`sbt`，以`ArchLinux`为例：

```
# pacman -S sbt
```

在Windows环境下，可以从官网`http://www.scala-sbt.org/download.html`中下载。  
下载完成之后解压并将目录下的`bin`目录加入`PATH`中。

如果已经安装了`Activator`，则无需再安装`sbt`，`Activator`中已经包含了`sbt`。



## 启动与使用
在任意目录下输入`sbt`指令，即可进入`sbt shell`，`sbt`会将当前路径作为`sbt`项目的**根目录**。

终端会输入如下信息：

```
[info] Set current project to sbt (in build file:xxx...)
>
```

若路径为有效的`sbt`项目路径，则在`sbt shell`中输入`run`指令会尝试编译源码执行项目。

旧版的`sbt`中(`sbt 0.7.x`之前)，在`sbt shell`中输入`run`指令会在路径下生成完整的sbt项目结构，但新版的sbt已**不提供**此特性(可使用`sbt new`指令创建项目)。

常见指令如下：

- `compile` 编译项目
- `update` 更新依赖
- `test` 运行测试用例
- `run` 运行项目
- `clean` 清理项目缓存
- `package` 将项目打包
- `project` 显示子项目/切换到子项目
- `console` 进入Scala REPL
- `reload` 重新加载项目的`build.sbt`构建配置

sbt指令在`sbt shell`内使用，部分指令也可作为参数跟在sbt指令之后直接在命令行中使用。  
在sbt指令直接使用时若带有参数需要用引号包围指令与参数，如`sbt project`：

```
$ sbt project //显示所有子项目
$ sbt "project 项目名称" //切换到指定子项目
```

sbt指令后可直接跟上**多个**指令参数，使用`;`符号分隔指令：

```
$ sbt "project 项目名称"; clean; compile //先切换到指定子项目，执行清理操作，之后再编译项目
```

### 使用 *Giter8* 模版
`Giter8`是由`Nathan Hamblen`在`2010`年开始发起的模版项目，目前由`foundweekends`项目维护。  
在`sbt 0.13.13`版本后，可使用`sbt new`指令创建基于`Giter8`模版的项目：

```
$ sbt new [Giter8模版名称]
```

使用`sbt new`指令新建模板项目，根据模板类型，会交互式地要求输入一些项目信息。  
之后会在`当前目录/项目名称`路径下生成指定模板的目录结构。

`Lightbend`系列的各项技术均提供了基于`Giter8`的官方项目模版，常用模版名称如下：

- `scala/scala-seed.g8` 普通Scala项目模版
- `akka/akka-scala-seed.g8` Akka项目模版
- `playframework/play-scala-seed.g8` PlayFramework项目模版

### 关于 *No Scala version specified or detected* 错误
当sbt版本升级后，若`~/.ivy2/cache`路径下存在旧版sbt的jar包，则在终端执行`sbt`指令时，可能会出现以下错误输出：

```
Error during sbt execution: No Scala version specified or detected
```

出现错误的原因是存在旧版本的`sbt`包缓存，解决方案是移除`~/.sbt`和`~/.ivy2/cache/org.scala-sbt`目录。  
执行以下指令：

```sh
$ rm ~/.sbt ~/.ivy2/cache/org.scala-sbt
```



## 项目结构
sbt项目结构与`Maven`项目类似。  
一个基本的sbt项目具有以下目录结构：

```
项目名称
├── build.sbt # 构建定义
├── project
│    ├── plugins.sbt # 添加sbt插件
│    └── build.properties # 构建规则与参数
└── src # 源码目录
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

新创建的项目没有`target`目录，在`sbt shell`中执行了`run`后会生成`target`和`project/target`目录。  
`target`目录中包含的所有内容均由编译系统生成，将项目目录加入版本控制时需要忽略这些目录。

### 默认路径
在sbt项目中，直接使用**相对路径**访问目录/文件，则默认起始路径为项目的**根路径**(即与`build.sbt`文件在统一路径下)。

在项目**根目录**下创建文件`temp.txt`：

```scala
import scala.reflect.io.File

object Main extends App {
  // 文件生成在根目录下，路径为 [项目名称]/temp.txt
  File("temp.txt").createFile(false)
}
```

- 使用**项目相对路径**访问资源目录

	sbt项目中的`src/main`与`src/test`下都存在`resources`目录。  
	`resources`路径下的文件可以根据项目的相对路径来访问。  
	假设`src/main/resources`路径下存在文件`temp.txt`，打印文件内容：

	```scala
	import scala.reflect.io.File

	object Main extends App {
	  // 使用项目相对路径
	  File("src/main/resources/temp.txt").lines foreach println
	}
	```

- 访问输出路径下的资源文件

	在项目构建时，`resources`目录下的文件会被复制到输出路径下，并保留子目录结构。  
	从输出目录获取资源文件可以使用`Class`类型的`getResource()`方法：

	```java
	public java.net.URL getResource(String name);
	```

	`getResource()`方法返回的路径为`URL`类型，可以使用`getFile()`方法将其转换为文件路径字符串。  
	`getResource()`方法接收的路径参数可以为**相对路径**或**绝对路径**。

	当参数为**绝对路径**时，参数路径会以输出路径为起点。  
	假设`src/main/resources`路径下存在文件`temp.txt`，则打印该文件内容：

	```scala
	import scala.reflect.io.File

	object Main extends App {
	  File(getClass.getResource("/temp.txt").getFile).lines foreach println
	}
	```

	当参数为**相对路径**时，参数路径会以**当前类所属包**的输出路径为起点。

- `jar`包资源文件

	与项目构建时类似，将项目打包为`jar`包后，`resources`目录下的文件会被复制到`jar`包内部的**根目录**。  
	运行`jar`包时，起始相对目录的位置为`jar`所处的路径，**不能**通过`src/main/resources/***`相对路径访问资源目录下的文件。

	`jar`包内部文件应使用`getResource()`方法来获取路径，且应使用`URL`的形式表示，直接使用文本路径不能被正确识别。  
	`jar`包内部的`URL`路径格式为`jar:file:...`。



## 构建配置
`sbt`项目根目录下的`build.sbt`定义了项目的构建配置。  
`project`目录下也可以添加`*.scala`构建定义。

可以在`build.sbt`文件中设定项目的名称、版本信息、构建规则、依赖等配置。  
`build.sbt`文件遵循`Scala`语法。

一个简单的`build.sbt`文件内容如下所示：

```scala
name := "项目名称"
version := "项目版本号"
scalaVersion := "Scala编译器版本号"

libraryDependencies ++= Seq(
  "xx" % "xx" % "xx", //项目Java依赖
  ...
   "xx" % "xx" %% "xx", //项目Scala依赖
  ...
)

scalacOptions ++= Seq(
  "-xxx", //编译器选项
  ...
)

enablePlugins(Xxx) //启用插件
```

`sbt shell`仅在**启动时**读取构建配置。  
若在`sbt shell`开启之后`build.sbt`文件发生了修改，则已经开启的`sbt shell`依旧使用之前的构建配置。  
若需要已开启的`sbt shell`使用新的构建配置，则应在`sbt shell`中使用`reload`指令重新加载构建配置。

### 指定 *sbt* 版本
sbt允许在项目中指定项目构建所需的sbt版本，而非直接使用启动的sbt launcher中内置的sbt版本。  
创建`project/build.properties`文件，在其中添加内容：

```scala
sbt.version = X.X.X //填写 sbt 版本号，如 0.13.16
```

在启动构建任务时，会查找指定sbt版本的依赖包是否存在，不存在则在下载依赖包后执行构建任务。

### 自定义源码路径
`sbt`项目默认源码路径为`项目根目录/src`，若需要管理默认路径之外的源码，在`build.sbt`中添加：

```scala
// 获取源码绝对路径，并构建 File 实例
def sourceDir(dir: String) = file(s"${file(".").getAbsolutePath}/$dir")

// 自定义源码路径需要修改 unmanagedSourceDirectories 配置项
unmanagedSourceDirectories in Compile ++= Seq(
  sourceDir("子目录1"),
  sourceDir("子目录2"),
  ...
)
```

### 多项目构建
`sbt`支持多项目构建，一个项目中可包含多个子项目。  
每个子项目均可包含独立、完整的构建配置。

使用`sbt`环境中预定义的`project`方法指定子项目的路径：

```scala
// 子项目的根路径为当前路径下的 xxx 子路径
// 子项目名称 ChildProject (变量名称)
lazy val ChildProject = project in file("xxx")
```

`project`方法构建的实例类型为`sbt.Project`，代表子项目的构建定义，实例名称会作为子项目的`ID`。  
若`project in file("xxx")`中的路径信息`xxx`为`.`(项目当前路径)时，获取的实例代表默认项目的构建定义。  
`sbt.Project`类型定义了一系列控制构建配置的方法：

```scala
package sbt

sealed trait Project extends AnyRef with ProjectDefinition[ProjectReference] {
  ...
  def in(dir : java.io.File): Project //设置构建定义的对应路径
  def configs(cs: librarymanagement.Configuration*): Project
  def dependsOn(deps: ClasspathDep[ProjectReference]*): Project //设置项目依赖
  def settings(ss: Def.SettingsDefinition*): Project //设置项目通用配置
  def enablePlugins(ns: Plugins*): Project //启用指定 sbt 插件
  def disablePlugins(ps: AutoPlugin*) : Project //禁用指定 sbt 插件
  ...
}
```

使用`settings()`方法向项目中添加通用定义：

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

所有能在父级项目中设定的配置都可以添加在子项目的`settings()`方法中。

使用`enablePlugins()/disablePlugins()`方法启用/禁用`sbt`插件。  
使用`dependsOn()`方法设定依赖项目，子项目能引用依赖项目的代码，并自动引入依赖项目的`libraryDependencies`。

`sbt.Project`类型的主要方法均返回自身实例，支持**链式调用**。  
常见的配置结构，如下所示：

```scala
val root = project in file(".") //父项目配置
  .settings(
    ...
  )
  ...

val child = (project in file("xxx"))  //子项目配置
  .dependsOn(root) //设定依赖项目
  .enablePlugins(xxx) //启用插件
  .settings( //模块配置项
    name := "xxx",
    version := "xxx",
    scalaVersion := "2.12.x"
    libraryDependencies ++= Seq(
      ... //jar包依赖
    ),
    scalacOptions ++= Seq(
      ... //编译器配置
    ),
    ...
  )
```

### 处理构建冲突
`jar`打包时将多个`jar`包依赖引入同一个包时，若依赖的`jar`包包含相对路径相同的目录、文件，则可能产生冲突。

如`com.typesafe.slick:slick`和`com.typesafe.akka:akka-actor`包中的根路径下均包含`reference.conf`配置文件，
该配置记录了模块运行时必要的默认配置。  
若打包时同时依赖这两个包，则生成的`jar`包中`reference.conf`文件只会保留一份。  
运行时`akka-actor`或`slick`可能会因为缺少默认配置异常退出。

解决冲突文件的简单方案是在项目`resource`路径下手动创建冲突文件，手动合并来自不同包的冲突文件内容。  
`sbt-assembly`插件提供了更完善的打包机制，支持自定义各类冲突文件的合并策略。



## 依赖管理
通过设定`build.sbt`文件中的`libraryDependencies`变量向项目中添加**托管依赖**。

`libraryDependencies`配置项是类型为`sbt.SettingKey[scala.Seq[sbt.ModuleID]]`的**字段**。  
每一项依赖由`sbt.ModuleID`类型定义，一个具体的依赖项格式如下所示：

```scala
// 普通依赖，通常适用于Java依赖包
groupID % artifactID % revision
// 在指定配置下的依赖
groupID % artifactID % revision % configuration
// 测试时使用的依赖，在打包时会忽略该依赖项，一般用于测试库如 JUnit/Scala Test 等
groupID % artifactID % revision % Test
// 对于开放源码的库，可以指定在添加依赖时同时下载库源码和Java DOC
groupID % artifactID % revision % withSource() withJavadoc()
```

对于多数使用Scala开发的项目，项目的`artifactID`命名上通常会以使用Scala版本号作为结尾(`Scala`编译器相关模块除外，如`scala-reflect`、`scala-compiler`等)。

在添加`Scala`项目依赖时，使用`%%`操作符连接`groupID`和`artifactID`，则会将当前Scala版本号追加到`artifactID`上：

```scala
groupID %% artifactID % revision
```

等价于：

```scala
groupID % artifactID_[Scala版本] % revision
```

以`Scala 2.12`的`Akka 2.4.17`为例，依赖信息为：

```scala
"com.typesafe.akka" %% "akka-actor" % "2.4.17" //省略Scala版本信息
"com.typesafe.akka" % "akka-actor_2.12" % "2.4.17" //两种表示方式等价
```

`sbt.SettingKey`类型重载了`+=`和`++=`运算符：

- `+=`运算符用于添加单项依赖，如：

	```scala
	libraryDependencies += groupID % artifactID % revision
	```

- `++=`运算符用于添加多个依赖序列，如：

	```scala
	libraryDependencies ++= Seq(
	  groupID0 % artifactID0 % revision0,
	  groupID1 % artifactID1 % revision1,
	  ...
	)
	```

### 常用依赖
`sbt`依赖的描述信息与`Maven`相同，`sbt`允许直接添加`Maven`仓库的依赖，包的信息可以在**Maven中心仓库**搜索到，地址为`http://search.maven.org/`。

一些常用包的`GroupId`和`ArtifactId`信息如下：

| 包介绍 | GroupId | ArtifactId |
|:------|:--------|:-----------|
| MySQL JDBC Driver | mysql | mysql-connector-java |
| Scala Reflect | org.scala-lang | scala-reflect |
| Scala Swing | org.scala-lang.modules | scala-swing_[Scala版本号] |
| Scala Test | org.scalatest | scalatest_[Scala版本号] |
| ScalaFx | org.scalafx | scalafx_[Scala版本号]
| Slick | com.typesafe.slick | slick_[Scala版本号] |
| Akka | com.typesafe.akka | akka-actor_[Scala版本号] |



## 编译参数
通过设定`build.sbt`文件中的`scalacOptions`变量可以控制`scalac`编译器的编译参数。  
设定了编译参数后，执行`compile`指令时会采用设定的编译参数进行编译。

所有`scalac`支持的命令行参数都可添加，如下所示：

```scala
scalacOptions ++= Seq(
  "-feature",
  "-language:implicitConversions"
  "..."
)
```

`Scala`中的部分语言特性需要使用参数`-language:xxx`来开启：

- 使用`-language:help`参数显示所有可使用的语言特性参数。
- 使用`-language:_`参数可以开启所有的语言特性。



## *sbt-buildinfo*
`sbt`未提供访问`build.sbt`中项目构建信息的接口，使用`sbt-buildinfo`插件可以在项目中访问构建信息。  
在sbt项目中的`project/plugins.sbt`中添加：

```scala
addSbtPlugin("com.eed3si9n" % "sbt-buildinfo" % "版本号")
```

在项目构建配置文件`build.sbt`中启用`sbt-buildinfo`插件：

```scala
enablePlugins(BuildInfoPlugin)
```

`sbt-buildinfo`插件的原理是利用`build.sbt`中的项目构建信息在项目构建时生成额外的源码，
并以**单例对象**的形式将构建信息提供给项目源码进行访问。

启用`sbt-buildinfo`插件后会增加插件相关的配置项。  
将`build.sbt`中的`name、version、scalaVersion、sbtVersion`等配置项传入`sbt-buildinfo`插件的`buildInfoKeys`配置项，
通过`buildInfoPackage`配置项设定生成单例的包路径。

在`build.sbt`文件中配置`sbt-buildinfo`插件，实例如下：

```scala
// sbt项目构建信息
name := "xxx"
version := "xxx"
scalaVersion := "2.12.3"
sbtVersion := "0.13.16"

// 启用 sbt-buildinfo 插件
enablePlugins(BuildInfoPlugin)

// 设定构建信息
buildInfoKeys := Seq(name, version, scalaVersion, sbtVersion)
buildInfoPackage := "xxx.yyy.zzz" //将构建信息生成到 xxx.yyy.zzz 包路径中
```

`sbt-buildinfo`插件生成的单例对象结构如下所示：

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



## *sbt-assembly*
`sbt-assembly`插件用于将项目的所有依赖打包到一个`jar`包中。

在sbt项目的`project/plugins.sbt`中引入插件：

```scala
addSbtPlugin("com.eed3si9n" % "sbt-assembly" % "版本号")
```

### 打包参数
在bulid.sbt中可设定打包时的主要参数：

- `assemblyJarName in assembly := "xxx.jar"` 设定生成的jar包名称，默认名称为`项目名称-assembly-日期.jar`
- `test in assembly := {}` 设定要打包的测试内容，默认打包时会包含测试代码，改字段置空则不打包测试代码
- `mainClass in assembly := Some("xxx.xxx.Main")` 设定jar的主类

### 合并策略
sbt-assembly提供了完善的机制用于处理打包流程中的文件冲突：

- `MergeStrategy.deduplicate` 默认合并策略
- `MergeStrategy.first` 保留首个文件
- `MergeStrategy.last` 保留最后的文件
- `MergeStrategy.singleOrError` 文件冲突时退出
- `MergeStrategy.concat` 拼接冲突的文件
- `MergeStrategy.rename` 根据所属的jar包重命名冲突的文件
- `MergeStrategy.discard` 丢弃文件

在`build.sbt`中添加文件合并逻辑，常见的合并操作如下所示：

```scala
// 合并规则
assemblyMergeStrategy in assembly := {
  case "reference.conf" => MergeStrategy.concat //匹配指定文件
  case PathList("aaa", "bbb", _*)  => MergeStrategy.first //匹配局部路径 aaa/bbb/* 下的文件
  case f if Assembly.isConfigFile(f) => MergeStrategy.concat //匹配配置文件
  case f if f endsWith ".xsb" => MergeStrategy.last //匹配指定后缀的文件
  case f => (assemblyMergeStrategy in assembly).value(f) //使用默认合并规则
}
```

`sbt-assembly 0.14.6`版本的默认合并规则如下所示：

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

### 执行构建
启用了sbt-assembly插件后，在sbt项目的根路径下使用`sbt assembly`指令(或在`sbt shell`中执行`assembly`指令)可执行打包操作。  
若包含子项目，需要使用`project 项目名称`切换到对应项目中再执行`assembly`构建指令。

在命令行中直接执行sbt构建指定项目：

```
$ sbt "project 项目名称"; assembly
```

sbt-assembly插件提供的冲突合并策略仅在使用`sbt assembly`指令打包时生效。  
使用`IDEA`提供的打包工具，合并策略不会生效。



## *Lightbend Activator* (已废弃)
`Activator`提供了成套的`Scala`开发环境，相当于：

```
Scala编译器 + sbt + Play Framework + Akka + 项目模版 + 基于Play的WEB端项目管理
```

`Activator`内置了sbt，可以直接使用`Activator`管理、构建sbt项目。

### 安装与配置
多数Linux发行版**没有**将`Activator`添加到仓库中，因而无论是`Linux/Windows`环境下，都需要从官网下载`Activator`。

配置`Activator`方式与`sbt`类似。  
从`http://www.lightbend.com/activator/download`下载完整版的`Activator`，解压后将`bin`目录加入`PATH`环境变量中即可。

### 基本操作
在普通目录中输入`activator`指令会在浏览器中打开Activator的帮助页面。

在`sbt`项目目录中输入`activator`指令会进入`sbt shell`。

其它常见的指令：

- `$ activator ui` 进入WEB端的Activator界面
- `$ activator shell` 进入sbt交互shell
- `$ activator list-templates` 列出模版列表

`Activator`中带有大量的预定义项目模版，使用模版创建项目：

`$ activator new [项目名称] [模版名称]`

`Activator`同样支持与`sbt`相同的指令。

### 后记
在`2017-4-24`的`Lightbend`官方新闻(`https://www.lightbend.com/blog/introducing-a-new-way-to-get-started-with-lightbend-technologies-and-saying-goodbye-to-activator`)中，宣布在`2017-5-24`停止对`Activator`的支持。  
新闻中指出了`Activator`在以下的情形存在缺陷：

- 将`Activator`良好地运行在多样的机器类型上。
- 将`Activator`可靠地运行在多样的网络环境上。
- 处理双重要求：`保持更新`与`从不更新`。

鉴于`Activator`无法良好地实现以上要求，`Lightbend`停止了对`Activator`的支持并提供了以下替代方案：

- 基于`Web`技术的`Project Starter`：

	在页面`http://developer.lightbend.com/start/`中直接创建项目模版并将其下载到本地。

- 使用新增的`sbt new`指令：

	`Giter8`项目提供了`Lightbend`各类技术对应的项目模版，使用`sbt new [Giter8模版名称]`创建对应的项目模版。
