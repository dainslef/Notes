## 简介
`React`是一套JavaScript库，提供了组件化方式来构建`WEB UI`。

官网中提到的React的优势：

- 让创建交互式UI变得简单。为应用的中每个状态创建简单的视图，当状态变化时，React会高效地渲染正确的组件。
- 封装组件来管理拥有的状态，通过组合组件来构建复杂的UI。使用JaveSript代替模板来编写组件逻辑，开发者可以简单地在程序中传递复杂的数据同时将状态保存在`DOM`之外。
- React不仅仅可用于构建`WEB UI`，还有用于移动端的`React Native`。



## 安装与配置
推荐使用`npm`来创建React项目，管理项目依赖。



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
