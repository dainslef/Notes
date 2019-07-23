- [簡介](#簡介)
- [Akka Actor](#akka-actor)
	- [配置 Akka Actor](#配置-akka-actor)
	- [定義 Actor](#定義-actor)
	- [創建 Actor](#創建-actor)
- [問題註記](#問題註記)
	- [Akka HTTP 文件緩存問題](#akka-http-文件緩存問題)



# 簡介
`Akka`是一套用於構建**彈性**(scalable)、**可擴展**(resilient)、**分佈式**(distributed)系統的開源庫。  
Akka讓用戶專注於**業務需求**(business needs)，而非編寫底層代碼來提供**可靠的行爲**(reliable behavior)、**容錯性**(fault tolerance)、**高性能**(high performance)。



# Akka Actor
`Akka Actor`提供了`Actor`模型在`JVM`上的實現。

Actor模型爲編寫高併發、分佈式系統提供了高級的抽象。  
Actor模型緩解了併發編程中的鎖和線程管理等問題，讓開發者能夠簡單、正確地構建並行系統。

Actor模型最初由`Carl Hewitt`在`1973`年的論文中提出，之後由`Ericsson`開發的`Erlang`實現，
在構建高併發、高可靠性的電信系統中有着成功的應用。  
`Akka Actor`提供了與`Erlang Actor`類似的語法。

`Akka Actor`現在是`Lightbend`官方推薦的Actor實現，原先標準庫中提供的`Scala Actor`在`Scala 2.10`版本後已被廢棄。

## 配置 Akka Actor
在sbt項目的`build.sbt`中添加依賴：

```scala
"com.typesafe.akka" %% "akka-actor" % "版本號"
```

## 定義 Actor
在包路徑`akka.actor`下定義了Actor的相關類型。  
自定義Actor應繼承/混入`akk.actor.Actor`特質，如下所示：

```scala
import akka.actor.Actor

class MyActor extends Actor {

  def receivce: Receive = {
    case ... => ...
    case _ => ...
  }

}
```

自定義Actor應重寫`receive`方法，在receive方法中提供消息處理邏輯。  
receive方法爲無參方法，返回值類型爲`akka.actor.Actor.Receive`。  
定義在Actor特質的伴生對象中：

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

`Actor.Receive`類型實際爲`Any => Unit`簽名的**偏函數**。

## 創建 Actor
自定義的Actor類型子類並不能直接構造實例使用，而是需要通過`ActorSystem`管理、創建出對應的`ActorRef`引用進行操作。

使用`ActorSystem`與`Props`創建`ActorRef`，基本代碼如下所示：

```scala
import akka.actor._

val actorSystem = ActorSystem()
val xxxActor = actorSystem.actorOf(Props[XxxActor])
...
```

`ActorSystem`類提供了對Actor的管理、調度。  
創建ActorRef需要首先構建ActorSystem實例，ActorSystem類的伴生對象提供了`apply()`方法用於構建實例：

```scala
object ActorSystem {
  ...
  def apply(): ActorSystem = apply("default")
  def apply(name: String): ActorSystem
  def apply(name: String, setup: ActorSystemSetup): ActorSystem
  ...
}
```

不同的ActorSystem以名字作爲區分，不填寫名稱參數時，默認名稱爲`default`。  
ActorSystem有較大系統開銷，不應反覆構造過多的ActorSystem實例。

`Props`類提供了Actor的配置。  
無構造器參數的Actor可直接使用Props伴生對象中的空參`apply()`方法生成默認Actor配置，
構造器帶有參數的Actor應使用Props伴生對象中的其它`apply()`方法的重載形式，
顯式傳入構造器參數/Actor實例構造Props配置。  
相關方法定義如下：

```scala
object Props extends AbstractProps {
  ...
  def apply[T <: Actor: ClassTag](): Props
  def apply[T <: Actor: ClassTag](creator: ⇒ T): Props
  def apply(clazz: Class[_], args: Any*): Props
  ...
}
```

構建Props實例如下所示：

```scala
class MyActor extends Actor {

  def this(xxx: String) {
    this
    ...
  }

}

val props = Props[MyActor] //使用無參構造器
val propsWithArgs = Props(classOf[MyActor], "xxxx") //使用參數有參構造器
val propsWithInstance = Props(new MyActor("xxxx")) //直接使用Actor實例
```

ActorSystem類繼承了`ActorRefFactory`特質，該特質提供了`actorOf()`方法，
可通過Props實例構建對應的ActorRef，相關方法定義如下：

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

除了直接通過ActorSystem創建頂層ActorRef外，亦可在Actor定義內部創建ActorRef。

`Actor`類型內定義了隱式成員`content`，通過content成員可以獲取當前Actor的`ActorContent`實例，
通過ActorContent實例的`actorOf()`方法可創建新的`ActorRef`。  
`ActorContent`特質繼承了`ActorRefFactory`特質，ActorRefFactory特質中同樣定義了`actorOf()`方法用於創建`ActorRef`。  
相關源碼如下：

```scala
trait Actor {
  ...
  implicit val context: ActorContext //通過 context 成員獲取 ActorContent 實例
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



# 問題註記
記錄一些Akka開發中遇到的問題。

## Akka HTTP 文件緩存問題
問題描述：  
使用Akka HTTP返回本地文件做爲請求響應時，Tomcat會在`/tmp/tomcat...`路徑下緩存該文件。
當本地文件內容更新後，Akka HTTP依舊返回Tomcat緩存路徑中的舊文件，請求端依舊得到舊文件。

解決方案：  
刪除Tomcat緩存目錄`/tmp/tomcat...`。
