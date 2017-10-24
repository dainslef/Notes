<!-- TOC -->

- [概述](#概述)
- [安装与配置](#安装与配置)
	- [基本使用](#基本使用)
	- [在 *macOS* 中使用 *docker*](#在-macos-中使用-docker)
- [镜像与容器](#镜像与容器)

<!-- /TOC -->



## 概述
`docker`是使用`Go`实现的开源容器引擎。  
`docker`将应用与依赖项放置在容器中执行，仅仅依赖宿主机的内核，简化了应用的运维与部署。



## 安装与配置
各类`Linux`发行版已经在仓库中内置了`docker`，直接使用发行版内置的包管理器安装即可。
如，在`Arch Linux`中：

```
# pacman -S docker
```

在`Ubuntu/Debian`中：

```
# apt install docker.io
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
待续。
