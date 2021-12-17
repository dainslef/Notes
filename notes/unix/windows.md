<!-- TOC -->

- [Windows CMD](#windows-cmd)
- [文件/目錄鏈接](#文件目錄鏈接)
- [系統引導](#系統引導)
- [常見問題記錄](#常見問題記錄)
	- [Reply from ::1: time<1ms](#reply-from-1-time1ms)

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



# 文件/目錄鏈接
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



# 系統引導
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
