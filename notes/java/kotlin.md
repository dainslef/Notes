<!-- TOC -->

- [REPL](#repl)

<!-- /TOC -->



# REPL
Kotlin自帶REPL，但功能較弱，無法與Scala、Haskell等成熟語言相比。

Kotlin官方提供了對Jupyter Notebook的支持[kotlin-jupyter](https://github.com/Kotlin/kotlin-jupyter)。
使用pip可直接進行安裝：

```
$ pip install kotlin-jupyter-kernel
```

在macOS下，使用Xcode提供的Python3時，
kotlin-jupyter-kernel被安裝到路徑`~/Library/Python/3.8/share/jupyter/kernels/kotlin`下，
而該路徑並不被macOS版本的jupyter識別，在macOS下，需要安裝到以下路徑之一：

```
~/Library/Jupyter/kernels
/usr/local/share/jupyter/kernels
```

安裝kotlin-jupyter-kernel到正確的位置：

```
$ jupyter kernelspec install ~/Library/Python/3.8/share/jupyter/kernels/kotlin
```

執行安裝指令成功後，kernel會被安裝到`/usr/local/share/jupyter/kernels/kotlin`路徑下，
但啟動依舊會存在問題，kernel的配置文件`kernel.json`內容如下：

```json
{
    "display_name": "Kotlin",
    "language": "kotlin",
    "interrupt_mode": "message",
    "argv": [
        "python",
        "-m",
        "run_kotlin_kernel",
        "{connection_file}"
    ]
}
```

該文件中配置的啟動參數使用了python指令(第6行)，但在macOS下，python指令默認啟動Python2，
因此會出現異常，修改啟動參數為python3即可正常啟動
