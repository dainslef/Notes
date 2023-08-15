<!-- TOC -->

- [簡介](#簡介)
- [安裝與配置](#安裝與配置)
	- [Mirror](#mirror)
- [安裝模塊](#安裝模塊)
	- [查看已安裝模塊](#查看已安裝模塊)
- [Serve](#serve)
	- [配置 SPA](#配置-spa)
- [常見錯誤](#常見錯誤)
	- [npm WARN tar zlib error: unexpected end of file](#npm-warn-tar-zlib-error-unexpected-end-of-file)
	- [npm ERR! Unexpected end of JSON input while parsing near '...rcemaps-apply":"lates'](#npm-err-unexpected-end-of-json-input-while-parsing-near-rcemaps-applylates)

<!-- /TOC -->



# 簡介
`npm`是`JavaScript`代碼的包管理器，類似於Python的`pip`，Ruby的`gem`。
npm也是`Node.js`項目的模塊管理工具。



# 安裝與配置
npm通常包含在`Node.js`中，安裝Node.js時會一同安裝npm。
主流的Linux發行版中已經包含了Node.js，以`ArchLinux`爲例，安裝npm：

```
# pacman -S nodejs
```

常用的npm指令：

- `install` 安裝模塊
- `update` 更新模塊
- `list` 列出當前路徑的包依賴樹
- `config` 調整npm配置

## Mirror
npm默認的鏡像地址位於海外：

```
$ npm config get registry
https://registry.npmjs.org/
```

牆內可能無法訪問，可將鏡像倉庫地址替換為淘寶npm鏡像：

```
$ npm config set registry https://registry.npm.taobao.org
```

使用淘寶鏡像會導致npm搜索功能失效：

```
$ npm search npm
npm WARN search fast search endpoint errored. Using old search.
npm WARN Failed to read search cache. Rebuilding
npm WARN Building the local index for the first time, please be patient
npm WARN Search data request failed, search might be stale
npm ERR! No search sources available

npm ERR! A complete log of this run can be found in:
npm ERR!     /Users/dainslef/.npm/_logs/xxx-debug.log
```

重新將鏡像修改為官方鏡像後搜索功能恢復正常：

```
$ npm config set registry https://registry.npmjs.org
$ npm search npm
NAME                      | DESCRIPTION          | AUTHOR          | DATE       | VERSION  | KEYWORDS
npm                       | a package manager…   | =adam_baldwin…  | 2019-12-11 | 6.13.4   | install modules package man
...
```

安裝淘寶鏡像包可以使用cnpm，cnpm功能與npm基本類似：

```
$ npm install -g cnpm
```



# 安裝模塊
使用`npm install`指令安裝Node.js模塊或JavaScript包：

```html
$ npm install 包名
# npm install -g 包名 <!-- 安裝模塊到全局路徑下 -->
```

默認模塊將安裝在當前路徑的`node_modules`路徑下，使用`-g`參數可將模塊安裝在**全局路徑**下。

部分模塊帶有可執行的CLI工具：

- 安裝在**當前目錄**時會在`項目路徑/node_modules/.bin`路徑下創建可執行腳本的符號鏈接。
- 安裝在**全局目錄**時會在根據操作系統類型在對應的bin路徑下創建腳本的符號鏈接。

在`Linux/macOS`中，全局安裝的模塊工具在`/usr/local/bin`下創建符號鏈接，通常該目錄已被加入`PATH`環境變量中，
即全局安裝的工具模塊可直接執行。
在`Windows`中，全局安裝的模塊工具在**Node.js安裝目錄**下創建符號鏈接，需要將該路徑手動加入`PATH`中。

從`npm 5.2.0`開始，npm包管理器會自帶`npx`指令，npx指令可用於執行安裝在**全局路徑/當前路徑**下的工具模塊，
免去了配置環境變量的步驟。

使用`npm update`更新模塊：

```html
$ npm update <!-- 更新當前目錄下的所有模塊 -->
$ npm update 包名 <!-- 更新當前目錄下的指定模塊 -->

# npm update -g <!-- 更新所有全局模塊 -->
# npm update -g 包名 <!-- 更新指定全局模塊 -->
```

## 查看已安裝模塊
使用`npm ls/list`相關指令查看已安裝模塊。

直接使用`npm ls/list`指令會以當前路徑做爲模塊根目錄，以樹狀呈現當前模塊的依賴。
以一個React項目爲例，`package.json`中定義的模塊依賴信息：

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

使用`npm ls/list`輸出依賴信息，如下所示：

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

直接使用`npm ls`命令會遞歸計算並輸出模塊所有的依賴，一些大型模塊(如`Webpack`)有複雜的依賴樹，
會在終端輸出大量的依賴信息。
使用`depth`參數會限制輸出依賴的層數，當設置`--depth=0`時僅輸出**主動設置**的依賴：

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

此時輸出的依賴信息即爲模塊`package.json`中定義的模塊依賴(`dependencies + devDependencies`)。



# Serve
`Serve`是一個簡單的基於Node.js的靜態WEB服務器。
Serve提供了常見的靜態服務器參數，併爲**單頁WEB應用**提供了參數，
相比`Apache`、`Nginx`等傳統WEB服務器在配置上更加簡單。
Serve亦是React項目推薦的默認WEB服務器。

安裝Serve：

```
$ npm install -g serve
```

使用Serve啓動WEB服務需要目標路徑下包含`index.html`頁面，默認路由將指向該頁面。

啓動Serve服務：

```html
$ serve <!-- 在當前路徑下啓動WEB服務 -->
$ serve 目標路徑 <!-- 在目標路徑下啓動WEB服務 -->
```

## 配置 SPA
`SPA`(**Single Web Page Application，單頁WEB應用**)是當今主流的WEB呈現方式，
配置SPA需要WEB服務器將路由發往同一個入口頁面。
Serve爲單頁應用提供了內置的參數，使用`-s`參數即可在路由沒有匹配資源時指向默認的`index.html`頁面。
示例：

```
$ serve -s 目標路徑
```



# 常見錯誤
常見npm相關錯誤記錄。

## npm WARN tar zlib error: unexpected end of file
錯誤原因：<br>
部分包未完全下載，或下載文件校驗不通過，安裝時使用緩存的錯誤文件安裝導致安裝失敗。

解決方法：<br>
執行`npm clean --force`清理緩存

## npm ERR! Unexpected end of JSON input while parsing near '...rcemaps-apply":"lates'
錯誤原因：<br>
部分緩存中的軟件包可能未能正確下載。

解決方法：<br>
查看對應錯誤日誌，清理錯誤的npm包緩存。
