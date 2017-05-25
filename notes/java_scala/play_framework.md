## 简介
`Play Framework`是一个轻量级的`MVC`框架。

早期的`Play Framework 1.x`是使用`Java`实现的框架，之后`Play Framework 2.x`则成为`Lightbend`公司官方支持的框架。

`Play Framework 2.x`框架本身采用`Scala`实现，拥有全新的代码基础，对外同时提供`Scala`和`Java`的API。  
`Play Framework 2.x`发布后，原先的`Play Framework 1.x`不再有实质性的功能更新，更新只提供BUG修复。



## 安装和配置
开发`Play Framework`需要安装`Lightbend Activator`。  
`Activator`包含了完整的Scala开发环境，使用方法在Scala笔记中已有记录。

### 创建项目
使用`activator`创建新的`Play Framework`项目：

- `$ activator new [项目名称] play-scala` 创建使用`Scala`作为开发语言的`Play Framework`项目
- `$ activator new [项目名称] play-java` 创建使用`Java`作为开发语言的`Play Framework`项目

`Play Framework`项目同样基于sbt构建，编译、运行项目使用sbt的相关指令即可。

### 项目结构
一个新创建的`Play Framework`项目文件结构如下所示：

```
项目名称
├── app //程序资源
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
│   └── views //页面模版
│       ├── index.scala.html
│       └── main.scala.html
├── build.sbt //sbt构建脚本(定义项目依赖等配置)
├── conf //存放配置文件和非编译资源
│   ├── application.conf //Play项目的主要配置文件
│   ├── logback.xml
│   └── routes //路由定义
├── libexec
│   └── activator-launch-1.3.10.jar
├── LICENSE
├── project
│   ├── build.properties //sbt项目构建参数
│   └── plugins.sbt //sbt插件
├── public //公共资源
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

### 设置 *Play* 版本
`Play Framework`项目基于`sbt`构建，框架本身是以`sbt`插件的形式定义在项目中的。  
在`[项目名称]/project/plugins.sbt`中，定义了所使用`Play Framework`的版本。

以`Play Framework 2.5.10`版本为例，默认生成的`plugins.sbt`文件如下所示：

```scala
logLevel := Level.Warn

resolvers += "Typesafe repository" at "http://repo.typesafe.com/typesafe/releases/"

addSbtPlugin("com.typesafe.play" % "sbt-plugin" % "2.5.10")		//play框架信息
```

将最后的版本号替换为需要的目标版本号即可。



## *Controller* (控制器)
在`Play Framework`中，使用`Controller`(控制器)内定义的`Action`实例来响应、处理`HTTP`请求。

`Controller`是特质，完整路径为`play.api.mvc.Controller`。  
常见的编码方式为继承`Controller`特质，在`Controller`特质的子类中定义`Action`处理`HTTP`请求。

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

### *Action*
`Action`单例是处理`HTTP`请求的基本单位，完整路径为`play.api.mvc.Action`。

`Action`单例继承自`ActionBuilder[Request]`特质，在`ActionBuilder`特质中定义了如下的`apply()`方法(源码摘自`Play 2.5.10`)用于构建`Action`：

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
  Ok("xxxx") //返回xxxx做为HTTP请求的回应
} //调用继承的apply(block: => Result)方法，方法参数为返回Result类型的传名参数

def echo = Action {
  request => Ok(s"Request is: [$request]")
} //调用继承的apply(block: R[AnyContent] => Result)方法，方法参数为接收Request类型，返回Result类型的Function
```

### *Result*
`Action`参数方法的返回类型为`play.api.mvc.Result`，包含了`HTTP`响应状态码以及返回的请求内容。

`HTTP`响应状态在`Play Framework`中使用`play.api.mvc.Results`特质中定义的内部类`Status`表示。  
`Results`特质中定义了一系列字段用于表示常用的`HTTP`状态码(源码摘自`Play 2.5.10`)：

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

使用`Ok()`、`Created()`等方法本质上是调用`Status`类的`apply()`方法，以页面返回内容为参数，生成`Result`对象。  
在实际开发过程中，并不会直接在控制器中写入页面内容，而是调用视图层中的模板做为页面的呈现内容。

`Result`对象也可以自行指定状态码和页面内容创建：

```scala
import play.api.http.HttpEntity

def index = Action {
  Result(
    header = ResponseHeader(200, Map.empty),
    body = HttpEntity.Strict(ByteString("Hello world!"), Some("text/plain"))
  )
}
```

