<!-- TOC -->

- [环境搭建](#环境搭建)
	- [管理 *Android SDK*](#管理-android-sdk)
	- [项目结构](#项目结构)
	- [构建定义](#构建定义)
- [*Activity*](#activity)
	- [*View* (视图)](#view-视图)
	- [启动指定 *Activity*](#启动指定-activity)
- [*Intent*](#intent)
- [*Menu*](#menu)
	- [定义菜单](#定义菜单)
	- [菜单项属性](#菜单项属性)
	- [创建菜单](#创建菜单)
	- [处理菜单事件](#处理菜单事件)
	- [*ActionBar*](#actionbar)

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



## *Activity*
`Activity`是`Android`中的核心组件，每个`Activity`对应一个独立的应用窗口。  
`Activity`类似于`Swing`中的`JFrame`、`Qt`中的`QWindow`、`JavaFx`中的`Stage`，做为应用的顶层窗口存在，一个应用可以由一个/多个`Activity`构成。

一个应用的多个`Activity`之间可相互跳转，并传递信息。  
跳转到新的`Activity`时，旧的`Activity`会停止并驻留在返回栈上，使用返回按钮会销毁新`Activity`，并恢复原`Activity`。
启动时呈现的`Activity`为主`Activity`，主`Activity`销毁会退出应用。

### *View* (视图)
`android.view.View`及其子类用于为`Activity`提供用户界面。  
`View`类型存在子类`ViewGroup`，可做为容器容纳其它`View`。

`Android`支持使用`XML`语法描述视图，在`app/res/layout`路径下添加视图描述文件，在`Activity`的`onCreate()`方法中调用`setContentView()`方法，传入资源ID来设定`Activity`的视图。  
如下所示：

```kotlin
class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.xxx) //通过资源ID设置视图
    }

    ...

}
```

使用`setContentView()`将视图资源设置到`Activity`后，视图资源的描述的每一个容器、控件都可以使用`findViewById()`方法通过视图`ID`获取对应的视图实例(需要对应控件在`XML`定义中声明了`android:id`属性)。  
如下所示，资源文件定义如下：

```
<TableLayout
        xmlns:android="http://schemas.android.com/apk/res/android"
        xmlns:tools="http://schemas.android.com/tools"

        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:padding="8dp">

    <ListView
            android:id="@+id/listView"
            android:layout_width="match_parent"
            android:layout_height="match_parent"/>

</TableLayout>
```

获取控件实例：

```kotlin
class MainActivity : AppCompatActivity() {

    val listView by lazy { findViewById(R.id.listView) as ListView }

    ...

}
```

### 启动指定 *Activity*
使用`startActivity()`方法启动另一个`Activity`。  
`startActivity()`方法定义在`Activity`中，定义如下：

```java
public void startActivity(Intent intent);
```

`intent`参数使用目标`Activity`的`Class`实例做为参数。  
如下所示：

```kotlin
startActivity(Intent(this, OtherActicity::class.java))
```



## *Intent*
`Intent`类型用来描述需要执行的操作。
`Intent`类型拥有多种构造方法：

```java
public Intent(Context packageContext, Class<?> cls);
public Intent(String action, Uri uri);
public Intent(String action, Uri uri,
		Context packageContext, Class<?> cls);
```

`Intent`常用于：

- 启动`Activity`(`startActivity()`方法)
- 启动`Service`(`startService()`方法)
- 与后端`Service`通信(`bindService()`方法)



## *Menu*
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

### *ActionBar*
从`Android 3.0 (API level 11)`开始，`Activity`带有`ActionBar`做为主菜单栏。

在`Activity`子类中使用`getActionBar()`获取`ActionBar`：

```kotlin
val bar = actionBar
```

在`Fragment`中获取`ActionBar`：

```kotlin
val bar = activity.actionBar
```

对于`AppCompatActivity`的子类，应使用`getSupportActionBar()`方法获取`ActionBar`：

```kotlin
//在 AppCompatActivity 子类中获取 ActionBar
val bar = supportActionBar

//在 Fragment 中获取 AppCompatActivity 子类的 ActionBar
val bar = activity.supportActionBar
```

在`AppCompatActivity`子类中使用`getActionBar()`会得到`null`。

获取`ActionBar`可用于设定主菜单的显示标题、Logo、返回菜单等。  
在`Activity/Fragment`子类中使用`setDisplayOptions()`方法设定在`ActionBar`中显示的内容。  
`setDisplayOptions()`方法具有以下重载：

```java
public abstract void setDisplayOptions(@DisplayOptions int options);
public abstract void setDisplayOptions(@DisplayOptions int options, @DisplayOptions int mask);
```

`options`参数设定启用的内容，`mask`参数设定禁用的内容，多个参数使用逻辑与操作符`|`连接。  
可使用以下选项：

```
DISPLAY_USE_LOGO
DISPLAY_SHOW_HOME
DISPLAY_HOME_AS_UP
DISPLAY_SHOW_TITLE
DISPLAY_SHOW_CUSTOM
```

亦可使用单独的方法独立地设置显示内容：

```kotlin
actionBar?.apply {
    setDisplayHomeAsUpEnabled(true)
    setDisplayShowCustomEnabled(true)
    setDisplayShowHomeEnabled(true)
    setDisplayShowTitleEnabled(true)
    setDisplayUseLogoEnabled(true)
}
```
