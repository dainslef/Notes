## 简介
`React`是`Facebook`开发的一套JavaScript库，提供了组件化的方式来构建`WEB UI`。

官网中提到的React的优势：

- 让创建交互式UI变得简单。为应用的中每个状态创建简单的视图，当状态变化时，React会高效地渲染正确的组件。
- 封装组件来管理拥有的状态，通过组合组件来构建复杂的UI。使用JaveSript代替模板来编写组件逻辑，开发者可以简单地在程序中传递复杂的数据同时将状态保存在`DOM`之外。
- React不仅仅可用于构建`WEB UI`，还有用于移动端的`React Native`。



## 安装与配置
推荐使用`npm`来创建React项目，管理项目依赖。  
React项目需要使用的`JSX`扩展语法不能被浏览器原生支持，需要配置`Babel`转译为普通的JavaScript代码。

### 使用 *create-react-app* 创建项目
直接配置React项目较为复杂，`Facebook`为React项目提供了官方的项目创建工具`create-react-app`。  
使用`npm`安装：

```
$ npm install -g create-react-app
```

使用`create-react-app`指令创建React项目：

```
$ create-react-app [项目名称] //若已配置 Node.js 相关环境变量，可直接使用 create-react-app 指令
$ npx create-react-app [项目名称] //亦可使用 npx 执行 create-react-app 指令
```

创建的React项目预置了以下npm指令：

```
$ npm start //启动开发服务器，默认为 3000 端口
$ npm test //启动测试服务器
$ npm run build //构建项目的生产版本(Release)，输出到项目根目录的 build 路径下
```

### 项目结构
使用`create-react-app`新创建的React项目具有以下结构：

```
项目根目录
├─ node_modules
│   └─ ...
├─ public
│   ├─ index.html
│   └─ ...
├─ src
│   ├─ index.js
│   └─ ...
├─ package.json
├─ package-lock.json
├─ README.md
└─ .gitignore
```

其中，`index.html`为单页应用的主页，`index.js`为React应用的入口。

`index.html`中使用`id`标记一个节点，使用`ReactDOM.render()`方法渲染该节点。  
简单的`Hello World`例子如下所示：

(页面)

```html
<!DOCTYPE html>
<html lang="en">

<head>
	<meta charset="utf-8">
	<link rel="shortcut icon" href="%PUBLIC_URL%/img/xxx.ico">
	<title>xxx</title>
</head>

<body>
	<div id="root"></div>
</body>

</html>
```

(代码)

```jsx
import React, { ReactDOM } from "react"

ReactDOM.render(
	<h1>Hello, world!</h1>,
	document.getElementById('root')
);
```



## *JSX*
React扩展了JavaScript语法，允许在JavaScript代码中直接使用类XML语法，被称为`JSX`。  
React的`JSX`类似于Scala的`XML Literal`，XML语句可直接作为变量或参数。  
如下所示：

```jsx
const element = <h1>xxx</h1>
```

### 在 *JSX* 中引用表达式
使用`{}`(**花括号**)在JSX标签中嵌入JavaScript表达式。
如下所示：

```jsx
const name = "Dainslef"
const element = <h1>Hello, my name is {name} !</h1>
```

### 在 *JSX* 中设置节点属性
使用具体的字符串作为JSX标签属性：

```jsx
const element = <div tabIndex="0"></div>
```

引用JavaScript表达式作为JSX标签属性：

```jsx
const element1 = <div tabIndex={0}></div>

const src = "/resource/xxx.jpg"
const element2 = <img src={src}></img>
```

### 闭合、嵌套标签
与XML类似，JSX使用`<Xxx/>`语法表示自闭合的标签：

```jsx
const element = <img src="/resource/xxx.jpg" />
```

JSX标签可以相互嵌套，如下所示：

```jsx
const element = 
	<div>
		<h1>Hello!</h1>
		<h2>Good to see you here.</h2>
	</div>
```



## 常见错误

### *Uncaught ReferenceError: $ is not defined*
使用`Webpack`打包，不能以常规方式使用JQuery，需要在Webpack配置中使用JQuery插件：

```js
new webpack.ProvidePlugin({
	$: 'jquery',
	jQuery: 'jquery'
})
```

### *Target container is not a DOM element.*
在`React`项目中，使用`Webpack`打包生成js文件时，生成的js文件应在主Html文件的最后(至少需要在被渲染的元素出现之后)导入。  
若在`<head>`标签中导入生成的js，React执行时会出现`Target container is not a DOM element.`错误，
原因是加载js时DOM尚未创建完毕。  
如下所示：

```html
<!DOCTYPE html>
<html lang="zh-cn">
<head>
	<meta charset="UTF-8">
	<title>Xxx</title>
	<!-- <script src="./build/bundle.js"></script> 错误，在<head>标签内导入js会出现错误 -->
</head>
<body>
	<div id="main"></div> <!-- 假设需要被渲染的节点id为 main -->
	<!-- <script src="./build/bundle.js"></script> 正确，在被渲染的元素出现后加载js，能够正常渲染元素 -->
</body>
<script src="./build/bundle.js"></script> <!-- 正确，在HTML页面底部导入JS，此时DOM已被加载完毕 -->
</html>
```
