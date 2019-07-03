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



# Repository
Maven會將依賴包緩存到本地，默認本地緩存倉庫路徑為`~/.m2/repository`。

## 修改本地緩存路徑
修改`$HOME/.m2/settings.xml`文件，添加`<localRepository/>`配置段：

```xml
<localRepository>...(自定義路徑)</localRepository>
```

## Mirror
Maven中心倉庫服務器位於海外，在牆內下載速度較慢。國內可使用阿里提供的鏡像源。

修改`$HOME/.m2/settings.xml`文件，添加`<mirrors/>`配置段：

```xml
<mirrors>
	<!-- 阿里雲倉庫 -->
	<mirror>
		<id>alimaven</id>
		<mirrorOf>central</mirrorOf>
		<name>aliyun maven</name>
		<url>http://maven.aliyun.com/nexus/content/repositories/central/</url>
	</mirror>
</mirrors>
```



# Language Level
默認配置下，Maven項目使用的`Language Level`和`Java Compiler`爲`Java 5(JDK 1.5)`，
該配置下Java5之後的語言特性如自定義註解(Java6)、try-with-resource(Java7)，Lambda(Java8)等諸多新特性無法使用。

使用Idea導入Maven工程時，Maven項目的LanguageLevel還會覆蓋項目的配置，導致Idea中設置的項目LanguageLevel失效。

更改項目的LanguageLevel，在pom.xml中加入以下配置：

```xml
<project>
	...
	<properties>
		<!-- 使用當前的JDK版本 -->
		<maven.compiler.source>1.8</maven.compiler.source>
		<maven.compiler.target>1.8</maven.compiler.target>
	</properties>
	...
</project>
```

也可以直接設置`maven-compiler-plugin`的編譯參數來控制LanguageLevel：

```xml
<project>
	...
	<build>
		...
		<plugins>
			<plugin>
				<groupId>org.apache.maven.plugins</groupId>
				<artifactId>maven-compiler-plugin</artifactId>
				<version>3.8.0</version>
				<configuration>
					<source>1.8</source>
					<target>1.8</target>
				</configuration>
			</plugin>
		</plugins>
		...
	</build>
	...
</project>
```
