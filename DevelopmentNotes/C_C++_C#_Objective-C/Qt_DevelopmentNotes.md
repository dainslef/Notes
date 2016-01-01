[TOC]

##Qt基础
`Qt`是一套基于`C++`的**跨平台**GUI开发库。

###Qt项目的构建
`Qt`并非使用标准C++，而在标准C++基础上添加了**信号槽**、**元对象系统**等机制，因而使用`Qt`的项目需要使用`qmake`工具对代码进行**预处理**。
进入项目代码所在的目录，执行命令：
`$ qmake -project		//根据Qt版本的不同，选择具体的构建工具，构建Qt4项目时使用qmake-qt4，Qt5项目为qmake-qt5`
`$ qmake [项目名称].pro	//项目名称一般为源码所在的文件夹的名称`
`$ make`
如果`make`时提示找不到对应的Qt库的头文件则需要在项目的`pro文件`中添加对应的内容，若提示GUI相关的头文件缺失，则添加`QT += widgets`，若数据库的头文件缺失，则添加`Qt += sql`。

###QtCreator常用快捷键
`Ctrl + Tab`切换正在编辑的代码文件
`F4`在配对的源码与头文件之前相互切换
`Ctrl + Shift + R`高亮显示当前光标所在的变量的所有使用情况，并可以批量修改
`Alt + 数字键`快速打开底栏的功能标签
`Ctrl + E > 2`打开横向分栏
`Ctrl + E > 3`打开竖向分栏
`Ctrl + /`注释/取消注释选定内容
`Ctrl + I`自动缩进选中代码
`Ctrl + Shift + UP`将当前行的代码向上移动一行
`Ctrl + Shift + DOWN`将当前行的代码向下移动一行

###Qt的常用控件
`QLineEdit`单行文本编辑框
`QTextEdit`多行文本编辑框
`QRadioButton`单选框
`QCheckButton`复选框
`QComboBox`组合框(下拉列表框)，使用`setMaxVisibleItems(int maxItems)`能设置同时显示的最大数目，但该选项在`gtk+/mac`风格下无效
`QToolBox`工具箱，可以用来实现抽屉效果
`QToolButton`工具箱按钮，有按下和弹起状态
`QListWdget`列表框，可以设置表格模式或图标模式，通过`setCurrentItem(nullptr)`清除当前选中的子目标

###在Qt中使用C++11
默认情况下，`Qt`是**没有**开启`C++11`支持的，让`Qt5`支持`C++11`需要在项目的`pro文件`中添加语句`CONFIG += c++11`，让`Qt4`支持`C++11`则需要在项目的`pro文件`中加入`QMAKE_CXXFLAGS += -std=c++11`。
添加`QMAKE_CXXFLAGS`参数的方法也使用于`Qt5`，只要编译器支持，还可以使用更新的`C++1y`。
添加`CONFIG`参数的方式只在`Qt5`中有效，且只能支持`C++11`。



##Qt的信号(signals)和槽(slots)机制
`Qt`中的信号和槽类似`C#`中的**委托事件**机制，是**观察者模式**的一种实现。只要信号一触发，与信号绑定的槽函数都会被调用。
`Qt`使用信号和槽传递消息，用户可以自行定义**信号**和**槽**，`Qt`对象中也包含了许多**预定义**的信号和槽。
一个类中如果需要声明信号和定义槽函数则需要从`QObject`类(或其子类)中继承，并在类的声明中加入宏`Q_OBJECT`。
`信号(signals)`只需要声明而不需要实现。使用`emit`关键字可以发送信号。信号的访问权限是`protected`且**不可更改**，也就是说**无法**在**该类**以及**该类子类**之外的区域发送信号，但信号的连接是随意的，可以在类外进行信号连接。
`槽(slots)`可以**自定义**访问权限，槽中的函数就像类的普通成员函数一样，除了函数声明之外需要有对应的函数实现。

###连接信号与槽
`Qt`中，使用`QObject`类中的静态函数`QObject::connect()`将信号与槽相连，`connect`的函数原型是`bool connect(sender, SIGNAL(signals()), receiver, SLOT(slots()))` ，其中`sender`和`receiver`分别表示信号发送者与信号接收者，可以传递**实例指针**或者**实例引用**作为参数。`SIGNAL()`中填写的是`sender`的信号函数，`SLOT()`中填写的是`receiver`的槽函数，信号的函数参数类型以及位置需要与槽函数一一对应，信号的参数目可以大于槽参数的数目，多余的参数会被**忽略**，此外参数只应该填写**参数类型**而不能画蛇添足的把参数名一起加上，这样会编译报错。使用`emit`关键字发送信号之后，传递给信号的参数值会按照对应位置传到槽中，然后槽函数执行。
多个信号与多个槽之间可以任意组合。
`connect`除了可以将信号和槽相连之外，还可以用于**连接信号**实现信号传递。
例如：
文件1 test.h

```cpp
#include <iostream>
#include <qt4/QtGui/QApplication>

class A : public QObject
{
	Q_OBJECT

signals:
	void send(int);
public slots:
	void get(int);
public:
	A(int);
	int set(int);
	int a;
};
```

文件2 test.cc

```cpp
#include <test.h>

A::A(int a) : a(a)
{
}

void A::get(int a)
{
	this->a = a;
}

int A::set(int a)
{
	emit send(a);		//发送信号send(int)，a的值作为参数传递到get(int)方法中
	return 0;
}

int main(int argc, char *argv[])
{
	A* a = new A(10);
	QObject::connect(a, SIGNAL(send(int)), a, SLOT(get(int)));		//用connect方法将实例指针a的send(int)信号与实例指针a的get(int)槽相连
	std::cout << a->a << std::endl;
	a->set(5);			//调用set(int)方法就会发送send(int)信号，使得get(int)槽函数调用，成员变量a的值发生改变
	std::cout << a->a << std::endl;
	return 0;
}
```

输出结果：
10
5

在实际应用中，需要注意，常见的槽功能(比如打开/关闭窗口之类的)，在`QWidget`之类的父类中已经为你实现了，继承父类自然就获得了这些槽函数，不用画蛇添足地自己重新实现功能类似的函数。

###`QObject::connect()`函数详解
`QObject::connect()`拥有多种重载：

```cpp
QMetaObject::Connection QObject::connect(const QObject* sender, const char* signal, const QObject* receiver, const char* method, Qt::ConnectionType type = Qt::AutoConnection);
```

这是Qt中最常用的信号槽连接方式，`sender`为信号发出者，`receiver`为信号接收者，`signal`为信号，`method`为槽函数。
使用此中形式的connect时，`signal`和`method`需要分别使用Qt提供的宏`SIGNAL()`和`SLOT()`。

```cpp
QMetaObject::Connection QObject::connect(const QObject* sender, const char* signal, const char* method, Qt::ConnectionType type = Qt::AutoConnection) const;
```

当connect连接的是**当前类**的槽函数时，可以省略接收者`receiver`。
即`connect(object, SIGNAL(signal()), SLOT(slot()))`相当于`connect(object, SIGNAL(signal()), this, SLOT(slot()))`。

```cpp
QMetaObject::Connection QObject::connect(const QObject* sender, PointerToMemberFunction signal, const QObject* receiver, PointerToMemberFunction method, Qt::ConnectionType type = Qt::AutoConnection);
```

