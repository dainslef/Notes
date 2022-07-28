<!-- TOC -->

- [Redis keyspace notifications](#redis-keyspace-notifications)
	- [Redis keyspace notifications 缺陷](#redis-keyspace-notifications-缺陷)
- [問題註記](#問題註記)
	- [WARNING you have Transparent Huge Pages (THP) support enabled in your kernel.](#warning-you-have-transparent-huge-pages-thp-support-enabled-in-your-kernel)

<!-- /TOC -->



# Redis keyspace notifications
Redis提供了[Redis keyspace notifications](https://redis.io/docs/manual/keyspace-notifications/)
機制會生成Redis中各類變更事件，如指令、創建、刪除、過期等，
開發者而通過監聽對應頻道消息實現特定業務邏輯。

keyspace notifications特性默認未開啟，即默認不會生成任何Key變更事件消息。
開啟需要修改redis.conf中的`notify-keyspace-events`配置項，
該配置項的可選取值如下：

```
K     Keyspace events, published with __keyspace@<db>__ prefix.
E     Keyevent events, published with __keyevent@<db>__ prefix.
g     Generic commands (non-type specific) like DEL, EXPIRE, RENAME, ...
$     String commands
l     List commands
s     Set commands
h     Hash commands
z     Sorted set commands
x     Expired events (events generated every time a key expires)
e     Evicted events (events generated when a key is evicted for maxmemory)
A     Alias for g$lshzxe, so that the "AKE" string means all the events.
```

其中`K`、`E`兩項指定事件產生的消息頻道：

- `K`： Key消息，消息結構為`__keyspace@<db>__:<key> <ooperation>`
- `E`： 操作消息，消息結構為`__keyspace@<db>__:<ooperation> <key>`

其它小寫字母配置項指定具體的監聽的事件類型，
監聽事件類型需要與K/E配置項搭配使用才生效，
僅設置監聽事件類型而不設置頻道則不會生成對應事件消息。

示例，生成Key過期事件的keyspace消息，配置項為：

```
notify-keyspace-events "Kx"
```

## Redis keyspace notifications 缺陷
Redis keyspace notifications實現機制是通過定時任務掃描並刪除過期Key，
因此可能存在通知消息延遲到達的情況，並且不保證消息一定送達，
當發送離線消息時客戶端不在線，則會錯過對應離線消息。



# 問題註記
記錄Redis使用過程中遇到的一些問題。

## WARNING you have Transparent Huge Pages (THP) support enabled in your kernel.
問題說明：<br>
Redis運行期間崩潰，運行期間出現以下警告：

```
WARNING you have Transparent Huge Pages (THP) support enabled in your kernel. This will create latency and memory usage issues with Redis. To fix this issue run the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled' as root, and add it to your /etc/rc.local in order to retain the setting after a reboot. Redis must be restarted after THP is disabled.
```

解決方案：<br>
Redis需要關閉或部分禁用Linux內核的[Transparent Hugepage Support (THP)](https://www.kernel.org/doc/html/latest/admin-guide/mm/transhuge.html)特性：

```html
<!-- 全部禁用THP特性 -->
# echo never > /sys/kernel/mm/transparent_hugepage/enabled
<!-- 可選的THP特性，不會強制對Redis啟用 -->
# echo madvise > /sys/kernel/mm/transparent_hugepage/enabled
```

THP是一種Linux的內存管理機制，
能在大內存的機器中減少查找`Translation Lookaside Buffer (TLB)`的開銷。
THP在部分場景下能夠有效地利用內存，對部分應用可起到加速作用，
但對於Redis、mongoDB等數據庫類型的程序，則不推薦使用THP，
因為數據庫通常更稀疏(sparse)而非連續(contiguous)地訪問內存，
使用THP甚至可能引發內存使用異常。

相關說明可參考[Redis官方文檔](https://redis.io/topics/latency)，
以及[StackOverflow](https://stackoverflow.com/questions/42591511/when-to-turn-off-transparent-huge-pages-for-redis)上的相關問答、
[mongoDB](https://docs.mongodb.com/manual/tutorial/transparent-huge-pages/)官方文檔。
