<!-- TOC -->

- [VLAN](#vlan)
	- [VLAN接口類型](#vlan接口類型)
- [Huawei](#huawei)
	- [端口組](#端口組)
	- [description（備註信息）](#description備註信息)
	- [vlan（VLAN配置）](#vlanvlan配置)
		- [VLAN配置access接口](#vlan配置access接口)
		- [VLAN配置trunk接口](#vlan配置trunk接口)

<!-- /TOC -->



# VLAN
VLAN用於劃分廣播域，隔離不同子網，避免交換機中出現廣播氾洪等問題。

交換機上的接口可指定VLAN類型和所屬VLAN，接口所屬VLAN稱為`PVID`（Port VLAN ID）。

## VLAN接口類型
VLAN接口可分為下列類型：

| VLAN類型 | 入口 | 出口 | 説明 |
| :- | :- | :- | :- |
| access | 接受無TAG數據，添加PVID作為TAG | TAG數據與PVID相同則去除TAG發出，否則丟棄 | 用於接入鏈路 |
| trunk | 接收無TAG數據添加PVID，接受有TAG數據判斷是否在允許列表中 | TAG數據與PVID相同則去除TAG發出，不同則直接轉發 | 用於幹道鏈路 |
| hybrid | 自行控制 | 自行控制 | 混合鏈路 |



# Huawei
進入/退出系統模式：

```
<Huawei> system-view
Enter system view, return user view with Ctrl+Z.
[Huawei]
[Huawei] quit
<Huawei>
```

在普通模式下可保存配置：

```
<Huawei> save
```

基本操作：

```html
[Huawei] undo xxx <!-- 某些指令對應的刪除操作 -->

<Huawei> display version <!-- 查看系統信息，包括開機時間等 -->
<Huawei> display ip routing-table <!-- 查看路由表 -->

<Huawei> display interface <!-- 查看接口 -->
<Huawei> display current-configuration <!-- 查看當前配置 -->

<!-- 進入特定接口視圖 -->
[Huawei] interface GigabitEthernet x/x/x
[Huawei] interface XGigabitEthernet x/x/x <!-- 光纖接口 -->
```

## 端口組
端口組用於將一組端口加入分組中，便於批量執行操作。

```
<HUAWEI> system-view
[HUAWEI] port-group 端口組名稱
[HUAWEI-port-group-端口組名稱] group-member GigabitEthernet x/x/start to GigabitEthernet x/x/end
```

進入端口組後，可進行批量操作，如配置VLAN等。

## description（備註信息）
在接口視圖中使用`description`指令為端口添加備註信息：

```
[Huawei] interface GigabitEthernet x/x/x
[Huawei-GigabitEthernetx/x/x] description xxx...
```

## vlan（VLAN配置）
華為交換機的VLAN配置可參考[官方文檔](https://support.huawei.com/enterprise/zh/doc/EDOC1100086528)。

查看VLAN信息：

```html
<Huawei> display vlan <!-- 查看VLAN信息 -->
<Huawei> display vlan summary <!-- 查看VLAN概況 -->
<Huawei> display port vlan <!-- 查看各個接口的VLAN類型和VLAN劃分 -->
<Huawei> display port vlan active <!-- 查看各個接口的當前使用的VLAN配置 -->
```

創建/刪除VLAN：

```html
[Huawei] vlan 100 <!-- 創建ID為100的VLAN -->
[Huawei-vlan100] quit
[Huawei] undo vlan 100 <!-- 刪除指定VLAN，需要退出VLAN配置視圖 -->
```

### VLAN配置access接口
將接口配置為access，並設置VLAN：

1. 執行命令`interface interface-type interface-number`，進入需要加入VLAN的以太網接口視圖。
1. 執行命令`port link-type access`，配置接口類型為access。
1. 執行命令`port default vlan vlan-id`，配置接口的缺省VLAN並將接口加入到指定VLAN。

```
[HUAWEI] interface gigabitethernet 1/0/1
[HUAWEI-GigabitEthernet1/0/1] port link-type access
[HUAWEI-GigabitEthernet1/0/1] port default vlan 100
[HUAWEI-GigabitEthernet1/0/1] quit
[HUAWEI] display port vlan gigabitethernet 1/0/1
Port                        Link Type    PVID  Trunk VLAN List
-------------------------------------------------------------------------------
GigabitEthernet1/0/1        access       100   -
```

### VLAN配置trunk接口
將接口配置為trunk，並允許特定VLAN：

1. 執行命令`interface interface-type interface-number`，進入需要加入VLAN的以太網接口視圖。
1. 執行命令`port link-type trunk`，配置接口類型為trunk。
1. 執行命令`port trunk allow-pass vlan { { vlan-id1 [ to vlan-id2 ] } &<1-10> | all }`，將接口加入到指定的VLAN中。
1. 執行命令`port trunk pvid vlan vlan-id`，配置Trunk接口的缺省VLAN（可選）。

> 當接口下通過的VLAN為接口的缺省VLAN時，該VLAN對應的報文將以Untagged方式進行轉發。
> 也就是說接口是以Untagged方式加入該VLAN的。

```
[HUAWEI] interface gigabitethernet 1/0/2
[HUAWEI-GigabitEthernet1/0/2] port link-type trunk
[HUAWEI-GigabitEthernet1/0/2] port trunk allow-pass vlan 100
[HUAWEI-GigabitEthernet1/0/2] quit
[HUAWEI] display port vlan gigabitethernet 1/0/2
Port                        Link Type    PVID  Trunk VLAN List
-------------------------------------------------------------------------------
GigabitEthernet1/0/2        trunk        1     1 100
```
