<!-- TOC -->

- [*WPF* 简介](#wpf-简介)
- [*XAML*](#xaml)
- [控件与布局](#控件与布局)
	- [控件样式](#控件样式)
	- [布局](#布局)
	- [控件对齐](#控件对齐)
- [*ResourceDictionary* (资源字典)](#resourcedictionary-资源字典)
	- [创建资源字典](#创建资源字典)
	- [引用资源字典](#引用资源字典)
- [数据绑定](#数据绑定)
	- [属性变更通知](#属性变更通知)
	- [绑定语法](#绑定语法)
	- [绑定模式](#绑定模式)
	- [数据更新触发器](#数据更新触发器)
	- [绑定源/目标更新触发事件](#绑定源目标更新触发事件)
	- [多重绑定](#多重绑定)
	- [无效依赖属性](#无效依赖属性)
- [触发器](#触发器)
	- [属性触发器](#属性触发器)
	- [数据触发器](#数据触发器)
	- [事件触发器](#事件触发器)
	- [事件绑定到命令](#事件绑定到命令)
- [*Window* (窗口) 与 *Page* (页面)](#window-窗口-与-page-页面)
	- [启动窗口/页面](#启动窗口页面)
	- [窗体加载与关闭](#窗体加载与关闭)
	- [页面跳转](#页面跳转)
- [*Grid* (网格容器)](#grid-网格容器)
- [*DataGrid* (数据网格)](#datagrid-数据网格)
	- [绑定数据库](#绑定数据库)
	- [数据源类型](#数据源类型)
- [*DatePicker* (日期控件)](#datepicker-日期控件)
	- [设置默认显示日期](#设置默认显示日期)
	- [禁止日期文本编辑](#禁止日期文本编辑)
- [DevExpress](#devexpress)
	- [常用控件](#常用控件)
	- [布局层级](#布局层级)
	- [主界面](#主界面)
	- [汉化控件](#汉化控件)
	- [加载指示器](#加载指示器)
	- [常见问题](#常见问题)

<!-- /TOC -->



## *WPF* 简介
`WPF`全称为`Windows Presentation Foundation`，是微软在`Windows Vsita`时代引入的用户界面框架。

`WPF`向开发人员提供了一个统一的编程模型，用于在`Windows`上构建现代业务线桌面应用程序。



## *XAML*
`XAML`是一种声明性标记语言，语法类似`xhtml`，`WPF`使用其创建`UI`。

在`Windows Form`中，一个`GUI`窗体的布局代码在文件**GUI类名.Designer.cs**中；  
在`WPF`中，`GUI`窗体不再**直接**使用`C#`代码创建，而使用**GUI类名.xaml**文件描述窗体布局。

`XAML`文件实际上是后缀名为`.xaml`的`XML`文件，默认编码为`UTF-8`。  
在项目编译时，`XAML`描述的`GUI`窗体会被转换为等价的`C#`代码。



## 控件与布局
`WPF`中所有控件位于`System.Windows.Controls`命名空间下，大多数控件从基类`System.Windows.Controls.Control`中继承。

- `Button` 按钮控件，类似于Qt中的`QButton`
- `Label` 标签控件，类似于Qt中的`QLabel`
- `TextBlock` 基本文本显示控件(不可编辑)
- `TextBox` 简单文本输入控件，类似于Qt中的`QLineEdit`
- `RadioButton` 单选框，类似于Qt中的`QRadioButton`
- `CheckBox` 复选框，类似于Qt中的`QCheckBox`
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

水平对齐属性可取值`Left`、`Right`，垂直对齐属性可取值`Top`、`Buttom`  
对齐属性取值`Stretch`则代表**拉伸元素填充父元素的整个布局槽**。

对于`TreeView`、`ListView`等控件，默认情况下其子控件`TreeViewItem`、`ListViewItem`不会填满整个父控件，设置`HorizontalContentAlignment`属性为`Stretch`则能够令子控件水平方向填充满父控件。



## *ResourceDictionary* (资源字典)
资源字典是一个以`<ResourceDictionary/>`为根标签，包含资源定义的`XAML`文件。

在`WPF`中，对于多个`XAML`重复引用的资源(样式、转换器类等)，可以将重复的资源定义写在**资源字典**中，在外部进行引用，避免编写重复代码。

资源字典作用类似于WEB开发中`HTML`引用的`CSS`文件。

### 创建资源字典
在需要创建资源字典的路径下单击右键，选择以下菜单添加资源字典：

```
添加 => 资源字典
```

典型的资源字典内容如下：

```xml
<ResourceDictionary
		xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
		xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
		xmlns:local="clr-namespace:Xxx.Xxxx">

	<!-- 资源字典内可以定义任意的资源内容 -->
	<Style TargetType="Xxx">
		...
	</Style>

	...

	<DataTemplate x:Key="XxxTemplate">
		...
	</DataTemplate>

	...

	<local:Xxx x:Key="Xxxxx"/>

	...

</ResourceDictionary>
```

### 引用资源字典
在常见标签的`<Resources/>`子标签中可以引用资源字典，以`<Application/>`标签为例：

```xml
<Application x:Class="Xxx.App"
		xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
		xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
		xmlns:local="Xxx.Xxxx..."
		StartupUri="Xxx...">

	<Application.Resources>
		<!-- 引用资源字典 -->
		<ResourceDictionary>
			<ResourceDictionary.MergedDictionaries>
				<ResourceDictionary Source="/Xxx/资源字典文件1.xaml"/>
				<ResourceDictionary Source="/Xxx/资源字典文件2.xaml"/>
				...
			</ResourceDictionary.MergedDictionaries>
		</ResourceDictionary>
	</Application.Resources>

</Application>
```

在`<Application/>`标签中引用的资源字典在**整个应用**中有效，在其它标签中引用的的资源字典仅在标签内部有效。

若资源字典使用`x:Key`属性命名，则需要通过资源字典的`x:Key`显式引用才能生效：

```xml
<Window x:Class="Xxx.XxxWindow"
		xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
		xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
		xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
		xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
		xmlns:local="Xxx.Xxxx...">

	<Window.Resources>
		<!-- 引用资源字典，使用x:Key属性 -->
		<ResourceDictionary x:Key="RefResources">
			<ResourceDictionary.MergedDictionaries>
				<ResourceDictionary Source="/Xxx/资源字典文件1.xaml"/>
				<ResourceDictionary Source="/Xxx/资源字典文件2.xaml"/>
				...
			</ResourceDictionary.MergedDictionaries>
		</ResourceDictionary>
	</Window.Resources>

	<!-- 显式通过x:Key属性使用资源字典，该资源字典仅在Grid标签内部生效 -->
	<Grid Resources="{StaticResource RefResources}">
		...
	</Grid>

</Window>
```



## 数据绑定
`WPF`作为数据驱动的UI框架，与`Qt`、`MFC`等传统消息式驱动的UI框架最显著的区别便是**数据绑定**。

在`WPF`中，典型的设计模式为`MVVM`。  
对于一个`View`，会创建对应的`ViewModel`来描述其数据结构，并通过控件绑定`ViewModel`中的属性来实现多控件同步数据变化。

### 属性变更通知
对于一个属性，要实现改变属性值时通知外部，需要满足以下要求：

- 属性所在的Model实现`INotifyPropertyChanged`接口。
- 属性的`set`方法中触发接口中定义的`PropertyChanged`事件。
- 触发`PropertyChanged`事件的参数使用发生变化的属性名称构造。

如下所示：

```cs
using System.ComponentModel;

class XXX : INotifyPropertyChanged
{
	// 实现接口事件
	public event PropertyChangedEventHandler PropertyChanged;

	// 属性私有变量
	private int _xxx = 0;

	// 属性包装器
	public int Xxx
	{
		get => _xxx;
		set
		{
			_xxx = value;
			// 属性变量变化时调用PropertyChanged事件，参数为属性名称(不是存储包装器值的私有变量名称)
			PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Xxx"));
		}
	}
}
```

只有需要自行修改数据源内数据并**通知外界**时才需要实现`INotifyPropertyChanged`接口，如果数据源仅仅作为**数据获取**使用则无必要。

- 封装`INotifyPropertyChanged`接口

	在实际开发中，一般会对`INotifyPropertyChanged`接口做一个简单的封装，如下所示：

	```cs
	using System.ComponentModel;
	using System.Runtime.CompilerServices;

	public class NotifyObject : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		/// <summary>
		/// 属性发生改变时调用该方法发出通知
		/// </summary>
		/// <param name="propertyName">属性名称</param>
		public void RaisePropertyChanged(string propertyName)
			=> PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
	}
	```

	使用：

	```cs
	class XXX : NotifyObject
	{
		private int _xxx = 0;

		// 属性包装器
		public int Xxx
		{
			get => _xxx;
			set
			{
				_xxx = value;
				RaisePropertyChanged("Xxx");
			}
		}
	}
	```

- 使用`nameof`获取属性字段名称

	在`C# 6.0`中新增了`nameof`关键字，作用是获取字段的**当前名称**(不是完整路径名称)。  
	可利用该特性获取属性名称，上述例子中的`Xxx`属性可以改写为：

	```cs
	class XXX : NotifyObject
	{
		private int _xxx = 0;

		// 属性包装器
		public int Xxx
		{
			get => _xxx;
			set
			{
				_xxx = value;
				RaisePropertyChanged(nameof(Xxx));
			}
		}
	}
	```

	使用`nameof`获取属性名称，能使属性在重构名称时避免手动修改传入属性通知方法的名称字符串。

- 使用`CallerMemberNameAttribute`特性简化属性通知方法

	在`.Net 4.5`中引入的`System.Runtime.CompilerServices.CallerMemberNameAttribute`可用于获取调用者的名称。  
	利用该特性可简化属性通知方法的参数。

	如下所示：

	```cs
	using System.ComponentModel;
	using System.Runtime.CompilerServices;

	public class NotifyObject : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		// propertyName参数使用CallerMemberName特性修饰，方法被调用时propertyName会自动填入调用者信息(属性名)
		public void RaisePropertyChanged([CallerMemberName] string propertyName = "")
			=> PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
	}
	```

	使用：

	```cs
	class XXX : NotifyObject
	{
		private int _xxx = 0;

		public int Xxx
		{
			get => _xxx;
			set
			{
				_xxx = value;

				// 方法调用无需参数，参数由编译器生成
				RaisePropertyChanged();
			}
		}
	}
	```

	被`[CallerMemberName]`特性修饰的方法参数在编译时会自动填入调用者的名称。  
	在属性中的`set`、`get`块中调用方法，则填入的参数为属性的名称。

	使用`[CallerMemberName]`特性，能使属性在重构名称时避免手动修改传入属性通知方法的名称字符串。

### 绑定语法
进行绑定操作需要明确目标对象的路径，`WPF`提供了`ElementName`、`Source`、`RelativeSource`三种绑定对象。

- 默认绑定

	在不显式指定绑定对象的情况下，默认将`DataContent`作为绑定对象。

	```xml
	XXX="{Binding xxx}"
	<!-- 等价于 -->
	XXX="{Binding Path=xxx}"
	<!-- 对于需要自定义显示逻辑的内容，指定转换器 -->
	XXX="{Binding Path=xxx, Converter={StaticResource xxx}}"
	<!-- 指定转换器同时可以传入一个自定义参数，用于传递某些附加信息 -->
	XXX="{Binding Path=xxx, Converter={StaticResource xxx}, ConverterParameter=xxx}"
	```

	绑定的转换器需要实现`System.Windows.Data.IValueConverter`接口，接口定义如下：

	```cs
	public interface IValueConverter
	{
		object Convert(object value, Type targetType, object parameter, CultureInfo culture);
		object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture);
	}
	```

	- `Convert`方法的`value`参数为待转换的源数据。
	- `ConvertBack`方法的`value`参数为转换后的数据。
	- `parameter`参数为数据绑定中传入的自定义转换参数。

	绑定中的`ConverterParameter`通常用于传递一些编译时就已确定的数据。  
	若需要传递多个动态变化的数据并同步更新，则应使用**多重绑定**。

- 绑定`ElementName`

	`ElementName`是控件拥有的属性，将绑定对象设置为当前XAML文件内的某一个控件。

	```xml
	XXX="{Binding ElementName=xxx, Path=xxx}}"
	```

- 绑定`Source`

	`Source`属性用于指定对象绑定路径的引用。

	```xml
	XXX="{Binding Source={StaticResource xxx}}"
	```

- 绑定`RelativeSource`

	`RelativeSource`属性支持以一定的规则来确定绑定对象。

	```xml
	<!-- 绑定到自身 -->
	XXX="{Binding xxx, RelativeSource={RelativeSource Self}}"
	<!-- 绑定到指定类型属性 -->
	XXX="{Binding xxx, RelativeSource={RelativeSource Mode=FindAncestor, AncestorType={x:Type xxx}}}"
	```

### 绑定模式
控件自身的属性被称为**目标属性**，绑定的数据源对象称为**源属性**。  
数据绑定时可以设置绑定模式(`Mode`)：

```xml
XXX="{Binding xxx, Mode=xxxx}"
```

源属性与目标属性之前有四类同步方式：

- `OneWay` 源属性发生变化通知目标属性。只读型控件的默认绑定方式(`Label`等)
- `OneWayToSource` 目标属性发生变化通知源属性
- `TwoWay` 源属性与目标属性相互同步改动，开销比单向同步更高。可编辑型控件的默认绑定方式(`TextBox`、`ComboBox`等)
- `OneTime` 仅在初始化目标属性时读取源属性一次，开销最低

### 数据更新触发器
在使用`OneWay/OneWayToSource`绑定时，绑定同时可以设置数据更新触发器(`UpdateSourceTrigger`)，配置何时更新绑定源数据：

```xml
XXX="{Binding xxx, UpdateSourceTrigger=xxxx}"
```

- `Default` 默认方式，对于不同的控件有不同的定义
- `PropertyChanged` 当绑定目标属性更改时，立即更新绑定源
- `LostFocus` 当绑定目标元素失去焦点时，更新绑定源
- `Explicit` 仅在调用`System.Windows.Data.BindingExpression.UpdateSource`方法时更新绑定源

### 绑定源/目标更新触发事件
对于`FrameworkElement`类的子控件，会包含`SourceUpdated/TargetUpdated`两个事件。

- 控件上任何设置了`NotifyOnTargetUpdated=True`的绑定在目标属性更新时都会触发`TargetUpdated`事件。
- 控件上任何设置了`NotifyOnSourceUpdated=True`的绑定在源属性更新时都会触发`SourceUpdated`事件。

绑定的`NotifyOnTargetUpdated/NotifyOnSourceUpdated`属性默认为`False`，需要在建立绑定时显式设置其值为`True`，如下所示：

```xml
<!-- 控件的事件触发回调函数可以直接设置 -->
<XXX SourceUpdated="源属性更新回调方法" TargetUpdated="目标属性更新回调方法"
		XXX="{Binding xxx, NotifyOnSourceUpdated=True, NotifyOnTargetUpdated=True}"/>
```

### 多重绑定
当一个控件的目标属性依赖于**多个**数据源时，可以使用**多重绑定**。

以常见的`Label`控件为例，多重绑定语法如下：

```xml
<Label>
	<Label.Content>
		<MultiBinding Converter="{StaticResource xxx}">
			<Binding Path="xxx1"/>
			<Binding Path="xxx2"/>
			...
		</MultiBinding>
	</Label.Content>
</Label>
```

使用多重绑定时，必须要指定转换器来处理多个数据源，转换器需要实现`IMultiValueConverter`接口。

与单一绑定使用的接口`IValueConverter`相比，`IMultiValueConverter`的接口方法`Convert()`首个参数类型由`object`变为`object[]`，数组中保存了多个绑定数据源的值，顺序按照绑定次序排列。

### 无效依赖属性
在实现数值转换接口时，需要对未设定值进行检验，数值转换异常时，首个参数会传入代表**未设定值**的特殊变量`DependencyProperty.UnsetValue`。



## 触发器
触发器能够在满足某种条件时触发操作。  
触发器包括以下三类：

- `Trigger` 属性触发器
- `DataTrigger` 数据触发器
- `EventTrigger` 事件触发器

`FrameworkElement`类型中定义了`Triggers`属性，用于设定触发器。  
继承自`FrameworkElement`类型的控件皆可在控件内部定义触发器，例如：

```xml
<Window>
	<Window.Triggers>
		<Trigger>
			...
		</Trigger>
	</Window.Triggers>
</Window>
```

`Style`、`DataTemplate`、`ControlTemplate`等类型可用于定义通用的触发器。  
以`Style`为例，定义触发器语法如下：

```xml
<Style TargetType="目标控件类型">
	<Style.Triggers>
		<Trigger>
			...
		</Trigger>
		<EventTrigger>
			...
		</EventTrigger>
		<DataTrigger>
			...
		</DataTrigger>
		...
	</Style.Triggers>
</Style>
```

### 属性触发器
属性触发器可用于监视任意可绑定的属性，当被监视的属性满足条件时则执行触发器。

以`Style`为例，监视`Image`控件的`IsEnabled`属性，如下所示：

```xml
<Style TargetType="Image">
	<Style.Triggers>
		<!-- 图片 IsEnabled 属性为 True 时，设置 Opacity 属性为 1.0 -->
		<Trigger Property="IsEnabled" Value="True">
			<Setter Property="Opacity" Value="1.0"/>
		</Trigger>
		<!-- 图片 IsEnabled 属性为 False 时，设置 Opacity 属性为 0.5 -->
		<Trigger Property="IsEnabled" Value="False">
			<Setter Property="Opacity" Value="0.5"/>
		</Trigger>
	</Style.Triggers>
</Style>
```

需要同时监视多个属性时，可以使用`MultiTrigger`(多条件触发器)，如下所示：

```xml
<Style TargetType="Image">
	<Style.Triggers>
		<MultiTrigger>
			<MultiTrigger.Conditions>
				<Condition Property="IsFocused" Value="True"/>
				<Condition Property="IsEnabled" Value="True"/>
			</MultiTrigger.Conditions>
			<Setter Property="Opacity" Value="1.0"/>
		</MultiTrigger>
		<MultiTrigger>
			<MultiTrigger.Conditions>
				<Condition Property="IsFocused" Value="False"/>
				<Condition Property="IsEnabled" Value="False"/>
			</MultiTrigger.Conditions>
			<Setter Property="Opacity" Value="0.5"/>
		</MultiTrigger>
	</Style.Triggers>
</Style>
```

### 数据触发器
数据触发器用于监视绑定路径的数据变化，当绑定的路径数据满足条件时则执行触发器。

与属性触发器类似，数据触发器也包括监视单一数据的`DataTrigger`与监视多数据的`MultiDataTrigger`。

```xml
<Style TargetType="Image">
	<Style.Triggers>
		
		<!-- 绑定路径为 Xxx 的目标数据值为 xxx 时，设置 Opacity 属性为 1.0 -->
		<DataTrigger Binding="{Binding Path=Xxx}" Value="xxx">
			<Setter Property="Opacity" Value="1.0"/>
		</DataTrigger>

		<!-- 多条件数据触发器 -->
		<MultiDataTrigger>
			<!-- 绑定路径为 XxxA 的目标数据值为 xxxA 时，绑定路径为 XxxB 的目标数据值为 xxxB 时，设置 Opacity 属性为 0.5 -->
			<MultiDataTrigger.Conditions>
				<Condition Binding="{Binding Path=XxxA}" Value="xxxA" />
				<Condition Binding="{Binding Path=XxxB}" Value="xxxB" />
			</MultiDataTrigger.Conditions>
			<Setter Property="Opacity" Value="0.5"/>
		</MultiDataTrigger>

	</Style.Triggers>
</Style>
```

### 事件触发器
事件触发器用于监视事件的发生，在事件触发时执行触发器。

事件触发器只能绑定到**路由事件**(委托类型为`RoutedEventHandler`)上。

```xml
<Style TargetType="Image">
	<Style.Triggers>

		<!-- 绑定到指定的路由事件 -->
		<EventTrigger RoutedEvent="Image.Loaded">
			<EventTrigger.Actions>
				<BeginStoryboard>
					<Storyboard>
						...
					</Storyboard>
				</BeginStoryboard>
			</EventTrigger.Actions>
		</EventTrigger>

	</Style.Triggers>
</Style>
```

### 事件绑定到命令
事件触发器不能实现事件到命令的转发，使用`System.Windows.Interactivity.dll`程序集可实现事件到命令的转发。  
`System.Windows.Interactivity.dll`**没有**包含在默认的`WPF`中，需要从`NuGet`中下载，并引入该程序集：

```xml
<!-- 通过命名空间引入 -->
xmlns:i="http://schemas.microsoft.com/expression/2010/interactivity"

<!-- 或者直接引入dll -->
xmlns:i="clr-namespace:System.Windows.Interactivity;assembly=System.Windows.Interactivity"
```

以`Image`控件为例，将`Image.MouseDown`事件绑定到`XxxCommand`上：

```xml
<Image>
	<i:Interaction.Triggers>
		<i:EventTrigger EventName="MouseDown">
			<i:InvokeCommandAction Command="{Binding XxxCommand}" CommandParameter="{Binding xxx}"/>
		</i:EventTrigger>
	</i:Interaction.Triggers>
</Image>
```



## *Window* (窗口) 与 *Page* (页面)
在`WPF`中，**窗口**的类型为`System.Windows.Window`，所有的其它窗口均从此类派生。

**页面**的类型为`System.Windows.Controls.Page`，`Page`不能够单独使用，需要搭配`NavigationWindow`或`Frame`才能显示页面。

### 启动窗口/页面
在`WPF`项目默认生成的`App`类的视图`App.xaml`中，`<Application/>`标签的属性`StartupUri`指明了应用的启动路径。

默认生成的`App.xaml`如下所示：

```xml
<Application x:Class="XXX.App"
		xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
		xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
		StartupUri="XXXX.xaml">
</Application>
```

启动路径中指定的xaml文件可以是`Window`，也可以是`Page`。

在使用`Page`做为`StartupUri`时，`WPF`会自动为该`Page`创建一个`NavigationWindow`。

### 窗体加载与关闭
在窗体首次初始化、加载过程中，在不同阶段会依次触发以下事件：

1. `FrameworkElement.Initialized`事件，在所有子元素已被设置完毕时触发。
1. `Window.Activated`事件，在窗口被激活时触发。
1. `FrameworkElement.Loaded`事件，在控件布局结束、数据绑定完成时触发。
1. `Window.ContentRendered`事件，在控件渲染完毕时触发。

在窗体关闭时，会依次触发以下事件：

1. `Window.Closing`事件，在窗口即将被关闭前触发，在此阶段可以取消窗口关闭。
1. `Window.Deactivated`事件，窗口变为后台窗口时触发。
1. `FrameworkElement.Unloaded`事件，窗口移除子元素完成时触发。
1. `Window.Closed`事件，窗口完全关闭时触发。

从`Window`类继承时，可以通过重写相关事件对应方法来实现更精细的阶段控制，以`FrameworkElement.Initialized`事件为例，重写`OnInitialized()`方法，如下所示：

```cs
protected override void OnInitialized(EventArgs e)
{
	// do something before initialized...
	base.OnInitialized(e);
	// do something after initialized...
}
```

重写`On*()`方法时不调用基类实现可以禁用匹配的事件。

### 页面跳转
页面之间相互跳转在前端可以使用`<Hyperlink/>`标签实现：

```xml
<Label>
	<Hyperlink NavigateUri="XXX.xaml">xxx</Hyperlink>
</Label>
```

也可以在后端设置页面`Content`属性内容来实现页面跳转：

```cs
// 直接设置页面Content字段到新页面的Uri实例实现跳转
Page.Content = new Uri("XXX.xaml", UriKind.Relative);
```

也可以通过使用`NavigationService`类控制页面跳转：

```cs
// 使用NavigationService跳转到页面路径
NavigationService.GetNavigationService(source).Navigate(new Uri("XXX.xaml", UriKind.Relative));
// 跳转到下一页面
NavigationService.GetNavigationService(source).GoForward();
// 跳转到下一页面
NavigationService.GetNavigationService(source).GoBack();
```



## *Grid* (网格容器)
`Grid`容器提供了常见的**网格布局**。

- `Grid`布局的行定义写在子标签`<Grid.RowDefinitions/>`中，列定义写在子标签`<Grid.ColumnDefinitions/>`中。

	- 每一行由`<RowDefinition/>`标签定义，属性`Height`决定行高。
	- 每一列由`<ColumnDefinition/>`标签定义，属性`Width`决定列宽。

- `Grid`布局的行高、列宽取值遵循以下规则：

	- 取值`*`为自动填满剩余大小。
	- 取值`auto`由系统分配最合适的控件大小。
	- `*`前可以添加数值，在有多个控件取值`*`是，默认由这些控件均分剩余的大小，`*`前添加数值则设定剩余大小分配的**权重**。

- `Grid`布局的位置定义：

	- `Grid`布局的序号从`0`开始。
	- 在控件属性中使用`Grid.Row`/`Grid.Cloumn`确定控件的行列位置。
	- 在控件属性中使用`Grid.RowSpan`/`Grid.CloumnSpan`能让控件占据多行、多列。

一个简单的`Grid`容器使用示例如下：

```xml
<!-- 定义一个带有1行4列的Grid -->
<Grid>
	<!--定义行-->
	<Grid.RowDefinitions>
		<RowDefinition/>
	</Grid.RowDefinitions>
	<!--定义列-->
	<Grid.ColumnDefinitions>
		<ColumnDefinition Width="100"/> <!-- 第1列，固定宽度100 -->
		<ColumnDefinition Width="*"/> <!-- 第2列，均分剩余宽度，权重1 -->
		<ColumnDefinition Width="0.5*"/> <!-- 第3列，均分剩余宽度，权重0.5 -->
		<ColumnDefinition Width="auto"/> <!-- 第4列，根据该网格包含的控件自动适配宽度 -->
	</Grid.ColumnDefinitions>

	<!-- 定义Grid网格内的填充内容 -->
	<Label Content="xxx" Grid.Row="0" Grid.Cloumn="0"/> <!-- Label控件位置，第1行，第1列 -->
	<TextBox Grid.Row="0" Grid.Cloumn="1"/> <!-- TextBox控件位置，第1行，第2列 -->
	<!-- 添加其它控件，操作类似... -->

</Grid>
```



## *DataGrid* (数据网格)
使用`DataGrid`控件能够方便地展示数据库中的表。

`DataGrid`基本语法类似于`Grid`控件，但`DataGrid`可绑定数据源，展示数据源中的内容。
与`Grid`相比，`DataGrid`只需设置列属性，每一行填充的内容由数据源决定。

`<DataGrid/>`标签常用属性：

- `ItemsSource`属性：

	用于设置控件的数据集，绑定的对象需要为集合类型。

- `SelectedItem`属性：

	用于设置控件的当前焦点数据，绑定的对象类型为数据集的模板参数。

- `AutoGenerateColumns`属性：

	用于设置是否自动将数据集中的列显示到控件上，若需要自定义数据显示逻辑，则应设置该属性为`false`。

- `Columns`属性：

	用于设置列样式和显示内容，可嵌套标签：

	- `<DataGridTextColumn/>`为普通文本列，最常用。
		- `Binding`属性，绑定指定列
		- `IsReadOnly`属性，设置内容是否只读
		- `Width`属性，设置宽度

基本代码模板：

```xml
<DataGrid Name="XXX" AutoGenerateColumns="False" ItemsSource="{Binding XXX}" SelectedItem="{Binding XXX}">
	<DataGrid.Columns>
		<DataGridTextColumn Header="XXX" Binding="{Binding XXX}" IsReadOnly="True"/>
		<DataGridTextColumn Header="XXX" Binding="{Binding XXX}" Width="*"/>
		...
	</DataGrid.Columns>
</DataGrid>
```

### 绑定数据库
`DataGrid`控件的属性`ItemsSource`既可以绑定自行创建的集合类型，也可以直接绑定数据库。

绑定数据库时，数据源为`DataView`类型，以`MySql`数据库为例：

```cs
MySqlConnection connection = new MySqlConnection("server = localhost; userid = XXX; password = XXX; database = XXX");
MySqlCommand command = new MySqlCommand("select * from 表名", connection);
MySqlDataAdapter dataAdapter = new MySqlDataAdapter(command);		//执行查询指令
DataSet dataSet = new DataSet();									//创建空数据源
dataAdapter.Fill(dataSet);											//填充数据源
dataGrid.ItemsSource = dataSet.Tables[0].DefaultView;				//绑定数据源中的表视图
```

绑定到数据库数据源时，数据库中的改动会自动同步到控件上。

### 数据源类型
`DataGrid`同样支持使用自定义数据集合做为数据源。  
在绑定数据源到自行创建的数据集合时，需要注意集合的类型。

- 常见的集合类型如`List`在数据发生增添、删除等操作时，**不会**通知控件刷新。将数据源绑定到此类集合上，会造成数据集发生变动，但控件上并未同步发生改动。
- 要实现控件随着数据源增删而同步刷新需要使用特定集合类型`ObservableCollection`，此类型实现了`INotifyCollectionChanged`、`INotifyPropertyChanged`接口，能够在集合发生变化时发出通知。



## *DatePicker* (日期控件)
`WPF`提供了日期选择控件`DatePicker`。

### 设置默认显示日期
设置控件的`SelectedDate`属性为指定时间即可。

设置`DatePicker`默认显示当前日期：

- 方法一，在后台设置。

	在后台代码中设置`SelectedDate`为当前时间：

	```cs
	datePicker.SelectedDate = System.DateTime.Now;
	```

- 方法二，在前台定义。

	在`XAML`中添加命名空间定义：

	```
	xmlns:sys="clr-namespace:System;assembly=mscorlib"
	```

	之后设置控件属性：

	```
	SelectedDate="{x:Static sys:DateTime.Now}"
	```

### 禁止日期文本编辑
默认情况下，`DatePicker`控件的文本日期显示框支持直接编辑文本来设定日期，需要禁止此特性可以使用以下方式：

- 将`Focusable`属性设置为`False`。

	设置`Focusable`属性通过禁用焦点获取来限制编辑功能，文本框状态显示正常。

	```xml
	<DatePicker Focusable="False"/>
	```

- 设置子控件`DatePickerTextBox`的`IsReadOnly`属性为`False`。

	`IsReadOnly`直接禁用了文本框的编辑属性，文本框直接显示为无法编辑。

	```xml
	<DatePicker.Resources>
		<Style TargetType="DatePickerTextBox">
			<Setter Property="IsReadOnly" Value="True"/>
		</Style>
	</DatePicker.Resources>
	```



## DevExpress
`DevExpress`是一套商业UI库，相比原生控件更加精美、控件功能更加强大。

### 常用控件
`DevExpress`为几乎所有WPF官方控件提供了功能更强大的版本。

常用的控件命名空间如下：

```xml
xmlns:dx="http://schemas.devexpress.com/winfx/2008/xaml/core"
xmlns:dxd="http://schemas.devexpress.com/winfx/2008/xaml/docking"
xmlns:dxe="http://schemas.devexpress.com/winfx/2008/xaml/editors"
xmlns:dxg="http://schemas.devexpress.com/winfx/2008/xaml/grid"
xmlns:dxnb="http://schemas.devexpress.com/winfx/2008/xaml/navbar"
```

### 布局层级
`DevExpress`扩展了常用的布局容器，在`DevExpress`中，常用的多文档式窗口布局(`MDI`)层级：

`DockLayoutManager` => `LayoutGroup`/`TabbedGroup`/`DocumentGroup` => `LayoutPanel`

`LayoutGroup`、`TabbedGroup`、`DocumentGroup`需要`DockLayoutManager`做为直接**父容器**，将`XXXGroup`直接添加在`LayoutPanel`中能通过编译，但在运行时出错。  
`LayoutPanel`不能直接添加到`DockLayoutManager`中，会出现错误：`属性LayoutRoot不支持类型LayoutPanel的值`。  
`LayoutGroup`可通过`Orientation`属性设置内部控件的对齐方向。

默认情况下，`LayoutPanel`会均分`LayoutGroup`的剩余空间，要令`LayoutPanel`大小随着内部控件大小改变则设置属性`ItemHeight/ItemWidth`为`auto`。

默认情况下，`DockLayoutManager`内的子控件会直接显示在布局中，要使某些子控件自动隐藏，可以使用`AutoHideGroup`，如下所示：

```xml
<dxd:DockLayoutManager.AutoHideGroups>
	<dxd:AutoHideGroup DockType="停靠方向">
		...
	</dxd:AutoHideGroup>
</dxd:DockLayoutManager.AutoHideGroups>
```

### 主界面
通常使用`DXDockPanel`进行主界面的布局。  
`DXDockPanel`的子控件可设置属性`DockPanel.Dock`，取值`Top/Buttom/Left/Right`，最后一个控件会作为中央控件填满剩余空间。

### 汉化控件
默认情况下，`DevExpress`提供的控件包含的默认文本均为**英文**，需要使用官方提供的语言资源包才能使对应控件展示文本替换为中文。

以`DevExpress 13.2`为例，需要下载中文资源包：`DevExpressLocalizedResources_2013.2_zh-CN.zip`。  
在项目的输出目录(生成可执行文件的目录)中创建`zh-CN`文件夹，将解压出的资源文件放置于该路径下。  
同时在`App`类中添加`UI`资源加载代码：

```cs
public partial class App : Application
{
	// 加载UI资源相关代码也可放置于App类的StartUp阶段
	static App()
	{
		// 加载DevExpress中文UI资源
		Thread.CurrentThread.CurrentUICulture = new CultureInfo("zh-CN");
		Thread.CurrentThread.CurrentCulture = new CultureInfo("zh-CN");
	}

	public App()
	{
		...
	}
}
```

### 加载指示器
`DevExpress`提供了多种加载指示控件，用于在加载内容时提示用户，避免UI假死：	

- `WaitIndicator` 等待指示器

	当后台需要执行一个耗时较长的操作时，前台使用`WaitIndicator`告知用户需要等待。  
	`WaitIndicator`平时处于隐藏状态，通过属性控制其显示状态。  
	`WaitIndicator`运行在**UI线程**，UI线程被占用会影响`WaitIndicator`的显示和等待动画播放。

	常用属性：

	- `DeferedVisibility` 是否显示
	- `Content` 设置等待提示文本

	如下所示：

	```xml
	<dx:WaitIndicator DeferedVisibility="True" Content="Loading..."/>
	```

	可以通过自定义数据模板更改等待指示器的外观：

	```xml
	<dx:WaitIndicator DeferedVisibility="True" Content="Loading..."> 
		<dx:WaitIndicator.ContentTemplate>
			<DataTemplate>
				<StackPanel Orientation="Vertical"> 
					<TextBlock Text="Please Wait" FontSize="20"/> 
					<TextBlock Text="{Binding xxx}"/> 
				</StackPanel>
			</DataTemplate>
		</dx:WaitIndicator.ContentTemplate> 
	</dx:WaitIndicator> 
	```

- `LoadingDecorator` 加载装饰器

	`LoadingDecorator`默认在控件加载完毕前显示，提示用户控件处于准备状态。  
	将`LoadingDecorator`包裹在目标控件外层，即可在目标控件加载时显示加载指示器。
	
	常用属性：

	- `IsSplashScreenShown` 是否显示
	- `SplashScreenDataContext` 绑定ViewModel
	- `SplashScreenLocation` 显示位置
	- `OwnerLock` 加载指示器显示时，目标控件的锁定方式
	- `BorderEffect` 边框高亮模式
	- `BorderEffectColor` 边框高亮色彩

	如下所示：

	```xml
	<dx:LoadingDecorator SplashScreenDataContext="{Binding xxx}" SplashScreenLocation="CenterContainer">
		<view:XxxView/>
	</dx:LoadingDecorator>
	```

	`LoadingDecorator`使用`WaitIndicator`实现。  
	但不同于`WaitIndicator`，`LoadingDecorator`运行在独立线程，UI线程的操作不会影响`LoadingDecorator`的显示和动画播放。

	未绑定`IsSplashScreenShown`属性时，`LoadingDecorator`会自动在目标控件处于加载状态时显示。  
	绑定`IsSplashScreenShown`属性时，则由数据源决定指示器的显示与否。

	可以通过自定义数据模板更改加载指示器的外观：

	```xml
	<dx:LoadingDecorator SplashScreenDataContext="{Binding xxx}" SplashScreenLocation="CenterContainer">
		<dx:LoadingDecorator.SplashScreenTemplate>
			<DataTemplate>
				<StackPanel Orientation="Vertical">
					<TextBlock Text="Please Wait" FontSize="20"/>
					<TextBlock Text="{Binding xxx}"/>
				</StackPanel>
			</DataTemplate>
		</dx:LoadingDecorator.SplashScreenTemplate>
		<view:XxxView/>
	</dx:LoadingDecorator>
	```

### 常见问题

- *DocumentGroup* 标签不可拖动、关闭

	`DocumentGroup`需要在`DockLayoutManager`中才能实现关闭标签、拖动标签等功能。

- *DocumentGroup* 关闭标签后标签依旧保留到`ClosedPanels`列表中

	设置`DocumentPanel`的`ClosingBehavior`属性为`ImmediatelyRemove`。
