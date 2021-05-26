<!-- TOC -->

- [Shadowsocks](#shadowsocks)
	- [shadowsocks-libev](#shadowsocks-libev)
- [Trojan](#trojan)
	- [安裝和管理Trojan服務](#安裝和管理trojan服務)
	- [配置Trojan服務](#配置trojan服務)

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
[`Trojan`](https://github.com/trojan-gfw/trojan)是用於繞過Chinazi GFW的解決方案。
Trojan運行TLS協議之上，使用多種協議避免GFW的主動/被動檢測，以及ISP的`QoS`限制。

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

## 配置Trojan服務
正確安裝Trojan後，編輯配置文件`/etc/trojan/config.json`，簡單的服務端配置示例：

```json
{
    "run_type": "server",
    "local_addr": "0.0.0.0",
    "local_port": 9998,
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
| password | 客戶端連接時需要使用的密碼 |
| ssl.cert | 指定使用的證書 |
| ssl.key | 指定使用的私有key |