connect函数同样支持使用成员指针形式的语法，`signal`和`method`可以使用成员指针的形式。
当一个信号有多个重载版本时，需要通过函数指针的强制类型转换来显式指明需要使用的重载版本。

```cpp
QMetaObject::Connection QObject::connect(const QObject* sender, PointerToMemberFunction signal, Functor functor)
```

在Qt5和C++11环境下，connect函数还可以直接连接到一个Lambda表达式上。

###异步信号
connect函数的最后一个参数枚举类型`Qt::ConnectionType`可以控制槽函数的回调方式。
无论使用哪种connect函数的重载，该参数都带有默认值`Qt::AutoConnection`。
使用`Qt::DirectConnection`方式连接slot时，槽函数会以**同步**的方式在**sender所处的线程**中执行。
使用`Qt::QueuedConnection`方式连接slot时，槽函数会以**异步**的方式在**receiver所处的线程**中执行，信号发出后，slot的执行请求会被加入事件队列，因而slot可能不会立即被执行。
使用`Qt::BlockingQueuedConnection	`方式连接slot时，槽函数的执行方式类似`Qt::QueuedConnection`，但sender所处的线程会阻塞，直到slot被执行完毕。
默认情况下，连接信号槽使用的是`Qt::AutoConnection`，使用连接方式时，若sender与receiver处于同一线程下，则使用`Qt::DirectConnection`模式，否则使用`Qt::QueuedConnection`模式。



##Qt事件机制
`事件(event)`是由系统或者Qt本身在不同的时刻发出的。当用户按下鼠标，敲下键盘，或者是窗口需要重新绘制的时候，都会发出一个相应的事件。一些事件是在对用户操作做出响应的时候发出，如键盘事件等；另一些事件则是由系统自动发出,如计时器事件。
`Qt`在`main`函数中要创建一个`QApplication`对象，在执行该对象的`exec()`函数时，就进入了事件的监听循环。每当事件发生时，Qt就会产生一个事件对象(所有的事件对象都继承于QEvent类)，然后将这个事件对象作为参数传递给QObject的event()函数，event()函数并不直接处理事件，而是将事件分类之后调用特定的事件处理函数，常见的事件处理函数有`mousePressEvent()``keyPressEvent()`等，想要自行处理事件就要重写对应的事件处理函数。

###注册自定义事件
除了系统产生的预定义事件外，可以自己使用`QEvent::registerEventType(int hint)`方法注册自定义事件，`hint`为事件序列号，`0~999`被系统占用，从`QEvent::User`(1000号)到`QEvent::MaxUser`(65535号)都是允许用户注册的值。事件类型为`QEvent::Type`，用`QEvent::registerEventType`注册时会返回整型的事件号，需要进行**强制类型转换**。

###产生一个事件
**发送**事件可以使用以下函数：

```cpp
void QCoreApplication::postEvent(QObject* receiver, QEvent* event);
bool QCoreApplication::sendEvent(QObject* receiver, QEvent* event);
void QCoreApplication::sendPostedEvents(QObject* receiver, int event_type);
bool QCoreApplication::notify(QObject* receiver, QEvent* event);
```

`postEvent()`函数将事件放入事件消息队列中，然后立即返回，函数只将事件放入队列的尾端，不保证事件立即得到处理。
`sendEent()`函数用`notify()`函数将事件直接派发给接收者和进行处理，返回事件处理者的返回值。事件会立即送至接受者，被发送后，Qt不会自动delete该事件，因此合适的做法是在栈上创建事件。
`sendPostedEvents()`函数将事件队列中用`postEvent()`函数放入的对应接受者和事件类型的事件立即分发，但是来自窗口系统的事件不被分发，它们被`processEvents()`函数分发。如果接受者是`null`，则对应所有的接受者；如果`event_type`为**0**，则对应`receiver`的所有的事件。该函数必须和`receiver`在同一个线程内被调用。

###处理事件
处理事件可以重写`QWidget::customEvent(QEvent*)`或`QWidget::event(QEvent*)` 函数，区别是前者**不需要**返回值，后者在处理完自定义事件之后需要继续返回对应控件的父类事件处理函数(`event()`是直接的事件处理函数)，返回事件循环的时候要注意当前类的继承关系，只返回最基本的循环`QObject::event()`则会有许多事件**不被处理**。
如果一个类的多个控件都需要相同的事件处理则可以重新实现`QObject::eventFilter(QObject *watched, QEvent *event)` 函数，然后在对应的控件对象上使用`QObject::installEventFilter(QObject *filterObj)` 函数安装过滤器，参数为要安装的过滤器所在的类指针。
在处理键盘事件时需要注意，如果已经接收了某个按键的事件同时进行操作，然后将事件继续返回事件队列时，如果这个键盘事件有系统默认的操作，则系统默认的操作依然会继续执行，则有可能与自己定义的操作产生冲突，正确的做法是对自己要处理的键盘事件返回`true`(这样系统定义的操作将不会触发，能够避免冲突)，只将不处理的键盘事件返回事件循环。

###事件机制与信号槽的区别
`Qt`中的事件是由窗口产生的，而信号槽机制还可用在命令行里，同时事件处理函数的返回值是有意义的，我们要根据这个返回值来确定是否还要继续事件的处理，但信号与槽绑定时并不关注返回值。事件通过事件队列来响应，如果事件的处理中又产生了新的事件，那么新的事件会加入到队列尾，直到当前事件处理完毕后， `QApplication`再去队列头取下一个事件来处理。而信号的处理方式有些不同，信号处理是**立即回调**的，也就是一个信号产生后，他上面所注册的所有槽都会**立即**被回调。



##Qt中的数据库连接
`Qt`中数据库连接主要是使用`QSqlDatabase`类，在使用这个类时需要注意，此类的构造函数是`protected`的，因此不能在类外使用，一般使用该类的静态成员函数`QSqlDatabase::addDatabase()`来创建`QSqlDataBase`对象。
在`Linux/Unix`系统中，连接本地数据库时`QSqlDatabase::setHostName()` 的参数因该填`localhost`，而不是环境变量中的`$hostname`。



##Qt中的表格
在`Qt`中，表格主要通过`QTableView`以及`QTableWidget`两类控件实现。
`QTableView`需要搭配**model**填充数据内容。
`QTableWidget`是`QTableView`的子类，相当于一个设定好了**model**的`QTableView`控件。

###使用QTableWidget
`QTableWidget`可以使用`QTableWidget::setColumnCount(int columns)/QTableWidget::setRowCount(int rows)`来设定表格的大小，使用`QTableWidget::setItem(int row, int column, QTableWidgetItem * item)`设定每一个单元格中的内容。
需要注意的是，默认情况下每一个单元格中的内容都是对象`QTableWidgetItem`，都需要使用`new`操作符构造对象与分配内存，因此，对于**数据量较大**的表格来说(几十w甚至上百w)，全部填充单元格的CPU、内存开销都是非常恐怖的。
`QTableWidget`中，每一个单元格的对象生命周期与整张表格相同，使用`setItem()`成员函数向原先有内容的单元格中设置新对象时原先的对象不会自动被销毁，一般使用`setItem()`之后不再替换该单元格上的对象，而是直接修改对象存储的内容。

