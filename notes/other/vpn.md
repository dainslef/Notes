<!-- TOC -->

- [OpenVPN](#openvpn)
	- [基本安裝與配置](#基本安裝與配置)
	- [下發路由](#下發路由)
	- [網關服務器](#網關服務器)
	- [iroute](#iroute)
	- [ifconfig-push](#ifconfig-push)
	- [設置腳本認證](#設置腳本認證)
- [OpenVPN問題記錄](#openvpn問題記錄)
	- [OPTIONS ERROR: failed to negotiate cipher with server. Add the server's cipher ('BF-CBC') to --data-ciphers (currently 'AES-256-GCM:AES-128-GCM:AES-128-CBC') if you want to connect to this server.](#options-error-failed-to-negotiate-cipher-with-server-add-the-servers-cipher-bf-cbc-to---data-ciphers-currently-aes-256-gcmaes-128-gcmaes-128-cbc-if-you-want-to-connect-to-this-server)

<!-- /TOC -->



# OpenVPN
OpenVPN是全功能的SSL VPN，通過SSL/TLS協議實現了OSI模型2層或3層安全網絡擴展，
支持多種客戶端認證方式，包括證書、智能卡、帳號密碼等，
並且允許指定用戶/組通過VPN虛擬接口應用特定的訪問控制策略。

## 基本安裝與配置
各大Unix的軟件倉庫中均已內置了OpenVPN安裝包：

```html
# apt install openvpn <!-- 大便系 -->
# pacman -S openvpn <!-- Arch系 -->
# brew install openvpn <!-- Homebrew -->
```

Linux下的OpenVPN安裝後會生成對應systemd service：

```html
# systemctl start openvpn@client <!-- 啟動OpenVPN客戶端服務 -->
# systemctl start openvpn@server <!-- 啟動OpenVPN服務端 -->
```

OpenVPN的命令行工具為`openvpn`，根據配置文件的不同，可運行在客戶端模式或服務端模式下；
默認的服務端配置文件為`/etc/openvpn/server.conf`，客戶端配置文件為`/etc/openvpn/client.conf`。

通過man手冊查看OpenVPN的命令行參數，
多數命令行參數去掉`--`後即可寫入配置文件中。

## 下發路由
OpenVPN可配置下發到客戶端的路由，以控制客戶端的網絡規則。

向客戶端下發指定路由：

```html
push "route 路由IP段 子網掩碼"
<!-- 示例 -->
push "route 10.89.64.0 255.255.255.0"
```

將客戶端的所有流量發送到VPN上：

```
push "redirect-gateway def1"
```

若客戶端通過無線網絡連接到VPN，則可添加local標識：

```
push "redirect-gateway local def1"
```

## 網關服務器
若將OpenVPN作為網關服務器，則需要使用iptables等服務將自身流量NAT後轉發：

```
# iptables -t nat -A POSTROUTING -s OpenVPN網段 -o 網卡 -j MASQUERADE
```

示例，假設VPN內部網段為`10.8.0.0/24`，網卡名稱為`ens1`，則NAT規則為：

```
# iptables -t nat -A POSTROUTING -s 10.8.0.0/24 -o ens1 -j MASQUERADE
```

同時，服務器還要開啟IPv4轉發功能，否則無法正常轉發流量：

```
# sysctl net.ipv4.ip_forward=1
```

## iroute
若需要實現tun模式下服務端訪問客戶端網絡，則可使用`iroute`。
iroute是OpenVPN內部路由，不會對內核路由表產生影響，
iroute將告知OpenVPN服務某一個客戶端擁有特定網絡。

關於iroute的說明可參見[官方社區Wiki](https://community.openvpn.net/openvpn/wiki/RoutedLans)，
以及[`ServerFault`](https://serverfault.com/questions/684508/access-openvpn-client-network-from-server)的對應問題。

## ifconfig-push
默認配置下OpenVPN對客戶端連接動態分配IP（從地址池中選取最小可用IP）。
若需要靜態分配客戶端連接IP，則可使用`ifconfig-push`。

與iroute類似，ifconfig-push同樣需要將配置寫在client-config-dir路徑下的同名用戶文件中。
ifconfig-push配置說明：

```
ifconfig-push 客戶端IP 服務端IP
```

關於ifconfig-push的說明參見[官方文檔](https://openvpn.net/community-resources/configuring-client-specific-rules-and-access-policies/)。

## 設置腳本認證
通過`auth-user-pass-verify`參數設置認證腳本和認證參數傳入方式：

```
auth-user-pass-verify 認證腳本路徑 認證方式
```

認證方式可取值`via-env`或`via-file`。
使用via-env認證時，用戶/密碼會作為環境變量`username`/`password`傳入腳本中；
使用via-file認證時，用戶/密碼會寫入臨時文件中，臨時文件路徑作為參數傳入腳本中。

認證腳本由用戶自行編寫認證邏輯，返回值為`0`代表認證通過，非零返回值代表認證失敗。
當使用via-env模式時，且傳入認證密碼時，需要在服務端額外配置`script-security`配置項，
並取值`3`，否則在腳本中無法讀取到密碼。（原因可參見man手冊，
以及[OpenVPN論壇](https://community.openvpn.net/openvpn/ticket/747)的對應問題討論）。

via-env模式的完整示例：

```
script-security 3
auth-user-pass-verify check_auth.fish via-env
```

`check_auth.fish`腳本內容：

```fish
#! /usr/bin/fish

# Allow user1/user2 to Login.

echo User login:
echo username: $username
echo password: $password

switch $username
	case "user1"
	case "user2"
	case "*"
		exit 1
end

switch $password
	case "password1"
	case "password2"
	case "*"
		exit 1
end
```



# OpenVPN問題記錄
記錄OpenVPN使用中遇到的一些問題。

## OPTIONS ERROR: failed to negotiate cipher with server. Add the server's cipher ('BF-CBC') to --data-ciphers (currently 'AES-256-GCM:AES-128-GCM:AES-128-CBC') if you want to connect to this server.
問題說明：<br>
客戶端指定的加密類型與服務端不符時客戶端會得到該錯誤信息。

解決方案：<br>
查看服務端的OpenVPN配置，確定`cipher`字段配置，將客戶端的cipher設置為與服務端相同。
