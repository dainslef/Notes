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

水平对齐属性可取值`Left`、`Right`，垂直对齐属性可取值`Top`、`Buttom`，代表向某个方向对齐。
对齐属性取值`Stretch`则代表**拉伸元素填充父元素的整个布局槽**。

对于`TreeView`、`ListView`等控件，默认情况下其子控件`TreeViewItem`、`ListViewItem`不会填满整个父控件，设置`HorizontalContentAlignment`属性为`Stretch`则能够令子控件水平方向填充满父控件。



## 数据绑定
`WPF`作为数据驱动的UI框架，与`Qt`、`MFC`等传统消息式驱动的UI框架最显著的区别便是**数据绑定**。

在`WPF`中，典型的设计模式为`MVVM`。
对于一个`View`，会创建对应的`ViewModel`来描述其数据结构，并通过控件绑定`ViewModel`中的属性来实现多控件同步数据变化。

对于一个属性，要实现改变属性值时通知外部，需要满足以下要求：

- 属性所在的Model实现`INotifyPropertyChanged`接口。
- 属性的`set`方法中触发接口中定义的`PropertyChanged`事件。
- 触发`PropertyChanged`事件的参数使用发生变化的属性名称构造。

如下所示：

```csharp
class XXX : INotifyPropertyChanged
{
	// 实现接口事件
	public event PropertyChangedEventHandler PropertyChanged;

	// 属性私有变量
	private int _xxx = 0;

	// 属性包装器
	public int Xxx
	{
		get { return _xxx; }
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

### 绑定语法
进行绑定操作需要明确目标对象的路径，`WPF`提供了`ElementName、Source、RelativeSource`三种绑定对象。

默认绑定
> 在不显式指定绑定对象的情况下，默认将`DataContent`作为绑定对象。
>
>	```xml
>	XXX="{Binding xxx}"
>	<!-- 等价于 -->
>	XXX="{Binding Path=xxx}"
>	<!-- 对于需要显示转换的内容，指定转换器 -->
>	XXX="{Binding Path=xxx, Converter={StaticResource xxx}}"
>	```

绑定`ElementName`
> `ElementName`是控件拥有的属性，将绑定对象设置为当前XAML文件内的某一个控件。
>
>	```xml
>	XXX="{Binding ElementName=xxx, Path=xxx}}"
>	```

绑定`Source`
> `Source`属性用于指定对象绑定路径的引用。
>
>	```xml
>	XXX="{Binding Source={StaticResource xxx}}"
>	```

绑定`RelativeSource`
> `RelativeSource`属性支持以一定的规则来确定绑定对象。
>
>	```xml
>	<!-- 绑定到自身 -->
>	XXX="{Binding xxx, RelativeSource={RelativeSource Self}}"
>	<!-- 绑定到指定类型属性 -->
>	XXX="{Binding xxx, RelativeSource={RelativeSource Mode=FindAncestor, AncestorType={x:Type xxx}}}"
>	```

### 绑定模式
控件自身的属性被称为**目标属性**，绑定的数据源对象称为**源属性**，源属性与目标属性之前有四类同步方式：

- `OneWay` 源属性发生变化通知目标属性。只读型控件的默认绑定方式(`Label`等)
- `OneWayToSource` 目标属性发生变化通知源属性
- `TwoWay` 源属性与目标属性相互同步改动，开销比单向同步更高。可编辑型控件的默认绑定方式(`TextBox`、`ComboBox`等)
- `OneTime` 仅在初始化源属性时读取目标属性一次，开销最低

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



## `Window`(窗口)与`Page`(页面)
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

0. `FrameworkElement.Initialized`事件，在所有子元素已被设置完毕时触发。
0. `Window.Activated`事件，在窗口被激活时触发。
0. `FrameworkElement.Loaded`事件，在控件布局结束、数据绑定完成时触发。
0. `Window.ContentRendered`事件，在控件渲染完毕时触发。

在窗体关闭时，会依次触发以下事件：

0. `Window.Closing`事件，在窗口即将被关闭前触发，在此阶段可以取消窗口关闭。
0. `Window.Deactivated`事件，窗口变为后台窗口时触发。
0. `FrameworkElement.Unloaded`事件，窗口移除子元素完成时触发。
0. `Window.Closed`事件，窗口完全关闭时触发。

从`Window`类继承时，可以通过重写相关事件对应方法来实现更精细的阶段控制，以`FrameworkElement.Initialized`事件为例，重写`OnInitialized()`方法，如下所示：

```csharp
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

```csharp
// 直接设置页面Content字段到新页面的Uri实例实现跳转
Page.Content = new Uri("XXX.xaml", UriKind.Relative);
```

也可以通过使用`NavigationService`类控制页面跳转：

```csharp
// 使用NavigationService跳转到页面路径
NavigationService.GetNavigationService(source).Navigate(new Uri("XXX.xaml", UriKind.Relative));
// 跳转到下一页面
NavigationService.GetNavigationService(source).GoForward();
// 跳转到下一页面
NavigationService.GetNavigationService(source).GoBack();
```



## `Grid`容器
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



## 日期控件`DatePicker`
`WPF`提供了日期选择控件`DatePicker`。

### 设置默认显示日期
设置控件的`SelectedDate`属性为指定时间即可。

> 设置`DatePicker`默认显示当前日期：
>
> 方法一，在后台设置。
>> 在后台代码中设置`SelectedDate`为当前时间：
>>
>>	```csharp
>>	datePicker.SelectedDate = System.DateTime.Now;
>>	```
>
> 方法二，在前台定义。
>> 在`XAML`中添加命名空间定义：
>>
>>	```
>>	xmlns:sys="clr-namespace:System;assembly=mscorlib"
>>	```
>>
>> 之后设置控件属性：
>>
>>	```
>>	SelectedDate="{x:Static sys:DateTime.Now}"
>>	```

### 禁止日期文本编辑
默认情况下，`DatePicker`控件的文本日期显示框支持直接编辑文本来设定日期，需要禁止此特性可以使用以下方式：

> 将`Focusable`属性设置为`False`。
>
>	```
>	<DatePicker Focusable="False"/>
>	```

设置`Focusable`属性通过禁用焦点获取来限制编辑功能，文本框状态显示正常。

> 设置子控件`DatePickerTextBox`的`IsReadOnly`属性为`False`。
>
>	```
>	<DatePicker.Resources>
>		<Style TargetType="DatePickerTextBox">
>			<Setter Property="IsReadOnly" Value="True"/>
>		</Style>
>	</DatePicker.Resources>
>	```

`IsReadOnly`直接禁用了文本框的编辑属性，文本框直接显示为无法编辑。