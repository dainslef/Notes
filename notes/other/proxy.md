<!-- TOC -->

- [Shadowsocks](#shadowsocks)
	- [shadowsocks-libev](#shadowsocks-libev)
- [生成TLS證書以及密鑰](#生成tls證書以及密鑰)
- [Trojan](#trojan)
	- [Linux安裝和管理Trojan服務](#linux安裝和管理trojan服務)
	- [FreeBSD編譯安裝Trojan](#freebsd編譯安裝trojan)
	- [配置Trojan服務](#配置trojan服務)
	- [Trojan轉發流量](#trojan轉發流量)
- [V2Ray & XRay](#v2ray--xray)
	- [XRay](#xray)
	- [安裝和配置V2Ray/XRay服務](#安裝和配置v2rayxray服務)
	- [VMess + TLS + WebSocket](#vmess--tls--websocket)
	- [VMess + TLS + gRPC](#vmess--tls--grpc)
	- [V2Ray/XRay Trojan](#v2rayxray-trojan)
	- [V2Ray/XRay Shadowsocks](#v2rayxray-shadowsocks)

<!-- /TOC -->



# Shadowsocks
[`Shadowsocks`](https://shadowsocks.org)是被設計用於突破Chinazi GFW的Tunnel Proxy（隧道代理），
是目前最經典、使用率最高的翻牆方案。

Shadowsocks擁有多個實現，最初使用Python實現，之後原作者慘遭支那晶哥喝茶；
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
    "server": ["::1", "0.0.0.0"],
    "mode": "tcp_and_udp",
    "server_port": 9999,
    "local_port": 1080,
    "password": "custom_password",
    "timeout": 60,
    "method": "xchacha20-ietf-poly1305"
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

shadowsocks-libev的官方鏡像亦託管在
[DockerHub](https://hub.docker.com/r/shadowsocks/shadowsocks-libev)，
使用容器啟動服務：

```html
<!-- 容器默認不讀取配置文件，需要手動設置啟動指令（使用 -c 參數設置配置路徑） -->
$ docker run -d -v /etc/shadowsocks-libev:/etc/shadowsocks-libev --network host --name shadowsocks shadowsocks/shadowsocks-libev ss-server -c /etc/shadowsocks-libev/config.json
```



# 生成TLS證書以及密鑰
基於TLS加密的需要私有密鑰（tls.key）和自簽名證書（tls.crt），
V2Ray、Trojan等服務均需要使用。

相關文件可以使用openssl工具生成：

```html
<!-- 同時生成新的RSA私有key和證書 -->
$ openssl req -new -newkey rsa -x509 -sha256 -days 證書有效天數 -nodes -out tls.crt -keyout tls.key
<!-- 使用已經存在的RSA私有key生成證書 -->
$ openssl req -new -x509 -nodes -key tls.key -sha256 -days 證書有效天數 -out tls.crt
```

若需要認證指定域名，則可添加`-subj`參數設置認證內容：

```
$ openssl ... -subj "/C=JP/ST=Tokyo/L=Tokyo/O=Company/OU=Personal/CN=xxx.domain.xxx" ...
```

參數說明：

| 參數 | 說明 |
| :- | :- |
| `-newkey rsa` | 創建私有RSA私有key，創建key時可指定key的長度`-newkey rsa:xxx`，默認`rsa:2048`（2048 bit），數值越大越安全，但會增加解密開銷；可選範圍為`512/1024/2048/4096`等 |
| `-x509` | 創建**自認證**（self-signed）的證書 |
| `-sha256` | 使用265bit的SHA（Secure Hash Algorithm）算法生成私有key |
| `-days` | 設定證書有效日期 |
| `-nodes` | 創建無需passphrase的證書 |

創建證書完成後，需要取消密鑰和證書的同組以及其它用戶的訪問權限：

```
$ chmod 600 tls.key tls.crt
```



# Trojan
[`Trojan`](https://github.com/trojan-gfw/trojan)是用於繞過GFW的解決方案。
Trojan通過模擬互聯網中最常見的HTTPS流量，使得GFW難以偵測。

文檔參見官方[GitHub Pages](https://trojan-gfw.github.io/trojan)頁面。

## Linux安裝和管理Trojan服務
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
$ docker run -itd -v /etc/trojan:/etc/trojan --network host --name trojan trojangfw/trojan
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
  "password": [ "custom_password" ],
  "log_level": 1,
  "ssl": {
    "cert": ".../tls.crt",
    "key": ".../tls.key",
    "alpn": [ "h2", "http/1.1" ],
    "alpn_port_override": { "h2": 9997 }
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
| password | 客戶端連接時需要使用的密碼 |
| ssl.cert | 指定使用的證書 |
| ssl.key | 指定使用的私有key |

## Trojan轉發流量
Trojan支持將非標流量轉發到指定目標端口，可將其它流量交由Nginx之類的Web服務進行HTTP偽裝。

相關參數說明：

| 配置項 | 說明 |
| :- | :- |
| remote_addr | 轉發流量的目標地址（當客戶端發送的數據包為普通HTTPS數據包時，可配置轉發請求到指定地址） |
| remote_port | 轉發流量的目標端口 |
| alpn | Application-Layer Protocol Negotiation (ALPN)，應用層協議協商，用於區分HTTP/1.1和HTTP/2流量 |
| alpn_port_override | 指定HTTP2流量的轉發端口，默認所有非標流量均轉發到remote_port |

Trojan會丟棄普通HTTP流量，僅轉發HTTPS流量；
在轉發HTTPS流量時，Trojan轉發的是剝離TLS之後的內容，因此轉發的目標端口應為普通HTTP端口。

Trojan默認使用的apln為`[ "http/1.1" ]`，可設置為`[ "h2", "http/1.1" ]`以支持HTTP/2，
或者直接設置`[ "h2" ]`強制所有流量使用HTTP/2。

雖然HTTP/2默認被設計為與TLS一同工作，
但Trojan使用在alpn設置為h2時依舊轉發出的是非TLS加密的HTTP/2流量，
對應Nginx配置為：

```conf
server {
	listen xxx http2;
	...
}
```



# V2Ray & XRay
[V2Ray](https://github.com/v2fly/v2ray-core)
是支持多種協議的通用網絡平台，可實現單服務多協議同時工作以及高定制化的入站、出站流量規則，
使用V2Ray則無須再單獨安裝Shadowsocks、Trojan等軟件包。

V2Ray最初主要支持VMess協議，後續添加了多種協議支持，
例如較新版本完整支持了Trojan協議，並添加了原版Trojan不支持的WebSocket/gRPC傳輸層支持。

V2Ray支持多種傳輸協議與代理協議的組合，如：

- Shadowsocks + TCP/UDP
- VMess + TCP + TLS
- VMess + WebSocket + TLS
- VMess + gRPC + TLS
- Trojan + TCP + TLS
- Trojan + WebSocket + TLS
- Trojan + gRPC + TLS

V2Ray官方頁面早期為[`v2ray.com`](https://www.v2ray.com)，
但原作者後續不再活躍，社區並無相關網站和倉庫的權限，
後續由社區維護了新的社區官方頁面[`v2fly.org`](https://www.v2fly.org/)；
官方提供的DockerHub帳號狀況類似，最初為[v2ray/official](https://hub.docker.com/r/v2ray/official)，
後續由變為社區維護的[v2fly/v2fly-core](https://hub.docker.com/r/v2fly/v2fly-core)。

## XRay
[XRay](https://github.com/XTLS/Xray-core)是V2Ray項目的分支，
主要添加了VLESS協議以及XTLS相關的功能，
XTLS相關功能因為[許可證問題](https://github.com/XTLS/Go/issues/9)被從V2Ray主分支中移除，
後續單獨創建項目繼續開發，目前開發活躍，性能以及各類功能特性均超越原版V2Ray。

XRay除原版功能外，提供了更多的協議組合，如：

- VLESS + TCP + XTLS
- VLESS + gRPC + XTLS
- VLESS + TCP + REALITY

XTLS將流量內層TLS直接拼接到代理外部，使代理無需對HTTPS流量進行數據解密，性能更高，
參見[GitHub XTLS Release Tag](https://github.com/rprx/v2ray-vless/releases/tag/xtls)。

XTLS Vision特性解決了TLS in TLS的流量特徵問題，
參見[GitHub Issues](https://github.com/XTLS/Xray-core/discussions/1295)。

## 安裝和配置V2Ray/XRay服務
V2Ray在各大發行版官方倉庫中均已包含，使用各大發行版的包管理器安裝即可：

```html
<!-- 安裝V2Ray -->
# apt install v2ray <!-- 大便係 -->
# pacman -S v2ray <!-- Arch係 -->
# pkg install v2ray <!-- FreeBSD -->

<!-- 安裝XRay，因為許可證問題XRay未包含在Debian係倉庫中 -->
# pacman -S xray <!-- Arch係 -->
# pkg install xray-core <!-- FreeBSD -->
```

管理服務：

```html
# systemctl enable/disable v2ray/xray <!-- 開啟/關閉V2Ray/XRay服務自啟動 -->
# systemctl start/stop v2ray/xray <!-- 啟動/停止V2Ray服務 -->
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
  name: v2ray
  namespace: custom-apps
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
              name: v2ray
      volumes:
        - name: v2ray
          hostPath:
            path: /etc/v2ray
            type: DirectoryOrCreate
```

XRay在DockerHub沒有官方組織，但可使用[teddysun/xray](https://hub.docker.com/r/teddysun/xray)鏡像，
可直接創建容器使用：

```
$ docker run -d -v /etc/xray:/etc/xray --network host --name xray teddysun/xray:版本號
```

## VMess + TLS + WebSocket
V2Ray/Xray支持使用WebSocket作為傳輸協議，
該種傳輸方式可搭配CDN使用，以實現隱藏代理服務器真實IP的作用。

服務端配置：

```json
{
  "inbound": {
    "protocol": "vmess",
    "port": 443,
    "settings": { "clients": [ { "id": "xxx-xxx..." } ] },
    "streamSettings": {
      "network": "ws",
      "wsSettings": { "path": "/xxx" },
      "security": "tls",
      "tlsSettings": {
        "certificates": [ {
            "certificateFile": "/opt/tls/tls.crt",
            "keyFile": "/opt/tls/tls.key"
          } ]
      }
    }
  },
  "outbound": { "protocol": "freedom" }
}
```

若使用Nginx等反向代理做轉發TLS流量轉發，則可省略V2Ray自身的`tlsSettings`、`security`配置。

Clash客戶端配置：

```yaml
...
proxies:
  - name: xxx
    type: vmess
    server: xxx.xxx.domain
    port: 443
    uuid: xxx-xxx... # UUID需要與服務端保持一致
    alterId: 0 # V2Ray v4.28.1之後，alterId設置為0表示啟用VMessAEAD（服務端會自動適配）
    cipher: auto
    network: ws
    tls: true
    ws-opts:
      path: /xxx # 需要匹配服務端配置中的WebSocket路徑
  ...
```

VMess協議自身不帶有HTTP偽裝，因此通常前置一個Nginx做流量轉發和偽裝，
Nginx轉發配置：

```conf
server {
	listen xxxx ssl;
	ssl_certificate .../tls.crt;
	ssl_certificate_key .../tls.key;

	# Forward WebSocket to V2Ray.
	location = /xxx {
		proxy_set_header Upgrade $http_upgrade;
		proxy_set_header Connection "upgrade";
		proxy_set_header Host $http_host;
		proxy_pass http://localhost:xxx;
	}

	# Redirect the other unmatched URLs to XXX.
	location / {
		rewrite ^/(.*) / break;
		proxy_pass https://xxx.xxx;
	}
}
```

## VMess + TLS + gRPC
V2Ray/XRay支持使用gRPC作為傳輸協議，
該種傳輸方式可搭配CDN使用，以實現隱藏代理服務器真實IP的作用。

V2Ray服務端配置：

```json
{
  "inbound": {
    "protocol": "vmess",
    "port": 443,
    "settings": { "clients": [ { "id": "xxx-xxx..." } ] },
    "streamSettings": {
      "network": "grpc",
      "grpcSettings": { "serviceName": "xxx", "multiMode": true },
      "security": "tls",
      "tlsSettings": {
        "certificates": [ {
            "certificateFile": "/opt/tls/tls.crt",
            "keyFile": "/opt/tls/tls.key"
          } ]
      }
    }
  },
  "outbound": { "protocol": "freedom" }
}
```

Clash客戶端配置：

```yaml
proxies:
  - name: xxx
    type: vmess
    server: xxx.xxx.domain
    port: 443
    uuid: xxx-xxx... # UUID需要與服務端保持一致
    alterId: 0 # V2Ray v4.28.1之後，alterId設置為0表示啟用VMessAEAD（服務端會自動適配）
    cipher: auto
    network: ws
    tls: true
    network: grpc
    grpc-opts:
      grpc-service-name: xxx # 需要匹配服務端配置中的serviceName
  ...
```

gRPC需要使用HTTP/2傳輸，因此使用代理轉發gRPC時端口監聽協議為HTTP/2，
對應Nginx轉發配置：

```
server {
	listen xxxx ssl http2;
	ssl_certificate .../tls.crt;
	ssl_certificate_key .../tls.key;

	# Forward GRPC to V2Ray.
	location /xxx {
		grpc_pass grpc://localhost:xxx;
	}

	# Redirect the other unmatched URLs to XXX.
	location / {
		rewrite ^/(.*) / break;
		proxy_pass https://xxx.xxx;
	}
}
```

## V2Ray/XRay Trojan
V2Ray/XRay現在已提供了完善的Trojan協議支持，
並擴充了原版Trojan的功能，支持選用WebSocket或gRPC作為傳輸協議。

`Trojan + TCP + TLS`配置：

```json
{
  "inbounds": [
    {
      "protocol": "trojan",
      "port": 443,
      "settings": {
        "clients": [ { "password": "xxx..." } ],
        "fallbacks": [ { "dest": 80 } ]
      },
      "streamSettings": {
        "network": "tcp",
        "security": "tls",
        "tlsSettings": {
          "certificates": [ {
              "certificateFile": "/opt/tls/tls.crt",
              "keyFile": "/opt/tls/tls.key"
            } ]
        }
      }
    }
  ],
  "outbound": { "protocol": "freedom" },
  ...
}
```

Trojan使用TCP作爲傳輸層時支持`Fallback`，可將非協議流量傳輸到其它服務或端口；
其它傳輸協議如WebSocket、gRPC等均不支持該特性。

`Trojan + WebSocket + TLS`配置：

```json
{
  "inbounds": [
    {
      "protocol": "trojan",
      "port": 443,
      "settings": { "clients": [ { "password": "xxx..." } ] },
      "streamSettings": {
        "network": "ws",
        "wsSettings": { "path": "/xxx..." },
        "security": "tls",
        "tlsSettings": {
          "certificates": [ {
              "certificateFile": "/opt/tls/tls.crt",
              "keyFile": "/opt/tls/tls.key"
            } ]
        }
      }
    }
  ],
  "outbound": { "protocol": "freedom" },
  ...
}
```

對應Clash配置：

```yaml
proxies:
  - name: xxx
    type: trojan
    server: xxx.xxx.domain
    port: 443
    password: xxx...
    network: ws
    ws-opts:
      path: /xxx-xxx...
  ...
```

`Trojan + gRPC + TLS`配置：

```json
{
  "inbounds": [
    {
      "protocol": "trojan",
      "port": 443,
      "settings": { "clients": [ { "password": "xxx..." } ] },
      "streamSettings": {
        "network": "grpc",
        "grpcSettings": { "serviceName": "xxx", "multiMode": true },
        "security": "tls",
        "tlsSettings": {
          "certificates": [ {
              "certificateFile": "/opt/tls/tls.crt",
              "keyFile": "/opt/tls/tls.key"
            } ]
        }
      }
    }
  ],
  "outbound": { "protocol": "freedom" },
  ...
}
```

對應Clash配置：

```yaml
proxies:
  - name: xxx
    type: trojan
    server: xxx.xxx.domain
    port: 443
    password: xxx...
    network: grpc
    grpc-opts:
      grpc-service-name: xxx-xxx...
  ...
```

## V2Ray/XRay Shadowsocks
V2Ray/XRay亦支持Shadowsocks協議，配置：

```json
{
  "inbounds": [
    {
      "protocol": "shadowsocks",
      "port": 2053,
      "settings": {
        "network": "tcp,udp",
        "password": "xxx...",
        "method": "chacha20-ietf-poly1305"
      }
    }
  ],
  "outbound": { "protocol": "freedom" },
  ...
}
```
