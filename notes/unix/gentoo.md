# 基本安装流程
首先，需要下载最近版本的镜像和portage树。

## 解压镜像
创建一个空的分区
挂到`/mnt`上，解压镜像到此：

```c
$ tar jvxf [镜像路径] -C /mnt //j参数
```

将portage树镜像解压到`/mnt/usr`目录：

```
$ tar jvxf [portage树目录] -C /mnt/usr
```

## 修改全局编译配置和USE标记
修改`/mnt/etc/portage/make.conf`，修改部分参数：

```sh
USE="X dbus kde -gnome -systemd -gstreamer"	# 如果是gnome桌面就"-kde"
MAKEOPTS="-j5" # 编译参数，为cpu核数加1
INPUT_DEVICES="evdev synaptics"
VIDEO_CARDS="radeon intel"
CFLAGS="-O2 -pipe -march=native"
GENTOO_MIRRORS="http://mirrors.ustc.edu.cn/gentoo" # 镜像目录
LINGUAS="zh_CN"
PYTHON_TARGETS="python3_4 python2_7"
PYTHON_SINGLE_TARGET="python3_4" # 设置默认的python环境
```

## 修改portage源
创建`/mnt/etc/portage/repos.conf/gentoo.conf`文件，加入portage树源：(该文件的父目录亦不存在，需要一同创建)

```ini
[gentoo]
location = /usr/portage
sync-type = rsync
sync-uri = rsync://mirrors.ustc.edu.cn/gentoo-portage
auto-sync = yes
```

## 添加环境变量
编辑`/mnt/etc/environment`，给新环境设置一些必要的环境变量(否则许多命令会提示找不到)：

```sh
LANG="en_US.utf8"
LC_ALL="en_US.UTF-8"
PATH=$PATH:/bin:/sbin:/usr/bin:/usr/sbin
```

## 配置DNS
复制当前机器的dns信息：

```c
# cp /etc/resolv.conf /mnt/etc/resolv.conf
```

## 进入gentoo环境
Gentoo没有提供类似`arch-chroot`之类的工具，因此在chroot之前需要手动绑定必要分区的位置：

```c
# mount -t proc none /mnt/proc
# mount --rbind /sys /mnt/sys
# mount --rbind /dev /mnt/dev
```

之后才能正常进入chroot环境：

```c
// 若当前环境shell并非bash，则需要显式指定chroot shell为bash，否则会提示shell不存在(stage3中仅包含bash)
# chroot /mnt /bin/bash

// 重新加载环境变量：
# source /etc/environment
```

## 编译内核
进入Gentoo的chroot环境后，安装内核源码：

```
# emerge gentoo-sources
```

转到内核源码目录`/usr/src/linux`，配置内核选项：

```
# make menuconfig
```

## 调整内核配置
查看机器pci信息：

```
00:00.0 Host bridge: Intel Corporation Haswell-ULT DRAM Controller (rev 09)
00:02.0 VGA compatible controller: Intel Corporation Haswell-ULT Integrated Graphics Controller (rev 09)
00:03.0 Audio device: Intel Corporation Haswell-ULT HD Audio Controller (rev 09)
00:14.0 USB controller: Intel Corporation 8 Series USB xHCI HC (rev 04)
00:16.0 Communication controller: Intel Corporation 8 Series HECI #0 (rev 04)
00:1b.0 Audio device: Intel Corporation 8 Series HD Audio Controller (rev 04)
00:1c.0 PCI bridge: Intel Corporation 8 Series PCI Express Root Port 3 (rev e4)
00:1c.3 PCI bridge: Intel Corporation 8 Series PCI Express Root Port 4 (rev e4)
00:1c.4 PCI bridge: Intel Corporation 8 Series PCI Express Root Port 5 (rev e4)
00:1d.0 USB controller: Intel Corporation 8 Series USB EHCI #1 (rev 04)
00:1f.0 ISA bridge: Intel Corporation 8 Series LPC Controller (rev 04)
00:1f.2 SATA controller: Intel Corporation 8 Series SATA Controller 1 [AHCI mode] (rev 04)
00:1f.3 SMBus: Intel Corporation 8 Series SMBus Controller (rev 04)
01:00.0 Ethernet controller: Broadcom Corporation NetXtreme BCM57786 Gigabit Ethernet PCIe (rev 01)
01:00.1 SD Host controller: Broadcom Corporation BCM57765/57785 SDXC/MMC Card Reader (rev 01)
02:00.0 Network controller: Qualcomm Atheros QCA9565 / AR9565 Wireless Network Adapter (rev 01)
03:00.0 Display controller: Advanced Micro Devices, Inc. [AMD/ATI] Opal XT [Radeon R7 M265] (rev ff)
```

