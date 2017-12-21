<!-- TOC -->

- [简介](#简介)
- [*Akka Actor*](#akka-actor)
	- [定义 *Actor*](#定义-actor)

<!-- /TOC -->



## 简介
`Akka`是一套用于构建**弹性**(scalable)、**可扩展**(resilient)、**分布式**(distributed)系统的开源库。  
Akka让用户专注于**业务需求**(business needs)，而非编写底层代码来提供**可靠的行为**(reliable behavior)、**容错性**(fault tolerance)、**高性能**(high performance)。



## *Akka Actor*
`Akka`提供了`Actor`模型在`JVM`上的实现。

Actor模型为编写高并发、分布式系统提供了高级的抽象。  
Actor模型缓解了并发编程中的锁和线程管理等问题，让开发者能够简单、正确地构建并行系统。

Actor模型最初由`Carl Hewitt`在`1973`年的论文中提出，之后由`Ericsson`开发的`Erlang`实现，在构建高并发、高可靠性的电信系统中有着成功的应用。  
`Akka Actor`提供了与`Erlang Actor`类似的语法。

Akka Actor现在是`Lightbend`官方推荐的Actor实现，原先标准库中提供的`Scala Actor`在`Scala 2.10`版本后已被废弃。

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

自定义Actor应重写`receive`方法，`receive`方法为无参方法，返回值类型为`akka.actor.Actor.Receive`，定义在Actor特质的伴生对象中：

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

`Actor.Receive`类型实际为`Any => Unit`形式的**偏函数**。