还可以使用从`Controller`特质继承的`TODO`字段表示页面尚未完成：

```scala
def todo = TODO
```

### *Redirect*
`Action`内可以不直接返回页面结果，而是重定向到其它路径。如下所示：

```scala
def index = Action {
  Redirect("/other")	//重定向到路径other
}
```

重定向操作会以`303 SEE_OTHER`做为默认的返回状态码，如果需要手动指定状态码，可以在`Redirect()`同时添加状态码参数：

```scala
def index = Action {
  Redirect("/other", MOVED_PERMANENTLY)
}
```



## 路由映射
在`Play Framework`中，路由映射写在项目的`/conf/routes`文件内。

路由映射定义了`HTTP`请求路径与控制器的对应关系。

### 路由语法
一条路由映射由`HTTP方法`、`HTTP路径`、`控制器Action`三部分组成。

默认的`routes`文件内容如下：

```
# Routes
# This file defines all application routes (Higher priority routes first)
# ~~~~

# Home page
GET         /                    controllers.Application.index

# Map static resources from the /public folder to the /assets URL path
GET         /assets/*file        controllers.Assets.at(path="/public", file)
```

### 匹配规则
假设控制器定义如下：

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

匹配路径的控制器有多个时，优先匹配位置靠前的控制器：

```
GET         /                    controllers.Application.index0
GET         /                    controllers.Application.index1		# 实际会跳转到index0
```

- 参数匹配

	若控制器方法带有参数，则可以使用请求路径的一部分做为参数匹配控制器方法：

	```
	GET        /test/:name              controllers.Application.num(name)
	```

	将会匹配所有`/test/*`形式的路径，`*`代表的内容会做为参数`name`传入控制器方法中。

	匹配控制器方法时可以限定类型：

	```
	GET        /test/:num               controllers.Application.num(num: Int)
	```

	路由语法中的控制器方法不支持重载，不要在多个匹配规则中调用一个控制器的重载方法：

	```
	GET        /test/:name              controllers.Application.name(name: Int)
	GET        /test/:name              controllers.Application.name(name: String)
	```

	报错`method name is defined twice`。

	当需要对有参控制器方法传入固定内容的参数时，参数名称不可省略：

	```
	GET        /test                    controllers.Application.name(name = "default")
	```

- 正则表达式匹配

	路由路径支持使用正则表达式来进行更精确的匹配，基本语法如下所示：

	```
	GET        /路径/$变量名称<正则表达式>  controllers.Xxx.xxx(变量名称)
	```

	以下两种表达方式等价：

	```
	GET        /test/:name              controllers.Application.num(name)
	GET        /test/$name<.+>          controllers.Application.num(name)
	```

### 配置多个路由文件
除了`/conf/routes`文件，在项目路径`/conf`下的所有`*.routes`文件都会被视作路由配置文件。

路由配置文件会被编译成`Routes`类，该类包含了由路由配置转换成的代码。  
生成的`Routes`类会继承自`play.core.routing.GeneratedRouter`抽象类。

路由配置文件在生成`Routes`类时会以**文件名称**做为**包名**，如`test.routes`文件会对应生成`test.Routes`类。  
默认的`routes`文件会生成`router.Routes`类。

`/conf/routes`为主要的路由匹配文件，默认配置下，只有该文件内设置的路由规则生效。  
可以通过`/conf/routes`跳转到其它路由文件，以`test.routes`为例，语法如下：

```
->          /xxxx                   test.Routes
```

该配置会匹配所有一级路径为`xxxx`的路径，并跳转到`test.routes`路由配置文件中查找匹配的路由规则。  
需要注意的是，跳转到其它路由文件时，传入的路径内容不包含已经匹配的部分，如路径`xxxx/abc`在传到`test.routes`文件中时，路径为`abc`。

### 自定义 *HTTP* 请求处理
可以通过继承`play.api.http.DefaultHttpRequestHandler`类，重写`routeRequest()`方法自定义`HTTP`请求处理逻辑。

如下所示：

