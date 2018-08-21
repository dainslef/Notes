- [概述](#概述)
	- [下载](#下载)
	- [环境变量配置](#环境变量配置)
	- [集群规划](#集群规划)
	- [路径规划](#路径规划)
	- [服务配置](#服务配置)
- [HDFS](#hdfs)
	- [访问地址](#访问地址)
	- [命令行工具](#命令行工具)
- [Hbase](#hbase)
	- [服务配置](#服务配置-1)
	- [数据模型](#数据模型)
		- [Conceptual View (概念视图)](#conceptual-view-概念视图)
		- [Physical View (物理视图)](#physical-view-物理视图)
		- [Namespace (命名空间)](#namespace-命名空间)
	- [HBase Shell](#hbase-shell)
	- [HBase Client API](#hbase-client-api)
- [问题注记](#问题注记)
	- [ERROR org.apache.hadoop.hdfs.server.namenode.NameNode: Failed to start namenode.org.apache.hadoop.hdfs.server.namenode.EditLogInputException: Error replaying edit log at offset 0. Expected transaction ID was 1](#error-orgapachehadoophdfsservernamenodenamenode-failed-to-start-namenodeorgapachehadoophdfsservernamenodeeditloginputexception-error-replaying-edit-log-at-offset-0-expected-transaction-id-was-1)
	- [Call From xxx to xxx failed on connection exception: java.net.ConnectException: Connection refused;](#call-from-xxx-to-xxx-failed-on-connection-exception-javanetconnectexception-connection-refused)
	- [java.io.IOException: Got error, status message , ack with firstBadLink as xxx.xxx.xxx.xxx:xxx](#javaioioexception-got-error-status-message--ack-with-firstbadlink-as-xxxxxxxxxxxxxxx)
	- [全部HA节点处于 stand by 状态](#全部ha节点处于-stand-by-状态)
	- [org.apache.hadoop.hbase.client.RetriesExhaustedException](#orgapachehadoophbaseclientretriesexhaustedexception)
	- [XXX: Error: JAVA_HOME is not set and could not be found.](#xxx-error-java_home-is-not-set-and-could-not-be-found)
	- [Caused by: java.lang.ClassNotFoundException: com.yammer.metrics.core.Gauge](#caused-by-javalangclassnotfoundexception-comyammermetricscoregauge)
	- [java.io.IOException: Incompatible clusterIDs in /tmp/hadoop-root/dfs/data: namenode clusterID = CID-...; datanode clusterID = CID-...](#javaioioexception-incompatible-clusterids-in-tmphadoop-rootdfsdata-namenode-clusterid--cid--datanode-clusterid--cid-)
	- [WARN org.apache.hadoop.hdfs.server.datanode.DataNode: IOException in offerService; java.io.EOFException: End of File Exception between local host is: "xxxs/xx.xx.xx.xx"; destination host is: "xxhostname":xxxx;](#warn-orgapachehadoophdfsserverdatanodedatanode-ioexception-in-offerservice-javaioeofexception-end-of-file-exception-between-local-host-is-xxxsxxxxxxxx-destination-host-is-xxhostnamexxxx)



# 概述
`Apache Hadoop`是一套面向**可靠性**、**可扩展性**、**分布式计算**的开源套件。

Hadoop是一套框架，允许使用简单的编程模型在计算机集群中对大型数据集进行分布式处理。
Hadoop被设计成从单个服务器扩展到数千台机器，每台机器都提供本地计算和存储。
Hadoop不依靠硬件来提供高可用性，而是被设计成在应用层检测和处理故障，因此能够在一组计算机集群上提供高可用性服务，即便每一台计算机都可能出现故障。

`Apache Hadoop`项目包含以下模块：

- `Hadoop Common` 支持其它Hadoop模块的公用库
- `Hadoop Distributed File System (HDFS™)` 提供支持高数据访问量的分布式文件系统
- `Hadoop YARN` 作业调度与集群资源管理的框架
- `Hadoop MapReduce` 基于YARN的并行数据计算引擎

Apache基金会中还包含大量的Hadoop关联项目，如：

- `Ambari™` 基于Web的Hadoop集群管理、监控工具
- `Avro™:` 数据序列化系统
- `HBase™` 支持大型表格结构化数据存储的可扩展分布式数据库
- `Hive™` 提供数据汇总和随机查询的数据仓库基础设施
- `Spark™` 用于Hadoop数据的快速和通用计算引擎，用于取代MapReduce
- `ZooKeeper™` 高性能的分布式应用程序协调服务

## 下载
在[Hadoop官网](http://hadoop.apache.org/releases.html)下载Hadoop软件包。

截止到`2018-3-30`，Hadoop主要分为`2.x`和`3.x`两大版本，`3.x`版本在配置上与`2.x`版本有较大差异。
`3.x`版本正式发布时间较晚(2017-12-13)、迭代周期较短，稳定性有待考证，本文配置使用`2.7.5`版本。

## 环境变量配置
配置环境变量，在`~/.profile`或`/etc/profile`中添加：

```sh
export HADOOP_HOME=... # 配置Hadoop软件包路径
PATH+=:$HADOOP_HOME/bin
PATH+=:$HADOOP_HOME/sbin # 将Hadoop相关工具加入PATH环境变量
```

## 集群规划
使用5台机器构建Hadoop集群，IP与主机映射关系写入`/etc/hosts`文件中：

```
172.16.0.126 spark-master
172.16.0.127 spark-slave0
172.16.0.128 spark-slave1
172.16.0.129 spark-slave2
172.16.0.130 spark-slave3
```

为集群中的每台机器配置SSH免密登陆，保证任意两台机器之间能够免密登陆。

每个节点执行的服务规划如下：

| 主机名称 | 执行服务 |
|:-|:-|
| spark-master | namenode, journalnode, zkfc, kafka |
| spark-slave0 | namenode, journalnode, zkfc, kafka, datanode，nodemanager |
| spark-slave1 | journalnode, zkfc, kafka, datanode，nodemanager |
| spark-slave2 | secondarynamenode, resourcemanager, datanode，nodemanager |
| spark-slave3 | resourcemanager, datanode，nodemanager |

- `spark-master/spark-slave0`两台机器配置NameNode，实现HA。
- `spark-slave0 ~ spark-slave3`作为DataNode。
- `spark-master/spark-slave0/spark-slave1`三台机器启动Zookeeper，并作为JournalNode，同时运行Kafka。

## 路径规划
Hadoop提供的HDFS等组件需要占用大量的磁盘空间，需要对磁盘分区做出合理规划。
以`/home/data/hadoop`路径为例，执行指令，在路径下创建以下子路径：

```c
// 创建缓存路径
# mkdir -p /home/data/hadoop/tmp

// 创建 DataNode 数据存储路径
# mkdir -p /home/data/hadoop/hdfs/data

// 创建 NameNode 数据存储路径
# mkdir -p /home/data/hadoop/hdfs/name

// 创建 JournalNode 数据存储路径
# mkdir -p /home/data/hadoop/hdfs/journal
```

## 服务配置
Hadoop服务配置项多而繁杂，根据Hadoop版本选择匹配的[官方文档](http://hadoop.apache.org/docs)进行查阅。
集群配置相关文档地址为`http://hadoop.apache.org/docs/{Hadoop版本}/hadoop-project-dist/hadoop-common/ClusterSetup.html`。

Hadoop配置文件位于`$HADOOP_HOME/etc/hadoop`路径下，需要修改的配置文件如下：

- `core-site.xml`

	Hadoop的核心配置项。<br>
	配置项说明：

	```xml
	<configuration>

		<!--
			指定 HDFS 的 nameservice 为 lj-nameservice
			亦可直接使用 NameNode 的RPC通信地址，如 hdfs://spark-master:9000
		-->
		<property>
			<name>fs.defaultFS</name>
			<value>hdfs://lj-nameservice</value>
		</property>

		<!--
			指定 Hadoop 临时文件目录
			默认临时文件会生成在 /tmp/hadoop-[用户名] 路径下，机器重启后临时文件会被清空
		-->
		<property>
			<name>hadoop.tmp.dir</name>
			<value>/home/data/hadoop/tmp</value>
		</property>

		<!-- 指定 Zookeeper 集群访问地址 -->
		<property>
			<name>ha.zookeeper.quorum</name>
			<value>spark-master:2181,spark-slave0:2181,spark-slave1:2181</value>
		</property>

		<!-- 配置隔离机制方法，多个机制用换行分割，即每个机制暂用一行-->
		<property>
			<name>dfs.ha.fencing.methods</name>
			<value>
				sshfence
				shell(/bin/true)
			</value>
		</property>

		<!-- 使用 sshfence 隔离机制时需要 ssh 免登陆 -->
		<property>
			<name>dfs.ha.fencing.ssh.private-key-files</name>
			<value>/root/.ssh/id_rsa</value>
		</property>

		<!-- 配置 sshfence 隔离机制超时时间 -->
		<property>
			<name>dfs.ha.fencing.ssh.connect-timeout</name>
			<value>30000</value>
		</property>

	</configuration>
	```

- `hdfs-site.xml`

	包含对NameNode和DataNode的配置项。<br>
	配置项说明：

	```xml
	<configuration>

		<!-- 指定副本数 -->
		<property>
			<name>dfs.replication</name>
			<value>2</value>
		</property>

		<!-- 指定 NameService，需要和 core-site.xml 中 fs.defaultFS 配置项保持一致 -->
		<property>
			<name>dfs.nameservices</name>
			<value>lj-nameservice</value>
		</property>

		<!-- 设置 NameService 下的 NameNode 名称 -->
		<property>
			<name>dfs.ha.namenodes.lj-nameservice</name>
			<value>namenode1,namenode2</value>
		</property>

		<!-- namenode1 的 RPC 通信地址 -->
		<property>
			<name>dfs.namenode.rpc-address.lj-nameservice.namenode1</name>
			<value>spark-master:9000</value>
		</property>

		<!-- namenode1 的 HTTP 通信地址 -->
		<property>
			<name>dfs.namenode.http-address.lj-nameservice.namenode1</name>
			<value>spark-master:50070</value>
		</property>

		<!-- namenode2 的 RPC 通信地址 -->
		<property>
			<name>dfs.namenode.rpc-address.lj-nameservice.namenode2</name>
			<value>spark-slave0:9000</value>
		</property>

		<!-- namenode2 的 HTTP 通信地址 -->
		<property>
			<name>dfs.namenode.http-address.lj-nameservice.namenode2</name>
			<value>spark-slave0:50070</value>
		</property>

		<!-- 指定 NameNode 在本地磁盘存放数据的位置(可选) -->
		<property>
			<name>dfs.namenode.name.dir</name>
			<value>/home/data/hadoop/hdfs/name</value>
		</property>

		<!-- 指定 DataNode 在本地磁盘存放数据的位置(可选) -->
		<property>
			<name>dfs.namenode.data.dir</name>
			<value>/home/data/hadoop/hdfs/data</value>
		</property>

		<!-- 指定 JournalNode 在本地磁盘存放数据的位置(可选) -->
		<property>
			<name>dfs.journalnode.edits.dir</name>
			<value>/home/data/hadoop/hdfs/journal</value>
		</property>

		<!-- 开启 NameNode 失败自动切换(HA，单NameNode时此配置无效) -->
		<property>
			<name>dfs.ha.automatic-failover.enabled</name>
			<value>true</value>
		</property>

		<!--
			指定HA集群中多个NameNode之间的共享存储路径(单NameNode时此配置无效)
			指定URL对应的机器上会启动 JournalNode 服务
			设定该配置需要启用HA(dfs.ha.automatic-failover.enabled设置为true)
			JournalNode至少需要配置3个，数量需要为奇数
			JournalNode配置不正确会造成NameNode启动失败
		-->
		<property>
			<name>dfs.namenode.shared.edits.dir</name>
			<value>qjournal://spark-master:8485;spark-slave0:8485;spark-slave1:8485/lj-nameservice</value>
		</property>

	</configuration>
	```

首次启动NameNode节点前，需要格式化NameNode对应的数据目录，执行指令：

```
$ hadoop namenode -format
```

启动/关闭Hadoop相关服务：

```c
// 启动 NameNode、DataNode、JournalNode 服务
$ start-dfs.sh
// 启动 NodeManager、ResourceManager 服务
$ start-yarn.sh

// 停止服务
$ stop-dfs.sh && stop-yarn.sh
```

服务启动日志记录在`$HADOOP_HOME/logs`路径下，主要服务的日志路径：

```c
// NameNode
$HADOOP_HOME/logs/hadoop-[用户名]-namenode-[主机名].log

// DataNode
$HADOOP_HOME/logs/hadoop-[用户名]-datanode-[主机名].log

// JournalNode
$HADOOP_HOME/logs/hadoop-[用户名]-journalnode-[主机名].log
```

服务启动失败时，可通过查询对应日志检查失败原因。



# HDFS
`Hadoop Distributed File System (HDFS)`是一个被设计成运行在商用硬件上的分布式文件系统。
HDFS与现存的分布式文件系统类似，不同之处在于HDFS是**高容错**(highly fault-tolerant)的，
HDFS被设计成能够部署在低成本的硬件上。HDFS提供了对应用数据的高吞吐访问，适用于拥有大量数据集的应用。
HDFS放宽了一些POSIX标准的要求，以便实现流式地访问文件系统数据。
HDFS最初被设计成`Apache Nutch`(一个Web搜索引擎项目)的基础设施，现在HDFS是`Apache Hadoop`项目的核心部分。

## 访问地址
HDFS的RPC通信地址规则如下：

```sh
# 默认端口 9000
hdfs://主机名或IP:RPC服务端口/HDFS路径
```

HDFS还提供了WEB管理界面，地址如下：

```sh
# 默认端口 50070
http://主机名或IP:WEB服务端口
```

## 命令行工具
使用`hdfs dfs`指令对HDFS文件系统进行操作。

查看指令帮助信息：

```
$ hdfs dfs -help [指令名称]
```

查看文件/目录：

```c
// 查看目录内容
$ hdfs dfs -ls [HDFS目录]

// 递归查看目录
$ hdfs dfs -lsr [HDFS目录]

// 查看文件内容
$ hdfs dfs -cat [HDFS文件路径]
$ hdfs dfs -tail [HDFS文件路径]

// 查看目录统计信息(文件数，大小等)
$ hdfs dfs -count [HDFS文件路径]
$ hdfs dfs -df [HDFS文件路径]
$ hdfs dfs -du [HDFS文件路径]
```

创建/删除文件：

```c
// 上传本地文件到HDFS
$ hdfs dfs -put [本地路径] [HDFS路径]

// 从HDFS下载文件
$ hdfs dfs -get [HDFS路径] [本地路径]

// 创建目录
// 使用 -p 参数递归创建不存在的路径
$ hdfs dfs -mkdir [HDFS路径]

// 移除文件、目录
$ hdfs dfs -rm [HDFS路径]
$ hdfs dfs -rmdir [HDFS路径]
```



# Hbase
`Apache HBase™`是基于Hadoop的数据库，具有分布式、可扩展、支持海量数据存储等特性。

HBase常用在需要随机、实时读写海量数据的场景下。项目的目标是在商业硬件集群上管理非常巨大的表(上亿行 x 上亿列)。
HBase是开源(open-source)、分布式(distributed)、版本化(versioned)、非关系型(non-relational)的数据库，参照了Google Bigtable的设计。
HBase在Hadoop和HDFS之上提供了类似Bigtable的功能。

HBase的详细介绍、配置、使用说明等可查阅[官方文档](http://hbase.apache.org/book.html)。

## 服务配置
从[HBase官网](http://hbase.apache.org/downloads.html)中下载稳定版本的HBase。
HBase依赖于Hadoop服务，HBase与Hadoop版本的兼容性参考中的`4.1`节。

配置环境变量，在`~/.profile`或`/etc/profile`中添加：

```sh
export HBASE_HOME=... # 配置软件包路径
PATH+=:$HBASE_HOME/bin # 将HBase相关工具脚本加入 PATH 中
```

HBase配置文件位于`$HBASE_HOME/conf`路径下，编辑`$HBASE_HOME/conf/hbase-site.xml`，添加下列配置：

```xml
<configuration>

	<!--
		指定 HBase 临时文件目录
		默认临时文件会生成在 /tmp/hbase-[用户名] 路径下，机器重启后临时文件会被清空
	-->
	<property>
		<name>hbase.tmp.dir</name>
		<value>/home/data/hadoop/hbase-tmp</value>
	</property>

	<!-- 指定 HBase 的数据存储路径 -->
	<property>
		<name>hbase.rootdir</name>
		<value>hdfs://spark-master:9000/hbase</value>
	</property>

	<!-- 设定 HBase 是否以分布式方式执行 -->
	<property>
		<name>hbase.cluster.distributed</name>
		<value>true</value>
	</property>

	<!-- 指定 Zookeeper 集群访问地址 -->
	<property>
		<name>hbase.zookeeper.quorum</name>
		<value>spark-master:2181,spark-slave0:2181,spark-slave1:2181</value>
	</property>

</configuration>
```

启动/关闭HBase服务：

```c
// 启动 HBase 服务
$ start-hbase.sh

// 关闭 HBase 服务
$ stop-hbase.sh
```



## 数据模型
HBase是面向**列**的数据库，数据由行排序，表中仅能定义列族。
一张表中可以拥有多个列族，一个列族可拥有任意数量的列。表中每个单元格的数据都具有时间戳。

### Conceptual View (概念视图)
HBase中表的概念结构如下所示：

<table style="text-align:center">
	<tr>
		<th rowspan="2">Row Key</th>
		<th rowspan="2">Time Stamp</th>
		<th colspan="4">Column Family A</th>
		<th colspan="4">Column Family B</th>
		<th rowspan="2">...</th>
	</tr>
	<tr>
		<th>column a</th>
		<th>column b</th>
		<th>column c</th>
		<th>...</th>
		<th>column e</th>
		<th>column f</th>
		<th>column g</th>
		<th>...</th>
	</tr>
	<tr>
		<td>Row Key 1</td>
		<td>t1</td>
		<td>A:a="..."</td>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
		<td>B:f="..."</td>
		<td></td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>Row Key 2</td>
		<td>t2</td>
		<td></td>
		<td></td>
		<td>A:c="..."</td>
		<td></td>
		<td>B:e="..."</td>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>Row Key 2</td>
		<td>t3</td>
		<td></td>
		<td>A:b="..."</td>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>Row Key 3</td>
		<td>t4</td>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
		<td></td>
		<td>B:g="..."</td>
		<td></td>
		<td></td>
	</tr>
</table>

与传统的数据库不同，空的单元格并不实际占用空间，这是HBase被称为`sparse`(稀疏)存储的原因。<br>
上述概念结构用JSON表示为近似于：

```json
{
	"Row Key 1": {
		"A": {
			"t1:A:a": "..."
		},
		"B": {
			"t1:B:f": "..."
		}
	},
	"Row Key 2": {
		"A": {
			"t2:A:c": "...",
			"t3:A:b": "..."
		},
		"B": {
			"t2:B:e": "..."
		}
	},
	"Row Key 3": {
		"A": {},
		"B": {
			"t4:B:g": "..."
		}
	}
}
```

### Physical View (物理视图)
在概念上表格可被视为由一组稀疏行组成，但在物理结构上按**列族**分类存储。新的列限定符(列族:列名)可以随时追加到现有的列族中。

上述例子中的表格对应物理结构如下：

- 表 `Column Family A`

	| Row Key | Time Stamp | Column Family (A) |
	| :-: | :-: | :-: |
	| Row Key 1 | t1 | A:a="..." |
	| Row Key 2 | t3 | A:b="..." |
	| Row Key 2 | t2 | A:c="..." |

- 表 `Column Family B`

	| Row Key | Time Stamp | Column Family (B) |
	| :-: | :-: | :-: |
	| Row Key 1 | t2 | B:e="..." |
	| Row Key 2 | t1 | B:f="..." |
	| Row Key 3 | t4 | B:g="..." |

概念视图中显示的空单元格实际上并不存储。
使用时间戳访问数据时，访问时间戳不存在的数据不会得到返回结果。
当指定的`行:列族:列名`存在多个版本的数据时，不使用时间戳访问数据，得到的是最新(时间戳最靠后)的版本。
查询**整行数据**时，得到的是该行数据每列各自的最新版本的数据。

### Namespace (命名空间)
命名空间是与传统的关系型数据库中的**数据库**概念类似的表格逻辑分组。<br>
命名空间是多租户(multi-tenancy)相关功能的基础：

- 配额管理(HBASE-8410)
- 命名空间安全管理(HBASE-9206)
- 区域服务器组(HBASE-6721)

## HBase Shell
HBase提供了基于`(J)Ruby`语言的交互式Shell(`IRB`)，提供了HBase中常用的功能函数。
IRB是标准的Ruby Shell，可直接执行Ruby代码。

使用`hbase shell`指令可进入HBase的IRB中：

```ruby
Version 1.2.6, rUnknown, Mon May 29 02:25:32 CDT 2017

hbase(main):001:0>
```

使用`help`函数查看基本的帮助信息，使用`help "函数名"`查看具体某个功能函数的详细用法。

常用指令函数用法：

- 表格操作

	使用`describe/desc`函数查看表信息：

	```ruby
	hbase> describe "表名"
	hbase> desc "表名"

	# 查看带有命名空间的表
	hbase> describe "命名空间:表名"
	hbase> desc "命名空间:表名"
	```

	使用`create`函数创建表格：

	```ruby
	# 首个参数为表名，之后为表中包含的列族
	hbase> create "表名", "列族1", "列族2", ...

	# HBase中每个列族拥有独立的配置，创建表同时设置每个列族的配置
	hbase> create "表名", { NAME => "列族1", XXX => xxx, ... }, { NAME => "列族2", XXX => xxx, ... }, ...
	```

	删除表格首先使用`disable`函数禁用表格，之后使用`drop`函数删除：

	```ruby
	# 禁用指定表
	hbase> disable "表名"

	# 删除指定表
	hbase> drop "表名"
	```

	使用`alter`函数调整已创建的表格的配置：

	```ruby
	hbase> alter "表名", Xxx => xxx, ...

	# 可以同时修改多个列族的配置
	hbase> alter "表名", { NAME => "列族1", Xxx => xxx, ... }, { NAME => "列族2", Xxx => xxx, ... }, ...
	```

	部分配置(如`VERSIONS`)直接修改无效，需要指定列族名称进行修改。

- 插入、更新数据

	使用`put`函数向表中插入、更新数据：

	```ruby
	hbase> put "命名空间:表名", "RowKey", "列族:列名", "值"

	# 命名空间和列名可以不写，默认为空
	hbase> put "表名", "RowKey", "列族", "值"
	hbase> put "表名", "RowKey", "列族", "值", 时间
	hbase> put "表名", "RowKey", "列族", "值", ATTRIBUTES => { Xxx => xxx, ... }
	hbase> put "表名", "RowKey", "列族", "值", 时间, ATTRIBUTES => { Xxx => xxx, ... }
	hbase> put "表名", "RowKey", "列族", "值", 时间, VISIBILITY => "PRIVATE|SECRET"
	```

	根据列族的VERSIONS配置，每个单元格会保存一定版本的数据，当保存的版本数达到设定的VERSIONS值时会丢弃时间戳最早的数据。

- 删除数据

	使用`delete/deleteall`函数从表中删除数据：

	```ruby
	# 使用delete函数删除指定单元格、指定时间的数据
	hbase> delete "命名空间:表名", "RowKey", "列族:列名", 时间
	hbase> delete "表名", "RowKey", "列族", 时间
	hbase> delete "表名", "RowKey", "列族", 时间, VISIBILITY => "PRIVATE|SECRET"

	# deleteall函数支持删除整行、所有时间戳的数据
	hbase> deleteall "命名空间:表名", "RowKey"
	hbase> deleteall "表名", "RowKey"
	hbase> deleteall "表名", "RowKey", "列族:列名"
	hbase> deleteall "表名", "RowKey", "列族", 时间
	hbase> deleteall "表名", "RowKey", "列族", 时间, VISIBILITY => "PRIVATE|SECRET"

	# delete/deleteall方法也存在于 HBase::Table 对象中，通过get_table函数构建对象
	hbase> table = get_table "表名"
	hbase> table.deleteall "RowKey" # 等价于 deleteall "表名", "RowKey"
	hbase> table.delete "RowKey", "列族", 时间 # 等价于 delete "表名", "RowKey", "列族", 时间
	```

- 查询数据

	使用`scan`函数查看表格内数据：

	```ruby
	# 查看整张表内的数据
	hbase> scan "表名"

	# 表名之后可携带查询参数，如RowKey前缀、列族、列名、返回数目、逆序等
	hbase> scan "表名", ROWPREFIXFILTER => "RowKey前缀", COLUMNS => ["列族", "列族:列名", ...], REVERSED => 是否逆序, LIMIT => 返回数目, FLITER => "自定义过滤器...", ....
	```

	使用`get`函数查看指定表中指定行的数据：

	```ruby
	# 获取指定表中某个RowKey的所有数据
	hbase> get "表名", "RowKey"

	# get方法也存在于 HBase::Table 对象中，通过get_table函数构建对象
	hbase> table = get_table "表名"
	hbase> table.get "RowKey" # 等价于 get "表名", "RowKey"

	# RowKey之后可添加限制条件
	hbase> get "表名", "RowKey", TIMERANGE => [时间1, 时间2]
	hbase> get "表名", "RowKey", COLUMN => "列名"
	hbase> get "表名", "RowKey", COLUMN => ["列名1", "列名2", "列名3", ...]
	hbase> get "表名", "RowKey", "列名"
	hbase> get "表名", "RowKey", "列名1", "列名2", ...
	hbase> get "表名", "RowKey", ["列名1", "列名2", ...]
	hbase> get "表名", "RowKey", COLUMN => "列名", TIMESTAMP => 时间
	hbase> get "表名", "RowKey", COLUMN => "列名", TIMERANGE => [时间1, 时间2], VERSIONS => 版本数目
	hbase> get "表名", "RowKey", COLUMN => "列名", TIMESTAMP => 时间, VERSIONS => 版本数目
	hbase> get "表名", "RowKey", FILTER => "自定义过滤器..."
	hbase> get "表名", "RowKey", CONSISTENCY => 'TIMELINE'
	hbase> get "表名", "RowKey", CONSISTENCY => 'TIMELINE', REGION_REPLICA_ID => 1
	```

## HBase Client API
使用HBase的客户端API首先需要引入对应依赖。

- 使用`Maven`则在`pom.xml`中引入：

	```xml
	<dependency>
		<groupId>org.apache.hbase</groupId>
		<artifactId>hbase-client</artifactId>
		<version>HBase版本</version>
	</dependency>
	```

- 使用`SBT`则在`build.sbt`中引入：

	```scala
	libraryDependencies += "org.apache.hbase" % "hbase-client" % "HBase版本"
	```

HBase相关API位于`org.apache.hadoop.hbase`包路径下，
Client相关API主要位于`org.apache.hadoop.hbase.client`包路径下。

主要的API用法：

- 创建数据连接

	通过`org.apache.hadoop.hbase.client.ConnectionFactory`工厂类提供的`ConnectionFactory.createConnection()`静态方法创建数据连接：

	```java
	public class ConnectionFactory {
		...
		public static Connection createConnection() throws IOException;
		public static Connection createConnection(Configuration conf) throws IOException;
		public static Connection createConnection(Configuration conf, User user) throws IOException;
		public static Connection createConnection(Configuration conf, ExecutorService pool, User user) throws IOException;
		...
	}
	```

	`ConnectionFactory.createConnection()`方法提供了多个重载，可在创建连接是设定连接配置、线程池、用户信息等配置。

	连接配置使用`org.apache.hadoop.hbase.HBaseConfiguration`类提供的`HBaseConfiguration.create()`静态方法创建。
	使用`Configuration.set()`方法向创建的配置实例中添加具体的配置项。

	连接创建完毕后，使用`Connection.getTable()`方法获取指定HBase数据表的实例进行具体的数据操作。

	创建数据连接、获取表格实例，示例代码如下：

	```java
	// 创建连接配置
	HBaseConfiguration hbaseConfiguration = HBaseConfiguration.create();
	// 设定配置项
	hbaseConfiguration.set("hbase.zookeeper.property.clientPort", "2181");
	hbaseConfiguration.set("hbase.zookeeper.quorum", "主机名/主机IP");
	...

	// 通过连接配置构建连接实例
	Connection hBaseConnection = ConnectionFactory.createConnection(hbaseConfig);

	// 通过连接获取指定表格实例
	Table table = hBaseConnection.getTable(TableName.valueOf("表名"));
	```


- 表格操作

	`org.apache.hadoop.hbase.client.Table`接口中声明了`Table.getTableDescriptor()`方法，
	Table实例使用此方法可获取表格的描述实例`HTableDescriptor`，该类中提供了查看、设置各类表格信息的方法：

	```java
	public class HTableDescriptor implements WritableComparable<HTableDescriptor> {

		...

		// 获取表的配置项
		public Map<String, String> getConfiguration();

		// 获取列族的描述信息
		public Collection<HColumnDescriptor> getFamilies();
		// 获取指定列族的描述信息
		public HColumnDescriptor getFamily(byte[] column);
		// 移除指定列族
		public HColumnDescriptor removeFamily(byte[] column);
		// 添加列族
		public HTableDescriptor addFamily(HColumnDescriptor family);
		// 修改列族
		public HTableDescriptor modifyFamily(HColumnDescriptor family);

		...

	}
	```

	`org.apache.hadoop.hbase.client.Connection`接口中声明了`Connection.getAdmin()`方法，
	Connection实例使用此方法获取表格管理实例`Admin`，该类提供了表格的查看、创建、删除、禁用等功能：

	```java
	public interface Admin extends Abortable, Closeable {

		...

		// 列出所有表
		HTableDescriptor[] listTables() throws IOException;

		// 创建、删除表
		void createTable(HTableDescriptor desc) throws IOException;
		void deleteTable(TableName tableName) throws IOException;

		// 启用、禁用表
		void enableTable(TableName tableName) throws IOException;
		void disableTable(TableName tableName) throws IOException;

		// 添加、删除、更新表中的列
		void addColumn(TableName tableName, HColumnDescriptor desc) throws IOException;
		void deleteColumn(TableName tableName, byte[] columnName) throws IOException;
		void modifyColumn(TableName tableName, HColumnDescriptor desc) throws IOException;

		...

	}
	```

- 增、删、改、查

	与命令行指令类似，通过创建以下类型实例描述增删改查操作：

	| 类型 | 操作 |
	| :- | :- |
	| org.apache.hadoop.hbase.client.Put | 插入、修改 |
	| org.apache.hadoop.hbase.client.Delete | 删除 |
	| org.apache.hadoop.hbase.client.Scan | 查询 |
	| org.apache.hadoop.hbase.client.Get | 指定查询 |

	Table类型中提供了同名方法，用于执行对应的操作：

	```java
	public interface Table extends Closeable {

		...

		// 查询
		Result get(Get get) throws IOException;
		Result[] get(List<Get> gets) throws IOException;
		ResultScanner getScanner(Scan scan) throws IOException;

		// 插入、修改
		void put(Put put) throws IOException;
		void put(List<Put> puts) throws IOException;

		// 删除
		void delete(Delete delete) throws IOException;
		void delete(List<Delete> deletes) throws IOException;

		...

	}
	```

	调用对应方法，将创建操作实例作为参数，执行增删改查操作。



# 问题注记
Hadoop配置中遇到问题的说明和解决方案。

## ERROR org.apache.hadoop.hdfs.server.namenode.NameNode: Failed to start namenode.org.apache.hadoop.hdfs.server.namenode.EditLogInputException: Error replaying edit log at offset 0.  Expected transaction ID was 1
问题说明：<br>
namenode启动失败，需要重新格式化，保证namenode的ID一致性。

解决方案：<br>
格式化失败尝试`hdfs  namenode -format -force`同时格式化namenode和datanode。

## Call From xxx to xxx failed on connection exception: java.net.ConnectException: Connection refused;
问题说明：<br>
执行`hdfs namenode -format`指令时，集群未启动，需要在集群已启动的情况下格式化NameNode。

解决方案：<br>
启动集群后再格式化NameNode。

## java.io.IOException: Got error, status message , ack with firstBadLink as xxx.xxx.xxx.xxx:xxx
问题说明：<br>
防火墙服务开启导致HDFS节点之间访问异常。

解决方案：<br>
关闭对应节点的防火墙服务：

```c
# systemctl stop firewalld //关闭防火墙服务
# systemctl disable firewalld //禁止防火墙服务自启动
```

## 全部HA节点处于 stand by 状态
问题说明：<br>
NameNode的HA状态异常，没有选举出active的节点，HA节点均为stand by。

解决方案：<br>
检查Zookeeper运行状态，NameNode选举依赖Zookeeper提供的服务。
若Zookeeper正常，则可尝试重新格式化NameNode。
或者使用`haadmin`工具强制指定active节点：

```
$ hdfs haadmin -transitionToActive --forcemanual [需要激活的NameNode名称]
```

## org.apache.hadoop.hbase.client.RetriesExhaustedException
问题说明：<br>
HBase建立连接不成功，重试次数过多后产生异常。

解决方案：<br>
在日志中打印HBase的连接字符串，检查连接字符串是否有错误。
HBase连接字符串中多个Zookeeper服务主机名之间用逗号分隔，不能带有空格：

```scala
val hbaseConfig = HBaseConfiguration.create()

// 错误
hbaseConfig.set("hbase.zookeeper.quorum", "spark-master, spark-slave0, spark-slave1")

// 正确
hbaseConfig.set("hbase.zookeeper.quorum", "spark-master,spark-slave0,spark-slave1")
```

## XXX: Error: JAVA_HOME is not set and could not be found.
问题说明：<br>
Hadoop、HBase、Spark启动时提示`JAVA_HOME`环境变量配置未配置，但实际环境变量中已设定JAVA_HOME。

解决方案：<br>
编辑`$HADOOP_HOME/etc/hadoop/hadoop-env.sh`文件，
将文件中的`export JAVA_HOME=${JAVA_HOME}`替换为实际的绝对路径。

## Caused by: java.lang.ClassNotFoundException: com.yammer.metrics.core.Gauge
问题说明：<br>
Spark应用使用HBase Client连接HBase数据库，建立连接时提示找不到类。

解决方案：<br>
打包Spark应用时需要完整包含HBase相关依赖，包括`hbase*`、`metrics*`、`htrace*`。

## java.io.IOException: Incompatible clusterIDs in /tmp/hadoop-root/dfs/data: namenode clusterID = CID-...; datanode clusterID = CID-...
问题说明：<br>
启动DataNode失败，提示DataNode的`clusterID`与NameNode不匹配。
通常是NameNode重新格式化后，DataNode数据路径未清空，仍保留与之前NameNode版本匹配的数据。

解决方案：<br>
清空DataNode中数据路径下的内容。
默认DataNode路径为`${hadoop.tmp.dir}/dfs/dfs`，若设定了`hadoop.datanode.data.dir`配置，则路径以该配置项为准。

## WARN org.apache.hadoop.hdfs.server.datanode.DataNode: IOException in offerService; java.io.EOFException: End of File Exception between local host is: "xxxs/xx.xx.xx.xx"; destination host is: "xxhostname":xxxx;
问题说明：<br>
启动DataNode时日志中提示目标IP与本地主机IP不符。使用`hadoop fs -xx...`指令访问HDFS文件系统时，
命令行提示`-ls: java.net.UnknownHostException: [NameService]`错误。

解决方案：<br>
修改`$HADOOP_HOME/etc/hadoop/core-site.xml`配置中的`fs.defaultFS`配置项，
不使用NameServices名称作为HDFS路径，而是直接使用HDFS的RPC地址。
如下所示：

```xml
<property>
	<name>fs.defaultFS</name>
	<value>hdfs://localhost:9000</value>
	<!-- 不使用 hdfs://XxxNameService 形式的HDFS路径 -->
</property>
```
