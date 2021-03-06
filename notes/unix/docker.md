<!-- TOC -->

- [概述](#概述)
- [安裝與配置](#安裝與配置)
	- [基本使用](#基本使用)
	- [在 macOS 中使用 docker](#在-macos-中使用-docker)
	- [Docker Desktop for macOS](#docker-desktop-for-macos)
		- [訪問 HyperKit 虛擬機](#訪問-hyperkit-虛擬機)
- [鏡像與容器](#鏡像與容器)
	- [鏡像管理](#鏡像管理)
	- [鏡像源](#鏡像源)
	- [容器管理](#容器管理)
	- [容器生成鏡像](#容器生成鏡像)
	- [容器導入/導出](#容器導入導出)
	- [Docker Hub](#docker-hub)
- [文件共享](#文件共享)
	- [文件傳輸](#文件傳輸)
	- [Bind Mounts (綁定掛載)](#bind-mounts-綁定掛載)
	- [Volumes (卷)](#volumes-卷)
- [端口映射](#端口映射)
	- [修改端口映射](#修改端口映射)

<!-- /TOC -->



# 概述
`Docker`是使用`Go`實現的開源容器引擎。
Docker將應用與依賴項放置在容器中執行，僅僅依賴宿主機的內核，簡化了應用的運維與部署。

與傳統虛擬機不同Docker屬於`OS-level virtualization`(操作系統層次的虛擬化)，
每個Docker實例實際僅僅是獨立的用戶空間實例，類似一個高級的`chroot`實現，
在普通的chroot上添加了資源控制等高級功能。



# 安裝與配置
各類Linux發行版的官方倉庫中均內置了Docker，使用發行版內置的包管理器安裝即可：

```
# pacman -S docker //Arch Linux
# apt install docker.io //Debian系
```

Docker容器使用宿主機的內核，需要宿主機內核版本`3.10+`。

## 基本使用
Docker在使用前需要開啓對應服務。

在基於`SysV init`的發行版上，執行：

```
# service docker start
```

在使用`systemd`的發行版上，執行：

```
# systemctl start docker
```

Docker提供了對應的命令行工具進行管理操作。
核心指令如下：

- `docker run` 新建容器執行指令
- `docker exec` 在已有的容器中執行指令
- `docker container` 管理容器
- `docker create` 創建容器
- `docker build` 構建鏡像
- `docker commit` 從容器構建鏡像
- `docker save/export` 導出鏡像到文件
- `docker import` 從文件導入鏡像
- `docker tag` 爲鏡像添加／移除標誌

## 在 macOS 中使用 docker
Docker使用了諸多`Linux Kernel`專有特性，並非POSIX兼容，無法直接移植到macOS中。
macOS中Docker使用`docker-machine`在VirtualBox中創建Linux虛擬機，並在虛擬機中運行Docker。

安裝Docker和`docker-machine`：

```
$ brew install docker docker-machine
```

`docker-machine`主要指令：

```
$ docker-machine create [虛擬機名稱] // 創建虛擬機
$ docker-machine rm [虛擬機名稱] // 移除虛擬機
$ docker-machine ls // 列出已創建的虛擬機
$ docker-machine start/stop [虛擬機名稱] // 啓動/停止虛擬機
$ docker-machine env [虛擬機名稱] // 獲取指定已啓動的虛擬機的環境變量
```

啓動虛擬機後，直接在命令行中使用`docker`指令，會得到以下錯誤輸出：

```
Cannot connect to the Docker daemon at unix:///var/run/docker.sock. Is the docker daemon running?
```

`docker`工具不能立即訪問虛擬機，需要設置相關環境變量。
使用`docker-machine env`指令獲取虛擬機相關環境變量，使用`eval`使環境變量生效，之後才能正常使用Ddocker相關指令：

```
$ eval $(docker-machine env [環境變量])
```

## Docker Desktop for macOS
通過docker-machine創建VirtualBox虛擬機來使用docker需要較多配置，存在諸多不便，
因而官方推出了[`Docker Desktop`](https://www.docker.com/products/docker-desktop)。

Dcoker Desktop針對Windows、macOS平臺提供了開箱即用的配置整合，內置了docker運行需要的Linux虛擬機，
並提供了美觀的GUI，便於對網絡、存儲、性能等各類配置進行管理。

Docker Desktop在對應平臺使用該平臺推薦的虛擬化技術創建虛擬機(Windows下使用HyperV，macOS下使用HyperKit)，
相比使用VirtualBox更加高效。

### 訪問 HyperKit 虛擬機
在macOS下，Docker Desktop使用HyperKit啟動虛擬機，用以提供docker執行需要的Linux環境。
通過訪問該虛擬機可以查看和配置docker運行的真實主機環境。

HyperKit創建的虛擬機會在以下路徑創建終端虛擬設備：

```html
~/Library/Containers/com.docker.docker/Data/com.docker.driver.amd64-linux/tty

<!-- 該設備實際指向 /dev 路徑下的終端設備 -->
$ ls -alh ~/Library/Containers/com.docker.docker/Data/com.docker.driver.amd64-linux/tty
lrwxr-xr-x  1 dainslef  staff    12B Aug 13 01:00 /Users/dainslef/Library/Containers/com.docker.docker/Data/com.docker.driver.amd64-linux/tty -> /dev/ttys009
<!-- 文件類型為特殊字符設備 -->
$ file ~/Library/Containers/com.docker.docker/Data/com.docker.driver.amd64-linux/tty
/Users/dainslef/Library/Containers/com.docker.docker/Data/com.docker.driver.amd64-linux/tty: character special (16/9)
```

通過`screen`指令可訪問該終端設備並進行交互：

```
$ screen ~/Library/Containers/com.docker.docker/Data/com.docker.driver.amd64-linux/tty
```

screen指令會創建窗口管理器，在窗口管理器中可直接與虛擬機進行交互：

- 普通指令與標準終端類似
- 使用`Ctrl-A k`可退出會話
- 使用`Ctrl-A Ctrl-D`掛起會話，使用`screen -r [pid]`恢復會話



# 鏡像與容器
鏡像與容器是Docker中的核心概念。

- **容器**(`Container`)是一個/一組在獨立環境中執行的應用。
- **鏡像**(`Image`)是用於創建容器的模版。

## 鏡像管理
鏡像包含一個定製的Linux環境，提供創建容器所需的文件。

使用`docker images`指令查看本地存在的鏡像：

```c
// 列出本地包含的鏡像
$ docker images

// 列出本地包含的鏡像，同 docker images
$ docker image ls
```

輸出內容格式如下：

```
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
ubuntu              latest              dd6f76d9cc90        7 hours ago         122MB
nixos/nix           latest              3513b310c613        5 weeks ago         177MB
```

- `REPOSITORY`爲鏡像所屬倉庫。
- `TAG`爲鏡像標籤。
- `IMAGE ID`爲鏡像ID，是鏡像的唯一標誌。

`Docker Hub`(`https://hub.docker.com`)提供了鏡像託管服務，可在該網站中查找各類定製鏡像。
各大發行版廠商均在Docker Hub中提供了官方鏡像，一些社區也提供了用於運行特定軟件服務的定製鏡像。

官方鏡像的鏡像名稱由`[鏡像倉庫]:[鏡像TAG]`形式構成，一般情況下，鏡像`TAG`可省略，
省略鏡像TAG時會使用**默認TAG**。一個鏡像倉庫可以提供多個標籤不同的鏡像，
如`ubuntu`倉庫中使用不同`TAG`提供了不同版本的Ubuntu鏡像(`ubuntu:16.04`、`ubuntu:14.04`等)。

使用`docker search`指令搜索鏡像：

```
$ docker search [查詢內容]
```

`docker search`指令並未提供依據TAG搜索鏡像的功能，名稱相同但TAG不同的鏡像需要在Docker Hub中查找。

使用`docker tag`指令可設置鏡像的名稱：

```
$ docker tag [鏡像ID/鏡像名稱] [鏡像新名稱]
```

對於未設置鏡像名稱的鏡像，會爲原鏡像添加`REPOSITORY`、`TAG`等信息；
對於已設置鏡像名稱的鏡像，會創建內容與原鏡像相同，使用新`REPOSITORY`、`TAG`等信息的新鏡像。

從`docker pull`指令從Docker Hub中拉取鏡像到本地：

```c
// 拉取指定名稱默認TAG的鏡像
$ docker pull [鏡像倉庫]

// 拉取指定名稱指定TAG的鏡像
$ docker pull [鏡像倉庫:鏡像TAG]

// 拉取鏡像，與 docker pull 相同
$ docker image pull [鏡像倉庫]
```

其它鏡像管理指令：

```c
// 刪除指定鏡像
$ docker rmi [鏡像ID/鏡像名稱]

// 刪除指定鏡像，同 docker rmi
$ docker image rm [鏡像ID/鏡像名稱]

// 顯示鏡像詳情
$ docker image inspect [鏡像ID/鏡像名稱]
```

## 鏡像源
默認Docker會從**官方源**(https://production.cloudflare.docker.com)中拉取鏡像，
在牆國通常無法連接或下載龜速。

相關配置文件為`daemon.json`，在不同OS和不同Docker發行版下路徑有所差異：

- macOS下，安裝`Docker Desktop`，則配置路徑為`~/.docker/daemon.json`
- Linux下，通過發行版默認包管理器安裝，則配置路徑通常為`/etc/docker/daemon.json`

在該配置中添加`registry-mirrors`配置項(以中科大USTC鏡像源為例)：

```json
{
	...
	"registry-mirrors": ["https://docker.mirrors.ustc.edu.cn/"],
	...
}
```

該配置項為數組結構，內容為文本數組(可添加多個鏡像地址)。

## 容器管理
容器是鏡像的運行實例，容器在獨立、隔離的Linux環境中運行一個或一組進程。

使用`docker create`指令創建容器，並在創建容器時指定啓動的進程：

```
$ docker create [容器參數...] [鏡像] [啓動進程] [進程參數...]
```

以`Ubuntu 14.04 LTS`爲例，創建以`bash`爲啓動進程的容器：

```
$ docker create ubuntu:14.04 bash
```

容器信息如下所示：

```
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS                   PORTS
     NAMES
8790b2625abc        ubuntu              "bash"              5 seconds ago       Created
     wonderful_poitras
```

創建容器時`docker`會自行爲每個容器分配唯一的`CONTAINER ID`，使用`CONTAINER ID`對指定容器進行操作。
亦可在創建容器時使用`--name`參數爲容器設置名稱，設定了名稱的容器可使用容器名稱替代`CONTAINER ID`。

創建容器時的一些常用參數：

- `-t` 創建容器時，爲容器分配僞終端
- `-i` 保持容器標準輸出到終端
- `--name` 創建容器時爲容器指定名稱

容器創建完成使用`docker start/stop`啓動/停止容器。
容器創建時若未分配**僞終端**，則在容器內進程執行完畢後會立即退出，
若需要容器一直處於執行狀態，則需要保證容器執行的進程爲**守護進程**，或在創建容器時爲容器分配**僞終端**。

創建可持續執行的容器，並指定容器名稱：

```
$ docker create -it --name Nix nixos/nix sh
```

使用`docker exec`指令可以使用已啓動的容器執行指令：

```
$ docker exec [選項] [鏡像] [啓動進程] [進程參數...]
```

使用`docker exec`進入已啓動容器內部的僞終端：

```
$ docker exec -it [容器ID/容器名稱] bash
```

使用`docker container`相關指令查看、管理容器相關信息。

```
$ docker ps // 查看正在運行中的容器
$ docker container ls // 同 docker ps
$ docker ps -a // 查看所有創建的容器
$ docker container ls -a // 同 docker ps -a
$ docker rm [容器ID/容器名稱] // 刪除指定容器
$ docker container rm [容器ID/容器名稱] // 同 docker rm
$ docker container inspect [容器ID/容器名稱] // 查看容器的詳細配置
```

## 容器生成鏡像
使用`docker commit`指令爲指定容器生成新的鏡像。

```
$ docker commit [選項] [容器ID/容器名稱] [鏡像倉庫:鏡像TAG]
```

`docker commit`僅會提交相對基礎鏡像變化的部分。

## 容器導入/導出
使用`docker save/export`指令將容器的內容導出爲`*.tar`格式的壓縮文件：

```
$ docker save/export [容器ID/容器名稱] -o [備份.tar]
```

使用`docker import`指令將`*.tar`形式的容器備份導入爲鏡像：

```
$ docker import [備份.tar] [鏡像倉庫:鏡像TAG]
```

導入鏡像時`鏡像倉庫:鏡像TAG`參數可以省略，省略該參數時，導入鏡像的`REPOSITORY`與`TAG`均爲`<none>`。

## Docker Hub
Docker官方提供了鏡像託管服務`Docker Hub`。
在`https://hub.docker.com`中註冊，在本機使用`docker login`登陸賬戶後即可使用鏡像託管服務。
將本地的個人鏡像上傳到Docker Hub：

```
$ docker push [鏡像名稱]
```

個人鏡像的鏡像名稱中`REPOSITORY`部分應以**Docker Hub ID**加**正斜槓**起始，鏡像名稱格式如下：

```
[Docker Hub ID]/Xxx:[鏡像TAG]
```

假設個人`Docker ID`爲`danslef`，本地測試鏡像信息如下：

```
REPOSITORY              TAG                 IMAGE ID            CREATED            SIZE
dainslef/test_image     2333               9f0a1d72c464        9 minutes ago       538MB
```

將測試鏡像上傳到Docker Hub：

```
$ docker push dainslef/test_image:2333
```



# 文件共享
Docker存儲採用特殊的`Union File System`(聯合文件系統)機制，容器內的文件不能直接被外部訪問。
容器與宿主機之間的文件共享可以通過以下方式：

- 使用`docker cp`指令直接在宿主機與容器之間傳輸文件
- 使用`Bind Mounts`(綁定掛載)機制，在容器中的指定路徑下掛載外部宿主機的某個目錄
- 使用`Volumes`(卷)機制，由docker創建並管理的存儲卷，由容器啓動時掛載，相比`Bind Mounts`具有更好的可管理性和可遷移性

## 文件傳輸
將宿主機的文件/目錄複製到容器中：

```
$ docker cp [宿主機文件/目錄] [容器ID/容器名稱]:[絕對路徑]
```

將容器的文件目錄複製到宿主機中：

```
$ docker cp [容器ID/容器名稱]:[絕對路徑] [宿主機文件/目錄]
```

容器中的文件/目錄需要爲**絕對路徑**，宿主機中的路徑可以爲相對路徑**或**絕對路徑。

## Bind Mounts (綁定掛載)
`Bind Mounts`(綁定掛載)是Docker早期就具有的功能，相比`Volumes`機制部分功能受限。
通過綁定掛載機制可以將主機的指定目錄直接掛載到容器中。

創建容器時，使用`-v/--volume`或`--mount`參數設定宿主機和容器的路徑綁定關係(`宿主機路徑:容器路徑`)，
如下所示：

```
$ docker create -v [宿主機路徑:容器內路徑] [其它容器參數...] [鏡像] [啓動進程] [進程參數...]
$ docker create --mount [宿主機路徑:容器內路徑] [其它容器參數...] [鏡像] [啓動進程] [進程參數...]
```

使用綁定掛載時，宿主機路徑、容器內路徑需要爲**絕對路徑**：

- 宿主機路徑使用相對路徑(不以`/`字符起始)時，指令會被解析爲**卷掛載**模式，宿主機的相對路徑實際成了卷的名稱。
- 容器路徑使用相對路徑時，會在創建容器時直接得到錯誤信息(`Error response from daemon: invalid volume specification: 'xxx...': invalid mount config for type "volume": invalid mount path: 'xxx/xxx...' mount path must be absolute`)。

綁定掛載僅能在容器創建時配置，若需修改已創建容器的掛載配置，
需要使用`docker save/export`指令導出鏡像後重新創建容器，在新創建容器時設定路徑掛載配置。

`-v`和`--mount`參數在創建綁定掛載時行爲存在細微差異：

- `-v` 容器內路徑不存在時會自動創建該路徑
- `--mount` 容器內路徑不存在時輸出錯誤信息，指令執行失敗

與Unix下傳統的mount指令行爲類似，當容器內路徑已存在且包含其它內容時，該路徑下原先存在的內容會被隱藏。

使用`docker inspect`指令查看指定容器信息，`Mounts`區段即爲掛載信息：

```json
{
    ...
        "Mounts": [
            {
                "Type": "bind",
                "Source": "/Users/dainslef/Downloads/BigData",
                "Destination": "/mnt/big_data",
                "Mode": "",
                "RW": true,
                "Propagation": "rprivate"
            }
        ],
    ...
}
```

## Volumes (卷)
`Volumes`(卷)是持久化由容器產生、使用數據的首選機制。
**綁定掛載**依賴於宿主機的物理路徑結構，**卷**則完全由Docker管理。
與綁定掛載相比，卷具有以下優點：

- 卷比綁定掛載更易於備份或遷移。
- 可以使用Docker CLI指令或Docker API管理卷。
- 卷在Windows容器和Linux容器上均可使用。
- 卷可以更安全地在多個容器間共享。
- 通過卷驅動程序，可以將卷存儲在遠程主機、雲提供商中，加密卷的內容，或者添加其它功能。
- 新的卷可以由容器預填充內容。

創建容器時，同樣使用`-v/--volume`或`--mount`參數設定卷掛載，但語法略有不同，如下所示：

```c
// 創建卷時不指定卷名稱會隨機生成名稱
$ docker create -v [容器內路徑] [其它容器參數...] [鏡像] [啓動進程] [進程參數...]
$ docker create --mount [容器內路徑] [其它容器參數...] [鏡像] [啓動進程] [進程參數...]

// 指定卷名稱
$ docker create -v [卷名稱:容器內路徑] [其它容器參數...] [鏡像] [啓動進程] [進程參數...]
$ docker create --mount [卷名稱:容器內路徑] [其它容器參數...] [鏡像] [啓動進程] [進程參數...]
```

卷的物理路徑在宿主機的`/var/lib/docker/volumes/[卷名稱]/_data`路徑下。
不指定卷名稱則每次都會創建新卷，指定卷名稱時若卷已存在則使用已存在的卷，掛載相同卷的容器對應路徑數據互通。

使用`docker volume`指令管理已存在的卷：

```c
// 列出Docker中已存在的卷
$ docker volume ls

// 通過卷名稱/卷ID刪除指定卷
$ docker volume rm [卷名稱/卷ID]

// 刪除所有未被使用(未跟容器關聯)的卷
$ docker volume prune
```

`docker volume ls`的典型輸出信息示例：

```
DRIVER              VOLUME NAME
local               413bfe6e5cf80d99594b379371e90edd5b799122294f8e0230def069af114aa8
local               TestVolume
```

使用`docker inspect`指令查看指定容器信息，卷掛載信息示例：

```json
{
    ...
        "Mounts": [
            {
                "Type": "volume",
                "Name": "TestVolume",
                "Source": "/var/lib/docker/volumes/TestVolume/_data",
                "Destination": "/root/data1",
                "Driver": "local",
                "Mode": "z",
                "RW": true,
                "Propagation": ""
            },
            {
                "Type": "volume",
                "Name": "413bfe6e5cf80d99594b379371e90edd5b799122294f8e0230def069af114aa8",
                "Source": "/var/lib/docker/volumes/413bfe6e5cf80d99594b379371e90edd5b799122294f8e0230def069af114aa8/_data",
                "Destination": "/root/data2",
                "Driver": "local",
                "Mode": "",
                "RW": true,
                "Propagation": ""
            }
        ],
    ...
}
```



# 端口映射
在docker中，在創建容器時可將容器內的端口映射到宿主機，宿主機可通過映射出的端口訪問容器提供的服務。

創建容器時使用`-p`參數指定端口的映射信息：

```c
$ docker create -p [主機端口]:[容器端口] [鏡像] [啓動進程] [進程參數...]

// 映射多個端口需要多次使用 -p 參數
$ docker create -p [主機端口1]:[容器端口2] -p [主機端口2]:[容器端口2] ...
```

## 修改端口映射
創建了容器之後，容器的端口不能直接修改。修改端口映射可採用提交(commit)/導出(export)鏡像的方式將容器的內容提交，
之後再重新使用`docker create`創建新容器，在創建新容器時使用新的`-p`參數設定新的端口映射。

還可以通過修改容器信息的方式來修改端口映射，修改配置後重啓整個Docker服務，之後重新啟動容器，
重新啟動的容器會使用修改後的配置，新的端口映射會隨之生效。
使用`docker inspect`查看目標容器的具體信息(以SSH服務的`22`端口為例)：

```json
$ docker inspect [容器ID]

[
    {
        ...
        "HostConfig": {
            ...
            "PortBindings": {
                "22/tcp": [
                    {
                        "HostIp": "",
                        "HostPort": "22"
                    }
                ],
                ...
            },
            ...
        },
        ...
        "NetworkSettings": {
            ...
            "Ports": {
                "22/tcp": [
                    {
                        "HostIp": "0.0.0.0",
                        "HostPort": "22"
                    }
                ],
                ...
            },
        }
        ...
    }
]
```

在容器詳細信息中的`HostConfig.PortBindings`以及`NetworkSettings.Ports`等配置段可看到容器的端口映射信息。
在宿主機中修改docker容器的相關配置文件：

- `/var/lib/docker/containers/[容器ID]/hostconfig.json`

	修改`PortBindings`配置段：

	```json
	{
		...
		"PortBindings": {
			"22/tcp": [
				{
					"HostIp": "",
					"HostPort": "22"
				}
			],
			...
		},
		...
	}
	```

- `/var/lib/docker/containers/[容器ID]/config.v2.json`

	修改`Config.ExposedPorts`和`NetworkSettings.Ports`配置段：

	```json
	{
		...
		"Config": {
			...
			"ExposedPorts": {
				"22/tcp": {},
				...
			},
			...
		},
		...
		"NetworkSettings": {
			...
			"Ports": {
				"22/tcp": [
					{
						"HostIp": "0.0.0.0",
						"HostPort": "22"
					}
				],
				...
			},
			...
		}
		...
	}
	```
