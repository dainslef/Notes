<!-- TOC -->

- [環境搭建](#環境搭建)
	- [管理 Android SDK](#管理-android-sdk)
	- [Intel HAXM](#intel-haxm)
- [Android Platform Tools](#android-platform-tools)
	- [Android Debug Bridge (adb)](#android-debug-bridge-adb)
	- [Fastboot](#fastboot)
- [項目構建](#項目構建)
	- [項目結構](#項目結構)
	- [構建定義](#構建定義)
	- [添加 Kotlin 支持](#添加-kotlin-支持)
- [資源](#資源)
	- [資源ID](#資源id)
- [Activity](#activity)
	- [View (視圖)](#view-視圖)
	- [啓動/結束 Activity](#啓動結束-activity)
	- [獲取 Activity 返回結果](#獲取-activity-返回結果)
	- [保存 Activity 狀態](#保存-activity-狀態)
- [Fragment](#fragment)
	- [Fragment View](#fragment-view)
	- [管理 Fragment](#管理-fragment)
	- [Fragment 數據傳遞](#fragment-數據傳遞)
- [Intent](#intent)
	- [Standard Extra Data](#standard-extra-data)
- [Menu](#menu)
	- [定義菜單](#定義菜單)
	- [菜單項屬性](#菜單項屬性)
	- [創建菜單](#創建菜單)
	- [處理菜單事件](#處理菜單事件)
	- [ActionBar](#actionbar)
	- [ToolBar](#toolbar)
- [LinearLayout](#linearlayout)
	- [佈局比例分配](#佈局比例分配)
- [ScrollView](#scrollview)
	- [嵌套 ScrollView 滑動衝突](#嵌套-scrollview-滑動衝突)
- [Android Design Support Library](#android-design-support-library)
	- [TabLayout](#tablayout)
	- [AppBarLayout](#appbarlayout)

<!-- /TOC -->



# 環境搭建
`Android`早期通過`Eclipse`外掛`ADT`(`Android Development Tools`)插件來進行開發。
`Eclipse ADT`插件現在已停止更新，官方推薦開發環境遷移到`Android Studio`。

`Android Studio`基於`IntelliJ IDEA Community`定製開發，
`IntelliJ IDEA`的`Android Support`插件提供了`Android Studio`的核心功能，啓用該插件即可進行`Android`開發。

## 管理 Android SDK
依次通過`Tools => Android => SDK Manager`進入`Android SDK`配置界面。

- `SDK Platforms`界面勾選需要的`Android SDK`版本。
- `SDK Tools`界面勾選需要的開發工具鏈。

選擇`Android SDK`時，需要注意`IntelliJ IDEA`的`Android Support`插件與`Android Studio`版本的對應關係。
如`IntelliJ IDEA 2017.2`的`Android Support`插件版本爲`10.2.3`，對應`Android Studio 2.3`，
`Android Studio 2.3`發佈時的`Android SDK`最高版本爲`API 25 (Android 7.1.1 Nougat)`。

高版本的`Android SDK`在低版本的`Android Support`插件中僅顯示`API`級別，不顯示版本信息。
如`Android 8.0 Oreo`在`Android Support 10.2.3`中僅顯示爲`API 26`。

不應使用與插件不匹配的高版本`Android SDK`(不顯示版本信息的版本)，高版本的`Android SDK`搭配低版本的`Android Support`插件可能會造成UI設計器、構建工具等出錯。

## Intel HAXM
**Android模擬器**需要`Intel HAXM`技術提供圖形加速支持，否則模擬器無法啓動。

在`Windows/Linux`平臺上，直接使用`Android Studio`安裝`Intel HAXM`。

在`macOS`平臺上，`Intel HAXM`安裝包提供的安裝腳本會檢測macOS版本，安裝腳本可能無法識別最新版macOS。
使用`Android Stduio`直接安裝`Intel HAXM`時，可能無法通過安裝腳本的檢測，
此時應在Intel官網下載安裝包，解壓得到`dpkg`格式的安裝包手動執行安裝。

`Intel HAXM`安裝完成後，在macOS下直接啓動模擬器會出現`/dev/kvm is not found`錯誤，
原因是HAXM的APP在macOS的默認安全策略下被禁止啓動，
在`System Preferences => Security & Privacy => General`選項中點擊**允許**相關APP執行。

在macOS下移除已安裝的`Intel HAXM`，執行指令：

```
sudo /System/Library/Extensions/intelhaxm.kext/Contents/Resources/uninstall.sh
```



# Android Platform Tools
`Android Platform Tools`是Android SDK提供的一系列命令行工具，
位於Android SDK下的`./platform-tools`子路徑中。
相關內容可參考[Android官方文檔](https://developer.android.com/studio/command-line/)。

Android Platform Tools可以獨立安裝，macOS/Linux通常在對應軟件倉庫中提供了安裝包：

```html
<!-- macOS -->
$ brew --cask install android-platform-tools
```

## Android Debug Bridge (adb)
[`Android Debug Bridge (adb)`](https://developer.android.com/studio/command-line/adb)工具用於與Android設備通信，
可執行一系列設備操作，例如安裝和調試應用，adb工具還提供了Unix Shell讓開發者在設備上執行一系列的指令。

adb工具為client-server架構，包含以下組件：

- client，即adb命令行工具，運行在開發機上。
- daemon(adbd)，用於在目標設備上執行指令，daemon會作為後台進程運行在每個目標設備上。
- server，用於管理client和daemon之間的通信，server會作為後台進程運行在開發機上。

當首次執行adb指令時，工具會檢測是否存在server進程，不存在則先運行server進程：

```
$ adb devices
* daemon not running; starting now at tcp:5037
* daemon started successfully
List of devices attached

$ ps -ef | grep adb
  501 41688     1   0  9:38PM ??         0:00.39 adb -L tcp:5037 fork-server server --reply-fd 4
  501 41764 21310   0  9:42PM ttys000    0:00.00 grep --color=auto adb
```

使用adb連接設備前，需要將目標設備開啟調試模式，之後從開發機可查詢到設備信息：

```
$ adb devices
List of devices attached
gi79q8rcrccedynf	device

$ adb devices -l
List of devices attached
gi79q8rcrccedynf       device usb:336658432X product:aosp_begonia model:Redmi_Note_8_Pro device:begonia transport_id:1
```

使用adb shell指令可在目標設備執行指令或直接進入目標設備的Unix Shell：

```html
<!-- 在目標設備上執行指令 -->
$ adb shell uname -a
Linux localhost 4.14.141-g1448309 #1 SMP PREEMPT Mon Jan 18 20:17:04 WIB 2021 aarch64

<!-- 進入目標設備的 Unix Shell -->
$ adb shell
begonia:/ $ ls -al
total 64
drwxr-xr-x  21 root   root       4096 2009-01-01 08:00 .
drwxr-xr-x  21 root   root       4096 2009-01-01 08:00 ..
dr-xr-xr-x 141 root   root          0 2021-03-20 12:34 acct
drwxr-xr-x  44 root   root        880 2021-03-20 12:34 apex
lrw-r--r--   1 root   root         11 2009-01-01 08:00 bin -> /system/bin
lrw-r--r--   1 root   root         50 2009-01-01 08:00 bugreports -> /data/user_de/0/com.android.shell/files/bugreports
drwxrwx---   6 system cache      4096 2021-03-16 01:12 cache
drwxr-xr-x   4 root   root          0 1970-01-01 08:00 config
lrw-r--r--   1 root   root         17 2009-01-01 08:00 d -> /sys/kernel/debug
drwxrwx--x  49 system system     4096 2021-04-11 19:42 data
d?????????   ? ?      ?             ?                ? data_mirror
drwxr-xr-x   2 root   root       4096 2009-01-01 08:00 debug_ramdisk
lrw-------   1 root   root         23 2009-01-01 08:00 default.prop -> system/etc/prop.default
drwxr-xr-x  21 root   root       5720 2021-03-20 12:34 dev
lrw-r--r--   1 root   root         11 2009-01-01 08:00 etc -> /system/etc
l?????????   ? ?      ?             ?                ? init -> ?
-?????????   ? ?      ?             ?                ? init.environ.rc
-?????????   ? ?      ?             ?                ? init.mi_thermald.rc
d?????????   ? ?      ?             ?                ? linkerconfig
drwx------   2 root   root      16384 2009-01-01 08:00 lost+found
drwxr-xr-x  16 root   system      340 2021-03-20 12:34 mnt
drwxr-xr-x   2 root   root       4096 2009-01-01 08:00 odm
drwxr-xr-x   2 root   root       4096 2009-01-01 08:00 oem
dr-xr-xr-x 655 root   root          0 1970-01-01 08:00 proc
lrw-r--r--   1 root   root         15 2009-01-01 08:00 product -> /system/product
drwxr-xr-x   3 root   root       4096 2009-01-01 08:00 res
lrw-r--r--   1 root   root         21 2009-01-01 08:00 sdcard -> /storage/self/primary
drwx--x---   5 shell  everybody   100 2021-04-11 19:42 storage
dr-xr-xr-x  15 root   root          0 2021-03-20 12:34 sys
drwxr-xr-x  14 root   root       4096 2009-01-01 08:00 system
lrw-r--r--   1 root   root         18 2009-01-01 08:00 system_ext -> /system/system_ext
drwxr-xr-x  12 root   shell      4096 2009-01-01 08:00 vendor
```

使用adb對目標設備進行文件傳輸：

```html
<!-- 從開發機傳輸文件到目標設備 -->
$ adb push [本地路徑] [目標路徑]

<!-- 從目標設備傳輸文件到開發機 -->
$ adb pull [目標路徑] [本地路徑]
```

使用adb對目標設備安裝包：

```html
$ adb install [包]
$ adb install -r [包] <!-- 替換掉已存在的包 -->
$ adb install -d [包] <!-- 允許包降級 -->

$ adb install-multiple [包...]
$ adb install-multi-package [包...]
```

## Fastboot
查看以fastboot模式連接到當前計算機的設備信息：

```
$ fastboot devices
gi79q8rcrccedynf	fastboot
$ fastboot devices -l
gi79q8rcrccedynf       fastboot usb:336592896X
```

若開發機為macOS平台，則目標設備切換到fastboot模式後可能需要重新連接數據線才能正常識別；
使用轉接頭亦可能導致目標設備無法識別。

fastboot工具可用於安裝設備鏡像。

以recovery鏡像為例，如[`TWRP`](https://twrp.me/Devices/)，
第三方recovery鏡像通常比原廠鏡像提供更多更強大的功能，也更便於使用，同時沒有刷機固件限制。

以安裝TWRP為例，從下載對應設備的官方鏡像，將設備重啟至fastboot模式，連接電腦後執行指令：

```
$ fastboot flash recovery [鏡像路徑]
```

示例：

```
$ fastboot flash recovery twrp.img
Sending 'recovery' (65536 KB)                      OKAY [  1.737s]
Writing 'recovery'                                 OKAY [  1.550s]
Finished. Total time: 3.289s
```



# 項目構建
Anddroid項目使用`Gradle`做爲構建工具。

## 項目結構
一個基本的Android項目具有以下目錄結構：

```
項目名稱
├── build.gradle
├── settings.gradle
├── gradle.properties
├── build # 構建緩存目錄
│    └── ...
├── gradle # Gradle Wrapper
│    └── ...
└── app # Android 核心目錄
     ├── build.gradle # Android 構建配置
     ├── build # Android 構建緩存
     │    └── ...
     ├── libs
     │    └── ...
     └── src # 項目源碼、資源目錄
          ├── androidTest # Android 測試
          │    └── ...
          ├── test # 單元測試
          │    └── ...
          └── main # APP主要目錄
               ├── AndroidManifest.xml
               ├── java # 源碼目錄
               │    └── ...
               └── res # 資源目錄
                    └── ...
```

## 構建定義
`Android`項目使用`Gradle`做爲構建工具，項目構建配置位於`app/build.gradle`。
構建配置基本結構如下：

```groovy
apply plugin: 'com.android.application'

android {
    compileSdkVersion xx(編譯SDK版本)
    buildToolsVersion "xx(構建工具版本)"
    defaultConfig {
        applicationId "xxx.yyy.zzz(包名)"
        minSdkVersion xx(最小SDK版本)
        targetSdkVersion xx(目標SDK版本)
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
    compile 'Xxx:Xxx:版本' //依賴項
    ...
    testCompile 'junit:junit:xxx'
}

repositories {
    mavenCentral() //使用 Maven 倉庫
}
```

## 添加 Kotlin 支持
在`Android`項目中添加`Kotlin`支持，需要以下步驟：

1. 在`build.gradle`中追加以下內容：

	```groovy
	buildscript {
	    ext.kotlin_version = 'Kotlin版本'
	    dependencies {
	        classpath "org.jetbrains.kotlin:kotlin-gradle-plugin:$kotlin_version"
	    }
	}
	```

1. 在`app/build.gradle`中追加以下內容：

	```groovy
	apply plugin: 'kotlin-android'

	dependencies {
	    compile "org.jetbrains.kotlin:kotlin-stdlib-jre7:$kotlin_version"
	}
	```



# 資源
資源是非代碼形式，如圖片、音頻、XML文件等。
在Andorid項目中，所有的資源均位於`res`路徑下。
`res`路徑下具有以下結構：

```
res
 ├── drawable # 矢量圖
 │    ├── activity_main.xml
 │    └── ...
 ├── layout # UI佈局 XML
 │    └── ...
 ├── menu # 菜單佈局 XML
 │    └── ...
 ├── values
 │    ├── colors.xml # 色彩
 │    ├── strings.xml # 字符串資源
 │    ├── styles.xml # 樣式定義
 │    ├── arrays.xml # 數組資源定義
 │    └── ...
 └── mipmap-*dpi # 不同DPI的位圖資源
      └── ...
```

## 資源ID
在Android項目構建時，`res`路徑下各類資源文件會被分配資源ID，在多數`Andorid API`中，均通過資源ID訪問資源。
資源ID定義在靜態類`R`中(`R.java`文件)中：

- 部分路徑會直接在`R`類型內生成對應名稱的**靜態內部類**：

	- `res/mipmap`
	- `res/drawable`
	- `res/layout`
	- `res/menu`

	路徑下的每個文件會在所屬路徑對應的靜態內部類中生成資源ID變量。

- `res/values`路徑下的資源文件直接生成對應**靜態內部類**：

	- `res/values/strings.xml`
	- `res/values/colors.xml`
	- `res/values/styles.xml`
	- `res/values/arrays.xml`

	文件內的每個資源定義會根據資源類型在對應的靜態內部類中生成資源ID變量。

- 使用`android:id`屬性定義的資源ID會在靜態內部類`R.id`中生成對應資源ID變量。

類型`R`的基本內容如下所示：

```java
public final class R {
	...
	// 對應 res/drawable 路徑下的資源文件
	public static final class drawable {
		...
		public static final int xxx = 0x????;
		...
	}
	// 對應 res/layout 路徑下的資源文件
	public static final class layout {
		...
		public static final int xxx = 0x????;
		...
	}
	// 對應 res/menu 路徑下的資源文件
	public static final class menu {
		...
		public static final int xxx = 0x????;
		...
	}
	// 對應 res/values/strings.xml 文件內的資源定義
	public static final class string {
		...
		public static final int xxx = 0x????;
		...
	}
	// 對應 res/values/colors.xml 文件內的資源定義
	public static final class color {
		...
		public static final int xxx = 0x????;
		...
	}
	// 對應 res/values/arrays.xml 文件內的資源定義
	public static final class array {
		...
		public static final int xxx = 0x????;
		...
	}
	// 對應 res/values/styles.xml 文件內的資源定義
	public static final class style {
		...
		public static final int xxx = 0x????;
		...
	}
	// 對應使用 android:id 屬性定義的資源
	public static final class id {
		...
		public static final int xxx = 0x????;
		...
	}
	...
}
```



# Activity
`Activity`是Android系統中的核心組件，每個Activity對應一個獨立的應用窗口。
Activity類似於`Swing`中的`JFrame`、`Qt`中的`QWindow`、`JavaFx`中的`Stage`，
做爲應用的頂層窗口存在，一個應用可以由一個/多個Activity構成。

多個Activity之間可相互跳轉，並傳遞信息。
跳轉到新的Activity時，舊的Activity會停止並駐留在返回棧上，使用返回按鈕會銷燬新Activity，並恢復原Activity。
啓動時呈現的Activity爲**主Activity(MainActivity)**，**主Activity**銷燬會退出應用。

## View (視圖)
`android.view.View`及其子類用於爲`Activity`提供用戶界面。
`View`類型存在子類`ViewGroup`，可做爲容器容納其它`View`。

在Android項目使用`XML`語法描述視圖佈局，在`app/res/layout`路徑下添加視圖資源文件，
重寫父類Activity的`onCreate()`方法，在其中調用`setContentView()`，傳入資源ID來設定Activity的視圖。
如下所示：

```kotlin
class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.xxx) //通過資源ID設置視圖
    }

    ...

}
```

使用`setContentView()`將視圖資源設置到`Activity`後，
視圖資源的描述的每一個容器、控件皆可由`findViewById()`方法通過視圖`ID`獲取對應的視圖實例
(需要對應控件在`XML`定義中聲明瞭`android:id`屬性)。
如下所示，資源文件定義如下：

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

獲取控件實例：

```kotlin
class MainActivity : AppCompatActivity() {

    val listView by lazy { findViewById(R.id.listView) as ListView }

    ...

}
```

Android項目中亦可如`Swing`一般使用純Java代碼構建視圖，但語法過於繁瑣，通常不使用。

## 啓動/結束 Activity
使用`startActivity()`方法啓動另一個`Activity`。
相關方法定義在`Activity`類中，具有多個重載：

```java
public class Activity extends ... {
	...
	public void startActivity(Intent intent);
	public void startActivity(Intent intent, @Nullable Bundle options)；
	...
}
```

`intent`參數使用目標Activity的**Class實例**做爲參數，指定需要啓動的目標Activity類型。
`intent`參數亦可附加傳遞數據、實例。
如下所示：

```kotlin
startActivity(Intent(this, OtherActicity::class.java))
```

結束`Activity`使用`finish()`方法：

```java
public class Activity extends ... {
	...
	public void finish();
	...
}
```

結束一個Activity後會回到上一個Activity。
若結束的是**主Activity**，則會退出應用。

## 獲取 Activity 返回結果
對於需要獲取返回結果的`Activity`啓動任務，應使用`startActivityForResult()`相關方法啓動：

```java
public class Activity extends ... {
	...
	public void startActivityForResult(@RequiresPermission Intent intent, int requestCode);
	public void startActivityForResult(@RequiresPermission Intent intent, int requestCode, @Nullable Bundle options);
	...
}
```

同時重寫`onActivityResult()`方法，該方法在目標`Activity`返回後會被回調：

```java
public class Activity extends ... {
	...
	protected void onActivityResult(int requestCode, int resultCode, Intent data);
	...
}
```

`requestCode`參數由`startActivityForResult()`時傳入，用於區分不同的啓動任務。
目標Activity在`finish()`調用前應使用`setResult()`方法設定返回值。

```java
public class Activity extends ... {
	...
	public final void setResult(int resultCode);
	public final void setResult(int resultCode, Intent data);
	...
}
```

## 保存 Activity 狀態
Activity在下列事件發生時會重新構造：

- 設備屏幕旋轉
- 系統內存不足時被清理，再度主動打開

重建的Activity狀態會被重置(重新構造Activity實例)。
若需要保存應用狀態，應重寫`onSaveInstanceState()`方法，相關定義如下：

```java
public class Activity extends ... {
	...
	protected void onSaveInstanceState(Bundle outState);
	public void onSaveInstanceState(Bundle outState, PersistableBundle outPersistentState);
	...
}
```

將需要保存狀態的字段傳入`outState`參數中。
當Activity重建時，會調用`onRestoreInstanceState()`方法，相關定義如下：

```java
public class Activity extends ... {
	...
	protected void onRestoreInstanceState(Bundle savedInstanceState);
	public void onRestoreInstanceState(Bundle savedInstanceState, PersistableBundle persistentState);
	...
}
```

Activity銷燬前存入`outState`參數中的字段可從`onRestoreInstanceState()`方法的`savedInstanceState`參數中取出，用於恢復Activity狀態。



# Fragment
`Fragment`是`Android 3.0 (API Level 11)`開始引入的新UI組件。

Fragment被稱爲**片段**，用來組成Activity中的UI部分。
一個Activity可由一個或多個Fragment組成，多個Activity亦可共享同一個Fragment。

Fragment有獨立的事件處理、生命週期。
但Fragment必須始終嵌入在Activity中，其生命週期直接受宿主Activity生命週期的影響：

- 宿主Activity暫停時，包含的子Fragment都將暫停。
- 宿主Activity銷燬時，包含的子Fragment都將被銷燬。

## Fragment View
與`Activity`類似，Fragment可以使用XML資源文件描述UI佈局，在`app/res/layout`路徑下添加視圖資源文件，
重寫父類Fragment的`onCreateView()`方法，在其中調用`LayoutInflater`實例的`inflate()`方法，
傳入資源ID來設定Fragment的視圖。

如下所示：

```kotlin
class XxxFragment : Fragment() {

    override fun onCreateView(inflater: LayoutInflater?, container: ViewGroup?,
                              savedInstanceState: Bundle?): View? {
        // 通過視圖資源ID設定Fragment的視圖
        return inflater!!.inflate(R.layout.fragment_xxx, container, false)
    }

    ...

}
```

## 管理 Fragment
Activity可在運行時動態地添加與移除、替換Fragment。

`FragmentManager`類型提供了對Fragment的管理操作。
Activity類型提供了`getFragmentManager()`方法，用於獲取FragmentManager實例：

```java
public class Activity extends ... {
	...
	public FragmentManager getFragmentManager();
	...
}
```

- 獲取 *Fragment*

	FragmentManager類型提供了`findFragmentById()`方法，通過傳入資源ID獲取指定Fragment實例：

	```java
	public class Fragment implements ComponentCallbacks2, OnCreateContextMenuListener {
		...
		public abstract Fragment findFragmentById(int id);
		...
	}
	```

	當指定的Fragment未被初始化時，`findFragmentById()`方法會返回空指針，
	因而在獲取Fragment時應進行`NullCheck`。

	如下所示：

	```kotlin
	val xxxFragment by lazy {
	    fragmentManager.findFragmentById(R.id.xxxFragment) ?: XxxFragment()
	}
	```

- *Fragment* 事務(添加、移除、替換、顯示、隱藏)

	FragmentManager類型提供了`beginTransaction()`方法用於啓動事務：

	```java
	public abstract class FragmentManager {
		...
		public abstract FragmentTransaction beginTransaction();
		...
	}
	```

	事務類型`FragmentTransaction`提供對Fragment增加、刪除、替換、隱藏、顯示等操作，以及對事務的提交：

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

	`containerViewId`參數可以是任意常見容器View的資源ID，如`FrameLayout、LinearLayout`等。
	在一個事務中完成各類Fragment操作後提交事務，入下所示：

	```kotlin
	fragmentManager.beginTransaction().apply {
	    add(R.id.xxx, xxxFragment)
	    remove(yyyFragment)
	    ...
	    commit()
	}
	```

## Fragment 數據傳遞
Fragment通過`setArguments()/getArguments()`方法傳遞`Bundle`類型的數據。
相關方法定義如下：

```java
public class Fragment implements ComponentCallbacks2, OnCreateContextMenuListener {
	...
	public void setArguments(Bundle args);
	final public Bundle getArguments();
	...
}
```

`Bundle`類型擁有一系列`getXxx()/setXxx()`方法用於**獲取/設置**指定類型的數據。
與`Intent`類型類似，`Bundle`類型傳遞數據的方法`setXxx()`接收字符串和數據內容做爲參數(數據內容由字符串作爲`Key`)，
獲取數據的相關方法`getXxx()`使用字符串標`Key`提取指定的數據。



# Intent
`Intent`類型用來描述需要執行的操作。
`Intent`類型擁有多種構造方法：

```java
public class Intent implements Parcelable, Cloneable {
	...
	public Intent(Context packageContext, Class<?> cls);
	public Intent(String action, Uri uri);
	public Intent(String action, Uri uri, Context packageContext, Class<?> cls);
	...
}
```

`Intent`常用於：

- 啓動`Activity`(`startActivity()`方法)
- 啓動`Service`(`startService()`方法)
- 與後端`Service`通信(`bindService()`方法)

## Standard Extra Data
`Intent`在通信時可添加附加數據。

使用`putExtra()`方法爲Intent實例添加附加數據，使用`getXxxExtra()`從Intent實例中獲取附加數據。

`putExtra()`方法接收字符串和數據內容做爲參數，字符串做爲數據的名稱，數據內容可爲多種類型。
`putExtra()`方法包含一系列重載，用於傳入不同類型的數據：

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

可直接將實現了`Parcelable/Serializable`接口的實例做爲數據內容傳入(序列化)。

`getXxxExtra()`系列方法針對不同類型的數據內容提供了獲取功能：

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

返回`Object`類型的`getExtra()`方法現在已經廢棄，不推薦使用。



# Menu
`Android`系統中包括三類菜單：

- 選項菜單和應用欄
- 上下文菜單
- 彈出菜單

從`Android 3.0 (API Level 11)`開始，設備不再擁有獨立菜單鍵，而是使用`Action Bar`提供主菜單。

## 定義菜單
在`app/res/menu`路徑下添加菜單的`XML`定義。
菜單對應`XML`文件的名稱會做爲菜單的資源`ID`，
如菜單定義爲`app/res/menu_main.xml`，則對應資源爲`R.menu.menu_main`。

菜單定義包括以下元素：

- `<menu>` 菜單的**根節點**。`<menu>`能夠包含一個或多個`<item>`和`<group>`子節點。
- `<item>` 菜單項(`MenuItem`)，可包含`<menu>`子節點(創建子菜單)。
- `<group>` 菜單組，對菜單進行編組，同組內的菜單共享可選、可見性等屬性。

基本的菜單定義示例如下：

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

## 菜單項屬性
菜單節點`<item>`的常用屬性：

- `android:title` 菜單顯示文本
- `android:icon` 菜單圖標
- `app:showAsAction` 菜單的展示方式，取值如下：

	- `alaways` 總是顯示
	- `never` 從不顯示
	- `ifRoom` 有足夠空間時顯示

## 創建菜單
在`Activity`及其子類中通過重寫`onCreateOptionsMenu()`方法創建菜單：

```kotlin
override fun onCreateOptionsMenu(menu: Menu?): Boolean {
    menuInflater.inflate(R.menu.Xxx, menu) //R.menu.Xxx 爲菜單對應的資源ID
    return true
}
```

`Fragment`亦可擁有菜單，通過重寫`Fragment`類的`onCreateOptionsMenu()`方法創建菜單：

```kotlin
override fun onCreateOptionsMenu(menu: Menu?, inflater: MenuInflater?) {
    inflater?.inflate(R.menu.Xxx, menu)
}
```

使用`Fragment`創建菜單時，需要在`Fragment`創建時調用`setHasOptionsMenu()`方法，
傳遞`true`參數才能使`Fragment`的`onCreateOptionsMenu()`方法被調用：

```kotlin
override fun onCreate(savedInstanceState: Bundle?) {

    super.onCreate(savedInstanceState)
    ...

    // 啓用菜單，否則 Fragment 中重寫的 onCreateOptionsMenu() 方法不被調用
    setHasOptionsMenu(true)
}
```

## 處理菜單事件
`Activity/Fragment`處理菜單事件方法類似，通過重寫基類的`onOptionsItemSelected()`方法響應菜單選擇事件：

```kotlin
override fun onOptionsItemSelected(item: MenuItem?): Boolean {

   ....

   return true
}
```

## ActionBar
從`Android 3.0 (API Level 11)`開始，`Activity`帶有`ActionBar`做爲主菜單欄。

在`Activity`子類中使用`getActionBar()`獲取`ActionBar`：

```kotlin
val bar = actionBar
```

在`Fragment`中獲取`ActionBar`：

```kotlin
val bar = activity.actionBar
```

對於`AppCompatActivity`的子類，應使用`getSupportActionBar()`方法獲取`ActionBar`：

```kotlin
//在 AppCompatActivity 子類中獲取 ActionBar
val bar = supportActionBar

//在 Fragment 中獲取 AppCompatActivity 子類的 ActionBar
val bar = activity.supportActionBar
```

在`AppCompatActivity`子類中使用`getActionBar()`會得到`null`。

獲取`ActionBar`可用於設定主菜單的顯示標題、Logo、返回菜單等。
在`Activity/Fragment`子類中使用`setDisplayOptions()`方法設定在`ActionBar`中顯示的內容。
`setDisplayOptions()`方法具有以下重載：

```java
public abstract void setDisplayOptions(@DisplayOptions int options);
public abstract void setDisplayOptions(@DisplayOptions int options, @DisplayOptions int mask);
```

`options`參數設定啓用的內容，`mask`參數設定禁用的內容，多個參數使用邏輯與操作符`|`連接。
可使用以下選項：

```
DISPLAY_USE_LOGO
DISPLAY_SHOW_HOME
DISPLAY_HOME_AS_UP
DISPLAY_SHOW_TITLE
DISPLAY_SHOW_CUSTOM
```

亦可使用單獨的方法獨立地設置顯示內容：

```kotlin
actionBar?.apply {
    setDisplayHomeAsUpEnabled(true) //顯示返回按鈕
    setDisplayShowCustomEnabled(true)
    setDisplayShowHomeEnabled(true)
    setDisplayShowTitleEnabled(true)
    setDisplayUseLogoEnabled(true) //顯示 APP Logo
}
```

## ToolBar
原生`ActionBar`具有以下缺陷：

- 僅支持`Android 3.0 (API Level 11)`以上的系統。
- 在不同的Android系統版本中，ActionBar的行爲有差異。
- ActionBar僅能位於APP中的固定位置，靈活性欠佳，不利於APP設計。

支持庫組件`android.support.v7.widget.Toolbar`提供了與原生ActionBar行爲、外觀類似的菜單工具欄。
ToolBar相比原生ActionBar有以下優勢：

- 支持`Android 2.1（API Level 7`以上的系統。
- 在不同版本的系統中具有更好的行爲一致性。
- 可自由定義ToolBar，配合`AppBarLayout`，可實現滾動隱藏等高級特效。

使用ToolBar需要禁用系統佈局中的原生ActionBar，使用`NoActionBar`主題。
在`app/manifests/AndroidManifest.xml`文件中的`<application/>`節點中，
將`android:theme`屬性設置爲`@style/Theme.AppCompat.Light.NoActionBar`，如下所示：

```xml
<application
	android:theme="@style/Theme.AppCompat.Light.NoActionBar"
	.../>
```

在佈局文件中聲明ToolBar：

```xml
<android.support.v7.widget.Toolbar
   	android:id="@+id/toolBar"
   	android:layout_width="match_parent"
   	android:layout_height="?attr/actionBarSize"
   	android:background="?attr/colorPrimary"
   	android:elevation="4dp"/>
```

ToolBar與ActionBar類似，通過`res/menu`下的菜單資源文件來設定菜單內容。
在`Activity`子類中重寫`onCreateOptionsMenu()`方法設定菜單內容，重寫`onCreate()`方法設置ToolBar：

```kotlin
class XxxActivity : AppCompatActivity() {

    val toolBar by lazy { findViewById(R.id.xxxToolBar) }

    override fun onCreate(savedInstanceState: Bundle?) {

        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_xxx)

        // 設置 ToolBar
        setSupportActionBar(toolbar)

    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {

        // 設置菜單內容
        menuInflater.inflate(R.menu.menu_xxx, menu)
        return super.onCreateOptionsMenu(menu)

    }

}
```

默認情況下，ToolBar的菜單按鈕爲**黑色**，可通過自定義`colorControlNormal`屬性手動指定菜單按鈕顏色。
在`app/res/values/styles.xml`文件中添加：

```xml
<style name="tooBarTheme">
    <!-- 定義菜單按鈕的色彩-->
    <item name="colorControlNormal">@android:color/xxx</item>
</style>
```

之後在佈局文件的ToolBar聲明中添加`app:theme`屬性引用主題：

```xml
<android.support.v7.widget.Toolbar
    ...
    app:theme="@style/tooBarTheme"/>
```

注意ToolBar必須以`app:theme`屬性引用Style才能使菜單按鈕色彩生效，使用`style`屬性引用不生效。



# LinearLayout
`LinearLayout`提供了基本的單向排列布局，佈局內的控件按水平/垂直方向排列。
在佈局文件中聲明：

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

使用`android:orientation`屬性設定控件的排布方向(`horizontal`水平排列控件，`vertical`垂直排列控件)。
使用`android:gravity`屬性設定控件自身的對齊方式。

## 佈局比例分配
`LinearLayout`支持以**百分比**設置佈局內部的寬度/高度分配。

如水平佈局按比例分配，需要設置內部控件的寬度屬性爲`android:layout_width="0dp"`；
通過`android:layout_weight`屬性設定每個控件的比例權重；
每個控件所佔寬度比例爲**當前控件的android:layout_weight值**/**佈局的android:layout_weight值總和**。

實例：在一行中添加兩個寬度相同的按鈕，如下所示：

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



# ScrollView
`ScrollView`爲尺寸過大、無法完全顯示的組件提供了滾動條。
`Android Design Support Library`中提供了支持**關聯滑動**特性的`android.support.v4.widget.NestedScrollView`，
與ScrollView擁有相似的基本特性。

將目標控件包含在ScrollView/NestedScrollView中，即可爲其提供滾動支持，以`TextView`爲例：

```xml
<ScrollView android:layout_width="match_parent"
            android:layout_height="match_parent"
            android:fillViewport="true">

    <TextView android:layout_width="match_parent"
              android:layout_height="match_parent"/>

</ScrollView>
```

當TextView中的文本內容超過顯示空間後，會出現滾動條。

在ScrollView/NestedScrollView中的子控件
使用`android:layout_height="match_parent"`屬性並不能讓子控件填滿ScrollView的剩餘空間，
若需要子控件完全填充ScrollView剩餘空間，則ScrollView自身應使用`android:fillViewport="true"`屬性。

## 嵌套 ScrollView 滑動衝突
當多個ScrollView嵌套時，內部的ScrollView**不能**正常爲其包含的控件提供滑動支持。
造成內部ScrollView滑動失效的原因是父控件處理了觸摸事件併爲。

如下所示，ScrollView嵌套的佈局聲明，滑動TextView不會產生正常的滾動文本效果：

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

解決方案是在內部ScrollView的觸摸事件回調中，
使用`requestDisallowInterceptTouchEvent()`方法讓父ScrollView將事件交由內部ScrollView處理。
重寫`onStart()`方法，如下所示：

```kotlin
override fun onStart() {

    // 禁止 Parent View 處理子控件的觸摸動作
    innerScrollView.apply {
        setOnTouchListener { _, _ ->
            requestDisallowInterceptTouchEvent(true)
            false
        }
    }

}
```



# Android Design Support Library
`Android 5.0 (API Level 21)`之後官方發佈了`Android Design Support Library`。
`Android Design Support Library`提供了更多現代的、符合的`Material Design`設計規範的控件。

使用`Android Design Support Library`，在`app/build.gradle`文件中添加依賴：

```groovy
dependencies {
    compile 'com.android.support:design:xx.x.x'
}
```

## TabLayout
`android.support.design.widget.TabLayout`提供了更加簡潔的Tab頁實現。
在佈局資源文件中聲明`TabLayout`：

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

    <!-- 使用 setupWithViewPager() 綁定 FragmentPagerAdapter 時，直接在節點內添加的 TabItem 不生效 -->
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

TabLayout中的常用屬性：

- `app:tabBackground` 標籤欄背景
- `app:tabIndicatorColor` 標籤指示器色彩
- `app:tabTextColor` 普通標籤文本色彩
- `app:tabSelectedTextColor` 選中標籤的文本色彩
- `app:tabIndicatorHeight` 標籤指示器的高度

`<TabLayout/>`節點內可以使用`<TabItem/>`節點直接添加具體的標籤項。
通過`addOnTabSelectedListener()`方法設定點擊監聽器：

```kotlin
tabLayout.addOnTabSelectedListener(object : TabLayout.OnTabSelectedListener {
    override fun onTabReselected(tab: TabLayout.Tab?) { ... }
    override fun onTabUnselected(tab: TabLayout.Tab?) { ... }
    override fun onTabSelected(tab: TabLayout.Tab?) { ... }
})
```

TabLayout可搭配`ViewPager`使用，搭配ViewPager時**無需**使用`addOnTabSelectedListener()`設定監聽器。
如下所示：

```koltin
viewPager.adapter = object : FragmentPagerAdapter(supportFragmentManager) {
    override fun getItem(position: Int) = ...
    override fun getCount() = ...
    override fun getPageTitle(position: Int) = ...
}
tabLayout.setupWithViewPager(viewPager)
```

使用`setupWithViewPager()`方法設定ViewPager後，佈局文件中聲明的`TabItem`不生效，
Tab標籤文本由`FragmentPagerAdapter`適配器的`getPageTitle()`方法決定。

## AppBarLayout
`android.support.design.widget.AppBarLayout`提供了對頂欄菜單的佈局支持，
搭配`ToolBar`，能實現複雜的頂欄效果。
AppBarLayout佈局與縱向LinearLayout類似，佈局內的組件依次在垂直方向上排列。
被AppBarLayout佈局包含的內容均作爲頂欄存在。
在佈局文件中聲明AppBarLayout：

```xml
<android.support.design.widget.AppBarLayout

            android:id="@+id/appBarLayout"

            android:layout_height="wrap_content"
            android:layout_width="match_parent">

    <!-- ToolBar 放在 AppBarLayout 內部 -->
    <android.support.v7.widget.Toolbar/>

    ... <!-- 可以將其它內容放在 AppBarLayout中，都將作爲頂欄的一部分存在 -->

</android.support.design.widget.AppBarLayout>
```

AppBarLayout在`android.support.design.widget.CoordinatorLayout`佈局下，
搭配`android.support.v4.widget.NestedScrollView`控件，可實現滾動隱藏工具欄效果。
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

確保滑動隱藏工具欄效果能生效，需要注意：

- 根佈局爲`android.support.design.widget.CoordinatorLayout`，其它佈局滑動工具攔效果不生效。
- AppBarLayout內需要滾動隱藏的組件設置了屬性`app:layout_scrollFlags="scroll"`。
- AppBarLayout的相鄰組件需要爲支持關聯滾動的組件如`android.support.v4.widget.NestedScrollView`。
- AppBarLayout的相鄰的關聯滾動組件需要設置屬性`app:layout_behavior="@string/appbar_scrolling_view_behavior"`。

`app:layout_scrollFlags`屬性取值如下(取多個屬性值時用`|`操作符連接)：

- `scroll` 需要響應滾動事件的組件需要設置該屬性，是其它滾動屬性的前置條件，默認優先滾動關聯組件
- `snap` 彈性滾動效果，下滑/上滑時，組件要麼隱藏，要麼完全展現，滾動距離未達要求時，當前控件回彈到之前狀態
- `enterAlways` 優先滾動當前控件，發生向下滾動行爲時，處於隱藏狀態的控件會立即出現，而不是等待關聯滾動組件滾動到頂部
- `enterAlwaysCollapsed` enterAlways的附加選項，向下滾動時，當前控件先滾動到最小高度，之後再開始滾動關聯組件，關聯組件滾動到頂部時再滾動當前組件到最大值
- `exitUntilCollapsed` enterAlways的附加選項，向上滾動時，當前組件縮小到最小高度，但不會完全隱藏