部分重要的内核选项：


- 处理器：(Intel CPU可关闭AMD CPU特性)

	```
	Processor type and features  ——>
		[ ] Enable MPS table								//支持ACPI的电脑都不选
		[ ] Support for extended (non-PC) x86 platforms		//关闭PC平台以外的支持
		Processor family (Core 2/newer Xeon)
		[ ] Linux guest support  ----						//安装在虚拟机里才需要
		[*] Multi-core scheduler support					//开启多核心支持
		[*] SMT (Hyperthreading) scheduler support			//SMT超线程开启
		[*] Intel Low Power Subsystem Support				//haswell以上可选
		[ ] kexec system call
		[ ] Build a relocatable kernel
		[*] EFI runtime service support						//EFI主板开启
		[ ] EFI stub support								//用不到
		Preemption Model --->
			(X) Preemptible Kernel (Low-Latency Desktop)	//低延时模式
	```

- 设备驱动相关：

	```
	Device Drivers  --->
		[ ] Multiple devices driver support (RAID and LVM)  ----	//关闭磁盘阵列
		Graphics support  --->
			[ ] Bootup logo		//关了，启动动画没用
			[*] Laptop Hybrid Graphics - GPU switching support		//双显卡切换支持
			Direct Rendering Manager  --->
				<*> Direct Rendering Manager
				<*> Intel 8xx/9xx/G3x/G4x/HD Graphics
			Frame buffer Devices  --->
				[*] Simple framebuffer support
		<*> Serial ATA and Parallel ATA drivers (libata)  --->
			[ ] ATA SFF support (for legacy IDE and PATA)		//关了，老式硬盘才需要
		[*] Network device support  ---> 						//取消全部，只留一个自己用的
			[*] Ethernet driver support  --->					//选择有线驱动
				[*] Broadcom devices (NEW)
				<*> Broadcom Tigon3 support						//BCM57786的驱动是这个
			[*] Wireless LAN  ---> 								//选择无线驱动
				Atheros Wireless Cards  --->
					 [*] Atheros bluetooth coexistence support
					 <*> Atheros 802.11n wireless cards support
					 [*] Atheros ath9k PCI/PCIe bus support (NEW)
		Input device support  --->
			[ ] Touchscreens  ----								//非触摸屏电脑关闭触屏支持
			[ ] Miscellaneous devices  ----
			[ ] Joysticks/Gamepads  ----
			(1366)  Horizontal screen resolution
			(768)   Vertical screen resolution				//设置分辨率
		[*] USB support  --->
			<*> xHCI HCD (USB 3.0) support					//打开USB3.0支持
		<*> MMC/SD/SDIO card support  --->
			<*> USB SD Host Controller (USHC) support
		[ ] LED Support  ----								//关闭LED驱动
	```

- 电源管理和ACPI：

	```
	Power management and ACPI options  --->
		[*] Suspend to RAM and standby						//睡眠功能
		[*] Hibernation (aka 'suspend to disk')				//休眠功能
		[ ] Power Management Debug Support					//不需要调试电源
		[*] ACPI (Advanced Configuration and Power Interface) Support  --->
			<*> Battery										//笔记本开启电池相关支持
			<*> Smart Battery System
		CPU Frequency scaling  --->
			Default CPUFreq governor (ondemand)  --->
				(X) ondemand
			< > 'userspace' governor for userspace frequency scaling		//关闭userspace调度器
			x86 CPU frequency scaling drivers  --->
				[*] Intel P state control
	```

- 文件系统(记得开启vfat、NTFS支持，另文件系统不建议编译成模块)：

	```
	File systems --->
		<*> FUSE (Filesystem in Userspace) support			//没有这货挂载Win分区会失败的
		CD-ROM/DVD Filesystems  --->
			<*> ISO 9660 CDROM file system support
			<*> UDF file system support						//刻盘可能会用到
		DOS/FAT/NT Filesystems  --->
			<*> MSDOS fs support
			<*> VFAT (Windows-95) fs support
			<*> NTFS file system support					//NTFS文件系统支持不打开无法挂载win分区
		-*- Native language support  --->
			<*> Simplified Chinese charset (CP936, GB2312)	//fat32的原生中文支持
	```

