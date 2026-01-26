<!-- TOC -->

- [概述](#概述)
    - [安裝與配置](#安裝與配置)
    - [容器化部署](#容器化部署)
    - [性能測試](#性能測試)

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
