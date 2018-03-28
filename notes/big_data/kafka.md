<!-- TOC -->

- [概述](#概述)
	- [下载](#下载)
	- [基础配置](#基础配置)

<!-- /TOC -->



## 概述
`Kafka`是高性能的分布式消息队列，在大数据领域有较广泛的应用。

### 下载
在`http://kafka.apache.org/downloads`下载`Kafka`。  
或者在`https://www.confluent.io/download`下载`Confluent Kafka`。

### 基础配置
首先配置环境变量，在`~/.profile`或`/etc/profile`中添加：

```sh
export KAFKA_HOME=... # 配置Kafka软件包路径
export PATH+=:$KAFKA_HOME/bin # 将Kafka相关工具加入PATH环境变量
```

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
