<!-- TOC -->

- [Windows CMD](#windows-cmd)
	- [文件/目錄鏈接](#文件目錄鏈接)
- [常用Unix工具指令](#常用unix工具指令)
	- [grep](#grep)
	- [find](#find)
	- [進程管理](#進程管理)
	- [日誌記錄](#日誌記錄)
	- [文件系統](#文件系統)
- [PulseAudio](#pulseaudio)
- [用戶管理](#用戶管理)
- [UID/GID/Sticky](#uidgidsticky)
- [ftp](#ftp)
	- [連接服務器](#連接服務器)
	- [常用指令](#常用指令)
- [SSH](#ssh)
	- [遠程登錄](#遠程登錄)
	- [服務配置](#服務配置)
	- [配置免密登陸](#配置免密登陸)
- [GNU GRUB](#gnu-grub)
	- [安裝與配置](#安裝與配置)
	- [安裝引導器](#安裝引導器)
	- [修復引導](#修復引導)
- [壓縮/解壓](#壓縮解壓)
	- [7z](#7z)
- [ulimit](#ulimit)
	- [配置文件](#配置文件)
	- [Core Dump (核心轉儲)](#core-dump-核心轉儲)
- [fdisk](#fdisk)
- [parted](#parted)
- [LVM](#lvm)
	- [基本操作](#基本操作)
	- [Physical Volume (PV，物理卷)](#physical-volume-pv物理卷)
	- [Volume Group (VG，卷組)](#volume-group-vg卷組)
	- [Logical Volume (LV，邏輯卷)](#logical-volume-lv邏輯卷)
	- [邏輯卷狀態和塊設備不顯示問題](#邏輯卷狀態和塊設備不顯示問題)
- [curl](#curl)
	- [FTP 操作](#ftp-操作)
- [Suspend 和 Hibernate](#suspend-和-hibernate)
- [systemd](#systemd)
	- [服務管理](#服務管理)
	- [服務分析](#服務分析)
	- [系統配置](#系統配置)
- [VTE](#vte)
	- [啓動參數](#啓動參數)
- [apt/dpkg](#aptdpkg)
	- [源配置](#源配置)
	- [Debian 源](#debian-源)
	- [Ubuntu 源](#ubuntu-源)
	- [apt-mirror](#apt-mirror)
		- [本地源配置](#本地源配置)
		- [使用本地源](#使用本地源)
- [常見問題記錄](#常見問題記錄)
	- [Ubuntu](#ubuntu)
		- [invoke-rc.d: initscript Xxxx, action "stop" failed.](#invoke-rcd-initscript-xxxx-action-stop-failed)

<!-- /TOC -->



# Windows CMD
Windows系統提供的命令行執行DOS系統工具指令。

文件操作相關：

```c
// 查看DOS指令的使用幫助
> [指令名稱] /help

// 查看目錄
> dir
// 新建目錄
> md
// 刪除目錄(空目錄)
> rd

// 複製文件
> copy
// 刪除文件
> del

// 展示目錄樹
> tree
// 移除目錄樹
> deltree
```

服務管理：

```c
// 啓動相關配置
> msconfig

// 啓動服務管理面板
> services.msc

// 創建/刪除服務
> sc create [服務名稱] binPath=[做爲服務啓動的指令]
> sc delete [服務名稱]

// 啓動/停止服務
> net start [服務名稱]
> net stop [服務名稱]
```

電源管理：

```c
> powercfg

// 開啓休眠
> powercfg /h on
// 禁用休眠
> powercfg /h off
```

其它實用工具：

```c
// 查看系統進程列表
> tasklist

// Windows遠程桌面工具
> mstsc

// 顯示主機名和用戶名
> whoami

// 查看網絡信息
> ipconfig
// 查詢完整的網絡信息
> ipconfig /all
// 查看路由信息
> route print

// 查看內存信息
> wmic memorychip

// DirectX診斷工具，可查看系統信息，顯卡對DirectX的支持情況
> dxdiag
```

## 文件/目錄鏈接
Windows文件管理器提供的快捷方式(`Shortcut`)並不是對應用程序透明的，
應用程序在使用快捷方式路徑時並不等價於使用目標文件路徑。
在Vista之後，Windows提供了`mklink`工具，mklink類似Unix下的`ln`工具，
可創建對應用程序完全透明的硬鏈接(`hard link`)/符號鏈接(`symbolic link`)。

創建到目標地址的軟連接文件：

```c
> mklink [文件名] [鏈接目標地址]
```

mklink指令默認創建軟連接文件，使用`/d`參數創建軟連接**目錄**：

```c
> mklink /d [目錄名] [鏈接目標目錄]
```

使用`/h`參數可創建硬鏈接代替軟連接，硬鏈接需要鏈接文件於目標文件在相同盤符下：

```c
> mklink /h [文件名] [鏈接目標文件]
```



# 常用Unix工具指令
一些Unix常用指令的簡介。

## grep
`grep`用於搜索文本中包含指定內容的行，常用於管道操作中處理其它指令的輸出結果。

```c
// 從給定的內容中查找包含 xxx 的內容
$ grep xxx

// 從給定的內容中排除包含 xxx 的內容
$ grep -v xxx

// 查找 xxx (嚴格匹配)
$ grep -w xxx
// 等價於grep -w
$ grep '\<xxx\>'

// 匹配 xxx 時忽略大小寫
$ grep -i xxx
```

## find
`find`用於查找滿足條件的文件，與其它指令搭配起到處理特定類型文件的作用。

按照名稱查找指定路徑下的文件：

```
$ find [路徑] -name [文件名稱]
```

按照文件類型查找指定路徑下的文件：

```c
/*
文件類型：
b 塊設備
c 字符設備
d 目錄
f 普通文件
l 符號鏈接
p 管道
s 套接字
*/
$ find [路徑] -type [文件類型]

// 查找路徑下的所有目錄
$ find [路徑] -type d

// 查找路徑下的所有文件
$ find [路徑] -type f
```

使用`-exec`參數對查找到目標執行額外附加操作：

```c
$ find [路徑] -exec [指令] \; //指令需要以分號結尾
```

exec參數執行的指令以`;`符號結尾，指令中可使用`{}`符號代表當前查找到的路徑，字符需要**轉義**。
示例，查找當前路徑下所有文件(排除目錄)，並將權限設置爲`644`：

```c
$ find . -type f -exec chmod 644 \{\} \;
```

## 進程管理
`kill`指令用於殺死進程，`ps`指令用於查看進程狀態。

```c
// 強制殺死進程(發送SIGKILL信號，該信號不可被忽略)
$ kill -9 [pid]
// 向指定進程發送指定名稱的信號
$ kill -s [sig_name] [pid]
// 向指定進程發送指定編號的信號
$ kill -n [sig_num] [pid]
// 列出系統支持的信號
$ kill -l

// 打印指定 pid 進程信息
$ ps --pid [pid]
// 打印所有進程信息
$ ps a
// 輸出指定內容的進程信息
$ ps -o cmd,user,stat,pid,ppid,pgid,sid,tpgid,tty
```

## 日誌記錄
使用傳統syslog服務的Linux發行版日誌存放在`/var/log`路徑下，以純文本形式存儲；
使用systemd服務的Linux發行版日誌使用二進制格式記錄，通過`journalctl`工具查看。

```c
// 查看登錄記錄、開關機記錄
$ last

// 輸出內核信息
$ dmesg

// 查看systemd日誌
$ journalctl
// 倒序查看systemd日誌
$ journalctl -r
```

## 文件系統
查看分區信息的相關指令：

```c
// 查看文件inode
$ ls -i

// 查看硬盤分區
$ lsblk
// 查看分區UUID
$ lsblk -f
// 查看分區UUID
# blkid

// 顯示已掛載分區的信息
$ mount
// 顯示指定分區的信息(分區大小，分區類型等)
# file -s [分區卷]

// 顯示已掛載的文件系統
# df
// 以合適的單位顯示文件系統大小
# df -h
// 顯示文件系統類型
# df -T
```

查看文件系統標誌使用`wipefs`指令：

```c
// 查看分區的文件系統標誌
$ wipefs [分區]
// 清理分區所包含的所有文件系統標誌
# wipefs -a [分區]
```



# PulseAudio
`PulseAudio`是用於`POSIX`系統的音頻系統，是音頻程序的代理(proxy)。
PulseAudio允許用戶對音頻應用和音頻硬件之間傳遞的音頻數據執行高級操作。
使用音頻服務可輕鬆實現諸如將音頻傳輸到另一臺機器上、改變樣本格式或通道數量、混合多種音頻等功能。

PulseAudio爲Linux系統設計，現在也被移植到了`Solaris`、`FreeBSD`、`NetBSD`、`macOS`、`Windows 2000`、`Windows XP`等系統上。

使用PulseAudio提供的`pactl`控制、調整音頻設備：

```c
// 輸出音頻設備信息(簡短輸出)
$ pactl list sinks short
// 輸出完整音頻設備信息
$ pactl list

// 調整設備音量，"調整幅度" 格式爲百分數如 "+5%"
$ pactl set-link-volume [音頻設備編號] [調整幅度]
// 開啓/關閉靜音
$ pactl set-sink-mute [音頻設備編號] [true/false]
```



# 用戶管理
在Linux中，用戶信息、用戶組信息相關文件均位於`/etc`路徑下：

| 文件路徑 | 作用 | 所屬用戶:用戶組 | 文件權限 |
| :- | :- | :- | :- |
| /etc/passwd | 保存用戶信息 | root:root | 644 |
| /etc/group | 保存用戶組信息 | root:root | 644 |
| /etc/shadow | 保存用戶密碼的加密信息 | root:shadow | 640 |
| /etc/gshadow | 保存用戶組密碼的加密信息 | root:shadow | 640 |

用戶管理：

```c
// 創建用戶
# useradd [用戶名]
// 創建用戶，併爲該用戶創建對應的同名家目錄
# useradd -m [用戶名]

// 刪除用戶
# userdel [用戶名]
// 刪除用戶，並同時刪除該用戶的家目錄
# userdel -r [用戶名]

// 修改用戶相關信息，如密碼、家目錄、登錄shell、用戶組等
# usermod
```

用戶組管理：

```c
// 創建用戶組
# groupadd [用戶組名]

// 刪除用戶組，用戶組需要爲空
# groupdel [用戶組名]

// 將用戶添加到用戶組中
# usermod -a -G [用戶組] [用戶名]
// 強制設置用戶的用戶組，若原先用戶加入的組不在給出的組列表中，將被移除原先的組(用戶的主組除外)
# usermod -G [用戶組1,用戶組2,...] [用戶名]
```

修改文件用戶、用戶組：

```c
// 更改指定文件所有者
$ chown [選項] [用戶名:用戶組] [文件名]
// 遞歸更改路徑下所有文件歸屬
$ chown -R [用戶名:用戶組] [路徑]

// 更改指定文件所屬用戶組
$ chgrp [選項] [用戶組名] [文件名]
```



# UID/GID/Sticky
Linux系統中擁有三類特殊權限標誌：

| 權限標誌 | 含義 |
| :- | :- |
| s(setuid) | 僅對文件有效，使文件在執行階段具有文件所有者的權限 |
| s(setgid) | 僅對目錄有效，使目錄下創建的文件都具有和該目錄所屬的組相同的組 |
| t(sticky) | 僅對文件有效，禁止文件被刪除(不受寫權限約束，對root用戶無效) |

使用8進制數值表示文件權限時，這些特殊權限佔有一組獨立的8進制位(位於傳統權限標誌位之前)。
如傳統文件的權限爲`777`，添加了特殊權限後使用`?777`表示，`?`即爲特殊權限的啓用情況。

特殊權限8進制數值的2進制位含義：

`321`

| 位置索引 | 含義 |
| :- | :- |
| 3(高位) | 高位使用字母s，表示setuid |
| 2(中間位) | 中間位同樣使用字母s，表示setgid |
| 1(低位) | 低位使用字母t，表示sticky bit |

使用`ls`指令展示文件權限信息時，若設置了這三類特殊權限，則會覆蓋原有的可執行權限位的顯示：

```c
$ touch test

// 設置所有權限，包括特殊權限
$ chmod 7777 test

// 打印權限信息，sst標誌代替了原本各自位置的x標誌
$ ls -alh test
-rwsrwsrwt 1 root root 0 Aug 26 15:17 test
```

使用`chmod`指令設置三類特殊權限：

```c
// 設置文件的setuid權限
$ chmod u+s [文件名]
// 設置目錄的setgid權限
$ chmod g+s [目錄名]
// 設置文件的stick bit權限
$ chmod o+t [文件名]

// 使用4組8進制數值設定文件讀寫執行權限和三類額外權限
$ chmod 7777 [文件/目錄]
```



# ftp
`Windows`系統下提供了`ftp`命令行工具用於訪問`FTP`服務器進行交互。

## 連接服務器
使用`ftp`指令與服務端建立連接：

```
$ ftp [服務端IP地址]
```

成功建立連接後，會提示輸入FTP用戶名/密碼，如下所示：

```
> ftp [服務端IP地址]
連接到 [服務端IP地址]。
...
用戶([IP地址]:(none)): Xxx
331 Password required for Xxx
密碼:
230 User Xxx logged in
ftp>
```

通過服務端用戶驗證後，會進入`ftp shell`，如下所示：

```
ftp> ...
```

亦可不指定服務端IP直接進入ftp shell，在命令行中打開FTP連接。
在ftp shell中使用`open/close`指令建立/關閉連接，如下所示：

```
ftp> open [服務端IP地址]
連接到 [服務端IP地址]。
...
用戶([IP地址]:(none)): Xxx
331 Password required for Xxx
密碼:
230 User Xxx logged in
ftp>
```

## 常用指令
`ftp shell`中常用指令：

| 指令 | 作用 |
| :- | :- |
| ![指令] | 使用系統`Shell`執行指令 |
| quit | 退出`ftp shell` |
| lcd/cd | 跳轉本地/遠程目錄 |
| open/close | 打開關閉連接 |
| ls/dir | 查看`FTP`目錄 |
| put/send | 向`FTP`發送文件 |
| get/recv | 接收來自`FTP`的文件 |
| mkdir/rmdir | 創建/刪除`FTP`目錄 |
| delete | 刪除`FTP`的文件 |
| rename | 重命名`FTP`的文件 |



# SSH
`SSH`全稱`Secure Shell`，是一種加密的網絡傳輸協議。
SSH通過在網絡中建立`Secure Channel`(安全通道)實現SSH客戶端與服務端之間的連接。

SSH常用在Unix系統中，用於傳輸命令行界面和遠程執行指令。
相比使用明文傳輸的`Telnet`協議，SSH能夠保證網絡環境中信息加密完整可靠。

SSH的主流實現是`OpenSSH`(全稱`OpenBSD Secure Shell`)。

## 遠程登錄
使用`ssh`指令遠程登錄配置了SSH服務的主機：

```c
// 使用 -p 參數指定遠程登錄端口，SSH服務默認端口爲22
$ ssh [用戶名]@[主機名/IP]
```

## 服務配置
SSH服務相關配置文件位於`/etc/ssh`路徑下：

- `/etc/ssh/ssh_config` ssh指令使用的配置
- `/etc/ssh/sshd_config` SSH服務使用的配置

常用SSH服務配置：

- `PermitRootLogin`

	配置SSH服務是否允許root登陸。

	| 配置項 | 取值含義 |
	| :- | :- |
	| yes(默認) | 允許root用戶登陸 |
	| no | 不允許root用戶登陸 |
	| without-password | 可登陸root用戶，但不能以密碼驗證的方式登陸(可用key驗證) |
	| forced-commands-only | 可登陸root用戶，但登陸後僅能執行指令後退出，不能交互 |

- `UseDNS`

	配置是否啓用DNS PTR。
	動態IP通常不會有PTR記錄，開啓DNS PTR有時導致SSH登陸過慢。

	| 配置項 | 取值含義 |
	| :- | :- |
	| yes | 開啓 |
	| no | 關閉 |

## 配置免密登陸
默認配置下，登陸SSH需要密碼，當部署一些依賴SSH協議的分佈式服務時(如`Hadoop`、`Zookeeper`、`Kafka`等)，需要配置免密登陸。

使用`ssh-keygen`工具生成公鑰和私鑰，如下所示：

```
$ ssh-keygen -t rsa
```

執行指令後會出現交互式對話提示輸入一些密鑰相關的信息，全部回車使用默認選項即可。
指令執行結束後，會在`~/.ssh`路徑下生成以下文件：

- `id_rsa` 私鑰文件，文件權限`600`
- `id_rsa.pub` 公鑰文件，文件權限`644`

在`~/.ssh`路徑下創建`authorized_keys`文件：

- 將其它機器的公鑰加入其中，允許其它機器免密登陸本機。
- 將本機的公鑰加入其它機器的authorized_keys文件中，則允許本機免密登陸其它機器。

將本機公鑰添加到目標主機可以使用`ssh-copy-id`指令：

```c
// 將 ~/.ssh/id_rsa.pub 中記錄的公鑰加入目標主機
$ ssh-copy-id [目標用戶名]@[目標主機地址/IP]

// 指定公鑰加入目標主機
$ ssh-copy-id [目標用戶名]@[目標主機地址/IP] -I [指定公鑰路徑]
```

正確生成當前機器的公鑰、私鑰，並將公鑰寫入目標機器authorized_keys文件中即可實現SSH免密登錄目標機器。

使用ssh指令登陸目標機器時，默認使用`~/.ssh/id_rsa`文件做爲私鑰進行驗證，若需要指定私鑰文件，可以添加`-i`參數：

```c
$ ssh -i [指定私鑰路徑] [目標用戶名]@[目標主機地址/IP]
```



# GNU GRUB
`GRUB`(`GRand Unified Bootloader`)是現代Linux的標準啓動管理器，是`LILO`(`Linux Loader`)的替代品。

GRUB支持多重引導，除了Linux，也能用於引導`Windows`、`FreeBSD`等其它現代操作系統。
GRUB在較新版本中提供了對`UEFI BIOS`新型固件的支持。

早期版本的GRUB(`i.e. version 0.9x`)現在被稱爲`GRUB Legacy`，已停止開發。
GRUB現在的主要版本爲`GRUB 2`。

## 安裝與配置
GRUB作爲重要的系統組件，通常已被收錄於各大發行版的官方源中，多數發行版會默認安裝GRUB。
使用包管理手動安裝GRUB：

```c
# pacman -S grub //Arch Linux
# apt install grub-common //Ubuntu、Debian
```

GRUB的配置文件爲`/boot/grub/grub.cfg`，可以使用`grub-mkconfig`指令根據已安裝的`OS`自動生成合適的引導配置：

```c
# grub-mkconfig -o /boot/grub/grub.cfg //通用
# update-grub //Debian系專屬
```

默認`grub-mkconfig`生成配置時僅會掃描硬盤中的Linux發行版，若需要生成的配置包含其它`OS`的引導菜單，需要額外安裝`os-prober`組件：

```c
# pacman -S os-prober //Arch Linux
# apt install os-prober //Ubuntu、Debian
```

## 安裝引導器
正確生成GRUB配置後，使用`grub-install`將引導器安裝到硬盤中。
對於使用`MBR`電腦，應在安裝時指明安裝設備：

```c
# grub-install /dev/sda //將GRUB引導器安裝到硬盤 /dev/sda 中
```

對於使用`UEFI`固件的新式電腦，需要將`ESP`分區掛載到`/boot/efi`路徑下，並且額外安裝`efibootmgr`組件:

```c
# pacman -S efibootmgr //Arch Linux
# apt install efibootmgr //Ubuntu、Debian
```

將GRUB引導器安裝到`UEFI`固件的電腦中無需額外參數：

```
# grub-install
```

安裝完成後會在`ESP`分區中生成對應的`efi`引導文件。

## 修復引導
當分區結構發生變化時，引導器可能不能正常加載。
若開機進入以`grub rescue>`爲提示符的救援界面時，可嘗試以下步驟恢復：

1. 查看分區結構，確認`Linux`分區位置。

	執行`ls`指令，查看分區列表：

	```
	grub rescue> ls
	(hd0) (hd0,gpt1) (hd0,gpt2) (hd0,gpt3) ...
	```

	確認分區的文件系統：

	```
	grub rescue> ls (hd0,gpt2)
	(hd0,gpt2): Filesystem is unknown.
	grub rescue> ls (hd0,gpt3)
	(hd0,gpt3): Filesystem is ext2.
	```

	確認分區的內容：

	```
	grub rescue> ls (hd0,gpt3)/
	...
	```

1. 指定啓動分區位置，手動加載啓動器。

	確認分區的位置後，設置啓動參數：

	```
	grub rescue> set boot=(hd0,gpt3)
	grub rescue> set prefix=(hd0,gpt3)/boot/grub
	grub rescue> insmod normal
	grub rescue> normal
	```

	之後即可進入正常的GRUB引導界面。

1. 重新安裝引導器。

	正常啓動系統後，在終端重新安裝引導器：

	```c
	# grub-install /dev/sda //MBR
	# grub-install //UEFI
	```



# 壓縮/解壓
Unix系統中傳統的檔案文件格式爲`tar archives`，可將多個文件、目錄下的資源打包到一個tar包中。
使用tar指令創建tar包，tar包經過壓縮後得到tar.gz(gzip)、tar.bz2(bzip2)等格式。

tar指令常見用法：

```c
// 生成 tar 包
$ tar cvf [tar文件] [被壓縮文件...]
// 使用 gzip 壓縮文件
$ tar cvzf [tar文件] [被壓縮文件...]

// 解壓文件
$ tar xvf [tar文件]
// 使用 gzip 解壓
$ tar xzvf [tar.gz文件]
// 使用 bzip2 解壓
$ tar xjvf [tar.bz2文件]

// 解壓文件到指定路徑
$ tar xvf [tar文件] -C [輸出路徑]
$ tar xzvf [tar.gz文件] -C [輸出路徑]
$ tar xjvf [tar.bz2文件] -C [輸出路徑]
```

## 7z
`7z`是開源的壓縮工具，支持多種壓縮格式，其特有的7z格式具有較高的壓縮比。

```c
// 生成指定類型的壓縮文件
// 類型可以是 7z zip tar bzip2 gzip 等
$ 7z a -t{類型} [生成文件] [被壓縮文件...]

// 解壓文件到指定路徑
$ 7z x [待解壓文件] -o[輸出路徑]

// 列出壓縮包的內容
$ 7z l [壓縮文件]
```



# ulimit
使用`ulimit`指令查看和設定各類限制。
指令格式：

```
$ ulimit [類別] [限制數值]
```

其中，常見類別如下：

- `-a` 查看所有種類的限制
- `-f` 文件存儲
- `-c` 核心文件轉儲
- `-t` CPU時間
- `-s` 堆棧大小
- `-u` 用戶進程數
- `-n` 打開文件數
- `-m` 內存大小

`限制數值`參數爲空時，指令爲查詢相關設定。
`限制數值`參數不爲空時，指令爲設定參數(可取值`unlimited`，表示**不限制**該類文件大小)。

以**核心轉儲**爲例：

- `$ ulimit -c` 查看系統設定的核心轉儲大小
- `$ ulimit -c unlimited` 設置核心轉儲大小爲無限

## 配置文件
通過配置文件`/etc/security/limits.conf`配置相關限制。
`limits.conf`文件每行爲一條配置，依次爲`<domain>`、`<type>`、`<item>`、`<value>`。

- `demain`(域)，域可以是用戶名、用戶組(使用`@`修飾)，或是通配符。
- `type`(類別)，可取值`soft/hard`，代表**軟限制/硬限制**。
- `item`(目標)，爲需要限制的資源類別，可取值`core`(核心轉儲)、`fsize`(文件大小)等，與指令參數對應。
- `value`(值)，指定限制資源的數值。

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

## Core Dump (核心轉儲)
啓用核心轉儲後，則在進程執行異常退出時，會生成包含異常信息的錯誤轉儲文件。
使用gdb可分析轉儲文件：

```
$ gdb [進程文件] [進程核心轉儲]
```

進入gdb shell之後，使用`bt`指令查看調用堆棧。



# fdisk
`fdisk`是Linux命令行下常用的交互式分區工具。

早期的fdisk不能識別`GPT`分區表，劃分GPT分區需要使用`parted`工具。
最近版本的fdisk已經能夠正常識別、顯示與創建GPT分區。

使用fdisk顯示分區信息：

```
# fdisk -l [磁盤路徑]
```

進行具體的磁盤分區操作需要進入fdisk會話：

- `# fdisk` 直接進入fdisk會話，選擇第一塊硬盤爲當前硬盤
- `# fdisk [磁盤路徑]` 進入fdisk會話，並選擇指定硬盤爲當前硬盤

在fdisk會話中，操作指令同樣會以對話的形式引導完成操作，基本指令如下：

- `m` 顯示指令菜單
- `n` 創建分區
- `d` 刪除分區
- `l` 列出已知的分區類型
- `F` 列出未分配的磁盤空間
- `p` 打印分區信息，輸出結果與在命令行中輸入`fdisk -l`相同
- `i` 列出某一個分區的具體信息
- `t` 修改分區類型信息
- `o` 創建DOS分區表
- `g` 創建GPT分區表
- `x` 進入高級功能會話

部分指令詳細介紹：

- `g/G/o/s` 創建分區表

	在會話中使用`g/G/o/s`指令創建不同類型的分區表，常見的分區表爲：

	- `DOS`分區表(使用指令`o`創建，用於MBR舊式BIOS的機器，僅允許4個主分區)
	- `EFI`分區表(使用指令`g`創建，用於EFI新式BIOS的機器，無分區限制)

- `n` 創建分區

	在會話中使用`n`指令進入交互式創建分區的對話：

	```c
	Command (m for help): n
	Partition number (4-128, default 4):
	...
	```

- `t` 修改分區類型

	普通Linux分區類型爲`Linux filesystem`；
	UEFI引導下的ESP分區類型需要爲`EFI System`。

在會話中使用`x`指令後進入高級功能會話，常用指令如下：

- `m` 功能不變，顯示指令菜單
- `n` 修改分區名稱
- `r` 返回主選單

在fdisk會話中進行的操作**不是**立即生效的，退出會話之前需要進行確認：

- `w` 將改動真正寫入硬盤
- `q` 不保存改動退出



# parted
`parted`是Linux下的另一種交互式分區工具，與`fdisk`相比，parted一直支持GPT分區表，
並且在功能選項上更加豐富，但在交互上沒有fdisk便捷。

- `# parted -l` 顯示所有分區信息
- `# parted [磁盤路徑] print` 顯示指定磁盤的分區信息

與fdisk工具類似，執行具體的磁盤分區需要進入parted會話：

```
# parted [磁盤路徑]
```

parted會話中的基本指令如下：

| 會話指令 | 簡介 |
| :- | :- |
| help | 顯示指令列表 |
| help [指令名稱] | 顯示指定指令的用法 |
| select [磁盤路徑] | 切換到指定磁盤 |
| mklabel [分區表類型] | 創建指定類型分區表，常用的分區表類型爲`msdos`和`gpt` |
| mkpart | 交互式創建分區，以會話的形式引導輸入創建分區所需的參數 |
| mkpart [主/擴展分區] [文件系統(可選)] [起始大小] [結束大小] | 創建分區 |
| rm [分區號] | 刪除指定分區 |
| toggle [分區號] [分區標識] | 添加指定分區的分區標誌 |
| set [分區號] [分區標識] on/off | 添加/刪除指定分區的分區標誌 |
| name [分區號] [分區名稱] | 命名指定分區 |
| print | 顯示分區信息 |
| print free | 顯示分區信息，包括磁盤中未被使用的空間 |
| print all | 顯示所有分區信息 |
| quit | 退出parted會話 |

相比fdisk，parted會話中的分區操作會立即執行生效，因此更需小心謹慎。



# LVM
`LVM`是`Logical Volume Manager`(邏輯卷管理)的簡寫，是Linux環境下對磁盤分區進行管理的一種機制。

使用LVM能夠將不同的硬盤上的物理卷(`Physical Volume`，簡稱`PV`)加入卷組(`Volume Group`，簡稱`VG`)。
在卷組中將其劃分爲不同的邏輯卷(`Logical Volume`，簡稱`LV`)，然後在邏輯卷中創建文件系統並進行掛載。

LVM在物理磁盤上提供了一層抽象，解除了分區與物理磁盤的綁定。
LVM中一個邏輯分區在物理結構上可能由多個磁盤組成，添加新的物理磁盤時，邏輯分區無需改變結構/重新掛載即可利用新增物理磁盤的空間實現動態擴容。

## 基本操作
配置LVM的**基本步驟**：

1. 創建硬盤分區
1. 創建物理卷：`# pvcreate [硬盤路徑/分區路徑]`(物理卷可以是整個硬盤或是硬盤中的某個分區)
1. 創建卷組：`# vgcreate [卷組名稱] [需要加入卷組的物理卷分區路徑]`
1. 創建邏輯卷：`# lvcreate -L [分區大小(xxGB/xxMB/...)] -n [邏輯分區名稱] [卷組名稱]`
1. 格式化邏輯分區，掛載使用

## Physical Volume (PV，物理卷)
物理卷`Physical Volume`是在磁盤上**實際存在**的物理分區。
被添加到LVM的物理分區需要擁有`lvm`標識(flag)。

物理卷相關的操作爲`pvXXX`系列指令：

- `# pvcreate [硬盤路徑/物理分區路徑]` 創建物理卷
- `# pvremove [硬盤路徑/物理分區路徑]` 移除物理卷
- `# pvmove [原物理分區路徑] [目標物理分區路徑]` 將原物理卷中的數據轉移到另一物理卷
- `# pvdisplay` 顯示已創建的物理卷

移除一個物理卷需要先將該物理卷從所屬的卷組中移除。
移除物理卷前需要保證沒有數據存儲在該物理卷中，若**要被移除的物理卷**中已有數據，則需要使用`pvmove`指令將該卷中的數據轉移到其它卷。

## Volume Group (VG，卷組)
物理卷需要加入卷組(`Volume Group`)才能被使用。

卷組相關的操作爲`vgXXX`系列指令：

- `# vgcreate [卷組名稱] [物理卷路徑]` 一個卷組至少需要包含一個物理卷，物理卷路徑可爲多個
- `# vgextend [卷組名稱] [物理卷路徑]` 向指定卷組中添加物理卷
- `# vgreduce [卷組名稱] [物理卷路徑]` 從指定卷組中刪除物理卷
- `# vgremove [卷組名稱]` 移除指定卷組
- `# vgdisplay` 顯示所有卷組

## Logical Volume (LV，邏輯卷)
邏輯卷(`Logical Volume`)是`LVM`中實際用於創建文件系統、掛載的分區。
邏輯卷的磁盤路徑爲`/dev/[邏輯卷所屬卷組名稱]/[邏輯卷名稱]`，使用該路徑可以像操作物理磁盤一樣對其進行創建文件系統、掛載等操作。

邏輯卷相關的操作爲`lvXXX`系列指令：

- `# lvcreate -L [分區大小(xxGB/xxMB/...)] -n [邏輯分區路徑] [卷組名稱]` 創建邏輯卷
- `# lvresize -L +/-[分區大小(xxGB/xxMB/...)] [邏輯分區路徑]` 在原先邏輯卷大小的基礎上擴充/縮減指定大小
- `# lvextend -L [分區大小(xxGB/xxMB/...)] [邏輯分區路徑]` 增加邏輯捲到指定大小(分區大小的數值需要大於原先該邏輯分區的大小)
- `# lvreduce -L [分區大小(xxGB/xxMB/...)] [邏輯分區路徑]` 減小邏輯捲到指定大小(分區大小的數值需要小於原先該邏輯分區的大小)
- `# lvremove [邏輯分區名稱]` 移除指定邏輯卷
- `# lvdisplay` 顯示所有邏輯卷

擴展邏輯卷大小無需卸載、重新掛載文件系統。
縮減邏輯卷大小需要重先卸載文件系統，縮減空間後重新掛載。

擴展邏輯卷大小後，對應邏輯卷的文件系統大小並未增大，因此會造成不同指令輸出分區大小不一致的情況：

- `df`指令顯示的是文件系統大小
- `parted`、`fdisk`、`lsblk`、`lvdisplay`等指令顯示的是邏輯分區的大小

根據邏輯卷的文件系統類型，調整對應文件系統的大小：

- `# xfs_growfs [邏輯分區路徑]` 擴展`xfs`文件系統的大小
- `# resize2fs [邏輯分區路徑] [分區大小]` 調整`ext`系列文件系統的大小

## 邏輯卷狀態和塊設備不顯示問題
使用lvdisplay查看邏輯卷狀態時，若邏輯卷`LV Status`顯示`NOT available`，
可使用`vgchange`激活卷組下所有的邏輯卷，使其狀態恢復爲`available`：

```c
# vgchange -a y [卷組名稱]
```

部分狀態爲`NOT available`的邏輯卷對應的塊設備不顯示在`/dev/mapper`和`/dev/[卷組]`路徑下，
可激活卷組後執行`vgmknodes`指令，會創建對應缺失的塊設備文件：

```
# vgmknodes
```



# curl
`curl`是一款功能強大的文件傳輸工具。

基本指令爲：

```
$ curl [目標文件路徑]
```

curl對於獲取的文件會直接以文本的形式輸出在終端上，可以使用`-o`參數導出到文件。
對於一些可能需要驗證用戶權限的協議(如`ftp`)，可以使用`-u`參數添加用戶信息，指令格式如下：

```
$ curl [目標文件路徑] -u [用戶名]:[密碼] -o [輸出文件路徑]
```

## FTP 操作
使用`curl`工具進行`FTP`操作：

- `$ curl ftp://[ip/域名] -u [用戶名]:[密碼]` 列出FTP下的文件、目錄列表
- `$ curl ftp://[用戶名]:[密碼]@[ip/域名]` 列出FTP下的文件、目錄列表(簡化)
- `$ curl ftp://[用戶名]:[密碼]@[ip/域名]/[文件路徑] -o [輸出文件路徑]` 傳輸FTP文件到本地指定路徑
- `$ curl ftp://[用戶名]:[密碼]@[ip/域名] -T [本地文件路徑]` 上傳本地文件到FTP

在上傳/下載時，默認情況下會出現進度提示，可添加`-s`參數取消進度提示。

對於一些複雜的FTP功能，需要直接使用FTP**協議指令**來完成。
在`curl`工具中，使用`-X`參數追加協議指令，命令格式如下：

```
$ curl ftp://[用戶名]:[密碼]@[ip/域名] -X "[FTP協議指令]"
```

常見的FTP協議指令如下：

| 指令 | 指令功能 |
| :- | :- |
| dele [FTP文件路徑] | 刪除FTP內文件 |
| rmd [FTP目錄] | 刪除FTP內目錄 |
| mkd [FTP目錄] | 創建FTP目錄 |
| list [FTP目錄] | 列出FTP目錄 |
| rnfr [FTP文件路徑] | 重命名FTP文件(第一步，指定需要重命名的文件) |
| rnto [FTP文件路徑] | 重命名FTP文件(第二步，指定文件重命名的名稱) |

對於協議指令，`curl`會在終端打印協議指令的執行結果(返回值)，FTP協議指令的常見返回值含義如下：

| 返回值 | 說明 |
| :- | :- |
| 250 | 請求的文件操作正常進行，已完成 |
| 257 | 路徑已創建 |
| 350 | 請求的文件操作在等待更進一步的信息 |
| 421 | 服務不可用，關閉控制連接 |
| 500 | 語法錯誤，無法識別命令(包括命令行過長之類的錯誤) |
| 501 | 參數或變元中有語法錯誤 |
| 502 | 命令還沒有被實現 |
| 503 | 命令的順序不對 |
| 530 | 無法登錄 |
| 550 | 請求的操作無法執行，文件不可用(例如找不到文件，無訪問權) |



# Suspend 和 Hibernate
*Suspend*和*Hibernate*是很容易混淆的兩個概念。

- `Suspend` (**睡眠**)：

	睡眠狀態下，系統將關閉大部分硬件的工作，系統狀態將會被保存在`RAM`中。
	處於睡眠狀態下的計算機將以極低的功耗運轉，但系統仍需要供電，電源指示燈會依舊閃爍。
	現代計算機**進入睡眠狀態/從睡眠狀態喚醒**僅僅需要幾秒時間。

- `Hibernate` (**休眠**)：

	休眠即`Suspend to disk`，系統將完全關閉所有硬件，系統狀態將被保存在`SWAP`中。
	處於休眠狀態下的計算機不需要供電，但系統分區時必須分配並掛載了`SWAP`交換區。
	從休眠狀態下喚醒將從硬盤(`SWAP`)中加載系統狀態。
	對於使用`HDD`的計算機，**進入休眠狀態/從休眠狀態喚醒**需要幾十秒甚至更久，相當於正常開機的速度。



# systemd
`systemd`是Linux下新式的init系統，在各大發行版中逐漸替代了原先`Unix System V`風格的init系統。

systemd的設計理念來自於Apple公司`macOS`中的`launchd`。
傳統的SystemV風格init系統需要一次一個串行地啓動服務進程，
systemd則根據服務進程的依賴關係並行地啓動服務，極大地減少了系統的啓動耗時。

配置文件：

- `/etc/systemd/system.conf` 全局配置文件
- `/etc/systemd/user.conf` 用戶配置文件

## 服務管理
`systemd`提供了統一、完整的服務管理功能：

- `# systemctl status [服務名稱]` 查看指定服務狀態
- `# systemctl start [服務名稱]` 啓動指定服務
- `# systemctl stop [服務名稱]` 停止指定服務
- `# systemctl enable [服務名稱]` 設置指定服務開機自啓動
- `# systemctl disable [服務名稱]` 取消指定服務開機自啓動

`systemd`服務文件通常以`*.service`爲後綴名。

- 系統服務：

	系統服務文件位於路徑`/usr/lib/systemd/system`下。
	啓用、禁用系統服務需要使用`root`權限(查看服務狀態不需要)。

- 用戶服務：

	用戶服務文件位於路徑`/usr/lib/systemd/user`下。
	管理用戶服務不需要以`root`權限執行`systemctl`指令，但需要在指令中添加`--user`參數：

	```
	$ systemctl --user status/start/stop/enable/disable [用戶服務名稱]
	```

## 服務分析
`systemd`提供了一系列工具用於查看查看、分析各類服務狀態。

使用`pstree`指令可以列出本機完整的systemd服務進程樹。

使用`systemctl list`系列指令查看服務狀態：

- `$ systemctl list-units` 列出已加載的服務單元信息
- `$ systemctl list-dependencies` 列出已加載服務單元的依賴關係
- `$ systemctl list-unit-files` 列出已安裝服務單元(所有服務單元)的自啓狀態
- `$ systemctl list-units -t [服務類型]` 查看指定類型的服務信息

使用`systemd-analyze`指令分析系統的啓動性能：

- `$ systemd-analyze` 顯示系統的啓動耗時
- `$ systemd-analyze blame` 列出所有的啓動單元，按照啓動耗時的高低進行排序

## 系統配置
`systemd`還集成了常用的系統配置工具：

- `hostnamectl` 配置主機名稱
- `timedatectl` 時區時間配置
- `localectl` 語言編碼配置
- `networkctl` 網絡配置
- `coredumpctl` 核心轉儲查看工具
- `journalctl` 日誌查看工具



# VTE
`VTE`是`Gnome`項目提供的輕量級終端庫，許多終端軟件使用VTE實現，如`gnome-terminal`、`roxterm`等。
VTE自身亦可做爲獨立的終端軟件使用。

相比其它終端模擬器，VTE提供了豐富的特性和較少的依賴(僅僅依賴`GTK+`)。

VTE當前的主流版本爲基於`GTK+ 2`的`VTE2`和基於`GTK+ 3`的`VTE3`。
在`Arch Linux`的打包中，`VTE2`的指令名稱爲`vte`，`VTE3`的指令名稱爲`vte-2.91`。

## 啓動參數
VTE通過在啓動時添加命令行參數進行設置。

VTE2常見參數如下所示：

- `-g` 設定終端初始大小(行列大小)，格式爲`mxn`
- `-f` 設定終端字體，參數後添加字體名稱
- `-n` 設定終端可回滾的行數，參數後添加回滾行數數值
- `-h` 設定終端色彩
- `-c` 在終端中執行指令
- `-W` 使用`GtkScrolledWindow`做爲終端容器，啓用此參數時使用`-g`參數設定終端大小纔有效
- `-P` 設定終端的滾動條顯示模式，參數可以爲`always`(總是顯示)、`auto`(自動)、`never`(從不顯示)
- `-B` 設定終端背景圖片
- `-S` 設定終端使用的`shell`
- `--reverse` 反轉終端色彩

以`awesomewm`配置中使用的VTE選項爲例：

```
$ vte -W -P never -g 120x40 -f "Monaco 10" -n 5000 --reverse
```

執行結果爲打開大小爲`120`列`40`行的`VTE2`終端，終端回滾`5000`行，不顯示滾動條，反轉配色。



# apt/dpkg
`Debian`系列發行版使用`deb`格式作爲軟件包的打包、分發格式。

`apt`是Debian系列發行版的前端包管理工具，用於deb處理軟件包之間的依賴關係。
主要功能如下：

- 在鏡像源中搜索、查找需要的軟件包。
- 計算軟件包的依賴。
- 系統更新。
- 查看指定軟件包的狀態。
- 變更已安裝軟件包的狀態。
- 安裝、卸載軟件包(通過dpkg)。

apt的常用指令：

```c
// 更新軟件源
# apt-get update
// 更新無依賴變化的軟件包
# apt-get upgrade
// 更新所有軟件包
# apt-get dist-upgrade

// 安裝/卸載軟件包
# apt-get install/remove [包名]
// 卸載軟件包時同時刪除配置
# apt-get remove --purge [包名]

// Ubuntu 14.04 之後可使用更簡單的命令形式
# apt update
# apt install/remove [包名]
# apt purge [包名]
# apt upgrade/dist-upgrade

// 清理無用依賴
# apt-get autoremove
# apt-get autoremove --purge

// 查看/搜索指定包
# apt-cache show/search	[包名]

// 將某個包標記爲自動/手動安裝
# apt-mask auto/manual [包名]
// 顯示手動安裝/自動安裝的包
$ apt-mask showauto/showmanaul
```

`dpkg`是與apt前端搭配的後端包管理工具，核心功能是管理deb軟件包的資源。
主要功能如下：

- 安裝軟件包，將軟件包解壓，釋放資源到系統對應路徑。
- 卸載軟件包，移除軟件包在系統中安裝的文件、配置。
- 列出、查看、搜索軟件包內的資源。
- 查看指定軟件包的狀態。
- 變更已安裝軟件包的狀態。

dpkg的常用指令：

```c
// 查詢文件屬於哪個包
$ dpkg-query -S [文件名]

// 安裝一個deb包
# dpkg -i [包名]

// 列出所有已安裝包的狀態信息
$ dpkg -l
// 列出指定包名的包的狀態信息
$ dpkg -l [包名]
// 根據包狀態篩選出有殘餘配置文件的包
$ dpkg -l [包名] | grep '^rc'

// 查看指定包的詳細描述信息
$ dpkg -s [包名]
// 列出指定包內包含的文件
$ dpkg -L [包名]
```

## 源配置
使用`apt`工具需要正確配置鏡像源地址，配置文件爲`/etc/apt/sources.list`。

`Debian`系列發行版軟件源格式爲：

```sh
# 二進制包
deb [軟件源地址] [版本號] [倉庫類型]

# 源碼包
deb-src [軟件源地址] [版本號] [倉庫類型]
```

其中：

- `軟件源地址` 爲有效的`URL`，可以是某個提供鏡像源服務的站點地址，也可以是本地源路徑
- `版本號` 爲發行版的版本代號，一行只能填寫一個版本號
- `倉庫類型` 爲按照授權類型劃分的倉庫類別，可以一行同時添加多個倉庫類型

`Ubuntu`與`Debian`的版本號、倉庫類型分類完全不同。

## Debian 源
`Debian`版本號有兩類：

1. 固定版本號，按照穩定程度分爲`stable`、`testing`、`unstable`、`experimental`。
1. 版本代號。

兩類作用相同，固定版本號會指向某個版本代號；
隨着開發進度的變化，固定版本號實際指向的版本代號會發生變化：

- 當前(`2017-5-11`)Debian的最新穩定版爲`Debian 8`，版本代號爲`jessie`，則使用固定版本號`stable`指向的實際版本號即爲`jessie`。
- 當前處於開發狀態的版本爲`Debian 9`，版本代號爲`stretch`，使用固定版本號`testing`則實際指向處於開發狀態的版本代號`stretch`。

版本代號後是**版本倉庫**，Debian的版本倉庫有：

- `[版本號]-updates` 提供常規更新
- `[版本號]-proposed-updates` 提供處於測試階段的更新(不建議啓用)
- `[版本號]-backports` 提供軟件的`testing`功能性更新

版本倉庫後需要指定啓用的倉庫類型，Debian倉庫類型主要有三類：

- `main` 主要倉庫，符合`DFSG`定義的開源軟件
- `contrib` 包含依賴於非自由軟件的開源軟件
- `non-free` 非自由軟件

以**中科大鏡像源**爲例，`Debian Stable`的`sources.list`配置：

```sh
deb https://mirrors.ustc.edu.cn/debian/ stable main contrib non-free
deb https://mirrors.ustc.edu.cn/debian/ stable-updates main contrib non-free
deb https://mirrors.ustc.edu.cn/debian/ stable-backports main contrib non-free
```

## Ubuntu 源
`Ubuntu`沒有固定版本號，需要使用發行版本號，主要的`LTS`版本的版本代號：

| 版本 | 版本代號 |
| :-: | :-: |
| `12.04 LTS` | `precise` |
| `14.04 LTS` | `trusty` |
| `16.04 LTS` | `xenial` |

Ubuntu**版本倉庫**：

- `[版本號]-security` 提供重要的安全性更新(漏洞修復)
- `[版本號]-updates` 提供建議的更新
- `[版本號]-backports` 提供功能性更新
- `[版本號]-proposed` 提供處於測試階段的`updates`更新(不建議啓用)

Ubuntu**倉庫類別**：

- `main` 主要倉庫，完全的開源軟件
- `restricted` 不完全的開源軟件
- `universe` 社區支持、維護的軟件
- `muitiverse` 非開源軟件
- `partner` 閉源商業軟件，該倉庫僅有官方源可用

以**中科大鏡像源**爲例，`Ubuntu 16.04 LTS`的`sources.list`配置：

```
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial main restricted universe muitiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-security main restricted universe muitiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-updates main restricted universe muitiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-backports main restricted universe muitiverse

deb http://archive.canonical.com/ubuntu/ xenial partner
```

## apt-mirror
`apt-mirror`是Debian系列發行版中用於製作**本地源**的工具。

### 本地源配置
`apt-mirror`的配置文件爲`/etc/apt/mirror.list`。若無特殊需求可直接使用默認配置。

默認配置下，鏡像會被同步到本地的`/var/spool/apt-mirror`路徑下。
修改`base_path`配置項可以指定本地鏡像的存儲位置。修改源地址可執行用於同步的遠程鏡像源。

以**中科大鏡像源**爲例，同步到本地的`~/Public/Mirrors`路徑下，配置：

```sh
set base_path /home/Xxx/Public/Mirrors

deb http://mirrors.ustc.edu.cn/ubuntu xenial main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu xenial-security main restricted universe multiverse
deb http://mirrors.ustc.edu.cn/ubuntu xenial-updates main restricted universe multiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-backports main restricted universe muitiverse
```

### 使用本地源
若僅需要本機使用本地源，可以直接使用`file:///...`訪問本機的源路徑。

`sources.list`配置：

```sh
deb file:///home/Xxx/Public/Mirrors/mirror/ubuntu xenial main restricted universe multiverse
deb file:///home/Xxx/Public/Mirrors/mirror/ubuntu xenial-security main restricted universe multiverse
deb file:///home/Xxx/Public/Mirrors/mirror/ubuntu xenial-updates main restricted universe multiverse
deb file:///home/Xxx/Public/Mirrors/mirror/ubuntu xenial-backports main restricted universe muitiverse
```



# 常見問題記錄
記錄各類發行版使用中可能會遇到的問題。

## Ubuntu
記錄Ubuntu發行版中遇到的問題。

### invoke-rc.d: initscript Xxxx, action "stop" failed.
問題描述：<br>
卸載部分軟件包時出現錯誤，無法正常卸載：

```
invoke-rc.d: could not determine current runlevel
 * ...
invoke-rc.d: initscript Xxxx, action "stop" failed.
dpkg: error processing package Xxxx (--remove):
 installed Xxxx package pre-removal script subprocess returned error exit status 1
Errors were encountered while processing:
 Xxxx
```

問題分析：<br>
卸載部分在`/etc/init.d`下注冊了服務的軟件包時，卸載腳本會嘗試執行`invoke-rc.d`指令，調用對應的服務腳本指令關閉服務。
在部分特殊的Linux環境下(如`WSL`、`Docker`)，服務腳本可能會執行失敗，腳本執行失敗導致卸載操作錯誤退出。

解決方法：<br>
修改`/etc/init.d`對應服務的腳本文件，在腳本頂部添加`exit 0`，讓腳本文件的實際邏輯不執行直接正常退出。
