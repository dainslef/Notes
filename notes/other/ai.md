<!-- TOC -->

- [GPU驅動](#gpu驅動)
    - [AMD GPU驅動](#amd-gpu驅動)
    - [NVIDIA GPU驅動](#nvidia-gpu驅動)
    - [Vulkan驅動](#vulkan驅動)
    - [TTM](#ttm)
- [Ollama](#ollama)
    - [Ollama Linux部署](#ollama-linux部署)
    - [Ollama運行模式](#ollama運行模式)
    - [Ollama操作說明](#ollama操作說明)
    - [Ollama配置](#ollama配置)
    - [Ollama數據存儲](#ollama數據存儲)
    - [Ollama容器化部署](#ollama容器化部署)

<!-- /TOC -->



# GPU驅動
儘管AI模型支持通過CPU運行，但GPU加速能顯著提升模型執行效率，
啟用GPU加速需要正確安裝和配置GPU驅動。

AMD/NVIDIA GPU有各自的專屬驅動與GPU加速，較新的GPU共同支持Vulkan加速。

## AMD GPU驅動
AMD GPU需要安裝[ROCm驅動](https://github.com/ROCm/ROCm)。

## NVIDIA GPU驅動
NVIDIA GPU需要安裝[CUDA驅動](https://developer.nvidia.com/cuda-downloads)。

## Vulkan驅動
較新的AMD/NVIDIA GPU均支持Vulkan加速，Vulkan配置較為簡單，啟用Vulkan加速僅需要標準的開源驅動，
主流Linux發行版的開源驅動已包含Vulkan支持，確保系統安裝了Mesa驅動即可。

與專屬GPU加速相比，部分模型在Vulkan加速下的性能有所下降，亦有部分模型在Vulkan加速下的性能更好，
不同模型建議分別測試專屬GPU加速與Vulkan加速的性能表現，以選擇最佳的加速模式。

## TTM
`TTM(Translation Table Manager)`是Linux內核中的內存管理子系統，負責管理GPU內存的分配和映射。

對於核心顯卡，可通過在GRUB/systemd-boot的`ttm`相關配置參數可調整GPU使用的內存比例：

```html
<!-- GRUB配置位於 /etc/default/grub -->
GRUB_CMDLINE_LINUX_DEFAULT="... ttm.pages_limit=xxx ttm.page_pool_size=xxx"

<!-- systemd-boot配置通常位於 /boot/loader/entries/*.conf -->
options ... ttm.pages_limit=xxx ttm.page_pool_size=xxx
```

TTM數值大小計算方式：

```
內存GB數 × 1024 × 1024 / 4
```

以8GB內存為例，TTM數值大小為：

```
8 × 1024 × 1024 / 4 = 2097152
```



# Ollama
[Ollama](https://github.com/ollama/ollama)項目提供了各類開源語言模型的快速本地部署。

Ollama支持Windows/macOS/Linux等主流操作系統，Windows/macOS系統下直接從官網下載安裝包即可。

## Ollama Linux部署
Linux系統使用腳本部署：

```
# curl -fsSL https://ollama.com/install.sh | sh
```

部署完成後，Ollama會創建systemd服務，並在`/usr/local/bin`路徑下安裝ollama工具。

牆國推薦使用離線部署，[Ollama GitHub Release](https://github.com/ollama/ollama/releases)
提供了常見平臺的完整離線包（不包含模型）。

## Ollama運行模式
Ollama在部署過程中會檢測服務器硬件，若存在NVIDIA/AMD顯卡，
則以GPU模式運行（GPU模式需要正確配置顯卡驅動），否則以CPU模式運行。

Ollama支持多種GPU加速後端，默認使用平台專屬的加速模式，NVIDIA GPU使用CUDA，AMD GPU使用ROCm。
Ollama亦實驗性提供了Vulkan加速，通過環境變量`OLLAMA_VULKAN=1`啟用Vulkan加速。

## Ollama操作說明
ollama指令操作說明：

```html
# ollama serve <!-- 啟動服務（通常使用systemctl管理服務） -->
# ollama ls/list <!-- 列出已下載的模型 -->
# ollama pull 模型名稱 <!-- 拉取指定模型，可從 https://ollama.com/search 查找支持的模型 -->
# ollama run/stop 模型名稱 <!-- 啟動/停止模型 -->
```

## Ollama配置
Ollama通過配置環境變量來控制部分配置，常用環境變量：

```ini
OLLAMA_HOST=0.0.0.0:11434 # 監聽地址
OLLAMA_ORIGINS=* # 允許跨域訪問
OLLAMA_KEEP_ALIVE=-1 # 模型運行時間限制
```

Ollama使用systemd管理服務，直接配置在系統中的環境變量**不生效**，需要添加到服務文件中；
修改`/etc/systemd/system/ollama.service`文件：

```ini
...
[Service]
# 默認 Ollama
Environment="OLLAMA_HOST=0.0.0.0:11434 OLLAMA_ORIGINS=* OLLAMA_KEEP_ALIVE=-1"
...
```

## Ollama數據存儲
Linux平臺下，Ollama會將模型數據存儲至`/usr/share/ollama/.ollama/models`路徑下。

## Ollama容器化部署
Ollama支持容器部署，參考[Ollama博客](https://ollama.com/blog/ollama-is-now-available-as-an-official-docker-image)。

Ollama官方提供了[Docker鏡像](https://hub.docker.com/r/ollama/ollama)，使用以下命令拉取：

```html
# docker pull ollama/ollama <!-- 通用鏡像 -->
# docker pull ollama/ollama:rocm <!-- AMD GPU若使用rocm加速則需要搭配rocm標籤的鏡像 -->
```

以各自平台的GPU加速模式運行容器：

```html
<!-- Nvidia GPU 需要安裝 Nvidia container toolkit -->
# docker run -d -v ollama:/root/.ollama -p 11434:11434 --gpus=all --name ollama ollama/ollama
<!-- AMD GPU 需要掛載特定設備文件 -->
# docker run -d -v ollama:/root/.ollama -p 11434:11434 --device=/dev/kfd --device=/dev/dri --gpus=all --name ollama ollama/ollama:rocm
```

以Vulkan加速模式運行容器：

```html
<!--
通過環境變量 OLLAMA_VULKAN=1 啟用Vulkan加速
即便是AMD GPU，使用Vulkan加速亦需要使用通用鏡像
-->
# docker run -d -v ollama:/root/.ollama -e OLLAMA_VULKAN=1 -p 11434:11434 --device=/dev/kfd --device=/dev/dri --gpus=all --name ollama ollama/ollama
```
