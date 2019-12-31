<!-- TOC -->

- [概述](#概述)
- [XAML](#xaml)
- [控件與佈局](#控件與佈局)
	- [控件樣式](#控件樣式)
	- [佈局](#佈局)
	- [控件對齊](#控件對齊)
- [ResourceDictionary (資源字典)](#resourcedictionary-資源字典)
	- [創建資源字典](#創建資源字典)
	- [引用資源字典](#引用資源字典)
- [數據綁定](#數據綁定)
	- [屬性變更通知](#屬性變更通知)
	- [綁定語法](#綁定語法)
	- [綁定靜態字段](#綁定靜態字段)
	- [後臺綁定](#後臺綁定)
	- [綁定模式](#綁定模式)
	- [數據更新觸發器](#數據更新觸發器)
	- [綁定源/目標更新觸發事件](#綁定源目標更新觸發事件)
	- [多重綁定](#多重綁定)
- [觸發器](#觸發器)
	- [屬性觸發器](#屬性觸發器)
	- [數據觸發器](#數據觸發器)
	- [事件觸發器](#事件觸發器)
	- [事件綁定到命令](#事件綁定到命令)
- [Window (窗口) 與 Page (頁面)](#window-窗口-與-page-頁面)
	- [啓動窗口/頁面](#啓動窗口頁面)
	- [窗體加載與關閉](#窗體加載與關閉)
	- [頁面跳轉](#頁面跳轉)
- [Grid (網格容器)](#grid-網格容器)
- [DataGrid (數據網格)](#datagrid-數據網格)
	- [綁定數據庫](#綁定數據庫)
	- [數據源類型](#數據源類型)
- [DatePicker (日期控件)](#datepicker-日期控件)
	- [設置默認顯示日期](#設置默認顯示日期)
	- [禁止日期文本編輯](#禁止日期文本編輯)
- [DevExpress](#devexpress)
	- [常用控件](#常用控件)
	- [佈局層級](#佈局層級)
	- [主界面](#主界面)
	- [漢化控件](#漢化控件)
	- [加載指示器](#加載指示器)
	- [常見問題](#常見問題)

<!-- /TOC -->



# 概述
`WPF`全稱爲`Windows Presentation Foundation`，是微軟在`Windows Vsita`時代引入的用戶界面框架。

`WPF`向開發人員提供了一個統一的編程模型，用於在`Windows`上構建現代業務線桌面應用程序。



# XAML
`XAML`是一種聲明性標記語言，語法類似`xhtml`，`WPF`使用其創建`UI`。

在`Windows Form`中，一個`GUI`窗體的佈局代碼在文件**GUI類名.Designer.cs**中；
在`WPF`中，`GUI`窗體不再**直接**使用`C#`代碼創建，而使用**GUI類名.xaml**文件描述窗體佈局。

`XAML`文件實際上是後綴名爲`.xaml`的`XML`文件，默認編碼爲`UTF-8`。
在項目編譯時，`XAML`描述的`GUI`窗體會被轉換爲等價的`C#`代碼。



# 控件與佈局
`WPF`中所有控件位於`System.Windows.Controls`命名空間下，大多數控件從基類`System.Windows.Controls.Control`中繼承。

- `Button` 按鈕控件，類似於Qt中的`QButton`
- `Label` 標籤控件，類似於Qt中的`QLabel`
- `TextBlock` 基本文本顯示控件(不可編輯)
- `TextBox` 簡單文本輸入控件，類似於Qt中的`QLineEdit`
- `RadioButton` 單選框，類似於Qt中的`QRadioButton`
- `CheckBox` 複選框，類似於Qt中的`QCheckBox`
- `PasswordBox` 密碼文本控件，類似於Qt中`QLineEdit`設置了`QLineEdit::EchoMode`屬性爲`QLineEdit::Password`
- `GroupBox` 控件組，類似於Qt中的`QGroupBox`，設置標題使用屬性`Header`

按鈕/標籤設置文本使用屬性`Content`，文本控件設置文本使用屬性`Text`。
`Content`屬性中可添加其它控件，`Text`屬性只能接收文本。

`TextBox`可以有焦點，可編輯，`TextBlock`不可。
`PasswordBox`擁有屬性`PasswordChar`用於設置密碼回顯字符。

## 控件樣式
使用`<Style>`標籤可以定義統一的控件樣式，基本用法如下：

```xml
<Style x:Key="key值" TargetType="{x:Type 類型}">
	<Setter Property="屬性名稱" Value="屬性值"/>
</Style>
```

- `TargetType`屬性爲`<Style/>`標籤必選，用於指明`<Style/>`生效的控件類型。
- `Key`屬性可以省略，當`Key`屬性省略時，有效範圍內的所有`TargetType`類型的控件都將應用該Style(類似於`CSS`)。

控件引用設定了`x:Key`屬性的`<Style/>`：

```xml
<XXX Style="{StaticResource key值}"/>
```

## 佈局
在`WPF`官方控件中，佈局並非可自由設置的屬性，應選用具有特定佈局的容器控件相互組合構建複雜界面。

- `StackPanel` 水平/垂直容器，屬性`Orientation`用於設置內部控件對齊方向
- `WrapPanel` 流式佈局容器，子控件按行排列，填滿一行自動換行
- `DockPanel` 停靠面板容器，上下左右四個方向可分別設置不同子控件，最後一個控件做爲中央控件填滿剩餘空間
- `Grid` 網格容器，可自由分配每個網格的空間(最常用)

## 控件對齊
大多數控件都具有以下對齊屬性：

- `VerticalAlignment`/`HorizontalAlignment` 設置控件自身的對齊方向
- `VerticalContentAlignment`/`HorizontalContentAlignment` 設置控件內部內容的對齊方向

水平對齊屬性可取值`Left`、`Right`，垂直對齊屬性可取值`Top`、`Buttom`
對齊屬性取值`Stretch`則代表**拉伸元素填充父元素的整個佈局槽**。

對於`TreeView`、`ListView`等控件，默認情況下其子控件`TreeViewItem`、`ListViewItem`不會填滿整個父控件，設置`HorizontalContentAlignment`屬性爲`Stretch`則能夠令子控件水平方向填充滿父控件。



# ResourceDictionary (資源字典)
資源字典是一個以`<ResourceDictionary/>`爲根標籤，包含資源定義的`XAML`文件。

在`WPF`中，對於多個`XAML`重複引用的資源(樣式、轉換器類等)，可以將重複的資源定義寫在**資源字典**中，在外部進行引用，避免編寫重複代碼。

資源字典作用類似於WEB開發中`HTML`引用的`CSS`文件。

## 創建資源字典
在需要創建資源字典的路徑下單擊右鍵，選擇以下菜單添加資源字典：

```
添加 => 資源字典
```

典型的資源字典內容如下：

```xml
<ResourceDictionary
		xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
		xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
		xmlns:local="clr-namespace:Xxx.Xxxx">

	<!-- 資源字典內可以定義任意的資源內容 -->
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

## 引用資源字典
在常見標籤的`<Resources/>`子標籤中可以引用資源字典，以`<Application/>`標籤爲例：

```xml
<Application x:Class="Xxx.App"
		xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
		xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
		xmlns:local="Xxx.Xxxx..."
		StartupUri="Xxx...">

	<Application.Resources>
		<!-- 引用資源字典 -->
		<ResourceDictionary>
			<ResourceDictionary.MergedDictionaries>
				<ResourceDictionary Source="/Xxx/資源字典文件1.xaml"/>
				<ResourceDictionary Source="/Xxx/資源字典文件2.xaml"/>
				...
			</ResourceDictionary.MergedDictionaries>
		</ResourceDictionary>
	</Application.Resources>

</Application>
```

在`<Application/>`標籤中引用的資源字典在**整個應用**中有效，在其它標籤中引用的的資源字典僅在標籤內部有效。

若資源字典使用`x:Key`屬性命名，則需要通過資源字典的`x:Key`顯式引用才能生效：

```xml
<Window x:Class="Xxx.XxxWindow"
		xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
		xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
		xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
		xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
		xmlns:local="Xxx.Xxxx...">

	<Window.Resources>
		<!-- 引用資源字典，使用x:Key屬性 -->
		<ResourceDictionary x:Key="RefResources">
			<ResourceDictionary.MergedDictionaries>
				<ResourceDictionary Source="/Xxx/資源字典文件1.xaml"/>
				<ResourceDictionary Source="/Xxx/資源字典文件2.xaml"/>
				...
			</ResourceDictionary.MergedDictionaries>
		</ResourceDictionary>
	</Window.Resources>

	<!-- 顯式通過x:Key屬性使用資源字典，該資源字典僅在Grid標籤內部生效 -->
	<Grid Resources="{StaticResource RefResources}">
		...
	</Grid>

</Window>
```



# 數據綁定
`WPF`作爲數據驅動的UI框架，與`Qt`、`MFC`等傳統消息式驅動的UI框架最顯著的區別便是**數據綁定**。

在`WPF`中，典型的設計模式爲`MVVM`。
對於一個`View`，會創建對應的`ViewModel`來描述其數據結構，並通過控件綁定`ViewModel`中的屬性來實現多控件同步數據變化。

控件自身的屬性被稱爲**目標屬性**，綁定的數據源對象稱爲**源屬性**。
通過將目標屬性綁定到源屬性上，源屬性的變化會同步到目標屬性上，改變源屬性即可改變目標屬性。
通過數據綁定避免直接操作`GUI`，實現顯示層與邏輯層隔離。

## 屬性變更通知
對於一個屬性，要實現改變屬性值時通知外部，需要滿足以下要求：

- 屬性所在的Model實現`INotifyPropertyChanged`接口。
- 屬性的`set`方法中觸發接口中定義的`PropertyChanged`事件。
- 觸發`PropertyChanged`事件的參數使用發生變化的屬性名稱構造。

如下所示：

```cs
using System.ComponentModel;

class XXX : INotifyPropertyChanged
{
	// 實現接口事件
	public event PropertyChangedEventHandler PropertyChanged;

	// 屬性私有變量
	private int _xxx = 0;

	// 屬性包裝器
	public int Xxx
	{
		get => _xxx;
		set
		{
			_xxx = value;
			// 屬性變量變化時調用PropertyChanged事件，參數爲屬性名稱(不是存儲包裝器值的私有變量名稱)
			PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Xxx"));
		}
	}
}
```

只有需要自行修改數據源內數據並**通知外界**時才需要實現`INotifyPropertyChanged`接口，如果數據源僅僅作爲**數據獲取**使用則無必要。

- 封裝`INotifyPropertyChanged`接口

	在實際開發中，一般會對`INotifyPropertyChanged`接口做一個簡單的封裝，如下所示：

	```cs
	using System.ComponentModel;
	using System.Runtime.CompilerServices;

	public class NotifyObject : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		/// <summary>
		/// 屬性發生改變時調用該方法發出通知
		/// </summary>
		/// <param name="propertyName">屬性名稱</param>
		public void RaisePropertyChanged(string propertyName)
			=> PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
	}
	```

	使用：

	```cs
	class XXX : NotifyObject
	{
		private int _xxx = 0;

		// 屬性包裝器
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

- 使用`nameof`獲取屬性字段名稱

	在`C# 6.0`中新增了`nameof`關鍵字，作用是獲取字段的**當前名稱**(不是完整路徑名稱)。
	可利用該特性獲取屬性名稱，上述例子中的`Xxx`屬性可以改寫爲：

	```cs
	class XXX : NotifyObject
	{
		private int _xxx = 0;

		// 屬性包裝器
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

	使用`nameof`獲取屬性名稱，能使屬性在重構名稱時避免手動修改傳入屬性通知方法的名稱字符串。

- 使用`CallerMemberNameAttribute`特性簡化屬性通知方法

	在`.Net 4.5`中引入的`System.Runtime.CompilerServices.CallerMemberNameAttribute`可用於獲取調用者的名稱。
	利用該特性可簡化屬性通知方法的參數。

	如下所示：

	```cs
	using System.ComponentModel;
	using System.Runtime.CompilerServices;

	public class NotifyObject : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		// propertyName參數使用CallerMemberName特性修飾，方法被調用時propertyName會自動填入調用者信息(屬性名)
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

				// 方法調用無需參數，參數由編譯器生成
				RaisePropertyChanged();
			}
		}
	}
	```

	被`[CallerMemberName]`特性修飾的方法參數在編譯時會自動填入調用者的名稱。
	在屬性中的`set`、`get`塊中調用方法，則填入的參數爲屬性的名稱。

	使用`[CallerMemberName]`特性，能使屬性在重構名稱時避免手動修改傳入屬性通知方法的名稱字符串。

## 綁定語法
進行綁定操作需要明確目標對象的路徑，`WPF`提供了`ElementName`、`Source`、`RelativeSource`三種綁定對象。

- 默認綁定

	在不顯式指定綁定對象的情況下，默認將`DataContent`作爲綁定對象。

	```xml
	XXX="{Binding xxx}"
	<!-- 等價於 -->
	XXX="{Binding Path=xxx}"
	<!-- 對於需要自定義顯示邏輯的內容，指定轉換器 -->
	XXX="{Binding Path=xxx, Converter={StaticResource xxx}}"
	<!-- 指定轉換器同時可以傳入一個自定義參數，用於傳遞某些附加信息 -->
	XXX="{Binding Path=xxx, Converter={StaticResource xxx}, ConverterParameter=xxx}"
	```

	綁定的轉換器需要實現`System.Windows.Data.IValueConverter`接口，接口定義如下：

	```cs
	public interface IValueConverter
	{
		object Convert(object value, Type targetType, object parameter, CultureInfo culture);
		object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture);
	}
	```

	- `Convert`方法的`value`參數爲待轉換的源數據。
	- `ConvertBack`方法的`value`參數爲轉換後的數據。
	- `parameter`參數爲數據綁定中傳入的自定義轉換參數。

	綁定中的`ConverterParameter`通常用於傳遞一些編譯時就已確定的數據。
	若需要傳遞多個動態變化的數據並同步更新，則應使用**多重綁定**。

- 綁定`ElementName`

	`ElementName`是控件擁有的屬性，將綁定對象設置爲當前XAML文件內的某一個控件。

	```xml
	XXX="{Binding xxx, ElementName=xxx}"
	```

- 綁定`Source`

	`Source`屬性用於指定對象綁定路徑的引用。

	```xml
	XXX="{Binding xxx, Source=xxx}"
	```

- 綁定`RelativeSource`

	`RelativeSource`屬性支持以一定的規則來確定綁定對象。

	```xml
	<!-- 綁定到自身 -->
	XXX="{Binding xxx, RelativeSource={RelativeSource Self}}"
	<!-- 綁定到指定類型屬性 -->
	XXX="{Binding xxx, RelativeSource={RelativeSource Mode=FindAncestor, AncestorType={x:Type xxx}}}"
	```

## 綁定靜態字段
綁定到靜態字段時，需要首先使用`xmlns`屬性聲明靜態字段所屬類的命名空間：

```XML
<Window xmlns:xxxNameSpace="clr-namespace:Xxx.Xxx...">
	...
</Window>
```

直接綁定到某個靜態字段：

```xml
XXX="{x:Static xxxNameSpace:Xxx.xxx}}"
```

綁定到靜態字段內部的某個屬性：

```xml
<!-- 綁定到靜態字段中的某個路徑(xxx) -->
XXX="{Binding xxx, Source={x:static namespace:Xxx.xxx}}"
```

亦可將靜態類聲明爲靜態資源：

```xml
<xxxNameSpace:Xxx x:Key="xxx">
```

綁定到靜態資源：

```xml
XXX="{StaticResource xxx}"
XXX="{Binding xxx, Source={StaticResource xxx}}"
```

## 後臺綁定
除了在`XAML`文件中直接建立數據綁定，也可以調用`API`在後端進行綁定。

所有繼承自`FrameworkElement`的類型均包含`SetBinding()`方法：

```cs
//
// 摘要:
//     根據提供的綁定對象，將綁定附加到此元素上。
//
// 參數:
//   dp:
//     標識應在其中建立綁定的屬性。
//
//   binding:
//     表示數據綁定的細節。
//
// 返回結果:
//     記錄綁定的情況。此返回值可用於錯誤檢查。
public BindingExpressionBase SetBinding(DependencyProperty dp, BindingBase binding);
```

使用`System.Windows.Data.Binding`類型構建綁定實例，並設置綁定相關參數。
調用目標控件的`SetBinding()`方法，將`Bingding`類型實例與具體的控件目標屬性相關聯：

```cs
Binding binding = new Binding
{
	Path = new PropertyPath("xxx"),
	Source = ...,
	Converter = ...,
	Mode = ...,
	...
};

目標控件實例.SetBinding(目標控件類型.依賴屬性, binding);
```

對於多數常見的數據綁定，僅需提供綁定路徑即可，`Binding`類型提供了以**綁定路徑字符串**構造實例的構造方法：

```cs
//
// 摘要:
//     使用初始路徑初始化 System.Windows.Data.Binding 類的新實例。
//
// 參數:
//   path:
//     綁定的初始 System.Windows.Data.Binding.Path。
public Binding(string path);
```

## 綁定模式
數據綁定時可以設置綁定模式(`Mode`)：

```xml
XXX="{Binding xxx, Mode=xxxx}"
```

源屬性與目標屬性之前有四類同步方式：

- `OneWay` 源屬性發生變化通知目標屬性。只讀型控件的默認綁定方式(`Label`等)
- `OneWayToSource` 目標屬性發生變化通知源屬性
- `TwoWay` 源屬性與目標屬性相互同步改動，開銷比單向同步更高。可編輯型控件的默認綁定方式(`TextBox`、`ComboBox`等)
- `OneTime` 僅在初始化目標屬性時讀取源屬性一次，開銷最低

## 數據更新觸發器
在使用`OneWay/OneWayToSource`綁定時，綁定同時可以設置數據更新觸發器(`UpdateSourceTrigger`)，配置何時更新綁定源數據：

```xml
XXX="{Binding xxx, UpdateSourceTrigger=xxxx}"
```

- `Default` 默認方式，對於不同的控件有不同的定義
- `PropertyChanged` 當綁定目標屬性更改時，立即更新綁定源
- `LostFocus` 當綁定目標元素失去焦點時，更新綁定源
- `Explicit` 僅在調用`System.Windows.Data.BindingExpression.UpdateSource`方法時更新綁定源

## 綁定源/目標更新觸發事件
對於`FrameworkElement`類的子控件，會包含`SourceUpdated/TargetUpdated`兩個事件。

- 控件上任何設置了`NotifyOnTargetUpdated=True`的綁定在目標屬性更新時都會觸發`TargetUpdated`事件。
- 控件上任何設置了`NotifyOnSourceUpdated=True`的綁定在源屬性更新時都會觸發`SourceUpdated`事件。

綁定的`NotifyOnTargetUpdated/NotifyOnSourceUpdated`屬性默認爲`False`，需要在建立綁定時顯式設置其值爲`True`，如下所示：

```xml
<!-- 控件的事件觸發回調函數可以直接設置 -->
<XXX SourceUpdated="源屬性更新回調方法" TargetUpdated="目標屬性更新回調方法"
		XXX="{Binding xxx, NotifyOnSourceUpdated=True, NotifyOnTargetUpdated=True}"/>
```

## 多重綁定
當一個控件的目標屬性依賴於**多個**數據源時，可以使用**多重綁定**。

以常見的`Label`控件爲例，多重綁定語法如下：

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

使用多重綁定時，必須要指定轉換器來處理多個數據源，轉換器需要實現`IMultiValueConverter`接口。

與單一綁定使用的接口`IValueConverter`相比，`IMultiValueConverter`的接口方法`Convert()`首個參數類型由`object`變爲`object[]`，數組中保存了多個綁定數據源的值，順序按照綁定次序排列。

在實現數值轉換接口時，需要對未設定值進行檢驗，數值轉換異常時，首個參數會傳入代表**未設定值**的特殊變量`DependencyProperty.UnsetValue`。



# 觸發器
觸發器能夠在滿足某種條件時觸發操作。
觸發器包括以下三類：

- `Trigger` 屬性觸發器
- `DataTrigger` 數據觸發器
- `EventTrigger` 事件觸發器

`FrameworkElement`類型中定義了`Triggers`屬性，用於設定觸發器。
繼承自`FrameworkElement`類型的控件皆可在控件內部定義觸發器，例如：

```xml
<Window>
	<Window.Triggers>
		<Trigger>
			...
		</Trigger>
	</Window.Triggers>
</Window>
```

`Style`、`DataTemplate`、`ControlTemplate`等類型可用於定義通用的觸發器。
以`Style`爲例，定義觸發器語法如下：

```xml
<Style TargetType="目標控件類型">
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

## 屬性觸發器
屬性觸發器可用於監視任意可綁定的屬性，當被監視的屬性滿足條件時則執行觸發器。

以`Style`爲例，監視`Image`控件的`IsEnabled`屬性，如下所示：

```xml
<Style TargetType="Image">
	<Style.Triggers>
		<!-- 圖片 IsEnabled 屬性爲 True 時，設置 Opacity 屬性爲 1.0 -->
		<Trigger Property="IsEnabled" Value="True">
			<Setter Property="Opacity" Value="1.0"/>
		</Trigger>
		<!-- 圖片 IsEnabled 屬性爲 False 時，設置 Opacity 屬性爲 0.5 -->
		<Trigger Property="IsEnabled" Value="False">
			<Setter Property="Opacity" Value="0.5"/>
		</Trigger>
	</Style.Triggers>
</Style>
```

需要同時監視多個屬性時，可以使用`MultiTrigger`(多條件觸發器)，如下所示：

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

## 數據觸發器
數據觸發器用於監視綁定路徑的數據變化，當綁定的路徑數據滿足條件時則執行觸發器。

與屬性觸發器類似，數據觸發器也包括監視單一數據的`DataTrigger`與監視多數據的`MultiDataTrigger`。

```xml
<Style TargetType="Image">
	<Style.Triggers>

		<!-- 綁定路徑爲 Xxx 的目標數據值爲 xxx 時，設置 Opacity 屬性爲 1.0 -->
		<DataTrigger Binding="{Binding Path=Xxx}" Value="xxx">
			<Setter Property="Opacity" Value="1.0"/>
		</DataTrigger>

		<!-- 多條件數據觸發器 -->
		<MultiDataTrigger>
			<!-- 綁定路徑爲 XxxA 的目標數據值爲 xxxA 時，綁定路徑爲 XxxB 的目標數據值爲 xxxB 時，設置 Opacity 屬性爲 0.5 -->
			<MultiDataTrigger.Conditions>
				<Condition Binding="{Binding Path=XxxA}" Value="xxxA" />
				<Condition Binding="{Binding Path=XxxB}" Value="xxxB" />
			</MultiDataTrigger.Conditions>
			<Setter Property="Opacity" Value="0.5"/>
		</MultiDataTrigger>

	</Style.Triggers>
</Style>
```

## 事件觸發器
事件觸發器用於監視事件的發生，在事件觸發時執行觸發器。

事件觸發器只能綁定到**路由事件**(委託類型爲`RoutedEventHandler`)上。

```xml
<Style TargetType="Image">
	<Style.Triggers>

		<!-- 綁定到指定的路由事件 -->
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

## 事件綁定到命令
事件觸發器不能實現事件到命令的轉發，使用`System.Windows.Interactivity.dll`程序集可實現事件到命令的轉發。
`System.Windows.Interactivity.dll`**沒有**包含在默認的`WPF`中，需要從`NuGet`中下載，並引入該程序集：

```xml
<!-- 通過命名空間引入 -->
xmlns:i="http://schemas.microsoft.com/expression/2010/interactivity"

<!-- 或者直接引入dll -->
xmlns:i="clr-namespace:System.Windows.Interactivity;assembly=System.Windows.Interactivity"
```

以`Image`控件爲例，將`Image.MouseDown`事件綁定到`XxxCommand`(`System.Windows.Input.ICommand`的子類)上：

```xml
<Image>
	<i:Interaction.Triggers>
		<i:EventTrigger EventName="MouseDown">
			<i:InvokeCommandAction Command="{Binding XxxCommand}" CommandParameter="{Binding xxx}"/>
		</i:EventTrigger>
	</i:Interaction.Triggers>
</Image>
```



# Window (窗口) 與 Page (頁面)
在`WPF`中，**窗口**的類型爲`System.Windows.Window`，所有的其它窗口均從此類派生。

**頁面**的類型爲`System.Windows.Controls.Page`，`Page`不能夠單獨使用，需要搭配`NavigationWindow`或`Frame`才能顯示頁面。

## 啓動窗口/頁面
在`WPF`項目默認生成的`App`類的視圖`App.xaml`中，`<Application/>`標籤的屬性`StartupUri`指明瞭應用的啓動路徑。

默認生成的`App.xaml`如下所示：

```xml
<Application x:Class="XXX.App"
		xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
		xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
		StartupUri="XXXX.xaml">
</Application>
```

啓動路徑中指定的xaml文件可以是`Window`，也可以是`Page`。

在使用`Page`做爲`StartupUri`時，`WPF`會自動爲該`Page`創建一個`NavigationWindow`。

## 窗體加載與關閉
在窗體首次初始化、加載過程中，在不同階段會依次觸發以下事件：

1. `FrameworkElement.Initialized`事件，在所有子元素已被設置完畢時觸發。
1. `Window.Activated`事件，在窗口被激活時觸發。
1. `FrameworkElement.Loaded`事件，在控件佈局結束、數據綁定完成時觸發。
1. `Window.ContentRendered`事件，在控件渲染完畢時觸發。

在窗體關閉時，會依次觸發以下事件：

1. `Window.Closing`事件，在窗口即將被關閉前觸發，在此階段可以取消窗口關閉。
1. `Window.Deactivated`事件，窗口變爲後臺窗口時觸發。
1. `FrameworkElement.Unloaded`事件，窗口移除子元素完成時觸發。
1. `Window.Closed`事件，窗口完全關閉時觸發。

從`Window`類繼承時，可以通過重寫相關事件對應方法來實現更精細的階段控制，以`FrameworkElement.Initialized`事件爲例，重寫`OnInitialized()`方法，如下所示：

```cs
protected override void OnInitialized(EventArgs e)
{
	// do something before initialized...
	base.OnInitialized(e);
	// do something after initialized...
}
```

重寫`On*()`方法時不調用基類實現可以禁用匹配的事件。

## 頁面跳轉
頁面之間相互跳轉在前端可以使用`<Hyperlink/>`標籤實現：

```xml
<Label>
	<Hyperlink NavigateUri="XXX.xaml">xxx</Hyperlink>
</Label>
```

也可以在後端設置頁面`Content`屬性內容來實現頁面跳轉：

```cs
// 直接設置頁面Content字段到新頁面的Uri實例實現跳轉
Page.Content = new Uri("XXX.xaml", UriKind.Relative);
```

也可以通過使用`NavigationService`類控制頁面跳轉：

```cs
// 使用NavigationService跳轉到頁面路徑
NavigationService.GetNavigationService(source).Navigate(new Uri("XXX.xaml", UriKind.Relative));
// 跳轉到下一頁面
NavigationService.GetNavigationService(source).GoForward();
// 跳轉到下一頁面
NavigationService.GetNavigationService(source).GoBack();
```



# Grid (網格容器)
`Grid`容器提供了常見的**網格佈局**。

- `Grid`佈局的行定義寫在子標籤`<Grid.RowDefinitions/>`中，列定義寫在子標籤`<Grid.ColumnDefinitions/>`中。

	- 每一行由`<RowDefinition/>`標籤定義，屬性`Height`決定行高。
	- 每一列由`<ColumnDefinition/>`標籤定義，屬性`Width`決定列寬。

- `Grid`佈局的行高、列寬取值遵循以下規則：

	- 取值`*`爲自動填滿剩餘大小。
	- 取值`auto`由系統分配最合適的控件大小。
	- `*`前可以添加數值，在有多個控件取值`*`是，默認由這些控件均分剩餘的大小，`*`前添加數值則設定剩餘大小分配的**權重**。

- `Grid`佈局的位置定義：

	- `Grid`佈局的序號從`0`開始。
	- 在控件屬性中使用`Grid.Row`/`Grid.Cloumn`確定控件的行列位置。
	- 在控件屬性中使用`Grid.RowSpan`/`Grid.CloumnSpan`能讓控件佔據多行、多列。

一個簡單的`Grid`容器使用示例如下：

```xml
<!-- 定義一個帶有1行4列的Grid -->
<Grid>
	<!--定義行-->
	<Grid.RowDefinitions>
		<RowDefinition/>
	</Grid.RowDefinitions>
	<!--定義列-->
	<Grid.ColumnDefinitions>
		<ColumnDefinition Width="100"/> <!-- 第1列，固定寬度100 -->
		<ColumnDefinition Width="*"/> <!-- 第2列，均分剩餘寬度，權重1 -->
		<ColumnDefinition Width="0.5*"/> <!-- 第3列，均分剩餘寬度，權重0.5 -->
		<ColumnDefinition Width="auto"/> <!-- 第4列，根據該網格包含的控件自動適配寬度 -->
	</Grid.ColumnDefinitions>

	<!-- 定義Grid網格內的填充內容 -->
	<Label Content="xxx" Grid.Row="0" Grid.Cloumn="0"/> <!-- Label控件位置，第1行，第1列 -->
	<TextBox Grid.Row="0" Grid.Cloumn="1"/> <!-- TextBox控件位置，第1行，第2列 -->
	<!-- 添加其它控件，操作類似... -->

</Grid>
```



# DataGrid (數據網格)
使用`DataGrid`控件能夠方便地展示數據庫中的表。

`DataGrid`基本語法類似於`Grid`控件，但`DataGrid`可綁定數據源，展示數據源中的內容。
與`Grid`相比，`DataGrid`只需設置列屬性，每一行填充的內容由數據源決定。

`<DataGrid/>`標籤常用屬性：

- `ItemsSource`屬性：

	用於設置控件的數據集，綁定的對象需要爲集合類型。

- `SelectedItem`屬性：

	用於設置控件的當前焦點數據，綁定的對象類型爲數據集的模板參數。

- `AutoGenerateColumns`屬性：

	用於設置是否自動將數據集中的列顯示到控件上，若需要自定義數據顯示邏輯，則應設置該屬性爲`false`。

- `Columns`屬性：

	用於設置列樣式和顯示內容，可嵌套標籤：

	- `<DataGridTextColumn/>`爲普通文本列，最常用。
		- `Binding`屬性，綁定指定列
		- `IsReadOnly`屬性，設置內容是否只讀
		- `Width`屬性，設置寬度

基本代碼模板：

```xml
<DataGrid Name="XXX" AutoGenerateColumns="False" ItemsSource="{Binding XXX}" SelectedItem="{Binding XXX}">
	<DataGrid.Columns>
		<DataGridTextColumn Header="XXX" Binding="{Binding XXX}" IsReadOnly="True"/>
		<DataGridTextColumn Header="XXX" Binding="{Binding XXX}" Width="*"/>
		...
	</DataGrid.Columns>
</DataGrid>
```

## 綁定數據庫
`DataGrid`控件的屬性`ItemsSource`既可以綁定自行創建的集合類型，也可以直接綁定數據庫。

綁定數據庫時，數據源爲`DataView`類型，以`MySql`數據庫爲例：

```cs
MySqlConnection connection = new MySqlConnection("server = localhost; userid = XXX; password = XXX; database = XXX");
MySqlCommand command = new MySqlCommand("select * from 表名", connection);
MySqlDataAdapter dataAdapter = new MySqlDataAdapter(command); //執行查詢指令
DataSet dataSet = new DataSet(); //創建空數據源
dataAdapter.Fill(dataSet); //填充數據源
dataGrid.ItemsSource = dataSet.Tables[0].DefaultView; //綁定數據源中的表視圖
```

綁定到數據庫數據源時，數據庫中的改動會自動同步到控件上。

## 數據源類型
`DataGrid`同樣支持使用自定義數據集合做爲數據源。
在綁定數據源到自行創建的數據集合時，需要注意集合的類型。

- 常見的集合類型如`List`在數據發生增添、刪除等操作時，**不會**通知控件刷新。將數據源綁定到此類集合上，會造成數據集發生變動，但控件上並未同步發生改動。
- 要實現控件隨着數據源增刪而同步刷新需要使用特定集合類型`ObservableCollection`，此類型實現了`INotifyCollectionChanged`、`INotifyPropertyChanged`接口，能夠在集合發生變化時發出通知。



# DatePicker (日期控件)
`WPF`提供了日期選擇控件`DatePicker`。

## 設置默認顯示日期
設置控件的`SelectedDate`屬性爲指定時間即可。

設置`DatePicker`默認顯示當前日期：

- 方法一，在後臺設置。

	在後臺代碼中設置`SelectedDate`爲當前時間：

	```cs
	datePicker.SelectedDate = System.DateTime.Now;
	```

- 方法二，在前臺定義。

	在`XAML`中添加命名空間定義：

	```
	xmlns:sys="clr-namespace:System;assembly=mscorlib"
	```

	之後設置控件屬性：

	```
	SelectedDate="{x:Static sys:DateTime.Now}"
	```

## 禁止日期文本編輯
默認情況下，`DatePicker`控件的文本日期顯示框支持直接編輯文本來設定日期，需要禁止此特性可以使用以下方式：

- 將`Focusable`屬性設置爲`False`。

	設置`Focusable`屬性通過禁用焦點獲取來限制編輯功能，文本框狀態顯示正常。

	```xml
	<DatePicker Focusable="False"/>
	```

- 設置子控件`DatePickerTextBox`的`IsReadOnly`屬性爲`False`。

	`IsReadOnly`直接禁用了文本框的編輯屬性，文本框直接顯示爲無法編輯。

	```xml
	<DatePicker.Resources>
		<Style TargetType="DatePickerTextBox">
			<Setter Property="IsReadOnly" Value="True"/>
		</Style>
	</DatePicker.Resources>
	```



# DevExpress
`DevExpress`是一套商業UI庫，相比原生控件更加精美、控件功能更加強大。

## 常用控件
`DevExpress`爲幾乎所有WPF官方控件提供了功能更強大的版本。

常用的控件命名空間如下：

```xml
xmlns:dx="http://schemas.devexpress.com/winfx/2008/xaml/core"
xmlns:dxd="http://schemas.devexpress.com/winfx/2008/xaml/docking"
xmlns:dxe="http://schemas.devexpress.com/winfx/2008/xaml/editors"
xmlns:dxg="http://schemas.devexpress.com/winfx/2008/xaml/grid"
xmlns:dxnb="http://schemas.devexpress.com/winfx/2008/xaml/navbar"
```

## 佈局層級
`DevExpress`擴展了常用的佈局容器，在`DevExpress`中，常用的多文檔式窗口布局(`MDI`)層級：

`DockLayoutManager` => `LayoutGroup`/`TabbedGroup`/`DocumentGroup` => `LayoutPanel`

`LayoutGroup`、`TabbedGroup`、`DocumentGroup`需要`DockLayoutManager`做爲直接**父容器**，將`XXXGroup`直接添加在`LayoutPanel`中能通過編譯，但在運行時出錯。
`LayoutPanel`不能直接添加到`DockLayoutManager`中，會出現錯誤：`屬性LayoutRoot不支持類型LayoutPanel的值`。
`LayoutGroup`可通過`Orientation`屬性設置內部控件的對齊方向。

默認情況下，`LayoutPanel`會均分`LayoutGroup`的剩餘空間，要令`LayoutPanel`大小隨着內部控件大小改變則設置屬性`ItemHeight/ItemWidth`爲`auto`。

默認情況下，`DockLayoutManager`內的子控件會直接顯示在佈局中，要使某些子控件自動隱藏，可以使用`AutoHideGroup`，如下所示：

```xml
<dxd:DockLayoutManager.AutoHideGroups>
	<dxd:AutoHideGroup DockType="停靠方向">
		...
	</dxd:AutoHideGroup>
</dxd:DockLayoutManager.AutoHideGroups>
```

## 主界面
通常使用`DXDockPanel`進行主界面的佈局。
`DXDockPanel`的子控件可設置屬性`DockPanel.Dock`，取值`Top/Buttom/Left/Right`，最後一個控件會作爲中央控件填滿剩餘空間。

## 漢化控件
默認情況下，`DevExpress`提供的控件包含的默認文本均爲**英文**，需要使用官方提供的語言資源包才能使對應控件展示文本替換爲中文。

以`DevExpress 13.2`爲例，需要下載中文資源包：`DevExpressLocalizedResources_2013.2_zh-CN.zip`。
在項目的輸出目錄(生成可執行文件的目錄)中創建`zh-CN`文件夾，將解壓出的資源文件放置於該路徑下。
同時在`App`類中添加`UI`資源加載代碼：

```cs
public partial class App : Application
{
	// 加載UI資源相關代碼也可放置於App類的StartUp階段
	static App()
	{
		// 加載DevExpress中文UI資源
		Thread.CurrentThread.CurrentUICulture = new CultureInfo("zh-CN");
		Thread.CurrentThread.CurrentCulture = new CultureInfo("zh-CN");
	}

	public App()
	{
		...
	}
}
```

## 加載指示器
`DevExpress`提供了多種加載指示控件，用於在加載內容時提示用戶，避免UI假死：

- `WaitIndicator` 等待指示器

	當後臺需要執行一個耗時較長的操作時，前臺使用`WaitIndicator`告知用戶需要等待。
	`WaitIndicator`平時處於隱藏狀態，通過屬性控制其顯示狀態。
	`WaitIndicator`運行在**UI線程**，UI線程被佔用會影響`WaitIndicator`的顯示和等待動畫播放。

	常用屬性：

	- `DeferedVisibility` 是否顯示
	- `Content` 設置等待提示文本

	如下所示：

	```xml
	<dx:WaitIndicator DeferedVisibility="True" Content="Loading..."/>
	```

	可以通過自定義數據模板更改等待指示器的外觀：

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

- `LoadingDecorator` 加載裝飾器

	`LoadingDecorator`默認在控件加載完畢前顯示，提示用戶控件處於準備狀態。
	將`LoadingDecorator`包裹在目標控件外層，即可在目標控件加載時顯示加載指示器。

	常用屬性：

	- `IsSplashScreenShown` 是否顯示
	- `SplashScreenDataContext` 綁定ViewModel
	- `SplashScreenLocation` 顯示位置
	- `OwnerLock` 加載指示器顯示時，目標控件的鎖定方式
	- `BorderEffect` 邊框高亮模式
	- `BorderEffectColor` 邊框高亮色彩

	如下所示：

	```xml
	<dx:LoadingDecorator SplashScreenDataContext="{Binding xxx}" SplashScreenLocation="CenterContainer">
		<view:XxxView/>
	</dx:LoadingDecorator>
	```

	`LoadingDecorator`使用`WaitIndicator`實現。
	但不同於`WaitIndicator`，`LoadingDecorator`運行在獨立線程，UI線程的操作不會影響`LoadingDecorator`的顯示和動畫播放。

	未綁定`IsSplashScreenShown`屬性時，`LoadingDecorator`會自動在目標控件處於加載狀態時顯示。
	綁定`IsSplashScreenShown`屬性時，則由數據源決定指示器的顯示與否。

	可以通過自定義數據模板更改加載指示器的外觀：

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

## 常見問題
記錄`DevExpress`控件在使用中遇到的問題。

- `DocumentGroup`中標籤不可拖動、關閉：

	`DocumentGroup`需要在`DockLayoutManager`中才能實現關閉標籤、拖動標籤等功能。

- `DocumentGroup`關閉標籤後標籤依舊保留到`ClosedPanels`列表中：

	設置`DocumentPanel`的`ClosingBehavior`屬性爲`ImmediatelyRemove`。
