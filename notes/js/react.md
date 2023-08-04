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
	- [Lists & Keys](#lists--keys)
- [Hooks](#hooks)
	- [State Hook (useState())](#state-hook-usestate)
	- [Effect Hook (useEffect() / useLayoutEffect())](#effect-hook-useeffect--uselayouteffect)
		- [Layout Effect](#layout-effect)
		- [組件更新](#組件更新)
		- [Effect Hook 完整示例](#effect-hook-完整示例)
	- [useRef()](#useref)
	- [useImperativeHandle() & forwardRef()](#useimperativehandle--forwardref)
- [路由](#路由)
	- [安裝](#安裝)
	- [Router](#router)
	- [Route](#route)
	- [Switch & Redirect](#switch--redirect)
	- [match & location & history](#match--location--history)
	- [withRouter](#withrouter)
- [常見錯誤](#常見錯誤)
	- [Uncaught ReferenceError: $ is not defined](#uncaught-referenceerror--is-not-defined)
	- [Target container is not a DOM element.](#target-container-is-not-a-dom-element)
	- [Warning: Each child in an array or iterator should have a unique "key" prop.](#warning-each-child-in-an-array-or-iterator-should-have-a-unique-key-prop)
	- [StrictMode](#strictmode)

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
直接配置React項目較爲複雜，Facebook爲React項目提供了官方的項目創建工具
[`create-react-app`](https://github.com/facebook/create-react-app)。

直接通過`npx`使用create-react-app創建React項目：

```html
$ npx create-react-app 項目名稱 <!-- 通過npx執行create-react-app，會自動安裝 -->
```

亦可使用npm安裝後使用：

```html
$ npm install -g create-react-app
$ create-react-app 項目名稱 <!-- 若已配置Node.js相關環境變量，可直接使用create-react-app指令 -->
```

創建的React項目預置了以下npm指令：

```html
$ npm start <!-- 啓動開發服務器，默認爲3000端口 -->
$ npm test <!-- 啓動測試服務器 -->
$ npm run build <!-- 構建項目的生產版本(Release)，輸出到項目根目錄的 build 路徑下 -->
```

## 項目結構
使用create-react-app新創建的React項目具有以下結構：

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

## Lists & Keys
Keys用於幫助react識別被修改、添加、更新的內容。以數組形式組合多個組件時，每個組件需要需要提供穩定的標識符(key)，示例：

```js
const numbers = [1, 2, 3, 4, 5]
const listItems = numbers.map(number =>
	<li key={number.toString()}>
		{number}
	</li>
)
```

key的最佳使用方法是使用文本作為來唯一標誌一組兄弟節點中的某一個。
最常用的方式是使用的數據ID作為key：

```js
const todoItems = todos.map(todo =>
	<li key={todo.id}>
		{todo.text}
	</li>
)
```

當數據沒有穩定ID時，使用數組索引作為key時最簡單的方式：

```js
const todoItems = todos.map((todo, index) =>
	// Only do this if items have no stable IDs
	<li key={index}>
		{todo.text}
	</li>
)
```

若數組內的組件會改變次序，則不應使用索引作為key，這會導致性能以及組件的狀態問題，
具體可參考此博客[Index as a key is an anti-pattern](https://medium.com/@robinpokorny/index-as-a-key-is-an-anti-pattern-e0349aece318)。



# Hooks
React自`16.8`版本開始引入了`Hooks`機制，能夠在不編寫class的條件下使用state以及其它React特性。
Hooks不包含破壞性的改動，完全與之前兼容，React團隊也不會移除基於class的組建特性。

Hooks的出現是為了解決之前的某些問題：

- 組建之間的狀態相關邏輯難以復用
- 複雜組件難以被理解
- Class組件會同時使開發者和機器困惑

更多詳細介紹，可參見[官方文檔](https://reactjs.org/docs/hooks-reference.html)。

## State Hook (useState())
`State Hook`用於在函數式組件中添加本地狀態，將組件重新渲染時保存狀態。
在傳統的class組件中，狀態保存在類的成員對象`state`中，使用成員的成員方法`this.setState()`更新狀態。
使用State Hook則通過`useState()`函數創建狀態字段，useState()函數接收屬性的初始值作為參數，
執行返回長度為2的數組，包含該字段和響應的更新更新函數。
使用示例：

```jsx
// create a state variable called "count" with initial value 0
const [count, setCount] = useState(0)
```

API在ts中的詳細定義：

```ts
/**
 * Returns a stateful value, and a function to update it.
 */
function useState<S>(initialState: S | (() => S)): [S, Dispatch<SetStateAction<S>>];

// convenience overload when first argument is ommitted
/**
 * Returns a stateful value, and a function to update it.
 */
function useState<S = undefined>(): [S | undefined, Dispatch<SetStateAction<S | undefined>>];
```

使用State Hook改寫基於ES6 Class組件的完整示例：

```jsx
import React, { useState } from 'react';

// use class based component
class Example extends React.Component {

	state = {
		count: 0
	}

	render() =>
		<div>
			<p>You clicked {this.state.count} times</p>
			<button onClick={() => this.setState({ count: this.state.count + 1 })}>
				Click me
			</button>
		</div>
}

// use State Hook
const Example = () => {
	// Declare a new state variable, which we'll call "count"
	const [count, setCount] = useState(0)
	return <div>
		<p>You clicked {count} times</p>
		<button onClick={() => setCount(count + 1)}>
			Click me
		</button>
	</div>
}
```

## Effect Hook (useEffect() / useLayoutEffect())
`Effect Hook`允許開發者在函數式組件中執行帶有**副作用**(side effects)的行為。
Effect Hook的用於提供類似ES6組件中生命週期方法(lifecycle methods)類似的功能，
近似於`componentDidMount(), componentDidUpdate(), componentWillUnmount(), componentWillUpdate()`等方法的組合。

Effect Hook中使用`useEffect()`函數，將ES6組件中對應生命週期函數內的邏輯寫入其中。
簡單的使用示例：

```jsx
useEffect(() => {
	// do something before component mount (componentDidMount(), componentDidUpdate()) ...
	return () => ... // do something before component umount (componentWillUnmount(), componentWillUpdate()) ...
}, [/* dependency args... */])
```

API在ts中的詳細定義：

```ts
// TODO (TypeScript 3.0): ReadonlyArray<unknown>
type DependencyList = ReadonlyArray<any>;

// NOTE: callbacks are _only_ allowed to return either void, or a destructor.
// The destructor is itself only allowed to return void.
type EffectCallback = () => (void | (() => void | undefined));

/**
 * Accepts a function that contains imperative, possibly effectful code.
 *
 * @param effect Imperative function that can return a cleanup function
 * @param deps If present, effect will only activate if the values in the list change.
 *
 * @version 16.8.0
 * @see https://reactjs.org/docs/hooks-reference.html#useeffect
 */
function useEffect(effect: EffectCallback, deps?: DependencyList): void;
```

useEffect()函數接收一個無參數Lambda：

- 該Lambda中的內容等價於寫在ES6組件的componentDidMount()/componentDidUpdate()中的內容。
- 該Lambda可以選擇是否帶有返回值，若存在返回值應為`() => void`簽名的Lambda，
該Lambda的內容等價於寫在ES6組件生命週期方法中componentWillUnmount()中的內容。

### Layout Effect
React中還提供了`useLayoutEffect()`，API在ts中的詳細定義：

```ts
/**
 * The signature is identical to `useEffect`, but it fires synchronously after all DOM mutations.
 * Use this to read layout from the DOM and synchronously re-render. Updates scheduled inside
 * `useLayoutEffect` will be flushed synchronously, before the browser has a chance to paint.
 *
 * Prefer the standard `useEffect` when possible to avoid blocking visual updates.
 *
 * If you’re migrating code from a class component, `useLayoutEffect` fires in the same phase as
 * `componentDidMount` and `componentDidUpdate`.
 *
 * @version 16.8.0
 * @see https://reactjs.org/docs/hooks-reference.html#uselayouteffect
 */
function useLayoutEffect(effect: EffectCallback, deps?: DependencyList): void;
```

該Hook於`useEffect()`簽名完全相同，但運行時機不同：

- useEffect()發生在render()結束後，不會阻塞瀏覽器的繪製。
- useLayoutEffect()發生在瀏覽器的繪製操作之前，通常用於處理DOM，該Hook中的操作會在DOM變更後立即執行，
該Hook執行完畢後瀏覽器才開始繪製，因而會阻塞瀏覽器的繪製操作。
- 兩種Effect Hook的運行順序為`useLayoutEffect() => DOM渲染完成 => useEffect()`。

### 組件更新
在Effect Hook中，沒有直接等價於componentDidMount()的方法，
useEffect()函數的在不使用依賴參數(可選，第二參數)的情況下，函數中的邏輯在每次組件初始化以及更新時均會執行。

要避免useEffect()中的邏輯在每次組件渲染中重複更新，則可指定依賴參數(第二參數，數組類型)，
傳入依賴參數後僅當依賴參數值發生變化才會執行函數體。

依賴參數可以傳入**空數組**，此時函數內的邏輯相當於寫在componentDidMount()中，僅在組件首次渲染時執行。

### Effect Hook 完整示例
使用Effect Hook改寫基於ES6 Class組件的完整示例：

```js
import React, { useEffect } from 'react';

// use ES6 class based component
class Example extends React.Component {

	componentDidMount() {
		alert("Component did mount...")
	}

	componentWillUnmount() {
		alert("Component will unmount...")
	}

	componentDidUpdate() {
		alert("Component did update...")
	}

	componentWillUpdate() {
		alert("Component will update...")
	}

	render() => <div></div>
}

// use Effect Hook
const Example = () => {
	useEffect(() => {
		// with empty dependency array, these code will only execute when component first load
		alert("Component did mount...")
		return () => alert("Component will unmount...")
	}, [])
	useEffect(() => {
		// without dependency args, these code will execute when the component rerender each time
		alert("Component did update...")
		return () => alert("Component will update...")
	})
  return <div></div>
}
```

## useRef()
`useRef()`返回一個可變引用對象，該對象的`.current`屬性被賦值為傳入的初始化參數(initialValue)；
該對象在整個組件的生命週期中都將保持。
API在ts中的詳細定義：

```ts
/**
 * `useRef` returns a mutable ref object whose `.current` property is initialized to the passed argument
 * (`initialValue`). The returned object will persist for the full lifetime of the component.
 *
 * Note that `useRef()` is useful for more than the `ref` attribute. It’s handy for keeping any mutable
 * value around similar to how you’d use instance fields in classes.
 *
 * @version 16.8.0
 * @see https://reactjs.org/docs/hooks-reference.html#useref
 */
// TODO (TypeScript 3.0): <T extends unknown>
function useRef<T>(initialValue: T): MutableRefObject<T>;

// convenience overload for refs given as a ref prop as they typically start with a null value
/**
 * `useRef` returns a mutable ref object whose `.current` property is initialized to the passed argument
 * (`initialValue`). The returned object will persist for the full lifetime of the component.
 *
 * Note that `useRef()` is useful for more than the `ref` attribute. It’s handy for keeping any mutable
 * value around similar to how you’d use instance fields in classes.
 *
 * Usage note: if you need the result of useRef to be directly mutable, include `| null` in the type
 * of the generic argument.
 *
 * @version 16.8.0
 * @see https://reactjs.org/docs/hooks-reference.html#useref
 */
// TODO (TypeScript 3.0): <T extends unknown>
function useRef<T>(initialValue: T|null): RefObject<T>;

// convenience overload for potentially undefined initialValue / call with 0 arguments
// has a default to stop it from defaulting to {} instead
/**
 * `useRef` returns a mutable ref object whose `.current` property is initialized to the passed argument
 * (`initialValue`). The returned object will persist for the full lifetime of the component.
 *
 * Note that `useRef()` is useful for more than the `ref` attribute. It’s handy for keeping any mutable
 * value around similar to how you’d use instance fields in classes.
 *
 * @version 16.8.0
 * @see https://reactjs.org/docs/hooks-reference.html#useref
 */
// TODO (TypeScript 3.0): <T extends unknown>
function useRef<T = undefined>(): MutableRefObject<T | undefined>;
```

簡單的使用示例：

```js
const refContainer = useRef(initialValue)
```

useRef()的一個常用用法是獲取子組件的引用，用與在事件中操作子組件：

```js
const Example = () => {
	const inputEl = useRef(null)
	const onButtonClick = () => {
		// `current` points to the mounted text input element
		inputEl.current.focus()
	}
	return
		<div>
			<input ref={inputEl} type="text" />
			<button onClick={onButtonClick}>Focus the input</button>
		<div/>
}
```

useRef()會在組件的每次渲染中提供相同的對象引用，引用對象不會因為組件重新渲染而變化。
useRef()同樣也不會在內部對象發生變化時發送通知，修改useRef()提供對象的內容也不會引起組件的重新渲染(區別於useState())。
當組件內部存在一些可變屬性需要修改，但又不希望修改屬性造成組件重新渲染時可使用useRef()替代useState()。

## useImperativeHandle() & forwardRef()
通過useRef()可訪問子組件的引用，但對於函數式組件，
僅獲取子組件引用無法如Class組件直接一樣訪問其內部方法；
需要使用`useImperativeHandle()`為引用添加對外暴露的方法，
同時將組件包含在`forwardRef()`方法中導出。

示例：

```js
import {forwardRef, useImperativeHandle, useRef} from 'react'

const Child = forwardRef((props, ref) => {
  // 調用 useImperativeHandle() 函數為對象的引用創建外部訪問方法
  useImperativeHandle(ref, () => ({
    childFunction1() { ... },
    childFunction2 = () => ...,
  }))

  return
    <div>
      <h2>child content</h2>
    </div>
})

export default function Parent() {
  const childRef = useRef(null)

  const handleClick = () => {
    // 通過引用的current對象訪問方法
    childRef.current.childFunction1()
    childRef.current.childFunction2()
  }

  return
    <div>
      <Child ref={childRef} />
      <h2>parent content</h2>
      <button onClick={handleClick}>Call child functions</button>
    </div>
}
```



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

## Route
使用`<Route />`標籤定義一個路由並綁定組件，當請求路徑匹配路由時顯示標籤綁定的組件：

```xml
<BrowserRouter>
	<div>
		<!-- 使用exact屬性則路徑需要完整匹配 -->
		<Route exact path="/">
			<Xxx />
		</Route>
		<!-- 綁定的組件可以寫在Route標籤內容中 -->
		<Route path="/xxx2">
			<Xxx2 />
		</Route>
		<!-- Route也可以寫成自閉和的形式，綁定的組件也可以寫在component屬性中 -->
		<Route path="/xxx3" component={Xxx3} />
	</div>
</BrowserRouter>
```

多個Route標籤匹配路徑時這些Route標籤對應的組件均會顯示。

Route標籤常用屬性說明：

| 屬性 | 說明 |
| :- | :- |
| path | 定義路由路徑 |
| component | 定義路由綁定的組件 |
| exact | 是否要求路徑完全匹配(默認路徑匹配規將定義路徑的子路徑也同樣視為匹配) |

## Switch & Redirect
每個Route標籤在匹配到路徑時均會顯示組件內容，而搭配Switch標籤時，只會展示第一個匹配到的組件，示例；

```xml
<BrowserRouter>
	<Switch>
		<Route path="/xxx1" component={Xxx1} />
		<Route path="/xxx2" component={Xxx2} />
		<Route path="/xxx3" component={Xxx3} />
	</Switch>
</BrowserRouter>
```

當輸入路徑`/xxx1`時，僅會展示Xxx1組件，其餘組件不展示。

Redirect標籤則可以在所有路由不匹配時跳轉到一個默認的路由，示例：

```xml
<BrowserRouter>
	<Switch>
		<Route path="/xxx1" component={Xxx1} />
		<Route path="/xxx2" component={Xxx2} />
		<Route path="/xxx3" component={Xxx3} />
		<Redirect to="/xxx1">
	</Switch>
</BrowserRouter>
```

當輸入任意一個不匹配所有路由的路徑時，全部重定向到`/xxx1`路徑。

## match & location & history
Route標籤會為綁定的組件的props中附加`match、location、history`等一系列屬性，可用於訪問歷史記錄、路由信息等。

- `match`

	match對象包含了路徑是如何與路由進行匹配的詳細信息，結構示例：

	```js
	{
		isExact: true
		params: {
			id: "2"
		}
		path: "/users/:id"
		url: "/users/2"
	}
	```

- `location`

	location對象表示應用的位置信息，結構示例：

	```js
	{
		key: 'ac3df4', // not with HashHistory!
		pathname: '/somewhere',
		search: '?some=search-string',
		hash: '#howdy',
		state: {
			[userDefined]: true
		}
	}
	```

- `history`

	history對象提供了對歷史記錄訪問、路由跳轉等功能，主要屬性、方法說明：

	| 屬性/方法 | 說明 |
	| :- | :- |
	| length | (number) 歷史記錄總條數 |
	| action | (string) 當前操作("PUSH"/"REPLACE"/"POP") |
	| location | 當前的location對象 |
	| push(path, [state]) | 歷史紀錄棧中添加一條新記錄 |
	| replace(path, [state]) | 替換當前歷史紀錄 |
	| go(n) | 以當前條目為基準，在歷史記錄棧中的移動n個條目 |
	| goBack() | 等價於 go(1) |
	| goForward() | 等價於 go(-1) |

## withRouter
在`4.x+`版本中，在非路由組件中訪問路由信息需要使用`withRouter()`函數包裝組件，示例：

```jsx
import React from "react"
import { withRouter } from "react-router"

class ShowTheLocation extends React.Component {
	render() {
		// 導出組件時使用withRouter()函數後，組件內部的props中會附加一系列屬性
		const { match, location, history } = this.props
		return <div>You are now at {location.pathname}</div>
	}
}

// 導出組件時使用withRouter()函數包裝
export default withRouter(ShowTheLocation)
```

若使用Hooks，同樣可將函數式組件作為參數傳入`withRouter()`函數中並導出，
對於函數式組件而言，`match、location、history`等屬性可通過解構參數得到，上述示例使用Hooks可改寫為：

```jsx
import React from "react"
import { withRouter } from "react-router"

// 導出組件時使用withRouter()函數包裝
export default withRouter(
	({ match, location, history }) => // 解構參數，獲取目標屬性
	<div>You are now at {location.pathname}</div>
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
[<Component1 key={"component1_key_xxx..."}/>,
<Component2 key={"component2_key_xxx..."}/>,
...]
```

## StrictMode
[`StrictMode`](https://react.dev/reference/react/StrictMode)用於在開發中儘早發現BUG：

```jsx
<StrictMode>
  <App />
</StrictMode>
```

StrictMode下會啟用下列特性：

- 組件會被額外宣染一次（用於發現impure rendering（非純淨宣染）相關的問題）
- 組件會額外執行Effects一次（用於發現缺失Effect清理相關的問題）
- 會檢查組件中使用的廢棄API
