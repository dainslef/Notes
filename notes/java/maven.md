<!-- TOC -->

- [配置文件](#配置文件)
	- [Repository](#repository)
	- [Mirror](#mirror)
- [依賴處理機制](#依賴處理機制)
	- [查看依賴樹](#查看依賴樹)
	- [依賴處理特性](#依賴處理特性)
		- [依賴協調(Dependency Mediation)](#依賴協調dependency-mediation)
		- [依賴管理(Dependency Management)](#依賴管理dependency-management)
		- [依賴作用域(Dependency Scope)](#依賴作用域dependency-scope)
		- [排除依賴(Excluded Dependencies)](#排除依賴excluded-dependencies)
		- [可選依賴(Optional Dependencies)](#可選依賴optional-dependencies)
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

## Repository
Maven會將依賴包緩存到本地，默認本地緩存倉庫路徑為`~/.m2/repository`。

修改`$HOME/.m2/settings.xml`文件，添加`<localRepository/>`配置段：

```xml
<settings>
	...
	<localRepository>...(自定義路徑)</localRepository>
	...
</settings>
```

某些項目依賴包不會發布到Maven官方源，而是發布到自建倉庫，
此時需要加載這些自建倉庫才能獲取這些依賴。

引入第三方倉庫可以在項目配置pom.xml中：

```xml
<project>
	...
	<repositories>
		<repository>
			<id>confluent</id>
			<name>Confluent Repo</name>
			<url>http://packages.confluent.io/maven</url>
		</repository>
	</repositories>
	...
</project>
```

也可以在全局配置settings.xml中引入第三方倉庫：

```xml
<settings>
	...
	<profiles>
		<profile>
			<id>custom-profile</id>
			<repositories>
				<repository>
					<id>jahia</id>
					<name>maven jahia</name>
					<url>http://maven.jahia.org/maven2</url>
				</repository>
			</repositories>
		</profile>
	</profiles>

	<activeProfiles>
		<activeProfile>custom-profile</activeProfile>
	</activeProfiles>
	...
</settings>
```

## Mirror
Maven中心倉庫服務器位於海外，在牆內下載速度較慢。國內可使用阿里提供的鏡像源。

修改`$HOME/.m2/settings.xml`文件，添加`<mirrors/>`配置段：

```xml
<settings>
	...
	<mirrors>
		<!-- 阿里雲倉庫 -->
		<mirror>
			<id>alimaven</id>
			<mirrorOf>*</mirrorOf>
			<name>aliyun maven</name>
			<url>https://maven.aliyun.com/repository/public</url>
		</mirror>
	</mirrors>
	...
</settings>
```



# 依賴處理機制
依賴處理機制是Maven的核心功能之一，完整說明參考[Maven官方文檔](https://maven.apache.org/guides/introduction/introduction-to-dependency-mechanism.html)。

Maven通過讀取項目構建文件(pom.xml)中的配置信息從遠程倉庫中查找類庫依賴，
並自動遞歸發現依賴，直至找到所有的依賴關係。

在pom.xml中使用`<dependency/>`標籤定義項目的依賴：

```xml
<project>
	...
	<dependencies>
		<dependency>
			<groupId>...</groupId>
			<artifactId>...</artifactId>
			<version>...</version>
		</dependency>
		... <!-- can add more dependencies -->
	</dependencies>
</project>
```

Maven的依賴管理機制對依賴關係的層級無限制，僅會在出現**環狀依賴**(cyclic dependency)時產生錯誤。

## 查看依賴樹
在項目根路徑下執行指令，即計算整個項目的依賴，並以樹狀圖形式輸出：

```
$ mvn dependency:tree
```

使用Idea時，可在Maven工具頁面中選擇`Show Dependices`按鈕查看項目依賴樹。

## 依賴處理特性
由於遞歸查找依賴，類庫的依賴圖會迅速增大。因此，存在部分附加特性用於限制包含的依賴。

### 依賴協調(Dependency Mediation)
Maven提供了jar包的依賴管理機制，但Java本身不支持多版本jar/module/class，
同一個jar/module/class，在運行期間僅能存在一個版本。
當同一個類庫的不同版本被依賴時，通過**最近定義**(Nearest Definition)規則找到合適的版本：

```
A
├── B
│   └── C
│       └── D 2.0
└── E
    └── D 1.0
```

在上述依賴關係樹中，A的兩個依賴B和E同時都間接依賴了D：

1. A -> B -> C -> D 2.0
1. A -> E -> D 1.0

第二條依賴鏈中D的依賴路徑更短，因此依賴協調最終選擇依賴D的1.0版本。

### 依賴管理(Dependency Management)
項目中可直接指定特定依賴的版本。Maven默認會自動管理傳遞依賴而不需要再指定傳遞依賴的版本。
當需要指定某個依賴的版本時，在`<dependencyManagement/>`標籤中直接指定特定依賴的版本：

```xml
<project>
	...
	<dependencyManagement>
		<dependencies>
			<dependency>
				<groupId>xxx</groupId>
				<artifactId>xxx</artifactId>
				<version>x.y.z</version>
			</dependency>
		...
		</dependencies>
	</dependencyManagement>
</project>
```

### 依賴作用域(Dependency Scope)
依賴作用域用於限制依賴的傳遞以及決定依賴是否要被包含在classpath中。

Maven包含6類依賴域：

- `compile`

	compile為默認域，當未顯式指定域時使用該域。
	compile域的依賴可被項目的所有classpath中使用，而且該類依賴可傳遞到關聯的項目。

- `provided`

	provided域類似compile，但由JDK或容器在運行期間提供依賴。
	provided域的依賴在編譯和測試時會添加到classpath中，但不會添加到runtime classpath中。
	該類依賴不傳遞。

	示例：構建Java EE的Web應用時，Servlet API以及相關的Java EE API可設置為provided域，
	因為Web容器(如Tomcat)會提供此類依賴。

- `runtime`

	runtime域的依賴在編譯時不被需要，但在運行時被需要。
	Maven在runtime以及test的classpath中包含該類依賴，但不在compile classpath中包含。

	示例：各類JDBC Driver的實現。

- `test`

	test域的依賴在程序正常運行時不被需要，僅在編譯、測試、執行階段需要。
	該類依賴不傳遞。

	示例：各類測試框架。

- `system`

	system域類似於provided，但開發者需要指定依賴jar的路徑(使用`<systemPath/>`標籤)。

	示例：

	```xml
	<dependency>
		<groupId>xxx.xxx</groupId>
		<artifactId>xxx-xxx</artifactId>
		<version>x.x.x</version>
		<scope>system</scope>
		<systemPath>/xxx/xxx.jar</systemPath> <!-- 顯式指定jar位置 -->
	</dependency>
	```

- `import`

	import域僅可在`<dependencyManagement/>`標籤段內使用，將指定目標依賴版本替換為import的依賴版本。
	import域的詳細說明參考[JBOSS社區文檔](https://developer.jboss.org/docs/DOC-15811)。

### 排除依賴(Excluded Dependencies)
使用`<exclusion/>`標籤排除指定依賴：

```xml
<project>
	...
	<dependencyManagement>
		<dependencies>
			<dependency>
				<groupId>...</groupId>
				<artifactId>...</artifactId>
				<version>...</version>
				<exclusions>
					<exclusion>
						<groupId>xxx</groupId>
						<artifactId>xxx</artifactId>
					</exclusion>
					...
				</exclusions>
			</dependency>
			...
		</dependencies>
	</dependencyManagement>
</project>
```

例如在依賴鏈`A -> B -> C`中，C通過依賴傳遞自動引入，
對A而言，若不需要依賴C，可以使用上述方式顯式排除依賴C。

### 可選依賴(Optional Dependencies)
使用`<optional/>`標籤設定指定依賴為可選依賴：

```xml
<project>
	...
	<dependencies>
		<dependency>
			<groupId>...</groupId>
			<artifactId>...</artifactId>
			<version>...</version>
			<optional>true</optional>
		</dependency>
		...
	</dependencies>
</project>
```

例如在依賴鏈`A -> B -> C`中，C通過依賴傳遞自動引入，
對A而言，C可以標記為可選依賴，當B依賴C時，A不會直接依賴C，
當B更新到某個版本後依賴變化不再依賴C時，A會直接依賴C。



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
模塊的目錄名稱最好與pom.xml中定義的artifactId相同，否則部分IDE在導入項目時可能不能正確識別子模塊。

默認查找父模塊的路徑為上級目錄，若需要指定父模塊的路徑，可通過`<relativePath/>`標籤設置：

```xml
<project>
	...
	<parent>
		...
		<relativePath>/xxx/pom.xml<relativePath/> <!-- 指定路徑 -->
	</parent>
	...
</project>
```



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

spring-boot-maven-plugin支持在編譯時生成構建信息，修改配置：

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
				<executions>
					<execution>
						<goals>
							<!-- generate build info in META-INF/build.properties -->
							<goal>build-info</goal>
						</goals>
					</execution>
				</executions>
			</plugin>
			...
		</plugins>
	</build>
	...
</project>
```

添加build-info配置項後，會在打包的JAR內生成`META-INF/build-info.properties`文件用於記錄構建信息，
格式如下：

```ini
build.artifact=a1902-terminal-control-server
build.group=com.ljshuoda
build.name=a1902-terminal-control-server
build.time=2021-06-21T02\:44\:22.068Z
build.version=1.0
```

若jar包中帶有build-info，當使用spring-boot-admin時，會展示項目的build-info信息。
若開啟了actuator相關端點，則URL`actuator/info`發送GET請求會得到build-info的json結構。
