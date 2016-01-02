[TOC]

##Java中的集合类型
与常见的编程语言相同，Java中的常见的**集合类型**为`List``Set``Map`。
`List`特点：元素**有序**，元素**可重复**。
`Map`特点：元素按键值对存储，**无序**。
`Set`特点：元素**无序**，元素**不可重复**(注意：元素虽然无放入顺序，但是元素在`Set`中的位置是有该元素的**HashCode**决定的，其位置其实是固定的)。

在Java中，这三种集合类型都是以接口形式存在的，不能直接使用，要使用这三种类型可以使用其实现类：
`List`的实现类为`LinkedList``ArrayList``Vector`；
`Set`接口有两个实现类`HashSet``LinkedHashSet`；
`Map`接口有三个实现类`HashMap``HashTable``LinkeHashMap`；

这些实现类各有优缺点：
`ArrayList`是**非线程安全**的，效率**高**；
`Vector`是基于**线程安全**的，效率**低**。
`HashMap`**非线程安全**，高效，**支持**null；
`HashTable`**线程安全**，低效，**不支持**null 。

语法：

```java
List<Type> list = new ArrayList<Type>();
list.add(type);
Map<Key, Type>  map = new HashMap<Key, Type>();
map.put(key, type);
```

Java支持泛型`<>`**菱形推断**，实例化时类型可以省略(Java1.7新特性)，上面的语句实例化可以简写为：

```java
List<Type> list = new ArrayList<>();
Map map = new HashMap<>();
```

甚至，你还可以直接省略`<>`符号，完全让编译器推断(Java1.8新特性，一般编译器会隐式推断为`Object`类型)：

```java
List list = new ArrayList();
Map map = new HashMap();
```

`Set`和`List`都可以得到一个迭代器用于迭代：

```java
Iterator iteratorList = list.iterator();
Iterator iteratorSet = set.iterator();
```

`Map`的`Key`就是一个`Set`，可以得到`Key`的集合再迭代：

```java
Set set = map.keySet();
Iterator iteratorSet = set.iterator();
```

`Map`使用`get(key)`可以得到对应的键值，但是这个键值是`Object`型的，需要通过向下转型来恢复键值类型。
`HashMap`之类的容器只能一个键对应**一个**键值，如果需要一个键绑定多个键值可以使用`IdentityHashMap`。



##浅复制与深复制
在Java中，**基础类型**如`int``double`等在复制时是拷贝了**整个值**，而对于**引用类型**，则默认拷贝的只是一个对象的**引用**(类似与C/C++中的**指针**)，对象本体**并未**被复制。

###浅复制
要想让一个类能够被复制，则类需要实现`Cloneable`接口，并重写`clone()`方法。
如下代码所示：

```java
class TestClone implements Cloneable {

	StringBuffer str = new StringBuffer("str");

	//重写clone()方法
	@Override
	public TestClone clone() {
		TestClone clone = null;
		try {
			clone = (TestClone)super.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return clone;
	}
}
```

虽然`clone()`方法来自于根类`Object`，但如果不实现`Cloneable`接口，则在调用`clone()`方法的时候会抛出`CloneNotSupportedException`异常。
编写代码测试：

```java
public class Main {
	public static void main(String[] args) {
		TestClone test = new TestClone();
		TestClone testClone = test.clone();
		test.str.append("New");
		System.out.println(testClone.str);
	}
}
```

输出结果：
strNew

可以发现调用`clone()`方法复制出的对象**testClone**在原对象**test**被修改后也发生了变化，并未真正的达到**复制**的效果。
原因是**TestClone**类完成的仅仅是**浅复制**的过程，类中的引用类型`StringBuffer`并未被真正复制。

###深复制
深复制一个对象，则需要将类中的每一个引用成员都进行**复制**，因此，**TestCode**的代码需要改成：

```java
class TestClone implements Cloneable {

	StringBuffer str = new StringBuffer("str");

	@Override
	public TestClone clone() {
		TestClone clone = null;
		try {
			clone = (TestClone)super.clone();
			clone.str = new StringBuffer(str);		//构建新的StringBuffer对象
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return clone;
	}
}
```

在重写`clone()`方法的过程中，要实现**深复制**，就需要类中的每一个引用类型重新构建，重新构建对象优先使用该引用类型的`clone()`方法(如果该类型实现了`Cloneable`接口)，如果需要复制的引用类型没有实现`Cloneable`接口，则直接使用构造函数创建一个与当前实例中保存内容相同的对象。
需要注意的是，`String`类型是个**特例**，虽然其为**引用类型**，但`String`内部重新实现了自身的`clone()`，在重写当前类的`clone()`方法的时候可以将其视为基本类型(即不必显式构建)。



