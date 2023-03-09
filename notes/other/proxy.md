<!-- TOC -->

- [Shadowsocks](#shadowsocks)
	- [shadowsocks-libev](#shadowsocks-libev)
- [Trojan](#trojan)
	- [安裝和管理Trojan服務](#安裝和管理trojan服務)
	- [FreeBSD編譯安裝Trojan](#freebsd編譯安裝trojan)
	- [配置Trojan服務](#配置trojan服務)
	- [生成RSA私有Key和CA](#生成rsa私有key和ca)
- [V2Ray](#v2ray)
	- [安裝和配置V2Ray服務](#安裝和配置v2ray服務)

<!-- /TOC -->



# Shadowsocks
[`Shadowsocks`](https://shadowsocks.org)是被設計用於突破Chinazi GFW的Tunnel Proxy(隧道代理)，
是目前最經典、使用率最高的翻牆方案。

Shadowsocks擁有多個實現，最初使用Python實現，之後原作者慘遭牆國國安喝茶；
現在Shadowsocks由社區維護，擁有C、Go、Rust等多種語言實現，
具體參見項目[GitHub](https://github.com/shadowsocks)。

## shadowsocks-libev
[shadowsocks-libev](https://github.com/shadowsocks/shadowsocks-libev)是目前功能最為齊全的實現，
軟件包已被各大主流發行版收錄。

```html
# apt install shadowsocks-libev <!-- 大便係 -->
# pacman -S shadowsocks-libev <!-- Arch係 -->
```

管理服務：

```html
# systemctl enable/disable trojan <!-- 開啟/關閉Trojan服務自啟動 -->
# systemctl start/stop trojan <!-- 啟動/停止Trojan服務 -->
```

正確安裝shadowsocks-libev後，編輯配置文件`/etc/shadowsocks-libev/config.json`，
簡單的服務端配置文件示例：

```json
{
    "server":["::1", "0.0.0.0"],
    "mode":"tcp_and_udp",
    "server_port":9999,
    "local_port":1080,
    "password":"custom_password",
    "timeout":60,
    "method":"chacha20-ietf-poly1305"
}
```

核心配置項說明：

| 配置項 | 說明 |
| :- | :- |
| server | 綁定地址，使用`0.0.0.0`則綁定本機ip |
| mode | 使用的傳輸層協議，`tcp_and_udp`為同時支持TCP和UDP |
| password | 客戶端連接時需要使用的密碼 |
| method | 使用的加密算法類型，推薦使用`chacha20-ietf-poly1305`/`aes-256-gcm` |
| server_port | 服務監聽端口 |
| local_port | 本地端口(配置服務可忽略該配置項) |



# Trojan
[`Trojan`](https://github.com/trojan-gfw/trojan)是用於繞過GFW的解決方案。
Trojan通過模擬互聯網中最常見的HTTPS流量，使得GFW難以偵測。

文檔參見官方[GitHub Pages](https://trojan-gfw.github.io/trojan)頁面。

## 安裝和管理Trojan服務
主流發行版均內置了Trojan軟件包，使用發行版默認的包管理即可直接安裝：

```html
# apt install trojan <!-- 大便係 -->
# pacman -S trojan <!-- Arch係 -->
```

管理服務：

```html
# systemctl enable/disable trojan <!-- 開啟/關閉Trojan服務自啟動 -->
# systemctl start/stop trojan <!-- 啟動/停止Trojan服務 -->
```

Trojan服務亦可通過docker創建容器部署，
[DockerHub](https://hub.docker.com/r/trojangfw/trojan)中提供了Trojan的官方鏡像，
創建並運行容器：

```
$ docker run -d -v /etc/trojan:/etc/trojan --network host --name trojan trojangfw/trojan:版本號
```

## FreeBSD編譯安裝Trojan
截止到FreeBSD當前版本（FreeBSD 13.1），Ports以及Pkg源中均未包含Trojan軟件包，因此需要手動編譯，
編譯部驟參考[官方Wiki](https://trojan-gfw.github.io/trojan/build)。

安裝依賴以及編譯工具：

```
# pkg install git cmake boost-libs
```

拉取源碼倉庫執行構建：

```html
$ git clone https://github.com/trojan-gfw/trojan.git
$ cd trojan
$ cmake -DENABLE_MYSQL=OFF <!-- 生成Makefile（關閉MySQL支持） -->
$ make <!-- 執行make操作 -->
# make install <!-- 執行安裝操作 -->
```

執行`make install`後，trojan執行文件會被安裝到`/usr/local/bin/trojan`，
設置服務自啟動可將其加入`/etc/rc.local`：

```sh
#! /bin/sh
/usr/local/bin/trojan &
```

## 配置Trojan服務
正確安裝Trojan後，編輯配置文件`/etc/trojan/config.json`，
Trojan服務的配置可參考[Trojan官方文檔](https://trojan-gfw.github.io/trojan/config.html)。

簡單的服務端配置示例：

```json
{
    "run_type": "server",
    "local_addr": "0.0.0.0",
    "local_port": 9998,
    "remote_addr": "127.0.0.1",
    "remote_port": 9999,
    "password": ["custom_password"],
    "log_level": 1,
    "ssl": {
        "cert": "/xxx/.../certificate.crt",
        "key": "/xxx/.../private_key",
        "alpn": ["h2","http/1.1"]
    },
    "tcp": {
        "prefer_ipv4": false,
        "no_delay": true,
        "keep_alive": true,
        "reuse_port": true,
        "fast_open": true,
        "fast_open_qlen": 20
    }
}
```

核心配置項說明：

| 配置項 | 說明 |
| :- | :- |
| run_type | 進程運行模式，使用`server`則作為Trojan服務執行 |
| local_addr | 綁定地址，使用`0.0.0.0`則綁定本機ip |
| local_port | 綁定端口 |
| remote_addr | 轉發HTTPS流量的目標地址（當客戶端發送的數據包為普通HTTPS數據包時，可配置轉發請求到指定地址） |
| remote_port | 轉發HTTPS流量的目標端口 |
| password | 客戶端連接時需要使用的密碼 |
| ssl.cert | 指定使用的證書 |
| ssl.key | 指定使用的私有key |

## 生成RSA私有Key和CA
以服務模式運行Trojan進程需要私有密鑰（private_key）和自簽名證書（certificate.crt），
相關文件可以使用openssl工具生成：

```html
<!-- 同時生成新的RSA私有key和證書 -->
$ openssl req -new -newkey rsa -x509 -sha256 -days [days] -nodes -out [certificate.crt] -keyout [private_key]
<!-- 使用已經存在的RSA私有key生成證書 -->
$ openssl req -new -x509 -nodes -key private_key -sha256 -days [days] -out [certificate.crt]
```

若需要認證指定域名，則可添加`-subj`參數設置認證內容：

```
$ openssl ... -subj "/C=JP/ST=Tokyo/L=Tokyo/O=Company/OU=Personal/CN=xxx.domain.xxx" ...
```

參數說明：

- `-newkey rsa` 創建私有RSA私有key，創建key時可指定key的長度`-newkey rsa:xxx`，
默認為`rsa:2048`(2048 bit)，數值越大越安全，但會增加解密開銷；可選範圍為`512/1024/2048/4096`等
- `-x509` 創建**自認證**(self-signed)的證書
- `-sha256` 使用265bit的SHA(Secure Hash Algorithm)算法生成私有key
- `-days` 設定證書有效日期
- `-nodes` 創建無需passphrase的證書

創建證書完成後，需要取消密鑰和證書的同組以及其它用戶的訪問權限：

```
$ chmod 600 private_key certificate.crt
```



# V2Ray
[V2Ray](https://github.com/v2ray/v2ray-core)
是支持多種協議的網絡平台，可實現單服務多協議同時工作以及高定制化的入站、出站流量規則。
相比Trojan，V2Ray性能稍差，但功能強大（較新版本的V2Ray亦支持Trojan協議）。

V2Ray官方頁面早期為[`v2ray.com`](https://www.v2ray.com)，
但原作者後續不再活躍，社區並無相關網站和倉庫的權限，
後續由社區維護了新的社區官方頁面[`v2fly.org`](https://www.v2fly.org/)；
官方提供的DockerHub帳號狀況類似，最初為[v2ray/official](https://hub.docker.com/r/v2ray/official)，
後續由變為社區維護的[v2fly/v2fly-core](https://hub.docker.com/r/v2fly/v2fly-core)。

## 安裝和配置V2Ray服務
V2Ray在各大發行版官方倉庫中均已包含，使用各大發行版的包管理器安裝即可：

```html
# apt install v2ray <!-- 大便係 -->
# pacman -S v2ray <!-- Arch係 -->
```

管理服務：

```html
# systemctl enable/disable v2ray <!-- 開啟/關閉V2Ray服務自啟動 -->
# systemctl start/stop v2ray <!-- 啟動/停止V2Ray服務 -->
```

[DockerHub](https://hub.docker.com/r/v2fly/v2fly-core)中提供了V2Ray的官方鏡像，
可直接創建容器使用：

```
$ docker run -d -v /etc/v2ray:/etc/v2ray --network host --name v2ray v2fly/v2fly-core:版本號
```

亦可基於Kubernetes部署：

```yaml
apiVersion: apps/v1
kind: DaemonSet
metadata:
  name: v2ray-daemon
  namespace: custom-components
  labels:
    app: v2ray
spec:
  selector:
    matchLabels:
      app: v2ray
  template:
    metadata:
      labels:
        app: v2ray
    spec:
      hostNetwork: true
      containers:
        - name: v2ray
          image: v2fly/v2fly-core:版本號
          volumeMounts:
            - mountPath: /etc/v2ray
              name: v2ray-config
      volumes:
        - name: v2ray-config
          hostPath:
            path: /etc/v2ray
            type: DirectoryOrCreate
```
