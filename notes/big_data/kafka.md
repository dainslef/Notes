<!-- TOC -->

- [概述](#概述)
	- [下載](#下載)
	- [環境變量配置](#環境變量配置)
	- [主服務配置](#主服務配置)
	- [服務啟動](#服務啟動)
	- [消費數據](#消費數據)
	- [分區擴展](#分區擴展)
		- [分區數據均衡](#分區數據均衡)
- [Topic & Partition](#topic--partition)
	- [分區消息順序](#分區消息順序)
	- [分區存儲機制](#分區存儲機制)
	- [話題操作](#話題操作)
	- [話題刪除](#話題刪除)
- [Kafka Connect](#kafka-connect)
	- [依賴服務配置](#依賴服務配置)
	- [JDBC Source Connector](#jdbc-source-connector)
		- [单机多实例](#单机多实例)
		- [堆溢出問題](#堆溢出問題)
- [問題記錄](#問題記錄)
	- [org.apache.kafka.clients.NetworkClient: Connection to node -1 could not be established. Broker may not be available.](#orgapachekafkaclientsnetworkclient-connection-to-node--1-could-not-be-established-broker-may-not-be-available)
	- [org.apache.kafka.common.errors.TimeoutException: Expiring 1 record(s) for xxx-topic-0: 30056 ms has passed since batch creation plus linger time](#orgapachekafkacommonerrorstimeoutexception-expiring-1-records-for-xxx-topic-0-30056-ms-has-passed-since-batch-creation-plus-linger-time)
	- [org.apache.kafka.common.errors.TimeoutException: Failed to update metadata after 60000 ms](#orgapachekafkacommonerrorstimeoutexception-failed-to-update-metadata-after-60000-ms)
	- [Error shile writing to checkpoint file ... Caused by: java.io.FileNotFoundException: ... (Too many open files)](#error-shile-writing-to-checkpoint-file--caused-by-javaiofilenotfoundexception--too-many-open-files)

<!-- /TOC -->



# 概述
`Kafka`是高性能的分佈式消息隊列，在大數據領域有較廣泛的應用。

Kafka通常用於以下兩大類應用：

- 構建實時流式數據管道，在系統與應用間可靠地獲取數據。
- 構建實例流式應用，轉換或響應流式數據。

## 下載
Kafka主要版本包括：

- [原生版本Kafka](http://kafka.apache.org/downloads)，由`Apache`基金會維護。
- [Confluent Kafka](https://www.confluent.io/download)，
由前`LinkedIn`的Kafka核心開發者創立的商業公司`Confluent`維護，在原生Kafka的基礎上提供了一系列的擴展功能。

## 環境變量配置
配置環境變量，在`~/.profile`或`/etc/profile`中添加：

```sh
export KAFKA_HOME=... # 配置Kafka軟件包路徑
export PATH+=:$KAFKA_HOME/bin # 將Kafka相關工具加入PATH環境變量
```

## 主服務配置
單機版Kafka使用默認配置即可正常啓動。
集羣版本Kafka需要修改以下配置：

- `$KAFKA_HOME/etc/kafka/server.properties`

	Kafka服務的核心啓動配置項。
	做爲集羣啓動時需要指定以下配置：

	```conf
	broker.id = 服務編號（數值，集羣中每個Kafka服務需要使用不同的ID）
	# 示例：broker.id = 1

	zookeeper.connect = Zookeeper集羣的地址:端口
	# 示例：zookeeper.connect = spark-master:2181, spark-slave0:2181, spark-slave1:2181

	listeners = Kafka服務監聽協議://監聽地址:監聽端口
	# 設定Kafka主服務的監聽地址和端口號，默認端口爲9092
	# 示例：listeners = PLAINTEXT://spark-master:9092
	```

	對於使用KRaft機制的Kafka，不再需要ZooKeeper配置，需要修改進程角色和監聽地址：

	```conf
	# 進程角色，使用KRaft進程角色添加controller
	process.roles=broker,controller

	# 設置所有KRaft地址
	controller.quorum.voters=服務編號@集群地址:KRaft端口,...
	# 示例：controller.quorum.voters=1@192.168.1.1:9093,2@192.168.1.2:9093,3@192.168.1.3:9093

	# 設置監聽地址，使用KRaft默認監聽9093端口
	listeners=PLAINTEXT://:9092,CONTROLLER://:9093
	```

	客戶端若未配置Kafka主機名連接時可能產生錯誤，
	通過配置告知客戶端正確的連接地址：

	```conf
	# 告知客戶端監聽的地址與端口，若未配置則使用listeners的值
	advertised.listeners=PLAINTEXT://外部訪問地址:服務端口
	# 示例：advertised.listeners=PLAINTEXT://192.168.1.1:9092
	```

	消息大小上限相關配置：

	```conf
	message.max.bytes = 消息最大字節數
	# 默認值爲1000000，取值應小於Consumer端的 fetch.message.max.bytes 配置
	# 示例：message.max.bytes = 5000000

	replica.fetch.max.bytes = 可複製最大字節數
	# 取值應大於 message.max.bytes ，否則會造成接收到的消息複製失敗
	# 示例：replica.fetch.max.bytes = 5001000
	```

	話題相關配置：

	```sh
	# 允許刪除話題
	delete.topic.enable = true
	# 禁用話題自動創建
	auto.create.topics.enable = true
	```

	Kafka會緩存所有消息，無論消息是否被消費，可通過配置設定消息的緩存清理策略。
	消息存儲相關配置：

	```sh
	num.partitions = 分區數量
	# 決定默認配置下創建的話題擁有的分區數量，多個分區會分佈在集羣內不同的機器中
	# 默認值爲 1

	log.dirs = 消息存儲路徑
	# 默認路徑爲 /tmp/kafka-logs ，路徑可以爲多個，多個路徑之間使用逗號分隔
	# 示例： log.dirs = /home/data/kafka/kafka_messages

	log.cleanup.policy = 消息清理策略
	# 默認值爲 delete，可選值爲 compact(壓縮)、delete(刪除)

	log.retention.minutes = 消息保存分鐘
	log.retention.hours = 消息保存小時
	# 默認保存 168 小時(一週)的消息，超過時間的消息會按照配置的清理策略(壓縮、刪除)進行處理

	log.retention.bytes = 一個 topic 中每個 partition 保存消息的最大大小
	# 默認值爲 -1(不清理)，超過大小的消息會按照清理策略被處理
	# 消息緩存大小上限： partition數量 x 每個partition的消息大小上限
	```

	Kafka提供了基於**時間**、**存儲大小**兩個維度來設定消息日誌的清理策略。

- `$KAFKA_HOME/etc/kafka/consumer.properties`

	消費者配置。
	修改消費端消息大小：

	```sh
	max.partition.fetch.bytes = 服務器每個 partition 返回的最大數據大小
	# 在批量返回的時候，如果第一批次比這個值大，也會繼續返回後面的批次。
	# 此配置需要與 broker 的 message.max.bytes，producer 的 max.request.size 配合使用。
	# 示例： max.partition.fetch.bytes = 5000000

	fetch.message.max.bytes = 消費者一次獲取請求能取得的數據最大值
	# 數據被讀入到內存中，可用來控制消費者的內存使用，必須大於等於最大消息長度。
	# 示例： fetch.message.max.bytes = 5000000
	```

- `$KAFKA_HOME/etc/kafka/producer.properties`

	生產者配置。
	修改生產者端消息大小：

	```sh
	max.request.size = 發送消息的請求最大字節數
	# kakfa服務端使用此配置限制消息大小，部分client端也會通過這個參數限制消息大小。
	# 示例： max.request.size = 5000000
	```

## 服務啟動
Kafka相關CLI工具位於`$KAFKA_HOME/bin`路徑下。

主服務啓動、停止相關指令：

```c
// 啓動服務
$ kafka-server-start -daemon $KAFKA_HOME/etc/kafka/server.properties

// 停止服務
$ kafka-server-stop
```

配置Kafka集羣需要在集羣中每臺機器中執行服務啓動指令。

## 消費數據
命令行端數據生產/消費相關指令：

```c
// 消費數據
// 使用 --from-beginning 參數輸出該話題從創建開始後的消息
// 使用 --consumer.config 參數指定消費端使用的配置文件
// 使用 --offset [偏移量] --partion [分區編號] 參數自定義讀取消息時的偏移量
$ kafka-console-consumer --bootstrap-server [listeners IP:端口] --topic [話題名稱]

// 生產數據
// 使用 --producer.config 參數指定生產者端使用的配置文件
$ kafka-console-producer --broker-list [listeners IP:端口] --topic [話題名稱]
```

## 分區擴展
一個話題的分區數目可以動態增加，使用`--partitions`參數增加分區數目：

```
$ kafka-topics --zookeeper [zookeeper_ip:port] --alter --topic [topic_name] --partitions [partition_count]
```

分區擴展需要謹慎，因為Kafka僅支持話題的分區擴展，但不支持縮減分區，一旦分區增加了便無法撤消。

### 分區數據均衡
使用分區擴展指令後，分區數目會立即增加，但已存在的數目並未均衡到新的分區，
需要手動執行`kafka-reassign-partitions`工具來遷移已存在的數據，詳細使用說明參考[官方文檔](https://kafka.apache.org/documentation/#basic_ops_cluster_expansion)。

首先需要編寫JSON配置指定需要數據遷移的話題，格式如下：

```json
{
	"version": 1,
	"topics": [
		{ "topic": "topic_name_1" },
		{ "topic": "topic_name_2" },
		...
	]
}
```

輸入該配置，使用`--generate`參數生成話題的分區信息和默認的話題分區重分配信息，指令格式如下：

```c
$ kafka-reassign-partitions --zookeeper [zookeeper_ip:port] --generate --topics-to-move-json-file [topic_info.json] --broker-list [broker_id_1,broker_id_2,...]
```

執行執行指令：

```c
// 生成配置，計畫將話題的原數據遷移到 broker 5,6 上
$ kafka-reassign-partitions.sh --zookeeper localhost:2181 --topics-to-move-json-file topics-to-move.json --broker-list "5,6" --generate
Current partition replica assignment

{"version":1,
"partitions":[{"topic":"foo1","partition":2,"replicas":[1,2]},
              {"topic":"foo1","partition":0,"replicas":[3,4]},
              {"topic":"foo2","partition":2,"replicas":[1,2]},
              {"topic":"foo2","partition":0,"replicas":[3,4]},
              {"topic":"foo1","partition":1,"replicas":[2,3]},
              {"topic":"foo2","partition":1,"replicas":[2,3]}]
}

Proposed partition reassignment configuration

{"version":1,
"partitions":[{"topic":"foo1","partition":2,"replicas":[5,6]},
              {"topic":"foo1","partition":0,"replicas":[5,6]},
              {"topic":"foo2","partition":2,"replicas":[5,6]},
              {"topic":"foo2","partition":0,"replicas":[5,6]},
              {"topic":"foo1","partition":1,"replicas":[5,6]},
              {"topic":"foo2","partition":1,"replicas":[5,6]}]
}
```

工具自動生成了默認的新的分區分配信息，保存分區配置到文件中，修改不滿足需求的部分，確認合理後執行數據遷移：

```c
// 執行數據遷移操作
$ kafka-reassign-partitions --zookeeper localhost:2181 --reassignment-json-file expand-cluster-reassignment.json --execute
Current partition replica assignment

{"version":1,
"partitions":[{"topic":"foo1","partition":2,"replicas":[1,2]},
              {"topic":"foo1","partition":0,"replicas":[3,4]},
              {"topic":"foo2","partition":2,"replicas":[1,2]},
              {"topic":"foo2","partition":0,"replicas":[3,4]},
              {"topic":"foo1","partition":1,"replicas":[2,3]},
              {"topic":"foo2","partition":1,"replicas":[2,3]}]
}

Save this to use as the --reassignment-json-file option during rollback
Successfully started reassignment of partitions
{"version":1,
"partitions":[{"topic":"foo1","partition":2,"replicas":[5,6]},
              {"topic":"foo1","partition":0,"replicas":[5,6]},
              {"topic":"foo2","partition":2,"replicas":[5,6]},
              {"topic":"foo2","partition":0,"replicas":[5,6]},
              {"topic":"foo1","partition":1,"replicas":[5,6]},
              {"topic":"foo2","partition":1,"replicas":[5,6]}]
}
```

使用`--verify`參數可用於確認分區的遷移進度：

```c
// 注意，執行該指令時的分區配置需要與執行--execute指令時的分區配置相同
$ kafka-reassign-partitions --zookeeper localhost:2181 --reassignment-json-file expand-cluster-reassignment.json --verify
Status of partition reassignment:
Reassignment of partition [foo1,0] completed successfully
Reassignment of partition [foo1,1] is in progress
Reassignment of partition [foo1,2] is in progress
Reassignment of partition [foo2,0] completed successfully
Reassignment of partition [foo2,1] completed successfully
Reassignment of partition [foo2,2] completed successfully
```



# Topic & Partition
Kafka爲一連串的記錄提供了抽象：`Topic`（話題）。
Topic作爲記錄發佈時的類別/服務名稱，Topic在Kafka中總是`multi-subscriber`（多訂閱者）的，
一個Topic可以擁有任意數量的訂閱者（零個或多個），數據會推送給訂閱者。

一個Topic的數據由一個或多個`Partition`組成（可配置），多個Partition會優先分配在不同的物理節點中。
Producer向Topic寫入數據時，數據會記錄在不同的Partition中，避免單一節點承載過多的IO請求。

使用`kafka-topics --describe`指令查看某個話題的詳情，輸出內容如下：

```
Topic:spark-streaming-test      PartitionCount:2        ReplicationFactor:1     Configs:
        Topic: spark-streaming-test     Partition: 0    Leader: 2       Replicas: 2     Isr: 2
        Topic: spark-streaming-test     Partition: 1    Leader: 3       Replicas: 3     Isr: 3
```

- `PartitionCount` 話題分區數量
- `ReplicationFactor` 話題備份數量
- `Configs` 包含每個Partition的詳細配置信息
	- `Partition` 分區編號
	- `Leader` 負責讀寫該分區的broker編號
	- `Replicas` 分區備份的broker編號，ReplicationFactor大於1時會有多個broker編號
	- `Isr` 當前處於活躍狀態的broker編號，是Replicas中分區編號的子集

多個Consumer之間通過`Group`分組，一條發佈到話題中的數據會發往每一個Group，
但同一Group中只有**一個**Consumer實例會收到數據。
當一個Group中存在多個Consumer時，Topic內的不同Partition會關聯到不同的Consumer，
當一個Partition中寫入數據時，只有與該Partition關聯的Consumer會收到數據。

一個Partition在一個Group內僅會關聯一個Consumer，
因此當同一Group下的Consumer數目**大於**Partition數目時，
會有Consumer因爲未關聯到Partition而收不到數據。

## 分區消息順序
在Kafka中，每個分區使用獨立的偏移量，因此僅保證**同一分區**內的消息順序，而**不保證**全局消息順序。

若需要保證話題全局消息順序，則可使用如下機制：

- 使用單一消費者消費一個話題的所有分區
- 發送數據時手動指定消息分區，將需要保證數據的消息發送至同一分區

## 分區存儲機制
Kafka將消息數據存儲在`$KAFKA_HOME/etc/kafka/server.properties`文件中的`log.dirs`配置項設定的路徑下。
Kafka根據Topic和Partition在消息存儲路徑下以`[話題名稱]-[分區編號]`的命名規則創建子路徑，記錄每個話題的數據。
例如，Topic爲`test`，Partition爲`3`，則會生成以下子路徑：

```sh
# 存在多個 broker 時，分區路徑會優先分佈在不同的 broker 上
話題存儲根路徑
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
話題相關的操作指令：

```html
<!--
創建話題
使用 --partitions 參數指定話題的分區數量
使用 --replication-factor 參數指定話題數據備份數量
-->
$ kafka-topics --create --zookeeper Zookeeper集羣IP:端口 --topic 話題名稱

<!-- 列出話題 -->
$ kafka-topics --list --zookeeper [Zookeeper集羣IP:端口]

<!-- 移除話題，若移除話題失敗需要在Kafka服務端配置中添加設定 delete.topic.enble = true -->
$ kafka-topics --delete --topic 話題名稱 --zookeeper Zookeeper集羣IP:端口

<!--
查看話題描述(包括話題的 Partition、PartitionCount、ReplicationFactor 等信息)
不使用 --topic 參數時展示所有話題的信息
-->
$ kafka-topics --describe --topic 話題名稱 --zookeeper Zookeeper集羣IP:端口
```

使用的Zookeeper集羣IP可以是connect參數中配置的任意IP。
在Kafka中，已創建的話題配置可以動態修改：

```html
<!--
單獨設定話題的指定配置，常用配置：
log.retention.hours 話題消息保存時間
replication-factor 分區副本數目
partitions 分區數目
-->
$ kafka-topics --alter --config 鍵=值 --topic 話題名稱 --zookeeper zookeeper地址:端口
```

從`Kafka 0.9.x`開始，Kafka引入了獨立的配置管理工具`kafka-configs.sh`，
原有`kafka-topics.sh`中話題管理功能提示會在今後的版本中被廢棄。
kafka-configs使用示例：

```c
// 添加/更新配置
$ kafka-configs --alter --add-config [xxx.xxx.xxx=xxx] --zookeeper spark-master --entity-type topics  --entity-name [topic_name]

// 移除配置
$ kafka-configs --alter --delete-config [xxx.xxx.xxx] --zookeeper spark-master --entity-type topics  --entity-name [topic_name]
```

## 話題刪除
Kafka中刪除話題操作較為複雜，直接使用刪除指令不會生效，需要在`server.proerties`配置中設置參數允許話題刪除：

```sh
# 默認話題不允許刪除，需要在每個broker中設置允許話題被刪除
delete.topic.enable = true
```

之後再使用話題刪除指令：

```c
$ kafka-topics --delete --topics [話題名稱] --zookeeper [Zookeeper集羣IP:端口]
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
	// 刪除對應話題相關配置
	[zk...] rmr /config/topics/[話題名稱]
	// 刪除話題的delete標記信息
	[zk...] rmr /admin/delete_topics/[話題名稱]
	```



# Kafka Connect
`Kafka Connect`是一套在`Apache Kafka`和其它數據系統間進行可靠的、可擴展的流式數據傳輸的框架。
Kafka Connect使得向Kafka輸入、輸出數據變得簡單。

## 依賴服務配置
Kafka Connect使用前除了啓動Zookeeper和Kafka主進程外，還需要啓動以下服務：

- `Schema Registry` (必備)

	SchemaRegistry服務提供了對出入Kafka的消息的監控，並對數據進行序列化/反序列化處理。
	服務配置文件爲`$KAFKA_HOME/etc/schema-registry/schema-registry.properties`，配置說明：

	```sh
	listeners = http://服務地址:服務端口
	# 設置 Schema Registry 服務綁定的地址與服務端口，默認端口8081
	# 示例： listeners = http://spark-master:8081

	kafkastore.connection.url = Zookeeper集羣地址:端口
	# 示例： kafkastore.connection.url = spark-master:2181, spark-slave0:2181, spark-slave1:2181

	kafkastore.bootstrap.servers = Kafka服務監聽協議://監聽地址:監聽端口
	# 對應 $KAFKA_HOME/etc/kafka/server.properties 中設定的 listeners 配置
	# 示例： kafkastore.bootstrap.servers = PLAINTEXT://spark-master:9092

	kafkastore.topic = 話題名稱
	# Schema Registry 服務存儲內部信息使用的 topic，默認話題名稱爲 _schemas
	# 示例： kafkastore.topic = _schemas

	debug = 是否開啓調試模式
	# 示例： debug = false
	```

	啓動服務：

	```
	$ schema-registry-start -daemon $KAFKA_HOME/etc/schema-registry/schema-registry.properties
	```

- `Kafka Rest` (可選)

	KafkaRest服務爲Kafka提供了`Rest API`支持，使Kafka可以通過HTTP請求進行互操作。
	通常該服務不必修改配置，JDBC Source Connector會在啟動時自動啟動該服務，
	但若該服務的默認端口喔被佔用，則依舊需要修改相關配置。
	服務配置文件爲`$KAFKA_HOME/etc/kafka-rest/kafka-rest.properties`，配置說明：

	```sh
	id = 服務ID
	# 示例： id = kafka-rest-server

	listeners = http://服務地址:服務端口
	# 設置 Kafka Rest 服務綁定的地址與服務端口，默認端口爲8082
	# 示例： listeners = http://spark-master:8082

	schema.registry.url = SchemaRegistry服務地址:端口
	# 對應 $KAFKA_HOME/etc/schema-registry/schema-registry.properties 中設定的 listeners 配置
	# 示例： schema.registry.url = http://spark-master:8081

	zookeeper.connect = Zookeeper集羣地址:端口
	# 示例： zookeeper.connect = spark-master:2181, spark-slave0:2181, spark-slave1:2181

	bootstrap.servers = Kafka服務監聽協議://監聽地址:監聽端口
	# 對應 $KAFKA_HOME/etc/kafka/server.properties 中設定的 listeners 配置
	# 示例： bootstrap.servers = PLAINTEXT://spark-master:9092
	```

	啓動服務：

	```
	$ kafka-rest-start -daemon $KAFKA_HOME/etc/kafka-rest/kafka-rest.properties
	```

## JDBC Source Connector
`JDBC Source Connector`可以實現通過Kafka監控數據庫變化，通過Kafka導入、導出數據，
[官方文檔地址](https://docs.confluent.io/current/connect/kafka-connect-jdbc/source-connector/source_config_options.html)(最新版本)。

按下列步驟創建監控MySQL新增數據的服務:

1. 確保所連接數據庫的驅動存在。

	連接`MySQL`數據庫時，需要提供額外的`JDBC Driver`。
	從`https://www.mysql.com/downloads/`或`Maven`下載MySQL對應的JDBC驅動Jar包。
	將`mysql-connector-java-x.x.xx.jar`放置在`$KAFKA_HOME/share/java/kafka-connect-jdbc`路徑下。

1. 修改連接配置：

	連接配置文件爲`$KAFKA_HOME/etc/schema-registry/connect-avro-standalone.properties`。
	配置項說明：

	```sh
	bootstrap.servers = Kafka服務監監聽地址:監聽端口
	# 對應 $KAFKA_HOME/etc/kafka/server.properties 中設定的 listeners 配置，僅需要服務地址、端口
	# 示例： bootstrap.servers = spark-master:9092

	key.converter.schema.registry.url = SchemaRegistry服務地址:端口
	value.converter.schema.registry.url = SchemaRegistry服務地址:端口
	# 對應 $KAFKA_HOME/etc/schema-registry/schema-registry.properties 中設定的 listeners 配置
	# 示例： schema.registry.url = http://spark-master:8081

	rest.host.name = Kafka Rest 服務地址
	rest.port = Rest 监听端口
	# 示例：
	# rest.host.name = spark-master
	# rest.port = 8083
	```

1. 創建數據源配置。

	創建配置`$KAFKA_HOME/etc/kafka-connect-jdbc/test-mysql.properties`。
	配置項說明：

	```sh
	name = 連接名稱
	# 示例： name = kafka-connector-mysql

	connector.class = 連接驅動類
	# 示例： connector.class = io.confluent.connect.jdbc.JdbcSourceConnector

	connection.url = 數據庫連接的 JDBC URL
	# 示例： connection.url = jdbc:mysql://xxx.xxx.xxx.xxx:3306/Xxx?user=xxx&password=xxx

	topic.prefix = 生成話題的前綴
	# 示例： topic.prefix = mysql-

	mode = 模式
	# 設置 JDBC Connector 的工作模式，支持 incrementing(自增)、timestamp(時間戳)、bulk(直接導入) 等模式
	# 示例：
	# mode = incrementing
	# mode = timestamp
	# mode = bulk
	# mode = timestamp+incrementing

	timestamp.column.name = 監控的列名
	# 根據監控列的變化返回數據，僅在 timestamp/timestamp+incrementing 模式下有效
	# 示例： timestamp.column.name = id

	incrementing.column.name = 監控的列名
	# 根據監控列的變化返回數據，僅在 incrementing 模式下有效
	# incrementing.column.name = id

	table.whitelist = 需要監控的表格白名單
	# 默認配置下，JDBC Connector 會嘗試監控數據庫內所有表格，使用白名單配置需要監控的表格名稱
	# 示例： table.whitelist = testTable1, testTable2

	query = 查詢SQL語句
	# mode 配置項爲查詢模式時纔有效，用於自定義返回數據的查詢邏輯
	# 示例： query = select * from testTable1 order by id desc limit 1
	```

1. 啓動數據連接服務：

	使用`connect-standalone`工具創建數據連接服務，使用之前修改的連接配置和創建的數據源配置：

	```c
	$ connect-standalone -daemon $KAFKA_HOME/etc/schema-registry/connect-avro-standalone.properties $KAFKA_HOME/etc/kafka-connect-jdbc/test-mysql.properties
	```

	執行connect-standalone指令時，當前路徑需要為$KAFKA_HOME。

數據監控服務正常啓動後，會按照數據源配置項`topic.prefix`以`話題前綴 + 表格名稱`的規則自動創建話題，
在話題中以JSON形式輸出表格新增的數據。
話題中輸出的數據以`Apache Avro`做爲數據交互格式，直接使用`kafka-console-consumer`獲取話題中的數據得到的信息不具備可讀性。
應使用`kafka-avro-console-consumer`工具消費數據：

```
$ kafka-avro-console-consumer --bootstrap-server [listeners IP:端口] --from-beginning --topic [話題名稱] --property schema.registry.url=[http://SchemaRegistry服務地址:端口]
```

JDBC Source Connector提供了多種數據源導入/監控模式：

| 模式 | 功能 |
| :- | :- |
| bulk | 在輪詢時導入整張表的數據 |
| incrementing | 嚴格通過自增列來檢測新增行(僅檢測表格中的新增行，不會檢測已存在的行的修改與刪除) |
| timestamp | 通過時間戳來檢測新增與變化的行 |
| timestamp + incrementing | 使用時間戳檢測新增與修改的行，並通過自增列爲更新提供全局唯一ID，每行能被分配一個唯一的流偏移量 |

除了bulk模式外，JDBC Source Connector對於已導出數據的表格會記錄偏移量，重啓服務會後只會追加導入新增數據；
若需要重新導入完整數據則可嘗試**刪除話題**或切換**導入模式**。

### 单机多实例
一个JDBC Source Connector进程可监控多张表，并将数据发送到同一个话题中；
若需要发送数据到不同的话题中，则需要启动多个JDBC Source Connector实例。

新启动JDBC Source Connector实例不必再重复启动和配置依赖服务，如Schema Registry服务，
多个JDBC Source Connector实例可以复用相同的Schema Registry。

JDBC Source Connector进程启动时会读取`$KAFKA_HOME/etc/schema-registry/connect-avro-standalone.properties`中
的`rest.port`配置项来决定自身Rest服务监听的端口，新启动的JDBC Source Connector进程需要修改该配置，
否则会端口占用导致启动失败。

### 堆溢出問題
當需要監聽的目標表格過大時，使用默認JVM配置啟動的Connector可能會產生`OutOfMemoryError`，
出現內存溢出問題後，數據監控線程會退出，之後不再能正常監聽數據表的變化數據。

默認配置下，Connector進程僅分配256MB內存，可通過java指令的`-Xms/-Xmx`參數顯式指定進程分配的內存。
查看Confluent軟件包提供的connect-standalone工具，
調用的`kafka-run-class`工具腳本會嘗試讀取環境變量`KAFKA_HEAP_OPTS`中的值來設定額外的內存參數，
未設置該環境變量時，默認僅設置`256MB`的最大內存：

```sh
...
# Memory options
if [ -z "$KAFKA_HEAP_OPTS" ]; then
  KAFKA_HEAP_OPTS="-Xmx256M"
fi
...
```



# 問題記錄

## org.apache.kafka.clients.NetworkClient: Connection to node -1 could not be established. Broker may not be available.
Kafka配置中`listeners`不能使用IP地址，只能使用主機名稱。listeners設置為localhost時，則不能被外網訪問。
KafkaClient的連接配置中，broker的主機和端口需要與listeners中配置的相同。

## org.apache.kafka.common.errors.TimeoutException: Expiring 1 record(s) for xxx-topic-0: 30056 ms has passed since batch creation plus linger time
Kafka的`listeners`配置項中需要使用本機的主機名。

## org.apache.kafka.common.errors.TimeoutException: Failed to update metadata after 60000 ms
通常為連接問題，檢查服務端話題各分區狀態是否正常；檢查Host文件中是否正確配置了目標主機的IP映射。

## Error shile writing to checkpoint file ... Caused by: java.io.FileNotFoundException: ... (Too many open files)
Kafka服務長期工作會開啟大量的文件描述符，而多數Linux發行版中，默認的Linux文件描述符限制默認是`1024`。
在Linux系統下，通過設置`/etc/security/limits.conf`來允許進程同時打開更大數目的描述符。