```scala
import javax.inject.Inject

import play.api.http._
import play.api.mvc.RequestHeader

class CustomRequestHandler @Inject()(
  routes: router.Routes, // 传入主构造器的路由配置实例为主要路由配置
  errorHandler: HttpErrorHandler,
  configuration: HttpConfiguration,
  filters: HttpFilters)
  extends DefaultHttpRequestHandler(routes, errorHandler, configuration, filters) {

  // 注入test.routes文件生成的路由规则类
  @Inject
  private var testRoutes: test.Routes = null

  // 重写默认的请求处理逻辑
  override def routeRequest(request: RequestHeader) = request.host match {
    case ... => super.routeRequest(request) // 满足xxx条件使用默认路由配置
    case ... => testRoutes.routes.lift(request) // 满足xxx条件使用test路由配置
    case _ => ...
  }

}
```

自定义的`HTTP`请求处理类需要在配置文件中启用，在`/conf/application.conf`文件中添加：

```
play.http.requestHandler = "CustomRequestHandler" # 使用自定义HTTP请求类的类名做为配置参数
```

`routeRequest()`方法参数为`play.api.mvc.RequestHeader`类型，包含了完整的请求信息，可以用于`URL`过滤、验证`Session`等诸多用途。



## *Template* (模板)
`Play Framework 2.x`内置了`Twirl`模板引擎。

### 模板引擎简介
`Twirl`模板引擎采用`Scala`实现，使用类`Scala`语法，是**类型安全**的模板引擎。

模板文件为纯文本，后缀为`*.scala.html`。  
在项目编译时，模板文件会被编译为`Scala`类，模板文件名会做为类名，模板文件所处的路径会做为模板类的包路径。

### *@* 关键字
`Twirl`模板引擎使用`@`做为引用模板语法的关键字，`@`关键字的主要用法：

- 直接引用模板参数

	```scala
	<p>Name: @name</p>
	```

- 调用模板参数的方法

	```scala
	<p>Name Length: @name.length</p>
	```

- 执行代码块

	```scala
	<p>@(name1.length + name2.length)</p>
	<p>@{
		val name = s"$name1 $name2"
		name
	}</p>
	```

	在使用`@{ ... }`执行代码块时，代码块的最后一个变量会做为整个代码块的**返回值**。

- 添加注释

	```scala
	@* 注释内容 *@
	```

	使用`@* *@`插入的注释内容在编译期间会被清除，不会保留到最后生成的`html`文件中。

若需要在模板中输出普通的`@`字符，则应使用`@@`。

### 模板传参
`Twirl`模板引擎需要**显式**定义模板接收的参数。  
传入模板的参数需要写在模板文件的最顶端。

模板参数表前需要使用`@`关键字修饰，语法与`Scala`方法参数语法类似：

```scala
@(title: String)

<html>
	...
</html>
```

模板参数表支持`Scala`的高级语法特性，如**参数默认值**、**柯里化**、**隐式参数**等：

```scala
@(title: String)(content: Html = Html(""))(implicit css: String = null)

<html>
	...
</html>
```

模板的参数表在编译为`Scala`类时，会做为生成类的`apply()`方法的参数表。

### 结构语法
`Twirl`模板引擎支持**循环**、**分支**等控制结构语法。

**循环**语法：

```scala
<ul>
@for(product <- products) {
	<li>@product.name ($@product.price)</li>
}
</ul>
```

**分支**语法：

```scala
@if(items.isEmpty()) {
	<h1>Nothing to display</h1>
} else {
	<h1>@items.size items!</h1>
}
```

`Twirl`模板引擎还支持`Scala`的模式匹配特性：

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

### 定义可复用的代码块
在模板中，对于多次使用的内容，可以定义可复用的代码块。

将代码块赋值到模板变量上：

- 使用`@xxx = { ... }`语法将普通的`html`文本赋值到模板变量上，模板变量为`play.twirl.api.HtmlFormat.Appendable`类型。
- 使用`@xxx = @{ ... }`语法将`Scala`代码的执行结果赋值到模板变量上，模板变量类型由`Scala`代码块的**返回值**决定。

```scala
@* 模板变量保存普通html *@
@header = {
	<script type="text/javascript"> ... </script>
	<script type="text/javascript"> ... </script>
}

@* 模板变量存储执行Scala代码执行结果 *@
@content = @{
	val xxx = ...
	xxx @* content 变量类型由返回值 xxx 的类型决定 *@
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

可复用代码块支持带有参数：

```scala
@display(product: models.Product) = {
	@product.name ($@product.price)		@* 输出内容： 产品名称 ($产品价格) *@
}

