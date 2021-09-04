<!-- TOC -->

- [概述](#概述)
	- [服務安裝](#服務安裝)
	- [服務管理](#服務管理)
- [文件同步規則](#文件同步規則)

<!-- /TOC -->



# 概述
[`Syncthing`](https://github.com/syncthing/syncthing)是一套使用Go實現的開源文件同步服務。

## 服務安裝
Syncthing軟件包在各大發行版中均已收錄，直接使用各大發行版的默認包管理器即可安裝：

```html
# apt install syncthing <!-- 大便係 -->
$ brew install syncthing <!-- macOS Homebrew -->
```

在基於systemd的發行版中，以Ubuntu為例，syncthing會創建兩個服務：

- `/lib/systemd/system/syncthing@.service`

	root權限的syncthing服務，使用了systemd中`special executable prefixes`的`@`前綴，
	前綴之後需要追加用戶名：

	```html
	# systemctl start/stop/enable/disable syncthing@用戶.service
	```

- `/usr/lib/systemd/user/syncthing.service`

	普通用戶權限的syncthing服務，每個用戶可獨立管理：

	```html
	$ systemctl --user start/stop/enable/disable syncthing.service
	```

	使用普通用戶權限的syncthing服務需要開啟用戶的`Linger`屬性：

	```html
	$ loginctl enable-linger <!-- 未啟用Linger則無用戶登入時該用戶所屬服務進程會退出 -->
	```

	詳細原因參考[問題描述](#syncthing服務僅在與服務器存在ssh連接時正常連接否則連接斷開)。

使用macOS的Homebrew，則直接使用普通服務管理指令即可：

```
$ brew services start/stop syncthing
```

更多Syncthing服務配置說明可參考[官方文檔](https://docs.syncthing.net/users/autostart.html)。

## 服務管理
默認配置下，服務安裝啟動後，會在`8384`端口提供Web管理頁面，服務數據通信使用`22000`端口，
部署在雲環境上，對應端口均需要開放TCP協議。

首次啟動服務，Syncthing會在`～/.config/syncthing`(Linux)或
`~/Library/Application Support/Syncthing`(macOS)下創建默認配置。
默認配置下，Web管理頁面僅本機地址可訪問，可修改`configuration.gui.address`節點，改成需要的地址。



# 文件同步規則
Syncthing支持git風格的自定義文件同步忽略規則，類似git中的`.gitignore`，
Syncthing在同步根路徑下創建`.stignore`來定義忽略規則。

`.stignore`文件中包含一組文件/路徑的模式，常用的幾種模式：

- `普通名稱` 匹配任意子路徑下的對應名稱文件
- `*`/`**` 匹配零或多個字符，`*`僅一層路徑有效，`**`任意層級子路徑有效
- `?` 匹配非單個字符(不包括路徑分隔符)
- `!` 反模式，模式以`!`為前綴，則模式的含義由排除變為**包含**
- `#include 文件名` 從其它文件中引用規則
- `//` 註釋語法

更多規則可參考[Syncthing官方文檔](https://docs.syncthing.net/users/ignoring.html)。

當多個模式有衝突時，以排在前的模式為準。
示例，忽略所有除`.gitignore`之外的隱藏文件：

```c
.* // 忽略所有`.`開頭的文件
!.gitignore // 取消忽略`.gitignore`
```

按照上述順序寫入`.stignore`並不生效，因為`.*`規則優先匹配(忽略所有隱藏文件)，正確寫法：

```
!.gitignore
.*
```
