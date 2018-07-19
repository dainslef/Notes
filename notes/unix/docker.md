- [概述](#概述)
- [安装与配置](#安装与配置)
	- [基本使用](#基本使用)
	- [在 macOS 中使用 docker](#在-macos-中使用-docker)
- [镜像与容器](#镜像与容器)
	- [镜像管理](#镜像管理)
	- [容器管理](#容器管理)
	- [容器生成镜像](#容器生成镜像)
	- [容器导入/导出](#容器导入导出)
	- [Docker Hub](#docker-hub)
- [文件共享](#文件共享)
	- [文件传输](#文件传输)
	- [Bind Mounts (绑定挂载)](#bind-mounts-绑定挂载)
	- [Volumes (卷)](#volumes-卷)



# 概述
`Docker`是使用`Go`实现的开源容器引擎。
Docker将应用与依赖项放置在容器中执行，仅仅依赖宿主机的内核，简化了应用的运维与部署。



# 安装与配置
各类`Linux`发行版的官方仓库中均内置了Docker，使用发行版内置的包管理器安装即可：

```
# pacman -S docker //Arch Linux
# apt install docker.io //Debian系
```

Docker容器使用宿主机的内核，需要宿主机内核版本`3.10+`。

## 基本使用
Docker在使用前需要开启对应服务。

在基于`SysV init`的发行版上，执行：

```
# service docker start
```

在使用`systemd`的发行版上，执行：

```
# systemctl start docker
```

Ddocker提供了对应的命令行工具进行管理操作。
核心指令如下：

- `docker run` 新建容器执行指令
- `docker exec` 在已有的容器中执行指令
- `docker container` 管理容器
- `docker create` 创建容器
- `docker build` 构建镜像
- `docker commit` 从容器构建镜像
- `docker save/export` 导出镜像到文件
- `docker import` 从文件导入镜像
- `docker tag` 为镜像添加／移除标志

## 在 macOS 中使用 docker
Docker使用了诸多`Linux Kernel`专有特性，并非`POSIX`兼容，无法直接移植到`macOS`中。
macOS中Docker使用`docker-machine`在`VirtualBox`中创建`Linux`虚拟机，并在虚拟机中运行Docker。

安装Docker和`docker-machine`：

```
$ brew install docker docker-machine
```

`docker-machine`主要指令：

```
$ docker-machine create [虚拟机名称] //创建虚拟机
$ docker-machine rm [虚拟机名称] //移除虚拟机
$ docker-machine ls //列出已创建的虚拟机
$ docker-machine start/stop [虚拟机名称] //启动/停止虚拟机
$ docker-machine env [虚拟机名称] //获取指定已启动的虚拟机的环境变量
```

启动虚拟机后，直接在命令行中使用`docker`指令，会得到以下错误输出：

```
Cannot connect to the Docker daemon at unix:///var/run/docker.sock. Is the docker daemon running?
```

`docker`工具不能立即访问虚拟机，需要设置相关环境变量。
使用`docker-machine env`指令获取虚拟机相关环境变量，使用`eval`使环境变量生效，之后才能正常使用Ddocker相关指令：

```
$ eval $(docker-machine env [环境变量])
```



# 镜像与容器
镜像与容器是Docker中的核心概念。

- **容器**(`Container`)是一个/一组在独立环境中执行的应用。
- **镜像**(`Image`)是用于创建容器的模版。

## 镜像管理
镜像包含一个定制的Linux环境，提供创建容器所需的文件。

使用`docker images`指令查看本地存在的镜像：

```c
// 列出本地包含的镜像
$ docker images

// 列出本地包含的镜像，同 docker images
$ docker image ls
```

输出内容格式如下：

```
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
ubuntu              latest              dd6f76d9cc90        7 hours ago         122MB
nixos/nix           latest              3513b310c613        5 weeks ago         177MB
```

- `REPOSITORY`为镜像所属仓库。
- `TAG`为镜像标签。
- `IMAGE ID`为镜像ID，是镜像的唯一标志。

`Docker Hub`(`https://hub.docker.com`)提供了镜像托管服务，可在该网站中查找各类定制镜像。
各大发行版厂商均在Docker Hub中提供了官方镜像，一些社区也提供了用于运行特定软件服务的定制镜像。

官方镜像的镜像名称由`[镜像仓库]:[镜像TAG]`形式构成，一般情况下，镜像`TAG`可省略，
省略镜像TAG时会使用**默认TAG**。一个镜像仓库可以提供多个标签不同的镜像，
如`ubuntu`仓库中使用不同`TAG`提供了不同版本的Ubuntu镜像(`ubuntu:16.04`、`ubuntu:14.04`等)。

使用`docker search`指令搜索镜像：

```
$ docker search [查询内容]
```

`docker search`指令并未提供依据TAG搜索镜像的功能，名称相同但TAG不同的镜像需要在Docker Hub中查找。

使用`docker tag`指令可设置镜像的名称：

```
$ docker tag [镜像ID/镜像名称] [镜像新名称]
```

对于未设置镜像名称的镜像，会为原镜像添加`REPOSITORY`、`TAG`等信息；
对于已设置镜像名称的镜像，会创建内容与原镜像相同，使用新`REPOSITORY`、`TAG`等信息的新镜像。

从`dcoker pull`指令从Docker Hub中拉取镜像到本地：

```c
// 拉取指定名称默认TAG的镜像
$ docker pull [镜像仓库]

// 拉取指定名称指定TAG的镜像
$ docker pull [镜像仓库:镜像TAG]

// 拉取镜像，与 docker pull 相同
$ docker image pull [镜像仓库]
```

其它镜像管理指令：

```c
// 删除指定镜像
$ docker rmi [镜像ID/镜像名称]

// 删除指定镜像，同 docker rmi
$ docker image rm [镜像ID/镜像名称]

// 显示镜像详情
$ docker image inspect [镜像ID/镜像名称]
```

## 容器管理
容器是镜像的运行实例，容器在独立、隔离的Linux环境中运行一个或一组进程。

使用`docker create`指令创建容器，并在创建容器时指定启动的进程：

```
$ docker create [容器参数...] [镜像] [启动进程] [进程参数...]
```

以`Ubuntu 14.04 LTS`为例，创建以`bash`为启动进程的容器：

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

创建容器时`docker`会自行为每个容器分配唯一的`CONTAINER ID`，使用`CONTAINER ID`对指定容器进行操作。
亦可在创建容器时使用`--name`参数为容器设置名称，设定了名称的容器可使用容器名称替代`CONTAINER ID`。

创建容器时的一些常用参数：

- `-t` 创建容器时，为容器分配伪终端
- `-i` 保持容器标准输出到终端
- `--name` 创建容器时为容器指定名称

容器创建完成使用`docker start/stop`启动/停止容器。
容器创建时若未分配**伪终端**，则在容器内进程执行完毕后会立即退出，
若需要容器一直处于执行状态，则需要保证容器执行的进程为**守护进程**，或在创建容器时为容器分配**伪终端**。

使用`docker exec`指令可以使用已启动的容器执行指令：

```
$ docker exec [选项] [镜像] [启动进程] [进程参数...]
```

使用`docker exec`进入已启动容器内部的伪终端：

```
$ docker exec -it [容器ID/容器名称] bash
```

使用`docker container`相关指令查看、管理容器相关信息。

```
$ docker ps //查看正在运行中的容器
$ docker container ls //同 docker ps
$ docker ps -a //查看所有创建的容器
$ docker container ls -a //同 docker ps -a
$ docker rm [容器ID/容器名称] //删除指定容器
$ docker container rm [容器ID/容器名称] //同 docker rm
```

## 容器生成镜像
使用`docker commit`指令为指定容器生成新的镜像。

```
$ docker commit [选项] [容器ID/容器名称] [镜像仓库:镜像TAG]
```

`docker commit`仅会提交相对基础镜像变化的部分。

## 容器导入/导出
使用`docker save/export`指令将容器的内容导出为`*.tar`格式的压缩文件：

```
$ docker save/export [容器ID/容器名称] -o [备份.tar]
```

使用`docker import`指令将`*.tar`形式的容器备份导入为镜像：

```
$ docker import [备份.tar] [镜像仓库:镜像TAG]
```

导入镜像时`镜像仓库:镜像TAG`参数可以省略，省略该参数时，导入镜像的`REPOSITORY`与`TAG`均为`<none>`。

## Docker Hub
Docker官方提供了镜像托管服务`Docker Hub`。
在`https://hub.docker.com`中注册，在本机使用`docker login`登陆账户后即可使用镜像托管服务。
将本地的个人镜像上传到Docker Hub：

```
$ docker push [镜像名称]
```

个人镜像的镜像名称中`REPOSITORY`部分应以**Docker Hub ID**加**正斜杠**起始，镜像名称格式如下：

```
[Docker Hub ID]/Xxx:[镜像TAG]
```

假设个人`Docker ID`为`danslef`，本地测试镜像信息如下：

```
REPOSITORY              TAG                 IMAGE ID            CREATED            SIZE
dainslef/test_image     2333               9f0a1d72c464        9 minutes ago       538MB
```

将测试镜像上传到Docker Hub：

```
$ docker push dainslef/test_image:2333
```



# 文件共享
Docker存储采用特殊的`Union File System`(联合文件系统)机制，容器内的文件不能直接被外部访问。
容器与宿主机之间的文件共享可以通过以下方式：

- 使用`docker cp`指令直接在宿主机与容器之间传输文件
- 使用`Bind Mounts`(绑定挂载)机制，在容器中的指定路径下挂载外部宿主机的某个目录
- 使用`Volumes`(卷)机制，由docker创建并管理的存储卷，由容器启动时挂载，相比`Bind Mounts`具有更好的可管理性和可迁移性

## 文件传输
将宿主机的文件/目录复制到容器中：

```
$ docker cp [宿主机文件/目录] [容器ID/容器名称]:[绝对路径]
```

将容器的文件目录复制到宿主机中：

```
$ docker cp [容器ID/容器名称]:[绝对路径] [宿主机文件/目录]
```

容器中的文件/目录需要为**绝对路径**，宿主机中的路径可以为相对路径**或**绝对路径。

## Bind Mounts (绑定挂载)
`Bind Mounts`(绑定挂载)是Docker早期就具有的功能，相比`Volumes`机制部分功能受限。
通过绑定挂载机制可以将主机的指定目录直接挂载到容器中。

创建容器时，使用`-v/--volume`或`--mount`参数设定宿主机和容器的路径绑定关系(`宿主机路径:容器路径`)，
如下所示：

```
$ docker create -v [宿主机路径:容器内路径] [其它容器参数...] [镜像] [启动进程] [进程参数...]
$ docker create --mount [宿主机路径:容器内路径] [其它容器参数...] [镜像] [启动进程] [进程参数...]
```

使用绑定挂载时，宿主机路径、容器内路径需要为**绝对路径**：

- 宿主机路径使用相对路径(不以`/`字符起始)时，指令会被解析为**卷挂载**模式，宿主机的相对路径实际成了卷的名称。
- 容器路径使用相对路径时，会在创建容器时直接得到错误信息(`Error response from daemon: invalid volume specification: 'xxx...': invalid mount config for type "volume": invalid mount path: 'xxx/xxx...' mount path must be absolute`)。

绑定挂载仅能在容器创建时配置，若需修改已创建容器的挂载配置，
需要使用`docker save/export`指令导出镜像后重新创建容器，在新创建容器时设定路径挂载配置。

`-v`和`--mount`参数在创建绑定挂载时行为存在细微差异：

- `-v` 容器内路径不存在时会自动创建该路径
- `--mount` 容器内路径不存在时输出错误信息，指令执行失败

与Unix下传统的mount指令行为类似，当容器内路径已存在且包含其它内容时，该路径下原先存在的内容会被隐藏。

使用`docker inspect`指令查看指定容器信息，`Mounts`区段即为挂载信息：

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
`Volumes`(卷)是持久化由容器产生、使用数据的首选机制。
**绑定挂载**依赖于宿主机的物理路径结构，**卷**则完全由Docker管理。
与绑定挂载相比，卷具有以下优点：

- 卷比绑定挂载更易于备份或迁移。
- 可以使用Docker CLI指令或Docker API管理卷。
- 卷在Windows容器和Linux容器上均可使用。
- 卷可以更安全地在多个容器间共享。
- 通过卷驱动程序，可以将卷存储在远程主机、云提供商中，加密卷的内容，或者添加其它功能。
- 新的卷可以由容器预填充内容。

创建容器时，同样使用`-v/--volume`或`--mount`参数设定卷挂载，但语法略有不同，如下所示：

```c
// 创建卷时不指定卷名称会随机生成名称
$ docker create -v [容器内路径] [其它容器参数...] [镜像] [启动进程] [进程参数...]
$ docker create --mount [容器内路径] [其它容器参数...] [镜像] [启动进程] [进程参数...]

// 指定卷名称
$ docker create -v [卷名称:容器内路径] [其它容器参数...] [镜像] [启动进程] [进程参数...]
$ docker create --mount [卷名称:容器内路径] [其它容器参数...] [镜像] [启动进程] [进程参数...]
```

卷的物理路径在宿主机的`/var/lib/docker/volumes/[卷名称]/_data`路径下。
不指定卷名称则每次都会创建新卷，指定卷名称时若卷已存在则使用已存在的卷，挂载相同卷的容器对应路径数据互通。

使用`docker volume`指令管理已存在的卷：

```c
// 列出Docker中已存在的卷
$ docker volume ls

// 通过卷名称/卷ID删除指定卷
$ docker volume rm [卷名称/卷ID]

// 删除所有未被使用(未跟容器关联)的卷
$ docker volume prune
```

`docker volume ls`的典型输出信息示例：

```
DRIVER              VOLUME NAME
local               413bfe6e5cf80d99594b379371e90edd5b799122294f8e0230def069af114aa8
local               TestVolume
```

使用`docker inspect`指令查看指定容器信息，卷挂载信息示例：

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