<ul>
@for(product <- products) {
	@display(product)
}
</ul>
```

在一个模板中调用其它模板，方法类似。  
一个模板文件本身可视为一个可复用的代码块。

### 模板类型
`Twirl`模板引擎默认支持`html`、`js`、`xml`、`txt`四种后缀的模板类型。
四种模板类型在API中已有默认定义，完整类型路径为：

```scala
play.twirl.api.Html
play.twirl.api.JavaScript
play.twirl.api.Xml
play.twirl.api.Txt
```

四种模板类型均继承于`play.twirl.api.BufferedContent`，而`BufferedContent`继承于`play.twirl.api.Appendable`和`play.twirl.api.Content`。  

`BufferedContent`抽象类中定义了`buildString()`方法用于控制文本生成、转义规则。

`Html`类型重写了的`buildString()`方法，对于`Html`类型的模板，以下字符将被转换：

| 转义前字符 | 转义后字符 |
|:--------:|:---------:|
| `<` | `&lt` |
| `>` | `&gt` |
| `"` | `&quot` |
| `\` | `$#x27` |
| `&` | `&amp` |

若需要避免文本转义，则应使用`Html`类型伴生对象中提供的`apply()`方法将无需转换的文本直接构造为`Html`类型。

### 自定义模板类型
若需要扩展支持的模板文件类型，则需要在项目构建配置`build.sbt`中设定`TwirlKeys.templateFormats`配置项。  
`TwirlKeys.templateFormats`配置项应添加`Map[String, String]`类型的配置：

- 配置**key**为需要扩展的文件类型。
- 配置**value**为文件类型对应采用的模板规则类的路径字符串，若无需自定义规则，可以使用预置的`play.twirl.api.XxxFormat`类型。

以常见的`json`格式为例，在`build.sbt`文件中添加：

```
// 将json后缀的模板应用预定义的js模板生成规则
TwirlKeys.templateFormats += "json" -> "play.twirl.api.JavaScriptFormat"
```

若现有的模板生成规则不能满足需要，则可以自行扩展`play.twirl.api.Format[T <: Appendable[T]]`特质，重写`raw()`、`escape()`等方法实现自定义的模板生成规则。

### 单独使用模板引擎
`Twirl`模板引擎支持在`sbt`项目中单独使用，不依赖于完整的`Play Framework`框架。

在普通`sbt`项目中的`project/plugins.sbt`文件中添加模板引擎的`sbt`插件：

```scala
// 添加模板引擎插件
addSbtPlugin("com.typesafe.sbt" % "sbt-twirl" % "版本号")
```

在项目构建配置文件`build.sbt`中启用模板引擎并配置模板编译扫描路径：

```scala
// 启用模板引擎插件
enablePlugins(SbtTwirl)

// 使模板编译器扫描源码下的模板目录
sourceDirectories in (Compile, TwirlKeys.compileTemplates) := (unmanagedSourceDirectories in Compile).value
```

启动了路径设置后，执行编译操作时，模板引擎编译器会扫描`src/main/scala`、`src/main/java`路径下的所有模板文件，根据模板生成`Scala`代码。  
生成的模板类会以子路径名做为**包名**。



## ORM
与`Django`不同，与`Spring MVC`类似，`Play Framework`需要搭配额外的ORM框架。

`Play Framework`支持多种ORM框架，推荐使用`Slick`。  
`Slick`是`LightBend`官方支持的函数式风格的ORM框架，官方介绍中称之为`Functional Relational Mapping(FRM)`。  
除了`Slick`，`Play Framework`还支持`Anorm`、`EBean`等ORM框架。

### 配置 *Slick*
`Slick`搭配不同数据库时需要对应的数据库驱动支持。

以`MySQL`为例，需要在`build.sbt`文件中添加以下依赖：

```scala
libraryDependencies ++= Seq(
  "com.typesafe.slick" %% "slick" % "版本号", //Slick ORM框架
  "com.typesafe.slick" %% "slick-hikaricp" % "版本号" //Slick 数据库连接池
  "mysql" % "mysql-connector-java" % "版本号" //JDBC 连接驱动包
)
```

默认配置下，`Slick`会使用连接池缓存数据库连接，因此需要`slick-hikaricp`。

对于在`Play`框架中使用`Slick`，则推荐使用`play-slick`库，该库提供了`Play`框架的`Slick`集成，添加`SBT`依赖：

