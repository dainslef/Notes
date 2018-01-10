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
