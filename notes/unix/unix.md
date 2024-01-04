<!-- TOC -->

- [常用Unix工具指令](#常用unix工具指令)
	- [find](#find)
	- [rsync](#rsync)
	- [tee](#tee)
	- [grep](#grep)
	- [envsubst](#envsubst)
	- [sed](#sed)
		- [截取輸出](#截取輸出)
		- [文本替換](#文本替換)
		- [插入/刪除/編輯指定行數的文本](#插入刪除編輯指定行數的文本)
	- [進程管理](#進程管理)
	- [日誌記錄](#日誌記錄)
	- [BIOS信息](#bios信息)
- [Linux Standard Base](#linux-standard-base)
	- [Filesystem Hierarchy Standard](#filesystem-hierarchy-standard)
- [Linux音頻架構](#linux音頻架構)
	- [ALSA](#alsa)
	- [PulseAudio](#pulseaudio)
- [用戶管理](#用戶管理)
- [FTP（File Transfer Protocol）](#ftpfile-transfer-protocol)
	- [連接服務器](#連接服務器)
	- [常用指令](#常用指令)
- [SSH（Secure Shell）](#sshsecure-shell)
	- [遠程登錄](#遠程登錄)
	- [SSH 配置](#ssh-配置)
	- [配置免密登陸](#配置免密登陸)
	- [關閉主機Key檢測](#關閉主機key檢測)
	- [SSH Tunnel（SSH隧道）](#ssh-tunnelssh隧道)
- [Linux引導配置](#linux引導配置)
	- [GNU GRUB](#gnu-grub)
		- [GRUB安裝與配置](#grub安裝與配置)
		- [安裝GRUB引導器](#安裝grub引導器)
		- [修復GRUB引導](#修復grub引導)
	- [systemd-boot](#systemd-boot)
- [壓縮/解壓](#壓縮解壓)
	- [7z](#7z)
- [ulimit](#ulimit)
	- [ulimit配置文件](#ulimit配置文件)
	- [prlimit](#prlimit)
	- [文件描述符限制](#文件描述符限制)
	- [Core Dump（核心轉儲）](#core-dump核心轉儲)
- [文件系統](#文件系統)
	- [fdisk](#fdisk)
	- [parted](#parted)
	- [擴容分區](#擴容分區)
	- [縮容分區](#縮容分區)
	- [flock（文件鎖）](#flock文件鎖)
	- [文件特殊權限](#文件特殊權限)
		- [setuid / setgid / sticky](#setuid--setgid--sticky)
		- [lsattr / chattr](#lsattr--chattr)
		- [chflags](#chflags)
	- [LVM (Logical Volume Manager)](#lvm-logical-volume-manager)
		- [LVM基本操作](#lvm基本操作)
		- [Physical Volume（PV，物理卷）](#physical-volumepv物理卷)
		- [Volume Group（VG，卷組）](#volume-groupvg卷組)
		- [Logical Volume（LV，邏輯卷）](#logical-volumelv邏輯卷)
		- [Thinly-Provisioned Logical Volumes（精簡邏輯卷）](#thinly-provisioned-logical-volumes精簡邏輯卷)
		- [邏輯卷狀態和塊設備不顯示問題](#邏輯卷狀態和塊設備不顯示問題)
- [時間管理](#時間管理)
	- [硬件時間](#硬件時間)
	- [NTP (Network Time Protocol)](#ntp-network-time-protocol)
		- [ntp服務配置](#ntp服務配置)
			- [ntp客戶端配置](#ntp客戶端配置)
			- [ntp服務端配置](#ntp服務端配置)
			- [ntp服務管理指令](#ntp服務管理指令)
	- [chrony時間服務](#chrony時間服務)
- [curl](#curl)
	- [HTTP請求](#http請求)
		- [HTTP文件下載](#http文件下載)
	- [用戶認證](#用戶認證)
	- [FTP 操作](#ftp-操作)
- [Suspend 和 Hibernate](#suspend-和-hibernate)
- [systemd](#systemd)
	- [systemd服務管理](#systemd服務管理)
	- [rc.local](#rclocal)
	- [systemd服務後綴](#systemd服務後綴)
	- [systemd服務分析](#systemd服務分析)
	- [編寫systemd服務](#編寫systemd服務)
	- [其它systemd系統管理工具](#其它systemd系統管理工具)
		- [loginctl](#loginctl)
- [網絡](#網絡)
	- [網絡配置](#網絡配置)
		- [ifupdown（Ubuntu（17.10之前）/ Debian）](#ifupdownubuntu1710之前-debian)
		- [Netplan（Ubuntu17.10之後）](#netplanubuntu1710之後)
		- [NetworkManager](#networkmanager)
		- [systemd-networkd](#systemd-networkd)
		- [`Failed to configure DHCPv4 client: No such file or directory`](#failed-to-configure-dhcpv4-client-no-such-file-or-directory)
	- [route（路由）](#route路由)
		- [route](#route)
		- [ip route](#ip-route)
		- [路由轉發](#路由轉發)
		- [追蹤路由](#追蹤路由)
	- [ARP（Address Resolution Protocol，地址解析協議）](#arpaddress-resolution-protocol地址解析協議)
	- [Bonding](#bonding)
	- [netstat & ss](#netstat--ss)
	- [mii-tool & ethtool](#mii-tool--ethtool)
	- [tcpdump](#tcpdump)
	- [Netcat (nc)](#netcat-nc)
		- [客戶端/服務端模式](#客戶端服務端模式)
		- [數據傳送](#數據傳送)
		- [Ncat](#ncat)
	- [iptables/nftables (netfilter)](#iptablesnftables-netfilter)
		- [iptables基本操作](#iptables基本操作)
- [Keepalived](#keepalived)
	- [vrrp_instance](#vrrp_instance)
	- [vrrp_sync_group](#vrrp_sync_group)
	- [Keepalived完整示例](#keepalived完整示例)
- [性能監控與測試](#性能監控與測試)
	- [Load Averages](#load-averages)
	- [cpupower](#cpupower)
	- [ps](#ps)
		- [自定義ps輸出內容格式](#自定義ps輸出內容格式)
		- [使用ps查看進程狀態](#使用ps查看進程狀態)
		- [查看LWP線程信息](#查看lwp線程信息)
	- [procps](#procps)
		- [top](#top)
	- [iftop](#iftop)
	- [sysstat](#sysstat)
		- [pidstat](#pidstat)
		- [mpstat](#mpstat)
		- [iostat](#iostat)
	- [sysbench](#sysbench)
	- [fio](#fio)
	- [RT-Tests](#rt-tests)
		- [cyclictest](#cyclictest)
	- [iperf / qperf](#iperf--qperf)
	- [HTTP壓測工具](#http壓測工具)
- [通知服務（Notification）](#通知服務notification)
	- [libnotify](#libnotify)
	- [Dunst](#dunst)
		- [Dunst配置](#dunst配置)
- [終端模擬器](#終端模擬器)
	- [VTE](#vte)
		- [VTE2](#vte2)
		- [VTE3](#vte3)
		- [複製粘貼快捷鍵](#複製粘貼快捷鍵)
	- [Kitty](#kitty)
- [Linux字體（fontconfig）](#linux字體fontconfig)
	- [管理字體](#管理字體)
	- [字體配置](#字體配置)
- [Debian系列發行版包管理](#debian系列發行版包管理)
	- [apt](#apt)
		- [apt下載依賴](#apt下載依賴)
		- [apt依賴類型](#apt依賴類型)
		- [apt-file](#apt-file)
		- [add-apt-repository](#add-apt-repository)
	- [dpkg](#dpkg)
	- [deb打包 (Binary packages)](#deb打包-binary-packages)
		- [debconf](#debconf)
		- [dpkg-divert](#dpkg-divert)
	- [apt軟件源配置](#apt軟件源配置)
		- [Debian源](#debian源)
		- [Ubuntu源](#ubuntu源)
	- [backports倉庫與倉庫優先級](#backports倉庫與倉庫優先級)
	- [apt-mirror](#apt-mirror)
		- [apt-mirror本地源配置](#apt-mirror本地源配置)
		- [使用apt-mirror本地源](#使用apt-mirror本地源)
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
		- [iptables/firewalld](#iptablesfirewalld)
		- [SELinux](#selinux)
		- [grub2-install: error: /usr/lib/grub/x86_64-efi/modinfo.sh doesn't exist. Please specify --target or --directory.](#grub2-install-error-usrlibgrubx86_64-efimodinfosh-doesnt-exist-please-specify---target-or---directory)
		- [http://.../repodata/repomd.xml: [Errno 14] HTTP Error 404 - Not Found Trying other mirror.](#httprepodatarepomdxml-errno-14-http-error-404---not-found-trying-other-mirror)
		- [官方ISO在OpenStack中無法識別鏡像](#官方iso在openstack中無法識別鏡像)

<!-- /TOC -->



# 常用Unix工具指令
一些Unix常用指令的簡介。

## find
`find`用於查找滿足條件的文件，與其它指令搭配起到處理特定類型文件的作用。

按照名稱查找指定路徑下的文件：

```
$ find 路徑 -name 文件名稱
```

按照文件類型查找指定路徑下的文件：

```html
<!--
文件類型：
b 塊設備
c 字符設備
d 目錄
f 普通文件
l 符號鏈接
p 管道
s 套接字
-->
$ find 路徑 -type 文件類型
$ find 路徑 -type d <!-- 查找路徑下的所有目錄 -->
$ find 路徑 -type f <!-- 查找路徑下的所有文件 -->

<!-- 查找空文件或目錄 -->
$ find 路徑 -empty

<!-- 查找空文件目錄參數可與查找類型參數組合使用 -->
$ find 路徑 -empty -type d
$ find 路徑 -empty -type f
```

查找時可排除指定目標路徑：

```
$ find 路徑 -name 文件名稱 -not -path 排除路徑
```

按照文件`inode`查找文件，可查詢一個inode對應的多個硬鏈接文件：

```html
$ ls -i <!-- 查看文件inode -->
$ find 路徑 -inum inode值
```

使用`-exec`參數對查找到目標執行額外附加操作：

```html
$ find 路徑 -exec 指令 \; <!-- 指令需要以分號結尾 -->
```

exec參數執行的指令以`;`符號結尾，指令中可使用`{}`符號代表當前查找到的路徑，字符需要**轉義**。

示例：

```html
<!-- 查找當前路徑下所有文件（排除目錄，並將權限設置爲644） -->
$ find . -type f -exec chmod 644 \{\} \;
```

## rsync
`rsync`工具用於文件同步。

基本操作，同步兩個目錄：

```html
<!-- 將源路徑下的內容同步到目標路徑下 -->
$ rsync -r 源路徑/ 目標路徑

<!-- 在目標路徑下創建源路徑目錄 -->
$ rsync -r 源路徑 目標路徑
```

rsync支持通過SSH進行文件同步：

```
$ rysnc -r 本地路徑 用戶@IP:遠程路徑
$ rysnc -r 用戶@IP:遠程路徑 本地路徑
```

常用參數說明：

| 參數 | 說明 |
| :- | :- |
| -z / --compress | 傳輸數據時使用壓縮算法，壓縮算法對機器資源消耗較大，僅推薦在配置較高的機器中使用 |
| -a / --archive | 等價於`-rlptgoD`，同步幾乎所有內容（但不包括硬鏈接） |
| -v / --verbose | 展示同步列表，`-vv`可展示跳過的路徑，`-vvv`可展示程序的調試信息 |
| -n / --dry-run | 僅列出待同步的內容而非實際進行操作 |
| -P / --progress | 展示同步任務的進度（包括同步列表，該參數替代-v） |

組合常用指令：

```html
<!-- 使用壓縮傳輸所有數據到目標路徑下 -->
$ rsync -avzP 源路徑 目標路徑

<!-- 直接傳輸所有數據到目標路徑下 -->
$ rsync -avP 源路徑 目標路徑
```

## tee
`tee`用於將標準輸入拷貝到標準輸出中，同時寫入一個或**多個**文件，常用於搭配管道操作。

指令語法：

```html
$ tee [-ai] [file ...]
```

參數說明：

- `-a` 默認寫入文件時使用重寫方式，使用該參數則變為追加新增內容到文件末尾
- `-i` 執行該指令時忽略SIGINT信號

使用實例：

```html
<!-- 將字符 abcd 寫入test1.txt,test2.txt兩個文件中 -->
$ echo abcd | tee test1.txt test2.txt
$ cat test1.txt
abcd
$ cat test2.txt
abcd
<!-- 以追加模式增加文本內容 -->
$ echo cdef | tee -a test1.txt
$ cat test1.txt
abcd
cdef
```

## grep
`grep`用於搜索文本中包含指定內容的行，常用於管道操作中處理其它指令的輸出結果。

```html
<!-- 從給定的內容中查找包含 xxx 的內容 -->
$ grep xxx
<!-- 從給定的內容中查找以 xxx 起始的內容 -->
$ grep ^xxx
<!-- 從給定的內容中排除包含 xxx 的內容 -->
$ grep -v xxx

<!-- 僅輸出指定次數的匹配內容 -->
$ grep -m 最大匹配次數 xxx
<!-- 僅輸出首個匹配內容 -->
$ grep -m 1 xxxs

<!-- 查找內容時，輸出目標內容附近指定行數相關的內容 -->
$ grep -C 行數

<!-- 查找 xxx (嚴格匹配) -->
$ grep -w xxx
<!-- 等價於grep -w -->
$ grep '\<xxx\>'

<!-- 匹配 xxx 時忽略大小寫 -->
$ grep -i xxx

<!-- 基於正則匹配 -->
$ grep -P xxx
$ grep -Po xxx <!-- 僅輸出匹配的部分-->
```

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

### 截取輸出
sed支持按行截取命令行輸出：

```html
<!-- 行數從 1 開始計數 -->
$ sed -n 行號p <!-- 截取指定行的輸出 -->
$ sed -n 起始行,結束行p <!-- 截取指定起止範圍的行-->
```

示例：

```html
$ echo a\nb\nc\nd
a
b
c
d
<!-- 獲取第2行輸出 -->
$ echo a\nb\nc\nd | sed -n 2p
b
<!-- 獲取第2～4行內容 -->
$ echo a\nb\nc\nd | sed -n 2,4p
b
c
d
```

### 文本替換
使用GNU sed工具可實現文本替換：

```html
<!-- 默認將替換後的內容輸出到終端 -->
$ sed 's/舊文本/新文本/' 文件路徑
<!--
當需要替換的目標文本中包含替換標識符時，需要使用 \ 進行轉義
用於切分源文本和被替換文本的標識符可以自定，比如使用 _ 或 - . ? < > 以及空格等等
可根據需要規避的文本靈活選擇替換標識符
 -->
$ sed 's 舊文本 新文本 ' 文件路徑
$ sed 's.舊文本.新文本.' 文件路徑
$ sed 's-舊文本-新文本-' 文件路徑

<!-- 默認替換操作僅替換首個匹配的內容，替換所有內容需表達式末尾添加字母 g -->
$ $ sed 's/舊文本/新文本/g' 文件路徑

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

<!-- 使用其它替換標誌符作用類似 -->
$ sed 's.$TEST.test.' test.txt
test output
$ sed 's-$TEST-test-' test.txt
test output

$ sed -i 's/$TEST/test/' test.txt
$ cat test.txt
test output
$ echo '$TEST output' | sed 's/$TEST/test/'
test output

$ echo aabbaa > test.txt
$ cat test.txt
aabbaa
<!-- 普通替換表達式僅替換首個匹配內容 -->
$ sed 's/aa/cc/' test.txt
ccbbaa
<!-- 匹配表達式末尾添加字母 g ，則替換所有匹配內容 -->
$ sed 's/aa/cc/g' test.txt
ccbbcc
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

### 插入/刪除/編輯指定行數的文本
sed支持在操作前添加**行號**，對指定行數的文本進行操作，操作指令包括：

- `i` 插入內容
- `d` 刪除內容
- `s` 替換內容

指令用法：

```html
<!-- 在指定行前插入內容 -->
$ sed '行號 i 內容' 文件路徑
<!-- 不使用行號，則在每一行插入內容 -->
$ sed 'i 內容' 文件路徑

<!-- 刪除指定行號的內容 -->
$ sed '行號 d' 文件路徑
<!-- 不使用行號則刪除所有內容 -->
$ sed 'd' 文件路徑

<!-- 替換指定行的文本 -->
$ sed '行號 s 舊文本 新文本 '
```

示例：

```html
$ echo 1111\n2222\n3333 > test.txt
$ cat test.txt
1111
2222
3333

<!-- 指定行添加內容 -->
$ sed '3 i xxxx' test.txt
1111
2222
xxxx
3333
<!-- 向所有行添加內容 -->
$ sed 'i xxxx' test.txt
xxxx
1111
xxxx
2222
xxxx
3333

<!-- 刪除指定行 -->
$ sed '3 d' test.txt
1111
2222
```

## 進程管理
`ps`指令用於查看進程狀態：

```html
$ ps u -p 進程號 <!-- 打印指定 pid 進程信息詳情 -->
$ ps au <!-- 打印當前所有進程信息詳情 -->
$ ps ux <!-- 打印所有進程信息詳情 -->
$ ps -o cmd,user,stat,pid,ppid,pgid,sid,tpgid,tty <!-- 輸出指定內容的進程信息 -->
```

`kill`指令向進程發送信號：

```html
# kill 進程號 <!-- 向進程發送信號，默認發送的信號為 TERM（終止信號） -->
# kill -9 進程號 <!-- 強制殺死進程（發送SIGKILL信號，該信號不可被忽略） -->
# kill -信號值 進程號 <!-- 向指定進程發送指定編號的信號 -->
# kill -s 信號值 進程號 <!-- 向指定進程發送指定名稱的信號 -->
$ kill -l <!-- 列出系統支持的信號 -->
```

除了使用pid的kill指令外，Linux和macOS(BSD)都支持使用進程名稱的`pkill/killall`，
指令語法與kill指令類似：

```
# killall 進程名
# killall -9 進程名
# killall -信號值 進程名

# pkill 進程名
# pkill -9 進程名
# pkill -信號值 進程名
```

Linux和macOS(BSD)都提供了`pgrep`指令用於根據進程名稱查詢pid的功能，
Linux的`sysvinit-tools`還提供了`pidof`工具，功能與pgrep類似：

```html
$ pgrep 進程名 <!-- 查詢指定進程名稱的pid -->
$ pgrep -l 進程名 <!-- 查詢指定進程的pid，同時輸出進程名稱 -->
$ pidof 進程名
```

pidof/pgrep指令與kill指令組合，可實現類似pkill/killall指令的效果：

```
# kill -9 $(pidof 進程名)
# kill -9 $(pgrep 進程名)
```

pidof/pgrep等指令功能可使用管道組合指令模擬：

```
$ ps A | grep 進程名 | awk '{print $1}'
```

## 日誌記錄
使用傳統syslog服務的Linux發行版日誌存放在`/var/log`路徑下，以純文本形式存儲；
使用systemd服務的Linux發行版日誌使用二進制格式記錄，通過`journalctl`工具查看。

```html
<!-- 查看登錄記錄、開關機記錄 -->
$ last

<!-- 輸出內核信息 -->
$ dmesg

<!-- 查看systemd日誌 -->
$ journalctl
<!-- 倒序查看systemd日誌 -->
$ journalctl -r
<!-- 查看指定服務的日誌 -->
$ journalctl -u 服務名稱
```

## BIOS信息
使用`dmidecode`指令輸出機器的DMI（SMBIOS）表，並以人類可讀的形式展示：

```
$ dmidecode
...
Handle 0x0002, DMI type 2, 8 bytes.  Base Board Information
        Manufacturer: Intel
        Product Name: C440GX+
        Version: 727281-001
        Serial Number: INCY92700942
...
```

其中`Product Name`項通常為設備型號：

```
$ dmidecode | grep "Product Name"
	Product Name: IBM System x3650 M4: -[79152VT]-
	Product Name: 00MV214
```



# Linux Standard Base
[Linux Standard Base（LSB）](https://refspecs.linuxfoundation.org/lsb.shtml)
由某些Linux發行版在Linux基金會的組織下制定的Linux系統結構標準。

LSB基於POSIX、 Single UNIX Specification（SUS）以及某些其它開放標準，
同時在某些領域做了一些擴展。

LSB的目標是開發和促成一組標準，以提升Linux發行版之間的兼容性，
使得軟件能夠運行在任意遵循標準的系統中，即使是以二進制形式。
並且LSB將幫助協調和吸引軟件廠商來為Linux移植和編寫軟件產品。

## Filesystem Hierarchy Standard
[Filesystem Hierarchy Standard（FHS）](https://www.pathname.com/fhs/)
是LSB標準的一部分，定義了Linux的標準目錄結構。

根路徑下應包含的子目錄：

| 目錄 | 說明 |
| :- | :- |
| bin | Essential command binaries |
| boot | Static files of the boot loader |
| dev | Device files |
| etc | Host-specific system configuration |
| lib | Essential shared libraries and kernel modules |
| media | Mount point for removeable media |
| mnt | Mount point for mounting a filesystem temporarily |
| opt | Add-on application software packages |
| sbin | Essential system binaries |
| srv | Data for services provided by this system |
| tmp | Temporary files |
| usr | Secondary hierarchy |
| var | Variable data |

特殊目錄：

| 目錄 | 說明 |
| :- | :- |
| home | User home directories (optional) |
| lib<qual> | Alternate format essential shared libraries (optional) |
| root | Home directory for the root user (optional) |



# Linux音頻架構
Linux的音頻子系統早期為`OSS`（Open Sound System），
因為許可證問題之後被替換為ALSA（Advanced Linux Sound Architecture）。

## ALSA
`ALSA`是內核內置的模塊，無需額外安裝，[`alsa-utils`](https://github.com/alsa-project/alsa-utils)
項目提供了ALSA的用戶態工具，常用工具包括`amixer`和`alsamixer`等。

alsamixer是TUI的音量配置工具，支持終端下的TUI交互。

amixer命令行音量配置工具，常用指令如下：

```html
<!-- 基本指令語法 -->
$ amixer 操作 音頻通道 <!-- 通常通道設置為Master -->

$ amixer get Master <!-- 獲取音量 -->
$ amixer set Master 百分比 <!-- 設置音量百分比，如 10%（需要寫出百分號） -->
$ amixer set Master 百分比+/- <!-- 按百分比增減音量 -->
```

amxier與alsamixer默認使用不同的音量比例計算方式，
amixer默認使用當前音量數值除以音量數值上限直接計算百分比，
alsamixer則使用另一套對更符合聽覺的算法計算音量百分比；
添加`-M`參數則會使amixer採用與alsamixer相同的音量計算方式：

```
$ amixer set/get -M Master ...
```

輸出信息示例：

```html
<!-- 查看音量輸出 -->
$ amixer get Master
Simple mixer control 'Master',0
  Capabilities: pvolume pvolume-joined pswitch pswitch-joined
  Playback channels: Mono
  Limits: Playback 0 - 87
  Mono: Playback 77 [89%] [-7.50dB] [on]

<!-- 使用正則提取音量輸出的百分比數值 -->
$ amixer get Master | grep -Po '\d+(?=%)'
89

<!-- 使用正則抓取音頻狀態 -->
$ amixer get Master | grep -Po "\[o\S+(?!])" | grep -Po "\w+"
on
```

## PulseAudio
`PulseAudio`是用於`POSIX`系統的音頻系統，是音頻程序的代理（proxy）。
PulseAudio允許用戶對音頻應用和音頻硬件之間傳遞的音頻數據執行高級操作。
使用音頻服務可輕鬆實現諸如將音頻傳輸到另一臺機器上、改變樣本格式或通道數量、混合多種音頻等功能。

PulseAudio爲Linux系統設計，現在也被移植到了`Solaris`、`FreeBSD`、`NetBSD`、
`macOS`、`Windows 2000`、`Windows XP`等系統上。

使用PulseAudio提供的`pactl`以及`pacmd`控制、調整音頻設備。

pactl提供了常用的功能：

```html
<!-- 展示音頻輸出設備信息（簡短輸出） -->
$ pactl list sinks short
<!-- 展示完整音頻設備信息 -->
$ pactl list

<!-- 調整設備音量，"調整幅度" 格式爲百分數如 "+5%" -->
$ pactl set-link-volume 音頻設備編號 調整幅度
<!-- 開啓/關閉靜音 -->
$ pactl set-sink-mute 音頻設備編號 1/0/yes/no/true/false
<!-- 切換靜音狀態 -->
$ pactl set-sink-mute 音頻設備編號 toggle
```

pactl的音頻設備輸出信息示例：

```html
<!-- 簡短信息，僅包含輸出設備編號、狀態等 -->
$ pactl list sinks short
0	alsa_output.pci-0000_00_1f.3.analog-stereo	module-alsa-card.c	s16le 2ch 44100Hz	SUSPENDED

<!-- 音頻輸出設備完整信息 -->
$ pactl list sinks
Sink #0
	State: SUSPENDED
	Name: alsa_output.pci-0000_00_1f.3.analog-stereo
	Description: Built-in Audio Analog Stereo
	Driver: module-alsa-card.c
	Sample Specification: s16le 2ch 44100Hz
	Channel Map: front-left,front-right
	Owner Module: 6
	Mute: no
	Volume: front-left: 39294 /  60% / -13.33 dB,   front-right: 39294 /  60% / -13.33 dB
	        balance 0.00
	Base Volume: 65536 / 100% / 0.00 dB
	Monitor Source: alsa_output.pci-0000_00_1f.3.analog-stereo.monitor
	Latency: 0 usec, configured 0 usec
	Flags: HARDWARE HW_MUTE_CTRL HW_VOLUME_CTRL DECIBEL_VOLUME LATENCY
	Properties:
		alsa.resolution_bits = "16"
		device.api = "alsa"
		device.class = "sound"
		alsa.class = "generic"
		alsa.subclass = "generic-mix"
		alsa.name = "ALC233 Analog"
		alsa.id = "ALC233 Analog"
		alsa.subdevice = "0"
		alsa.subdevice_name = "subdevice #0"
		alsa.device = "0"
		alsa.card = "0"
		alsa.card_name = "HDA Intel PCH"
		alsa.long_card_name = "HDA Intel PCH at 0xb1128000 irq 133"
		alsa.driver_name = "snd_hda_intel"
		device.bus_path = "pci-0000:00:1f.3"
		sysfs.path = "/devices/pci0000:00/0000:00:1f.3/sound/card0"
		device.bus = "pci"
		device.vendor.id = "8086"
		device.vendor.name = "Intel Corporation"
		device.product.id = "9d70"
		device.product.name = "Sunrise Point-LP HD Audio"
		device.form_factor = "internal"
		device.string = "front:0"
		device.buffering.buffer_size = "352800"
		device.buffering.fragment_size = "176400"
		device.access_mode = "mmap+timer"
		device.profile.name = "analog-stereo"
		device.profile.description = "Analog Stereo"
		device.description = "Built-in Audio Analog Stereo"
		module-udev-detect.discovered = "1"
		device.icon_name = "audio-card-pci"
	Ports:
		analog-output-speaker: Speakers (type: Speaker, priority: 10000, availability unknown)
		analog-output-headphones: Headphones (type: Headphones, priority: 9900, not available)
	Active Port: analog-output-speaker
	Formats:
		pcm
```

pacmd相比pactl提供了完整的PulseAudio功能，
支持pactl的全部指令（部分指令語法存在差異），輸出結果格式略有不同。

```html
<!-- 看音頻輸出設備的信息，類似於 pactl list sinks -->
$ pacmd list-sinks
<!-- pacmd 的 set-link-volume 參數不支持使用百分比調整音量 -->
$ pacmd set-link-volume 音頻設備編號 音量數值
```

pactl工具缺少一些實用功能（直接提取音量、靜音狀態等），需要組合實用指令並提取輸出。
獲取音量：

```html
<!-- 從輸出中查找音量部分，截取 Volume 行所在的內容。-->
$ pactl list sinks | grep '^[[:space:]]Volume:' | head -n 1 | tail -n 1 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,'
```

獲取靜音狀態：

```html
<!-- 截取 Mute 輸出行 -->
$ pactl list sinks | awk '/Mute/ { print $2 }'
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

```html
<!-- 創建用戶 -->
# useradd 用戶名
<!-- 創建用戶，併爲該用戶創建對應的同名家目錄 -->
# useradd 用戶名 -m
<!-- 創建用戶同時指定密碼 -->
# useradd 用戶名 -p 密碼
<!-- 創建用戶時指定默認用戶組（默認會創建用戶名同名用戶組） -->
# useradd 用戶名 -g 用戶組
<!-- 創建用戶時指定默認Shell -->
# useradd 用戶名 -s Shell路徑

<!-- 刪除用戶 -->
# userdel 用戶名
<!-- 刪除用戶，並同時刪除該用戶的家目錄 -->
# userdel -r 用戶名

<!-- 修改用戶相關信息，如密碼、家目錄、登錄Shell、用戶組等 -->
# usermod
```

用戶組管理：

```html
<!-- 創建用戶組 -->
# groupadd 用戶組名

<!-- 刪除用戶組，用戶組需要爲空 -->
# groupdel 用戶組名

<!-- 將用戶添加到用戶組中 -->
# usermod -a -G 用戶組 用戶名
<!-- 強制設置用戶的用戶組，若原先用戶加入的組不在給出的組列表中，將被移除原先的組(用戶的主組除外) -->
# usermod -G 用戶組1,用戶組2,... 用戶名
```

修改文件用戶、用戶組：

```html
<!-- 更改指定文件所有者 -->
$ chown 選項 用戶名:用戶組 文件名
<!-- 遞歸更改路徑下所有文件歸屬 -->
$ chown -R 用戶名:用戶組 路徑

<!-- 更改指定文件所屬用戶組 -->
$ chgrp 選項 用戶組名 文件名
```



# FTP（File Transfer Protocol）
Windows系統下提供了`ftp`命令行工具用於訪問FTP服務器進行交互。

## 連接服務器
使用`ftp`指令與服務端建立連接：

```
$ ftp 服務端IP地址
```

成功建立連接後，會提示輸入FTP用戶名/密碼，如下所示：

```
> ftp 服務端IP地址
連接到 [服務端IP地址]。
...
用戶(IP地址:(none)): Xxx
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
ftp> open 服務端IP地址
連接到 [服務端IP地址]。
...
用戶(IP地址:(none)): Xxx
331 Password required for Xxx
密碼:
230 User Xxx logged in
ftp>
```

## 常用指令
`ftp shell`中常用指令：

| 指令 | 說明 |
| :- | :- |
| !指令 | 使用系統`Shell`執行指令 |
| quit | 退出`ftp shell` |
| lcd/cd | 跳轉本地/遠程目錄 |
| open/close | 打開關閉連接 |
| ls/dir | 查看`FTP`目錄 |
| put/send | 向`FTP`發送文件 |
| get/recv | 接收來自`FTP`的文件 |
| mkdir/rmdir | 創建/刪除`FTP`目錄 |
| delete | 刪除`FTP`的文件 |
| rename | 重命名`FTP`的文件 |



# SSH（Secure Shell）
`SSH`全稱`Secure Shell`，是一種加密的網絡傳輸協議。
SSH通過在網絡中建立`Secure Channel`（安全通道）實現SSH客戶端與服務端之間的連接。

SSH常用在Unix系統中，用於傳輸命令行界面和遠程執行指令。
相比使用明文傳輸的Telnet協議，SSH能夠保證網絡環境中信息加密完整可靠。

SSH的主流實現是`OpenSSH`（全稱`OpenBSD Secure Shell`）。

## 遠程登錄
使用`ssh`指令遠程登錄配置了SSH服務的主機：

```html
$ ssh 用戶名@主機名/IP

<!-- 使用 -p 參數指定遠程登錄端口，SSH服務默認端口爲22 -->
$ ssh 用戶名@主機名/IP -p 端口

<!-- 使用 -t 參數指定使用的shell，如bash/zsh/fish等 -->
$ ssh 用戶名@主機名/IP -t shell類型
```

## SSH 配置
SSH服務相關配置文件位於`/etc/ssh`路徑下：

| 配置文件 | 簡介 | 配置項手冊 |
| :- | :- | :- |
| `/etc/ssh/ssh_config` | ssh指令使用的配置 | `man ssh_config` |
| `/etc/ssh/sshd_config` | sshd服務使用的配置 | `man sshd_config` |

常用SSH服務配置：

- `PasswordAuthentication`

	配置是否允許密碼登入，公網環境建議關閉。

	| 配置值 | 含義 |
	| :- | :- |
	| no | 關閉（默認） |
	| yes | 開啓 |

- `PermitRootLogin`

	配置SSH服務是否允許root登陸，公網環境建議關閉。

	| 配置值 | 含義 |
	| :- | :- |
	| yes（默認） | 允許root用戶登陸 |
	| no | 不允許root用戶登陸 |
	| without-password | 可登陸root用戶，但不能以密碼驗證的方式登陸（可用key驗證） |
	| forced-commands-only | 可登陸root用戶，但登陸後僅能執行指令後退出，不能交互 |

- `UseDNS`

	配置是否啓用DNS PTR。
	動態IP通常不會有PTR記錄，開啓DNS PTR有時導致SSH登陸過慢。

	| 配置值 | 含義 |
	| :- | :- |
	| yes | 開啓 |
	| no | 關閉 |

對於位於公網環境SSH服務器，為防止非法用戶暴力破解SSH密碼，建議調整下列配置：

```yaml
LoginGraceTime 5s # 服務端關閉未成功認證連接的時間，默認值2m
MaxAuthTries 1 # 設置每個連接的最大認證嘗試次數，默認值6

PermitRootLogin no # 默認值yes，公網環境不建議允許root用戶直接登入
PasswordAuthentication no # 默認值yes，公網環境不建議允許密碼登入
```

公網環境下，防火牆可能會定期關閉不活躍的連接，會導致SSH連接被異常關閉，
可通過配置心跳相關參數定期發送心跳包，避免SSH連接被防火牆異常關閉：

```yaml
TCPKeepAlive yes # 設置是否在空閒時自動發送心跳包，默認值yes，需要保證該配置開啟後續的心跳參數才會生效
ClientAliveInterval 10s # 設置心跳包間隔（秒），默認值為0（不會自動發送心跳包），該間隔應小於防火牆關閉連接的時間，若值較大可能造成心跳包未發送連接就已被關閉
```

## 配置免密登陸
默認配置下，登陸SSH需要密碼，當部署一些依賴SSH協議的分佈式服務時（如`Hadoop`、`Zookeeper`、`Kafka`等），
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

```html
<!-- 將 ~/.ssh/id_rsa.pub 中記錄的公鑰加入目標主機 -->
$ ssh-copy-id 目標用戶名@目標主機名或地址

<!-- 指定公鑰加入目標主機 -->
$ ssh-copy-id 目標用戶名@目標主機名或地址 -I 公鑰路徑
```

正確生成當前機器的公鑰、私鑰，
並將公鑰寫入目標機器authorized_keys文件中即可實現SSH免密登錄目標機器。

使用ssh指令登陸目標機器時，默認使用`~/.ssh/id_rsa`文件做爲私鑰進行驗證，
若需要指定私鑰文件，可以添加`-i`參數：

```c
$ ssh -i 私鑰路徑 目標用戶名@目標主機地址
```

免密登錄失敗可查看相關日誌信息：

```html
<!-- CentOS -->
/var/log/secure
/var/log/audit/audit.log

<!-- Debian/Ubuntu -->
/var/log/auth.log
```

或使用`ssh -v/-vv/-vvv`在執行登錄指令時輸出額外的日誌信息。

## 關閉主機Key檢測
默認配置下，SSH首次連接時將連接的目標主機密鑰信息記錄在`~/.ssh/known_hosts`文件中，
之後每次登入該主機均會檢測目標主機與文件記錄中的是否一致，若不一致則拒絕登入，輸出信息：

```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that the RSA host key has just been changed.
The fingerprint for the RSA key sent by the remote host is
*****
Please contact your system administrator.
Add correct host key in /home/user/.ssh/known_hosts to get rid of this message.
Offending key in /home/user/.ssh/known_hosts:1
RSA host key for ***** has changed and you have requested strict checking.
Host key verification failed.
```

刪除~/.ssh/known_hosts中對應的記錄可恢復登入，
但若目標IP為Floating IP，IP後的主機會發生變化，
則應當關閉Key檢測，臨時禁用主機Key檢測可在ssh指令中添加參數：

```
$ ssh -o StrictHostKeyChecking=no 用戶名@目標地址或主機名
```

永久關閉主機Key檢測需要修改`~/.ssh/config`（用戶配置）或`/etc/ssh/ssh_config`（全局配置）：

```
Host *
	StrictHostKeyChecking no
	UserKnownHostsFile=/dev/null
```

該配置可限定主機地址範圍：

```
Host 192.168.0.*
	StrictHostKeyChecking no
	UserKnownHostsFile=/dev/null
```

## SSH Tunnel（SSH隧道）
SSH自帶了Tunnel功能，可在本機監聽指定端口，並將該端口的流向送到中轉主機中，
流量通過隧道到達中轉主機，再從中轉主機訪問實際目標地址。

可以簡單地實現端口轉發功能，用於客戶機無法直接訪問目標地址，但中轉服務器可訪問目標地址的場景。

參數說明：

```html
<!-- 默認轉發端口僅監聽localhost -->
$ ssh -L 本地映射端口:目標地址:目標端口 中轉用戶@中轉主機地址

<!-- 設置轉發端口監聽任意地址（用於用戶側遠程訪問） -->
$ ssh -L *:映射端口:目標地址:目標端口 中轉用戶@中轉主機地址

<!-- 默認SSH創建隧道依舊會進入終端，使用 -N 參數可不進入終端 -->
$ ssh -NL ...
```

網絡結構：

```
執行指令:
ssh -L 本地映射端口:目標地址:目標端口 中轉用戶@中轉主機地址
/|\
 |
 |                         Tunnel
SSH客戶端（監聽本地映射端口） =======> SSH服務端（中轉主機） -> 實際目標地址（目標端口）
```

實際目標地址可以與中轉主機相同，亦可不同，僅需要中轉主機能訪問到即可。



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

	對於boot分區未單獨掛載的場景，啟動分區應為**根分區**；
	對於單獨掛載boot分區的場景，啟動分區為單獨掛載的**boot分區**。

1. 指定啓動分區位置，手動加載啓動器。

	確認分區的位置後，設置啓動參數：

	```html
	grub rescue> set boot=(hd0,gpt3)
	grub rescue> set prefix=(hd0,gpt3)/boot/grub <!-- RedHat系列路徑為 (,)/boot/grub2 -->
	grub rescue> insmod normal
	grub rescue> normal
	```

	之後即可進入正常的GRUB引導界面。

1. 重新安裝引導器。

	正常啓動系統後，在終端重新安裝引導器：

	```html
	<!-- RedHat系列指令為 grub2-install -->
	# grub-install /dev/sda <!-- MBR -->
	# grub-install <!-- UEFI -->
	```

## systemd-boot
`systemd-boot`最初名為`gummiboot`，相比傳統的GRUB，設計上更簡單，僅支持UEFI設備。
通常發行版的`systemd`軟件包中已經包含了該部分。

systemd-boot支持各類EFI執行文件，如Linux kernel EFISTUB、UEFI shell、GRUB、或Windows Boot Manager。
使用systemd-boot引導系統，不再需要傳統GRUB的efibootmgr以及os-prober等組件，
可直接引導機器上的所有的現存支持UEFI的操作系統。

systemd-boot提供了`bootctl`工具管理EFI引導：

```html
# bootctl install/update
```

使用bootctl安裝引導器後，ESP分區下目錄結構為：

```
├── EFI
└── loader
    ├── entries
    │   ├── xxx1.conf
    │   └── xxx2.conf
    ├── loader.conf
    └── random-seed
```

bootctl安裝後會創建`$ESP/loader`、`$ESP/EFI/systemd`等路徑，
將systemd-boot引導器安裝到`$ESP/EFI/systemd/systemd-bootx64.efi`路徑，
引導配置存放在`$ESP/loader/entries`路徑下。

systemd-boot會加載`$ESP/loader/loader.conf`作為默認配置。
在loader.conf中，選擇加載其它`$ESP/loader/entries`路徑下的配置作為默認配置，
以及調整其它引導相關配置（如引導介面的等待時間）。
loader.conf的完整參數說明參考[官方文檔](https://systemd.io/BOOT_LOADER_SPECIFICATION/)以及man手冊`man loader.conf`。

loader.conf配置內容示例：

```
timeout 9999
console-mode keep
default xxx1.conf
```

entries配置示例：

```
title Arch Linux
linux /vmlinuz-linux-zen
initrd /initramfs-linux-zen.img
options root=/dev/sdaX
```

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

```html
<!-- 查看系統設定的核心轉儲大小 -->
$ ulimit -c

<!-- 設置核心轉儲大小爲無限 -->
$ ulimit -c unlimited
```

系統限制分為**軟限制**和**硬限制**，ulimit指令默認顯示和修改的是**軟限制**。
要顯示和修改**硬限制**，需要額外添加`-H`參數。

同樣以**核心轉儲**為例：

```html
<!-- 查看系統設定的核心轉儲大小(硬限制) -->
$ ulimit -cH

<!-- 設置核心轉儲大小爲無限(硬限制) -->
$ ulimit -Hc unlimited
```

使用ulimit默認修改的配置僅對當前會話有效，退出當前會話後，配置重新變為默認值。
要使修改的系統限制永久生效，需要修改`/etc/security/limits.conf`文件中配置。

## ulimit配置文件
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

修改limits.conf文件後不必重啓服務器，
僅需要關閉當前開啟的會話（當前以開啟的會話依舊會使用之前資源限制配置），
關閉會話後重新登錄系統新的資源限制便會生效（對於普通進程而言）；
若進程使用了Linux PAM（如SSH），則需要重啟機器生效。

## prlimit
使用`prlimit`可以查看和動態修改運行中的進程的資源限制：

```html
<!-- 查看進程的全部資源限制 -->
$ prlimit -p 進程號

<!-- 設置進程的資源限制 -->
$ prlimit -p 進程號 --類別=軟限制數值:硬限制數值
```

## 文件描述符限制
對於文件描述符，ulimit**不可**設置為`unlimited`。

ulimit控制**單個進程**的文件描述符上限；
**每個會話**的文件描述符數目還受內核參數`fs.file-max`限制，
查看和修改當前系統限制：

```html
$ sysctl fs.file-max
fs.file-max = 9223372036854775807

<!-- 直接通過proc文件系統查看配置 -->
$ cat /proc/sys/fs/file-max
9223372036854775807

<!-- 修改配置 -->
# sysctl fs.file-max=值
```

## Core Dump（核心轉儲）
啓用核心轉儲後，則在進程執行異常退出時，會生成包含異常信息的錯誤轉儲文件。
使用gdb可分析轉儲文件：

```
$ gdb 進程文件 進程核心轉儲
```

進入gdb shell之後，使用`bt`指令查看調用堆棧。



# 文件系統
Unix系統遵循[`Everything is a file`](https://en.wikipedia.org/wiki/Everything_is_a_file)
設計哲學，任何資源、硬件在系統中均抽象為文件。

硬盤在Linux中以塊設備（block）形式呈現，位於`/dev`路徑下，
通常名稱為`sda`（塊設備路徑`/dev/sda`），
存在多塊磁盤時，則按照次序命名為`sdb,sdc,sdd,...`，依此類推。

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
<!-- 顯示指定分區的信息（分區大小，分區類型等） -->
# file -s 分區塊設備

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
$ wipefs 塊設備
<!-- 清理分區所包含的所有文件系統標誌 -->
# wipefs -a 塊設備
```

使用`fdisk/parted`等工具操作分區塊設備後，內核的分區表並不會立即刷新，
需要使用`partprobe`工具刷新內核分區表信息：

```
# partprobe 塊設備
```

## fdisk
`fdisk`是Linux命令行下常用的交互式磁盤管理工具。

早期的fdisk不能識別`GPT`分區表，劃分GPT分區需要使用`parted`工具。
最近版本的fdisk已經能夠正常識別、顯示與創建GPT分區。

使用fdisk顯示分區信息：

```
# fdisk -l 磁盤塊設備路徑
```

進行具體的磁盤分區操作需要進入fdisk會話：

```html
# fdisk <!-- 直接進入fdisk會話，選擇第一塊硬盤爲當前硬盤 -->
# fdisk 磁盤塊設備路徑 <!-- 進入fdisk會話，並選擇指定硬盤爲當前硬盤 -->
```

在fdisk會話中，操作指令同樣會以對話的形式引導完成操作，基本指令如下：

| 指令 | 說明 |
| :- | :- |
| `m` | 顯示指令菜單 |
| `n` | 創建分區 |
| `d` | 刪除分區 |
| `l` | 列出已知的分區類型 |
| `F` | 列出未分配的磁盤空間 |
| `p` | 打印分區信息，輸出結果與在命令行中輸入`fdisk -l`相同 |
| `i` | 列出某一個分區的具體信息 |
| `t` | 修改分區類型信息 |
| `o` | 創建DOS分區表 |
| `g` | 創建GPT分區表 |
| `x` | 進入高級功能會話 |

部分指令詳細介紹：

- `g/G/o/s` 創建分區表

	在會話中使用`g/G/o/s`指令創建不同類型的分區表，常見的分區表爲：

	- `DOS`分區表（使用指令`o`創建，用於MBR舊式BIOS的機器，僅允許4個主分區）
	- `EFI`分區表（使用指令`g`創建，用於EFI新式BIOS的機器，無分區限制）

- `n` 創建分區

	在會話中使用`n`指令進入交互式創建分區的對話：

	```
	Command (m for help): n
	Partition number (4-128, default 4):
	...
	```

- `t` 修改分區類型

	普通Linux分區類型爲`Linux filesystem`；
	UEFI引導下的ESP分區類型需要爲`EFI System`。

在會話中使用`x`指令後進入高級功能會話，常用指令如下：

| 指令 | 說明 |
| :- | :- |
| `m` | 功能不變，顯示指令菜單 |
| `n` | 修改分區名稱 |
| `r` | 返回主選單 |

在fdisk會話中進行的操作**並非**立即生效的，退出會話之前需要進行確認：

| 指令 | 說明 |
| :- | :- |
| `w` | 將改動真正寫入硬盤 |
| `q` | 不保存改動退出 |

## parted
`parted`是Linux下的另一種交互式分區工具，與`fdisk`相比，parted一直支持GPT分區表，
並且在功能選項上更加豐富，但在交互上沒有fdisk便捷。

與fdisk工具類似，執行具體的磁盤分區需要進入parted會話：

```html
# parted 磁盤設備

<!-- 示例
# parted /dev/nvme0n1
GNU Parted 3.5
Using /dev/nvme0n1
Welcome to GNU Parted! Type 'help' to view a list of commands.
(parted) ...
-->
```

parted也支持直接將操作指令添加在參數中：

```
# parted 磁盤設備 指令...
```

常用功能：

- `# parted -l` 顯示所有分區信息
- `# parted 磁盤設備 print` 顯示指定磁盤的分區信息

parted會話中的基本指令如下：

| 會話指令 | 簡介 |
| :- | :- |
| help | 顯示指令列表 |
| help 指令名稱 | 顯示指定指令的用法 |
| select 磁盤路徑 | 切換到指定磁盤 |
| mklabel 分區表類型 | 創建指定類型分區表，常用的分區表類型爲`msdos`和`gpt` |
| mkpart | 交互式創建分區，以會話的形式引導輸入創建分區所需的參數 |
| mkpart primary/logical/extended 文件系統（可選） 起始位置 結束位置 | 創建分區 |
| resizepart 分區編號 分區結束位置 | 修改指定分區大小（分區位置支持使用MB、GB等單位） |
| rm 分區號 | 刪除指定分區 |
| toggle 分區號 分區標識 | 添加指定分區的分區標誌（如UEFI的ESP分區，應添加`esp`標識） |
| set 分區號 分區標識 on/off | 添加/刪除指定分區的分區標誌 |
| name 分區號 分區名稱 | 命名指定分區 |
| print | 顯示分區信息 |
| print free | 顯示分區信息，包括磁盤中未被使用的空間 |
| print all | 顯示所有分區信息 |
| quit | 退出parted會話 |

`mkpart`創建分區設置大小除了使用起始/結束位置外，還支持下列方式：

- 具體存儲大小，如`10G`、`10M`等。
- 百分比大小，如`10%`、`20%`等。
- 結束未知設置為`-1`，使用所有剩餘空間。

相比fdisk，parted會話中的分區操作會立即執行生效，因此更需小心謹慎。

## 擴容分區
parted直接提供了resizepart子指令，可直接對正在使用的分區進行擴容，
使用resizepart指令設置新的分區結束位置即可。

fdisk未直接提供調整分區大小的功能，但刪除分區默認**不會**清空分區內容，
利用該特性，可通過刪除分區並在**相同起始位置**重建分區的方式進行無損分區擴容。

無論使用哪種工具，均需要當前分區的結束位置后存在剩餘未使用的空間。

分區大小變更後，需要調整文件系統大小以匹配新分區大小，否則文件系統實際可使用大小不變。
常用文件系統的擴容工具：

```html
# xfs_growfs 分區塊設備路徑 <!-- 擴展xfs文件系統的大小 -->
# resize2fs 分區塊設備路徑 分區大小 <!-- 調整ext系列文件系統的大小 -->
```

## 縮容分區
縮容分區操作與擴容分區相反，先調整文件系統大小，
之後進行分區物理位置調整，為分區設置新的結束位置。

與擴容操作不同，多數文件系統不支持在綫縮容，需要先取消分區挂載，之後縮減分區大小。
部分文件系統不支持縮容，如`xfs`。

## flock（文件鎖）
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

當使用flock執行指令時，若目標指令會創建子進程，則子進程會在flock結束後繼續持有鎖（文件描述符共享），
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

## 文件特殊權限
Unix文件系統中，除了常規的777讀寫權限外，還有部分特殊權限可提供額外的控制機制。

### setuid / setgid / sticky
Unix系統中擁有三類特殊權限標誌：

| 權限標誌 | 含義（對可執行文件使用） | 含義（對目錄使用） |
| :- | :- | :- |
| s(setuid) | 使文件在執行階段具有文件所有者的權限 | 在多數Unix實現（包括Linux）下，對目錄設置setuid會被忽略 |
| s(setgid) | 使文件在執行階段具有文件所屬組的權限 | 使目錄下的文件都具有和該目錄所屬組相同的權限 |
| t(sticky) | 禁止文件被所屬用戶外的其它用戶刪除（不受寫權限約束，對root用戶無效） | 在Linux/macOS上均被忽略 |

使用8進制數值表示文件權限時，這些特殊權限佔有一組獨立的8進制位（位於傳統權限標誌位**之前**）。
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

```html
$ touch test

<!-- 設置所有權限，包括特殊權限 -->
$ chmod 7777 test

<!-- 打印權限信息，sst標誌代替了原本各自位置的x標誌 -->
$ ls -alh test
-rwsrwsrwt 1 root root 0 Aug 26 15:17 test
```

使用`chmod`指令設置三類特殊權限：

```html
<!-- 設置文件的setuid權限 -->
$ chmod u+s 文件名
<!-- 設置目錄的setgid權限 -->
$ chmod g+s 目錄名
<!-- 設置文件的stick bit權限 -->
$ chmod o+t 文件名

<!-- 使用4組8進制數值設定文件讀寫執行權限和三類額外權限 -->
$ chmod 7777 文件/目錄
```

### lsattr / chattr
Linux支持使用`chattr`為文件/目錄附加部分特殊屬性，指令語法：

```
# chattr +-=[aAcCdDeFijPsStTu] 文件/目錄
```

常用操作說明：

```html
<!-- 設置/增加/刪除 特定屬性 -->
# chattr =屬性 文件/目錄
# chattr +屬性 文件/目錄
# chattr -屬性 文件/目錄

<!-- 使用 -R 參數可遞歸對目錄生效 -->
# chattr -R 屬性操作 目錄

<!-- 使用 -V 參數可展示操作詳情 -->
# chattr -V 屬性操作 目錄/文件
```

chattr設置的特殊屬性可使用`lsattr`查看：

```html
$ lsattr 目錄/文件
$ lsattr -R 目錄 <!-- 遞歸展示目錄下所有內容的屬性 -->
```

不同文件系統對各類屬性的支持有所不同，詳情需要參見各文件系統的官方文檔。

常用的特殊屬性：

- `a(append only)` 設置文件僅可以`append`模式打開

	設置該屬性後，文件不可刪除，不可以重寫模式重定向，僅可以追加模式重定向：

	```html
	# chattr -V =a test <!-- 需要root權限來設置a屬性 -->
	chattr 1.45.5 (07-Jan-2020)
	Flags of test set as -----a--------------

	<!-- 設置a屬性後，普通用戶不可刪除文件（即使為文件所有者） -->
	$ rm test
	rm: cannot remove 'test': Operation not permitted
	<!-- 設置a屬性後，root用戶亦不可刪除文件 -->
	# rm test
	rm: cannot remove 'test': Operation not permitted

	<!-- 設置了a屬性後，無論普通用戶或root用戶均不可進行重定向重寫內容 -->
	$ echo fuckccp > test
	<W> fish: An error occurred while redirecting file 'test'
	open: Operation not permitted
	# echo fuckccp > test
	<W> fish: An error occurred while redirecting file 'test'
	open: Operation not permitted

	<!-- 追加模式重定向正常，且無需root權限 -->
	$ echo fuckccp >> test
	$ cat test
	fuckccp
	```

- `i(immutable)` 設置文件不可刪除、修改

	設置該屬性後不可進行修改和創建硬鏈接：

	```html
	# chattr -V =i test
	chattr 1.45.5 (07-Jan-2020)
	Flags of test set as ----i---------------

	<!-- 與a屬性類似，同樣無法刪除文件 -->
	$ rm test
	rm: cannot remove 'test': Operation not permitted
	# rm test
	rm: cannot remove 'test': Operation not permitted

	<!-- 相比a屬性，i屬性還禁止重定向追加內容 -->
	$ echo fuckccp > test
	<W> fish: An error occurred while redirecting file 'test'
	open: Operation not permitted
	$ echo fuckccp >> test
	<W> fish: An error occurred while redirecting file 'test'
	open: Operation not permitted
	# echo fuckccp > test
	<W> fish: An error occurred while redirecting file 'test'
	open: Operation not permitted
	# echo fuckccp >> test
	<W> fish: An error occurred while redirecting file 'test'
	open: Operation not permitted

	<!-- i屬性禁止創建硬鏈接 -->
	# ln test test1
	ln: failed to create hard link 'test1' => 'test': Operation not permitted
	```

- `C(not copy-on-write)` 設置文件不使用寫時複製特性

	對於支持寫時複製的文件系統，設置改屬性可保證文件立即分配實際空間，進而避免一些限制。

	例如，在btrfs中，若使用普通文件作為SWAP則會得到下列錯誤：

	```
	# swapon swapfile
	...
	BTRFS warning (device sda2): swapfile must not be copy-on-write
	...
	```

	删除原SWAP文件，重新创建，創建SWAP文件後設置`C`屬性則不再出現該錯誤：

	```
	# chattr +C swapfile
	```

	詳情參考[StackExchange](https://superuser.com/questions/1067150/how-to-create-swapfile-on-ssd-disk-with-btrfs)
	上的對應問答。

### chflags
BSD系列系統中（包括macOS）擁有與Linux下chattr類似的機制`chflags`，指令語法：

```
$ chflags [-fhvx] [-R [-H | -L | -P]] flags file ...
```

常用操作說明：

```html
<!-- 對指定的文件/目錄進行屬性操作 -->
$ chflags 屬性 文件/目錄 <!-- 設置指定屬性 -->
$ chflags 屬性1,屬性2,屬性3 文件/目錄 <!-- 同時設置多個屬性，使用逗號分隔 -->
$ chflags 0 文件/目錄 <!-- 清除設置的屬性 -->

<!-- 使用 -R 參數可遞歸對目錄生效 -->
$ chflags -R 屬性操作 目錄

<!-- 使用 -V 參數可展示操作詳情 -->
# chflags -v 屬性操作 目錄/文件
```

與lsattr不同，chflags設置的屬性直接使用ls工具搭配`-lO`參數進行查看，示例：

```html
$ ls -lO 目錄/文件
$ ls -lRO 目錄 <!-- 遞歸展示目錄下所有內容的屬性 -->
```

macOS/BSD下常用的特殊屬性：

- `hidden`

	設置該屬性後文件隱藏，不在GUI中展示。

- `sappnd, sappend`

	與Linux中的`a`屬性類似，設置該屬性後，文件不可刪除，僅支持追加寫入（需要管理員權限）：

	```html
	# chflags -v sappnd test
	test
	$ ls -lO test
	-rw-r--r--  1 dainslef  staff  sappnd 0 Dec  5 11:16 test
	$ rm test <!-- 普通用戶無權限刪除文件 -->
	override rw-r--r-- dainslef/staff sappnd for test? y
	rm: test: Operation not permitted
	# rm test <!-- 管理員用戶亦無權限刪除文件 -->
	override rw-r--r-- dainslef/staff sappnd for test? y
	rm: test: Operation not permitted
	# echo fuckccp > test <!-- 不可重定向寫入 -->
	warning: An error occurred while redirecting file 'test'
	open: Operation not permitted
	$ echo fuckccp >> test <!-- 可追加寫入 -->
	$ cat test
	fuckccp
	```

- `schg, schange, simmutable`

	與Linux中的`i`屬性類似，設置該屬性後，文件不可刪除、修改（需要管理員權限）：

	```html
	# chflags -v schg test
	test
	$ ls -lO test
	-rw-r--r--  1 dainslef  staff  schg 0 Dec  5 11:16 test
	# echo fuckccp > test
	warning: An error occurred while redirecting file 'test'
	open: Operation not permitted
	# echo fuckccp >> test
	warning: An error occurred while redirecting file 'test'
	open: Operation not permitted
	# rm test <!-- 管理員亦無法刪除 -->
	override rw-r--r-- dainslef/staff schg for test? y
	rm: test: Operation not permitted
	```

- `uappnd, uappend`

	功能與`sappnd, sappend`類似，但無須管理員權限，可由文件所有者添加該屬性：

	```html
	$ chflags -v uappnd test
	test
	$ ls -lO test
	-rw-r--r--  1 dainslef  staff  uappnd 0 Dec  5 11:16 test
	# echo fuckccp > test <!-- 管理員亦不可重定向寫入 -->
	warning: An error occurred while redirecting file 'test'
	open: Operation not permitted
	$ echo fuckccp >> test <!-- 普通用戶即可追加寫入 -->
	$ rm test <!-- 普通用戶不可刪除 -->
	override rw-r--r-- dainslef/staff uappnd for test? y
	rm: test: Operation not permitted
	# rm test <!-- 管理員可刪除 -->
	override rw-r--r-- dainslef/staff uappnd for test? y
	```

- `uchg, uchange, uimmutable`

	功能與`schg, schange, simmutable`類似，但無須管理員權限，可由文件所有者添加該屬性：

	```html
	$ chflags -v uchg test
	test
	$ ls -lO test
	-rw-r--r--  1 dainslef  staff  uchg 0 Dec  5 11:16 test
	# echo fuckccp > test <!-- 管理員亦不可重定向寫入 -->
	warning: An error occurred while redirecting file 'test'
	open: Operation not permitted
	# echo fuckccp >> test <!-- 管理員亦不可追加寫入 -->
	warning: An error occurred while redirecting file 'test'
	open: Operation not permitted
	$ rm test <!-- 普通用戶不可刪除 -->
	override rw-r--r-- dainslef/staff uchg for test? y
	rm: test: Operation not permitted
	# rm test <!-- 管理員可刪除 -->
	override rw-r--r-- dainslef/staff uchg for test? y
	```

## LVM (Logical Volume Manager)
`LVM (Logical Volume Manager)`，邏輯卷管理，是Linux環境下對磁盤分區進行管理的一種機制。

使用LVM能夠將不同的硬盤上的物理卷(`Physical Volume`，簡稱`PV`)加入卷組(`Volume Group`，簡稱`VG`)。
在卷組中將其劃分爲不同的邏輯卷(`Logical Volume`，簡稱`LV`)，然後在邏輯卷中創建文件系統並進行掛載。

LVM在物理磁盤上提供了一層抽象，解除了分區與物理磁盤的綁定。
LVM中一個邏輯分區在物理結構上可能由多個磁盤組成，添加新的物理磁盤時，
邏輯分區無需改變結構/重新掛載即可利用新增物理磁盤的空間實現動態擴容。

### LVM基本操作
配置LVM的**基本步驟**：

1. 創建硬盤分區
1. 創建物理卷：`# pvcreate 物理卷塊設備`(物理卷塊設備可以是整個硬盤設備或是硬盤中的某個分區設備)
1. 創建卷組：`# vgcreate 卷組名稱 待加入卷組的物理卷塊設備`
1. 創建邏輯卷，生成邏輯卷塊設備：`# lvcreate -L 分區大小(xxGB/xxMB/...) -n 邏輯卷名稱 卷組名稱`
1. 在邏輯塊設備中進行格式化、創建文件系統等操作，之後可掛載使用

### Physical Volume（PV，物理卷）
物理卷`Physical Volume`是在磁盤上**實際存在**的物理分區。
被添加到LVM的物理分區需要擁有`lvm`標識(flag)。

物理卷相關的操作爲`pvXXX`系列指令：

```html
# pvcreate 磁盤塊設備/磁盤物理分區塊設備 <!-- 創建物理卷 -->
# pvremove 磁盤塊設備/磁盤物理分區塊設備 <!-- 移除物理卷 -->
# pvdisplay <!-- 顯示已創建的物理卷 -->
```

移除一個物理卷需要先將該物理卷從所屬的卷組中移除。
移除物理卷前需要保證沒有數據存儲在該物理卷中，若**要被移除的物理卷**中已有數據，
則需要使用`pvmove`指令將該卷中的數據轉移到其它卷：

```html
# pvmove 物理分區塊設備 <!-- 將該物理分區中的數據遷移到VG的其它PV中 -->
# pvmove 原物理分區塊設備 目標物理分區塊設備 <!-- 指定將PV中的數據轉移到另一PV中 -->
```

### Volume Group（VG，卷組）
物理卷需要加入卷組(`Volume Group`)才能被使用。

卷組相關的操作爲`vgXXX`系列指令：

```html
# vgcreate 卷組名稱 物理卷塊設備 <!-- 一個卷組至少需要包含一個物理卷，物理卷塊設備可爲多個 -->
# vgextend 卷組名稱 物理卷塊設備 <!-- 向指定卷組中添加物理卷 -->
# vgreduce 卷組名稱 物理卷塊設備 <!-- 從指定卷組中刪除物理卷 -->
# vgremove 卷組名稱 <!-- 移除指定卷組 -->
# vgdisplay <!-- 顯示所有卷組 -->
```

### Logical Volume（LV，邏輯卷）
邏輯卷(`Logical Volume`)是`LVM`中實際用於創建文件系統、掛載的分區。
邏輯卷的磁盤塊設備路徑爲`/dev/[邏輯卷所屬卷組名稱]/[邏輯卷名稱]`，
邏輯卷的塊設備可如物理磁盤塊設備一般進行創建文件系統、掛載等操作。

邏輯卷相關的操作爲`lvXXX`系列指令：

```html
<!-- 顯示所有邏輯卷 -->
# lvdisplay

<!-- 創建邏輯卷 -->
# lvcreate -L 分區大小(xxGB/xxMB/...) 卷組名稱 <!-- 創建邏輯卷，自動生成卷名稱 -->
# lvcreate -L 分區大小 -n 邏輯分區名稱 卷組名稱 <!-- 創建邏輯卷，手動指定卷名稱 -->

<!-- 移除指定邏輯卷 -->
# lvremove 邏輯卷塊設備

# lvresize -L +/-分區大小 邏輯分區塊設備 <!-- 在原先邏輯卷大小的基礎上擴充/縮減指定大小 -->
# lvextend -L 分區大小 邏輯分區塊設備 <!-- 增加邏輯捲到指定大小(分區大小的數值需要大於原先該邏輯分區的大小) -->
# lvreduce -L 分區大小 邏輯分區塊設備 <!-- 減小邏輯捲到指定大小(分區大小的數值需要小於原先該邏輯分區的大小) -->
```

擴展邏輯卷大小無需卸載、重新掛載文件系統。
縮減邏輯卷大小需要重先卸載文件系統，縮減空間後重新掛載。

擴展邏輯卷大小後，對應邏輯卷的文件系統大小並未增大，因此會造成不同指令輸出分區大小不一致的情況：

- `df`指令顯示的是文件系統大小
- `parted`、`fdisk`、`lsblk`、`lvdisplay`等指令顯示的是邏輯分區的大小

擴展邏輯卷大小后，需要根據邏輯卷分區類型使用對應工具擴展文件系統大小，
之後分區可用空間才會真正增加。

縮減邏輯卷時操作相反，先卸載對應分區，使用文件系統對應的工具縮減文件系統大小，
之後再縮減文件系統所屬的LVM分區的大小。

### Thinly-Provisioned Logical Volumes（精簡邏輯卷）
`Thinly-Provisioned Logical Volumes`（精簡邏輯卷）相比普通LV卷不需要立即分配空間，
而僅佔用實際使用大小的空間，使用精簡邏輯卷可以創建出超過實際大小的邏輯存儲。

使用瘦邏輯卷前需要創建`Thinly-Provisioned Logical Volumes Pool`（精簡邏輯卷池）：

```html
# lvcreate -T -L 邏輯卷池大小 卷組名稱/邏輯卷池名稱
```

之後使用`-T/--thin`參數創建精簡邏輯卷：

```
# lvcreate -T -n 邏輯卷名稱 -V 分區大小 --thinpool 精簡卷池 邏輯卷組
# lvcreate --type thin -n 邏輯卷名稱 -V 分區大小 --thinpool 精簡卷池 邏輯卷組
```

移除瘦邏輯卷操作類似：

```html
# lvremove 精簡邏輯卷塊設備
# lvremove 卷組名稱/邏輯卷池名稱 <!-- 移除逻辑卷池 -->
```

### 邏輯卷狀態和塊設備不顯示問題
使用lvdisplay查看邏輯卷狀態時，若邏輯卷`LV Status`顯示`NOT available`，
可使用`vgchange`激活卷組下所有的邏輯卷，使其狀態恢復爲`available`：

```c
# vgchange -a y 卷組名稱
```

部分狀態爲`NOT available`的邏輯卷對應的塊設備不顯示在`/dev/mapper`和`/dev/卷組`路徑下，
可激活卷組後執行`vgmknodes`指令，會創建對應缺失的塊設備文件：

```
# vgmknodes
```



# 時間管理
多數Unix中，均可使用`date`指令查看時間和設置：

```html
$ date <!-- 查看當前時間 -->
Mon Mar  6 16:42:16 CST 2023

# date '時間' <!-- 設置系統時間 -->
```

使用systemd的現代Linux發行版中，時間管理亦可使用`timedatectl`工具：

```html
$ timedatectl
               Local time: Mon 2023-03-06 09:19:53 UTC
           Universal time: Mon 2023-03-06 09:19:53 UTC
                 RTC time: Mon 2023-03-06 09:19:54
                Time zone: Etc/UTC (UTC, +0000)
System clock synchronized: yes
              NTP service: active
          RTC in local TZ: no

$ timedatectl list-timezones <!-- 查看支持的時區 -->
# timedatectl set-timezone 時區 <!-- 設置時區 -->
```

## 硬件時間
使用`hwclock`指令查看系統的硬件時間：

```html
$ hwclock

<!-- 輸出詳情 -->
$ hwclock -v

<!-- 同步系統時間與硬件時間 -->
# hwclock -s/--hctosys <!-- 硬件時間寫入系統時間 -->
# hwclock -w/--systohc <!-- 系統時間寫入硬件時間 -->
```

## NTP (Network Time Protocol)
`NTP(Network Time Protocol)`是用於在多台計算機之間同步時鐘信息的網絡協議。

NTP目前主要有兩類實現：

- [`ntp`](https://ntp.org) NTP官方標準實現
- [`chrony`](https://chrony.tuxfamily.org/) 輕量級的NTP實現，主要用在紅帽係發行版中

### ntp服務配置
配置NTP服務前需要在系統中安裝ntp軟件包，
各大Linux發行版的軟件源中均包含了ntp軟件包，
以ArchLinux為例，安裝ntp：

```
# pacman -S ntp
```

NTP配置文件為`/etc/ntp.conf`。

啟動NTP服務：

```
# systemctl start ntpd
```

#### ntp客戶端配置
將服務器配置為ntp客戶端，需要在配置中添加同步目標主機。
添加`server`配置段：

```sh
...
# 配置格式 server [版本號].[需要同步的主機地址]
server time.stdtime.gov.tw prefer # 設置具有更高優先級的主機
server 0.xxx
server 1.xxx
...
```

#### ntp服務端配置
配置了NTP服務的主機可以允許同一網絡下的其它ntp客戶端同步此服務器。
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
| nopeer | 阻止對等關聯（不允許同一層級服務關連） |

若在局域網中使用NTP時，則應考慮將某一台服務器作為基準時間，在該台服務器的配置中添加：

```
server 127.127.1.0
fudge 127.127.1.0
```

該服務器向自身進行同步，自身作為時鐘同步源。

#### ntp服務管理指令
使用`ntpstat`指令查看NTP服務狀態：

```
$ ntpstat
synchronised to unspecified (120.25.115.20) at stratum 3
   time correct to within 35 ms
   polling server every 64 s
```

亦可使用`ntpq -p`查看NTP同步状态，輸出示例：

```html
<!-- 同步正常輸出 -->
$ ntpq -p
     remote           refid      st t when poll reach   delay   offset  jitter
==============================================================================
 192.168.0.155   .POOL.          16 p    -   64    0    0.000    0.000   0.000
*192.168.0.155   192.168.2.150   13 u   24   64  377    4.080    0.011   0.193

<!-- 同步失敗輸出 -->
$ ntpq -p
localhost: timed out, nothing received
***Request timed out
```

對於同步延遲、失敗的情況可嘗試使用`ntpdate`指令進行**手動同步**：

```
# ntpdate [server ip/hostname]
```

ntpdate指令可添加`-d`參數輸出調試信息，示例：

```
# ntpdate -d 172.20.10.2
14 Jan 16:57:13 ntpdate[926]: ntpdate 4.2.8p12@1.3728-o (1)
Looking for host 172.20.10.2 and service ntp
host found : 172.20.10.2
transmit(172.20.10.2)
receive(172.20.10.2)
transmit(172.20.10.2)
receive(172.20.10.2)
transmit(172.20.10.2)
receive(172.20.10.2)
transmit(172.20.10.2)
receive(172.20.10.2)

server 172.20.10.2, port 123
stratum 6, precision -24, leap 00, trust 000
refid [127.127.1.0], root delay 0.000000, root dispersion 0.011078
transmitted 4, in filter 4
reference time:    e76c5873.0e9733f0  Sat, Jan 14 2023  6:23:47.056
originate timestamp: e76c587e.8f58b927  Sat, Jan 14 2023  6:23:58.559
transmit timestamp:  e76cecef.29e1db09  Sat, Jan 14 2023 16:57:19.163
filter delay:  0.02858  0.02690  0.02689  0.02708
         0.00000  0.00000  0.00000  0.00000
filter offset: -38000.5 -38000.5 -38000.5 -38000.6
         0.000000 0.000000 0.000000 0.000000
delay 0.02689, dispersion 0.00880
offset -38000.595912

14 Jan 16:57:19 ntpdate[926]: step time server 172.20.10.2 offset -38000.595912 sec
```

使用`ntpq/ntpdc`指令進入交互式Shell，進行具體的NTP查詢操作：

```html
<!-- ntpq - standard NTP query program -->
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

<!-- ntpdc - special NTP query program -->
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

## chrony時間服務
自`CentOS 7/RHEL 7`開始，RedHat使用`chrony`代替了傳統的ntpd作為時間同步服務。
相比傳統的ntpd，chrony具有以下優勢：

1. 更快的同步速度。
1. 能更好地響應時鐘頻率的快速變化，對於不穩定的虛擬機環境或使用不穩定始終的低功耗場景下更有效。
1. 在初始化同步之後不再計時。
1. 在處理非對稱延遲時居於更好的穩定性。
1. 不需要定期輪詢服務器，在網絡不定期間斷的場景下仍可快速同步時鐘。

chrony詳細介紹可參考[官方網站](https://chrony.tuxfamily.org/index.html)。

主流的發行版的軟件倉庫中均內置了chrony：

```html
<!-- Arch Linux -->
# pacman -S chrony

<!-- CentOS -->
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

```html
<!-- 查看服務的執行狀態 -->
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

<!--
查看用於同步的源
M表示源的類型，'^'表示服務器，'='表示對等主機
S表示源的狀態，'*'表示已同步，'+'表示已綁定，'-'表示被排除，'?'表示連接故障，'x'表示目標時鐘錯誤，'~'表示目標時鐘不穩定
-->
$ chronyc sources
210 Number of sources = 1
MS Name/IP address    Stratum    Poll   Reach   LastRx   Last sample
=============================================================================
^* 192.0.2.1           11        6      377      63      +1827us[+6783us]

<!-- 查看從當前主機同步的客戶端 -->
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
| -L, --location | Follow redirects | `-L` |

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

```html
<!-- 查看指定服務狀態 -->
# systemctl status 服務名稱
<!-- 啓動指定服務 -->
# systemctl start 服務名稱
<!-- 停止指定服務 -->
# systemctl stop 服務名稱
<!-- 設置指定服務開機自啓動 -->
# systemctl enable 服務名稱
<!-- 取消指定服務開機自啓動 -->
# systemctl disable 服務名稱
```

systemd服務文件以`*.service`爲後綴名。

- 系統服務：

	系統服務文件位於路徑`/usr/lib/systemd/system`下。
	啓用、禁用系統服務需要使用root權限(查看服務狀態不需要)。

- 用戶服務：

	用戶服務文件位於路徑`/usr/lib/systemd/user`（全局路徑）或`~/.config/systemd/user`（用戶路徑）下。
	管理用戶服務以普通權限執行`systemctl`指令，同時在指令中添加`--user`參數：

	```
	$ systemctl --user status/start/stop/enable/disable 用戶服務名稱
	```

## rc.local
早期sysinit發行版添加開機自啟動指令通常會將指令寫在`/etc/init.d/rc.local`，
在systemd時代，多數systemd發行版已經不再存在該文件；
部分發行版會保留rc.local的功能作為服務提供，以Debian係發行版為例：

```
$ systemctl status rc-local
● rc-local.service - /etc/rc.local Compatibility
     Loaded: loaded (/lib/systemd/system/rc-local.service; static; vendor preset: enabled)
    Drop-In: /usr/lib/systemd/system/rc-local.service.d
             └─debian.conf
     Active: inactive (dead)
       Docs: man:systemd-rc-local-generator(8)

$ cat /lib/systemd/system/rc-local.service
#  SPDX-License-Identifier: LGPL-2.1+
#
#  This file is part of systemd.
#
#  systemd is free software; you can redistribute it and/or modify it
#  under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation; either version 2.1 of the License, or
#  (at your option) any later version.

# This unit gets pulled automatically into multi-user.target by
# systemd-rc-local-generator if /etc/rc.local is executable.
[Unit]
Description=/etc/rc.local Compatibility
Documentation=man:systemd-rc-local-generator(8)
ConditionFileIsExecutable=/etc/rc.local
After=network.target

[Service]
Type=forking
ExecStart=/etc/rc.local start
TimeoutSec=0
RemainAfterExit=yes
GuessMainPID=no
```

Ubuntu/Debian提供了`rc-local`服務，功能與之前類似，開啟該服務自啟動即可。

## systemd服務後綴
systemd中的服務可帶有一些特殊後綴，參考[systemd.service官方文檔](https://www.freedesktop.org/software/systemd/man/systemd.service.html)中的`Table 1. Special executable prefixes`。

| 前綴 | 說明 |
| :- | :- |
| `@` | 服務執行路徑前綴`@`字符，則完整服務名稱@字符之後的內容（`xxx@?.service`中的`?`）會作為`argv[0]`傳遞給執行進程 |
| `_` | 服務指令路徑前綴`_`字符，則指令的非零退出代碼、由於信號的退出會被視為失敗而記錄，但不會有其它額外效果（等同於執行成功） |
| `:` | 服務執行路徑前綴`:`字符，則服務指令內容中的環境變量替換不生效 |
| `+` | 服務執行路徑前綴`+`字符，則服務指令以完全權限執行，在此模式下，權限限制類配置（如`User=, Group=`等）、各類文件命名空間配置（如`PrivateDevices=, PrivateTmp=`等）不會應用到命令行，但依舊影響其它`ExecStart=, ExecStop=, …`行 |
| `!` | 類似`+`字符，服務指令以高權限執行，但僅僅影響用戶/組相關參數（`User=, Group=, SupplementaryGroups=`），該功能可與`DynamicUser=`組合使用，此時在指令執行前分配動態用戶/組 |
| `!!` | 與`!`類似，但僅對不支持ambient process capabilities（環境進程功能）的系統（不支持AmbientCapabilities=）產生影響。 |

部分帶有特殊字符的服務示例：

- `user@.service`，@之後可添加UID，顯示不同用戶的狀態。

	```html
	<!-- 用戶帳號 -->
	$ systemctl status user@1001.service
	● user@1001.service - User Manager for UID 1001
	     Loaded: loaded (/lib/systemd/system/user@.service; static; vendor preset: enabled)
	    Drop-In: /usr/lib/systemd/system/user@.service.d
	             └─timeout.conf
	     Active: active (running) since Wed 2021-05-19 15:43:12 UTC; 1h 0min ago
	       Docs: man:user@.service(5)
	   Main PID: 1463 (systemd)
	     Status: "Startup finished in 287ms."
	      Tasks: 2
	     Memory: 3.5M
	     CGroup: /user.slice/user-1001.slice/user@1001.service
	             └─init.scope
	               ├─1463 /lib/systemd/systemd --user
	               └─1465 (sd-pam)

	May 19 15:43:12 oracle-cloud systemd[1463]: Listening on GnuPG cryptographic agent (ssh-agent emulation).
	May 19 15:43:12 oracle-cloud systemd[1463]: Listening on GnuPG cryptographic agent and passphrase cache.
	May 19 15:43:12 oracle-cloud systemd[1463]: Listening on debconf communication socket.
	May 19 15:43:12 oracle-cloud systemd[1463]: Listening on REST API socket for snapd user session agent.
	May 19 15:43:12 oracle-cloud systemd[1463]: Listening on D-Bus User Message Bus Socket.
	May 19 15:43:12 oracle-cloud systemd[1463]: Reached target Sockets.
	May 19 15:43:12 oracle-cloud systemd[1463]: Reached target Basic System.
	May 19 15:43:12 oracle-cloud systemd[1463]: Reached target Main User Target.
	May 19 15:43:12 oracle-cloud systemd[1463]: Startup finished in 287ms.
	May 19 15:43:12 oracle-cloud systemd[1]: Started User Manager for UID 1001.

	<!-- root帳號 -->
	$ systemctl status user@0.service
	● user@0.service - User Manager for UID 0
	     Loaded: loaded (/lib/systemd/system/user@.service; static; vendor preset: enabled)
	    Drop-In: /usr/lib/systemd/system/user@.service.d
	             └─timeout.conf
	     Active: inactive (dead)
	       Docs: man:user@.service(5)
	```

- `syncthing@.service`，@之後可添加用戶名，不同用戶可擁有不同服務狀態。

	```html
	<!-- 顯示root用戶的服務狀態 -->
	$ systemctl status syncthing@root.service
	● syncthing@root.service - Syncthing - Open Source Continuous File Synchronization for root
	     Loaded: loaded (/lib/systemd/system/syncthing@.service; disabled; vendor preset: enabled)
	     Active: inactive (dead)
	       Docs: man:syncthing(1)

	<!-- 顯示ubuntu用戶的服務狀態 -->
	$ systemctl status syncthing@ubuntu.service
	● syncthing@ubuntu.service - Syncthing - Open Source Continuous File Synchronization for ubuntu
	     Loaded: loaded (/lib/systemd/system/syncthing@.service; enabled; vendor preset: enabled)
	     Active: active (running) since Wed 2021-05-19 16:37:00 UTC; 4min 7s ago
	       Docs: man:syncthing(1)
	   Main PID: 2720 (syncthing)
	      Tasks: 12 (limit: 1107)
	     Memory: 61.0M
	     CGroup: /system.slice/system-syncthing.slice/syncthing@ubuntu.service
	             └─2720 /usr/bin/syncthing -no-browser -no-restart -logflags=0

	May 19 16:37:03 oracle-cloud syncthing[2720]: [5LDX2] INFO: TCP listener ([::]:22000) starting
	May 19 16:37:03 oracle-cloud syncthing[2720]: [5LDX2] INFO: Relay listener (dynamic+https://relays.syncthing.net/endpoi>
	May 19 16:37:03 oracle-cloud syncthing[2720]: [5LDX2] INFO: Completed initial scan of sendreceive folder "Default Folde>
	May 19 16:37:03 oracle-cloud syncthing[2720]: [5LDX2] INFO: Loading HTTPS certificate: open /home/ubuntu/.config/syncth>
	May 19 16:37:03 oracle-cloud syncthing[2720]: [5LDX2] INFO: Creating new HTTPS certificate
	May 19 16:37:03 oracle-cloud syncthing[2720]: [5LDX2] INFO: GUI and API listening on 127.0.0.1:8384
	May 19 16:37:03 oracle-cloud syncthing[2720]: [5LDX2] INFO: Access the GUI via the following URL: http://127.0.0.1:8384/
	May 19 16:37:03 oracle-cloud syncthing[2720]: [5LDX2] INFO: My name is "oracle-cloud"
	May 19 16:37:13 oracle-cloud syncthing[2720]: [5LDX2] INFO: Detected 0 NAT services
	May 19 16:37:44 oracle-cloud syncthing[2720]: [5LDX2] INFO: Joined relay relay://144.217.112.143:443
	```

## systemd服務分析
systemd提供了一系列工具用於查看查看、分析各類服務狀態。

使用`systemctl status/list`系列指令查看服務狀態：


```html
$ systemctl status <!-- 列出系統服務依賴樹 -->

$ systemctl list-units <!-- 列出已加載的服務單元信息 -->
$ systemctl list-dependencies <!-- 列出已加載服務單元的依賴關係 -->
$ systemctl list-timers <!-- 列出定時任務 -->
$ systemctl list-unit-files <!-- 列出已安裝服務單元(所有服務單元)的自啓狀態 -->
$ systemctl list-units -t 服務類型 <!-- 查看指定類型的服務信息 -->
```

默認指令展示系統全局服務信息，添加`--user`參數則展示當前用戶服務信息。

使用`systemd-analyze`指令分析系統的啓動性能：

```html
$ systemd-analyze <!-- 顯示系統的啓動耗時 -->
$ systemd-analyze blame <!-- 列出所有的啓動單元，按照啓動耗時的高低進行排序 -->
```

## 編寫systemd服務
一個基本的systemd服務結構如下：

```ini
[Unit]
Description=User Daemon

[Service]
ExecStart=/usr/bin/xxx --xxxargs

[Install]
WantedBy=default.target
```

Unit區段中編寫服務的描述信息，可用於設置服務的前置依賴條件：

```ini
[Unit]
Description=User Daemon
After=xxx.target
```

Service區段爲核心的服務內容，設置服務的類型、執行指令、錯誤恢復等內容：

```ini
[Service]
Type=xxx # 服務類型
ExecStartPre=xxx # 在服務指令執行前執行一個前置操作，如等待一定時間（sleep xxx）
ExecStart=xxx # 服務執行指令
Restart=xxx # 服務重啓策略
RestartSec=xxx # 服務重啓的等待時間
```

Install區段決定服務在啓動流程中的位置，
只有具有Install區段的服務纔可使用`systemctl enable`開啓自啓動，
開啓服務自啓動後，會在對應的目標路徑下中創建符號鏈接。

## 其它systemd系統管理工具
systemd還集成了常用的系統管理工具：

| 工具名稱 | 功能 |
| :- | :- |
| hostnamectl | 配置主機名稱 |
| timedatectl | 時區時間配置 |
| localectl | 語言編碼配置 |
| networkctl | 網絡配置 |
| resolvectl | DNS配置 |
| coredumpctl | 核心轉儲查看 |
| journalctl | 日誌查看工具 |
| loginctl | 會話狀態管理 |
| busctl | | D-Bus監控 |
| userdbctl | 用戶管理 |
| machinectl | 虛擬機/容器管理

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

[`net-tools`](https://sourceforge.net/projects/net-tools)套件歷史悠久，
提供了與其它Unix類似的網絡管理工具(ifconfig、route等)，但目前已停止維護。

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

ip指令的基本使用：

```html
$ ip <!-- 展示指令基本用法 -->
$ ip 子指令 help <!-- 展示特定子指令的用法 -->

<!-- 設置/移除ip -->
# ip addr add 地址/子網 dev 網卡設備
# ip addr del 地址/子網

<!-- 重置網卡 -->
# ip dev 網卡設備 flush <!-- 重置指定網卡設備的所有狀態 -->
# ip addr flush 網卡設備 <!-- 重置網卡配置的地址 -->
```

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

## 網絡配置
各大發行版的網絡配置差異較大，同一發行版的不同版本網絡配置也不盡相同。

### ifupdown（Ubuntu（17.10之前）/ Debian）
Ubuntu與Debian早期默認使用`ifupdown`軟件包管理網絡配置。

ifupdown配置文件位於`/etc/network`路徑下，核心配置文件爲`/etc/network/interfaces`：

```shell
# The loopback network interface
auto lo
iface lo inet loopback

# The DHCP network interface
auto xxx
iface xxx inet dhcp

# The custom network interface
auto xxx
iface xxx inet static
address x.x.x.x
netmask x.x.x.x
gateway x.x.x.x
```

配置更改後，需要重啓網絡服務使之生效：

```
# systemctl restart networking
```

配置DNS：

```html
# echo "nameserver x.x.x.x" > /etc/resolvconf/resolv.conf.d/base

<!-- 刷新DNS，使配置生效 -->
# resolvconf -u
```

### Netplan（Ubuntu17.10之後）
Ubuntu 17.10後，爲了簡化網絡配置，不再使用Debian的網絡配置方式，
而是引入了新的網絡配置工具Netplan。

Netplan配置文件位於`/etc/netplan/xx_config.yaml`：

```yaml

network:
  version: 2
  renderer: networkd
  ethernets:
    # The DHCP network interface
    xxx:
      dhcp4: true
    # The static network interface
    eth0:
      addresses: [x.x.x.x/x, x.x.x.x/x]
      gateway4: x.x.x.x
      nameservers:
        addresses: [x.x.x.x]
```

應用網絡配置：

```
# netplan apply
```

### NetworkManager
`NetworkManager`是現代Linux發行版的主流網絡管理服務，
NetworkManager服務用於管理網絡連接和其它網絡接口，
如Ethernet、WiFi、Mobile Broadband，使網絡配置和操作變得盡可能自動化。

NetworkManager最初由RedHat開發，之後由GNOME項目進行維護。
紅帽系列發行版RHEL、CentOS、Fedora等均默認使用NetworkManager。

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
<!-- 網絡設備狀態相關 -->
$ nmcli device <!-- 查看接口狀態 -->
# nmcli device reapply 接口名稱 <!-- 修改網絡配置後，重新加載指定接口的配置 -->

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

<!-- 列出網絡連接信息 -->
$ nmcli connection
```

nmtui提供友好的TUI，可直接編輯、啟用、禁用連接。

### systemd-networkd
使用systemd的發行版亦可使用`systemd-networkd`管理網絡。

使用systemd-networkd需要在systemd中啟用對應服務：

```html
# systemctl start systemd-networkd.service
# systemctl enable systemd-networkd.service <!-- 設置服務自啟動 -->
```

systemd-networkd使用`networkctl`指令管理網絡：

```html
<!-- 展示網絡設備列表 -->
# networkctl
# networkctl list

<!-- 展示網絡狀態 -->
# networkctl status

<!-- 啟用/停止指定網絡設備 -->
# networkctl up/down 網卡設備
```

systemd-networkd的配置文件為`/etc/systemd/networkd.conf`，
以及`/etc/systemd/network`路徑，配置靜態地址示例：

```conf
[Match]
MACAddress=... # 通過MAC地址匹配設備

[Network]
Address=x.x.x.x/x
Address=x.x.x.x/x
... # 可配置多組IP地址
Gateway=x.x.x.x
DNS=x.x.x.x
```

DHCP則可直接使用：

```conf
[Match]
MACAddress=... # 通過MAC地址匹配設備

[Network]
DHCP=yes # DHCP會自動配置網關、DNS
# Address=x.x.x.x/x # DHCP亦可設置靜態地址
```

### `Failed to configure DHCPv4 client: No such file or directory`
問題描述：<br>
systemd-networkd開啟DHCP配置，出現下列錯誤，導致網卡獲取IP失敗：

```
...
systemd-networkd[850]: enp2s0: Cinfiguring with /etc/systemd/network/enp2s0.network
systemd-networkd[850]: enp2s0: Failed to configure DHCPv4 client: No such file or directory
...
```

解決方案：<br>
systemd-networkd需要正確生成`/etc/machine-id`文件，生成該文件：

```
# systemd-machine-id-setup
```

之後重啟systemd-networkd服務網絡即可恢復正常。

## route（路由）
`route`是大多數Unix的默認路由管理工具。

Linux同時支持`route`（net-tools）以及`ip route`（iproute2）用於管理路由。

### route
macOS/BSD等傳統Unix中，僅使用route指令管理路由，基本操作：

```html
<!-- 添加路由 -->
# route add 網段/子網 網關
# route add 網段/子網 -interface 網卡 <!-- 設置指定網段從特定網卡發送 -->

<!-- 刪除路由 -->
# route delete 網段/子網
```

Linux使用route指令默認會打印路由表信息：

```
$ route
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
default         _gateway        0.0.0.0         UG    100    0        0 enp0s3
10.0.0.0        0.0.0.0         255.255.255.0   U     0      0        0 enp1s0
...
```

macOS/BSD中則默認輸出指令的幫助信息，查看路由表需要使用`netstat`指令：

```html
<!-- FreeBSD 13.2 -->
$ route
route: usage: route [-46dnqtv] command [[modifiers] args]

<!-- macOS 13.4  -->
$ route
usage: route [-dnqtv] command [[modifiers] args]

<!-- 使用 netstat 在macOS/BSD中查看路由表 -->
$ netstat -rn
Routing tables

Internet:
Destination        Gateway            Flags     Netif Expire
default            10.0.0.1           UGS      vtnet0
10.0.0.0/24        link#1             U        vtnet0
...

Internet6:
Destination                       Gateway                       Flags     Netif Expire
::/96                             ::1                           URS         lo0
::1                               link#2                        UHS         lo0
::ffff:0.0.0.0/96                 ::1                           URS         lo0
fe80::/10                         ::1                           URS         lo0
...
```

### ip route
ip route常用指令：

```html
<!-- 打印路由表 -->
$ ip route

<!-- 添加路由 -->
# ip route add 網段 via 網關
# ip route add 網段 via 網關 src 源地址 <!-- 設置指定源地址的路由 -->
# ip route add 網段 dev 網卡設備
# ip route add 網段 dev 網卡設備 via 網關 <!-- 同時指定設備和網關 -->

<!-- 刪除路由 -->
# ip route del 網段
```

使用示例：

```html
<!-- 打印路由 -->
$ ip route
default via 10.10.10.1 dev eno1 onlink
10.10.10.0/24 dev eno1  proto kernel  scope link  src 10.10.10.253

<!-- 按設備添加路由 -->
# ip route add 192.168.100.0/24 dev eno1
$ ip route
default via 10.10.10.1 dev eno1 onlink
10.10.10.0/24 dev eno1  proto kernel  scope link  src 10.10.10.253
192.168.100.0/24 dev eno1  scope link

<!-- 按地址添加路由 -->
# ip route add 192.168.101.0/24 via 10.10.10.252
$ ip route
default via 10.10.10.1 dev eno1 onlink
10.10.10.0/24 dev eno1  proto kernel  scope link  src 10.10.10.253
192.168.100.0/24 dev eno1  scope link
192.168.101.0/24 via 10.10.10.252 dev eno1

<!-- 刪除上述添加的路由 -->
# ip route del 192.168.100.0/24
# ip route del 192.168.101.0/24
$ ip route
default via 10.10.10.1 dev eno1 onlink
10.10.10.0/24 dev eno1  proto kernel  scope link  src 10.10.10.253
```

ip route默認輸出的路由表樣式可讀性較差，
iproute2還提供了`routel`工具可更清晰地展示路由表：

```html
<!-- 打印路由表 -->
$ routel
         target            gateway          source    proto    scope    dev tbl
    10.89.64.0/ 24                     10.89.64.64   kernel     link wlp3s0
     224.0.0.0/ 4                                    static     link enp2s0
    10.89.64.64              local     10.89.64.64   kernel     host wlp3s0 local
            ::1                                      kernel              lo
        fe80::/ 64                                   kernel          enp2s0
        fe80::/ 64                                   kernel          wlp3s0
            ::1              local                   kernel              lo local
...
```

### 路由轉發
Linux具備路由轉發功能，作為路由器使用，在proc文件系統中查看系統路由功能是否開啟：

```html
<!-- 值為0路由轉發功能處於關閉狀態，值為1時開啟 -->
$ sysctl net.ipv4.ip_forward <!-- 通過sysctl工具查看 -->
$ cat /proc/sys/net/ipv4/ip_forward <!-- 直接查看proc文件系統 -->
```

臨時開啟路由轉發功能：

```html
# sysctl net.ipv4.ip_forward=1 <!-- 通過sysctl工具修改 -->
# echo 1 > /proc/sys/net/ipv4/ip_forward <!-- 直接修改proc文件系統 -->
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

### 追蹤路由
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

Linux系統下iputils工具鏈還提供了`tracepath`工具作為traceroute的替代品，
相比traceroute，tracepath的無須root權限，擁有更簡單的命令行參數。

## ARP（Address Resolution Protocol，地址解析協議）
傳統Unix使用和Linux的net-tools均使用`arp`指令查看系統ARP：

```html
<!-- Linux -->
$ arp
Address                  HWtype  HWaddress           Flags Mask            Iface
192.168.198.99                   (incomplete)                              cali4dbaef0c8a4
192.168.198.103          ether   1a:42:4a:ac:bb:1a   C                     cali873a04bdbec
...

<!-- macOS/BSD -->
$ arp -a
loaclhost (10.15.131.254) at 88:40:33:87:d9:5d on en6 ifscope [ethernet]
loaclhost (10.15.131.255) at ff:ff:ff:ff:ff:ff on en6 ifscope [ethernet]
? (172.20.10.1) at 6a:fe:f7:bb:e2:64 on en0 ifscope [ethernet]
...
```

iproute2使用`ip neigh`子指令進行查看系統的ARP：

```
$ ip neigh
192.168.198.99 dev cali4dbaef0c8a4  FAILED
192.168.198.103 dev cali873a04bdbec lladdr 1a:42:4a:ac:bb:1a REACHABLE
...
```

## Bonding
[Bonding](https://wiki.linuxfoundation.org/networking/bonding)
可將兩個以上的物理網卡接口綁定為一個邏輯接口。
使用Bonding可復用多塊網卡提升網絡IO並提高接口可靠性，
組成Bonding的物理接口一部分發生故障時，整個接口依舊可以正常工作。

系統的Bonding信息可查看`/proc/net/bonding`路徑下的對應Bonding設備名稱。

以Debian系列發行版為例，Bonding配置可參考[Bonding Wiki](https://wiki.debian.org/Bonding)，
配置Bonding直接修改`/etc/network/interfaces`即可：

```sh
...
auto bond0
iface bond0 inet static
  address x.x.x.x
  netmask x.x.x.x
  gateway x.x.x.x
  bond-mode 6 # 設置bond模式，可以為編號或者名稱
  bond-miimon 100 # 設置檢查間隔（單位：毫秒）
  bond-slaves eth1 eth2 eth3 ... # 設定組成bond的網卡
...
```

`bond-mode`用於配置Bonding的工作模式，共有編號`0 ~ 6`共7種：

| 編號 | 名稱 | 說明 | 交換機需求 |
| :- | :- | :- | :- |
| 0 | balance-rr | Round-robin策略，按順序從第一張slave網卡到最後一張slave網卡發送數據 | Requires static Etherchannel enabled (not LACP-negotiated) |
| 1 | active-backup | 主備策略，同一時刻僅使用一張slave網卡 | Requires autonomous ports |
| 2 | balance-xor | 使用xmit_hash_policy（源網卡MAC異或目標網卡MAC，按slave網卡數目取余），保證相同兩台機器之間始終使用同一slave網卡 | Requires static Etherchannel enabled (not LACP-negotiated) |
| 3 | broadcast | 同時使用所有slave網卡發送數據，提供高容錯性 | Requires static Etherchannel enabled (not LACP-negotiated) |
| 4 | 802.3ad | Dynamic link aggregation，鏈路聚合模式，需要交換機LACP支持 | Requires LACP-negotiated Etherchannel enabled |
| 5 | balance-tlb | Adaptive transmit load balancing，自適應傳輸負載均衡，可實現發送流量的均衡負載 | Requires autonomous ports |
| 6 | balance-alb | Adaptive load balancing，自適應負載均衡，可實現收、發流量的負載均衡，接收負載均衡通過ARP協商實現 | Requires autonomous ports |

通常使用`bond-mode 0`或`bond-mode 2`。
bond-mode 2可以通過配置layer 3+4模式實現基於協議的哈希策略。
Bonding連線多交換機時，bond-mode 1/5/6可能會因爲ARP衝突導致網絡不通；
bind-mode 3則會重複發包，可能會對上層業務產生影響（以ping為例，會得到dup警告）。

## netstat & ss
`netstat`是net-tools中提供的socket查看工具，各大平台的netstat工具參數有較大差異。

Linux/macOS均支持的netstat參數：

- `-n` 禁用常用端口的名稱轉義，默認常用端口會直接轉換為協議名稱如`80`（http）
- `-h` 展示幫助信息

Linux平台的netstat的常用參數：

- `-a` 展示所有監聽/非監聽類型的socket
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
參數基本與Linux平台的netstat類似，如`-a`、`-t`、`-u`、`-p`、`-n`、`-l`等。

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
| -i interface | 指定網卡，不指定網卡默認使用第一張網卡，可使用any監聽所有網卡 |
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
<!-- 過濾指定目標的ICMP協議 -->
# tcpdump dst a.b.c.d and icmp
<!-- 過濾指定子網下非SSH協議 -->
# tcpdump net a.b.c.d/子網 and not ssh and port not 80

<!-- 可通過括號設置條件優先級（表達式需要加引號） -->
#  tcpdump "net a.b.c.d/子網 and (port 80 or port 443)"
```

## Netcat (nc)
`nc`（netcat）是Unix環境下常用的TCP/UDP連接和監聽工具；
可用於打開TCP連接，發送UDP數據包，監聽TCP/UDP端口，執行端口掃描，
該工具同時支持IPv4和IPv6。

macOS/BSD、部分Linux發行版預裝了該工具，
未預裝該工具的Linux可在發行版軟件倉庫中安裝該工具。

### 客戶端/服務端模式
nc工具可以選擇運行在客戶端/服務端模式。

作為服務端，可使用nc監聽指定端口：

```html
$ nc -l 地址 端口
$ nc -l 地址 <!-- 監聽時可省略主機/IP，默認監聽127.0.0.1/localhost -->
```

作為客戶端，可使用nc向指定端口發送數據：

```
$ nc 地址 端口
```

客戶端/服務端添加`-v`參數均可輸出額外的提示信息。
默認nc使用TCP協議，使用`-u`參數可使用UDP協議進行交互：

```html
<!-- 服務端-->
$ nc -lu 端口
$ nc -lu 地址 端口

<!-- 客戶端 -->
$ nc 地址 端口
```

默認服務端僅能接受**一個**連接，客戶端或服務端使用`Ctrl + C`結束會話後，客戶端、服務端均會關閉。
可使用`-k`可實現僅關閉連接而不退出進程：

```html
$ nc -lk 端口 <!-- 在客戶端連接關閉後可繼續接受新連接 -->
```

可使用`-w`參數設定連接的存活時間，超過存活時間的連接會被斷開：

```html
$ nc -lw 時間數值 端口 <!-- 存活時間單位為：秒 -->
$ nc -lw 時間數值 地址 端口 <!-- 多個參數組合時，-w需要放在最後，否則存在參數解析錯誤 -->
```

監聽連接時，省略主機/IP信息**默認**監聽`127.0.0.1/localhost`，
macOS的nc客戶端在UDP模式下使用localhost無法正常通信，改為IP連接即可。

可使用`-z`參數對指定端口進行活躍性檢測，示例：

```
$ nc -z 127.0.0.1 3306
Connection to 127.0.0.1 port 3306 [tcp/mysql] succeeded!
$ nc -uz 127.0.0.1 3306
Connection to 127.0.0.1 port 3306 [udp/mysql] succeeded!
```

### 數據傳送
默認模式下，nc直接在命令行中進行標準輸入輸出。
與大多數Unix工具類似，可使用管道、重定向來傳送數據量較大的數據，
或者將接收到的數據寫入文件中。

```html
<!-- 重定向輸入數據 -->
$ nc -l 端口 > 輸出文件

<!-- 基於文件重定向發送數據 -->
$ nc 地址 端口 < 輸入文件
<!-- 基於管道發送數據 -->
$ echo 傳輸內容 | nc 地址 端口
```

當數據發送完畢，連接將會關閉。

### Ncat
[Ncat(nmap-ncat)](https://nmap.org/ncat/)是Nmap項目提供的一個現代netcat實現，
ncat兼容絕大多數nc參數，同時提供了更多強大的特性：

- 多連接支持；原版nc作為服務端僅支持單一連接，而ncat做為服務端支持多客戶端連接。
- 更多協議支持；添加了更多現代協議如SSL、SOCKS4、HTTP等的支持。
- 更詳細的日誌輸出；支持通過添加多個`-v`參數展示不同級別的日誌輸出，包括函數調用等細節信息。

ncat使用`-k`參數可接受多個客戶端的連接：

```
$ ncat -lvk 9999
Ncat: Version 7.92 ( https://nmap.org/ncat )
Ncat: Listening on :::9999
Ncat: Listening on 0.0.0.0:9999
Ncat: Connection from ::1.
Ncat: Connection from ::1:59238.
aaaaa
aaa
Ncat: Connection from ::1.
Ncat: Connection from ::1:59241.
bbbbbb
bbbb
```

## iptables/nftables (netfilter)
iptables以及其繼任者nftables均來自[netfilter](https://www.netfilter.org/)項目，
netfilter項目提供了包過濾、網絡地址/端口轉換（NAT），包日誌、用戶態包查詢等功能。

netfilter hooks提供了在Linux內核中提供了框架，允許內核模塊在Linux網絡棧的不同位置註冊回調函數。

### iptables基本操作
查看啟用的iptables規則：

```html
<!-- 默認展示INPUT、FORWARD、OUTPUT 規則 -->
# iptables -L
<!-- 輸出結果示例
Chain INPUT (policy ACCEPT)
target     prot opt source               destination

Chain FORWARD (policy ACCEPT)
target     prot opt source               destination

Chain OUTPUT (policy ACCEPT)
target     prot opt source               destination
-->

<!-- 展示規則同時輸出行號 -->
# iptables -L --line-number

<!-- 額外展示NAT規則 -->
# iptables -t nat -L
<!-- 輸出示例
Chain PREROUTING (policy ACCEPT)
target     prot opt source               destination
DNAT       all  --  anywhere             172.16.0.90          to:10.8.0.6

Chain INPUT (policy ACCEPT)
target     prot opt source               destination

Chain OUTPUT (policy ACCEPT)
target     prot opt source               destination

Chain POSTROUTING (policy ACCEPT)
target     prot opt source               destination
SNAT       all  --  10.8.0.0/24          anywhere             to:192.168.110.181
-->
```

添加和刪除NAT規則：

```html
<!-- SNAT -->
# iptables -t nat -A POSTROUTING -s 源網段/地址 -o 網卡 -j MASQUERADE
# iptables -t nat -A POSTROUTING -s 源網段/地址 -o 網卡 -j SNAT --to-source 需要轉換成的地址
<!-- DNAT -->
# iptables -t nat -A PREROUTING -d 目標網段/地址 -o 網卡 -j DNAT --to-destination 需要轉換成的地址

<!-- 刪除指定規則 -->
# iptables -D 規則類型 規則編號
# iptables -t nat -D 規則類型 規則編號 <!-- 刪除NAT相關規則 -->
```



# Keepalived
[Keepalived](https://www.keepalived.org)在Linux系統上提供浮動IP、高可用等特性。
詳細特性參見[官方文檔](https://www.keepalived.org/manpage.html)。

## vrrp_instance
`vrrp_instance`是Keepalived的核心功能，
基於[VRRP](https://en.wikipedia.org/wiki/Virtual_Router_Redundancy_Protocol)協議提供浮動IP。

```sh
vrrp_instance VI {
	state MASTER # or BACKUP，設置默認的主備狀態
	interface 網卡設備
	priority 100 # 優先級
	advert_int 1 # 檢測間隔（秒）
	virtual_router_id 51 # 虛擬路由ID，用於區分不同VRRP實例，相同浮動IP的成員應使用相同ID
	authentication {
		auth_type PASS
		auth_pass xxxx
	}
	virtual_ipaddress {
		X.X.X.X/X
		X.X.X.X/X dev 網卡設備 # 將虛擬IP綁定到指定網卡設備
	}
}
```

vrrp_instance關鍵字後的實例名稱在不同節點的配置中可以不同，
vrrp_instance通過virtual_router_id來區別是否屬於同一浮動IP的主機組。
配置浮動IP後，選舉MASTER的節點配置中指定的網卡設備上會分配Secondary IP Address：

```html
$ ip addr
...
3: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq portid 3868dd6980f8 state UP group default qlen 1000
    link/ether 38:68:dd:69:80:f8 brd ff:ff:ff:ff:ff:ff
    inet 10.10.10.252/24 brd 10.10.10.255 scope global eno1
       valid_lft forever preferred_lft forever
    inet 10.10.10.254/24 scope global secondary eno1 <!-- Secondary IP -->
       valid_lft forever preferred_lft forever
    inet6 fe80::3a68:ddff:fe69:80f8/64 scope link
       valid_lft forever preferred_lft forever
...
```

當MASTER節點Down機，則浮動IP會根據優先級自動切換到相同virtual_router_id的其它設備中。
使用浮動IP則處理UDP協議時需要注意，服務綁定地址需要為浮動地址，否則，UDP連接的回應包無法送達；
通常默認綁定的地址為網卡的首地址而非Secondary IP，因此使用浮動IP時UDP服務需要顯式指定綁定IP。

## vrrp_sync_group
`vrrp_sync_group`提供了將多個實例編組同步切換的功能，
當同步組內部的任意一個實例發生主備狀態切換，整個組內的其它實例也會同步切換。

早期官方文檔提供的[vrrp_sync_group示例](https://keepalived.readthedocs.io/en/latest/case_study_failover.html#architecture-specification)存在錯誤，
參考[GitHub issue](https://github.com/voxpupuli/puppet-keepalived/issues/129)。

```
vrrp_sync_group VG {
	group {
		VI_1
		VI_2
	}
}

vrrp_instance VI_1 {
	...
}

vrrp_instance VI_2 {
	...
}
```

## Keepalived完整示例
配置文件路徑`/etc/keepalived/keepalived.conf`，
假設存在兩台主機，每台主機各自擁有`10.0.0.*`和`192.168.0.*`網段的網口，
要使主機網口的任意一個發生故障都整組網口一併切換，配置示例：

```html
<!-- 主節點 -->
vrrp_sync_group VG {
    group {
        VI_MAIN
        VI_INNER
    }
}

vrrp_instance VI_MAIN {
    state MASTER
    virtual_router_id 1
    priority 2 # master should have higer priority
    advert_int 1 # check time time intervel
    interface eno1 # bind interface need be generated
    authentication {
        auth_type PASS
        auth_pass pass_xxx_main
    }
    virtual_ipaddress {
        10.0.0.100/24
    }
}

vrrp_instance VI_INNER {
    state MASTER
    virtual_router_id 2
    priority 2
    advert_int 1 # check time time intervel
    interface ens3f3 # bind interface need be generated
    authentication {
        auth_type PASS
        auth_pass pass_xxx_inner
    }
    virtual_ipaddress {
        192.168.0.100/24
    }
}

<!-- 備節點 -->
vrrp_sync_group VG {
    group {
        VI_MAIN
        VI_INNER
    }
}

vrrp_instance VI_MAIN {
    state BACKUP
    virtual_router_id 1
    priority 1
    advert_int 1 # check time time intervel
    interface eno1 # bind interface need be generated
    authentication {
        auth_type PASS
        auth_pass pass_xxx_main
    }
    virtual_ipaddress {
        10.0.0.101/24
    }
}

vrrp_instance VI_INNER {
    state BACKUP
    virtual_router_id 2
    priority 1
    advert_int 1 # check time time intervel
    interface ens3f3 # bind interface need be generated
    authentication {
        auth_type PASS
        auth_pass pass_xxx_inner
    }
    virtual_ipaddress {
        192.168.0.101/24
    }
}
```



# 性能監控與測試
Linux下存在大量的性能監控工具，包括`procps`、`sysstat`等工具套件，以及用於網絡性能監控的`iftop`工具等。

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

## cpupower
`cpupower`用於調整CPU的功耗模式，主要包括frequency（主頻策略）、idle（空閒策略）等。

frequency相關指令：

```html
$ cpupower frequency-info <!-- 查看當前主頻策略，通常默認為 powersave 模式 -->
# cpupower frequency-set -g performance <!-- 設置主頻策略為 performance 模式 -->
# cpupower frequency-set -g powersave <!-- 設置主頻策略為 powersave 模式 -->
```

示例：

```html
$ cpupower frequency-info
analyzing CPU 0:
  driver: intel_pstate
  CPUs which run at the same hardware frequency: 0
  CPUs which need to have their frequency coordinated by software: 0
  maximum transition latency:  Cannot determine or is not supported.
  hardware limits: 1000 MHz - 4.00 GHz
  available cpufreq governors: performance powersave
  current policy: frequency should be within 1000 MHz and 4.00 GHz.
                  The governor "powersave" may decide which speed to use
                  within this range. <!-- 當前主頻策略為 powersave 模式 -->
  current CPU frequency: 1000 MHz (asserted by call to hardware)
  boost state support:
    Supported: yes
    Active: yes

# cpupower frequency-set -g performance
Setting cpu: 0
Setting cpu: 1
Setting cpu: 2
Setting cpu: 3
...

$ cpupower frequency-info
analyzing CPU 0:
  driver: intel_pstate
  CPUs which run at the same hardware frequency: 0
  CPUs which need to have their frequency coordinated by software: 0
  maximum transition latency:  Cannot determine or is not supported.
  hardware limits: 1000 MHz - 4.00 GHz
  available cpufreq governors: performance powersave
  current policy: frequency should be within 1000 MHz and 4.00 GHz.
                  The governor "performance" may decide which speed to use
                  within this range. <!-- 當前主頻策略变更為 performance 模式 -->
  current CPU frequency: 1.06 GHz (asserted by call to hardware)
  boost state support:
    Supported: yes
    Active: yes
```

idle相關指令：

```html
$ cpupower idle-info <!-- 查看IDLE狀態 -->
# cpupower idle-set -D 0 <!-- 禁用指定編號及以上的IDLE狀態，編號為0，則禁用所有IDLE狀態 -->
# cpupower idle-set -E <!-- 啟用IDLE狀態 -->
```

示例：

```html
<!-- 查看當前IDLE狀態 -->
$ cpupower idle-info
CPUidle driver: intel_idle
CPUidle governor: menu
analyzing CPU 0:

Number of idle states: 4 <!-- 當前系統支持IDLE狀態總數 -->
Available idle states: POLL C1-SKX C1E-SKX C6-SKX <!-- 當前系統支持IDLE狀態列表 -->
POLL:
Flags/Description: CPUIDLE CORE POLL IDLE
Latency: 0
Usage: 7455646
Duration: 60865137786
C1-SKX:
Flags/Description: MWAIT 0x00
Latency: 2
Usage: 83620840
Duration: 16659764337
C1E-SKX:
Flags/Description: MWAIT 0x01
Latency: 10
Usage: 452511545
Duration: 264177003930
C6-SKX:
Flags/Description: MWAIT 0x20
Latency: 133
Usage: 670636566
Duration: 1480585205926

<!-- 禁用IDLE -->
# cpupower idle-set -D 0
Idlestate 0 disabled on CPU 0
Idlestate 1 disabled on CPU 0
Idlestate 2 disabled on CPU 0
Idlestate 3 disabled on CPU 0
Idlestate 0 disabled on CPU 1
Idlestate 1 disabled on CPU 1
Idlestate 2 disabled on CPU 1
Idlestate 3 disabled on CPU 1
...

<!-- 查看IDLE信息，可以看到 POLL C1-SKX C1E-SKX C6-SKX 等IDLE狀態已被禁用 -->
$ cpupower idle-info
CPUidle driver: intel_idle
CPUidle governor: menu
analyzing CPU 0:

Number of idle states: 4
Available idle states: POLL C1-SKX C1E-SKX C6-SKX
POLL (DISABLED) : <!-- IDLE狀態已被禁用 -->
Flags/Description: CPUIDLE CORE POLL IDLE
Latency: 0
Usage: 7148617
Duration: 58800889384
C1-SKX (DISABLED) :
Flags/Description: MWAIT 0x00
Latency: 2
Usage: 83620815
Duration: 16659760958
C1E-SKX (DISABLED) :
Flags/Description: MWAIT 0x01
Latency: 10
Usage: 452511088
Duration: 264176360697
C6-SKX (DISABLED) :
Flags/Description: MWAIT 0x20
Latency: 133
Usage: 670636095
Duration: 1480582639238

<!-- 啟用IDLE -->
# cpupower idle-set -E
Idlestate 0 enabled on CPU 0
Idlestate 1 enabled on CPU 0
Idlestate 2 enabled on CPU 0
Idlestate 3 enabled on CPU 0
Idlestate 0 enabled on CPU 1
Idlestate 1 enabled on CPU 1
Idlestate 2 enabled on CPU 1
Idlestate 3 enabled on CPU 1
...
```

## ps
`ps`指令是Unix下最常用的進程信息查看工具，可查看進程的CPU、內存等常見的資源使用情況。
Linux與macOS/BSD系列指令參數有部分差異。

ps指令支持多種參數風格，通常參數為短參數（單橫槓參數，如`-a,-A,-u,-v,-p,-o`），
在BSD風格下部分短參數作為**首個參數**時可以省略單橫槓，Linux也部分支持該風格。
部分參數在有/無單橫槓時含義不同，如`u`（特定顯示格式）和`-u [uid]`（顯示特定uid所屬進程）。

通用用法：

```html
<!---
默認顯示當前用戶進程
macOS 格式 PID TTY TIME CMD
Linux 格式 PID TTY STAT TIME COMMAND
-->
$ ps

<!-- 顯示所有進程，不包含無控制終端的進程 -->
$ ps a
<!-- 顯示所有進程，包含無控制終端的進程 -->
$ ps ax <!-- 參數x指示顯示結果包含無控制終端進程 -->
$ ps A <!-- macOS/BSD專有，Linux使用 -A 參數 -->

<!--
Linux 展示 USER PID %CPU %MEM VSZ RSS TTY STAT START TIME COMMAND
macOS 展示 USER PID %CPU %MEM VSZ RSS TT STAT STARTED TIME COMMAND
-->
$ ps u

<!--
Linux 展示 PID TTY STAT TIME MAJFL TRS DRS RSS %MEM COMMAND
macOS 展示 PID STAT TIME SL RE PAGEIN VSZ RSS LIM TSIZ %CPU %MEM COMMAND
-->
$ ps v

<!-- 組合參數展示所有進程詳細信息 -->
$ ps aux
$ ps avx
<!-- macOS/BSD -->
$ ps Au
$ ps Av

<!-- 展示指定特徵的進程信息 -->
$ ps p 進程號
$ ps U 用戶名

<!-- 展示當前終端進程 -->
$ ps t
<!-- 展示特定終端進程 -->
$ ps t 終端

<!--
Linux 展示 PID TTY STAT TIME COMMAND
macOS 不支持
-->
$ ps f

<!--
Linux 展示 F S UID PID PPID C PRI NI ADDR SZ WCHAN TTY TIME CMD
macOS 展示 UID PID PPID F CPU PRI NI SZ RSS WCHAN S ADDR TTY TIME CMD
-->
$ ps l

<!--
Linux 展示 PID PGID SID TTY TIME CMD
macOS 展示 USER PID PPID PGID SESS JOBC STAT TT TIME COMMAND
-->
$ ps j
```

### 自定義ps輸出內容格式
ps指令還支持通過關鍵字自定義輸出內容：

```html
$ ps o [keyword1,keyword2,keyword3...] <!-- 通用 -->
$ ps -o [keyword1,keyword2,keyword3...] <!-- BSD風格 -->

<!-- 查看支持的指標 -->
$ ps L
```

macOS和Linux均支持的關鍵字：

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

### 使用ps查看進程狀態
ps指令的輸出信息中STAT關鍵字代表進程的狀態，默認ps指令輸出中不包含該字段，
Linux以及macOS/BSD下均可使用`ps x`展示進程狀態：

```html
<!-- Linux -->
$ ps x
PID TTY      STAT   TIME COMMAND
  1 ?        Ss    11:01 /usr/lib/systemd/systemd --system --deserialize=72
  2 ?        S      0:00 [kthreadd]
  3 ?        I<     0:00 [rcu_gp]
  4 ?        I<     0:00 [rcu_par_gp]
  5 ?        I<     0:00 [slub_flushwq]
  6 ?        I<     0:00 [netns]
  8 ?        I<     0:00 [kworker/0:0H-events_highpri]
 ...

<!-- macOS/BSD -->
$ ps x
PID TT  STAT        TIME COMMAND
  0  -  DLs      8:21.91 [kernel]
  1  -  ILs      0:00.91 /sbin/init
  2  -  DL       0:00.00 [KTLS]
  3  -  DL       0:00.00 [crypto]
  4  -  DL       1:41.77 [cam]
  5  -  DL       6:38.46 [zfskern]
  ...
```

亦可使用自定義關鍵字方式輸出該字段內容。

進程狀態的含義可參考Linux中man手冊的描述：

> Here are the different values that the s, stat and state output specifiers (header "STAT" or "S") will display
> to describe the state of a process:
>
>         D    uninterruptible sleep (usually IO)
>         I    Idle kernel thread
>         R    running or runnable (on run queue)
>         S    interruptible sleep (waiting for an event to complete)
>         T    stopped by job control signal
>         t    stopped by debugger during the tracing
>         W    paging (not valid since the 2.6.xx kernel)
>         X    dead (should never be seen)
>         Z    defunct ("zombie") process, terminated but not reaped by its parent
>
> For BSD formats and when the stat keyword is used, additional characters may be displayed:
>
>         <    high-priority (not nice to other users)
>         N    low-priority (nice to other users)
>         L    has pages locked into memory (for real-time and custom IO)
>         s    is a session leader
>         l    is multi-threaded (using CLONE_THREAD, like NPTL pthreads do)
>         +    is in the foreground process group

### 查看LWP線程信息
Linux下默認ps指令僅展示進程，查看LWP線程信息：

```html
<!-- 使用 -L 參數展示LWP線程信息 -->
$ ps -L
$ ps -efL <!-- 與其它參數組合使用 -->
```

亦可通過使用`o/-o`參數指定輸出相關關鍵字：

```html
<!--
lwp 為LWP線程ID
psr 為當前使用的CPU核心編號

查看LWP以及對應的CPU核心分佈
-->
$ ps -o cmd,pid,lwp,psr
```

## procps
[`procps`](https://gitlab.com/procps-ng/procps)包提供了核心的性能監測工具套件，
包括`top`、`vmstat`、`pmap`、`uptime`、`tload`等常用工具；

### top
`top`是Linux/Unix下最常見的性能監控工具，所有的Linux發行版均包含該工具，Linux下的top工具由procps套件提供。
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
0      kernel_task  11.9 08:21:25 194/4 0    0     752M+  0B     0B     0     0     running   0[0]
...
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
...
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

- 展示每個核心的消耗

	默認top指令展示的是所有CPU的總體資源消耗。
	Linux下載top介面中輸入`1`即可展示每個CPU核心各自的資源消耗，再次輸入則關閉。

## iftop
`iftop`是常用的網絡IO監控工具，通常發行版中並未直接包含，需要從倉庫中安裝：

```html
<!-- CentOS中iftop不在主倉庫中 -->
# yum install epel-release
# yum install iftop

<!-- 大便系 -->
# apt install iftop

<!-- Arch系 -->
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

```html
<!-- 監控指定網卡的IO -->
$ iftop -i [devname]

<!-- 按照源/目標地址排序 -->
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

```html
# apt install sysstat <!-- 大便系 -->
# yum install sysstat <!-- 紅帽系 -->
# pacman -S sysstat <!-- Arch系 -->
```

### pidstat
`pidstat`工具相比系統自帶的ps工具，提供了更為完善的性能參數統計。

默認指令會監控所有進程；
統計指定進程，並指定監控間隔：

```html
<!-- 按照指定的時間間隔輸出間隔內的平均資源佔用，退出指令後會展示整個指令期間的平均資源佔用 -->
$ pidstat -p 進程號 [interval]

<!-- 統計指定次數後退出 -->
$ pidstat -p 進程號 [interval] [count]
```

### mpstat
`mpstat`用於查看系統的CPU負載：

```html
<!-- 默認僅展示綜合負載 -->
$ mpstat

<!-- 同時展示每個核心的負載 -->
$ mpstat -P ALL
```

### iostat
`iostat`工具用於監測磁盤IO，基本使用方式與pidstat類似。

默認指令會監控所有磁盤；
統計指定磁盤，並指定監控間隔：

```
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

## sysbench
[`sysbench`](https://github.com/akopytov/sysbench)是基於`LuaJIT`實現的一套多線程性能測試工具。

多數發行版倉庫中已包含了sysbench，可直接安裝：

```html
<!-- macOS Homebrew -->
$ brew install sysbench

<!-- 大便係 -->
# apt install sysbench

<!-- Arch係 -->
# pacman -S sysbench

<!-- CentOS需要添加額外倉庫 -->
# curl -s https://packagecloud.io/install/repositories/akopytov/sysbench/script.rpm.sh | bash
# yum install sysbench
```

基本指令語法：

```
$ sysbench [options]... [testname] [command]
```

- `testname`為測試類型（可選），內置的測試類型包含`fileio`、`memory`、`cpu`等。
- `command`為測試指令（可選），與內置測試配合使用，用於設置測試的行為，包含下列指令：
	- `prepare`執行部分操作的準備操作，例如在fileio測試中，會在磁盤上創建必要的文件。
	- `run`執行測試操作。
	- `cleanup`移除測試創建的臨時數據文件。
	- `help`展示指令幫助信息。
- `options`為額外的命令行參數，參數以`--`開始。

實例，CPU性能測試：

```html
<!-- 默認參數下，使用單線程執行10s測試 -->
$ sysbench cpu run

<!-- 使用指定線程數執行測試 -->
$ sysbench --threads=線程數目 cpu run

<!-- 執行測試指定秒 -->
$ sysbench --time=秒數 cpu run

<!-- 執行測試指定次數 -->
$ sysbench --event=測試次數 cpu run
```

多個限定參數可組合使用，滿足其中一個限定條件後會終止測試。

## fio
[`fio`](https://github.com/axboe/fio)用於多維度測試磁盤性能，

基本操作：

```
$ fio --name 任務名稱 --filename 測試目標 --rw 測試操作 --bs 塊大小 --ioengine IO引擎 --runtime 測試時間
```

參數說明參考[官方文檔](https://fio.readthedocs.io/en/latest/fio_doc.html)。

常用參數：

| 參數 | 說明 |
| :- | :- |
| name | 測試任務名稱（必要，缺少該參數會報錯） |
| runtime | 測試時間（單位：秒）|
| filename | 測試目標，可以是文件、塊設備等 |
| size | 測試數據大小 |
| bs | 讀寫塊大小，常見取值`4K`、`4M`等 |
| rw | 讀寫操作，常見取值`read/write/rw`（順序讀、寫、讀寫），`randread/randwrite/randrw`（隨機讀、寫、讀寫） |
| ioengine | IO引擎，常見取值`sync`（同步IO），`libaio`（Linux異步IO） |
| sync | 指定打開文件的IO方式，取值可為`none/0`（非同步IO，默認值），`sync/1`（使用O_SYNC），`dsync`（使用O_DSYNC） |
| iodepth | 文件IO單元書目，默認值`1`，iodepth大於1時對sync IO引擎無效 |
| direct | 使用非緩衝IO，對應`O_DIRECT`，取值可為`0`（使用緩衝IO，默認值），`1`（使用非緩衝IO） |
| invalidate | 使現在文件IO生成的buffer/page cache無效化，取值可為`1`（默認）和`0` |

fio的測試目標可以為**塊設備**或是文件系統中的**普通文件**，
測試目標為塊設備則反映設備的裸盤性能。

測試目標已存在時可不設置size參數，fio會以測試目標自身大小作為測試數據大小；
測試目標不存在時必須設置size參數，fio會創建對應大小的文件。

默認fio會寫滿指定size大小的數據後結束，設置runtime則會在達到測試時間後立即結束。

fio輸出結果説明：

```html
$ fio --name test1 --filename /dev/vdb --rw write --bs 4M --ioengine libaio --iodepth 16
test1: (g=0): rw=write, bs=(R) 4096KiB-4096KiB, (W) 4096KiB-4096KiB, (T) 4096KiB-4096KiB, ioengine=libaio, iodepth=16
fio-3.34
Starting 1 process
Jobs: 1 (f=1): [f(1)][100.0%][eta 00m:00s]
test1: (groupid=0, jobs=1): err= 0: pid=2472: Wed May 10 17:33:54 2023 <!-- 任務名稱，進程號，測試時間 -->
  write: IOPS=4, BW=16.5MiB/s (17.3MB/s)(10.0GiB/619920msec); 0 zone resets <!-- 帶寬、IOPS -->
    slat (usec): min=1485, max=6053.6k, avg=242062.98, stdev=304457.15
    clat (usec): min=34, max=16007k, avg=3631335.35, stdev=2530028.55
     lat (msec): min=27, max=16219, avg=3873.40, stdev=2643.07
    clat percentiles (msec): <!-- 延遲分佈 -->
     |  1.00th=[   28],  5.00th=[  334], 10.00th=[ 1603], 20.00th=[ 2072],
     | 30.00th=[ 2299], 40.00th=[ 2635], 50.00th=[ 3004], 60.00th=[ 3339],
     | 70.00th=[ 3842], 80.00th=[ 4665], 90.00th=[ 6812], 95.00th=[ 9329],
     | 99.00th=[12550], 99.50th=[13624], 99.90th=[15905], 99.95th=[15905],
     | 99.99th=[16040]
   bw (  KiB/s): min= 7447, max=540672, per=100.00%, avg=19123.85, stdev=22224.28, samples=1095
   iops        : min=    1, max=  132, avg= 4.42, stdev= 5.45, samples=1095
  lat (usec)   : 50=0.04%
  lat (msec)   : 50=1.91%, 100=0.08%, 250=2.30%, 500=1.37%, 750=0.16%
  lat (msec)   : 1000=0.23%, 2000=11.84%, >=2000=82.07%
  cpu          : usr=0.07%, sys=3.70%, ctx=43458, majf=0, minf=16 <!-- CPU佔用 -->
  IO depths    : 1=0.1%, 2=0.1%, 4=0.2%, 8=0.3%, 16=99.4%, 32=0.0%, >=64=0.0%
     submit    : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.0%, 32=0.0%, 64=0.0%, >=64=0.0%
     complete  : 0=0.0%, 4=100.0%, 8=0.0%, 16=0.1%, 32=0.0%, 64=0.0%, >=64=0.0%
     issued rwts: total=0,2560,0,0 short=0,0,0,0 dropped=0,0,0,0
     latency   : target=0, window=0, percentile=100.00%, depth=16

Run status group 0 (all jobs):
  WRITE: bw=16.5MiB/s (17.3MB/s), 16.5MiB/s-16.5MiB/s (17.3MB/s-17.3MB/s), io=10.0GiB (10.7GB), run=619920-619920msec

Disk stats (read/write):
  vdb: ios=47/10046, merge=0/2552552, ticks=16/17496007, in_queue=17496023, util=99.80%
```

## RT-Tests
[`RT-Tests`](https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/rt-tests)
是Linux官方維護的一套實時性測試工具集。

RT-Tests通常已包含在各大發行版的倉庫中，可直接安裝：

```html
# apt install rt-tests <!-- 大便係 -->
# pacman -S rt-tests <!-- Arch係 -->
```

### cyclictest
[`cyclictest`](https://wiki.linuxfoundation.org/realtime/documentation/howto/tools/cyclictest/start)
通過重複測量線程預期喚醒時間與實際喚醒時間的差值來統計系統的實時性。

直接執行cyclictest，默認會使用單個核心，無限循環測試，直到手動退出進程：

```
$ cyclictest
# /dev/cpu_dma_latency set to 0us
policy: other/other: loadavg: 0.12 0.14 0.40 1/172 12785

T: 0 (12783) P: 0 I:1000 C: 573372 Min:     53 Act:  103 Avg:  147 Max:   14413
```

常用參數：

| 參數 | 說明 |
| :- | :- |
| -S/--smp | 測試所有核心，相當於`-t -a` |
| -l/--loops | 測試循環次數，默認為0（無限循環） |
| -m/--mlockall | 鎖定分配內存，避免換頁，默認關閉 |
| -i/--interval | 設置基礎測試間隔，單位為us，默認為1000us |

## iperf / qperf
[`iPerf`](https://iperf.fr/)以及[`qperf`](https://github.com/linux-rdma/qperf)
可用於測試網絡的帶寬、時延、UDP丟包率等網絡性能參數。

iPerf目前最新版本為`iperf3`，主流發行版的軟件源中已包含了該軟件包，直接安裝即可：

```html
# apt install iperf3 <!-- 大便係 -->
# pacman -S iperf3 <!-- Arch係 -->
$ nix-env -iA nixos.iperf <!-- Nix -->
```

使用iPerf需要在服務端、客戶端各自啟動進程：

```html
<!-- 服務端
常用參數：
-B 指定綁定地址
-p 指定監聽端口
-D 作為服務運行
-->
$ iperf3 -s

<!-- 客戶端
常用參數：
-u 使用UDP協議
-n 限制帶寬，示例 2M 4M 512K
-P 設置並行數
-->
$ iperf3
```

iperf每個服務端進程僅能同時接收一個客戶端的請求，需要同時接收多個客戶端請求則應啟動多個進程。
iperf3服務端不需要設定監聽協議，會根據客戶端的協議類型自動選擇。

## HTTP壓測工具
常見的HTTP壓測工具：

- [ab(Apache Bench)](https://httpd.apache.org/docs/current/programs/ab.html)
命令行工具，Apache HTTP Server的一部分
- [Apache JMeter](https://jmeter.apache.org/) Java實現的GUI壓測工具
- [autocannon](https://github.com/mcollina/autocannon) NodeJS實現的命令行壓測工具



# 通知服務（Notification）
多數Linux桌面環境默認已內置了通知機制，
如`Gnome`、`KDE`等完善的桌面環境，以及`AwesomeWM`等少部分窗口管理器；
然而多數窗口管理器未集成通知服務，默認無法展示通知，需要自行配置通知服務。

## libnotify
`libnotify`爲多數通知服務提供了通用的通知發送指令接口：

```html
$ notify-send 消息主題 消息內容

<!-- 展示進度條（progress bar）-->
$ notify-send 消息主題 消息內容 -h int:value:百分比數值

<!-- 設置通知駐留時間，單位：毫秒 -->
$ notify-send 消息主題 消息內容 -t 時間數值

<!--
設置通知級別，不同通知級別通常有不同的通知色彩以及駐留時間，取決與通知服務的實現
通知級別取值：low，normal，critical
-->
$ notify-send 消息主題 消息內容 -u 通知級別
```

## Dunst
[`Dunst`](https://dunst-project.org/)提供了輕量級的通知服務實現，
適合搭配各類未內置通知服務的窗口管理器使用。

安裝Dunst：

```
# pacman -S dunst
```

dunst兼容libnotify，但完整功能需要使用自身指令。
dunst使用`dunstctl`管理通知，使用`dunstify`發送通知，常用功能：

```html
<!-- 關閉所有通知 -->
$ dunstctl close-all

<!--
dunstify 發送通知基本功能與 notify-send 類似，
dunstify僅能在通知服務爲Dunst時使用，但提供了完整的功能
-->
$ dunstify 消息主題 消息內容
```

### Dunst配置
Dunst配置可參考[官方文檔](https://dunst-project.org/documentation/)，
以及[ArchLinux Wiki](https://wiki.archlinux.org/title/Dunst)
和[Github Wiki](https://github.com/dunst-project/dunst/wiki)。

全局配置文件路徑爲`/etc/dunst/dunstrc`，用戶配置路徑爲`~/.config/dunst/dunstrc`。

默認Dunst處理通知的行爲是左鍵關閉當前通知，右鍵關閉全部通知，中鍵執行通知操作；
該行爲不符合常規通知系統的操作習慣（多數通知系統左鍵爲執行通知操作），進行修改：

```ini
[global]
	# Change the default notification actions.
	mouse_left_click = do_action, close_current
	mouse_middle_click = close_all
	mouse_right_click = close_current
```

設置通知背景透明：

```ini
[global]
	# Set up the transparency (0~100)
	transparency = 15
```



# 終端模擬器
終端模擬器是GUI環境下常用的應用之一，用於在GUI環境下創建終端會話並進行交互。

## VTE
`VTE`是Gnome項目提供的輕量級終端庫，許多終端軟件使用VTE實現，
如`gnome-terminal`、`roxterm`等。VTE自身亦可做爲獨立的終端軟件使用。

相比其它終端模擬器，VTE提供了豐富的特性和較少的依賴（僅僅依賴`GTK+`）。

VTE當前的主流版本爲基於GTK2的VTE2和基於GTK3的VTE3。
在Arch Linux/NixOS等多數發行版的打包中，
VTE2的指令名稱爲`vte`，VTE3的指令名稱爲`vte-2.91`。

VTE2現已停止維護，部分發行版（如Arch Linux）已經移除了其對應軟件包。

### VTE2
VTE2開發時間較早，現已不支持部分終端顯示特性
(如systemctl的服務狀態輸出中包含路徑字符串，在VTE2下顯示為亂碼)。

VTE通過在啓動時添加命令行參數進行設置，VTE2常見參數如下所示：

| 參數 | 說明 |
| :- | :- |
| `-g` | 設定終端初始大小(行列大小)，格式爲`124x456` |
| `-f` | 設定終端字體，參數後添加字體名稱 |
| `-n` | 設定終端可回滾的行數，參數後添加回滾行數數值 |
| `-h` | 設定終端色彩 |
| `-c` | 在終端中執行指令 |
| `-W` | 使用`GtkScrolledWindow`做爲終端容器，啓用此參數時使用`-g`參數設定終端大小纔有效 |
| `-P` | 設定終端的滾動條顯示模式，參數可以爲`always`(總是顯示)、`auto`(自動)、`never`(從不顯示) |
| `-B` | 設定終端背景圖片 |
| `-S` | 設定終端使用的`shell` |
| `--reverse` | 反轉終端色彩 |

以`awesomewm`配置中使用的VTE選項爲例：

```
$ vte -W -P never -g 120x40 -f "Monaco 10" -n 5000 --reverse
```

執行結果爲打開大小爲`120`列`40`行的`VTE2`終端，終端回滾`5000`行，不顯示滾動條，反轉配色。

### VTE3
VTE3默認會使用Gnome3 App慣用的HeadBar風格，默認參數下啟動會帶有一個巨大的窗口裝飾器，
可使用參數關閉。

VTE3大多數參數兼容VTE2，為保持與VTE2相近的風格，可使用以下參數：

| 參數 | 說明 |
| :- | :- |
| `-T` | 透明度，參數為數值，VTE3默認終端不透明 |
| `--no-decorations` | 禁用巨醜的HeadBar |
| `--no-scrollbar` | VTE3默認顯示滾動條，使用該參數禁用 |

保持與VTE2相似的風格，參數示例：

```
$ vte-2.91 -g 120x40 -f "Monaco 10" -n 5000 -T 20 --reverse --no-decorations --no-scrollbar
```

部分參數在VTE3中已經移除，如`-W`，使用該類參數會報錯；
部分參數未移除，但在幫助信息中已不存在，如`-P`，使用該類參數不報錯但不生效。

### 複製粘貼快捷鍵
VTE中提供了**剪切板**功能，但Linux終端中常見的複製粘貼快捷鍵並不生效。

在VTE中複製粘貼快捷鍵如下：

- `Control + Insert` 複製
- `Shift + Insert` 粘貼

## Kitty
[Kitty](https://sw.kovidgoyal.net/kitty/)是使用OpenGL實現GUI渲染的終端，且功能豐富，支持多標籤。

Kitty的組合鍵使用`ctrl + shift`組合其它按鍵，常用快捷鍵：

| 快捷鍵 | 說明 |
| :- | :- |
| `ctrl + shift` + `t` | 創建新標籤頁 |
| `ctrl + shift` + `q` | 關閉當前標籤頁 |
| `ctrl + shift` + `left` / `right` | 切換當前標籤頁 |
| `ctrl + shift` + `,` / `.` | 移動當前標籤頁 |
| `ctrl + shift` + `w` | 關閉終端程序 |
| `ctrl + shift` + `h` | 進入搜索模式，搜索模式下輸入`/`進行後向搜索，輸入`?`進行前向搜索 |



# Linux字體（fontconfig）
Linux下字體配置需要依賴`fontconfig`軟件包，多數發行版安裝了桌面環境後會自動將該包作為依賴安裝。

手動安裝該軟件包：

```html
# yum/dnf install fontconfig <!-- 紅帽係 -->
# pacman -S fontconfig <!-- Arch係 -->
# apt install fontconfig <!-- 大便係 -->
```

安裝fontconfig軟件包後，可使用`man fonts.conf`查看字體配置手冊。

## 管理字體
fontconfig軟件包提供了一系列字體管理工具。

```html
$ fc-list <!-- 列出系統中已安裝的字體信息，包括字體路徑、名稱、字型等 -->
/usr/share/fonts/dejavu/DejaVuSansCondensed-Oblique.ttf: DejaVu Sans,DejaVu Sans Condensed:style=Condensed Oblique,Oblique
/usr/share/fonts/dejavu/DejaVuSansCondensed-Bold.ttf: DejaVu Sans,DejaVu Sans Condensed:style=Condensed Bold,Bold
/usr/share/fonts/dejavu/DejaVuSans.ttf: DejaVu Sans:style=Book
...

$ fc-cache <!-- 刷新字體緩存，用於環境中新增了字體之後 -->
$ fc-conflist <!-- 查看當前生效的配置列表 -->

<!-- 檢查特定字形當前使用的字體 -->
$ fc-match 字形
$ fc-match --verbose 字形 <!-- 輸出特定字形的詳細信息 -->
```

## 字體配置
字體文件可存放在系統路徑`/usr/share/fonts`以及用戶路徑`~/.local/share/fonts`，
早期用戶字體路徑`~/.fonts`現已廢棄。

全局的字體配置路徑為`/etc/fonts/fonts.conf`以及`/etc/fonts/conf.d`目錄。
用戶字體配置文件早期為`~/.fonts.conf`以及`~/.fonts.conf.d`目錄，
現已被標記爲**廢棄**。

現在的用戶配置爲`$XDG_CONFIG_HOME/fontconfig/fonts.conf`
（通常爲`$HOME/.config/fontconfig/fonts.conf`）；
以及`$XDG_CONFIG_HOME/fontconfig/conf.d`
（通常爲`$HOME/.config/fontconfig/conf.d`）。

字體配置遵循XML語法。

字體軟件包通常提供配套的配置存放於`/usr/share/fontconfig/conf.avail`路徑下，
可在用戶配置路徑下創建符號鏈接使之生效。

字體配置示例：

```xml
<?xml version='1.0'?>
<!DOCTYPE fontconfig SYSTEM 'fonts.dtd'>

<!-- Link this file (if need) to path ~/.fonts.conf -->
<fontconfig>

	<!-- Default fonts -->
	<alias binding="same">
		<family>sans-serif</family>
		<prefer><family>Noto Sans</family></prefer>
	</alias>

	<alias binding="same">
		<family>serif</family>
		<prefer><family>Noto Sans</family></prefer>
	</alias>

	<alias binding="same">
		<family>monospace</family>
		<prefer><family>Cascadia Code PL</family></prefer>
	</alias>

	<alias binding="same">
		<family>emoji</family>
		<prefer>
			<family>Cascadia Code PL</family>
			<family>Noto Color Emoji</family>
		</prefer>
	</alias>

	<alias binding="same">
		<family>system-ui</family>
		<prefer>
			<family>Cascadia Code PL</family>
			<family>Noto Sans</family>
		</prefer>
	</alias>

</fontconfig>

```

字體配置中`<family/>`標籤制定需要設置的字形，系統字形如下所示：

| 字形 | 說明 |
| :- | :- |
| serif | 襯線字體 |
| sans-serif | 無襯線字體 |
| monospace | 等寬字體，常用於編碼 |
| system-ui | UI字體 |
| emoji | emoji字符 |

檢查字體配置可使用`fc-match`指令，示例：

```
$ fc-match system-ui
NotoSans-Regular.ttf: "Noto Sans" "Regular"
$ fc-match emoji
NotoColorEmoji.ttf: "Noto Color Emoji" "Regular"
$ fc-match monospace
CascadiaCodePL-Regular.otf: "Cascadia Code PL" "Regular"
```



# Debian系列發行版包管理
`Debian`系列發行版使用`deb`格式作爲軟件包的打包、分發格式；
使用`apt`（依賴管理）和`dpkg`（包處理）進行管理。

## apt
`apt`是Debian系列發行版的前端包管理工具，用於deb處理軟件包之間的依賴關係。
主要功能如下：

- 在鏡像源中搜索、查找需要的軟件包。
- 計算軟件包的依賴。
- 系統更新。
- 查看指定軟件包的狀態。
- 變更已安裝軟件包的狀態。
- 安裝、卸載軟件包（通過dpkg）。

apt的常用指令：

```html
<!-- 更新軟件源 -->
# apt-get update
<!-- 更新無依賴變化的軟件包 -->
# apt-get upgrade
<!-- 更新所有軟件包 -->
# apt-get dist-upgrade

<!-- 安裝軟件包 -->
# apt-get install 軟件包名稱
# apt-get install 軟件包名稱/倉庫名稱 <!-- 安裝指定倉庫中的軟件包（在軟件包同時存在與多個倉庫時） -->
# apt-get install 軟件包名稱=版本號 <!-- 安裝指定版本的軟件包（可用於降級版本） -->

<!-- 卸載軟件包 -->
# apt-get remove 軟件包名稱
# apt-get remove --purge 軟件包名稱 <!-- 卸載軟件包時同時刪除配置 -->

<!-- 清理無用依賴 -->
# apt-get autoremove
# apt-get autoremove --purge

<!-- 查看指定軟件包詳情 -->
$ apt-cache show 軟件包名稱
<!-- 針對多個倉庫中同時存在的軟件包，查看軟件包所屬倉庫及候選版本 -->
$ apt-cache madison 軟件包名稱
$ apt-cache policy 軟件包名稱
<!-- 搜索軟件包 -->
$ apt-cache search 軟件包名稱 <!-- 模糊查找（包括相關信息） -->
$ apt-cache list '*軟件包關鍵字*' <!-- 精確匹配軟件包名關鍵字查找 -->
<!-- 查看包的依賴 -->
$ apt-cache depends 軟件包名稱
<!-- 計算包的反向依賴（被引用依賴） -->
$ apt-cache rdepends 軟件包名稱 <!-- 默認查詢所有依賴（包括未安裝依賴），輸出結果中有豎橫線｜標誌的為本地已安裝的依賴項 -->
$ apt-cache rdepends --recurse 軟件包名稱 <!-- 遞歸查詢反向依賴 -->
$ apt-cache rdepends --installed 軟件包名稱 <!-- 僅查詢安裝的反向依賴 -->
$ apt-cache rdepends --installed --important 軟件包名稱 <!-- 查詢安裝的反向依賴，僅輸出重要依賴 -->

<!-- 將某個包標記爲自動/手動安裝 -->
# apt-mask auto/manual 軟件包名稱
<!-- 顯示手動安裝/自動安裝的包 -->
$ apt-mask showauto/showmanaul
```

較新版本的apt工具為部分常用指令提供了更簡單的命令形式，直接使用apt作為指令，
apt指令整合了apt-get和apt-cache指令的部分功能，並提供更好的交互體驗。

```html
<!-- apt-get 相關 -->
# apt update
# apt install/remove 軟件包名稱
# apt autoremove
# apt purge 軟件包名稱
# apt upgrade/full-upgrade

<!-- apt-cache 相關 -->
$ apt show/search/list 軟件包名稱
# apt rdepends 軟件包名稱
```

apt手冊中提及了新版apt工具的兼容性保證問題：

> The apt(8) commandline is designed as an end-user tool and it may change behavior between versions. While it tries not to break backward compatibility this is not guaranteed either if a change seems beneficial for interactive use.
>
> All features of apt(8) are available in dedicated APT tools like apt-get(8) and apt-cache(8) as well. apt(8) just changes the default value of some options (see apt.conf(5) and specifically the Binary scope). So you should prefer using these commands (potentially with some additional options enabled) in your scripts as they keep backward compatibility as much as possible.

即apt命令的輸出可能會隨著版本升級而發生改變（不保證前向兼容），
將apt相關子指令的輸出結果用在重定向時會輸出警告信息：

```
$ apt rdepends iproute2 | grep "|"

WARNING: apt does not have a stable CLI interface. Use with caution in scripts.

 |Depends: wondershaper
 |Depends: vpnc-scripts
 |Depends: tcllib
 ...
```

使用apt-cache則不會輸出警告信息：

```
$ apt-cache rdepends iproute2 | grep "|"
 |Depends: wondershaper
 |Depends: vpnc-scripts
 |Depends: tcllib
 ...
```

### apt下載依賴
apt install指令可以使用`-d/--download-only`參數僅獲取安裝包而不安裝
（通常用於下載離線安裝時使用的安裝包）：

```html
<!--
使用--download-only參數會基於當前環境解析依賴，下載目標軟件包以及缺失的依賴項，
依賴項會被緩存在 /var/cache/apt/archives 路徑下
-->
# apt install -d 軟件包名稱
# apt install --download-only 軟件包名稱
```

### apt依賴類型
deb軟件包的依賴包括下列幾種：

| 依賴類型 | 說明 | 關聯度（與當前軟件包） |
| :- | :- | :- |
| Depends | 必要依賴，必須被安裝，否則當前軟件包無法工作 | 高 |
| Recommends | 推薦依賴，通常與當前軟件包一同搭配使用 | 中 |
| Suggests | 建議依賴，通常是建議的軟件包中包含與當前軟件包功能相關的文件 | 低 |

關於的區別，參考[Debian官方FAQ](https://www.debian.org/doc/manuals/debian-faq/pkg-basics.en.html#depends)。

默認配置下，使用apt安裝軟件包，會安裝Depends和Recommends，而不會安裝Suggests；
使用autoremove清理軟件包，則會同時保留Depends、Recommends和Suggests。

可通過在`/etc/apt/apt.conf.d`路徑下添加配置文件設置各類依賴的安裝策略和自動清理策略，
默認策略如下：

```sh
APT::Install-Recommends "true"; # 安裝 Recommends 依賴
APT::Install-Suggests "false"; # 不安裝 Suggests 依賴
APT::AutoRemove::RecommendsImportant "true"; # 不清理 Recommends 依賴
APT::AutoRemove::SuggestsImportant "true"; # 不清理 Suggests 依賴
```

要使清理依賴規則與安裝時匹配，應在清理時不保留Suggests，添加配置：

```sh
APT::AutoRemove::SuggestsImportant "false";
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
# apt-file search 文件名
```

### add-apt-repository
`add-apt-repository`是Ubuntu對apt工具的功能擴展，
解決了傳統Debian係發行版添加第三方庫操作較為複雜的問題。

傳統Debian發行版添加外部倉庫需要添加source.list，並執行導入證書等操作
（詳情參見[Debian Wiki](https://wiki.debian.org/DebianRepository/UseThirdParty)）；
在Ubuntu中，提供了[`Personal Package Archives`(PPA)](https://launchpad.net/ubuntu/+ppas)，
集中管理用戶創建的第三方倉庫，使用者通過add-apt-repository工具僅需單指令即可完成倉庫添加配置。

以redis為例，通常較為穩定的發行版倉庫自帶redis版本較低，Ubuntu可添加PPA來獲得最新版：

```
# add-apt-repository ppa:redislabs/redis
```

add-apt-repository包含在`software-properties-common`軟件包中，
通常Ubuntu及其衍生發行版會默認安裝該包，部分精簡鏡像（如ubuntu-core）未包含該工具，可手動安裝：

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
<!-- 安裝一個deb包 -->
# dpkg -i deb安裝包
<!-- 批量安裝deb包 -->
# dpkg -i xxx*.deb
<!--
批量安裝deb包時，解析包的順序是按照包名稱的ASC碼順序，
在多數場景下該順序與實際依賴順序不符，因此會造成部分軟件包不滿足依賴而配置失敗，
安裝時搭配--force-all參數可強制配置軟件包，避免因為依賴解析順序而中斷配置流程
-->
# dpkg -i --force-all xxx*.deb

<!-- 移除軟件包 -->
# dpkg -r 軟件包名稱
<!-- 移除軟件包同時清除配置（包括配置文件以及執行postrm） -->
# dpkg -rP 軟件包名稱
# dpkg -r --purge 軟件包名稱

<!-- 列出所有已安裝包的狀態信息 -->
$ dpkg -l
$ dpkg --list
<!-- 列出指定包名的包的狀態信息 -->
$ dpkg -l 軟件包名稱

<!-- 包狀態帶有rc標記時說明包存在殘餘配置，根據包狀態篩選出有殘餘配置文件的包 -->
$ dpkg -l 軟件包名稱 | grep '^rc'
<!-- 清除指定包的殘餘配置 -->
# dpkg --purge 軟件包名稱
<!-- 查找所有存在殘餘配置的包並清除殘餘配置 -->
$ dpkg -l | grep "^rc" | cut -d " " -f 3 | xargs sudo dpkg --purge

<!-- 查詢文件屬於哪個已安裝的軟件包 -->
$ dpkg -S 文件名
<!-- 查看指定包的詳細描述信息 -->
$ dpkg -s 軟件包名稱
<!-- 列出指定包內包含的文件 -->
$ dpkg -L 軟件包名稱
```

## deb打包 (Binary packages)
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

	維護者腳本包括preinst、postinst、prerm、postrm等，
	可用於在安裝過程的前後附加一些特殊操作，這些腳本權限範圍需要在`0555`到`0775`之間。
	維護者腳本詳細介紹可參考[官方文檔](https://www.debian.org/doc/debian-policy/ch-maintainerscripts.html)，
	以及[Debian Wiki](https://wiki.debian.org/MaintainerScripts)。

	維護者腳本存在一些限制，例如不能在腳本中使用dpkg相關功能(因為執行腳本期間dpkg會被鎖定)。

- 目錄其它路徑下的文件會被視為安裝文件，執行安裝過程中會被複製到根路徑下的對應位置

	例如`./opt/xxx`會直接複製到`/opt/xxx`路徑下。
	軟件包含的文件信息會被dpkg數據庫記錄，
	同一個路徑不能直接被不同軟件包持有，否則安裝時會產生衝突。

使用`dpkg-deb`工具進行將一個指定目錄打包為deb包：

```
$ dpkg-deb --build 打包路徑
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

模板輸入在安裝包被執行一次後會被緩存，重複安裝流程，
對話框則不會再出現（狀態已被debconf數據庫中）。
若需要每次執行安裝都強制展示對話框，
則應在每次調用db_input前設置模板的seen屬性：

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

關於使用dpkg-divert，可參考
[Ask Ubuntu](https://askubuntu.com/questions/116768/providing-a-customized-config-file-for-another-package)
上的對應問題。

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

## apt軟件源配置
使用`apt`工具需要正確配置鏡像源地址，配置文件爲`/etc/apt/sources.list`。

`Debian`系列發行版軟件源格式爲：

```sh
# 二進制包
deb 軟件源地址 版本號 倉庫類型

# 源碼包
deb-src 軟件源地址 版本號 倉庫類型
```

其中：

- `軟件源地址` 爲有效的`URL`，可以是某個提供鏡像源服務的站點地址，也可以是本地源路徑
- `版本號` 爲發行版的版本代號，一行只能填寫一個版本號
- `倉庫類型` 爲按照授權類型劃分的倉庫類別，可以一行同時添加多個倉庫類型

軟件源地址使用`http`或`https`協議，具體支持的協議類型視軟件源自身而定，
通常主流的牆國軟件源如USTC（中科大源）、TUNA（清華源）等均支持兩種協議，
使用https可以避免牆國運營商的的緩存劫持，但需要安裝`apt-transport-https`軟件包。

`Ubuntu`與`Debian`的版本號、倉庫類型分類完全不同。

### Debian源
`Debian`版本號有兩類：

1. 固定版本號，按照穩定程度分爲`stable`、`testing`、`unstable`、`experimental`。
1. 版本代號。

兩類作用相同，固定版本號會指向某個版本代號；
隨着開發進度的變化，固定版本號實際指向的版本代號會發生變化：

- 當前（`2017-5-11`）Debian的最新穩定版爲`Debian 8`，版本代號爲`jessie`，
則使用固定版本號`stable`指向的實際版本號即爲`jessie`。
- 當前處於開發狀態的版本爲`Debian 9`，版本代號爲`stretch`，
使用固定版本號`testing`則實際指向處於開發狀態的版本代號`stretch`。

當固定版本號指向的實際版本發生變化時，更新軟件源時會給出相應提示：

```
# apt update
...
E: Repository 'https://deb.debian.org/debian testing InRelease' changed its 'Codename' value from 'bookworm' to 'trixie'
N: This must be accepted explicitly before updates for this repository can be applied. See apt-secure(8) manpage for details.
Do you want to accept these changes and continue updating from this repository? [y/N]
...
```

版本代號後是**版本倉庫**，Debian的版本倉庫有：

- `版本號-updates` 提供常規更新
- `版本號-backports` 將testing源的部分更新下放到stable版本中
- `版本號-security` 提供安全更新
- `版本號-proposed-updates` 提供處於測試階段的更新（不建議啓用）

版本倉庫後需要指定啓用的倉庫類型，Debian倉庫類型主要有三類：

- `main` 主要倉庫，符合`DFSG`定義的開源軟件
- `contrib` 包含依賴於非自由軟件的開源軟件
- `non-free` 非自由軟件
- `non-free-firmware` 非自由固件（`Debian 12 bookworm`版本開始引入，之前版本非自由固件亦在non-free倉庫中）

以**中科大鏡像源**爲例，`Debian Stable`的`sources.list`配置：

```sh
deb https://mirrors.ustc.edu.cn/debian/ stable main contrib non-free
deb https://mirrors.ustc.edu.cn/debian/ stable-updates main contrib non-free
deb https://mirrors.ustc.edu.cn/debian/ stable-backports main contrib non-free
deb https://mirrors.ustc.edu.cn/debian-security/ stable-security main non-free contrib
```

### Ubuntu源
`Ubuntu`沒有固定版本號，需要使用發行版本號，主要的`LTS`版本的版本代號：

| 版本 | 版本代號 |
| :-: | :-: |
| `12.04 LTS` | `precise` |
| `14.04 LTS` | `trusty` |
| `16.04 LTS` | `xenial` |

Ubuntu**版本倉庫**：

- `版本號-updates` 提供建議的更新
- `版本號-backports` 提供功能性更新
- `版本號-security` 提供重要的安全性更新（漏洞修復）
- `版本號-proposed` 提供處於測試階段的`updates`更新（不建議啓用）

Ubuntu**倉庫類別**：

- `main` 主要倉庫，完全的開源軟件
- `restricted` 不完全的開源軟件
- `universe` 社區支持、維護的軟件
- `muitiverse` 非開源軟件
- `partner` 閉源商業軟件，該倉庫僅有官方源可用

以**中科大鏡像源**爲例，`Ubuntu 16.04 LTS`的`sources.list`配置：

```sh
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial main restricted universe muitiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-security main restricted universe muitiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-updates main restricted universe muitiverse
deb https://mirrors.ustc.edu.cn/ubuntu/ xenial-backports main restricted universe muitiverse

deb http://archive.canonical.com/ubuntu/ xenial partner
```

快速將官方源替換為USTC源：

```
# sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list
```

## backports倉庫與倉庫優先級
`backports`倉庫是Debian係發行中重要的一類倉庫，
該倉庫中包含內核、固件等軟件包的下一個release的測試版本，
對`Debian Stable`/`Ubuntu LTS`系列的穩定發行版而言尤為重要，
可在不改版發行版大版本的前提下，更新內核等指定軟件包到較新的大版本。

以`Debian 11 bullseye`為例，默認內核為`5.10`，
Stable發行版在整個維護週期中，內核均不會改變版本號，
若需要更新內核，則可啟用backports倉庫，指定安裝backports內核：

```
# apt install linux-image-rt-amd64/bullseye-backports
```

`Debian 11 bullseye`的backports內核實際是下一個release（Debian 12 book）中的內核版本，為`6.1`版本。

可使用`apt-cache madison`或`apt policy`查看一個軟件包在多個倉庫中的版本，以內核為例：

```
$ apt-cache madison linux-image-rt-amd64
linux-image-rt-amd64 | 6.1.15-1~bpo11+1 | http://mirrors.ustc.edu.cn/debian bullseye-backports/main amd64 Packages
linux-image-rt-amd64 | 5.10.162-1 | http://mirrors.ustc.edu.cn/debian-security bullseye-security/main amd64 Packages
linux-image-rt-amd64 | 5.10.158-2 | http://mirrors.ustc.edu.cn/debian bullseye/main amd64 Packages

$ apt policy linux-image-rt-amd64
linux-image-rt-amd64:
  Installed: 6.1.15-1~bpo11+1
  Candidate: 6.1.15-1~bpo11+1
  Version table:
 *** 6.1.15-1~bpo11+1 100
        100 http://mirrors.ustc.edu.cn/debian bullseye-backports/main amd64 Packages
        100 /var/lib/dpkg/status
     5.10.162-1 500
        500 http://mirrors.ustc.edu.cn/debian-security bullseye-security/main amd64 Packages
     5.10.158-2 500
        500 http://mirrors.ustc.edu.cn/debian bullseye/main amd64 Packages
```

從apt policy中的輸出可知，bullseye、bullseye-security、bullseye-backports均包含內核包，
bullseye、bullseye-security倉庫中的優先級為500，bullseye-backports倉庫優先級為100，
因此bullseye-backports倉庫中的軟件包默認不會被選中，除非指令倉庫名稱進行安裝：

```
# apt install 軟件包名/版本代號-backports
```

## apt-mirror
`apt-mirror`是Debian系列發行版中用於製作**本地源**的工具。

### apt-mirror本地源配置
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

### 使用apt-mirror本地源
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
支持詞彙級別的轉換、異體字轉換和地區習慣用詞轉換（支那、臺灣、香港、日本新字體）。

項目託管在[GitHub](https://github.com/BYVoid/OpenCC)上。

## 命令行工具opencc
OpenCC提供的命令行工具`opencc`在各大平台的倉庫中均以內置，可使用對應包管理器直接安裝：

```html
# pacman -S opencc <!-- Arch Linux -->
$ brew install opencc <!-- macOS Homebrew -->
```

簡單的指令用法：

```
$ opencc -i 輸入文本文件 -o 輸出文本文件
```

默認的轉換策略是將殘體字轉換為正體字。
通過`-c`參數可設定轉換文本使用的配置：

```
$ opencc -i 輸入文本文件 -o 輸出文本文件 -c 配置json
```

文本轉換配置為json文件，OpenCC提供了常見的轉換配置：

| 配置名稱 | 源語言 | 目標語言 | 說明 |
| :- | :- | :- | :- |
| `s2t.json` | Simplified Chinese | Traditional Chinese | 殘體到正體 |
| `t2s.json` | Traditional Chinese | Simplified Chinese | 正體到殘體 |
| `s2tw.json` | Simplified Chinese | Traditional Chinese (Taiwan Standard) | 殘體到臺灣正體 |
| `tw2s.json` | Traditional Chinese (Taiwan Standard) | Simplified Chinese | 臺灣正體到殘體 |
| `s2hk.json` | Simplified Chinese | Traditional Chinese (Hong Kong variant) | 殘體到香港繁體 |
| `hk2s.json` | Traditional Chinese (Hong Kong variant) | Simplified Chinese | 香港繁體到殘體 |
| `s2twp.json` | Simplified Chinese | Traditional Chinese (Taiwan Standard) with Taiwanese idiom | 殘體到臺灣正體並轉換爲臺灣常用詞彙 |
| `tw2sp.json` | Traditional Chinese (Taiwan Standard) | Simplified Chinese with Mainland Chinese idiom | 臺灣正體到殘體並轉換爲支語常用詞彙 |
| `t2tw.json` | Traditional Chinese (OpenCC Standard) | Taiwan Standard | 正體（OpenCC 標準）到臺灣正體 |
| `hk2t.json` | Traditional Chinese (Hong Kong variant) | Traditional Chinese | 香港繁體到正體（OpenCC 標準） |
| `t2hk.json` | Traditional Chinese (OpenCC Standard) | Hong Kong variant | 正體（OpenCC 標準）到香港繁體 |
| `t2jp.json` | Traditional Chinese Characters (Kyūjitai) | New Japanese Kanji (Shinjitai) | 正體（OpenCC 標準，舊字體）到日本語新字體 |
| `jp2t.json` | New Japanese Kanji (Shinjitai) | Traditional Chinese Characters (Kyūjitai) | 日本語新字體到正體（OpenCC 標準，舊字體） |
| `tw2t.json` | Traditional Chinese (Taiwan standard) | Traditional Chinese | 臺灣正體到正體（OpenCC 標準） |



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
從[鏡像下載頁](https://cros.tech/device)下載最新的通用Chrome OS鏡像，
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

### iptables/firewalld
CentOS是默認啟用網絡防火牆的發行版：

- `CentOS 6` iptables
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

```
$ sestatus
SELinux status:                 disabled
```

臨時開啟/關閉SELinux可使用`setenforce`指令：

```html
# setenforce 0 <!-- 關閉SELinux -->
# setenforce 1 <!-- 開啟SELinux -->
```

永久禁用SELinux可編輯`/etc/selinux/config`文件，將`SELINUX=enforcing`修改為`SELINUX=disabled`。

### grub2-install: error: /usr/lib/grub/x86_64-efi/modinfo.sh doesn't exist. Please specify --target or --directory.
問題描述：<br>
在CentOS 7、UEFI引導下，使用`grub-install`指令安裝grub引導器時出現錯誤。

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
在雲平台上，應使用為雲平台設計的專屬鏡像，
參考[OpenStack文檔](https://docs.openstack.org/image-guide/obtain-images.html)，
從`http://cloud.centos.org/centos/7/images/`下載對應的CentOS 7的qcow2鏡像即可。
