<!-- TOC -->

- [配置文件](#配置文件)
- [依賴管理](#依賴管理)
	- [查看依賴樹](#查看依賴樹)
	- [排除指定依賴](#排除指定依賴)
- [Repository](#repository)
	- [修改本地緩存路徑](#修改本地緩存路徑)
	- [Mirror](#mirror)
- [Language Level](#language-level)
- [Sub Project](#sub-project)
- [Package](#package)
	- [maven-assembly-plugin](#maven-assembly-plugin)
	- [spring-boot-maven-plugin](#spring-boot-maven-plugin)

<!-- /TOC -->



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
		<mirrorOf>*</mirrorOf>
		<name>aliyun maven</name>
		<url>https://maven.aliyun.com/repository/public</url>
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



# Sub Project
與sbt類似，Maven同樣可在一個項目中創建多個子項目，每個子項目可繼承父項目的依賴、插件等配置。

在父項目的pom.xml中加入`<module/>`標簽，提供子模塊路徑的聲明：

```xml
<project>
	...
	<modules>
		<module>...</module> <!-- 告知子模塊的路徑 -->
		<module>...</module>
		...
	</modules>
	...
</project>
```

子項目擁有獨立的目錄和pom.xml配置，在子模塊的配置中添加`<parent/>`標簽，聲明父模塊的引用：

```xml
<project>
	...
	<parent>
		<artifactId>spring-cloud-practice</artifactId>
		<groupId>dainslef</groupId>
		<version>0.1</version>
	</parent>
	...
</project>
```

子模塊繼承父模塊的`<groupId/>`、`<version/>`，無須單獨配置。



# Package
Maven默認的package功能僅將當前項目生成的class文件進行打包，要打包所有依賴資源，需要引入額外插件。

## maven-assembly-plugin
與sbt的`sbt-assembly`類似，Maven的`maven-assembly-plugin`插件提供將所有項目依賴打包到一個JAR的功能。

在pom.xml文件中添加插件配置：

```xml
<project>
	...
	<build>
		...
		<plugins>
			...
			<plugin>
				<artifactId>maven-assembly-plugin</artifactId>
				<version>3.1.0</version>
				<executions>
					<execution>
						<id>make-assembly</id>
						<phase>package</phase>
						<goals>
							<goal>single</goal>
						</goals>
					</execution>
				</executions>
				<configuration>
					<descriptorRefs>
						<descriptorRef>jar-with-dependencies</descriptorRef>
					</descriptorRefs>
					<archive>
					<manifest>
						<!-- 定義 Mainfest 文件中的MainClass(JAR文件的執行入口類) -->
						<mainClass>xxx.xxx.Xxx...</mainClass>
					</manifest>
					</archive>
				</configuration>
			</plugin>
			...
	 	</plugins>
		...
	</build>
	...
</project>
```

## spring-boot-maven-plugin
對於`Spring Boot`項目，使用該插件能將所有依賴打包到一個JAR。

在pom.xml文件中添加插件配置：

```xml
<project>
	...
	<build>
		<plugins>
			...
			<!-- package plugin for Spring project, build all dependencies into one jar -->
			<plugin>
				<groupId>org.springframework.boot</groupId>
				<artifactId>spring-boot-maven-plugin</artifactId>
			</plugin>
			...
		</plugins>
	</build>
	...
</project>
```

相比`maven-assembly-plugin`，`spring-boot-maven-plugin`對於Spring Boot項目的打包結構更加合理，
所有依賴的JAR包不會被被解包重新封裝，而是保留原始結構壓縮到生成的JAR包中，避免了傳統插件打包時的文件衝突等問題。
