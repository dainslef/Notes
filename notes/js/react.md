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
)
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



## 组件
**组件**是React的核心。

组件的概念类似于JavaScript中的**函数**。  
组件接收输入的属性(保存在`props`中)，返回React对象，用以描述需要在屏幕中显示的内容。

React使用组件机制将HTML代码块封装为可复用的组件，通过一个个组件组合构成复杂的WEB应用。

### 组件命名
在React中，自定义组件名称应以大写字母开始。  
React将小写字母开始的组件视为`DOM`标签。
 
例如，`<div />`代表`HTML`中的`div`标签，但`<Component />`代表名为`Component`的自定义组件。

### *Functional Component*
定义组件最简单的方式是直接使用JavaScript中的函数：

```jsx
function MyComponent(props) {
	return <img src={props.src} alt={props.alt} />
}

// 使用 ES6 语法
const MyComponent = props => <img src={props.src} alt={props.alt} />
```

使用定义的组件：

```jsx
// 使用定义的组件
<MyComponent src="/resource/xxx.jpg" alt="test"/>
```

直接使用JavaScript函数定义的组件被称为`Functional Component`(函数式组件)。

### *ES6 Component*
组件支持使用`ES6`新特性`class`进行定义。  
自定义组件类从`React.Component`类型中继承，通过实现`render()`成员方法来描述组件的内容。  
如下所示：

```jsx
class MyComponent extends Component {
	render = () => ...
}

// 使用定义的组件
<MyComponent />
```

组件属性保存在`props`属性中，通过`this.props.属性名`进行访问。  
如下所示：

```jsx
class MyComponent extends Component {
	render = () => <img src={this.props.src} alt={this.props.alt} />
}

// 使用定义的组件
<MyComponent src="/resource/xxx.jpg" alt="test"/>
```

### 组合组件
组件标签之间可以相互组合。  
如下所示：

```jsx
class Image extends Component {
	render = () => <img src={this.props.src} alt={this.props.alt} />
}

class MyComponent extends Component {
	render = () =>
		<div>
			<h1>Name1</h1>
			<h1>Name2</h1>
			<Image src="abc.jpg" alt="image1" />
			<Image src="cde.jpg" alt="image2" />
			<Image src="efg.jpg" alt="image3" />
		</div>
}
```

对于一些结构类似的组件，可以通过**高阶函数**映射生成，上述代码可简化为：

```jsx
class Image extends Component {
	render = () => <img src={this.props.src} alt={this.props.alt} />
}

const names = [1, 2].map(i => <h1>Name{i}</h2>)
const images = ["abc", "cde", "efg"]
	.map((name, index) => <Image src={`${name}.jpg`} alt={`image${index}`}/>)

class MyComponent extends Component {
	render = () =>
		<div>
			{names}
			{images}
		</div>
}
```

### *State* (组件状态)
`state`字段在React组件中具有特殊意义。  
在组件类中定义`state`字段来保存组件的本地状态(`Local State`)。  

`Functional Component`(函数式组件)自身是无状态的，组件需要保存本地状态应使用`ES6 Component`。

组件的`state`字段可以在构造器中定义：

```jsx
class MyComponent extends Component {

	constructor(props) {
		super(props)
		this.state = {
			myState1: ... ,
			myState2: ... ,
			...
		}
	}

	render = () => ...

}
```

或者直接做为类成员定义：

```jsx
class MyComponent extends Component {

	state = {
		myState1: ... ,
		myState2: ... ,
		...
	}

	render = () => ...

}
```

当需要更新组件状态时，不要直接修改`this.state`成员，应使用`setState()`方法，如下所示：

```jsx
// 错误示例，直接修改 state 字段DOM不会更新
this.state.myState1 = xxx

// 正确用法
this.setState({ myState1: xxx })
```

使用`setState()`方法更新组件状态，对应组件所属的DOM会重新渲染。

在React中更新组件状态是**异步**(`Asynchronous`)的，出于性能考虑，React可能会将多个状态更新方法(`setState()`)合并到一次更新中。  
当一个状态依赖于多个之前的状态时，不应简单地直接使用`setState()`更新状态，如下所示：

```jsx
/*
	错误，counter 的新状态依赖于之前的 this.state.counter 和 this.props.increment
	若 setState() 调用时 this.props.increment 也发生更新操作或 this.state.counter 还有其它 setState() 更新方式，则这些可能会被合并到一次更新中，造成状态更新错误
*/
this.setState({
	counter: this.state.counter + this.props.increment
})
```

正确的做法是将`setState()`方法中的参数由**JSON对象**替换为**方法**，
被替换的方法应带有两个参数，前一个参数为之前的`state`，后一个参数为之前的`props`，如下所示：

```jsx
// 正确，使用方法代替JSON对象，从方法参数中获取之前地状态，保证状态正确更新
this.setState((prevState, props) => {
	counter: prevState.counter + props.increment
})
```

### *Lifecycle Methods* (生命周期方法)
在组件的生命周期中，首次被渲染为DOM时，在React中被称为**挂载**(`mounting`)；  
在组件被从DOM树中移除时，在React中被称为**卸载**(`unmounting`)。

通过在组件类中定义`componentDidMount()`、`componentWillUnmount()`方法可在组件挂载、卸载时添加额外的逻辑。  
如下所示：

```jsx
class MyComponent extends Component {

	componentDidMount() {
		// 组件DOM渲染完毕时，执行该方法中的逻辑
	}

	componentWillUnmount() {
		// 组件DOM被移除时，执行该方法中的逻辑
	}

	render = () => ...

}
```

- `componentDidMount()`方法通常用于初始化一些依赖于DOM的资源，一般与DOM无关的资源可直接放在构造方法中，componentDidMount()方法执行时保证DOM已被渲染完毕。
- `componentWillUnmount()`方法用法类似`C++`中的**析构函数**，通常用于在组件卸载时执行一些清理操作(如**定时器**等)。



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
