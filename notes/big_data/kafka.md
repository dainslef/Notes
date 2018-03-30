<!-- TOC -->

- [概述](#概述)
	- [下载](#下载)
	- [环境变量配置](#环境变量配置)
	- [主服务配置](#主服务配置)
	- [工具指令](#工具指令)

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
