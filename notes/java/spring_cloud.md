<!-- TOC -->

- [概述](#概述)
- [Spring Cloud 版本](#spring-cloud-版本)
	- [依賴管理](#依賴管理)
- [Spring Cloud Netfix](#spring-cloud-netfix)
	- [Eureka](#eureka)
		- [Eureka Server](#eureka-server)
		- [Eureka Client](#eureka-client)
		- [Eureka Event](#eureka-event)
	- [Zuul](#zuul)
		- [保留前綴父級路徑URL](#保留前綴父級路徑url)
		- [Sensitive Headers](#sensitive-headers)
		- [ZuulFilter](#zuulfilter)
		- [HandlerInterceptorAdapter 與 ZuulFilter](#handlerinterceptoradapter-與-zuulfilter)
		- [CrossOrigin (跨域問題)](#crossorigin-跨域問題)
- [Spring Cloud Config](#spring-cloud-config)
	- [Config Server](#config-server)
	- [Config Client](#config-client)
	- [公共配置](#公共配置)
	- [自動發現配置中心](#自動發現配置中心)
	- [@RefreshScope](#refreshscope)
	- [手動刷新配置](#手動刷新配置)
	- [客戶端配置自動刷新](#客戶端配置自動刷新)
	- [Config Server WEB API 與整合 Eureka Server](#config-server-web-api-與整合-eureka-server)
- [Spring Cloud Stream](#spring-cloud-stream)
	- [依賴配置](#依賴配置)
	- [應用結構](#應用結構)
	- [Sink & Source](#sink--source)
	- [自定義管道](#自定義管道)
	- [MessageChannel](#messagechannel)
	- [消息結構](#消息結構)

<!-- /TOC -->



# 概述
`Spring Cloud`為開發者提供了套件，用於快速構建分佈式系統的公共部分(如配置管理、服務發現、熔斷、智能路由、微代理、
控制總綫、全局鎖、選舉、分佈式Session、集羣狀態等)。
分佈式服務的協作通常遵循某些樣板模式，使用Spring Cloud的開發者能夠快速地構建實現這些模式的服務和應用。
Spring Cloud能夠很好地運行在任何分佈式平臺，包括開發者自己的筆記本電腦，裸機數據中心，以及託管平臺(如Cloud Foundry)。

具體可查閲[`Spring Cloud官方文檔`](https://cloud.spring.io/spring-cloud-static/spring-cloud.html)。



# Spring Cloud 版本
與Spring Boot不同，Spring Cloud組件版本不使用數字版本號，而使用版本代號，因爲相同Spring Cloud大版本下各個子組件的版本并不統一。

Spring Cloud版本號遵循`版本代號.SRx`的結構，版本代號是一系列首字母按照羅馬字母順序排佈的單詞
(`Angel`為首個版本，`Brixton`為第二個版本，以此類推)，`SRx`代表`service releases`，`x`是數字，
表示服務更新，主要包括安全性維護、BUG修復等。
以當前(2019-5-29)的最新穩定版爲例，版本號為`Greenwich.SR1`，即第七個大版本，第一個service release版本。

每個版本代號需要搭配匹配的Spring Boot版本才能正常工作(即項目的parent需要為版本匹配的Spring Boot)：

| Spring Cloud | Spring Boot |
| :- | :- |
| Greenwich | 2.1.x |
| Finchley | 2.0.x |
| Edgware | 1.5.x |
| Dalston | 1.5.x |

## 依賴管理
與Spring Boot類似，Spring Cloud同樣存在公用的基礎依賴，並以此決定各個組件的版本。

Spring Cloud的組件版本通過`spring-cloud-dependencies`包進行設定，在Maven中添加：

```xml
<!-- Spring Cloud base dependency -->
<dependencyManagement>
	<dependencies>
		<dependency>
			<groupId>org.springframework.cloud</groupId>
			<artifactId>spring-cloud-dependencies</artifactId>
			<version>{spring-cloud-version}</version>
			<type>pom</type>
			<scope>import</scope>
		</dependency>
	</dependencies>
</dependencyManagement>
```

添加依賴后，Spring Cloud相關組件不必再逐一指定版本號，統一由spring-cloud-dependencies決定。



# Spring Cloud Netfix
`Spring Cloud Netflix`項目提供了對Netfix服務的Spring Boot集成，包括：

- `Eureka`(Service Discovery，服務發現)
- `Hystrix`(Circuit Breaker，熔斷器)
- `Zuul`(Intelligent Routing，智能路由)
- `Ribbon`(Client Side Load Balancing，客戶端負載均衡)

詳細介紹可查閲[Spring Cloud Netfix官方文檔](https://cloud.spring.io/spring-cloud-netflix/spring-cloud-netflix.html)。

## Eureka
Eureka分爲Client和Server兩部分，Server提供注冊服務，Client向Server進行注冊。
Client會定期向Server發送心跳包告知服務的存活狀態。

### Eureka Server
在Maven中引入以下依賴：

```xml
<!-- Eureka Client -->
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-netflix-eureka-server</artifactId>
</dependency>

<!-- Eureka need Spring Cloud Config Client -->
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-config</artifactId>
</dependency>
```

在項目的`application.yaml`中配置Eureka Server的服務信息：

```yaml
# 設定 Eureka Server 的服務端口
server.port: xxxx

eureka.client:
  # Standalone Mode，關閉 Eureka Server 自身的服務註冊
  registerWithEureka: false
  fetchRegistry: false
```

Eureka Server自身亦是Eureka Client，默認配置下同樣要求一個Eureka Server來註冊並維持心跳
(未配置依然可運行，但會定期彈出告警信息)，
可以使用配置自身的服務關閉註冊(Standalone Mode)或者使用自身地址進行註冊。

在Spring Boot配置類上添加`@EnableEurekaServer`註解即可啓用Eureka Server：

```kt
import org.springframework.boot.SpringApplication
import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.cloud.netflix.eureka.server.EnableEurekaServer

@SpringBootApplication
@EnableEurekaServer
class ServerConfig

fun main(args: Array<String>) {
    SpringApplication.run(ServerConfig::class.java, *args)
}
```

Eureka Server的服務URL爲`http://主機ip:配置端口/eureka/`。
Eureka Server的提供了WBE UI來展示已註冊服務的狀態，URL爲`http://主機ip:配置端口`。

### Eureka Client
在Maven中引入以下依賴：

```xml
<!-- Eureka Client -->
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-netflix-eureka-client</artifactId>
</dependency>

<!-- Eureka need Spring Cloud Config Client -->
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-config</artifactId>
</dependency>
```

在項目的`application.yaml`中配置Eureka Client的連接、應用名：

```yaml
eureka.client.service-url.defaultZone: http://Eureka主機ip:服務端口/eureka/ # 設定需要註冊的 Eureka Server 地址
spring.application.name: xxx # 設置應用名稱，默認配置下，應用名稱會用於生成 Eureka Client ID
```

在配置類中注入`EurekaClient`類型的Bean：

```kt
import com.netflix.discovery.EurekaClient
import org.springframework.boot.SpringApplication
import org.springframework.boot.autoconfigure.SpringBootApplication

@SpringBootApplication
class ClientConfig {

    // 注入 EurekaClient
    @Autowired
    lateinit var client: EurekaClient

}

fun main(args: Array<String>) {
    SpringApplication.run(ClientConfig::class.java, *args)
}
```

`import com.netflix.discovery.EurekaClient`是Eureka直接提供的客戶端類型，
Spring Cloud Netfix還提供了更加通用的`org.springframework.cloud.client.discovery.DiscoveryClient`類型，
接口相對更加簡單：

```kt
import org.springframework.boot.SpringApplication
import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.cloud.client.discovery.DiscoveryClient

@SpringBootApplication
class ClientConfig {

    // 注入 DiscoveryClient
    @Autowired
    lateinit var client: DiscoveryClient

}

fun main(args: Array<String>) {
    SpringApplication.run(ClientConfig::class.java, *args)
}
```

### Eureka Event
Spring Eureka組件會為實例在生命周期的各個階段均會發送不同類型的Spring事件(`ApplicationEvent`的子類)：

- `EurekaInstanceRenewedEvent` 實例續約事件
- `EurekaInstanceRegisteredEvent` 實例注冊事件
- `EurekaInstanceCanceledEvent` 實例下綫事件
- `EurekaRegistryAvailableEvent` 注冊服務可用事件
- `EurekaServerStartedEvent` Eureka Server啓動事件

相關事件触发源碼位於`org.springframework.cloud.netflix.eureka.server.InstanceRegistry`文件中。
可使用`@EventListener`注解修飾方法進行監聽：

```kt
import org.springframework.cloud.netflix.eureka.server.event.*
import org.springframework.context.annotation.Configuration
import org.springframework.context.event.EventListener

@Configuration
class EurekaEventHandler {

    @EventListener
    fun listen(event: EurekaInstanceCanceledEvent) {
        ...
    }

    @EventListener
    fun listen(event: EurekaInstanceRegisteredEvent) {
        ...
    }

    ...

}
```

在Spring Cloud Finchley/Greenwich等版本中，Spring Eureka發送的事件與EurekaClient提供的注冊信息并非**實時同步**更新。
當EventListener接收到事件通知時，此時Eureka Client中的注冊信息仍然是舊的，通常需要等待5s以上注冊信息才會同步變化。

## Zuul
路由是微服務體系中的一個組成部分，`Zuul`提供了基於JVM的路由和服務端的負載均衡。

使用Zuul，在Maven中引入以下依賴：

```xml
<!-- Zuul -->
<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-starter-netflix-zuul</artifactId>
    <version>${spring-boot-version}</version>
</dependency>
```

在配置了Eureka的微服務集羣中，Zuul可通過應用名稱查找到指定的服務，並實現路由轉發。
在`application.yaml`中添加路由配置：

```yaml
zuul.routes:
  應用名稱1: /Xxx1/**
  應用名稱2: /Xxx2/**
  ...
```

簡單的路由配置可直接為一個應用添加一個前置路徑層級，向Zuul發送的請求的URL匹配到對應的路由則會被轉發到對應名稱的應用。

Zuul支持更細粒度的路由控制：

```yaml
zuul.routes:
  路由名稱:
    path: /Xxx/**
    serviceId: 應用名稱
```

### 保留前綴父級路徑URL
默認的轉發規則下，用作匹配標識的前綴在轉發到目標服務後會被丟棄，若需保留前綴，則使用如下配置：

```yaml
zuul.routes:
  路由名稱:
    path: /Xxx/**
    serviceId: 應用名稱
    stripPrefix: false
```

### Sensitive Headers
Zuul在轉發請求時會丟棄敏感信息相關請求頭，設定`zuul.sensitiveHeaders`配置項可設定全局的敏感信息頭，
默認的請求頭配置為：

```yaml
zuul.sensitiveHeaders: Cookie,Set-Cookie,Authorization
```

`zuul.sensitiveHeaders`配置項是**黑名單**(blacklist)，
即默認配置下，`Cookie`、`Set-Cookie`、`Authorization`三個請求頭在轉發時會被丟棄。
以Cookie被丟棄爲例，使用Spring Session等分佈式Session解決方案時，會導致Zuul轉發的目標模塊無法正確獲取到Session實例。

在轉發時要保留所有認證信息，將該配置項置空即可：

```yaml
zuul.sensitiveHeaders:
```

還可配置指定服務的轉發、保留敏感信息請求頭：

```yaml
zuul.routes:
  路由名稱:
    path: /Xxx/**
    serviceId: 應用名稱
    sensitiveHeaders: ...
```

### ZuulFilter
`ZuulFilter`提供了在轉發請求時對請求進行額外處理、攔截請求等功能。

ZuulFilter使用方式類似Spring攔截器，繼承ZuulFilter類，重寫相關方法，並提供Bean即可：

```kt
import javax.ws.rs.core.MediaType

import com.netflix.zuul.ZuulFilter
import com.netflix.zuul.context.RequestContext

import org.springframework.cloud.netflix.zuul.filters.support.FilterConstants.PRE_TYPE
import org.springframework.context.annotation.Configuration

@Configuration
class CustomFilter : ZuulFilter() {

    override fun shouldFilter() = true // 在過濾器的run()方法前執行，判斷run()方法是否需要執行
    override fun filterType() = PRE_TYPE // 過濾器類型
    override fun filterOrder() = 0 // 過濾器的執行優先級

    // 過濾器核心邏輯
    override fun run() {
        RequestContext.getCurrentContext()?.apply {
            ...
            setSendZuulResponse(...) // 通過該方法控制請求是否可被進一步轉發
            ...
        }
    }

}
```

### HandlerInterceptorAdapter 與 ZuulFilter
Zuul監控、轉發的請求運行在獨立的ZuulServlet中，
因而Spring MVC提供的攔截器`HandlerInterceptorAdapter`不會對Zuul管理、轉發的請求生效。
Zuul監聽的相關請求**不會**觸發Spring MVC提供的攔截器。

在Zuul中，過濾/攔截相關功能需要使用`ZuulFilter`。

相關問題參考StackOverflow上的[**對應提問**](`https://stackoverflow.com/questions/39801282/handlerinterceptoradapter-and-zuul-filter`)。

### CrossOrigin (跨域問題)
使用Zuul轉發請求的模塊同樣需要處理跨域問題，要正確實現轉發跨域請求，需要滿足：

- 目標模塊需要在自身控制器類中添加`@CrossOrigin(allowCredentials = "true")`注解。
- Zuul自身提供`CorsFilter`的Bean來允許請求的跨域轉發。

CorsFilter示例：

```kt
import org.springframework.web.cors.CorsConfiguration
import org.springframework.web.cors.UrlBasedCorsConfigurationSource
import org.springframework.context.annotation.Configuration

@Configuration
class XxxConfig {

    ...

    @Bean
    fun corsFilter() = CorsFilter(UrlBasedCorsConfigurationSource().apply {
        registerCorsConfiguration("/**", CorsConfiguration().apply {
            allowCredentials = true //在請求回應中設置允許跨域
            addAllowedOrigin("*") //設置允許的源
            addAllowedHeader("*") //設置允許的請求頭
            addAllowedMethod("*") //設置允許的方法
        })
    })

    ...

}
```



# Spring Cloud Config
Spring Cloud Config提供了對分佈式系統的外部配置文件支持，包括客戶端和服務端。

詳細介紹可查閲[Spring Cloud Config官方文檔](https://cloud.spring.io/spring-cloud-config/spring-cloud-config.html)。

## Config Server
在Maven中引入以下依賴：

```xml
<!-- Config Server -->
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-config-server</artifactId>
</dependency>
```

在Spring Boot配置類上添加`@EnableConfigServer`註解即可開啓Config Server功能。

Config Server支持多種模式，最簡單的是`native`模式，直接將文件系統中的某個路徑作爲配置目錄。
在Config Server的`application.yaml`寫入配置：

```yaml
spring:
  profiles.active: native # 設置 Config Server 為 native 模式
  cloud.config.server.native.search-locations: classpath:/ # 指定配置路徑
```

放置配置路徑下所有符合規範的`properties/yaml`文件會被作爲配置對外提供。
配置路徑下的配置文件應遵循`${spring.cloud.config.name}-${spring.cloud.config.profile}.yaml`的命名規範。

Config Server提供了Monitor組件，用於監測配置文件的變化，在Maven中引入依賴：

```xml
<!-- Monitor can discover files which are motified -->
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-config-monitor</artifactId>
</dependency>
```

Monitor組件依賴了`Spring Cluoud DBus`組件，通過該組件進行配置變化信息的推送。
而DBus又依賴于`Spring Cloud Stream`組件，需要添加具體的Stream後端，否則運行時會出現如下錯誤：

```
...
Cannot create binder factory, no `META-INF/spring.binders` resources found on the classpath
```

Spring Cluoud Stream支持多種後端，如官方默認的`RabbitMQ`：

```xml
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-stream-rabbit</artifactId>
</dependency>
```

若集羣中已配置了`Kafka`，則推薦使用對應依賴：

```xml
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-stream-kafka</artifactId>
</dependency>
```

配置對應的Stream後端之後，在配置中添加對應消息隊列的連接配置，以Kafka爲例：

```yaml
spring.cloud.stream.kafka.binder.brokers: ...
```

## Config Client
在Maven中引入以下依賴：

```xml
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-config</artifactId>
</dependency>
```

使用Config Client無需額外代碼，只需要修改配置，相關默認配置：

```yaml
spring.cloud.config:
  name: ${spring.application.name} # 配置的應用名稱
  profile: ${spring.profiles.active} # 配置的profile名稱
  uri: http://localhost:8888/ # 配置服務地址
```

修改配置時需要注意，以上配置寫入`application.yaml`中**不生效**，應寫入`bootstrap.yaml`文件中。
Config Server的配置目錄中需要存在名稱為`${spring.cloud.config.name}-${spring.cloud.config.profile}.yaml`的配置文件。

## 公共配置
以`application*`為前綴的配置文件(application.properties, application.yml, application-*.properties等)，
會在所有客戶端之間共享，所有客戶端之間公用的重複配置可以直接寫在其中。

公共配置中的配置項優先級低，可被應用特定的配置內容重寫。

在使用`native`模式時，需要指定配置搜索路徑(`spring.cloud.config.server.native.search-locations`)為Config Server配置路徑外的位置。
若配置搜索路徑在Config Server中，則相關的`application*`文件不會被視爲公共配置，因爲這些配置屬於Config Server。

## 自動發現配置中心
Config Client與Eureka一同使用時，可直接通過`service-id`查找到配置中心，
將service-id設置為Config Server應用名稱(`spring.application.name`)即可。

```yaml
spring.cloud.config.discovery:
  # when use Eureka, you can use service-id to find Spring Cloud Server, instead of hard code in config file
  enabled: true
  service-id: 配置中心的${spring.application.name}
```

自動發現相關配置內容同樣需要寫入`bootstrap.yaml`文件中。

## @RefreshScope
Config Client中的配置默認僅在初始化時加載一次，若需要實現配置熱更新，則需要搭配`@RefreshScope`註解，
被該註解修飾的配置類注入的配置能夠實現動態更新。

`@RefreshScope`註解的詳細介紹，參考[`Spring Cloud官方文檔`](https://projects.spring.io/spring-cloud/spring-cloud.html#_refresh_scope)。

> @RefreshScope works (technically) on an @Configuration class, but it might lead to surprising behaviour: e.g. it does not mean that all the @Beans defined in that class are themselves @RefreshScope. Specifically, anything that depends on those beans cannot rely on them being updated when a refresh is initiated, unless it is itself in @RefreshScope (in which it will be rebuilt on a refresh and its dependencies re-injected, at which point they will be re-initialized from the refreshed @Configuration).

@RefreshScope通常用於@Configuration修飾的類中，但可能會導致意外的行爲：
不是所有定義在@RefreshScope範圍內的Bean都會自動更新，典型的，在一次refresh完成後，Bean依賴的內容不會被更新，
除非該內容的定義也被@RefreshScope修飾。

## 手動刷新配置
在Config Client端添加執行器組件：

```xml
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-actuator</artifactId>
</dependency>
```

修改`bootstrap.yaml`文件，導出用於配置更新的Rest API：

```yaml
management.endpoints.web.exposure.include: health,info,refresh
```

向需要刷新配置的客戶端的`actuator/refresh`路徑發送POST請求即可實現手動刷新：

```
$ curl -X POST http://localhost:xxxx/actuator/refresh
```

## 客戶端配置自動刷新
Config Server配置Moniter，可實現服務端配置自動刷新，並將變化的信息通過`Spring Cloud DBus`向外廣播。
Config Client通過配置Spring Cloud DBus，訂閲指定Channel的消息，可實現配置自動刷新。

使用Kafka作爲DBus後端，Config Client需要引入以下依賴：

```xml
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-bus-kafka</artifactId>
</dependency>
```

使用RabbitMQ作爲DBus後端，Config Client需要引入以下依賴：

```xml
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-bus-amqp</artifactId>
</dependency>
```

在`application.yaml`中添加對應DBus後端的連接配置即可運行。

在`Spring Cloud Finchley/Greenwich`版本中，Spring Cloud DBus的實現存在BUG，
Config Client訂閲的Channel ID與Config Server發送配置變化消息的Channel ID默認生成規則不同，
會導致Config Client訂閲錯誤的Channel，進而Config Server端正常發現配置變化並推送DBus消息時，
Config Client卻端未收到任何消息。
解決方案是手動指定Client Config的DBus ID，在`application.yaml`中添加配置：

```yaml
spring.cloud.bus.id: ${vcap.application.name:${spring.application.name:application}}:${vcap.application.instance_index:${spring.profiles.active:${local.server.port:${server.port:0}}}}:${vcap.application.instance_id:${random.value}}
```

## Config Server WEB API 與整合 Eureka Server
Config Server配置完成后，會通過WEB API對外提供服務：

```
/{application}.yml
/{application}/{profile}[/{label}]
/{application}-{profile}.yml
/{label}/{application}-{profile}.yml
/{application}-{profile}.properties
/{label}/{application}-{profile}.properties
```

默認的WEB API規則会將符合以上規則的URL視爲對配置的訪問。

Eureka Server和Config Server可以進行整合，在配置類中同時添加`@EnableEurekaServer`和`@EnableConfigServer`即可。
Config Server與Eureka Server進行整合後，會導致Eureka Server提供的Web UI中CSS樣式錯誤。
因而Eureka Server Web UI中的CSS和JS請求均會被作爲對配置的請求，進而造成頁面需要的資源失效。

解決方案是為Config Server相關請求添加前綴，隔離Config Server相關請求，避免幹擾Eureka相關請求。
在Config Server的`application.yaml`中添加：

```yaml
spring.cloud.config.server.prefix: /config # 為所有 Config Server 的請求添加 /config 前綴
```



# Spring Cloud Stream
`Spring Cloud Stream`是用於構建消息驅動(message-driven)的微服務框架。
Spring Cloud Stream支持多種主流的消息隊列實現，如Kafka、RabbitMQ等，為不同的消息隊列實現提供了一套公用的API。

更多介紹可查閲[Spring Cloud Stream官方文檔](https://cloud.spring.io/spring-cloud-stream/spring-cloud-stream.html)。

## 依賴配置
在Spring Boot項目中配置Spring Cloud的基礎依賴，然後添加Spring Cloud Stream對應的starter依賴。
不同的消息隊列後端擁有不同的starter，以Kafka爲例：

```xml
<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-starter-stream-kafka</artifactId>
</dependency>
```

其它消息隊列類似，`RabbitMQ`依賴即爲`spring-cloud-starter-stream-rabbit`。

## 應用結構
Spring Cloud Stream應用通過`input/output`兩類消息管道(channel)經過`Binder`與外部消息隊列相連。
對於不同的消息隊列，Binder擁有各自特定的實現，但對外提供一致的接口。

Spring Cloud Stream官方文檔中給出了應用結構的圖示：

![Spring Cloud Stream Application Model](../../images/spring-cloud-stream-application-model.png)

## Sink & Source
Spring Cloud Stream中提供了預定義的消息通道：

- `org.springframework.cloud.stream.messaging.Source` 消息發佈端，對應管道名稱`output`
- `org.springframework.cloud.stream.messaging.Sink` 消息接收端，對應管道名稱`input`

在`application.yaml`中加入管道消息發佈端和接收端綁定：

```yaml
spring.cloud.stream.bindings: # 設定管道
  output: # 消息發佈管道
    destination: input # 消息接收管道，一個的消息可以存在多個消息
```

使用`@EnableBinding(Source.class)`注解修飾配置類，注入Source類型實例，即可通過該實例向管道中發送消息：

```kt
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.messaging.support.GenericMessage
import org.springframework.cloud.stream.annotation.EnableBinding
import org.springframework.cloud.stream.messaging.Source

@EnableBinding(Source::class)
class MessageSender {

    @Autowired
    private lateinit var source: Source

    fun sendMessage(message: String) {
        source.output().send(GenericMessage(message))
    }

}
```

使用`@EnableBinding(Sink.class)`注解修飾配置類，使用`@StreamListener`注解修飾指定方法，
被修飾的方法會在消息到達時被回調：

```kt
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.messaging.support.GenericMessage
import org.springframework.cloud.stream.annotation.EnableBinding
import org.springframework.cloud.stream.annotation.StreamListener
import org.springframework.cloud.stream.messaging.Sink

@EnableBinding(Sink::class)
class MessageReceiver {

    @StreamListener(Sink.INPUT)
    fun receiveMessage(message: String) {
        ...
    }

}
```

`@EnbaleBinding`注解可以同時綁定多個管道配置，包括輸入/輸出配置：

```kt
import org.springframework.beans.factory.annotation.Autowired
import org.springframework.messaging.support.GenericMessage
import org.springframework.cloud.stream.annotation.EnableBinding
import org.springframework.cloud.stream.annotation.StreamListener
import org.springframework.cloud.stream.messaging.Sink
import org.springframework.cloud.stream.messaging.Source

@EnableBinding(Sink::class, Source::class)
class MessageReceiver {

    @Autowired
    private lateinit var source: Source

    fun sendMessage(message: String) {
        source.output().send(GenericMessage(message))
    }

    @StreamListener(Sink.INPUT)
    fun receiveMessage(message: String) {
        ...
    }

}
```

## 自定義管道
若需要自定義管道，可以仿照官方源碼中的Sink/Source定義，自定義管道接口。
使用`@Input`注解修飾消息接收管道，`@Output`注解修飾消息發佈管道，注解參數中填寫管道名稱，
輸入/輸出管道可以定義在同一個接口中。

```kt
import org.springframework.cloud.stream.annotation.Input
import org.springframework.cloud.stream.annotation.Output
import org.springframework.messaging.MessageChannel
import org.springframework.messaging.SubscribableChannel

interface CustomSinkSource {

    // Receive message use input1 channel
    @Input(inChannel1)
    fun input1(): SubscribableChannel

    // Receive message use input2 channel
    @Input(inChannel2)
    fun input2(): SubscribableChannel

    // Send message use output1 channel
    @Output(outChannel1)
    fun output1(): MessageChannel

    // Send message use output2 channel
    @Output(outChannel2)
    fun output2(): MessageChannel

    companion object {
        const val outChannel1 = "customOutChannel1"
        const val outChannel2 = "customOutChannel2"
        const val inChannel1 = "customInChannel1"
        const val inChannel2 = "customInChannel2"
    }

}
```

## MessageChannel
管道實例對應的類型為`org.springframework.messaging.MessageChannel`，還可以直接注入管道實例進行消息發送：

```kt
import org.springframework.messaging.support.GenericMessage
import org.springframework.cloud.stream.annotation.EnableBinding
import org.springframework.cloud.stream.annotation.StreamListener
import org.springframework.cloud.stream.messaging.Source
import org.springframework.messaging.MessageChannel

import javax.annotation.Resource;

@EnableBinding(Source::class)
class MessageReceiver {

    @Resource(name = Source.OUTPUT)
    private lateinit var output: MessageChannel

    fun sendMessage(message: String) {
        output.send(GenericMessage(message))
    }

}
```

## 消息結構
Spring Cloud Stream中消息類型的頂層接口為`org.springframework.messaging.Message<T>`，
定義了一條消息包含的基本内容，如下所示：

> 源碼摘取自 Spring Cloud Stream 2.12 RELEASE
>
> ```java
> public interface Message<T> {
>    T getPayload();
>    MessageHeaders getHeaders();
> }
> ```

實際常用的消息類型為實現了`Message<T>`接口的`org.springframework.messaging.support.GenericMessage`。
使用GenericMessage類型，會自動為消息生成id、timestamp等header，同時還可在消息構造函數自行添加header。

一條消息包含主要内容`payload`和消息的標識`headers`，headers中的標志可用來判斷消息類型，
在`@StreamListener`注解的`condition`參數中添加判斷條件，條件使用**SPeL表達式**(`SPeL expression`)語法。

早期版本的Spring Cloud Stream中condition可以訪問payload的實際結構，
但現在的實現中無論payload的content-type實際何種類型，均采用`byte[]`進行傳輸，
并且在condition判斷階段不會將payload的内容轉化為實際類型，因而，不再能夠在condition中直接訪問payload的實際結構。

參考[官方文檔](`https://docs.spring.io/spring-cloud-stream/docs/current/reference/htmlsingle/#_using_streamlistener_for_content_based_routing`)中的描述：

> ### Content Type Negotiation in the Context of condition
>
> It is important to understand some of the mechanics behind content-based routing using the condition argument of @StreamListener, especially in the context of the type of the message as a whole. It may also help if you familiarize yourself with the Content Type Negotiation before you proceed.
>
> Consider the following scenario:
>
> ```java
> @EnableBinding(Sink.class)
> @EnableAutoConfiguration
> public static class CatsAndDogs {
>
>     @StreamListener(target = Sink.INPUT, condition = "payload.class.simpleName=='Dog'")
>     public void bark(Dog dog) {
>        // handle the message
>     }
>
>     @StreamListener(target = Sink.INPUT, condition = "payload.class.simpleName=='Cat'")
>     public void purr(Cat cat) {
>        // handle the message
>     }
> }
> ```
>
> The preceding code is perfectly valid. It compiles and deploys without any issues, yet it never produces the result you expect.
>
> That is because you are testing something that does not yet exist in a state you expect. That is becouse the payload of the message is not yet converted from the wire format (byte[]) to the desired type. In other words, it has not yet gone through the type conversion process described in the Content Type Negotiation.
>
> So, unless you use a SPeL expression that evaluates raw data (for example, the value of the first byte in the byte array), use message header-based expressions (such as condition = "headers['type']=='dog'").