####*向QTableWidget中添加控件*
`QTableWidget`还可以使用`QTableWidget::setCellWidget(int row, int column, QWidget * widget)`来向指定单元格中添加控件。
当使用了`setCellWidget()`添加控件之后，该单元格便不能使用`QTableWidget::item(int row, int column)` 方法来获取指定单元格的内容(会报空指针错误)，因为该单元格中没有`QTableWidgetItem`，正确的访问方式是使用`QTableWidget::cellWidget(int row, int column)`来获取指定单元格的**对象指针**。
需要注意的是，向表格直接使用`setCellWidget()`设置的控件是不受`setTextAlign()`影响的，会自动挤到单元格的一边，需要控件居中显示则需要新建`QWidget`并设置**Layout**作为容器，在向设置好布局的Widget中添加需要的控件，然后再将Widget设置到表格中。
例如：

```cpp
QWidget* widget = new QWidget(table);
QHBoxLayout* layout = new QHBoxLayout(widget);
layout->addWidget(new QCheckBox(widget));
widget->setLayout(layout);
table->setCellWidget(row, column, widget);
```

####*设置QTableWidget不可编辑*
使用`setEditTriggers(QAbstractItemView::NoEditTriggers)`可以将整个表格设为不可编辑。
需要注意的是，该不可编辑设置只对`QTableWidgetItem`有效，使用`setCellWidget()`方法设置的控件不会受到影响。

####*设置表格列自动扩展*
通过`QTableView::horizontalHeader()`方法可以获取整个表格的`QHeaderView`，然后使用其成员函数`setStretchLastSection(bool stretch)`，参数为`true`时则最后一栏的长度会自动扩展，也可以使用`setResizeMode(QHeaderView::Stretch)`来使所有列自动扩展。
例如：

```cpp
QTableWidget* table = new QTableWidget;
table->horizontalHeader()->setStretchLastSection(true);				//最后一行自动扩展
table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);		//所有行自动扩展
```

####*设置表格列自动适配宽度*
使用`QTableView::resizeColumnsToContents()`可以使**所有列**的列宽自动适配内容宽度。
使用`QTableView::resizeColumnToContents(int column)`设置**指定列**为自动适配内容宽度。

####*获取QTableWidget中发生变化的位置*
首先通过`QObject::sender()`获取信号的发出源对象，使用`dynamic_cast`宏转换为`QWidget`，再使用`QWidget::frameGeometry()`得到一个`QRect`型返回值表示该控件在其**parent窗口**中的位置，再通过`QTableView::indexAt(const QPoint &pos)`得到包含有单元格位置信息的`QModelIndex`返回值，使用`QModelIndex::row()/QModelIndex::column()`获取源对象的行列值。
举例：

```cpp
QTableWidget* table = new QTableWidget;
QModeIndex index = table->indexAt(dynamic_cast<QWidget*>(sender())->frameGeometry().center());
int row = index.row();
int column = index.column();
```

###使用QTableView
`QTableView`可以自由搭配不同的**model**，通过`QTableView::setModel(QAbstractItemModel* model)` 来设定使用的model，`QTableView`本身并不存放数据，数据保存在model中，可以通过`QAbstractItemView::model()` 来获取表格中已经组装的model，大量的变更数据可以直接`delete`旧的model，然后设定并组装新的model。

####*使用QSqlTableMode搭配QTableView实现数据库直接操作*
先创建出一个`QSqlTableMode`对象，如果已经有数据库连接且不需要从新的数据库中读取数据，则构造函数中的`QSqlDatabase`对象可以取默认值。
然后调用`QSqlTableMode::setTable()`设置要显示的表名，用`QSqlTableMode::setHeaderData()`设置每一列显示的数据。
在设置完`QSqlTableMode`之后，调用其成员函数`select()`将数据表格配置提交生效。
然后创建`QTableView`对象，使用其成员函数`setModel()`将先前建立的`QSqlTableMode`对象作为参数传入即可。
`QSqlTableMode`可以直接在表上进行修改操作，使用其成员函数`insertRow()`和`removeRow()`可分别实现**插入行**与**删除行**操作，需要注意的是，删除行时需要手动调用`select()`成员函数进行**提交**，否则被删除的行将依然占位置(虽然内容已被清除)。
在Qt中，数据库记录行数是从**0**开始计数的，而`QSqlTableMode`在显示数据库数据时，表格是从1开始计数的，使用`rowCount()`函数得到的返回值比表格上显示的行数**小**1。

####*刷新QTableView*
默认情况下，数据库的数据发生了变化，`QTableView`是不会**实时更新**的(model未发生变化)，需要调用`QSqlTableModel::select()`函数更新`QSqlTableMode`内的数据，然后`QTableView`才会将这些数据显示出来。



##Qt中的布局

###常用的布局样式
`QHBoxLayout`水平布局
`QVBoxLayout`垂直布局
`QGridLayout`表格布局
`QSpacerItem`**面板弹簧**，可以控制组件的对齐方式
`QStackedLayout`把子控件进行分组或者分页，一次只显示一组或者一页，隐藏其他组或者页上的控件
`QSplitter`分裂器，使用分裂器可以将两个控件(布局)绑定为一个整体，处于一个水平/垂直分裂器中的两个控件可以自由控制水平/垂直方向上分配的空间(自由分界)
布局之间可以相互嵌套，从而构成复杂的界面。
需要注意的是，Qt中的布局的构造函数中同样可以设定父窗口，但如果传入了父类窗口指针，则该布局会尝试成为该窗口的默认布局，但许多控件是拥有默认布局的，在运行时会发出警告。

###限制布局的大小
在Qt中，无法直接地限定一个布局的大小，如果需要一块布局限定在指定的大小下，比较简单的做法是将目标布局放入一个QWidget控件中，然后使用`QWidget::setFixedSize()`成员函数限定QWidget控件的大小即可。

###栅格化布局
在使用`QtCreator`设计UI时，默认情况下，界面元素的布局是不会随着窗口大小的变化而变化的，如果需要设计元素布局会随着窗口改变的界面，则需要使用栅格化布局。
栅格化布局本质上是将整个界面的布局设置为`QGirdLayout`，处于该布局内的窗口元素都会随着窗口大小的改变而变化其位置与间隔。



##使用qApp
`Qt`中如果包含了`QApplication`或`QCoreApplication`头文件，就可以使用全局变量`qApp`，该变量的作用是返回一个**当前实例**。

###qApp的宏定义
在`QApplication`中为`#define qApp (static_cast<QApplication*>(QCoreApplication::instance()))`
在`QCoreapplication`中为`#define qApp QCoreApplication::instance()`
在使用一些`静态槽函数`时，连接信号槽时就需要使用此变量，比如`QApplication::aboutQt()`。



##Qt的菜单构建

###构建主菜单
`Qt`中的菜单栏为`QMenuBar`，而显示在菜单栏上的一级选项为`QMenu`，而每个`QMenu`可以通过`QMenu::addAction(QAction*)` 来添加`QAction`作为菜单项。
一般来说，`Qt`应用程序都会包含一个继承于`QMainWindow`类的主窗口，主窗口通过`QMainWindow::setMenuBar(QMenuBar*)`方法来设定窗口的菜单栏。
而`QMenuBar`菜单栏通过`QMenuBar::addMenu(QMenu*)`方法添加`QMenu`作为一级菜单，`QMenu`也可以通过`QMenu::addMenu(QMenu*)`来添加二级菜单。
`QAction`除了添加在菜单中，还可以添加在`QToolBar`中。
`QAction`可以保持按下的状态，通过`QAction::setCheckable(bool)`设置为true时，按下QAction便不会自动弹起，需要再次点击才会弹起。
默认情况下，可以有**多个**`QAction`保持**按下**的状态，如果需要限定只能有一个`QAction`保持按下的状态，则可以将这些`QAction`加入**同一个**`QActionGroup`中。

