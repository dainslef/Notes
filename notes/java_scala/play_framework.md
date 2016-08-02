## 简介
`Play Framework`是一个轻量级的`MVC`框架。

早期的`Play Framework 1.x`是使用`Java`实现的框架，之后`Play Framework 2.x`则成为`Lightbend`公司官方支持的框架。

`Play Framework 2.x`框架本身采用`Scala`实现，拥有全新的代码基础，对外同时提供`Scala`和`Java`的API。
`Play Framework 2.x`发布后，原先的`Play Framework 1.x`不再有实质性的功能更新，更新只提供BUG修复。



## 安装和配置 *Play Framework*
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
├── app									//程序资源
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
│   └── views							//页面模版
│       ├── index.scala.html
│       └── main.scala.html
├── bin
│   ├── activator
│   └── activator.bat
├── build.sbt							//sbt构建脚本(定义项目依赖等配置)
├── conf								//存放配置文件和非编译资源
│   ├── application.conf				//Play项目的主要配置文件
│   ├── logback.xml
│   └── routes							//路由定义
├── libexec
│   └── activator-launch-1.3.10.jar
├── LICENSE
├── project
│   ├── build.properties				//sbt项目构建参数
│   └── plugins.sbt						//sbt插件
├── public								//公共资源
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



## ORM
与`Django`不同，与`SpringMVC`类似，`Play Framework`需要搭配额外的ORM框架。

`Play Framework`支持多种ORM框架，推荐使用`Slick`，`Slick`时`LightBend`官方开发的函数式风格的ORM框架，官方介绍中称之为`Functional Relational Mapping(FRM)`。
除了`Slcik`，`Play Framework`还支持`Anorm`、`EBean`等ORM框架。

### 配置 *Slick*
`Slick`搭配不同数据库时需要对应的数据库驱动支持。

以`MySQL`为例，需要在`build.sbt`文件中添加以下依赖：

```scala
libraryDependencies ++= Seq(
	"com.typesafe.slick" %% "slick" % "版本号",		//Slick ORM框架
	"mysql" % "mysql-connector-java" % "版本号"		//JDBC 连接驱动包
)
```

对于在`Play`框架中使用`Slick`，则推荐使用`play-slick`库，该库提供了`Play`框架的`Slick`集成，添加`SBT`依赖：

```scala
"com.typesafe.play" %% "play-slick" % "版本号"
```

`play-slick`依赖于`slick`，`SBT`依赖中添加了`play-slick`则无需再添加`slick`。

添加框架依赖之后，需要在项目配置文件`conf/application.conf`中添加数据库的具体连接配置。

```scala
slick.dbs.default {											//"default"为默认的配置名称，可以自行修改
	driver = "slick.driver.MySQLDriver$"					//Slick对应数据库的驱动，注意"$"符号不能少
	db {
		driver = "com.mysql.jdbc.Driver"					//JDBC驱动
		url = "jdbc:mysql://localhost:3306/db_name"			//数据库连接字符串
		user= "dainslef"									//数据库用户名
		password = "XXX"									//数据库密码
	}
}
```

`Play Framework`的配置文件语法灵活，上述配置也可以写成：

```scala
slick.dbs.default.driver = "slick.driver.MySQLDriver"
slick.dbs.default.db.driver = "com.mysql.jdbc.Driver"
slick.dbs.default.db.url = "jdbc:mysql://localhost:3306/db_name"
slick.dbs.default.db.user = "dainslef"
slick.dbs.default.db.password = "XXX"
```

### 定义 *Slick* 对象模型
自定义模型类需要从`slick.driver.数据库驱动名称.api.Table[T]`类型中继承，对于不同的数据库，需要使用不同的数据库驱动名称，例如：

- `MySQL`数据库驱动名称为`MySQLDriver`，完整路径则为`slick.driver.MySQLDriver.api.Table[T]`。
- `PostgresSQL`数据库驱动名称为`PostgresDriver`，完整路径为`slick.driver.PostgresDriver.api.Table[T]`。

