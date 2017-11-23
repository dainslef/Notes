<!-- TOC -->

- [环境搭建](#环境搭建)
	- [管理 *Android SDK*](#管理-android-sdk)
	- [项目结构](#项目结构)
	- [构建定义](#构建定义)
- [Menu](#menu)
	- [定义菜单](#定义菜单)
	- [菜单项属性](#菜单项属性)
	- [创建菜单](#创建菜单)
	- [处理菜单事件](#处理菜单事件)

<!-- /TOC -->



## 环境搭建
`Android`早期通过`Eclipse`外挂`ADT`(`Android Development Tools`)插件来进行开发。  
`Eclipse ADT`插件现在已停止更新，官方推荐开发环境迁移到`Android Studio`。

`Android Studio`基于`IntelliJ IDEA Community`定制开发，
`IntelliJ IDEA`的`Android Support`插件提供了`Android Studio`的核心功能，启用该插件即可进行`Android`开发。

### 管理 *Android SDK*
依次通过`Tools => Android => SDK Manager`进入`Android SDK`配置界面。

- `SDK Platforms`界面勾选需要的`Android SDK`版本。
- `SDK Tools`界面勾选需要的开发工具链。

选择`Android SDK`时，需要注意`IntelliJ IDEA`的`Android Support`插件与`Android Studio`版本的对应关系。  
如`IntelliJ IDEA 2017.2`的`Android Support`插件版本为`10.2.3`，对应`Android Studio 2.3`，
`Android Studio 2.3`发布时的`Android SDK`最高版本为`API 25 (Android 7.1.1 Nougat)`。

高版本的`Android SDK`在低版本的`Android Support`插件中仅显示`API`级别，不显示版本信息。  
如`Android 8.0 Oreo`在`Android Support 10.2.3`中仅显示为`API 26`。

不应使用与插件不匹配的高版本`Android SDK`(不显示版本信息的版本)，高版本的`Android SDK`搭配低版本的`Android Support`插件可能会造成UI设计器、构建工具等出错。

### 项目结构
`Anddroid`项目使用`Gradle`构建。  
一个基本的`Android`项目具有以下目录结构：

```
项目名称
├── build.gradle
├── settings.gradle
├── gradle.properties
├── build # 构建缓存目录
│    └── ...
├── gradle # Gradle Wrapper
│    └── ...
└── app # Android 核心目录
     ├── build.gradle # Android 构建配置
     ├── build # Android 构建缓存
     │    └── ...
     ├── libs
     │    └── ...
     └── src # 项目源码目录
          ├── androidTest # Android 测试
          │    └── ...
          ├── test # 单元测试
          │    └── ...
          └── main # APP 核心源码
               ├── AndroidManifest.xml
               ├── java
               │    └── ...
               └── res
                    ├── drawable # 矢量图
                    │    ├── activity_main.xml
                    │    └── ...
                    ├── layout # 布局描述 XML
                    │    └── ...
                    ├── menu # 菜单描述 XML
                    │    └── ...
                    ├── values
                    │    ├── colors.xml
                    │    ├── strings.xml
                    │    ├── styles.xml
                    │    └── ...
                    └── mipmap-*dpi # 不同DPI的位图资源
                         └── ...
```

### 构建定义
`Android`项目使用`Gradle`做为构建工具，项目构建配置位于`app/build.gradle`。  
构建配置基本结构如下：

```groovy
apply plugin: 'com.android.application'

android {
    compileSdkVersion xx(编译SDK版本)
    buildToolsVersion "xx(构建工具版本)"
    defaultConfig {
        applicationId "xxx.yyy.zzz(包名)"
        minSdkVersion xx(最小SDK版本)
        targetSdkVersion xx(目标SDK版本)
        versionCode 1
        versionName "1.0"
        testInstrumentationRunner "android.support.test.runner.AndroidJUnitRunner"
    }
    buildTypes {
        release {
            minifyEnabled false
            proguardFiles getDefaultProguardFile('proguard-android.txt'), 'proguard-rules.pro'
        }
    }
}

dependencies {
    compile fileTree(dir: 'libs', include: ['*.jar'])
    compile 'Xxx:Xxx:版本' //依赖项
    ...
    testCompile 'junit:junit:xxx'
}

repositories {
    mavenCentral() //使用 Maven 仓库
}
```

在`Android`项目中添加`Kotlin`支持，需要以下步骤：

1. 在`build.gradle`中追加以下内容：

	```groovy
	buildscript {
	    ext.kotlin_version = 'Kotlin版本'
	    dependencies {
	        classpath "org.jetbrains.kotlin:kotlin-gradle-plugin:$kotlin_version"
	    }
	}
	```

1. 在`app/build.gradle`中追加以下内容：

	```groovy
	apply plugin: 'kotlin-android'

	dependencies {
	    compile "org.jetbrains.kotlin:kotlin-stdlib-jre7:$kotlin_version"
	}
	```



## Menu
`Android`系统中包括三类菜单：

- 选项菜单和应用栏
- 上下文菜单
- 弹出菜单

从`Android 3.0 (API Level 11)`开始，设备不再拥有独立菜单键，而是使用`Action Bar`提供主菜单。

### 定义菜单
在`app/res/menu`路径下添加菜单的`XML`定义。  
菜单对应`XML`文件的名称会做为菜单的资源`ID`，如菜单定义为`app/res/menu_main.xml`，则对应资源为`R.menu.menu_main`。

菜单定义包括以下元素：

- `<menu>`

	菜单的**根节点**。`<menu>`能够包含一个或多个`<item>`和`<group>`子节点。

- `<item>`

	菜单项(`MenuItem`)，可包含`<menu>`子节点(创建子菜单)。

- `<group>`

	菜单组，对菜单进行编组，同组内的菜单共享可选、可见性等属性。

基本的菜单定义示例如下：

```xml
<?xml version="1.0" encoding="utf-8"?>
<menu xmlns:android="http://schemas.android.com/apk/res/android"
      xmlns:app="http://schemas.android.com/apk/res-auto">

    <item
            android:id="@+id/app_bar_switch"
            android:title="@string/app_name"/>

    <item
            android:id="@+id/app_bar_search"
            android:icon="@drawable/ic_search_black_24dp"
            app:showAsAction="ifRoom"
            android:title="@string/search" android:actionViewClass="android.widget.SearchView"/>

    <item
            android:id="@+id/version"
            android:title="@string/version"/>

</menu>
```

### 菜单项属性
菜单节点`<item>`的常用属性：

- `android:title` 菜单显示文本
- `android:icon` 菜单图标
- `app:showAsAction` 菜单的展示方式，取值如下：

	- `alaways` 总是显示
	- `never` 从不显示
	- `ifRoom` 有足够空间时显示

### 创建菜单
在`Activity`及其子类中通过重写`onCreateOptionsMenu()`方法创建菜单：

```kotlin
override fun onCreateOptionsMenu(menu: Menu?): Boolean {
    menuInflater.inflate(R.menu.Xxx, menu) //R.menu.Xxx 为菜单对应的资源ID
    return true
}
```

`Fragment`亦可拥有菜单，通过重写`Fragment`类的`onCreateOptionsMenu()`方法创建菜单：

```kotlin
override fun onCreateOptionsMenu(menu: Menu?, inflater: MenuInflater?) {
    inflater?.inflate(R.menu.Xxx, menu)
}
```

使用`Fragment`创建菜单时，需要在`Fragment`创建时调用`setHasOptionsMenu()`方法，传递`true`参数才能使`Fragment`的`onCreateOptionsMenu()`方法被调用：

```kotlin
override fun onCreate(savedInstanceState: Bundle?) {

    super.onCreate(savedInstanceState)
    ...

    // 启用菜单，否则 Fragment 中重写的 onCreateOptionsMenu() 方法不被调用
    setHasOptionsMenu(true)
}
```

### 处理菜单事件
`Activity/Fragment`处理菜单事件方法类似，通过重写基类的`onOptionsItemSelected()`方法响应菜单选择事件：

```kotlin
override fun onOptionsItemSelected(item: MenuItem?): Boolean {

   ....

   return true
}
```
