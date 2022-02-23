<!-- TOC -->

- [Nix Package Manager](#nix-package-manager)
	- [多版本管理](#%E5%A4%9A%E7%89%88%E6%9C%AC%E7%AE%A1%E7%90%86)
	- [Nix User Environments](#nix-user-environments)
	- [Nix Channel](#nix-channel)
	- [Unfree](#unfree)
- [NixOS](#nixos)
	- [查看文檔](#%E6%9F%A5%E7%9C%8B%E6%96%87%E6%AA%94)
	- [安裝](#%E5%AE%89%E8%A3%9D)
	- [chroot安裝環境](#chroot%E5%AE%89%E8%A3%9D%E7%92%B0%E5%A2%83)
	- [配置管理](#%E9%85%8D%E7%BD%AE%E7%AE%A1%E7%90%86)
		- [版本升級與回退](#%E7%89%88%E6%9C%AC%E5%8D%87%E7%B4%9A%E8%88%87%E5%9B%9E%E9%80%80)
		- [Binary Cache](#binary-cache)
	- [系統軟件包與服務配置](#%E7%B3%BB%E7%B5%B1%E8%BB%9F%E4%BB%B6%E5%8C%85%E8%88%87%E6%9C%8D%E5%8B%99%E9%85%8D%E7%BD%AE)
	- [systemd服務](#systemd%E6%9C%8D%E5%8B%99)
	- [用戶配置](#%E7%94%A8%E6%88%B6%E9%85%8D%E7%BD%AE)
	- [Shell配置](#shell%E9%85%8D%E7%BD%AE)
	- [字體配置](#%E5%AD%97%E9%AB%94%E9%85%8D%E7%BD%AE)
	- [音頻配置](#%E9%9F%B3%E9%A0%BB%E9%85%8D%E7%BD%AE)
	- [輸入法配置](#%E8%BC%B8%E5%85%A5%E6%B3%95%E9%85%8D%E7%BD%AE)
	- [桌面配置](#%E6%A1%8C%E9%9D%A2%E9%85%8D%E7%BD%AE)
		- [Gnome桌面環境可選軟件包配置](#gnome%E6%A1%8C%E9%9D%A2%E7%92%B0%E5%A2%83%E5%8F%AF%E9%81%B8%E8%BB%9F%E4%BB%B6%E5%8C%85%E9%85%8D%E7%BD%AE)
- [問題紀錄](#%E5%95%8F%E9%A1%8C%E7%B4%80%E9%8C%84)
	- [Failed to start Network Time Synchronization.](#failed-to-start-network-time-synchronization)
	- [No output backlight property](#no-output-backlight-property)
	- [systemd-boot not installed in ESP.](#systemd-boot-not-installed-in-esp)

<!-- /TOC -->



# Nix Package Manager
`Nix Package Manager`是純函數式(purely functional)的包管理器，
Nix像純函數式語言(如Haskell)處理值一樣對待軟件包：
通過無副作用(no side-effects)的純函數來構建，在構建完成後就不再改變。

與傳統的軟件包管理器設計不同，Nix將軟件包存儲在`Nix Store`中(通常是`/nix/store`路徑下)，
每個軟件包存儲在**獨立**的子目錄中,軟件包路徑的命名規則爲`[軟件包id]-[軟件包名]-[版本]`，路徑示例：

```
/nix/store/b6gvzjyb2pg0kjfwrjmg1vfhh54ad73z-firefox-33.1/
```

## 多版本管理
Nix包管理器支持同時管理、安裝一個軟件包的多個版本，
保證了不同應用在依賴同一個軟件包的不同版本時不會造成`DLL hell`(動態庫依賴地獄)。
不同版本的軟件包安裝在Nix Store中的不同路徑下，各自隔離，不會相互影響。

Nix包管理器是函數式包管理器，在升級軟件包時不會對既有軟件包進行修改，
而是在Nix Store中添加新的軟件包，然後切換至新版本(修改符號連接指向)；
在版本升級後，舊版本軟件包依然存在，並且支持回滾到舊版本。

## Nix User Environments
`Nix User Environments`(Nix用戶環境)包含一組對特定用戶可用的軟件包，
Nix支持多用戶，允許同時存在多個用戶環境，每個用戶環境實際相當於一個特定的Nix Store視圖。

使用`nix-env`指令管理Nix用戶環境；
查詢、安裝、移除、更新軟件包：

```html
<!-- 列出已安裝的軟件包 -->
# nix-env -q
<!-- 列出倉庫內所有軟件包 -->
# nix-env -q

<!-- 查詢指定名稱的軟件包 -->
# nix-env -qa [軟件包名稱]
<!-- 查詢名稱中包含指定字段的軟件包，使用正則表達式語法 -->
# nix-env -qa '.*軟件包名稱.*'

<!-- 安裝軟件包 -->
# nix-env -i [軟件包名稱]
# nix-env --install [軟件包名稱]
# nix-env -iA [channel名稱.包名稱] <!-- 使用完整名稱安裝軟件包，可避免歧義 -->
# nix-env -iv [軟件包名稱] <!-- 安裝軟件包時輸出詳細日誌，便於發現錯誤 -->

<!-- 移除指定軟件包 -->
# nix-env -e [軟件包名稱]
# nix-env --uninstall [軟件包名稱]
<!-- 移除所有軟件包 -->
# nix-env -e '.*'

<!-- 更新所有軟件包 -->
# nix-env -u
<!-- 更新指定軟件包 -->
# nix-env -u '軟件包'
<!-- 查看可升級的軟件包 -->
# nix-env -u --dry-run
```

使用`nix-env -e`刪除的軟件包併爲真正的刪除軟件包本體，而是移除了到該軟件包的軟鏈接。
使用`nix-store --gc`來真正清理軟件包緩存：

```html
<!-- 清理軟件包時會計算當前系統的依賴關係，將不被依賴的軟件包全部清理 -->
# nix-store --gc

<!-- 使用--print-dead參數時僅計算並打印會被清理的依賴，不真正執行清理操作 -->
# nix-store --gc --print-dead
```

## Nix Channel
NixOS中的`Channel`概念上類似與常規發行版的`Mirror`(軟件源)。
NixOS的channel按照維度分類：

- 按照版本分類：**unstable**和**指定版本**
- 按照包類別分類：**nixos**和**nixpkgs**

```html
<!-- 官方源 -->
nixos https://nixos.org/channels/nixos-unstable
nixpkgs https://nixos.org/channels/nixpkgs-unstable

<!-- TUNA源 -->
nixos https://mirrors.tuna.tsinghua.edu.cn/nix-channels/nixos-unstable
nixpkgs https://mirrors.tuna.tsinghua.edu.cn/nix-channels/nixpkgs-unstable
```

使用`nix-channel`指令管理channel：

```html
$ nix-channel --list <!-- 顯示當前已配置的channel -->
$ nix-channel --add [url] [name] <!-- 添加指定channel -->
$ nix-channel --remove [name] <!-- 移除指定channel -->
```

在添加channel時若不指定名稱，則按找包類別使用默認名稱，例如`nixos-unstable`的channel名稱爲`nixos`。
channel名稱是**唯一**的，添加名稱相同的channel時，後添加的會替換先前的channel。

示例，設置nixpkg使用TUNA源：

```
$ nix-channel --add https://mirrors.tuna.tsinghua.edu.cn/nix-channels/nixpkgs-unstable nixpkgs
```

對於獨立安裝的Nix，若需要使用Binary Cache，則應修改`/etc/nix/nix.conf`，添加如下配置：

```
substituters = https://mirrors.tuna.tsinghua.edu.cn/nix-channels/store https://cache.nixos.org/
```

更新軟件包前應先更新channel：

```html
# nix-channel --update <!-- NixOS下使用 -->
# nix-env -u <!-- 更新軟件源後更新軟件包 -->
```

## Unfree
NixOS軟件源中收錄了部分Unfree的軟件包，如`Chrome`、`Visual Studio Code`等，
此類軟件包因爲許可證問題，默認不可被安裝。

臨時允許unfree軟件安裝，安裝時需要將`allowUnfree`屬性置爲true：

```
# nix-env -iA nixos.vscode --arg config '{ allowUnfree = true; }'
```

全局允許unfree軟件安裝，需要在configuration.nix配置中設定`nixpkgs.config.allowUnfree`屬性：

```nix
nixpkgs.config.allowUnfree = true;
```

configuration.nix配置中的unfree配置能允許在`environment.systemPackages`配置項中加入unfree軟件包，如：

```nix
environment.systemPackages = with pkgs; [ vscode ];
```

Nix包管理器對於每個用戶擁有獨立的配置，全局的unfree配置並不會對具體的某個用戶生效，
要使某個用戶能夠使用`nix-env -i`安裝unfree軟件包，
則需要編輯用戶的Nix配置`~/.config/nixpkgs/config.nix`，在該配置文件中加入：

```nix
{
  allowUnfree = true;
}
```



# NixOS
`NixOS`是基於`Nix package manager`的Linux發行版，提供了統一的包管理與配置管理。

## 查看文檔
NixOS自帶了對應版本的手冊，執行`nixos-help`指令會調用系統默認瀏覽器打開NixOS手冊。
手冊離線亦可閱讀，由`nixos-manual-html`軟件包提供。

## 安裝
[NixOS官網](https://nixos.org/nixos/download.html)提供了鏡像下載，官方提供的鏡像支持`x86/x64`平台。
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

```nix
boot.loader = {
  efi = {
    # 允許安裝進程修改EFI啓動參數
    canTouchEfiVariables = true;

    # 設定ESP分區掛載位置，早期Linux標準位置爲/boot/efi，
    # 最近的發行版則多數直接使用/boot，NixOS默認使用/boot，通常無需更改
    # efiSysMountPoint = "/boot/efi";
  };

  # 啓用 systemd 的啓動支持(systemd-boot)
  # 該配置與GRUB不必同時啟用
  systemd-boot.enable = true;

  # 啟用GRUB引導器，使用UEFI+GPT的設備無需指定GRUB引導器位置，MBR的舊式設備則需要指定(如"/dev/sda"等)
  # 該配置與systemd-boot不必同時啟用
  # grub {
  #   device = "nodev";
  #   useOSProber = true; # 啟用查找其它OS，雙系統時使用
  # };
};
```

其中，GRUB引導器和systemd-boot之間可二選一，不必同時安裝，
對於UEFI+GPT的現代設備，推薦使用systemd-boot。

默認生成的配置會使用當前穩定版系統，若需要使用unstable系統，
則應替換默認channel，添加對應新channel：

```html
<!-- 以USTC源為例 -->
# nix-channel --add https://mirrors.tuna.tsinghua.edu.cn/nix-channels/nixos-unstable
```

Nix配置修改完成後執行安裝操作：

```c
# nixos-install
```

執行指令後安裝器會以給定的Nix配置執行系統安裝流程：安裝系統文件、配置引導器、配置賬戶信息等。

## chroot安裝環境
NixOS提供了與ArchLinux的`arch-chroot`類似的工具，分區正確掛載後可直接進入安裝後的新系統：

```html
<!-- 默認新系統的掛載路徑爲 /mnt -->
$ nixos-enter
```

亦可使用Linux的標準chroot指令進行掛載：

```
# mount -o bind /dev /mnt/dev
# mount -o bind /proc /mnt/proc
# mount -o bind /sys /mnt/sys
# chroot /mnt /nix/var/nix/profiles/system/activate
# chroot /mnt /run/current-system/sw/bin/bash
```

## 配置管理
在NixOS中，系統核心配置`/etc/nixos/configuration.nix`接管了系統內所有服務以及軟件包的配置，
以常規方式修改軟件包自身配置的方式對於系統級軟件包**無效**。
以`sudo`爲例，直接修改`/etc/sudoers`配置並不能正常賦予某個用戶管理員權限。

重新構建系統配置：

```html
# nixos-rebuild switch <!-- 重新構建配置，並立即切換到新配置 -->
# nixos-rebuild switch --upgrade <!-- 構建配置同時更新系統 -->
# nixos-rebuild switch --upgrade-all <!-- 完整更新系統 -->
```

每次rebuild生成的配置會以啟動項的方式顯示在GRUB菜單中，
想要恢復之前配置環境僅需重啓進入GRUB進入對應菜單即可。

列出所有的配置：

```
# nix-env --list-generations
```

執行清理操作：

```html
<!-- 刪除指定編號的配置 -->
# nix-env --delete-generations [配置編號...]

<!-- 清理所有非激活配置和過時軟件包 -->
# nix-collect-garbage -d
```

### 版本升級與回退
執行`nixos-rebuild`系列指令重構配置。

```html
# nixos-rebuild boot <!-- 構建配置後繼續使用當前配置，新配置將在下次啟動時作為默認配置載入 -->
# nixos-rebuild test <!-- 構建並立即切換到新配置，但下次重啓後恢復之前的配置(測試配置) -->

# nixos-rebuild switch <!-- 構建配置後立即切換到新配置 -->
# nixos-rebuild switch --upgrade <!-- 刷新軟件源後構建並切換配置，相當於系統更新 -->
```

系統會按照當前nix-channel中指定的nixos源進行升級，該源也可以由configuration.nix中的配置來指定：

```nix
system.autoUpgrade.channel = "https://mirrors.tuna.tsinghua.edu.cn/nix-channels/nixos-unstable";
```

回滾之前配置可在開機的GRUB啟動菜單中選擇；亦可在命令行中回滾配置，執行：

```html
# nixos-rebuild switch --rollback <!-- 回滾到當前配置的上一版本配置 -->
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

從`NixOS 22.05`開始，Binary Cache配置項變更爲`nix.settings.substituters`：

```nix
nix.settings.substituters = ["https://mirrors.tuna.tsinghua.edu.cn/nix-channels/store"];
```

執行nix-rebuild指令後，會重新生成`/etc/nix/nix.conf`，
Binary Cache配置項會體現在該文件的`substituters`配置項中：

```
$ cat /etc/nix/nix.conf
...
substituters = https://cache.nixos.org/ https://mirrors.tuna.tsinghua.edu.cn/nix-channels/store
...
```

## 系統軟件包與服務配置
在NixOS中，可將常用的軟件包配置爲系統軟件包，
在configuration.nix配置中設定`environment.systemPackages`配置項：

```nix
environment.systemPackages = with pkgs; [
  git neofetch stack rustup ... # 添加軟件包名稱
]
```

設定的軟件包會在`nixos-rebuild`時做爲系統軟件包自動安裝，而不需要手動安裝。

對於部分影響系統配置的應用和服務，NixOS中提供了獨立的配置項，
在configuration.nix配置中`programs`、`services`配置段：

```nix
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

## systemd服務
NixOS使用`systemd`管理服務，啓用與禁用services配置段中設定的服務，需要設定`systemd.services`配置段：

```nix
systemd.services.服務名稱.enable = true/false;
...

# 以MySQL服務爲例，禁用服務
systemd.services.mysql.enable = false;
```

在services配置段中啓用的服務通常會默認會開機自啓動，
且**無法修改**自啓狀態，若直接通過`enable`配置項禁用服務，
則**不會生成**該服務的systemd service(即無法使用systemctl相關指令管理服務)。

若需要禁用服務自啟動同時保留該服務的systemd service unit，
可使用`wantedBy`配置搭配`lib.mkForce`函數強制覆蓋自啟動配置項：

```nix
# 強制清空服務的啟動依賴，則目標服務不會被任何其它服務依賴（達到關閉自啟動的目的）
systemd.services.服務名稱.wantedBy = lib.mkForce [];
```

## 用戶配置
在`users.users`配置項中設定用戶相關配置。

```nix
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

```nix
programs.zsh.enable = true; # zsh
programs.fish.enable = true; # fish
```

啓用了需要的shell後，修改configuration.nix中的**用戶配置**。
以fish爲例：

```nix
programs.fish.enable = true;

users.users.[用戶名] = {
  ...
  shell = pkgs.fish;
};
```

## 字體配置
configuration.nix配置中常用的字體相關配置：

```nix
fonts.fonts = with pkgs; [ ... ]; # 配置字體包
fonts.fontconfig.defaultFonts = {
  monospace = ["Xxx"]; # 等寬字體
  sansSerif = ["Xxx"]; # 無襯線字體
  serif = ["Xxx"]; # 襯線字體
};
```

用戶自定義字體路徑`~/.fonts`已被上游廢棄，在NixOS中，將個人字體放置在此路徑下不會被加入字體列表。
取代該路徑的用戶字體路徑是`$XDG_DATA_HOME/fonts`，實際對應路徑爲`~/.local/share/fonts`。

## 音頻配置
默認配置下不會開啟音頻，需要手動開啟配置：

```nix
# 開啟PulseAudio服務，sound.enable配置會隨著該配置自動啟用，因此不必顯式配置
hardware.pulseaudio.enable = true;
```

默認NixOS中PulseAudio默認不會提供系統級服務，而是針對每個用戶提供服務。
默認全局systemd服務中不存在`pulseaudio.service`，而是在用戶服務中：

```
$ systemctl --user status pulseaudio.service
```

默認pulseaudio.service未配置自啟動，因此部分桌面環境下音量指示器會出現無設備指示，
需要播放任意視屏/音頻激活pulseaudio.service後音量指示器才能正常顯示。
解決該問題需要將pulseaudio.service設置為自啟動，則音量指示器開機後立即正常顯示：

```
$ systemctl --user enable pulseaudio.service
```

若系統未正確生成pulseaudio.service服務，則可手動啓動pulseaudio：

```
$ pulseaudio --start
```

NixOS中亦可將pulseaudio.service配置爲系統服務：

```nix
hardware.pulseaudio.systemWide = true;
# 使用系統級的PluseAudio，則用戶需要加入 audio 組中才能正常輸出音頻
users.extraUsers.用戶名稱.extraGroups = [ "audio" ... ];
```

## 輸入法配置
在configuration.nix配置的`i18n.inputMethod`配置項中設定使用的輸入法：

```nix
i18n.inputMethod = {
  enabled = "fcitx"; # 使用fcitx輸入法
  fcitx.engines = with pkgs.fcitx-engines; [libpinyin anthy];
};
```

在Gnome3桌面環境下，推薦使用`iBus`輸入法：

```nix
i18n.inputMethod = {
  enabled = "ibus"; # 使用ibus輸入法
  ibus.engines = with pkgs.ibus-engines; [libpinyin anthy];
};
```

## 桌面配置
NixOS提供了對各類主流桌面環境的支持，與常規發行版不同，
安裝桌面環境不是直接通過包管理器直接安裝對應桌面相關軟件包，
而是在configuration.nix配置中設定桌面相關配置。

配置各類桌面環境前，需要首先開啓`X Window System (X11)`：

```nix
services.xserver.enable = true;
```

`services.xserver.desktopManager`配置項設定使用的桌面環境：

```nix
services.xserver.desktopManager.plasma5.enable = true;
services.xserver.desktopManager.xfce.enable = true;
services.xserver.desktopManager.gnome3.enable = true;
services.xserver.desktopManager.mate.enable = true;
```

`services.xserver.windowManager`配置項設定使用的窗口管理器：

```nix
services.xserver.windowManager.xmonad.enable = true;
services.xserver.windowManager.twm.enable = true;
services.xserver.windowManager.icewm.enable = true;
services.xserver.windowManager.i3.enable = true;
```

`services.xserver.displayManager`配置項設定使用的登陸管理器：

```nix
services.xserver.displayManager.sddm.enable = true; # SDDM爲默認使用的登陸管理器
services.xserver.displayManager.slim.enable = true;
services.xserver.displayManager.lightdm.enable = true;
```

### Gnome桌面環境可選軟件包配置
NixOS下的Gnome3默認會安裝所有Gnome的可選軟件包，如播放器、遊戲等。
可通過`environment.gnome3.excludePackages`配置項指定排除不需要的軟件包：

```nix
environment.gnome3.excludePackages = [ pkgs.gnome3.gnome-weather pkgs.gnome3.simple-scan ... ];
```

還可以排除所有的Gnome3可選軟件包：

```nix
environment.gnome3.excludePackages = pkgs.gnome3.optionalPackages;
```

使用`environment.gnome3.excludePackages`可能會屏蔽掉`environment.systemPackages`中設定的Gnome模塊，
因此在`2019-8-25`的更新(正式版本為`release-19.09`)中，`environment.gnome3.excludePackages`配置項已被廢棄，
新版本中控制Gnome3的可選軟件包使用`services.gnome3`系列配置項進行控制：

```nix
services.gnome3 = {
  core-os-services.enable = false;
  core-shell.enable = false;
  core-utilities.enable = false; # 控制周邊工具軟件包是否安裝
  games.enable = false; # 控制遊戲相關軟件包是否安裝
}
```

詳情可參考[NixOS官方更新日誌](https://nixos.org/nixos/manual/release-notes.html#sec-release-19.09-highlights)：

> The GNOME 3 desktop manager module sports an interface to enable/disable core services, applications, and optional GNOME packages like games.
>
> This can be achieved with the following options which the desktop manager default enables, excluding games.
>
> services.gnome3.core-os-services.enable
>
> services.gnome3.core-shell.enable
>
> services.gnome3.core-utilities.enable
>
> services.gnome3.games.enable
>
> With these options we hope to give users finer grained control over their systems. Prior to this change you'd either have to manually disable options or use environment.gnome3.excludePackages which only excluded the optional applications. environment.gnome3.excludePackages is now unguarded, it can exclude any package installed with environment.systemPackages in the GNOME 3 module.



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
移除符號鏈接`/var/lib/systemd/timesync`和路徑`/var/lib/private/systemd/timesync`下的所有內容，
重啓服務則不會再收到錯誤提示。
參考[GitHub NixOS/nixpkgs Issues #31540](https://github.com/NixOS/nixpkgs/issues/31540)。

## No output backlight property
問題說明：<br>
使用`xbacklight`相關指令時，提示`No output backlight property`。
啟用`hardware.acpilight.enable`參數、用戶加入`video`組後依舊如此。

解決方案：<br>
對於使用intel核芯顯卡的計算機，需要正確配置intel顯卡驅動，在configuration.nix中添加：

```nix
services.xserver.videoDivers = ["intel"];
```

實際上，僅需要正確配置intel顯卡驅動，xbacklight即可正常工作，無需設置acpilight或是將用戶加入video用戶組。

## systemd-boot not installed in ESP.
問題說明：<br>
使用systemd-boot管理作為啟動管理器時，若引導器未能正確安裝，在重新生成NixOS構建配置時會得到以下錯誤信息：

```c
# nixos-rebuild switch
...
systemd-boot not installed in ESP.
...
```

錯誤信息中告知了引導器未能正確安裝在ESP分區中。

解決方案：<br>
使用systemd-boot提供的`bootctl`工具可重新安裝引導器到ESP分區中：

```c
# bootctl install
...
Created EFI boot entry "Linux Boot Manager".
```

正確安裝了引導器會出現`Created EFI boot entry "Linux Boot Manager".`文本提示，
在BIOS中的啟動項管理頁面可看到對應引導器並進行配置。
