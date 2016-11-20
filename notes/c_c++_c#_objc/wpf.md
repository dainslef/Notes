[TOC]

## `WPF` 简介
`WPF`全称为`Windows Presentation Foundation`，是微软在`Windows Vsita`时代引入的用户界面框架。

`WPF`向开发人员提供了一个统一的编程模型，用于在`Windows`上构建现代业务线桌面应用程序。



## `XAML`
`XAML`是一种声明性标记语言，语法类似`xhtml`，`WPF`使用其创建`UI`。

在`Windows Form`中，一个`GUI`窗体的布局代码在文件**GUI类名.Designer.cs**中；
而在`WPF`中，`GUI`窗体不再**直接**使用`C#`代码创建，而使用**GUI类名.xaml**文件描述窗体布局。

`XAML`文件实际上是后缀名为`.xaml`的`XML`文件，默认编码为`UTF-8`。



## 常用控件
`WPF`中所有控件位于`System.Windows.Controls`命名空间下，大多数控件从基类`System.Windows.Controls.Control`中继承。

- `Button` 按钮控件，类似于Qt中的`QButton`
- `Label` 标签控件，类似于Qt中的`QLabel`
- `TextBlock` 基本文本显示控件(不可编辑)
- `TextBox` 简单文本输入控件，类似于Qt中的`QLineEdit`
- `GroupBox` 控件组，类似于Qt中的`QGroupBox`，设置标题使用属性`Header`

按钮/标签设置文本使用属性`Content`，文本控件设置文本使用属性`Text`。`Content`属性中可添加其它控件，`Text`属性只能接收文本。