###构建右键菜单
`QWidget`及其子类都可以通过重写虚函数`contextMenuEvent(QContextMenuEvent*)`来构建**右键菜单**。

```cpp
void QWidget::contextMenuEvent(QContextMenuEvent*)
{
	QMenu* contextMenu = new QMenu(this);
	contextMenu->addAction(new QAction("Test"));
	contextMenu->exec(cursor().pos());		//使用cursor()获取当前控件的QCursor鼠标对象，然后使用 QCursor::pos() 获得当前鼠标的位置，这样右键菜单便能在鼠标位置出现
}
```



##Qt鼠标监听

###鼠标点按事件
Qt中鼠标点按动作会触发下列事件：

```cpp
void QWidget::mousePressEvent(QMouseEvent* e);
void QWidget::mouseReleaseEvent(QMouseEvent* e);
```

**重写**这些事件处理函数即可。
对于鼠标事件`QMouseEvent`，可以使用`QMouseEvent::pos()`获取控件内坐标，和`QMouseEvent::globalPos()`获取全局坐标(显示器坐标)。

###鼠标移动事件
移动鼠标会触发下列事件：

```cpp
void QWidget::mouseMoveEvent(QMouseEvent* e);
void QWidget::leaveEvent(QEvent* event);
void QWidget::enterEvent(QEvent* event);
```

当鼠标移入控件时，会触发`enterEvent()`函数，当鼠标移出控件时会触发`leaveEvent()`，触发这些事件并**不需要**控件获得焦点，只需要鼠标进入/退出指定控件区域即会触发。
需要注意的是，默认情况下Qt只监听鼠标**按下之后**的动作，如果需要Qt监听所有鼠标动作需要使用函数`setMouseTracking(true);`



##自定义控件
Qt中的控件类一般在构造函数中都有一个`QWidget* parent = 0`的参数用来指定当前类的实例属于哪个**父窗口**(该参数默认为0，即没有父窗口)，当一个控件类实例的父窗口被关闭时，Qt会**自动析构**以此窗口为父窗口的所有控件类。
在给Qt控件定义父窗口时需要注意，布局控件`QLayout`在实例化时参数填写了父窗口则代表将这个实例化的布局应用到作为参数传入父窗口上，很多时候这样做是无效的，会提示父窗口已经拥有布局，因此在实例化布局控件是没必要指定父窗口。
当我们需要自定义自己的控件时，一般会根据需求继承于QWidget或其子类，在自定义控件类的构造函数中，建议也要添加一个参数用于设定父窗口，推荐如下方式在类内声明构造函数：

```cpp
MyWidget(QWidget* parent = 0);
```

类外定义写成：

```cpp
MyWidget::MyWidget(QWidget* parent) : QWidget(parent)
{
	/* 函数体 */
};
```

与标准C++不同的是，Qt类中的成员函数默认参数只能写在类体内部的函数声明中，在类外的函数实现中再给函数参数设定默认值同时在实例化时用省略默认值的形式调用函数会报错(但在标准C++中，成员函数的默认参数既可以写在类内的声明中，也可以写在类外的定义中)。

###获取子控件的指针
当一个窗体中包含了大量的子控件时，若要获取某个子控件的指针，不必将该控件做为成员变量写入类定义中，
Qt提供了以下方式来获取子控件的指针：

```cpp
template<typename T> T QObject::findChild (const QString& name = QString()) const;		//通过ObjectName来获取需要的控件指针
template<typename T>  QList<T> QObject::findChildren(const QRegExp& regExp) const;		//通过正则表达式来获取子控件指针
const QObjectList& QObject::children() const;											//直接返回所有子控件
```

前两种方法需要知道控件的**类型**，最后一种不需要，但得到的是`QObject`类型。
借助Qt的**元对象系统**，可以获取`QObject`类的**真实类型信息**，如可使用以下方式获取类名：

```cpp
QString class_name = obj->metaObject()->className();
```



##Qt中的窗口

###在Qt中新建窗口
Qt中一般新建一个窗口都采取在**堆**中分配内存的方式(使用`new`操作符来创建一个指向该块内存的指针)，在`main`函数中，也可已尝试不使用指针直接在栈中创建对象，但是，在其他函数中，是不能这样做的，因为一个函数结束，则该函数的**栈**就会被**销毁**，而对象如果实在栈中创建则会随着函数的结束而被删除。
新建窗口的构造函数一般有两种，`show()`默认只会创建一个普通的新窗口，用户可以在新窗口和旧窗口之间切换焦点，而`exec()`则会创建一个模态窗口，在新创建的模态窗口被关闭前，你不能将焦点切换回父窗口。
`show()`通过设置参数也可以创建模态窗口，但`exec()`只能创建模态窗口。
`show()`创建窗口之后程序会**继续执行**后面的代码，但使用`exec()`创建模态窗口则会**阻塞线程**，直到模态对话框收到`accept()``reject()`等操作才会继续执行代码。

###窗口内存回收
一般情况下，通过指定`QWidget*`的父窗口指针，当父窗口被析构时，当前窗口的内存也被释放。
如果不指定父窗口，则可使用创建栈变量的形式，出栈时变量自动释放：

```cpp
QWidget w;
w.exec();
```

还可以通过设置窗口的`Qt::WA_DeleteOnClose`属性来让窗口关闭时自动释放内存：

```cpp
QWidget* w = new QWidget;
w->setAttribute(Qt::WA_DeleteOnClose, true);
w->show();
```

需要注意的是，设置了`Qt::WA_DeleteOnClose`属性则不能将窗口类以**栈变量**的形式创建，因为栈变量在出栈时还会被析构一次，造成**重复析构**。

###Qt中的预设窗口
对于一些**功能简单**的交互对话框，我们不必要一一自己实现，在Qt中提供了许多预设好的简单对话框(均为**静态成员函数**，可直接使用)。
如获取用户输入可以使用`QDialog`子类的成员函数：

```cpp
QString QInputDialog::getText(...);				//用于获取字符串
int QInputDialog::getInt(...);					//用于获取整型数值
QColor QColorDialog::getColor(...);				//用于提供色彩选择对话框
QFont QFontDialog::getFont(...);				//用于提供文字选择对话框
QString QFileDialog::getOpenFileName(...);		//用于获取选择的文件路径(文件原先存在)
QString QFileDialog::getSaveFileName(...);		//用于获取创建的文件路径(文件原先不存在)
QString QFileDialog::getExistingDirectory(...);	//用于获取指定目录的路径
```

提示用户和获取用户判断的对话框为`QMessageBox`：

```cpp
StandardButton QMessageBox::question(...);		//询问用户的判断
StandardButton QMessageBox::information(...);	//提示用户普通信息
StandardButton QMessageBox::warning(...);		//提示用户警告信息
StandardButton QMessageBox::critical(...);		//提示用户危险信息
```

