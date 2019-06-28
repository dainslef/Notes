<!-- TOC -->

- [Swing 簡介](#swing-簡介)
	- [Scala Swing](#scala-swing)
- [常用控件](#常用控件)
	- [代碼風格](#代碼風格)
- [Border](#border)
	- [設置邊框](#設置邊框)
	- [BorderFactory](#borderfactory)
- [JTextArea](#jtextarea)
- [MessageBox](#messagebox)
- [事件機制](#事件機制)
	- [Java Swing 事件機制](#java-swing-事件機制)
	- [Scala Swing 事件機制](#scala-swing-事件機制)
- [MVC](#mvc)
	- [ComboBox](#combobox)
	- [JTable](#jtable)

<!-- /TOC -->



# Swing 簡介
`Swing`是`Java`平臺下的傳統`GUI`庫。
Swing是Java標準庫的一部分，包含於`Java SE`中。

與上代圖形技術`AWT`的比較：

- `AWT`使用各平臺原生控件，在各平臺上的原生控件上做了基礎的封裝。
- `Swing`控件完全由`Java`繪製。
- `AWT`控件因平臺而異，相同控件在各`OS`中表現不盡相同。
- `Swing`控件在各`OS`下具有統一的外觀樣式與功能。
- `AWT`使用原生控件，執行效率高。
- `Swing`使用自繪控件，執行效率低下(在現代版本的`Java`中已有較大改善)。

## Scala Swing
Scala標準庫中提供了`Java Swing`對應的`Scala API`封裝：`Scala Swing`。

在sbt項目中添加Scala Swing依賴：

```scala
libraryDependencies += "org.scala-lang.modules" %% "scala-swing" % "版本號"
```



# 常用控件
Java Swing提供的控件位於`javax.swing`包路徑下，命名均以字母`J`起始。

Scala Swing對`Java Swing`提供的多數控件進行了淺層的封裝，使之更符合Scala的API風格。
Scala Swing控件位於`scala.swing`路徑下，名稱爲對應的Java Swing控件去掉首字母`J`。

容器類控件：

| Java Swing 控件名稱 | Scala Swing 控件名稱 | 控件簡介 |
| :- | :- | :- |
| JFrame | Frame | 頂層窗體控件 |
| JDialog | Dialog | 對話框窗體 |
| JPanel | Panel | 面板 |
| JScrollPane | ScrollPane | 滾動面板 |

`JFrame/Frame`一般做爲頂層容器，可以獨立做爲對話框顯示，但`JPanel/Panel`不能獨立做爲對話框。

文本控件：

| Java Swing 控件名稱 | Scala Swing 控件名稱 | 控件簡介 |
| :- | :- | :- |
| JLabel | Label | 文本標籤 |
| JTextField | TextField | 單行文本框 |
| JTextArea | TextArea | 多行文本框 |
| JPasswordField | PasswordField | 密碼文本框(可設定回顯字符) |

按鈕控件：

| Java Swing 控件名稱 | Scala Swing 控件名稱 | 控件簡介 |
| :- | :- | :- |
| JButton | Button | 普通按鈕 |
| JCheckBox | CheckBox | 複選框 |
| JRadioButton | RadioButton | 單選框 |
| JComboBox | ComboBox | 組合框(下拉列表框) |

多個`JRadioButton/RadioButton`需要添加到同一個`ButtonGroup`中才能實現**單選**效果。

菜單欄：

| Java Swing 控件名稱 | Scala Swing 控件名稱 | 控件簡介 |
| :- | :- | :- |
| JMenubar | Menubar | 菜單欄 |
| JMenu | Menu | 菜單欄上的按鈕 |
| JMenuItem | MenuItem | 點擊菜單按鈕彈出的菜單項 |

常用的表單組件都有對應的菜單版本，比如`JRadioButtonMenuItem`、`JCheckBoxMenuItem`等。
向`JMenu`中`add()`菜單項時，雖然可以選擇普通組件，但普通組件不能觸發菜單效果(點按之後菜單不收回)。

## 代碼風格
在Java Swing中，常見的創建控件、配置控件的方式爲先構建對象實例，之後調用實例的成員方法設置控件屬性。

使用Java Swing創建窗口，在窗口中添加控件：

```java
JFrame frame = new JFrame();
JLabel label = new JLabel();

label.setText("Test");
label.setMinimumSize(new Dimension(80, 40));

frame.add(label);
frame.setSize(new Dimension(200, 100));
frame.setVisible(true);
```

在Scala Swing中，創建控件、配置控件通常同步進行，使用**匿名類**特性，在創建控件時直接在構造方法中設定控件的各類屬性。

Scala Swing的API更貼近Scala的語言風格。
使用Scala Swing構建配置控件語法更加類似DSL，可讀性更高。

上述Java Swing例子使用Scala Swing代碼如下：

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
`javax.swing.border.Border`類型定義了邊框的接口。

## 設置邊框
常見**GUI容器**類如`JFrame`、`JPanel`等都可以通過`setBorder()`方法來設置邊框：

```java
public void setBorder(Border border);
```

## BorderFactory
工廠類`BorderFactory`提供了一系列創建各類常見樣式邊框的靜態方法。

- `EmptyBorder`

	EmptyBorder爲僅佔據面板空間的透明邊框。
	通過使用EmptyBorder，可以實現控制控件邊界空隙的效果(類似於**CSS**中的`Margin`屬性)。

	創建EmptyBorder的靜態方法：

	```java
	// 創建默認樣式的 EmptyBorder
	public static Border createEmptyBorder();
	// 創建指定邊距的 EmptyBorder
	public static Border createEmptyBorder(int top, int left, int bottom, int right);
	```

- `TitledBorder`

	TitledBorder爲框線上帶有標題的邊框。
	Swing中並未提供默認的`GroupBox`控件，但可以對JPanel等控件設定TitledBorder來實現類似效果。

	創建TitledBorder的靜態方法：

	```java
	public static TitledBorder createTitledBorder(Border border, String title,
			int titleJustification, int titlePosition, Font titleFont, Color titleColor);
	```



# JTextArea
`JTextField`僅適用於顯示簡單的**單行文本**，涉及到**多行文本**時，應使用`JTextArea`控件：

```java
JTextArea textArea = new JTextArea();
```

可以設置文本域**自動換行**：

```java
textArea.setLineWrap(true);
```

當文本域內容太多無法全部顯示時，可以使用`JScrollPane`控件，將文本域添加到其中：

```java
JScrollPane scrollPane = new JScrollPane(textArea);
```

當文本無法全部顯示時會出現**滾動條**。



# MessageBox
與`Qt`類似，Swing也提供了彈出`MessageBox`的靜態方法，即`JOptionPane.showMessageDialog()`。

```java
// 調出標題爲"Message"的信息消息對話框
static void showMessageDialog(Component parentComponent, Object message);
// 調出對話框，顯示使用由messageType參數確定的默認圖標的message
static void showMessageDialog(Component parentComponent,
		Object message, String title, int messageType);
// 調出一個顯示信息的對話框，指定了所有參數
static void showMessageDialog(Component parentComponent,
		Object message, String title, int messageType, Icon icon);
```

- `parentComponent`參數爲父對話框。
- `messageType`參數控制對話框的內置按鈕，可取值`DEFAULT_OPTION`、`YES_NO_OPTION`等。
- `message`參數爲在對話框中顯示的消息內容。

使用`showInputDialog()`、`showConfirmDialog()`等方法可以用於顯示其他用途的窗口，參數類似。



# 事件機制
Java**沒有**類似C#的語言級別事件機制。

Java Swing的事件機制採用`Observer`模式。
Scala Swing在事件處理上採用了`Reactor`模式，與Java Swing風格不同。

## Java Swing 事件機制
Java Swing的事件機制主要包括以下部分：

1. 監聽器，包含對事件的處理邏輯：

	所有的的監聽源都實現了`java.util.EventListener`接口。
	`EventListener`接口是空接口，`Java Swing`根據不同的事件類型定義了一系列繼承於`EventListener`的子接口。

	不同的監聽器接口定義了不同的抽象方法，當對應的監聽事件觸發時，對應方法會被調用。
	通過重寫監聽器接口的抽象方法來實現事件處理邏輯。

1. 事件源，即觸發事件的控件：

	事件源是某個具體的控件對象。
	控件對象通過綁定監聽器對象在事件觸發時調用對應監聽器對象的重寫方法。

	Java Swing中的控件都提供了命名類似的方法用於與監聽器交互：

	```java
	// 綁定到指定監聽器實例
	public synchronized void addXxxListener(XxxListener listener);
	// 移除到指定監聽器實例的綁定
	public synchronized void removeXxxListener(XxxListener listener);
	// 獲取當前控件已綁定的所有監聽器實例
	public synchronized XxxListener[] getXxxListeners();
	```

	不同的控件類型根據其控件職能會擁有不同類型監聽器的交互方法。

1. 事件，包含特定的事件信息：

	所有的事件都繼承自`java.util.EventObject`。

	事件保存了具體的某一次事件發生時的事件信息。
	事件做爲監聽器抽象方法的參數，當事件觸發時，對應的事件信息做爲參數傳入。

	以按鈕控件的`ActionEvent`爲例，實現ActionEvent的處理需要以下步驟：

	1. 構建ActionEvent監聽器，監聽器實現`ActionListener`接口，重寫抽象方法`actionPerformed()`。
	1. 按鈕控件對象調用`addActionListener()`方法，將控件綁定監聽器。

	如下代碼所示：

	```java
	// 構建監聽器，ActionListener只有單個抽象方法，爲函數式接口
	ActionListener action = e -> ...;

	JButton button = new JButton();

	// 將控件綁定監聽器
	button.addActionListener(action);
	```

常見監聽器類型應用：

1. `KeyListener` (鍵盤按鍵監聽器)

	通過鍵盤監聽器可屏蔽指定按鍵輸入。

	實現KeyListener接口，重寫`keyTyped()`方法。
	對`KeyEvent`類型的事件參數調用`getKeyChar()`方法獲取輸入的字符，判斷輸入內容。
	對需要屏蔽的輸入使用`setKeyChar('\0')`轉化爲空輸入。

	如下所示：(只接受數字輸入)

	```java
	KeyListener keyListener = e -> {
		if (e.getKeyChar() < '0' || e.getKeyChar() > '9') e.setKeyChar('\0');
	}
	```

## Scala Swing 事件機制
Scala Swing中，事件採用集中式處理，所有被監聽的控件發出的各類事件會被彙總統一處理。

Scala Swing所有控件的基類`scala.swing.UIElement`都間接混入了事件發佈者特質`scala.swing.Publisher`：

```scala
trait UIElement extends Proxy with LazyPublisher {
  ...
}

private[swing] trait LazyPublisher extends Publisher {
  ...
}
```

`Publisher`特質繼承於反應器特質`scala.swing.Reactor`，該特質定義了用於發佈事件的`publish()`方法：

```scala
trait Publisher extends Reactor {
  ...
  def publish(e: Event) { ... }
  ...
}
```

`Reactor`特質定義了與訂閱者的交互方法，使用`listenTo()`添加訂閱者，`deafTo()`移除訂閱者。
`Reactor`特質定義了字段`reactions`，類型爲`scala.swing.Reactions`：

```scala
trait Reactor {
  ...
  val reactions: Reactions = ...
  def listenTo(ps: Publisher*) = ...
  def deafTo(ps: Publisher*) = ...
  ...
}
```

`Reactions`爲抽象類，繼承於自身單例對象中定義的類型別名`Reactions.Reaction`(實際類型爲偏函數`PartialFunction[Event, Unit]`)。
`Reactions`抽象類定義了用於增減偏函數的方法`+-()`、`-=()`：

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

向`reactions`字段添加自定義的事件處理偏函數來處理UI事件。
reactions字段添加的偏函數參數爲`scala.swing.event.Event`，返回值類型爲`Unit`。

`Event`特質是所有Scala Swing事件類型的基類。
事件類型與Java Swing中類似，但使用了Scala的樣例類特性，便於在事件處理偏函數中使用。

以`ActionEvent`爲例，在Scala Swing中實現ActionEvent事件的處理：

```scala
val button = new Button

// 監聽控件
listenTo(button)

// 偏函數添加 ActionEvent 事件處理邏輯
reactions += {
  case ActionEvent(source) => ...
}
```



# MVC
Swing中的組件採用了`MVC`的設計模式，對於`JList`、`JComboBox`、`JTable`等控件均可通過組裝Model構建對象並顯示內容。

## ComboBox
獲取目標Map的`Key`集合：

```java
Set set = map.keySet();
```

接着將集合轉化爲對象數組：

```java
Object[] object = set.toArray();
```

接着構造一個用對象數組初始化的`DefaultComboBoxModel`對象，並以此構建`JComoBox`對象：

```java
JComboBox comboBox = new JComboBox(new DefaultComboBoxModel(object));
```

## JTable
構建一個`JTable`主要有兩種方式：

```java
JTable(Object[][] rowData, Object[] columnNames);
JTable(TableModel dm);
```

即使用`Object數組`確定表格模型或是使用`TableModel`類構建表格模型。
使用對象數組構建表格模型可以先從數組庫中讀取對應數據，然後將數據存儲在對象數組中。

使用TableModel的基本步驟：

1. 構建TableMode對象。
1. 使用TableMode類的成員方法`setValueAt(Object aValue, int rowIndex, int columnIndex)`設定表格模型每個位置的數據。
1. 使用JTable構造函數或在已有的JTable實例調用`setModel(TableModel dataModel)`成員方法創建表格。
