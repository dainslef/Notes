<!-- TOC -->

- [Swing 简介](#swing-简介)
	- [Scala Swing](#scala-swing)
- [常用控件](#常用控件)
	- [代码风格](#代码风格)
- [Border](#border)
	- [设置边框](#设置边框)
	- [BorderFactory](#borderfactory)
- [JTextArea](#jtextarea)
- [MessageBox](#messagebox)
- [事件机制](#事件机制)
	- [Java Swing 事件机制](#java-swing-事件机制)
	- [Scala Swing 事件机制](#scala-swing-事件机制)
- [MVC](#mvc)
	- [ComboBox](#combobox)
	- [JTable](#jtable)

<!-- /TOC -->



# Swing 简介
`Swing`是`Java`平台下的传统`GUI`库。
Swing是Java标准库的一部分，包含于`Java SE`中。

与上代图形技术`AWT`的比较：

- `AWT`使用各平台原生控件，在各平台上的原生控件上做了基础的封装。
- `Swing`控件完全由`Java`绘制。
- `AWT`控件因平台而异，相同控件在各`OS`中表现不尽相同。
- `Swing`控件在各`OS`下具有统一的外观样式与功能。
- `AWT`使用原生控件，执行效率高。
- `Swing`使用自绘控件，执行效率低下(在现代版本的`Java`中已有较大改善)。

## Scala Swing
Scala标准库中提供了`Java Swing`对应的`Scala API`封装：`Scala Swing`。

在sbt项目中添加Scala Swing依赖：

```scala
libraryDependencies += "org.scala-lang.modules" %% "scala-swing" % "版本号"
```



# 常用控件
Java Swing提供的控件位于`javax.swing`包路径下，命名均以字母`J`起始。

Scala Swing对`Java Swing`提供的多数控件进行了浅层的封装，使之更符合Scala的API风格。
`Scala Swing`控件位于`scala.swing`路径下，名称为对应的`Java Swing`控件去掉首字母`J`。

容器类控件：

| Java Swing 控件名称 | Scala Swing 控件名称 | 控件简介 |
|:-------------------|:-------------------|:--------|
| JFrame | Frame | 顶层窗体控件 |
| JDialog | Dialog | 对话框窗体 |
| JPanel | Panel | 面板 |
| JScrollPane | ScrollPane | 滚动面板 |

`JFrame/Frame`一般做为顶层容器，可以独立做为对话框显示，但`JPanel/Panel`不能独立做为对话框。

文本控件：

| Java Swing 控件名称 | Scala Swing 控件名称 | 控件简介 |
|:-------------------|:-------------------|:--------|
| JLabel | Label | 文本标签 |
| JTextField | TextField | 单行文本框 |
| JTextArea | TextArea | 多行文本框 |
| JPasswordField | PasswordField | 密码文本框(可设定回显字符) |

按钮控件：

| Java Swing 控件名称 | Scala Swing 控件名称 | 控件简介 |
|:-------------------|:-------------------|:--------|
| JButton | Button | 普通按钮 |
| JCheckBox | CheckBox | 复选框 |
| JRadioButton | RadioButton | 单选框 |
| JComboBox | ComboBox | 组合框(下拉列表框) |

多个`JRadioButton/RadioButton`需要添加到同一个`ButtonGroup`中才能实现**单选**效果。

菜单栏：

| Java Swing 控件名称 | Scala Swing 控件名称 | 控件简介 |
|:-------------------|:-------------------|:--------|
| JMenubar | Menubar | 菜单栏 |
| JMenu | Menu | 菜单栏上的按钮 |
| JMenuItem | MenuItem | 点击菜单按钮弹出的菜单项 |

常用的表单组件都有对应的菜单版本，比如`JRadioButtonMenuItem`、`JCheckBoxMenuItem`等。
向`JMenu`中`add()`菜单项时，虽然可以选择普通组件，但普通组件不能触发菜单效果(点按之后菜单不收回)。

## 代码风格
在Java Swing中，常见的创建控件、配置控件的方式为先构建对象实例，之后调用实例的成员方法设置控件属性。

使用Java Swing创建窗口，在窗口中添加控件：

```java
JFrame frame = new JFrame();
JLabel label = new JLabel();

label.setText("Test");
label.setMinimumSize(new Dimension(80, 40));

frame.add(label);
frame.setSize(new Dimension(200, 100));
frame.setVisible(true);
```

在Scala Swing中，创建控件、配置控件通常同步进行，使用**匿名类**特性，在创建控件时直接在构造方法中设定控件的各类属性。

Scala Swing的API更贴近Scala的语言风格。
使用Scala Swing构建配置控件语法更加类似DSL，可读性更高。

上述Java Swing例子使用Scala Swing代码如下：

```scala
val frame = new Frame {
  contents = new Label {
    text = "Test"
    minimumSize = new Dimension(80, 40)
  }
  size = new Dimension(200, 100)
  visible = true
}
```



# Border
`javax.swing.border.Border`类型定义了边框的接口。

## 设置边框
常见**GUI容器**类如`JFrame`、`JPanel`等都可以通过`setBorder()`方法来设置边框：

```java
public void setBorder(Border border);
```

## BorderFactory
工厂类`BorderFactory`提供了一系列创建各类常见样式边框的静态方法。

- `EmptyBorder`

	`EmptyBorder`为仅占据面板空间的透明边框。
	通过使用`EmptyBorder`，可以实现控制控件边界空隙的效果(类似于**CSS**中的`Margin`属性)。

	创建`EmptyBorder`的静态方法：

	```java
	// 创建默认样式的 EmptyBorder
	public static Border createEmptyBorder();
	// 创建指定边距的 EmptyBorder
	public static Border createEmptyBorder(int top, int left, int bottom, int right);
	```

- `TitledBorder

	`TitledBorder`为框线上带有标题的边框。
	`Swing`中并未提供默认的`GroupBox`控件，但可以对`JPanel`等控件设定`TitledBorder`来实现类似效果。

	创建`EmptyBorder`的静态方法：

	```java
	public static TitledBorder createTitledBorder(Border border, String title,
			int titleJustification, int titlePosition, Font titleFont, Color titleColor);
	```



# JTextArea
`JTextField`仅适用于显示简单的**单行文本**，涉及到**多行文本**时，应使用`JTextArea`控件：

```java
JTextArea textArea = new JTextArea();
```

可以设置文本域**自动换行**：

```java
textArea.setLineWrap(true);
```

当文本域内容太多无法全部显示时，可以使用`JScrollPane`控件，将文本域添加到其中：

```java
JScrollPane scrollPane = new JScrollPane(textArea);
```

当文本无法全部显示时会出现**滚动条**。



# MessageBox
与**Qt**类似，`Swing`也提供了弹出`MessageBox`的静态方法，即`JOptionPane.showMessageDialog()`。

```java
// 调出标题为"Message"的信息消息对话框
static void showMessageDialog(Component parentComponent, Object message);
// 调出对话框，显示使用由messageType参数确定的默认图标的message
static void showMessageDialog(Component parentComponent,
		Object message, String title, int messageType);
// 调出一个显示信息的对话框，指定了所有参数
static void showMessageDialog(Component parentComponent,
		Object message, String title, int messageType, Icon icon);
```

- `parentComponent`参数为父对话框。
- `messageType`参数控制对话框的内置按钮，可取值`DEFAULT_OPTION`、`YES_NO_OPTION`等。
- `message`参数为在对话框中显示的消息内容。

使用`showInputDialog()`、`showConfirmDialog()`等方法可以用于显示其他用途的窗口，参数类似。



# 事件机制
Java**没有**类似C#的语言级别事件机制。

Java Swing的事件机制采用`Observer`模式。
Scala Swing在事件处理上采用了`Reactor`模式，与Java Swing风格不同。

## Java Swing 事件机制
Java Swing的事件机制主要包括以下部分：

1. 监听器，包含对事件的处理逻辑。
1. 事件源，即触发事件的控件。
1. 事件，包含特定的事件信息。

- 监听器

	所有的的监听源都实现了`java.util.EventListener`接口。
	`EventListener`接口是空接口，`Java Swing`根据不同的事件类型定义了一系列继承于`EventListener`的子接口。

	不同的监听器接口定义了不同的抽象方法，当对应的监听事件触发时，对应方法会被调用。
	通过重写监听器接口的抽象方法来实现事件处理逻辑。

- 事件源

	事件源是某个具体的控件对象。
	控件对象通过绑定监听器对象在事件触发时调用对应监听器对象的重写方法。

	Java Swing中的控件都提供了命名类似的方法用于与监听器交互：

	```java
	// 绑定到指定监听器实例
	public synchronized void addXxxListener(XxxListener listener);
	// 移除到指定监听器实例的绑定
	public synchronized void removeXxxListener(XxxListener listener);
	// 获取当前控件已绑定的所有监听器实例
	public synchronized XxxListener[] getXxxListeners();
	```

	不同的控件类型根据其控件职能会拥有不同类型监听器的交互方法。

- 事件

	所有的事件都继承自`java.util.EventObject`。

	事件保存了具体的某一次事件发生时的事件信息。
	事件做为监听器抽象方法的参数，当事件触发时，对应的事件信息做为参数传入。

	以按钮控件的`ActionEvent`为例，实现`ActionEvent`的处理需要以下步骤：

	1. 构建`ActionEvent`监听器，监听器实现`ActionListener`接口，重写抽象方法`actionPerformed()`。
	1. 按钮控件对象调用`addActionListener()`方法，将控件绑定监听器。

	如下代码所示：

	```java
	// 构建监听器，ActionListener只有单个抽象方法，为函数式接口
	ActionListener action = e -> ...;

	JButton button = new JButton();

	// 将控件绑定监听器
	button.addActionListener(action);
	```

- 常见监听器类型应用

	1. *KeyListener* (键盘按键监听器)

 		通过键盘监听器可屏蔽指定按键输入。

		实现`KeyListener`接口，重写`keyTyped()`方法。
		对`KeyEvent`类型的事件参数调用`getKeyChar()`方法获取输入的字符，判断输入内容。
		对需要屏蔽的输入使用`setKeyChar('\0')`转化为空输入。

		如下所示：(只接受数字输入)

		```java
		KeyListener keyListener = e -> {
			if (e.getKeyChar() < '0' || e.getKeyChar() > '9') e.setKeyChar('\0');
		}
		```

## Scala Swing 事件机制
`Scala Swing`中，事件采用集中式处理，所有被监听的控件发出的各类事件会被汇总统一处理。

`Scala Swing`所有控件的基类`scala.swing.UIElement`都间接混入了事件发布者特质`scala.swing.Publisher`：

```scala
trait UIElement extends Proxy with LazyPublisher {
  ...
}

private[swing] trait LazyPublisher extends Publisher {
  ...
}
```

`Publisher`特质继承于反应器特质`scala.swing.Reactor`，该特质定义了用于发布事件的`publish()`方法：

```scala
trait Publisher extends Reactor {
  ...
  def publish(e: Event) { ... }
  ...
}
```

`Reactor`特质定义了与订阅者的交互方法，使用`listenTo()`添加订阅者，`deafTo()`移除订阅者。
`Reactor`特质定义了字段`reactions`，类型为`scala.swing.Reactions`：

```scala
trait Reactor {
  ...
  val reactions: Reactions = ...
  def listenTo(ps: Publisher*) = ...
  def deafTo(ps: Publisher*) = ...
  ...
}
```

`Reactions`为抽象类，继承于自身单例对象中定义的类型别名`Reactions.Reaction`(实际类型为偏函数`PartialFunction[Event, Unit]`)。
`Reactions`抽象类定义了用于增减偏函数的方法`+-()`、`-=()`：

```scala
object Reactions {
  ...
  type Reaction = PartialFunction[Event, Unit]
  ...
}

abstract class Reactions extends Reactions.Reaction {
  ...
  def += (r: Reactions.Reaction): this.type
  def -= (r: Reactions.Reaction): this.type
  ...
}
```

向`reactions`字段添加自定义的事件处理偏函数来处理UI事件。
`reactions`字段添加的偏函数参数为`scala.swing.event.Event`，返回值类型为`Unit`。

`Event`特质是所有`Scala Swing`事件类型的基类。
事件类型与`Java Swing`中类似，但使用了`Scala`的样例类特性，便于在事件处理偏函数中使用。

以`ActionEvent`为例，在`Scala Swing`中实现`ActionEvent`事件的处理：

```scala
val button = new Button

// 监听控件
listenTo(button)

// 偏函数添加 ActionEvent 事件处理逻辑
reactions += {
  case ActionEvent(source) => ...
}
```



# MVC
`Swing`中的组件采用了`MVC`的设计模式，对于`JList`、`JComboBox`、`JTable`等控件均可通过组装`Model`构建对象并显示内容。

## ComboBox
获取目标`Map`的`Key`集合：

```java
Set set = map.keySet();
```

接着将集合转化为对象数组：

```java
Object[] object = set.toArray();
```

接着构造一个用对象数组初始化的`DefaultComboBoxModel`对象，并以此构建`JComoBox`对象：

```java
JComboBox comboBox = new JComboBox(new DefaultComboBoxModel(object));
```

## JTable
构建一个`JTable`主要有两种方式：

```java
JTable(Object[][] rowData, Object[] columnNames);
JTable(TableModel dm);
```

即使用`Object数组`确定表格模型或是使用`TableModel`类构建表格模型。
使用对象数组构建表格模型可以先从数组库中读取对应数据，然后将数据存储在对象数组中。

使用`TableModel`类的基本步骤：

1. 构建`TableMode`对象。
1. 使用`TableMode`类的成员方法`setValueAt(Object aValue, int rowIndex, int columnIndex)`设定表格模型每个位置的数据。
1. 在`JTable`使用构造函数或在已有的`JTable`实例调用`setModel(TableModel dataModel)`成员方法创建表格。
