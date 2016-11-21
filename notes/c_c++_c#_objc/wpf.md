[TOC]

## `WPF` 简介
`WPF`全称为`Windows Presentation Foundation`，是微软在`Windows Vsita`时代引入的用户界面框架。

`WPF`向开发人员提供了一个统一的编程模型，用于在`Windows`上构建现代业务线桌面应用程序。



## `XAML`
`XAML`是一种声明性标记语言，语法类似`xhtml`，`WPF`使用其创建`UI`。

在`Windows Form`中，一个`GUI`窗体的布局代码在文件**GUI类名.Designer.cs**中；
而在`WPF`中，`GUI`窗体不再**直接**使用`C#`代码创建，而使用**GUI类名.xaml**文件描述窗体布局。

`XAML`文件实际上是后缀名为`.xaml`的`XML`文件，默认编码为`UTF-8`。



## 控件与布局
`WPF`中所有控件位于`System.Windows.Controls`命名空间下，大多数控件从基类`System.Windows.Controls.Control`中继承。

- `Button` 按钮控件，类似于Qt中的`QButton`
- `Label` 标签控件，类似于Qt中的`QLabel`
- `TextBlock` 基本文本显示控件(不可编辑)
- `TextBox` 简单文本输入控件，类似于Qt中的`QLineEdit`
- `PasswordBox` 密码文本控件，类似于Qt中`QLineEdit`设置了`QLineEdit::EchoMode`属性为`QLineEdit::Password`
- `GroupBox` 控件组，类似于Qt中的`QGroupBox`，设置标题使用属性`Header`

按钮/标签设置文本使用属性`Content`，文本控件设置文本使用属性`Text`。
`Content`属性中可添加其它控件，`Text`属性只能接收文本。

`TextBox`可以有焦点，可编辑，`TextBlock`不可。
`PasswordBox`拥有属性`PasswordChar`用于设置密码回显字符。

### 控件样式
使用`<Style>`标签可以定义统一的控件样式，基本用法如下：

```xml
<Style x:Key="key值" TargetType="{x:Type 类型}">
	<Setter Property="属性名称" Value="属性值"/>
</Style>
```

- `TargetType`属性为`<Style/>`标签必选，用于指明`<Style/>`生效的控件类型。
- `Key`属性可以省略，当`Key`属性省略时，有效范围内的所有`TargetType`类型的控件都将应用该Style(类似于`CSS`)。

控件引用设定了`x:Key`属性的`<Style/>`：

```xml
<XXX Style="{StaticResource key值}"/>
```

### 布局
在`WPF`官方控件中，布局并非可自由设置的属性，应选用具有特定布局的容器控件相互组合构建复杂界面。

- `StackPanel` 水平/垂直容器，属性`Orientation`用于设置内部控件对齐方向
- `WrapPanel` 流式布局容器，子控件按行排列，填满一行自动换行
- `DockPanel` 停靠面板容器，上下左右四个方向可分别设置不同子控件，最后一个控件做为中央控件填满剩余空间
- `Grid` 网格容器，可自由分配每个网格的空间(最常用)

### 控件对齐
大多数控件都具有以下对齐属性：

- `VerticalAlignment`/`HorizontalAlignment` 设置控件自身的对齐方向
- `VerticalContentAlignment`/`HorizontalContentAlignment` 设置控件内部内容的对齐方向

水平对齐属性可取值`Left`、`Right`，垂直对齐属性可取值`Top`、`Buttom`，代表向某个方向对齐。
对齐属性取值`Stretch`则代表**拉伸元素填充父元素的整个布局槽**。

对于`TreeView`、`ListView`等控件，默认情况下其子控件`TreeViewItem`、`ListViewItem`不会填满整个父控件，设置`HorizontalContentAlignment`属性为`Stretch`则能够令子控件水平方向填充满父控件。