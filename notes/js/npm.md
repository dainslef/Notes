- [简介](#简介)
- [安装与配置](#安装与配置)
- [安装模块](#安装模块)
	- [查看已安装模块](#查看已安装模块)
- [Serve](#serve)
	- [配置 SPA](#配置-spa)
- [常见错误](#常见错误)
	- [npm WARN tar zlib error: unexpected end of file](#npm-warn-tar-zlib-error-unexpected-end-of-file)



# 简介
`npm`是`JavaScript`代码的包管理器，类似于Python的`pip`，Ruby的`gem`。
npm也是`Node.js`项目的模块管理工具。



# 安装与配置
npm通常包含在`Node.js`中，安装Node.js时会一同安装npm。
主流的Linux发行版中已经包含了Node.js，以`ArchLinux`为例，安装npm：

```
# pacman -S nodejs
```

常用的npm指令：

- `install` 安装模块
- `update` 更新模块
- `list` 列出当前路径的包依赖树
- `config` 调整npm配置



# 安装模块
使用`npm install`指令安装Node.js模块或JavaScript包：

```c
$ npm install 包名
# npm install -g 包名 // 安装模块到全局路径下
```

默认模块将安装在当前路径的`node_modules`路径下，使用`-g`参数可将模块安装在**全局路径**下。

部分模块带有可执行的CLI工具：

- 安装在**当前目录**时会在`项目路径/node_modules/.bin`路径下创建可执行脚本的符号链接。
- 安装在**全局目录**时会在根据操作系统类型在对应的bin路径下创建脚本的符号链接。

在`Linux/macOS`中，全局安装的模块工具在`/usr/local/bin`下创建符号链接，通常该目录已被加入`PATH`环境变量中，
即全局安装的工具模块可直接执行。
在`Windows`中，全局安装的模块工具在**Node.js安装目录**下创建符号链接，需要将该路径手动加入`PATH`中。

从`npm 5.2.0`开始，npm包管理器会自带`npx`指令，npx指令可用于执行安装在**全局路径/当前路径**下的工具模块，
免去了配置环境变量的步骤。

使用`npm update`更新模塊：

```c
$ npm update // 更新當前目錄下的所有模塊
$ npm update 包名 // 更新當前目錄下的指定模塊

# npm update -g // 更新所有全局模塊
# npm update -g 包名 // 更新指定全局模塊
```

## 查看已安装模块
使用`npm ls/list`相关指令查看已安装模块。

直接使用`npm ls/list`指令会以当前路径做为模块根目录，以树状呈现当前模块的依赖。
以一个React项目为例，`package.json`中定义的模块依赖信息：

```json
{
	...
	"dependencies": {
		"react": "^16.2.0",
		"react-dom": "^16.2.0",
		"react-redux": "^5.0.6",
		"react-router": "^4.2.0",
		"redux": "^3.7.2"
	},
	"devDependencies": {
		"babel-core": "^6.26.0",
		"babel-loader": "^7.1.2",
		"babel-preset-es2015": "^6.24.1",
		"babel-preset-react": "^6.24.1",
		"webpack": "^3.10.0",
		"webpack-dev-server": "^2.9.7"
	},
	...
}
```

使用`npm ls/list`输出依赖信息，如下所示：

```
$ npm ls
test-react@0.0.1 /Users/dainslef/Downloads/WorkSpace/test-react
├─┬ react@16.2.0
│ ├─┬ fbjs@0.8.16
│ │ ├── core-js@1.2.7
│ │ ├─┬ isomorphic-fetch@2.2.1
│ │ │ ├─┬ node-fetch@1.7.3
│ │ │ │ ├─┬ encoding@0.1.12
│ │ │ │ │ └── iconv-lite@0.4.19 deduped
│ │ │ │ └── is-stream@1.1.0
│ │ │ └── whatwg-fetch@2.0.3
│ │ ├── loose-envify@1.3.1 deduped
│ │ ├── object-assign@4.1.1 deduped
│ │ ├─┬ promise@7.3.1
│ │ │ └── asap@2.0.6
│ │ ├── setimmediate@1.0.5
│ │ └── ua-parser-js@0.7.17
│ ├─┬ loose-envify@1.3.1
│ │ └── js-tokens@3.0.2 deduped
│ ├── object-assign@4.1.1
│ └── prop-types@15.6.0 deduped
...
```

直接使用`npm ls`命令会递归计算并输出模块所有的依赖，一些大型模块(如`Webpack`)有复杂的依赖树，
会在终端输出大量的依赖信息。
使用`depth`参数会限制输出依赖的层数，当设置`--depth=0`时仅输出**主动设置**的依赖：

```
$ npm ls --depth=0
test-react@0.0.1 /Users/dainslef/Downloads/WorkSpace/test-react
├── babel-core@6.26.0
├── babel-loader@7.1.2
├── babel-preset-es2015@6.24.1
├── babel-preset-react@6.24.1
├── react@16.2.0
├── react-dom@16.2.0
├── react-redux@5.0.6
├── react-router@4.2.0
├── redux@3.7.2
├── webpack@3.10.0
└── webpack-dev-server@2.9.7
```

此时输出的依赖信息即为模块`package.json`中定义的模块依赖(`dependencies + devDependencies`)。



# Serve
`Serve`是一个简单的基于Node.js的静态WEB服务器。
Serve提供了常见的静态服务器参数，并为**单页WEB应用**提供了参数，相比`Apache`、`Nginx`等传统WEB服务器在配置上更加简单。
Serve亦是React项目推荐的默认WEB服务器。

安装Serve：

```
$ npm install -g serve
```

使用Serve启动WEB服务需要目标路径下包含`index.html`页面，默认路由将指向该页面。

启动Serve服务：

```
$ serve //在当前路径下启动WEB服务
$ serve 目标路径 //在目标路径下启动WEB服务
```

## 配置 SPA
`SPA`(**Single Web Page Application，单页WEB应用**)是当今主流的WEB呈现方式，配置SPA需要WEB服务器将路由发往同一个入口页面。
Serve为单页应用提供了内置的参数，使用`-s`参数即可在路由没有匹配资源时指向默认的`index.html`页面。
如下所示：

```
$ serve -s 目标路径
```



# 常见错误
常见`npm`相关错误记录。

## npm WARN tar zlib error: unexpected end of file
错误原因：<br>
部分包未完全下载，或下载文件校验不通过，安装时使用缓存的错误文件安装导致安装失败。

解决方法：<br>
执行`npm clean --force`清理缓存

## npm ERR! Unexpected end of JSON input while parsing near '...rcemaps-apply":"lates'
错误原因：<br>
部分缓存中的软件包可能未能正确下载。

解决方法：<br>
查看对应错误日志，清理错误的npm包缓存。
