<!-- TOC -->

- [概述](#概述)
- [Spring Cloud Netfix](#spring-cloud-netfix)
	- [Eureka Server](#eureka-server)
	- [Eureka Client](#eureka-client)

<!-- /TOC -->



# 概述
`Spring Cloud`為開發者提供了套件，用於快速構建分佈式系統的公共部分(如配置管理、服務發現、熔斷、智能路由、微代理、
控制總綫、全局鎖、選舉、分佈式Session、集羣狀態等)。
分佈式服務的協作通常遵循某些樣板模式，使用Spring Cloud的開發者能夠快速地構建實現這些模式的服務和應用。
Spring Cloud能夠很好地運行在任何分佈式平臺，包括開發者自己的筆記本電腦，裸機數據中心，以及託管平臺(如Cloud Foundry)。

具體可查閲[`Spring Cloud官方文檔`](https://cloud.spring.io/spring-cloud-static/spring-cloud.html)。



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
	<version>${spring-boot-version}</version>
</dependency>

<!-- Eureka need Spring Cloud Config Client -->
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-config</artifactId>
	<version>${spring-boot-version}</version>
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
...
<!-- Eureka Client -->
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-netflix-eureka-client</artifactId>
	<version>${spring-boot-version}</version>
</dependency>

<!-- Eureka need Spring Cloud Config Client -->
<dependency>
	<groupId>org.springframework.cloud</groupId>
	<artifactId>spring-cloud-starter-config</artifactId>
	<version>${spring-boot-version}</version>
</dependency>
...
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
