# 配置文件
Maven默認的配置文件為`~/.m2/settings.xml`。
若配置文件不存在，則可手動創建，配置文件模板：

```xml
 <?xml version="1.0" encoding="UTF-8"?>
 <settings xmlns="http://maven.apache.org/SETTINGS/1.0.0"
		xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
		xsi:schemaLocation="http://maven.apache.org/SETTINGS/1.0.0 http://maven.apache.org/xsd/settings-1.0.0.xsd">

	...

 </settings>
```

要使該配置在Idea中生效，需要勾選`Preferences => Build, Execution, Deployment => Build Tools => Maven => User settings file => Override`，
選擇自定義的settings.xml文件。



# 依賴管理
依賴管理是Maven的核心功能之一。

## 查看依賴樹
在項目根路徑下執行指令，即計算整個項目的依賴，並以樹狀圖形式輸出：

```
$ mvn dependency:tree
```

使用Idea時，可在Maven工具頁面中選擇`Show Dependices`按鈕查看項目依賴樹。

## 排除指定依賴
在添加某個依賴項時，可選擇排除該依賴庫的某些依賴：

```xml
<dependency>
    <groupId>...</groupId>
    <artifactId>...</artifactId>
    <version>...</version>
    <exclusions>
        <exclusion>
            <artifactId>要排除的內容</artifactId>
            <groupId>要排除的內容</groupId>
        </exclusion>
    </exclusions>
</dependency>
```

使用Idea時，可在Maven依賴圖中搜索指定包名，右鍵選擇`Exclude`將指定依賴從項目中排除。
