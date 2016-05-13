[TOC]

## *PyQt* 简介
`PyQt`为`Qt`库提供了`Python`语言的接口，使用`PyQt`能够快速地完成GUI程序的开发。

本笔记基于`Python3`和`PyQt5`。

### 安装 *PyQt*
在`Linux`、`OS X`等Unix环境下，安装`PyQt`直接使用`pip`包管理器即可，无需额外的配置：

`$ pip install pyqt5`



## 信号槽机制
信号`signals`和槽`slots`机制是`Qt`的基础。

在`PyQt`中，信号槽的接口风格与传统的`C++ Qt`略有不同。

### 连接信号槽
信号使用`connect()`方法与槽函数或是其它信号相连。

与`C++ Qt`中的静态成员函数`QObject::connect()`不同，`PyQt5`中的`connect()`函数是作为`class pyqtBoundSignal(builtins.object)`类型的**成员函数**存在的，其接口风格类似于`C#`中的`event`以及`C++`中的`boost::signals`。

函数定义如下：

```py
connect(slot, type = Qt.AutoConnection, no_receiver_check = False)
```

与`C++`不同，Python中的成员函数、全局函数无需额外修饰即可直接作为槽函数与信号连接。

### 自定义信号
使用`class pyqtSignal(builtins.object)`来定义信号：

```py
pyqtSignal(*types, name: str = ..., revision: int = ..., arguments: Sequence = ...)
```

自定义信号需要作为**类成员**定义在类中才能正常连接槽函数，**不能**作为**实例成员**定义在类中。

如下所示：

```py
class TestSignal(QObject):

	signalIntStr = pyqtSignal(int, str)		# 正确，信号作为类成员定义

	def __init__(self):
		self.signalInt = pyqtSignal(int) 	# 错误，信号作为实例成员定义
```

### 自定义信号实例
信号连接各类槽函数的演示如下：

```py
from PyQt5.QtCore import QObject, pyqtSignal


class TestSignals(QObject):
	signalIntStr = pyqtSignal(int, str)		# 定义一个首参数为int，第二参数为str类型的信号

	def __init__(self, parent = None):
		super().__init__(parent = parent)
		self.signalIntStr.connect(self.instanceSlot)		# 信号连接到类的实例成员函数

	def instanceSlot(self, num, strings):					# 被信号连接的槽函数本身并未经过特殊修饰
		print("Call instanceSlot, num: %d, strings: %s" % (num, strings))


class Slot:
	@staticmethod
	def staticSlot(num, strings):
		print("Call staticSlot, num: %d, strings: %s" % (num, strings))


def globalSlot(num, strings):
	print("Call globalSlot, num: %d, strings: %s" % (num, strings))


testSignals = TestSignals()

testSignals.signalIntStr.connect(globalSlot)				# 信号连接到全局函数
testSignals.signalIntStr.connect(Slot.staticSlot)			# 信号连接到静态成员函数

testSignals.signalIntStr.emit(666, "TestSignals")			# 触发信号
```

输出结果：(Python 3.5.1 && PyQt 5.6)

```
Call instanceSlot, num: 666, strings: TestSignals
Call globalSlot, num: 666, strings: TestSignals
Call staticSlot, num: 666, strings: TestSignals
```



## 使用 *QtDesigner* 构建UI
与传统的`C++ Qt`开发相同，使用`PyQt`开发同样可以使用`QtDesigner`进行拖放式的快速UI布局。
之后，使用Qt提供的`User Interface Compiler`将拖放的到的UI文件编译称对应的编程语言代码。

在`PyQt`开发中，使用`pyuic`工具将`QtDesigner`得到的UI文件编译成对应的Python代码：

`$ pyuic5 [source_name].ui -o [code_name].py`

其步骤类似于`C++ Qt`开发中使用`uic`将UI文件编译成对应C++代码的过程。

### 调用UI文件生成的源码
与`C++ Qt`开发类似，`User Interface Compiler`会根据窗口类的名称生成对应的`Ui_xxx`类，引用生成的代码大致分为以下几个步骤：

0. 在自己的窗口类中实例化`Ui_xxx`类。
0. 通过`Ui_xxx`类的实例调用其实例成员方法`setupUi()`，将当前窗口类的`self`引用作为第二个参数传入。

之后，当前的窗口类便会使用UI文件中定义的布局。

与`C++ Qt`开发类似，使用`PyQt`开发时，如果需要使用`QObject`内存回收机制，则需要重定义构造函数，为构造函数添加`parent`参数，并显式调用父类构造函数，将`parent`参数传入其中。

