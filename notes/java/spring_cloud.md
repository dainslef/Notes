<!-- TOC -->

- [概述](#概述)
- [依賴管理](#依賴管理)
- [Spring Cloud Netfix](#spring-cloud-netfix)
	- [Eureka Server](#eureka-server)
	- [Eureka Client](#eureka-client)
	- [Zuul](#zuul)
		- [保留前綴父級路徑URL](#保留前綴父級路徑url)
		- [Sensitive Headers](#sensitive-headers)
		- [ZuulFilter](#zuulfilter)
		- [HandlerInterceptorAdapter 與 ZuulFilter](#handlerinterceptoradapter-與-zuulfilter)
- [Spring Cloud Config](#spring-cloud-config)
	- [Config Server](#config-server)
	- [Config Client](#config-client)
	- [公共配置](#公共配置)
	- [自動發現配置中心](#自動發現配置中心)
	- [@RefreshScope](#refreshscope)
	- [手動刷新配置](#手動刷新配置)

<!-- /TOC -->



# 概述
`Spring Cloud`為開發者提供了套件，用於快速構建分佈式系統的公共部分(如配置管理、服務發現、熔斷、智能路由、微代理、
控制總綫、全局鎖、選舉、分佈式Session、集羣狀態等)。
分佈式服務的協作通常遵循某些樣板模式，使用Spring Cloud的開發者能夠快速地構建實現這些模式的服務和應用。
Spring Cloud能夠很好地運行在任何分佈式平臺，包括開發者自己的筆記本電腦，裸機數據中心，以及託管平臺(如Cloud Foundry)。

具體可查閲[`Spring Cloud官方文檔`](https://cloud.spring.io/spring-cloud-static/spring-cloud.html)。



# 依賴管理
與Spring Boot項目類似，Spring Cloud項目同樣存在公用的基礎依賴，並以此決定各個組件的版本。

Spring Cloud的組件版本通過`spring-cloud-dependencies`包進行設定，在Maven中添加：

```xml
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

與Spring Boot不同，Spring Cloud組件版本不使用版本號，而使用版本代號，因爲相同Spring Cloud版本下各個子組件的版本并不統一。
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



# Spring Cloud Netfix
`Spring Cloud Netflix`項目提供了對Netfix服務的Spring Boot集成，包括：

- `Eureka`(Service Discovery，服務發現)
- `Hystrix`(Circuit Breaker，熔斷器)
- `Zuul`(Intelligent Routing，智能路由)
- `Ribbon`(Client Side Load Balancing，客戶端負載均衡)

## Eureka Server
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
server:
  port: xxxx

eureka:
  client:
    # Standalone Mode，關閉 Eureka Server 自身的服務註冊
    registerWithEureka: false
    fetchRegistry: false
```

Eureka Server自身亦是Eureka Client，默認配置下同樣要求一個Eureka Server來註冊並維持心跳(未配置依然可運行，但會定期彈出告警信息)，
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

## Eureka Client
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
eureka:
  client:
    service-url:
      defaultZone: http://Eureka主機ip:服務端口/eureka/ # 設定需要註冊的 Eureka Server 地址

spring:
  application:
    name: xxx # 設置應用名稱，默認配置下，應用名稱會用於生成 Eureka Client ID
```

在Spring Boot配置類上添加`@EnableEurekaClient`註解即可啓用Eureka Client，在配置類中注入`EurekaClient`類型的Bean：

```kt
import com.netflix.discovery.EurekaClient
import org.springframework.boot.SpringApplication
import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.cloud.netflix.eureka.EnableEurekaClient

@SpringBootApplication
@EnableEurekaClient
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
以及對應的`@EnableDiscoveryClient`註解，接口相對更加簡單：

```kt
import com.netflix.discovery.EurekaClient
import org.springframework.boot.SpringApplication
import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.cloud.netflix.eureka.EnableEurekaClient

@SpringBootApplication
@EnableDiscoveryClient
class ClientConfig {

    // 注入 DiscoveryClient
    @Autowired
    lateinit var client: DiscoveryClient

}

fun main(args: Array<String>) {
    SpringApplication.run(ClientConfig::class.java, *args)
}
```

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
zuul:
  routes:
    應用名稱1: /Xxx1/**
    應用名稱2: /Xxx2/**
    ...
```

簡單的路由配置可直接為一個應用添加一個前置路徑層級，向Zuul發送的請求的URL匹配到對應的路由則會被轉發到對應名稱的應用。

Zuul支持更細粒度的路由控制：

```yaml
zuul:
  routes:
    路由名稱:
      path: /Xxx/**
      serviceId: 應用名稱
```

### 保留前綴父級路徑URL
默認的轉發規則下，用作匹配標識的前綴在轉發到目標服務後會被丟棄，若需保留前綴，則使用如下配置：

```yaml
zuul:
  routes:
    路由名稱:
      path: /Xxx/**
      serviceId: 應用名稱
      stripPrefix: false
```

### Sensitive Headers
Zuul在轉發請求時會丟棄敏感信息相關請求頭，設定`zuul.sensitiveHeaders`配置項可設定全局的敏感信息頭，
默認的請求頭配置為：

```yaml
zuul:
  sensitiveHeaders: Cookie,Set-Cookie,Authorization
```

`zuul.sensitiveHeaders`配置項是**黑名單**(blacklist)，
即默認配置下，`Cookie`、`Set-Cookie`、`Authorization`三個請求頭在轉發時會被丟棄。
以Cookie被丟棄爲例，使用Spring Session等分佈式Session解決方案時，會導致Zuul轉發的目標模塊無法正確獲取到Session實例。

在轉發時要保留所有認證信息，將該配置項置空即可：

```yaml
zuul:
  sensitiveHeaders:
```

還可配置指定服務的轉發、保留敏感信息請求頭：

```yaml
zuul:
  routes:
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



# Spring Cloud Config
Spring Cloud Config提供了對分佈式系統的外部配置文件支持，包括客戶端和服務端。

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
  profiles:
    active: native # 設置 Config Server 為 native 模式
  cloud:
    config:
      server:
        native:
          search-locations: classpath:/ # 指定配置路徑
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
spring:
  cloud:
    stream:
      kafka:
        binder:
          brokers: ...
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
spring:
  cloud:
    config:
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
spring:
  cloud:
    config:
      # when use Eureka, you can use service-id to find Spring Cloud Server, instead of hard code in config file
      discovery:
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
management:
  endpoints:
    web:
      exposure:
        include: health,info,refresh
```

向需要刷新配置的客戶端的`actuator/refresh`路徑發送POST請求即可實現手動刷新：

```
$ curl -X POST http://localhost:xxxx/actuator/refresh
```
