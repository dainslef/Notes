<!-- TOC -->

- [ArchLinux安裝](#archlinux安裝)
	- [安裝鏡像](#安裝鏡像)
	- [修改系統預置源](#修改系統預置源)
	- [配置ArchLinuxCN源](#配置archlinuxcn源)
	- [系統分區](#系統分區)
	- [安裝基礎軟件包](#安裝基礎軟件包)
	- [配置安裝環境](#配置安裝環境)
- [桌面環境配置](#桌面環境配置)
	- [配置顯卡驅動](#配置顯卡驅動)
	- [DPI縮放](#dpi縮放)
	- [字體配置](#字體配置)
- [包管理](#包管理)
	- [pacman](#pacman)
		- [pacman操作](#pacman操作)
		- [pacman配置](#pacman配置)
		- [pacman-contrib](#pacman-contrib)

<!-- /TOC -->



# ArchLinux安裝
[Arch Linux](https://archlinux.org/)是輕量級、滾動更新的發行版。

## 安裝鏡像
Arch Linux官方僅提供純命令行鏡像，安裝較爲不便，
[Arch Linux GUI](https://archlinuxgui.in/)項目提供了GUI鏡像，
使用GUI鏡像安裝更加簡便（避免命令行下繁雜的無線網絡配置）。

## 修改系統預置源
安裝鏡像中預置的系統源在牆國可能無法訪問或速度過慢，
編輯`/etc/pacman.d/mirrorlist`，在文件首部添加牆內源：

```html
<!-- 清華源 -->
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinux/$repo/os/$arch
<!-- 中科大源 -->
Server = https://mirrors.ustc.edu.cn/archlinux/$repo/os/$arch
```

## 配置ArchLinuxCN源
`ArchLinuxCN`源是對官方源的補充，打包一些牆國常用但又未包含在官方源的中軟件。
編輯`/etc/pacman.conf`，添加倉庫配置：

```
[archlinuxcn]
SigLevel = Optional TrustAll
Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch
```

## 系統分區
在使用`UEFI + GPT`的現代計算機中，安裝Linux至少需要以下分區：

| 分區 | 文件系統 | 說明 |
| :- | :- | :- |
| / | btrfs/ext4 | 根分區 |
| /boot | vfat | ESP分區 |
| SWAP | swap | 交換區 |

若機器中已安裝了Windows，則通常ESP分區已創建。
早期ESP分區在Linux中推薦的掛載點位置為`/boot/efi`，
現在推薦直接使用`/boot`，便於使用systemd-boot生成引導項時引導內核。

分區操作完成後，創建文件系統：

```
# mkfs.btrfs /dev/xxx_root
# mkswap /dev/xxx_swap
```

將根分區掛載至安裝鏡像環境的/mnt路徑下，ESP分區掛載至/mnt/boot下：

```
# mount /dev/xxx_root /mnt
# mount /dev/xxx_esp /mnt/boot
```

掛載分區後，為新系統生成分區表：

```
# genfstab > /mnt/etc/fstab
```

## 安裝基礎軟件包
之後為根路徑安裝基本的軟件包，使用pacstrap工具，在安裝軟件包時給定根路徑：

```html
<!-- 安裝基本的軟件包，以及內核、驅動、編輯器等 -->
# pacstrap -i /mnt base vim linux-zen linux-firwmare
```

早期的base為軟件包組（package group），自[2019-10-6](https://archlinux.org/news/base-group-replaced-by-mandatory-base-package-manual-intervention-required/)開始，
base變為元包（meta package），base元中依賴了除內核外所有必備的操作系統組件。

## 配置安裝環境
完成基礎環境安裝後，此時系統已可進入；
使用`arch-chroot`工具切換到新的系統環境中：

```
# arch-chroot /mnt
```

進入新環境後，設置常用的系統參數：

```html
<!-- 設置時間相關參數 -->
# timedatectl set-timezone ... <!-- 設置時區 -->
# timedatectl set-ntp 1 <!-- 開啟NTP -->
# timedatectl set-local-rtc 1 <!-- 設置機器硬件時鐘為本地時鐘，當與Windows組建雙系統時需要該配置 -->

# hostnamectl set-hostname ... <!-- 設置主機名稱 -->
# localectl set-locale en_US.UTF-8 <!-- 設置語言編碼 -->
```

之後配置用戶密碼，以及創建普通用戶：

```
# passwd
# useradd -m xxx
$ passwd xxx
```

最後安裝引導器，對於支持systemd的現代發行版，推薦直接使用systemd-boot，而非傳統的GRUB2。
使用systemd-boot引導系統，不再需要傳統GRUB的efibootmgr以及os-prober等組件。
安裝引導器：

```
# bootctl install
```

引導器成功安裝後，在`/boot/loader/entries`路徑下創建引導配置archlinux.conf：

```
title Arch Linux
linux /vmlinuz-linux-zen
initrd /initramfs-linux-zen.img
options root=/dev/xxx_root
```



# 桌面環境配置
ArchLinux默認並未集成任何桌面環境，可根據自身需求安裝需要的桌面環境。

## 配置顯卡驅動
Intel核芯顯卡早年使用Intel官方提供的開源驅動`xf86-video-intel`，
但該驅動已多年未有實質性更新，現在Intel核顯支持已直接集成到Xorg中，已不需要單獨安裝驅動。

AMD核芯顯卡驅動分爲兩類，較老的CPU使用`xf86-video-ati`，
Zen系列之後較新的CPU使用`xf86-video-amdgpu`。

## DPI縮放
通過修改全局配置`/etc/X11/Xreources`或用戶配置`~/.Xresources`設置UI縮放比例。
默認DPI爲96，按照需要縮放的比例設置DPI值，如120（25%），144（50%）：

```
Xft.dpi: 120
```

通過查看`/etc/lightdm/Xsession`可知，加載Xresources邏輯如下：

```sh
# Load resources
for file in "/etc/X11/Xresources" "$HOME/.Xresources"; do
    if [ -f "$file" ]; then
        echo "Loading resource: $file"
        xrdb -merge "$file"
    fi
done
```

因此Xresources需要xrdb工具才能生效：

```
# pacman -S xorg-xrdb
```

Display Manager的縮放配置需要單獨設定，以lightdm-gtk-greeter爲例，
修改對應配置`/etc/lightdm/lightdm-gtk-greeter.conf`：

```
[greeter]
...
xft-dpi=120
...
```

## 字體配置
當下較為完善的字體是Google開發的Noto系列字體：

```html
# pacman -S noto-fonts-cjk <!-- 東亞語言安裝CJK包，包含日韓港臺語字體 -->
# pacman -S noto-fonts-emoji <!-- Emoji符號 -->
```

等寬字體推薦使用微軟的`otf-cascadia-code`，內置了Powerline和連體字符的支持
（使用`Cascadia Code PL`字形）：

```
# pacman -S otf-cascadia-code
```

僅安裝上述字體還會缺少部分Unicode符號（如AwesomeWM電池插件充滿時的閃電符號），
補全此類特殊字符可安裝DejaVu字體：

```
# pacman -S ttf-dejavu
```



# 包管理
ArchLinux的包管理主要由預編譯包管理器`pacman`以及源碼構建系統`abs`構成。

## pacman
[`pacman`](https://wiki.archlinux.org/title/pacman)是ArchLinux的官方包管理器。

相比傳統包管理器，pacman設計較爲簡單，僅管理預編譯包，速度更快；
pacman同時包含包管理器前端和後端，相當於`apt + dpkg`或`yum/dnf/zypper + rpm`的組合。

### pacman操作
軟件包搜索、安裝、刪除：

```html
$ pacman -Ss 軟件包名稱 <!-- 搜索軟件包 -->
# pacman -S 軟件包名稱 <!-- 安裝軟件包 -->

<!-- 移除軟件包 -->
# pacman -R 軟件包名稱 <!-- 移除指定軟件包，默認移除操作會保留軟件包配置 -->
# pacman -Rn 軟件包名稱 <!-- 移除指定軟件包，不保存配置 -->
# pacman -Rs 軟件包名稱 <!-- 遞歸刪除依賴 -->
# pacman -Rnsc 軟件包名稱 <!-- 移除軟件包及其依賴 -->
```

查看和管理軟件包安裝原因：

```html
<!-- 查看手動安裝的軟件包 -->
$ pacman -Qe
$ pacman -Qeq <!-- 僅輸出軟件包，忽略版本號信息 -->

<!-- 列出可被移除的軟件包（不被其它軟件包依賴，且自身作為依賴安裝的軟件包） -->
$ pacman -Qdt
$ pacman -Qdtt <!-- 輸出包括僅被可選依賴(Optional Deps)的軟件包 -->
```

### pacman配置
pacman配置文件為`/etc/pacman.conf`，使用ini配置語法，結構較為簡單。

核心功能特性位於`[options]`區段中：

```ini
...
[options]
...
Color # 彩色輸出
VerbosePkgLists # 軟件包變更時列出變化詳情
ILoveCandy # 吃豆人彩蛋
...
```

軟件倉庫相關配置（以牆國ArchLinuxCN源為例）：

```ini
...
[archlinuxcn]
SigLevel = Optional TrustAll # 第三方倉庫跳過證書認證
Server = https://repo.archlinuxcn.org/$arch
...
```

### pacman-contrib
pacman的一些社區提供的輔助脚本被單獨拆分到`pacman-contrib`包中，
其中包含`pactree`等實用工具。

pactree可用於遞歸展示指定軟件包的依賴樹：

```html
<!-- 查看軟件包的正向依賴 -->
$ pactree 軟件包

<!-- 查看軟件包的反向依賴 -->
$ pactree -r 軟件包
```
