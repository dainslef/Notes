<!-- TOC -->

- [Kubernetes部署](#kubernetes部署)
    - [前置環境配置](#前置環境配置)
        - [內核及網絡配置](#內核及網絡配置)
        - [containerd配置](#containerd配置)
    - [官方源部署](#官方源部署)
    - [牆國源部署](#牆國源部署)
    - [安裝Kubernetes軟件包](#安裝kubernetes軟件包)
    - [初始化集群](#初始化集群)
    - [向集群添加/移除節點](#向集群添加移除節點)
        - [排查集群錯誤](#排查集群錯誤)
        - [重置集群節點](#重置集群節點)
    - [CNI（Container Network Interface）](#cnicontainer-network-interface)
        - [使用helm部署網絡插件](#使用helm部署網絡插件)
    - [升級集群](#升級集群)
    - [清理集群容器](#清理集群容器)
- [Kubernetes對象](#kubernetes對象)
    - [Kubernetes API](#kubernetes-api)
- [kubectl](#kubectl)
    - [kubectl常用操作](#kubectl常用操作)
    - [kubectl訪問容器](#kubectl訪問容器)
    - [kubectl配置](#kubectl配置)
        - [kubectl配置結構](#kubectl配置結構)
        - [kubectl關閉證書驗證](#kubectl關閉證書驗證)
- [集群架構](#集群架構)
    - [Node](#node)
    - [Control Plane](#control-plane)
    - [Pod](#pod)
    - [Service](#service)
        - [Service類型](#service類型)
        - [Service代理模式](#service代理模式)
        - [禁用流量轉發](#禁用流量轉發)
        - [NodePort開放端口](#nodeport開放端口)
    - [ReplicaSet](#replicaset)
    - [Deployment](#deployment)
    - [StatefulSet](#statefulset)
    - [DaemonSet](#daemonset)
    - [Ingress](#ingress)
        - [NGINX Igress Controller](#nginx-igress-controller)
    - [server-snippet](#server-snippet)
        - [Ingress 503](#ingress-503)
- [DNS](#dns)
    - [配置DNS策略](#配置dns策略)
- [Labels 與 Selectors](#labels-與-selectors)
- [ConfigMap 與 Secret](#configmap-與-secret)
- [Taints（污点）](#taints污点)
- [證書（PKI certificates）](#證書pki-certificates)
    - [組件證書自動更新](#組件證書自動更新)
    - [根證書更新](#根證書更新)
- [Dashboard](#dashboard)
    - [創建Dashboard用戶](#創建dashboard用戶)
    - [Kubernetes 1.24 版本手動創建Token](#kubernetes-124-版本手動創建token)
    - [清理serviceaccount與clusterrolebindings資源](#清理serviceaccount與clusterrolebindings資源)
    - [添加Token到配置中](#添加token到配置中)
- [CRI（Container Runtime Interface）](#cricontainer-runtime-interface)
    - [containerd](#containerd)
    - [crictl](#crictl)
        - [crictl運行時配置](#crictl運行時配置)
        - [crictl清理鏡像](#crictl清理鏡像)
- [Helm](#helm)
    - [Helm倉庫管理](#helm倉庫管理)
    - [Helm部署應用](#helm部署應用)
    - [Helm查看部署應用](#helm查看部署應用)
    - [Helm版本回退](#helm版本回退)
    - [使用Helm部署常用的應用](#使用helm部署常用的應用)

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

```html
# pacman -S containerd <!-- Arch系 -->
# apt install containerd <!-- 大便系 -->
# dnf install containerd <!-- 紅帽系 -->
```

首先生成默認的containerd配置：

```html
# mkdir /etc/containerd/

<!-- container默認不會創建配置文件，需要手動生成配置 -->
# containerd config default > /etc/containerd/config.toml
```

將`SystemdCgroup`配置項設置為true（缺少該配置會導致容器反覆重啟）：

```toml
[plugins."io.containerd.grpc.v1.cri".containerd.runtimes.runc]
  ...
  [plugins."io.containerd.grpc.v1.cri".containerd.runtimes.runc.options]
    SystemdCgroup = true
```

**牆國**內還需要配置containerd鏡像源，
修改配置的`sandbox_image`（該項配置默認爲`"k8s.gcr.io/pause:3.5"`，強國無法訪問，需要修改）
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

若Kubernetes需要使用本地倉庫（如Harbor等）需要禁用TLS加密或添加倉庫認證信息。
參考[containerd的Harbor接入配置](../unix/container.md#containerd登入)。

## 官方源部署
在牆國之外或使用代理可直接訪問Google源環境的環境下，配置官方源（舊）：

```html
<!-- 導入倉庫籤名，Ubuntu 22.04 之後推薦將 key 放置在 /etc/apt/keyrings 路徑下 -->
# curl -fsSLo /usr/share/keyrings/kubernetes-archive-keyring.gpg https://packages.cloud.google.com/apt/doc/apt-key.gpg

<!-- 添加 Kubernetes 倉庫 -->
# echo "deb [signed-by=/usr/share/keyrings/kubernetes-archive-keyring.gpg] https://apt.kubernetes.io/ kubernetes-xenial main" > /etc/apt/sources.list.d/kubernetes.list
```

從2023-8-15開始，Kubernetes使用新的軟件源，參考官方博客
[pkgs.k8s.io: Introducing Kubernetes Community-Owned Package Repositories](https://kubernetes.io/blog/2023/08/15/pkgs-k8s-io-introduction/)。
新的軟件源`pkgs.k8s.io`在統一的域名下根據deb/rpm等不同打包方式提供倉庫，不再區分發行版版本；
同時為每個版本設置獨立倉庫，更加易於維護。
以1.28版本為例，配置軟件源：

```html
<!-- 導入倉庫簽名 -->
# curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.28/deb/Release.key | gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpg

<!-- 添加 Kubernetes 倉庫 -->
# echo "deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.28/deb /" | sudo tee /etc/apt/sources.list.d/kubernetes.list
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
（截止目前2022-05，Ubuntu最新LTS版本爲22.04，
但當前Kubernetes倉庫僅提供最高Xenial/16.04版本的安裝包），
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

初始化集群時可設定各類參數（如calico插件需要使用`--pod-network-cidr=192.168.0.0/16`配置pod網段）。
強國部署需要設置阿裏鏡像源，否則無法完成初始化：

```
# kubeadm init --image-repository='registry.cn-hangzhou.aliyuncs.com/google_containers'
```

## 向集群添加/移除節點
成功初始化集群後，當前節點將作為control-plane（控制平面），之後可繼續添加其它節點。
初始化的信息中會告知其它節點加入當前集群的指令：

```html
<!--
實例：
# kubeadm join 10.89.64.11:6443 --token teyt0x.4bxr2bpw9kej2xue --discovery-token-ca-cert-hash sha256:29d2587fd75618a9f02cf428637ca84d36ca55e8e9bb76071c1966fb5790c30e
-->
# kubeadm join control-plane地址:6443 --token token_xxx --discovery-token-ca-cert-hash hash_format:hash_xxx
```

加入集群的token可通過下列指令獲取：

```html
$ kubeadm token list

<!-- 查看token對應的discovery-token-ca-cert-hash -->
$ openssl x509 -pubkey -in /etc/kubernetes/pki/ca.crt | openssl rsa -pubin -outform der 2>/dev/null | openssl dgst -sha256 -hex | sed 's/^.* //'
```

加入集群的token默認有效期僅24小時，token過期後可重新生成：

```html
<!-- 使用 --print-join-command 參數可直接輸出token對應的集群節點加入語句 -->
$ kubeadm token create --print-join-command
```

若需要將節點移出集群，則按順序執行下列操作：

```html
$ kubectl cordon 節點名稱/ID <!-- 停止節點調度 -->
$ kubectl drain 節點名稱/ID <!-- 將節點排除出集群 -->
$ kubectl delete node 節點名稱/ID <!-- 刪除指定節點 -->
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

### 重置集群節點
若需要重置集群節點的狀態，在目標節點中使用`kubeadm reset`指令。

## CNI（Container Network Interface）
初始化集群後，需要配置[Network Plugins（網絡插件）](https://kubernetes.io/docs/concepts/extend-kubernetes/compute-storage-net/network-plugins)，
否則coredns會一直處於pending狀態：

```
$ kubectl get pods -A
NAMESPACE     NAME                                          READY   STATUS    RESTARTS        AGE
kube-system   coredns-64897985d-hzp5f                       0/1     Pending   0               10m
kube-system   coredns-64897985d-sksh6                       0/1     Pending   0               10m
kube-system   etcd-ubuntu-arch64-tokyo                      1/1     Running   10              10m
kube-system   kube-apiserver-ubuntu-arch64-tokyo            1/1     Running   10              10m
kube-system   kube-controller-manager-ubuntu-arch64-tokyo   1/1     Running   0               10m
kube-system   kube-proxy-k9gvq                              1/1     Running   0               10m
kube-system   kube-scheduler-ubuntu-arch64-tokyo            1/1     Running   11              10m
```

配置CNI插件，配置較為簡單的網絡插件如下：

- [flannel](https://github.com/flannel-io/flannel)
- [Weave](https://www.weave.works/docs/net/latest/kubernetes/kube-addon/)
- [calico](https://projectcalico.docs.tigera.io/getting-started/kubernetes/quickstart)

已經安裝了一種CNI插件後，切換到其它CNI插件，需要重置節點，
並移除`/etc/kubenetes`、`/etc/cni`等路徑（該類路徑會包含原CNI插件的配置，影響kubeadm的插件選擇）。
**注意**，`/opt/cni`下會包含`kubernetes-cni`軟件包生成的bin，如`vlan`、`loopback`等，
不可刪除，否則coredns無法運行，會產生類似錯誤：

```
  Warning  FailedCreatePodSandBox  9m1s                  kubelet            Failed to create pod sandbox: rpc error: code = Unknown desc = failed to setup network for sandbox "2e4502e156e797ad76deb3ddaf69d43bde9aef936bae0bacb631158e7cd3b212": failed to find plugin "loopback" in path [/opt/cni/bin]
  Warning  FailedCreatePodSandBox  40s (x38 over 8m47s)  kubelet            (combined from similar events): Failed to create pod sandbox: rpc error: code = Unknown desc = failed to setup network for sandbox "352f1abbd2c2d27f116426ac0abbf8c2f18d6b0446e19c2b9b8eb385b8e8aa43": failed to find plugin "loopback" in path [/opt/cni/bin]
```

部分CNI插件（如`Weave`）亦會在`/opt/cni/bin`下創建自身使用的bin
（如`/opt/cni/bin/weave-net`，`/opt/cni/bin/weave-plugin-*.*.*`）。

舊的CNI插件已啟動，則即使重置kubeadm節點，已創建的網絡設備不會關閉刪除，
會影響新的CNI插件工作，因此在重置節點後，若更換了CNI插件，則應重啟服務器，避免干擾配置。

### 使用helm部署網絡插件
部分CNI支持通過helm部署，以calico為例，
官方提供了[教程](https://projectcalico.docs.tigera.io/getting-started/kubernetes/helm)
用於使用helm部署網絡插件。

基本操作：

```html
<!-- 使用 helm 部署 calico 時，假定 kubeadm 已使用 --pod-network-cidr=192.168.0.0/16 參數初始化 -->
$ kubectl create namespace xxx-namespace
$ helm repo add projectcalico https://projectcalico.docs.tigera.io/charts
$ helm install tigera-operator projectcalico/tigera-operator --namespace xxx-namespace
```

## 升級集群
集群升級可參考[官方文檔](https://kubernetes.io/docs/tasks/administer-cluster/kubeadm/kubeadm-upgrade)。

升級集群首先需要安裝升級目標版本的Kubernetes軟件包，
軟件包安裝完成後，檢視當前安裝的`kubeadm`版本信息：

```html
<!-- 以 v1.25.5 為例 -->
$ kubeadm version
kubeadm version: &version.Info{Major:"1", Minor:"25", GitVersion:"v1.25.5", GitCommit:"804d6167111f6858541cef440ccc53887fbbc96a", GitTreeState:"clean", BuildDate:"2022-12-08T10:13:29Z", GoVersion:"go1.19.4", Compiler:"gc", Platform:"linux/arm64"}
```

確認kubeadm的版本為需要升級的版本，之後可查看升級計畫：

```
# kubeadm upgrade plan
[upgrade/config] Making sure the configuration is correct:
[upgrade/config] Reading configuration from the cluster...
[upgrade/config] FYI: You can look at this config file with 'kubectl -n kube-system get cm kubeadm-config -o yaml'
[preflight] Running pre-flight checks.
[upgrade] Running cluster health checks
[upgrade] Fetching available versions to upgrade to
[upgrade/versions] Cluster version: v1.24.3
[upgrade/versions] kubeadm version: v1.25.5
I1209 15:46:42.222749 1130494 version.go:256] remote version is much newer: v1.26.0; falling back to: stable-1.25
[upgrade/versions] Target version: v1.25.5
[upgrade/versions] Latest version in the v1.24 series: v1.24.9

Components that must be upgraded manually after you have upgraded the control plane with 'kubeadm upgrade apply':
COMPONENT   CURRENT       TARGET
kubelet     1 x v1.25.5   v1.24.9

Upgrade to the latest version in the v1.24 series:

COMPONENT                 CURRENT   TARGET
kube-apiserver            v1.24.3   v1.24.9
kube-controller-manager   v1.24.3   v1.24.9
kube-scheduler            v1.24.3   v1.24.9
kube-proxy                v1.24.3   v1.24.9
CoreDNS                   v1.8.6    v1.9.3
etcd                      3.5.3-0   3.5.6-0

You can now apply the upgrade by executing the following command:

	kubeadm upgrade apply v1.24.9

_____________________________________________________________________

Upgrade to the latest stable version:

COMPONENT                 CURRENT   TARGET
kube-apiserver            v1.24.3   v1.25.5
kube-controller-manager   v1.24.3   v1.25.5
kube-scheduler            v1.24.3   v1.25.5
kube-proxy                v1.24.3   v1.25.5
CoreDNS                   v1.8.6    v1.9.3
etcd                      3.5.3-0   3.5.6-0

You can now apply the upgrade by executing the following command:

	kubeadm upgrade apply v1.25.5

_____________________________________________________________________


The table below shows the current state of component configs as understood by this version of kubeadm.
Configs that have a "yes" mark in the "MANUAL UPGRADE REQUIRED" column require manual config upgrade or
resetting to kubeadm defaults before a successful upgrade can be performed. The version to manually
upgrade to is denoted in the "PREFERRED VERSION" column.

API GROUP                 CURRENT VERSION   PREFERRED VERSION   MANUAL UPGRADE REQUIRED
kubeproxy.config.k8s.io   v1alpha1          v1alpha1            no
kubelet.config.k8s.io     v1beta1           v1beta1             no
_____________________________________________________________________
```

升級計畫中會列出升級的內容，通常可升級到同版本的最新子版本，以及最新的穩定版本（跨大版本升級）。
確認需要升級的版本後，執行輸出的升級指令實施升級操作：

```
# kubeadm upgrade apply v1.25.5
[upgrade/config] Making sure the configuration is correct:
[upgrade/config] Reading configuration from the cluster...
[upgrade/config] FYI: You can look at this config file with 'kubectl -n kube-system get cm kubeadm-config -o yaml'
[preflight] Running pre-flight checks.
[upgrade] Running cluster health checks
[upgrade/version] You have chosen to change the cluster version to "v1.25.5"
[upgrade/versions] Cluster version: v1.24.3
[upgrade/versions] kubeadm version: v1.25.5
[upgrade] Are you sure you want to proceed? [y/N]: y
[upgrade/prepull] Pulling images required for setting up a Kubernetes cluster
[upgrade/prepull] This might take a minute or two, depending on the speed of your internet connection
...

[upgrade/successful] SUCCESS! Your cluster was upgraded to "v1.25.5". Enjoy!

[upgrade/kubelet] Now that your control plane is upgraded, please proceed with upgrading your kubelets if you haven't already done so.
```

輸出`[upgrade/successful] SUCCESS! Your cluster was upgraded to "xxx". Enjoy!`則代表升級成功。

升級完成後，`kube-system`命名空間下的pods會被全部替換，
位於`/etc/kubernetes/manifests`路徑下的配置會替換為新版本，
舊的配置會被備份到`/etc/kubernetes/tmp`路徑下，
若對其中內容進行過修改，則應手動比較配置差異，重新添加配置
（常用配置如修改NodePort範圍，需要恢復`/etc/kubernetes/manifests/kube-apiserver.yaml`文件）。

目前Kubernetes僅支持升級到N+1版本，升級到更高版本需要逐次一一升級；
若使用ArchLinux等滾動發行版，新版本發佈時應儘快升級，避免源內的kubeadm軟件包高與集群版本過多導致無法升級。

## 清理集群容器
Kubernetes默認**不會**刪除不再使用的容器，使用crictl可以看到不再使用的容器：

```
# crictl ps -a
```

kubelet具備自動清理冗余容器的功能，通過配置kubelet的命令行參數可開啟相關功能，
編輯`/var/lib/kubelet/kubeadm-flags.env`文件，在其中添加參數：

```sh
--maximum-dead-containers=0 # 設置最大舊容器的數目，默認取值-1（無限制）
```

還有兩組參數可用於更加靈活得設置容器清除策略：

- `--maximum-dead-containers-per-container` 單獨設置每個實例的舊容器數目
- `--minimum-container-ttl-duration` 依據時間清理舊容器

修改參數後重啟kubelet服務即可。

鏡像清理參考[crictl](#crictl清理鏡像)對應章節內容。



# Kubernetes對象
Kubernetes常用`yaml`的形式描述對象，
參考[官方文檔](https://kubernetes.io/docs/concepts/overview/working-with-objects/kubernetes-objects/)；
使用`kubectl`工具執行yaml格式的對象描述：

```
$ kubctl apply -f 對象描述.yaml
```

Kubernetes的對象描述包含下列內容：

- `apiVersion` API版本
- `kind` 資源類型
- `metadata` 元數據，通常包括name、namespace等
- `spec` 描述對象的具體內容

具體可填寫的內容可查閱具體資源的對應Kubernetes API。

kubectl工具會將yaml格式的對象描述轉換爲等價的Kubernetes API調用
（yaml描述轉換為JSON請求體，發送REST API）。

## Kubernetes API
Kubernetes使用[`Kubernetes API`](https://kubernetes.io/docs/concepts/overview/kubernetes-api/)
創建、修改、刪除對象。

Kubernetes API的詳細定義參見
[`Kubernetes API Reference`](https://kubernetes.io/docs/reference/kubernetes-api/)，
文檔中羅列了不同類別資源yaml的詳細定義。

除了直接使用REST API操作Kubernetes集羣，Kubernetes提供了主流語言的Client綁定，
參考[Client Libraries](https://kubernetes.io/docs/reference/using-api/client-libraries/)。



# kubectl
kubectl提供了與Kubernetes集群通信的功能。

kubectl工具的指令完整說明參考[官方文檔](https://kubernetes.io/docs/reference/kubectl/)。

基本語法：

```
$ kubectl [command] [TYPE] [NAME] [flags]
```

- command指定操作類型，如create/get/describe/delete等。
- TYPE指定資源類型，如pods/services等，資源類型大小寫不敏感，且支持部分匹配。
- NAME指令資源名稱，資源名稱大小寫敏感。

## kubectl常用操作
`kubectl get`用於查看各類資源：

```html
$ kubectl get 資源類型 <!-- 查看指定資源類型 -->
$ kubectl get all <!-- 查看所有資源類型 -->
```

以pods資源為例：

```html
$ kubectl get pods <!-- 查看默認命名空間下的pods -->
$ kubectl get pods pod名稱 <!-- 查看特定名稱的pod -->
$ kubectl get pods -n 命名空間 <!-- 查看特定命名空間下的pods -->
$ kubectl get pods -A <!-- 查看所有命名空間下的pods -->
$ kubectl get pods -o wide/json/yaml <!-- 設置輸出結果的格式 -->
```

查看指定資源的詳細描述：

```html
$ kubectl describe 資源類型 對象名稱
```

查看集群中的發生的事件：

```
$ kubectl get events
```

修改已部署的資源對象：

```html
<!-- 直接編輯對象YAML -->
$ kubectl edit 資源類型 對象名稱

<!-- 更新部分內容 -->
$ kubectl patch 資源類型 對象名稱 -p '更新內容' <!-- 更新內容使用JSON語法 -->
```

kubectl在執行edit指令時，會讀取環境變量`$EDITOR`作為編輯器，
可通過設置$EDITOR使用功能更強的編輯器，以fish shell下使用VSCode為例：

```fish
set -xg EDITOR "code --wait"
```

## kubectl訪問容器
kubectl支持與docker類似的exec指令用於在容器內執行指令。

```html
$ kubectl exec -n 命名空間 Pod名稱 -- 指令

<!-- 進入容器Shell環境 -->
$ kubectl exec -it -n 命名空間 pod名稱 -- sh
```

對於多容器Pod，可使用`-c`參數指定進入的容器名稱：

```
$ kubectl exec -n 命名空間 pod名稱 -c 容器名稱 -- 指令
```

## kubectl配置
kubeclt默認配置路徑為`~/.kube/config`。

### kubectl配置結構
配置為YAML格式，基本配置結構：

```yaml
apiVersion: v1
kind: Config
preferences: {}
current-context: 當前context名稱
contexts:
  - context:
      cluster: 集群名稱
      user: 集群使用的用戶名
    name: context名稱
  ...
clusters:
  - cluster:
      insecure-skip-tls-verify: true
      server: https://x.x.x.x:6443
    name: 集群名稱
  ...
users:
  - name: 用戶名
    user:
      client-certificate-data: 認證數據
      client-key-data: key數據
  ...
```

集群可定義`clusters`字段下，用戶認證信息定義在`users`下，
用戶認證數據和集群在`contexts`字段下綁定組合構成一個個集群環境context；
`current-context`指定kubectl指令默認使用的context，
存在多個context時，使用`--content`參數指令指定特定context：

```
$ kubectl --context 指定context ...
```

### kubectl關閉證書驗證
默認生成的配置下，kubectl會校驗生成私有證書的IP地址，
可使用`insecure-skip-tls-verify`參數關閉：

```yaml
...
clusters:
  - cluster:
      # 將 certificate-authority-data 字段註釋
      # certificate-authority-data: ...
      server: https://x.x.x.x:6443
      insecure-skip-tls-verify: true # 忽略認證
    name: kubernetes
...
```



# 集群架構
Kubernetes集群架構參考[官方文檔](https://kubernetes.io/docs/concepts/architecture/)。

集群架構示意圖如下：

![Kubernetes Cluster](../../images/kubernetes_cluster.svg)

集群組件的詳細介紹參考[官方文檔](https://kubernetes.io/docs/concepts/overview/components)。

## Node
Kubernetes將工作負載放置在容器中，容器放置在Pod中，Pod運行在Node上。
Node可以是物理機或虛擬機。每個Node均由Control Plane管理，並包含運行Pod必要的服務。

一個Node中包含下列組件：

- `kubelet` 用於確保由Kubernetes創建的容器正確地運行在Pod中
- `kube-proxy` 管理節點的網絡規則（如iptables、IPVS等）
- `容器運行時（通常是containerd）` 用於運行容器

通常在集群中會存在多個Nodes，在某些資源受限或學習環境下，才會僅存在單個Node。

使用`kubectl get nodes`查看集群中的節點，示例：

```
$ kubectl get nodes
NAME  STATUS   ROLES           AGE   VERSION
xxx   Ready    control-plane   24d   v1.26.3
...
```

## Control Plane
Control Plane（控制平面）負責管理集群中的Node節點，
Control Plane可以部署在集群內的任何機器中，一個Control Plane節點中會運行下列組件：

- `etcd` 鍵值數據庫，用於存儲集群中的數據
- `kube-apiserver` 用於對外暴露Kubernetes API，是Control Plane的前端
- `kube-scheduler` 用於將Pod分配到實際的Node中
- `kube-controller-manager` 管理、執行各類控制器進程
（常見的控制器包括Node/Job/ServiceAccount controller等，
但Kubernetes將控制器統一編譯到一個`kube-controllers`二進制文件中）
- `cloud-controller-manager` 用於在雲平台中特定的雲相關控制邏輯，如節點控制、服務控制、路由控制等

通常而言，Control Plane節點應僅提供Node節點管理功能而不承擔工作負載，
業務相關的Pod默認不會調度在Control Plane中；
對於單節點場景，可通過去除Control Plane的Taints來允許調度業務Pods。

## Pod
Pod是Kubernetes中可創建和管理的最小部署單元。

Pod可以包含一個或一組容器（通常Pod僅包含單個容器），
同一個Pod內的容器使用相同的存儲和網絡，並且始終被調度在相同的宿主機上。

創建容器API示例：

```yaml
apiVersion: v1
kind: Pod
metadata:
  name: Pod名稱
  namespace: 命名空間
spec:
  hostNetwork: true # 默認false
  containers:
    - name: 容器名稱
      image: 鏡像
    ... # 一個Pod可包含多個容器
  ports:
    - containerPort: 容器端口號
    ...
```

使用`spec.hostNetwork`選項可控制Pod中的容器是否直接使用宿主機網絡，
默認該選項值為false，開啟該選項則Kubernetes的網絡隔離對該Pod無效，
容器內進程將直接使用宿主機端口，需要注意端口衝突問題。

容器端口配置`spec.ports.containerPort`僅作為提示信息使用，是否設置容器端口並不影響實際網絡通信。

在實際生產環境下，通常不會直接創建容器，而是通過`Deployment`、`DaemonSet`等高級特性部署邏輯。

## Service
Service將一組相同的Pod組成服務，提供單一IP和域名。
使用Kubernetes則系統不再需要使用額外的服務發現機制，
Kubernetes會以環境變量的形式告知Pod內容器服務IP，並在組成服務的Pod之間負載均衡。

### Service類型
Service包括下列類型：

- ClusterIP
- NodePort
- LoadBalance

關於三種模式的網絡拓撲差異參考[官方文檔](https://kubernetes.io/docs/tutorials/services/source-ip/)。

### Service代理模式
kube-proxy負載均衡默認使用iptables實現，亦可手動配置為IPVS。

編輯kube-proxy的configmap，設置`mode`參數為`ipvs`：

```html
<!-- 默認 mode 參數為設置值（默認使用iptables），將其修改為 ipvs -->
$ kubectl edit configmap -n kube-system kube-proxy
<!--  -->
$ kubectl rollout restart daemonset -n kube-system kube-proxy
```

詳情參考[StackOverflow](https://stackoverflow.com/questions/56493651/enable-ipvs-mode-in-kube-proxy-on-a-ready-kubernetes-local-cluster)上的相關問答。

使用`ipvsadm`管理IPVS轉發規則：

```html
<!-- 查看當前的轉發規則 -->
# ipvsadm -ln
```

IPVS存在NodePort模式下無法使用本地地址（127.0.0.1）的問題，
參考[GitHub Issues](https://github.com/kubernetes/kubernetes/issues/67730)。

### 禁用流量轉發
默認配置下訪問Service的流量會轉發流量到不同的節點上，
即便使用127.0.0.1本地地址，亦會轉發到不同的節點上。

若需配置流量的轉發策略，可在創建Service時配置下列參數：

| 參數 | 取值 | 默認值 | 說明 |
| :- | :- | :- | :- |
| `internalTrafficPolicy` | Cluster/Local | Cluster | 設置集群內部流量的轉發策略 |
| `externalTrafficPolicy` | Cluster/Local | Cluster | 設置集群外部流量的轉發策略 |

```yaml
apiVersion: v1
kind: Service
metadata:
  ...
spec:
  ...
  internalTrafficPolicy: ...
  externalTrafficPolicy: ...
  ...
```

對與已創建的服務則執行：

```
$ kubectl patch services 服務名稱 -p '{"spec":{"internalTrafficPolicy":"Local"}}'
$ kubectl patch services 服務名稱 -p '{"spec":{"externalTrafficPolicy":"Local"}}'
```

internalTrafficPolicy設置為Local後，
外部流量進入集群，需要當前節點存在對應服務的pods，當前節點無服務pods則無法訪問服務。

internalTrafficPolicy設置為Local同時對內部、外部流量生效，
外部、內部流量均不再轉發（但依舊進行NAT轉換），容器內部收到數據包源IP為所在物理機節點IP。

externalTrafficPolicy設置為Local則僅對外部流量生效，
外部流量不再轉發（並且不進行NAT轉換），內部流量依舊轉發，容器內部收到數據包源IP為客戶端原始IP。

internalTrafficPolicy與externalTrafficPolicy皆設置為Local時，
行為與externalTrafficPolicy設置Local相同。

### NodePort開放端口
NodePort端口範圍默認為`30000-32767`，擴展端口範圍需要修改`kube-apiserver`的配置文件
`/etc/kubernetes/manifests/kube-apiserver.yaml`：

```yaml
apiVersion: v1
kind: Pod
metadata:
  ...
spec:
  containers:
  - command:
    - kube-apiserver
    ...
    # Custom Node Port range
    - --service-node-port-range=1-65535
```

需要修改每一個運行kube-apiserver節點的配置，更改配置後，需要重啟該進程。
若Kubernetes使用kubeadm或KubeSphere創建，kube-apiserver以Pods形式部署，Pod會自動重啟。

## ReplicaSet
ReplicaSet用於控制Pods的數目，保證指定Pods的複製實例數目在一個穩定的狀態，
當Pods異常退出時，Kubernetes會自動重新創建Pods維持指定的數目。

示例：

```yaml
apiVersion: apps/v1
kind: ReplicaSet
metadata:
  name: frontend
  labels:
    app: guestbook
    tier: frontend
spec:
  # Modify replicas according to your case.
  replicas: 3
  selector:
    matchLabels:
      tier: frontend
  template:
    metadata:
      labels:
        tier: frontend
    spec:
      containers:
        - name: php-redis
          image: gcr.io/google_samples/gb-frontend:v3
```

## Deployment
Deployment可用於管理Pods和ReplicaSets，提供滾動更新等部署功能。

Deployment中同樣可使用replicas配置項定義Pods的複製數目，
應用Deployment後會自動生成對應的ReplicaSets。

Deployment可執行重啟操作，用於鏡像變化時更新Pods：

```
$ kubectl rollout restart deployment -n 命名空間 Deployment名稱
```

默認StrategyType為`RollingUpdate`，即逐個替換舊Pod。

示例（使用Deployment部署Nginx）：

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.14.2
        ports:
        - containerPort: 80
```

## StatefulSet
[StatefulSet](https://kubernetes.io/docs/concepts/workloads/controllers/statefulset)
用於管理存在狀態的集群服務，與Deployment相似，StatefulSet管理的一組Pods使用相同的容器規格，
不同在於StatefulSet中各個Pods是不可互換的，每個Pod擁有獨立的標識符，
StatefulSet會持久化Pod的標識符，在任何重編排（rescheduling）下均會保持該標識。

StatefulSet適合下列需求：

- 穩定、唯一的網絡標識
- 穩定、持久化的存儲
- 有序的部署和擴容
- 有序、自動化的滾動更新

Deployment適合用於無狀態的集群，StatefulSet適合部署依賴狀態的集群，如Zookeeper、Galera Cluster等。

StatefulSet創建方式與Deployment基本相同，但StatefulSet在使用外部存儲時，必須使用PersistentVolume，
Kubernetes會記錄每個PersistentVolume與StatefulSet内Pods的對應關係（persistent identifier），
保證重編排時依舊維持該對應關係。

使用傳統的Deployment部署時，Pod名稱會隨機生成後綴，重新編排時Pod名稱會發生變化；
使用StatefulSet則Pod名稱不會變化。

使用StatefulSet創建的集群，每個Pod均會擁有獨立、固定的名稱及網絡標識，
默認命名規則為`服務名稱-Pod編號`，Pod編號從`0`開始到`replicas - 1`結束，
借助該機制，在編排容器時即可確定所有Pod的域名，分布式服務以此配置實現集群通信；

示例，假設`tiananmen8964`命名空間下存在名為`fuckccp`的服務，
replicas為3，則生成的3個Pod域名分別為：

1. `fuckccp-0.fuckccp.tiananmen8964.svc.cluster.local`
1. `fuckccp-1.fuckccp.tiananmen8964.svc.cluster.local`
1. `fuckccp-2.fuckccp.tiananmen8964.svc.cluster.local`

## DaemonSet
[DaemonSet](https://kubernetes.io/docs/concepts/workloads/controllers/daemonset/)
用於每個Node固定啟動一個Pod的場景，創建DaemonSet後會自動根據集群規模生成數目匹配的Pods，
擴充/刪除Node，Pods數目隨之改變。

與Deployment類似，DaemonSet亦支持rollout相關操作。

示例（使用DaemonSet部署V2Ray）：

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
          image: v2fly/v2fly-core:v4.45.2
          volumeMounts:
            - mountPath: /etc/v2ray
              name: v2ray-config
      volumes:
        - name: v2ray-config
          hostPath:
            path: /etc/v2ray
            type: DirectoryOrCreate
```

## Ingress
[Ingress](https://kubernetes.io/docs/concepts/services-networking/ingress/)
通過HTTP和HTTPS路由規劃外部流量到內部服務的訪問方式，路由規則在Ingress資源中定義。

Ingress架構如下所示：

![Kubernetes Ingress](../../images/kubernetes_ingress.svg)

Ingress需要[Ingress Controller](https://kubernetes.io/docs/concepts/services-networking/ingress-controllers/)
提供服務才能生效，Ingress Controller擁有多種實現。
OpenStack等雲平台中可使用對應平台的Ingress Controller；
或者使用NGINX Igress Controller。

默認集群配置下Ingress Controller並未自動安裝，
需要開發者自行配置選擇合適的Ingress Controller實現。

### NGINX Igress Controller
[`NGINX Igress Controller`](https://github.com/kubernetes/ingress-nginx)
是最常見的Igress Controller，使用NGINX作為反向代理於負載均衡器。

NGINX Ingress Controller詳細使用方式參見[官方文檔](https://kubernetes.github.io/ingress-nginx/)。

使用Helm安裝NGINX Igress Controller：

```
$ helm repo add ingress-nginx https://kubernetes.github.io/ingress-nginx
$ helm install ingress-nginx ingress-nginx/ingress-nginx
```

Ingress API參考
[官方文檔](https://kubernetes.io/docs/reference/kubernetes-api/service-resources/ingress-v1/)，
對象描述示例：

```yaml
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: custom-ingress
  namespace: custom-components
  annotations:
    nginx.ingress.kubernetes.io/rewrite-target: /$1
spec:
  ingressClassName: ingress-nginx
  rules:
  - http:
      paths:
      - path: /prefix1
        pathType: Prefix
        backend:
          service:
            name: test1
            port:
              number: 443
      - path: /prefix2/(.*)
        pathType: Prefix
        backend:
          service:
            name: test2
            port:
              number: 80
        ...
```

NGINX Igress Controller會根據Ingress對象描述的規則
在Igress Controller容器中生成對應的NGINX配置文件（容器中的`/etc/nginx/nginx.conf`）。

NGINX Igress Controller在`spec.rules.http.paths.path`中支持使用正則表達式捕獲內容，
捕獲的內容在`metadata.annotations.nginx.ingress.kubernetes.io/rewrite-target`
中可使用`$1`、`$2`等變量名獲取對應位置的捕獲內容來構成轉發後的URL。

## server-snippet
使用`metadata.annotations.nginx.ingress.kubernetes.io/server-snippet`
可直接向生成的nginx.conf中添加配置內容，示例：

```yaml
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: custom-ingress
  namespace: custom-components
  annotations:
    nginx.ingress.kubernetes.io/rewrite-target: /$1
    nginx.ingress.kubernetes.io/server-snippet: |
      location ~* ^/xxx/(.*) {
        rewrite ^/xxx/(.*) /Xxx/xxx/$1 break;
        proxy_pass https://xxx.xxx.xxx;
      }
spec:
  ingressClassName: ingress-nginx
  rules:
    ...
```

NGINX Igress Controller中使用的路徑匹配和proxy_pass轉發與標準NGINX中存在一些差異，
參見[StackOverflow](https://stackoverflow.com/questions/63275239/kubernetes-nginx-ingress-server-snippet-annotation-not-taking-effect)
上的對應問題。

從`NGINX Igress Controller 1.9`版本開始，默認禁用了server-snippet，
需要設置`allow-snippet-annotations`才能使用，
相關問題參見[GitHub Issues](https://github.com/kubernetes/ingress-nginx/issues/10452)；
相關配置參見[GitHub文檔](https://github.com/kubernetes/ingress-nginx/blob/main/docs/user-guide/nginx-configuration/configmap.md#allow-snippet-annotations)。

使用Helm安裝NGINX Igress Controller需要搭配使用`--set controller.allowSnippetAnnotations=true`參數。

### Ingress 503
Ingress中轉發的目標服務需要與Ingress本體位於同一命名空間，否則會出現503錯誤。

若需要強行轉發服務流量到不同命名空間的服務，可考慮使用完整服務域名，
根據Igress Controller類型，編寫專屬規則配置。



# DNS
Kubernetes集群內的所有Pod、Service均可通過域名進行訪問，
參考[Kubernetes官方文檔](https://kubernetes.io/docs/concepts/services-networking/dns-pod-service/#pod-s-dns-policy)。

以Service為例，Kubernetes會將Service的服務名稱註冊到的DNS中，
在每一個Kubernetes集群內的Pod容器中均可使用**域名**訪問服務：

- `服務名稱` 訪問同命名空間的服務
- `服務名稱.命名空間` 訪問不同命名空間的服務
- `服務名稱.命名空間.svc.cluster.local` 服務完整域名

## 配置DNS策略
使用`spec.dnsPolicy`可配置Pod內容器的DNS策略。

對於使用host網絡的容器（啟用`spec.hostNetwork`），
默認不會配置Kubernetes的DNS（無法以域名形式訪問Pod/Services），
設置DNS策略為`ClusterFirstWithHostNet`即可如普通Pod一樣使用Kubernetes的DNS：

```yaml
spec:
  hostNetwork: true
  dnsPolicy: ClusterFirstWithHostNet
  ...
```



# Labels 與 Selectors
Labels（標籤）用於為特定的資源打上相關標籤，便於為資源歸類。
通常在`metadata`中使用`labels`為指定資源添加標籤：

```yaml
...
metadata:
  name: xxx
  labels:
    key1: value1
    key2: value2
    ...
...
```

標籤常用於
在API中使用`selector`：

```yaml
...
selector:
  matchLabels:
    key1: value1
    key2: value2
    ...
  matchExpressions:
    - {key: key3, operator: In, values: [value1, value2, ...]}
    - {key: key4, operator: NotIn, values: [value1, value2, ...]}
    - ...
...
```

`selector`支持`matchLabels`（等值匹配）與`matchExpressions`（表達式匹配），
多個條件之間是`&&`（and，邏輯與）關係。

kubectl命令行亦可使用`-l`參數指定標籤實現**批量操作**：

```html
<!-- 刪除所有標籤為 key=value 的xxx資源 -->
$ kubectl delete xxx -l "key=value"
```

完整的Labels和Selectors說明參考
[官方文檔](https://kubernetes.io/docs/concepts/overview/working-with-objects/labels/)。



# ConfigMap 與 Secret
[`ConfigMap`](https://kubernetes.io/docs/concepts/configuration/configmap)
用於存儲配置數據供Pod中掛載使用，API說明：

```yaml
---
# 定義配置
apiVersion: v1
kind: ConfigMap
metadata:
  name: 配置名稱
  namespace: 命名空間
data:
  配置項1: |
    ...
  配置項2: |
    ...
  ...

---
# 創建Pod時使用配置
apiVersion: v1
kind: Pod
metadata:
  name: Pod名稱
  namespace: 命名空間
spec:
  containers:
    - name: 容器名稱
      image: 鏡像
      volumeMounts:
        - mountPath: 配置掛載到容器的路徑
          name: 引用配置（與volumes中對應）
      volumes:
        - name: 配置名稱（由容器引用）
          configMap:
            name: ConfigMap配置名稱
            # 自定義配置配置項的掛載文件名，若使用配置項默認名稱，則無須自定義
            items:
              - key: ConfigMap指定配置名稱下的配置項
                path: 掛載為配置文件的名稱
```

[`Secret`](https://kubernetes.io/docs/concepts/configuration/secret)
與ConfigMap作用類似，但用於存儲加密數據，API說明：

```yaml
---
# 定義Secret
apiVersion: v1
kind: Secret
metadata:
  name: Secret名稱
  namespace: 命名空間
type: Opaque
data:
  # 作為環境變量引入
  加密數據1: ...
  加密數據2: ...
  ...
stringData:
  # 作為文件引入
  加密文件1: |
    ...
  加密文件2: |
    ...
  ...

---
# 創建Pod時使用Secret
apiVersion: v1
kind: Pod
...
spec:
  containers:
    - name: 容器名稱
      image: 鏡像
      volumeMounts:
        ...
      volumes:
        - name: ...
          secret:
            secretName: Secret名稱
            ...
      env:
        - name: 環境變量名稱
          valueFrom:
            secretKeyRef:
              name: Secret名稱
              key: 指定加密數據的Key
```

Secret使用方法與ConfigMap基本類似，但存在下列區別：

- Secret存在多種類型，默認類型為`Opaque`，
存儲任意的用戶定義加密數據，根據加密數據類型的不同，可使用對應的細分類型
- Secret存儲的數據亦分為兩種類型：
	- `data` 作為環境變量寫入容器中
	- `stringData` 作為文件掛載到容器中



# Taints（污点）
Taints特性會影響pod對運行node的選擇策略。

更改節點的污染：

```html
$ kubectl taint nodes 節點名稱 污點 <!-- 為指定node添加taint -->
$ kubectl taint nodes 節點名稱 污點- <!-- 為指定node去除taint -->
```

修改污點不會影響已經部署的pods，重新啟動pods才會再次匹配污點策略。

默認Kubernetes的master節點中使用了污點`node-role.kubernetes.io/master:NoSchedule`，
該污點使得在master節點上不能部署用戶pods。

```
$ kubectl describe nodes master節點名稱
...
Taints:             node-role.kubernetes.io/master:NoSchedule
...
```

禁止在master節點中調度pods，通過刪除污點可解除該限制：

```html
<!-- 移除污點 -->
$ kubectl taint nodes --all node-role.kubernetes.io/master-

<!-- 恢復污點 -->
$ kubectl taint node 節點名稱 node-role.kubernetes.io/master:NoSchedule
```

解除該污點後，需要重新重啟對應被暫停調度的pods。

若master節點同時帶有角色`control-plane`，
則還需要解除`node-role.kubernetes.io/control-plane:NoSchedule`污點，操作類似。



# 證書（PKI certificates）
Kubernetes使用PKI certificates用於TLS認證，
證書相關完整內容參考[官方文檔](https://kubernetes.io/docs/tasks/administer-cluster/kubeadm/kubeadm-certs/)。

證書位於`/etc/kubernetes/pki`路徑下，
默認根證書有效期10年，各組件證書有效期1年；
使用`kubeadm certs`相關指令查看證書有效期和更新證書：

```html
<!-- 檢查證書有效期 -->
# kubeadm certs check-expiration

<!-- 手動更新所有證書 -->
# kubeadm certs renew all
```

KubeKey集群刷新證書[參考KubeKey章節](#KubeKey集群刷新證書)。

## 組件證書自動更新
kubelet內置了組件證書的自動刷新證書機制並已默認開啟，會在證書過期前自動刷新。

查看證書刷新機制是否啟用：

```
$ cat /var/lib/kubelet/config.yaml | grep rotate
```

關閉該機制可在集群升級時傳入`--certificate-renewal=false`參數：

```
# kubeadm upgrade apply --certificate-renewal=false
```

## 根證書更新
Kubernetes不支持根證書自動更新，也未提供根證書的更新工具指令，
根證書更新步驟參考[官方文檔](https://kubernetes.io/docs/tasks/tls/manual-rotation-of-ca-certificates/)。

證書說明和要求參考[官方文檔](https://kubernetes.io/docs/setup/best-practices/certificates/)。



# Dashboard
Kubernetes提供了基於WEB-UI的控制面板，
參考[官方文檔](https://kubernetes.io/docs/tasks/access-application-cluster/web-ui-dashboard/)。

部署面板：

```html
$ kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/版本號/aio/deploy/recommended.yaml
<!-- 示例： kubectl apply -f https://raw.githubusercontent.com/kubernetes/dashboard/v2.5.1/aio/deploy/recommended.yaml -->
```

部署Pod完成後，在需要使用面板的機器執行：

```
$ kubectl proxy
```

之後可訪問面板的Web地址：

```
http://localhost:8001/api/v1/namespaces/kubernetes-dashboard/services/https:kubernetes-dashboard:/proxy/
```

對於使用Helm部署的Dashboard，訪問地址需要替換命名空間：

```
http://localhost:8001/api/v1/namespaces/命名空間/services/https:kubernetes-dashboard:https/proxy/
```

## 創建Dashboard用戶
部署面板後需要創建服務帳戶（参考[官方GitHub](https://github.com/kubernetes/dashboard/blob/master/docs/user/access-control/creating-sample-user.md)）：

```yaml
# 創建ServiceAccount，命名空間 kubernetes-dashboard，用戶名 custom-kubernetes-dashboard-admin
# 若不創建用戶亦可使用內置用戶 kubernetes-dashboard
apiVersion: v1
kind: ServiceAccount
metadata:
  name: custom-kubernetes-dashboard-admin
  namespace: kubernetes-dashboard

---
# 創建ClusterRoleBinding，為之前創建的 custom-kubernetes-dashboard-admin 用戶綁定 cluster-admin 角色
# 若未綁定 cluster-admin 角色，則對應用戶生成的Token無權限查看集群信息
apiVersion: rbac.authorization.k8s.io/v1
kind: ClusterRoleBinding # ClusterRoleBinding類別的資源無命名空間
metadata:
  name: custom-cluster-admin-role-binding-for-kubernetes-dashboard
roleRef:
  apiGroup: rbac.authorization.k8s.io
  kind: ClusterRole
  name: cluster-admin
subjects:
- kind: ServiceAccount
  name: custom-kubernetes-dashboard-admin
  namespace: kubernetes-dashboard
```

創建角色後，可查看Token：

```html
<!-- 獲取 Token（1.24版本前） -->
$ kubectl -n kubernetes-dashboard describe serviceaccount custom-kubernetes-dashboard-admin <!-- 查看默認Token -->
$ kubectl -n kubernetes-dashboard describe secrets xxxtoken
```

亦可不創建serviceaccount，直接復用kubernetes-dashboard內置的`kubernetes-dashboard`用户，
操作類似，為其綁定`cluster-admin`角色即可。

## Kubernetes 1.24 版本手動創建Token
`Kubernetes 1.24`版本後，ServiceAccount不再自動生成Token，可手動創建臨時Token：

```
$ kubectl -n kubernetes-dashboard create token custom-kubernetes-dashboard-admin
```

亦可創建帳戶對應的Secret資源（低版本不需要）：

```yaml
apiVersion: v1
kind: Secret
type: kubernetes.io/service-account-token
metadata:
  name: custom-secret-for-kubernetes-dashboard
  namespace: kubernetes-dashboard
  annotations:
    kubernetes.io/service-account.name: custom-kubernetes-dashboard-admin
    kubernetes.io/service-account.namespace: kubernetes-dashboard
```

手動創建Secret後，直接查看對應資源即可得到Token信息：

```html
$ kubectl -n kubernetes-dashboard describe secrets custom-secret-for-kubernetes-dashboard
```

## 清理serviceaccount與clusterrolebindings資源
若不再使用Token，則應清理對應資源：

```html
<!-- 刪除 serviceaccount，生成的 secret 會對應刪除 -->
$ kubectl delete serviceaccount -n kubernetes-dashboard custom-kubernetes-dashboard-admin
<!-- 刪除 clusterrolebindings（該類資源無命名空間） -->
$ kubectl delete clusterrolebindings custom-cluster-admin-role-binding-for-kubernetes-dashboard
```

直接刪除secrets系統依舊會自動重新創建。

## 添加Token到配置中
若需要經常使用Dashboard，每次通過命令行查看secrets對應Token較為不便，
可直接將Token加入`~/.kube/config`配置中，之後認真僅需要選取該文件即可。

配置示例：

```yaml
apiVersion: v1
clusters:
...
contexts:
...
current-context: kubernetes-admin@kubernetes
kind: Config
users:
- name: kubernetes-admin
  user:
    client-certificate-data: ...
    client-key-data: ...
    token: tokenxxx... # token填寫到該位置
```



# CRI（Container Runtime Interface）
[CRI](https://kubernetes.io/blog/2016/12/container-runtime-interface-cri-in-kubernetes/)
是Kubernetes在1.5版本中引入的標準容器運行時接口。

該接口屏蔽了底層容器運行時的差異，使得Kubernetes架構中，容器運行時成為可替換的部分。

## containerd
[containerd](https://containerd.io/)是目前主流的CRI實現，Docker亦使用了該實現。
containerd提供了自身的命令行管理工具`ctr`。

由於Kubernetes的鏡像、容器不在默認命名空間，因此默認指令不會輸出Kubernetes相關內容，
指定命名空間後可正常輸出：

```
$ ctr --namespace k8s.io container ls
CONTAINER                                                           IMAGE                                            RUNTIME
0cca207bef4f47844f5befc9e66bd6e0637fe8b163f85f8f11b08698bc54186e    k8s.gcr.io/pause:3.5                             io.containerd.runc.v2
...
```

containerd配置位於路徑`/etc/containerd/config.toml`，
修改配置需要重啟服務，可以使用crictl確認配置的生效情況：

```
$ crictl info
```

## crictl
Kubernetes提供了
[`crictl`](https://github.com/kubernetes-sigs/cri-tools/blob/master/docs/crictl.md)
工具用於管理容器，crictl通過標準的`CRI`接口管理容器，
提供了與docker類似的命令行接口：

```
$ crictl
NAME:
   crictl - client for CRI

USAGE:
   crictl [global options] command [command options] [arguments...]

VERSION:
   v1.19.0

COMMANDS:
   attach              Attach to a running container
   create              Create a new container
   exec                Run a command in a running container
   version             Display runtime version information
   images, image, img  List images
   inspect             Display the status of one or more containers
   inspecti            Return the status of one or more images
   imagefsinfo         Return image filesystem info
   inspectp            Display the status of one or more pods
   logs                Fetch the logs of a container
   port-forward        Forward local port to a pod
   ps                  List containers
   pull                Pull an image from a registry
   run                 Run a new container inside a sandbox
   runp                Run a new pod
   rm                  Remove one or more containers
   rmi                 Remove one or more images
   rmp                 Remove one or more pods
   pods                List pods
   start               Start one or more created containers
   info                Display information of the container runtime
   stop                Stop one or more running containers
   stopp               Stop one or more running pods
   update              Update one or more running containers
   config              Get and set crictl client configuration options
   stats               List container(s) resource usage statistics
   completion          Output shell completion code
   help, h             Shows a list of commands or help for one command

GLOBAL OPTIONS:
   --config value, -c value            Location of the client config file. If not specified and the default does not exist, the program's directory is searched as well (default: "/etc/crictl.yaml") [$CRI_CONFIG_FILE]
   --debug, -D                         Enable debug mode (default: false)
   --image-endpoint value, -i value    Endpoint of CRI image manager service (default: uses 'runtime-endpoint' setting) [$IMAGE_SERVICE_ENDPOINT]
   --runtime-endpoint value, -r value  Endpoint of CRI container runtime service (default: uses in order the first successful one of [unix:///var/run/dockershim.sock unix:///run/containerd/containerd.sock unix:///run/crio/crio.sock]). Default is now deprecated and the endpoint should be set instead. [$CONTAINER_RUNTIME_ENDPOINT]
   --timeout value, -t value           Timeout of connecting to the server in seconds (e.g. 2s, 20s.). 0 or less is set to default (default: 2s)
   --help, -h                          show help (default: false)
   --version, -v                       print the version (default: false)
```

### crictl運行時配置
crictl執行需要root權限，默認配置下會按照下列數序查找支持的運行時：

1. unix:///var/run/dockershim.sock (dockershim)
1. unix:///run/containerd/containerd.sock (containerd)
1. unix:///run/crio/crio.sock (cri-o)
1. unix:///var/run/cri-dockerd.sock (cri-dockerd)

若docker不是當前使用的運行時，則會輸出告警信息：

```
# crictl ps -a
WARN[0000] runtime connect using default endpoints: [unix:///var/run/dockershim.sock unix:///run/containerd/containerd.sock unix:///run/crio/crio.sock]. As the default settings are now deprecated, you should set the endpoint instead.
ERRO[0002] connect endpoint 'unix:///var/run/dockershim.sock', make sure you are running as root and the endpoint has been started: context deadline exceeded
WARN[0002] image connect using default endpoints: [unix:///var/run/dockershim.sock unix:///run/containerd/containerd.sock unix:///run/crio/crio.sock]. As the default settings are now deprecated, you should set the endpoint instead.
ERRO[0004] connect endpoint 'unix:///var/run/dockershim.sock', make sure you are running as root and the endpoint has been started: context deadline exceeded
...
```

修改配置`/etc/crictl.yaml`（默認不存在該文件，需要手動創建），加入當前使用的運行時，以containerd為例：

```
# echo -e "runtime-endpoint: unix:///run/containerd/containerd.sock\nimage-endpoint: unix:///run/containerd/containerd.sock" > /etc/crictl.yaml
```

其它常用配置：

```yaml
runtime-endpoint: unix:///run/containerd/containerd.sock
image-endpoint: unix:///run/containerd/containerd.sock
timeout: 2
debug: false
pull-image-on-create: false
```

### crictl清理鏡像
與Docker類似，crictl支持prune操作清理不再使用的鏡像：

```
# crictl rmi --prune
```



# Helm
[Helm](https://helm.sh/)是Kubernetes的包管理器，可簡化應用在Kubernetes環境下的部署和管理。

## Helm倉庫管理
Helm在部署應用前需要添加倉庫，倉庫相關操作：

```html
$ helm repo add 倉庫名稱 倉庫地址
$ helm repo add --insecure-skip-tls-verify 倉庫名稱 倉庫地址 <!-- 添加證書無效的HTTPS倉庫時跳過驗證 -->
$ helm repo remove 倉庫名稱
$ helm repo list <!-- 列出倉庫 -->
$ helm repo update <!-- 更新倉庫 -->
```

## Helm部署應用
部署應用相關操作：

```html
<!-- 安裝應用 -->
$ helm install 應用安裝名稱 倉庫名稱/應用名稱 -n 命名空間
$ helm install 倉庫名稱/應用名稱 -n 命名空間 --generate-name <!-- 自動生成應用的安裝名稱 -->
$ helm install 應用安裝名稱 倉庫名稱/應用名稱 -n 命名空間 --version 版本號 <!-- 指定部署版本 -->

<!-- 移除應用 -->
$ helm uninstall 應用安裝名稱 -n 命名空間

<!-- 升級應用 -->
$ helm repo update <!-- 升級之前首先刷新倉庫 -->
$ helm upgrade --install 應用安裝名稱 倉庫名稱/應用名稱
```

安裝、升級應用時通過`--set`參數控制部署配置：

```html
<!-- 安裝應用時設置配置參數 -->
$ helm install --set key1=value1,key2=value2,... -n 命名空間 應用安裝名稱 倉庫名稱/應用名稱
<!-- 對於升級操作類似，需要使用與之前安裝相同的參數 -->
$ helm upgrade --install --set key1=value1,key2=value2,... -n 命名空間 應用安裝名稱 倉庫名稱/應用名稱

<!--
對與數組結構的value，使用花括號語法：
--set key={xxx1,xxx2}
轉換為yaml結構為：
key:
- xxx1
- xxx2
-->
$ helm install --set key={xxx1,xxx2,...} -n 命名空間 應用安裝名稱 倉庫名稱/應用名稱
```

自定義部署配置亦可使用yaml格式寫在文件中，使用`-f`參數指定部署配置：

```
$ helm install 應用安裝名稱 倉庫名稱/應用名稱 -f 自定義配置.yaml
```

應用的配置可從項目的[`ArtifactHub`](https://artifacthub.io/)中查詢得到。

其它配置相關操作：

```html
<!-- 查看當前使用的配置參數 -->
$ helm get values -n 命名空間 應用安裝名稱

<!-- 在應用安裝完成後更新指定參數 -->
$ helm ugrade --set key=xxx -n 命名空間 應用安裝名稱 倉庫名稱/應用名稱
```

## Helm查看部署應用
查看已部署的應用：

```html
<!-- 列出部署的應用 -->
$ helm list
$ helm list -n 命名空間 <!-- 列出指定命名空間下的應用 -->
$ helm list -A <!-- 列出所有命名空間的應用 -->

<!-- 查看部署指定應用的詳情 -->
$ helm status -n 命名空間 應用安裝名稱
```

對於多套集群環境，helm支持與kubectl類似的`--kube-context`參數來選擇集群。

## Helm版本回退
使用Helm部署/升級應用每次操作均會增加應用的`REVISION`值（修訂編號），
若升級後的應用出現問題可回退到之前的REVISION版本：

```html
<!-- 查看應用變更歷史，包含每個編號和對應版本 -->
$ helm history -n 命名空間 應用安裝名稱
<!-- 將應用版本回退到指定修訂編號對應的版本 -->
$ helm rollback -n 命名空間 應用安裝名稱 目標修訂編號
```

示例：

```html
<!--
以 tigera-operator 為例，最初部署版本為v3.26.1，後續經過多次升級至版本v3.27.2，
查看版本變更歷史
-->
$ helm history -n helm-charts tigera-operator
REVISION	UPDATED                 	STATUS    	CHART                  	APP VERSION	DESCRIPTION
1       	Tue Sep  5 17:11:05 2023	superseded	tigera-operator-v3.26.1	v3.26.1    	Install complete
2       	Fri Dec 15 13:02:11 2023	superseded	tigera-operator-v3.26.4	v3.26.4    	Upgrade complete
3       	Fri Feb 23 15:38:14 2024	superseded	tigera-operator-v3.27.2	v3.27.2    	Upgrade complete

<!-- v3.27.2 版本存在BUG -->
```

## 使用Helm部署常用的應用
與DockerHub類似，Helm也提供了[`ArtifactHub`](https://artifacthub.io)，
多數項目均可使用Helm部署。

```html
$ kubectl create namespace helm-charts

<!--
Calico CNI
(Need init kubeadm with parameters: kubeadm init --pod-network-cidr=192.168.0.0/16)
-->
$ helm repo add tigera-operator https://projectcalico.docs.tigera.io/charts
$ helm install -n helm-charts tigera-operator tigera-operator/tigera-operator

<!-- kubernetes-dashboard -->
$ helm repo add kubernetes-dashboard https://kubernetes.github.io/dashboard
$ helm install -n helm-charts kubernetes-dashboard kubernetes-dashboard/kubernetes-dashboard

<!-- metrics-server -->
$ helm repo add metrics-server https://kubernetes-sigs.github.io/metrics-server
$ helm install -n helm-charts metrics-server metrics-server/metrics-server --set 'args={--kubelet-insecure-tls=true}'

<!--
Prometheus + Grafana

Use kubectl to get the default Grafana admin password:
$ kubectl get secret -n helm-charts -o jsonpath='{.data.admin-password}' kube-prometheus-stack-grafana | base64 --decode

Setup the root path for reverse proxy:
grafana:
  grafana.ini:
    server:
      root_url: http://0.0.0.0/grafana
      serve_from_sub_path: true
-->
$ helm repo add kube-prometheus-stack https://prometheus-community.github.io/helm-charts
$ helm install -n helm-charts kube-prometheus-stack kube-prometheus-stack/kube-prometheus-stack --set 'grafana.adminPassword=自定義默認密碼' --set 'grafana.grafana\.ini.server.root_url=http://0.0.0.0/grafana,grafana.grafana\.ini.server.serve_from_sub_path=true'

<!--
Nginx Ingress Controller

!!! attention Since version 1.9.0, "server-snippet" annotation is disabled by default and has to be explicitly enabled, see allow-snippet-annotations.
See https://github.com/kubernetes/ingress-nginx/blob/main/docs/user-guide/nginx-configuration/configmap.md#allow-snippet-annotations
-->
$ helm repo add ingress-nginx https://kubernetes.github.io/ingress-nginx
$ helm install -n helm-charts ingress-nginx ingress-nginx/ingress-nginx --set controller.allowSnippetAnnotations=true

<!--
Harbor
Harbor并未提供ARM64架構的鏡像，ARM平臺服務器不要使用Helm部署Harbor
-->
$ helm repo add harbor https://helm.goharbor.io
$ helm install -n helm-charts harbor harbor/harbor
```

升級Helm包與安裝類似，將`helm install`替換為`helm upgrade --install`，其它參數保持不變。
