- [概述](#概述)
	- [下载](#下载)
	- [环境变量配置](#环境变量配置)
	- [主服务配置](#主服务配置)
	- [工具指令](#工具指令)
- [Topic & Partition](#topic--partition)
	- [存储机制](#存储机制)
- [Kafka Connect](#kafka-connect)
	- [依赖服务配置](#依赖服务配置)
	- [JDBC Source Connector](#jdbc-source-connector)



# 概述
`Kafka`是高性能的分布式消息队列，在大数据领域有较广泛的应用。

Kafka通常用于以下两大类应用：

- 构建实时流式数据管道，在系统与应用间可靠地获取数据。
- 构建实例流式应用，转换或响应流式数据。

## 下载
Kafka主要版本包括：

- [原生版本Kafka](http://kafka.apache.org/downloads)，由`Apache`基金会维护。
- [Confluent Kafka](https://www.confluent.io/download)，
由前`LinkedIn`的Kafka核心开发者创立的商业公司`Confluent`维护，在原生Kafka的基础上提供了一系列的扩展功能。

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

	消息大小上限相关配置：

	```sh
	message.max.bytes = 消息最大字节数
	# 默认值为1000000，取值应小于Consumer端的 fetch.message.max.bytes 配置
	# 示例： message.max.bytes = 5000000

	replica.fetch.max.bytes = 可复制最大字节数
	# 取值应大于 message.max.bytes ，否则会造成接收到的消息复制失败
	# 示例： replica.fetch.max.bytes = 5001000
	```

	話題相關配置：

	```sh
	# 允許刪除話題
	delete.topic.enable = true
	# 禁用話題自動創建
	auto.create.topics.enable = true
	```

	Kafka会缓存所有消息，无论消息是否被消费，可通过配置设定消息的缓存清理策略。
	消息存储相关配置：

	```sh
	num.partitions = 分区数量
	# 决定默认配置下创建的话题拥有的分区数量，多个分区会分布在集群内不同的机器中
	# 默认值为 1

	log.dirs = 消息存储路径
	# 默认路径为 /tmp/kafka-logs ，路径可以为多个，多个路径之间使用逗号分隔
	# 示例： log.dirs = /home/data/kafka/kafka_messages

	log.cleanup.policy = 消息清理策略
	# 默认值为 delete，可选值为 compact(压缩)、delete(删除)

	log.retention.minutes = 消息保存分钟
	log.retention.hours = 消息保存小时
	# 默认保存 168 小时(一周)的消息，超过时间的消息会按照配置的清理策略(压缩、删除)进行处理

	log.retention.bytes = 一个 topic 中每个 partition 保存消息的最大大小
	# 默认值为 -1(不清理)，超过大小的消息会按照清理策略被处理
	# 消息缓存大小上限： partition数量 x 每个partition的消息大小上限
	```

	Kafka提供了基于**时间**、**存储大小**两个维度来设定消息日志的清理策略。

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

## 服務啟動
Kafka相关CLI工具位于`$KAFKA_HOME/bin`路径下。

主服务启动、停止相关指令：

```c
// 启动服务
$ kafka-server-start -daemon $KAFKA_HOME/etc/kafka/server.properties

// 停止服务
$ kafka-server-stop
```

配置Kafka集群需要在集群中每台机器中执行服务启动指令。

## 消費數據
命令行端数据生产/消费相关指令：

```c
// 消费数据
// 使用 --from-beginning 参数输出该话题从创建开始后的消息
// 使用 --consumer.config 参数指定消费端使用的配置文件
// 使用 --offset [偏移量] --partion [分区编号] 参数自定义读取消息时的偏移量
$ kafka-console-consumer --bootstrap-server [listeners IP:端口] --topic [话题名称]

// 生产数据
// 使用 --producer.config 参数指定生产者端使用的配置文件
$ kafka-console-producer --broker-list [listeners IP:端口] --topic [话题名称]
```



# Topic & Partition
Kafka为一连串的记录提供了抽象：`Topic`(话题)。
Topic作为记录发布时的类别/服务名称，Topic在Kafka中总是`multi-subscriber`(多订阅者)的，
一个Topic可以拥有任意数量的订阅者(零个或多个)，数据会推送给订阅者。

一个Topic的数据由一个或多个`Partition`组成(可配置)，多个Partition会优先分配在不同的物理节点中。
Producer向Topic写入数据时，数据会记录在不同的Partition中，避免单一节点承载过多的IO请求。

使用`kafka-topics --describe`指令查看某个话题的详情，输出内容如下：

```
Topic:spark-streaming-test      PartitionCount:2        ReplicationFactor:1     Configs:
        Topic: spark-streaming-test     Partition: 0    Leader: 2       Replicas: 2     Isr: 2
        Topic: spark-streaming-test     Partition: 1    Leader: 3       Replicas: 3     Isr: 3
```

- `PartitionCount` 话题分区数量
- `ReplicationFactor` 话题备份数量
- `Configs` 包含每个Partition的详细配置信息
	- `Partition` 分区编号
	- `Leader` 负责读写该分区的broker编号
	- `Replicas` 分区备份的broker编号，ReplicationFactor大于1时会有多个broker编号
	- `Isr` 当前处于活跃状态的broker编号，是Replicas中分区编号的子集

多个Consumer之间通过`Group`分组，一条发布到话题中的数据会发往每一个Group，
但同一Group中只有**一个**Consumer实例会收到数据。
当一个Group中存在多个Consumer时，Topic内的不同Partition会关联到不同的Consumer，当一个Partition中写入数据时，
只有与该Partition关联的Consumer会收到数据。

一个Partition在一个Group内仅会关联一个Consumer，因此当同一Group下的Consumer数目**大于**Partition数目时，
会有Consumer因为未关联到Partition而收不到数据。

## 存储机制
Kafka将消息数据存储在`$KAFKA_HOME/etc/kafka/server.properties`文件中的`log.dirs`配置项设定的路径下。
Kafka根据Topic和Partition在消息存储路径下以`[话题名称]-[分区编号]`的命名规则创建子路径，记录每个话题的数据。
例如，Topic为`test`，Partition为`3`，则会生成以下子路径：

```sh
# 存在多个 broker 时，分区路径会优先分布在不同的 broker 上
话题存储根路径
  ├── test-0
  ├── test-1
  ├── test-2
  ...
```

創建話題時，備份的數量**不能大於**broker的數量，否則會得到異常：

```
Error while executing topic command : Replication factor: 2 larger than available brokers: 1.
[2019-08-05 05:05:12,837] ERROR org.apache.kafka.common.errors.InvalidReplicationFactorException: Replication factor: 2 larger than available brokers: 1.
 (kafka.admin.TopicCommand$)
```

## 話題操作
话题相關的操作指令：

```c
// 创建话题
// 使用 --partitions 参数指定话题的分区数量
// 使用 --replication-factor 参数指定话题数据备份数量
$ kafka-topics --create --zookeeper [Zookeeper集群IP:端口] --topic [话题名称]

// 列出话题
$ kafka-topics --list --zookeeper [Zookeeper集群IP:端口]

// 移除话题，若移除话题失败需要在Kafka服务端配置中添加设定 delete.topic.enble = true
$ kafka-topics --delete --topic [话题名称] --zookeeper [Zookeeper集群IP:端口]

// 查看话题描述(包括话题的 Partition、PartitionCount、ReplicationFactor 等信息)
// 不使用 --topic 参数时展示所有话题的信息
$ kafka-topics --describe --topic [话题名称] --zookeeper [Zookeeper集群IP:端口]
```

使用的Zookeeper集群IP可以是connect参数中配置的任意IP。
在Kafka中，已创建的话题配置可以动态修改：

```c
// 单独设定话题的某个配置
$ kafka-topics --alter --config [话题配置xxx=xxx] --topic [话题名称] --zookeeper [Zookeeper集群IP:端口]
```

## 話題刪除
Kafka中刪除話題操作較為複雜，直接使用刪除指令不會生效，需要在`server.proerties`配置中設置參數允許話題刪除：

```sh
# 默認話題不允許刪除，需要在每個broker中設置允許話題被刪除
delete.topic.enable = true
```

之後再使用話題刪除指令：

```c
$ kafka-topics --delete --topics [話題名稱] --zookeeper [Zookeeper集群IP:端口]
```

若未啟用`delete.topic.enable`參數，則執行刪除指令不會真正刪除話題，僅為話題打上刪除標記。
手動完整刪除話題還需要執行以下步驟：

- 刪除話題數據目錄：

	```c
	// 刪除話題對應的所有分區目錄
	$ rm -rf $KAFKA_LOGS/[話題名稱]*
	```

- 刪除ZooKeeper中對應話題的相關記錄：

	```c
	// 進入ZooKeeper命令行環境
	$ zkCli.sh

	// 刪除對應話題相關信息
	[zk...] rmr /brokers/topics/[話題名稱]
	// 刪除話題的delete標記信息
	[zk...] rmr /admin/delete_topics/[話題名稱]
	```



# Kafka Connect
`Kafka Connect`是一套在`Apache Kafka`和其它数据系统间进行可靠的、可扩展的流式数据传输的框架。
Kafka Connect使得向Kafka输入、输出数据变得简单。

## 依赖服务配置
Kafka Connect使用前除了启动Zookeeper和Kafka主进程外，还需要启动以下服务：

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
	$ schema-registry-start -daemon $KAFKA_HOME/etc/schema-registry/schema-registry.properties
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
	$ kafka-rest-start -daemon $KAFKA_HOME/etc/kafka-rest/kafka-rest.properties
	```

## JDBC Source Connector
`JDBC Source Connector`可以实现通过Kafka监控数据库变化，通过Kafka导入、导出数据，
[官方文档地址](https://docs.confluent.io/current/connect/kafka-connect-jdbc/source-connector/source_config_options.html)(最新版本)。

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
	# 设置 JDBC Connector 的工作模式，支持 incrementing(自增)、timestamp(时间戳)、bulk(直接导入) 等模式
	# 示例：
	# mode = incrementing
	# mode = timestamp
	# mode = bulk
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

1. 启动数据连接服务：

	使用`connect-standalone`工具创建数据连接服务，使用之前修改的连接配置和创建的数据源配置：

	```c
	$ connect-standalone -daemon $KAFKA_HOME/etc/schema-registry/connect-avro-standalone.properties $KAFKA_HOME/etc/kafka-connect-jdbc/test-mysql.properties
	```

	執行connect-standalone指令時，當前路徑需要為$KAFKA_HOME。

数据监控服务正常启动后，会按照数据源配置项`topic.prefix`以`话题前缀 + 表格名称`的规则创建话题，
在话题中以JSON形式输出表格新增的数据。
话题中输出的数据以`Apache Avro`做为数据交互格式，直接使用`kafka-console-consumer`获取话题中的数据得到的信息不具备可读性。
应使用`kafka-avro-console-consumer`工具消费数据：

```
$ kafka-avro-console-consumer --bootstrap-server [listeners IP:端口] --from-beginning --topic [话题名称] --property schema.registry.url=[http://SchemaRegistry服务地址:端口]
```

JDBC Source Connector提供了多种数据源导入/监控模式：

| 模式 | 功能 |
| :- | :- |
| bulk | 在轮询时导入整张表的数据 |
| incrementing | 严格通过自增列来检测新增行(仅检测表格中的新增行，不会检测已存在的行的修改与删除) |
| timestamp | 通过时间戳来检测新增与变化的行 |
| timestamp + incrementing | 使用时间戳检测新增与修改的行，并通过自增列为更新提供全局唯一ID，每行能被分配一个唯一的流偏移量 |
