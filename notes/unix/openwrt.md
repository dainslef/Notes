<!-- TOC -->

- [mtd](#mtd)

<!-- /TOC -->



# mtd
`mtd`是路由器刷機使用的固件寫入工具。

路由器的分區信息寫在`/proc/mtd`文件中，不同機型不同固件會有不同的分區信息，示例：

```html
<!-- Mi Router 4C, Official Firmware  -->
$ cat /proc/mtd
dev:    size   erasesize  name
mtd0: 01000000 00010000 "ALL"
mtd1: 00020000 00010000 "Bootloader"
mtd2: 00010000 00010000 "Config"
mtd3: 00010000 00010000 "Factory"
mtd4: 00010000 00010000 "crash"
mtd5: 00010000 00010000 "cfg_bak"
mtd6: 00100000 00010000 "overlay"
mtd7: 00c60000 00010000 "OS1"
mtd8: 00b00000 00010000 "rootfs"
mtd9: 00200000 00010000 "disk"

<!-- Redmi Router AC2100, Official Firmware  -->
$ cat /proc/mtd
dev:    size   erasesize  name
mtd0: 07f80000 00020000 "ALL"
mtd1: 00080000 00020000 "Bootloader"
mtd2: 00040000 00020000 "Config"
mtd3: 00040000 00020000 "Bdata"
mtd4: 00040000 00020000 "Factory"
mtd5: 00040000 00020000 "crash"
mtd6: 00040000 00020000 "crash_syslog"
mtd7: 00040000 00020000 "cfg_bak"
mtd8: 00400000 00020000 "kernel0"
mtd9: 00400000 00020000 "kernel1"
mtd10: 01a00000 00020000 "rootfs0"
mtd11: 01a00000 00020000 "rootfs1"
mtd12: 02600000 00020000 "overlay"
mtd13: 01b80000 00020000 "obr"
mtd14: 00c1c000 0001f000 "ubi_rootfs"
mtd15: 021e8000 0001f000 "data"

<!-- Redmi Router AC2100, OpenWrt Firmware  -->
$ cat /proc/mtd
dev:    size   erasesize  name
mtd0: 00080000 00020000 "Bootloader"
mtd1: 00040000 00020000 "Config"
mtd2: 00040000 00020000 "Bdata"
mtd3: 00040000 00020000 "factory"
mtd4: 00040000 00020000 "crash"
mtd5: 00040000 00020000 "crash_syslog"
mtd6: 00040000 00020000 "reserved0"
mtd7: 00400000 00020000 "kernel_stock"
mtd8: 00400000 00020000 "kernel"
mtd9: 07580000 00020000 "ubi"
```

使用mtd將固件寫入目標分區：

```
# mtd -r write 固件路徑 分區名稱
```
