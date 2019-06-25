<!-- TOC -->

- [Qt 基礎](#qt-基礎)
	- [項目構建](#項目構建)
	- [QtCreator 常用快捷鍵](#qtcreator-常用快捷鍵)
	- [常用控件](#常用控件)
	- [在 Qt 中使用 C++11](#在-qt-中使用-c11)
- [基礎控件](#基礎控件)
- [Signal (信號) 和 Slot (槽)](#signal-信號-和-slot-槽)
	- [連接信號槽](#連接信號槽)
	- [QObject::connect()](#qobjectconnect)
	- [異步信號](#異步信號)
- [事件機制](#事件機制)
	- [註冊自定義事件](#註冊自定義事件)
	- [產生事件](#產生事件)
	- [處理事件](#處理事件)
	- [事件機制與信號槽的區別](#事件機制與信號槽的區別)
- [數據庫連接](#數據庫連接)
- [表格](#表格)
	- [QTableWidget](#qtablewidget)
	- [QTableView](#qtableview)
- [佈局](#佈局)
	- [常用的佈局樣式](#常用的佈局樣式)
	- [限制佈局的大小](#限制佈局的大小)
	- [柵格化佈局](#柵格化佈局)
- [qApp](#qapp)
	- [菜單構建](#菜單構建)
	- [構建主菜單](#構建主菜單)
	- [構建右鍵菜單](#構建右鍵菜單)
- [鼠標監聽](#鼠標監聽)
	- [鼠標點按事件](#鼠標點按事件)
	- [鼠標移動事件](#鼠標移動事件)
- [自定義控件](#自定義控件)
	- [獲取子控件的指針](#獲取子控件的指針)
- [窗口](#窗口)
	- [新建窗口](#新建窗口)
	- [窗口內存回收](#窗口內存回收)
	- [預設窗口](#預設窗口)
	- [窗口按鈕、邊框設置](#窗口按鈕邊框設置)
	- [窗口大小的設置](#窗口大小的設置)
- [文本與字符串處理](#文本與字符串處理)
	- [字符串轉換](#字符串轉換)
	- [格式化文本](#格式化文本)
	- [QLabel 多行顯示文本](#qlabel-多行顯示文本)
	- [限制 QLineEdit 輸入內容](#限制-qlineedit-輸入內容)
- [QListWidget](#qlistwidget)
	- [QListView::IconMode](#qlistviewiconmode)
	- [使 QListWidgetItem 能被勾選](#使-qlistwidgetitem-能被勾選)
	- [用 QListWidgetItem 保存數據](#用-qlistwidgetitem-保存數據)
	- [對齊 QListWidgetItem](#對齊-qlistwidgetitem)
	- [查找 QListWidgetItem](#查找-qlistwidgetitem)
- [QTreeWidget](#qtreewidget)
	- [添加行](#添加行)
	- [設置列寬自動擴展](#設置列寬自動擴展)
	- [清空、刪除、移除節點](#清空刪除移除節點)
	- [其它常用設置](#其它常用設置)
	- [遍歷 QTreeWidgetItem](#遍歷-qtreewidgetitem)
- [圖片顯示/圖片存儲](#圖片顯示圖片存儲)
	- [在 QLabel 中顯示圖片](#在-qlabel-中顯示圖片)
	- [在 QComobox/QListWidget 中顯示圖片](#在-qcomoboxqlistwidget-中顯示圖片)
	- [向數據庫中寫入圖片](#向數據庫中寫入圖片)
	- [從數據庫中讀取圖片](#從數據庫中讀取圖片)
	- [繪圖系統](#繪圖系統)
	- [paintEvent()](#paintevent)
	- [QPainter](#qpainter)
	- [QPixmap](#qpixmap)
	- [QImage](#qimage)
	- [圖片透明化](#圖片透明化)
- [處理命令行參數](#處理命令行參數)
	- [獲取命令行輸入](#獲取命令行輸入)
	- [解析命令行參數](#解析命令行參數)
	- [獲取系統環境變量](#獲取系統環境變量)
- [窗口截圖](#窗口截圖)
- [QWebKit](#qwebkit)
	- [加載頁面](#加載頁面)
	- [響應頁面點擊事件](#響應頁面點擊事件)
- [字體設置](#字體設置)
	- [打印出當前系統支持的字體](#打印出當前系統支持的字體)
	- [獲取文本的寬高](#獲取文本的寬高)
- [文件操作](#文件操作)
	- [QFile](#qfile)
	- [QFileInfo](#qfileinfo)
	- [QDir](#qdir)
- [國際化](#國際化)
	- [動態切換程序語言](#動態切換程序語言)
- [常見錯誤](#常見錯誤)
	- [關於 `undefined reference to vtable for XXX(類名)` 錯誤](#關於-undefined-reference-to-vtable-for-xxx類名-錯誤)
	- [關於 `Warning: File XXX has modification time 3.9e+08 s in the future` 警告](#關於-warning-file-xxx-has-modification-time-39e08-s-in-the-future-警告)
	- [關於 `qt error: C2001: 常量中有換行符` 錯誤](#關於-qt-error-c2001-常量中有換行符-錯誤)
	- [關於 `底層受到操作系統信號而停止` 錯誤](#關於-底層受到操作系統信號而停止-錯誤)
	- [關於 `Z-order assignment: XXX is not a valid widget.` 警告](#關於-z-order-assignment-xxx-is-not-a-valid-widget-警告)
	- [關於Windows專屬BUG：中文亂碼](#關於windows專屬bug中文亂碼)
	- [關於 `This application failed to start because it could not find or load the Qt platform plugin "windows".` 運行錯誤](#關於-this-application-failed-to-start-because-it-could-not-find-or-load-the-qt-platform-plugin-windows-運行錯誤)
	- [關於 `找不到Qt5Core.dll` 運行錯誤](#關於-找不到qt5coredll-運行錯誤)
	- [關於 `Cannot start the terminal emulator "xterm", change the setting in the Environment options.` 運行錯誤](#關於-cannot-start-the-terminal-emulator-xterm-change-the-setting-in-the-environment-options-運行錯誤)

<!-- /TOC -->



# Qt 基礎
`Qt`是一套基於`C++`的**跨平臺**GUI開發庫。

## 項目構建
Qt並非使用標準C++，而在標準C++基礎上添加了**信號槽**、**元對象系統**等機制，
Qt項目需要使用`qmake`工具對代碼進行**預處理**。

在Qt項目的根路徑下，執行命令：

```c
$ qmake -project //根據Qt版本的不同，選擇具體的構建工具，構建Qt4項目時使用qmake-qt4，Qt5項目爲qmake-qt5
$ qmake [項目名稱].pro //項目名稱一般爲源碼所在的文件夾的名稱
$ make
```

若執行make時提示找不到對應的Qt庫的頭文件，則需要在項目`pro文件`中添加對應的內容：

- 提示GUI相關的頭文件缺失，則添加`QT += widgets`。
- 數據庫的頭文件缺失，則添加`Qt += sql`。

## QtCreator 常用快捷鍵
- `Ctrl + Tab` 切換正在編輯的代碼文件
- `F4` 在配對的源碼與頭文件之前相互切換
- `Ctrl + Shift + R` 高亮顯示當前光標所在的變量的所有使用情況，並可以批量修改
- `Alt + 數字鍵` 快速打開底欄的功能標籤
- `Ctrl + E > 2` 打開橫向分欄
- `Ctrl + E > 3` 打開豎向分欄
- `Ctrl + /` 註釋/取消註釋選定內容
- `Ctrl + I` 自動縮進選中代碼
- `Ctrl + Shift + UP` 將當前行的代碼向上移動一行
- `Ctrl + Shift + DOWN` 將當前行的代碼向下移動一行

## 常用控件
Qt中的控件均繼承自`QWidget`：

- `QLineEdit` 單行文本編輯框
- `QTextEdit` 多行文本編輯框
- `QRadioButton` 單選框
- `QCheckBox` 複選框
- `QComboBox` 組合框(下拉列表框)，使用`setMaxVisibleItems(int maxItems)`能設置同時顯示的最大數目，但該選項在`gtk+/mac`風格下無效
- `QToolBox` 工具箱，可以用來實現抽屜效果
- `QToolButton` 工具箱按鈕，有按下和彈起狀態
- `QListWdget` 列表框，可以設置表格模式或圖標模式，通過`setCurrentItem(nullptr)`清除當前選中的子目標
- `QDateEdit` 日期選擇器
- `QTimeEdit` 時間選擇器

## 在 Qt 中使用 C++11
Qt**沒有**默認開啓`C++11`支持。

讓`Qt5`支持`C++11`需要在項目`pro文件`中添加語句`CONFIG += c++11`。<br>
讓`Qt4`支持`C++11`需要在項目`pro文件`中添加語句`QMAKE_CXXFLAGS += -std=c++11`。

添加`QMAKE_CXXFLAGS`參數的方法也使用於`Qt5`，只要編譯器支持，還可以使用更新的`C++14`、`C++17`。<br>
添加`CONFIG`參數的方式只在`Qt5`中有效，且只能支持`C++11`。



# 基礎控件
Qt中，常見的UI類的的繼承關係爲：

```
QObject +  QPaintDevice => QWidget
QWidget => QFrame, QMainWindow, QDialog
QObject + QSurface => QWindow
QWindow + QPaintDevice => QPaintDeviceWindow
```

- `QWindow`是對底層窗口系統的抽象，與宿主OS相關，開發中*不應該*直接使用此類。
- `QWidget`是所有UI控件的基類，是最基本的UI對象。
- `QFrame`定義了控件的邊框樣式，從`QFrame`繼承的控件可以定義邊框樣式(`QFrame::setFrameStyle(int style)`)。
- `QMainWindow`提供了程序主窗口的框架，可對其設置**Menu Bar、Tool Bars、Dock Widgets、Central Widget、Status Bars**等區域，快速構建出程序的主窗口。
- `QDilog`定義了基本的對話框樣式。



# Signal (信號) 和 Slot (槽)
Qt中的信號和槽類似`C#`中的**委託事件**機制，是**觀察者模式**的一種實現。
只要信號一觸發，與信號綁定的槽方法都會被調用。
`Qt`使用信號和槽傳遞消息，用戶可以自行定義**信號**和**槽**，`Qt`對象中也包含了許多**預定義**的信號和槽。
一個類中如果需要聲明信號和定義槽方法則需要從`QObject`類(或其子類)中繼承，並在類的聲明中加入宏`Q_OBJECT`。

- `信號(signals)`只需要聲明而不需要實現。使用`emit`關鍵字可以發送信號。
信號的訪問權限是`protected`且**不可更改**，也就是說**無法**在**該類**以及**該類子類**之外的區域發送信號，
但信號的連接是隨意的，可以在類外進行信號連接。
- `槽(slots)`可以**自定義**訪問權限，槽中的方法就像類的普通成員方法一樣，除了方法聲明之外需要有對應的方法實現。

## 連接信號槽
使用`QObject`類型提供的靜態方法`QObject::connect()`將信號與槽相連，`connect`的方法原型是：

```cpp
bool connect(sender, SIGNAL(signals()), receiver, SLOT(slots()));
```

- `sender`和`receiver`分別表示信號發送者與信號接收者，可以傳遞**實例指針**或者**實例引用**作爲參數。
- `SIGNAL()`中填寫的是`sender`的信號方法。
- `SLOT()`中填寫的是`receiver`的槽方法。
- 信號的方法參數類型以及位置需要與槽方法**一一對應**，信號的參數目可以大於槽參數的數目，多餘的參數會被**忽略**。
- 參數只應該填寫**參數類型**而不能畫蛇添足的把參數名一起加上，這樣會編譯報錯。
- 使用`emit`關鍵字發送信號之後，傳遞給信號的參數值會按照對應位置傳到槽中，然後槽方法執行。
- 多個信號與多個槽之間可以任意組合。
- `connect`除了可以將信號和槽相連之外，還可以用於**連接信號**實現信號傳遞。

如下所示：

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
	emit send(a); //發送信號send(int)，a的值作爲參數傳遞到get(int)方法中
	return 0;
}

int main(int argc, char *argv[])
{
	A* a = new A(10);
	QObject::connect(a, SIGNAL(send(int)), a, SLOT(get(int))); //用connect方法將實例指針a的send(int)信號與實例指針a的get(int)槽相連
	std::cout << a->a << std::endl;
	a->set(5); //調用set(int)方法就會發送send(int)信號，使得get(int)槽方法調用，成員變量a的值發生改變
	std::cout << a->a << std::endl;
	return 0;
}
```

輸出結果：

```
10
5
```

在實際應用中，需要注意，常見的槽功能(比如打開/關閉窗口之類的)，在`QWidget`之類的父類中已經爲你實現了，繼承父類自然就獲得了這些槽方法，不用畫蛇添足地自己重新實現功能類似的方法。

## QObject::connect()
`QObject::connect()`擁有多種重載：

```cpp
QMetaObject::Connection QObject::connect(const QObject* sender, const char* signal,
	const QObject* receiver, const char* method, Qt::ConnectionType type = Qt::AutoConnection);
```

這是Qt中最常用的信號槽連接方式，`sender`爲信號發出者，`receiver`爲信號接收者，`signal`爲信號，`method`爲槽方法。
使用此中形式的connect時，`signal`和`method`需要分別使用Qt提供的宏`SIGNAL()`和`SLOT()`。

```cpp
QMetaObject::Connection QObject::connect(const QObject* sender,
	const char* signal, const char* method, Qt::ConnectionType type = Qt::AutoConnection) const;
```

當connect連接的是**當前類**的槽方法時，可以省略接收者`receiver`。
即`connect(object, SIGNAL(signal()), SLOT(slot()))`相當於`connect(object, SIGNAL(signal()), this, SLOT(slot()))`。

```cpp
QMetaObject::Connection QObject::connect(const QObject* sender, PointerToMemberFunction signal,
	const QObject* receiver, PointerToMemberFunction method, Qt::ConnectionType type = Qt::AutoConnection);
```

`connect()`方法同樣支持使用成員指針形式的語法，`signal`和`method`可以使用成員指針的形式。
當一個信號有多個重載版本時，需要通過方法指針的強制類型轉換來顯式指明需要使用的重載版本。

```cpp
QMetaObject::Connection QObject::connect(const QObject* sender, PointerToMemberFunction signal, Functor functor);
```

在Qt5和C++11環境下，connect方法還可以直接連接到一個Lambda表達式上。

## 異步信號
`connect()`方法的最後一個參數枚舉類型`Qt::ConnectionType`可以控制槽方法的回調方式。
`connect()`方法的各個重載版本中，該參數都帶有**默認值**`Qt::AutoConnection`。

- `Qt::DirectConnection` 槽方法以**同步**方式在**sender所處的線程**中執行
- `Qt::QueuedConnection` 槽方法以**異步**方式在**receiver所處的線程**中執行，信號發出後，slot的執行請求會被加入事件隊列，因而slot可能不會立即被執行
- `Qt::BlockingQueuedConnection` 槽方法的執行方式類似`Qt::QueuedConnection`，但sender所處的線程會阻塞，直到slot被執行完畢
- `Qt::AutoConnection` 默認行爲，若sender與receiver處於同一線程下，則使用`Qt::DirectConnection`模式，否則使用`Qt::QueuedConnection`模式



# 事件機制
`事件(event)`是由系統或者Qt本身在不同的時刻發出的。

當用戶按下鼠標，敲下鍵盤，或者是窗口需要重新繪製的時候，都會發出一個相應的事件。
一些事件是在對用戶操作做出響應的時候發出，如鍵盤事件等；另一些事件則是由系統自動發出，如計時器事件。

`Qt`在`main`方法中要創建一個`QApplication`實例，在執行該實例的`exec()`方法時，即進入事件的監聽循環。
當事件發生時，`Qt`會產生事件實例(所有的事件對象都繼承於`QEvent`類)，然後將此事件實例作爲參數傳遞給`QObject`的`event()`方法。
`event()`方法並不直接處理事件，而是將事件分類之後調用特定的事件處理方法，
常見的事件處理方法有`mousePressEvent()`、`keyPressEvent()`等，自行處理事件需要**重寫**對應的事件處理方法。

## 註冊自定義事件
除系統產生的事件外，可以自行使用`QEvent::registerEventType(int hint)`方法註冊自定義事件。

- `hint`參數爲事件序列號，`0~999`被系統佔用，從`QEvent::User`(1000號)到`QEvent::MaxUser`(65535號)都是允許用戶註冊的值。
- 事件類型爲`QEvent::Type`，用`QEvent::registerEventType`註冊時會返回整型的事件號，需要進行**強制類型轉換**。

## 產生事件
**發送**事件可以使用以下方法：

```cpp
void QCoreApplication::postEvent(QObject* receiver, QEvent* event);
bool QCoreApplication::sendEvent(QObject* receiver, QEvent* event);
void QCoreApplication::sendPostedEvents(QObject* receiver, int event_type);
bool QCoreApplication::notify(QObject* receiver, QEvent* event);
```

- `postEvent()`方法將事件放入事件消息隊列中，然後立即返回。
該方法只將事件放入隊列的尾端，不保證事件立即得到處理。
- `sendEent()`方法用`notify()`方法將事件直接派發給接收者和進行處理，返回事件處理者的返回值。
事件會立即送至接受者，發送後，`Qt`不會自動`delete`該事件，因此合適的做法是在棧上創建事件。
- `sendPostedEvents()`方法將事件隊列中用`postEvent()`方法放入的對應接受者和事件類型的事件立即分發，但是來自窗口系統的事件不被分發，它們被`processEvents()`方法分發。
若接受者是`null`，則對應所有的接受者；
若`event_type`爲**0**，則對應`receiver`的所有的事件。
該方法必須和`receiver`在同一個線程內被調用。

## 處理事件
處理事件可以重寫下列方法：

```cpp
void QObject::customEvent(QEvent *event);
bool QObject::event(QEvent *e);
```

前者**不需要**返回值，後者在處理完自定義事件之後需要繼續返回對應控件的父類事件處理方法(`event()`是直接的事件處理方法)。
返回事件循環的時候要注意當前類的繼承關係，只返回最基本的循環`QObject::event()`則會有許多事件**不被處理**。

若一個類的多個控件都需要相同的事件處理則可以重新實現`QObject::eventFilter(QObject *watched, QEvent *event)`方法，
然後在對應的控件對象上使用`QObject::installEventFilter(QObject *filterObj)` 方法安裝過濾器，參數爲要安裝的過濾器所在的類指針。

在處理鍵盤事件時需要注意，若已經接收了某個按鍵的事件同時進行操作，然後將事件繼續返回事件隊列時，
若這個鍵盤事件有系統默認的操作，則系統默認的操作依然會繼續執行，則有可能與自己定義的操作產生衝突，
正確的做法是對自己要處理的鍵盤事件返回`true`(這樣系統定義的操作將不會觸發，能夠避免衝突)，只將不處理的鍵盤事件返回事件循環。

## 事件機制與信號槽的區別
`Qt`中事件由窗口產生，而信號槽機制還可用在命令行裏，同時事件處理方法的返回值是有意義的，
需要根據返回值判定是否要繼續事件處理，但信號與槽綁定時並**不關注**返回值。

事件通過事件隊列來響應，若事件的處理中又產生了新的事件，那麼新的事件會加入到隊列尾，
直到當前事件處理完畢後，`QApplication`再去隊列頭取下一個事件來處理。

信號的處理方式不同，信號處理方式是**立即回調**，一個信號產生後，該信號所註冊的所有槽都會**立即**被回調。



# 數據庫連接
`Qt`中數據庫連接主要是使用`QSqlDatabase`類，在使用這個類時需要注意，此類的構造方法是`protected`的，
因此不能在類外使用，一般使用該類的靜態成員方法`QSqlDatabase::addDatabase()`來創建`QSqlDataBase`對象。

注意事項：

- 在`Linux/Unix`系統中，連接本地數據庫時`QSqlDatabase::setHostName()` 的參數因該填`localhost`，而不是環境變量中的`$hostname`。
- 完成`QSqlDatabase`類實例創建與數據庫相關連接信息設置後，不要忘記調用`QSqlDatabase::open()`打開數據庫，否則無法讀取數據庫中的數據。



# 表格
在`Qt`中，表格主要通過`QTableView`以及`QTableWidget`兩類控件實現。

- `QTableView`需要搭配**model**填充數據內容。
- `QTableWidget`是`QTableView`的子類，相當於一個設定好了**model**的`QTableView`控件。

## QTableWidget
`QTableWidget`可以使用`QTableWidget::setColumnCount(int columns)/QTableWidget::setRowCount(int rows)`來設定表格的大小，
使用`QTableWidget::setItem(int row, int column, QTableWidgetItem * item)`設定每一個單元格中的內容。

默認情況下每一個單元格中的內容都是對象`QTableWidgetItem`，都需要使用`new`操作符構造對象與分配內存，
因此，對於**數據量較大**的表格來說(幾十w甚至上百w)，全部填充單元格的CPU、內存開銷都是非常恐怖的。

`QTableWidget`中，每一個單元格的對象生命週期與整張表格相同，
使用`setItem()`成員方法向原先有內容的單元格中設置新對象時原先的對象不會自動被銷燬，
一般使用`setItem()`之後不再替換該單元格上的對象，而是直接修改對象存儲的內容。

- 向`QTableWidget`中添加控件

	`QTableWidget`還可以使用`QTableWidget::setCellWidget(int row, int column, QWidget * widget)`來向指定單元格中添加控件。
	當使用了`setCellWidget()`添加控件之後，該單元格便不能使用`QTableWidget::item(int row, int column)` 方法來獲取指定單元格的內容(會報空指針錯誤)，
	因爲該單元格中沒有`QTableWidgetItem`，正確的訪問方式是使用`QTableWidget::cellWidget(int row, int column)`來獲取指定單元格的**對象指針**。
	向表格直接使用`setCellWidget()`設置的控件不受`setTextAlign()`影響，會自動擠到單元格一邊，
	需要控件居中顯示則需要新建`QWidget`並設置**Layout**作爲容器，
	在向設置好佈局的Widget中添加需要的控件，然後再將Widget設置到表格中。

	如下所示：

	```cpp
	QWidget* widget = new QWidget(table);
	QHBoxLayout* layout = new QHBoxLayout(widget);
	layout->addWidget(new QCheckBox(widget));
	widget->setLayout(layout);
	table->setCellWidget(row, column, widget);
	```

- 設置`QTableWidget`不可編輯

	使用`setEditTriggers(QAbstractItemView::NoEditTriggers)`可以將整個表格設爲不可編輯。
	不可編輯設置只對`QTableWidgetItem`有效，使用`setCellWidget()`方法設置的控件不會受到影響。

- 表格擴展

	設置表格大小自動擴展：

	1. 通過`QTableView::horizontalHeader()`方法獲取整個表格的`QHeaderView`。
	1. 然後使用其成員方法`setStretchLastSection(bool stretch)`，參數爲`true`時則最後一欄的長度會自動擴展。
	1. 也可以使用`setSectionResizeMode(QHeaderView::Stretch)`來使所有列自動擴展
	(`Qt4`時使用`setResizeMode()`設置所有列擴展，`Qt5`後該方法被**廢棄**，使用`setSectionResizeMode()`替代)。

	如下所示：

	```cpp
	QTableWidget* table = new QTableWidget;
	table->horizontalHeader()->setStretchLastSection(true); //最後一行自動擴展
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //所有行自動擴展
	```

	設定列寬匹配單元格內容：

	- 使用`QTableView::resizeColumnsToContents()`可以使**所有列**的列寬自動適配內容寬度。
	- 使用`QTableView::resizeColumnToContents(int column)`設置**指定列**爲自動適配內容寬度。

- 獲取變化的單元格

	獲取`QTableWidget`中發生變化的位置：

	1. 通過`QObject::sender()`獲取信號的發出源。
	1. 使用`dynamic_cast`宏轉換爲`QWidget`。
	1. 再使用`QWidget::frameGeometry()`得到一個`QRect`型返回值表示該控件在其**parent窗口**中的位置。
	1. 再通過`QTableView::indexAt(const QPoint& pos)`得到包含有單元格位置信息的`QModelIndex`返回值。
	1. 使用`QModelIndex::row()/QModelIndex::column()`獲取源對象的行列值。

	如下所示：

	```cpp
	QTableWidget* table = new QTableWidget;
	QModeIndex index = table->indexAt(dynamic_cast<QWidget*>(sender())->frameGeometry().center());
	int row = index.row();
	int column = index.column();
	```

## QTableView
`QTableView`可以自由搭配不同的**model**：

```cpp
void QTableView::setModel(QAbstractItemModel *model)
```

`QTableView`本身並不存放數據，數據保存在`model`中，可以通過`QAbstractItemView::model()` 來獲取表格中已經組裝的model，
大量的變更數據可以直接`delete`舊的`model`，然後設定並組裝新的`model`。

- `QSqlTableMode`搭配`QTableView`實現數據庫直接操作

	1. 創建出一個`QSqlTableMode`對象，如果已經有數據庫連接且不需要從新的數據庫中讀取數據，則構造方法中的`QSqlDatabase`對象可以取默認值。
	1. 調用`QSqlTableMode::setTable()`設置要顯示的表名，用`QSqlTableMode::setHeaderData()`設置每一列顯示的數據。
	1. 設置完`QSqlTableMode`之後，調用其成員方法`select()`將數據表格配置提交生效。
	1. 創建`QTableView`對象，使用其成員方法`setModel()`將先前建立的`QSqlTableMode`對象作爲參數傳入即可。

- 修改`QSqlTableMode`

	`QSqlTableMode`可以直接在表上進行修改操作。
	使用其成員方法`insertRow()`和`removeRow()`可分別實現**插入行**與**刪除行**操作。
	刪除行時需要手動調用`select()`成員方法進行**提交**，否則被刪除的行將依然佔位置(雖然內容已被清除)。

- 數據庫記錄序號

	數據庫記錄行數是從**0**開始，而`QSqlTableMode`在顯示數據庫數據時，表格是從`1`開始計數的，
	使用`rowCount()`方法得到的返回值比表格上顯示的行數**小**1。

- 刷新`QTableView`

	默認情況下，數據庫的數據發生了變化，`QTableView`不會**實時更新**(model未發生變化)。
	需要調用`QSqlTableModel::select()`方法更新`QSqlTableMode`內的數據，然後`QTableView`纔會將這些數據顯示出來。



# 佈局

## 常用的佈局樣式
佈局之間可以相互嵌套，從而構成複雜的界面。
常用佈局：

- `QHBoxLayout` 水平佈局
- `QVBoxLayout` 垂直佈局
- `QGridLayout` 表格佈局
- `QSpacerItem` **面板彈簧**，可以控制組件的對齊方式
- `QStackedLayout` 把子控件進行分組或者分頁，一次只顯示一組或者一頁，隱藏其他組或者頁上的控件
- `QSplitter` 分裂器，使用分裂器可以將兩個控件(佈局)綁定爲一個整體，處於一個水平/垂直分裂器中的兩個控件可以自由控制水平/垂直方向上分配的空間(自由分界)

需要注意的是，Qt中的佈局的構造方法中同樣可以設定父窗口，但如果傳入了父類窗口指針，則該佈局會嘗試成爲該窗口的默認佈局，但許多控件是擁有默認佈局的，在運行時會發出警告。

## 限制佈局的大小
在Qt中，無法直接限定一個佈局的大小，如果需要一塊佈局限定在指定的大小下，比較簡單的做法是將目標佈局放入一個QWidget控件中，
然後使用`QWidget::setFixedSize()`成員方法限定QWidget控件的大小即可。

## 柵格化佈局
在使用`QtCreator`設計UI時，默認情況下，界面元素的佈局是不會隨着窗口大小的變化而變化的，
如果需要設計元素佈局會隨着窗口改變的界面，則需要使用柵格化佈局。

柵格化佈局本質上是將整個界面的佈局設置爲`QGirdLayout`，處於該佈局內的窗口元素都會隨着窗口大小的改變而變化其位置與間隔。



# qApp
`Qt`中如果包含了`QApplication`或`QCoreApplication`頭文件，就可以使用全局變量`qApp`，該變量的作用是返回一個**當前實例**。

`qApp` 的宏定義：

- 在`QApplication`中爲`#define qApp (static_cast<QApplication*>(QCoreApplication::instance()))`
- 在`QCoreapplication`中爲`#define qApp QCoreApplication::instance()`

在使用一些`靜態槽方法`時，連接信號槽時就需要使用此變量，比如`QApplication::aboutQt()`。



## 菜單構建

## 構建主菜單
`Qt`中的菜單欄爲`QMenuBar`，而顯示在菜單欄上的一級選項爲`QMenu`，
而每個`QMenu`可以通過`QMenu::addAction(QAction*)` 來添加`QAction`作爲菜單項。

通常`Qt`應用程序會包含一個繼承於`QMainWindow`類的主窗口，
主窗口通過`QMainWindow::setMenuBar(QMenuBar*)`方法來設定窗口的菜單欄。

而`QMenuBar`菜單欄通過`QMenuBar::addMenu(QMenu*)`方法添加`QMenu`作爲一級菜單，
`QMenu`也可以通過`QMenu::addMenu(QMenu*)`來添加二級菜單。

`QAction`除了添加在菜單中，還可以添加在`QToolBar`中。
`QAction`可以保持按下的狀態，通過`QAction::setCheckable(bool)`設置爲true時，
按下QAction便不會自動彈起，需要再次點擊纔會彈起。
默認可以有**多個**`QAction`保持**按下**的狀態，若需限定只能有一個`QAction`保持按下的狀態，
則可以將這些`QAction`加入**同一個**`QActionGroup`中。

## 構建右鍵菜單
`QWidget`及其子類都可以通過重寫虛方法`contextMenuEvent(QContextMenuEvent*)`來構建**右鍵菜單**。

```cpp
void QWidget::contextMenuEvent(QContextMenuEvent*)
{
	QMenu* contextMenu = new QMenu(this);
	contextMenu->addAction(new QAction("Test"));
	contextMenu->exec(cursor().pos()); //使用cursor()獲取當前控件的QCursor鼠標對象，然後使用 QCursor::pos() 獲得當前鼠標的位置，這樣右鍵菜單便能在鼠標位置出現
}
```



# 鼠標監聽

## 鼠標點按事件
Qt中鼠標點按動作會觸發下列事件：

```cpp
void QWidget::mousePressEvent(QMouseEvent* e);
void QWidget::mouseReleaseEvent(QMouseEvent* e);
```

**重寫**這些事件處理方法即可。

對於鼠標事件`QMouseEvent`，可以使用`QMouseEvent::pos()`獲取控件內座標，和`QMouseEvent::globalPos()`獲取全局座標(顯示器座標)。

## 鼠標移動事件
移動鼠標會觸發下列事件：

```cpp
void QWidget::mouseMoveEvent(QMouseEvent* e);
void QWidget::leaveEvent(QEvent* event);
void QWidget::enterEvent(QEvent* event);
```

當鼠標移入控件時，會觸發`enterEvent()`方法，當鼠標移出控件時會觸發`leaveEvent()`，觸發這些事件並**不需要**控件獲得焦點，只需要鼠標進入/退出指定控件區域即會觸發。

需要注意的是，默認情況下Qt只監聽鼠標**按下之後**的動作，如果需要Qt監聽所有鼠標動作需要使用方法`setMouseTracking(true);`



# 自定義控件
`Qt`中的控件類通常在構造方法中有`QWidget* parent = 0`的參數用來指定當前類的實例的歸屬。
默認該參數默認爲0，即沒有父窗口。
當一個控件類實例的父窗口被關閉時，`Qt`會**自動析構**以此窗口爲父窗口的所有控件類。

佈局控件`QLayout`在實例化時參數填寫了父窗口則代表將這個實例化的佈局應用到作爲參數傳入父窗口上。
很多時候這樣做是無效的，會提示父窗口已經擁有佈局，因此在實例化佈局控件是沒必要指定父窗口。

需要自定義控件時，根據需求繼承於`QWidget`或其子類，在自定義控件類的構造方法中，建議也要添加一個參數用於設定父窗口。
如下所示：

```cpp
MyWidget(QWidget* parent = 0);
```

類外定義寫成：

```cpp
MyWidget::MyWidget(QWidget* parent) : QWidget(parent)
{
	/* 方法體 */
};
```

與標準C++不同的是，Qt類中的成員方法默認參數只能寫在類體內部的方法聲明中，
在類外的方法實現中再給方法參數設定默認值同時在實例化時用省略默認值的形式調用方法會報錯
(但在標準C++中，成員方法的默認參數既可以寫在類內的聲明中，也可以寫在類外的定義中)。

## 獲取子控件的指針
當一個窗體中包含了大量的子控件時，若要獲取某個子控件的指針，不必將該控件做爲成員變量寫入類定義中，
Qt提供了以下方式來獲取子控件的指針：

```cpp
template<typename T> T QObject::findChild(const QString& name = QString()) const; //通過ObjectName來獲取需要的控件指針
template<typename T> QList<T> QObject::findChildren(const QRegExp& regExp) const; //通過正則表達式來獲取子控件指針
const QObjectList& QObject::children() const; //直接返回所有子控件
```

前兩種方法需要知道控件的**類型**，最後一種不需要，但得到的是`QObject`類型。
藉助Qt的**元對象系統**，可以獲取`QObject`類的**真實類型信息**，如可使用以下方式獲取類名：

```cpp
QString class_name = obj->metaObject()->className();
```



# 窗口

## 新建窗口
Qt中打開窗口主要有兩種方式：

- `show()`默認會創建一個新的**普通窗口**，用戶可以在新窗口和舊窗口之間切換焦點。
- `exec()`創建一個**模態窗口**，在新創建的模態窗口被關閉前，你不能將焦點切換回父窗口。

`show()`通過設置參數也可以創建模態窗口，但`exec()`只能創建模態窗口。
`show()`創建窗口之後程序會**繼續執行**後面的代碼，但使用`exec()`創建模態窗口則會**阻塞線程**，直到模態對話框收到`accept()`、`reject()`等操作纔會繼續執行代碼。

- 注意事項

	新建**普通窗口**通常採取在**堆**中分配內存的方式(使用`new`操作符來創建一個指向該塊內存的指針)。
	在`main`方法中，也可嘗試不使用指針直接在棧中創建對象(`main`方法由於事件循環存在，不會自動退出)。
	在其他方法中，不應在棧上創建普通窗口，因爲方法結束，該方法的**棧**就會被**銷燬**，而如果實例在棧中創建則會隨着方法結束而被析構。
	新建**模態窗口**則無需在堆中創建，創建模態窗口的`exec()`方法在被創建的窗口關閉前不會返回，窗口實例不會被提前析構。

## 窗口內存回收
一般情況下，通過指定`QWidget*`的父窗口指針，當父窗口被析構時，當前窗口的內存也被釋放。

如果不指定父窗口，則可使用創建棧變量的形式，出棧時變量自動釋放：

```cpp
QWidget w;
w.exec();
```

還可以通過設置窗口的`Qt::WA_DeleteOnClose`屬性來讓窗口關閉時自動釋放內存：

```cpp
QWidget* w = new QWidget;
w->setAttribute(Qt::WA_DeleteOnClose, true);
w->show();
```

需要注意的是，設置了`Qt::WA_DeleteOnClose`屬性則不能將窗口類以**棧變量**的形式創建，因爲棧變量在出棧時還會被析構一次，造成**重複析構**。

## 預設窗口
對於一些**功能簡單**的交互對話框，我們不必要一一自己實現，在Qt中提供了許多預設好的簡單對話框(均爲**靜態成員方法**，可直接使用)。

如獲取用戶輸入可以使用`QDialog`子類的成員方法：

```cpp
QString QInputDialog::getText(...); //用於獲取字符串
int QInputDialog::getInt(...); //用於獲取整型數值
QColor QColorDialog::getColor(...); //用於提供色彩選擇對話框
QFont QFontDialog::getFont(...); //用於提供文字選擇對話框
QString QFileDialog::getOpenFileName(...); //用於獲取選擇的文件路徑(文件原先存在)
QString QFileDialog::getSaveFileName(...); //用於獲取創建的文件路徑(文件原先不存在)
QString QFileDialog::getExistingDirectory(...); //用於獲取指定目錄的路徑
```

提示用戶和獲取用戶判斷的對話框爲`QMessageBox`：

```cpp
StandardButton QMessageBox::question(...); //詢問用戶的判斷
StandardButton QMessageBox::information(...); //提示用戶普通信息
StandardButton QMessageBox::warning(...); //提示用戶警告信息
StandardButton QMessageBox::critical(...); //提示用戶危險信息
```

## 窗口按鈕、邊框設置
通過使用`void setWindowFlags(Qt::WindowFlags type);`方法可以設置窗口的邊框樣式以及窗口上具有的按鈕。

默認情況下，可以使用Qt預設的窗口邊框樣式，在枚舉類型`enum Qt::WindowType`中，常用的有`Qt::Widget`、`Qt::Window`、`Qt::Dialog`等樣式。
如果預設的窗口樣式不能滿足需求，則可以使用`Qt::CustomizeWindowHint`搭配自定義按鈕組成需要的樣式，例如，創建一個僅帶有空的標題欄的窗口可以使用代碼：

```cpp
setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
```

## 窗口大小的設置
一般而言設置Qt的窗口大小可以使用下列方法：

```cpp
void QWidget::setGeometry(int x, int y, int w, int h);
void QWidget::resize(int w, int h);
```

前者在設置大小的同時還能設置窗口在屏幕的顯示位置，後者用於重新設定窗口大小。

窗口採用柵格化佈局時，使用以上兩個方法在設定大小時很可能不會生效。
此時可以使用`QWidget::setFixedSize(const QSize &)`來設定固定的窗口大小，這個大小能夠覆蓋佈局定義的大小而強制生效，如果只需要設定寬或是高可以單獨使用`QWidget::setFixedWidth(int w)`或是`QWidget::setFixedHeight(int h)`。

窗口設置了固定的大小如果需要再改動，可以將宏`QWIDGETSIZE_MAX`作爲參數傳入`QWidget::setFixedSize(const QSize&)`方法中，窗口就會重新變成可調大小。

使用`QWidget::sizeHint()`方法可以獲取Qt判斷的窗口**最合適**大小。



# 文本與字符串處理
在Qt中使用`QString`做爲基本的字符串類。

## 字符串轉換
在Qt中，默認字符串與數字用加號拼接然後轉換爲`QString`類型時，數字會被當作`ASC碼`對待，
要使數字保持語義轉化爲字符串則需要使用`QString::number(int/double/long)`方法進行轉換。

`QString`可以通過`QString::toStdString()`來得到傳統風格的`C++`字符串類型`std::string`，
而`std::string`可以通過`std::string::c_str()`方法轉換爲c風格的`char*`字符數組指針。
`QString`可以使用靜態方法`QString::fromStdString(const std::string &str)`來直接將`std::string`轉換爲`QString`。

對於可能出現的字符串亂碼問題，可以使用靜態方法`QString QString::fromLocal8Bit(const char* str, int size = -1)`來構建`QString`。

## 格式化文本
`QString`類提供了多樣的**格式化文本**功能，類C風格的格式化可以使用其成員方法`QString::sprintf(const char *cformat, ...)`進行。

需要注意的是，Qt本身並不推薦使用`QString::sprintf()`來進行文本格式化，
`QString::sprintf()`在`Qt 5.5`中已經被標記爲`Obsolete(廢棄的)`，可能會在未來版本中移除該方法。

Qt風格的文本格式化應使用`QString::arg(const QString& a, int fieldWidth = 0, QChar fillChar = QLatin1Char(' '))`來進行。

## QLabel 多行顯示文本
在默認情況下，`QLabel`控件只會**單行**顯示文本，一旦文本內容超過了`QLabel`控件的`Width`，就無法顯示。
如果需要在指定寬度下完整顯示文本，就需要將`QLabel`設置爲允許多行顯示。使用`setWordWrap(true)`方法設置`QLabel`的允許多行顯示。

## 限制 QLineEdit 輸入內容
很多時候，需要對用戶輸入的內容加以限制，對於簡單的限制，可以使用`QLineEdit::setValidator(const QValidator* v)`限制輸入內容。

- 限制只能輸入整數
```cpp
QLineEdit* lineEdit = new QLineEdit();
lineEdit->setValidator(new QIntValidator(0, 1000, this)); //限制輸入0~1000的數值
```
- 限制只能輸入小數
```cpp
QLineEdit* lineEdit = new QLineEdit();
lineEdit->setValidator(new QDoubleValidator(0.0, 1000.0, 2, this)); //限制輸入0.0~1000.0的數值，最大保留小數點後兩位
```
- 複雜的輸入限制(使用正則表達式校驗器`QRegExpValidator`)
```cpp
QLineEdit* lineEdit = new QLineEdit();
lineEdit->setValidator(new QRegExpValidator(QRegExp("正則表達式內容")), this);
```



# QListWidget
`QListWidget`是一個自帶了**model**的`QListView`實現，使用`QListWidget`可以方便的構建列表框。
`QListWdget`的索引號從**0**開始。

## QListView::IconMode
`QListWdget`默認以列表的模式顯示，但`QListWidget`實現了`QListView`中的`setViewModel()`方法，支持**圖標模式**。
使用方法`QListWidget::setViewMode(ViewMode mode)`，參數爲`QListView::IconMode`即可將`QListWidget`設置爲圖標模式。
使用方法`QListWidget::setMovement(Movement movement)`可以設置圖標的移動模式，參數爲`QListView::Static`時圖標不可移動。

## 使 QListWidgetItem 能被勾選
`QListWidgetItem`使用`void QListWidgetItem::setCheckState(Qt::CheckState state)`來設置勾選狀態，使用此成員方法則item前會出現類似`QCheckBox`樣式的複選框。
當`state`參數取值`Qt::Checked`爲勾選狀態，`Qt::Unchecked`爲非勾選狀態。

## 用 QListWidgetItem 保存數據
`QListWidget`中的每一個列表項都是一個`QListWidgetItem`對象，對於`QListWidgetItem`，常用的方法有：

```cpp
void QListWidgetItem::setText(const QString& text); //設置列表項/圖標模式下的顯示文字
void QListWidgetItem::setData(int role, const QVariant& value); //設置item保存的數據內容
```

`setData()`成員方法中的第一個參數爲保存數據的角色`Qt::ItemDataRole`，該值從`0~14`之間爲Qt自身使用的Role，
比如item默認的文本數據就保存在`0`角色中，即在Role爲`0`時，`setText()`和`setData()`只有**一個**能生效(後調用的那個會把先前的數據覆蓋)。

提供給用戶使用的Role從`Qt::UserRole`開始，`Qt::UserRole`之後的數值都可以由用戶使用。

## 對齊 QListWidgetItem
如果給`QListWidgetItem`設定了文本，那麼，在文本長度不一致的時候，圖標很可能不會保持對齊狀態。
此時可以使用`QListWidgetItem::setSizeHint(const QSize& size)`來強制設定每個item的大小，
使每個item大小完全相同，達到對齊的效果(過長的文本會以省略號顯示)。

## 查找 QListWidgetItem
可以使用`QList<QListWidgetItem*> QListWidget::findItems(const QString& text, Qt::MatchFlags flags) const`
來查找指定文本內容的`QListWidgetItem`。
可以通過設定`flags`來設定一些簡單的匹配規則，常用的匹配規則有：

- `Qt::MatchStartsWith` 查找名稱最前部分匹配text的item
- `Qt::MatchEndsWith` 查找名稱最後部分匹配text的item
- `Qt::MatchContains` 查找名稱包含text的item
- `Qt::MatchFixedString` 查找完全匹配text的item，默認忽略大小寫的，通過枚舉`Qt::MatchCaseSensitive`設置大小寫敏感



# QTreeWidget
`QTreeWidget`是`QTreeView`的自帶model實現。
`QTreeWidget`不僅可以用於展示**樹狀列表**，也可以一定程度上代替`QTable`來**構建表格**。

## 添加行
`QTreeWidget`中每一行都是一個`QTreeWidgetItem`對象，
在構建`QTreeWidgetItem`時傳入`QTreeWidget`指針即會將該item自動添加到該樹形控件中。
可以使用以下方法來對`QTreeWidgetItem`進行設置：

```cpp
void QTreeWidgetItem::setText(int column, const QString& text); //設置指定列的文本內容
void QTreeWidgetItem::setCheckState(int column, Qt::CheckState state); //設置指定列的勾選狀態，使用該方法後指定列會處於可勾選狀態
void QTreeWidgetItem::setData(int column, int role, const QVariant& value); //item的每一列都可以用來保存數據
void QTreeWidgetItem::setFlags(Qt::ItemFlags flags); //設置標誌，可用來控制item的一些行爲。比如：是否可用(Qt::ItemIsEnabled)、是否可編輯(Qt::ItemIsEditable)、是否可選中(Qt::ItemIsSelectable)、是否可由用戶點選(Qt::ItemIsUserCheckable)等。
```

每一個`QTreeWidgetItem`還可以添加其它`QTreeWidgetItem`，從而形成**樹狀**。

## 設置列寬自動擴展
與`QTableWidget`類似，`QTreeView/QTreeWidget`也可以使用`QTreeView::resizeColumnToContents(int column) [slot]`設置指定列的**列寬自適應**。
`QTreeWidget`的表頭爲一個`QHeaderView`對象，更細節的列寬分配可通過`QHeaderView`類的相關方法來進行設置。
`QTreeWidget`實現了`QHeaderView* QTreeView::header()`方法，因此通過`header()`方法可以直接獲得`QHeaderView`對象指針。

使用以下方法對`QTreeWidget`進行列寬設置：

```cpp
void QHeaderView::setStretchLastSection(bool stretch); //設置最後一列自動擴展
void QHeaderView::setSectionResizeMode(int logicalIndex, ResizeMode mode); //設置指定列的列寬擴展模式，有固定大小(Fixed)、擴展列寬到合適大小(Stretch)、根據內容寬度決定列寬(ResizeToContents)等
```

## 清空、刪除、移除節點
刪除QTreeWidget的item可以直接使用`delete`操作符，釋放掉指定item的內存，該item便會從樹形控件上刪除。

將整個樹形控件清空可以使用：

```cpp
void QTreeWidget::clear(); //使用clear()方法會在清空樹形控件的同時將所包含item的內存釋放
```

如果僅僅需要解除某個QTreeWidgetItem與樹形控件的綁定關係(即只移除控件不釋放內存)，可以使用：

```cpp
QTreeWidgetItem* QTreeWidget::takeTopLevelItem(int index); //從樹形控件上移除指定索引位置的頂層item，不回收item的內存，item在移除後依然可以重新添加
void QTreeWidgetItem::removeChild(QTreeWidgetItem* child); //從某個節點上移除其子節點，不釋放內存
```

使用`takeTopLevelItem()`方法移除指定item後會返回被移除item的指針，若參數位置的item不存在，則返回`0`，利用此特性，
可以循環移除QTreeWidget的所有item，如下所示：

```cpp
while (tree->takeTopLevelItem(0)); //循環直到索引0所在的位置item不存在，則說明所有的item都已被移除
```

需要注意的是，通過`void QTreeWidget::setItemWidget(QTreeWidgetItem* item, int column, QWidget* widget)`方法向某個item中添加的widget時，
並**沒有**將item與該widget綁定。使用`taketoplevelitem()`方法移除item再重新填加item後，
item原先位置設置的widget不會顯示出來，需要重新使用`setItemWidget()`方法進行設定後纔會顯示。

## 其它常用設置

```cpp
void QHeaderView::setSortIndicatorShown(bool show); //使QTreeWidget的頭標籤支持點按排序
void QTreeWidgetItem::setBackgroundColor(int column, const QBrush& brush); //填充指定列的背景色
void QHeaderView::setDefaultSectionSize(int size); //設置默認列寬
void QHeaderView::setMinimumSectionSize(int size); //設置最小列寬
```

## 遍歷 QTreeWidgetItem
使用`QTreeWidgetItem`的迭代器對象`QTreeWidgetItemIterator`即可進行`QTreeWidget`的遍歷

```cpp
for (QTreeWidgetItemIterator it(QTreeWidget*); *it; ++it)
{
	/* do something... */
}
```

`QTreeWidgetItemIterator`可以分別以`QTreeWidget`指針或是`QTreeWidgetItem`指針進行構建，用來遍歷不同層次的目錄樹。



# 圖片顯示/圖片存儲

## 在 QLabel 中顯示圖片
首先得到要打開的圖片的路徑：

```cpp
QString url = QFileDialog::getOpenFileName(this);
```

創建一個QLabel控件：

```cpp
QLabel* label = new QLabel(this);
```

用前面得到的路徑變量url創建一個`QPixmap`控件：

```cpp
QPixmap pixmap(url);
```

通過`QPixmap::setPixmap()`方法設定`QLabel`的`QPixmap`控件來讓`QLabel`顯示圖片：

```cpp
label->setPixmap(pixmap);
```

如果圖片大小不匹配，可以通過`QPixmap::sacled()`方法改變圖片的顯示比例：

```cpp
QPixmap QPixmap::scaled(int width, int height);
```

需要注意的是該方法返回的是`QPixmap`類型，變更了大小的新的`QPixmap`在**返回值**中，需要顯式的賦值給一個`QPixmap`對象。

## 在 QComobox/QListWidget 中顯示圖片
使用`QComboBox::addItem(const QIcon& icon, const QString& text, const QVariant& userData = QVariant())`向一個組合框添加選項內容時，
將需要在組合框中顯示的圖片轉換成`QIcon`類型，填入第一個參數即可。

`QComboBox`在顯示圖片具有自身默認大小，無論原圖片的大小如何，都會被縮放成`QComboBox`中指定的大小。

指定`QComboBox`中顯示圖片的大小需要使用`QComboBox::setIconSize(const QSize& size)`來顯式指定。
對於`QListWidget`，操作方式類似，控制顯示圖片的大小同樣需要使用`QListWidget::setIconSize(const QSize& size)`來顯式指定。

## 向數據庫中寫入圖片
首先通過得到的文件路徑用`QFile`打開文件：

```cpp
QFile file(url);
```

然後將得到的文件對象設置`OpenMode`(對於上傳圖片到數據庫的操作，只需要只讀屬性)，未設置此屬性會造成無權限讀取文件：

```cpp
file.open(QIODevice::ReadOnly);
```

將打開的文件對象轉化爲**二進制**數據：

```cpp
QByteArray byte = file.readAll();
```
將得到的二進制數用`QVariant`封裝：

```cpp
QVariant var(byte);
```

然後使用`QSqlQuery`對象執行插入語句將var插入數據庫(不能使用exec()語句直接插入，因爲`QVariant`與`QString`不能直接相連)：

```cpp
sql.prepare("inesrt into [表名] (列名) values(?)");
sql.addBindValue(var);
sql.exec();
```

## 從數據庫中讀取圖片
首先使用`QSqlQuery`對象執行`exec()`查詢語句，然後將智能指針**下移**一個位置:

```cpp
sql.exec("查詢語句");
sql.next();
```

將`QSqlQuery`對象中的數據轉化爲二進制數據：

```cpp
QByteArray byte = sql.value(0).toByteArray();
```

將得到的二進制數據傳入`QPixmap`對象：

```cpp
QPixmap map;
map.loadFromData(byte);
```

最後將`QPixmap`對象綁定到`QLabel`控件上：

```cpp
QLabel* label = new QLabel;
label->setPixmap(map);
```



##繪圖系統
Qt的**繪圖系統**主要包括：

- `QPainter` 用於執行繪圖的操作。
- `QPaintDevice` 提供一個二維空間的抽象，給`QPainter`提供繪製圖形的空間。
- `QPaintEngine` 對於開發人員透明，用於`QPainter`和`QPaintDevice`之間的**通訊**。

`QPaintDevice`相當於畫板，`QPainter`相當於畫筆，`QPaintDevice`有多種子類如`QPixmap`、`QImage`等。

## paintEvent()
一般而言，自行繪製圖形可以自定義一個類繼承於`QWidget`，然後重寫`QWidget::paintEvent(QPiantEvent*)`事件處理方法，
將繪製圖形的操作放在`paintEvent()`事件處理方法中。

在`Qt4`之後，繪圖操作可以不必放在`paintEvent()`事件處理方法中運行，但對於從`QWidget`繼承過來的類而言，
必須將繪製操作放在`paintEvent()`中，可以封裝一個類用於管理paint操作，然後將該類放在`paintEvent()`中實例化。

`paintEvent()`是一個會被頻繁觸發的事件，每次窗口有刷新行爲都會觸發該事件方法進行重繪。
`paintEvent()`事件方法也可以被手動觸發，`QWidget`的子類使用`repaint()`、`update()`成員方法就能主動觸發重繪事件。

## QPainter
`QPainter`相當於畫筆，用於控制線的**樣式**、**顏色**、**粗細**等。

使用`QPainter`繪製圖像時，需要在構建`QPainter`實例時傳入需要繪製的設備的地址作爲參數或者使用`begin()`成員方法來確定繪製設備，
比如`QPainter painter(this);`就是實例化了一個繪製**當前控件**的`QPainter`。
一個`painter`只能同時繪製一個設備(一支筆不能同時在兩張紙上寫字)，但可以在繪製設備之間進行切換，
從一個繪製設備切換到另一個繪製設備之前需要使用`end()`成員方法結束上一個被繪製的設備，
然後將下一個可繪製設備的地址傳入`begin()`成員方法進行繪製。

`QPainter`提供了一系列的API用於繪製各類圖形，如`QPainter::drawPoint/drawLine()/drawPath()/drawRect()`等。
`QPainter`不僅能用於繪製圖像，還可以用於繪製**文字**(使用`drawText()`方法)。

`QPainter`使用`QPainter::setPen(const QPen& pen)`可以設置畫筆的樣式(線形、色彩等)。
`QPainter`使用`QPainter::setFont(const QFont& font)`可以設置文本的字體。

## QPixmap
使用默認的構造方法(無參構造方法)構造`QPixmap`時，會產生一個**空的**`QPixmap`對象，
空的`QPixmap`對象是**不能**傳入`QPainter`進行繪製操作的(運行時提示`QPainter::begin: Paint device returned engine == 0, type: 2`)，
需要重載的`賦值操作符/load()`等成員方法加載數據之後才能繪製，
也可以使用帶有初始大小的`QPixmap(const QSize& size)`、`QPixmap(int width, int height)`等構造方法創建一個**初始非空**的`QPixmap`對象。

相比直接在控件上進行繪製，使用`QPixmap`最大的不同是像`QPixmap`中繪製的數據是可以被保存下來的，而直接在控件上繪製則每次刷新會丟失先前繪製的內容。

`QPixmap`可以使用`QImage QPixmap::toImage() const`轉換爲`QImage`。

## QImage
與`QPixmap`類似，使用無參構造方法創建的`QImage`同樣是空的，沒有分配內存不能直接用於`QPainter`繪製，
使用`QPainter`繪製需要使用有參構造方法構建**非空**的`QImage`對象。

相比`QPixmap`，`QImage`支持進行**像素級別**的操作，`QPixmap`的實現依賴於硬件，`QImage`不依賴於硬件，
`QPixmap`主要用於繪圖,針對屏幕顯示而最佳化設計，`QImage`主要是爲圖像I/O、圖片訪問和像素修改而設計。

## 圖片透明化
使用`QImage`處理圖片時可以通過設置圖片的**Alpha通道**使圖片透明化。

簡單的透明處理可以使用`QImage::setAlphaChannel(const QImage& alphaChannel)`以另一個`QImage`對象作爲參數使圖片透明化。
若需要手動指定透明度(Alpha值)，則可以創建一個帶有Alpha通道的`QImage`對象，如`QImage temp_image(win_size, QImage::Format_ARGB32);`
使用設置了透明畫刷的`QPainter`對其進行色彩填充，然後將此`QImage`作爲`QImage::setAlphaChannel()`成員方法的參數。

如下所示：

```cpp
int alpha = 100; //定義alpha透明度
QImage temp_image(100, 100); //創建空白QImage
QPainter painter(&image);
painter.fillRect(0, 0, 100, 100, QColor(alpha, alpha, alpha, alpha)); //填充色彩
image.setAlphaChannel(temp_image); //以temp_image爲樣本設置原圖像的alpha通道
```



# 處理命令行參數
`Qt5.2`之後提供了類`QCommandLineParser`以及`QCommandLineOption`來進行命令行參數的處理。

## 獲取命令行輸入
Qt中不需要傳遞`argc`和`**argv`，可以通過靜態方法`QStringList QCoreApplication::arguments()`在任意位置獲取到用戶輸入的命令行參數。

## 解析命令行參數
`QCommandLineOption`用於表示某一個具體的命令參數，`QCommandLineParser`用於添加用`QCommandLineOption`類表示的命令行參數。
構造`QCommandLineOption`對象時傳入一個`QString`做爲參數的名稱，通過`QCommandLineOption::setDefaultValue(const QString& defaultValue)`設置參數的默認值。
`QCommandLineParser`使用`QCommandLineParser::addOption(const QCommandLineOption& option)`添加`QCommandLineOption`命令行參數類。
通過使用`bool QCommandLineParser::isSet(const QCommandLineOption& option)/isSet(const QString& name)`判斷命令行中是否帶有指定參數。

## 獲取系統環境變量
使用`QStringList QProcess::systemEnvironment()`可以獲取系統所有的環境變量。
將得到的`QStringList`使用`startsWith("xxx=")`即可獲取以xxx爲名稱的環境變量的值。



# 窗口截圖
一般使用`QWidget`的靜態成員方法進行截圖：

```cpp
QPixmap grabWidget(QObject* widget, int x = 0, int y = 0, int w = -1, int h = -1);
```

也可以使用`QScreen`對象進行截圖操作。

```cpp
QScreen* screen = QGuiApplication::primaryScreen();
QPixmap view = screen->grabWindow(winId(), 0, 0, size().width(), size().height());
```



# QWebKit
Qt提供了基於`WebKit`引擎的`QWebKit`做爲**網頁解析引擎**。
網頁瀏覽功能可以使用`QWebView`控件。
使用`QWebView`控件需要添加`QWebKit`庫(該庫默認沒有被引用)。

## 加載頁面
使用`QWebView::load(const QUrl& url)`將連接地址做爲參數可以讓`QWebView`載入一個頁面。
連接地址需要符合`URL`(統一資源定位符)的規範，格式應寫成`協議://路徑1/路徑2/路徑xxx?參數1=參數值1&參數2=參數值2&參數xxx=參數值xxx`。

常見的協議有：

- `http` 超文本傳輸協議
- `https` 用安全套接字層傳送的超文本傳輸協議
- `ftp` 文件傳輸協議
- `file` 本地或互聯網分享文件路徑

## 響應頁面點擊事件
在`QWebView`中展示的頁面點擊鏈接可以發出信號`QWebView::linkClicked(const QUrl& url)`，捕獲該信號進行處理即可。

默認情況下，點擊鏈接**不會**自動發送該信號，發送點擊信號需要以下步驟：

1. 使用`QWebView::page()`獲取當前頁面。
1. 使用`void QWebPage::setLinkDelegationPolicy(LinkDelegationPolicy policy)`將獲取頁面的鏈接代理設置爲`QWebPage::DelegateExternalLinks/QWebPage::DelegateAllLinks`。
1. 進行點擊操作產生點擊信號。



# 字體設置
通過使用`QFontDataBase`對象可以獲取當前系統的字體數據。
通過使用`QFontMetrics`對象可以獲取指定樣式字體的寬度、高度。

## 打印出當前系統支持的字體

```cpp
foreach (const QString& font_name, QFontDatabase().families())
	std::cout << font_name << std::endl;
```

其中，`QStringList QFontDatabase::families(WritingSystem writingSystem = Any) const`方法的參數可以用於指定文字類型，例如，列出簡體中文的字體可以寫成：

```cpp
foreach (const QString& font_name, QFontDatabase().families(QFontDatabase::SimplifiedChinese))
	std::cout << font_name << std::endl;
```

## 獲取文本的寬高
`QFontMetrics`類的構造方法可以使用`QFont`做爲參數。
使用`int QFontMetrics::width(const QString& text, int len = -1) const`可以獲取指定文本的寬度。

```cpp
QFont font("times", 24);
QFontMetrics fm(font);
int pixelsWide = fm.width("What's the width of this text?");
int pixelsHigh = fm.height();
```



# 文件操作
Qt中的文件和目錄相關類主要爲`QFile`和`QFileInfo`以及`QDir`。
`QFile`用於文件操作，而`QFileInfo`用於獲取文件信息，`QDir`用於過濾文件。

## QFile
`QFile`類定義了一系列的靜態成員方法，提供了常見的文件操作：

```cpp
bool QFile::copy(const QString& fileName, const QString& newName); //複製文件
bool QFile::exists(const QString& fileName); //判斷文件是否存在
bool QFile::open(OpenMode mode); //檢測文件的讀寫狀態
bool QFile::remove(const QString& fileName); //刪除文件
bool QFile::rename(const QString& oldName, const QString& newName); //重命名文件
bool QFile::link(const QString& fileName, const QString& linkName); //創建文件快捷方式，在Unix系統下爲創建符號鏈接
```

## QFileInfo
`QFileInfo`類提供了一系列獲取文件信息的方法：

```cpp
QString QFileInfo::absoluteFilePath() const; //獲取文件的絕對路徑(包含文件名)
QString QFileInfo::absolutePath() const; //獲取文件的路徑(不含文件名)
QString QFileInfo::baseName() const; //獲取文件的不含後綴的文件名(以第一個"."符號爲界)
QString QFileInfo::completeBaseName() const; //獲取文件的不含最後一個後綴的文件名(以最後一個"."符號爲界)
QString QFileInfo::fileName() const; //獲取文件的完整文件名(不含路徑)
```

## QDir
`QDir`類能夠按指定規則在路徑下篩選出符合要求的文件，常用的方法有：

```cpp
QFileInfoList QDir::entryInfoList(const QStringList& nameFilters, Filters filters = NoFilter, SortFlags sort = NoSort) const;
QStringList QDir::entryList(const QStringList& nameFilters, Filters filters = NoFilter, SortFlags sort = NoSort) const;
QFileInfoList QDir::entryInfoList(Filters filters = NoFilter, SortFlags sort = NoSort) const;
QStringList QDir::entryList(Filters filters = NoFilter, SortFlags sort = NoSort) const;
```

其中過濾規則`Filters`是一個枚舉類，定義了一些的過濾條件，如`QDir::Readable`表示文件可讀，`QDir::Writable`表示文件可寫。
當不添加任何參數時，方法返回的是路徑下的**所有文件**。



# 國際化
對Qt工程進行國際化首先需要在項目中創建`ts`翻譯文件，並對需要翻譯的文本使用`QObject::tr()`方法進行標記。

`ts`翻譯文件本質上是一個**XML文檔**，記錄了源碼中被標記的文本與翻譯文本之間的對應關係。
`ts`翻譯文件可以被編譯成`qm`格式的二進制翻譯文件，用於被程序加載。

## 動態切換程序語言
使用`QTranslator`類可以實現程序語言的動態切換。

通過`QTranslator::load()`的重載方法加載`qm`文件：

```cpp
bool QTranslator::load(const QString& filename, const QString& directory = QString(),
		const QString& search_delimiters = QString(), const QString& suffix = QString());
bool QTranslator::load(const QLocale& locale, const QString& filename,
		const QString& prefix = QString(), const QString& directory = QString(), const QString& suffix = QString());
```

最後使用`bool QCoreApplication::installTranslator(QTranslator* translationFile)`方法將加載好`qm`文件的`QTranslator`對象做爲參數傳入，界面語言便會立即變化。
需要注意的是，需要保證加載的`QTranslator`對象不被銷燬，翻譯才能正常顯示，否則界面又會變回默認的語言。



# 常見錯誤

## 關於 `undefined reference to vtable for XXX(類名)` 錯誤
在類定義中，若使用`Q_OBJECT`宏，則需將對應代碼使用`moc`工具預處理生成`*.moc`文件才能正常編譯。
`qmake`工具掃描代碼中的`Q_OBJECT`時只會從`*.h`命名的文件中查找，若在編碼中將類的定義寫在`*.cpp/*.cc`文件中，
則不會被`qmake`工具識別，生成對應`Makefile`文件也不會將對應`*.moc`文件加入編譯使得`make`指令編譯報錯。
正確的做法是按照`C++`規範將類的定義寫在`*.h`頭文件中。

`Qt`在編譯項目時默認採用的是`make`編譯，會在編譯時忽略那些未曾改動的文件，
因此有時出現此錯誤時還可以嘗試完全刪除已經存在的二進制文件和編譯中間文件，然後從頭開始重新編譯整個項目。
一般對於此類錯誤的解決辦法是手動運行`qmake`後整個項目重新編譯。

## 關於 `Warning: File XXX has modification time 3.9e+08 s in the future` 警告
通常`Qt`在`make`項目時連續出現類似錯誤(並且呈現出死循環狀態)，一般是項目中的文件時間混亂，
部分文件的時間超過了系統當前的時間造成的。
解決辦法是將項目裏的所有文件`touch`一遍即可。
此外，`make`出現`make: 警告：檢測到時鐘錯誤。您的創建可能是不完整的。`的錯誤提示一般也是類似原因造成的。

## 關於 `qt error: C2001: 常量中有換行符` 錯誤
在`Windows`環境中使用`Qt`+`VC編譯器`並且源碼爲`utf-8`編碼時，需要保留`BOM`，
使用**無BOM的utf-8編碼**會讓編譯器在遇到中文字符時報編碼錯誤，需要將文件編碼的`UTF-8 BOM`選項設置爲`如果編碼是utf-8則添加`。

## 關於 `底層受到操作系統信號而停止` 錯誤
通常情況下，遇到此類問題可能是對空指針進行了操作。

在Qt中，需要注意指針是否已經被初始化，同時，在編寫類的析構方法時也許要慎重，
如果一個指針需要傳遞給其他類使用，則不能在當前類的析構方法中`delete`此指針。

## 關於 `Z-order assignment: XXX is not a valid widget.` 警告
在使用`QtDesigner`拖放控件順序不當時可能會出現此警告，解決方法是刪除對應控件的`<zorder></zorder>`標籤。

## 關於Windows專屬BUG：中文亂碼
在`Windows`系統下，使用`VS`開發`Qt`程序時，即使代碼文件的編碼設置爲`UTF-8`，
並且通過`QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));`顯式設定編碼爲`UTF-8`，依然會出現中文亂碼的問題。

對於少量的中文內容，可以使用`QString::fromLocal8bit(const char*);`方法讓中文內容正常顯示。
對於大量的中文內容，每次出現中文都使用QString的成員方法轉換非常麻煩，可以使用如下宏解決中文編碼問題：

```cpp
#pragma execution_character_set("utf-8")
```

該宏需要特定版本的VS支持，對於`VS2010`，需要安裝`VS2010SP1`更新。`VS2012`不支持該宏，`VS2013`支持。

## 關於 `This application failed to start because it could not find or load the Qt platform plugin "windows".` 運行錯誤
在使用非安裝版本的Qt或是系統中未安裝Qt時啓動Qt程序可能會遇到此錯誤提示，原因是未能加載Qt的運行時動態鏈接庫。
需要將Qt安裝目錄下的`...\plugins\platforms`文件夾複製到需要執行的程序所在的目錄。
直接將`platforms`文件夾中的dll複製出來是沒有效果的。

## 關於 `找不到Qt5Core.dll` 運行錯誤
在已經安裝了`Qt`的機器上出現此錯誤，一般爲Qt的**環境變量**未正確配置。
需要創建環境變量`QTDIR`，綁定的位置爲`Qt`的`Main`目錄。
需要將`%QTDIR%\bin`加入`PATH`環境變量中。

## 關於 `Cannot start the terminal emulator "xterm", change the setting in the Environment options.` 運行錯誤
此錯誤在`Linux/Unix`環境下可能出現，`QtCreator`在項目選項中默認勾選了`Run in terminal`，此選項需要一個兼容`QtCreator`的終端，默認使用`xterm`。
若開啓此選項需要安裝`xterm`或其它`QtCreator`兼容的終端，未安裝`xterm`或終端運行指令配置不正確則會出現錯誤。
可以在`Projects => [Config_name] => Run`選項中取消`Run in terminal`的勾選，則不會出現此錯誤。
