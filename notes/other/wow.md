<!-- TOC -->

- [MaNGOS](#mangos)
	- [MaNGOS服務說明](#mangos服務說明)
	- [部署MaNGOS數據庫](#部署mangos數據庫)
	- [MaNGOS目錄結構](#mangos目錄結構)
	- [部署MaNGOS核心服務](#部署mangos核心服務)
	- [修改配置](#修改配置)

<!-- /TOC -->



# MaNGOS
[MaNGOS](https://www.getmangos.eu/)是歷史悠久開源的魔獸世界服務端，
後續從MaNGOS發展出了TrinityCore、AzerothCore等一系列分支。

## MaNGOS服務說明
MaNGOS服務分為兩部分：

- `realmd` 提供服務器登入、驗證等服務
- `mangosd` 提供遊戲主體服務

此外，還需要部署MySQL數據庫提供數據存儲。

不同版本的WOW需要不同版本的mangosd服務，但realmd服務可以共用。

MaNGOS的核心服務mangosd支持下列WOW版本：

| WOW版本 | MaNGOS代號 |
| :- | :- |
| Vanilla | ZERO |
| The Burning Crusade | ONE |
| Wrath of the Lich King | TWO |
| Cataclysm | THREE |

不同版本對應不同的倉庫地址，以ZERO版本爲例：

- 主服務倉庫：https://github.com/mangoszero/server.git
- 數據庫倉庫：https://github.com/mangoszero/database.git

其它版本類似，將倉庫地址中的代號切換為對應版本即可。

## 部署MaNGOS數據庫
首先部署數據庫，推薦使用Docker/containerd部署。

克隆數據庫倉庫，以ZERO版本爲例：

```
$ git clone https://github.com/mangoszero/database.git --recursive --depth 1
```

克隆倉庫之後進入源碼目錄，執行數據庫部署脚本：

```
$ ./InstallDatabases.sh
```

在脚本中可設置需要部署哪些數據庫，以及數據的訪問方式，創建數據庫的名稱等。

## MaNGOS目錄結構
項目整體部署結構：

```html
/opt/mangos
├── mysql <!-- 數據庫 -->
├── realmd <!-- 登入器服務 -->
│   ├── bin
│   └── etc
├── zero <!-- 各版本游戲主服務 -->
│   └── ...
├── two
│   └── ...
└── ...
```

MaNGOS游戲服務部署目錄結構：

```html
.
├── bin
│   └── ...
├── etc
│   ├── dbc
│   ├── maps
│   ├── mmaps
│   ├── vmaps
│   └── mangosd.conf
└── source
    ├── database
    ├── build
    └── server
```

## 部署MaNGOS核心服務
安裝必要依賴：

```
# apt install git cmake build-essential default-libmysqlclient-dev libbz2-dev
```

以ZERO版本爲例，克隆倉庫源碼並編譯：

```html
<!-- 創建目錄，克隆倉庫源碼 -->
$ mkdir -p /opt/mangos/zero/source
$ cd /opt/mangos/zero/source
$ git clone https://github.com/mangoszero/server.git --recursive --depth 1

<!-- 生成構建信息 -->
$ cmake /opt/mangos/zero/source/server -B /opt/mangos/zero/source/build

<!-- 構建項目 -->
$ cmake --build /opt/mangos/zero/source/build -j 綫程數目

<!-- 安裝生成的構建文件 -->
$ cmake --install /opt/mangos/zero/source/build
```

登入服務所有游戲版本通用，在編譯任意版本的主服務過程中會一并編譯，
生成的安裝内容位於`/opt/mangos/zero/source/build/install/bin`路徑下。

## 修改配置
mangosd配置文件修改下列內容：

```
$ diff mangosd.conf.dist mangosd.conf
66,68c66,68
< LoginDatabaseInfo            = "127.0.0.1;3306;root;mangos;realmd"
< WorldDatabaseInfo            = "127.0.0.1;3306;root;mangos;mangos0"
< CharacterDatabaseInfo        = "127.0.0.1;3306;root;mangos;character0"
---
> LoginDatabaseInfo            = "10.4.0.1;3306;root;mangos;realmd"
> WorldDatabaseInfo            = "10.4.0.1;3306;root;mangos;mangos0"
> CharacterDatabaseInfo        = "10.4.0.1;3306;root;mangos;character0"
391c391
< LogLevel                     = 3
---
> LogLevel                     = 1
395c395
< LogFileLevel                 = 0
---
> LogFileLevel                 = 3
1743c1743
< Warden.WinEnabled            = 1
---
> Warden.WinEnabled            = 0
```
