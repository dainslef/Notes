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
	- [数据模型](#数据模型)
		- [Conceptual View (概念视图)](#conceptual-view-概念视图)
		- [Physical View (物理视图)](#physical-view-物理视图)
- [问题注记](#问题注记)
	- [ERROR org.apache.hadoop.hdfs.server.namenode.NameNode: Failed to start namenode.org.apache.hadoop.hdfs.server.namenode.EditLogInputException: Error replaying edit log at offset 0. Expected transaction ID was 1](#error-orgapachehadoophdfsservernamenodenamenode-failed-to-start-namenodeorgapachehadoophdfsservernamenodeeditloginputexception-error-replaying-edit-log-at-offset-0-expected-transaction-id-was-1)
	- [Call From xxx to xxx failed on connection exception: java.net.ConnectException: Connection refused;](#call-from-xxx-to-xxx-failed-on-connection-exception-javanetconnectexception-connection-refused)
	- [java.io.IOException: Got error, status message , ack with firstBadLink as xxx.xxx.xxx.xxx:xxx](#javaioioexception-got-error-status-message--ack-with-firstbadlink-as-xxxxxxxxxxxxxxx)
	- [全部HA节点处于 stand by 状态](#全部ha节点处于-stand-by-状态)



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
Hadoop服务配置项多而繁杂，[官方文档地址](http://hadoop.apache.org/docs/)，根据Hadoop版本选择匹配的文档进行查阅。  
集群配置相关文档地址为`http://hadoop.apache.org/docs/{Hadoop版本}/hadoop-project-dist/hadoop-common/ClusterSetup.html`。

Hadoop配置文件位于`$HADOOP_HOME/etc/hadoop`路径下，需要修改的配置文件如下：

- `core-site.xml`

	Hadoop的核心配置项。
	配置项说明：

	```xml
	<configuration>

		<!-- 指定 hdfs 的 nameservice 为 lj-nameservice -->
		<property>
			<name>fs.defaultFS</name>
			<value>hdfs://lj-nameservice/</value>
		</property>

		<!-- 指定 hadoop 临时文件目录 -->
		<property>
			<name>hadoop.tmp.dir</name>
			<value>/home/data/hadoop/tmp</value>
		</property>

		<!-- 指定 zookeeper 集群访问地址 -->
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

	包含对NameNode和DataNode的配置项。
	配置项说明：

	```xml
	<configuration>

		<!-- 指定副本数 -->
		<property>
			<name>dfs.replication</name>
			<value>2</value>
		</property>
	
		<!-- 指定 nameservice，需要和 core-site.xml 中 fs.defaultFS 配置项保持一致 -->
		<property>
			<name>dfs.nameservices</name>
			<value>lj-nameservice</value>
		</property>

		<!-- 设置 nameservice 下的 NameNode 名称 -->
		<property>
			<name>dfs.ha.namenodes.lj-nameservice</name>
			<value>namenode1,namenode2</value>
		</property>

		<!-- namenode1 的 RPC 通信地址 -->
		<property>
			<name>dfs.namenode.rpc-address.lj-nameservice.namenode1</name>
			<value>spark-master:9000</value>
		</property>

		<!-- namenode1 的 http 通信地址 -->
		<property>
			<name>dfs.namenode.http-address.lj-nameservice.namenode1</name>
			<value>spark-master:50070</value>
		</property>

		<!-- namenode2 的 RPC 通信地址 -->
		<property>
			<name>dfs.namenode.rpc-address.lj-nameservice.namenode2</name>
			<value>spark-slave0:9000</value>
		</property>

		<!-- namenode2 的 http 通信地址 -->
		<property>
			<name>dfs.namenode.http-address.lj-nameservice.namenode2</name>
			<value>spark-slave0:50070</value>
		</property>

		<!-- 指定HA集群中多个 NameNode 之间的共享存储路径 -->
		<property>
			<name>dfs.namenode.shared.edits.dir</name>
			<value>qjournal://spark-master:8485;spark-slave0:8485;spark-slave1:8485/lj-nameservice</value>
		</property>

		<!-- 指定 JournalNode 在本地磁盘存放数据的位置 -->
		<property>
			<name>dfs.journalnode.edits.dir</name>
			<value>/home/data/hadoop/hdfs/journal</value>
		</property>

		<!-- 开启 NameNode 失败自动切换 -->
		<property>
			<name>dfs.ha.automatic-failover.enabled</name>
			<value>true</value>
		</property>

	</configuration>
	```



# HDFS
`Hadoop Distributed File System (HDFS)`是一个被设计成运行在商用硬件上的分布式文件系统。  
HDFS与现存的分布式文件系统类似，不同之处在于HDFS是**高容错**(highly fault-tolerant)的，HDFS被设计成能够部署在低成本的硬件上。  
HDFS提供了对应用数据的高吞吐访问，适用于拥有大量数据集的应用。  
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

与传统的数据库不同，空的单元格并不实际占用空间，这是HBase被称为`sparse`(稀疏)存储的原因。
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



# 问题注记
Hadoop配置中遇到问题的说明和解决方案。

## ERROR org.apache.hadoop.hdfs.server.namenode.NameNode: Failed to start namenode.org.apache.hadoop.hdfs.server.namenode.EditLogInputException: Error replaying edit log at offset 0.  Expected transaction ID was 1
问题说明：  
namenode启动失败，需要重新格式化，保证namenode的ID一致性。

解决方案：  
格式化失败尝试`hdfs  namenode -format -force`同时格式化namenode和datanode。

## Call From xxx to xxx failed on connection exception: java.net.ConnectException: Connection refused;
问题说明：  
执行`hdfs namenode -format`指令时，集群未启动，需要在集群已启动的情况下格式化NameNode。

解决方案：  
启动集群后再格式化NameNode。

## java.io.IOException: Got error, status message , ack with firstBadLink as xxx.xxx.xxx.xxx:xxx
问题说明：  
防火墙服务开启导致HDFS节点之间访问异常。

解决方案：  
关闭对应节点的防火墙服务：

```c
# systemctl stop firewalld //关闭防火墙服务
# systemctl disable firewalld //禁止防火墙服务自启动
```

## 全部HA节点处于 stand by 状态
问题说明：  
NameNode的HA状态异常，没有选举出active的节点，HA节点均为stand by。

解决方案：  
检查Zookeeper运行状态，NameNode选举依赖Zookeeper提供的服务。  
若Zookeeper正常，则可尝试重新格式化NameNode。  
或者使用`haadmin`工具强制指定active节点：

```
$ hdfs haadmin -transitionToActive --forcemanual [需要激活的NameNode名称]
```
