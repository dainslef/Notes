<!-- TOC -->

- [Ollama](#ollama)
    - [Ollama Linux部署](#ollama-linux部署)
    - [Ollama操作說明](#ollama操作說明)
    - [Ollama配置](#ollama配置)
    - [Ollama數據存儲](#ollama數據存儲)

<!-- /TOC -->



# Ollama
[Ollama](https://github.com/ollama/ollama)項目提供了各類開源語言模型的快速本地部署。

Ollama支持Windows/macOS/Linux等主流操作系統，Windows/macOS系統下直接從官網下載安裝包即可。

## Ollama Linux部署
Linux系統使用腳本部署：

```
# curl -fsSL https://ollama.com/install.sh | sh
```

Ollama在部署過程中會檢測服務器硬件，若存在NVIDIA/AMD顯卡，則以GPU模式運行，否則以CPU模式運行；
部署完成後，Ollama會創建systemd服務，並在`/usr/local/bin`路徑下安裝ollama工具。

牆國推薦使用離線部署，[Ollama GitHub Release](https://github.com/ollama/ollama/releases)
提供了常見平臺的完整離線包（不包含模型）。

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
