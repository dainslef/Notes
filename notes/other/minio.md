<!-- TOC -->

- [概述](#概述)
    - [安裝與配置](#安裝與配置)
    - [容器化部署](#容器化部署)
    - [性能測試](#性能測試)
- [mc（Minio Client）](#mcminio-client)
- [Erasure Code（糾刪碼）](#erasure-code糾刪碼)
    - [版本控制](#版本控制)

<!-- /TOC -->



# 概述
[MinIO](https://min.io/)是高性能的分佈式對象存儲服務，適用於雲原生應用程序和大數據工作負載。

MinIO具備下列特性：

- 可擴展性，支持從單節點到數千節點的擴展
- 可靠性，支持基於糾刪碼的數據冗余
- 易於部署
- 兼容Amazon S3 API

## 安裝與配置
通過二進制部署MinIO：

```html
$ wget https://dl.min.io/server/minio/release/linux-amd64/minio
$ chmod +x minio
<!-- 啟動MinIO服務，指定WEB端口（默認WEB端口隨即生成）、數據目錄路徑 -->
$ ./minio server --console-address :9001 數據目錄路徑

<!--
訪問MinIO：
API: http://localhost:9000
Console: http://localhost:9001
-->
```

## 容器化部署
[DockerHub](https://hub.docker.com/r/minio/minio)提供了MinIO的官方Docker鏡像，
可以通過以下命令運行MinIO容器：

```html
$ docker run -p 9000-9001:9000-9001 --name minio -v 宿主機數據目錄:/data minio/minio:版本tag minio server --console-address :9001 /data
```

MinIO默認提供兩類鏡像：

- `minio/minio:RELEASE.202X-XX-XXT00-00-00Z` 普通鏡像，需要現代CPU指令集支持（如SSE、AVX等）
- `minio/minio:RELEASE.202X-XX-XXT00-00-00Z-cpuv1` 不使用現代CPU指令集的鏡像，部分操作（如加解密、壓縮）效率較低，適用於老舊硬件或虛擬化環境

## 性能測試
MinIO使用[warp](https://github.com/minio/warp)工具進行性能測試：

```html
$ warp get --duration=測試時長 --warp-client=client-{1...X} --host=minio-server-{1...Y} --access-key=用戶名 --secret-key=密碼
$ warp put --duration=測試時長 --warp-client=client-{1...X} --host=minio-server-{1...Y} --access-key=用戶名 --secret-key=密碼
```



# mc（Minio Client）
[mc](https://docs.min.io/docs/minio-client-quickstart-guide.html)
是MinIO提供的客戶端管理工具，MinIO的官方鏡像中已內置了該工具。

```html
<!-- 為指定MinIO集群別名 -->
$ mc alias set 集群別名 http://localhost:9000 MinIO用戶 MinIO密碼

<!-- 創建/刪除桶 -->
$ mc mb 集群別名/桶名稱
$ mc rb 集群別名/桶名稱

<!-- 查看集群下的內容列表 -->
$ mc ls 集群別名
$ mc ls 集群別名/桶名稱

<!-- 上傳/下載/查看/刪除文件 -->
$ mc cp 本地文件 集群別名/桶名稱/文件
$ mc cp 集群別名/桶名稱/文件 本地文件
$ mc cat 集群別名/桶名稱/文件
$ mc rm 集群別名/桶名稱/文件
```



# Erasure Code（糾刪碼）
[Erasure Code](https://docs.min.io/enterprise/aistor-object-store/operations/core-concepts/erasure-coding/)
機制用於實現數據冗余和容錯能力。通過將數據分割成多個碎片並添加冗余碎片，
MinIO能夠在部分節點失效的情況下仍然保證數據的完整性和可用性。

```
$ minio server http://node{1...X}/data{1...Y} --console-address :9001
```

其中，`node{1...X}`表示MinIO集群中的節點數量，`data{1...Y}`表示每個節點上的數據目錄數量，
總盤數為`X * Y`，MinIO會根據總盤數自動配置合適的糾刪碼，
糾刪碼將數據分為N個數據塊和M個校驗塊，可容忍最多M個磁盤故障，確保數據的可靠存儲和高可用性：

常見集群規模與糾刪碼配置對應關係：

| 總磁盤數 | EC模式 | 存儲效率 | 容錯能力 |
| :- | :- | :- | :- |
| 3 | EC:1 | 67% | 1塊盤 |
| 4 | EC:2 | 50% | 2塊盤 |
| 6 | EC:2 | 67% | 2塊盤 |
| 8 | EC:4 | 50% | 4塊盤 |
| 12 | EC:4 | 67% | 4塊盤 |
| 16 | EC:6 | 62.5% | 6塊盤 |

查看當前集群使用的糾刪碼模式：

```html
$ mc admin info 集群別名
```

## 版本控制
MinIO支持對象版本控制，可以通過啟用版本控制來保護數據免受意外刪除或覆蓋。

```html
<!-- 啟用/暫停版本控制，默認版本控制未開啟 -->
$ mc version enable 集群別名/桶名稱
$ mc version suspend 集群別名/桶名稱

<!-- 查看版本狀態 -->
$ mc version info 集群別名/桶名稱

<!-- 列出對象的所有版本 -->
$ mc ls --versions 集群別名/桶名稱/對象路徑
$ mc cat --version-id 版本ID 集群別名/桶名稱/對象路徑
```

MinIO的版本控制一旦開啟就無法關閉，只能暫停。
