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
	- [保存 *Activity* 状态](#保存-activity-状态)
- [*Fragment*](#fragment)
	- [*Fragment View*](#fragment-view)
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
	- [*ToolBar*](#toolbar)
- [*LinearLayout*](#linearlayout)
	- [布局比例分配](#布局比例分配)
- [*ScrollView*](#scrollview)
	- [嵌套 *ScrollView* 滑动冲突](#嵌套-scrollview-滑动冲突)
- [*Android Design Support Library*](#android-design-support-library)
	- [*TabLayout*](#tablayout)
	- [*AppBarLayout*](#appbarlayout)

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
 │    ├── arrays.xml # 数组资源定义
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
	
	路径下的每个文件会在所属路径对应的静态内部类中生成资源ID变量。

- `res/values`路径下的资源文件直接生成对应**静态内部类**：

	- `res/values/strings.xml`
	- `res/values/colors.xml`
	- `res/values/styles.xml`
	- `res/values/arrays.xml`

	文件内的每个资源定义会根据资源类型在对应的静态内部类中生成资源ID变量。

- 使用`android:id`属性定义的资源ID会在静态内部类`R.id`中生成对应资源ID变量。

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
	// 对应 res/values/arrays.xml 文件内的资源定义
	public static final class array {
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
	// 对应使用 android:id 属性定义的资源
	public static final class id {
		...
		public static final int xxx = 0x????;
		...
	}
	...
}
```



## *Activity*
`Activity`是Android系统中的核心组件，每个Activity对应一个独立的应用窗口。  
Activity类似于`Swing`中的`JFrame`、`Qt`中的`QWindow`、`JavaFx`中的`Stage`，
做为应用的顶层窗口存在，一个应用可以由一个/多个Activity构成。

多个Activity之间可相互跳转，并传递信息。  
跳转到新的Activity时，旧的Activity会停止并驻留在返回栈上，使用返回按钮会销毁新Activity，并恢复原Activity。  
启动时呈现的Activity为**主Activity(MainActivity)**，**主Activity**销毁会退出应用。

### *View* (视图)
`android.view.View`及其子类用于为`Activity`提供用户界面。  
`View`类型存在子类`ViewGroup`，可做为容器容纳其它`View`。

在Android项目使用`XML`语法描述视图布局，在`app/res/layout`路径下添加视图资源文件，
重写父类Activity的`onCreate()`方法，在其中调用`setContentView()`，传入资源ID来设定Activity的视图。  
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

使用`setContentView()`将视图资源设置到`Activity`后，视图资源的描述的每一个容器、控件皆可由`findViewById()`方法通过视图`ID`获取对应的视图实例(需要对应控件在`XML`定义中声明了`android:id`属性)。  
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

Android项目中亦可如`Swing`一般使用纯Java代码构建视图，但语法过于繁琐，通常不使用。

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

### 保存 *Activity* 状态
Activity在下列事件发生时会重新构造：

- 设备屏幕旋转
- 系统内存不足时被清理，再度主动打开

重建的Activity状态会被重置(重新构造Activity实例)。  
若需要保存应用状态，应重写`onSaveInstanceState()`方法，相关定义如下：

```java
public class Activity extends ... {
	...
	protected void onSaveInstanceState(Bundle outState);
	public void onSaveInstanceState(Bundle outState, PersistableBundle outPersistentState);
	...
}
```

将需要保存状态的字段传入`outState`参数中。  
当Activity重建时，会调用`onRestoreInstanceState()`方法，相关定义如下：

```java
public class Activity extends ... {
	...
	protected void onRestoreInstanceState(Bundle savedInstanceState);
	public void onRestoreInstanceState(Bundle savedInstanceState, PersistableBundle persistentState);
	...
}
```

Activity销毁前存入`outState`参数中的字段可从`onRestoreInstanceState()`方法的`savedInstanceState`参数中取出，用于恢复Activity状态。



## *Fragment*
`Fragment`是`Android 3.0 (API Level 11)`开始引入的新UI组件。

Fragment被称为**片段**，用来组成Activity中的UI部分。  
一个Activity可由一个或多个Fragment组成，多个Activity亦可共享同一个Fragment。

Fragment有独立的事件处理、生命周期。  
但Fragment必须始终嵌入在Activity中，其生命周期直接受宿主Activity生命周期的影响：

- 宿主Activity暂停时，包含的子Fragment都将暂停。
- 宿主Activity销毁时，包含的子Fragment都将被销毁。

### *Fragment View*
与`Activity`类似，Fragment可以使用XML资源文件描述UI布局，在`app/res/layout`路径下添加视图资源文件，
重写父类Fragment的`onCreateView()`方法，在其中调用`LayoutInflater`实例的`inflate()`方法，传入资源ID来设定Fragment的视图。  
如下所示：

```kotlin
class XxxFragment : Fragment() {

    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?,
                              savedInstanceState: Bundle?): View? {
        // 通过视图资源ID设定Fragment的视图
        return inflater!!.inflate(R.layout.fragment_xxx, container, false)
    }

    ...

}
```

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

- `<menu>` 菜单的**根节点**。`<menu>`能够包含一个或多个`<item>`和`<group>`子节点。
- `<item>` 菜单项(`MenuItem`)，可包含`<menu>`子节点(创建子菜单)。
- `<group>` 菜单组，对菜单进行编组，同组内的菜单共享可选、可见性等属性。

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

### *ToolBar*
原生`ActionBar`具有以下缺陷：

- 仅支持`Android 3.0 (API Level 11)`以上的系统。
- 在不同的Android系统版本中，ActionBar的行为有差异。
- ActionBar仅能位于APP中的固定位置，灵活性欠佳，不利于APP设计。

支持库组件`android.support.v7.widget.Toolbar`提供了与原生ActionBar行为、外观类似的菜单工具栏。  
ToolBar相比原生ActionBar有以下优势：

- 支持`Android 2.1（API Level 7`以上的系统。
- 在不同版本的系统中具有更好的行为一致性。
- 可自由定义ToolBar，配合`AppBarLayout`，可实现滚动隐藏等高级特效。

使用ToolBar需要禁用系统布局中的原生ActionBar，使用`NoActionBar`主题。  
在`app/manifests/AndroidManifest.xml`文件中的`<application/>`节点中将`android:theme`属性设置为`@style/Theme.AppCompat.Light.NoActionBar`，如下所示：

```xml
<application
	android:theme="@style/Theme.AppCompat.Light.NoActionBar"
	.../>
```

在布局文件中声明ToolBar：

```xml
<android.support.v7.widget.Toolbar
   	android:id="@+id/toolBar"
   	android:layout_width="match_parent"
   	android:layout_height="?attr/actionBarSize"
   	android:background="?attr/colorPrimary"
   	android:elevation="4dp"/>
```

ToolBar与ActionBar类似，通过`res/menu`下的菜单资源文件来设定菜单内容。  
在`Activity`子类中重写`onCreateOptionsMenu()`方法设定菜单内容，重写`onCreate()`方法设置ToolBar：

```kotlin
class XxxActivity : AppCompatActivity() {

    val toolBar by lazy { findViewById(R.id.xxxToolBar) }

    override fun onCreate(savedInstanceState: Bundle?) {

        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_xxx)

        // 设置 ToolBar
        setSupportActionBar(toolbar)

    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {

        // 设置菜单内容
        menuInflater.inflate(R.menu.menu_xxx, menu)
        return super.onCreateOptionsMenu(menu)

    }

}
```

默认情况下，ToolBar的菜单按钮为**黑色**，可通过自定义`colorControlNormal`属性手动指定菜单按钮颜色。  
在`app/res/values/styles.xml`文件中添加：

```xml
<style name="tooBarTheme">
    <!-- 定义菜单按钮的色彩-->
    <item name="colorControlNormal">@android:color/xxx</item>
</style>
```

之后在布局文件的ToolBar声明中添加`app:theme`属性引用主题：

```xml
<android.support.v7.widget.Toolbar
    ...
    app:theme="@style/tooBarTheme"/>
```

注意ToolBar必须以`app:theme`属性引用Style才能使菜单按钮色彩生效，使用`style`属性引用不生效。



## *LinearLayout*
`LinearLayout`提供了基本的单向排列布局，布局内的控件按水平/垂直方向排列。  
在布局文件中声明：

```xml
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
              android:layout_width="match_parent"
              android:layout_height="match_parent"
              android:paddingLeft="16dp"
              android:paddingRight="16dp"
              android:orientation="horizontal"
              android:gravity="center">

   <!-- Include other widget or layout tags here. These are considered
           "child views" or "children" of the linear layout -->

 </LinearLayout>
```

使用`android:orientation`属性设定控件的排布方向(`horizontal`水平排列控件，`vertical`垂直排列控件)。
使用`android:gravity`属性设定控件自身的对齐方式。

### 布局比例分配
`LinearLayout`支持以**百分比**设置布局内部的宽度/高度分配。

如水平布局按比例分配，需要设置内部控件的宽度属性为`android:layout_width="0dp"`；
通过`android:layout_weight`属性设定每个控件的比例权重；
每个控件所占宽度比例为**当前控件的android:layout_weight值**/**布局的android:layout_weight值总和**。

实例：在一行中添加两个宽度相同的按钮，如下所示：

```xml
<LinearLayout
        android:orientation="horizontal"

        android:layout_width="match_parent"
        android:layout_height="wrap_content">

    <Button android:text="@string/button1"
            android:layout_width="0dp"
            android:layout_weight="1"
            android:layout_height="wrap_content"/>

    <Button android:text="@string/button2"
            android:layout_width="0dp"
            android:layout_weight="1"
            android:enabled="false"
            android:layout_height="wrap_content"/>

</LinearLayout>
```



## *ScrollView*
`ScrollView`为尺寸过大、无法完全显示的组件提供了滚动条。  
`Android Design Support Library`中提供了支持**关联滑动**特性的`android.support.v4.widget.NestedScrollView`，与ScrollView拥有相似的基本特性。

将目标控件包含在ScrollView/NestedScrollView中，即可为其提供滚动支持，以`TextView`为例：

```xml
<ScrollView android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:fillViewport="true">

    <TextView android:layout_width="match_parent"
              android:layout_height="match_parent"/>

</ScrollView>
```

当TextView中的文本内容超过显示空间后，会出现滚动条。

在ScrollView/NestedScrollView中的子控件使用`android:layout_height="match_parent"`属性并不能让子控件填满ScrollView的剩余空间，
若需要子控件完全填充ScrollView剩余空间，则ScrollView自身应使用`android:fillViewport="true"`属性。

### 嵌套 *ScrollView* 滑动冲突
当多个ScrollView嵌套时，内部的ScrollView**不能**正常为其包含的控件提供滑动支持。  
造成内部ScrollView滑动失效的原因是父控件处理了触摸事件并为。

如下所示，ScrollView嵌套的布局声明，滑动TextView不会产生正常的滚动文本效果：

```xml
<ScrollView android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:fillViewport="true">

    <ScrollView android:id="@+id/innerScrollView"
                android:layout_width="match_parent"
                android:layout_height="match_parent"
                android:fillViewport="true">
    
        <TextView android:layout_width="match_parent"
                  android:layout_height="match_parent"/>
    
    </ScrollView>

</ScrollView>
```

解决方案是在内部ScrollView的触摸事件回调中使用`requestDisallowInterceptTouchEvent()`方法让父ScrollView将事件交由内部ScrollView处理。  
重写`onStart()`方法，如下所示：

```kotlin
override fun onStart() {

    // 禁止 Parent View 处理子控件的触摸动作
    innerScrollView.apply {
        setOnTouchListener { _, _ ->
            requestDisallowInterceptTouchEvent(true)
            false
        }
    }

}
```



## *Android Design Support Library*
`Android 5.0 (API Level 21)`之后官方发布了`Android Design Support Library`。  
`Android Design Support Library`提供了更多现代的、符合的`Material Design`设计规范的控件。

使用`Android Design Support Library`，在`app/build.gradle`文件中添加依赖：

```groovy
dependencies {
    compile 'com.android.support:design:xx.x.x'
}
```

### *TabLayout*
`android.support.design.widget.TabLayout`提供了更加简洁的Tab页实现。  
在布局资源文件中声明`TabLayout`：

```xml
<android.support.design.widget.TabLayout

        android:id="@+id/tabLayout"

        android:layout_height="50dp"
        android:layout_width="match_parent"

        app:tabBackground="@color/colorPrimary"
        app:tabIndicatorColor="@android:color/white"
        app:tabTextColor="@android:color/darker_gray"
        app:tabSelectedTextColor="@android:color/white"
        app:tabIndicatorHeight="4dp">

    <!-- 使用 setupWithViewPager() 绑定 FragmentPagerAdapter 时，直接在节点内添加的 TabItem 不生效 -->
    <android.support.design.widget.TabItem
            android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:text="@string/xxx"/>
    <android.support.design.widget.TabItem
            android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:text="@string/xxx"/>

</android.support.design.widget.TabLayout>
```

TabLayout中的常用属性：

- `app:tabBackground` 标签栏背景
- `app:tabIndicatorColor` 标签指示器色彩
- `app:tabTextColor` 普通标签文本色彩
- `app:tabSelectedTextColor` 选中标签的文本色彩
- `app:tabIndicatorHeight` 标签指示器的高度

`<TabLayout/>`节点内可以使用`<TabItem/>`节点直接添加具体的标签项。  
通过`addOnTabSelectedListener()`方法设定点击监听器：

```kotlin
tabLayout.addOnTabSelectedListener(object : TabLayout.OnTabSelectedListener {
    override fun onTabReselected(tab: TabLayout.Tab?) { ... }
    override fun onTabUnselected(tab: TabLayout.Tab?) { ... }
    override fun onTabSelected(tab: TabLayout.Tab?) { ... }
})
```

TabLayout可搭配`ViewPager`使用，搭配ViewPager时**无需**使用`addOnTabSelectedListener()`设定监听器。  
如下所示：

```koltin
viewPager.adapter = object : FragmentPagerAdapter(supportFragmentManager) {
    override fun getItem(position: Int) = ...
    override fun getCount() = ...
    override fun getPageTitle(position: Int) = ...
}
tabLayout.setupWithViewPager(viewPager)
```

使用`setupWithViewPager()`方法设定ViewPager后，布局文件中声明的`TabItem`不生效，
Tab标签文本由`FragmentPagerAdapter`适配器的`getPageTitle()`方法决定。

### *AppBarLayout*
`android.support.design.widget.AppBarLayout`提供了对顶栏菜单的布局支持，搭配`ToolBar`，能实现复杂的顶栏效果。  
AppBarLayout布局与纵向LinearLayout类似，布局内的组件依次在垂直方向上排列。  
被AppBarLayout布局包含的内容均作为顶栏存在。  
在布局文件中声明AppBarLayout：

```xml
<android.support.design.widget.AppBarLayout

            android:id="@+id/appBarLayout"

            android:layout_height="wrap_content"
            android:layout_width="match_parent">

    <!-- ToolBar 放在 AppBarLayout 内部 -->
    <android.support.v7.widget.Toolbar/>

    ... <!-- 可以将其它内容放在 AppBarLayout中，都将作为顶栏的一部分存在 -->

</android.support.design.widget.AppBarLayout>
```

AppBarLayout在`android.support.design.widget.CoordinatorLayout`布局下，搭配`android.support.v4.widget.NestedScrollView`控件，可实现滚动隐藏工具栏效果。  
如下所示：

```xml
<android.support.design.widget.CoordinatorLayout

        xmlns:android="http://schemas.android.com/apk/res/android"
        xmlns:tools="http://schemas.android.com/tools"
        xmlns:app="http://schemas.android.com/apk/res-auto"

        android:layout_width="match_parent"
        android:layout_height="match_parent">

    <android.support.design.widget.AppBarLayout

            android:id="@+id/appBarLayout"

            android:layout_width="match_parent"
            android:layout_height="wrap_content">

        <android.support.v7.widget.Toolbar

                android:id="@+id/toolbar"
                android:layout_width="match_parent"
                android:layout_height="?attr/actionBarSize"

                app:layout_scrollFlags="scroll|snap|enterAlways"

                app:titleTextColor="@android:color/white"
                app:subtitleTextColor="@android:color/darker_gray"
                app:title="@string/appName"
                app:subtitle="@string/subtitle"

                app:theme="@style/tooBarTheme"/>

    </android.support.design.widget.AppBarLayout>

    <android.support.v4.widget.NestedScrollView

            xmlns:android="http://schemas.android.com/apk/res/android"
            xmlns:tools="http://schemas.android.com/tools"

            android:layout_width="match_parent"
            android:layout_height="wrap_content"

            app:layout_behavior="@string/appbar_scrolling_view_behavior">

        ...

    </android.support.v4.widget.NestedScrollView>

</android.support.design.widget.CoordinatorLayout>
```

确保滑动隐藏工具栏效果能生效，需要注意：

- 根布局为`android.support.design.widget.CoordinatorLayout`，其它布局滑动工具拦效果不生效。
- AppBarLayout内需要滚动隐藏的组件设置了属性`app:layout_scrollFlags="scroll"`。
- AppBarLayout的相邻组件需要为支持关联滚动的组件如`android.support.v4.widget.NestedScrollView`。
- AppBarLayout的相邻的关联滚动组件需要设置属性`app:layout_behavior="@string/appbar_scrolling_view_behavior"`。

`app:layout_scrollFlags`属性取值如下(取多个属性值时用`|`操作符连接)：

- `scroll` 需要响应滚动事件的组件需要设置该属性，是其它滚动属性的前置条件，默认优先滚动关联组件
- `snap` 弹性滚动效果，下滑/上滑时，组件要么隐藏，要么完全展现，滚动距离未达要求时，当前控件回弹到之前状态
- `enterAlways` 优先滚动当前控件，发生向下滚动行为时，处于隐藏状态的控件会立即出现，而不是等待关联滚动组件滚动到顶部
- `enterAlwaysCollapsed` enterAlways的附加选项，向下滚动时，当前控件先滚动到最小高度，之后再开始滚动关联组件，关联组件滚动到顶部时再滚动当前组件到最大值
- `exitUntilCollapsed` enterAlways的附加选项，向上滚动时，当前组件缩小到最小高度，但不会完全隐藏