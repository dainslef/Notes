<!-- TOC -->

- [簡介](#簡介)
	- [ECMA Script](#ecma-script)
- [作用域](#作用域)
	- [塊作用域 (ES6)](#塊作用域-es6)
- [for 語句](#for-語句)
	- [for-in](#for-in)
	- [for-of](#for-of)
	- [迭代變量作用域](#迭代變量作用域)
- [this](#this)
	- [Function's this](#functions-this)
	- [Arrow Function's this](#arrow-functions-this)
	- [Node.js環境中的 this](#nodejs環境中的-this)
- [Prototype (原型)](#prototype-原型)
	- [原型鏈](#原型鏈)
	- [原型繼承](#原型繼承)
- [屬性訪問器](#屬性訪問器)
	- [訪問器屬性](#訪問器屬性)

<!-- /TOC -->



# 簡介
`JavaScript`是**弱類型**、**隱式類型**、**動態類型**的腳本語言。

JavaScript可用於瀏覽器端，所有的現代瀏覽器均支持JavaScript。
JavaScript在瀏覽器端可用於操作`HTML`標籤，控制WEB頁面的交互邏輯。

JavaScript亦可用於服務端，使用`Node.js`可通過JavaScript操作服務端API。
Node.js基於性能優秀的`Chrome V8`引擎，提供了一套**事件驅動I/O**的JavaScript運行環境。

## ECMA Script
`ECMA Script`是JavaScript的工業標準，由`Ecma International`(**Ecma國際**，前身爲**歐洲計算機制造商協會**)制定。

JavaScript是`ECMA-262`標準的擴展，兼容ECMAScript。
JavaScript額外包含以下內容：

- 與HTML頁面交互的`DOM`(`Document Object Model`，文檔對象模型)
- 與瀏覽器窗口交互的`BOM`(`Browser Object Model`，瀏覽器對象模型)

到目前爲止(2018年)，ECMAScript現在的主流標準爲`ES5`，最新標準爲`ES8, ECMAScript 2017`。
一些現代瀏覽器(`FireFox`、`Chrome`等)已部分實現了最新標準。



# 作用域
塊語義見`ECMAScript 2015`規範`13.2`節`Block`。
定義與變量語義見`ECMAScript 2015`規範`13.3`節`Declarations and the Variable Statement`。

在`ES6`之前，JavaScript中僅存在**函數內作用域**與**全局作用域**。

- 使用`var`關鍵字聲明變量，在全局區域爲全局變量，在函數內爲局部變量：

	```js
	var num = 2333

	test = () => {
		var num = 6666
		console.info(`Num in function: ${num}`)
	}

	console.info(`Num before in global: ${num}`)
	test()
	console.info(`Num after in global: ${num}`)
	```

	輸出結果：

	```
	Num before in global: 2333
	Num in function: 6666
	Num after in global: 2333
	```

	在函數內使用var關鍵字聲明的局部變量不會對外部全局變量造成影響。

- 直接對未聲明的變量使用賦值語句，則會自動在全局區域創建該變量：

	```js
	test = () => {
		num = 6666
		console.info(`Num in function: ${num}`)
	}

	test()
	console.info(`Num in global: ${num}`)
	```

	輸出結果：

	```
	Num in function: 6666
	Num in global: 6666
	```

	函數內的賦值語句創建了全局變量，在函數外可訪問。

- ES6之前，`Block`(代碼塊)不具有獨立作用域：

	使用`var`關鍵字在代碼塊內部定義的變量在代碼塊所屬的函數作用域內均可訪問。
	示例：

	```js
	var num = 2333

	{
		// 塊內的變量定義語句影響了外部定義變量
		var num = 6666
	}

	console.info(num)
	```

	輸出結果：

	```
	6666
	```

	常見的語法結構如`if`、`for`、`while`等包含的代碼塊中使用`var`定義變量特性類似。
	示例：

	```js
	var num = 2333

	if (true) {
		var num = 6666
	}

	console.info(num)
	```

	輸出結果：

	```
	6666
	```

## 塊作用域 (ES6)
ES6之後，新增了關鍵字`let/const`，使用let/const關鍵字定義的字段僅在塊作用域中有效：

```js
var num1 = 2333, num2 = 2333

{
	// 使用let/const關鍵字定義局部變量，不會對外部變量造成影響
	let num1 = 6666
	const num2 = 7777
}

console.info(num1, num2)
```

輸出結果：

```
2333 2333
```

ES6之後，常見的語法結構如`if`、`for`、`while`等包含的代碼塊中均可使用`let/const`關鍵字定義本地變量。



# for 語句
迭代器語義見`ECMAScipt 2015`規範`13.7`節`Iteration Statements`。

JavaScript中使用`for`關鍵字描述循環語法。

for語句的基本用法與**C語言**中的語法類似：

```js
for (表達式; 表達式; 表達式) {
	...
}
```

## for-in
JavaScript中的for語句支持使用`for-in`語法遍歷集合：

```js
for (變量 in 集合) {
	...
}
```

與傳統語言的for-in語法不同，在JavaScript的for-in語句中迭代變量保存的是當前迭代的**索引**，而集合的非迭代值。
示例：

```js
for (i in [5, 6, 7, 8]) console.info(i)
```

輸出結果：

```
0
1
2
3
```

## for-of
ES6開始引入了`for-of`語法：

```js
for (變量 of 集合) {
	...
}
```

for-of語法更近似與傳統語言的集合遍歷語法，迭代變量中保存的是當前循環的迭代值。
示例：

```js
for (v of [5, 6, 7, 8]) console.info(v)
```

輸出結果：

```
5
6
7
8
```

## 迭代變量作用域
使用`for-in/for-of`語句中的迭代變量同樣遵循作用域規則。

默認情形下，迭代變量定義在**全局作用域**中：

```js
test = () => {
	for (i in [5, 6, 7, 8]) console.info(`i: ${i}`)
}

test()
console.info(`i in global: ${i}`)
```

輸出結果：

```
i: 0
i: 1
i: 2
i: 3
i in global: 3
```

迭代變量前可使用`var/let/const`關鍵字做爲修飾，分別對應不同的作用域。

- `var`，迭代變量在所屬函數作用域內有效

	```js
	test = () => {
		for (var i in [5, 6, 7, 8]) console.info(`i: ${i}`)
		console.info(`i in function: ${i}`)
	}

	test()
	console.info(`i in global: ${i}`)
	```

	輸出結果：

	```
	i: 0
	i: 1
	i: 2
	i: 3
	i in function: 3
	C:\Users\dainslef\test.js:7
	console.info(`i in global: ${i}`)
	                             ^

	ReferenceError: i is not defined
	    at Object.<anonymous> (C:\Users\dainslef\test.js:7:30)
	    at Module._compile (module.js:662:30)
	    at Object.Module._extensions..js (module.js:673:10)
	    at Module.load (module.js:575:32)
	    at tryModuleLoad (module.js:515:12)
	    at Function.Module._load (module.js:507:3)
	    at Function.Module.runMain (module.js:703:10)
	    at startup (bootstrap_node.js:193:16)
	    at bootstrap_node.js:665:3
	```

- `let/const`，迭代變量在所屬for語句塊內有效

	```js
	test = () => {
		for (let i in [5, 6, 7, 8]) console.info(`i: ${i}`)
		console.info(`i in function: ${i}`)
	}

	test()
	console.info(`i in global: ${i}`)
	```

	輸出結果：

	```
	i: 0
	i: 1
	i: 2
	i: 3
	C:\Users\dainslef\test.js:3
	        console.info(`i in function: ${i}`)
	                                       ^

	ReferenceError: i is not defined
	    at test (C:\Users\dainslef\test.js:3:33)
	    at Object.<anonymous> (C:\Users\dainslef\test.js:6:1)
	    at Module._compile (module.js:662:30)
	    at Object.Module._extensions..js (module.js:673:10)
	    at Module.load (module.js:575:32)
	    at tryModuleLoad (module.js:515:12)
	    at Function.Module._load (module.js:507:3)
	    at Function.Module.runMain (module.js:703:10)
	    at startup (bootstrap_node.js:193:16)
	    at bootstrap_node.js:665:3
	```



# this
JavaScript中的`this`關鍵字與傳統的OOP語言有較大差異。
在不同的上下文、不同的語法結構中，this具有不同的含義，指向不同的對象。

## Function's this
函數環境記錄相關內容見`ECMAScript 2015`規範`8.1.1.3`節`Function Environment Records`。
函數執行語義見`ECMAScript 2015`規範`14.1`節`Function Definitions`中`14.1.20`小節`Runtime Semantics: Evaluation`。
函數具有獨立的詞法環境，詞法環境相關內容見`ECMAScript 2015`規範`8.1`節`Lexical Environmens`。

使用`function`關鍵字定義的函數中this由調用者決定。
普通地調用函數，函數的調用者默認爲全局對象，在不同的JavaScript運行時下，全局對象略有不同：

- 在**瀏覽器**環境中，全局對象爲`window`。
- 在`Node.js`環境中，全局對象爲`global`。

示例：

```js
function test() {
	this.name = "test name"
	console.info(`this === global: ${this === global}`)
}

test()

console.info(`name: ${name}`)
```

輸出結果：(Node.js v9.8.0)

```
this === global: true
name: test name
```

使用`對象.方法()`的語法調用函數時，this指向調用對象：

```js
function test(target) {
	this.name = "test name"
	console.info(`this === target: ${this === target}`)
}

obj = { test: test }
obj.test(obj)

console.info(`obj: ${obj}`)
```

輸出結果：(Node.js v9.8.0)

```
this === target: true
obj: { test: [Function: test], name: 'test name' }
```

作爲匿名函數使用時，this同樣指向調用對象：

```js
obj = {}

function testNormal(f) {
	f(this)
}

function testMember(f) {
	obj.f = f
	obj.f(this)
}

testNormal(function (target) {
	console.info("Test Normal Call:")
	console.info(`this == gobal: ${this === global}`)
	console.info(`this == target: ${this === target}`)
})

testMember(function (target) {
	console.info("Test Member Call:")
	console.info(`this == gobal: ${this === global}`)
	console.info(`this == target: ${this === target}`)
})

obj.testNormal = testNormal
obj.testMember = testMember

obj.testNormal(function (target) {
	console.info("Test Normal Call in obj:")
	console.info(`this == gobal: ${this === global}`)
	console.info(`this == target: ${this === target}`)
})

obj.testMember(function (target) {
	console.info("Test Member Call in obj:")
	console.info(`this == gobal: ${this === global}`)
	console.info(`this == target: ${this === target}`)
})
```

輸出結果：(Node.js v9.8.0)

```
Test Normal Call:
this == gobal: true
this == target: true
Test Member Call:
this == gobal: false
this == target: false
Test Normal Call in obj:
this == gobal: true
this == target: false
Test Member Call in obj:
this == gobal: false
this == target: true
```

函數搭配`new`關鍵字作爲**構造函數**使用時，會創建新的對象，此時this指向創建的對象：

```js
function test(args) {
	this.name = "test name"
	args.obj = this
}

args = {}
obj = new test(args)

console.info(`obj === args.obj: ${obj === args.obj}`)
```

輸出結果：(Node.js v9.9.0)

```
obj === args.obj: true
```

## Arrow Function's this
箭頭函數的函數環境相關內容見`ECMAScript 2015`規範`14.2`節`Arrow Function Definitions`中`14.2.16`小節`Runtime Semantics: Evaluation`。

箭頭函數**沒有**獨立的詞法作用域，箭頭函數中的this由箭頭函數的父級上下文決定，與調用者**無關**。
示例：

```js
/*
 * 箭頭函數 test 此時的父級作用域爲模塊作用域
 * 函數內 this 指向模塊作用域(即 module.exports，不是 global)
 */
test = () => {
	this.name = "test name"
	console.info(`this === global: ${this === global}`)
	console.info(`this === module.epxorts: ${this === module.exports}`)
}

test()
console.info(`this.name: ${this.name}`) //直接訪問 name 或 global.name 會拋出異常
console.info(`module.exports.name: ${module.exports.name}`)
```

輸出結果：(Node.js v10.0.0)

```
this === global: false
this === module.epxorts: true
this.name: test name
module.exports.name: test name
```

使用`對象.方法()`的語法調用**箭頭函數**時，this依舊指向**定義時**的父級上下文：

```js
test = target => {
	this.name = "test name" // this 始終指向模塊作用域，與外部調用者無關
	console.info(`this === target: ${this === target}`)
	console.info(`this === module.epxorts: ${this === module.exports}`)
}

obj = { test: test }
obj.test(obj)

console.info(`obj: ${obj}`)
console.info(`obj.name: ${obj.name}`) // obj 對象中並不存在 name 屬性
console.info(`module.exports.name: ${module.exports.name}`) // name 屬性添加到了模塊作用域中
```

輸出結果：(Node.js v10.0.0)

```
this === target: false
this === module.epxorts: true
obj: { test: [Function: test] }
obj.name: undefined
module.exports.name: test name
```

## Node.js環境中的 this
在`Node.js`環境中，全局this在不同場景下代表不同內容：

- `Node.js REPL`

	在Node.js提供的REPL中，this指向全局對象`global`。
	示例：(Node.js v10.1.0)

	```js
	> global === this
	true
	```

- `Node.js Module`

	使用Node.js解釋器執行JavaScript源碼文件時，每個源碼文件會作爲一個JS模塊(`Module`)。
	模塊中的this指向模塊導出對象`module.exports`，而非全局對象`global`。
	示例：

	```js
	console.info(`this === global: ${this === global}`)
	console.info(`this === module.epxorts: ${this === module.exports}`)
	```

	輸出結果：(Node.js v10.1.0)

	```
	this === global: false
	this === module.epxorts: true
	```



# Prototype (原型)
原型相關內容見`ECMAScript 2015`規範`4.2.1`節`Objects`。

在JavaScript中，每個使用`function`關鍵字定義的函數皆具有`prototype`屬性。

使用`new`操作符調用函數時，函數會做爲`constructor`(構造器)使用，
除了正常執行函數體外，還會創建對象，並返回所創建對象的引用，
創建的對象帶有`__proto__`屬性，該屬性指向對象的構造器的prototype屬性。
示例：

```js
> function Test() {} //定義函數
undefined
> Test.prototype
Test {}
> t = new Test //使用構造器語法創建對象
Test {}
> t.__proto__ == Test.prototype //創建的對象的__proto__屬性指向構造器的prototype屬性
true
```

在訪問對象的屬性、方法不存在時，JavaScript運行時會繼續在對象的原型中查找，
使用同一構造器創建的對象共享相同的prototype對象，
可使用prototype屬性定義一些對象間共享的字段、方法。
示例：

```js
> function Test() {}
undefined
> Test.prototype.name = "Test"
'Test'
> Test.prototype.show = function() { console.info(`Name: ${this.name}`) }
[Function]
> t1 = new Test
Test {}
> t2 = new Test
Test {}
> t1.name //訪問原型中定義的屬性
'Test'
> t2.name
'Test'
> t1.show() //調用原型中定義的方法
Name: Test
undefined
> t2.show()
Name: Test
undefined
> t1.__proto__ == t2.__proto__ //相同構造器創建的對象擁有相同的prototype對象
true
```

## 原型鏈
訪問對象的屬性、方法時，若對應名稱的字段不存在，則JavaScript運行時會查找`對象.__proto__`中是否有定義，
若`對象.__proto__`中無定義，則查找`對象.__proto__.proto__`中是否有定義，依此類推，直至`__proto__`屬性爲`null`。
遞歸地從`__prot·o__`屬性中查找字段的機制被稱爲**原型鏈**。
示例：

```js
> function Test() {}
undefined
> t = new Test
Test {}
> t.__proto__ //實例t的原型
Test {}
> t.__proto__.__proto__ //實例t原型的原型
{}
> t.__proto__.__proto__.__proto__ //實例t原型的原型的原型，爲null(原型鏈到此爲止)
null
> t.__proto__ == Test.prototype //實例t的原型
true
> t.__proto__.__proto__ == Object.prototype //實例t的父原型
true
```

函數`Test()`創建的實例`t`的原型鏈爲：

```
Test.prototype => Object.prototype => null
```

使用`instanceof`關鍵字可以檢測對象的原型鏈中是否具有某個函數的原型。

```js
> function Test() {}
undefined
> t = new Test
Test {}
> t instanceof Test
true
> t instanceof Object
true
> function Other() {}
undefined
> t instanceof Other
false
```

## 原型繼承
在ES6之前，JavaScript不具有標準的OOP語法，可以使用**原型鏈**模擬面嚮對象語言中的繼承功能。

繼承一個父原型需要以下步驟：

1. 在函數體中調用要作爲父類的函數

	使用`函數名.call(this, 參數表...)`或`函數名.apply(this, 參數數組)`的方式調用要作爲父類的函數。
	使用call()/apply()調用函數並將this引用傳入，則所調用函數內的this操作會作用於當前的this引用。
	示例：

	```js
	function Base(...) {
		...
	}

	function Child(...) {
		Base.call(this, ...)
		...
	}
	```

	子類構造函數中使用call()/apply()調用父類構造函數，讓子類實例繼承父類在this引用中定義的字段。

1. 修改函數prototype屬性

	函數prototype屬性中指向父原型的`__proto__`引用默認指向`Object.prototype`；
	將該引用修改爲指向父原型。
	示例：

	```js
	Child.prototype.__proto__ = Base.prototype
	```

	修改子類原型內的父原型引用，使子類實例繼承父類在原型中定義的字段。

完整的繼承示例：

```js
function Base(name) {
	this.baseName = name
}

function Child(name, baseName) {
	Base.call(this, baseName) //調用父原型的構造函數
	this.childName = name
}

// 向原型中添加屬性
Base.prototype.showBase = function () {
	console.info(`Base name: ${this.baseName}`)
}

Child.prototype.showChild = function () {
	this.showBase()
	console.info(`Child name: ${this.childName}`)
}

// 變更作爲子類函數的原型的父原型的指向
Child.prototype.__proto__ = Base.prototype

// 構建實例
child = new Child("Test Child", "Test Base")

// 檢驗原型鏈
console.info(`child instanceof Child: ${child instanceof Child}`)
console.info(`child instanceof Base: ${child instanceof Base}`)

// 調用方法，正常訪問原型、父原型中定義的內容
child.showChild()
```

輸出結果：

```
child instanceof Child: true
child instanceof Base: true
Base name: Test Base
Child name: Test Child
```



# 屬性訪問器
在JavaScript中，對象可爲自身屬性定義訪問器(`get()/set()`方法)，在訪問屬性時，實際會調用對應的訪問器方法。

## 訪問器屬性
訪問器屬性相關內容見`ECMAScript 2015`規範`6.1.7`節`The Object Type`。

使用Object對象的內置方法`Object.defineProperty()`定義屬性時，可爲屬性設定屬性描述對象(`PropertyDescriptor`)，
在該對象中定義對應的`get()/set()`方法。
示例：

```js
obj = {
	_name: "2333" //實際保存屬性內容的字段
}

/*
 * 使用 Object.defineProperty() 方法定義屬性：
 * 第一參數爲被添加屬性的對象
 * 第二參數爲屬性名稱
 * 第三參數爲屬性的屬性描述對象，在該對象中添加 get()/set() 方法
 */
Object.defineProperty(obj, "name", {
	get() {
		console.info("Read property ...")
		return this._name
	},
	set(value) {
		console.info(`Set property ...`)
		this._name = value
	}
})

console.info(obj.name)
console.info(obj.name = "6666")
```

輸出結果：

```
Read property ...
2333
Set property ...
6666
```

`ES5`開始添加了定義訪問器屬性的簡便語法，在對象的方法前使用`set/get`關鍵字修飾，即可使方法成爲屬性訪問器方法。
上述例子使用ES5語法可以簡寫成：

```js
obj = {
	_name: "2333",
	get name() {
		console.info("Read property ...")
		return this._name
	},
	set name(value) {
		console.info("Set property name ...")
		this._name = value
	}
}

console.info(obj.name)
console.info(obj.name = "6666")
```
