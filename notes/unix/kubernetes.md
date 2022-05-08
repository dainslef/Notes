<!-- TOC -->

- [Kubernetes部署](#kubernetes部署)
	- [前置環境配置](#前置環境配置)
		- [內核及網絡配置](#內核及網絡配置)
		- [containerd配置](#containerd配置)
	- [牆國源部署](#牆國源部署)
	- [安裝Kubernetes軟件包](#安裝kubernetes軟件包)
	- [初始化集群](#初始化集群)
		- [排查集群錯誤](#排查集群錯誤)

<!-- /TOC -->



# Kubernetes部署
Kubernetes的基本配置流程參考官方文檔的[Getting started](https://kubernetes.io/docs/setup/)部分。

常用的部署方式是使用kubeadm工具，對應文檔[Bootstrapping clusters with kubeadm](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/)。
使用kubeadm工具部署集群的詳細步驟對應文檔[Creating a cluster with kubeadm](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/create-cluster-kubeadm/)。

## 前置環境配置
Kubernetes對網絡、內核參數、容器等環境存在一系列要求。

### 內核及網絡配置
Kubernetes需要開啓`br_netfilter`內核模塊：

```html
<!-- 設置內核模塊自啟動 -->
# echo br_netfilter > /etc/modules-load.d/k8s.conf
<!-- 啟用內核模塊 -->
# modprobe br_netfilter
```

開啓iptables配置：

```
# echo -e 'net.bridge.bridge-nf-call-ip6tables=1\nnet.bridge.bridge-nf-call-iptables=1\nnet.ipv4.ip_forward=1' > /etc/sysctl.d/k8s.conf
# sysctl --system
```

Kubernetes默認需要關閉系統SWAP（爲了避免潛在的性能問題），開啓了SWAP會導致集羣初始化失敗，
雖然使用`KUBELET_EXTRA_ARGS=--fail-swap-on=false`環境變量可繞過該限制，但不推薦使用。

### containerd配置
Kubernetes可使用containerd作為運行時，各大發行版可直接從軟件倉庫中安裝contianerd：

```
# pacman -S contianerd
# apt install contianerd
# dnf install contianerd
```

牆國內還需要配置containerd鏡像源：

```html
# mkdir /etc/containerd/

<!-- container默認不會創建配置文件，需要手動生成配置 -->
# containerd config default > /etc/containerd/config.toml
```

之後修改配置的`sandbox_image`（該項配置默認爲`"k8s.gcr.io/pause:3.5"`，強國無法訪問，需要修改）
以及`[plugins."io.containerd.grpc.v1.cri".registry.mirrors]`部分
（該配置項默認已創建，但默認爲空，早期版本的containerd該項配置可能名稱爲`[plugins.io]`）：

```toml
...
[plugins]
  ...
  # 較早期的containerd版本（如1.2x）該配置項可能爲[plugins.cri]
  [plugins."io.containerd.grpc.v1.cri"]
    sandbox_image = "registry.aliyuncs.com/k8sxio/pause:3.5"
    ...
    # 若上述配置配置名稱爲[plugins.cri]，則後續該項下的所有子配置均使用該名稱做前綴
    [plugins."io.containerd.grpc.v1.cri".registry]
      ...
      [plugins."io.containerd.grpc.v1.cri".registry.mirrors]
        [plugins."io.containerd.grpc.v1.cri".registry.mirrors."docker.io"]
          endpoint = ["https://bqr1dr1n.mirror.aliyuncs.com"]
        [plugins."io.containerd.grpc.v1.cri".registry.mirrors."k8s.gcr.io"]
          endpoint = ["https://registry.aliyuncs.com/k8sxio"]
```

修改containerd配置后，需要重啓服務使配置生效：

```
# systemctl restart containerd
```

## 牆國源部署
由於牆國內無法直接訪問Google源，因此在無法使用代理的環境下，需要配置國內源。
以阿裏雲爲例：

```html
<!-- 導入倉庫籤名 -->
# curl https://mirrors.aliyun.com/kubernetes/apt/doc/apt-key.gpg -o /etc/apt/trusted.gpg.d/k8s.gpg

<!-- 添加 Kubernetes 倉庫 -->
# add-apt-repository "deb https://mirrors.aliyun.com/kubernetes/apt/ kubernetes-xenial main"
```

Kubernetes可能並未提供與操作系統版本匹配的倉庫
（截止目前2022-05，Ubuntu最新LTS版本爲22.04，但當前Kubernetes倉庫僅提供最高Xenial/16.04版本的安裝包），
由於Kubernetes使用Golang實現，因而對操作系統依賴較少，
在版本較新的操作系統中使用舊版本的Kubernetes倉庫通常不會有問題，
但推薦使用與安裝包完全匹配的系統版本，避免出現潛在的問題。

## 安裝Kubernetes軟件包
軟件源配置完畢後，直接使用對應包管理器安裝kubeadm即可：

```
# apt install kubeadm
```

在Debian系發行版中，其他必要的Kubernetes工具如`kubectl`、`cri-tools`等會自動作爲依賴安裝。

除了Kubernetes軟件包自身，還需要安裝匹配的容器運行時，如Docker、contianerd等。

## 初始化集群
Kubernetes現在默認使用containerd，在牆國由於Kubernetes官方鏡像被牆，
使用kubeadm初始化集群：

```
# kubeadm init 其它參數...
```

初始化集群時可設定各類參數，同樣需要設置阿裏鏡像源，否則無法完成初始化：

```
# kubeadm init --image-repository='registry.cn-hangzhou.aliyuncs.com/google_containers'
```

成功初始化集群後，當前節點將作為control-plane（控制平面），之後可繼續添加其它節點。
初始化的信息中會告知其它節點加入當前集群的指令：

```
# kubeadm join control-plane地址:6443 --token token_xxx --discovery-token-ca-cert-hash hash_xxx
```

加入集群的token可通過下列指令獲取：

```html
$ kubeadm token list

<!-- 查看token對應的discovery-token-ca-cert-hash -->
$ openssl x509 -pubkey -in /etc/kubernetes/pki/ca.crt | openssl rsa -pubin -outform der 2>/dev/null | openssl dgst -sha256 -hex | sed 's/^.* //'
```

### 排查集群錯誤
初始化集群時可能會出現各類錯誤，可通過journalctl進行查看：

```html
<!-- 常見的錯誤可能在kubelet、containerd等進程中 -->
$ journalctl -xeu kubelet
$ journalctl -xeu containerd
```

部分發行版默認會開啓防火牆導致部分服務無法正常監聽端口，需要關閉防火牆服務，
以Ubunut爲例：

```
# systemctl stop apparmor.service
# systemctl disable apparmor.service

# systemctl stop ufw.service
# systemctl disable ufw.service
```

完成集群初始化後，複製認證配置：

```
# mkdir -p $HOME/.kube
# cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
```

之後即可通過kubectl工具訪問集群。
