# Nix package manager
`Nix package manager`是纯函数式(purely functional)的包管理器，
Nix像纯函数式语言(如Haskell)处理值一样对待软件包：通过无副作用(no side-effects)的纯函数来构建，在构建完成后就不再改变。

与传统的软件包管理器设计不同，Nix将软件包存储在`Nix Store`中(通常是`/nix/store`路径下)，
每个软件包存储在**独立**的子目录中,软件包路径的命名规则为`[软件包id]-[软件包名]-[版本]`，路径示例：

```
/nix/store/b6gvzjyb2pg0kjfwrjmg1vfhh54ad73z-firefox-33.1/
```

## 多版本管理
Nix包管理器支持同时管理、安装一个软件包的多个版本，
保证了不同应用在依赖同一个软件包的不同版本时不会造成`DLL hell`(动态库依赖地狱)。
不同版本的软件包安装在Nix Store中的不同路径下，各自隔离，不会相互影响。

## 基本指令
查询、安装、移除、更新软件包：

```c
// 查询软件包
# nix-env -q [软件包名称]
# nix-env -qa

// 安装软件包
# nix-env -i [软件包名称]
# nix-env --install [软件包名称]
// 移除软件包
# nix-env -e [软件包名称]
# nix-env --uninstall [软件包名称]

// 更新所有软件包
# nix-env -u
// 更新指定软件包
# nix-env -u '软件包'
```

使用`nix-env -e`删除的软件包并为真正的删除软件包本体，而是移除了到该软件包的软链接。
使用`nix-store --gc`来真正清理软件包缓存：

```c
// 清理软件包时会计算当前系统的依赖关系，将不被依赖的软件包全部清理
# nix-store --gc

// 使用--print-dead参数时仅计算并打印会被清理的依赖，不真正执行清理操作
# nix-store --gc --print-dead
```



# NixOS
`NixOS`是基于`Nix package manager`的Linux发行版，提供了统一的包管理与配置管理。

## 安装
[NixOS官网](https://nixos.org/nixos/download.html)提供了镜像下载，官方提供的镜像支持`x86/x64`平台。
镜像包括带有KDE桌面的LiveCD版(`Graphical live CD`)和无GUI环境的精简版(`Minimal installation CD`)，

以`Minimal installation CD`为例，下载刻录镜像后启动进入安装环境。
首先对磁盘进行分区，安装镜像中提供了`fdisk`、`gparted`等常用分区工具，分区操作与其它发行版安装流程相同。
对于旧式BIOS的机器推荐使用DOS分区表搭配MBR引导，对于支持UEFI的机器推荐使用GPT分区表搭配UEFI启动。

通常最精简的UEFI安装包括三个分区，存放引导器的启动分区`ESP`、交换区`SWAP`、主分区。
以fdisk工具为例，三个分区的分区类型(partiton table)和分区路径配置如下：

| 分区路径 | 分区类型(类型编号) | 分区作用 | 推荐大小 | 文件系统 |
| :- | :- |
| /dev/sda1 | EFI System (1) | 存放引导器 | 200MB | FAT32(vfat) |
| /dev/sda2 | Linux swap (19) | 虚拟内存 | 1～2倍内存大小 | / |
| /dev/sda3 | Linux filesystem (20) | 主要分区 | 20GB+ | EXT4/XFS/BTRFS |

分区完成后在对应分区创建文件系统：

```c
# mkfs.vfat /dev/sda1
# mkswap /dev/sda2
# mkfs.ext4 /dev/sda3
```

挂载分区到安装环境的`/mnt`目录下：

```c
# mount /dev/sda3 /mnt
# mkdir -p /mnt/boot
# mount /dev/sda1 /mnt/boot
# swapon /dev/sda2
```

之后开始生成Nix安装配置：

```c
# nixos-generate-config --root /mnt
```

编辑生成的Nix配置`/mnt/etc/nixos/configuration.nix`，多数配置使用默认值即可。
针对UEFI启动，需要确认以下选项是否开启：

```sh
boot.loader.systemd-boot.enable = true # 启动 systemd 的启动支持
boot.loader.efi.canTouchEfiVariables = true # 允许安装进程修改EFI启动参数
```

Nix配置修改完成后执行安装操作：

```c
# nixos-install
```

执行指令后安装器会以给定的Nix配置执行系统安装流程：安装系统文件、配置引导器、配置账户信息等。