- 可执行文件：

	```
	Executable file formats / Emulations  --->
		[ ] IA32 Emulation									//不需要32位模拟
	```

- 虚拟化：

	```
	[*] Virtualization  --->
		<*> Kernel-based Virtual Machine (KVM) support
			<*> KVM for Intel processors support			//VirtualBox会用到
	```

- 内核安全与内核调试：

	```
	Kernel hacking  --->
	Security options  --->				//除了默认必选的全关了，不是内核开发者不凑热闹
	```

## 安装内核
确认配置无误之后，执行make指令开始根据makefile进行编译。

编译内核之后复制镜像：

```
# cp arch/x86/boot/bzImage /boot/kernel-[版本号]-gentoo
```

之后安装内核模块：

```
# make modules_install
```

根据桌面环境选择默认的配置文件集：

```
# eselect profile list
[1]   default/linux/amd64/13.0
[2]   default/linux/amd64/13.0/selinux
[3]   default/linux/amd64/13.0/desktop
[4]   default/linux/amd64/13.0/desktop/gnome
[5]   default/linux/amd64/13.0/desktop/gnome/systemd
[6]   default/linux/amd64/13.0/desktop/kde
[7]   default/linux/amd64/13.0/desktop/kde/systemd
```

openRC服务下更换显示管理器，编辑`/etc/conf.d/xdm`文件，将`DISPLAYMANAGER="xdm"`改为安装的显示管理器：

```c
# rc-update add xdm default //默认登录到显示管理器
```

加入蓝牙模块自启动：

```c
# rc-update add bluetooth //没写运行级别会默认加入default运行级别
```



# emerge 包管理器
Gentoo使用`emerge`作为包管理器，常用指令：

```c
# emerge --sync //同步portage树
# emerge -e world //更换全局USE之后重新编译所有包
# emerge -u system //升级系统软件
# emerge -u world //升级整个系统
# emerge -auvDN world //完整升级系统
# emerge -pv [包名] //查看某个包的可用USE
# emerge --udpate --newuse [包名] //更新USE之后安装包刷新依赖关系
# emerge --depclean //清理无用依赖
# emerge -a //执行操作前询问
# eclean distfiles //清理包文件(请先 emerge gentoolkit)
$ qfile [文件名/路径名] //查看文件属于哪个包
```

emerge常用参数：

```
world | system， world范围更广，包含了system，这是两个包的set。
-p pretend 预览
-a ask 先予询问
-c clean 清理系统
-C unmerge 卸载，与emerge相反
--depclean 深度清理，移除与系统无关的包
-h help 帮助文件
-v verbose 详细内容
-s search 查找
-S searchdesc 从文件名和描述中查找，效率低
-u update 升级软件包
-U upgradeonly 仅仅升级，不降级软件包
-D deep 计算整个系统的依赖关系
-e emptytree 清空依赖树，重新构建某个包/系统整个依赖树
-1 oneshot 一次性安装，不将其信息加入系统目录树
-o onlydeps 只安装其依赖关系，而不安装软件本身
-t tree 显示其目录树信息
-k usepkg 使用二进制包
-K usepkgonly 只使用二进制包
-f fetchonly 仅下载安装包
--sync 从指定的rsync站点更新portage树，先前所作所有portage树更改均失效
-N newuse 使用新的USE FLAG，如有必要，需重新编译
-n noreplace 更新system，但先前安装的软件不予覆盖
```

## equery
查询系统内已安装的包的信息需要安装额外的工具`app-portage/gentoolkit`，该包含有eclean、equery等工具。

```c
$ equery list [包名] //列出对应包名的包安装了哪些版本
$ equery files [包名] //查看包里有哪些文件
$ equery belongs [文件路径] //查看文件属于哪个包
$ equery depends [包名] //查看某个包的依赖
$ equery uses [包名] //查看一个已经安装的包使用了哪些USE
```

## 包组列表
系统默认的包组有`system`和`world`，system列表为系统成员组件，不可更改(由你选择的profile决定)；
world包组成员列表记录在`/var/lib/portage/world`文件中，可自行更改，
这些包及其依赖包被保护，其余包被视为孤立包，执行清理依赖命令时孤立包会被移除。