```scala
"com.typesafe.play" %% "play-slick" % "版本号"
```

`play-slick`依赖于`slick`和`slick-hikaricp`，`SBT`依赖中添加了`play-slick`则无需再添加`slick`以及`slick-hikaricp`。

添加框架依赖之后，需要在项目配置文件`conf/application.conf`中添加数据库的具体连接配置。

```scala
slick.dbs.default { //"default"为默认的配置名称，可以自行修改
	driver = "slick.driver.MySQLDriver$" //Slick对应数据库的驱动，注意"$"符号不能少
	db {
		driver = "com.mysql.jdbc.Driver" //JDBC驱动
		url = "jdbc:mysql://IP地址:端口号/数据库名称" //数据库连接字符串
		user= "MySQL用户名" //数据库用户名
		password = "MySQL密码" //数据库密码
		connectionPool = disabled/enabled //是否使用连接池，使用连接池则需要slick-hikaricp插件支持
	}
}
```

`Play Framework`的配置文件语法灵活，上述配置也可以写成：

```scala
slick.dbs.default.driver = "slick.driver.MySQLDriver$"
slick.dbs.default.db.driver = "com.mysql.jdbc.Driver"
slick.dbs.default.db.url = "jdbc:mysql://IP地址:端口号/数据库名称"
slick.dbs.default.db.user = "MySQL用户名"
slick.dbs.default.db.password = "MySQL密码"
```

### 定义 *Slick* 对象模型
自定义模型类需要从`slick.driver.数据库驱动名称.api.Table[T]`类型中继承，对于不同的数据库，需要使用不同的数据库驱动名称，例如：

- `MySQL`数据库驱动名称为`MySQLDriver`，完整路径则为`slick.driver.MySQLDriver.api.Table[T]`。
- `PostgresSQL`数据库驱动名称为`PostgresDriver`，完整路径为`slick.driver.PostgresDriver.api.Table[T]`。

泛型参数`T`具体可以是**元组**(`Tuple`)类型或是**样例类**，内容为表中包含的字段类型。  
与`Django`不同，`Slick`**不使用**专门的类型来映射SQL字段类型，而是直接使用语言内置类型(`Int`、`String`等)映射SQL中的字段类型。

假设有以下结构的MySQL表：

```sql
CREATE TABLE `TestTable` (
	`Index` int(4) NOT NULL DEFAULT '0',
	`Name` varchar(48) NOT NULL DEFAULT '',
	PRIMARY KEY (`Index`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
```

在Play框架中，该表对应的模型类可以写成：

```scala
import slick.driver.MySQLDriver.api._
import slick.lifted.ProvenShape

// 元组参数类型为表中字段的类型，参数中可以指定对应表在数据库中的名称
class TestTable(tag: Tag) extends Table[(Int, String)](tag, "TestTable") {

  // 列的类型为Rep，使用cloumn方法生成，参数中可以指定列对象对应的SQL字段的名称
  def index: Rep[Int] = cloumn[Int]("Index", O.PrimaryKey)
  def name: Rep[String] = column[String]("Name")

  // ProvenShape类型由隐式转换得到，重写无参*方法确定字段的排列顺序
  def * : ProvenShape[(Int, String)] = (index, name)
}
```

对于简单的表格直接使用**元组**表示代码更为简洁，但若表格结构较为复杂则应为表格结构定义单独的**样例类**，上表采用样例类可以改写为：

```scala
import slick.driver.MySQLDriver.api._

// 使用样例类来表示表格的结构
case class TestModel(index: Int, name: String)

// 元组参数类型为表中字段的类型，参数中可以指定对应表在数据库中的名称
class TestTable(tag: Tag) extends Table[TestModel](tag, "TestTable") {

  // 具体类型可以省略
  def index = cloumn[Int]("Index", O.PrimaryKey)
  def name = column[String]("Name")

  // 需要使用<>()方法将元组与样例类绑定
  def * = (index, name) <> (TestModel.tupled, TestModel.unapply)
}
```

对于时间类型(`MySQL`中的`DateTime`类型)，`Slick`可以将其映射到`Java`中的以下类型：

- `java.sql.Date`
- `java.sql.Time`
- `java.sql.Timestamp`

对于二进制类型(`MySQL`中的`Blob`类型)，`Slick`可以将其映射到`Java`中的以下类型：

