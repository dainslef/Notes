<!-- TOC -->

- [Windows CMD](#windows-cmd)
	- [文件操作](#文件操作)
	- [服務管理](#服務管理)
	- [其它實用工具](#其它實用工具)
- [文件/目錄鏈接](#文件目錄鏈接)
- [系統引導](#系統引導)
- [電源管理](#電源管理)
	- [Modern Standby](#modern-standby)
- [Microsoft Office](#microsoft-office)
	- [Office Deployment Tool](#office-deployment-tool)
- [微軟輸入法](#微軟輸入法)
	- [自定義短語](#自定義短語)
	- [輸入法卡頓問題](#輸入法卡頓問題)
- [文件共享（SMB服務）](#文件共享smb服務)
	- [SMB命令行](#smb命令行)
	- [優化SMB服務性能](#優化smb服務性能)
- [常見問題記錄](#常見問題記錄)
	- [Reply from ::1: time<1ms](#reply-from-1-time1ms)
	- [Intel CPU機型會在C盤根目錄下創建空的Intel目錄](#intel-cpu機型會在c盤根目錄下創建空的intel目錄)
	- [非中文環境下中文非Unicode編碼程序亂碼](#非中文環境下中文非unicode編碼程序亂碼)

<!-- /TOC -->



# Windows CMD
Windows系統提供的命令行執行DOS系統工具指令。

指令通用操作：

```html
<!-- DOS指令參數使用正斜槓（/）標識參數 -->
> 指令 /參數

<!-- DOS指令的幫助參數，類似於Unix下的 -h 或 --help -->
> 指令 /?
```

## 文件操作
常用的文件操作相關指令。

```html
<!-- 查看目錄 -->
> dir
<!-- 新建目錄 -->
> md
<!-- 刪除目錄（空目錄）-->
> rd

<!-- 複製文件 -->
> copy
<!-- 刪除文件 -->
> del
<!-- 查看文件 -->
> type

<!-- 展示目錄樹 -->
> tree
<!-- 移除目錄樹 -->
> deltree
```

## 服務管理
Windows在控制面板中提供了直觀的GUI服務管理，但亦可通過指令管理服務。

```html
<!-- 啓動相關配置 -->
> msconfig

<!-- 啓動服務管理面板 -->
> services.msc
```

`net`是DOS時代遺留產物，用於提供基本的服務管理功能。

```html
<!-- 啓動/停止服務 -->
> net start 服務名稱
> net stop 服務名稱
```

`sc`是微軟在Windows使用NT內核後引入的服務管理工具。

```html
<!-- 創建/刪除服務 -->
> sc create 服務名稱 binPath=服務啓動指令
> sc delete 服務名稱

<!-- 啟動/停止服務 -->
> sc start 服務名稱
> sc stop 服務名稱

<!-- 查詢服務 -->
> sc query <!-- 查詢指定服務 -->
> sc query 服務名稱 <!-- 查詢所有服務 -->
> sc qc 服務名稱 <!-- 查詢服務配置信息 -->
```

就實現機制而言，net指令為**同步**執行，指令會阻塞直到服務完全啟動；
而sc指令為**異步**執行，指令不會等待服務指令執行完畢。
net和sc的詳細區別參考[StackExchange](https://superuser.com/questions/315166/net-start-service-and-sc-start-what-is-the-difference)上的相關討論。

## 其它實用工具
常用工具：

```html
<!-- 查看系統進程列表 -->
> tasklist

<!-- Windows遠程桌面工具 -->
> mstsc

<!-- 顯示主機名和用戶名 -->
> whoami

<!-- 查看內存信息 -->
> wmic memorychip

<!-- DirectX診斷工具，可查看系統信息，顯卡對DirectX的支持情況 -->
> dxdiag
```

網絡基礎：

```html
<!-- 查看網絡信息 -->
> ipconfig
<!-- 查詢完整的網絡信息 -->
> ipconfig /all
<!-- 查看路由信息 -->
> route print
<!-- 追蹤路由 -->
> tracert 地址/主機名
```

語言包管理：

```html
> lpksetup

<!-- 刪除語言包 -->
> lpksetup /u
```



# 文件/目錄鏈接
Windows文件管理器提供的快捷方式(`Shortcut`)並不是對應用程序透明的，
應用程序在使用快捷方式路徑時並不等價於使用目標文件路徑。
在Vista之後，Windows提供了`mklink`工具，mklink類似Unix下的`ln`工具，
可創建對應用程序完全透明的硬鏈接(`hard link`)/符號鏈接(`symbolic link`)。

創建到目標地址的軟連接文件：

```html
> mklink 文件名 鏈接目標地址
```

mklink指令默認創建軟連接文件，使用`/d`參數創建軟連接**目錄**：

```html
> mklink /d 目錄名 鏈接目標目錄
```

使用`/h`參數可創建硬鏈接代替軟連接，硬鏈接需要鏈接文件於目標文件在相同盤符下：

```html
> mklink /h 文件名 鏈接目標文件
```



# 系統引導
標準的UEFI引導Windows系統通常包括以下分區：

- ESR (EFI system partition，通常為FAT文件系統)
- MSR (Microsoft Reserved Partition，通常為NTFS文件系統)
- Windows系統分區

其中，ESP分區存放引導器，Windows引導器路徑為`\EFI\MICROSOFT\BOOT\`；
MSR分區可以不分配，但每次重裝系統或Windows大版本更新都會重新自動創建。

BCDBoot是微軟官方提供的引導配置工具，主要有以下功能：

- 在新安裝的Windows鏡像后添加啓動文件
- 為電腦設置從包含Windows鏡像的虛擬硬盤（virtual hard disk，VHD）中啓動
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
若不確定當前系統分區的盤符，可使用`diskpart`指令進行查看：

```html
> diskpart
DISKPART > list volume <!-- 列出分區結構 -->
```

其它常用的diskpart操作：

```html
DISKPART > select volume 分區索引 <!-- 選定當前操作分區 -->
DISKPART > assign letter=字母 <!-- 給指定分區分配磁盤盤符 -->
```



# 電源管理
Windows使用`powercfg`指令管理電源計劃（電源策略），
指令使用説明參考[MSDN](https://learn.microsoft.com/en-us/windows-hardware/design/device-experiences/powercfg-command-line-options#option_list)。

常用操作：

```html
<!-- 列出所有電源計劃 -->
> powercfg /l

<!-- 查看所有電源計劃配置 -->
> powercfg /q
> powercfg /q 電源計劃GUID <!-- 查看指定電源計劃配置 -->
```

若系統已設置Sleep時間為Never，但系統依舊進入睡眠，
則可能是因爲`Hibernate`并未禁用，檢查睡眠相關配置：

```html
<!-- 查看睡眠狀態 -->
> powercfg /a

<!-- 禁用Hibernate -->
> powercfg /h off
```

若系統已開啓休眠，則輸出中會包含下列内容：

```html
> powercfg /a
The following sleep states are available on this system:
    Standby (S0 Low Power Idle) Network Connected
    Hibernate <!-- 當前睡眠狀態中包含 Hibernate -->
...
```

成功禁用Hibernate后，查看睡眠狀態會出現下列輸出：

```html
> powercfg /a
The following sleep states are available on this system: <!-- 當前睡眠狀態中不再包含 Hibernate -->
    Standby (S0 Low Power Idle) Network Connected
...

    Hibernate
        Hibernation has not been enabled.

    Hybrid Sleep
        Standby (S3) is not available.
        Hibernation is not available. <!-- 提示 Hibernate 未被啓用 -->
        The hypervisor does not support this standby state.
...
```

## Modern Standby
[`Modern Standby`](https://learn.microsoft.com/en-us/windows-hardware/design/device-experiences/modern-standby)
是Windows 10開始引入的新休眠機制，與傳統S3對比參見
[`Modern Standby vs S3`](https://learn.microsoft.com/en-us/windows-hardware/design/device-experiences/modern-standby-vs-s3)。

啓用Modern Standby可能會導致系統在空閑時關閉網絡（即使睡眠時間設置為Never），
導致部分需要網絡的服務無法正常運行（如SMB文件共享）；
禁用Modern Standby，恢復傳統的S3模式則不會出現此類問題。

禁用與啓用Modern Standby使用指令（需要重啓生效）：

```html
<!-- 禁用 Modern Standby -->
> reg add HKLM\System\CurrentControlSet\Control\Power /v PlatformAoAcOverride /t REG_DWORD /d 0
<!-- 啓用 Modern Standby -->
> reg delete HKLM\System\CurrentControlSet\Control\Power /v PlatformAoAcOverride /f
```

對應睡眠狀態輸出：

```html
<!-- 啓用 Modern Standby -->
> powercfg /a
The following sleep states are available on this system:
    Standby (S0 Low Power Idle) Network Connected

<!-- 禁用 Modern Standby -->
> powercfg /a
The following sleep states are available on this system:
    Standby (S3)
```



# Microsoft Office
對於沒有訂閲Office 365的用戶，推薦安裝Office離綫部署版本。
從Microsoft Download Center下載[`Office Deployment Tool`](https://www.microsoft.com/en-us/download/confirmation.aspx?id=49117)。

相關介紹可參考[微軟官方幫助頁面](https://support.microsoft.com/en-us/office/use-the-office-offline-installer-f0a85fe7-118f-41cb-a791-d59cef96ad1c#OfficePlans=signinorgid)，
Plan應選擇`Office for business`。

## Office Deployment Tool
部署工具下載完成后，執行安裝會解壓得到下列文件：

```
> ls
Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----         2/28/2022   1:12 AM           1164 configuration-Office2019Enterprise.xml
-a----         2/28/2022   1:12 AM           1368 configuration-Office2021Enterprise.xml
-a----         2/28/2022   1:12 AM           1014 configuration-Office365-x64.xml
-a----         2/28/2022   1:12 AM           1014 configuration-Office365-x86.xml
-a----         2/28/2022   1:12 AM        8158008 setup.exe
```

其中，`setup.exe`為安裝器，`configuration-*.xml`為各個版本的Office下載配置。
以`Office2021Enterprise`爲例，下載Office離綫安裝包：

```
> setup.exe /download configuration-Office2021Enterprise.xml
```

下載完成后，會在對應路徑下生成Office子路徑，即爲離綫安裝所需資源，執行安裝操作：

```
> setup.exe /configure .\configuration-Office2021Enterprise.xml
```



# 微軟輸入法
微軟輸入法使用`Shift`切換中英文輸入。

微軟輸入法提供了兩種特殊模式：

- `v`模式，輸入v鍵后可進行時間、日期等常用輸入到漢字的轉換
- `u`模式，輸入u鍵后可追加各類按鍵進行特殊標點（`uubd`）、特殊符號（`uuts`）等輸入。

## 自定義短語
微軟輸入法中并未直接提供**直角引號**的輸入方式，可通過添加自定義短語的方式添加快捷輸入，
進入菜單：

```
Settings > Language & region > Microsoft Pinyin > Lexicon and self-learning > User defined phrases
```

在其中添加自定義短語快捷輸入方式。

## 輸入法卡頓問題
Windows 11内置的微軟拼音可能會出現跨語言輸入法切換卡頓的問題，
從其它語言切換到微軟拼音后，輸入前幾個字符輸入提示框不會立即出現，而需要等待數秒。

解決方案是清空個人輸入法配置，讓系統重新生成配置，刪除如下路徑中的内容：

```
C:\Users\用戶名​​\AppData\Roaming\Microsoft\InputMethod\Chs
```



# 文件共享（SMB服務）
Windows系統内置了文件共享功能（基於SMB協議），在文件管理器的右鍵菜單中選擇：

```
Properties > Sharing > Share...
```

完整的共享管理可通過`Computer Managenment`功能管理：

```
> WinMgmt.exe
```

相關選項説明：

```html
<!-- 配置和管理的共享路徑 -->
Computer Management > System Tools > Shared Folders

<!-- 設置和管理授權用戶 -->
Computer Management > System Tools > Shared Folders > 選擇共享路徑（點擊右鍵） > Properties > Share Permissions

<!-- 管理Windows用戶，文件共享通過Windows的賬戶體系進行認證 -->
Computer Management > System Tools > Local Users and Groups
```

對於MicrosoftAccount（微軟帳戶），文件共享的認證信息為：

- 用戶：MicrosoftAccount\用戶名@郵箱後綴
- 密碼：MicrosoftAccount密碼

相關問題討論參考[StackExchange](https://superuser.com/questions/740375/how-to-login-to-network-share-when-microsoft-account-is-tied-to-windows-login)。

由於文件共享功能使用Windows帳戶體系，用於文件共享的用戶同樣會出現在登入介面中，
若需避免該用戶出現在登入介面中，可在用戶管理中將該用戶的用戶組設置中移除`Users`用戶組。

## SMB命令行
Windows的共享功能使用SMB協議實現，其它非Windows系統亦可通過SMB客戶端訪問，
可在PowerShell中查看SMB服務狀態與配置：

```html
<!-- 查看SMB服務配置 -->
> Get-SmbServerConfiguration

<!-- 查看SMB客戶端配置 -->
> Get-SmbClientConfiguration

<!-- 查看SMB連接 -->
> Get-SmbConnection
```

## 優化SMB服務性能
Windows默認的共享配置并未最大化傳輸速率，參考微軟官方文檔
[Slow SMB files transfer speed](https://learn.microsoft.com/en-us/windows-server/storage/file-server/troubleshoot/slow-file-transfer)
以及
[Performance tuning for SMB file servers](https://learn.microsoft.com/en-us/windows-server/administration/performance-tuning/role/file-server/smb-file-server)。

關閉SMB客戶端的一些性能限制：

```html
<!--
EnableBandwidthThrottling 0 關閉帶寬節流
EnableLargeMtu 1 使用大MTU
-->
> Set-SmbClientConfiguration -EnableBandwidthThrottling 0 -EnableLargeMtu 1
```

此外，若系統啓用了HyperV功能，且HyperV的虛擬交換機配置了橋接外部網絡，
則被橋接的網卡提供SMB服務時連接速率會**大大受限**，
應切換HyperV虛擬交換機的外部橋接網卡，或直接禁用外部網卡橋接。



# 常見問題記錄
記錄Windows中常見問題的解決方案。

## Reply from ::1: time<1ms
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

1. 在控制面版中禁用對應網卡的IPv6協議（`Control Panel\Network and Internet\Network Connections`）。
1. 參考[微軟官方文檔](https://support.microsoft.com/en-us/help/929852/guidance-for-configuring-ipv6-in-windows-for-advanced-users)，
	從注冊表中禁用或優先選擇IPv4網絡：

	```html
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

## Intel CPU機型會在C盤根目錄下創建空的Intel目錄
問題描述：<br>
Intel機型在每次重啓后均會在C盤根路徑下創建空的Intel目錄，
刪除該目錄后下次開機又會自動創建。

解決方案：<br>
經過排查，發現是`Intel(R) HD Graphics Control Panel`服務創建了該目錄，
在服務管理面板中禁用該服務即可阻止Intel目錄的自動創建。

## 非中文環境下中文非Unicode編碼程序亂碼
問題描述：<br>
對於不支持Unicode的早期Windows程序，在非中文的Windows環境下會出現亂碼。

解決方案：<br>
按下列順序找到菜單：

```
System >
Time & language >
Language & region >
Administrative language settings >
Language for non-Unicode program
```

設置`Current language for non-Unicode program`為`Chinese (Simplified)`。
