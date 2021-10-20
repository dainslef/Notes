<!-- TOC -->

- [概述](#概述)
	- [与 Linux 的比较](#与-linux-的比较)
- [安装与配置](#安装与配置)
	- [UEFI引导](#uefi引导)
	- [GRUB2引导](#grub2引导)
- [无线网络配置](#无线网络配置)
- [服务管理](#服务管理)
- [包管理](#包管理)
	- [pkg](#pkg)
	- [Ports](#ports)
	- [系统版本升级](#系统版本升级)
- [常用工具指令](#常用工具指令)
	- [PCI設備](#pci設備)

<!-- /TOC -->



# 概述
`FreeBSD`是**开源**、**自由**的`Unix Like`操作系统。
FreeBSD继承自`BSD`(`Berkeley Software Distribution`)系列，是正统的Unix分支，
但由于法律原因，FreeBSD不能称为Unix。

相比Linux，FreeBSD更加贴近传统Unix的设计理念。

## 与 Linux 的比较
授权协议差异：

- Linux使用`GPLv2`许可证，许可证兼容性较差，内核二次开发需要继续开源代码，直接导致一些使用其它许可证的开源技术无法并入Linux内核，如`ZFS`文件系统
- FreeBSD使用`BSD`许可证，许可证宽松，有多家公司基于FreeBSD进行商业性的二次开发，如`Apple`的`macOS`、`Sony`的`Play Station 3/4`等

开发模式差异：

- Linux项目仅仅包含内核开发，开发迭代较快，上游工具链由不同的团队维护，同时有众多基于Linux内核的**发行版**
- FreeBSD项目是完整的操作系统，包含内核、设备驱动、工具链、文档等，整个系统均由同一团队维护，因而具有较高的一致性，但开发迭代较慢，衍生发行版也较少

社区规模差异：

- Linux商业宣传优秀，社会关注度高，开发团队庞大，对于新硬件、新技术有较好支持
- FreeBSD关注度和商业宣传不如Linux，开发团队规模较小，开发进度较慢，对新硬件的支持较为缓慢



# 安装与配置
[FreeBSD官网](http://ftp.freebsd.org/pub/FreeBSD)提供了镜像下载。
`ISO-IMAGES`目录下即为正式发布版本的镜像，选择匹配的CPU架构和版本即可。

镜像命名规则如下：

```
FreeBSD-[版本号]-RELEASE-[CPU架构]-[镜像类型].img/iso
```

镜像类型分为以下几类：

- `bootonly` 后缀名为`iso`，仅供启动引导使用
- `disc1` 后缀名为`iso`，基本镜像，包含基本软件包
- `dvd1` 后缀名为`iso`，包含大量常用软件包
- `memstick` 后缀名`img`，刻录使用镜像，包含基本软件包
- `memstick-mini` 后缀名`img`，刻录使用镜像，包含核心软件包，最小化安装使用

后缀名`iso`的镜像用于虚拟机启动，后缀名`img`的镜像用于刻盘安装。
刻录镜像使用`dd`指令，并需要添加部分参数，以`amd64`架构的`memstick-mini`镜像为例，刻录指令如下：

```
# dd if='FreeBSD-[版本]-RELEASE-amd64-memstick-mini.img' of='/dev/[磁盘id]' bs=1M conv=sync
```

## UEFI引导
`FreeBSD 10`开始引入`UEFI`启动支持，`FreeBSD 10`运行在`UEFI`模式下需要下载独立的带有`uefi`名称的镜像版本。
以`FreeBSD 10.3`为例，对应的`amd64`刻录镜像名称为`FreeBSD-10.3-RELEASE-amd64-uefi-memstick.img`。
从`FreeBSD 11`开始，镜像均支持`UEFI`启动，不再区分是否带有`uefi`。

引导`UEFI`模式安装的`FreeBSD`需要下载`iso`格式的镜像，解压后提取`/boot/boot1.efi`文件。
在`ESP`分区中创建`FreeBSD`目录，将`boot1.efi`文件拷贝到其中。
在`UEFI BIOS`中手动选取`boot1.efi`文件作为系统引导项，重启即可在`UEFI`模式下引导安装完成的`FreeBSD`系统。

## GRUB2引导
在`grub.conf`文件中为`FreeBSD`创建启动项，指定`FreeBSD`启动文件`boot1.efi`的位置，配置如下：

```
menuentry 'FreeBSD' {
    insmod part_gpt
    insmod fat
    set root='hd0,gpt1'
    chainloader /EFI/FreeBSD/boot1.efi # FreeBSD efi文件的实际路径
}
```

使用`boot1.efi`文件引导`FreeBSD`相比直接通过`GRUB2`启动**BSD内核**的方式更加简单，无需复杂的引导配置。



# 无线网络配置
命令行环境下配置无线网络推荐使用`wpa_supplicant`工具。
需要自行在`/etc`路径下创建`wpa_supplicant.conf`。
配置模版如下所示：

```shell
network={
	# scan_ssid=1 # 當連接隱藏的無線熱點時需要額外添加該參數
	ssid="无线网ssid"
	psk="密码"
}
```

無限設備需要寫入`/etc/rc.conf`中，配置規則：

```html
wlans_無線設備名稱="無線網絡接口名稱" <!-- FreeBSD中無線網絡接口名稱通常使用 wlan0 -->
ifconfig_無線網絡接口名稱="WPA DHCP"
```

無線設備名稱使用sysctl指令查詢，示例：

```
$ sysctl net.wlan.devices
sysctl net.wlan.devices: iwm0
```

可知無線設備為`iwm0`，則對應無線配置為：

```
wlans_iwm0="wlan0"
ifconfig_wlan0="WPA DHCP"
```

之后启动网络服务：

```
# service netif start
```

连接未加密的无线网络，不需要使用`wpa_supplicant.conf`，直接在`/etc/rc.conf`中添加：

```
wlans_iwm0="wlan0"
ifconfig_wlan0="ssid [无线网ssid] DHCP"
```



# 服务管理
FreeBSD采用传统的`BSD`风格的`init`系统，服务项在`/etc/rc.d`目录下。
可以使用service命令来管理服务：

```
# service [服务名称] [start | stop | status]
```

开机自启动的服务，以及一些系统配置存放在`/etc/rc.conf`文件中。
例如，需要开机自启动`ssh`服务则可以将`sshd_enable="YES"`加入`rc.conf`文件中。

常见服务配置：

```
hostname="MacBook" //主机名称
ifconfig_em0="DHCP" //网络DHCP
ifconfig_em0_ipv6="inet6 accept_rtadv" //ipv6
sshd_enable="YES" //ssh服务
ntpd_enable="YES" //时间同步服务
powerd_enable="YES" //电源管理服务
dumpdev="AUTO" //内核错误转储服务
```



# 包管理
FreeBSD同时提供了基于源码编译软件包的`Ports`系统和基于预编译二进制包的`pkg`包管理。

## pkg
`FreeBSD 10`之后引入了新的`pkg`工具用于管理软件包，常用指令类似与`yum/apt/dnf`：

```html
# pkg install 软件包名称
# pkg search 软件包名称
# pkg remove 软件包名称
# pkg autoremove 软件包名称
# pkg info <!-- 查询所有已安装的软件包 -->
# pkg info 软件包名称 <!-- 查询某个软件包的具体信息(包括软件包的文件组成，依赖关系，来源等) -->
```

## Ports
`Ports`系统提供了官方源内所有软件包的**源码树**，编译安装前能够定制编译参数，控制依赖项。
Ports源码树位于`/usr/ports`目录之，首次使用前需要初始化Ports树，执行：

```
# portsnap fetch extract
```

之后更新Ports树执行：

```
# portsnap update
```

编译Ports树下某个软件包的源码只需进入对应的源码目录中，执行以下步骤：

1. `make config` 进入交互式界面，配置编译依赖
1. `make` 执行编译操作
1. `make install` 编译完成后执行安装操作
1. `make clean` 安装完成后清理编译生成的临时文件

使用源码编译的软件包安装后同样受到`pkg`包管理器的管理。

## 系统版本升级
FreeBSD并非**滚动发行版**，系统有明确的版本划分，升级系统版本需要使用升级工具`freebsd-update`。
升级到指定版本，执行指令：

```
# freebsd-update -r [版本号-发布状态] upgrade
```

以`FreeBSD 10.1`正式版，执行指令：

```
# freebsd-update -r 10.1-RELEASE upgrade
```

之后系统会开始下载升级所需要的补丁，下载完成之后，执行更新指令：

```
# /usr/sbin/freebsd-update install
```



# 常用工具指令
FreeBSD下大量工具指令與Linux中不同。

## PCI設備
Linux下使用`lspci`查看PCI設備，FreeBSD中則使用`pciconf`：

```html
$ pciconf -h
usage: pciconf -l [-bcv]
       pciconf -a selector
       pciconf -r [-b | -h] selector addr[:addr2]
       pciconf -w [-b | -h] selector addr value

$ pciconf -l
hostb0@pci0:0:0:0:  class=0x060000 card=0x00000000 chip=0x12378086 rev=0x02 hdr=0x00
isab0@pci0:0:1:0:  class=0x060100 card=0x00000000 chip=0x70008086 rev=0x00 hdr=0x00
atapci0@pci0:0:1:1:  class=0x01018a card=0x00000000 chip=0x71118086 rev=0x01 hdr=0x00
vgapci0@pci0:0:2:0:  class=0x030000 card=0x00000000 chip=0xbeef80ee rev=0x00 hdr=0x00
em0@pci0:0:3:0:   class=0x020000 card=0x001e8086 chip=0x100e8086 rev=0x02 hdr=0x00
none0@pci0:0:4:0:  class=0x088000 card=0x00000000 chip=0xcafe80ee rev=0x00 hdr=0x00
none1@pci0:0:7:0:  class=0x068000 card=0x00000000 chip=0x71138086 rev=0x08 hdr=0x00
atapci1@pci0:0:13:0:  class=0x010601 card=0x00000000 chip=0x28298086 rev=0x02 hdr=0x00

$ pciconf -lv <!-- 查看完整信息 -->
hostb0@pci0:0:0:0: class=0x060000 card=0x00000000 chip=0x12378086 rev=0x02 hdr=0x00
    vendor     = 'Intel Corporation'
    device     = '82440/1FX 440FX (Natoma) System Controller'
    class      = bridge
    subclass   = HOST-PCI
isab0@pci0:0:1:0: class=0x060100 card=0x00000000 chip=0x70008086 rev=0x00 hdr=0x00
    vendor     = 'Intel Corporation'
    device     = 'PIIX3 PCI-to-ISA Bridge (Triton II) (82371SB)'
    class      = bridge
    subclass   = PCI-ISA
atapci0@pci0:0:1:1: class=0x01018a card=0x00000000 chip=0x71118086 rev=0x01 hdr=0x00
    vendor     = 'Intel Corporation'
    device     = 'PIIX4/4E/4M IDE Controller (82371AB/EB/MB)'
    class      = mass storage
    subclass   = ATA
...
```
