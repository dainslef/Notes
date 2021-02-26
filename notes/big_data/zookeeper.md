<!-- TOC -->

- [概述](#概述)
	- [服務配置](#服務配置)
	- [環境變量](#環境變量)
- [问题注记](#问题注记)
	- [Will not attempt to authenticate using SASL (unknown error)](#will-not-attempt-to-authenticate-using-sasl-unknown-error)

<!-- /TOC -->



# 概述
`ZooKeeper`是用於管理配置信息、命名、提供分佈式同步、組等功能的集中式服務。
所有此類服務功能可用於其它分佈式應用，通常實現此類功能需要很大工作量並且不可避免的需要修復BUG。
由於此類服務的複雜性，開發者在開發初期通常並未重視該問題，進而使得應用在後續更改中變得脆弱和難以管理。
即使開發者正確處理問題，不同服務的實現會導致應用部署時難以管理。

ZooKeeper相關文檔包括[官方文檔](https://zookeeper.apache.org/doc/current/)，
以及[ZooKeeper Wiki](https://cwiki.apache.org/confluence/display/ZOOKEEPER/Index)。

## 服務配置
創建ZooKeeper配置文件`$ZOOKEEPER_HOME/conf/zoo.cfg`，添加各個節點的信息：

```
server.1=hostname1:2888:3888
server.2=hostname2:2888:3888
...
```

可將`$ZOOKEEPER_HOME/bin`路徑加入PATH，以便於直接使用ZooKeeper的命令行工具。
常用的ZooKeeper命令行工具：

- `zkServer.sh` 用於查看服務狀態，啟動和停止服務

	```html
	# zkServer.sh start <!-- 啟動服務 -->
	ZooKeeper JMX enabled by default
	Using config: /root/software/zookeeper-3.4.11/conf/zoo.cfg
	Starting zookeeper ... STARTED

	# zkServer.sh status <!-- 查看服務狀態 -->
	ZooKeeper JMX enabled by default
	Using config: /root/software/zookeeper-3.4.11/conf/zoo.cfg
	Mode: standalone

	# zkServer.sh stop <!-- 終止服務 -->
	ZooKeeper JMX enabled by default
	Using config: /root/software/zookeeper-3.4.11/conf/zoo.cfg
	Stopping zookeeper ... STOPPED
	```

- `zkCli.sh` 用於進入ZooKeeper Shell

	```html
	# zkCli.sh <!-- 進入 ZooKeeper Shell -->
	Connecting to localhost:2181
	...
	Welcome to ZooKeeper!
	JLine support is enabled
	...
	[zk: localhost:2181(CONNECTED) 1] <!-- 使用 Tab 列出可用指令 -->

	stat           set            ls             delquota       ls2            setAcl         setquota       history
	redo           printwatches   delete         sync           listquota      rmr            get            create
	addauth        quit           getAcl         close          connect
	[zk: localhost:2181(CONNECTED) 0] ls / <!-- 查看跟路徑下的節點 -->
	[cluster, controller_epoch, brokers, zookeeper, admin, isr_change_notification, consumers, log_dir_event_notification, latest_producer_id_block, config]
	[zk: localhost:2181(CONNECTED) 1] get /zookeeper/quota <!-- 查看指定節點下的信息 -->

	cZxid = 0x0
	ctime = Thu Jan 01 08:00:00 CST 1970
	mZxid = 0x0
	mtime = Thu Jan 01 08:00:00 CST 1970
	pZxid = 0x0
	cversion = 0
	dataVersion = 0
	aclVersion = 0
	ephemeralOwner = 0x0
	dataLength = 0
	numChildren = 0
	```

## 環境變量
腳本`$ZOOKEEPER_HOME/bin/zkEnv.sh`中定義了影響ZooKeeper配置的環境變量。

- `ZOO_LOG_DIR` 影響啟動服務時的產生的日誌文件`zookeeper.out`的路徑
- `ZOOCFG` 設置ZooKeeper的配置文件的路徑



# 问题注记
记录Zookeeper使用过程中遇到的错误信息以及对应解决方法。

## Will not attempt to authenticate using SASL (unknown error)
错误说明：<br>
Zookeeper日志中反复提示Socket被关闭，且SASL鉴权失败。
错误信息如下：

```
2018-06-25 00:20:02,755 [myid:] - INFO  [main-SendThread(localhost:2181):ClientCnxn$SendThread@1161] - Unable to read additional data from server sessionid 0x0, likely server has closed socket, closing socket connection and attempting reconnect
2018-06-25 00:20:03,065 [myid:] - INFO  [main-SendThread(localhost:2181):ClientCnxn$SendThread@1035] - Opening socket connection to server localhost/127.0.0.1:2181. Will not attempt to authenticate using SASL (unknown error)
2018-06-25 00:20:03,066 [myid:] - INFO  [main-SendThread(localhost:2181):ClientCnxn$SendThread@877] - Socket connection established to localhost/127.0.0.1:2181, initiating session
```

解决方案：<br>
查看防火墙服务是否开启，关闭防火墙服务：

```
# systemctl status firewalld.service
# systemctl stop firewalld.service
```

执行`hostname`指令，查看`/etc/hosts`文件，当主机名称不为`localhost`且在host文件中配置了主机IP映射时，
在Zookeeper配置文件中设置`server.xxx`配置项时，使用主机名代替IP。

如：

```
server.1=172.16.0.126:2888:3888
server.2=172.16.0.127:2888:3888
server.3=172.16.0.128:2888:3888
```

改为：

```
server.1=spark-master:2888:3888
server.2=spark-slave0:2888:3888
server.3=spark-slave1:2888:3888
```
