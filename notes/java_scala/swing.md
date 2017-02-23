[TOC]

## *Swing* 简介
`Swing`是`Java`平台下的传统`GUI`库，`Swing`中的控件样式与平台无关，完全由`Java`绘制。

## 常用控件
容器：

- `JFrame` 窗体框架
- `JDialog` 对话框
- `JPanel` 面板
- `JScrollPane` 滚动面板

`JFrame`一般做为顶层容器，可以独立做为对话框显示，但`JPanel`不能独立做为对话框。

文本组件：

- `JLabel` 显示文本
- `JTextField` 单行编辑框
- `JPasswordField` 密码编辑框
- `JTextArea` 多行编辑区域

表单组件：

- `JButton` 普通按钮
- `JCheckBox` 复选框，方框里打勾
- `JRadioButton和ButtonGroup` 单选框，圆点
- `JComboBox` 组合框，俗称**下拉列表框**

菜单栏：

- `JMenubar` 菜单栏
- `JMenu` 菜单栏上的按钮
- `JMenuItem` 点击菜单按钮弹出的菜单项

常用的表单组件都有对应的菜单版本，比如`JRadioButtonMenuItem`、`JCheckBoxMenuItem`等。
向`JMenu`中`add()`菜单项时，虽然可以选择普通组件，但普通组件不能触发菜单效果(点按之后菜单不收回)。



## 边框
一般的**GUI容器**类如`JFrame`、`JPanel`等都可以通过`setBorder()`方法来设置边框。

通过使用透明边框，可以实现控制界面边界空隙的效果(类似于**CSS**中的`Margin`属性)。

如下代码所示：

```java
//界面上下左右空出10个像素
setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
```



## 事件机制
`Java`没有像`C#`那样在语言级别提供事件机制，事件机制仅仅在`Java`中仅仅是一套接口：

事件处理需要重写监听器的接口方法。
> `Swing`根据事件类型定义了一系列的事件监听器接口，如鼠标点按事件的`ActionListener`，处理键盘的`KeyListener`，处理鼠标的`MouseListener`等等。
> 不同的事件接口拥有不同数目的接口方法，根据需求重写对应的接口方法。

将控件绑定监听器实例。
> GUI控件类有一套与监听器接口对应的方法`addXXXListener()`用于添加不同类型的监听器实例，将对应的监听器实例作为参数传入，则当控件操作触发时，便会运行绑定监听器中的代码。
> 控件类也可以使用`removeXXXListener()`用于移除已绑定的监听器。

### 在键盘事件中屏蔽指定按键
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

### 显示多行文本
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
与**Qt**一样，Java也提供了弹出MessageBox的静态方法，即`JOptionPane.showMessageDialog()`。

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

其中，`messageType`可以取`DEFAULT_OPTION`、`YES_NO_OPTION`、`YES_NO_CANCEL_OPTION`或`OK_CANCEL_OPTION`等。
此外，还有`showInputDialog()`、`showConfirmDialog()`等方法可以用于显示其他用途的窗口。



## *MVC*
`Swing`中的组件采用了`MVC`的设计模式，对于`JList`、`JComboBox`、`JTable`等控件均可通过组装`Model`构建对象并显示内容。

### 使用 *Model* 组装 *ComboBox*
先得到`Map`的`Key`集合：

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

### 使用 *JTable* 显示数据库
构建一个`JTable`主要有两种方式：

```java
JTable(Object[][] rowData, Object[] columnNames);
JTable(TableModel dm);
```

即使用`Object数组`确定表格模型或是使用`TableModel`类构建表格模型。
使用对象数组构建表格模型可以先从数组库中读取对应数据，然后将数据存储在对象数组中。

使用`TableModel`类的基本步骤：

0. 先构建`TableMode`对象。
0. 使用`TableMode`类的成员方法`setValueAt(Object aValue, int rowIndex, int columnIndex)`设定表格模型每个位置的数据。
0. 在`JTable`使用构造函数或在已有的`JTable`实例调用`setModel(TableModel dataModel)`成员方法创建表格。