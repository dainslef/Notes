## 简介
`npm`是`JavaScript`代码的包管理器，类似于`Python`的`pip`，`Ruby`的`gem`。  
`npm`也是`Node.js`项目的模块管理工具。



## 安装与配置
`npm`通常包含在`Node.js`中，安装Node.js时会一同安装npm。
主流的`Linux`发行版中已经包含了`Node.js`，以`ArchLinux`为例：

```
# pacman -S nodejs
```

常用的npm指令：

- `install` 安装模块
- `update` 更新模块
- `list` 列出当前路径的包依赖树
- `config` 调整npm配置



## 安装模块
使用`npm install`指令安装Node.js模块或JavaScript包：

```
$ npm install 包名
# npm install -g 包名
```

默认模块将安装在当前路径的`node_modules`路径下，使用`-g`参数可将模块安装在**全局路径**下。

部分模块带有可执行的`CLI`工具：

- 安装在**当前目录**时会在`项目路径/node_modules/.bin`路径下创建可执行脚本的符号链接。
- 安装在**全局目录**时会在根据操作系统类型在对应的bin路径下创建脚本的符号链接。

在`Linux/macOS`中，全局安装的模块工具在`/usr/local/bin`下创建符号链接，通常该目录已被加入`PATH`环境变量中，即全局安装的工具模块可直接执行。  
在`Windows`中，全局安装的模块工具在**Node.js安装目录**下创建符号链接，需要将该路径手动加入`PATH`中。

从`npm 5.2.0`开始，npm包管理器会自带`npx`指令，npx指令可用于执行安装在**全局路径/当前路径**下的工具模块，免去了配置环境变量的步骤。



## *Serve*
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

### 配置 *SPA*
`SPA`(**Single Web Page Application，单页WEB应用**)是当今主流的WEB呈现方式，配置SPA需要WEB服务器将路由发往同一个入口页面。  
Serve为单页应用提供了内置的参数，使用`-s`参数即可在路由没有匹配资源时指向默认的`index.html`页面。  
如下所示：

```
$ serve -s 目标路径
```