一般手动执行安装某个包时，该包的包名会被加入`/var/lib/portage/world`文件(即主动安装的包是不会被清理的，
除非主动移除手动安装的包)。
使用`--oneshot`指令安装的包不会被加入world列表中。

## 多版本包管理(slot机制)
对于Python，JDK等多版本共存软件，使用select命令选取一个默认版本：

```
# eselect [软件名] set [软件版本]
```

例如使用Python2.7为默认版本：

```c
# eselect python set python2.7 //版本必须是在环境变量定义下可寻的二进制文件名
```

使用help参数可以查看详情：

```
$ eselect help
```

## overlay
overlay仓库类似于`Arch Linux`中的`AUR`仓库，用来提供一些官方源中未包含的软件包。

安装overlay：

```c
# emerge -av layman
# cat /var/lib/layman/make.conf >> /etc/portage/make.conf //将第三方portage添加到库中
# layman -a gentoo-zh //加入国人仓库
```

常用命令：

```c
# layman -L //获取overlay列表，并列出
# layman -a XXX //添加XXX overlay
# layman -d XXX //删除XXX overlay
# layman -s XXX //更新XXX overlay
# layman -S //更新所有 overlay
```



# 其他配置
不同于一般发行版，Gentoo有需要需要注意的特殊知识。

## 关于 Kernel Modules
内核模块被安装在`/lib/modules/``uname -r```目录中。
使用如下命令查看可用的内核模块：

```
# find /lib/modules/`uname -r` -type f -iname '*.o' -or -iname '*.ko'
```

使用默认的openRC服务管理，将查询到的内核模块名按需加入`/etc/conf.d/modules`中可以使模块开机自启动(后缀名`*.ko`可省略)。
配置文件中的内核模块不能写alisa名称，而是要写清模块文件的名字。
如果使用systemd作为服务管理，则将需要开机启动的模块写入`/etc/modprobe.d/`中的任意文件。

## 关于 flags
全局USE标记在`/etc/portage/make.conf`中。
每个软件单独设定USE标记在`/etc/portage/package.use`里。
其他标记如`PYTHON_TARGETS`，`PYTHON_SINGLE_TARGET`等也可以加入`make.conf`(全局)，
页可写入`package.use`(单个包有效)。

## 关于 Masked
包被Masked的原因很多。
因为许可证被Masked，需要将接受的许可证级别的写在`/etc/portage/package.license`里。
部分软件稳定性不达标会被Masked，如果需要安装，则将对应的包名和稳定性级别加入`/etc/portage/package.accept_keywords`里。
如果要安装很多稳定性级别不够的包，一一加入很麻烦，可以在`/etc/portage/make.conf`中使用全局关键字 `ACCEPT_KEYWORDS="~amd64"`，一般不推荐这样做，这会降低系统稳定性。

## 关于 CONFIGURATION FILES
有时包更新带来新的配置文件便会产生文件冲突，新加入的配置文件会以`.cfg00xx_[原配置文件名]`命名，可以使用：

```
# find /etc -name '*._cfg*'
```

找出这些冲突的配置文件，然后一一比较内容，并决定取舍。

## openRC
Gentoo默认使用`openRC`管理服务，常用指令：

```c
# rc-update -a [服务名] default //添加一个服务(add)
# rc-update -d [服务名] default //移除一个服务(delete)
# rc-update //列出服务树(已设置自启动的服务)
# rc-update -v //列出服务树(包括未设置自启动的服务)
# rc-status //查看用户添加启动的服务
# rc-status [运行级别] //查看某个运行级别中的服务
# rc-status -s //显示所有服务的状态
```

openRC系统的服务模块位于`/etc/conf.d`目录下，可以根据需求自行添加。

## MySQL初始化
默认情况下，安装完MySQL/MariaDB数据库并未进行初始化配置，此时服务无法启动，
需要手动进行初始化：

```c
# emerge --config dev-db/mariadb //初始化mysql配置
```

之后就可以启动msyql服务：

```
# /etc/init.d/mysql start
```

## 修改主机名
与其它systemd发行版不同，主机名配置位于`/etc/conf.d/hostname`。

## 安装JDK
默认源中似乎没有OpenJDK，但是可以安装OracleJDK，安装包需要自己从Oracle官网下载。
下载完成后，移动到`/usr/portage/distfiles`文件夹中，注意修改文件权限为`664`，文件属主和用户组都改为`portage`。
然后在安装源里的OracleJDK包。
