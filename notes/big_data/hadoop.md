<!-- TOC -->

- [概述](#概述)

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
