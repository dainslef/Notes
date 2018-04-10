<!-- TOC -->

- [概述](#概述)
	- [下载](#下载)
	- [环境变量配置](#环境变量配置)
	- [集群规划](#集群规划)
	- [路径规划](#路径规划)
	- [服务配置](#服务配置)

<!-- /TOC -->



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
在[Hadoop官网](`http://hadoop.apache.org/releases.html`)下载Hadoop软件包。

截止到`2018-3-30`，Hadoop主要分为`2.x`和`3.x`两大版本，`3.x`版本在配置上与`2.x`版本有较大差异。  
`3.x`版本正式发布时间较晚(2017-12-13)、迭代周期较短，稳定性有待考证，本文配置使用`2.7.5`版本。

## 环境变量配置
配置环境变量，在`~/.profile`或`/etc/profile`中添加：

```sh
export HADOOP_HOME=... # 配置Hadoop软件包路径
export PATH+=:$HADOOP_HOME/bin
export PATH+=:$HADOOP_HOME/sbin # 将Hadoop相关工具加入PATH环境变量
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
|:--------|:-------|
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
