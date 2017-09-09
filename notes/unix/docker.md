<!-- TOC -->

- [概述](#概述)
- [安装与配置](#安装与配置)
	- [基本使用](#基本使用)

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
