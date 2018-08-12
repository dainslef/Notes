- [ftp](#ftp)
	- [连接服务器](#连接服务器)
	- [常用指令](#常用指令)
- [SSH](#ssh)
	- [远程登录](#远程登录)
	- [服务配置](#服务配置)
	- [配置免密登陆](#配置免密登陆)
- [GNU GRUB](#gnu-grub)
	- [安装与配置](#安装与配置)
	- [安装引导器](#安装引导器)
	- [修复引导](#修复引导)
- [ulimit](#ulimit)
	- [配置文件](#配置文件)
	- [Core Dump (核心转储)](#core-dump-核心转储)
- [fdisk](#fdisk)
- [*parted*](#parted)
- [LVM](#lvm)
	- [基本操作](#基本操作)
	- [Physical Volume (PV，物理卷)](#physical-volume-pv物理卷)
	- [Volume Group (VG，卷组)](#volume-group-vg卷组)
	- [Logical Volume (LV，逻辑卷)](#logical-volume-lv逻辑卷)
- [curl](#curl)
	- [FTP 操作](#ftp-操作)
- [Suspend 和 Hibernate](#suspend-和-hibernate)
- [systemd](#systemd)
	- [服务管理](#服务管理)
	- [服务分析](#服务分析)
	- [系统配置](#系统配置)
- [VTE](#vte)
	- [启动参数](#启动参数)
- [apt](#apt)
	- [源配置](#源配置)
	- [Debian 源](#debian-源)
	- [Ubuntu 源](#ubuntu-源)
	- [apt-mirror](#apt-mirror)
		- [本地源配置](#本地源配置)
		- [使用本地源](#使用本地源)
- [常见问题记录](#常见问题记录)
	- [Ubuntu](#ubuntu)
		- [invoke-rc.d: initscript Xxxx, action "stop" failed.](#invoke-rcd-initscript-xxxx-action-stop-failed)



# ftp
`Windows`系统下提供了`ftp`命令行工具用于访问`FTP`服务器进行交互。

## 连接服务器
使用`ftp`指令与服务端建立连接：

```
$ ftp [服务端IP地址]
```

成功建立连接后，会提示输入`FTP`用户名/密码，如下所示：

```
> ftp [服务端IP地址]
连接到 [服务端IP地址]。
...
用户([IP地址]:(none)): Xxx
331 Password required for Xxx
密码:
230 User Xxx logged in
ftp>
```

通过服务端用户验证后，会进入`ftp shell`，如下所示：

```
ftp> ...
```

亦可不指定服务端`IP`直接进入`ftp shell`，在`ftp`命令行中打开`FTP`连接。
在`ftp shell`中使用`open/close`指令建立/关闭连接，如下所示：

```
ftp> open [服务端IP地址]
连接到 [服务端IP地址]。
...
用户([IP地址]:(none)): Xxx
331 Password required for Xxx
密码:
230 User Xxx logged in
ftp>
```

## 常用指令
`ftp shell`中常用指令：

- `![指令]` 使用系统`Shell`执行指令
- `quit` 退出`ftp shell`
- `lcd/cd` 跳转本地/远程目录
- `open/close` 打开关闭连接
- `ls/dir` 查看`FTP`目录
- `put/send` 向`FTP`发送文件
- `get/recv` 接收来自`FTP`的文件
- `mkdir/rmdir` 创建/删除`FTP`目录
- `delete` 删除`FTP`的文件
- `rename` 重命名`FTP`的文件



# SSH
`SSH`全称`Secure Shell`，是一种加密的网络传输协议。
SSH通过在网络中建立`Secure Channel`(安全通道)实现SSH客户端与服务端之间的连接。

SSH常用在Unix系统中，用于传输命令行界面和远程执行指令。
相比使用明文传输的`Telnet`协议，SSH能够保证网络环境中信息加密完整可靠。

SSH的主流实现是`OpenSSH`(全称`OpenBSD Secure Shell`)。

## 远程登录
使用`ssh`指令远程登录配置了SSH服务的主机：

```c
// 使用 -p 参数指定远程登录端口，SSH服务默认端口为22
$ ssh [用户名]@[主机名/IP]
```

## 服务配置
SSH服务相关配置文件位于`/etc/ssh`路径下：

- `/etc/ssh/ssh_config` ssh指令使用的配置
- `/etc/ssh/sshd_config` SSH服务使用的配置

常用SSH服务配置：

- `PermitRootLogin`

	配置SSH服务是否允许root登陆。

	| 配置项 | 取值含义 |
	| :- | :- |
	| yes(默认) | 允许root用户登陆 |
	| no | 不允许root用户登陆 |
	| without-password | 可登陆root用户，但不能以密码验证的方式登陆(可用key验证) |
	| forced-commands-only | 可登陆root用户，但登陆后仅能执行指令后退出，不能交互 |

- `UseDNS`

	配置是否启用DNS PTR。
	动态IP通常不会有PTR记录，开启DNS PTR有时导致SSH登陆过慢。

	| 配置项 | 取值含义 |
	| :- | :- |
	| yes | 开启 |
	| no | 关闭 |

## 配置免密登陆
默认配置下，登陆SSH需要密码，当部署一些依赖SSH协议的分布式服务时(如`Hadoop`、`Zookeeper`、`Kafka`等)，需要配置免密登陆。

使用`ssh-keygen`工具生成公钥和私钥，如下所示：

```
$ ssh-keygen -t rsa
```

执行指令后会出现交互式对话提示输入一些密钥相关的信息，全部回车使用默认选项即可。
指令执行结束后，会在`~/.ssh`路径下生成以下文件：

- `id_rsa` 私钥文件，文件权限`600`
- `id_rsa.pub` 公钥文件，文件权限`644`

在`~/.ssh`路径下创建`authorized_keys`文件：

- 将其它机器的公钥加入其中，允许其它机器免密登陆本机。
- 将本机的公钥加入其它机器的authorized_keys文件中，则允许本机免密登陆其它机器。

将本机公钥添加到目标主机可以使用`ssh-copy-id`指令：

```c
// 将 ~/.ssh/id_rsa.pub 中记录的公钥加入目标主机
$ ssh-copy-id [目标用户名]@[目标主机地址/IP]

// 指定公钥加入目标主机
$ ssh-copy-id [目标用户名]@[目标主机地址/IP] -I [指定公钥路径]
```

正确生成当前机器的公钥、私钥，并将公钥写入目标机器authorized_keys文件中即可实现SSH免密登录目标机器。

使用ssh指令登陆目标机器时，默认使用`~/.ssh/id_rsa`文件做为私钥进行验证，若需要指定私钥文件，可以添加`-i`参数：

```c
$ ssh -i [指定私钥路径] [目标用户名]@[目标主机地址/IP]
```



# GNU GRUB
`GRUB`(`GRand Unified Bootloader`)是现代Linux的标准启动管理器，是`LILO`(`Linux Loader`)的替代品。

GRUB支持多重引导，除了Linux，也能用于引导`Windows`、`FreeBSD`等其它现代操作系统。
GRUB在较新版本中提供了对`UEFI BIOS`新型固件的支持。

早期版本的GRUB(`i.e. version 0.9x`)现在被称为`GRUB Legacy`，已停止开发。
GRUB现在的主要版本为`GRUB 2`。

## 安装与配置
`GRUB`作为重要的系统组件，通常已被收录于各大发行版的官方源中，多数发行版会默认安装`GRUB`。
使用包管理手动安装`GRUB`：

```
# pacman -S grub //Arch Linux
# apt install grub-common //Ubuntu、Debian
```

`GRUB`的配置文件为`/boot/grub/grub.cfg`，可以使用`grub-mkconfig`指令根据已安装的`OS`自动生成合适的引导配置：

```
# grub-mkconfig -o /boot/grub/grub.cfg //通用
# update-grub //Debian系专属
```

默认`grub-mkconfig`生成配置时仅会扫描硬盘中的`Linux`发行版，若需要生成的配置包含其它`OS`的引导菜单，需要额外安装`os-prober`组件：

```
# pacman -S os-prober //Arch Linux
# apt install os-prober //Ubuntu、Debian
```

## 安装引导器
正确生成`GRUB`配置后，使用`grub-install`将引导器安装到硬盘中。
对于使用`MBR`电脑，应在安装时指明安装设备：

```
# grub-install /dev/sda //将GRUB引导器安装到硬盘 /dev/sda 中
```

对于使用`UEFI`固件的新式电脑，需要将`ESP`分区挂载到`/boot/efi`路径下，并且额外安装`efibootmgr`组件:

```
# pacman -S efibootmgr //Arch Linux
# apt install efibootmgr //Ubuntu、Debian
```

将`GRUB`引导器安装到`UEFI`固件的电脑中无需额外参数：

```
# grub-install
```

安装完成后会在`ESP`分区中生成对应的`efi`引导文件。

## 修复引导
当分区结构发生变化时，引导器可能不能正常加载。
若开机进入以`grub rescue>`为提示符的救援界面时，可尝试以下步骤恢复：

1. 查看分区结构，确认`Linux`分区位置。

	执行`ls`指令，查看分区列表：

	```
	grub rescue> ls
	(hd0) (hd0,gpt1) (hd0,gpt2) (hd0,gpt3) ...
	```

	确认分区的文件系统：

	```
	grub rescue> ls (hd0,gpt2)
	(hd0,gpt2): Filesystem is unknown.
	grub rescue> ls (hd0,gpt3)
	(hd0,gpt3): Filesystem is ext2.
	```

	确认分区的内容：

	```
	grub rescue> ls (hd0,gpt3)/
	...
	```

1. 指定启动分区位置，手动加载启动器。

	确认分区的位置后，设置启动参数：

	```
	grub rescue> set boot=(hd0,gpt3)
	grub rescue> set prefix=(hd0,gpt3)/boot/grub
	grub rescue> insmod normal
	grub rescue> normal
	```

	之后即可进入正常的GRUB引导界面。

1. 重新安装引导器。

	正常启动系统后，在终端重新安装引导器：

	```
	# grub-install /dev/sda //MBR
	# grub-install //UEFI
	```



# ulimit
使用`ulimit`指令查看和设定各类限制。
指令格式：

```
$ ulimit [类别] [限制数值]
```

其中，常见类别如下：

- `-a` 查看所有种类的限制
- `-f` 文件存储
- `-c` 核心文件转储
- `-t` CPU时间
- `-s` 堆栈大小
- `-u` 用户进程数
- `-n` 打开文件数
- `-m` 内存大小

`限制数值`参数为空时，指令为查询相关设定。
`限制数值`参数不为空时，指令为设定参数(可取值`unlimited`，表示**不限制**该类文件大小)。

以**核心转储**为例：

- `$ ulimit -c` 查看系统设定的核心转储大小
- `$ ulimit -c unlimited` 设置核心转储大小为无限

## 配置文件
通过配置文件`/etc/security/limits.conf`配置相关限制。
`limits.conf`文件每行为一条配置，依次为`<domain>`、`<type>`、`<item>`、`<value>`。

- `demain`(域)，域可以是用户名、用户组(使用`@`修饰)，或是通配符。
- `type`(类别)，可取值`soft/hard`，代表**软限制/硬限制**。
- `item`(目标)，为需要限制的资源类别，可取值`core`(核心转储)、`fsize`(文件大小)等，与指令参数对应。
- `value`(值)，指定限制资源的数值。

如下所示：

```
#<domain>      <type>  <item>         <value>

#*               soft    core            0
#root            hard    core            100000
#*               hard    rss             10000
#@student        hard    nproc           20
#@faculty        soft    nproc           20
#@faculty        hard    nproc           50
#ftp             hard    nproc           0
#ftp             -       chroot          /ftp
#@student        -       maxlogins       4
```

## Core Dump (核心转储)
启用核心转储后，则在进程执行异常退出时，会生成包含异常信息的错误转储文件。
使用`gdb`可分析转储文件：

```
$ gdb [进程文件] [进程核心转储]
```

进入`gdb shell`之后，使用`bt`指令查看调用堆栈。



# fdisk
`fdisk`是Linux命令行下常用的交互式分区工具。

早期的fdisk不能识别`GPT`分区表，划分`GPT`分区需要使用`parted`工具。
最近版本的fdisk已经能够正常识别、显示与创建`GPT`分区。

使用fdisk显示分区信息：

```
# fdisk -l [磁盘路径]
```

进行具体的磁盘分区操作需要进入fdisk会话：

- `# fdisk` 直接进入fdisk会话，选择第一块硬盘为当前硬盘
- `# fdisk [磁盘路径]` 进入fdisk会话，并选择指定硬盘为当前硬盘

在`fdisk`会话中，操作指令同样会以对话的形式引导完成操作，基本指令如下：

- `m` 显示指令菜单
- `n` 创建分区
- `d` 删除分区
- `l` 列出已知的分区类型
- `F` 列出未分配的磁盘空间
- `p` 打印分区信息，输出结果与在命令行中输入`fdisk -l`相同
- `i` 列出某一个分区的具体信息
- `t` 修改分区类型信息
- `o` 创建DOS分区表
- `g` 创建GPT分区表
- `x` 进入高级功能会话

在`fdisk`中使用`x`指令后进入高级功能会话，常用指令如下：

- `m` 功能不变，显示指令菜单
- `n` 修改分区名称
- `r` 返回主选单

在`fdisk`会话中进行的操作**不是**立即生效的，退出`fdisk`会话之前需要进行确认：

- `w` 将改动真正写入硬盘
- `q` 不保存改动退出



# *parted*
`parted`是Linux下的另一种交互式分区工具，与`fdisk`相比，`parted`一直支持GPT分区表，并且在功能选项上更加丰富，但在交互上没有`fdisk`简便。

- `# parted [磁盘路径] print` 显示分区信息
- `# parted [磁盘路径] print all` 显示所有分区信息

与`fdisk`工具类似，执行具体的磁盘分区需要进入`parted`会话：

```
# parted [磁盘路径]
```

`parted`会话中的基本指令如下：

- `help` 显示指令列表
- `help [指令名称]` 显示指定指令的用法
- `select [磁盘路径]` 切换到指定磁盘
- `mklabel [分区表类型]` 创建指定类型分区表，常用的分区表类型为`msdos`和`gpt`
- `mkpart [分区类型(主分区/扩展分区)] [文件系统(可选)] [分区起始位置] [分区结束位置]` 创建分区<br>
	正确使用带有参数的`mkpart`指令可直接创建分区。<br>
	使用不带参数的`mkpart`指令则会以会话的形式引导输入创建分区所需的参数。
- `rm [分区号]` 删除指定分区
- `set [分区号] [分区标识] on/off` 添加/删除指定分区的分区标志
- `toggle [分区号] [分区标识]`
- `name [分区号] [分区名称]` 命名指定分区
- `print` 显示分区信息
- `print free` 显示分区信息，包括磁盘中未被使用的空间
- `print all` 显示所有分区信息
- `quit` 退出`parted`会话

相比`fdisk`，`parted`会话中的分区操作是立即执行并生效的，因此更需小心谨慎。



# LVM
`LVM`是`Logical Volume Manager`(逻辑卷管理)的简写，是Linux环境下对磁盘分区进行管理的一种机制。

使用`LVM`能够将不同的硬盘上的物理卷(`Physical Volume`，简称`PV`)加入卷组(`Volume Group`，简称`VG`)。
在卷组中将其划分为不同的逻辑卷(`Logical Volume`，简称`LV`)，然后在逻辑卷中创建文件系统并进行挂载。

## 基本操作
配置`LVM`的**基本步骤**：

1. 创建硬盘分区
1. 创建物理卷：`# pvcreate [硬盘路径/分区路径]`(物理卷可以是整个硬盘或是硬盘中的某个分区)
1. 创建卷组：`# vgcreaate [卷组名称] [需要加入卷组的物理卷分区路径]`
1. 创建逻辑卷：`# lvcreate -L [分区大小(xxGB/xxMB/...)] -n [逻辑分区名称] [卷组名称]`
1. 格式化逻辑分区，挂载使用

## Physical Volume (PV，物理卷)
物理卷`Physical Volume`是在磁盘上**实际存在**的物理分区。
被添加到`LVM`的物理分区需要拥有`lvm`标识(flag)。

物理卷相关的操作为`pvXXX`系列指令：

- `# pvcreate [硬盘路径/物理分区路径]` 创建物理卷
- `# pvremove [硬盘路径/物理分区路径]` 移除物理卷
- `# pvmove [原物理分区路径] [目标物理分区路径]` 将原物理卷中的数据转移到另一物理卷
- `# pvdisplay` 显示已创建的物理卷

移除一个物理卷需要先将该物理卷从所属的卷组中移除。
移除物理卷前需要保证没有数据存储在该物理卷中，若**要被移除的物理卷**中已有数据，则需要使用`pvmove`指令将该卷中的数据转移到其它卷。

## Volume Group (VG，卷组)
物理卷需要加入卷组(`Volume Group`)才能被使用。

卷组相关的操作为`vgXXX`系列指令：

- `# vgcreate [卷组名称] [物理卷路径]` 一个卷组至少需要包含一个物理卷，物理卷路径可为多个
- `# vgreduce [卷组名称] [物理卷路径]` 从一个卷组中删除指定的物理卷
- `# vgremove [卷组名称]` 移除指定卷组
- `# vgdisplay` 显示所有卷组

## Logical Volume (LV，逻辑卷)
逻辑卷(`Logical Volume`)是`LVM`中实际用于创建文件系统、挂载的分区。
逻辑卷的磁盘路径为`/dev/[逻辑卷所属卷组名称]/[逻辑卷名称]`，使用该路径可以像操作物理磁盘一样对其进行创建文件系统、挂载等操作。

逻辑卷相关的操作为`lvXXX`系列指令：

- `# lvcreate -L [分区大小(xxGB/xxMB/...)] -n [逻辑分区名称] [卷组名称]` 创建逻辑卷
- `# lvresize -L +/-[分区大小(xxGB/xxMB/...)] [逻辑分区名称]` 在原先逻辑卷大小的基础上扩充/缩减指定大小
- `# lvextend -L [分区大小(xxGB/xxMB/...)] [逻辑分区名称]` 增加逻辑卷到指定大小(分区大小的数值需要大于原先该逻辑分区的大小)
- `# lvreduce -L [分区大小(xxGB/xxMB/...)] [逻辑分区名称]` 减小逻辑卷到指定大小(分区大小的数值需要小于原先该逻辑分区的大小)
- `# lvremove [逻辑分区名称]` 移除指定逻辑卷
- `# lvdisplay` 显示所有逻辑卷

扩展逻辑卷大小无需卸载、重新挂载文件系统。
缩减逻辑卷大小需要重先卸载文件系统之后**同时**缩减文件系统大小和逻辑卷大小，之后重新挂载。



# curl
`curl`是一款功能强大的文件传输工具。

基本指令为：

```
$ curl [目标文件路径]
```

curl对于获取的文件会直接以文本的形式输出在终端上，可以使用`-o`参数导出到文件。
对于一些可能需要验证用户权限的协议(如`ftp`)，可以使用`-u`参数添加用户信息，指令格式如下：

```
$ curl [目标文件路径] -u [用户名]:[密码] -o [输出文件路径]
```

## FTP 操作
使用`curl`工具进行`FTP`操作：

- `$ curl ftp://[ip/域名] -u [用户名]:[密码]` 列出FTP下的文件、目录列表
- `$ curl ftp://[用户名]:[密码]@[ip/域名]` 列出FTP下的文件、目录列表(简化)
- `$ curl ftp://[用户名]:[密码]@[ip/域名]/[文件路径] -o [输出文件路径]` 传输FTP文件到本地指定路径
- `$ curl ftp://[用户名]:[密码]@[ip/域名] -T [本地文件路径]` 上传本地文件到FTP

在上传/下载时，默认情况下会出现进度提示，可添加`-s`参数取消进度提示。

对于一些复杂的FTP功能，需要直接使用FTP**协议指令**来完成。
在`curl`工具中，使用`-X`参数追加协议指令，命令格式如下：

```
$ curl ftp://[用户名]:[密码]@[ip/域名] -X "[FTP协议指令]"
```

常见的FTP协议指令如下：

| 指令 | 指令功能 |
| :- | :- |
| dele [FTP文件路径] | 删除FTP内文件 |
| rmd [FTP目录] | 删除FTP内目录 |
| mkd [FTP目录] | 创建FTP目录 |
| list [FTP目录] | 列出FTP目录 |
| rnfr [FTP文件路径] | 重命名FTP文件(第一步，指定需要重命名的文件) |
| rnto [FTP文件路径] | 重命名FTP文件(第二步，指定文件重命名的名称) |

对于协议指令，`curl`会在终端打印协议指令的执行结果(返回值)，FTP协议指令的常见返回值含义如下：

| 返回值 | 说明 |
| :- | :- |
| 250 | 请求的文件操作正常进行，已完成 |
| 257 | 路径已创建 |
| 350 | 请求的文件操作在等待更进一步的信息 |
| 421 | 服务不可用，关闭控制连接 |
| 500 | 语法错误，无法识别命令(包括命令行过长之类的错误) |
| 501 | 参数或变元中有语法错误 |
| 502 | 命令还没有被实现 |
| 503 | 命令的顺序不对 |
| 530 | 无法登录 |
| 550 | 请求的操作无法执行，文件不可用(例如找不到文件，无访问权) |



# Suspend 和 Hibernate
*Suspend*和*Hibernate*是很容易混淆的两个概念。

- `Suspend`(**睡眠**)：

	睡眠状态下，系统将关闭大部分硬件的工作，系统状态将会被保存在`RAM`中。
	处于睡眠状态下的计算机将以极低的功耗运转，但系统仍需要供电，电源指示灯会依旧闪烁。
	现代计算机**进入睡眠状态/从睡眠状态唤醒**仅仅需要几秒时间。

- `Hibernate`(**休眠**)：

	休眠即`Suspend to disk`，系统将完全关闭所有硬件，系统状态将被保存在`SWAP`中。
	处于休眠状态下的计算机不需要供电，但系统分区时必须分配并挂载了`SWAP`交换区。
	从休眠状态下唤醒将从硬盘(`SWAP`)中加载系统状态。
	对于使用`HDD`的计算机，**进入休眠状态/从休眠状态唤醒**需要几十秒甚至更久，相当于正常开机的速度。



# systemd
`systemd`是`Linux`下新式的init系统，在各大发行版中逐渐替代了原先`Unix System V`风格的init系统。

systemd的设计理念来自于`Apple`公司`macOS`中的`launchd`，
传统的SystemV风格init系统需要一次一个串行地启动服务进程，
systemd则根据服务进程的依赖关系并行地启动服务，极大地减少了系统的启动耗时。

配置文件：

- `/etc/systemd/system.conf` 全局配置文件
- `/etc/systemd/user.conf` 用户配置文件

## 服务管理
`systemd`提供了统一、完整的服务管理功能：

- `# systemctl status [服务名称]` 查看指定服务状态
- `# systemctl start [服务名称]` 启动指定服务
- `# systemctl stop [服务名称]` 停止指定服务
- `# systemctl enable [服务名称]` 设置指定服务开机自启动
- `# systemctl disable [服务名称]` 取消指定服务开机自启动

`systemd`服务文件通常以`*.service`为后缀名。

- 系统服务：

	系统服务文件位于路径`/usr/lib/systemd/system`下。
	启用、禁用系统服务需要使用`root`权限(查看服务状态不需要)。

- 用户服务：

	用户服务文件位于路径`/usr/lib/systemd/user`下。
	管理用户服务不需要以`root`权限执行`systemctl`指令，但需要在指令中添加`--user`参数：

	```
	$ systemctl --user status/start/stop/enable/disable [用户服务名称]
	```

## 服务分析
`systemd`提供了一系列工具用于查看查看、分析各类服务状态。

使用`pstree`指令可以列出本机完整的systemd服务进程树。

使用`systemctl list`系列指令查看服务状态：

- `$ systemctl list-units` 列出已加载的服务单元信息
- `$ systemctl list-dependencies` 列出已加载服务单元的依赖关系
- `$ systemctl list-unit-files` 列出已安装服务单元(所有服务单元)的自启状态
- `$ systemctl list-units -t [服务类型]` 查看指定类型的服务信息

使用`systemd-analyze`指令分析系统的启动性能：

- `$ systemd-analyze` 显示系统的启动耗时
- `$ systemd-analyze blame` 列出所有的启动单元，按照启动耗时的高低进行排序

## 系统配置
`systemd`还集成了常用的系统配置工具：

- `hostnamectl` 配置主机名称
- `timedatectl` 时区时间配置
- `localectl` 语言编码配置
- `networkctl` 网络配置
- `coredumpctl` 核心转储查看工具
- `journalctl` 日志查看工具



# VTE
`VTE`是`Gnome`项目提供的轻量级终端库，许多终端软件使用`VTE`实现，如`gnome-terminal`、`roxterm`等。
`VTE`自身亦可做为独立的终端软件使用。

相比其它终端模拟器，`VTE`提供了丰富的特性和较少的依赖(仅仅依赖`GTK+`)。

`VTE`当前的主流版本为基于`GTK+ 2`的`VTE2`和基于`GTK+ 3`的`VTE3`。
在`Arch Linux`的打包中，`VTE2`的指令名称为`vte`，`VTE3`的指令名称为`vte-2.91`。

## 启动参数
`VTE`通过在启动时添加命令行参数进行设置。

`VTE2`常见参数如下所示：

- `-g` 设定终端初始大小(行列大小)，格式为`mxn`
- `-f` 设定终端字体，参数后添加字体名称
- `-n` 设定终端可回滚的行数，参数后添加回滚行数数值
- `-h` 设定终端色彩
- `-c` 在终端中执行指令
- `-W` 使用`GtkScrolledWindow`做为终端容器，启用此参数时使用`-g`参数设定终端大小才有效
- `-P` 设定终端的滚动条显示模式，参数可以为`always`(总是显示)、`auto`(自动)、`never`(从不显示)
- `-B` 设定终端背景图片
- `-S` 设定终端使用的`shell`
- `--reverse` 反转终端色彩

以`awesomewm`配置中使用的`VTE`选项为例：

```
$ vte -W -P never -g 120x40 -f "Monaco 10" -n 5000 --reverse
```

执行结果为打开大小为`120`列`40`行的`VTE2`终端，终端回滚`5000`行，不显示滚动条，反转配色。



# apt
`apt`是`Debian`系列发行版的前端包管理工具。

`apt`主要功能：

- 在镜像源中搜索、查找需要的软件包。
- 计算软件包的依赖。
- 安装、卸载软件包。
- 查看指定软件包的状态。
- 变更已安装软件包的状态。
- 系统更新。

## 源配置
使用`apt`工具需要正确配置镜像源地址，配置文件为`/etc/apt/sources.list`。

`Debian`系列发行版软件源格式为：

```sh
# 二进制包
deb [软件源地址] [版本号] [仓库类型]

# 源码包
deb-src [软件源地址] [版本号] [仓库类型]
```

其中：

- `软件源地址` 为有效的`URL`，可以是某个提供镜像源服务的站点地址，也可以是本地源路径
- `版本号` 为发行版的版本代号，一行只能填写一个版本号
- `仓库类型` 为按照授权类型划分的仓库类别，可以一行同时添加多个仓库类型

`Ubuntu`与`Debian`的版本号、仓库类型分类完全不同。

## Debian 源
`Debian`版本号有两类：

1. 固定版本号，按照稳定程度分为`stable`、`testing`、`unstable`、`experimental`。
1. 版本代号。

两类作用相同，固定版本号会指向某个版本代号。
随着开发进度的变化，实际指向的版本代号会发生变化。

当前(`2017-5-11`)`Debian`的最新稳定版为`Debian 8`，版本代号为`jessie`，则使用固定版本号`stable`指向的实际版本号即为`jessie`。
当前处于开发状态的版本为`Debian 9`，版本代号为`stretch`，使用固定版本号`testing`则实际指向处于开发状态的版本代号`stretch`。

版本代号后可以追加版本仓库，`Debian`的版本仓库有：

- `[版本号]-updates` 提供常规更新
- `[版本号]-proposed-updates` 提供处于测试阶段的更新(不建议启用)
- `[版本号]-backports` 提供软件的`testing`功能性更新

版本仓库后需要指定启用的仓库类型，`Debian`仓库类型主要有三类：

- `main` 主要仓库，符合`DFSG`的开源软件
- `contrib` 包含依赖于非自由软件的开源软件
- `non-free` 非自由软件

以**中科大镜像源**为例，`Debian Stable`的`sources.list`配置：

```sh
deb https://mirrors.ustc.edu.cn/debian/ stable main contrib non-free
deb https://mirrors.ustc.edu.cn/debian/ stable-updates main contrib non-free
deb https://mirrors.ustc.edu.cn/debian/ stable-backports main contrib non-free
```

## Ubuntu 源
`Ubuntu`没有固定版本号，需要使用发行版本号，主要的`LTS`版本的版本代号：

| 版本 | 版本代号 |
|:----:|:------:|
| `12.04 LTS` | `precise` |
| `14.04 LTS` | `trusty` |
| `16.04 LTS` | `xenial` |

`Ubuntu`的版本仓库有：

- `[版本号]-security` 提供重要的安全性更新(漏洞修复)
- `[版本号]-updates` 提供建议的更新
- `[版本号]-backports` 提供功能性更新
- `[版本号]-proposed` 提供处于测试阶段的`updates`更新(不建议启用)

`Ubuntu`仓库类别有：

- `main` 主要仓库，完全的开源软件
- `restricted` 不完全的开源软件
- `universe` 社区支持、维护的软件
- `muitiverse` 非开源软件
- `partner` 闭源商业软件，该仓库仅有官方源可用

以**中科大镜像源**为例，`Ubuntu 16.04 LTS`的`sources.list`配置：

```
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial main restricted universe muitiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-security main restricted universe muitiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-updates main restricted universe muitiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-backports main restricted universe muitiverse

deb http://archive.canonical.com/ubuntu/ xenial partner
```

## apt-mirror
`apt-mirror`是`Debian`系列发行版中用于制作**本地源**的工具。

### 本地源配置
`apt-mirror`的配置文件为`/etc/apt/mirror.list`。若无特殊需求可直接使用默认配置。

默认配置下，镜像会被同步到本地的`/var/spool/apt-mirror`路径下。
修改`base_path`配置项可以指定本地镜像的存储位置。修改源地址可执行用于同步的远程镜像源。

以**中科大镜像源**为例，同步到本地的`~/Public/Mirrors`路径下，配置：

```sh
set base_path /home/Xxx/Public/Mirrors

deb http://mirrors.ustc.edu.cn/ubuntu xenial main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu xenial-security main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu xenial-updates main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-backports main restricted universe muitiverse
```

### 使用本地源
若仅需要本机使用本地源，可以直接使用`file:///...`访问本机的源路径。

`sources.list`配置：

```sh
deb file:///home/Xxx/Public/Mirrors/mirror/ubuntu xenial main restricted universe multiverse
deb file:///home/Xxx/Public/Mirrors/mirror/ubuntu xenial-security main restricted universe multiverse
deb file:///home/Xxx/Public/Mirrors/mirror/ubuntu xenial-updates main restricted universe multiverse
deb file:///home/Xxx/Public/Mirrors/mirror/ubuntu xenial-backports main restricted universe muitiverse
```



# 常见问题记录
记录各类发行版使用中可能会遇到的问题。

## Ubuntu
记录`Ubuntu`发行版中遇到的问题。

### invoke-rc.d: initscript Xxxx, action "stop" failed.
问题描述：<br>
卸载部分软件包时出现错误，无法正常卸载：

```
invoke-rc.d: could not determine current runlevel
 * ...
invoke-rc.d: initscript Xxxx, action "stop" failed.
dpkg: error processing package Xxxx (--remove):
 installed Xxxx package pre-removal script subprocess returned error exit status 1
Errors were encountered while processing:
 Xxxx
```

问题分析：<br>
卸载部分在`/etc/init.d`下注册了服务的软件包时，卸载脚本会尝试执行`invoke-rc.d`指令，调用对应的服务脚本指令关闭服务。
在部分特殊的Linux环境下(如`WSL`、`Docker`)，服务脚本可能会执行失败，脚本执行失败导致卸载操作错误退出。

解决方法：<br>
修改`/etc/init.d`对应服务的脚本文件，在脚本顶部添加`exit 0`，让脚本文件的实际逻辑不执行直接正常退出。
