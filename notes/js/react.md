<!-- TOC -->

- [簡介](#簡介)
- [安裝與配置](#安裝與配置)
	- [create-react-app](#create-react-app)
	- [項目結構](#項目結構)
- [JSX](#jsx)
	- [引用表達式](#引用表達式)
	- [設置節點屬性](#設置節點屬性)
	- [閉合、嵌套標籤](#閉合嵌套標籤)
- [Component (組件)](#component-組件)
	- [組件命名](#組件命名)
	- [Functional Component](#functional-component)
	- [ES6 Component](#es6-component)
	- [組合組件](#組合組件)
	- [State (組件狀態)](#state-組件狀態)
	- [Lifecycle Methods (生命週期方法)](#lifecycle-methods-生命週期方法)
- [路由](#路由)
	- [安裝](#安裝)
	- [Router](#router)
- [常見錯誤](#常見錯誤)
	- [Uncaught ReferenceError: $ is not defined](#uncaught-referenceerror--is-not-defined)
	- [Target container is not a DOM element.](#target-container-is-not-a-dom-element)
	- [Warning: Each child in an array or iterator should have a unique "key" prop.](#warning-each-child-in-an-array-or-iterator-should-have-a-unique-key-prop)

<!-- /TOC -->



# 簡介
`React`是`Facebook`開發的一套JavaScript庫，提供了組件化的方式來構建`WEB UI`。

官網中提到的React的優勢：

- 讓創建交互式UI變得簡單。爲應用的中每個狀態創建簡單的視圖，當狀態變化時，React會高效地渲染正確的組件。
- 封裝組件來管理擁有的狀態，通過組合組件來構建複雜的UI。使用JaveSript代替模板來編寫組件邏輯，
開發者可以簡單地在程序中傳遞複雜的數據同時將狀態保存在`DOM`之外。
- React不僅僅可用於構建`WEB UI`，還有用於移動端的`React Native`。



# 安裝與配置
推薦使用`npm`來創建React項目，管理項目依賴。
React項目需要使用的`JSX`擴展語法不能被瀏覽器原生支持，需要配置`Babel`轉譯爲普通的JavaScript代碼。

## create-react-app
直接配置React項目較爲複雜，`Facebook`爲React項目提供了官方的項目創建工具`create-react-app`。
使用`npm`安裝：

```
$ npm install -g create-react-app
```

使用`create-react-app`指令創建React項目：

```
$ create-react-app [項目名稱] //若已配置 Node.js 相關環境變量，可直接使用 create-react-app 指令
$ npx create-react-app [項目名稱] //亦可使用 npx 執行 create-react-app 指令
```

創建的React項目預置了以下npm指令：

```
$ npm start //啓動開發服務器，默認爲 3000 端口
$ npm test //啓動測試服務器
$ npm run build //構建項目的生產版本(Release)，輸出到項目根目錄的 build 路徑下
```

## 項目結構
使用`create-react-app`新創建的React項目具有以下結構：

```
項目根目錄
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

其中，`index.html`爲單頁應用的主頁，`index.js`爲React應用的入口。

`index.html`中使用`id`標記一個節點，使用`ReactDOM.render()`方法渲染該節點。
簡單的`Hello World`例子示例：

(頁面)

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

(代碼)

```jsx
import React, { ReactDOM } from "react"

ReactDOM.render(
	<h1>Hello, world!</h1>,
	document.getElementById('root')
)
```



# JSX
React擴展了JavaScript語法，允許在JavaScript代碼中直接使用類XML語法，被稱爲`JSX`。
React的`JSX`類似於Scala的`XML Literal`，XML語句可直接作爲變量或參數。
示例：

```jsx
const element = <h1>xxx</h1>
```

## 引用表達式
使用`{}`(**花括號**)在JSX標籤中嵌入JavaScript表達式。
示例：

```jsx
const name = "Dainslef"
const element = <h1>Hello, my name is {name}!</h1>
```

## 設置節點屬性
使用具體的字符串作爲JSX標籤屬性：

```jsx
const element = <div tabIndex="0"></div>
```

引用JavaScript表達式作爲JSX標籤屬性：

```jsx
const element1 = <div tabIndex={0}></div>

const src = "/resource/xxx.jpg"
const element2 = <img src={src}></img>
```

## 閉合、嵌套標籤
與XML類似，JSX使用`<Xxx/>`語法表示自閉合的標籤：

```jsx
const element = <img src="/resource/xxx.jpg" />
```

JSX標籤可以相互嵌套，示例：

```jsx
const element =
	<div>
		<h1>Hello!</h1>
		<h2>Good to see you here.</h2>
	</div>
```



# Component (組件)
**組件**(Component)是React的核心。

組件的概念類似於JavaScript中的**函數**。
組件接收輸入的屬性(保存在`props`中)，返回React對象，用以描述需要在屏幕中顯示的內容。

React使用組件機制將HTML代碼塊封裝爲可複用的組件，通過一個個組件組合構成複雜的WEB應用。

## 組件命名
在React中，自定義組件名稱應以大寫字母開始。
React將小寫字母開始的組件視爲`DOM`標籤。

例如，`<div />`代表`HTML`中的`div`標籤，但`<Component />`代表名爲`Component`的自定義組件。

## Functional Component
定義組件最簡單的方式是直接使用JavaScript中的函數：

```jsx
function MyComponent(props) {
	return <img src={props.src} alt={props.alt} />
}

// 使用 ES6 語法
const MyComponent = props => <img src={props.src} alt={props.alt} />
```

使用定義的組件：

```jsx
// 使用定義的組件
<MyComponent src="/resource/xxx.jpg" alt="test"/>
```

直接使用JavaScript函數定義的組件被稱爲`Functional Component`(函數式組件)。

## ES6 Component
組件支持使用ES6新特性`class`進行定義。
自定義組件類從`React.Component`類型中繼承，通過實現`render()`成員方法來描述組件的內容。
示例：

```jsx
class MyComponent extends Component {
	render = () => ...
}

// 使用定義的組件
<MyComponent />
```

組件屬性保存在`props`屬性中，通過`this.props.屬性名`進行訪問。
示例：

```jsx
class MyComponent extends Component {
	render = () => <img src={this.props.src} alt={this.props.alt} />
}

// 使用定義的組件
<MyComponent src="/resource/xxx.jpg" alt="test"/>
```

## 組合組件
組件標籤之間可以相互組合。
示例：

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

對於一些結構類似的組件，可以通過**高階函數**映射生成，上述代碼可簡化爲：

```jsx
class Image extends Component {
	render = () => <img src={this.props.src} alt={this.props.alt} />
}

const names = [1, 2].map(i => <h1>Name{i}</h1>)
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

## State (組件狀態)
`state`字段在React組件中具有特殊意義。
在組件類中定義`state`字段來保存組件的本地狀態(`Local State`)。

`Functional Component`(函數式組件)自身是無狀態的，組件需要保存本地狀態應使用`ES6 Component`。

組件的`state`字段可以在構造器中定義：

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

或者直接做爲類成員定義：

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

當需要更新組件狀態時，不要直接修改`this.state`成員，應使用`setState()`方法，示例：

```jsx
// 錯誤示例，直接修改 state 字段DOM不會更新
this.state.myState1 = xxx

// 正確用法
this.setState({ myState1: xxx })
```

使用`setState()`方法更新組件狀態，對應組件所屬的DOM會重新渲染。

在React中更新組件狀態是**異步**(`Asynchronous`)的，出於性能考慮，
React可能會將多個狀態更新方法(`setState()`)合併到一次更新中。
當一個狀態依賴於多個之前的狀態時，不應簡單地直接使用`setState()`更新狀態，示例：

```jsx
/*
	錯誤，counter 的新狀態依賴於之前的 this.state.counter 和 this.props.increment
	若 setState() 調用時 this.props.increment 也發生更新操作或 this.state.counter 還有其它 setState() 更新方式，則這些可能會被合併到一次更新中，造成狀態更新錯誤
*/
this.setState({
	counter: this.state.counter + this.props.increment
})
```

正確的做法是將`setState()`方法中的參數由**JSON對象**替換爲**方法**，
被替換的方法應帶有兩個參數，前一個參數爲之前的`state`，後一個參數爲之前的`props`，示例：

```jsx
// 正確，使用方法代替JSON對象，從方法參數中獲取之前地狀態，保證狀態正確更新
this.setState((prevState, props) => {
	counter: prevState.counter + props.increment
})
```

## Lifecycle Methods (生命週期方法)
在組件的生命週期中，首次被渲染爲DOM時，在React中被稱爲**掛載**(`mounting`)；
在組件被從DOM樹中移除時，在React中被稱爲**卸載**(`unmounting`)。

通過在組件類中定義`componentDidMount()`、`componentWillUnmount()`方法可在組件掛載、卸載時添加額外的邏輯。
示例：

```jsx
class MyComponent extends Component {

	componentDidMount() {
		// 組件DOM渲染完畢時，執行該方法中的邏輯
	}

	componentWillUnmount() {
		// 組件DOM被移除時，執行該方法中的邏輯
	}

	render = () => ...

}
```

- `componentDidMount()`方法通常用於初始化一些依賴於DOM的資源，一般與DOM無關的資源可直接放在構造方法中，
componentDidMount()方法執行時保證DOM已被渲染完畢。
- `componentWillUnmount()`方法用法類似`C++`中的**析構函數**，通常用於在組件卸載時執行一些清理操作(如**定時器**等)。



# 路由
React項目提供了官方的路由組件`React Router`。
React Router當前主流的版本爲`3.x`和`4.x+`，從`4.x`版本開始，API相對`3.x`版有較大改動，本文以`4.x+`API爲準。

React Router擁有兩個實現：

- 基於DOM，用於WEB開發的`React Router DOM`
- 用於移動開發的`React Router Native`

React Router的詳細介紹參考[官方文檔](https://reacttraining.com/react-router)。

## 安裝
React Router並未直接包含在React中，需要使用npm單獨安裝：

```
$ npm install react-router-dom //React Router DOM
$ npm install react-router-native //React Router Native
```

## Router
根據使用場景的區別，React Router提供了以下幾類Router：

- `BrowserRouter`

	BrowserRouter使用HTML5提供的`history API`(`pushState()`, `replaceState()`、`popstate`事件)來保持UI和URL的同步。
	BrowserRouter常用於支持HTML5的現代瀏覽器中。

- `HashRouter`

	HashRouter使用URL的`hash`(如：`window.location.hash`)來保持UI和URL的同步。
	HashRouter用在不支持HTML5的舊式瀏覽器中。

- `StaticRouter`

	StaticRouter並不改變地址，常用於服務端渲染的場景下。

- `MemoryRouter`

	MemoryRouter將歷史URL保存在內存中(不從地址欄中讀取/寫入URL)。
	MemoryRouter常用於測試環境或非瀏覽器環境(如`React Native`)。

將需要使用路由功能的組件置於`<Router />`標籤內部。
通常直接將頁面的根組件置於`<Router />`標籤中：

```jsx
import React, { Component } from "react"
import ReactDOM from "react-dom"
import { BrowserRouter } from "react-router-dom"

class App extends Component {
	...
}

ReactDOM.render(
	<BrowserRouter>
		<App />
	</BrowserRouter>,
	document.getElementById("root")
)
```



# 常見錯誤
React開發中的踩坑記錄。

## Uncaught ReferenceError: $ is not defined
使用`Webpack`打包，不能以常規方式使用JQuery，需要在Webpack配置中使用JQuery插件：

```js
new webpack.ProvidePlugin({
	$: 'jquery',
	jQuery: 'jquery'
})
```

## Target container is not a DOM element.
在`React`項目中，使用`Webpack`打包生成js文件時，生成的js文件應在主Html文件的最後(至少需要在被渲染的元素出現之後)導入。
若在`<head>`標籤中導入生成的js，React執行時會出現`Target container is not a DOM element.`錯誤，
原因是加載js時DOM尚未創建完畢。

示例：

```html
<!DOCTYPE html>
<html lang="zh-cn">
<head>
	<meta charset="UTF-8">
	<title>Xxx</title>
	<!-- <script src="./build/bundle.js"></script> 錯誤，在<head>標籤內導入js會出現錯誤 -->
</head>
<body>
	<div id="main"></div> <!-- 假設需要被渲染的節點id爲 main -->
	<!-- <script src="./build/bundle.js"></script> 正確，在被渲染的元素出現後加載js，能夠正常渲染元素 -->
</body>
<script src="./build/bundle.js"></script> <!-- 正確，在HTML頁面底部導入JS，此時DOM已被加載完畢 -->
</html>
```

## Warning: Each child in an array or iterator should have a unique "key" prop.
使用數組承載組件或使用`map`函數通過數組批量生成組件時，數組內的每一個組件需要設置唯一的`key`屬性，
否則會在運行期間得到告警信息。

示例：

```jsx
// 提示需要 key 屬性
[<Component1 />,
<Component2 />,
...]

// 正確
[<Component1 key={1}/>,
<Component2 key={2}/>,
...]
```