###Qt中窗口按钮、边框设置
通过使用`void setWindowFlags(Qt::WindowFlags type);`函数可以设置窗口的边框样式以及窗口上具有的按钮。
默认情况下，可以使用Qt预设的窗口边框样式，在枚举类型`enum Qt::WindowType`中，常用的有`Qt::Widget``Qt::Window``Qt::Dialog`等样式。
如果预设的窗口样式不能满足需求，则可以使用`Qt::CustomizeWindowHint`搭配自定义按钮组成需要的样式，例如，创建一个仅带有空的标题栏的窗口可以使用代码：

```cpp
setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
```

###窗口大小的设置
一般而言设置Qt的窗口大小可以使用下列函数：

```cpp
void QWidget::setGeometry(int x, int y, int w, int h);
void QWidget::resize(int w, int h);
```

前者在设置大小的同时还能设置窗口在屏幕的显示位置，后者用于重新设定窗口大小。
当窗口采用栅格化布局的时候，使用以上两个函数在设定大小时很可能不会生效，此时可以使用`QWidget::setFixedSize(const QSize &)`来设定固定的窗口大小，这个大小能够覆盖布局定义的大小而强制生效，如果只需要设定宽或是高可以单独使用`QWidget::setFixedWidth(int w)`或是`QWidget::setFixedHeight(int h)`。
窗口设置了固定的大小如果需要再改动，可以将宏`QWIDGETSIZE_MAX`作为参数传入`QWidget::setFixedSize(const QSize&)`函数中，窗口就会重新变成可调大小。
使用`QWidget::sizeHint()`函数可以获取Qt判断的窗口**最合适**大小。



##文本与字符串处理
在Qt中使用`QString`做为基本的字符串类。

###字符串转换
Qt基于`C++`语言，与`Java``C#`不同，没有**自动装箱**和**拆箱**机制，在`Java`中，可以直接将数字与字符串简单得用加号相连并保持数字的语义转化为新的字符串，但在C++中，数字是不能直接与字符串相加的，需要借助标准库中的函数进行转换才能与字符串相加。
在Qt中，默认字符串与数字用加号拼接然后转换为`QString`类型时，数字会被当作`ASC码`对待，要使数字保持语义转化为字符串则需要使用`QString::number(int/double/long)`函数进行转换。
`QString`可以通过`QString::toStdString()`来得到传统风格的`C++`字符串类型`std::string`，而`std::string`可以通过`std::string::c_str()`函数转换为c风格的`char*`字符数组指针。
`QString`可以使用静态方法`QString::fromStdString(const std::string &str)`来直接将`std::string`转换为`QString`。
对于可能出现的字符串乱码问题，可以使用静态方法`QString QString::fromLocal8Bit(const char* str, int size = -1)`来构建`QString`。

###格式化文本
`QString`类提供了多样的**格式化文本**功能，类C风格的格式化可以使用其成员函数`QString::sprintf(const char *cformat, ...)`进行。
需要注意的是，Qt本身并不推荐使用`QString::sprintf()`来进行文本格式化，`QString::sprintf()`在`Qt5.5`中已经被标记为`Obsolete(废弃的)`，可能会在未来版本中移除该函数。
Qt风格的文本格式化应使用`QString::arg(const QString& a, int fieldWidth = 0, QChar fillChar = QLatin1Char(' '))`来进行。

###QLabel多行显示文本
在默认情况下，`QLabel`控件只会**单行**显示文本，一旦文本内容超过了`QLabel`控件的`Width`，就无法显示。
如果需要在指定宽度下完整显示文本，就需要将`QLabel`设置为允许多行显示。使用`setWordWrap(true)`方法设置`QLabel`的允许多行显示。

###限制QLineEdit的输入内容
很多时候，需要对用户输入的内容加以限制，对于简单的限制，可以使用`QLineEdit::setValidator(const QValidator* v)`限制输入内容。

####*限制只能输入整数*

```cpp
QLineEdit* lineEdit = new QLineEdit();
lineEdit->setValidator(new QIntValidator(0, 1000, this));				//限制输入0~1000的数值
```

####*限制只能输入小数*

```cpp
QLineEdit* lineEdit = new QLineEdit();
lineEdit->setValidator(new QDoubleValidator(0.0, 1000.0, 2, this));		//限制输入0.0~1000.0的数值，最大保留小数点后两位
```

####*复杂的输入限制*
对于复杂的输入限制，可以使用正则表达式校验器`QRegExpValidator`。

```cpp
QLineEdit* lineEdit = new QLineEdit();
lineEdit->setValidator(new QRegExpValidator(QRegExp("正则表达式内容")), this);
```



##使用QListWidget
`QListWidget`是一个自带了**model**的`QListView`实现，使用`QListWidget`可以方便的构建列表框。
`QListWdget`的索引号从**0**开始。

###使用IconMode
`QListWdget`默认以列表的模式显示，但`QListWidget`实现了`QListView`中的`setViewModel()`方法，支持**图标模式**。
使用方法`QListWidget::setViewMode(ViewMode mode)`，参数为`QListView::IconMode`即可将`QListWidget`设置为图标模式。
使用方法`QListWidget::setMovement(Movement movement)`可以设置图标的移动模式，参数为`QListView::Static`时图标不可移动。

###使QListWidgetItem能被勾选
`QListWidgetItem`使用`void QListWidgetItem::setCheckState(Qt::CheckState state)`来设置勾选状态，使用此成员方法则item前会出现类似`QCheckBox`样式的复选框。
当`state`参数取值`Qt::Checked`为勾选状态，`Qt::Unchecked`为非勾选状态。

###使用QListWidgetItem保存数据
`QListWidget`中的每一个列表项都是一个`QListWidgetItem`对象，对于`QListWidgetItem`，常用的方法有：

```cpp
void QListWidgetItem::setText(const QString& text);						//设置列表项/图标模式下的显示文字
void QListWidgetItem::setData(int role, const QVariant& value);			//设置item保存的数据内容
```

需要注意的是`setData()`成员函数中的第一个参数为保存数据的角色`Qt::ItemDataRole`，该值从0~14之间的为Qt自身使用的Role，比如item默认的文本数据就保存在0角色中，即在role为0时，`setText()`和`setData()`只有**一个**能生效(后调用的那个会把先前的数据覆盖)。
提供给用户使用的Role从`Qt::UserRole`开始，`Qt::UserRole`之后的数值都可以由用户使用。

###使QListWidgetItem对齐
如果给`QListWidgetItem`设定了文本，那么，在文本长度不一致的时候，图标很可能不会保持对齐状态，此时可以使用`QListWidgetItem::setSizeHint(const QSize &size)`来强制设定每个item的大小，使每个item大小完全相同，达到对齐的效果(过长的文本会以省略号显示)。

###查找指定名称的QListWidgetItem
可以使用`QList<QListWidgetItem*> QListWidget::findItems(const QString& text, Qt::MatchFlags flags) const`来查找指定文本内容的`QListWidgetItem`。
其中，可以通过设定`flags`来设定一些简单的匹配规则，常用的匹配规则有：
`Qt::MatchStartsWith`查找名称最前部分匹配text的item
`Qt::MatchEndsWith`查找名称最后部分匹配text的item
`Qt::MatchContains`查找名称包含text的item
`Qt::MatchFixedString`查找完全匹配text的item，默认情况下是忽略大小写的，通过设置`Qt::MatchCaseSensitive`可设置匹配为大小写敏感



##使用QTreeWidget
`QTreeWidget`是`QTreeView`的自带model实现。`QTreeWidget`不仅可以用于展示**树状列表**，也可以一定程度上代替`QTable`来**构建表格**。

