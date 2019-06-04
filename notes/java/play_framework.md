<!-- TOC -->

- [概述](#概述)
- [安裝和配置](#安裝和配置)
	- [創建項目](#創建項目)
	- [項目結構](#項目結構)
	- [設置 Play 版本](#設置-play-版本)
- [Controller (控制器)](#controller-控制器)
	- [Action](#action)
	- [Result](#result)
	- [Redirect](#redirect)
- [路由映射](#路由映射)
	- [路由語法](#路由語法)
	- [匹配規則](#匹配規則)
	- [配置多個路由文件](#配置多個路由文件)
	- [自定義 HTTP 請求處理](#自定義-http-請求處理)
- [Template (模板)](#template-模板)
	- [模板引擎簡介](#模板引擎簡介)
	- [`@` 關鍵字](#-關鍵字)
	- [模板傳參](#模板傳參)
		- [結構語法](#結構語法)
		- [定義可複用的代碼塊](#定義可複用的代碼塊)
		- [模板類型](#模板類型)
		- [自定義模板類型](#自定義模板類型)
		- [單獨使用模板引擎](#單獨使用模板引擎)
- [ORM](#orm)

<!-- /TOC -->



# 概述
`Play Framework`是一個輕量級的`MVC`框架。

早期的`Play Framework 1.x`是使用Java實現的框架，之後`Play Framework 2.x`則成爲`Lightbend`公司官方支持的框架。

`Play Framework 2.x`框架本身採用Scala實現，擁有全新的代碼基礎，對外同時提供Scala和Java的API。
`Play Framework 2.x`發佈後，原先的`Play Framework 1.x`不再有實質性的功能更新，更新只提供BUG修復。



# 安裝和配置
開發`Play Framework`需要安裝`Lightbend Activator`。
`Activator`包含了完整的Scala開發環境，使用方法在Scala筆記中已有記錄。

## 創建項目
使用activator創建新的`Play Framework`項目：

- `$ activator new [項目名稱] play-scala` 創建使用Scala作爲開發語言的`Play Framework`項目
- `$ activator new [項目名稱] play-java` 創建使用Java作爲開發語言的`Play Framework`項目

`Play Framework`項目同樣基於sbt構建，編譯、運行項目使用sbt的相關指令即可。

## 項目結構
一個新創建的`Play Framework`項目文件結構如下所示：

```
項目名稱
├── app //程序資源
│   ├── controllers
│   │   ├── AsyncController.scala
│   │   ├── CountController.scala
│   │   └── HomeController.scala
│   ├── filters
│   │   └── ExampleFilter.scala
│   ├── Filters.scala
│   ├── Module.scala
│   ├── services
│   │   ├── ApplicationTimer.scala
│   │   └── Counter.scala
│   └── views //頁面模版
│       ├── index.scala.html
│       └── main.scala.html
├── build.sbt //sbt構建腳本(定義項目依賴等配置)
├── conf //存放配置文件和非編譯資源
│   ├── application.conf //Play項目的主要配置文件
│   ├── logback.xml
│   └── routes //路由定義
├── LICENSE
├── project
│   ├── build.properties //sbt項目構建參數
│   └── plugins.sbt //sbt插件
├── public //公共資源
│   ├── images
│   │   └── favicon.png
│   ├── javascripts
│   │   └── hello.js
│   └── stylesheets
│       └── main.css
├── README
└── test
    ├── ApplicationSpec.scala
    └── IntegrationSpec.scala
```

## 設置 Play 版本
`Play Framework`項目基於`sbt`構建，框架本身是以`sbt`插件的形式定義在項目中的。
在`[項目名稱]/project/plugins.sbt`中，定義了所使用`Play Framework`的版本。

以`Play Framework 2.5.10`版本爲例，默認生成的`plugins.sbt`文件如下所示：

```scala
logLevel := Level.Warn

resolvers += "Typesafe repository" at "http://repo.typesafe.com/typesafe/releases/"

addSbtPlugin("com.typesafe.play" % "sbt-plugin" % "2.5.10") //play框架信息
```

將最後的版本號替換爲需要的目標版本號即可。



# Controller (控制器)
在`Play Framework`中，使用`Controller`(控制器)內定義的`Action`實例來響應、處理`HTTP`請求。

`Controller`是特質，完整路徑爲`play.api.mvc.Controller`。
常見的編碼方式爲繼承`Controller`特質，在`Controller`特質的子類中定義`Action`處理`HTTP`請求。

如下所示：

```scala
package controllers

import play.api.mvc._

class CustomController extends Controller {
  ...
  def xxx = Action {
    ...
  }
  ...
}
```

## Action
`Action`單例是處理`HTTP`請求的基本單位，完整路徑爲`play.api.mvc.Action`。

`Action`單例繼承自`ActionBuilder[Request]`特質，在`ActionBuilder`特質中定義瞭如下的`apply()`方法(源碼摘自`Play 2.5.10`)用於構建`Action`：

```scala
trait ActionBuilder[+R[_]] extends ActionFunction[Request, R] {
  ...
  final def apply(block: R[AnyContent] => Result): Action[AnyContent] = apply(BodyParsers.parse.default)(block)
  final def apply(block: => Result): Action[AnyContent] =
    apply(BodyParsers.parse.ignore(AnyContentAsEmpty: AnyContent))(_ => block)
  ...
}
```

基本的`Action`使用方法：

```scala
def index = Action {
  Ok("xxxx") //返回xxxx做爲HTTP請求的迴應
} //調用繼承的apply(block: => Result)方法，方法參數爲返回Result類型的傳名參數

def echo = Action {
  request => Ok(s"Request is: [$request]")
} //調用繼承的apply(block: R[AnyContent] => Result)方法，方法參數爲接收Request類型，返回Result類型的Function
```

## Result
`Action`參數方法的返回類型爲`play.api.mvc.Result`，包含了`HTTP`響應狀態碼以及返回的請求內容。

`HTTP`響應狀態在`Play Framework`中使用`play.api.mvc.Results`特質中定義的內部類`Status`表示。
`Results`特質中定義了一系列字段用於表示常用的`HTTP`狀態碼(源碼摘自`Play 2.5.10`)：

```scala
trait Results {
  ...

  class Status(status: Int) extends Result(header = ResponseHeader(status), body = HttpEntity.NoEntity) {
    ...
    def apply[C](content: C)(implicit writeable: Writeable[C]): Result = {
      Result(header, writeable.toEntity(content))
    }
    ...
  }

  /** Generates a ‘200 OK’ result. */
  val Ok = new Status(OK)

  /** Generates a ‘201 CREATED’ result. */
  val Created = new Status(CREATED)

  /** Generates a ‘202 ACCEPTED’ result. */
  val Accepted = new Status(ACCEPTED)

  /** Generates a ‘203 NON_AUTHORITATIVE_INFORMATION’ result. */
  val NonAuthoritativeInformation = new Status(NON_AUTHORITATIVE_INFORMATION)

  /** Generates a ‘204 NO_CONTENT’ result. */
  val NoContent = Result(header = ResponseHeader(NO_CONTENT), body = HttpEntity.NoEntity)

  /** Generates a ‘205 RESET_CONTENT’ result. */
  val ResetContent = Result(header = ResponseHeader(RESET_CONTENT), body = HttpEntity.NoEntity)

  /** Generates a ‘206 PARTIAL_CONTENT’ result. */
  val PartialContent = new Status(PARTIAL_CONTENT)

  /** Generates a ‘207 MULTI_STATUS’ result. */
  val MultiStatus = new Status(MULTI_STATUS)
  ...
}
```

使用`Ok()`、`Created()`等方法本質上是調用`Status`類的`apply()`方法，以頁面返回內容爲參數，生成`Result`對象。
在實際開發過程中，並不會直接在控制器中寫入頁面內容，而是調用視圖層中的模板做爲頁面的呈現內容。

`Result`對象也可以自行指定狀態碼和頁面內容創建：

```scala
import play.api.http.HttpEntity

def index = Action {
  Result(
    header = ResponseHeader(200, Map.empty),
    body = HttpEntity.Strict(ByteString("Hello world!"), Some("text/plain"))
  )
}
```

還可以使用從`Controller`特質繼承的`TODO`字段表示頁面尚未完成：

```scala
def todo = TODO
```

## Redirect
`Action`內可以不直接返回頁面結果，而是重定向到其它路徑。如下所示：

```scala
def index = Action {
  Redirect("/other") //重定向到路徑other
}
```

重定向操作會以`303 SEE_OTHER`做爲默認的返回狀態碼，如果需要手動指定狀態碼，可以在`Redirect()`同時添加狀態碼參數：

```scala
def index = Action {
  Redirect("/other", MOVED_PERMANENTLY)
}
```



# 路由映射
在Play中，路由映射寫在項目的`/conf/routes`文件內。

路由映射定義了`HTTP`請求路徑與控制器的對應關係。

## 路由語法
一條路由映射由`HTTP方法`、`HTTP路徑`、`控制器Action`三部分組成。

默認的`routes`文件內容如下：

```
# Routes
# This file defines all application routes (Higher priority routes first)
# ~~~~

# Home page
GET         /                    controllers.Application.index

# Map static resources from the /public folder to the /assets URL path
GET         /assets/*file        controllers.Assets.at(path="/public", file)
```

## 匹配規則
假設控制器定義如下：

```scala
package controllers

import play.api.mvc._

class Application extends Controller {

  def index0 = Action { Ok("Index0") }
  def index1 = Action { Ok("Index1") }

  def name(name: String) = Action {
    Ok(s"Name $name")
  }

  def name(nameId: Int) = Action {
    Ok(s"NameId $nameId")
  }

  def num(num: Int) = Action {
    Ok(s"Num: $num")
  }

}
```

匹配路徑的控制器有多個時，優先匹配位置靠前的控制器：

```
GET         /                    controllers.Application.index0
GET         /                    controllers.Application.index1		# 實際會跳轉到index0
```

- 參數匹配

	若控制器方法帶有參數，則可以使用請求路徑的一部分做爲參數匹配控制器方法：

	```
	GET        /test/:name              controllers.Application.num(name)
	```

	將會匹配所有`/test/*`形式的路徑，`*`代表的內容會做爲參數`name`傳入控制器方法中。

	匹配控制器方法時可以限定類型：

	```
	GET        /test/:num               controllers.Application.num(num: Int)
	```

	路由語法中的控制器方法不支持重載，不要在多個匹配規則中調用一個控制器的重載方法：

	```
	GET        /test/:name              controllers.Application.name(name: Int)
	GET        /test/:name              controllers.Application.name(name: String)
	```

	報錯`method name is defined twice`。

	當需要對有參控制器方法傳入固定內容的參數時，參數名稱不可省略：

	```
	GET        /test                    controllers.Application.name(name = "default")
	```

- 正則表達式匹配

	路由路徑支持使用正則表達式來進行更精確的匹配，基本語法如下所示：

	```
	GET        /路徑/$變量名稱<正則表達式>  controllers.Xxx.xxx(變量名稱)
	```

	以下兩種表達方式等價：

	```
	GET        /test/:name              controllers.Application.num(name)
	GET        /test/$name<.+>          controllers.Application.num(name)
	```

## 配置多個路由文件
除了`/conf/routes`文件，在項目路徑`/conf`下的所有`*.routes`文件都會被視作路由配置文件。

路由配置文件會被編譯成`Routes`類，該類包含了由路由配置轉換成的代碼。
生成的`Routes`類會繼承自`play.core.routing.GeneratedRouter`抽象類。

路由配置文件在生成`Routes`類時會以**文件名稱**做爲**包名**，如`test.routes`文件會對應生成`test.Routes`類。
默認的`routes`文件會生成`router.Routes`類。

`/conf/routes`爲主要的路由匹配文件，默認配置下，只有該文件內設置的路由規則生效。
可以通過`/conf/routes`跳轉到其它路由文件，以`test.routes`爲例，語法如下：

```
->          /xxxx                   test.Routes
```

該配置會匹配所有一級路徑爲`xxxx`的路徑，並跳轉到`test.routes`路由配置文件中查找匹配的路由規則。
需要注意的是，跳轉到其它路由文件時，傳入的路徑內容不包含已經匹配的部分，如路徑`xxxx/abc`在傳到`test.routes`文件中時，路徑爲`abc`。

## 自定義 HTTP 請求處理
可以通過繼承`play.api.http.DefaultHttpRequestHandler`類，重寫`routeRequest()`方法自定義`HTTP`請求處理邏輯。

如下所示：

```scala
import javax.inject.Inject

import play.api.http._
import play.api.mvc.RequestHeader

class CustomRequestHandler @Inject()(
  routes: router.Routes, // 傳入主構造器的路由配置實例爲主要路由配置
  errorHandler: HttpErrorHandler,
  configuration: HttpConfiguration,
  filters: HttpFilters)
  extends DefaultHttpRequestHandler(routes, errorHandler, configuration, filters) {

  // 注入test.routes文件生成的路由規則類
  @Inject
  private var testRoutes: test.Routes = null

  // 重寫默認的請求處理邏輯
  override def routeRequest(request: RequestHeader) = request.host match {
    case ... => super.routeRequest(request) // 滿足xxx條件使用默認路由配置
    case ... => testRoutes.routes.lift(request) // 滿足xxx條件使用test路由配置
    case _ => ...
  }

}
```

自定義的`HTTP`請求處理類需要在配置文件中啓用，在`/conf/application.conf`文件中添加：

```
play.http.requestHandler = "CustomRequestHandler" # 使用自定義HTTP請求類的類名做爲配置參數
```

`routeRequest()`方法參數爲`play.api.mvc.RequestHeader`類型，包含了完整的請求信息，可以用於`URL`過濾、驗證`Session`等諸多用途。



# Template (模板)
`Play Framework 2.x`內置了`Twirl`模板引擎。

## 模板引擎簡介
`Twirl`模板引擎採用Scala實現，使用類Scala語法，是**類型安全**的模板引擎。

模板文件爲純文本，命名規則爲`*.scala.模板類型`。
默認的`HTML`模板後綴爲`*.scala.html`。
在項目編譯時，模板文件會被編譯爲Scala類，模板文件名會做爲類名，模板文件所處的路徑會做爲模板類的包路徑。

## `@` 關鍵字
`Twirl`模板引擎使用`@`做爲引用模板語法的關鍵字，`@`關鍵字的主要用法：

- 直接引用模板參數

	```scala
	<p>Name: @name</p>
	```

- 調用模板參數的方法

	```scala
	<p>Name Length: @name.length</p>
	```

- 執行代碼塊

	```scala
	<p>@(name1.length + name2.length)</p>
	<p>@{
		val name = s"$name1 $name2"
		name
	}</p>
	```

	在使用`@{ ... }`執行代碼塊時，代碼塊的最後一個變量會做爲整個代碼塊的**返回值**。

- 添加註釋

	```scala
	@* 註釋內容 *@
	```

	使用`@* *@`插入的註釋內容在編譯期間會被清除，不會保留到最後生成的`html`文件中。

若需要在模板中輸出普通的`@`字符，則應使用`@@`。

## 模板傳參
Twirl模板引擎需要**顯式**定義模板接收的參數。
傳入模板的參數需要寫在模板文件的最頂端。

模板參數表前需要使用`@`關鍵字修飾，語法與Scala方法參數語法類似：

```scala
@(title: String)

<html>
	...
</html>
```

模板參數表支持Scala的高級語法特性，如**參數默認值**、**柯里化**、**隱式參數**等：

```scala
@(title: String)(content: Html = Html(""))(implicit css: String = null)

<html>
	...
</html>
```

模板的參數表在編譯爲Scala類時，會做爲生成類的`apply()`方法的參數表。

### 結構語法
`Twirl`模板引擎支持**循環**、**分支**等控制結構語法。

**循環**語法：

```scala
<ul>
@for(product <- products) {
	<li>@product.name ($@product.price)</li>
}
</ul>
```

**分支**語法：

```scala
@if(items.isEmpty()) {
	<h1>Nothing to display</h1>
} else {
	<h1>@items.size items!</h1>
}
```

`Twirl`模板引擎還支持Scala的模式匹配特性：

```scala
@(op: Option[String])

@op match {
	case Some(str) => {
		<p>@str</p>
	}
	case None => {
		<p>empty</p>
	}
}
```

### 定義可複用的代碼塊
在模板中，對於多次使用的內容，可以定義可複用的代碼塊。

將代碼塊賦值到模板變量上：

- 使用`@xxx = { ... }`語法將普通的`html`文本賦值到模板變量上，模板變量爲`play.twirl.api.HtmlFormat.Appendable`類型。
- 使用`@xxx = @{ ... }`語法將Scala代碼的執行結果賦值到模板變量上，模板變量類型由Scala代碼塊的**返回值**決定。

```scala
@* 模板變量保存普通html *@
@header = {
	<script type="text/javascript"> ... </script>
	<script type="text/javascript"> ... </script>
}

@* 模板變量存儲執行Scala代碼執行結果 *@
@content = @{
	val xxx = ... // @{ ... } 代碼塊中可以直接使用Scala語法
	xxx // content 變量類型由返回值 xxx 的類型決定
}

<html>

	<head>
		@header
	<head>

	<body>
		@content
	</body>

</html>
```

可複用代碼塊支持帶有參數：

```scala
@display(product: models.Product) = {
	@product.name ($@product.price) @* 輸出內容： 產品名稱 ($產品價格) *@
}

<ul>
@for(product <- products) {
	@display(product)
}
</ul>
```

在一個模板中調用其它模板，方法類似。
一個模板文件本身可視爲一個可複用的代碼塊。

### 模板類型
`Twirl`模板引擎默認支持`html`、`js`、`xml`、`txt`四種後綴的模板類型。
四種模板類型在API中已有默認定義，完整類型路徑爲：

```scala
play.twirl.api.Html
play.twirl.api.JavaScript
play.twirl.api.Xml
play.twirl.api.Txt
```

四種模板類型均繼承於`play.twirl.api.BufferedContent`，而`BufferedContent`繼承於`play.twirl.api.Appendable`和`play.twirl.api.Content`。

`BufferedContent`抽象類中定義了`buildString()`方法用於控制文本生成、轉義規則。

`Html`類型重寫了的`buildString()`方法，對於`Html`類型的模板，以下字符將被轉換：

| 轉義前字符 | 轉義後字符 |
|:--------:|:---------:|
| `<` | `&lt` |
| `>` | `&gt` |
| `"` | `&quot` |
| `\` | `$#x27` |
| `&` | `&amp` |

若需要避免文本轉義，則應使用`Html`類型伴生對象中提供的`apply()`方法將無需轉換的文本直接構造爲`Html`類型。

### 自定義模板類型
若需要擴展支持的模板文件類型，則需要在項目構建配置`build.sbt`中設定`TwirlKeys.templateFormats`配置項。
`TwirlKeys.templateFormats`配置項應添加`Map[String, String]`類型的配置：

- 配置**key**爲需要擴展的文件類型。
- 配置**value**爲文件類型對應採用的模板規則類的路徑字符串，若無需自定義規則，可以使用預置的`play.twirl.api.XxxFormat`類型。

以常見的`json`格式爲例，在`build.sbt`文件中添加：

```scala
// 將json後綴的模板應用預定義的js模板生成規則
TwirlKeys.templateFormats += "json" -> "play.twirl.api.JavaScriptFormat"
```

若現有的模板生成規則不能滿足需要，則可以自行擴展`play.twirl.api.Format[T <: Appendable[T]]`特質，重寫`raw()`、`escape()`等方法實現自定義的模板生成規則。

### 單獨使用模板引擎
`Twirl`模板引擎提供了`sbt-twirl`插件，支持在`sbt`項目中單獨使用，不依賴於完整的`Play Framework`框架。

在普通`sbt`項目中的`project/plugins.sbt`文件中引入該插件：

```scala
// 添加模板引擎插件
addSbtPlugin("com.typesafe.sbt" % "sbt-twirl" % "版本號")
```

在項目構建配置文件`build.sbt`中啓用模板引擎插件：

```scala
// 啓用模板引擎插件
enablePlugins(SbtTwirl)
```

執行編譯操作時，模板引擎編譯器會掃描`src/main/twirl`和`src/test/twirl`路徑下的所有模板文件(以`*.scala.xxx`命名)，根據模板內容生成Scala代碼。

生成模板類的路徑遵頊以下規則：

- 模板文件直接位於模板目錄中時，生成類路徑爲`模板類型.文件名稱`
- 模板文件位於模板目錄中的某個子目錄時，生成類路徑爲`子路徑.模板類型.文件名稱`

舉例，假設`sbt`項目存在以下目錄結構：

```
項目名稱
└── src
    └── main
        └── twirl
            ├── test.scala.js
            └── template
                ├── test1.scala.html
                └── test2.scala.xml
```

生成的Scala代碼類型路徑分別爲：

```scala
js.test //無子路徑直接以"模板類型"做爲包名
template.html.test1 //存在子路徑時以"子路徑.模板類型"做爲包名
template.xml.test2
```

可設置模版引擎在編譯時掃描源碼路徑(`src/main/scala`、`src/main/java`)。
在`build.sbt`中添加目錄配置：

```scala
// 使模板編譯器掃描項目源碼目錄
sourceDirectories in (Compile, TwirlKeys.compileTemplates) := (unmanagedSourceDirectories in Compile).value
```



# ORM
`Play Framework`並未內置`ORM`，需要搭配額外的`ORM`框架。

`Play Framework`支持多種`ORM`框架，官方推薦使用`Slick`。
`Slick`是`LightBend`官方支持的函數式風格的`ORM`，官方介紹中稱之爲`Functional Relational Mapping(FRM)`。

除了`Slick`，`Play Framework`還支持`Anorm`、`EBean`等ORM框架。
