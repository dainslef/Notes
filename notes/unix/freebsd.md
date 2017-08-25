<!-- TOC -->

- [概述](#概述)
	- [与 *Linux* 的差异](#与-linux-的差异)
- [安装与配置](#安装与配置)
	- [在 *UEFI* 下引导 *FreeBSD*](#在-uefi-下引导-freebsd)
	- [使用 *GRUB2* 引导 *FreeBSD*](#使用-grub2-引导-freebsd)

<!-- /TOC -->



## 概述
`FreeBSD`是**开源**、**自由**的`Unix Like`操作系统。  
`FreeBSD`继承自`BSD`(`Berkeley Software Distribution`)系列，是正统的`Unix`分支，但由于法律原因，`FreeBSD`不能称为`Unix`。

相比`Linux`，`FreeBSD`更加贴近传统`Unix`的设计风格。

### 与 *Linux* 的差异
授权协议差异：

- `Linux`使用`GPLv2`许可证，许可证兼容性较差，内核二次开发需要继续开源代码，直接导致一些使用其它许可证的开源技术无法并入`Linux`内核，如`ZFS`文件系统
- `FreeBSD`使用`BSD`许可证，许可证宽松，有多家公司基于`FreeBSD`进行商业性的二次开发，如`Apple`的`macOS`、`Sony`的`Play Station 3/4`等

开发模式差异：

- `Linux`项目仅仅包含内核开发，上游工具链由不同的团队维护，同时有众多基于`Linux`内核的**发行版**
- `FreeBSD`项目是完整的操作系统，包含内核、设备驱动、工具链、文档等，关注度和商业宣传不如`Linux`，开发团队规模较小，对于新

社区规模差异：

- `Linux`商业宣传优秀，社会关注度高，开发团队庞大，对于新硬件、新技术有较好支持
- `FreeBSD`开发团队规模较小，开发进度较慢，对新硬件的支持较为缓慢



## 安装与配置
`FreeBSD`官方`FTP`站点提供了镜像下载，地址为`ftp://ftp.freebsd.org/pub/FreeBSD`。  
`ISO-IMAGES`目录下即为正式发布版本的镜像，选择匹配的`CPU`架构和版本即可。

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

### 在 *UEFI* 下引导 *FreeBSD*
`FreeBSD 10`开始引入`UEFI`启动支持，`FreeBSD 10`运行在`UEFI`模式下需要下载独立的带有`uefi`名称的镜像版本。  
以`FreeBSD 10.3`为例，对应的`amd64`刻录镜像名称为`FreeBSD-10.3-RELEASE-amd64-uefi-memstick.img`。  
从`FreeBSD 11`开始，镜像均支持`UEFI`启动，不再区分是否带有`uefi`。

引导`UEFI`模式安装的`FreeBSD`需要下载`iso`格式的镜像，解压后提取`/boot/boot1.efi`文件。  
在`ESP`分区中创建`FreeBSD`目录，将`boot1.efi`文件拷贝到其中。  
在`UEFI BIOS`中手动选取`boot1.efi`文件作为系统引导项，重启即可在`UEFI`模式下引导安装完成的`FreeBSD`系统。

### 使用 *GRUB2* 引导 *FreeBSD*
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