###添加行
`QTreeWidget`中每一行都是一个`QTreeWidgetItem`对象，在构建`QTreeWidgetItem`时传入`QTreeWidget`指针即会将该item自动添加到该树形控件中。
可以使用以下方法来对`QTreeWidgetItem`进行设置：

```cpp
void QTreeWidgetItem::setText(int column, const QString& text);						//设置指定列的文本内容
void QTreeWidgetItem::setCheckState(int column, Qt::CheckState state);				//设置指定列的勾选状态，使用该方法后指定列会处于可勾选状态
void QTreeWidgetItem::setData(int column, int role, const QVariant& value);			//item的每一列都可以用来保存数据
void QTreeWidgetItem::setFlags(Qt::ItemFlags flags);								//设置标志，可用来控制item的一些行为。比如：是否可用(Qt::ItemIsEnabled)、是否可编辑(Qt::ItemIsEditable)、是否可选中(Qt::ItemIsSelectable)、是否可由用户点选(Qt::ItemIsUserCheckable)等。
```

每一个`QTreeWidgetItem`还可以添加其它`QTreeWidgetItem`，从而形成**树状**。

###设置列宽
使用`QTreeView::resizeColumnToContents(int column) [slot]`可以设置指定列的**列宽自适应**。
`QTreeWidget`的表头为一个`QHeaderView`对象，更细节的列宽分配可通过`QHeaderView`类的相关方法来进行设置。
`QTreeWidget`实现了`QHeaderView* QTreeView::header()`方法，因此通过`header()`方法可以直接获得`QHeaderView`对象指针。
使用以下方法对`QTreeWidget`进行列宽设置：

```cpp
void QHeaderView::setStretchLastSection(bool stretch);								//设置最后一列自动扩展
void QHeaderView::setSectionResizeMode(int logicalIndex, ResizeMode mode);			//设置指定列的列宽扩展模式，有固定大小(Fixed)、扩展列宽到合适大小(Stretch)、根据内容宽度决定列宽(ResizeToContents)等
```

###其它常用设置

```cpp
void QHeaderView::setSortIndicatorShown(bool show);									//使QTreeWidget的头标签支持点按排序
void QTreeWidgetItem::setBackgroundColor(int column, const QBrush& brush);			//填充指定列的背景色
void QHeaderView::setDefaultSectionSize(int size);									//设置默认列宽
void QHeaderView::setMinimumSectionSize(int size);									//设置最小列宽
```

###遍历QTreeWidgetItem
使用`QTreeWidgetItem`的迭代器对象`QTreeWidgetItemIterator`即可进行`QTreeWidget`的遍历

```cpp
for (QTreeWidgetItemIterator it(QTreeWidget*); *it; ++it)
{
	/* do something... */
}
```

`QTreeWidgetItemIterator`可以分别以`QTreeWidget`指针或是`QTreeWidgetItem`指针进行构建，用来遍历不同层次的目录树。



##图片的显示以及图片存储入数据库的操作

###在QLabel控件中显示图片
首先得到要打开的图片的路径：

```cpp
QString url = QFileDialog::getOpenFileName(this);
```

创建一个QLabel控件：

```cpp
QLabel* label = new QLabel(this);
```

用前面得到的路径变量url创建一个`QPixmap`控件：

```cpp
QPixmap pixmap(url);
```

通过`QPixmap::setPixmap()`函数设定`QLabel`的`QPixmap`控件来让`QLabel`显示图片：

```cpp
label->setPixmap(pixmap);
```

如果图片大小不匹配，可以通过`QPixmap::sacled()`函数改变图片的显示比例：

```cpp
QPixmap QPixmap::scaled(int width, int height);
```

需要注意的是该函数返回的是`QPixmap`类型，变更了大小的新的`QPixmap`在**返回值**中，需要显式的赋值给一个`QPixmap`对象。

###在QComobox/QListWidget中显示图片
使用`QComboBox::addItem(const QIcon &icon, const QString &text, const QVariant &userData = QVariant())`向一个组合框添加选项内容时，将需要在组合框中显示的图片转换成`QIcon`类型，填入第一个参数即可。
需要注意的是，`QComboBox`在显示图片是是有自身默认的大小的，无论原图片的大小如何，都会被缩放成`QComboBox`中指定的大小。
指定`QComboBox`中显示图片的大小需要使用`QComboBox::setIconSize(const QSize &size)`来显式指定。
对于`QListWidget`，操作方式类似，控制显示图片的大小同样需要使用`QListWidget::setIconSize(const QSize &size)`来显式指定。

###向数据库中写入图片
首先通过得到的文件路径用`QFile`打开文件：

```cpp
QFile file(url);
```

然后将得到的文件对象设置`OpenMode`(对于上传图片到数据库的操作，只需要只读属性)，未设置此属性会造成无权限读取文件：

```cpp
file.open(QIODevice::ReadOnly);
```

将打开的文件对象转化为**二进制**数据：

```cpp
QByteArray byte = file.readAll();
```
将得到的二进制数用`QVariant`封装：

```cpp
QVariant var(byte);
```

然后使用`QSqlQuery`对象执行插入语句将var插入数据库(不能使用exec()语句直接插入，因为`QVariant`与`QString`不能直接相连)：

```cpp
sql.prepare("inesrt into [表名] (列名) values(?)");
sql.addBindValue(var);
sql.exec();
```

###从数据库中读取图片
首先使用`QSqlQuery`对象执行`exec()`查询语句，然后将智能指针**下移**一个位置:

```cpp
sql.exec("查询语句");
sql.next();
```

将`QSqlQuery`对象中的数据转化为二进制数据：

```cpp
QByteArray byte = sql.value(0).toByteArray();
```

将得到的二进制数据传入`QPixmap`对象：

```cpp
QPixmap map;
map.loadFromData(byte);
```

最后将`QPixmap`对象绑定到`QLabel`控件上：

```cpp
QLabel* label = new QLabel;
label->setPixmap(map);
```



##Qt绘图系统
`Qt`的**绘图系统**包括`QPainter``QPaintDevice``QPaintEngine`三个类。
`QPainter`用于执行绘图的操作，`QPaintDevice`则是一个二维空间的抽象，给`QPainter`提供绘制图形的空间，而`QPaintEngine`通常对于开发人员透明，用于`QPainter`和`QPaintDevice`之间的**通讯**。
`QPaintDevice`相当于画板，`QPainter`相当于画笔，`QPaintDevice`有多种子类如`QPixmap``QImage`等。

###paintEvent()
一般而言，自行绘制图形可以自定义一个类继承于`QWidget`，然后重写`QWidget::paintEvent(QPiantEvent*)`事件处理函数，将绘制图形的操作放在`paintEvent()`事件处理函数中。
在`Qt4`之后，绘图操作可以不必放在`paintEvent()`事件处理函数中运行，但对于从`QWidget`继承过来的类而言，必须将绘制操作放在`paintEvent()`中，可以封装一个类用于管理paint操作，然后将该类放在`paintEvent()`中实例化。
`paintEvent()`是一个会被频繁触发的事件，每次窗口有刷新行为都会触发该事件函数进行重绘。
`paintEvent()`事件函数也可以被手动触发，`QWidget`的子类使用`repaint()``update()`成员函数就能主动触发重绘事件。