- `java.sql.Blob`
- `java.sql.Clob`
- `Array[Byte]`

### 获取 *DataBase* 实例
正确配置了`Slick`之后，需要获取数据库对象来进行具体的增删改查操作。

- 使用`play.api.db.slick.DatabaseConfigProvider`获取数据库对象：

	`DatabaseConfigProvider`需要在sbt中添加`play-slick`插件。

	使用`DatabaseConfigProvider`特质提供的无参`get`方法来获取写在`conf/application.conf`文件中的特定数据库配置：

	```scala
	trait DatabaseConfigProvider {
	  def get[P <: BasicProfile]: DatabaseConfig[P]
	}
	```

	配置类型`DatabaseConfig`定义如下：

	```scala
	trait DatabaseConfig[P <: BasicProfile] {
	  val driver: P
	  def db: P#Backend#Database
	  def config: Config
	  def driverName: String
	  def driverIsObject: Boolean
	}
	```

	使用无参方法`db`即可获得可供操作的数据库对象。  
	`Database`对象在使用完毕后需要关闭。

	在`Play 2.4`及之前的版本，直接通过单例对象获取：

	```scala
	val dbConfig = DatabaseConfigProvider.get[JdbcProfile](Play.current)
	val db = dbConfig.db
	```

	在最新的`Play 2.5`中，`Play Framework`的设计发生了变化，不再拥有全局的`Play.current`对象。  
	`DatabaseConfigProvider`需要通过`DI`(`Dependcy Inject`，即**依赖注入**)的方式来获取。  
	一个注入了`DatabaseConfigProvider`的控制器如下所示：

	```scala
	import javax.inject.Inject

	import slick.driver.JdbcProfile
	import play.api.mvc._
	import play.api.db.slick.DatabaseConfigProvider

	@Singleton
	class TestController @Inject()(dbConfig: DatabaseConfigProvider) extends Controller {
	  def testPage = Action {
	    val db = dbConfig.get[JdbcProfile].db
	    ...
	    Ok(...)
	  }
	}
	```

	默认情况下，使用的是配置文件`conf/application.conf`中`slick.dbs.default`配置项内写入的配置。  
	若需要使用自定义配置，则需要使用`@NamedDatabase`注解，如下所示：

	```scala
	import play.api.db.NamedDatabase

	@Singleton
	class TestController @Inject()(@NamedDatabase("配置名称") dbConfig: DatabaseConfigProvider) extends Controller {
	  ...
	}
	```

	其中，**配置名称**填写的**不是**完整路径，如`slick.dbs.XXX`的配置名称仅需填写`XXX`即可。

	`DatabaseConfigProvider`也可以通过`set`注入，如下所示：

	```scala
	import javax.inject.Inject

	import slick.driver.JdbcProfile
	import play.api.mvc._
	import play.api.db.NamedDatabase
	import play.api.db.slick.DatabaseConfigProvider

	@Singleton
	class TestController extends Controller {

	  // 成员字段需要为可变对象var才能注入，val字段不能注入
	  @Inject
	  @NamedDatabase("配置名称")
	  private var dbConfig: DatabaseConfigProvider = null

	  def testPage = Action {
	    val database = dbConfig.get[JdbcProfile].db
	    ...
	    Ok(...)
	  }
	}
	```

- 使用`slick.driver.MySQLDriver.api.Database`获取数据库对象：

	在**不使用**`play-slick`插件或是单独使用`Slick`框架的情况下，可以使用`Database`类来直接构建数据库对象：

	```scala
	val db = Database.forDriver(
	  new com.mysql.jdbc.Driver(),
	  "jdbc:mysql://localhost:端口号/数据库名称",
	  "MySQL用户名",
	  "MySQL密码")
	```

	`Database`类同样支持从项目配置文件`conf/application.conf`中读取数据库配置：

	```scala
	val db = Database.forConfig("配置名称")
	```

	`Database`类需要的配置无需`slick.dbs.xxx`的前缀，仅需`slick.dbs.xxx.db`部分的内容：

	```scala
	配置名称 = {
		driver = com.mysql.jdbc.Driver
		url = "jdbc:mysql://IP地址:端口号/数据库名称"
		user = "MySQL用户名"
		password = "MySQL密码"
		connectionPool = disabled
	}
	```

