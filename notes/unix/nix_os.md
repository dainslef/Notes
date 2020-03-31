<!-- TOC -->

- [Nix package manager](#nix-package-manager)
	- [多版本管理](#多版本管理)
	- [基本指令](#基本指令)
	- [Nix Channel](#nix-channel)
	- [Unfree](#unfree)
- [NixOS](#nixos)
	- [安裝](#安裝)
	- [配置管理](#配置管理)
		- [構建與版本升級](#構建與版本升級)
		- [Binary Cache](#binary-cache)
	- [系統軟件包與服務配置](#系統軟件包與服務配置)
	- [用戶配置](#用戶配置)
	- [Shell配置](#shell配置)
	- [字體配置](#字體配置)
	- [輸入法配置](#輸入法配置)
	- [桌面配置](#桌面配置)
		- [Gnome桌面環境可選軟件包配置](#gnome桌面環境可選軟件包配置)
- [問題紀錄](#問題紀錄)
	- [Failed to start Network Time Synchronization.](#failed-to-start-network-time-synchronization)

<!-- /TOC -->



# Nix package manager
`Nix package manager`是純函數式(purely functional)的包管理器，
Nix像純函數式語言(如Haskell)處理值一樣對待軟件包：通過無副作用(no side-effects)的純函數來構建，在構建完成後就不再改變。

與傳統的軟件包管理器設計不同，Nix將軟件包存儲在`Nix Store`中(通常是`/nix/store`路徑下)，
每個軟件包存儲在**獨立**的子目錄中,軟件包路徑的命名規則爲`[軟件包id]-[軟件包名]-[版本]`，路徑示例：

```
/nix/store/b6gvzjyb2pg0kjfwrjmg1vfhh54ad73z-firefox-33.1/
```

## 多版本管理
Nix包管理器支持同時管理、安裝一個軟件包的多個版本，
保證了不同應用在依賴同一個軟件包的不同版本時不會造成`DLL hell`(動態庫依賴地獄)。
不同版本的軟件包安裝在Nix Store中的不同路徑下，各自隔離，不會相互影響。

## 基本指令
查詢、安裝、移除、更新軟件包：

```c
// 查詢軟件包
# nix-env -q [軟件包名稱]
# nix-env -qa
// 查詢名稱中包含指定字段的軟件包
# nix-env -qa '.*軟件包名稱.*'

// 安裝軟件包
# nix-env -i [軟件包名稱]
# nix-env --install [軟件包名稱]
# nix-env -iA [channel名稱.包名稱] //使用完整名稱安裝軟件包，可避免歧義
# nix-env -iv [軟件包名稱] //安裝軟件包時輸出詳細日誌，便於發現錯誤

// 移除軟件包
# nix-env -e [軟件包名稱]
# nix-env --uninstall [軟件包名稱]

// 更新所有軟件包
# nix-env -u
// 更新指定軟件包
# nix-env -u '軟件包'
// 查看可升級的軟件包
# nix-env -u --dry-run
```

使用`nix-env -e`刪除的軟件包併爲真正的刪除軟件包本體，而是移除了到該軟件包的軟鏈接。
使用`nix-store --gc`來真正清理軟件包緩存：

```c
// 清理軟件包時會計算當前系統的依賴關係，將不被依賴的軟件包全部清理
# nix-store --gc

// 使用--print-dead參數時僅計算並打印會被清理的依賴，不真正執行清理操作
# nix-store --gc --print-dead
```

## Nix Channel
NixOS中的`Channel`概念上類似與常規發行版的`Mirror`(軟件源)。
NixOS的channel按照維度分類：

- 按照版本分類：**unstable**和**指定版本**
- 按照包類別分類：**nixos**和**nixpkgs**

```sh
nixos https://nixos.org/channels/nixos-unstable
nixpkgs https://nixos.org/channels/nixpkgs-unstable
```

使用`nix-channel`指令管理channel：

```c
$ nix-channel --list //顯示當前已配置的channel
$ nix-channel --add [url] [name] //添加指定channel
$ nix-channel --remove [name] //移除指定channel
```

在添加channel時若不指定名稱，則按找包類別使用默認名稱，例如`nixos-unstable`的channel名稱爲`nixos`。
channel名稱是**唯一**的，添加名稱相同的channel時，後添加的會替換先前的channel。

更新軟件包前應先更新channel：

```
# nixos-channel --update
# nix-env -u
```

## Unfree
NixOS軟件源中收錄了部分Unfree的軟件包，如`Chrome`、`Visual Studio Code`等，
此類軟件包因爲許可證問題，默認不可被安裝。

臨時允許unfree軟件安裝，安裝時需要將`allowUnfree`屬性置爲true：

```
# nix-env -iA nixos.vscode --arg config '{ allowUnfree = true; }'
```

全局允許unfree軟件安裝，需要在configuration.nix配置中設定`nixpkgs.config.allowUnfree`屬性：

```sh
nixpkgs.config.allowUnfree = true;
```

configuration.nix配置中的unfree配置能允許在`environment.systemPackages`配置項中加入unfree軟件包，如：

```sh
environment.systemPackages = with pkgs; [ vscode ];
```

Nix包管理器對於每個用戶擁有獨立的配置，全局的unfree配置並不會對具體的某個用戶生效，
要使某個用戶能夠使用`nix-env -i`安裝unfree軟件包，則需要編輯用戶的Nix配置`~/.config/nixpkgs/config.nix`，
在該配置文件中加入：

```sh
{
  allowUnfree = true;
}
```



# NixOS
`NixOS`是基於`Nix package manager`的Linux發行版，提供了統一的包管理與配置管理。

## 安裝
[NixOS官網](https://nixos.org/nixos/download.html)提供了鏡像下載，官方提供的鏡像支持`x86/x64`平臺。
鏡像包括帶有KDE桌面的LiveCD版(`Graphical live CD`)和無GUI環境的精簡版(`Minimal installation CD`)，

以`Minimal installation CD`爲例，下載刻錄鏡像後啓動進入安裝環境。
首先對磁盤進行分區，安裝鏡像中提供了`fdisk`、`gparted`等常用分區工具，分區操作與其它發行版安裝流程相同。
對於舊式BIOS的機器推薦使用DOS分區表搭配MBR引導，對於支持UEFI的機器推薦使用GPT分區表搭配UEFI啓動。

通常最精簡的UEFI安裝包括三個分區，存放引導器的啓動分區`ESP`、交換區`SWAP`、主分區。
以fdisk工具爲例，三個分區的分區類型(partiton table)和分區路徑配置如下：

| 分區路徑 | 分區類型(類型編號) | 分區作用 | 推薦大小 | 文件系統 |
| :- | :- | :- | :- | :- |
| /dev/sda1 | EFI System (1) | 存放引導器 | 200MB | FAT32(vfat) |
| /dev/sda2 | Linux swap (19) | 虛擬內存 | 1～2倍內存大小 | / |
| /dev/sda3 | Linux filesystem (20) | 主要分區 | 20GB+ | EXT4/XFS/BTRFS |

分區完成後在對應分區創建文件系統：

```c
# mkfs.vfat /dev/sda1
# mkswap /dev/sda2
# mkfs.ext4 /dev/sda3
```

掛載分區到安裝環境的`/mnt`目錄下：

```c
# mount /dev/sda3 /mnt
# mkdir -p /mnt/boot
# mount /dev/sda1 /mnt/boot
# swapon /dev/sda2
```

之後開始生成Nix安裝配置：

```c
# nixos-generate-config --root /mnt
```

編輯生成的Nix配置`/mnt/etc/nixos/configuration.nix`，多數配置使用默認值即可。
針對UEFI啓動，需要確認以下選項是否開啓：

```sh
boot.loader.efi.efiSysMountPoint = "/boot/efi" # 設定ESP分區掛載位置
boot.loader.grub.device = "nodev" # 使用 UEFI + GPT 的設備無需指定grub引導器位置，MBR需要指定(如 /dev/sda 等)

boot.loader.systemd-boot.enable = true # 啓動 systemd 的啓動支持
boot.loader.efi.canTouchEfiVariables = true # 允許安裝進程修改EFI啓動參數
```

Nix配置修改完成後執行安裝操作：

```c
# nixos-install
```

執行指令後安裝器會以給定的Nix配置執行系統安裝流程：安裝系統文件、配置引導器、配置賬戶信息等。

## 配置管理
在NixOS中，系統核心配置`/etc/nixos/configuration.nix`接管了系統內所有服務以及軟件包的配置，
以常規方式修改軟件包自身配置的方式對於系統級軟件包**無效**。
以`sudo`爲例，直接修改`/etc/sudoers`配置並不能正常賦予某個用戶管理員權限。

重新構建系統配置：

```c
# nixos-rebuild switch // 重新構建配置，並立即切換到新配置
# nixos-rebuild switch --upgrade // 構建配置同時更新系統
```

每次rebuild生成的配置會以啟動項的方式顯示在GRUB菜單中，想要恢復之前配置環境僅需重啓進入GRUB進入對應菜單即可。

列出所有的配置：

```
# nix-env --list-generations
```

執行清理操作：

```c
// 刪除指定編號的配置
# nix-env --delete-generations [配置編號...]

// 清理所有非激活配置和過時軟件包
# nix-collect-garbage -d
```

### 構建與版本升級
執行`nixos-rebuild switch --upgrade`指令重構配置並執行升級操作時，
系統會按照當前nix-channel中指定的nixos源進行升級，該源也可以由configuration.nix中的配置來指定：

```
system.autoUpgrade.channel = https://mirrors.tuna.tsinghua.edu.cn/nix-channels/nixos-unstable;
```

### Binary Cache
Nix會在構建軟件包時會使用名為`Binary Cache`的優化機制，即構建目標時優先從指定軟件源中下載**預編譯**版本，
而非直接從源碼中進行編譯。

默認的Binary Cache地址為`https://cache.nixos.org/`，身在牆國該地址無法正常訪問，
Nix會在該步驟上會浪費大量時間(直到訪問超時)，可在執行構建時禁用Binary Cache機制：

```
# nixos-rebuild switch --option use-binary-caches false
```

清華大學提供了牆內可用的Binary Cache源，在執行構建時可顯式指定Binary Cache源為該地址：

```
# nixos-rebuild switch --option binary-caches https://mirrors.tuna.tsinghua.edu.cn/nix-channels/store
```

亦可在configuration.nix中顯式指定Binary Cache源使用清華鏡像源：

```nix
nix.binaryCaches = ["https://mirrors.tuna.tsinghua.edu.cn/nix-channels/store"];
```

需要注意，清華的Binary Cache源相比官方源cache.nixos.org缺少一些包，
僅使用清華源會導致部分包因為找不到匹配的二進制版本而需要從源碼進行編譯。

## 系統軟件包與服務配置
在NixOS中，可將常用的軟件包配置爲系統軟件包，在configuration.nix配置中設定`environment.systemPackages`配置項：

```sh
environment.systemPackages = with pkgs; [
  git neofetch stack rustup ... # 添加軟件包名稱
]
```

設定的軟件包會在`nixos-rebuild`時做爲系統軟件包自動安裝，而不需要手動安裝。

對於部分影響系統配置的應用和服務，NixOS中提供了獨立的配置項，
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

  # 桌面環境配置，以KDE5爲例
  xserver = {
    enable = true;
    desktopManager.plasma5.enable = true;
    displayManager.sddm.enable = true;
  };

  # 數據庫配置，以MySQL爲例
  mysql = {
    enable = true;
    package = pkgs.mariadb;
  };

  ...
};
```

NixOS使用`systemd`管理服務的狀態，在services配置段中啓用的服務默認會開機自啓動，且無法修改自啓狀態。
啓用與禁用services配置段中設定的服務，需要設定`systemd.services`配置段：

```nix
systemd.services.<name>.enable = true/false;
...

# 以MySQL服務爲例，禁用服務自啓
systemd.services.mysql.enable = false;
```

## 用戶配置
在`users.users`配置項中設定用戶相關配置。

```sh
users.users.[用戶名] = {
  isNormalUser = true; # 設定是否爲普通用戶，普通用戶才擁有獨立的家目錄和用戶組
  home = "家目錄"; # 默認家目錄爲"/home/用戶名"，有特殊需求可使用此配置指定家目錄
  description = "用戶簡介";
  extraGroups = ["wheel" "networkmanager"]; # 爲用戶添加額外的用戶組
};
```

要使用戶能使用`sudo`，需要將用戶加入`wheel`(管理員)用戶組中。

## Shell配置
默認配置下使用`bash`做爲普通用戶的默認shell，要使用其它shell應在configuration.nix配置中開啓需要使用的shell，
常見的shell如下：

```sh
programs.zsh.enable = true; # ZSH
programs.fish.enable = true; # fish
```

啓用了需要的shell後，修改configuration.nix中的**用戶配置**。
以fish爲例：

```sh
programs.fish.enable = true;

users.users.[用戶名] = {
  ...
  shell = pkgs.fish;
};
```

## 字體配置
configuration.nix配置中常用的字體相關配置：

```sh
fonts.enableFontDir = true; # 爲所有字體在"/run/current-system/sw/share/X11-fonts"路徑下創建軟連接
fonts.fonts = with pkgs; [ ... ]; # 配置字體包
fonts.fontconfig.defaultFonts = {
  monospace = [ "Xxx" ]; # 等寬字體
  sansSerif = [ "Xxx" ]; # 無襯線字體
  serif = [ "Xxx" ]; # 襯線字體
};
```

用戶自定義字體路徑`~/.fonts`已被上游廢棄，在NixOS中，將個人字體放置在此路徑下不會被加入字體列表。
取代該路徑的用戶字體路徑是`$XDG_DATA_HOME/fonts`，實際對應路徑爲`~/.local/share/fonts`。

## 輸入法配置
在configuration.nix配置的`i18n.inputMethod`配置項中設定使用的輸入法：

```sh
i18n.inputMethod = {
  enabled = "fcitx"; # 使用fcitx輸入法
  fcitx.engines = with pkgs.fcitx-engines; [ libpinyin anthy ];
};
```

在Gnome3桌面環境下，推薦使用`iBus`輸入法：

```sh
i18n.inputMethod = {
  enabled = "ibus"; # 使用ibus輸入法
  ibus.engines = with pkgs.ibus-engines; [ libpinyin anthy ];
};
```

## 桌面配置
NixOS提供了對各類主流桌面環境的支持，與常規發行版不同，安裝桌面環境不是直接通過包管理器直接安裝對應桌面相關軟件包，
而是在configuration.nix配置中設定桌面相關配置。

配置各類桌面環境前，需要首先開啓`X Window System (X11)`：

```sh
services.xserver.enable = true;
```

`services.xserver.desktopManager`配置項設定使用的桌面環境：

```sh
services.xserver.desktopManager.plasma5.enable = true;
services.xserver.desktopManager.xfce.enable = true;
services.xserver.desktopManager.gnome3.enable = true;
services.xserver.desktopManager.mate.enable = true;
```

`services.xserver.windowManager`配置項設定使用的窗口管理器：

```sh
services.xserver.windowManager.xmonad.enable = true;
services.xserver.windowManager.twm.enable = true;
services.xserver.windowManager.icewm.enable = true;
services.xserver.windowManager.i3.enable = true;
```

`services.xserver.displayManager`配置項設定使用的登陸管理器：

```sh
services.xserver.displayManager.sddm.enable = true; # SDDM爲默認使用的登陸管理器
services.xserver.displayManager.slim.enable = true;
services.xserver.displayManager.lightdm.enable = true;
```

### Gnome桌面環境可選軟件包配置
NixOS下的Gnome3默認會安裝所有Gnome的可選軟件包，如播放器、遊戲等。
可通過`environment.gnome3.excludePackages`配置項指定排除不需要的軟件包：

```sh
environment.gnome3.excludePackages = [ pkgs.gnome3.gnome-weather pkgs.gnome3.simple-scan ... ];
```

還可以排除所有的Gnome3可選軟件包：

```sh
environment.gnome3.excludePackages = pkgs.gnome3.optionalPackages;
```

使用`environment.gnome3.excludePackages`可能會屏蔽掉`environment.systemPackages`中設定的Gnome模塊，
因此在`2019-8-25`的更新(正式版本為`release-19.09`)中，`environment.gnome3.excludePackages`配置項已被廢棄，
新版本中控制Gnome3的可選軟件包使用`services.gnome3`系列配置項進行控制：

```sh
services.gnome3 = {
  core-os-services.enable = false;
  core-shell.enable = false;
  core-utilities.enable = false; # 控制周邊工具軟件包是否安裝
  games.enable = false; # 控制遊戲相關軟件包是否安裝
}
```



# 問題紀錄
紀錄在安裝、配置、日常使用NixOS時遇到的問題以及對應的解決方案。

## Failed to start Network Time Synchronization.
問題說明：<br>
執行`nixos-rebuild switch`構建新配置並進行切換後，出現時間同步服務啟動失敗的提示：

```
# nixos-rebuild switch
building Nix...
building the system configuration...
activating the configuration...
setting up /etc...
setting up tmpfiles
warning: the following units failed: systemd-timesyncd.service

● systemd-timesyncd.service - Network Time Synchronization
   Loaded: loaded (/nix/store/4rv8z4s8hvs11r98414gqzkvxws5kii5-systemd-234/example/systemd/system/systemd-timesyncd.service; enabled; vendor preset: enabled)
  Drop-In: /nix/store/yr7yppbvy8ibpjzdb4f0ra10063avjpx-system-units/systemd-timesyncd.service.d
           └─overrides.conf
   Active: failed (Result: exit-code) since Sat 2017-11-11 20:19:13 UTC; 4s ago
     Docs: man:systemd-timesyncd.service(8)
  Process: 16674 ExecStart=/nix/store/4rv8z4s8hvs11r98414gqzkvxws5kii5-systemd-234/lib/systemd/systemd-timesyncd (code=exited, status=226/NAMESPACE)
 Main PID: 16674 (code=exited, status=226/NAMESPACE)

Nov 11 20:19:13 nixos systemd[1]: systemd-timesyncd.service: Unit entered failed state.
Nov 11 20:19:13 nixos systemd[1]: systemd-timesyncd.service: Failed with result 'exit-code'.
Nov 11 20:19:13 nixos systemd[1]: systemd-timesyncd.service: Service has no hold-off time, scheduling restart.
Nov 11 20:19:13 nixos systemd[1]: Stopped Network Time Synchronization.
Nov 11 20:19:13 nixos systemd[1]: systemd-timesyncd.service: Start request repeated too quickly.
Nov 11 20:19:13 nixos systemd[1]: Failed to start Network Time Synchronization.
Nov 11 20:19:13 nixos systemd[1]: systemd-timesyncd.service: Unit entered failed state.
Nov 11 20:19:13 nixos systemd[1]: systemd-timesyncd.service: Failed with result 'exit-code'.
warning: error(s) occurred while switching to the new configuration
```

解決方案：<br>
移除符號鏈接`/var/lib/systemd/timesync`和路徑`/var/lib/private/systemd/timesync`下的所有內容，重啓服務則不會再收到錯誤提示。
參考[GitHub NixOS/nixpkgs Issues #31540](https://github.com/NixOS/nixpkgs/issues/31540)。
