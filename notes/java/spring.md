<!-- TOC -->

- [Spring Profiles](#spring-profiles)
	- [單文件多Profile](#單文件多profile)
	- [@Profile](#profile)
- [Log](#log)
	- [WebRequest Log](#webrequest-log)

<!-- /TOC -->



# Spring Profiles
Spring支持使用`properties/yaml`等文件格式作爲項目的配置文件。

Spring Profiles的完整介紹參考[Spring官方文檔](https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-profiles)。

Spring應用支持多種配置，每組配置被稱為一個`profile`。
`bootstrap/application.properties/yaml`等文件中存放默認配置，
不同profile下的特殊配置寫在獨立的文件中，以`boostrap/application-{profile名稱}.properties/yaml`命名。

以`test`作為profile名稱和yaml格式為例，默認配置文件為：

```
boostrap.yaml
application.yaml
```

`test`對應profile專屬的配置應寫在如下文件中：

```
boostrap-test.yaml
application-test.yaml
```

一個Spring應用運行時得到的配置為默認配置與profile專屬配置之和。
profile配置和默認配置擁有相同的配置項時，profile配置中的配置優先級更高，會覆蓋共用配置文件中的對應內容。

啟動項目時在命令行使用參數`--spring.profiles.active=xxx1,xxx2,...`來指定激活的profile。

## 單文件多Profile
多個profile也可以寫在同一個文件內，使用`---`符號隔開，在屬性`spring.profiles`配置項中標記配置的名稱：

```yaml
# 分別定義 config1, config2, test1, test2 四套Profile

---
spring.profiles: config1
...

---
spring.profiles: config2
...

---
spring.profiles: test1
...

---
spring.profiles: test2
...
```

## @Profile
在Bean上使用`@Profile`註解能夠限定Bean僅在特定條件下啟用該Bean：

```kt
@Service
@Profile("test1") // 設置該Bean僅在profile的test激活時生效
class BeanXxx {
    ...
}
```

`@Profile`註解支持邏輯語法，可以結合判斷多個Profile來決定是否啟用Bean。
詳細可參考Spring的[`Profile API`](https://docs.spring.io/spring-framework/docs/current/javadoc-api/org/springframework/core/env/Profiles.html)官方文檔。

邏輯運算符說明：

- `!` 邏輯**非**
- `&` 邏輯**與**
- `|` 邏輯**或**

需要注意，邏輯運算符`&`和`|`不能在不使用括號指定優先級的情況下使用，例如`a & b | c`不是有效的表達式，
應寫成`(a & b) | c`或`a & (b | c)`(顯式用括號指定優先級)。

簡單示例：

```kt
@Profile("test1 & test2") // 在test1和test2均激活時啟用Bean
@Profile("test1 | test2") // 在test1或test2均激活時啟用Bean
@Profile("!test1") // 在test1未激活時啟用Bean
@Profile("!test1 & test2") // 在test1未激活且test2激活時啟用Bean
```

`@Profile`註解參數實際為一個數組，因此支持數組語法：

```kt
@Profile(["test1", "test2"]) // 等價於 @Profile("test1 & test2")
```



# Log
Spring Boot中包含五個日志級別，日志從簡單到詳細依次為`ERROR`、`WARN`、`INFO`、`DEBUG`、`TRACE`。
默认的日志输出级别是INFO，因而很多详细的日志并不会被输出。

通過配置項`logging.level.[包路徑/類路徑]`來控制不同類的日志輸出級別；
使用**包路徑**，則包内的所有類均使用該日志級別，使用**類路徑**，則只有目標類型的日志會使用對應級別。
使用`root`可設定所有類型的默認日志級別。

儅存在多個日志級別配置時，更細粒度的日志級別配置會優先生效。
如下所示：

```yaml
logging.level:
  root: INFO # 默認使用 INFO 級別輸出日志
  org.springframework:
    web: DEBUG # org.springframework.web包下的類使用 DEBUG 級別輸出日志
    web.servlet.DispatcherServlet: TRACE # org.springframework.web.servlet.DispatcherServlet類使用 TRACE 級別輸出日志
```

更詳細的説明可參考[官方文檔](https://docs.spring.io/spring-boot/docs/current/reference/html/howto-logging.html)。

## WebRequest Log
默認的日誌級別沒有啟用Web請求的日誌記錄，
`org.springframework.web.servlet.DispatcherServlet`類提供了servlet請求日誌，
將日誌級別開至DEBUG即可：

```yaml
logging.level:
  org.springframework.web.servlet.DispatcherServlet: DEBUG
```

DispatcherServlet類型會記錄所有請求日誌，若需要限定記錄請求的類型、URL等(屏蔽部分系統請求如`/actuator`)，
可以使用Spring提供的過濾器接口：

- CommonsRequestLoggingFilter
- ServletContextRequestLoggingFilter

提供對應過濾器的Bean即可實現請求URL日誌打印，
與DispatcherServlet類似，以上過濾器默認打印的URL日誌為DEBUG級別，
需要在配置中正確開啟對應的日誌級別。
