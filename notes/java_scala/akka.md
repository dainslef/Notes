<!-- TOC -->

- [简介](#简介)
- [*Akka Actor*](#akka-actor)
	- [配置 *Akka Actor*](#配置-akka-actor)
	- [定义 *Actor*](#定义-actor)
	- [创建 *Actor*](#创建-actor)

<!-- /TOC -->



## 简介
`Akka`是一套用于构建**弹性**(scalable)、**可扩展**(resilient)、**分布式**(distributed)系统的开源库。  
Akka让用户专注于**业务需求**(business needs)，而非编写底层代码来提供**可靠的行为**(reliable behavior)、**容错性**(fault tolerance)、**高性能**(high performance)。



## *Akka Actor*
`Akka Actor`提供了`Actor`模型在`JVM`上的实现。

Actor模型为编写高并发、分布式系统提供了高级的抽象。  
Actor模型缓解了并发编程中的锁和线程管理等问题，让开发者能够简单、正确地构建并行系统。

Actor模型最初由`Carl Hewitt`在`1973`年的论文中提出，之后由`Ericsson`开发的`Erlang`实现，在构建高并发、高可靠性的电信系统中有着成功的应用。  
`Akka Actor`提供了与`Erlang Actor`类似的语法。

Akka Actor现在是`Lightbend`官方推荐的Actor实现，原先标准库中提供的`Scala Actor`在`Scala 2.10`版本后已被废弃。

### 配置 *Akka Actor*
在sbt项目的`build.sbt`中添加依赖：

```scala
"com.typesafe.akka" %% "akka-actor" % "版本号"
```

### 定义 *Actor*
在包路径`akka.actor`下定义了Actor的相关类型。  
自定义Actor应继承/混入`akk.actor.Actor`特质，如下所示：

```scala
import akka.actor.Actor

class MyActor extends Actor {

  def receivce: Receive = {
    case ... => ...
    case _ => ...
  }

}
```

自定义Actor应重写`receive`方法，在receive方法中提供消息处理逻辑。  
receive方法为无参方法，返回值类型为`akka.actor.Actor.Receive`。  
定义在Actor特质的伴生对象中：

```scala
object Actor {
  ...
  /**
   * Type alias representing a Receive-expression for Akka Actors.
   */
  //#receive
  type Receive = PartialFunction[Any, Unit]
  ...
}
```

`Actor.Receive`类型实际为`Any => Unit`签名的**偏函数**。

### 创建 *Actor*
自定义的Actor类型子类并不能直接构造实例使用，而是需要通过`ActorSystem`管理、创建出对应的`ActorRef`引用进行操作。

使用`ActorSystem`与`Props`创建`ActorRef`，基本代码如下所示：

```scala
import akka.actor._

val actorSystem = ActorSystem()
val xxxActor = actorSystem.actorOf(Props[XxxActor])
...
```

`ActorSystem`类提供了对Actor的管理、调度。  
创建ActorRef需要首先构建ActorSystem实例，ActorSystem类的伴生对象提供了`apply()`方法用于构建实例：

```scala
object ActorSystem {
  ...
  def apply(): ActorSystem = apply("default")
  def apply(name: String): ActorSystem
  def apply(name: String, setup: ActorSystemSetup): ActorSystem
  ...
}
```

不同的ActorSystem以名字作为区分，不填写名称参数时，默认名称为`default`。  
ActorSystem有较大系统开销，不应反复构造过多的ActorSystem实例。

`Props`类提供了Actor的配置。  
无构造器参数的Actor可直接使用Props伴生对象中的空参`apply()`方法生成默认Actor配置，
构造器带有参数的Actor应使用Props伴生对象中的其它`apply()`方法的重载形式，显式传入构造器参数/Actor实例构造Props配置。  
相关方法定义如下：

```scala
object Props extends AbstractProps {
  ...
  def apply[T <: Actor: ClassTag](): Props
  def apply[T <: Actor: ClassTag](creator: ⇒ T): Props
  def apply(clazz: Class[_], args: Any*): Props
  ...
}
```

构建Props实例如下所示：

```scala
class MyActor extends Actor {

  def this(xxx: String) {
    this
    ...
  }

}

val props = Props[MyActor] //使用无参构造器
val propsWithArgs = Props(classOf[MyActor], "xxxx") //使用参数有参构造器
val propsWithInstance = Props(new MyActor("xxxx")) //直接使用Actor实例
```

ActorSystem类继承了ActorRefFactory特质，该特质提供了`actorOf()`方法，可通过Props实例构建对应的ActorRef，相关方法定义如下：

```scala
abstract class ActorSystem extends ActorRefFactory {
  ...
}

trait ActorRefFactory {
  ...
  def actorOf(props: Props): ActorRef
  def actorOf(props: Props, name: String): ActorRef
  ...
}
```

除了直接通过ActorSystem创建顶层ActorRef外，亦可在Actor定义内部创建ActorRef。

`Actor`类型内定义了隐式成员`content`，通过content成员可以获取当前Actor的`ActorContent`实例，通过ActorContent实例的`actorOf()`方法可创建新的`ActorRef`。  
`ActorContent`特质继承了`ActorRefFactory`特质，ActorRefFactory特质中同样定义了`actorOf()`方法用于创建`ActorRef`。  
相关源码如下：

```scala
trait Actor {
  ...
  implicit val context: ActorContext //通过 context 成员获取 ActorContent 实例
  ...
}

trait ActorContext extends ActorRefFactory {
  ...
}

trait ActorRefFactory {
  ...
  def actorOf(props: Props): ActorRef
  def actorOf(props: Props, name: String): ActorRef
  ...
}
```
