<!-- TOC -->

- [Log](#log)
	- [WebRequest Log](#webrequest-log)

<!-- /TOC -->



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
