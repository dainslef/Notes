<!-- TOC -->

- [概述](#概述)
- [安装与配置](#安装与配置)
	- [基本使用](#基本使用)
	- [在 *macOS* 中使用 *docker*](#在-macos-中使用-docker)
- [镜像与容器](#镜像与容器)
	- [获取镜像](#获取镜像)

<!-- /TOC -->



## 概述
`docker`是使用`Go`实现的开源容器引擎。  
`docker`将应用与依赖项放置在容器中执行，仅仅依赖宿主机的内核，简化了应用的运维与部署。



## 安装与配置
各类`Linux`发行版的官方仓库中均内置了`docker`，使用发行版内置的包管理器安装即可：

```
# pacman -S docker //Arch Linux
# apt install docker.io //Debian系
```

`docker`容器使用宿主机的内核，需要宿主机内核版本`3.10+`。

### 基本使用
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

### 在 *macOS* 中使用 *docker*
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



## 镜像与容器
镜像与容器是`docker`中的核心概念。

- **容器**(`Container`)是一个/一组在独立环境中执行的应用。
- **镜像**(`Image`)是用于创建容器的模版。

### 获取镜像
镜像包含一个定制的`Linux`环境，提供创建容器所需的文件。

`Docker Hub`(`https://hub.docker.com`)提供了镜像托管服务，可在该网站中查找各类定制镜像。  
各大发行版厂商均在`Docker Hub`中提供了官方镜像，一些社区也提供了用于运行特定软件服务的定制镜像。

使用`docker search`指令搜索镜像：

```
$ docker search [镜像名称]
```

完整的镜像名称由`[NAME]:[TAG]`形式构成，一般情况下，镜像`TAG`可省略，省略镜像`TAG`时会使用默认`TAG`。  
`docker search`指令并未提供依据`TAG`搜索镜像的功能，名称相同`TAG`不同的镜像需要在`Docker Hub`中查找。

从`dcoker pull`指令从`Docker Hub`中拉取镜像到本地：

```
$ docker pull [镜像名称] //拉取指定名称默认TAG的镜像
$ docker pull [镜像名称:镜像TAG] //拉取指定名称指定TAG的镜像
```