### 查询集操作
以`slick.driver.数据库驱动名称.api.Table`的子类做为为泛型参数，构建`slick.lifted.TableQurey[T]`查询集实例，该实例提供各类数据操作方法。

`TableQurey`类型的单例对象中提供了无参的`apply`方法，以`TestTable`表为例，直接使用`TableQurey[TestTable]`即可构建实例。

- 查询

	查询操作类似于使用`Scala`集合库中的**高阶函数**，常见操作如下：

	```scala
	val query = TableQuery[TestTable]
	query.filter(_.name === "abc") //筛选出符合条件的数据
	query.drop(10) //丢弃前10条数据
	query.take(5) //截取前5条数据
	query.sortBy(_.index) //按index字段排序数据(增序)
	query.sortBy(_.index.desc) //按index字段排序数据(减序)
	```

	高阶函数内的数据表列实际类型均为`slick.lifted.Rep[T]`。

	在使用`filter()`方法筛选数据时，`Rep`类型重载了基本运算符，可直接使用`>`、`<`、`>=`、`<=`等运算符进行比较。  
	但在表示`==`、`!=`操作时，需要使用`===`、`=!=`操作符代替，原因是基类`Any`已经定义了`==`、`!=`操作符，不能通过隐式转换调用。

- 插入

	`TableQurey`类型重载了`+=`运算符，使用其插入新行：

	```scala
	val query = TableQuery[TestTable]
	query += TestModel(666, "dainslef")
	```

	对于`PrimaryKey`或是`Unique`的列，不能插入重复的内容，否则会触发`java.sql.SQLIntegrityConstraintViolationException`异常。
	使用`TableQurey`类型的`insertOrUpdate()`在插入重复字段时更新该行内容而非产生异常。

	```scala
	val query = TableQuery[TestTable]
	query.insertOrUpdate(TestModel(666, "SSR"))		//若主键为666的行已存在，则更新行的内容
	```

- 修改

	使用查询操作筛选出目标数据集后使用`update()`方法更新行：

	```scala
	val query = TableQuery[TestTable]
	query.filter(_.name === "dainslef") //筛选出name为dainslef的行
	  .map(_.name) //将筛选出的行中的name字段映射成新的查询集
	  .update("Dainslef") //更新筛选出的行中指定字段的内容
	```

- 删除

	删除操作与修改操作类似，使用查询操作筛选出目标数据集之后使用`delete`方法删除行：

	```scala
	val query = TableQuery[TestTable]
	query.filter(_.name === "dainslef").delete //删除所有name为dainslef的行
	```

### 应用查询集操作
查询集`TableQurey`类型执行的操作需要通过`Database`实例才能真正执行，如下所示：

```scala
val db = Database.forConfig("xxx")
val query = TableQuery[TestTable]

query... //执行各类查询过滤操作

val action = query.result //获取查询操作，返回类型为DriverAction[T]
val future = db.run(action)
```

`Database.run()`方法为异步执行，调用方法时不会阻塞，返回类型为`Future[Seq[XxxModel]]`。  
若需要同步等待数据操作结束，可以使用`Await.result()`方法，该方法同时返回`Future`的执行结果：

```scala
val result = Await.result(future, Duration.Inf)
```

若查询的内容不存在，`Future`内包含的查询结果序列`Seq[XxxModel]`大小为`0`(不是`null`)。

对于所有返回`DriverAction`类型的操作都需要使用`Database.run()`方法执行才能生效。  
如下所示：

```scala
val db = Database.forConfig("xxx")
val query = TableQuery[TestTable]

query.delete //删除、插入等操作返回类型皆为DriverAction
query += TestModel(111, "XXXX") //未生效

val action = query.result
val future = db.run(action) //获取的结果未改变
```

正确的做法是：

```scala
val db = Database.forConfig("xxx")
val query = TableQuery[TestTable]

db.run(query.delete)
db.run(query += TestModel(111, "XXXX")) //使用Database.run()方法使操作生效

val action = query.result
val future = db.run(action)
```

多个返回`DriverAction`的操作不必每次都调用`Database.run()`方法执行，可以将多个操作添加到`DBIO`序列中一并执行，如下所示：

```scala
val db = Database.forConfig("xxx")
val query = TableQuery[TestTable]

val actions = DBIO.seq(
  query.delete,
  query += TestModel(111, "XXXX")
)

db.run(actions) //执行多个操作
```