### 简单实例：使用 *QSqlTableModel* 组装 *QTableView* 浏览 *MaraiDB* 数据库
在`MariaDB`数据库中创建创建如下结构的表：

```sql
CREATE TABLE `TestData` (
	`Name` varchar(50) NOT NULL,
	`Password` int(11) NOT NULL,
	`ID` int(11) NOT NULL AUTO_INCREMENT,
	UNIQUE KEY `TestData_ID_uindex` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
```

使用`QtCreator`创建如下的UI文件：

```xml
<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
	<class>sqlBrwoser</class>
	<widget class="QWidget" name="sqlBrwoser">
		<property name="geometry">
			<rect>
				<x>0</x>
				<y>0</y>
				<width>666</width>
				<height>506</height>
			</rect>
		</property>
		<property name="windowTitle">
			<string>SqlBrowser</string>
		</property>
		<layout class="QGridLayout" name="gridLayout">
			<item row="0" column="0">
				<widget class="QTableView" name="tableView"/>
			</item>
			<item row="1" column="0">
				<widget class="QPushButton" name="pushButton">
					<property name="text">
						<string>Close</string>
					</property>
				</widget>
			</item>
		</layout>
	</widget>
	<resources/>
	<connections/>
</ui>
```

使用`pyuic`工具为其生成`Python`代码模块`ui.py`：

```py
# file_name: ui.py

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_sqlBrwoser(object):
	def setupUi(self, sqlBrwoser):
		sqlBrwoser.setObjectName("sqlBrwoser")
		sqlBrwoser.resize(666, 506)
		self.gridLayout = QtWidgets.QGridLayout(sqlBrwoser)
		self.gridLayout.setObjectName("gridLayout")
		self.tableView = QtWidgets.QTableView(sqlBrwoser)
		self.tableView.setObjectName("tableView")
		self.gridLayout.addWidget(self.tableView, 0, 0, 1, 1)
		self.pushButton = QtWidgets.QPushButton(sqlBrwoser)
		self.pushButton.setObjectName("pushButton")
		self.gridLayout.addWidget(self.pushButton, 1, 0, 1, 1)

		self.retranslateUi(sqlBrwoser)
		QtCore.QMetaObject.connectSlotsByName(sqlBrwoser)

	def retranslateUi(self, sqlBrwoser):
		_translate = QtCore.QCoreApplication.translate
		sqlBrwoser.setWindowTitle(_translate("sqlBrwoser", "SqlBrowser"))
		self.pushButton.setText(_translate("sqlBrwoser", "Close"))
```

编写主模块`main.py`：

```py
# file_name: main.py

from PyQt5.QtWidgets import QWidget, QApplication, QMessageBox
from PyQt5.QtSql import QSqlTableModel, QSqlDatabase
from PyQt5.QtCore import Qt

from ui import Ui_sqlBrwoser

class Dialog(QWidget):


	def __init__(self, parent = None):

		# 将父窗口对象传给父类的parent
		super().__init__(parent = parent)

		# 创建父类的ui对象
		self.ui = Ui_sqlBrwoser()
		self.ui.setupUi(self)

		self.initSql()

		# 为关闭按钮连接槽函数
		self.ui.pushButton.clicked.connect(self.showDialog)


	def initSql(self):

		db = QSqlDatabase.addDatabase("QMYSQL")		# 创建指定驱动类型的数据库对象
		db.setHostName("localhost")					# 设置数据库地址
		db.setDatabaseName("Test")					# 设置使用数据库的名称

		# 不要忘记open()数据库，否则无法获得数据，参数为用户名和密码，若已调用成员函数设置用了户名密码，则参数可不填
		db.open("dainslef", "015")

		# 创建并组装数据库的model
		self.mode = QSqlTableModel(self, db)		# 可以显式指定数据库，不指定则默认使用当前打开的数据库
		self.mode.setTable("TestData")				# 设置表名
		self.mode.setHeaderData(0, Qt.Vertical, "Name")
		self.mode.setHeaderData(1, Qt.Vertical, "Password")
		self.mode.setHeaderData(2, Qt.Vertical, "ID")
		self.mode.select()							# 显式提交model，刷新表中数据

		self.ui.tableView.setModel(self.mode)


	def showDialog(self):
		if QMessageBox.question(self, "Question", "Do you want to close the window?") \
				== QMessageBox.Yes:
			self.close()


import sys

app = QApplication(sys.argv)
dialog = Dialog()
dialog.show()
app.exec_()
```