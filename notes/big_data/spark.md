# 概述
`Apache Spark`是一套**快速**(fast)、**多用途**(general-purpose)的集群计算系统(cluster computing system)。

Spark提供了`Scala`、`Java`、`Python`、`R`等语言的上层API和支持通用执行图的优化引擎。  
Spark同时提供了一套高级工具集包括`Spark SQL`(针对SQL和结构化数据处理)、`MLib`(针对机器学习)、`GraphX`(针对图处理)、`Spark Streaming`。

## 下载
在[Spark官网](http://spark.apache.org/downloads.html)下载Saprk软件包。  
下载Spark时需要注意Spark版本与Hadoop、Scala版本的对应关系：

- `Spark 2.0`之后官网提供的软件包默认基于`Scala 2.11`构建。
- Spark运行需要的Hadoop最低版本通常会写入压缩包名称中，如`spark-2.3.0-bin-hadoop2.7.tgz`最低需要`Hadoop 2.7`。

Scala版本兼容性：

- 大版本兼容性

	Scala编译器编译出的字节码在不同大版本之间**不具有**二进制兼容性，如`2.10`/`2.11`/`2.12`等。  
	在添加`Spark API`依赖时需要根据集群运行的Spark版本使用正确的Scala编译器版本。

- 小版本兼容性

	Scala编译器在小版本之前二进制兼容，如`2.12.1`/`2.12.2`等。  
	在小版本内切换编译器版本无需重新编译生成字节码。

## 服务配置
编辑`/etc/profile`或`~/.profile`，配置Spark相关的环境变量：

```sh
export SPARK_HOME=... # 配置软件包路径
export PATH+=:$SPARK_HOME/bin # 将Spark工具加入 PATH 中
export PATH+=:$SPARK_HOME/sbin # 将Spark工具加入 PATH 中

# 以下配置也可写入 $SPARK_HOME/conf/spark-env.sh 中
export SPARK_MASTER_HOST=172.16.0.126 # 集群的 Master 节点
export SPARK_WORKER_CORES=4 # 指定 Worker 节点使用的核心数
export SPARK_WORKER_MEMORY=16g # 指定 Worker 节点能够最大分配给 Executors 的内存大小
export HADOOP_CONF_DIR=$HADOOP_HOME/etc/hadoop # 指定 Hadoop 集群的配置路径
```

之后创建`$SPARK_HOME/conf/slaves`文件，将需要做为Worker的主机名添加到改文件中：

```sh
spark-slave0
spark-slave1
spark-slave2
...
```

保证集群各机器间能够免密登陆，将配置文件分发到集群的其它机器上，执行指令启动/关闭服务：

```c
$ start-all.sh //启动服务
$ stop-all.sh //停止服务
```

正常启动Spark服务后，使用JPS查看进程，主节点应有`Master`进程，从节点应有`Worker`进程。  
默认配置下，Spark在`8080`端口提供集群管理的WEB界面。



# 常见错误
Spark开发、使用中常见错误说明。

## *Unable to load native-hadoop library for your platform... using builtin-java classes where applicable*
错误说明：  
Spark运行环境中已包含了Scala、Hadoop、Zookeeper等依赖，与Jar包中自带的依赖产生冲突。

解决方式：  
开发环境中为确保源码正常编译，需要完整引入Spark相关依赖，但在生成Jar时，需要移除Spark以及相关联的Scala、Hadoop、Zookeeper相关依赖。  

## *Operation category READ is not supported in state standby*
错误说明：  
配置了NameNode HA的Hadoop集群会存在`active`、`standby`两种状态。  
SparkStreaming使用HDFS为数据源时URL需要使用active节点的主机名。

解决方式：  
登陆HDFS的WEB管理界面查看节点状态，设置HDFS的URL时使用active节点的主机名。

## *org.apache.spark.SparkException: Failed to get broadcast_xxx of broadcast_xxx*
错误说明：  
在集群模式下执行Spark应用时，多个JVM实例间持有不同的SparkContent实例，导致Worker节点间通信出错。

解决方式：  
避免使用单例模式保存SparkContent实例，单例模式在集群中存在多个JVM实例时不可靠。  
创建SparkContext应在主函数代码中进行，构建SparkContext应使用伴生对象中提供的`SparkContext.getOrCreate()`方法。