###QPainter
`QPainter`相当于画笔，用于控制线的**样式**、**颜色**、**粗细**等。
使用`QPainter`绘制图像时，需要在构建`QPainter`实例时传入需要绘制的设备的地址作为参数或者使用`begin()`成员函数来确定绘制设备，比如`QPainter painter(this);`就是实例化了一个绘制**当前控件**的`QPainter`。
一个`painter`只能同时绘制一个设备(一支笔不能同时在两张纸上写字)，当可以在绘制设备之间进行切换，从一个绘制设备切换到另一个绘制设备之前需要使用`end()`成员函数结束上一个被绘制的设备，然后将下一个可绘制设备的地址传入`begin()`成员函数进行绘制。
`QPainter`不仅能用于绘制图像，还可以用于绘制**文字**(使用`drawText()`方法)。
`QPainter`使用`QPainter::setPen(const QPen& pen)`可以设置画笔的样式(线形、色彩等)。
`QPainter`使用`QPainter::setFont(const QFont& font)`可以设置文本的字体。

###QPixmap
使用默认的构造函数(无参构造函数)构造`QPixmap`时，会产生一个**空的**`QPixmap`对象，空的`QPixmap`对象是**不能**传入`QPainter`进行绘制操作的(运行时提示`QPainter::begin: Paint device returned engine == 0, type: 2`)，需要重载的`赋值操作符/load()`等成员函数加载数据之后才能绘制，也可以使用带有初始大小的`QPixmap(const QSize& size)``QPixmap(int width, int height)`等构造函数创建一个**初始非空**的`QPixmap`对象。
相比直接在控件上进行绘制，使用`QPixmap`最大的不同是像`QPixmap`中绘制的数据是可以被保存下来的，而直接在控件上绘制则每次刷新会丢失先前绘制的内容。
`QPixmap`可以使用`QImage QPixmap::toImage() const`转换为`QImage`。

###QImage
与`QPixmap`类似，使用无参构造函数创建的`QImage`同样是空的，没有分配内存不能直接用于`QPainter`绘制，使用`QPainter`绘制需要使用有参构造函数构建**非空**的`QImage`对象。
相比`QPixmap`，`QImage`支持进行**像素级别**的操作，`QPixmap`的实现依赖于硬件，`QImage`不依赖于硬件，`QPixmap`主要用于绘图,针对屏幕显示而最佳化设计，`QImage`主要是为图像I/O、图片访问和像素修改而设计。

###图片透明化
使用`QImage`处理图片时可以通过设置图片的**Alpha通道**使图片透明化。
简单的透明处理可以使用`QImage::setAlphaChannel(const QImage& alphaChannel)`以另一个`QImage`对象作为参数使图片透明化。
如果需要手动指定透明度(Alpha值)，则可以创建一个带有Alpha通道的`QImage`对象，如`QImage temp_image(win_size, QImage::Format_ARGB32);`
使用设置了透明画刷的`QPainter`对其进行色彩填充，然后将此`QImage`作为`QImage::setAlphaChannel()`成员函数的参数。
例如：

```cpp
int alpha = 100;								//定义alpha透明度
QImage temp_image(100, 100);					//创建空白QImage
QPainter painter(&image);
painter.fillRect(0, 0, 100, 100, QColor(alpha, alpha, alpha, alpha));		//填充色彩
image.setAlphaChannel(temp_image);				//以temp_image为样本设置原图像的alpha通道
```



##Qt处理命令行参数
`Qt5.2`之后提供了类`QCommandLineParser`以及`QCommandLineOption`来进行命令行参数的处理。

###获取命令行输入
Qt中不需要传递`argc`和`**argv`，可以通过静态方法`QStringList QCoreApplication::arguments()`在任意位置获取到用户输入的命令行参数。

###解析命令行参数
`QCommandLineOption`用于表示某一个具体的命令参数，`QCommandLineParser`用于添加用`QCommandLineOption`类表示的命令行参数。
构造`QCommandLineOption`对象时传入一个`QString`做为参数的名称，通过`QCommandLineOption::setDefaultValue(const QString& defaultValue)`设置参数的默认值。
`QCommandLineParser`使用`QCommandLineParser::addOption(const QCommandLineOption& option)`添加`QCommandLineOption`命令行参数类。
通过使用`bool QCommandLineParser::isSet(const QCommandLineOption& option)/isSet(const QString& name)`判断命令行中是否带有指定参数。

###获取系统环境变量
使用`QStringList QProcess::systemEnvironment()`可以获取系统所有的环境变量。
将得到的`QStringList`使用`startsWith("xxx=")`即可获取以xxx为名称的环境变量的值。



##Qt窗口截图
一般使用`QWidget`的静态成员函数进行截图：

```cpp
QPixmap grabWidget(QObject* widget, int x = 0, int y = 0, int w = -1, int h = -1);
```

也可以使用`QScreen`对象进行截图操作。

```cpp
QScreen* screen = QGuiApplication::primaryScreen();
QPixmap view = screen->grabWindow(winId(), 0, 0, size().width(), size().height());
```



##Qt网页浏览
Qt提供了基于`WebKit`引擎的`QWebKit`做为**网页解析引擎**。网页浏览功能可以使用`QWebView`控件。
使用`QWebView`控件需要添加`QWebKit`库(该库默认没有被引用)。

###加载页面
使用`QWebView::load(const QUrl& url)`将连接地址做为参数可以让`QWebView`载入一个页面。
需要注意的是，连接地址需要符合`URL`(统一资源定位符)的规范，格式应写成`协议://路径1/路径2/路径xxx?参数1=参数值1&参数2=参数值2&参数xxx=参数值xxx`。
常见的协议有：`http`(超文本传输协议资源)`https`(用安全套接字层传送的超文本传输协议)`ftp`(文件传输协议)`file`(本地电脑或互联网分享文件)。

###响应页面点击事件
在`QWebView`中展示的页面点击链接可以发出信号`QWebView::linkClicked(const QUrl& url)`，捕获该信号进行处理即可。
需要注意的是，默认情况下，点击链接并不会自动发送该信号，需要使用`QWebView::page()`获取当前页面，然后再使用`void QWebPage::setLinkDelegationPolicy(LinkDelegationPolicy policy)`将获取页面的链接代理设置为`QWebPage::DelegateExternalLinks/QWebPage::DelegateAllLinks`时才会触发连接信号。



##Qt字体设置
通过使用`QFontDataBase`对象可以获取当前系统的字体数据。
通过使用`QFontMetrics`对象可以获取指定样式字体的宽度、高度。

###打印出当前系统支持的字体

```cpp
foreach (const QString& font_name, QFontDatabase().families())
	std::cout << font_name <<std::endl;
```

其中，`QStringList QFontDatabase::families(WritingSystem writingSystem = Any) const`函数的参数可以用于指定文字类型，例如，列出简体中文的字体可以写成：

```cpp
foreach (const QString& font_name, QFontDatabase().families(QFontDatabase::SimplifiedChinese))
	std::cout << font_name <<std::endl;
```

###获取文本的宽高
`QFontMetrics`类的构造函数可以使用`QFont`做为参数。
使用`int QFontMetrics::width(const QString& text, int len = -1) const`可以获取指定文本的宽度。

```cpp
QFont font("times", 24);
QFontMetrics fm(font);
int pixelsWide = fm.width("What's the width of this text?");
int pixelsHigh = fm.height();
```



