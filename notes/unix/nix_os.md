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
// 查询名称中包含指定字段的软件包
# nix-env -qa '.*软件包名称.*'

// 安装软件包
# nix-env -i [软件包名称]
# nix-env --install [软件包名称]
# nix-env -iA [channel名称.包名称] //使用完整名称安装软件包，可避免歧义
# nix-env -iv [软件包名称] //安装软件包时输出详细日志，便于发现错误

// 移除软件包
# nix-env -e [软件包名称]
# nix-env --uninstall [软件包名称]

// 更新所有软件包
# nix-env -u
// 更新指定软件包
# nix-env -u '软件包'
// 查看可升级的软件包
# nix-env -u --dry-run
```

使用`nix-env -e`删除的软件包并为真正的删除软件包本体，而是移除了到该软件包的软链接。
使用`nix-store --gc`来真正清理软件包缓存：

```c
// 清理软件包时会计算当前系统的依赖关系，将不被依赖的软件包全部清理
# nix-store --gc

// 使用--print-dead参数时仅计算并打印会被清理的依赖，不真正执行清理操作
# nix-store --gc --print-dead
```

## Nix Channel
NixOS中的`Channel`概念上类似与常规发行版的`Mirror`(软件源)。
NixOS的channel按照维度分类：

- 按照版本分类：**unstable**和**指定版本**
- 按照包类别分类：**nixos**和**nixpkgs**

```sh
nixos https://nixos.org/channels/nixos-unstable
nixpkgs https://nixos.org/channels/nixpkgs-unstable
```

使用`nix-channel`指令管理channel：

```c
$ nix-channel --list //显示当前已配置的channel
$ nix-channel --add url [name] //添加指定channel
$ nix-channel --remove name //移除指定channel
```

在添加channel时若不指定名称，则按找包类别使用默认名称，例如`nixos-unstable`的channel名称为`nixos`。
channel名称是**唯一**的，添加名称相同的channel时，后添加的会替换先前的channel。

更新软件包前应先更新channel：

```
# nixos-channel --update
# nix-env -u
```

## Unfree
NixOS软件源中收录了部分Unfree的软件包，如`Chrome`、`Visual Studio Code`等，
此类软件包因为许可证问题，默认不可被安装。

临时允许unfree软件安装，安装时需要将`allowUnfree`属性置为true：

```
# nix-env -iA nixos.vscode --arg config '{ allowUnfree = true; }'
```

全局允许unfree软件安装，需要在configuration.nix配置中设定`nixpkgs.config.allowUnfree`属性：

```sh
nixpkgs.config.allowUnfree = true;
```

configuration.nix配置中的unfree配置能允许在`environment.systemPackages`配置项中加入unfree软件包，如：

```sh
environment.systemPackages = with pkgs; [ vscode ];
```

Nix包管理器对于每个用户拥有独立的配置，全局的unfree配置并不会对具体的某个用户生效，
要使某个用户能够使用`nix-env -i`安装unfree软件包，则需要编辑用户的Nix配置`~/.config/nixpkgs/config.nix`，
在该配置文件中加入：

```sh
{
  allowUnfree = true;
}
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
| :- | :- | :- | :- | :- |
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

## 配置管理
在NixOS中，Nix配置接管了系统内所有软件包的配置，同时，以常规方式修改软件包自身配置的方式对于系统级软件包无效。
以`sudo`为例，直接修改`/etc/sudoers`配置并不能正常赋予某个用户管理员权限。

重新应用配置：

```c
# nixos-rebuild switch //重新生成配置，并立即切换到新配置
# nixos-rebuild switch --upgrade //生成配置同时更新系统
```

列出所有的配置：

```
# nix-env --list-generations
```

执行清理操作：

```c
// 删除指定编号的配置
# nix-env --delete-generations [配置编号...]

// 清理所有非激活配置和过时软件包
# nix-collect-garbage -d
```

## 系统软件包与服务配置
在NixOS中，可将常用的软件包配置为系统软件包，在configuration.nix配置中设定`environment.systemPackages`配置项：

```sh
environment.systemPackages = with pkgs; [
  git neofetch stack rustup ... # 添加软件包名称
]
```

设定的软件包会在`nixos-rebuild`时做为系统软件包自动安装，而不需要手动安装。

对于部分影响系统配置的应用和服务，NixOS中提供了独立的配置项，
在configuration.nix配置中`programs`、`services`配置段：

```sh
programs = {
  fish.enable = true;
  chromium.enable = true;
  npm.enable = true;
  java.enable = true;
  wireshark.enable = true;
  vim.defaultEditor = true;
  ...
};

services = {

  # 桌面环境配置，以KDE5为例
  xserver = {
    enable = true;
    desktopManager.plasma5.enable = true;
    displayManager.sddm.enable = true;
  };

  # 数据库配置，以MySQL为例
  mysql = {
    enable = true;
    package = pkgs.mariadb;
  };

  ...
};
```

NixOS使用`systemd`管理服务的状态，在services配置段中启用的服务默认会开机自启动，且无法修改自启状态。
启用与禁用services配置段中设定的服务，需要设定`systemd.services`配置段：

```sh
systemd.services.<name>.enable = true/false;
...

# 以MySQL服务为例，禁用服务自启
systemd.services.mysql.enable = false;
```

## 用户配置
在`users.users`配置项中设定用户相关配置。

```sh
users.users.[用户名] = {
  isNormalUser = true; # 设定是否为普通用户，普通用户才拥有独立的家目录和用户组
  home = "家目录"; # 默认家目录为"/home/用户名"，有特殊需求可使用此配置指定家目录
  description = "用户简介";
  extraGroups = ["wheel" "networkmanager"]; # 为用户添加额外的用户组
};
```

要使用户能使用`sudo`，需要将用户加入`wheel`(管理员)用户组中。

## Shell配置
默认配置下使用`bash`做为普通用户的默认shell，要使用其它shell应在configuration.nix配置中开启需要使用的shell，
常见的shell如下：

```sh
programs.zsh.enable = true; # ZSH
programs.fish.enable = true; # fish
```

启用了需要的shell后，修改configuration.nix中的**用户配置**。
以fish为例：

```sh
programs.fish.enable = true;

users.users.[用户名] = {
  ...
  shell = pkgs.fish;
};
```

## 字体配置
configuration.nix配置中常用的字体相关配置：

```sh
fonts.enableFontDir = true; # 为所有字体在"/run/current-system/sw/share/X11-fonts"路径下创建软连接
fonts.fonts = with pkgs; [ ... ]; # 配置字体包
fonts.fontconfig.defaultFonts = {
  monospace = [ "Xxx" ]; # 等宽字体
  sansSerif = [ "Xxx" ]; # 无衬线字体
  serif = [ "Xxx" ]; # 衬线字体
};
```

用户自定义字体路径`~/.fonts`已被上游废弃，在NixOS中，将个人字体放置在此路径下不会被加入字体列表。
取代该路径的用户字体路径是`$XDG_DATA_HOME/fonts`，实际对应路径为`~/.local/share/fonts`。

## 输入法配置
在configuration.nix配置的`i18n.inputMethod`配置项中设定使用的输入法：

```sh
i18n.inputMethod = {
  enabled = "fcitx"; # 使用fcitx输入法
  fcitx.engines = with pkgs.fcitx-engines; [ libpinyin anthy ];
};
```

在Gnome3桌面环境下，推荐使用`iBus`输入法：

```sh
i18n.inputMethod = {
  enabled = "ibus"; # 使用ibus输入法
  ibus.engines = with pkgs.ibus-engines; [ libpinyin anthy ];
};
```
