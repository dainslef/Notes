<!-- TOC -->

- [Windows CMD](#windows-cmd)
	- [文件/目錄鏈接](#文件目錄鏈接)
	- [Windows系統引導](#windows系統引導)
	- [Windows常見問題記錄](#windows常見問題記錄)
		- [Reply from ::1: time<1ms](#reply-from-1-time1ms)
- [常用Unix工具指令](#常用unix工具指令)
	- [grep](#grep)
	- [find](#find)
	- [tee](#tee)
	- [進程管理](#進程管理)
	- [日誌記錄](#日誌記錄)
- [PulseAudio](#pulseaudio)
- [用戶管理](#用戶管理)
- [setuid/setgid/sticky](#setuidsetgidsticky)
- [FTP (File Transfer Protocol)](#ftp-file-transfer-protocol)
	- [連接服務器](#連接服務器)
	- [常用指令](#常用指令)
- [SSH (Secure Shell)](#ssh-secure-shell)
	- [遠程登錄](#遠程登錄)
	- [SSH 配置](#ssh-配置)
	- [配置免密登陸](#配置免密登陸)
- [路由轉發](#路由轉發)
	- [追蹤路由](#追蹤路由)
- [Linux引導配置](#linux引導配置)
	- [GNU GRUB](#gnu-grub)
		- [GRUB安裝與配置](#grub安裝與配置)
		- [安裝GRUB引導器](#安裝grub引導器)
		- [修復GRUB引導](#修復grub引導)
	- [systemd-boot](#systemd-boot)
- [壓縮/解壓](#壓縮解壓)
	- [7z](#7z)
- [ulimit](#ulimit)
	- [配置文件](#配置文件)
	- [prlimit](#prlimit)
- [Core Dump (核心轉儲)](#core-dump-核心轉儲)
- [文件系統](#文件系統)
	- [fdisk](#fdisk)
	- [parted](#parted)
	- [flock](#flock)
- [LVM (Logical Volume Manager)](#lvm-logical-volume-manager)
	- [基本操作](#基本操作)
	- [Physical Volume (PV，物理卷)](#physical-volume-pv物理卷)
	- [Volume Group (VG，卷組)](#volume-group-vg卷組)
	- [Logical Volume (LV，邏輯卷)](#logical-volume-lv邏輯卷)
	- [邏輯卷狀態和塊設備不顯示問題](#邏輯卷狀態和塊設備不顯示問題)
- [NTP (Network Time Protocol)](#ntp-network-time-protocol)
	- [NTP 服務配置](#ntp-服務配置)
		- [NTP Client 配置](#ntp-client-配置)
		- [NTP Server 配置](#ntp-server-配置)
	- [NTP 管理指令](#ntp-管理指令)
	- [chrony](#chrony)
- [curl](#curl)
	- [HTTP請求](#http請求)
		- [HTTP文件下載](#http文件下載)
	- [用戶認證](#用戶認證)
	- [FTP 操作](#ftp-操作)
- [Suspend 和 Hibernate](#suspend-和-hibernate)
- [systemd](#systemd)
	- [systemd服務管理](#systemd服務管理)
	- [systemd服務分析](#systemd服務分析)
	- [系統管理](#系統管理)
		- [loginctl](#loginctl)
- [網絡](#網絡)
	- [net-tools & iproute2](#net-tools--iproute2)
	- [netstat & ss](#netstat--ss)
	- [mii-tool & ethtool](#mii-tool--ethtool)
	- [NetworkManager](#networkmanager)
	- [tcpdump](#tcpdump)
	- [Netcat (nc)](#netcat-nc)
		- [客戶端/服務端模式](#客戶端服務端模式)
		- [數據傳送](#數據傳送)
- [性能監控與測試](#性能監控與測試)
	- [Load Averages](#load-averages)
	- [ps](#ps)
	- [top](#top)
	- [iftop](#iftop)
	- [sysstat](#sysstat)
		- [pidstat](#pidstat)
		- [iostat](#iostat)
	- [HTTP壓測工具](#http壓測工具)
- [VTE](#vte)
	- [VTE2](#vte2)
	- [VTE3](#vte3)
	- [複製粘貼快捷鍵](#複製粘貼快捷鍵)
- [字體配置](#字體配置)
	- [管理字體](#管理字體)
	- [字體相關路徑](#字體相關路徑)
	- [字體渲染問題](#字體渲染問題)
- [字符串模板](#字符串模板)
	- [envsubst](#envsubst)
	- [sed](#sed)
- [apt/dpkg](#aptdpkg)
	- [apt](#apt)
		- [apt-file](#apt-file)
		- [add-apt-repository](#add-apt-repository)
	- [dpkg](#dpkg)
	- [deb打包(Binary packages)](#deb打包binary-packages)
		- [debconf](#debconf)
		- [dpkg-divert](#dpkg-divert)
	- [源配置](#源配置)
		- [Debian 源](#debian-源)
		- [Ubuntu 源](#ubuntu-源)
	- [apt-mirror](#apt-mirror)
		- [本地源配置](#本地源配置)
		- [使用本地源](#使用本地源)
- [OpenCC](#opencc)
	- [命令行工具opencc](#命令行工具opencc)
- [Chrome OS](#chrome-os)
	- [安裝 Chrome OS](#安裝-chrome-os)
	- [Linux容器問題](#linux容器問題)
- [Linux常見問題記錄](#linux常見問題記錄)
	- [sshd: pam_limits(sshd:session): error parsing the configuration file: '/etc/security/limits.conf'](#sshd-pam_limitssshdsession-error-parsing-the-configuration-file-etcsecuritylimitsconf)
	- [Ubuntu](#ubuntu)
		- [invoke-rc.d: initscript Xxxx, action "stop" failed.](#invoke-rcd-initscript-xxxx-action-stop-failed)
	- [CentOS](#centos)
		- [iptable/firewalld](#iptablefirewalld)
		- [SELinux](#selinux)
		- [grub2-install: error: /usr/lib/grub/x86_64-efi/modinfo.sh doesn't exist. Please specify --target or --directory.](#grub2-install-error-usrlibgrubx86_64-efimodinfosh-doesnt-exist-please-specify---target-or---directory)
		- [http://.../repodata/repomd.xml: [Errno 14] HTTP Error 404 - Not Found Trying other mirror.](#httprepodatarepomdxml-errno-14-http-error-404---not-found-trying-other-mirror)
		- [官方ISO在OpenStack中無法識別鏡像](#官方iso在openstack中無法識別鏡像)

<!-- /TOC -->



# Windows CMD
Windows系統提供的命令行執行DOS系統工具指令。

文件操作相關：

```c
// 查看DOS指令的使用幫助
> [指令名稱] /?

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
// 查看文件
> type

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

語言包管理：

```c
> lpksetup

// 刪除語言包
> lpksetup /u
```

服務管理：

```c
// 啟動/停止服務
> sc start [服務名稱]
> sc stop [服務名稱]

// 查詢服務
> sc query // 查詢指定服務
> sc query [服務名稱] // 查詢所有服務
> sc qc [服務名稱] // 查詢服務配置信息

// 創建/刪除服務
> sc create [服務名稱] binPath=[指令]
> sc delete [服務名稱]
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

## Windows系統引導
標準的UEFI引導Windows系統通常包括以下分區：

- ESR (EFI system partition，通常為FAT文件系統)
- MSR (Microsoft Reserved Partition，通常為NTFS文件系統)
- Windows系統分區

其中，ESP分區存放引導器，Windows引導器路徑為`\EFI\MICROSOFT\BOOT\`；
MSR分區可以不分配，但每次重裝系統或Windows大版本更新都會重新自動創建。

BCDBoot是微軟官方提供的引導配置工具，主要有以下功能：

- 在新安裝的Windows鏡像后添加啓動文件
- 為電腦設置從包含Windows鏡像的虛擬硬盤( virtual hard disk, VHD)中啓動
- 修復系統分區
- 在安裝了雙系統的電腦中設置和更新啓動菜單

詳細内容可查看微軟[官方文檔](https://docs.microsoft.com/en-us/windows-hardware/manufacture/desktop/bcdboot-command-line-options-techref-di)。

指令格式：

```
> bcdboot <source> [/l <locale>] [/s <volume-letter> [/f <firmware type>]] [/v] [/m [{OS Loader GUID}]] [/addlast or /p] [/d] [/c]
```

假設Windows系統分區盤符為`C:\`，ESP分區盤符為`H:\`，則將引導器安裝到ESP分區的指令為：

```
> bcdboot c:\windows /s h: /f UEFI
```

使用`/v`參數可以顯示指令執行的詳情，在某些執行錯誤的情況下，可以展示更詳細的錯誤原因。

## Windows常見問題記錄
記錄Windows中常見問題的解決方案。

### Reply from ::1: time<1ms
問題描述：<br>
ping本機(`localhost`)時，出現如下輸出：

```
> ping localhost

Pinging mypc [::1] with 32 bytes of data:

Reply from ::1: time<1ms
Reply from ::1: time<1ms
Reply from ::1: time<1ms
Reply from ::1: time<1ms

Ping statistics for ::1:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),
Approximate round trip times in milli-seconds:
    Minimum = 0ms, Maximum = 0ms, Average = 0ms
```

向`::1`地址而非常規的`127.0.0.1`發起請求。

問題分析：<br>
`::1`是IPv6協議的默認本機地址，類似IPv4下的`127.0.0.1`，系統處在無有效IPv6網絡的環境下，ping本機出現回環。

解決方案：<br>
可依次嘗試以下解決方案：

1. 在控制面版中禁用對應網卡的IPv6協議(`Control Panel\Network and Internet\Network Connections`)。
1. 參考[微軟官方文檔](https://support.microsoft.com/en-us/help/929852/guidance-for-configuring-ipv6-in-windows-for-advanced-users)，
	從注冊表中禁用或優先選擇IPv4網絡：

	```c
	> reg add "HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\Tcpip6\Parameters" /v DisabledComponents /t REG_DWORD /d <value> /f
	```

	常用的取值及含義：

	| 值 | 含義 |
	| :- | :- |
	| 0x20 | Prefer IPv4 over IPv6 |
	| 0xff | Disable IPv6 |

1. 查看IPv6路由表：

	```c
	> netsh interface ipv6 show route
	```

	移除`::1`地址相關的路由：

	```c
	> netsh interface ipv6 delete route "route..."
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

按照文件`inode`查找文件，可查詢一個inode對應的多個硬鏈接文件：

```c
$ ls -i // 查看文件inode
$ find [路徑] -inum [inode]
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

## tee
`tee`用於將標準輸入拷貝到標準輸出中，同時寫入一個或**多個**文件，常用於搭配管道操作。

指令語法：

```c
$ tee [-ai] [file ...]
```

參數說明：

- `-a` 默認寫入文件時使用重寫方式，使用該參數則變為追加新增內容到文件末尾
- `-i` 執行該指令時忽略SIGINT信號

使用實例：

```c
// 將字符 abcd 寫入test1.txt,test2.txt兩個文件中
$ echo abcd | tee test1.txt test2.txt
$ cat test1.txt
abcd
$ cat test2.txt
abcd
// 以追加模式增加文本內容
$ echo cdef | tee -a test1.txt
$ cat test1.txt
abcd
cdef
```

## 進程管理
`ps`指令用於查看進程狀態：

```html
$ ps u -p [pid] <!-- 打印指定 pid 進程信息詳情 -->
$ ps au <!-- 打印當前所有進程信息詳情 -->
$ ps ux <!-- 打印所有進程信息詳情 -->
$ ps -o cmd,user,stat,pid,ppid,pgid,sid,tpgid,tty <!-- 輸出指定內容的進程信息 -->
```

`kill`指令向進程發送信號：

```html
# kill [pid] <!-- 向進程發送信號，默認發送的信號為 TERM(終止信號) -->
# kill -9 [pid] <!-- 強制殺死進程(發送SIGKILL信號，該信號不可被忽略) -->
# kill -[sig_num] [pid] <!-- 向指定進程發送指定編號的信號 -->
# kill -s [sig_name] [pid] <!-- 向指定進程發送指定名稱的信號 -->
$ kill -l <!-- 列出系統支持的信號 -->
```

除了使用pid的kill指令外，Linux和macOS(BSD)都支持使用進程名稱的`pkill/killall`，
指令語法與kill指令類似：

```
# killall [process_name]
# killall -9 [process_name]
# killall -[sig_num] [process_name]

# pkill [process_name]
# pkill -9 [process_name]
# pkill -[sig_num] [process_name]
```

Linux和macOS(BSD)都提供了`pgrep`指令用於根據進程名稱查詢pid的功能，
Linux的`sysvinit-tools`還提供了`pidof`工具，功能與pgrep類似：

```html
$ pgrep [process_name] <!-- 查詢指定進程名稱的pid -->
$ pgrep -l [process_name] <!-- 查詢指定進程的pid，同時輸出進程名稱 -->
$ pidof [process_name]
```

pidof/pgrep指令與kill指令組合，可實現類似pkill/killall指令的效果：

```
# kill -9 $(pidof [process_name])
# kill -9 $(pgrep [process_name])
```

pidof/pgrep等指令功能可使用管道組合指令模擬：

```
$ ps A | grep [process_name] | awk '{print $1}'
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
# useradd [用戶名] -m
// 創建用戶同時指定密碼
# useradd [用戶名] -p [密碼]
// 創建用戶時指定默認用戶組(默認會創建用戶名同名用戶組)
# useradd [用戶名] -g [用戶組]
// 創建用戶時指定默認Shell
# useradd [用戶名] -s [Shell路徑]

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



# setuid/setgid/sticky
Unix系統中擁有三類特殊權限標誌：

| 權限標誌 | 含義(對可執行文件使用) | 含義(對目錄使用) |
| :- | :- | :- |
| s(setuid) | 使文件在執行階段具有文件所有者的權限 | 在多數Unix實現(包括Linux)下，對目錄設置setuid會被忽略 |
| s(setgid) | 使文件在執行階段具有文件所屬組的權限 | 使目錄下的文件都具有和該目錄所屬組相同的權限 |
| t(sticky) | 禁止文件被所屬用戶外的其它用戶刪除(不受寫權限約束，對root用戶無效) | 在Linux/macOS上均被忽略 |

使用8進制數值表示文件權限時，這些特殊權限佔有一組獨立的8進制位(位於傳統權限標誌位**之前**)。
如傳統文件的權限爲`777`，添加了特殊權限後使用`?777`表示，`?`即爲特殊權限的啓用情況。

特殊權限的三個二進制位含義：

```
4 - 2 - 1
```

| 數值 | 含義 |
| :- | :- |
| 4(高位) | 高位使用字母s，表示setuid |
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



# FTP (File Transfer Protocol)
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



# SSH (Secure Shell)
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

## SSH 配置
SSH服務相關配置文件位於`/etc/ssh`路徑下：

- `/etc/ssh/ssh_config` ssh指令使用的配置
- `/etc/ssh/sshd_config` SSH服務使用的配置

常用SSH服務配置：

- `PermitRootLogin`

	配置SSH服務是否允許root登陸。

	| 配置值 | 取值含義 |
	| :- | :- |
	| yes(默認) | 允許root用戶登陸 |
	| no | 不允許root用戶登陸 |
	| without-password | 可登陸root用戶，但不能以密碼驗證的方式登陸(可用key驗證) |
	| forced-commands-only | 可登陸root用戶，但登陸後僅能執行指令後退出，不能交互 |

- `UseDNS`

	配置是否啓用DNS PTR。
	動態IP通常不會有PTR記錄，開啓DNS PTR有時導致SSH登陸過慢。

	| 配置值 | 取值含義 |
	| :- | :- |
	| yes | 開啓 |
	| no | 關閉 |

## 配置免密登陸
默認配置下，登陸SSH需要密碼，當部署一些依賴SSH協議的分佈式服務時(如`Hadoop`、`Zookeeper`、`Kafka`等)，
需要配置免密登陸。

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
- 文件權限為`600`，權限不正確會導致其它機器的免密登錄失效。

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

免密登錄失敗可查看相關日誌信息：

```
/var/log/secure
/var/log/audit/audit.log
```

或使用`ssh -v/-vv/-vvv`在執行登錄指令時輸出額外的日誌信息。



# 路由轉發
Linux具備路由轉發功能，作為路由器使用，在proc文件系統中查看系統路由功能是否開啟：

```c
// 值為0路由轉發功能處於關閉狀態，值為1時開啟
$ cat /proc/sys/net/ipv4/ip_forward
```

臨時開啟路由轉發功能可直接對該文件賦值：

```
# echo 1 > /proc/sys/net/ipv4/ip_forward
```

通過編輯配置`/etc/sysctl.cnf`可永久開啟路由轉發功能：

```
# Kernel sysctl configuration file for ...
#
# For binary values, 0 is disabled, 1 is enabled.  See sysctl(8) and
# sysctl.conf(5) for more details.

# Controls IP packet forwarding
net.ipv4.ip_forward = 1
# Controls source route verification
net.ipv4.conf.default.rp_filter = 1
```

## 追蹤路由
`traceroute`是傳統Unix使用的路由追蹤工具，在Linux、macOS、BSD上均可使用。

```
$ traceroute www.baidu.com
traceroute: Warning: www.baidu.com has multiple addresses; using 39.156.66.14
traceroute to www.a.shifen.com (39.156.66.14), 64 hops max, 52 byte packets
 1  172.20.10.1 (172.20.10.1)  2.899 ms  6.245 ms  4.776 ms
 2  * * *
 3  192.168.26.105 (192.168.26.105)  29.399 ms  67.376 ms  40.647 ms
 4  * * *
 5  183.203.61.233 (183.203.61.233)  28.742 ms  29.355 ms  24.181 ms
 6  221.183.47.225 (221.183.47.225)  42.761 ms  25.997 ms  28.628 ms
 7  221.183.37.249 (221.183.37.249)  35.779 ms  40.650 ms  49.872 ms
 8  * 221.183.53.182 (221.183.53.182)  37.733 ms *
 9  * * *
10  39.156.27.5 (39.156.27.5)  79.128 ms
    39.156.67.97 (39.156.67.97)  40.540 ms
    39.156.27.5 (39.156.27.5)  44.496 ms
11  * * *
```

Linux系統下iputils工具鏈還提供了`tracepath`工具作為traceroute的替代品，相比traceroute，
tracepath的無須root權限，擁有更簡單的命令行參數。

在Windows系統下，使用`tracert`工具追蹤路由，功能與traceroute類似。

```
C:\Windows\system32>tracert www.baidu.com

Tracing route to www.a.shifen.com [39.156.66.14]
over a maximum of 30 hops:

  1    <1 ms    <1 ms     1 ms  10.0.2.2
  2     6 ms     2 ms     4 ms  172.20.10.1
  3     *        *        *     Request timed out.
  4     *       73 ms    35 ms  192.168.26.105
  5     *        *        *     Request timed out.
  6    25 ms    34 ms    21 ms  183.203.61.233
  7    25 ms    31 ms     *     221.183.47.225
  8    38 ms    56 ms    60 ms  221.183.37.249
  9     *        *        *     Request timed out.
 10    43 ms    50 ms    38 ms  39.156.27.5
 11    47 ms    59 ms    91 ms  39.156.67.29
 12     *        *        *     Request timed out.
 13     *        *        *     Request timed out.
 14     *        *        *     Request timed out.
 15     *        *        *     Request timed out.
 16    59 ms    42 ms    83 ms  39.156.66.14

Trace complete.
```



# Linux引導配置
Linux下存在多種引導器，從早期的LILO、到主流的GRUB，以及較新的systemd-boot等。

## GNU GRUB
`GRUB`(`GRand Unified Bootloader`)是現代Linux的標準啓動管理器，是`LILO`(`Linux Loader`)的替代品。

GRUB支持多重引導，除了Linux，也能用於引導`Windows`、`FreeBSD`等其它現代操作系統。
GRUB在較新版本中提供了對`UEFI BIOS`新型固件的支持。

早期版本的GRUB(`i.e. version 0.9x`)現在被稱爲`GRUB Legacy`，已停止開發。
GRUB現在的主要版本爲`GRUB 2`。

### GRUB安裝與配置
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

### 安裝GRUB引導器
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

### 修復GRUB引導
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

## systemd-boot
`systemd-boot`最初名為`gummiboot`，相比傳統的GRUB，設計上更簡單，僅支持UEFI設備。
通常發行版的`systemd`軟件包中已經包含了該部分。

systemd-boot支持各類EFI執行文件，如Linux kernel EFISTUB、UEFI shell、GRUB、或Windows Boot Manager。

systemd-boot提供了`bootctl`工具管理EFI引導：

```html
# bootctl install/update
```

使用bootctl安裝引導器後，ESP分區下目錄結構為：

```
|- EFI
|  |- systemd
|  |  |- systemd-bootx64.efi
|  |
|  |- Microsoft
|  |  |
|  |  ...
|  |
|  |- Linux
|     |
|     ...
|
|- loader
   |- entries
   |  |- xxx-01.conf
   |  |- xxx-02.conf
   |  |- ...
   |
   |- loader.conf
```

bootctl安裝後會創建`$ESP/loader`、`$ESP/EFI/systemd`等路徑，
將systemd-boot引導器安裝到`$ESP/EFI/systemd/systemd-bootx64.efi`路徑，
引導配置存放在`$ESP/loader/entries`路徑下。
systemd-boot會加載`$ESP/loader/loader.conf`作為默認配置，
在loader.conf中，選擇加載其它`$ESP/loader/entries`路徑下的配置作為默認配置，
以及調整其它引導相關配置（如引導介面的等待時間）。

早期ESP分區默認掛載位置為`/boot/efi`，
但對於使用systemd-boot的場景推薦直接將ESP分區掛載到`/boot`路徑下。
以ArchLinux為例，系統默認會將內核文件安裝到/boot路徑下，
使用/boot路徑作為ESP路徑便於編寫systemd-boot引導配置。



# 壓縮/解壓
Unix系統中傳統的檔案文件格式爲`tar archives`，可將多個文件、目錄下的資源打包到一個tar包中。
使用tar指令創建tar包，tar包經過壓縮後得到tar.gz(gzip)、tar.bz2(bzip2)等格式。

`tar`指令常見用法：

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

```c
// 查看系統設定的核心轉儲大小
$ ulimit -c

// 設置核心轉儲大小爲無限
$ ulimit -c unlimited
```

系統限制分為**軟限制**和**硬限制**，ulimit指令默認顯示和修改的是**軟限制**。
要顯示和修改**硬限制**，需要額外添加`-H`參數。

同樣以**核心轉儲**為例：

```c
// 查看系統設定的核心轉儲大小(硬限制)
$ ulimit -cH

// 設置核心轉儲大小爲無限(硬限制)
$ ulimit -cH unlimited
```

使用ulimit默認修改的配置僅對當前會話有效，退出當前會話後，配置重新變為默認值。
要使修改的系統限制永久生效，需要修改`/etc/security/limits.conf`文件中配置。

## 配置文件
通過配置文件`/etc/security/limits.conf`配置相關限制。
`limits.conf`文件每行爲一條配置，依次爲`<domain>`、`<type>`、`<item>`、`<value>`。

- `demain`(域)，域可以是用戶名、用戶組(使用`@`修飾)，或是通配符。
- `type`(類別)，可取值`soft/hard`，代表**軟限制/硬限制**，超過軟限制後會得到警告；超過硬限制後會直接失敗。
- `item`(目標)，爲需要限制的資源類別，可取值`core`(核心轉儲)、`fsize`(文件大小)等，與指令參數對應。
- `value`(值)，指定限制資源的數值。

詳細的item列表以及對應說明：

| item | 說明 |
| :- | :- |
| core | limits the core file size (KB) |
| data | max data size (KB) |
| fsize | maximum filesize (KB) |
| memlock | max locked-in-memory address space (KB) |
| nofile | max number of open files |
| rss | max resident set size (KB) |
| stack | max stack size (KB) |
| cpu | max CPU time (MIN) |
| nproc | max number of processes |
| as | address space limit (KB) |
| maxlogins | max number of logins for this user |
| maxsyslogins | max number of logins on the system |
| priority | the priority to run user process with |
| locks | max number of file locks the user can hold |
| sigpending | max number of pending signals |
| msgqueue | max memory used by POSIX message queues (bytes) |
| nice | max nice priority allowed to raise to values: [-20, 19] |
| rtprio | max realtime priority |
| chroot | change root to directory (Debian-specific) |

規則示例：

```
<domain>      <type>  <item>         <value>

*               soft    core            0
root            hard    core            100000
*               hard    rss             10000
@student        hard    nproc           20
@faculty        soft    nproc           20
@faculty        hard    nproc           50
ftp             hard    nproc           0
ftp             -       chroot          /ftp
@student        -       maxlogins       4
```

與常規Unix配置類似，配置中使用`#`註釋內容。

添加配置時需要保證配置內容無衝突，例如，soft資源限制應小於等於hard限制。
錯誤的配置可能導致SSH服務無法被登陸，甚至本地帳戶無法登陸。

修改limits.conf文件後不必重啓服務器，僅需要關閉當前開啟的會話(當前以開啟的會話依舊會使用之前資源限制配置)，
關閉會話後重新登錄系統新的資源限制便會生效(對於普通進程而言)；
若進程使用了Linux PAM(如SSH)，則需要重啟機器生效。

## prlimit
使用`prlimit`可以查看和動態修改運行中的進程的資源限制：

```c
// 查看進程的全部資源限制
$ prlimit -p [進程號]

// 設置進程的資源限制
$ prlimit -p [進程號] --[類別=軟限制數值:硬限制數值]
```



# Core Dump (核心轉儲)
啓用核心轉儲後，則在進程執行異常退出時，會生成包含異常信息的錯誤轉儲文件。
使用gdb可分析轉儲文件：

```
$ gdb [進程文件] [進程核心轉儲]
```

進入gdb shell之後，使用`bt`指令查看調用堆棧。



# 文件系統
Unix系統遵循[`Everything is a file`](https://en.wikipedia.org/wiki/Everything_is_a_file)的設計哲學，
任何資源、硬件在系統中均抽象為文件。

硬盤在Linux中以塊設備(block)形式呈現，位於`/dev`路徑下，
通常名稱為`sda`(塊設備路徑`/dev/sda`)，存在多塊磁盤時，則按照次序命名為`sdb,sdc,sdd,...`，依此類推。
每塊磁盤下的分區同樣會生成塊設備，按照分區編號命名為`sda1,sda2,sda3,...`，依此類推。

磁盤塊設備根據發行版/平台環境差異，也可能使用`vda`等其它名稱。

使用`lsblk`可查看當前系統的磁盤分區結構：

```html
<!-- 查看磁盤分區 -->
$ lsblk
NAME   MAJ:MIN RM  SIZE RO TYPE MOUNTPOINT
vda    253:0    0  100G  0 disk
├─vda1 253:1    0   10G  0 part [SWAP]
├─vda2 253:2    0   40G  0 part /
└─vda3 253:3    0   50G  0 part /opt

<!--
上述輸出信息展示系統中存在一塊100GB磁盤/dev/vda，包含三個分區：
vda1 SWAP交換區 10GB
vda2 根分區 40GB
vda3 掛載點/opt 50GB
-->

<!-- 通過file指令查看磁盤信息 -->
$ file /dev/vda
/dev/vda: block special (253/0) <!-- 類型為塊設備 -->
# file -s /dev/vda <!-- 使用 -s 參數展示塊設備的信息 -->
/dev/vda: DOS/MBR boot sector <!-- 結果為MBR分區表 -->
# file -s /dev/vda2 <!-- 展示分區信息，包含文件系統類型、UUID等 -->
/dev/vda2: Linux rev 1.0 ext4 filesystem data, UUID=cb65c6f7-f958-4b48-be0f-0cec86767ad6, volume name "SYSROOT" (needs journal recovery) (extents) (large files) (huge files)
```

查看分區信息的相關指令：

```html
<!-- 查看文件inode -->
$ ls -i

<!-- 查看分區UUID -->
$ lsblk -f
$ blkid

<!-- 顯示已掛載分區的信息 -->
$ mount
<!-- 顯示指定分區的信息(分區大小，分區類型等) -->
# file -s [塊設備]

<!-- 顯示已掛載的文件系統 -->
# df
<!-- 以合適的單位顯示文件系統大小 -->
# df -h
<!-- 顯示文件系統類型 -->
# df -T
```

查看文件系統標誌使用`wipefs`指令：

```html
<!-- 查看分區的文件系統標誌 -->
$ wipefs [塊設備]
<!-- 清理分區所包含的所有文件系統標誌 -->
# wipefs -a [塊設備]
```

使用`fdisk/parted`等工具操作分區塊設備後，內核的分區表並不會立即刷新，
需要使用`partprobe`工具刷新內核分區表信息：

```
# partprobe [塊設備]
```

分區大小變更後，需要調整文件系統大小以匹配新分區大小，否則文件系統實際可使用大小不變。



## fdisk
`fdisk`是Linux命令行下常用的交互式磁盤管理工具。

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

fdisk未直接提供調整分區大小的功能，但fdisk刪除分區默認**不會**清空磁盤內容，
對於磁盤存在額外空餘空間的情形，可通過刪除分區並在**相同起始位置**重建分區的方式進行無損分區擴容。

## parted
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

## flock
[flock](https://www.linux.org/docs/man1/flock.html)提供鎖管理的Shell接口，
使用鎖可實現腳本實例互斥等功能。

基本用法：

```html
<!-- 鎖定指定路徑/文件，執行指定指令 -->
$ flock [options] <file|directory> <command> [command args]
$ flock [options] <file|directory> -c <command>
<!-- 鎖定指令文件描述符 -->
$ flock [options] <file descriptor number>
```

flock默認使用阻塞模式執行，即當待鎖定的資源被其它flock持有時，
當前flock會一直等待，知道待鎖定的資源被釋放；
使用`-n/--nb/--nonblock`參數，則可讓flock以非阻塞模式執行，
該模式下flock獲取不到鎖時會立即退出。

```html
$ flock -n <文件|路徑> <指令> [參數]

<!-- 使用非阻塞模式，可以指定異常退出的錯誤代碼，默認錯誤代碼為1 -->
$ flock -n -E <錯誤碼> <文件|路徑> <指令> [參數]
```

示例：

```html
$ flock /tmp/sleep.lock sleep 10 & <!-- 後台執行，鎖定10s -->
[1] 19524
$ flock -n /tmp/sleep.lock echo "Get Lock!"
$ echo $?
1 <!-- 鎖定失敗，返回值1 -->
$ flock -n -E 100 /tmp/sleep.lock echo "Get Lock!"
$ echo $?
100 <!-- 鎖定失敗，返回值100 -->
...
$ flock -n /tmp/sleep.lock sleep 10
Get Lock! <!-- 進程結束，鎖定成功 -->
[1]+  Done                    flock -n /tmp/sleep.lock sleep 10
```

使用`lslocks`指令可查看當前環境中使用的鎖，示例：

```
$ flock /tmp/sleep.lock sleep 10 &
$ lslocks
flock           14204 FLOCK   0B WRITE 0     0   0 /tmp/sleep.lock
...
```

當使用flock執行指令時，若目標指令會創建子進程，則子進程會在flock結束後繼續持有鎖(文件描述符共享)，
該特性會導致只要之前該子進程不退出，鎖會一直被持有，直到創建的子進程結束。
使用`-o, --close`參數可解決該問題，使用`-o`參數則flock在獲取鎖成功、執行目標指令前關閉鎖文件的描述符。
示例：

```html
$ flock -o /tmp/sleep.lock sleep 10 & <!-- 使用 -o 參數進行鎖定 -->
[1] 21878
$ echo $?
0
$ flock -o /tmp/sleep.lock sleep 10 & <!-- 立即繼續鎖定 -->
[2] 22220
$ echo $?
0 <!-- 返回值為0，繼續鎖定成功，第一個flock進程創建的sleep子進程沒有繼承鎖，所以立即開始第二次鎖定依然成功 -->
```



# LVM (Logical Volume Manager)
`LVM (Logical Volume Manager)`，邏輯卷管理，是Linux環境下對磁盤分區進行管理的一種機制。

使用LVM能夠將不同的硬盤上的物理卷(`Physical Volume`，簡稱`PV`)加入卷組(`Volume Group`，簡稱`VG`)。
在卷組中將其劃分爲不同的邏輯卷(`Logical Volume`，簡稱`LV`)，然後在邏輯卷中創建文件系統並進行掛載。

LVM在物理磁盤上提供了一層抽象，解除了分區與物理磁盤的綁定。
LVM中一個邏輯分區在物理結構上可能由多個磁盤組成，添加新的物理磁盤時，
邏輯分區無需改變結構/重新掛載即可利用新增物理磁盤的空間實現動態擴容。

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

```c
# pvcreate [硬盤路徑/物理分區路徑] // 創建物理卷
# pvremove [硬盤路徑/物理分區路徑] // 移除物理卷
# pvmove [原物理分區路徑] [目標物理分區路徑] // 將原物理卷中的數據轉移到另一物理卷
# pvdisplay // 顯示已創建的物理卷
```

移除一個物理卷需要先將該物理卷從所屬的卷組中移除。
移除物理卷前需要保證沒有數據存儲在該物理卷中，若**要被移除的物理卷**中已有數據，
則需要使用`pvmove`指令將該卷中的數據轉移到其它卷。

## Volume Group (VG，卷組)
物理卷需要加入卷組(`Volume Group`)才能被使用。

卷組相關的操作爲`vgXXX`系列指令：

```c
# vgcreate [卷組名稱] [物理卷路徑] // 一個卷組至少需要包含一個物理卷，物理卷路徑可爲多個
# vgextend [卷組名稱] [物理卷路徑] // 向指定卷組中添加物理卷
# vgreduce [卷組名稱] [物理卷路徑] // 從指定卷組中刪除物理卷
# vgremove [卷組名稱] // 移除指定卷組
# vgdisplay // 顯示所有卷組
```

## Logical Volume (LV，邏輯卷)
邏輯卷(`Logical Volume`)是`LVM`中實際用於創建文件系統、掛載的分區。
邏輯卷的磁盤路徑爲`/dev/[邏輯卷所屬卷組名稱]/[邏輯卷名稱]`，使用該路徑可以像操作物理磁盤一樣對其進行創建文件系統、掛載等操作。

邏輯卷相關的操作爲`lvXXX`系列指令：

```c
# lvcreate -L [分區大小(xxGB/xxMB/...)] -n [邏輯分區路徑] [卷組名稱] // 創建邏輯卷
# lvresize -L +/-[分區大小(xxGB/xxMB/...)] [邏輯分區路徑] // 在原先邏輯卷大小的基礎上擴充/縮減指定大小
# lvextend -L [分區大小(xxGB/xxMB/...)] [邏輯分區路徑] // 增加邏輯捲到指定大小(分區大小的數值需要大於原先該邏輯分區的大小)
# lvreduce -L [分區大小(xxGB/xxMB/...)] [邏輯分區路徑] // 減小邏輯捲到指定大小(分區大小的數值需要小於原先該邏輯分區的大小)
# lvremove [邏輯分區名稱] // 移除指定邏輯卷
# lvdisplay // 顯示所有邏輯卷
```

擴展邏輯卷大小無需卸載、重新掛載文件系統。
縮減邏輯卷大小需要重先卸載文件系統，縮減空間後重新掛載。

擴展邏輯卷大小後，對應邏輯卷的文件系統大小並未增大，因此會造成不同指令輸出分區大小不一致的情況：

- `df`指令顯示的是文件系統大小
- `parted`、`fdisk`、`lsblk`、`lvdisplay`等指令顯示的是邏輯分區的大小

根據邏輯卷的文件系統類型，調整對應文件系統的大小：

```c
# xfs_growfs [邏輯分區路徑] // 擴展xfs文件系統的大小
# resize2fs [邏輯分區路徑] [分區大小] // 調整ext系列文件系統的大小
```

縮減邏輯卷時操作相反，先卸載對應分區，使用文件系統對應的工具縮減文件系統大小，之後再縮減文件系統所屬的LVM分區的大小。

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



# NTP (Network Time Protocol)
`NTP(Network Time Protocol)`是用於在多台計算機之間同步時鐘信息的網絡協議。

## NTP 服務配置
配置NTP服務前需要在系統中安裝ntp軟件包，各大Linux發行版的軟件源中均包含了ntp軟件包，
以ArchLinux為例，安裝ntp：

```
# pacman -S ntp
```

NTP配置文件為`/etc/ntp.conf`。

啟動NTP服務：

```
# systemctl start ntpd
```

### NTP Client 配置
將服務器配置為NTP Client，需要在配置中添加同步目標主機。
添加`server`配置段：

```sh
...
# 配置格式 server [版本號].[需要同步的主機地址]
server time.stdtime.gov.tw prefer # 設置具有更高優先級的主機
server 0.xxx
server 1.xxx
...
```

### NTP Server 配置
配置了NTP服務的主機可以允許同一網絡下的其它NTP客戶端同步此服務器。
添加`restrict`配置段：

```sh
...
# 配置格式 restrict [IP] mask [子網掩碼] [參數]...
restrict 192.168.1.0 mask 255.255.255.0 nomodify notrap
...
```

restrict配置項中，子網掩碼和其它參數均為**可選**。

restrict配置段的參數簡介：

| 參數 | 簡介 |
| :- | :- |
| ignore | 阻止所有類型的NTP連接 |
| nomodify | 阻止任何配置修改 |
| noquery | 阻止ntpq/ntpdc查詢，但允許時間查詢 |
| notrap | 阻止ntpdc控制消息協議 |
| notrust | 阻止未認證的客戶端 |
| nopeer | 阻止對等關聯(不允許同一層級服務關連) |

若在局域網中使用NTP時，則應考慮將某一台服務器作為基準時間，在該台服務器的配置中添加：

```
server 127.127.1.0
fudge 127.127.1.0
```

該服務器向自身進行同步，自身作為時鐘同步源。

## NTP 管理指令
使用`ntpstat`指令查看NTP服務狀態：

```
$ ntpstat
synchronised to unspecified (120.25.115.20) at stratum 3
   time correct to within 35 ms
   polling server every 64 s
```

對於同步延遲、失敗的情況可嘗試使用`ntpdate`指令進行**手動同步**：

```
# ntpdate [server ip/hostname]
```

使用`ntpq/ntpdc`指令進入交互式Shell，進行具體的NTP查詢操作：

```c
// ntpq - standard NTP query program
$ ntpq
ntpq> help
ntpq commands:
:config          delay            mreadvar         readlist
addvars          exit             mrl              readvar
associations     help             mrv              rl
authenticate     host             ntpversion       rmvars
cl               hostnames        opeers           rv
clearvars        keyid            passociations    saveconfig
clocklist        keytype          passwd           showvars
clockvar         lassociations    peers            timeout
config-from-file lopeers          poll             version
cooked           lpassociations   pstatus          writelist
cv               lpeers           quit             writevar
debug            mreadlist        raw

// ntpdc - special NTP query program
$ ntpdc
ntpdc> help
ntpdc commands:
addpeer      controlkey   fudge        keytype      quit         timeout
addrefclock  ctlstats     help         listpeers    readkeys     timerstats
addserver    debug        host         loopinfo     requestkey   traps
addtrap      delay        hostnames    memstats     reset        trustedkey
authinfo     delrestrict  ifreload     monlist      reslist      unconfig
broadcast    disable      ifstats      passwd       restrict     unrestrict
clkbug       dmpeers      iostats      peers        showpeer     untrustedkey
clockstat    enable       kerninfo     preset       sysinfo      version
clrtrap      exit         keyid        pstats       sysstats
```

## chrony
自`CentOS 7/RHEL 7`開始，RedHat使用`chrony`代替了傳統的ntpd作為時間同步服務。
相比傳統的ntpd，chrony具有以下優勢：

1. 更快的同步速度。
1. 能更好地響應時鐘頻率的快速變化，對於不穩定的虛擬機環境或使用不穩定始終的低功耗場景下更有效。
1. 在初始化同步之後不再計時。
1. 在處理非對稱延遲時居於更好的穩定性。
1. 不需要定期輪詢服務器，在網絡不定期間斷的場景下仍可快速同步時鐘。

chrony詳細介紹可參考[官方網站](https://chrony.tuxfamily.org/index.html)。

主流的發行版的軟件倉庫中均內置了chrony：

```c
// Arch Linux
# pacman -S chrony

// CentOS
# yum install chrony
```

chrony配置文件為`/etc/chrony.conf`，核心配置如下：

```sh
server [主機名稱/IP地址] [參數] # 設置用於同步的服務端

# 設置允許從該機同步的客戶端，支持以下類型的IP限制
# allow 1.2.3.4
# allow 1.2             # 對應網段 1.2.*.*
# allow 3.4.5           # 對應網段 3.4.5.*
# allow 6.7.8/22
# allow 6.7.8.9/22
# allow 2001:db8::/32
# allow 0/0
# allow ::/0
# allow all             # 允許任意主機同步
allow [IP地址]/[子網]
```

在局域網環境下，可將一台服務器作為時鐘同步源，允許主機從自身同步：

```sh
local # 允許主機以本地時間作為時鐘源
```

服務管理(以systemD發行版為例)：

```c
# systemctl enbale/disable chronyd // 開啟/關閉chrony自啟動
# systemctl start/stop chronyd // 啟動/停止chrony
```

chrony核心的工具指令包括`chronyc`(管理指令)/`chronyd`(服務進程)。
使用chronyc可進入類似ntpdc對應交互終端，直接指令子命令，常用指令：

```c
// 查看服務的執行狀態
$ chronyc tracking
Reference ID : 192.0.2.1 (192.0.2.1)
Stratum : 12
Ref time (UTC) : Fri Aug 05 19:06:51 2016
System time     : 0.000823375 seconds fast of NTP time
Last offset     : 0.001989304 seconds
RMS offset      : 0.060942811 seconds
Frequency       : 1728.043 ppm slow
Residual freq   : 1.100 ppm
Skew            : 94.293 ppm
Root delay	    : 0.000207 seconds
Root dispersion : 0.016767 seconds
Update interval : 65.1 seconds
Leap status     : Normal

// 查看用於同步的源
// M表示源的類型，'^'表示服務器，'='表示對等主機
// S表示源的狀態，'*'表示已同步，'+'表示已綁定，'-'表示被排除，'?'表示連接故障，'x'表示目標時鐘錯誤，'~'表示目標時鐘不穩定
$ chronyc sources
210 Number of sources = 1
MS Name/IP address    Stratum    Poll   Reach   LastRx   Last sample
=============================================================================
^* 192.0.2.1           11        6      377      63      +1827us[+6783us]

// 查看從當前主機同步的客戶端
$ chronyc clients
Hostname                      NTP   Drop Int IntL Last     Cmd   Drop Int  Last
===============================================================================
spark-master                   11      0  7     -   67       0      0   -     -
```



# curl
`curl`是一款功能強大的文件傳輸工具。

基本指令語法：

```
$ curl [參數] [目標路徑]
```

curl對於獲取的文件會直接以文本的形式輸出在終端上，可以使用`-o`參數導出到文件。
更多參數和用法參考[Gist](https://gist.github.com/subfuzion/08c5d85437d5d4f00e58)。

## HTTP請求
HTTP請求常用參數說明：

| 參數 | 說明 | 示例 |
| :- | :- | :- |
| -X, --request | HTTP Method | `-X POST`, `-X PUT` |
| -H, --header <header> | HTTP Request Headers | `-H "Content-Type: application/json"`, `-H "Content-Type: application/x-www-form-urlencoded"` |
| -d, --data <data> | HTTP Request Body | `-d '{"key1":"value1", "key2":"value2"}'`, `-d @data.json` |
| -b, --cookie <name=data> | Cookie | `-b key1=value1&key2=value2` |
| -F, --form <name=content> | From Data | `-F key1=value1&key2=value2` |
| -v, --verbose | Verbose | `-v` |
| -k, --insecure | Skip TLS certificate check | `-k` |

請求示例：

```html
<!-- POST Request with Json Content -->
$ curl -d '{"key1":"value1", "key2":"value2"}' -H "Content-Type: application/json" -X POST http://localhost:3000/data
<!-- POST Request with Json File -->
$ curl -d "@data.json" -H "Content-Type: application/json" -X POST http://localhost:3000/data
<!-- POST Request with From Data -->
$ curl -d "param1=value1&param2=value2" -H "Content-Type: application/x-www-form-urlencoded" -X POST http://localhost:3000/data
```

使用`-v`參數展示請求詳情，會顯示請求和回復的頭等敏感信息：

```
$ curl -v http://172.16.3.135
*   Trying 172.16.3.135...
* TCP_NODELAY set
* Connected to 172.16.3.135 (172.16.3.135) port 80 (#0)
> GET / HTTP/1.1
> Host: 172.16.3.135
> User-Agent: curl/7.64.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Server: nginx/1.10.3 (Ubuntu)
< Date: Wed, 14 Apr 2021 05:11:21 GMT
< Content-Type: text/html
< Content-Length: 618
< Last-Modified: Mon, 12 Apr 2021 02:35:43 GMT
< Connection: keep-alive
< ETag: "6073b1ff-26a"
< Accept-Ranges: bytes
<
<!DOCTYPE html>
<html>
<head>
<title>Welcome to nginx!</title>
<style>
    body {
        width: 35em;
        margin: 0 auto;
        font-family: Tahoma, Verdana, Arial, sans-serif;
    }
</style>
</head>
<body>
<h1>I am high reliability 1</h1>
<p>If you see this page, the nginx web server is successfully installed and
working. Further configuration is required.</p>

<p>For online documentation and support please refer to
<a href="http://nginx.org/">nginx.org</a>.<br/>
Commercial support is available at
<a href="http://nginx.com/">nginx.com</a>.</p>

<p><em>Thank you for using nginx.</em></p>
</body>
</html>
* Connection #0 to host 172.16.3.135 left intact
* Closing connection 0
```

### HTTP文件下載
curl同樣可用於在基於HTTP協議的文件下載，相關參數說明：

| 參數 | 說明 | 示例 |
| :- | :- | :- |
| -o, --output | Write output to <file> instead of stdout | `-o <file>` |
| -O, --remote-name | Write output to a local file named like the remote file we get | `-O` |
| -L, --location | Download file from new location (for 302 response) | `-L` |
| -s, --silent | Silent or quiet mode | `-s` |

使用`-o`參數可將請求回應內容重定向到文件中，即實現下載效果：

```html
$ curl http://example.com -o my.file
$ curl http://example.com --output my.file

<!-- 下載內容直接使用服務端提供的文件名稱 -->
$ curl -O http://example.com

<!--
部分下載地址並不直接提供資源，而是提供一個包含實際資源地址的30x系列回復，
此時使用-L參數會繼續向實際資源地址發起下載請求
-->
$ curl -OL http://example.com
```

默認下載會展示如下樣式的進度指示器：

```
  % Total    % Received % Xferd  Average Speed   Time    Time
                                 Dload  Upload   Total   Spent
100  1270  100  1270    0     0  50573      0 --:--:-- --:--:--
```

使用`--silent`參數可關閉進度指示(靜默模式)：

```
$ curl http://example.com -o my.file -s
$ curl http://example.com --output my.file --silent
```

curl的其它高級下載功能：

```html
<!-- 多文件下載 -->
$ curl -o aa example.com -o bb example.net
$ curl example.com example.net -o aa -o bb

<!-- 文件名變量替換 -->
$ curl http://{one,two}.example.com -o "file_#1.txt"
$ curl http://{site,host}.host[1-5].com -o "#1_#2"
```

## 用戶認證
對於一些可能需要驗證用戶權限的協議(如`ftp`)，可以使用`-u`參數添加用戶信息，指令格式如下：

```
$ curl [目標文件路徑] -u [用戶名]:[密碼] -o [輸出文件路徑]
```

## FTP 操作
使用curl工具進行`FTP`操作：

- `$ curl ftp://[ip/域名] -u [用戶名]:[密碼]` 列出FTP下的文件、目錄列表
- `$ curl ftp://[用戶名]:[密碼]@[ip/域名]` 列出FTP下的文件、目錄列表(簡化)
- `$ curl ftp://[用戶名]:[密碼]@[ip/域名]/[文件路徑] -o [輸出文件路徑]` 傳輸FTP文件到本地指定路徑
- `$ curl ftp://[用戶名]:[密碼]@[ip/域名] -T [本地文件路徑]` 上傳本地文件到FTP

在上傳/下載時，默認情況下會出現進度提示，可添加`-s`參數取消進度提示。

使用`-T`/`--upload-file`參數在上傳文件時指定要傳送的文件本地路徑：

```html
$ curl --upload-file "{file1,file2}" http://www.example.com
<!-- 若文件名有規律，可指定範圍上傳 -->
$ curl -T "img[1-1000].png" ftp://ftp.example.com/upload/
```

對於一些複雜的FTP功能，需要直接使用FTP**協議指令**來完成。
在curl工具中，使用`-X`參數追加協議指令，命令格式如下：

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
詳細說明參見[官方文檔](https://www.freedesktop.org/software/systemd/man/index.html)。

systemd的設計理念來自於Apple公司`macOS`中的`launchd`。
傳統的SystemV風格init系統需要一次一個串行地啓動服務進程，
systemd則根據服務進程的依賴關係並行地啓動服務，極大地減少了系統的啓動耗時。

配置文件：

- `/etc/systemd/system.conf` 全局配置文件
- `/etc/systemd/user.conf` 用戶配置文件

## systemd服務管理
systemd提供了統一、完整的服務管理功能：

- `# systemctl status [服務名稱]` 查看指定服務狀態
- `# systemctl start [服務名稱]` 啓動指定服務
- `# systemctl stop [服務名稱]` 停止指定服務
- `# systemctl enable [服務名稱]` 設置指定服務開機自啓動
- `# systemctl disable [服務名稱]` 取消指定服務開機自啓動

`systemd`服務文件通常以`*.service`爲後綴名。

- 系統服務：

	系統服務文件位於路徑`/usr/lib/systemd/system`下。
	啓用、禁用系統服務需要使用root權限(查看服務狀態不需要)。

- 用戶服務：

	用戶服務文件位於路徑`/usr/lib/systemd/user`下。
	管理用戶服務不需要以root權限執行`systemctl`指令，但需要在指令中添加`--user`參數：

	```
	$ systemctl --user status/start/stop/enable/disable [用戶服務名稱]
	```

## systemd服務分析
systemd提供了一系列工具用於查看查看、分析各類服務狀態。

使用`pstree`指令可以列出本機完整的systemd服務進程樹。

使用`systemctl list`系列指令查看服務狀態：

- `$ systemctl list-units` 列出已加載的服務單元信息
- `$ systemctl list-dependencies` 列出已加載服務單元的依賴關係
- `$ systemctl list-unit-files` 列出已安裝服務單元(所有服務單元)的自啓狀態
- `$ systemctl list-units -t [服務類型]` 查看指定類型的服務信息

使用`systemd-analyze`指令分析系統的啓動性能：

- `$ systemd-analyze` 顯示系統的啓動耗時
- `$ systemd-analyze blame` 列出所有的啓動單元，按照啓動耗時的高低進行排序

## 系統管理
systemd還集成了常用的系統管理工具：

| 工具名稱 | 功能 |
| :- | :- |
| hostnamectl | 配置主機名稱 |
| timedatectl | 時區時間配置 |
| localectl | 語言編碼配置 |
| networkctl | 網絡配置 |
| coredumpctl | 核心轉儲查看工具 |
| journalctl | 日誌查看工具 |
| loginctl | 會話狀態管理工具 |

### loginctl
`loginctl`用於配置systemd的登入管理器，loginctl自身服務為`systemd-logind.service`。

使用loginctl可查看當前的會話狀態：

```html
<!-- 默認列出當前登入的用戶會話 -->
$ loginctl
SESSION  UID USER   SEAT TTY
   1592 1001 ubuntu      pts/0
   1593 1001 ubuntu      pts/1

2 sessions listed.

<!-- 展示會話狀態，默認展示當前會話，亦可添加會話ID查看指定會話狀態 -->
$ loginctl session-status
1593 - ubuntu (1001)
           Since: Wed 2021-08-11 07:44:11 UTC; 2h 1min ago
          Leader: 329658 (sshd)
             TTY: pts/1
          Remote: 150.136.122.136
         Service: sshd; type tty; class user
           State: active
            Unit: session-1593.scope
                  ├─329658 sshd: ubuntu [priv]
                  ├─329731 sshd: ubuntu@pts/1
                  ├─329732 -fish
                  ├─330604 loginctl session-status
                  └─330605 pager

<!-- 展示會話參數，默認展示當前會話，亦可添加會話ID查看指定會話參數 -->
$ loginctl show-session
EnableWallMessages=no
NAutoVTs=6
KillUserProcesses=no
RebootToFirmwareSetup=no
RebootToBootLoaderMenu=18446744073709551615
IdleHint=no
IdleSinceHint=1628675225030795
IdleSinceHintMonotonic=4811977373202
DelayInhibited=shutdown
InhibitDelayMaxUSec=30s
UserStopDelayUSec=10s
HandlePowerKey=poweroff
HandleSuspendKey=suspend
HandleHibernateKey=hibernate
HandleLidSwitch=suspend
HandleLidSwitchDocked=ignore
HoldoffTimeoutUSec=30s
IdleAction=ignore
IdleActionUSec=30min
PreparingForShutdown=no
PreparingForSleep=no
Docked=no
LidClosed=no
OnExternalPower=yes
RemoveIPC=yes
RuntimeDirectorySize=102178816
InhibitorsMax=8192
NCurrentInhibitors=1
SessionsMax=8192
NCurrentSessions=2
```

使用loginctl查看用戶狀態：

```html
<!-- 列出當前用戶 -->
$ loginctl list-users
 UID USER
1001 ubuntu

1 users listed.

<!-- 查看用戶狀態，默認展示當前用戶，可搭配用戶ID展示特定用戶狀態 -->
$ loginctl user-status
ubuntu (1001)
           Since: Wed 2021-08-11 07:27:55 UTC; 2h 22min ago
           State: active
        Sessions: 1593 *1592
          Linger: yes <!-- Linger屬性控制用戶服務是否能在用戶登出後保留 -->
            Unit: user-1001.slice
                  ├─session-1592.scope
                  │ ├─329368 sshd: ubuntu [priv]
                  │ ├─329441 sshd: ubuntu@pts/0
                  │ ├─329442 -fish
                  │ ├─329640 man loginctl
                  │ └─329650 pager
                  ├─session-1593.scope
                  │ ├─329658 sshd: ubuntu [priv]
                  │ ├─329731 sshd: ubuntu@pts/1
                  │ ├─329732 -fish
                  │ ├─330745 loginctl user-status
                  │ └─330746 pager
                  └─user@1001.service
                    ├─init.scope
                    │ ├─328930 /lib/systemd/systemd --user
                    │ └─328931 (sd-pam)
                    └─syncthing.service
                      └─328936 /usr/bin/syncthing -no-browser -no-restart -logflags=0
...
```

用戶的Linger屬性控制用戶服務是否能在用戶登出後保留，修改該屬性：

```html
<!-- 默認操作當前用戶 -->
$ loginctl enable-linger/disable-linger

<!-- 啟用/禁用特定用戶的Linger -->
$ loginctl enable-linger 用戶名/用戶ID
$ loginctl disable-linger 用戶名/用戶ID
```



# 網絡
Linux下網絡工具主要包括老式的net-tools系列和新的iproute2系列工具。

Linux的proc文件系統在`/proc/net`路徑下也提供大量網絡相關信息：

```
$ ls /proc/net/
anycast6   fib_triestat   ip6_mr_vif         mcfilter   psched     rt_cache      tcp       wireless
arp        icmp           ip_mr_cache        mcfilter6  ptype      snmp          tcp6      xfrm_stat
connector  if_inet6       ip_mr_vif          netfilter  raw        snmp6         udp
dev        igmp           ip_tables_matches  netlink    raw6       sockstat      udp6
dev_mcast  igmp6          ip_tables_names    netstat    route      sockstat6     udplite
dev_snmp6  ip6_flowlabel  ip_tables_targets  packet     rt6_stats  softnet_stat  udplite6
fib_trie   ip6_mr_cache   ipv6_route         protocols  rt_acct    stat          unix
```

## net-tools & iproute2
[`net-tools`](https://sourceforge.net/projects/net-tools)套件歷史悠久，
提供了與其它Unix類似的網絡管理工具(ip、route等)，但目前已停止維護。

[`iproute2`](https://wiki.linuxfoundation.org/networking/iproute2)是下一代的Linux網絡工具套件。

net-tools與iproute2的主要功能對照：

| Legacy utility | Replacement command | Note |
| :- | :- | :- |
| ifconfig | ip addr, ip link | Address and link configuration |
| route | ip route | Routing tables
| arp | ip neigh | Neighbors |
| iptunnel | ip tunnel | Tunnels |
| nameif | ifrename, ip link set name | Rename network interfaces |
| ipmaddr | ip maddr | Multicast |
| netstat | ss | Show network port status |
| brctl | bridge | Handle bridge addresses and devices |

常見的網絡管理指令：

```html
# ip dev [網卡] flush <!-- 重置指定網卡設備的狀態 -->
```

## netstat & ss
`netstat`是net-tools中提供的socket查看工具，各大平台的netstat工具參數有較大差異。

Linux/macOS均支持的netstat參數：

- `-n` 禁用常用端口的名稱轉義，默認常用端口會直接轉換為協議名稱如`80`(http)
- `-h` 展示幫助信息

Linux平台的netstat的常用參數：

- `-t` 展示TCP端口
- `-u` 展示UDP端口
- `-l` 展示處於監聽狀態的端口
- `-p` 展示使用端口的進程信息

多個參數可組合使用：

```c
// 展示處於監聽狀態的UDP、TCP端口以及監聽進程
$ netstat -utnlp
```

`ss`是iproute2提供的次世代工具，提供與netstat類似的功能。
參數基本與Linux平台的netstat類似，如`-t`、`-u`、`-p`、`-n`、`-l`等。

macOS平台netstat的常用參數：

- `-p` 展示使用指定協議的端口
- `-v` 列出詳情，包括進程信息
- `-a` 顯示包含被服務端進程監聽的socket
- `-n` 不解析主機名稱，能顯著提升指令執行速度

展示macOS下的監聽TCP端口的進程：

```
$ netstat -anvf tcp | grep LISTEN
$ netstat -anvp udp
```

macOS沒有ss，但還可通過lsof查看端口監聽：

```html
$ lsof -iTCP -nP | grep LISTEN
$ lsof -iUDP -nP
$ lsof -i:端口號 -nP <!-- 查詢指定端口 -->
```

## mii-tool & ethtool
`mii-tool`用於查看網卡的狀態，指令語法：

```
usage: mii-tool [-VvRrwl] [-A media,... | -F media] [-p addr] <interface ...>
       -V, --version               display version information
       -v, --verbose               more verbose output
       -R, --reset                 reset MII to poweron state
       -r, --restart               restart autonegotiation
       -w, --watch                 monitor for link status changes
       -l, --log                   with -w, write events to syslog
       -A, --advertise=media,...   advertise only specified media
       -F, --force=media           force specified media technology
       -p, --phy=addr              set PHY (MII address) to report
media: 1000baseTx-HD, 1000baseTx-FD,
       100baseT4, 100baseTx-FD, 100baseTx-HD,
       10baseT-FD, 10baseT-HD,
       (to advertise both HD and FD) 1000baseTx, 100baseTx, 10baseT
```

其中`xxxbase`代表網卡的速率，100base即為百兆網卡，1000base即為千兆網卡。

實例：

```c
$ mii-tool eno2
eno2: negotiated 1000baseT-FD flow-control, link ok
```

`ethtool`可用於查看網卡的性能參數，包括帶寬等信息。
基本指令格式：

```
# ethtool devname
```

實例：

```
# ethtool enp1s0
Settings for enp1s0:
	Supported ports: [ TP MII ]
	Supported link modes:   10baseT/Half 10baseT/Full
	                        100baseT/Half 100baseT/Full
	                        1000baseT/Half 1000baseT/Full
	Supported pause frame use: No
	Supports auto-negotiation: Yes
	Advertised link modes:  10baseT/Half 10baseT/Full
	                        100baseT/Half 100baseT/Full
	Advertised pause frame use: Symmetric Receive-only
	Advertised auto-negotiation: Yes
	Link partner advertised link modes:  10baseT/Half 10baseT/Full
	                                     100baseT/Half 100baseT/Full
	Link partner advertised pause frame use: Symmetric
	Link partner advertised auto-negotiation: Yes
	Speed: 100Mb/s
	Duplex: Full
	Port: MII
	PHYAD: 0
	Transceiver: internal
	Auto-negotiation: on
	Supports Wake-on: pumbg
	Wake-on: g
	Current message level: 0x00000033 (51)
			       drv probe ifdown ifup
	Link detected: yes
```

## NetworkManager
`NetworkManager`是現代Linux發行版的主流網絡管理服務。
NetworkManager服務用於管理網絡連接和其它網絡接口，如Ethernet、WiFi、Mobile Broadband，
使網絡配置和操作變得盡可能自動化。

NetworkManager最初由RedHat開發，之後由GNOME項目進行維護。

NetworkManager基本概念可參考[Wikipedia](https://en.wikipedia.org/wiki/NetworkManager)，
功能配置相關可參考[ArchWiki](https://wiki.archlinux.org/index.php/NetworkManager)。

啟用關閉NetworkManager服務：

```
$ systemctl status NetworkManager
# systemctl enable NetworkManager
# systemctl disable NetworkManager
```

NetworkManager提供了基於命令行的網絡配置工具`nmcli`和基於TUI的`nmtui`。

nmcli常用指令：

```html
<!-- 列出無線網絡列表 -->
$ nmcli device wifi list
<!-- 連接指定無線網絡 -->
# nmcli device wifi connect [SSID] password [password]
# nmcli device wifi connect [SSID] password [password] hidden yes
<!-- 關閉無線網卡 -->
# nmcli radio wifi off

<!-- 連接管理相關 -->
$ nmcli connection show
# nmcli connection up [name/uuid]
# nmcli connection delete [name/uuid]

<!-- 網絡設備狀態相關 -->
$ nmcli device

<!-- 列出網絡連接信息 -->
$ nmcli connection
```

nmtui提供友好的TUI，可直接編輯、啟用、禁用連接。

## tcpdump
tcpdump是Unix環境下常用的抓包工具，macOS下系統自帶了該工具，
Linux下可從對應發行版軟件倉庫中進行安裝。

tcpdump指令的核心用法：

```
# tcpdump 參數 表達式
```

常用參數：

| 參數 | 說明 |
| :- | :- |
| -i interface | 指定網卡 |
| -n | 禁用地址、端口轉換 |
| -v | 展示協議類型 |
| -e | 展示鏈路層頭，對於以太網，展示源、目標地址以及包大小 |
| -X | 展示包的內容 |
| -tttt | 展示可讀的完整時間戳 |

tcpdump抓包的內容可導入/導出PCAP（PEE-cap）文件：

```
# tcpdump -w pcap文件
# tcpdump -r pcap文件
```

常用表達式：

```html
<!-- 依據網絡地址過濾 -->
# tcpdump  網口
# tcpdump host a.b.c.d
# tcpdump src a.b.c.d
# tcpdump dst a.b.c.d
# tcpdump net a.b.c.d/子網 <!-- 網段地址，如 1.1.1.0/24 -->

<!-- 依據協議過濾 -->
# tcpdump tcp
# tcpdump udp
# tcpdump icmp

<!-- 依據端口過濾 -->
# tcpdump port 端口
# tcpdump portrange 起始端口-結束端口

<!-- 依據包長度過濾 -->
# tcpdump less 包大小
# tcpdump greater 包大小
# tcpdump <= 包大小
```

tcpdump數據過濾表達式可搭配or、and、not等邏輯操作符組合多種條件：

```html
<!-- 過濾指定子網下非SSH協議 -->
# tcpdump net a.b.c.d/子網 and not ssh and port not 80
```

## Netcat (nc)
`nc`(netcat)是Unix環境下常用的TCP/UDP連接和監聽工具；
可用於打開TCP連接，發送UDP數據包，監聽TCP/UDP端口，執行端口掃描，該工具同時支持IPv4和IPv6。

macOS/BSD、部分Linux發行版預裝了該工具，
未預裝該工具的Linux可在發行版軟件倉庫中安裝該工具。

### 客戶端/服務端模式
nc工具可以選擇運行在客戶端/服務端模式。

作為服務端，可使用nc監聽指定端口：

```html
$ nc -l [ip/hostname] [port]
$ nc -l [port] <!-- 監聽時可省略主機/ip，默認監聽127.0.0.1/localhost -->
```

作為客戶端，可使用nc向指定端口發送數據：

```
$ nc [ip/hostname] [port]
```

客戶端/服務端添加`-v`參數均可輸出額外的提示信息。
默認nc使用TCP協議，使用`-u`參數可使用UDP協議進行交互：

```html
<!-- 服務端-->
$ nc -lu [port]
$ nc -lu [ip/hostname] [port]

<!-- 客戶端 -->
$ nc [ip/hostname] [port]
```

默認服務端僅能接受**一個**連接，客戶端或服務端使用`Ctrl + C`結束會話後，客戶端、服務端均會關閉。
可使用`-k`可實現僅關閉連接而不退出進程：

```html
$ nc -lk [port] <!-- 在客戶端連接關閉後可繼續接受新連接 -->
```

可使用`-w`參數設定連接的存活時間，超過存活時間的連接會被斷開：

```html
$ nc -lw [timeout] [port] <!-- 存活時間單位為：秒 -->
$ nc -lw [timeout] [ip/hostname] [port] <!-- 多個參數組合時，-w需要放在最後，否則存在參數解析錯誤 -->
```

監聽連接時，省略主機/ip信息**默認**監聽`127.0.0.1/localhost`，
macOS的nc客戶端在UDP模式下使用localhost無法正常通信，改為ip連接即可。

### 數據傳送
默認模式下，nc直接在命令行中進行標準輸入輸出。
與大多數Unix工具類似，可使用管道、重定向來傳送數據量較大的數據，
或者將接收到的數據寫入文件中。

```c
// 重定向輸入數據
$ nc -l [port] > [output_file]

// 基於文件重定向發送數據
$ nc [hostname/ip] [port] < [input_file]
// 基於管道發送數據
$ echo [content] | nc [hostname/ip] [port]
```

當數據發送完畢，連接將會關閉。



# 性能監控與測試
Linux下存在大量的性能監控工具，包括Unix系統通用的`ps`、`top`，
以及功能更加強大的`sysstat`工具套件，還有用於網絡性能監控的`iftop`工具等。

Linux的proc文件系統直接提供了大量進程、文件系統信息，可直接觀測：

| Path | Description |
| :- | :- |
| /proc/cpuinfo | Information about the processor, such as its type, make, model, and performance. |
| /proc/meminfo | Information about memory usage, both physical and swap. Concatenating this file produces similar results to using 'free' or the first few lines of 'top'. |
| /proc/PID/cmdline | Command line arguments. |
| /proc/PID/cpu | Current and last cpu in which it was executed. |
| /proc/PID/cwd | Link to the current working directory. |
| /proc/PID/environ | Values of environment variables. |
| /proc/PID/exe | Link to the executable of this process. |
| /proc/PID/fd | Directory, which contains all file descriptors. |
| /proc/PID/maps | Memory maps to executables and library files. |
| /proc/PID/mem | Memory held by this process. |
| /proc/PID/root | Link to the root directory of this process. |
| /proc/PID/stat | Process status. |
| /proc/PID/statm | Process memory status information. |
| /proc/PID/status | Process status in human readable form. |

多數Linux下的性能監控套件會依賴proc文件系統，而多數其它Unix並未提供該特性，
這使得Linux下的多數性能監控工具無法移植到其它Unix平台，如macOS/BSD。

## Load Averages
[`Load Averages`](https://en.wikipedia.org/wiki/Load_(computing))是Unix系統中重要的負載指標，
表示一個時間段內的系統資源佔用，通常以三個數值的形式展示，
分別表示最近**1分鐘**、**5分鐘**、**15分鐘**的平均性能負載。

在Linux、macOS/BSD等主流Unix系統中，Load Averages可使用uptime、top等工具可直接查看：

```html
<!-- macOS uptime -->
$ uptime
22:01  up 16 days, 15:51, 4 users, load averages: 2.90 3.09 3.64

<!-- macOS top -->
$ top
Processes: 504 total, 3 running, 501 sleeping, 2144 threads                                                    23:08:32
Load Avg: 2.97, 3.57, 3.14  CPU usage: 18.91% user, 9.92% sys, 71.15% idle
SharedLibs: 377M resident, 61M data, 68M linkedit. MemRegions: 106212 total, 2679M resident, 112M private, 734M shared.
PhysMem: 8117M used (2067M wired), 74M unused.
VM: 2610G vsize, 2308M framework vsize, 36511848(0) swapins, 36934832(0) swapouts.
Networks: packets: 3954498/4439M in, 2344905/1114M out. Disks: 8950050/274G read, 3033173/187G written.

PID COMMAND %CPU TIME #TH #WQ #PORT MEM PURG CMPRS PGRP PPID STATE BOOSTS %CPU_ME
...

<!-- Linux uptime -->
16:22:10 up  8:25,  load average: 0.32, 0.10, 0.03

<!-- Linux top -->
Mem: 351012K used, 1688252K free, 76K shrd, 25448K buff, 191728K cached
CPU:   0% usr   4% sys   0% nic  95% idle   0% io   0% irq   0% sirq
Load average: 0.14 0.10 0.04 2/385 559
  PID  PPID USER     STAT   VSZ %VSZ CPU %CPU COMMAND
...
```

空載系統下Load Averages數值為0，隨著系統負載升高，該數值隨之增大。

Linux系統下，每個使用/等待CPU資源的進程會增加數值1的負載，
對單核CPU而言，假設Load Averages數值為`5.12`，
則說明平均有`1`個進程使用CPU資源，`5.12 - 1 == 4.12`個進程在等待CPU資源。
Load Averages數值大於`1`則說明系統過載，例如`1.05`表示系統過載`5%`，`5.12`表示過載`412%`；
對多核CPU而言，每個CPU核心均可執行1個進程，因此Load Averages數值大於CPU核心數才說明系統過載，
例如8核心的CPU，若Load Averages數值為`8.18`，則系統僅過載`18%`。

不同Unix下Load Averages的具體計算方式不同，不能直接比較，
macOS使用線程數計算系統負載，而不是Linux使用的進程數目，因而通常macOS系統下顯示的負載會高於1。
macOS下的Load Averages介紹可參考[StackExchange](https://superuser.com/questions/370622/how-is-load-average-calculated-on-osx-it-seems-too-high-and-how-do-i-analyze)上的相關問答。
macOS的進程模型具體可參考[Mach內核官方文檔](https://developer.apple.com/library/archive/documentation/Darwin/Conceptual/KernelProgramming/Architecture/Architecture.html)。

## ps
`ps`指令是Unix下最常用的進程信息查看工具，可查看進程的CPU、內存等常見的資源使用情況。
Linux與macOS/BSD系列指令參數有部分差異。

ps指令支持多種參數風格，通常參數為短參數(單橫槓參數，如`-a,-A,-u,-v,-p,-o`)，
在BSD風格下部分短參數作為**首個參數**時可以省略單橫槓，Linux也部分支持該風格。
部分參數在有/無單橫槓時含義不同，如`u`(特定顯示格式)和`-u [uid]`(顯示特定uid所屬進程)。

通用用法：

```c
// 默認顯示當前用戶進程
// macOS 格式 PID TTY TIME CMD
// Linux 格式 PID TTY STAT TIME COMMAND
$ ps

// 顯示所有進程，不包含無控制終端的進程
$ ps a
// 顯示所有進程，包含無控制終端的進程
$ ps ax // 參數"x"指示顯示結果包含無控制終端進程
$ ps A // macOS/BSD專有，Linux不支持該參數

// Linux 展示 USER PID %CPU %MEM VSZ RSS TTY STAT START TIME COMMAND
// macOS 展示 USER PID %CPU %MEM VSZ RSS TT STAT STARTED TIME COMMAND
$ ps u

// Linux 展示 PID TTY STAT TIME MAJFL TRS DRS RSS %MEM COMMAND
// macOS 展示 PID STAT TIME SL RE PAGEIN VSZ RSS LIM TSIZ %CPU %MEM COMMAND
$ ps v

// 組合參數展示所有進程詳細信息
$ ps aux
$ ps avx
$ ps -ef
// macOS/BSD
$ ps Au
$ ps Av

// 展示指定特徵的進程信息
$ ps p [pid]
$ ps U [user]

// 展示當前終端進程
$ ps t
// 展示特定終端進程
$ ps t [tty]

// Linux 展示 UID PID PPID C STIME TTY TIME CMD
// macOS 展示 UID PID PPID C STIME TTY TIME CMD
$ ps f

// Linux 展示 F S UID PID PPID C PRI NI ADDR SZ WCHAN TTY TIME CMD
// macOS 展示 UID PID PPID F CPU PRI NI SZ RSS WCHAN S ADDR TTY TIME CMD
$ ps l

// Linux 展示 PID PGID SID TTY TIME CMD
// macOS 展示 USER PID PPID PGID SESS JOBC STAT TT TIME COMMAND
$ ps j
```

ps指令還支持通過關鍵字自定義監控內容：

```c
$ ps o [keyword1,keyword2,keyword3...]

// 查看支持的監控內容
$ ps L
```

macOS和Linux均支持的監控內容：

| Keyword | Description |
| :- | :- |
| %cpu | percentage CPU usage (alias pcpu) |
| %mem | percentage memory usage (alias pmem) |
| args | command and arguments |
| comm | command |
| command | command and arguments |
| cpu | short-term CPU usage factor (for scheduling) |
| etime | elapsed running time |
| flags | the process flags, in hexadecimal (alias f) |
| gid | processes group id (alias group) |
| lstart | time started |
| pgid | process group number |
| pid | process ID |
| ppid | parent process ID |
| pri | scheduling priority |
| rgid | real group ID |
| rss | resident set size |
| ruid | real user ID |
| ruser | user name (from ruid) |
| sess | session ID |
| sig | pending signals (alias pending) |
| sigmask | blocked signals (alias blocked) |
| start | time started |
| state | symbolic process state (alias stat) |
| svgid | saved gid from a setgid executable |
| svuid | saved UID from a setuid executable |
| time | accumulated CPU time, user + system (alias cputime) |
| tt | control terminal name (two letter abbreviation) |
| tty | full name of control terminal |
| uid | effective user ID |
| user | user name (from UID) |
| vsz | virtual size in Kbytes (alias vsize) |
| wchan | wait channel (as a symbolic name) |

實例：

```
$ ps p 78276 -o command,pid,gid,user,tty,%cpu,%mem,pri,state,time
COMMAND   PID   GID USER     TTY       %CPU %MEM PRI STAT      TIME
-fish   78276    20 dainslef ttys000    0.0  0.0  31 S      0:00.45
```

Linux下的ps指令同樣支持BSD風格的參數，顯式格式與macOS/BSD下基本相同。

## top
`top`是Linux/Unix下最常見的性能監控工具，所有的Linux發行版均包含該工具，
macOS/BSD系列同樣包含該工具，但參數操作方式有所不同。

在命令行輸入top指令進入指令介面，默認參數下，top會一直在前台以1s為間隔刷新顯示進程信息，
輸入`q`可退出top。

macOS下top的介面樣式：

```
Processes: 475 total, 2 running, 473 sleeping, 2441 threads                                                    17:49:08
Load Avg: 4.03, 5.05, 4.77  CPU usage: 33.64% user, 17.64% sys, 48.70% idle
SharedLibs: 276M resident, 41M data, 21M linkedit. MemRegions: 170650 total, 2367M resident, 73M private, 753M shared.
PhysMem: 8096M used (2015M wired), 95M unused.
VM: 2850G vsize, 2308M framework vsize, 117166562(62) swapins, 119790867(0) swapouts.
Networks: packets: 18095435/9910M in, 13327243/5146M out. Disks: 32894176/942G read, 17636222/665G written.

PID    COMMAND      %CPU TIME     #TH   #WQ  #PORT MEM    PURG   CMPRS  PGRP  PPID  STATE    BOOSTS           %CPU_ME
1368   Terminal     48.1 24:33.43 9     3    416-  131M   26M-   41M-   1368  1     sleeping *0[32380+]       0.69481
143    WindowServer 30.6 12:14:01 14    6    2461  1177M- 7736K- 166M   143   1     sleeping *0[1]            3.04495
0      kernel_task  11.9 08:21:25 194/4 0    0     752M+  0B     0B     0     0     running   0[0]            0.00000
1857   Code Helper  9.5  12:10.20 23    1    156+  57M+   0B     25M-   1369  1369  sleeping *0[1]            0.00000
97866  idea         7.2  28:05.73 53    1    399   2049M  0B     1303M- 97866 1     sleeping *0[685]          0.00000
785    mdworker_sha 6.0  00:03.88 4     1    61    1388K  0B     312K   785   1     sleeping *0[1]            0.37947
697    mdworker_sha 5.9  00:08.64 4     1    61    1400K  0B     340K   697   1     sleeping *0[1]            0.94696
835    top          5.8  00:01.10 1/1   0    25    6464K+ 0B     0B     835   1463  running  *0[1]            0.00000
782    mdworker_sha 5.8  00:03.88 4     1    61    2196K  0B     340K   782   1     sleeping *0[1]            0.11713
91744  com.apple.We 5.1  06:50.51 10    4    174   431M+  6160K- 168M+  91744 1     sleeping  0[71425+]       0.00000
99766  Code Helper  4.5  04:43.04 25    1    247   184M-  0B     65M    1369  1369  sleeping *0[1]            0.00000
696    mdworker_sha 4.5  00:08.22 4     1    61    1392K  0B     364K   696   1     sleeping *0[1]            0.27370
400    mds_stores   4.4  67:55.94 8     6    103+  48M+   36K    31M    400   1     sleeping *0[1]            0.00000
784    mdworker_sha 4.4  00:04.14 4     1    61    1396K  0B     368K   784   1     sleeping *0[1]            0.78489
800    mdworker_sha 4.3  00:02.11 4     1    49    1064K  0B     0B     800   1     sleeping *0[1]            0.61253
787    mdworker_sha 4.3  00:03.93 4     1    61    2280K  0B     332K   787   1     sleeping *0[1]            0.12357
92     mds          4.3  41:57.87 10    7    482   27M+   0B     20M    92    1     sleeping *0[1]            0.88632
649    mdworker_sha 4.3  00:14.11 4     1    61    1380K  0B     532K   649   1     sleeping *0[1]            0.54691
783    mdworker_sha 4.2  00:03.87 4     1    61    2172K  0B     348K   783   1     sleeping *0[1]            0.26021
780    mdworker_sha 4.1  00:04.05 4     1    61    1388K  0B     348K   780   1     sleeping *0[1]            0.58266
90530  WeChat       3.6  04:05.32 29    7    2723- 149M-  0B     118M-  90530 1     sleeping *7[6]            0.03709
62021  MySQLWorkben 3.0  24:25.94 20    1    5377  276M   0B     253M   62021 1     sleeping  0[14444]        0.00000
12350  gamecontroll 3.0  31:36.68 5     4    70    1608K  0B     492K   12350 1     sleeping *0[3850039+]     0.00000
99810  bluetoothaud 3.0  02:48.31 4     1    191   4648K  0B     1460K  99810 1     sleeping *0[1]            0.00000
91739  NeteaseMusic 2.8  07:32.94 21    4    3014  75M+   84K    35M-   91739 1     sleeping *0[2311]         0.35759
191    coreaudiod   1.2  16:22.49 6     1    1362  9008K  0B     5016K  191   1     sleeping *0[1]            0.00000
28209  java         1.0  57:47.77 98    1    235   250M   0B     195M-  16532 1     sleeping *0[1]            0.00000
69     fseventsd    0.8  19:40.71 15    1    297   3640K  0B     1076K  69    1     sleeping *0[1]            0.03872
699    WeatherWidge 0.4  09:35.25 4     2    2948  55M    0B     49M    699   1     sleeping *1[22]           0.00000
1373   Finder       0.3  10:51.38 8     2    661   100M   0B     76M    1373  1     sleeping *0[12526]        0.00000
78384  OneDrive     0.3  32:17.78 17    4    2182  484M   64K    293M   78384 1     sleeping *0[2673]         0.00000
1369   Electron     0.2  29:47.52 31    1    1414  120M+  0B     50M-   1369  1     sleeping *0[30361]        0.00000
```

Linux下top的介面樣式：

```
top - 17:50:00 up 34 days, 14:44,  1 user,  load average: 0.03, 0.14, 0.28
Tasks: 176 total,   1 running, 175 sleeping,   0 stopped,   0 zombie
%Cpu(s):  1.0 us,  0.9 sy,  0.0 ni, 98.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem : 32686896 total,  3285348 free, 28451196 used,   950352 buff/cache
KiB Swap: 31457276 total, 24550632 free,  6906644 used.  3808324 avail Mem

  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
 4191 root      20   0   13.7g   1.0g   7016 S   2.0  3.3   1218:28 java
 4608 root      20   0   13.7g 993028   6776 S   2.0  3.0   1011:57 java
 4856 root      20   0   13.7g   1.0g   6948 S   1.7  3.2   1032:24 java
11171 root      20   0   13.7g   1.8g   7780 S   1.7  5.6 716:33.35 java
 1867 root      20   0   13.7g   2.1g   7224 S   1.3  6.7 533:29.57 java
 5344 root      20   0   22.1g   6.5g   6576 S   1.3 20.7 518:56.08 java
 6766 root      20   0   13.8g 664472   7052 S   1.3  2.0 728:52.60 java
 7604 root      20   0   13.7g   2.2g   7408 S   1.3  6.9 707:33.46 java
 9472 root      20   0   13.7g 808752   7760 S   1.3  2.5 392:01.19 java
15990 root      20   0   13.7g 654456   7776 S   1.3  2.0 396:45.45 java
21867 root      20   0   13.6g 555228   7756 S   0.7  1.7 261:55.44 java
 3071 root      20   0   12.5g 145636   6180 S   0.3  0.4  88:32.05 java
 3154 root      20   0 7319888 803444   6836 S   0.3  2.5 525:59.38 java
 3770 root      20   0    9.8g   5.8g   6624 S   0.3 18.6 255:39.33 java
 4087 root      20   0 6958564 254508   6248 S   0.3  0.8  54:58.17 java
 6762 root      20   0  165752   7624    764 S   0.3  0.0  56:10.98 redis-server
21455 root      20   0 8714932   1.2g  86512 S   0.3  3.7  15:19.40 java
    1 root      20   0  191296   2680   1504 S   0.0  0.0   3:54.78 systemd
    2 root      20   0       0      0      0 S   0.0  0.0   0:01.21 kthreadd
    3 root      20   0       0      0      0 S   0.0  0.0   2:31.62 ksoftirqd/0
    5 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/0:0H
    7 root      rt   0       0      0      0 S   0.0  0.0   0:00.04 migration/0
    8 root      20   0       0      0      0 S   0.0  0.0   0:00.00 rcu_bh
    9 root      20   0       0      0      0 S   0.0  0.0  48:24.47 rcu_sched
   10 root      rt   0       0      0      0 S   0.0  0.0   0:13.40 watchdog/0
   11 root      rt   0       0      0      0 S   0.0  0.0   0:13.10 watchdog/1
   12 root      rt   0       0      0      0 S   0.0  0.0   0:00.03 migration/1
   13 root      20   0       0      0      0 S   0.0  0.0   0:04.07 ksoftirqd/1
   15 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/1:0H
   16 root      rt   0       0      0      0 S   0.0  0.0   0:10.39 watchdog/2
   17 root      rt   0       0      0      0 S   0.0  0.0   0:00.02 migration/2
   18 root      20   0       0      0      0 S   0.0  0.0   0:03.77 ksoftirqd/2
   20 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/2:0H
```

macOS/BSD指令參數：

```
top	[-a | -d | -e | -c <mode>]
	[-F | -f]
	[-h]
	[-i <interval>]
	[-l <samples>]
	[-ncols <columns>]
	[-o <key>] [-O <secondaryKey>]
		keys: pid (default), command, cpu, cpu_me, cpu_others, csw,
			time, threads, ports, mregion, mem, rprvt, purg, vsize, vprvt,
			kprvt, kshrd, pgrp, ppid, state, uid, wq, faults, cow, user,
			msgsent, msgrecv, sysbsd, sysmach, pageins, boosts, instrs, cycles
	[-R | -r]
	[-S]
	[-s <delay>]
	[-n <nprocs>]
	[-stats <key(s)>]
	[-pid <processid>]
	[-user <username>]
	[-U <username>]
	[-u]
```

Linux下指令參數：

```
top -hv|-bcHiOSs -d secs -n max -u|U user -p pid -o fld -w [cols]
```

常用功能說明：

- 控制刷新時間間隔

	直接執行top指令會以一定時間為間隔動態展示全部進程的資源佔用，默認時間間隔通常為1s。
	macOS下使用`-s`，Linux下使用`-d`指定時間間隔。

- 僅展示指定用戶的進程信息

	默認top會展示所有進程信息，macOS下使用`-U`，Linux使用`-u`顯示指定用戶的進程信息。

- 按照指定資源指標排序進程

	默認top指令以CPU佔用率作為進程排序的資源指標。

	macOS下使用`-o`指定排序的主要指標，`-O`指定第二排序指標；
	亦可在top指令執行後在指令介面中輸入`o`設定排序指標，設置會立即生效。

	Linux下在指令介面中使用`Shift + <`和`Shift + >`組合鍵動態切換進程排序的資源指標。

## iftop
`iftop`是常用的網絡IO監控工具，通常發行版中並未直接包含，需要從倉庫中安裝：

```c
// CentOS中iftop不在主倉庫中
# yum install epel-release
# yum install iftop

// 大便系
# apt install iftop

// Arch系
# pacman -S iftop
```

在命令行中直接輸入iftop指令，會進入展示網絡IO的TUI：

```
$ iftop
                 19.1Mb           38.1Mb           57.2Mb           76.3Mb	95.4Mb
└────────────────┴────────────────┴────────────────┴────────────────┴─────────────────
spark-master                  => spark-slave2                  93.5Kb  53.6Kb  46.9Kb
                              <=                               91.7Kb   150Kb   143Kb
spark-master                  => spark-slave3                   143Kb  74.5Kb  71.5Kb
                              <=                               79.6Kb  87.2Kb  65.7Kb
spark-master                  => spark-slave0                   401Kb  99.7Kb   224Kb
                              <=                                115Kb  35.6Kb   112Kb
spark-master                  => 172.16.0.164                  2.94Kb  11.2Kb  16.7Kb
                              <=                                464b   1.31Kb  1.65Kb
spark-master                  => 172.16.1.92                    264b   1.68Kb  1.65Kb
                              <=                                740b   7.73Kb  7.72Kb
spark-master                  => spark-slave1                  6.36Kb  2.87Kb  6.04Kb
                              <=                               5.67Kb  5.43Kb  77.1Kb
172.16.3.255                  => 172.16.1.116                     0b	  0b	  0b
                              <=                               1.36Kb  1.61Kb  1.61Kb
172.16.3.255                  => 172.16.1.115                     0b	  0b	  0b
                              <=                               1.36Kb  1.36Kb  1.61Kb
224.0.0.252                   => 172.16.0.14                      0b	  0b	  0b
                              <=                                520b    520b    520b
172.16.3.255                  => 172.16.0.198                     0b	  0b	  0b
                              <=                                624b    374b    406b
172.16.3.255                  => 172.16.0.54                      0b	  0b	  0b
                              <=                                624b    374b    406b
224.0.0.252                   => 172.16.0.198                     0b	  0b	  0b
                              <=                                880b    352b    396b

──────────────────────────────────────────────────────────────────────────────────────
TX:             cum:   2.38MB   peak:   2.93Mb        rates:    647Kb   244Kb   366Kb
RX:                    2.78MB           3.18Mb                  300Kb   294Kb   413Kb
TOTAL:                 5.16MB           6.10Mb                  947Kb   537Kb   779Kb
```

iftop的TUI中主要參數的含義：

- `TX` 代表`transmitted traffic`(發送流量)
- `RX` 代表`received traffic`(接收流量)
- `TOTAL` 代表發送、接收流量之和
- `cum` 代表累加流量
- `peak` 代表最高瞬時流量

常用參數：

```c
// 監控指定網卡的IO
$ iftop -i [devname]

// 按照源/目標地址排序
$ iftop -o source/destination
```

## sysstat
[`sysstat`](https://github.com/sysstat/sysstat)套件是Linux下的性能監控工具，
包含了一系列工具：

- `iostat` reports CPU statistics and input/output statistics for block devices and partitions.
- `mpstat` reports individual or combined processor related statistics.
- `pidstat` reports statistics for Linux tasks (processes) : I/O, CPU, memory, etc.
- `tapestat` reports statistics for tape drives connected to the system.
- `cifsiostat` reports CIFS statistics.

主流發行版通常並未直接集成sysstat，但在軟件倉庫中提供了該套件，可直接安裝：

```c
# apt install sysstat // 大便系
# yum install sysstat // 紅帽系
# pacman -S sysstat // Arch系
```

### pidstat
`pidstat`工具相比系統自帶的ps工具，提供了更為完善的性能參數統計。

默認指令會監控所有進程；
統計指定進程，並指定監控間隔：

```c
// 按照指定的時間間隔輸出間隔內的平均資源佔用，退出指令後會展示整個指令期間的平均資源佔用
$ pidstat -p [pid] [interval]

// 統計指定次數後退出
$ pidstat -p [pid] [interval] [count]
```

### iostat
`iostat`工具用於監測磁盤IO，基本使用方式與pidstat類似。

默認指令會監控所有磁盤；
統計指定磁盤，並指定監控間隔：

```c
$ iostat -p [dev] [interval]
$ iostat -p [dev] [interval] [count]
```

默認IO的吞吐單位為`kB/s`，若磁盤吞吐量較高，可設置為`MB/s`：

```
$ iostat -m
```

CPU佔用可於各個分區磁盤佔用並列展示：

```
$ iostat -x
```

可以設置生成統計信息同時帶上時間戳：

```
$ iostat -t
```

## HTTP壓測工具
常見的HTTP壓測工具：

- [ab(Apache Bench)](https://httpd.apache.org/docs/current/programs/ab.html)
命令行工具，Apache HTTP Server的一部分
- [Apache JMeter](https://jmeter.apache.org/) Java實現的GUI壓測工具
- [autocannon](https://github.com/mcollina/autocannon) NodeJS實現的命令行壓測工具



# VTE
`VTE`是`Gnome`項目提供的輕量級終端庫，許多終端軟件使用VTE實現，如`gnome-terminal`、`roxterm`等。
VTE自身亦可做爲獨立的終端軟件使用。

相比其它終端模擬器，VTE提供了豐富的特性和較少的依賴(僅僅依賴`GTK+`)。

VTE當前的主流版本爲基於`GTK+ 2`的`VTE2`和基於`GTK+ 3`的`VTE3`。
在`Arch Linux`/`NixOS`等多數發行版的打包中，VTE2的指令名稱爲`vte`，VTE3的指令名稱爲`vte-2.91`。

VTE2現已停止維護，部分發行版(如Arch Linux)已經移除了其對應軟件包。

## VTE2
VTE2開發時間較早，現已不支持部分終端顯示特性
(如systemctl的服務狀態輸出中包含路徑字符串，在VTE2下顯示為亂碼)。

VTE通過在啓動時添加命令行參數進行設置，VTE2常見參數如下所示：

- `-g` 設定終端初始大小(行列大小)，格式爲`124x456`
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

## VTE3
VTE3默認會使用Gnome3 App慣用的HeadBar風格，默認參數下啟動會帶有一個巨大的窗口裝飾器，
可使用參數關閉。

VTE3大多數參數兼容VTE2，為保持與VTE2相近的風格，可使用以下參數：

- `-T` 透明度，參數為數值，VTE3默認終端不透明
- `--no-decorations` 禁用巨醜的HeadBar
- `--no-scrollbar` VTE3默認顯示滾動條，使用該參數禁用

保持與VTE2相似的風格，參數示例：

```
$ vte-2.91 -W -P never -g 120x40 -f "Monaco 10" -n 5000 -T 20 --reverse --no-decorations --no-scrollbar
```

## 複製粘貼快捷鍵
VTE中提供了**剪切板**功能，但Linux終端中常見的複製粘貼快捷鍵並不生效。

在VTE中複製粘貼快捷鍵如下：

- `Control + Insert` 複製
- `Shift + Insert` 粘貼



# 字體配置
Linux下字體配置需要依賴`fontconfig`軟件包，多數發行版安裝了桌面環境後會自動將該包作為依賴安裝。

手動安裝該軟件包：

```html
# yum/dnf install fontconfig <!-- 紅帽係 -->
# pacman -S fontconfig <!-- Arch係 -->
# apt install fontconfig <!-- 大便係 -->
```

## 管理字體
fontconfig軟件包提供了一系列字體管理工具。

```html
$ fc-list <!-- 列出系統中已安裝的字體信息，包括字體路徑、名稱、字型等 -->
/usr/share/fonts/dejavu/DejaVuSansCondensed-Oblique.ttf: DejaVu Sans,DejaVu Sans Condensed:style=Condensed Oblique,Oblique
/usr/share/fonts/dejavu/DejaVuSansCondensed-Bold.ttf: DejaVu Sans,DejaVu Sans Condensed:style=Condensed Bold,Bold
/usr/share/fonts/dejavu/DejaVuSans.ttf: DejaVu Sans:style=Book
...

$ fc-cache <!-- 刷新字體緩存，用於環境中新增了字體之後 -->
```

## 字體相關路徑
字體文件可存放在系統路徑`/usr/share/fonts`以及用戶路徑`~/.local/share/fonts`，
早期用戶字體路徑`~/.fonts`現已廢棄。

全局的字體配置路徑為`/etc/fonts/fonts.conf`，用戶字體配置路徑為`~/.config/fontconfig/fonts.conf`。
字體配置遵循XML語法，多數安裝的字體都會在路徑`/usr/share/fontconfig/conf.avail`下提供字體對應的配置，
可將全局字體配置鏈接到具體使用的字體配置。

## 字體渲染問題
對於無法預估確認字體名稱的環境下，使用錯誤的字體名稱可能導致渲染內容出現`口口...`，
可直接使用通用字體類型`serif`、`sans-serif`等，系統會根據fontconfig配置選取合適的字體。



# 字符串模板
Linux中可以使用`envsubst`替換模板中的環境變量引用，或者使用`sed`指令實現基於正則的文本替換。

## envsubst
envsubst來自GNU項目的[gettext](https://www.gnu.org/software/gettext/)工具鏈，
gettext提供了一系列的文本處理工具，如gettext、msggrep、envsubst等。
envsubst使用方法較為簡單，該工具從標準輸入接收文本，直接讀取當前環境變量，
替換環境變量內容後輸出到標準輸出。

默認為交互模式，輸入文本後按回車鍵輸出替換後的內容：

```html
$ envsubst
$HOME $EDITOR
/Users/dainslef vim
Current language: $LANG
Current language: en_US.UTF-8
```

亦可使用管道/重定向等方式輸入內容：

```html
<!-- 使用管道 -->
$ echo $HOME $EDITOR | envsubst
/Users/dainslef vim
$ echo 'Current language: $LANG'
Current language: $LANG
$ echo 'Current language: $LANG' | envsubst
Current language: en_US.UTF-8

<!-- 使用重定向 -->
$ envsubst <<< $HOME
/Users/dainslef
$ envsubst <<< 'Current language: $LANG'
Current language: en_US.UTF-8
```

使用envsubst默認會轉換所有符合環境變量語法(`$XXX`)的內容，
若被替換的目標環境變量不存在，則以空字符串替代：

```html
<!-- 查詢當前環境變量的信息 -->
$ env | grep LANG
LANG=en_US.UTF-8
LANGUAGE=en_US:en
$ env | grep UNKNOWN

$ echo 'Current language: $LANG, Unkown: $UNKNOWN'
Current language: $LANG, Unkown: $UNKNOWN
<!-- 環境變量 $UNKNOWN 不存在，輸出空內容 -->
$ echo 'Current language: $LANG, Unkown: $UNKNOWN' | envsubst
Current language: en_US.UTF-8, Unkown:
```

envsubst可添加一個文本參數控制需要替換的環境變量：

```html
<!-- 僅替換 $UNKNOWN -->
$ echo 'Current language: $LANG, Unkown: $UNKNOWN' | envsubst '$UNKNOWN'
Current language: $LANG, Unkown:
<!-- 僅替換 $LANG -->
$ echo 'Current language: $LANG, Unkown: $UNKNOWN' | envsubst '$LANG'
Current language: en_US.UTF-8, Unkown: $UNKNOWN
<!-- 替換多個環境變量 -->
$ echo 'Current language: $LANG, Unkown: $UNKNOWN' | envsubst '$UNKNOWN $LANG'
Current language: en_US.UTF-8, Unkown:
<!-- 全不替換 -->
$ echo 'Current language: $LANG, Unkown: $UNKNOWN' | envsubst ''
Current language: $LANG, Unkown: $UNKNOWN
```

## sed
`sed`是流式編輯器(stream editor)，通常各類Unix中均包含該工具，
在Linux中內置的實現是[`GNU sed`](https://www.gnu.org/software/sed/manual/sed.html)。

使用GNU sed工具可實現文本替換：

```html
<!-- 默認將替換後的內容輸出到終端 -->
$ sed 's/舊文本/新文本/' 文件路徑

<!-- 可替換輸出文件內容 -->
$ sed -i 's/舊文本/新文本/' 文件路徑

<!-- 基於其它指令的重定向輸出 -->
$ cat/echo/... | sed 's/舊文本/新文本/'
```

示例：

```html
<!-- Linux GNU sed -->
$ cat test.txt
$TEST output
$ sed 's/$TEST/test/' test.txt
test output
$ sed -i 's/$TEST/test/' test.txt
$ cat test.txt
test output
$ echo '$TEST output' | sed 's/$TEST/test/'
test output
```

需要注意，sed在不同Unix中的實現功能參數有所不同，以BSD的sed為例，
`-i`參數設置後綴，將輸出內容保存到現有文件，同時備份原內容到添加後綴的文件中。
示例：

```html
<!-- macOS BSD sed -->
$ cat test.txt
$TEST output
$ sed -i .back 's/$TEST/test/' test.txt
$ cat test.txt
test output <!-- 輸出文件內容已被替換 -->
$ cat test.txt.back
$TEST output <!-- 原文件被備份到 "原文件名+後綴" 的文件中 -->
```



# apt/dpkg
`Debian`系列發行版使用`deb`格式作爲軟件包的打包、分發格式；
使用`apt`(依賴管理)和`dpkg`(包處理)進行管理。

## apt
`apt`是Debian系列發行版的前端包管理工具，用於deb處理軟件包之間的依賴關係。
主要功能如下：

- 在鏡像源中搜索、查找需要的軟件包。
- 計算軟件包的依賴。
- 系統更新。
- 查看指定軟件包的狀態。
- 變更已安裝軟件包的狀態。
- 安裝、卸載軟件包(通過dpkg)。

apt的常用指令：

```html
<!-- 更新軟件源 -->
# apt-get update
<!-- 更新無依賴變化的軟件包 -->
# apt-get upgrade
<!-- 更新所有軟件包 -->
# apt-get dist-upgrade

<!-- 安裝/卸載軟件包 -->
# apt-get install/remove [包名]
<!-- 卸載軟件包時同時刪除配置 -->
# apt-get remove --purge [包名]

<!-- 清理無用依賴 -->
# apt-get autoremove
# apt-get autoremove --purge

<!-- 查看/搜索指定包 -->
# apt-cache show/search	[包名]
<!-- 查看包的依賴 -->
$ apt-cache depends [package_name]
<!-- 計算包的反向依賴(被引用數)，輸出結果中有豎橫線｜標誌的為本地已安裝的依賴項 -->
$ apt-cache rdepends [package_name]

<!-- 將某個包標記爲自動/手動安裝 -->
# apt-mask auto/manual [package_name]
<!-- 顯示手動安裝/自動安裝的包 -->
$ apt-mask showauto/showmanaul
```

`Ubuntu 14.04`之後apt指令為部分常用指令提供了更簡單的命令形式：

```html
<!-- apt-get 相關 -->
# apt update
# apt install/remove [package_name]
# apt autoremove
# apt purge [package_name]
# apt upgrade/dist-upgrade

<!-- apt-cache 相關 -->
$ apt show/search [package_name]
# apt rdepends [package_name]
```

apt install指令可以使用`-d/--download-only`參數僅獲取安裝包而不安裝
(通常用於下載離線安裝時使用的安裝包)：

```html
<!--
使用--download-only參數會基於當前環境解析依賴，下載目標軟件包以及缺失的依賴項，
依賴項會被緩存在 /var/cache/apt/archives 路徑下
-->
# apt install -d [package_name]
# apt install --download-only [package_name]
```

### apt-file
apt包管理器默認未提供查找包內文件的功能，此類功能可通過安裝`apt-file`實現：

```
# apt install apt-file
```

使用`apt-file`：

```html
<!-- 建立/更新軟件包的文件信息 -->
# apt-file update
<!-- 查看/搜索某個文件的軟件包歸屬 -->
# apt-file search [file/path]
```

### add-apt-repository
`add-apt-repository`是Ubuntu對apt工具的功能擴展，
解決了傳統Debian係發行版添加第三方庫操作較為複雜的問題。

傳統Debian發行版添加外部倉庫需要添加source.list，並執行導入證書等操作
(詳情參見[Debian Wiki](https://wiki.debian.org/DebianRepository/UseThirdParty))；
在Ubuntu中，提供了[`Personal Package Archives`(PPA)](https://launchpad.net/ubuntu/+ppas)，
集中管理用戶創建的第三方倉庫，使用者通過add-apt-repository工具僅需單指令即可完成倉庫添加配置。

以redis為例，通常較為穩定的發行版倉庫自帶redis版本較低，Ubuntu可添加PPA來獲得最新版：

```
# add-apt-repository ppa:redislabs/redis
```

add-apt-repository包含在`software-properties-common`軟件包中，
通常Ubuntu及其衍生發行版會默認安裝該包，部分精簡鏡像(如ubuntu-core)未包含該工具，可手動安裝：

```
# apt install software-properties-common
```

## dpkg
`dpkg`是與apt前端搭配的後端包管理工具，核心功能是管理deb軟件包的資源。
主要功能如下：

- 安裝軟件包，將軟件包解壓，釋放資源到系統對應路徑。
- 卸載軟件包，移除軟件包在系統中安裝的文件、配置。
- 列出、查看、搜索軟件包內的資源。
- 查看指定軟件包的狀態。
- 變更已安裝軟件包的狀態。

dpkg的常用指令：

```html
<!-- 查詢文件屬於哪個包 -->
$ dpkg-query -S [file_name]

<!-- 安裝一個deb包 -->
# dpkg -i [deb_package]
<!-- 批量安裝deb包 -->
# dpkg -i [*.deb]
<!--
批量安裝deb包時，解析包的順序是按照包名稱的ASC碼順序，
在多數場景下該順序與實際依賴順序不符，因此會造成部分軟件包不滿足依賴而配置失敗，
安裝時搭配--force-all參數可強制配置軟件包，避免因為依賴解析順序而中斷配置流程
-->
# dpkg -i --force-all [*.deb]

<!-- 列出所有已安裝包的狀態信息 -->
$ dpkg -l
$ dpkg --list
<!-- 列出指定包名的包的狀態信息 -->
$ dpkg -l [package_name]

<!-- 包狀態帶有rc標記時說明包存在殘餘配置，根據包狀態篩選出有殘餘配置文件的包 -->
$ dpkg -l [package_name] | grep '^rc'
<!-- 清除指定包的殘餘配置 -->
# dpkg --purge [package_name]
<!-- 查找所有存在殘餘配置的包並清除殘餘配置 -->
$ dpkg -l | grep "^rc" | cut -d " " -f 3 | xargs sudo dpkg --purge

<!-- 查看指定包的詳細描述信息 -->
$ dpkg -s [package_name]
<!-- 列出指定包內包含的文件 -->
$ dpkg -L [package_name]
```

## deb打包(Binary packages)
一個二進制deb包的結構如下所示(假設當前路徑為deb包的根路徑)：

```
.
├── DEBIAN
│   ├── control
│   ├── preinst
│   ├── postinst
│   ├── prerm
│   ├── postrm
│   ├── templates
│   └── ...
└── files...
```

主要內容說明：

- `DEBIAN`路徑下存放包元數據，包括定義和維護者腳本(package maintainer scripts)

	使用`./DEBIAN/control`文件定義deb包的信息和依賴，基本格式如下：

	```
	Package: a1902-package
	Version: 1.0-1
	Section: base
	Priority: optional
	Architecture: amd64
	Depends: linux-base (>= 4), mysql-server (>= 5.7), nginx (>= 1.0), redis-server (>= 5)
	Maintainer: Dainslef Tei <dainslef@outlook.com>
	Description: This is the package of A1902 Project.
	```

	`Architecture`為軟件包支持的CPU架構，與CPU架構無關的軟件包可填寫`all`，表示支持所有架構。

	維護者腳本包括preinst、postinst、prerm、postrm等，可用於在安裝過程的前後附加一些特殊操作，
	這些腳本權限範圍需要在`0555`到`0775`之間。
	維護者腳本詳細介紹可參考[官方文檔](https://www.debian.org/doc/debian-policy/ch-maintainerscripts.html)，以及[Debian Wiki](https://wiki.debian.org/MaintainerScripts)。

	維護者腳本存在一些限制，例如不能在腳本中使用dpkg相關功能(因為執行腳本期間dpkg會被鎖定)。

- 目錄其它路徑下的文件會被視為安裝文件，執行安裝過程中會被複製到根路徑下的對應位置

	例如`./opt/xxx`會直接複製到`/opt/xxx`路徑下。
	軟件包含的文件信息會被dpkg數據庫記錄，同一個路徑不能直接被不同軟件包持有，否則安裝時會產生衝突。

使用`dpkg-deb`工具進行將一個指定目錄打包為deb包：

```
$ dpkg-deb --build [需要被打包的目錄]
```

生成的軟件包以最外層打包目錄為名，後綴為deb格式。

### debconf
[debconf](http://www.fifi.org/doc/debconf-doc/tutorial.html)提供了deb維護者常用的交互工具,
可用於生成基於TUI的交互對話框，包括輸入框、單選/多選框等多種形式。

debconf提供的Shell API位於`/usr/share/debconf/confmodule`，需要在腳本代碼開始前引入。
confmodule模塊執行機制較為特殊，加載該模塊後會reload當前腳本，
因此需要避免在腳本中段引入該模塊，否則會出現腳本內confmodule模塊引入之前的代碼被重複執行的問題。

confmodule模塊提供的API實現對話框交互：

```html
db_input <level> <package_name/template_name> <!-- 加載模板 -->
db_go <!-- 執行模板 -->
db_get <package_name/template_name> <!-- 獲取模板的執行結果，結果保存在變量RET中，使用$RET語法讀取 -->
```

模板輸入在安裝包被執行一次後會被緩存，重複安裝流程，對話框則不會再出現(狀態已被debconf數據庫中)。
若需要每次執行安裝都強制展示對話框，則應在每次調用db_input前設置模板的seen屬性：

```html
db_set <package_name/template_name> seen false <!-- 設置指定模板為未顯示狀態 -->
```

對於包含副作用的函數(如echo等)，也要避免在引入confmodule模塊前執行，
否則可能會打亂db_input/db_get相關API的輸入/輸出位置。

模板存放在`/DEBIAN/templates`文件中，格式如下：

```
Template: packagename/something
Type: [select,multiselect,string,boolean,note,text,password]
Default: [an optional default value]
Description: Blah blah blah?
  Blah blah blah. Blah blah. Blah blah blah. Blah blah. Blah blah blah.
  blah.
  ...
```

templates文件中可編寫多個模板，多個模板之間使用空行隔開。
加載模板時使用`包名/模板名稱`引用定義的模板。

使用`debconf-show`指令可以查看指定包的模板設定值：

```html
$ debconf-show 包名

<!-- 以 MySQL 為例 -->
$ debconf-show mysql-community-server
* mysql-community-server/root-pass: (password omitted)
* mysql-community-server/re-root-pass: (password omitted)
* mysql-community-server/data-dir:
* mysql-server/default-auth-override: Use Legacy Authentication Method (Retain MySQL 5.x Compatibility)
  mysql-community-server/remove-data-dir: false
  mysql-server/lowercase-table-names:
  mysql-community-server/root-pass-mismatch:
```

已存在設定值的模板再次安裝默認不會展示輸入框。
除了在API層次上使用`db_set <package_name/template_name> seen false`強制外，
亦可使用`debconf-communicate`指令清除指定包的deconf數據庫：

```html
# echo PURGE | debconf-communicate 包名 <!-- 清空指定包名下所有的模板配置 -->

<!-- 清空指定模板配置 -->
# echo RESET 模板 | debconf-communicate 包名
# echo UNREGISTER 模板 | debconf-communicate 包名
```

清空對應模板在deconf數據庫中的記錄後，下次執行模板則會正確展示模板問題的交互TUI。

### dpkg-divert
dpkg不允許兩個不同的deb包管理相同路徑的文件，因此在打包時需要注意避免與其它deb的文件衝突。
對於部分場景，可能需要用自己構建的deb包替換掉一些由系統deb包管理的文件，
此時可使用`dpkg-divert`提供的文件重命名機制，
將原本衝突的文件路徑(origin_conflict_path，打包時的路徑)在dpkg數據庫中
重命名為另一個路徑(renamed_path，該路徑在磁盤中實際不存在)，從而避免造成衝突；
但自身deb包內文件的實際路徑不變，因此可用於替換受其它deb包管理的文件。

關於使用dpkg-divert，
可參考[Ask Ubuntu](https://askubuntu.com/questions/116768/providing-a-customized-config-file-for-another-package)上的對應問題。

使用dpkg-divert創建文件重命名規則：

```html
<!--
構建包內提供的衝突文件路徑 origin_conflict_path
打包時重命名的路徑 renamed_path
指令執行成功的輸出結果：
Adding 'diversion of [origin_conflict_path] to [renamed_path] by a1902-packages'
-->
# dpkg-divert --add --package [packaage_name] --divert [renamed_path] --rename [origin_conflict_path]
```

其它dpkg-divert規則管理指令：

```html
<!---
列出當前系統中定義的文件重命名規則，輸出內容結構示例：
diversion of [origin_conflict_path] to [renamed_path] by [package]
-->
$ dpkg-divert --list

<!-- 移除指定重命名規則 -->
$ dpkg-divert --remove --package [packaage_name] [origin_conflict_path]
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

### Debian 源
`Debian`版本號有兩類：

1. 固定版本號，按照穩定程度分爲`stable`、`testing`、`unstable`、`experimental`。
1. 版本代號。

兩類作用相同，固定版本號會指向某個版本代號；
隨着開發進度的變化，固定版本號實際指向的版本代號會發生變化：

- 當前(`2017-5-11`)Debian的最新穩定版爲`Debian 8`，版本代號爲`jessie`，
則使用固定版本號`stable`指向的實際版本號即爲`jessie`。
- 當前處於開發狀態的版本爲`Debian 9`，版本代號爲`stretch`，
使用固定版本號`testing`則實際指向處於開發狀態的版本代號`stretch`。

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

### Ubuntu 源
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



# OpenCC
`OpenCC`(Open Chinese Convert)是一個中文簡繁轉換的開源項目，
支持詞彙級別的轉換、異體字轉換和地區習慣用詞轉換(牆國、臺灣、香港、日本新字體)。

項目託管在[GitHub](https://github.com/BYVoid/OpenCC)上。

## 命令行工具opencc
OpenCC提供的命令行工具`opencc`在各大平台的倉庫中均以內置，可使用對應包管理器直接安裝：

```c
# pacman -S opencc // Arch Linux
$ brew install opencc // macOS Homebrew
```

簡單的指令用法：

```
$ opencc -i <輸入文本文件> -o <輸出文本文件>
```

默認的轉換策略是將殘體字轉換為正體字。
通過`-c`參數可設定轉換文本使用的配置：

```
$ opencc -i <輸入文本文件> -o <輸出文本文件> -c <*.json>
```

文本轉換配置為json文件，OpenCC提供了常見的轉換配置：

- `s2t.json` Simplified Chinese to Traditional Chinese 簡體到繁體
- `t2s.json` Traditional Chinese to Simplified Chinese 繁體到簡體
- `s2tw.json` Simplified Chinese to Traditional Chinese (Taiwan Standard) 簡體到臺灣正體
- `tw2s.json` Traditional Chinese (Taiwan Standard) to Simplified Chinese 臺灣正體到簡體
- `s2hk.json` Simplified Chinese to Traditional Chinese (Hong Kong variant) 簡體到香港繁體
- `hk2s.json` Traditional Chinese (Hong Kong variant) to Simplified Chinese 香港繁體到簡體
- `s2twp.json` Simplified Chinese to Traditional Chinese (Taiwan Standard) with Taiwanese idiom 簡體到繁體（臺灣正體標準）並轉換爲臺灣常用詞彙
- `tw2sp.json` Traditional Chinese (Taiwan Standard) to Simplified Chinese with Mainland Chinese idiom 繁體（臺灣正體標準）到簡體並轉換爲中國大陸常用詞彙
- `t2tw.json` Traditional Chinese (OpenCC Standard) to Taiwan Standard 繁體（OpenCC 標準）到臺灣正體
- `hk2t.json` Traditional Chinese (Hong Kong variant) to Traditional Chinese 香港繁體到繁體（OpenCC 標準）
- `t2hk.json` Traditional Chinese (OpenCC Standard) to Hong Kong variant 繁體（OpenCC 標準）到香港繁體
- `t2jp.json` Traditional Chinese Characters (Kyūjitai) to New Japanese Kanji (Shinjitai) 繁體（OpenCC 標準，舊字體）到日文新字體
- `jp2t.json` New Japanese Kanji (Shinjitai) to Traditional Chinese Characters (Kyūjitai) 日文新字體到繁體（OpenCC 標準，舊字體）
- `tw2t.json` Traditional Chinese (Taiwan standard) to Traditional Chinese 臺灣正體到繁體（OpenCC 標準）



# Chrome OS
[Chrome OS](https://en.wikipedia.org/wiki/Chrome_OS)是由Google推出的基於Gentoo的Linux系統。
Chrome OS使用Chrome瀏覽器作為其主要用戶介面，
Chrome OS初期設計目標為雲操作系統，基於Google的雲服務，設備數據主要存儲在雲端；
Chrome OS本地運行的APP主要為使用Web技術的Chome App(後來被PWA取代)，面向上網本用戶和性能較低的設備；
Chrome OS發展後期則不再侷限於雲服務和Web App，
而是基於容器技術提供了完整的Linux環境(Debian發行版)以及Android App(直接內置Play Store)。

與Chrome和Chromium類似，Chrome OS也擁有開源版本[Chromium OS](https://en.wikipedia.org/wiki/Chromium_OS)，
但開源版本的Chromium OS並未提供Android容器等功能。

## 安裝 Chrome OS
Chrome OS並未直接開源，通常預裝在Chromebook中，
PC用戶想要體驗Chrome OS可以通過安裝完全開源的[Chromium OS](https://www.chromium.org/chromium-os)，
或者其它基於Chromium OS的x86發行版如neverware的[CloudReady](https://www.neverware.com/freedownload)。

GitHub上的[brunch](https://github.com/sebanc/brunch)項目提供了通用的x86_64 Chrome OS鏡像，
以及對應的安裝工具。

從[brunch項目下載頁](https://github.com/sebanc/brunch/releases)下載最新的brunch框架，
從[鏡像下載頁](https://cros.tech/device/rammus)下載最新的通用Chrome OS鏡像，
需要保證brunch框架與鏡像版本一致。

鏡像代號與CPU平台的關係：

| 代號 | 支持平台 |
| :- | :- |
| rammus | Intel CPU 1th ~ 9th |
| volteer | Intel Core CPU 10th & 11th |
| zork | AMD Ryzen CPU |

製作一個主流Linux發行版的USB安裝盤，將brunch框架和通用鏡像拷貝到安裝盤中，
考慮到鏡像大小，建議使用16GB以上的U盤。

Linux啟動U盤和對應工具鏡像準備完成後，進入Linux LiveCD環境，
在環境中安裝`pv`、`tar`、`cgpt`和`sgdisk`等工具，
解壓brunch框架：

```
$ sudo bash chromeos-install.sh -src ChromeOSx64鏡像(xxx.bin) -dst 磁盤設備路徑(如/dev/sda)
```

安裝正常結束後，重啟PC會進入Chrome OS的恢復模式，等待幾十分鐘的系統恢復過程後即可進入系統。

使用brunch框架安裝的Chrome OS默認關閉了官方的更新通道，需要使用brunch框架自帶工具進行更新：

```
$ sudo chromeos-update -r 更新鏡像 -f 磁盤路徑
```

## Linux容器問題
在`Brunch r91 stable 20210620`版本中，默認配置下安裝Linux環境會存在問題，提示：

```
Error installing Linux...
Error download the virtual machine. Please try again.
```

該問題可通過禁用`chrome://flags#crostini-use-dlc`解決。
參考[GtHub Issues](https://github.com/sebanc/brunch/issues/1124)。



# Linux常見問題記錄
記錄各類發行版使用中可能會遇到的問題。

## sshd: pam_limits(sshd:session): error parsing the configuration file: '/etc/security/limits.conf'
問題描述：<br>
修改了`/etc/security/limits.conf`，之後SSH服務無法被登陸，
每次SSH客戶端嘗試登陸均被立即關閉連接，查看SSH服務日誌出現上述錯誤。
修改limits.conf文件至正確內容後無效，依舊出現該錯誤。

問題分析：<br>
該問題是由於limits.conf文件內容語法不正確；
或是配置項存在衝突，如soft資源限制大於hard資源限制，
亦或是未配置hard資源限制導致soft限制大於默認hard限制。
需要注意，SSH服務使用了PAM(Pluggable Authentication Modules)，
對於limits.conf的修改需要重啟機器才會生效，僅修改配置/重啟服務會一直重複得到該錯誤。

解決方案：<br>
修改limits.conf至正確語法、正確配置參數，之後重啟機器。

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

解決方案：<br>
修改`/etc/init.d`對應服務的腳本文件，在腳本頂部添加`exit 0`，讓腳本文件的實際邏輯不執行直接正常退出。

## CentOS
記錄CentOS發行版中遇到的問題。

### iptable/firewalld
CentOS是默認啟用網絡防火牆的發行版：

- `CentOS 6` iptable
- `CentOS 7` firewalld

默認的防火牆策略會導致需要監聽端口的服務啟動失敗、數據包被過濾等情況。

### SELinux
CentOS默認啟用了SELinux，會導致某些需要綁定端口的服務啟動失敗。

以**nginx**為例，在**CentOS 7**下啟動失敗：

```
● nginx.service - nginx - high performance web server
   Loaded: loaded (/usr/lib/systemd/system/nginx.service; disabled; vendor preset: disabled)
   Active: failed (Result: exit-code) since Thu 2019-04-25 10:54:42 CST; 20min ago
     Docs: http://nginx.org/en/docs/
  Process: 3721 ExecStart=/usr/sbin/nginx (code=exited, status=1/FAILURE)

Apr 25 10:54:42 localhost.localdomain systemd[1]: Starting nginx - high performance web server...
Apr 25 10:54:42 localhost.localdomain nginx[3721]: nginx: [emerg] bind() to 0.0.0.0:7171 failed (13: Permission denied)
Apr 25 10:54:42 localhost.localdomain systemd[1]: nginx.service: control process exited, code=exited status=1
Apr 25 10:54:42 localhost.localdomain systemd[1]: Failed to start nginx - high performance web server.
Apr 25 10:54:42 localhost.localdomain systemd[1]: Unit nginx.service entered failed state.
Apr 25 10:54:42 localhost.localdomain systemd[1]: nginx.service failed.
```

關閉SELinux後正常。

查看系統的SELinux狀態：

```c
$ sestatus
SELinux status:                 disabled
```

臨時開啟/關閉SELinux可使用`setenforce`指令：

```c
# setenforce 0 // 關閉SELinux
# setenforce 1 // 開啟SELinux
```

永久禁用SELinux可編輯`/etc/selinux/config`文件，將`SELINUX=enforcing`修改為`SELINUX=disabled`。

### grub2-install: error: /usr/lib/grub/x86_64-efi/modinfo.sh doesn't exist. Please specify --target or --directory.
問題描述：<br>
在`CentOS 7`、UEFI引導下，使用`grub-install`指令安裝grub引導器時出現錯誤。

解決方案：<br>
該問題是CentOS 7默認安裝時未安裝`grub-efi-modules`導致的，執行安裝：

```
# yum install grub2-efi-modules
```

### http://.../repodata/repomd.xml: [Errno 14] HTTP Error 404 - Not Found Trying other mirror.
問題描述：<br>
在`CentOS 7`下，網絡正常，倉庫配置正確，但執行`yum update`出現如下錯誤：

```
[root@spark-slave3 ~]# yum update
Loaded plugins: fastestmirror
http://mirror.centos.org/centos/%24releasever/extras/x86_64/repodata/repomd.xml: [Errno 14] HTTP Error 404 - Not Found
Trying other mirror.
To address this issue please refer to the below wiki article

https://wiki.centos.org/yum-errors

If above article doesn't help to resolve this issue please use https://bugs.centos.org/.



 One of the configured repositories failed (CentOS-$releasever - Extras),
 and yum doesn't have enough cached data to continue. At this point the only
 safe thing yum can do is fail. There are a few ways to work "fix" this:

     1. Contact the upstream for the repository and get them to fix the problem.

     2. Reconfigure the baseurl/etc. for the repository, to point to a working
        upstream. This is most often useful if you are using a newer
        distribution release than is supported by the repository (and the
        packages for the previous distribution release still work).

     3. Run the command with the repository temporarily disabled
            yum --disablerepo=extras ...

     4. Disable the repository permanently, so yum won't use it by default. Yum
        will then just ignore the repository until you permanently enable it
        again or use --enablerepo for temporary usage:

            yum-config-manager --disable extras
        or
            subscription-manager repos --disable=extras

     5. Configure the failing repository to be skipped, if it is unavailable.
        Note that yum will try to contact the repo. when it runs most commands,
        so will have to try and fail each time (and thus. yum will be be much
        slower). If it is a very temporary problem though, this is often a nice
        compromise:

            yum-config-manager --save --setopt=extras.skip_if_unavailable=true

failure: repodata/repomd.xml from extras: [Errno 256] No more mirrors to try.
http://mirror.centos.org/centos/$releasever/extras/x86_64/repodata/repomd.xml: [Errno 14] HTTP Error 404 - Not Found
```

相關文秘描述參考[StackExchange](https://superuser.com/questions/1091450/centos-7-2-yum-repo-configuration-fails)。

解決方案：<br>
出現此問題是由於`/etc/yum/vars/releasever`被修改或破壞，
進而導致yum無法檢測當前系統版本，執行修復：

```
# mkdir -p /etc/yum/vars
# echo 7 > /etc/yum/vars/releasever
```

### 官方ISO在OpenStack中無法識別鏡像
問題描述：<br>
在OpenStack中使用CentOS 7使用ISO鏡像創建實例，進入安裝流程中，引導器無法識別存儲卷，無法創建硬盤。
使用外掛卷的方式安裝系統，安裝完成後無法啟動，提示`Can't find boot volume`。

解決方案：<br>
在雲平台上，應使用為雲平台設計的專屬鏡像，參考[OpenStack文檔](https://docs.openstack.org/image-guide/obtain-images.html)，從`http://cloud.centos.org/centos/7/images/`下載對應的CentOS 7的qcow2鏡像即可。
