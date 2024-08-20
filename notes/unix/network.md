<!-- TOC -->

- [VLAN](#vlan)
    - [VLAN接口類型](#vlan接口類型)
- [Huawei](#huawei)
    - [interface（接口）](#interface接口)
    - [port-group（端口組）](#port-group端口組)
    - [description（備註信息）](#description備註信息)
    - [vlan（VLAN配置）](#vlanvlan配置)
        - [VLAN配置access接口](#vlan配置access接口)
        - [VLAN配置trunk接口](#vlan配置trunk接口)
    - [VLANIF配置](#vlanif配置)
        - [VLANIF設置192.168.1.1地址失敗](#vlanif設置19216811地址失敗)
- [ZTE](#zte)
    - [interface（接口配置）](#interface接口配置)
    - [switchvlan-configuration（VLAN配置）](#switchvlan-configurationvlan配置)

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

<Huawei> display this <!-- 查看當前視圖的配置 -->
<Huawei> display current-configuration <!-- 查看當前配置 -->
```

## interface（接口）
接口是交換機基本操作。

```html
<!-- 查看接口 -->
<Huawei> display interface
<Huawei> display interface brief <!-- 查看接口信息概覽 -->

<!-- 進入特定接口視圖 -->
[Huawei] interface GigabitEthernet x/x/x
[Huawei] interface XGigabitEthernet x/x/x <!-- 光纖接口 -->
```

使用interface指令進入接口視圖後，可禁用/啟用接口：

```html
<!-- 進入特定接口視圖 -->
[Huawei] interface GigabitEthernet x/x/x
<!-- 禁用接口 -->
[Huawei-GigabitEthernetx/x/x] shutdown
<!-- 解除接口禁用 -->
[Huawei-GigabitEthernetx/x/x] undo shutdown
```

## port-group（端口組）
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

注意，添加VLAN配置前首先需要**創建**對應VLAN，否則配置**不會**真正生效；
若對應VLAN未創建，使用`display port vlan`雖然能夠看到VLAN配置，
但使用`display port vlan active`則不會展示該VLAN。

### VLAN配置access接口
將接口配置為access，並設置VLAN：

1. 執行命令`interface 接口類型 接口編號`，進入需要加入VLAN的以太網接口視圖。
1. 執行命令`port link-type access`，配置接口類型為access。
1. 執行命令`port default vlan VLAN編號`，配置接口的缺省VLAN並將接口加入到指定VLAN。

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

1. 執行命令`interface 接口類型 接口編號`，進入需要加入VLAN的以太網接口視圖。
1. 執行命令`port link-type trunk`，配置接口類型為trunk。
1. 執行命令`port trunk allow-pass vlan { { vlan-id1 [ to vlan-id2 ] } &<1-10> | all }`，將接口加入到指定的VLAN中。
1. 執行命令`port trunk pvid vlan VLAN編號`，配置Trunk接口的缺省VLAN（可選）。

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

## VLANIF配置
VLANIF是一種三層虛擬接口（SVI，Switch Virtual Interface），用於不同VLAN網段之間的互通，
VLANIF的配置參考華爲[官方文檔](https://support.huawei.com/enterprise/en/doc/EDOC1000178172/433bc017/configuring-a-vlanif-interface)。

查看交換機當前的vlanif配置：

```
<HUAWEI> display interface vlanif
```

在VLAN中創建VLANIF接口，並配置IP地址：

```
[HUAWEI] interface vlanif 10
[HUAWEI-Vlanif10] ip address 10.1.1.1 24
[HUAWEI-Vlanif10] quit
[HUAWEI] interface vlanif 20
[HUAWEI-Vlanif20] ip address 10.10.10.1 24
[HUAWEI-Vlanif20] quit
```

刪除VLANIF接口使用undo操作：

```
[HUAWEI] undo interface vlanif 10
```

### VLANIF設置192.168.1.1地址失敗
設置VLANIF時，可能會出現地址衝突信息：

```
[App_E_Switch_01-Vlanif14]ip address 192.168.1.1 24
Error: The specified address conflicts with another address.
```

此時可通過查看arp信息排查指定網段/地址是否存在佔用：

```
[App_E_Switch_01-Vlanif14]display arp
IP ADDRESS      MAC ADDRESS     EXPIRE(M) TYPE INTERFACE      VPN-INSTANCE
                                          VLAN
------------------------------------------------------------------------------
192.168.1.253   d446-494b-13a0            I -  MEth0/0/1
172.16.0.1      d446-494b-13ae            I -  Vlanif13
172.16.0.10     fa16-3ed5-95ac  9         D-0  GE0/0/10
                                          13
172.16.0.16     fa16-3e4d-310b  16        D-0  GE0/0/10
                                          13
172.16.0.9      fa16-3e77-1e30  14        D-0  GE0/0/10
                                          13
172.16.0.11     fa16-3e90-8718  12        D-0  GE0/0/10
                                          13
172.16.0.17     fa16-3ef7-0b67  14        D-0  GE0/0/10
                                          13
172.16.0.62     3429-8f90-3267  13        D-0  GE1/0/24
                                          13
172.16.0.19     fa16-3e42-c187  3         D-0  GE0/0/10
                                          13
192.168.100.1   d446-494b-13ab            I -  Vlanif10
192.168.100.64  00e0-4c36-0284  12        D-0  GE0/0/5
                                          10
------------------------------------------------------------------------------
Total:11        Dynamic:8       Static:0     Interface:3
```

可知Console管理口默認使用了`192.168.1.0`網段，導致VLANIF設置`192.168.1.1`失敗，
將`MEth0/0/1`設置為其它地址即可：

```
[App_E_Switch_01] interface MEth 0/0/1
[App_E_Switch_01-MEth0/0/1] display this
#
interface MEth0/0/1
 ip address 192.168.1.253 255.255.255.0
#
return
[App_E_Switch_01-MEth0/0/1] ip address 192.168.255.1 24
```



# ZTE
進入特權模式：

```
> enable
Password:
#
```

默認密碼`zxr10`，部分型號為`Zxr10_IPTN`。

在特權模式下可保存配置：

```
# write
```

進入配置模式：

```
# configure terminal
Enter configuration commands, one per line.  End with CTRL/Z.
(config)#
```

## interface（接口配置）
查看接口狀態：

```
(config)# show interface
```

## switchvlan-configuration（VLAN配置）
進入VLAN配置模式：

```
(config)# switchvlan-configuration
(config-swvlan)#
```

查看VLAN信息：

```html
(config-swvlan)# show this <!-- 查看完整vlan信息 -->
(config-swvlan)# show vlan
```

進入指定VLAN：

```html
(config-swvlan)# vlan 編號
(config-swvlan-sub-編號)# switchport pvid 接口編號起始-結束
<!-- 示例：
(config-swvlan-sub-132)# switchport pvid gei-0/1/1/11-12
將 gei-0/1/1/11-12 的接口設置 PVID 為 132
設置 PVID 時會默認將接口設置為 ACCESS 模式
-->
```

配置接口的訪問屬性需要先進入VLAN配置模式，之後進入VLAN接口配置模式：

```html
(config)# switchvlan-configuration
(config-swvlan)# interface <interface-name>
(config-swvlan-if-ifname)# switchport mode { access| hybrid | trunk }
<!-- 設置 VLAN ID，若 VLAN ID 不存在則創建 -->
(config-swvlan-if-ifname)# switchport access vlan <vlan_id>
(config-swvlan-if-ifname)# switchport trunk native vlan <vlan_id>
(config-swvlan-if-ifname)# switchport hybrid native vlan <vlan_id>
```
