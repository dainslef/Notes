[TOC]

## *Swing* 简介
`Swing`是`Java`平台下的传统`GUI`库。

`Swing`是`Java`标准库的一部分，包含于`Java SE`中。

与上代图形技术`AWT`的比较：

- `AWT`使用各平台原生控件，在各平台上的原生控件上做了基础的封装。
- `Swing`控件完全由`Java`绘制。
- `AWT`控件因平台而异，相同控件在各`OS`中表现不尽相同。
- `Swing`控件在各`OS`下具有统一的外观样式与功能。
- `AWT`使用原生控件，执行效率高。
- `Swing`使用自绘控件，执行效率低下(在现代版本的`Java`中已有较大改善)。

### *Scala Swing*
`Scala`标准库中提供了`Java Swing`对应的`Scala API`封装。

在`sbt`项目中添加`Scala Swing`库：

```scala
libraryDependencies += "org.scala-lang.modules" %% "scala-swing" % "版本号"
```



## 常用控件
`Java Swing`提供的控件位于`javax.swing`包路径下，命名均以字母`J`起始。

`Scala Swing`对`Java Swing`提供的多数控件进行了浅层的封装，使之更符合`Scala`的`API`风格。
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

菜单栏：

| Java Swing 控件名称 | Scala Swing 控件名称 | 控件简介 |
|:-------------------|:-------------------|:--------|
| JMenubar | Menubar | 菜单栏 |
| JMenu | Menu | 菜单栏上的按钮 |
| JMenuItem | MenuItem | 点击菜单按钮弹出的菜单项 |

常用的表单组件都有对应的菜单版本，比如`JRadioButtonMenuItem`、`JCheckBoxMenuItem`等。
向`JMenu`中`add()`菜单项时，虽然可以选择普通组件，但普通组件不能触发菜单效果(点按之后菜单不收回)。



## *Border*
`javax.swing.border.Border`类型定义了边框的接口。

### 设置边框
常见**GUI容器**类如`JFrame`、`JPanel`等都可以通过`setBorder()`方法来设置边框：

```java
public void setBorder(Border border);
```

### *BorderFactory*
工厂类`BorderFactory`提供了一系列创建各类常见样式边框的静态方法。

*EmptyBorder*
> `EmptyBorder`为仅占据面板空间的透明边框。
>
> 通过使用`EmptyBorder`，可以实现控制控件边界空隙的效果(类似于**CSS**中的`Margin`属性)。
>
> 创建`EmptyBorder`的静态方法：
>
>	```java
>	// 创建默认样式的 EmptyBorder
>	public static Border createEmptyBorder();
>	// 创建指定边距的 EmptyBorder
>	public static Border createEmptyBorder(int top, int left, int bottom, int right);
>	```

*TitledBorder*
> `TitledBorder`为框线上带有标题的边框。
>
> `Swing`中并未提供默认的`GroupBox`控件，但可以对`JPanel`等控件设定`TitledBorder`来实现类似效果。
>
> 创建`EmptyBorder`的静态方法：
>
>	```java
>	public static TitledBorder createTitledBorder(Border border, String title,
>			int titleJustification, int titlePosition, Font titleFont, Color titleColor);
>	```



## *JTextArea*
`JTextField`只能用来显示简单的**单行文本**，涉及到**多行文本**的复杂情况，需要使用到`JTextArea`控件：

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

这样当文本无法全部显示时会出现**滚动条**。



## *MessageBox*
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
- `messageType`参数为对话框类型，可取值`DEFAULT_OPTION`、`YES_NO_OPTION`、`YES_NO_CANCEL_OPTION`、`OK_CANCEL_OPTION`等。
- `message`参数为在对话框中显示的消息内容。

使用`showInputDialog()`、`showConfirmDialog()`等方法可以用于显示其他用途的窗口。



## 事件机制
`Java`没有像`C#`那样在语言级别提供事件机制，事件机制仅仅在`Java`中仅仅是一套接口。

事件处理需要重写监听器的接口方法。
> `Swing`根据事件类型定义了一系列的事件监听器接口，如鼠标点按事件的`ActionListener`，处理键盘的`KeyListener`，处理鼠标的`MouseListener`等等。
> 不同的事件接口拥有不同数目的接口方法，根据需求重写对应的接口方法。

将控件绑定监听器实例。
> GUI控件类有一套与监听器接口对应的方法`addXXXListener()`用于添加不同类型的监听器实例，将对应的监听器实例作为参数传入，则当控件操作触发时，便会运行绑定监听器中的代码。
> 控件类也可以使用`removeXXXListener()`用于移除已绑定的监听器。

### 屏蔽指定按键输入
实现`KeyListener`接口，重写`keyTyped(KeyEvent)`方法，通过`getKeyChar()`方法获取输入的字符，然后对其进行判断，如果是想要屏蔽的按键则使用`setKeyChar('\0')`将其转化为空输入。

如下所示：(只接受数字输入)

```java
KeyEvent keyEvent = e -> {
	if (e.getKeyChar() < '0' || e.getKeyChar() > '9')
		e.setKeyChar('\0');
}
```

### *DocumentListener* (文本输入监听器)
包含三个方法：

- `public void changedUpdate(DocumentEvent e)` 监听文本属性的变化
- `public void insertUpdate(DocumentEvent e)` 监听文本内容的插入事件
- `public void removeUpdate(DocumentEvent e)` 监听文本内容的删除事件

`JTextField`控件本身没有`addDocumentListener()`方法，需要先使用`getDocument()`方法获取`Document`对象才能调用`addDocumentListener()`。
在事件处理方法中，对`JTextField`对象调用`getText()`方法即可获得输入文本的内容。



## *MVC*
`Swing`中的组件采用了`MVC`的设计模式，对于`JList`、`JComboBox`、`JTable`等控件均可通过组装`Model`构建对象并显示内容。

### *ComboBox*
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

### *JTable*
构建一个`JTable`主要有两种方式：

```java
JTable(Object[][] rowData, Object[] columnNames);
JTable(TableModel dm);
```

即使用`Object数组`确定表格模型或是使用`TableModel`类构建表格模型。
使用对象数组构建表格模型可以先从数组库中读取对应数据，然后将数据存储在对象数组中。

使用`TableModel`类的基本步骤：

0. 构建`TableMode`对象。
0. 使用`TableMode`类的成员方法`setValueAt(Object aValue, int rowIndex, int columnIndex)`设定表格模型每个位置的数据。
0. 在`JTable`使用构造函数或在已有的`JTable`实例调用`setModel(TableModel dataModel)`成员方法创建表格。