##泛型方法
Java中的泛型同样支持独立于类的泛型方法，与**C++/C#**等语言不同，Java在泛型方法中的类型声明放在方法的修饰符(`public``static``final``abstract`等)之后，返回值声明之前。
Java中的泛型**不需要**也**不支持**使用`<>`符号显式指定泛型类型，在泛型方法中输入内容JVM会自动进行类型推倒。
例如：

```java
public class Test {
	public static void main(String[] args) {
		Func t = new Func();
		System.out.println(t.getType(123));
		System.out.println(t.getType("Test"));
		System.out.println(t.getType(25.672));
	}
}

class Func {
	public <T> T getType(T t) {
		return t;
	}
}
```

输出结果：(Windows 10 && JDK 1.8)
java
123
Test
25.672



##与Access数据库交互
**JDK1.7**之前，可以使用**JDBC-ODBC**桥接**Access**数据库，但在**JDK1.8**之后，**JDBC-ODBC**桥被移除，只能使用专有的Access驱动来连接Access数据库(驱动名称：`Access_JDBC40.jar`)。

###连接Access数据库的一般步骤
```java
//这样写是相对路径
String connectUrl = "jdbc:Access:///***.accdb";

//这样写是绝对路径
//String connectUrl = "jdbc:Access:///c:/a/b/***.accdb";

//注册驱动
Class.forName("com.hxtt.sql.access.AccessDriver");
//创建连接
Connection connection = DriverManager.getConnection(connectUrl);
Statement statement = connection
	.createStatement(
		ResultSet.TYPE_SCROLL_INSENSITIVE,
		ResultSet.CONCUR_READ_ONLY);
		//后两个参数是为了得到resultSet集能够进行last()操作
```

###Access数据库的一些小常识
1.表单的高级字段设置在`开始 - 视图 - 设计视图`中。
2.配置自增属性需要将字段类型设为`自动编号`。
3.默认情况下，创建的数据类型`数字`的字段大小为`长整型`，这是不支持**小数输入**的，小数输入会自动被去尾，需要将字段大小设置为`单精度浮点型/双精度浮点型`才能支持小数位。
4.如果需要某个字段的内容唯一不可重复，可以将改字段的索引设置为`有(无重复)`即可。



##Eclipse使用注记
**Eclipse**是Java开发中最常用的IDE，Eclipse通过插件扩展可以进行多种语言的开发。

###在Eclipse中查看JDK类源码
与**NetBeans**不同，在Eclipse中默认是无法直接查看JDK中类库的源码的，需要手动指定源码的位置。
一般情况下，JDK源码位于JDK的安装目录下的`src.zip`文件中。
在Eclipse中按以下步骤添加源码路径：
`Window`=>`Preferences`=>`Java`=>`Installed JREs`=>选中使用的`JRE` =>`Edit`=>选中`../xxx/rt.jar`=>`Source Attachment Configuration`=>`Exernal location`=>选中`src.zip`=>`OK`=>`Finish`

###设置Eclipse编辑器自动换行
Eclipse的编辑器没有自动换行的功能，该功能需要通过第三方插件进行实现。
在Eclipse中按以下步骤安装`Word Wrap`插件使编辑器能够自动换行：
`Help`=>`Install New Software`=>`Add Repository`=>输入仓库地址`http://ahtik.com/eclipse-update`=>安装`WordWrap`插件=>安装完成之后重启IDE=>编辑器中点右键，激活`Word Warp`选项=>`Finish`



##IntelliJ IDEA常用配置项
**IntelliJ IDEA**相比Eclipse而言，有着更精美的UI，且对`Scala``Golang`等冷门语言有着更好的支持。

###设置显示行号和不可见空白
`File`=>`Settings`=>`Editor`=>`General`=>`Appearance`=> ...
勾选`Show whitespaces(显示空白)`和`Show line numbers(显示行号)`选项。
勾选`Show menthod separators`则会在方法定义之间出现横线做为分隔符。

###设置缩进
默认情况下，IDEA使用的是**空格**做为缩进，如果需要使用**tab缩进**，则按以下路径设置：
`File`=>`Settings`=>`Editor`=>`Code Style`=>`[目标语言]`=>`Tabs and Indents`
选中`Use tab charactor`。
勾选`Smart tabs`则会在**行尾**使用tab键时使用**空格**代替tab。
勾选`Keep indents on empyt lines`则会在**空行**中**保持缩进**。

