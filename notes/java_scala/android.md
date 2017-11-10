<!-- TOC -->

- [环境搭建](#环境搭建)
	- [管理 *Android SDK*](#管理-android-sdk)

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
