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

`Play Framework`支持多种ORM框架，推荐使用`Slick`，`Slick`时`LightBend`官方开发的函数式风格的ORM框架，官方介绍中称之为`Functional Relational Mapping (FRM)`。
除了`Slcik`，`Play Framework`还支持`Anorm`、`EBean`等ORM框架。

### 配置 *Slick*
`Slick`搭配不同数据库时需要对应的数据库驱动支持。

以`MySQL`为例，需要在`build.sbt`文件中添加以下依赖：

```scala
libraryDependencies ++= Seq(
	"com.typesafe.slick" %% "slick" % "[版本号]",		//Slick ORM框架
	"mysql" % "mysql-connector-java" % "[版本号]"		//JDBC 连接驱动包
)
```

添加框架依赖之后，需要在项目配置文件`application.conf`中添加数据库的具体连接配置：

```scala
slick.dbs.default {											//default为默认的配置名称，可以自行修改
	driver = "slick.driver.MySQLDriver"						//Slick对应数据库的驱动
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

### 定义对象模型
