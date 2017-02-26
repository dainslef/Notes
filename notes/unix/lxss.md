[TOC]

在`Windows 10`周年更新`Version 1607`中引入了`Linux Subsystem`(`LXSS`)。

## 使用 *Linux Subsystem*
启用`Linux Subsystem`需要执行以下步骤：

0. `设置`中启用`开发人员模式`。
0. `启用或关闭Windows功能`中勾选`适用于Linux的Windows子系统`。
0. 在`CMD`中输入`bash`指令，按照提示即可进入子系统安装步骤。


## *Linux Subsystem* 概述
`Linux Subsystem`的安装路径为`[用户目录]/AppData/Local/Lxss`路径下。
在`Linux Subsystem`中，`Windows`下的分区会被挂载到`/mnt`路径下。

`Linux Subsystem`使用`lxrun`工具进行管理：

- `lxrun /install` 安装子系统
- `lxrun /uninstall` 移除子系统，默认情况下保留`/home`和`/root`目录，指令搭配`/full`参数则执行完全卸载
- `lxrun /update` 更新子系统的包索引
- `lxrun /setdefaultuser` 配置子系统用户

### 与 *Cygwin/Msys* 比较
`Linux Subsystem`与`Msys`等有着本质区别：

- `Msys`是传统的`Unix`工具链的`Windows`版本移植，是编译成`Windows`二进制格式(`PE32/PE32+`)的程序。
- `Linux Subsystem`是运行在`Windows`内核上的完整`Linux`系统，软件包均为原生的`Linux`二进制格式(`ELF`)程序。

`Linux Subsystem`优劣
> 优势：
>
> `Linux Subsystem`是**完整的**`Linux`发行版(`Bulid 14393.10`内置的子系统基于`Ubuntu 14.04`)，`Linux Subsystem`直接使用`Ubuntu`官方源，能够使用几乎所有`Ubuntu`软件包。
>
> 劣势：
>
> `Linux Subsystem`需要使用`Bash Launcher`进入独立的`Linux`环境，`Linux`环境与`Windows`环境相互独立存在，交互较为困难，`Linux Subsystem`下的`Unix`工具如同`Linux`原生程序一样区分大小写、不支持`Windows`格式的路径。

`Msys`优劣
> 优势：
>
> `Msys`将传统`Unix`工具直接编译为`Windows PE32/PE32+`可执行格式，可直接在`CMD`中调用，`Cygwin/Msys`移植的`Unix`工具能够直接支持`Windows`格式的路径，与现有的`Windows`环境无缝交互。
>
> 劣势：
>
> `Msys/Cygwin`源中移植到`Windows`平台的`Unix`工具数目有限。