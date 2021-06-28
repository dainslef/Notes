<!-- TOC -->

- [問題註記](#問題註記)
	- [WARNING you have Transparent Huge Pages (THP) support enabled in your kernel.](#warning-you-have-transparent-huge-pages-thp-support-enabled-in-your-kernel)

<!-- /TOC -->



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
