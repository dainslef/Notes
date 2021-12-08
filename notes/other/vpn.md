# OpenVPN
OpenVPN是全功能的SSL VPN，通過SSL/TLS協議實現了OSI模型2層或3層安全網絡擴展，
支持多種客戶端認證方式，包括證書、智能卡、帳號密碼等，
並且允許指定用戶/組通過VPN虛擬接口應用特定的訪問控制策略。

## 下發路由
OpenVPN可配置下發到客戶端的路由，以控制客戶端的網絡規則。

將客戶端的所有流量發送到VPN上：

```
push "redirect-gateway def1"
```

若客戶端通過無線網絡連接到VPN，則可添加local標識：

```
push "redirect-gateway local def1"
```

## iroute
若需要實現tun模式下服務端訪問客戶端網絡，則可使用`iroute`。
iroute是OpenVPN內部路由，不會對內核路由表產生影響，
iroute將告知OpenVPN服務某一個客戶端擁有特定網絡。

關於iroute的說明可參見[官方社區Wiki](https://community.openvpn.net/openvpn/wiki/RoutedLans)，以及[`ServerFault`](https://serverfault.com/questions/684508/access-openvpn-client-network-from-server)的對應問題。

## OpenVPN問題記錄
記錄OpenVPN使用中遇到的一些問題。

### OPTIONS ERROR: failed to negotiate cipher with server. Add the server's cipher ('BF-CBC') to --data-ciphers (currently 'AES-256-GCM:AES-128-GCM:AES-128-CBC') if you want to connect to this server.
問題說明：<br>
客戶端指定的加密類型與服務端不符時客戶端會得到該錯誤信息。

解決方案：<br>
查看服務端的OpenVPN配置，確定`cipher`字段配置，將客戶端的cipher設置為與服務端相同。
