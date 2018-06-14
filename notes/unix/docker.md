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



# 概述
`docker`是使用`Go`实现的开源容器引擎。  
`docker`将应用与依赖项放置在容器中执行，仅仅依赖宿主机的内核，简化了应用的运维与部署。



# 安装与配置
各类`Linux`发行版的官方仓库中均内置了`docker`，使用发行版内置的包管理器安装即可：

```
# pacman -S docker //Arch Linux
# apt install docker.io //Debian系
```

`docker`容器使用宿主机的内核，需要宿主机内核版本`3.10+`。

## 基本使用
`docker`在使用前需要开启对应服务。

在基于`SysV init`的发行版上，执行：

```
# service docker start
```

在使用`systemd`的发行版上，执行：

```
# systemctl start docker
```

`docker`提供了对应的命令行工具进行管理操作。  
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
`docker`使用了诸多`Linux Kernel`专有特性，并非`POSIX`兼容，无法直接移植到`macOS`中。  
`macOS`中`docker`使用`docker-machine`在`VirtualBox`中创建`Linux`虚拟机，并在虚拟机中运行`docker`。

安装`docker`和`docker-machine`：

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
使用`docker-machine env`指令获取虚拟机相关环境变量，使用`eval`使环境变量生效，之后才能正常使用`docker`相关指令：

```
$ eval $(docker-machine env [环境变量])
```



# 镜像与容器
镜像与容器是`docker`中的核心概念。

- **容器**(`Container`)是一个/一组在独立环境中执行的应用。
- **镜像**(`Image`)是用于创建容器的模版。

## 镜像管理
镜像包含一个定制的`Linux`环境，提供创建容器所需的文件。

使用`docker images`指令查看本地存在的镜像：

```
$ docker images //列出本地包含的镜像
$ docker image ls //列出本地包含的镜像，同 docker images
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
各大发行版厂商均在`Docker Hub`中提供了官方镜像，一些社区也提供了用于运行特定软件服务的定制镜像。

官方镜像的镜像名称由`[镜像仓库]:[镜像TAG]`形式构成，一般情况下，镜像`TAG`可省略，省略镜像`TAG`时会使用默认`TAG`。  
一个镜像仓库可以提供多个标签不同的镜像，如`ubuntu`仓库中使用不同`TAG`提供了不同版本的`ubuntu`镜像(`ubuntu:16.04`、`ubuntu:14.04`等)。

使用`docker search`指令搜索镜像：

```
$ docker search [查询内容]
```

`docker search`指令并未提供依据`TAG`搜索镜像的功能，名称相同`TAG`不同的镜像需要在`Docker Hub`中查找。

使用`docker tag`指令可设置镜像的名称：

```
$ docker tag [镜像ID/镜像名称] [镜像新名称]
```

对于未设置镜像名称的镜像，会为原镜像添加`REPOSITORY`、`TAG`等信息；  
对于已设置镜像名称的镜像，会创建内容与原镜像相同，使用新`REPOSITORY`、`TAG`等信息的新镜像。

从`dcoker pull`指令从`Docker Hub`中拉取镜像到本地：

```
$ docker pull [镜像仓库] //拉取指定名称默认TAG的镜像
$ docker pull [镜像仓库:镜像TAG] //拉取指定名称指定TAG的镜像
$ docker image pull [镜像仓库] //拉取镜像，与 docker pull 相同
```

其它镜像管理指令：

```
$ docker rmi [镜像ID/镜像名称] //删除指定镜像
$ docker image rm [镜像ID/镜像名称] //删除指定镜像，同 docker rmi
$ docker image inspect [镜像ID/镜像名称] //显示镜像详情
```

## 容器管理
容器是镜像的运行实例，容器在独立、隔离的`Linux`环境中运行一个或一组进程。

使用`docker create`指令创建容器，并在创建容器时指定启动的进程：

```
$ docker create [选项] [镜像] [启动进程] [进程参数...]
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
`docker`官方提供了镜像托管服务`Docker Hub`。  
在`https://hub.docker.com`中注册，在本机使用`docker login`登陆账户后即可使用镜像托管服务。  
将本地的个人镜像上传到`Docker Hub`：

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

将测试镜像上传到`Docker Hub`：

```
$ docker push dainslef/test_image:2333
```



# 文件共享
`docker`存储采用特殊的`Union File System`(联合文件系统)机制，容器内的文件不能直接被外部访问。  
容器与宿主机之间的文件共享可以通过以下方式：

- 使用`docker cp`指令直接在宿主机与容器之间传输文件
- 使用`Bind mounts`(绑定挂载)机制，在容器中的指定路径下挂载外部宿主机的某个目录
- 使用`Volumes`(卷)机制，由`docker`创建并管理的存储卷，由容器启动时挂载，相比`Bind mounts`具有更好的可管理性和可迁移性

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