###其它常用选项
代码折叠：`File`=>`Settings`=>`Editor`=>`General`=>`Code Folding`
代码自动换行：`File`=>`Settings`=>`Editor`=>`General`=>`Soft Wraps`
设置空白处的点按逻辑：`File`=>`Settings`=>`Editor`=>`General`=> `Virtual Space`
设置Java强制类型转换前是否空格：`File`=>`Settings`=>`Editor`=>`Code Style`=>`Java`=>`Spaces`=>`After type cast`
设置Scala函数是否自动补全空返回类型：`File`=>`Settings`=>`Editor`=>`Code Style`=>`Scala`=>`Other`=>`Enfore procedure syntax for methods with Unit return type`
设置光标悬停显示变量/方法信息：`File`=>`Settings`=>`Editor`=>`General`=>`Other`=>`Show quick documentation on mouse move`



##关于Java中package
在Java中，没有使用package的话，在javac编译java文件生成class字节码时，需要将所有用到的源码文件写在参数中，不在当前目录下的源码文件要写清路径。
如果源码文件过多，则可以使用`package`关键字将其打包归类，然后在主类所在的文件中使用`import`关键字来将包导入使用。
如果没有使用package关键字，则所有的内容被视为在一个包中。

###import的基本用法
`import`的格式是：

```java
import [包名].[类名];
```

如果需要包含内部类，则可以使用多级import，如：

```java
import [包名].[类名].[类名]....;
```

需要注意的是，import与代码文件的路径**无关**(但运行class文件时需要将class文件放在与其源码中package名称相同的对应目录下，否则会在执行时出错)。
另外，包名也可以是`*.*.*`的形式。

###使用静态导入
`Java1.5`中新加入了`import static`关键字，相比传统的`import`，`import static`关键字的包含目标是类中的静态方法，格式如下：

```java
import static [包名].[类名].[类名]....[静态方法名]
```

这样能够在使用对应类的静态方法时不必写出类名而是直接写出函数名即可。

###package使用实例
有两个文件**A.java**和**B.java**。
文件B中的类被A中引用,则将B打包,代码中添加`package b`，并放在b目录下。
而文件A中引用B中的类。
按照要求，两文件的位置：
**文件A**路径为`~/A.java`。
**文件B**路径为`~/b/B.java`。

实例代码(普通import)：
A.java:

```java
import b.B;

public class A {
	public static void main(String[] args) {
		B.getNow();
	}
}
```

B.java:

```java
package b;

public class B {
	public static void getNow() {
		System.out.println("Success!");
	}
}
```

实例代码(import static)：
A.java:

```java
import static b.B.getNow;

public class A {
	public static void main(String[] args) {
		getNow();
	}
}
```

B.java:

```java
package b;

public class B {
	public static void getNow() {
		System.out.println("Success!");
	}
}
```

其中**A.java**文件能够正常调用类B的方法`getNow()`。
一个java文件只能有**一个public类**，java文件的名称应该与那个public类的类名**一致**。
需要注意的是，package打包的文件最好放在与包名相同的文件夹中，这样生成的字节码class文件才会在对应目录生成。如果源码是放在一处的，则编译之后产生的字节码文件需要按照package关系放在与包名相同的目录下，否则执行class文件时会报错，显示找不到对应的class文件！

###使用第三方包时的编译/运行方式
很多时候，我们需要使用java官方库之外的第三方库(jar文件)，编译时需要添加额外的参数。
假设代码中引用了一个第三方库，则编译时应使用`-cp`参数，如下：
`$ javac -cp [第三方库的路径] [源码文件]`
编译生成的class文件是无法直接被`java`指令执行的，因为该class文件使用了第三方库，而这个库的位置并不在系统的环境变量之中，因此运行也需要显式地指定所需库的位置：
`$ java -Djava.ext.dirs=[第三方库所在的目录] [编译生成的class文件]`



##Swing开发注记
**Swing**是Java下的GUI开发库，Swing中的控件样式与平台无关，完全由Java绘制。

