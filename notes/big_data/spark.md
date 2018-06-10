- [概述](#概述)
	- [下载](#下载)
	- [服务配置](#服务配置)
- [集群模型](#集群模型)
	- [集群管理器类型](#集群管理器类型)
	- [术语表](#术语表)
- [RDD (弹性分布式数据集)](#rdd-弹性分布式数据集)
	- [创建 RDD](#创建-rdd)
	- [RDD 分区](#rdd-分区)
	- [RDD 操作](#rdd-操作)
	- [Shuffle 操作](#shuffle-操作)
		- [背景知识](#背景知识)
		- [性能影响](#性能影响)
	- [作业调度](#作业调度)
		- [Job Sumbit](#job-sumbit)
- [Spark Streaming](#spark-streaming)
	- [Streaming Context](#streaming-context)
	- [DStream](#dstream)
	- [数据变换](#数据变换)
		- [updateStateByKey()](#updatestatebykey)
		- [mapWithState()](#mapwithstate)
- [常见错误](#常见错误)
	- [Unable to load native-hadoop library for your platform... using builtin-java classes where applicable](#unable-to-load-native-hadoop-library-for-your-platform-using-builtin-java-classes-where-applicable)
	- [Operation category READ is not supported in state standby](#operation-category-read-is-not-supported-in-state-standby)
	- [org.apache.spark.SparkException: Failed to get broadcast_xxx of broadcast_xxx](#orgapachesparksparkexception-failed-to-get-broadcast_xxx-of-broadcast_xxx)



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



# 集群模型
Spark应用作为独立的进程集在集群中运行，通过`SparkContext`对象在用户主程序(`dirver program`)中与集群组织、交互。

Spark应用在集群中运行时，SparkContext会连接到某种类型的`cluster managers`(集群管理器，如`Mesos`、`YARN`)，由集群管理器在多个应用间分配资源。
一旦连接建立，Spark会在集群的节点中获取`executors`(执行器)，executors是执行计算操作和存储用户应用数据的进程。
之后，SparkContext将用户的应用代码(在`JAR`中或Python源码文件)发送到executors。
最终，SparkContext发送`tasks`(任务)到executors中运行。

集群结构如下图所示：

![avatar](../../images/spark_cluster_overview.png)

关于集群架构的一些注意事项：

1. 每个用户应用拥有属于自己的执行器进程(executor processes)，这些进程保持在整个应用期间，并在多个线程中执行tasks。
这有利于隔离不同的用户应用，包括调度端(每个driver调度自己的tasks)和执行端(来自不同应用的tasks子不同的JVM中执行)。
1. Spark并不知道底层集的群管理器，仅需要能获取执行器进程并能相互通信。
相对而言，将Spark运行在支持其它应用的集群管理器上更加简单(如`Mesos`、`YARN`)。
1. dirver program必须在整个生命周期内监听并接受来自executors的连接。因此，driver program必须能从work nodes寻址。
1. 由于diriver在集群中调度tasks，因此需要在网络位置上邻近worker nodes，最好在相同的局域网中。
如果需要向远程集群发送请求，最好为driver开启RPC，在与worker nodes邻近的网络位置启动driver，
使用RPC提交操作，而不是在与worker nodes较远的网络位置上直接执行driver。

## 集群管理器类型
Spark当前支持以下集群管理器：

- `Standalone` Spark内置的简单集群管理器
- `Apache Mesos` 通用的资源管理器，也可用于执行Hadoop MapReduce和服务应用
- `Hadoop YARN` Hadoop2的资源管理器
- `Kubernetes` 用于自动化部署、容器应用管理的开源系统

## 术语表
以下列表总结了在集群概念中提及的术语：

术语 | 含义
:-|:-
Application | Spark中的用户应用程序，由集群中的driver program和executors组成。
Application jar | 包含用户应用内容的JAR包。JAR包中应打包用户代码所需要的第三方依赖库，但不应该包含Hadoop或Spark库，这些库会在应用运行时添加。
Driver program | 执行用户应用中的main()函数并创建SparkContext的进程。
Cluster manager | 在集群中获取资源的外部服务(如Mesos、YARN)。
Deploy mode | 区分driver进程的执行位置。`cluster`模式下，在集群内部启动driver；`client`模式下，在集群外部启动driver。
Worker node | 可以在集群中执行用户应用代码的节点(部署了Spark服务的IP)。
Executor | 在woker node中启动的用户应用的进程，执行tasks并在内存/磁盘中保存数据。每个用户应用都拥有属于自身的executor。
Task | 将要发往executor的工作单元(a unit of work)。
Job | 由多个Spark操作(如`save()`、`collect()`等)的task组成的并行计算。
Stage | 每个job被拆分成较小的、具有依赖关系的task集合，这些任务集被称为stage。



# RDD (弹性分布式数据集)
`RDD`(`Resilient Distributed Datasets`，弹性分布式数据集)是高容错性(fault-tolerant)、可并行操作的的数据集合。
RDD是Spark中对数据的抽象，是Spark中的核心概念。

## 创建 RDD
Spark提供了两种创建RDD的方式：

1. 并行化程序中已存在的普通数据集：

	调用`SparkContext.parallelize()`方法将已存在的普通数据集(`Seq[T]`)转换为`RDD[T]`。  
	方法定义如下(源码取自`Spark 2.3.0`)：

	```scala
	class SparkContext(config: SparkConf) extends Logging {
	  ...
	  def parallelize[T: ClassTag](seq: Seq[T], numSlices: Int = defaultParallelism): RDD[T] = ...
	  ...
	}
	```

	使用示例：

	```scala
	scala> val normalData = 1 to 10 //构建普通数据集
	normalData: scala.collection.immutable.Range.Inclusive = Range(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)

	scala> val rddData = sc.parallelize(normalData) //并行化数据集，生成RDD
	rddData: org.apache.spark.rdd.RDD[Int] = ParallelCollectionRDD[0] at parallelize at <console>:26
	```

1. 引用来自外部存储系统的数据集，如本地文件系统、HDFS、HBase、AmazonS3等：

	以文本文件为例，调用`SparkContext.textFile()`方法使用文本文件创建RDD。
	该方法传入文件的URI，按行读取文件构建文本数据集。  
	使用示例：

	```scala
	scala> val textRdd = sc.textFile("test.json")
	textRdd: org.apache.spark.rdd.RDD[String] = test.json MapPartitionsRDD[3] at textFile at <console>:24
	```

## RDD 分区
RDD在创建完毕后可以被并行地操作。  
一个重要的参数是分区数量(numbers of partions)，分区数量决定了数据集将会被切分成多少个分区。
Spark执行task时会在集群中的每一个分区进行。典型的分配方式是根据CPU数目每个CPU分配2～4个分区(CPU双核/四核)。
通常Spark会根据集群自动设置分区大小，但也可以通过设置`SparkContext.parallelize()`方法的第二参数来手动控制分区数量。

## RDD 操作
RDD支持两类操作：

1. `Transformation`

	通过已有的RDD创建出新的RDD，常见的transformation操作有`map()`、`filter()`、`flatMap()`等。

1. `Action`

	对RDD进行计算并返回计算结果，常见的action操作有`reduce()`、`collect()`、`count()`、`first()`等。

所有的transformation操作是延迟执行(lazy)的，transformation操作不会立即计算结果，而仅仅是记录要执行的操作。
transformation操作只在action操作要求返回结果时进行计算。Spark这样的设计能够保证计算更有效率，
例如，当一个数据集先后进行了`map()`和`reduce()`操作，Spark服务端便只会返回reduce之后的结果，而不是更大的map之后的数据集。

默认情况下，每个执行transformation操作之后的RDD会每次执行action操作时重新计算。
可以使用`persist()/cache()`方法将RDD在内存中持久化，Spark将在集群中保留这些数据，在下次查询时访问会更加快速。
Spark同样支持将RDD持久化到磁盘中，或是在多个节点之间复制。

## Shuffle 操作
Spark中的某些操作会触发被称为**shuffle**的事件。  
Suffle是Spark中将不同分组、横跨多个分区的数据再分布(re-distributing)的一套机制，
通常会包含跨excutor、跨机器的复制数据。这使得shuffle成为一种复杂(complex)、高开销(costly)的操作。

### 背景知识
以`reduceByKey()`操作为例，该操作对类型为`RDD[(Key, Value)]`的RDD执行，
将相同Key的所有`(Key, Value)`元组通过执行传入的reduce函数聚合到一个`(Key, Value)`的新元组中，构成新的RDD。
一个Key关联的所有`(Key, Value)`元组未必在相同的分区、甚至相同的机器，但计算结果时需要在相同的位置。

在Spark中，数据通常不会跨分区分布到某个特定操作所需要的位置。在计算期间，单个任务将在单个分区中执行。
事实上，为执行一个reduceByKey()的reduce task，Spark需要执行所有的操作，
必须从所有分区读取所有的Key和Value，并将多个分区中的Value组合，从而为每个Key计算最终结果。  
这个重新分配数据的过程即被称为shuffle。

新执行shuffle操作之后，元素在每个分区是确定的(deterministic)，分区的排序也是确定的，但元素的排序不是。
如果需要将元素排序，可以使用下列操作：

- `mapPartitions()` 使用`sorted()`等方法排序每一个分区
- `repartitionAndSortWithinPartitions()` 在重分区同时高效地排序分区
- `sortBy()` 生成一个全局已排序的RDD

会引起shuffle的操作包括：

- `repartition`操作，例如`repartition()`、`coalesce()`方法
- `byKey`操作，例如`groupByKey()`、`reduceByKey()`方法
- `join`操作，例如`join()`、`cogroup()`方法

### 性能影响
Shuffle是高开销(expensive)的操作，因为它涉及磁盘IO、网络IO、数据序列化。
为了shuffle操作组织数据，Spark会生成一系列tasks：

- `map tasks` 组织数据(organize the data)
- `reduce tasks` 聚合数据(aggregate the data)

这样的命名来自`Hadoop MapReudce`，与Spark中的`map()`、`reduce()`方法不直接相关。

## 作业调度
Spark在提交作业时会为RDD相关操作生成DAG(Directed Acyclic Graph，有向无环图)。

`DAGScheduler`类是Spark中作业调度的核心。  
在SparkContextc初始化过程中会创建DAGScheduler、TaskScheduler、SchedulerBackend实例，用于作业调度、任务调度。

### Job Sumbit
在driver program中，每次对RDD调用action操作的相关方法(如count()、reduce()、collect()等)，都会提交Job，
执行SparkContext的`runJob()`方法，通过DAGScheduler执行`runJob()`、`submitJob()`，
最终调用EventLoop(实现类DAGSchedulerEventProcessLoop)中post()方法发送`JobSubmitted()`消息通知任务提交完成。

```
    action操作
RDD =========> SparkContext.runJob() => DAGScheduler.runJob() => DAGScheduler.submitJob() => DAGSchedulerEventProcessLoop.post()
```

相关源码分析如下(源码取自`Spark 2.3.0`)：

- RDD中的action操作会调用SparkContext的`runJob()`方法提交Job(以count()、collect()、reduce()为例)：

	```scala
	abstract class RDD[T: ClassTag](
	    @transient private var _sc: SparkContext,
	    @transient private var deps: Seq[Dependency[_]]
	  ) extends Serializable with Logging {

	  ...

	  private def sc: SparkContext = {
	    if (_sc == null) {
	      throw new SparkException(
	        "This RDD lacks a SparkContext. It could happen in the following cases: \n(1) RDD " +
	        "transformations and actions are NOT invoked by the driver, but inside of other " +
	        "transformations; for example, rdd1.map(x => rdd2.values.count() * x) is invalid " +
	        "because the values transformation and count action cannot be performed inside of the " +
	        "rdd1.map transformation. For more information, see SPARK-5063.\n(2) When a Spark " +
	        "Streaming job recovers from checkpoint, this exception will be hit if a reference to " +
	        "an RDD not defined by the streaming job is used in DStream operations. For more " +
	        "information, See SPARK-13758.")
	    }
	    _sc
	  }

	  ...

	  /**
	   * Return the number of elements in the RDD.
	   */
	  def count(): Long = sc.runJob(this, Utils.getIteratorSize _).sum

	  ...

	  /**
	   * Return an array that contains all of the elements in this RDD.
	   *
	   * @note This method should only be used if the resulting array is expected to be small, as
	   * all the data is loaded into the driver's memory.
	   */
	  def collect(): Array[T] = withScope {
	    val results = sc.runJob(this, (iter: Iterator[T]) => iter.toArray)
	    Array.concat(results: _*)
	  }

	  ...

	  /**
	   * Reduces the elements of this RDD using the specified commutative and
	   * associative binary operator.
	   */
	  def reduce(f: (T, T) => T): T = withScope {
	    val cleanF = sc.clean(f)
	    val reducePartition: Iterator[T] => Option[T] = iter => {
	      if (iter.hasNext) {
	        Some(iter.reduceLeft(cleanF))
	      } else {
	        None
	      }
	    }
	    var jobResult: Option[T] = None
	    val mergeResult = (index: Int, taskResult: Option[T]) => {
	      if (taskResult.isDefined) {
	        jobResult = jobResult match {
	          case Some(value) => Some(f(value, taskResult.get))
	          case None => taskResult
	        }
	      }
	    }
	    sc.runJob(this, reducePartition, mergeResult)
	    // Get the final result out of our Option, or throw an exception if the RDD was empty
	    jobResult.getOrElse(throw new UnsupportedOperationException("empty collection"))
	  }

	  ...

	}
	```

- SparkConext的`runJob()`方法会调用自身关联的DAGScheduler中的`runJob()`方法
(SparkContext中的runJob()方法有多个重载，最终都会转发到调用DAGScheduler的重载)：

	```scala
	class SparkContext(config: SparkConf) extends Logging {

	  ...
	
	  @volatile private var _dagScheduler: DAGScheduler = _

	  ...
	
	  private[spark] def dagScheduler: DAGScheduler = _dagScheduler
	  private[spark] def dagScheduler_=(ds: DAGScheduler): Unit = {
	    _dagScheduler = ds
	  }

	  ...

	  _dagScheduler = new DAGScheduler(this)

	  ...

	  /**
	   * Run a function on a given set of partitions in an RDD and pass the results to the given
	   * handler function. This is the main entry point for all actions in Spark.
	   *
	   * @param rdd target RDD to run tasks on
	   * @param func a function to run on each partition of the RDD
	   * @param partitions set of partitions to run on; some jobs may not want to compute on all
	   * partitions of the target RDD, e.g. for operations like `first()`
	   * @param resultHandler callback to pass each result to
	   */
	  def runJob[T, U: ClassTag](
	      rdd: RDD[T],
	      func: (TaskContext, Iterator[T]) => U,
	      partitions: Seq[Int],
	      resultHandler: (Int, U) => Unit): Unit = {
	    if (stopped.get()) {
	      throw new IllegalStateException("SparkContext has been shutdown")
	    }
	    val callSite = getCallSite
	    val cleanedFunc = clean(func)
	    logInfo("Starting job: " + callSite.shortForm)
	    if (conf.getBoolean("spark.logLineage", false)) {
	      logInfo("RDD's recursive dependencies:\n" + rdd.toDebugString)
	    }
	    dagScheduler.runJob(rdd, cleanedFunc, partitions, callSite, resultHandler, localProperties.get)
	    progressBar.foreach(_.finishAll())
	    rdd.doCheckpoint()
	  }

	  ...

	}
	```

- DAGScheduler中的`runJob()`会调用自身的`submitJob()`方法提交Job，在submitJob()方法中将Job最终post到EventLoop中：

	```scala
	private[spark]
	class DAGScheduler(
	    private[scheduler] val sc: SparkContext,
	    private[scheduler] val taskScheduler: TaskScheduler,
	    listenerBus: LiveListenerBus,
	    mapOutputTracker: MapOutputTrackerMaster,
	    blockManagerMaster: BlockManagerMaster,
	    env: SparkEnv,
	    clock: Clock = new SystemClock())
	  extends Logging {

	  ...

	  /**
	   * Submit an action job to the scheduler.
	   *
	   * @param rdd target RDD to run tasks on
	   * @param func a function to run on each partition of the RDD
	   * @param partitions set of partitions to run on; some jobs may not want to compute on all
	   *   partitions of the target RDD, e.g. for operations like first()
	   * @param callSite where in the user program this job was called
	   * @param resultHandler callback to pass each result to
	   * @param properties scheduler properties to attach to this job, e.g. fair scheduler pool name
	   *
	   * @return a JobWaiter object that can be used to block until the job finishes executing
	   *         or can be used to cancel the job.
	   *
	   * @throws IllegalArgumentException when partitions ids are illegal
	   */
	  def submitJob[T, U](
	      rdd: RDD[T],
	      func: (TaskContext, Iterator[T]) => U,
	      partitions: Seq[Int],
	      callSite: CallSite,
	      resultHandler: (Int, U) => Unit,
	      properties: Properties): JobWaiter[U] = {
	    // Check to make sure we are not launching a task on a partition that does not exist.
	    val maxPartitions = rdd.partitions.length
	    partitions.find(p => p >= maxPartitions || p < 0).foreach { p =>
	      throw new IllegalArgumentException(
	        "Attempting to access a non-existent partition: " + p + ". " +
	          "Total number of partitions: " + maxPartitions)
	    }

	    val jobId = nextJobId.getAndIncrement()
	    if (partitions.size == 0) {
	      // Return immediately if the job is running 0 tasks
	      return new JobWaiter[U](this, jobId, 0, resultHandler)
	    }

	    assert(partitions.size > 0)
	    val func2 = func.asInstanceOf[(TaskContext, Iterator[_]) => _]
	    val waiter = new JobWaiter(this, jobId, partitions.size, resultHandler)
	    eventProcessLoop.post(JobSubmitted(
	      jobId, rdd, func2, partitions.toArray, callSite, waiter,
	      SerializationUtils.clone(properties)))
	    waiter
	  }

	  /**
	   * Run an action job on the given RDD and pass all the results to the resultHandler function as
	   * they arrive.
	   *
	   * @param rdd target RDD to run tasks on
	   * @param func a function to run on each partition of the RDD
	   * @param partitions set of partitions to run on; some jobs may not want to compute on all
	   *   partitions of the target RDD, e.g. for operations like first()
	   * @param callSite where in the user program this job was called
	   * @param resultHandler callback to pass each result to
	   * @param properties scheduler properties to attach to this job, e.g. fair scheduler pool name
	   *
	   * @note Throws `Exception` when the job fails
	   */
	  def runJob[T, U](
	      rdd: RDD[T],
	      func: (TaskContext, Iterator[T]) => U,
	      partitions: Seq[Int],
	      callSite: CallSite,
	      resultHandler: (Int, U) => Unit,
	      properties: Properties): Unit = {
	    val start = System.nanoTime
	    val waiter = submitJob(rdd, func, partitions, callSite, resultHandler, properties)
	    ThreadUtils.awaitReady(waiter.completionFuture, Duration.Inf)
	    waiter.completionFuture.value.get match {
	      case scala.util.Success(_) =>
	        logInfo("Job %d finished: %s, took %f s".format
	          (waiter.jobId, callSite.shortForm, (System.nanoTime - start) / 1e9))
	      case scala.util.Failure(exception) =>
	        logInfo("Job %d failed: %s, took %f s".format
	          (waiter.jobId, callSite.shortForm, (System.nanoTime - start) / 1e9))
	        // SPARK-8644: Include user stack trace in exceptions coming from DAGScheduler.
	        val callerStackTrace = Thread.currentThread().getStackTrace.tail
	        exception.setStackTrace(exception.getStackTrace ++ callerStackTrace)
	        throw exception
	    }
	  }

	  ...

	}
	```



# Spark Streaming
`Spark Streaming`是对核心`Spark API`的扩展，包含了对实时数据流(live data streams)的可扩展(scalable)、高吞吐(high-throughput)、容错性(fault-tolerant)的流式处理。  
数据可从多种数据源中获取，如`Kafka`、`Flume`、`HDFS`或`TCP Socket`，数据能将复杂的算法使用高阶函数表达，如`map()`、`reduce()`、`join()`、`window()`等。  
最终，处理过后的数据可被发布到文件系统、数据库、实时仪表等。  
实际上，可以将Spark的`Machine Learning`(机器学习)和`Graph Processing`(图处理)算法应用于数据流。

![avatar](../../images/spark_streaming_arch.png)

SparkStreaming接收实时的输入数据流并将数据划分批次，每个批次的数据将由Spark引擎处理并在批次中生成最终结果集的流。

![avatar](../../images/spark_streaming_flow.png)

SparkStreaming为一个连续的数据流提供了高层抽象，叫做`DStream`(`discretized stream`，离散流)。  
DStreams可以从多种数据源(如`Kafka`、`Flume`等)的输入数据流创建，或者通过其它DStream的高阶运算得到。  
DStream本质上是一个`RDD`的序列。

## Streaming Context
`Streaming Context`是所有SparkStreaming功能的主要入口点，通过`SparkConf`或已存在的`SparkContext`构建`StreamingContext`实例：

```scala
import org.apache.spark.streaming.{Seconds, StreamingContext}
import org.apache.spark.{SparkConf, SparkContext}

val sparkConf = new SparkConf() {
  setAppName("应用名称...")
  setMaster("spark://xxx:xxx...")
  ...
}

/* 通过 SparkConf 直接构建 StreamingContext 实例
 * 第二参数为生成数据批次的间隔
 */
new StreamingContext(sparkConf, Seconds(1)) {
  /* CheckPoint不设置在运行时会产生异常：
   * java.lang.IllegalArgumentException: requirement failed:
   * The checkpoint directory has not been set. Please set it by StreamingContext.checkpoint().
   */
  checkpoint("hdfs://xxx:xxx...")
  ...
}

/* 获取 SparkContent 实例时，使用伴生对象中的 getOrCreate() 方法
 * 避免分布式场景下多个 SparkContent 实例同时存在发生异常
 */
new StreamingContext(SparkContext.getOrCreate(sparkConf), Seconds(10)) {
  checkpoint("hdfs://xxx:xxx...")
  ...
}
```

通过StreamingContext从不同的数据源构建输入数据的DStream，常见的数据源获取方式如下：

```scala
// 使用 Socket 做为数据源，返回值类型为 org.apache.spark.streaming.dstream.DStream
streamingContext.socketTextStream(...)

// 使用 HDFS 做为数据源
streamingContext.textFileStream(...)
```

## DStream
`DStream`是SparkStreaming提供的基础抽象，表示一串连续的数据流，可以是来自数据源的输入数据流，也可以由其它数据流转换生成。  
实质上，DStream是一组连续的RDD，每个DStream中的RDD包含者来自某个时间间隔的数据，如下所示：

![avatar](../../images/spark_streaming_dstream.png)

DStream中执行的操作将会应用到底层的每个RDD中。  
例如，对DStream1执行`flatMap()`操作得到DStream2，DStream1中的每一个RDD均会通过flatMap()生成新的RDD，并构成DStream2，如下所示：

![avatar](../../images/spark_streaming_dstream_operate.png)

底层的RDD变化由Spark引擎完成计算。DStream操作隐藏了多数的底层细节，给开发者提供了便利的高层次API。

## 数据变换
与RDD类似，DStream允许对输入的数据进行变换操作。
DStream支持多数RDD中可用的变换操作，如`map()`、`flatMap()`、`fliter()`、`reduce()`等，
其中较为特殊的是支持存储状态的`updateStateByKey()`和`mapWithState()`操作。

### updateStateByKey()
`updateStateByKey()`允许保存任意的状态并一直使用数据流中的新数据来更新它。
使用updateStateByKey()需要以下两个步骤：

1. 定义状态，状态可以任意的数据类型。
1. 定义状态更新函数，指定如何根据输入数据和之前的状态来更新状态、输出数据。

updateStateByKey()方法并未直接定义在DStream类型中，而是由`PairDStreamFunctions[K, V]`类型提供，
`PairDStreamFunctions[K, V]`由`DStream[(K, V)]`隐式转换得到，如下所示(源码取自`Spark 2.3.0`)：

```scala
object DStream {

  implicit def toPairDStreamFunctions[K, V](stream: DStream[(K, V)])
      (implicit kt: ClassTag[K], vt: ClassTag[V], ord: Ordering[K] = null):
    PairDStreamFunctions[K, V] = {
    new PairDStreamFunctions[K, V](stream)
  }
  ...
}
```

即调用updateStateByKey()方法的DStream需要为`DStream[(K, V)]`类型。
updateStateByKey()方法包含多个重载，定义如下(源码取自`Spark 2.3.0`)：

```scala
class PairDStreamFunctions[K, V](self: DStream[(K, V)])
  (implicit kt: ClassTag[K], vt: ClassTag[V], ord: Ordering[K]) extends Serializable {
  ...
  def updateStateByKey[S: ClassTag](
    updateFunc: (Seq[V], Option[S]) => Option[S]): DStream[(K, S)] = ...
  def updateStateByKey[S: ClassTag](
    updateFunc: (Seq[V], Option[S]) => Option[S],
    partitioner: Partitioner): DStream[(K, S)] = ...
  def updateStateByKey[S: ClassTag](
    updateFunc: (Seq[V], Option[S]) => Option[S],
    partitioner: Partitioner, initialRDD: RDD[(K, S)]): DStream[(K, S)] = ...
  ...
}
```

方法参数`updateFunc`即为真正的数据处理逻辑，参数类型为：

```scala
(Seq[V], Option[S]) => Option[S]
```

数据处理函数的输入/输出如下：

1. 第一参数为根据Key值归类的值序列，原DStream中Key相同的Value构成`Seq[V]`做为第一输入参数。
1. 第二参数为存储的状态，首次调用为空，之后调用为上一次计算返回的状态。
1. 返回值是更新的状态，下次触发updateStateByKey()方法时相同Key会使用此刻的返回值。

输入数据类型由原DStream的Value类型(`V`)决定，状态类型(`S`)由用户决定。
经过updateStateByKey()处理，生成新的类型为`DStream[(K, S)]`的DStream。

整个计算流程的类型变化关系：

```scala
DStream[(K, V)] => PairDStreamFunctions[K, V] => PairDStreamFunctions.updateStateByKey[S]() => DStream[(K, S)]
```

### mapWithState()
`mapWithState()`直接处理**每一条**数据，通过每一条数据的Key、Value、之前的状态计算出新的数据。

mapWithState()方法同样由`PairDStreamFunctions[K, V]`类型提供，需要原DStream为`DStream[(K, V)]`类型。
截止到`Spark 2.3.0`版本，mapWithState相关API依然带有`@Experimental`注解(实验性的)，定义如下(源码取自`Spark 2.3.0`)：

```scala
class PairDStreamFunctions[K, V](self: DStream[(K, V)])
  (implicit kt: ClassTag[K], vt: ClassTag[V], ord: Ordering[K]) extends Serializable {
  ...
  @Experimental
  def mapWithState[StateType: ClassTag, MappedType: ClassTag](
    spec: StateSpec[K, V, StateType, MappedType]
    ): MapWithStateDStream[K, V, StateType, MappedType] = ...
  ...
}
```

mapWithState()方法接收的参数为`StateSpec`类型，可以使用StateSpec伴生对象中提供的`function()`相关方法构建。
相关方法定义如下(源码取自`Spark 2.3.0`)：

```scala
@Experimental
object StateSpec {
  ...
  def function[KeyType, ValueType, StateType, MappedType](
    mappingFunction: (KeyType, Option[ValueType], State[StateType]) => MappedType
    ): StateSpec[KeyType, ValueType, StateType, MappedType] = ...
  def function[KeyType, ValueType, StateType, MappedType](
    mappingFunction: JFunction3[KeyType, Optional[ValueType], State[StateType], MappedType]
    ): StateSpec[KeyType, ValueType, StateType, MappedType] = ...
  ...
}
```

传入StateSpec.function()的参数`mappingFunction`即为mapWithState()方法真正的处理逻辑，参数类型为：

```scala
(KeyType, Option[ValueType], State[StateType]) => MappedType
```

数据处理函数的输入/输出如下：

1. 第一参数为原DStream中的Key。
1. 第二参数为原DStream中的Value。
1. 第三参数为Key对应存储状态。类型为`State[StateType]`，使用`State.update()`添加、更新状态值，使用`State.remove()`移除状态。
1. 返回值为通过Key、Value、存储状态计算得到的新数据。

KeyType、ValueType实际类型由原DStream决定，存储状态类型StateType、目标数据类型MappedType由用户决定。
经过mapWithState()处理，生成新的类型为`MapWithStateDStream[K, V, StateType, MappedType]`的DStream。

整个计算流程的类型变化关系：

```scala
DStream[(K, V)] => PairDStreamFunctions[K, V] => PairDStreamFunctions.mapWithState[K, V, StateType, MappedType]() => MapWithStateDStream[K, V, StateType, MappedType]
```

`MapWithStateDStream[K, V, StateType, MappedType]`类型继承自`DStream[MappedType]`，
即mapWithState()操作最终生成的是目标数据类型MappedType的DStream。
定义如下所示(源码取自`Spark 2.3.0`)：

```scala
@Experimental
sealed abstract class MapWithStateDStream[KeyType, ValueType, StateType, MappedType: ClassTag](
    ssc: StreamingContext) extends DStream[MappedType](ssc) {
  ...
}
```



# 常见错误
记录Spark开发、使用过程中遇到的错误信息以及对应解决方法。

## Unable to load native-hadoop library for your platform... using builtin-java classes where applicable
错误说明：  
Spark运行环境中已包含了Scala、Hadoop、Zookeeper等依赖，与Jar包中自带的依赖产生冲突。

解决方式：  
开发环境中为确保源码正常编译，需要完整引入Spark相关依赖，但在生成Jar时，需要移除Spark以及相关联的Scala、Hadoop、Zookeeper相关依赖。  

## Operation category READ is not supported in state standby
错误说明：  
配置了NameNode HA的Hadoop集群会存在`active`、`standby`两种状态。  
SparkStreaming使用HDFS为数据源时URL需要使用active节点的主机名。

解决方式：  
登陆HDFS的WEB管理界面查看节点状态，设置HDFS的URL时使用active节点的主机名。

## org.apache.spark.SparkException: Failed to get broadcast_xxx of broadcast_xxx
错误说明：  
在集群模式下执行Spark应用时，多个JVM实例间持有不同的SparkContent实例，导致Worker节点间通信出错。

解决方式：  
避免使用单例模式保存SparkContent实例，单例模式在集群中存在多个JVM实例时不可靠。  
创建SparkContext应在主函数代码中进行，构建SparkContext应使用伴生对象中提供的`SparkContext.getOrCreate()`方法。
