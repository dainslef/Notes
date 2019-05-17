<!-- TOC -->

- [簡介](#簡介)
	- [配置 Slick](#配置-slick)
	- [Play Framework 集成](#play-framework-集成)
	- [接口包路徑](#接口包路徑)
- [Model 定義](#model-定義)
	- [特殊類型映射](#特殊類型映射)
- [DataBase 實例](#database-實例)
	- [使用 Database 類構建實例](#使用-database-類構建實例)
	- [使用 Play Frameowrk 注入實例](#使用-play-frameowrk-注入實例)
- [查詢集操作](#查詢集操作)
	- [構建 TableQurey 實例](#構建-tablequrey-實例)
	- [查詢](#查詢)
	- [插入](#插入)
	- [修改](#修改)
	- [刪除](#刪除)
	- [應用查詢集操作](#應用查詢集操作)

<!-- /TOC -->



# 簡介
`Slick`是`LightBend`官方支持的函數式風格的`ORM`框架，官方介紹中稱之爲`Functional Relational Mapping(FRM)`。

## 配置 Slick
Slick搭配不同數據庫時需要對應的數據庫驅動支持。

以MySQL爲例，需要在`build.sbt`文件中添加以下依賴：

```scala
libraryDependencies ++= Seq(
  "com.typesafe.slick" %% "slick" % "版本號", //Slick ORM框架
  "com.typesafe.slick" %% "slick-hikaricp" % "版本號" //Slick 數據庫連接池
  "mysql" % "mysql-connector-java" % "版本號" //JDBC 連接驅動包
)
```

默認配置下，`Slick`會使用連接池緩存數據庫連接，需要搭配插件`slick-hikaricp`。

## Play Framework 集成
對於在`Play Framework`中使用`Slick`，則推薦使用`play-slick`庫，該庫提供了`Play Framework`的`Slick`集成，添加`sbt`依賴：

```scala
"com.typesafe.play" %% "play-slick" % "版本號"
```

`play-slick`依賴於`slick`和`slick-hikaricp`，`SBT`依賴中添加了`play-slick`則無需再添加`slick`以及`slick-hikaricp`。

## 接口包路徑
Slick相關用戶接口在包路徑`slick.jdbc.數據庫類型.api`下(`Slick 3.2.0`版本之後)。
在`Slick 3.1.1`版本之前，相關接口位於包路徑`slick.driver.數據庫驅動.api`下。

常見的數據庫對應的包路徑：

| 數據庫名稱 | 包路徑 |
| :-: | :-: |
| MySQL | slick.jdbc.MySQLProfile.api |
| PostgresSQL | slick.jdbc.PostgresProfile.api |



# Model 定義
自定義模型類需要從`slick.jdbc.數據庫類型.api.Table[T]`類型中繼承。
泛型參數`T`具體可以是**元組**(`Tuple`)類型或是**樣例類**，內容爲表中包含的字段類型。
與Django不同，Slick**不使用**專門的類型來映射SQL字段類型，而是直接使用語言內置類型(Int、String等)映射SQL中的字段類型。

假設有以下結構的MySQL表：

```sql
CREATE TABLE `TestTable` (
	`Index` int(4) NOT NULL DEFAULT '0',
	`Name` varchar(48) NOT NULL DEFAULT '',
	PRIMARY KEY (`Index`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
```

在Slick中，該表對應的模型類可以寫成：

```scala
import slick.jdbc.MySQLProfile.api._
import slick.lifted.ProvenShape

// 元組參數類型爲表中字段的類型，參數中可以指定對應表在數據庫中的名稱
class TestTable(tag: Tag) extends Table[(Int, String)](tag, "TestTable") {

  // 列的類型爲Rep，使用cloumn方法生成，參數中可以指定列對象對應的SQL字段的名稱
  def index: Rep[Int] = cloumn[Int]("Index", O.PrimaryKey)
  def name: Rep[String] = column[String]("Name")

  // ProvenShape類型由隱式轉換得到，重寫無參*方法確定字段的排列順序
  def * : ProvenShape[(Int, String)] = (index, name)
}
```

對於簡單的表格直接使用**元組**表示代碼更爲簡潔，但若表格結構較爲複雜則應爲表格結構定義單獨的**樣例類**，上表採用樣例類可以改寫爲：

```scala
import slick.jdbc.MySQLProfile.api._

// 使用樣例類來表示表格的結構
case class TestModel(index: Int, name: String)

// 元組參數類型爲表中字段的類型，參數中可以指定對應表在數據庫中的名稱
class TestTable(tag: Tag) extends Table[TestModel](tag, "TestTable") {

  // 具體類型可以省略
  def index = cloumn[Int]("Index", O.PrimaryKey)
  def name = column[String]("Name")

  // 需要使用<>()方法將元組與樣例類綁定
  def * = (index, name) <> (TestModel.tupled, TestModel.unapply)
}
```

若映射的表名不確定，則可保留構造方法中的表名參數，在運行時傳入。
模型定義示例：

```scala
import slick.jdbc.MySQLProfile.api._
import slick.lifted.ProvenShape

// 保留表名參數，通過主構造方法傳入
class NoNameTable(tag: Tag, tableName: String) extends Table[(Int, String)](tag, tableName) {
	...
}
```

## 特殊類型映射
對於時間類型(`MySQL`中的`DateTime`類型)，`Slick`可以將其映射到`Java`中的以下類型：

- `java.sql.Date`
- `java.sql.Time`
- `java.sql.Timestamp`

對於二進制類型(`MySQL`中的`Blob`類型)，`Slick`可以將其映射到`Java`中的以下類型：

- `java.sql.Blob`
- `java.sql.Clob`
- `Array[Byte]`



# DataBase 實例
正確配置了Slick之後，需要獲取數據庫對象來進行具體的增刪改查操作。

Slick根據數據庫類型提供了不同的`Database`類型，格式如下：

```scala
slick.jdbc.數據庫類別.api.Database
```

以MySQL數據庫爲例，應使用`slick.jdbc.MySQLProfile.api.Database`類型。
`Database`對象在使用完畢後需要關閉以釋放資源。

## 使用 Database 類構建實例
使用`Database`伴生對象中的方法直接構建數據庫對象實例：

```scala
val db = Database.forDriver(
  new com.mysql.jdbc.Driver(),
  "jdbc:mysql://localhost:端口號/數據庫名稱",
  "MySQL用戶名",
  "MySQL密碼"
)

val db = Database.forURL(
  "jdbc:mysql://localhost:端口號/數據庫名稱",
  "MySQL用戶名",
  "MySQL密碼"
)
```

或者從項目配置文件`conf/application.conf`中讀取數據庫配置構建實例：

```scala
val db = Database.forConfig("配置名稱")
```

配置格式示例：

```scala
配置名稱 {
	driver = com.mysql.jdbc.Driver
	url = "jdbc:mysql://IP地址:端口號/數據庫名稱"
	user = "MySQL用戶名"
	password = "MySQL密碼"
	connectionPool = disabled
}
```

## 使用 Play Frameowrk 注入實例
對於在`Play Framework`框架中使用Slick，可以使用`play-sick`插件。

在項目配置文件`conf/application.conf`中添加數據庫的具體連接配置。
使用`play-sick`時，配置中需要使用特定前綴`slick.dbs.XXX`，`XXX`需要替換爲需要的配置名稱。
默認配置名稱爲`default`，配置結構示例：

```scala
slick.dbs.default { //"default"爲默認的配置名稱，可以自行修改
	driver = "slick.driver.MySQLDriver$" //Slick對應數據庫的驅動，注意"$"符號不能少
	db {
		driver = "com.mysql.jdbc.Driver" //JDBC驅動
		url = "jdbc:mysql://IP地址:端口號/數據庫名稱" //數據庫連接字符串
		user= "MySQL用戶名" //數據庫用戶名
		password = "MySQL密碼" //數據庫密碼
		connectionPool = disabled/enabled //是否使用連接池，使用連接池則需要slick-hikaricp插件支持
	}
}
```

配置文件語法靈活，上述配置也可以寫成：

```scala
slick.dbs.default.driver = "slick.driver.MySQLDriver$"
slick.dbs.default.db.driver = "com.mysql.jdbc.Driver"
slick.dbs.default.db.url = "jdbc:mysql://IP地址:端口號/數據庫名稱"
slick.dbs.default.db.user = "MySQL用戶名"
slick.dbs.default.db.password = "MySQL密碼"
```

使用`play.api.db.slick.DatabaseConfigProvider`獲取數據庫對象，定義示例：

```scala
trait DatabaseConfigProvider {
  def get[P <: BasicProfile]: DatabaseConfig[P]
}
```

使用`DatabaseConfigProvider`特質提供的無參`get`方法來獲取配置。
配置類型`DatabaseConfig`定義如下：

```scala
trait DatabaseConfig[P <: BasicProfile] {
  val driver: P
  def db: P#Backend#Database
  def config: Config
  def driverName: String
  def driverIsObject: Boolean
}
```

使用無參方法`db`即可獲得可供操作的數據庫對象。

在`Play Framework 2.4`及之前的版本，直接通過單例對象獲取：

```scala
val dbConfig = DatabaseConfigProvider.get[JdbcProfile](Play.current)
val db = dbConfig.db
```

在最新的`Play Framework 2.5`中，框架設計發生了變化，不再擁有全局的`Play.current`對象。
`DatabaseConfigProvider`需要通過`DI`(`Dependcy Inject`，即**依賴注入**)的方式來獲取。

一個注入了`DatabaseConfigProvider`的控制器示例：

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

默認情況下，使用配置文件`conf/application.conf`中`slick.dbs.default`配置項內寫入的配置。
若需要使用自定義名稱的配置，則需要使用`@NamedDatabase`註解，示例：

```scala
import play.api.db.NamedDatabase

@Singleton
class TestController @Inject()(@NamedDatabase("配置名稱") dbConfig: DatabaseConfigProvider) extends Controller {
  ...
}
```

其中，**配置名稱**填寫的**不是**完整路徑，如`slick.dbs.XXX`的配置名稱僅需填寫`XXX`即可。

`DatabaseConfigProvider`也可以通過`set`注入，示例：

```scala
import javax.inject.Inject

import slick.driver.JdbcProfile
import play.api.mvc._
import play.api.db.NamedDatabase
import play.api.db.slick.DatabaseConfigProvider

@Singleton
class TestController extends Controller {

  // 成員字段需要爲可變對象var才能注入，val字段不能注入
  @Inject
  @NamedDatabase("配置名稱")
  private var dbConfig: DatabaseConfigProvider = null

  def testPage = Action {
    val database = dbConfig.get[JdbcProfile].db
    ...
    Ok(...)
  }
}
```



# 查詢集操作
查詢集類型爲`slick.lifted.TableQurey[T]`，該類型提供各類數據操作方法。
泛型參數類型需要爲`slick.driver.數據庫驅動名稱.api.Table`的子類。

## 構建 TableQurey 實例
`TableQurey`類型的單例對象中提供了用於構建類型的`apply`方法，示例：

```scala
object TableQuery {

  /** Create a TableQuery for a table row class using an arbitrary constructor function. */
  def apply[E <: AbstractTable[_]](cons: Tag => E): TableQuery[E] = ...

  /** Create a TableQuery for a table row class which has a constructor of type (Tag). */
  def apply[E <: AbstractTable[_]]: TableQuery[E] = ...

}
```

對於映射表名已確定的`Table`子類，可使用無參`apply`方法直接構建實例。
以`TestTable`表爲例，直接使用`TableQurey[TestTable]`即可構建實例。
示例：

```scala
val query = TableQuery[TestTable]
...
```

對於構造方法傳入表名稱的`Table`子類，應使用接收高階類型參數的`apply(Tag => E)`方法。
以`NoNameTable`爲例，示例：

```scala
val query = TableQuery[NoNameTable](new NoNameTable(_, "數據庫中表的名稱"))
```

## 查詢
查詢操作類似於使用Scala集合庫中的**高階函數**，常見操作如下：

```scala
val query = TableQuery[TestTable]
query.filter(_.name === "abc") //篩選出符合條件的數據
query.drop(10) //丟棄前10條數據
query.take(5) //截取前5條數據
query.sortBy(_.index) //按index字段排序數據(增序)
query.sortBy(_.index.desc) //按index字段排序數據(減序)
```

高階函數內的數據表列實際類型均爲`slick.lifted.Rep[T]`。

在使用`filter()`方法篩選數據時，`Rep`類型重載了基本運算符，可直接使用`>`、`<`、`>=`、`<=`等運算符進行比較。
但在表示`==`、`!=`操作時，需要使用`===`、`=!=`操作符代替，原因是基類`Any`已經定義了`==`、`!=`操作符，不能通過隱式轉換調用。

## 插入
`TableQurey`類型重載了`+=`運算符，使用其插入新行：

```scala
val query = TableQuery[TestTable]
query += TestModel(666, "dainslef")
```

對於`PrimaryKey`或是`Unique`的列，不能插入重複的內容，否則會觸發`java.sql.SQLIntegrityConstraintViolationException`異常。
使用`TableQurey`類型的`insertOrUpdate()`在插入重複字段時更新該行內容而非產生異常。

```scala
val query = TableQuery[TestTable]
query.insertOrUpdate(TestModel(666, "SSR")) //若主鍵爲666的行已存在，則更新行的內容
```

## 修改
使用查詢操作篩選出目標數據集後使用`update()`方法更新行：

```scala
val query = TableQuery[TestTable]
query.filter(_.name === "dainslef") //篩選出name爲dainslef的行
  .map(_.name) //將篩選出的行中的name字段映射成新的查詢集
  .update("Dainslef") //更新篩選出的行中指定字段的內容
```

## 刪除
刪除操作與修改操作類似，使用查詢操作篩選出目標數據集之後使用`delete`方法刪除行：

```scala
val query = TableQuery[TestTable]
query.filter(_.name === "dainslef").delete //刪除所有name爲dainslef的行
```

## 應用查詢集操作
查詢集`TableQurey`類型執行的操作需要通過`Database`實例才能真正執行，示例：

```scala
val db = Database.forConfig("xxx")
val query = TableQuery[TestTable]

query... //執行各類查詢過濾操作

val action = query.result //獲取查詢操作，返回類型爲DriverAction[T]
val future = db.run(action)
```

`Database.run()`方法爲異步執行，調用方法時不會阻塞，返回類型爲`Future[Seq[XxxModel]]`。
若需要同步等待數據操作結束，可以使用`Await.result()`方法，該方法同時返回`Future`的執行結果：

```scala
val result = Await.result(future, Duration.Inf)
```

若查詢的內容不存在，`Future`內包含的查詢結果序列`Seq[XxxModel]`大小爲`0`(不是`null`)。

對於所有返回`DriverAction`類型的操作都需要使用`Database.run()`方法執行才能生效。
示例：

```scala
val db = Database.forConfig("xxx")
val query = TableQuery[TestTable]

query.delete //刪除、插入等操作返回類型皆爲DriverAction
query += TestModel(111, "XXXX") //未生效

val action = query.result
val future = db.run(action) //獲取的結果未改變
```

正確的做法是：

```scala
val db = Database.forConfig("xxx")
val query = TableQuery[TestTable]

db.run(query.delete)
db.run(query += TestModel(111, "XXXX")) //使用Database.run()方法使操作生效

val action = query.result
val future = db.run(action)
```

多個返回`DriverAction`的操作不必每次都調用`Database.run()`方法執行，可以將多個操作添加到`DBIO`序列中一併執行，示例：

```scala
val db = Database.forConfig("xxx")
val query = TableQuery[TestTable]

val actions = DBIO.seq(
  query.delete,
  query += TestModel(111, "XXXX")
)

db.run(actions) //執行多個操作
```
