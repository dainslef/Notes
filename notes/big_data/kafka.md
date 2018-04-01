<!-- TOC -->

- [概述](#概述)
	- [下载](#下载)
	- [环境变量配置](#环境变量配置)
	- [主服务配置](#主服务配置)
	- [工具指令](#工具指令)
- [*Kafka Connect*](#kafka-connect)
	- [依赖服务配置](#依赖服务配置)
	- [*JDBC Source Connector*](#jdbc-source-connector)

<!-- /TOC -->



# 概述
`Kafka`是高性能的分布式消息队列，在大数据领域有较广泛的应用。

Kafka通常用于以下两大类应用：

- 构建实时流式数据管道，在系统与应用间可靠地获取数据。
- 构建实例流式应用，转换或响应流式数据。

## 下载
Kafka主要版本包括：

- [原生版本Kafka](http://kafka.apache.org/downloads)，由`Apache`基金会维护。
- [Confluent Kafka](https://www.confluent.io/download)，由前`LinkedIn`的Kafka核心开发者创立的商业公司`Confluent`维护，在原生Kafka的基础上提供了一系列的扩展功能。

## 环境变量配置
配置环境变量，在`~/.profile`或`/etc/profile`中添加：

```sh
export KAFKA_HOME=... # 配置Kafka软件包路径
export PATH+=:$KAFKA_HOME/bin # 将Kafka相关工具加入PATH环境变量
```

## 主服务配置
单机版Kafka使用默认配置即可正常启动。  
集群版本Kafka需要修改以下配置：

- `$KAFKA_HOME/etc/kafka/server.properties`

	Kafka服务的核心启动配置项。  
	做为集群启动时需要指定以下配置：

	```sh
	broker.id = 服务编号(数值，集群中每个Kafka服务需要使用不同的ID)
	# 示例： broker.id = 1

	zookeeper.connect = Zookeeper集群的地址:端口
	# 示例： zookeeper.connect = spark-master:2181, spark-slave0:2181, spark-slave1:2181

	listeners = Kafka服务监听协议://监听地址:监听端口
	# 设定Kafka主服务的监听地址和端口号，默认端口为9092
	# 示例： listeners = PLAINTEXT://spark-master:9092
	```

	消息大小相关配置：

	```sh
	message.max.bytes = 消息最大字节数
	# 默认值为1000000，取值应小于Consumer端的 fetch.message.max.bytes 配置
	# 示例： message.max.bytes = 5000000

	replica.fetch.max.bytes = 可复制最大字节数
	# 取值应大于 message.max.bytes ，否则会造成接收到的消息复制失败
	# 示例： replica.fetch.max.bytes = 5001000
	```

- `$KAFKA_HOME/etc/kafka/consumer.properties`

	消费者配置。  
	修改消费端消息大小：

	```sh
	max.partition.fetch.bytes = 服务器每个 partition 返回的最大数据大小
	# 在批量返回的时候，如果第一批次比这个值大，也会继续返回后面的批次。
	# 此配置需要与 broker 的 message.max.bytes，producer 的 max.request.size 配合使用。
	# 示例： max.partition.fetch.bytes = 5000000

	fetch.message.max.bytes = 消费者一次获取请求能取得的数据最大值
	# 数据被读入到内存中，可用来控制消费者的内存使用，必须大于等于最大消息长度。
	# 示例： fetch.message.max.bytes = 5000000
	```

- `$KAFKA_HOME/etc/kafka/producer.properties`

	生产者配置。  
	修改生产者端消息大小：

	```sh
	max.request.size = 发送消息的请求最大字节数
	# kakfa服务端使用此配置限制消息大小，部分client端也会通过这个参数限制消息大小。
	# 示例： max.request.size = 5000000
	```

## 工具指令
Kafka相关CLI工具位于`$KAFKA_HOME/bin`路径下。

主服务启动指令：

```c
// 启动服务
$ kafka-server-start -daemon [server.properties配置路径]

// 停止服务
$ kafka-server-stop
```

配置Kafka集群需要在集群中每台机器中执行服务启动指令。

话题操作指令：

```c
// 创建话题
$ kafka-topics --create --zookeeper [Zookeeper集群IP:端口] --replication-factor 1 --partitions 1 --topic [话题名称]

// 列出话题
$ kafka-topics --list --zookeeper [Zookeeper集群IP:端口]

// 移除话题，若移除话题失败需要在Kafka服务端配置中添加设定 delete.topic.enble = true
$ kafka-topics --delete --topic [话题名称] --zookeeper [Zookeeper集群IP:端口]
```

使用的Zookeeper集群IP可以是connect参数中配置的任意IP。

命令行端数据生产/消费相关指令：

```c
// 消费数据
// 使用 --from-beginning 参数输出该话题从创建开始后的消息
// 使用 --consumer.config 参数指定消费端使用的配置文件
$ kafka-console-consumer --bootstrap-server [listeners IP:端口] --topic [话题名称]

// 生产数据
// 使用 --producer.config 参数指定生产者端使用的配置文件
$ kafka-console-producer --broker-list [listeners IP:端口] --topic [话题名称]
```



# *Kafka Connect*
`Kafka Connect`是一套在`Apache Kafka`和其它数据系统间进行可靠的、可扩展的流式数据传输的框架。  
`Kafka Connect`使得向Kafka输入、输出数据变得简单。

## 依赖服务配置
`Kafka Connect`使用前除了启动`Zookeeper`和`Kafka`主进程外，还需要启动以下服务：

- `Schema Registry`

	SchemaRegistry服务提供了对出入Kafka的消息的监控，并对数据进行序列化/反序列化处理。  
	服务配置文件为`$KAFKA_HOME/etc/schema-registry/schema-registry.properties`，配置说明：

	```sh
	listeners = http://服务地址:服务端口
	# 设置 Schema Registry 服务绑定的地址与服务端口，默认端口8081
	# 示例： listeners = http://spark-master:8081

	kafkastore.connection.url = Zookeeper集群地址:端口
	# 示例： kafkastore.connection.url = spark-master:2181, spark-slave0:2181, spark-slave1:2181

	kafkastore.bootstrap.servers = Kafka服务监听协议://监听地址:监听端口
	# 对应 $KAFKA_HOME/etc/kafka/server.properties 中设定的 listeners 配置
	# 示例： kafkastore.bootstrap.servers = PLAINTEXT://spark-master:9092

	kafkastore.topic = 话题名称
	# Schema Registry 服务存储内部信息使用的 topic，默认话题名称为 _schemas
	# 示例： kafkastore.topic = _schemas

	debug = 是否开启调试模式
	# 示例： debug = false
	```

	启动服务：

	```
	$ schema-registry-start -daemon etc/schema-registry/schema-registry.properties
	```

- `Kafka Rest`

	KafkaRest服务为Kafka提供了`Rest API`支持，使Kafka可以通过HTTP请求进行互操作。  
	服务配置文件为`$KAFKA_HOME/etc/kafka-rest/kafka-rest.properties`，配置说明：

	```sh
	id = 服务ID
	# 示例： id = kafka-rest-server

	listeners = http://服务地址:服务端口
	# 设置 Kafka Rest 服务绑定的地址与服务端口，默认端口为8082
	# 示例： listeners = http://spark-master:8082
	
	schema.registry.url = SchemaRegistry服务地址:端口
	# 对应 $KAFKA_HOME/etc/schema-registry/schema-registry.properties 中设定的 listeners 配置
	# 示例： schema.registry.url = http://spark-master:8081
	
	zookeeper.connect = Zookeeper集群地址:端口
	# 示例： zookeeper.connect = spark-master:2181, spark-slave0:2181, spark-slave1:2181
	
	bootstrap.servers = Kafka服务监听协议://监听地址:监听端口
	# 对应 $KAFKA_HOME/etc/kafka/server.properties 中设定的 listeners 配置
	# 示例： bootstrap.servers = PLAINTEXT://spark-master:9092
	```

	启动服务：

	```
	$ kafka-rest-start -daemon etc/kafka-rest/kafka-rest.properties
	```

## *JDBC Source Connector*
`JDBC Source Connector`可以实现通过Kafka监控数据库变化，通过Kafka导入、导出数据，[官方文档地址](https://docs.confluent.io/current/connect/connect-jdbc/docs/source_connector.html)(最新版本)。

按下列步骤创建监控MySQL新增数据的服务:

1. 确保所连接数据库的驱动存在。

	连接`MySQL`数据库时，需要提供额外的`JDBC Driver`。  
	从`https://www.mysql.com/downloads/`或`Maven`下载MySQL对应的JDBC驱动Jar包。  
	将`mysql-connector-java-x.x.xx.jar`放置在`$KAFKA_HOME/share/java/kafka-connect-jdbc`路径下。

1. 修改连接配置：

	连接配置文件为`$KAFKA_HOME/etc/schema-registry/connect-avro-standalone.properties`。  
	配置项说明：

	```sh
	bootstrap.servers = Kafka服务监监听地址:监听端口
	# 对应 $KAFKA_HOME/etc/kafka/server.properties 中设定的 listeners 配置，仅需要服务地址、端口
	# 示例： bootstrap.servers = spark-master:9092

	kafkastore.connection.url = Zookeeper集群地址:端口
	# 示例： kafkastore.connection.url = spark-master:2181, spark-slave0:2181, spark-slave1:2181

	rest.host.name = Kafka Rest 服务地址
	# 示例：
	# rest.host.name = spark-master
	# rest.port = 8083
	```

1. 创建数据源配置。

	创建配置`$KAFKA_HOME/etc/kafka-connect-jdbc/test-mysql.properties`。  
	配置项说明：

	```sh
	name = 连接名称
	# 示例： name = kafka-connector-mysql

	connector.class = 连接驱动类
	# 示例： connector.class = io.confluent.connect.jdbc.JdbcSourceConnector

	connection.url = 数据库连接的 JDBC URL
	# 示例： connection.url = jdbc:mysql://xxx.xxx.xxx.xxx:3306/Xxx?user=xxx&password=xxx

	topic.prefix = 生成话题的前缀
	# 示例： topic.prefix = mysql-
	
	mode = 模式
	# 设置 JDBC Connector 的工作模式，
	# 示例：
	# mode = incrementing
	# mode = timestamp
	# mode = timestamp+incrementing

	timestamp.column.name = 监控的列名
	# 根据监控列的变化返回数据，仅在 timestamp/timestamp+incrementing 模式下有效
	# 示例： timestamp.column.name = id

	incrementing.column.name = 监控的列名
	# 根据监控列的变化返回数据，仅在 incrementing 模式下有效
	# incrementing.column.name = id
	
	table.whitelist = 需要监控的表格白名单
	# 默认配置下，JDBC Connector 会尝试监控数据库内所有表格，使用白名单配置需要监控的表格名称
	# 示例： table.whitelist = testTable1, testTable2

	query = 查询SQL语句
	# mode 配置项为查询模式时才有效，用于自定义返回数据的查询逻辑
	# 示例： query = select * from testTable1 order by id desc limit 1
	```
