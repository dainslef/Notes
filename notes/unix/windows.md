<!-- TOC -->

- [Windows CMD](#windows-cmd)
	- [文件操作](#文件操作)
	- [服務管理](#服務管理)
	- [電源管理](#電源管理)
	- [其它實用工具](#其它實用工具)
- [文件/目錄鏈接](#文件目錄鏈接)
- [系統引導](#系統引導)
- [Microsoft Office](#microsoft-office)
	- [Office Deployment Tool](#office-deployment-tool)
- [常見問題記錄](#常見問題記錄)
	- [Reply from ::1: time<1ms](#reply-from-1-time1ms)
	- [Intel CPU機型會在C盤根目錄下創建空的Intel目錄](#intel-cpu機型會在c盤根目錄下創建空的intel目錄)

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

## 電源管理
常用的電源管理指令。

```html
> powercfg

<!-- 開啓休眠 -->
> powercfg /h on
<!-- 禁用休眠 -->
> powercfg /h off
```

## 其它實用工具

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
> .\setup.exe /configure .\configuration-Office2021Enterprise.xml
```



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
