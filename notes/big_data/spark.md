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
