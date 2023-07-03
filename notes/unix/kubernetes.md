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
	- [kubectl配置](#kubectl配置)
		- [kubectl配置結構](#kubectl配置結構)
		- [kubectl關閉證書驗證](#kubectl關閉證書驗證)
- [集群架構](#集群架構)
	- [Node](#node)

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

## 官方源部署
在牆國之外或使用代理可直接訪問Google源環境的環境下，配置官方源：

```html
<!-- 導入倉庫籤名，Ubuntu 22.04 之後推薦將 key 放置在 /etc/apt/keyrings 路徑下 -->
# curl -fsSLo /usr/share/keyrings/kubernetes-archive-keyring.gpg https://packages.cloud.google.com/apt/doc/apt-key.gpg

<!-- 添加 Kubernetes 倉庫 -->
# echo "deb [signed-by=/usr/share/keyrings/kubernetes-archive-keyring.gpg] https://apt.kubernetes.io/ kubernetes-xenial main" > /etc/apt/sources.list.d/kubernetes.list
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

初始化集群時可設定各類參數（如calico插件需要使用`--pod-network-cidr=...`配置pod網段）。
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
[upgrade/prepull] You can also perform this action in beforehand using 'kubeadm config images pull'
[upgrade/apply] Upgrading your Static Pod-hosted control plane to version "v1.25.5" (timeout: 5m0s)...
[upgrade/etcd] Upgrading to TLS for etcd
[upgrade/staticpods] Preparing for "etcd" upgrade
[upgrade/staticpods] Renewing etcd-server certificate
[upgrade/staticpods] Renewing etcd-peer certificate
[upgrade/staticpods] Renewing etcd-healthcheck-client certificate
[upgrade/staticpods] Moved new manifest to "/etc/kubernetes/manifests/etcd.yaml" and backed up old manifest to "/etc/kubernetes/tmp/kubeadm-backup-manifests-2022-12-09-15-50-04/etcd.yaml"
[upgrade/staticpods] Waiting for the kubelet to restart the component
[upgrade/staticpods] This might take a minute or longer depending on the component/version gap (timeout 5m0s)
[apiclient] Found 1 Pods for label selector component=etcd
[upgrade/staticpods] Component "etcd" upgraded successfully!
[upgrade/etcd] Waiting for etcd to become available
[upgrade/staticpods] Writing new Static Pod manifests to "/etc/kubernetes/tmp/kubeadm-upgraded-manifests3205360824"
[upgrade/staticpods] Preparing for "kube-apiserver" upgrade
[upgrade/staticpods] Renewing apiserver certificate
[upgrade/staticpods] Renewing apiserver-kubelet-client certificate
[upgrade/staticpods] Renewing front-proxy-client certificate
[upgrade/staticpods] Renewing apiserver-etcd-client certificate
[upgrade/staticpods] Moved new manifest to "/etc/kubernetes/manifests/kube-apiserver.yaml" and backed up old manifest to "/etc/kubernetes/tmp/kubeadm-backup-manifests-2022-12-09-15-50-04/kube-apiserver.yaml"
[upgrade/staticpods] Waiting for the kubelet to restart the component
[upgrade/staticpods] This might take a minute or longer depending on the component/version gap (timeout 5m0s)
[apiclient] Found 1 Pods for label selector component=kube-apiserver
[upgrade/staticpods] Component "kube-apiserver" upgraded successfully!
[upgrade/staticpods] Preparing for "kube-controller-manager" upgrade
[upgrade/staticpods] Renewing controller-manager.conf certificate
[upgrade/staticpods] Moved new manifest to "/etc/kubernetes/manifests/kube-controller-manager.yaml" and backed up old manifest to "/etc/kubernetes/tmp/kubeadm-backup-manifests-2022-12-09-15-50-04/kube-controller-manager.yaml"
[upgrade/staticpods] Waiting for the kubelet to restart the component
[upgrade/staticpods] This might take a minute or longer depending on the component/version gap (timeout 5m0s)
[apiclient] Found 1 Pods for label selector component=kube-controller-manager
[upgrade/staticpods] Component "kube-controller-manager" upgraded successfully!
[upgrade/staticpods] Preparing for "kube-scheduler" upgrade
[upgrade/staticpods] Renewing scheduler.conf certificate
[upgrade/staticpods] Moved new manifest to "/etc/kubernetes/manifests/kube-scheduler.yaml" and backed up old manifest to "/etc/kubernetes/tmp/kubeadm-backup-manifests-2022-12-09-15-50-04/kube-scheduler.yaml"
[upgrade/staticpods] Waiting for the kubelet to restart the component
[upgrade/staticpods] This might take a minute or longer depending on the component/version gap (timeout 5m0s)
[apiclient] Found 1 Pods for label selector component=kube-scheduler
[upgrade/staticpods] Component "kube-scheduler" upgraded successfully!
[upgrade/postupgrade] Removing the old taint &Taint{Key:node-role.kubernetes.io/master,Value:,Effect:NoSchedule,TimeAdded:<nil>,} from all control plane Nodes. After this step only the &Taint{Key:node-role.kubernetes.io/control-plane,Value:,Effect:NoSchedule,TimeAdded:<nil>,} taint will be present on control plane Nodes.
[upload-config] Storing the configuration used in ConfigMap "kubeadm-config" in the "kube-system" Namespace
[kubelet] Creating a ConfigMap "kubelet-config" in namespace kube-system with the configuration for the kubelets in the cluster
[kubelet-start] Writing kubelet configuration to file "/var/lib/kubelet/config.yaml"
[bootstrap-token] Configured RBAC rules to allow Node Bootstrap tokens to get nodes
[bootstrap-token] Configured RBAC rules to allow Node Bootstrap tokens to post CSRs in order for nodes to get long term certificate credentials
[bootstrap-token] Configured RBAC rules to allow the csrapprover controller automatically approve CSRs from a Node Bootstrap Token
[bootstrap-token] Configured RBAC rules to allow certificate rotation for all node client certificates in the cluster
[addons] Applied essential addon: CoreDNS
[addons] Applied essential addon: kube-proxy

[upgrade/successful] SUCCESS! Your cluster was upgraded to "v1.25.5". Enjoy!

[upgrade/kubelet] Now that your control plane is upgraded, please proceed with upgrading your kubelets if you haven't already done so.
```

輸出`[upgrade/successful] SUCCESS! Your cluster was upgraded to "xxx". Enjoy!`則代表升級成功。
升級完成後，`kube-system`命名空間下的pods會被全部替換，
位於`/etc/kubernetes/manifests`路徑下的配置會替換為新版本，
同時舊的配置會被備份到`/etc/kubernetes/tmp`路徑下，
若對其中內容進行過修改，則應手動比較配置差異，重新添加配置。

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
- `kube-proxy` 管理節點的網絡規則（如iptables、ipvs等）
- `容器運行時（通常是containerd）` 用於運行容器

通常在集群中會存在多個Nodes，在某些資源受限或學習環境下，才會僅存在單個Node。

使用`kubectl get nodes`查看集群中的節點，示例：

```
$ kubectl get nodes
NAME  STATUS   ROLES           AGE   VERSION
xxx   Ready    control-plane   24d   v1.26.3
...
```
