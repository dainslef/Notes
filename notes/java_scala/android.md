<!-- TOC -->

- [环境搭建](#环境搭建)
	- [管理 *Android SDK*](#管理-android-sdk)
	- [*Intel HAXM*](#intel-haxm)
- [项目构建](#项目构建)
	- [项目结构](#项目结构)
	- [构建定义](#构建定义)
	- [添加 *Korlin* 支持](#添加-korlin-支持)
- [资源](#资源)
	- [资源ID](#资源id)
- [*Activity*](#activity)
	- [*View* (视图)](#view-视图)
	- [启动/结束 *Activity*](#启动结束-activity)
	- [获取 *Activity* 返回结果](#获取-activity-返回结果)
- [*Fragment*](#fragment)
	- [管理 *Fragment*](#管理-fragment)
	- [*Fragment* 数据传递](#fragment-数据传递)
- [*Intent*](#intent)
	- [*Standard Extra Data*](#standard-extra-data)
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

### *Intel HAXM*
**Android模拟器**需要`Intel HAXM`技术提供图形加速支持，否则模拟器无法启动。

在`Windows/Linux`平台上，直接使用`Android Studio`安装`Intel HAXM`。

在`macOS`平台上，`Intel HAXM`安装包提供的安装脚本会检测macOS版本，安装脚本可能无法识别最新版macOS。  
使用`Android Stduio`直接安装`Intel HAXM`时，可能无法通过安装脚本的检测，
此时应在Intel官网下载安装包，解压得到`dpkg`格式的安装包手动执行安装。

`Intel HAXM`安装完成后，在macOS下直接启动模拟器会出现`/dev/kvm is not found`错误，
原因是HAXM的APP在macOS的默认安全策略下被禁止启动，
在`System Preferences => Security & Privacy => General`选项中点击**允许**相关APP执行。

在macOS下移除已安装的`Intel HAXM`，执行指令：

```
sudo /System/Library/Extensions/intelhaxm.kext/Contents/Resources/uninstall.sh
```



## 项目构建
Anddroid项目使用`Gradle`做为构建工具。

### 项目结构
一个基本的Android项目具有以下目录结构：

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
     └── src # 项目源码、资源目录
          ├── androidTest # Android 测试
          │    └── ...
          ├── test # 单元测试
          │    └── ...
          └── main # APP主要目录
               ├── AndroidManifest.xml
               ├── java # 源码目录
               │    └── ...
               └── res # 资源目录
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

### 添加 *Korlin* 支持
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



## 资源
资源是非代码形式，如图片、音频、XML文件等。  
在Andorid项目中，所有的资源均位于`res`路径下。  
`res`路径下具有以下结构：

```
res
 ├── drawable # 矢量图
 │    ├── activity_main.xml
 │    └── ...
 ├── layout # UI布局 XML
 │    └── ...
 ├── menu # 菜单布局 XML
 │    └── ...
 ├── values
 │    ├── colors.xml # 色彩
 │    ├── strings.xml # 字符串资源
 │    ├── styles.xml # 样式定义
 │    └── ...
 └── mipmap-*dpi # 不同DPI的位图资源
      └── ...
```

### 资源ID
在Android项目构建时，`res`路径下各类资源文件会被分配资源ID，在多数`Andorid API`中，均通过资源ID访问资源。  
资源ID定义在静态类`R`中(`R.java`文件)中：

- 部分路径会直接在`R`类型内生成对应名称的**静态内部类**：

	- `res/mipmap`
	- `res/drawable`
	- `res/layout`
	- `res/menu`
	
	路径下的每个文件会在所属路径对应的静态内部类中生成资源ID。

- `res/values`路径下的资源文件直接生成对应**静态内部类**：

	- `res/values/strings.xml`
	- `res/values/colors.xml`
	- `res/values/styles.xml`

	文件内的每个资源定义会根据资源类型在对应的静态内部类中生成资源ID。

类型`R`的基本内容如下所示：

```java
public final class R {
	...
	// 对应 res/drawable 路径下的资源文件
	public static final class drawable {
		...
		public static final int xxx = 0x????;
		...
	}
	// 对应 res/layout 路径下的资源文件
	public static final class layout {
		...
		public static final int xxx = 0x????;
		...
	}
	// 对应 res/menu 路径下的资源文件
	public static final class menu {
		...
		public static final int xxx = 0x????;
		...
	}
	// 对应 res/values/strings.xml 文件内的资源定义
	public static final class string {
		...
		public static final int xxx = 0x????;
		...
	}
	// 对应 res/values/colors.xml 文件内的资源定义
	public static final class color {
		...
		public static final int xxx = 0x????;
		...
	}
	// 对应 res/values/styles.xml 文件内的资源定义
	public static final class style {
		...
		public static final int xxx = 0x????;
		...
	}
	...
}
```



## *Activity*
`Activity`是`Android`中的核心组件，每个`Activity`对应一个独立的应用窗口。  
`Activity`类似于`Swing`中的`JFrame`、`Qt`中的`QWindow`、`JavaFx`中的`Stage`，
做为应用的顶层窗口存在，一个应用可以由一个/多个`Activity`构成。

一个应用的多个`Activity`之间可相互跳转，并传递信息。  
跳转到新的`Activity`时，旧的`Activity`会停止并驻留在返回栈上，使用返回按钮会销毁新`Activity`，并恢复原`Activity`。
启动时呈现的`Activity`为主`Activity`，主`Activity`销毁会退出应用。

### *View* (视图)
`android.view.View`及其子类用于为`Activity`提供用户界面。  
`View`类型存在子类`ViewGroup`，可做为容器容纳其它`View`。

`Android`支持使用`XML`语法描述视图，在`app/res/layout`路径下添加视图描述文件，
在`Activity`的`onCreate()`方法中调用`setContentView()`方法，传入资源ID来设定`Activity`的视图。  
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

### 启动/结束 *Activity*
使用`startActivity()`方法启动另一个`Activity`。  
相关方法定义在`Activity`类中，具有多个重载：

```java
public class Activity extends ... {
	...
	public void startActivity(Intent intent);
	public void startActivity(Intent intent, @Nullable Bundle options)；
	...
}
```

`intent`参数使用目标Activity的**Class实例**做为参数，指定需要启动的目标Activity类型。  
`intent`参数亦可附加传递数据、实例。  
如下所示：

```kotlin
startActivity(Intent(this, OtherActicity::class.java))
```

结束`Activity`使用`finish()`方法：

```java
public class Activity extends ... {
	...
	public void finish();
	...
}
```

结束一个Activity后会回到上一个Activity。  
若结束的是**主Activity**，则会退出应用。

### 获取 *Activity* 返回结果
对于需要获取返回结果的`Activity`启动任务，应使用`startActivityForResult()`相关方法启动：

```java
public class Activity extends ... {
	...
	public void startActivityForResult(@RequiresPermission Intent intent, int requestCode);
	public void startActivityForResult(@RequiresPermission Intent intent, int requestCode, @Nullable Bundle options);
	...
}
```

同时重写`onActivityResult()`方法，该方法在目标`Activity`返回后会被回调：

```java
public class Activity extends ... {
	...
	protected void onActivityResult(int requestCode, int resultCode, Intent data);
	...
}
```

`requestCode`参数由`startActivityForResult()`时传入，用于区分不同的启动任务。  
目标Activity在`finish()`调用前应使用`setResult()`方法设定返回值。

```java
public class Activity extends ... {
	...
	public final void setResult(int resultCode);
	public final void setResult(int resultCode, Intent data);
	...
}
```



## *Fragment*
`Fragment`是`Android 3.0 (API Level 11)`开始引入的新UI组件。

Fragment被称为**片段**，用来组成Activity中的UI部分。  
一个Activity可由一个或多个Fragment组成，多个Activity亦可共享同一个Fragment。

Fragment有独立的事件处理、生命周期。  
但Fragment必须始终嵌入在Activity中，其生命周期直接受宿主Activity生命周期的影响：

- 宿主Activity暂停时，包含的子Fragment都将暂停。
- 宿主Activity销毁时，包含的子Fragment都将被销毁。

### 管理 *Fragment*
Activity可在运行时动态地添加与移除、替换Fragment。

`FragmentManager`类型提供了对Fragment的管理操作。  
Activity类型提供了`getFragmentManager()`方法，用于获取FragmentManager实例：

```java
public class Activity extends ... {
	...
	public FragmentManager getFragmentManager();
	...
}
```

- 获取 *Fragment*

	FragmentManager类型提供了`findFragmentById()`方法，通过传入资源ID获取指定Fragment实例：

	```java
	public class Fragment implements ComponentCallbacks2, OnCreateContextMenuListener {
		...
		public abstract Fragment findFragmentById(int id);
		...
	}
	```

	当指定的Fragment未被初始化时，`findFragmentById()`方法会返回空指针，因而在获取Fragment时应进行`NullCheck`。  
	如下所示：

	```kotlin
	val xxxFragment by lazy {
	    fragmentManager.findFragmentById(R.id.xxxFragment) ?: XxxFragment()
	}
	```

- *Fragment* 事务(添加、移除、替换、显示、隐藏)

	FragmentManager类型提供了`beginTransaction()`方法用于启动事务：

	```java
	public abstract class FragmentManager {
		...
		public abstract FragmentTransaction beginTransaction();
		...
	}
	```

	事务类型`FragmentTransaction`提供对Fragment增加、删除、替换、隐藏、显示等操作，以及对事务的提交：

	```java
	public abstract class FragmentTransaction {
		...
		public abstract FragmentTransaction add(@IdRes int containerViewId, Fragment fragment);
		public abstract FragmentTransaction remove(Fragment fragment);
		public abstract FragmentTransaction replace(@IdRes int containerViewId, Fragment fragment);
		public abstract FragmentTransaction hide(Fragment fragment);
		public abstract FragmentTransaction show(Fragment fragment);
		public abstract int commit();
		...
	}
	```

	`containerViewId`参数可以是任意常见容器View的资源ID，如`FrameLayout、LinearLayout`等。  
	在一个事务中完成各类Fragment操作后提交事务，入下所示：

	```kotlin
	fragmentManager.beginTransaction().apply {
	    add(R.id.xxx, xxxFragment)
	    remove(yyyFragment)
	    ...
	    commit()
	}
	```

### *Fragment* 数据传递
Fragment通过`setArguments()/getArguments()`方法传递`Bundle`类型的数据。  
相关方法定义如下：

```java
public class Fragment implements ComponentCallbacks2, OnCreateContextMenuListener {
	...
	public void setArguments(Bundle args);
	final public Bundle getArguments();
	...
}
```

`Bundle`类型拥有一系列`getXxx()/setXxx()`方法用于**获取/设置**指定类型的数据。  
与`Intent`类型类似，`Bundle`类型传递数据的方法`setXxx()`接收字符串和数据内容做为参数(数据内容由字符串作为`Key`)，获取数据的相关方法`getXxx()`使用字符串标`Key`提取指定的数据。



## *Intent*
`Intent`类型用来描述需要执行的操作。  
`Intent`类型拥有多种构造方法：

```java
public class Intent implements Parcelable, Cloneable {
	...
	public Intent(Context packageContext, Class<?> cls);
	public Intent(String action, Uri uri);
	public Intent(String action, Uri uri, Context packageContext, Class<?> cls);
	...
}
```

`Intent`常用于：

- 启动`Activity`(`startActivity()`方法)
- 启动`Service`(`startService()`方法)
- 与后端`Service`通信(`bindService()`方法)

### *Standard Extra Data*
`Intent`在通信时可添加附加数据。

使用`putExtra()`方法为Intent实例添加附加数据，使用`getXxxExtra()`从Intent实例中获取附加数据。

`putExtra()`方法接收字符串和数据内容做为参数，字符串做为数据的名称，数据内容可为多种类型。  
`putExtra()`方法包含一系列重载，用于传入不同类型的数据：

```java
public class Intent implements Parcelable, Cloneable {
	...
	public Intent putExtra(String name, int value);
	public Intent putExtra(String name, String value);
	public Intent putExtra(String name, Parcelable value);
	public Intent putExtra(String name, Serializable value);
	...
}
```

可直接将实现了`Parcelable/Serializable`接口的实例做为数据内容传入(序列化)。

`getXxxExtra()`系列方法针对不同类型的数据内容提供了获取功能：

```java
public class Intent implements Parcelable, Cloneable {
	...
	public int getIntExtra(String name, int defaultValue);
	public String getStringExtra(String name);
	public <T extends Parcelable> T getParcelableExtra(String name);
	public Serializable getSerializableExtra(String name);
	...
}
```

返回`Object`类型的`getExtra()`方法现在已经废弃，不推荐使用。



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

使用`Fragment`创建菜单时，需要在`Fragment`创建时调用`setHasOptionsMenu()`方法，
传递`true`参数才能使`Fragment`的`onCreateOptionsMenu()`方法被调用：

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
从`Android 3.0 (API Level 11)`开始，`Activity`带有`ActionBar`做为主菜单栏。

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
    setDisplayHomeAsUpEnabled(true) //显示返回按钮
    setDisplayShowCustomEnabled(true)
    setDisplayShowHomeEnabled(true)
    setDisplayShowTitleEnabled(true)
    setDisplayUseLogoEnabled(true) //显示 APP Logo
}
```
