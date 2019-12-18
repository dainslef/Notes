<!-- TOC -->

- [基礎類型](#基礎類型)
	- [n進製表示](#n進製表示)
	- [2進制數據流](#2進制數據流)
- [容器類型](#容器類型)
	- [list (列表)](#list-列表)
	- [tuple (元組)](#tuple-元組)
	- [dict (字典)](#dict-字典)
	- [set (集合)](#set-集合)
	- [生成容器](#生成容器)
	- [切片](#切片)
- [變量類型](#變量類型)
	- [查看變量類型](#查看變量類型)
	- [判斷變量是否屬於某種類型](#判斷變量是否屬於某種類型)
- [decorator (裝飾器)](#decorator-裝飾器)
	- [定義裝飾器](#定義裝飾器)
	- [裝飾有參函數](#裝飾有參函數)
	- [裝飾器參數](#裝飾器參數)
- [OOP](#oop)
	- [實例類成員](#實例類成員)
	- [靜態類成員](#靜態類成員)
	- [類方法](#類方法)
	- [屬性](#屬性)
	- [隱含參數](#隱含參數)
	- [私有成員](#私有成員)
	- [繼承](#繼承)
	- [一些特殊的內置成員](#一些特殊的內置成員)
- [range() 函數](#range-函數)
- [變量作用域](#變量作用域)
	- [global 關鍵字](#global-關鍵字)
	- [nonlocal 關鍵字](#nonlocal-關鍵字)
- [generator (生成器)](#generator-生成器)
	- [遍歷生成器與獲取生成器的返回值](#遍歷生成器與獲取生成器的返回值)
	- [使用 send() 與生成器進行交互](#使用-send-與生成器進行交互)
- [與 C/C++ 等常見語言的基本語法差異](#與-cc-等常見語言的基本語法差異)
- [Socket API](#socket-api)
	- [創建 Socket](#創建-socket)
	- [TCP 服務端](#tcp-服務端)
	- [UDP 服務端](#udp-服務端)
	- [客戶端](#客戶端)
- [包管理器 pip](#包管理器-pip)
	- [安裝和配置 pip](#安裝和配置-pip)
	- [鏡像源](#鏡像源)
	- [常用操作](#常用操作)
	- [包依賴檢查與清理](#包依賴檢查與清理)
- [文檔瀏覽](#文檔瀏覽)
- [PEP8 編碼規範總結](#pep8-編碼規範總結)
	- [代碼編排](#代碼編排)
	- [空格使用](#空格使用)
	- [命名規範](#命名規範)
	- [註釋規範](#註釋規範)

<!-- /TOC -->



# 基礎類型
`Python`爲**強類型**語言，不同數據類型之間需要顯式轉換。

基礎類型有：

- `int、float` 數值類型，整數、小數
- `chr、str` 字符、字符串
- `bool` 布爾類型，取值`True/False`

進行強制類型轉換的語法類似`C++`，以函數的語法調用類型即可。

轉化數字到字符串：

```py
>>> data = str(100)
>>> type(data)
<class 'str'>
>>> data
'100'
```

轉化數字到對應`ASCII`碼的數值：

```py
>>> data = chr(65)
>>> data
'A'
```

轉換數值到布爾類型：

```py
>>> b = bool(100)
>>> b
True
>>> b = bool(0)
>>> b
False
>>> b = bool(-100)
>>> b
True
```

## n進製表示
在`Python`中2進制/8進制/16進制的表示方式：

```py
# 2進制，0b做前綴
>>> 0b1000001
65
# 8進制，0o做前綴
>>> 0o101
65
# 16進制，0x做前綴
>>> 0x41
65
```

使用`chr()`將數值視爲`ASCII`碼轉換爲字符，使用`ord()`將字符轉換爲`ASCII`碼：

```py

>>> c = chr(0x41)
>>> c
'A'
>>> ord(c)
65
```

使用`bin()`、`oct()`、`str()`、`hex()`可以分別獲取數值對應的2進制、8進制、10進制、16進制文本：

```py
>>> bin(65)
'0b1000001'
>>> oct(65)
'0o101'
>>> str(65)
'65'
>>> hex(65)
'0x41'
```

## 2進制數據流
在Python中，Socket中發送2進制流需要使用`bytes`或`bytearray`格式進行包裝。

- `bytes`和`bytearray`使用列表(`list`)或數值構造。
	- 使用數值構造時，表示創建一個字節數爲指定數值的空二進制流。
	- 使用列表構造時，用於構造`bytes/bytearray`的列表中每一個成員必須爲`0 ~ 255`之間的數值。
- `bytes/bytearray`都支持通過索引讀取。
- `bytes/bytearray`區別在於`bytes`內容不可變，`bytearray`內容可被修改。

如下代碼所示：

```py
# 以數值創建指定字節數的bytes/bytearray
>>> a = bytes(5)
>>> a
b'\x00\x00\x00\x00\x00'
>>> b = bytearray(5)
>>> b
bytearray(b'\x00\x00\x00\x00\x00')

# 以列表初始化bytes/bytearray
>>> c = bytes([0x41, 0x61])
>>> c
b'Aa'
>>> d = bytearray([0x41, 0x61])
>>> d
bytearray(b'Aa')

# 索引獲取
>>> c[0]
65
>>> d[0]
65

# 索引賦值
>>> c[0] = 0x63
Traceback (most recent call last):
	File "<stdin>", line 1, in <module>
TypeError: 'bytes' object does not support item assignment
>>> c
b'Aa'
>>> d[0] = 0x65
>>> d
bytearray(b'ea')
```

`bytes/bytearray`類型可以通過`decode()`成員方法解碼成普通字符串：

```py
>>> c.decode()
'Aa'
>>> c.decode()
'Aa'
```



# 容器類型
`Python`中的常見容器類型有：

- `tuple` 元組，不可變有序集合
- `list` 列表，可變有序集合
- `set` 集合，不可變
- `dict` 字典，保存鍵值對的集合

## list (列表)
`list`是一個**有序集合**，可以容納各類數據，並能隨意添加和刪除。
`list`中的數據可以是另一個`list`，訪問方式類似**二維數組**。

定義一個`list`：

```py
>>> l = ['first', 'second']
>>> type(l)
<class 'list'>
```

取出`list`中指定下標的內容(下標可以爲負數，即逆序取出內容)：

```py
>>> l[0]
'first'
```

計算`list`的長度：

```py
>>> len(l)
2
```

向list尾部添加內容：

```py
>>> l.append('third')
>>> l
['first', 'second', 'third']
```

向指定位置添加內容：

```py
>>> l.insert(0, 'one') # 在list表首添加字符串"one"
['one', 'first', 'second', 'third']
```

刪除指定位置的數據：

```py
>>> l.pop(0) # 刪除list表首的數據，不寫參數時默認刪除list最後一個數據
>>> l
['first', 'second', 'third']
```

替換指定位置的數據：

```py
>>> l[0] = [1, 2, 3] # 將list表首的數據替換爲另一個list：[1, 2, 3]
>>> l
[[1, 2, 3], 'second', 'third']
```

反轉列表：

```py
>>> l.reverse()
>>> l
['third', 'second', [1, 2, 3]]
```

列表可使用`+=`運算符追加新的列表，示例：

```py
>>> l = [1, 2, 3]
>>> l += [4]
>>> l
[1, 2, 3, 4]
```

列表不能使用`+=`操作符添加單個元素，會拋出異常：

```py
>>> l = [1, 2, 3]
>>> l += 4
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: 'int' object is not iterable
```

使用`+=`添加`str`類型時，`str`會被拆解爲包含多個`char`的列表進行插入，示例：

```py
>>> s = []
>>> s += "abc"
>>> s
['a', 'b', 'c']
```

## tuple (元組)
`tuple`與`list`類似，但`tuple`中的數據**不可修改**，因此沒有`append()`、`insert()`、`pop()`之類的方法。
`tuple`可以像數組一樣通過下標訪問，但不能對其賦值：

```py
>>> t = (1, 2, 3)
>>> type(t)
<class 'tuple'>
>>> t[2]
3
>>> t[2] = 10
Traceback (most recent call last):
File "<stdin>", line 1, in <module>
TypeError: 'tuple' object does not support item assignment
```

定義一個至少有一個元素的`tuple`時，需要寫成：

```py
>>> t = (1, )
```

逗號**不能省略**，這是爲了**消歧義**(防止與數學括號相混淆)。

若`tuple`的成員是一個`list`，則`list`內容依然**可變**(`tuple`只保證對元組成員的引用不變，
但成員本身的內容是否可變由成員自身的類型決定)。

## dict (字典)
`dict`使用`鍵-值`(key-value)存儲，類似於`Java`中的`Map`，擁有很快的查找速度。
相對於`list`，`dict`擁有更快的查找刪除速度，而且不會隨着`dict`內容的增加而減慢查找刪除速度，
但`dict`內存開銷更大(空間換時間)。在`dict`中，`key`是**唯一、不能改變**的，`value`則沒有此限制。
`dict`根據`key`的值來計算對應`value`的位置(hash算法)，因此`key`是不能改變的，而可變對象`list`不能作爲`key`。

定義`dict`使用大括號：

```py
>>> d = { 'first': 'one', 'second': 2, 'third': 3 }
>>> type(d)
<class 'dict'>
```

取出dict中的某個內容：

```py
>>> d['first']
'one'
```

改變指定key的value：

```py
>>> d['first'] = 1
>>> d
{'first': 1, 'second': 2, 'third': 3}
```

可以判斷一個list中是否存在某個key：

```py
>>> 'first' in dict
True
```

向dict中添加數據類似於操作數組：

```py
>>> d['new'] = 4
>>> d
{'first': 1, 'second': 2, 'third': 3, 'new': 4}
```

刪除`dict`中的內容使用`pop(key)`成員方法，刪除了某個`dict`中的某個`key`，則該`key`的`value`也會隨之被刪除：

```py
>>> d.pop('new')
>>> d
{'first': 1, 'second': 2, 'third': 3}
```

## set (集合)
`set`是一組**沒有**`value`的`key`的集合，`set`中的內容是**不可重複**的。
定義一個`set`：

```py
>>> s = { 1, 2, 3, 3 } #即使在定義時輸入重複的元素，解釋器也會將其自動忽略
>>> s
{1, 2, 3}
```

使用`add(key)`成員函數對給`set`添加`key`：

```py
>>> s.add('test')
>>> s
{1, 2, 3, 'test'}
```

## 生成容器
在定義容器的表達式中，可以直接加入`for`、`if`語句等作爲條件生成容器內容。

```py
>>> l = [i for i in range(0, 10) if i > 5]
>>> l
[6, 7, 8, 9]
>>> s = { i for i in range(0, 10) }
>>> s
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
>>> d = { i: i + 1 for i in range(0, 10) if i % 3 == 0 }
>>> d
{0: 1, 9: 10, 3: 4, 6: 7}
```

## 切片
Python中的`list`、`tuple`、`str`等類型支持**切片**操作。
切片語法：

```py
var[start:end:step]
```

- `start`爲起始下標，`end`爲結束下標，`step`爲步進數(默認爲`1`)。
- 範圍爲`[start, end)`，即獲取下標`start`到`end - 1`之間的內容。
- 下標`start`和`end`的值可以超過容器界限，等價於一直取值到容器的邊界。

示例：

```py
>>> t = (1, 2, 3, 4, 5)
# 獲取下標1到3範圍之間的內容
>>> t[1:4]
(2, 3, 4)
# 獲取下標1及其之後的內容
>>> t[1:]
(2, 3, 4, 5)
# 獲取下標4之前的內容
>>> t[:4]
(1, 2, 3, 4)
# 索引超過容器的邊界則相當於取到容器結束
>>> t[:100] #等價於 t[:]
(1, 2, 3, 4, 5)
# 逆序索引切片
>>> t[-4:-1]
(2, 3, 4)
# 返回以2爲間隔的內容
>>> t[::2]
(1, 3, 5)
# 返回以3爲間隔的內容
>>> t[::3]
(1, 4)
# 返回以-1爲間隔的內容(倒序輸出)
>>> t[::-1]
(5, 4, 3, 2, 1)
```

Python中變量皆爲**引用**，使用賦值操作符只是複製引用，但使用切片能夠實現容器**值複製**：

```py
>>> l0 = [1, 2, 3]
>>> l1 = l0
>>> l1[0] = 100
>>> l1
[100, 2, 3]
>>> l0 # 引用複製，l1內容改變，l0也會隨之改變
[100, 2, 3]
>>> l2 = l0[:] # 切片重新生成容器，非引用複製
>>> l2[0] = 1000
>>> l2
[1000, 2, 3]
>>> l0 # l0的值並未發生變化
[100, 2, 3]
```



# 變量類型
Python屬於隱式類型語言，不必顯式指定類型的簽名(在`Python 3.6`之前Python不能指定類型類型簽名)；
同時Python屬於強類型語言，變量不會隱式的轉換類型。

## 查看變量類型
使用`type()`函數可以查看變量類型：

```py
>>> a = lambda x: x + 2
>>> type(a)
<class 'function'>
>>> b = {'first': 1, 'second': 2, 'third': 3}
>>> type(b)
<class 'dict'>
```

## 判斷變量是否屬於某種類型
使用`isinstance()`函數可以判斷某個變量是否是某種類型：

```py
>>> isinstance(100, int)
True
```

也可以使用`is`操作符判斷類型：

```py
>>> type(100) is int
True
```

比較類實例時，`is`操作符與`isinstance()`函數邏輯不同：

- `isinstance()`只要實例類型是從比較類型中派生出的，返回`True`。
- `is`只有實例類型與比較類型完全匹配才返回`True`。

```py
>>> class A: pass
>>> class B(A): pass
>>> b = B()
>>> type(b) is B
True
>>> type(b) is A
False
>>> type(b) is object
False
>>> isinstance(b, B)
True
>>> isinstance(b, A)
True
>>> isinstance(b, object)
True
```



# decorator (裝飾器)
裝飾器能夠爲已有的函數附加額外的功能。
裝飾器也是設計模式中的一種，通過組合的方式來複用已有的功能。

## 定義裝飾器
在Python中，裝飾器本質上就是一個普通的函數，接受一個函數作爲輸入參數，同時返回一個裝飾後的函數。
裝飾器基本的結構示例：

```py
def decorator_name(func_name):
	def wrapper(): # 定義一個局部函數作爲包裝函數
		# code before...
		func_name() # 調用被裝飾的函數
		# code after...
	return wrapper # 返回裝飾後的函數
```

在函數定義前加上`@裝飾器名`即會使用裝飾器來包裝定義的函數，示例：

```py
@decorator_name
def func_name():
	# code...
```

實際上，Python中使用裝飾器只是一個**語法糖**，實際相當於調用裝飾器函數產出一個新的函數。
上述代碼等價於：

```py
def func_name():
	# code...
func_name = decorator_name(func_name)
```

一個基本的裝飾器應用示例：

```py
from time import clock

# 打印被裝飾的函數運行消耗的時間
def time_cost(func):
	def wrapper():
		start = clock()
		func()
		end = clock()
		print("Time used: %f seconds" % (end - start))
	return wrapper

# 將要使用的裝飾器的名稱寫在函數定義前
@time_cost
def show(): # 裝飾器是語法糖，方法show的屬性"__name__"返回值爲"wrapper"(即裝飾器內的包裝函數的名字)
	print("Call method:", show.__name__)

show()
```

輸出結果：

```
Call method: wrapper
Time used: 0.000052 seconds
```

## 裝飾有參函數
對於參數不爲空的函數，定義裝飾器函數時，需要修改包裝函數的參數表，爲其添加參數。
如果能確定被裝飾函數的函數原型，可以將包裝函數的參數數量設置爲與被裝飾函數相同，示例：

```py
from time import clock

def time_cost(func):
	# 包裝函數的參數表與被裝飾的show()函數相同
	def wrapper(text):
		start = clock()
		func(text)
		end = clock()
		print("Time used: %f seconds" % (end - start))
	return wrapper

@time_cost
def show(text):
	print("Call show(): ", text)

show("Test arg")
```

輸出結果：

```
Call show(): Test arg
Time used: 0.000052 seconds
```

若被裝飾的函數是未知的，則需要將包裝函數的參數表定義爲接收可變參數。
定義一個輸出傳入參數種類和內容的裝飾器，示例：

```py
def decorator(func):

	def wrapper(*args, **kwargs):

		print("Print keyword parameters:")
		for arg in args:
			print("Value:", arg)

		print("Print positional parameters:")
		for key in kwargs:
			print("Key:", key, "Value:", kwargs[key])

		print()
		func(*args, **kwargs) # 即使函數的參數表是確定的，依然可以使用可變參數的形式傳入參數

	return wrapper

@decorator
def show(num1, num2, num3, num4):
	print("Call method:", show.__name__)
	print("Num1 is: %d" % num1)
	print("Num2 is: %d" % num2)
	print("Num3 is: %d" % num3)
	print("Num4 is: %d" % num4)

show(1, 2, num3 = 3, num4 = 4)
```

輸出結果：

```
Print keyword parameters:
Value: 1
Value: 2
Print positional parameters:
Key: num4 Value: 4
Key: num3 Value: 3

Call method: wrapper
Num1 is: 1
Num2 is: 2
Num3 is: 3
Num4 is: 4
```

## 裝飾器參數
裝飾器本身也可以帶有參數。
定義帶有參數的裝飾器需要在包裝函數外再封裝一層。
基本樣式示例：

```py
def decorator_name(decorator_args):
	# code...
	def decorator_wrapper_name(func_name):
		# code...
		def wrapper(*arg, **kwargs):
			# code...
			func_name(*arg, **kwargs)
			# code...
		return wrapper
	return decorator_wrapper_name
```

在實際編碼中裝飾器可以根據傳入的參數來提供不同的裝飾功能，示例：

```py
from time import clock

# 第一層裝飾器函數用於包裝裝飾器本身的參數，返回真正的裝飾器函數
def decorator(decorator_arg = ""):

	# 真正的裝飾器函數
	def decorator_wrapper(func):

		# 包裝函數
		def wrapper(*args, **kwargs):
			# 判斷不同的裝飾器參數，實現不同的裝飾器功能
			if (decorator_arg == "Args"):
				print("Mode: Print Args", end = "\n\n")
				print("Print keyword parameters:")
				for arg in args:
					print("Value:", arg)
				print("Print positional parameters:")
				for key in kwargs:
					print("Key:", key, "Value:", kwargs[key])
				print()
				func(*args, **kwargs)
			elif (decorator_arg == "Time_cost"):
				print("Mode: Time Cost", end = "\n\n")
				start = clock()
				func(*args, **kwargs)
				end = clock()
				print("Time used: %f" % (end - start))
			else:
				print("Mode: Print Prefix", end = "\n\n")
				print("Use prefix.")
				func(*args, **kwargs)
			print()

		return wrapper

	return decorator_wrapper # decorator_wrapper纔是真正接收函數作爲參數的裝飾器函數

def show(num1, num2, num3, num4):
	print("Call method:", show.__name__)
	print("Num1 is: %d" % num1)
	print("Num2 is: %d" % num2)
	print("Num3 is: %d" % num3)
	print("Num4 is: %d" % num4)

# 使用不同的裝飾器參數來裝飾同一個函數，實現不同的功能
@decorator()
def show1(num1, num2, num3, num4):
	show(num1, num2, num3, num4)
@decorator("Time_cost")
def show2(num1, num2, num3, num4):
	show(num1, num2, num3, num4)
@decorator("Args")
def show3(num1, num2, num3, num4):
	show(num1, num2, num3, num4)

show1(1, 2, num3 = 3, num4 = 4)
show2(1, 2, num3 = 3, num4 = 4)
show3(1, 2, num3 = 3, num4 = 4)
```

輸出結果：

```
Mode: Print Prefix

Use prefix.
Call method: show
Num1 is: 1
Num2 is: 2
Num3 is: 3
Num4 is: 4

Mode: Time Cost

Call method: show
Num1 is: 1
Num2 is: 2
Num3 is: 3
Num4 is: 4
Time used: 0.000020

Mode: Print Args

Print keyword parameters:
Value: 1
Value: 2
Print positional parameters:
Key: num4 Value: 4
Key: num3 Value: 3

Call method: show
Num1 is: 1
Num2 is: 2
Num3 is: 3
Num4 is: 4
```



# OOP
與傳統的OOP語言類似，Python中的class具有**獨立**的**變量作用域**。
相比傳統的OOP語言如Java、C++等，Python對於OOP並沒有完整的支持，
在Python中**不支持**函數重載、**不支持**定義保護對象。

## 實例類成員
在Python中，類作用域內**不包含**隱式的對象引用(即類作用域中沒有類似C++中的`this`指針或是Java中的`this`引用)，
而是需要在成員函數的參數中傳入對象實例。

- 每個類的實例成員函數的第一個參數必須爲當前類的實例，通常使用`self`來命名。
- 通過類實例調用成員函數時，第一個參數(類實例參數)爲隱含參數，不用寫明。
- 即使在類內部，實例成員變量、實例成員函數也必須通過對象實例來調用。
- 在類內非函數作用域中，直接使用變量名相當於定義類的靜態成員變量。
- 在成員函數作用域中，直接使用變量名相當於在函數內部創建了一個局部變量。

示例：

```py
class Test:

	def __init__(self, num1, num2):
		self.num1 = num2 # 實例變量定義無需單獨聲明，在構造函數中定義即可在整個類中使用
		self.num2 = num1

	def show(self): # 實例成員函數第一個參數爲對象實例
		print(self.num1, self.num2) # 即使在類內部訪問類的實例成員變量也需要通過實例對象
		# 直接訪問num1、num2如使用語句 print(num1) 則會得到"num1未定義"的錯誤提示

test = Test(1, 2)
test.show()
```

輸出結果：

```
2 1
```

## 靜態類成員
在Python中同樣可以定義類的靜態成員，與傳統的OOP語言類似，訪問靜態成員使用`類名.靜態成員名`即可。

定義靜態成員函數，需要注意：

- 類的靜態成員函數在定義前需要加裝飾器`@staticmethod`。
- 靜態成員函數**沒有**隱含參數，因此**不需要也不能**將第一個參數設定爲類的實例。
- 同一個類的靜態成員函數**不能**與實例成員函數同名。

定義類的靜態成員變量，需要注意：

- 定義類的靜態成員變量可以直接將變量名寫在**類內非函數作用域**中(不需要也不能使用類名，會報錯)。
- Python爲動態語言，可以在運行期間創建成員變量，可以在函數作用域或全局作用域使用`類名.靜態變量名`創建靜態成員變量。
- 即使在類的內部，訪問靜態成員同樣需要使用類名而不能直接調用。
- 靜態成員變量可以與實例成員變量同名。
- 靜態成員同樣可以通過類實例調用。
- 當一個類實例中存在同名的靜態成員變量與實例成員變量時，優先調用實例成員變量。

如下代碼所示：

```py
class Test:

	num1 = 100
	num2 = 200 # 在類作用域中定義靜態成員變量num1，num2

	def __init__(self, num1, num2):
		self.num1 = num2
		self.num2 = num1 # 定義實例成員變量num1，num2
		Test.num3 = num2
		Test.num4 = num1 # 在構造函數中定創建態成員變量num3，num4

	def show(self):
		print(self.num1, self.num2)
		Test.static_show()	# 即使在類內部，訪問自身類的靜態成員函數也需要加類名

	@staticmethod
	def static_show(): # 靜態成員函數的定義前加裝飾器@staticmethod
		print(Test.num1, Test.num2, Test.num3, Test.num4)

# print(Test.num3) # 報錯，Test類的__init__()一次都沒有被調用，此時Test.num3不存在
test = Test(1, 2)
test.show()
test.static_show() # 靜態成員函數也能夠被實例訪問
```

## 類方法
類方法在定義時需要添加裝飾器`@classmethod`，類方法在其他主流OOP編程語言(Java、C++、C#等)中沒有對應的概念。

- 類方法的隱含參數是類的**類型**，而非類的實例，通常使用`cls`來命名。
- 類方法可以通過類實例或是類名調用。
- 類方法只能訪問靜態成員(即使通過**實例**調用)。

如下代碼所示：

```py
class Test:

	num = 100

	def __init__(self, num):
		self.num = num

	@classmethod
	def show(cls, str):
		print(str, cls.num, Test.num)

t = Test(200)
t.show("Called by t.show()") # 通過實例與通過類名的調用結果完全相同，訪問都是靜態變量
Test.show("Called by Test.show()")
```

輸出結果：

```
Called by t.show() 100 100
Called by Test.show() 100 100
```

## 屬性
Python中同樣支持`屬性`，`屬性`的概念與C#中類似。
Python中的屬性實際上是一組特定簽名的`getter`、`setter`方法，用以有限制地存取某個私有變量，
`getter`、`setter`方法被定義爲`屬性`之後，便能夠以類似訪問成員變量的語法來調用。

- 使用 *property()* 函數定義屬性

	可以使用`property()`函數來綁定屬性。
	`property()`函數的基本結構如下：

	```py
	property_name = property(fget = None, fset = None, fdel = None, doc = None)
	```

	函數依次接收`getter`、`setter`、`deleter`和屬性描述作爲參數，返回值賦值的變量名稱即爲屬性的名稱。
	示例：

	```py
	class Num:

		def __init__(self, value):
			self.__num = value

		# getter函數
		def get_num(self):
			return self.__num

		# setter函數
		def set_num(self, value):
			self.__num = value

		# deleter函數
		def del_num(self):
			del self.__num

		# 使用property()函數綁定屬性讀寫函數，返回變量num計委屬性名稱
		num = property(get_num, set_num, del_num, doc = None)

	n = Num(10)
	print(n.num) # 使用用讀屬性，實際調用get_num()
	n.num = 100 # 使用寫屬性，實際調用set_num()
	print(n.num)
	del n.num # 刪除成員，實際調用del_num()
	```

	若需定義`只讀屬性`，則調用`property()`函數時`fset`參數取`None`即可。

- 使用**裝飾器**定義屬性

	在`Python 2.6`之後，支持使用**裝飾器**語法定義屬性。

	- 使用`@property`裝飾器裝飾`getter`函數，同時該函數的名稱即爲**屬性名**。
	- 使用`@屬性名.setter`裝飾器裝飾`setter`函數。
	- 使用`@屬性名.deleter`裝飾器裝飾`deleter`函數。
	- 使用裝飾器語法來定義屬性時，`getter`、`setter`、`deleter`函數的函數名都需要與屬性名**相同**。

	上例中的代碼等價於：

	```py
	class Num:

		def __init__(self, value):
			self.__num = value

		@property
		def num(self):
			return self.__num

		@num.setter
		def num(self, value):
			self.__num = value

		@num.deleter
		def num(self):
			del self.__num

	n = Num(10)
	print(n.num)
	n.num = 100
	print(n.num)
	del n.num
	```

## 隱含參數
本質上，Python對於成員方法的區分實際上是對於隱含參數的處理方式不同。
對於一個實例方法，如下調用：

```py
instance.func_name(args...)
```

實際上等價於：

```py
class_name.func_name(isinstance, args...)
```

Python解釋器只是將實例本身填充到了實例方法的第一個參數上而已，因而實例方法也可以以靜態方法的語法被調用。
在C#中也存在類似的語法轉換，被稱爲**擴展方法**。

添加了裝飾器`@staticmethod`或`@classmethod`的方法便不再能夠進行這種轉換，如下代碼所示：

```py
class Test:

	num = 100

	def __init__(self, num):
		self.num = num

	def call(self):
		print("instance_method:", self.num)

	@classmethod
	def cls_call(cls):
		print("class_method:", cls.num)

	@staticmethod
	def static_call(self):
		print("static_method:", self.num)

	def no_arg():
		print("no_arg_method:", Test.num)

t = Test(200)

t.call() # 調用實例成員方法
Test.call(t) # 以靜態方法的語法調用實例成員方法，調用成功，輸出相同

Test.cls_call() # 通過類名調用類方法
t.cls_call() # 通過調用實例調用類方法，輸出與通過類名調用相同
# Test.cls_call(t) # 報錯，提式參數過多

# t.static_call() # 報錯，提示缺少參數"slef"
t.static_call(t)
Test.static_call(t)

Test.no_arg()
# t.no_arg() # 報錯，提示參數過多
```

輸出結果：

```
instance_method: 200
instance_method: 200
class_method: 100
class_method: 100
static_method: 200
static_method: 200
no_arg_method: 100
```

通過以上結果可以得出：

- 實例方法的調用語法實際是語法糖，普通的實例方法可以通過類名語法進行調用。
- 通過普通語法調用實例方法時，解釋器會將實例作爲隱含參數。
- 使用了`@staticmethod`裝飾器之後，通過實例調用該靜態方法，解釋器不再會將實例作爲隱含參數。
- 使用了`@classmethod`裝飾器之後，通過實例調用該類方法，解釋器依然將實例視爲類名處理。
- 參數爲空的成員方法，即使沒有添加任何裝飾器，也只能通過類名訪問。

## 私有成員
`Python`類中默認成員的訪問屬性爲公有，在`Python`中不能定義保護成員，但可以定義私有成員。

在命名類的成員時，以`__`開頭的成員即爲**私有成員**，不能在類的外部被訪問。
如下代碼所示：

```py
class Test:

	__num = 100

	def __init__(self, num):
		self.__num = num
		Test.__num = num

	def show(self):
		print(self.__num, Test.__num)

test = Test(1)
test.show() # 調用show()成員函數正確打印私有成員內容
print(test.__num, Test.__num) # 直接輸出私有成員內容報錯，錯誤提示 " 'Test'對象沒有屬性__num "
```

在`CPython`的實現中，私有變量並非真正被隱藏，僅僅是解釋器對私有變量的名稱做了一些改動使得外界無法訪問。
以`__xxx`爲名的私有成員的實際名稱被修改爲`_類名__xxx`，使用改動後的名稱可以正常訪問私有成員。

上個例子稍作修改即可訪問到私有變量：

```py
class Test:

	__num = 100

	def __init__(self, num):
		self.__num = num
		Test.__num = num

	def show(self):
		print(self.__num, Test.__num)

test = Test(1)
test.show()
print(test._Test__num, Test._Test__num) # 需要注意的是，不同的Python解釋器重命名的方式可能略有不同
```

輸出結果：

```
1 1
1 1 # 正常獲得了私有成員變量的內容
```

## 繼承
繼承一個類時，若自定義構造函數`__init__()`，則需要在構造函數中調用父類構造函數。

調用父類構造函數時，可以使用以下方式：

- `Parent_name.__init__(self, args...)`
- `super(Parent_name, self).__init__(args...)`
- `super().__init__(self, args...)`

示例：

```py
class Parent:
	def __init__(self, a, b):
		self.a = a
		self.b = b

class Child(Parent):
	def __init__(self, a, b):
		# 以下三種方式皆可
		# Parent.__init__(self, a, b)
		# super(Parent, self).__init__(a, b)
		super().__init__(a, b)
```

## 一些特殊的內置成員
在Python中，有一類特殊的類成員，命名以`__`開始也以`__`結束，這一類成員並**不是**私有成員，可以直接被訪問。
系統定義的屬性與方法：

```py
Class.__doc__ # 類型幫助信息 'Class Doc.'
Class.__name__ # 類型名稱 'Class'
Class.__module__ # 類型所在模塊 '__main__'
Class.__bases__ # 類型所繼承的基類 (<type 'object'>,)
Class.__dict__ # 類型字典，存儲所有類型成員信息。 <dictproxy object at 0x00D3AD70>
Class().__class__ # 類型 <class '__main__.Class'>
Class().__module__ # 實例類型所在模塊 '__main__'
Class().__dict__ # 對象字典，存儲所有實例成員信息。 { 'i': 1234 }
```

一些常用的特殊方法：

```py
t = T() # 實際調用 t.__init__() 構造函數
del t # 實際調用 t.__del__() 析構函數
repr(t) # 實際調用 t.__repr__() 將對象轉成字符串顯示(適合解釋器閱讀)
str(t) # 實際調用 t.__str__() 將值轉化爲字符串形式(適合人閱讀)，print()打印會調用對象的__str__()函數
format(t, format_spec) # 實際調用 t.__format__(format_spec) 格式化字符串的值
t() # 實際調用 t.__call__() 提供與函數類似的行爲
len(t) # 實際調用 t.__len__()
t[key] # 實際調用 t.__getitem__(key) 訪問索引值
t[key] = value # 實際調用 t.__setitem__(key, value) 索引賦值
t.member # 實際調用 t.__getattr__(menber) 訪問成員
t.member = value # 實際調用 t.__setattr__(member, value) 成員賦值
t < k # 實際調用 t.__it__(k) 小於運算符
t > k # 實際調用 t.__gt__(k) 大於運算符
t + k # 實際調用 t.__add__(k) 加號運算符
```


# range() 函數
`range(start, stop, step)`函數接收三個參數，產生`[start, end)`範圍的數字，以`step`爲步進。

其中`start`、`step`參數參數帶有默認值，默認情況下`start`爲**0**，`step`爲**1**。

`Python 2`中，`range()`返回類型是`list`。
`Python 3`中，`range()`返回類型是`range`，得到`list`需要使用`list(xxx)`顯式地進行強制類型轉換。

`range()`函數一般用於`for`循環遍歷，例如：

```py
for a in range(5):
	print(a, end = ' ')
```

輸出結果：

```
0 1 2 3 4
```



# 變量作用域
在`Python`中，定義變量與賦值變量語法相同，這一設計導致局部作用域下訪問外部變量時會有語義衝突。

## global 關鍵字
在局部作用域下，直接對全局變量賦值，解釋器會認爲你創建了一個與全局變量同名的**局部變量**，該變量在函數結束之後會被釋放。
在局部作用域下，訪問全局變量需要使用`global`關鍵字，聲明使用全局變量而不是創建新的變量。

示例：

```py
num = 0

def set_num():
	num = 1

def set_global_num():
	global num
	num = 1

print("num:", num)
set_num()
print("num after set_num():", num)
set_global_num()
print("num after set_global_num():", num)
```

輸出結果：

```
num: 0
num after set_num(): 0
num after set_global_num(): 1
```

## nonlocal 關鍵字
`global`關鍵字解決了局部作用域訪問全局變量的問題，但不能解決閉包函數訪問外部局部變量的問題。
在`Python 3`中，引入了`nonlocal`關鍵字用於訪問外部非全局作用域的變量。

示例：

```py
def func():

	num = 0

	def set_num():
		num = 1

	def set_nonlocal_num():
		nonlocal num	# 聲明使用外部局部作用域的變量num，而不是創建新的局部變量num
		num = 1

	print("num:", num)
	set_num()
	print("num after set_num():", num)
	set_nonlocal_num()
	print("num after set_nonlocal_num():", num)

func()
```

輸出結果：

```
num: 0
num after set_num(): 0
num after set_nonlocal_num(): 1
```

`nonlocal`關鍵字在上一級局部作用域中未找到變量時會向更外層的局部作用域中查找，示例：

```py
def func():

	num = 0

	def set_nonlocal_num():
		def set_num():
			nonlocal num # 會一直查找外部局部作用域中名爲num的變量，不僅僅在上一層作用域
			num = 1
		set_num()

	print("num:", num)
	set_nonlocal_num()
	print("num after set_nonlocal_num():", num)

func()
```

輸出結果：

```
num: 0
num after set_nonlocal_num(): 1
```



# generator (生成器)
使用生成器可以方便的生成一串特定的值。

- 在函數定義中使用關鍵字`yield`則該函數變成爲一個**生成器**。
- 執行生成器函數**不會**得到該函數的返回值，而是得到一個生成器對象。
- 對生成器對象使用`next(生成器對象)`方法會執行一次生成器，執行到`yield`關鍵字時，方法暫停，並返回`yield`語句的返回值。
	再次調用`next()`方法會從上次`yield`結束的語句繼續開始執行，直到再次運行到`yield`語句。

在`Python 2`中，可以使用`生成器對象.next()`的方式進行生成器迭代，
在`Python 3`中，可以使用`生成器對象.__next()__`，作用與`next(生成器對象)`相同。

如下代碼所示：

```py
def get():
	for i in range(0, 3):
		yield i
	return 100

a = get()
print(type(a))
print(next(a))
print(a.__next__())
print(a.__next__())
```

輸出結果：

```py
<class 'generator'>
0
1
Traceback (most recent call last):
File "test.py", line 10, in <module>
	print(a.__next__())
StopIteration: 100
```

## 遍歷生成器與獲取生成器的返回值
除了使用`next()`函數來進行生成器迭代外，還可以採用**for循環**的形式。
正常情況下，無法獲得生成器函數的返回值，若需要返回值，則可以捕獲**StopIteration**異常，
通過異常對象獲取生成器函數的返回值。

示例：

```py
def get():
	for i in range(0, 3):
		yield i
	return 100

a = get()
while True:
	try:
		print(next(a))
	except StopIteration as ex:
		print("The return value is:", ex.value)
		break
```

輸出結果：

```
0
1
2
The return value is: 100
```

如果需要將生成器生成的內容添加到容器中，可以使用**列表生成式**，示例：

```py
def get():
	yield 100
	yield 200
	yield 300

g = get()
print([next(g) for i in range(0, 3)])
```

輸出結果：

```
[100, 200, 300]
```

## 使用 send() 與生成器進行交互
當使用`next()`生成器啓動後，便可以使用`生成器對象.send(內容)`向生成器傳遞內容，
`send()`傳遞的內容將作爲`yield`表達式的**返回值**。
`next()`相當於`send(None)`，即`None`爲`yield`表達式的默認返回值。
執行了`send()`函數相當於先執行一次`next()`，然後將`send()`中的參數作爲`yield`的返回值。
首次啓動生成器必須使用`next()`，因爲第一次迭代沒有`yield`表達式參與，以後的每一次迭代都可以使用`send()`代替`next()`。

如下代碼所示：

```py
def get():
	for i in range(0, 3):
		num = yield i
		print(num)

g = get()
next(g)
print(g.send(10))
print(g.send(20))
```

輸出結果：

```
10
1
20
2
```



# 與 C/C++ 等常見語言的基本語法差異
- Python**沒有**自增自減運算符。
- Python中**沒有**`switch`關鍵字。
- Python中的邏輯運算符用直白的英語表示：`and(且)`、`or(或)`、`not(非)`，位運算操作符不變。
- Python比較對象是否相同用`is`、`is not`。
- Python比較是否屬於用`in`、`not in`。
- Python乘方用`**`符號，`2 ** 3`的值是`8`，相當於`2 ^ 3`(數學意義上)。
- Python**沒有**三目運算符，但可以用類似的語句替代。在C語言中的語句`A ? B : C`，
在Python中可寫成`A and B or C`或`B if A else C`。但該語法與三目運算符並不完全等價，
空字符串`''`，數字`0`，空list`[]`，空dict`{}`，空tuple`()`，`None`等在邏輯運算中都被當作假來處理。



# Socket API
`Python`中的`sokcet`模塊對`BSD`的`Socket API`做了基本的封裝，函數調用名稱與`BSD Socket`相同，
但在參數上有所簡化，使之更加易於使用。

## 創建 Socket
`socket`類的構造函數定義爲：

```py
__init__(self, family=<AddressFamily.AF_INET: 2>, type=<SocketKind.SOCK_STREAM: 1>, proto=0, fileno=None)
```

- `family`參數爲協議類型，常見的取值有`AF_INET`(`IPv4`)、`AF_INET6`(`IPv6`)。
- `type`參數爲socket類型，常見的取值有`SOCK_DGRAM`(`UDP`)、`SOCK_STREAM`(`TCP`)。

在`Python`中，`socket()`創建的是`Socket`對象而非文件描述符。

常見用法如下：

```py
# 創建 UDP Socket 對象
udpSock = socket(AF_INET, SOCK_DGRAM)
# 創建 TCP Socket 對象
tcpSock = socket(AF_INET, SOCK_STREAM)
```

## TCP 服務端
對於`TCP`而言，接收數據前需要綁定並監聽端口：

```py
# 綁定端口
tcpSock.bind(("ip地址", 端口號))
# 監聽端口
tcpSock.listen(最大連接數)
```

`TCP`需要使用`accept()`方法顯式接受連接：

```py
# 使用accept()方法等待客戶端連接建立
clientSock, clientAddr = tcpSock.accept()
```

在有用戶建立連接之前，`accept()`方法會一直阻塞。
當成功建立連接後，`accept()`方法返回客戶端socket對象以及客戶端地址。

使用`accept()`方法返回的客戶端socket對象即可接收與發送消息。

## UDP 服務端
`UDP`是無連接的，只需`bind()`綁定端口與主機地址，無需監聽與等待連接，示例：

```py
udpSock.bind(("ip地址", 端口號))
```

`UDP`直接使用自身對象發送與接收消息。

## 客戶端
客戶端在socket對象創建完成後，使用`connect()`方法與服務端連接後即可發送與接收消息：

```py
clientSock.connect(("ip地址", 端口))
```

對於無連接的`UDP`通信方式而言，調用`connect()`方法不是必須的，`UDP`下的`connect()`方法並未真正執行連接操作，
僅僅設置了默認的發送目標端口和目標IP而已。



# 包管理器 pip
`Python`提供了包管理器`pip`用於安裝、管理第三方模塊。

## 安裝和配置 pip
在部分Linux發行版中，`pip`並沒有隨`Python`一併被安裝。
`pip`可以從發行版的軟件源中安裝，也可以下載安裝腳本：

```
$ wget https://bootstrap.pypa.io/get-pip.py
$ sudo python3 get-pip.py //將pip安裝到系統目錄(Linux下需要root權限)
$ python3 get-pip.py --user //將pip安裝到用戶目錄
```

系統目錄下的Python包是所有用戶共享的，用戶目錄下的Python包只有所有者可訪問。

- `Linux`下的`pip`相關特性

	安裝**pip**到系統目錄需要`root`權限，系統`Python`模塊安裝在路徑`/usr/lib/python[version]/site-packages`下，需要`root`權限對其進行寫入操作。
	安裝`Python`模塊到用戶目錄下無需`root`權限，用戶`Python`模塊在路徑`~/.local/lib/python[version]/site-packages`下。
	還會在`~/.local/bin`路徑下生成可執行腳本。

	由發行版自身的包管理器(`apt`、`yum`、`dnf`、`pacman`等)安裝的`Python`模塊也會顯示在`pip list`指令的輸出中。
	系統包管理器安裝的`Python`模塊通常被系統某些組件依賴，嘗試刪除這些包時會收到`DEPRECATION`(反對)，提示這些包是由`distutils`(發行版工具)安裝的，一般情況下，除非必要，不要刪除這些由發行版包管理器安裝的`Python`模塊。

- `macOS`下的`pip`相關特性

	使用**homebrew**安裝`Python`時會自動安裝`pip`，使用`pip`**無需**`root`權限。
	系統`Python`模塊安裝在路徑`/usr/local/lib/python[version]/site-packages/`下。
	用戶`Python`模塊安裝在路徑`~/Library/Python/[version]/lib/python/site-packages`下。
	系統`Python`模塊會在`/usr/local/bin`路徑下生成可執行腳本。
	用戶`Python`模塊會在`~/Library/Python/[version]/bin`路徑下生成可執行腳本。

## 鏡像源
由於`GFW`的存在，`pip`官方源可能無法訪問。
使用國內鏡像源替換官方源，推薦使用`USTC`源，在`.pip/pip.conf`文件中添加內容：

```
[global]
index-url = https://mirrors.ustc.edu.cn/pypi/web/simple
format = columns
```

## 常用操作
`pip`包管理器使用方式類似`Linux`發行版的包管理器，常見操作如下：

```
# pip install [package_name] //安裝包
# pip uninstall [package_name] //移除包
# pip install --upgrade [package_name] //升級指定包
# pip install -U [package_name] //升級指定包，"-U"參數等價於"--upgrade"
$ pip install --user [package_name] //安裝指定包到用戶目錄
$ pip list //列出已安裝的包
$ pip list --outdated //列出可以升級的包
$ pip list --user //列出安裝在用戶目錄的包
$ pip show [package_name] //顯示包的詳細信息
$ pip show --files [package_name] //列出包安裝的文件列表
$ pip help [operate] //查看pip相關操作的幫助信息，如"pip help install"即查看"pip install"指令的所有用法
```

## 包依賴檢查與清理
相比Linux各大發行版的包管理器。`pip`是一個非常**原始**、**簡陋**的包管理器工具。

`pip`的主要缺陷如下：

- 沒有一次性升級所有包的指令。
- 沒有依賴清理功能，卸載一個包時不會清理無用依賴。

清理無用的`pip`包可以安裝工具`pip-autoremove`：

```
$ pip install pip-autoremove
```

`pip-autoremove`的常見操作如下：

```
$ pip-autoremove -l //列出未被使用的依賴(可以被清理的依賴)
$ pip-autoremove -L //列出不被其它包依賴的包(主動安裝的包)
```



# 文檔瀏覽
Python提供了文檔工具`pydoc`。

使用`pydoc`可以方便地查看Python標準庫以及從pip安裝的模塊的對應文檔：

```
$ pydoc -p [port]
```

指定端口號即可使用瀏覽器瀏覽Python文檔。
`port`值取`0`時任意選擇一個可以使用的端口。



# PEP8 編碼規範總結
**PEP**是`Python Enhancement Proposal`的縮寫，即`Python增強建議`。

## 代碼編排
- 以`80`個字符做爲單行界限。
- 優先使用`4`個**空格**做爲縮進，但在使用`Tab`做爲縮進的代碼中，應保持使用`Tab`。
- 代碼換行優先在括號內部換行，也可以使用`\`換行符。
- 在括號內換行時，以其它括號內的元素作爲對齊標準，或者使用懸掛式縮進。
- 在使用懸掛式縮進時，應使用進一步縮進以便於與其它行區分。
- 類定義和頂層函數定義之間空兩行；類中的方法定義之間空一行；函數內邏輯無關段落之間空一行；其他地方儘量不要再空行。
- 不要將多句語句寫在同一行，儘管使用`;`允許。

## 空格使用
總體原則，避免不必要的空格。

- 各種右括號前不要加空格。
- 逗號、冒號、分號前不要加空格。
- 函數的左括號前不要加空格。如`Func(1)`。
- 序列的左括號前不要加空格。如`list[2]`。
- `if`、`for`、`while`語句中，即使執行語句只有一句，也必須另起一行。
- 函數默認參數使用的賦值符左右省略空格。
- 賦值操作符(`=`、`+=`等)、比較操作符(`==`、`>`、`<`、`in`、`is`等)、布爾操作符(`and`、`is`、`not`)左右各加一個空格，不要爲了對齊增加空格。

## 命名規範
- 類名使用駝峯命名法。
- 成員變量和方法使用全小寫下劃線風格。
- 常量使用全大寫下劃線風格。
- 模塊名稱使用全小寫，除了`__init__`這樣的特殊模塊，不要在自定義的模塊名稱中加入下劃線。
- 使用複數形式命名列表，如`members = ['user1','user2']`。
- 使用顯式名稱命名字典，如`name_age = {'Peter':18,'Dainslef':24}`。
- 避免使用通用名稱，如`list`、`tuple`、`dict`等。
- 避免使用系統中已經存在的名稱，如`os`、`sys`等。

## 註釋規範
- 塊註釋，在一段代碼前增加註釋，註釋符號`#`後與註釋內容之間應有一個空格。
- 塊註釋的段落之間以只有`#`符號的行隔開。
- 行註釋添加在代碼之後，應儘量少用。
- 避免無意義的註釋。