##Qt文件操作
Qt中的文件和目录相关类主要为`QFile`和`QFileInfo`以及`QDir`。
其中，`QFile`用于文件操作，而`QFileInfo`用于获取文件信息，`QDir`用于过滤文件。

###QFile
`QFile`类定义了一系列的静态成员函数，提供了常见的文件操作：

```cpp
bool QFile::copy(const QString& fileName, const QString& newName);		//复制文件
bool QFile::exists(const QString& fileName);							//判断文件是否存在
bool QFile::open(OpenMode mode);										//检测文件的读写状态
bool QFile::remove(const QString& fileName);							//删除文件
bool QFile::rename(const QString& oldName, const QString& newName);		//重命名文件
bool QFile::link(const QString& fileName, const QString& linkName);		//创建文件快捷方式，在Unix系统下为创建符号链接
```

###QFileInfo
`QFileInfo`类提供了一系列获取文件信息的方法：

```cpp
QString QFileInfo::absoluteFilePath() const;							//获取文件的绝对路径(包含文件名)
QString QFileInfo::absolutePath() const;								//获取文件的路径(不含文件名)
QString QFileInfo::baseName() const;									//获取文件的不含后缀的文件名(以第一个"."符号为界)
QString QFileInfo::completeBaseName() const;							//获取文件的不含最后一个后缀的文件名(以最后一个"."符号为界)
QString QFileInfo::fileName() const;									//获取文件的完整文件名(不含路径)
```

###QDir
`QDir`类能够按指定规则在路径下筛选出符合要求的文件，常用的方法有：

```cpp
QFileInfoList QDir::entryInfoList(const QStringList& nameFilters, Filters filters = NoFilter, SortFlags sort = NoSort) const;
QStringList QDir::entryList(const QStringList& nameFilters, Filters filters = NoFilter, SortFlags sort = NoSort) const;
QFileInfoList QDir::entryInfoList(Filters filters = NoFilter, SortFlags sort = NoSort) const;
QStringList QDir::entryList(Filters filters = NoFilter, SortFlags sort = NoSort) const;
```

其中过滤规则`Filters`是一个枚举类，定义了一些的过滤条件，如`QDir::Readable`表示文件可读，`QDir::Writable`表示文件可写。
当不添加任何参数时，方法返回的是路径下的**所有文件**。



##Qt国际化
对Qt工程进行国际化首先需要在项目中创建`ts`翻译文件，并对需要翻译的文本使用`QObject::tr()`方法进行标记。
`ts`翻译文件本质上是一个**XML文档**，记录了源码中被标记的文本与翻译文本之间的对应关系。
`ts`翻译文件可以被编译成`qm`格式的二进制翻译文件，用于被程序加载。

###动态切换程序语言
使用`QTranslator`类可以实现程序语言的动态切换。
通过`QTranslator::load()`的重载方法加载`qm`文件：

```cpp
bool QTranslator::load(const QString& filename, const QString& directory = QString(), const QString& search_delimiters = QString(), const QString& suffix = QString());
bool QTranslator::load(const QLocale& locale, const QString& filename, const QString& prefix = QString(), const QString& directory = QString(), const QString& suffix = QString());
```

最后使用`bool QCoreApplication::installTranslator(QTranslator* translationFile)`方法将加载好`qm`文件的`QTranslator`对象做为参数传入，界面语言便会立即变化。
需要注意的是，需要保证加载的`QTranslator`对象不被销毁，翻译才能正常显示，否则界面又会变回默认的语言。



##Qt常见错误

###关于 _undefined reference to vtable for XXX(类名)_ 错误
在一个类的定义中，如果使用类`Q_OBJECT`宏，则需要将对应的代码使用`moc`工具进行预处理生成`*.moc`文件才能够正常编译，而`qmake`工具在扫描代码中的`Q_OBJECT`时只会从`*.h`命名的文件中查找，如果在编码过程中没有按照编码规范而是将类的定义写在`*.cpp/*.cc`文件中的话，`qmake`工具是不会识别的，生成对应的`Makefile`文件也不会将对应的`*.moc`文件加入编译使得make指令编译报错。
正确的做法是按照C++标准将类的定义写在`*.h`头文件中。
此外，Qt在编译项目时默认采用的是`make`编译，会在编译时忽略那些未曾改动的文件，因此有时出现此错误时还可以尝试完全删除已经存在的二进制文件和编译中间文件，然后从头开始重新编译整个项目。
一般对于此类错误的解决办法是手动运行`qmake`后整个项目重新编译。

###关于 _Warning: File '***' has modification time 3.9e+08 s in the future_ 错误
一般情况下，Qt在`make`项目时连续出现类似错误(并且呈现出死循环状态)，一般是项目中的文件时间混乱，部分文件的时间超过了系统当前的时间造成的。
解决办法是将项目里的所有文件`touch`一遍即可。
此外，make出现`make: 警告：检测到时钟错误。您的创建可能是不完整的。`的错误提示一般也是类似原因造成的。

###关于 _qt error: C2001: 常量中有换行符_ 错误
在`Windows`环境中使用`Qt`+`VC编译器`并且源码为`utf-8`编码时，需要保留`BOM`，使用**无BOM的utf-8编码**会让编译器在遇到中文字符时报编码错误，需要将文件编码的`UTF-8 BOM`选项设置为`如果编码是utf-8则添加`。

###关于 _底层受到操作系统信号而停止_ 错误
通常情况下，遇到此类问题可能是对空指针进行了操作。
在Qt中，需要注意指针是否已经被初始化，同时，在编写类的析构函数时也许要慎重，如果一个指针需要传递给其他类使用，则不能在当前类的析构函数中`delete`此指针。

###关于 _Z-order assignment: '***' is not a valid widget._ 警告
在使用`QtDesigner`拖放控件顺序不当时可能会出现此警告，解决方法是删除对应控件的`<zorder></zorder>`标签。

###关于Windows专属BUG：中文乱码
在Windows系统下，使用VS开发Qt程序时，即使代码文件的编码设置为`UTF-8`，并且通过`QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));`显式设定编码为`UTF-8`，依然会出现中文乱码的问题。
对于少量的中文内容，可以使用`QString::fromLocal8bit(const char*);`函数让中文内容正常显示。
对于大量的中文内容，每次出现中文都使用QString的成员函数转换非常麻烦，可以使用如下宏解决中文编码问题：

```cpp
#pragma execution_character_set("utf-8")
```

需要注意的是，该宏需要特定版本的VS支持，对于`VS2010`，需要安装`VS2010SP1`更新。VS2012不支持该宏，VS2013支持。

###关于 _This application failed to start because it could not find or load the Qt platform plugin "windows"._ 运行错误
在使用非安装版本的Qt或是系统中未安装Qt时启动Qt程序可能会遇到此错误提示，原因是未能加载Qt的运行时动态链接库。
需要将Qt安装目录下的`...\plugins\platforms`文件夹复制到需要执行的程序所在的目录。
需要注意的是，直接将`platforms`文件夹中的dll复制出来是没有效果的。

###关于 _找不到Qt5Core.dll_ 运行错误
在已经安装了Qt的机器上出现此错误，一般为Qt的**环境变量**未正确配置。
需要创建环境变量`QTDIR`，绑定的位置为Qt的主要目录(即包含有bin、include、lib等目录的路径)。
需要将`%QTDIR%\bin`加入`PATH`环境变量中。