泛型参数`T`具体可以是**元组**(`Tuple`)类型或是**样例类**，内容为表中包含的字段类型。
与django不同，Slick**不使用**专门的类型来映射SQL字段类型，而是直接使用语言内置类型(`Int`、`String`等)映射SQL中的字段类型。

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
case class TestTableMember(index: Int, name: String)

// 元组参数类型为表中字段的类型，参数中可以指定对应表在数据库中的名称
class TestTable(tag: Tag) extends Table[TestTableMember](tag, "TestTable") {

	// 具体类型可以省略
	def index = cloumn[Int]("Index", O.PrimaryKey)
	def name = column[String]("Name")

	// 需要使用<>()方法将元组与样例类绑定
	def * = (index, name) <> (TestTableMember.tupled, TestTableMember.unapply)
}
```

### 使用 *Slick* 访问数据库
正确配置了`Slick`之后，需要获取数据库对象来进行具体的增删改查操作。

使用`play.api.db.slick.DatabaseConfigProvider`获取数据库对象
> `DatabaseConfigProvider`来自于`play-slick`插件，仅仅依赖`Slick`是不够的。

> 使用`DatabaseConfigProvider`特质提供的无参`get`方法来获取写在`conf/application.conf`文件中的特定数据库配置：

```scala
trait DatabaseConfigProvider {
	def get[P <: BasicProfile]: DatabaseConfig[P]
}
```

> 配置类型`DatabaseConfig`定义如下：

>	```scala
>	trait DatabaseConfig[P <: BasicProfile] {
>		/** Get the configured Database. It is instantiated lazily when this method is called for the
>			* first time, and must be closed after use. */
>		def db: P#Backend#Database

>		/** The configured driver. */
>		val driver: P

>		/** The raw configuration. */
>		def config: Config

>		/** The name of the driver class or object (without a trailing "$"). */
>		def driverName: String

>		/** Whether the `driverName` represents an object instead of a class. */
>		def driverIsObject: Boolean
>	}
>	```

> 使用无参方法`db`即可获得可供操作的数据库对象。

> 在`Play 2.4`及之前的版本，直接通过单例对象获取：

>	```scala
>	val dbConfig = DatabaseConfigProvider.get[JdbcProfile](Play.current)
>	val database = dbConfig.db
>	```

> 在最新的`Play 2.5`中，`Play`框架的设计发生了变化，不再拥有全局的`Play.current`对象，`DatabaseConfigProvider`也需要通过`DI`(`Dependcy Inject`，即**依赖注入**)的方式来获取，一个注入了`DatabaseConfigProvider`的控制器如下所示：

>	```scala
>	import javax.inject.Inject

>	import play.api.mvc._
>	import slick.driver.JdbcProfile
>	import play.api.db.slick.DatabaseConfigProvider

>	@Singleton
>	class TestController @Inject()(dbConfig: DatabaseConfigProvider) extends Controller {
>		def testPage = Action {
>			val database = dbConfig.get[JdbcProfile].db
>			...
>			Ok(...)
>		}
>	}
>	```

> 默认情况下，使用的是配置文件`conf/application.conf`中`slick.dbs.default`配置项内写入的配置，如果需要使用自定义配置，则需要使用`@NamedDatabase`注解，如下所示：

>	```scala
>	import play.api.db.NamedDatabase

>	@Singleton
>	class TestController @Inject()(@NamedDatabase("配置名称") dbConfig: DatabaseConfigProvider) extends Controller {
>		...
>	}
>	```

> 其中，**配置名称**填写的**不是**完整路径，如`slick.dbs.XXX`的配置名称仅需填写`XXX`即可。

使用`slick.driver.MySQLDriver.api.Database`获取数据库对象
> 在**不使用**`play-slick`插件或是单独使用`Slick`框架的情况下，可以使用`Database`类来直接构建数据库对象：

>	```scala
>	val database = Database.forDriver(
>		new com.mysql.jdbc.Driver(),
>		"jdbc:mysql://localhost:端口号/数据库名称",
>		"MySQL用户名",
>		"MySQL密码")
>	```