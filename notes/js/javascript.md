<!-- TOC -->

- [简介](#简介)
	- [*ECMA Script*](#ecma-script)
- [作用域](#作用域)

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