###常用控件
容器：
`JFrame`(窗体框架)
`JDialog`(对话框，比JFrame消耗资源少)
`JPanel`(面板)
`JScrollPane`(滚动面板)
`JFrame`一般做为顶层容器，可以独立做为对话框显示，但JPanel不能独立做为对话框。
文本组件：
`JLabel`(显示文本)
`JTextField`(单行编辑框)
`JPasswordField`(密码编辑框)
`JTextArea`(多行编辑区域)
表单组件：
`JButton`
`JCheckBox`(复选框，方框里打勾)
`JRadioButton和ButtonGroup`(单选框，圆点)
`JComboBox`(组合框，俗称下拉列表框)
菜单栏：
`JMenubar`(菜单栏)
`JMenu`(菜单栏上的按钮)
`JMenuItem`(点击菜单按钮弹出的菜单项)
常用的表单组件都有对应的菜单版本，比如`JRadioButtonMenuItem``JCheckBoxMenuItem`等。
向`JMenu`中`add()`菜单项时，虽然可以选择普通组件，但普通组件不能触发菜单效果(点按之后菜单不收回)。

###设置边框
一般的**GUI容器**类如`JFrame``JPanel`等都可以通过`setBorder()`方法来设置边框。
特别的，通过使用透明边框，可以实现控制界面边界空隙的效果(类似于**CSS**中的`Margin`属性)。
例如：

```java
//界面上下左右空出10个像素
setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
```

###利用Map的Key来作为ComoBox的下拉选项
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

###Java事件机制
Java的事件机制是通过**监听器**实现的。
要处理**GUI事件**，先要根据需求实现事件接口，比如点按事件的`ActionListener`，处理键盘的`KeyListener`，处理鼠标的`MouseListener`等等。
然后在要被监听的的GUI控件上调用对应的`addXXXListener()`方法将接口实例化的对象作为参数传入即可。

###在键盘事件中屏蔽指定按键
实现`KeyListener`接口，重写`keyTyped(KeyEvent)`方法，通过`getKeyChar()`方法获取输入的字符，然后对其进行判断，如果是想要屏蔽的按键则使用`setKeyChar('\0')`将其转化为空输入。
举例：(只接受数字输入)

```java
KeyEvent keyEvent = e -> {
	if ((e.getKeyChar() < '0' || e.getKeyChar() > '9'))
		e.setKeyChar('\0');
}
```

###文本输入监听器DocumentListener
包含三个方法：
`public void changedUpdate(DocumentEvent e)`监听文本属性的变化；
`public void insertUpdate(DocumentEvent e)`监听文本内容的插入事件；
`public void removeUpdate(DocumentEvent e)`监听文本内容的删除事件。
需要注意的是`JTextField`控件本身没有`addDocumentListener()`方法，需要先使用`getDocument()`方法获取`Document`对象才能调用`addDocumentListener()`。
在事件处理方法中，对JTextField对象调用getText()方法即可获得输入文本的内容。

###显示多行文本
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

###静态MessageBox方法
与**Qt**一样，Java也提供了弹出MessageBox的静态方法，即`JOptionPane.showMessageDialog()`。

```java
static void showMessageDialog(Component parentComponent, Object message) 									//调出标题为 "Message" 的信息消息对话框。
static void showMessageDialog(Component parentComponent, Object message, String title, int messageType) 				//调出对话框，它显示使用由 messageType 参数确定的默认图标的 message。
static void showMessageDialog(Component parentComponent, Object message, String title, int messageType, Icon icon) 						//调出一个显示信息的对话框，为其指定了所有参数。
```

其中，`messageType`可以取`DEFAULT_OPTION``YES_NO_OPTION``YES_NO_CANCEL_OPTION`或`OK_CANCEL_OPTION`等。
此外，还有`showInputDialog()``showConfirmDialog()`等方法可以用于显示其他用途的窗口。

###使用JTable显示数据库
构建一个`JTable`主要有两种方式：

```java
JTable(Object[][] rowData, Object[] columnNames)
JTable(TableModel dm)
```

即使用`Object数组`确定表格模型或是使用`TableModel`类构建表格模型。
使用对象数组构建表格模型可以先从数组库中读取对应数据，然后将数据存储在对象数组中。
使用`TableModel`类可以先构建`TableMode`对象，然后使用`TableMode`类的成员方法`setValueAt(Object aValue, int rowIndex, int columnIndex)`设定表格模型每个位置的数据，最后在JTable使用构造函数或在已有的`JTable`对象调用`setModel(TableModel dataModel)`成员方法创建表格。



##常见问题记录

###String.split()方法
函数的定义为：

```java
public String[] split(String regex)
```

`String`类中提供的文本切片函数`String.split()`接收的参数是**正则表达式**(Regex)。
因此，以一些**特殊符号**(`.``+`等)作为分隔符时，不能直接使用符号本身，而是需要使用转义符号，如以**小数点**作为分隔符切片需要写成：

```java
String[] nums = "123.456.789".split("\\.");
```
