<!-- TOC -->

- [Redis安裝和維護](#redis安裝和維護)
	- [性能測試](#性能測試)
- [Redis通用功能](#redis通用功能)
	- [Replication（主從複製）](#replication主從複製)
- [Redis Keyspace Notifications](#redis-keyspace-notifications)
	- [Redis keyspace notifications 缺陷](#redis-keyspace-notifications-缺陷)
- [問題註記](#問題註記)
	- [WARNING you have Transparent Huge Pages (THP) support enabled in your kernel.](#warning-you-have-transparent-huge-pages-thp-support-enabled-in-your-kernel)

<!-- /TOC -->



# Redis安裝和維護
Redis在各大發行版倉庫中均已收錄，直接使用發行版內置的包管理器安裝即可：

```html
# pacman -S redis <!-- Arch係 -->
# apt install redis-server <!-- Debian係 -->
```

Redis官方提供了功能完善的GUI客戶端[Redis Insight](https://redis.com/redis-enterprise/redis-insight)，
Redis Insight使用Electron實現，源碼託管在[GitHub](https://github.com/RedisInsight/RedisInsight)上。

Linux多數發行版官方倉庫尚未收錄該軟件包，
macOS可直接通過Homebrew安裝：

```
$ brew install redisinsight
```

## 性能測試
Redis內置了性能測試工具`redis-benchmark`。

redis-benchmark多數參數與redis-cli類似，支持一些測試相關參數：

```html
$ redis-benchmark -t 測試類型 <!-- 測試指定類型，辱 ping,set,get 等 -->
$ redis-benchmark -n 請求數目 <!-- 測試的總請求數目 -->
```

實例：

```html
<!-- 測試 10000 請求下的查詢性能 -->
$ redis-benchmark -q
PING_INLINE: 71428.57 requests per second, p50=0.295 msec
PING_MBULK: 86206.90 requests per second, p50=0.287 msec
SET: 85470.09 requests per second, p50=0.287 msec
GET: 89285.71 requests per second, p50=0.295 msec
INCR: 90090.09 requests per second, p50=0.295 msec
LPUSH: 88495.58 requests per second, p50=0.311 msec
RPUSH: 81300.81 requests per second, p50=0.375 msec
LPOP: 81300.81 requests per second, p50=0.383 msec
RPOP: 84745.77 requests per second, p50=0.295 msec
SADD: 89285.71 requests per second, p50=0.287 msec
HSET: 88495.58 requests per second, p50=0.287 msec
SPOP: 86206.90 requests per second, p50=0.295 msec
ZADD: 90090.09 requests per second, p50=0.287 msec
ZPOPMIN: 93457.95 requests per second, p50=0.287 msec
LPUSH (needed to benchmark LRANGE): 52631.58 requests per second, p50=0.311 msec
LRANGE_100 (first 100 elements): 39525.69 requests per second, p50=0.623 msec
LRANGE_300 (first 300 elements): 19267.82 requests per second, p50=1.279 msec
LRANGE_500 (first 500 elements): 12642.22 requests per second, p50=1.895 msec
LRANGE_600 (first 600 elements): 11441.65 requests per second, p50=2.167 msec
MSET (10 keys): 86206.90 requests per second, p50=0.391 msec
```



# Redis通用功能
Redis與數據結構無關的通用功能。

- `HELP` 查看目標指令的幫助信息。
- `INFO` 查看服務狀態，默認輸出所有狀態信息參數可添加不同類別。
- `KEYS` 查找KEY，支持按照模式匹配出所有滿足條件的KEY。
- `TYPE` 查看指定Key的數據結構類型。
- `FLUSHALL` / `FLUSHDB` 清理所有數據。
FLUSHALL清理所有數據庫中的內容，FLUSHDB清理當前數據庫的內容。
- `EXPIRE` 設置KEY過期時間。
Redis中的數據默認永久生效，需要使用EXPIRE為數據設定過期時間。

## Replication（主從複製）
Redis通過`REPLICAOF`指令設置主從複製，在從節點執行該指令即可同步主節點的數據：

```html
<!-- 建立同步關係（進入同步模式） -->
> REPLICAOF 主節點地址 主節點端口

<!-- 解除同步關係（退出同步模式） -->
> REPLICAOF NO ONE
```

執行該指令後，若建立同步關係成功，作為從節點的當前節點舊數據會被清除替換為主節點的數據。
進入同步模式後，從節點會持續從主節點同步數據，在網絡中斷後也會自動重新開始同步。
在同步後，默認從節點會進入**只讀模式**（不可執行涉及數據寫入的指令），查看同步狀態信息：

```html
<!-- 主節點同步信息示例 -->
> INFO REPLICATION
# Replication
role:master <!-- 節點角色 -->
connected_slaves:xxx <!-- 連結的從節點數目 -->
slave0:ip=x.x.x.x,port=6379,state=online,offset=xxx,lag=x
master_replid:xxx
master_replid2:xxx
master_repl_offset:xxx
second_repl_offset:xxx
repl_backlog_active:x
repl_backlog_size:xxx
repl_backlog_first_byte_offset:xxx
repl_backlog_histlen:xxx

<!-- 從節點同步信息示例 -->
> INFO REPLICATION
# Replication
role:slave <!-- 節點角色 -->
master_host:x.x.x.x <!-- 主節點地址 -->
master_port:6379 <!-- 主節點端口 -->
master_link_status:up <!-- 主節點狀態 -->
master_last_io_seconds_ago:0 <!-- 最近同步時間 -->
master_sync_in_progress:0 <!-- 當前正在進行的同步操作數目 -->
slave_repl_offset:xxx
slave_priority:100
slave_read_only:1 <!-- 從節點是否只讀 -->
connected_slaves:0
master_replid:xxx
master_replid2:xxx
master_repl_offset:xxx
second_repl_offset:xxx
repl_backlog_active:x
repl_backlog_size:xxx
repl_backlog_first_byte_offset:xxx
repl_backlog_histlen:xxx
```

通過指令創建的主從同步關係在節點重啟後不會保存，
要使Redis服務在啟動時保持同步關係，需要在redis.conf中加入：

```
replicaof 主節點地址 主節點端口
```

配置項與命令行下的同步指令相同。



# Redis Keyspace Notifications
Redis提供了[Redis Keyspace Notifications](https://redis.io/docs/manual/keyspace-notifications/)
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
