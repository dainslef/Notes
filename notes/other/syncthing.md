<!-- TOC -->

- [概述](#概述)
	- [服務安裝](#服務安裝)

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
