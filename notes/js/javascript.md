<!-- TOC -->

- [简介](#简介)
	- [*ECMA Script*](#ecma-script)
- [作用域](#作用域)
	- [块作用域(ES6)](#块作用域es6)
- [*for* 语句](#for-语句)
	- [*for-in*](#for-in)
	- [*for-of*](#for-of)
	- [迭代变量作用域](#迭代变量作用域)
- [*Prototype* (原型)](#prototype-原型)
	- [原型链](#原型链)
	- [原型继承](#原型继承)

<!-- /TOC -->



## 简介
`JavaScript`是**弱类型**、**隐式类型**、**动态类型**的脚本语言。

JavaScript可用于浏览器端，所有的现代浏览器均支持JavaScript。  
JavaScript在浏览器端可用于操作`HTML`标签，控制WEB页面的交互逻辑。

JavaScript亦可用于服务端，使用`Node.js`可通过JavaScript操作服务端API。  
Node.js基于性能优秀的`Chrome V8`引擎，提供了一套**事件驱动I/O**的JavaScript运行环境。

### *ECMA Script*
`ECMA Script`是JavaScript的工业标准，由`Ecma International`(**Ecma国际**，前身为**欧洲计算机制造商协会**)制定。

JavaScript是`ECMA-262`标准的扩展，兼容ECMAScript。  
JavaScript额外包含以下内容：

- 与HTML页面交互的`DOM`(`Document Object Model`，文档对象模型)
- 与浏览器窗口交互的`BOM`(`Browser Object Model`浏览器对象模型)

到目前为止(2018年)，ECMAScript现在的主流标准为`ES5`，最新标准为`ES8, ECMAScript 2017`。  
一些现代浏览器(`FireFox`、`Chrome`等)已部分实现了最新标准。



## 作用域
在`ES6`之前，JavaScript中仅存在**函数内作用域**与**全局作用域**。

- 使用`var`关键字声明变量，在全局区域为全局变量，在函数内为局部变量：

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

	输出结果：

	```
	Num before in global: 2333
	Num in function: 6666
	Num after in global: 2333
	```

	在函数内使用var关键字声明的局部变量不会对外部全局变量造成影响。

- 直接对未声明的变量使用赋值语句，则会自动在全局区域创建该变量：

	```js
	test = () => {
		num = 6666
		console.info(`Num in function: ${num}`)
	}
	
	test()
	console.info(`Num in global: ${num}`)
	```

	输出结果：

	```
	Num in function: 6666
	Num in global: 6666
	```

	函数内的赋值语句创建了全局变量，在函数外可访问。

- ES6之前，`Block`(代码块)不具有独立作用域：

	使用`var`关键字在代码块内部定义的变量在代码块所属的函数作用域内均可访问。  
	如下所示：

	```js
	var num = 2333

	{
		// 块内的变量定义语句影响了外部定义变量
		var num = 6666
	}
	
	console.info(num)
	```

	输出结果：

	```
	6666
	```

	常见的语法结构如`if`、`for`、`while`等包含的代码块中使用`var`定义变量特性类似。  
	如下所示：

	```js
	var num = 2333

	if (true) {
		var num = 6666
	}

	console.info(num)
	```

	输出结果：

	```
	6666
	```

### 块作用域(ES6)
ES6之后，新增了关键字`let/const`，使用let/const关键字定义的字段仅在块作用域中有效：

```js
var num1 = 2333, num2 = 2333

{
	// 使用let/const关键字定义局部变量，不会对外部变量造成影响
	let num1 = 6666
	const num2 = 7777
}

console.info(num1, num2)
```

输出结果：

```
2333 2333
```

ES6之后，常见的语法结构如`if`、`for`、`while`等包含的代码块中均可使用`let/const`关键字定义本地变量。



## *for* 语句
JavaScript中使用`for`关键字描述循环语法。

for语句的基本用法与**C语言**中的语法类似：

```js
for (表达式; 表达式; 表达式) {
	...
}
```

### *for-in*
JavaScript中的for语句支持使用`for-in`语法遍历集合：

```js
for (变量 in 集合) {
	...
}
```

与传统语言的for-in语法不同，在JavaScript的for-in语句中迭代变量保存的是当前迭代的**索引**，而集合的非迭代值。  
如下所示：

```js
for (i in [5, 6, 7, 8]) console.info(i)
```

输出结果：

```
0
1
2
3
```

### *for-of*
ES6开始引入了`for-of`语法：

```js
for (变量 of 集合) {
	...
}
```

for-of语法更近似与传统语言的集合遍历语法，迭代变量中保存的是当前循环的迭代值。  
如下所示：

```js
for (v of [5, 6, 7, 8]) console.info(v)
```

输出结果：

```
5
6
7
8
```

### 迭代变量作用域
使用`for-in/for-of`语句中的迭代变量同样遵循作用域规则。

默认情形下，迭代变量定义在**全局作用域**中：

```js
test = () => {
	for (i in [5, 6, 7, 8]) console.info(`i: ${i}`)
}

test()
console.info(`i in global: ${i}`)
```

输出结果：

```
i: 0
i: 1
i: 2
i: 3
i in global: 3
```

迭代变量前可使用`var/let/const`关键字做为修饰，分别对应不同的作用域。

- `var`，迭代变量在所属函数作用域内有效

	```js
	test = () => {
		for (var i in [5, 6, 7, 8]) console.info(`i: ${i}`)
		console.info(`i in function: ${i}`)
	}

	test()
	console.info(`i in global: ${i}`)
	```

	输出结果：

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

- `let/const`，迭代变量在所属for语句块内有效

	```js
	test = () => {
		for (let i in [5, 6, 7, 8]) console.info(`i: ${i}`)
		console.info(`i in function: ${i}`)
	}
	
	test()
	console.info(`i in global: ${i}`)	
	```

	输出结果：

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



## *Prototype* (原型)
在JavaScript中，每个使用`function`关键字定义的函数皆具有`prototype`属性。  

使用`new`操作符调用函数时，函数会做为`constructor`(构造器)使用，  
除了正常执行函数体外，还会创建对象，并返回所创建对象的引用，  
创建的对象带有`__proto__`属性，该属性指向对象的构造器的prototype属性。  
如下所示：

```js
> function Test() {} //定义函数
undefined
> Test.prototype
Test {}
> t = new Test //使用构造器语法创建对象
Test {}
> t.__proto__ == Test.prototype //创建的对象的__proto__属性指向构造器的prototype属性
true
```

在访问对象的属性、方法不存在时，JavaScript运行时会继续在对象的原型中查找，  
使用同一构造器创建的对象共享相同的prototype对象，  
可使用prototype属性定义一些对象间共享的字段、方法。  
如下所示：

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
> t1.name //访问原型中定义的属性
'Test'
> t2.name
'Test'
> t1.show() //调用原型中定义的方法
Name: Test
undefined
> t2.show()
Name: Test
undefined
> t1.__proto__ == t2.__proto__ //相同构造器创建的对象拥有相同的prototype对象
true
```

### 原型链
访问对象的属性、方法时，若对应名称的字段不存在，则JavaScript运行时会查找`对象.__proto__`中是否有定义，
若`对象.__proto__`中无定义，则查找`对象.__proto__.proto__`中是否有定义，依此类推，直至`__proto__`属性为`null`。  
递归地从`__prot·o__`属性中查找字段的机制被称为**原型链**。  
如下所示：

```js
> function Test() {}
undefined
> t = new Test
Test {}
> t.__proto__ //实例t的原型
Test {}
> t.__proto__.__proto__ //实例t原型的原型
{}
> t.__proto__.__proto__.__proto__ //实例t原型的原型的原型，为null(原型链到此为止)
null
> t.__proto__ == Test.prototype //实例t的原型
true
> t.__proto__.__proto__ == Object.prototype //实例t的父原型
true
```

函数`Test()`创建的实例`t`的原型链为：

```
Test.prototype => Object.prototype => null
```

使用`instanceof`关键字可以检测对象的原型链中是否具有某个函数的原型。

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

### 原型继承
在ES6之前，JavaScript不具有标准的OOP语法，可以使用**原型链**模拟面向对象语言中的继承功能。

继承一个父原型需要以下步骤：

1. 在函数体中调用要作为父类的函数

	使用`函数名.call(this, 参数表...)`或`函数名.apply(this, 参数数组)`的方式调用要作为父类的函数。  
	使用call()/apply()调用函数并将this引用传入，则所调用函数内的this操作会作用于当前的this引用。  
	如下所示：

	```js
	function Base(...) { 
		...
	}

	function Child(...) {
		Base.call(this, ...)
		...
	}
	```

	子类构造函数中使用call()/apply()调用父类构造函数，让子类实例继承父类在this引用中定义的字段。

1. 修改函数prototype属性

	函数prototype属性中指向父原型的`__proto__`引用默认指向`Object.prototype`；  
	将该引用修改为指向父原型。  
	如下所示：

	```js
	Child.prototype.__proto__ = Base.prototype
	```

	修改子类原型内的父原型引用，使子类实例继承父类在原型中定义的字段。

完整的继承示例：

```js
function Base(name) {
	this.baseName = name
}

function Child(name, baseName) {
	Base.call(this, baseName) //调用父原型的构造函数
	this.childName = name
}

// 向原型中添加属性
Base.prototype.showBase = function () {
	console.info(`Base name: ${this.baseName}`)
}

Child.prototype.showChild = function () {
	this.showBase()
	console.info(`Child name: ${this.childName}`)
}

// 变更作为子类函数的原型的父原型的指向
Child.prototype.__proto__ = Base.prototype

// 构建实例
child = new Child("Test Child", "Test Base")

// 检验原型链
console.info(`child instanceof Child: ${child instanceof Child}`)
console.info(`child instanceof Base: ${child instanceof Base}`)

// 调用方法，正常访问原型、父原型中定义的内容
child.showChild()
```

输出结果：

```
child instanceof Child: true
child instanceof Base: true
Base name: Test Base
Child name: Test Child
```
