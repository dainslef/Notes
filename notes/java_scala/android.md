<!-- TOC -->

- [环境搭建](#环境搭建)
	- [管理 *Android SDK*](#管理-android-sdk)
	- [项目结构](#项目结构)
	- [构建定义](#构建定义)

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

在`Android`项目中添加`Kotlin`支持，在`app/build.gradle`中追加以下内容：

```groovy
apply plugin: 'kotlin-android'

dependencies {
    compile "org.jetbrains.kotlin:kotlin-stdlib-jre7:$kotlin_version"
}
```
