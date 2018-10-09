<!-- TOC -->

- [简介](#简介)
	- [配置 Slick](#配置-slick)
	- [Play Framework 集成](#play-framework-集成)
	- [接口包路径](#接口包路径)
- [Model 定义](#model-定义)
	- [特殊类型映射](#特殊类型映射)
- [DataBase 实例](#database-实例)
	- [使用 Database 类构建实例](#使用-database-类构建实例)
	- [使用 Play Frameowrk 注入实例](#使用-play-frameowrk-注入实例)
- [查询集操作](#查询集操作)
	- [构建 TableQurey 实例](#构建-tablequrey-实例)
	- [查询](#查询)
	- [插入](#插入)
	- [修改](#修改)
	- [删除](#删除)
	- [应用查询集操作](#应用查询集操作)

<!-- /TOC -->



# 简介
`Slick`是`LightBend`官方支持的函数式风格的`ORM`框架，官方介绍中称之为`Functional Relational Mapping(FRM)`。

## 配置 Slick
Slick搭配不同数据库时需要对应的数据库驱动支持。

以MySQL为例，需要在`build.sbt`文件中添加以下依赖：

```scala
libraryDependencies ++= Seq(
  "com.typesafe.slick" %% "slick" % "版本号", //Slick ORM框架
  "com.typesafe.slick" %% "slick-hikaricp" % "版本号" //Slick 数据库连接池
  "mysql" % "mysql-connector-java" % "版本号" //JDBC 连接驱动包
)
```

默认配置下，`Slick`会使用连接池缓存数据库连接，需要搭配插件`slick-hikaricp`。

## Play Framework 集成
对于在`Play Framework`中使用`Slick`，则推荐使用`play-slick`库，该库提供了`Play Framework`的`Slick`集成，添加`sbt`依赖：

```scala
"com.typesafe.play" %% "play-slick" % "版本号"
```

`play-slick`依赖于`slick`和`slick-hikaricp`，`SBT`依赖中添加了`play-slick`则无需再添加`slick`以及`slick-hikaricp`。

## 接口包路径
Slick相关用户接口在包路径`slick.jdbc.数据库类型.api`下(`Slick 3.2.0`版本之后)。
在`Slick 3.1.1`版本之前，相关接口位于包路径`slick.driver.数据库驱动.api`下。

常见的数据库对应的包路径：

| 数据库名称 | 包路径 |
| :-: | :-: |
| MySQL | slick.jdbc.MySQLProfile.api |
| PostgresSQL | slick.jdbc.PostgresProfile.api |



# Model 定义
自定义模型类需要从`slick.jdbc.数据库类型.api.Table[T]`类型中继承。
泛型参数`T`具体可以是**元组**(`Tuple`)类型或是**样例类**，内容为表中包含的字段类型。
与Django不同，Slick**不使用**专门的类型来映射SQL字段类型，而是直接使用语言内置类型(Int、String等)映射SQL中的字段类型。

假设有以下结构的MySQL表：

```sql
CREATE TABLE `TestTable` (
	`Index` int(4) NOT NULL DEFAULT '0',
	`Name` varchar(48) NOT NULL DEFAULT '',
	PRIMARY KEY (`Index`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
```

在Slick中，该表对应的模型类可以写成：

```scala
import slick.jdbc.MySQLProfile.api._
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
import slick.jdbc.MySQLProfile.api._

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

若映射的表名不确定，则可保留构造方法中的表名参数，在运行时传入。
模型定义示例：

```scala
import slick.jdbc.MySQLProfile.api._
import slick.lifted.ProvenShape

// 保留表名参数，通过主构造方法传入
class NoNameTable(tag: Tag, tableName: String) extends Table[(Int, String)](tag, tableName) {
	...
}
```

## 特殊类型映射
对于时间类型(`MySQL`中的`DateTime`类型)，`Slick`可以将其映射到`Java`中的以下类型：

- `java.sql.Date`
- `java.sql.Time`
- `java.sql.Timestamp`

对于二进制类型(`MySQL`中的`Blob`类型)，`Slick`可以将其映射到`Java`中的以下类型：

- `java.sql.Blob`
- `java.sql.Clob`
- `Array[Byte]`



# DataBase 实例
正确配置了Slick之后，需要获取数据库对象来进行具体的增删改查操作。

Slick根据数据库类型提供了不同的`Database`类型，格式如下：

```scala
slick.jdbc.数据库类别.api.Database
```

以MySQL数据库为例，应使用`slick.jdbc.MySQLProfile.api.Database`类型。
`Database`对象在使用完毕后需要关闭以释放资源。

## 使用 Database 类构建实例
使用`Database`伴生对象中的方法直接构建数据库对象实例：

```scala
val db = Database.forDriver(
  new com.mysql.jdbc.Driver(),
  "jdbc:mysql://localhost:端口号/数据库名称",
  "MySQL用户名",
  "MySQL密码"
)

val db = Database.forURL(
  "jdbc:mysql://localhost:端口号/数据库名称",
  "MySQL用户名",
  "MySQL密码"
)
```

或者从项目配置文件`conf/application.conf`中读取数据库配置构建实例：

```scala
val db = Database.forConfig("配置名称")
```

配置格式示例：

```scala
配置名称 {
	driver = com.mysql.jdbc.Driver
	url = "jdbc:mysql://IP地址:端口号/数据库名称"
	user = "MySQL用户名"
	password = "MySQL密码"
	connectionPool = disabled
}
```

## 使用 Play Frameowrk 注入实例
对于在`Play Framework`框架中使用Slick，可以使用`play-sick`插件。

在项目配置文件`conf/application.conf`中添加数据库的具体连接配置。
使用`play-sick`时，配置中需要使用特定前缀`slick.dbs.XXX`，`XXX`需要替换为需要的配置名称。
默认配置名称为`default`，配置结构示例：

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

配置文件语法灵活，上述配置也可以写成：

```scala
slick.dbs.default.driver = "slick.driver.MySQLDriver$"
slick.dbs.default.db.driver = "com.mysql.jdbc.Driver"
slick.dbs.default.db.url = "jdbc:mysql://IP地址:端口号/数据库名称"
slick.dbs.default.db.user = "MySQL用户名"
slick.dbs.default.db.password = "MySQL密码"
```

使用`play.api.db.slick.DatabaseConfigProvider`获取数据库对象，定义示例：

```scala
trait DatabaseConfigProvider {
  def get[P <: BasicProfile]: DatabaseConfig[P]
}
```

使用`DatabaseConfigProvider`特质提供的无参`get`方法来获取配置。
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

在`Play Framework 2.4`及之前的版本，直接通过单例对象获取：

```scala
val dbConfig = DatabaseConfigProvider.get[JdbcProfile](Play.current)
val db = dbConfig.db
```

在最新的`Play Framework 2.5`中，框架设计发生了变化，不再拥有全局的`Play.current`对象。
`DatabaseConfigProvider`需要通过`DI`(`Dependcy Inject`，即**依赖注入**)的方式来获取。

一个注入了`DatabaseConfigProvider`的控制器示例：

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

默认情况下，使用配置文件`conf/application.conf`中`slick.dbs.default`配置项内写入的配置。
若需要使用自定义名称的配置，则需要使用`@NamedDatabase`注解，示例：

```scala
import play.api.db.NamedDatabase

@Singleton
class TestController @Inject()(@NamedDatabase("配置名称") dbConfig: DatabaseConfigProvider) extends Controller {
  ...
}
```

其中，**配置名称**填写的**不是**完整路径，如`slick.dbs.XXX`的配置名称仅需填写`XXX`即可。

`DatabaseConfigProvider`也可以通过`set`注入，示例：

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



# 查询集操作
查询集类型为`slick.lifted.TableQurey[T]`，该类型提供各类数据操作方法。
泛型参数类型需要为`slick.driver.数据库驱动名称.api.Table`的子类。

## 构建 TableQurey 实例
`TableQurey`类型的单例对象中提供了用于构建类型的`apply`方法，示例：

```scala
object TableQuery {

  /** Create a TableQuery for a table row class using an arbitrary constructor function. */
  def apply[E <: AbstractTable[_]](cons: Tag => E): TableQuery[E] = ...

  /** Create a TableQuery for a table row class which has a constructor of type (Tag). */
  def apply[E <: AbstractTable[_]]: TableQuery[E] = ...

}
```

对于映射表名已确定的`Table`子类，可使用无参`apply`方法直接构建实例。
以`TestTable`表为例，直接使用`TableQurey[TestTable]`即可构建实例。
示例：

```scala
val query = TableQuery[TestTable]
...
```

对于构造方法传入表名称的`Table`子类，应使用接收高阶类型参数的`apply(Tag => E)`方法。
以`NoNameTable`为例，示例：

```scala
val query = TableQuery[NoNameTable](new NoNameTable(_, "数据库中表的名称"))
```

## 查询
查询操作类似于使用Scala集合库中的**高阶函数**，常见操作如下：

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

## 插入
`TableQurey`类型重载了`+=`运算符，使用其插入新行：

```scala
val query = TableQuery[TestTable]
query += TestModel(666, "dainslef")
```

对于`PrimaryKey`或是`Unique`的列，不能插入重复的内容，否则会触发`java.sql.SQLIntegrityConstraintViolationException`异常。
使用`TableQurey`类型的`insertOrUpdate()`在插入重复字段时更新该行内容而非产生异常。

```scala
val query = TableQuery[TestTable]
query.insertOrUpdate(TestModel(666, "SSR")) //若主键为666的行已存在，则更新行的内容
```

## 修改
使用查询操作筛选出目标数据集后使用`update()`方法更新行：

```scala
val query = TableQuery[TestTable]
query.filter(_.name === "dainslef") //筛选出name为dainslef的行
  .map(_.name) //将筛选出的行中的name字段映射成新的查询集
  .update("Dainslef") //更新筛选出的行中指定字段的内容
```

## 删除
删除操作与修改操作类似，使用查询操作筛选出目标数据集之后使用`delete`方法删除行：

```scala
val query = TableQuery[TestTable]
query.filter(_.name === "dainslef").delete //删除所有name为dainslef的行
```

## 应用查询集操作
查询集`TableQurey`类型执行的操作需要通过`Database`实例才能真正执行，示例：

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
示例：

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

多个返回`DriverAction`的操作不必每次都调用`Database.run()`方法执行，可以将多个操作添加到`DBIO`序列中一并执行，示例：

```scala
val db = Database.forConfig("xxx")
val query = TableQuery[TestTable]

val actions = DBIO.seq(
  query.delete,
  query += TestModel(111, "XXXX")
)

db.run(actions) //执行多个操作
```
