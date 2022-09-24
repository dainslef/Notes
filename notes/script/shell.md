<!-- TOC -->

- [概述](#概述)
- [切換默認 Shell](#切換默認-shell)
- [Shell 交互](#shell-交互)
	- [調試信息](#調試信息)
	- [訪問歷史路徑](#訪問歷史路徑)
	- [匹配規則](#匹配規則)
	- [字符串截取](#字符串截取)
	- [任務管理](#任務管理)
	- [管道](#管道)
	- [重定向](#重定向)
	- [bash/zsh擴展重定向語法](#bashzsh擴展重定向語法)
		- [here-document](#here-document)
		- [here-string](#here-string)
		- [process-substitution](#process-substitution)
	- [標準輸入輸出](#標準輸入輸出)
- [Shell 語法](#shell-語法)
	- [變量](#變量)
		- [本地變量](#本地變量)
		- [環境變量](#環境變量)
		- [文本轉義](#文本轉義)
	- [指令](#指令)
	- [數組](#數組)
	- [數值計算](#數值計算)
	- [條件語法](#條件語法)
	- [if/switch/case (分支語法)](#ifswitchcase-分支語法)
	- [for/while (循環語法)](#forwhile-循環語法)
	- [select 語句](#select-語句)
	- [輸出內容](#輸出內容)
	- [自定義函數](#自定義函數)
	- [函數參數處理](#函數參數處理)
	- [函數返回值](#函數返回值)
- [其它 Shell 特性](#其它-shell-特性)
	- [隨機數](#隨機數)
	- [Fork Bomb](#fork-bomb)

<!-- /TOC -->



# 概述
Unix系統中的`Shell`一般指`CLI Shell`，提供了`CLI`方式的系統交互接口。
Shell本身是**指令解釋器**，將用戶輸入的指令轉換爲對OS的實際操作。

Unix系統中默認Shell可更換，不同的Unix使用的默認Shell亦不相同。

傳統Shell：

| 名稱 | 簡介 |
| :- | :- |
| `sh`(`Bourne Shell`) | 在`Version 7 Unix`中引入，其特性被之後的其它Shell作爲設計基礎 |
| `bash`(`Bourne-Again Shell`) | GNU項目的一部分，特性是`Bourne Shell`的超集，現代使用最廣汎的Shell，是`Linux`、`macOS`的默認Shell |
| `csh`(`C Shell`) | `BSD Unix`的默認Shell，採用類似`C`語言風格的語法 |
| `tcsh`(`TENEX C Shell`) | 基於`csh`，兼容`csh`，在`csh`基礎上添加了命令補全等特性，是`FreeBSD`的默認`Shell` |

現代Shell：

| 名稱 | 簡介 |
| :- | :- |
| `zsh`(`Z Shell`) | 兼容bash語法，同時提供更多強大功能 |
| `fish` | 智能、用戶友好的現代Shell，相比zsh擁有更多的內置特性與更現代化的設計。fish放棄了bash兼容性，使用全新設計的語法，更加簡潔、優雅 |



# 切換默認 Shell
更換默認Shell使用`chsh`指令，不同Unix中chsh指令的參數、效果不同。

- `Linux`中使用`chsh`會提示輸入新的默認Shell路徑
- `FreeBSD/macOS`中使用`chsh`會進入Shell的配置編輯界面

`/etc/shells`文件記錄了本機安裝的所有Shell，需要保證使用的Shell路徑已添加到該文件中。
macOS下使用`Homebrew`安裝fish不會更新`/etc/shells`文件，
需要手動將fish的路徑`/usr/local/bin/fish`添加到該文件中才能正常使用fish作爲默認Shell。



# Shell 交互
Shell中的常用組合鍵：

- `Ctrl + C` 停止當前指令(發送中斷信號`SIGINT`)
- `Ctrl + \` 停止當前指令(發送退出信號`SIGQUIT`)
- `Ctrl + D` 停止當前指令
- `Crtl + W` 刪除一段已輸入內容(到前一個空格爲止)
- `Ctrl + U` 清除所有已輸入內容

使用`!!`指令可以還原上一條輸入的指令(`bash/zsh`中支持該指令，`fish`不支持)：

```sh
$ ls
Applications	Documents	Library		Music		Public
Desktop		Downloads	Movies		Pictures
$ !!
ls
Applications	Documents	Library		Music		Public
Desktop		Downloads	Movies		Pictures
$ !! -l
ls -l
total 0
drwx------@  4 dainslef  staff   136 Aug 24 00:20 Applications
drwx------+  4 dainslef  staff   136 Aug 26 21:40 Desktop
drwx------+  5 dainslef  staff   170 Aug 20 00:38 Documents
drwx------+  6 dainslef  staff   204 Aug 26 17:31 Downloads
drwx------+ 61 dainslef  staff  2074 Aug 20 16:53 Library
drwx------+  3 dainslef  staff   102 Aug 19 22:05 Movies
drwx------+  5 dainslef  staff   170 Aug 19 23:55 Music
drwx------+  5 dainslef  staff   170 Aug 26 13:27 Pictures
drwxr-xr-x+  7 dainslef  staff   238 Aug 22 23:28 Public
```

使用`$?`可以獲取**上一條**指令的**執行結果**(`bash/zsh`中支持該指令，`fish`不支持)：

```sh
$ ls
Applications	Documents	Library		Music		Public
Desktop		Downloads	Movies		Pictures
$ echo $?
0 # 指令執行成功，返回 0
$ abc # 執行一條不存在的指令，執行失敗
bash: abc: command not found
$ echo $?
127 # 指令執行失敗，返回 127
```

## 調試信息
bash/zsh使用`-x`參數執行腳本時會輸出調試信息：

```
$ bash -x [bash腳本]
$ zsh -x [zsh腳本]
```

在bash腳本內容中，添加`set -v`，則會逐行輸出當前執行的指令內容，可搭配輸出分析腳本的執行情況。
示例腳本：

```bash
echo "test"
ls

set -v # 開啟指令輸出

echo "test"
ls
```

輸出結果；

```html
test
Applications    Documents       Library         Music           Public
Desktop         Downloads       Movies          Pictures        test.sh

<!-- 開啟 set -v 之後的輸出內容前會打印出執行的指令 -->
echo "test"
test
ls
Applications    Documents       Library         Music           Public
Desktop         Downloads       Movies          Pictures        test.sh
```

fish使用`-D`或`--debug-stack-frames`參數設定腳本調試級別，按調試級別輸出不同程度的調試信息：

```
$ fish -D [調試級別] [fish腳本]
$ fish --debug-stack-frames=[調試級別] [fish腳本]
```

fish默認的調適級別是`0`，通常使用`3`、`4`級別來獲取足夠的調適信息。
fish最大的調適級別可達`128`。

## 訪問歷史路徑
`zsh/fish`中均提供了查看歷史路徑的快捷指令。

在zsh中，使用`d`指令列出歷史路徑，使用**路徑編號**跳轉到編號對應路徑：

```sh
$ cd Downloads
$ d
0	~/Downloads
1	~

$ 1 # 使用編號作爲指令跳轉到對應路徑
~
```

在fish中，使用`dirh`指令列出歷史路徑，
使用`prevd 編號`跳轉到之前的指定路徑，使用`nextd 編號`跳轉到之後的指定路徑：

```sh
$ cd Downloads
$ dirh
 1) /Users/dainslef
	/Users/dainslef/Downloads

$ prevd 1 # 跳轉到之前的指定路徑
$ dirh
	/Users/dainslef
 1) /Users/dainslef/Downloads

$ nextd 1 # 跳轉到之後的指定路徑
$ dirh
 1) /Users/dainslef
	/Users/dainslef/Downloads
```

## 匹配規則
`Shell`中可使用以下**通配符**：

- `*` 匹配任意長度的字符串
- `?` 匹配任意單個字符
- `[]` 匹配一定範圍內的單個字符

示例：

```
*test* 匹配 xxxxtestxxxx 或 xtestxxxx 或 xxxxtestx 或 xtestx 等
?test? 匹配 xtestx ，但無法匹配 xxxxtestxxxx
test[1-9] 匹配 test1, test2 ... test9
```

對於一些需要輸入通配符原始字符的情形，需要使用`\`符號避免轉義。

## 字符串截取
使用`#*`/`##*`可字符串中抽取特定字符之後的內容：

```sh
file="path_a/path_b/abc.cde.hs"

${file#*/} # 獲取首個"/"之後的內容: path_b/abc.cde.hs
${file##*/} # 獲取最後一個"/"之後的內容: abc.cde.hs
${file#*.} # 獲取首個"."之後的內容: cde.hs
${file##*.} # 獲取最後一個"."之後的內容: hs
```

使用`%`/`%%`可從字符串中提取特定字符之前的內容：

```sh
file="path_a/path_b/abc.cde.hs"

${file#/*} # 獲取首個"/"之前的內容: path_a
${file##/*} # 獲取最後一個"/"之前的內容: path_a/path_b
${file#.*} # 獲取首個"."之前的內容: path_a/path_b/abc
${file##.*} # 獲取最後一個"."之前的內容: path_a/path_b/abc.cde
```

使用`${var:start:length}`可以自左向右獲取指定起始位置、指定長度的字符子串：

```sh
file="path_a/path_b/abc.cde.hs"

${file:7:6} # 從左邊第8個字符開始獲取之後的6個字符： path_b
${file:7} # 從左邊第8個字符開始獲取之後的所有字符： path_b/abc.cde.hs
```

使用`${var:0-start:0-length}`可以自右向左獲取字符子串：

```sh
file="path_a/path_b/abc.cde.hs"

${file:0-10} # 獲取最右端的10個字符：abc.cde.hs
${file:0-10:7} # 獲取最右的10個字符，從中自左向右截取7個字符： abc.cde
${file:0-10:0-2} # 獲取最右的10個字符，從中自右向左截取2個字符： hs
```

## 任務管理
指令後添加`&`操作符可以讓指令在後臺運行：

```
$ 指令 &
```

對於正在指令的指令，使用`Ctrl + Z`組合鍵可將指令暫停，並回到控制臺。
在後臺運行的指令與被暫停的指令可以使用`jobs`指令查看：

```
$ jobs
```

輸出結果(後臺運行`top`，`vim &`指令)：

```
Job	Group	State	Command
2	4099	stopped	top
1	4085	stopped	vim &
```

在後臺運行的任務會被分配任務編號。
使用`fg/bg`指令使在後臺掛起的指令恢復執行：

- `$ fg %[Job ID]` 恢復後臺指定編號的任務到前臺執行
- `$ bg %[Job ID]` 令指定編號的任務繼續在後臺執行

## 管道
Shell中的**管道**操作符`|`用於將一個進程的輸出作爲另一進程的輸入。

示例：

```sh
$ 指令1 | 指令2 | 指令3 | ...
```

管道操作符符`|`可多次連接指令。

使用`grep`指令過濾其它指令的輸出文本是最常見的管道應用：

```sh
$ ls | grep *abc* # 列出當前路徑下文件/路徑名稱中帶有 abc 字符的內容
```

`ls`指令的輸出作爲輸入內容傳入`grep`中。

## 重定向
默認情況下，進程執行的標準輸出、標準錯誤輸出均在終端內顯示。
使用`>`或`>>`操作符可以重定向輸出內容到文件中：

```sh
$ 指令 > 目標文件
$ 指令 >> 目標文件
```

- `>` 重定向輸出會覆蓋目標文件原有內容
- `>>` 重定向輸出以追加的形式添加到目標文件末尾

輸出重定向語法在bash/zsh/fish中基本相同。

標準輸入同樣支持重定向操作。
對於需要接收輸入內容的指令，使用`<`操作符可將輸入由標準輸入重定向到文件中：

```sh
$ 指令 < 目標文件
```

## bash/zsh擴展重定向語法
對於bash/zsh，輸入重定向額外支持`<<`以及`<<<`語法、`< <(...)`語法。

### here-document
`<<`語法被稱為`here-document`，用於在命令行開啟一個支持多行輸入的文檔，
`<<`操作符後需要指定**文檔結束標誌**：

```
$ 指令 << 結束標誌
> ...
> ...
> 結束標誌
```

實例：

```html
<!-- 設置結束標誌為 END -->
$ grep abc << END
> abc
> cde
> END <!-- 接收到結束標誌，文檔結束 -->
abc

<!-- 等價指令
假設文件 input.txt 中存在如下內容：
abc
cde
-->
$ grep abc < input.txt
abc
```

`<<`操作效果近似於創建一個文檔，輸入內容後將指令的標準輸入重定向到該文檔。
fish中**不支持**here-document語法。

### here-string
`<<<`語法被稱為`here-string`，該操作符將直接傳入文本內容，而不是文件作為重定向的輸入。

實例：

```
$ grep abc <<< abcdef
abcdef
```

fish中**不支持**here-string語法，但該語法可簡單地使用管道操作符替代：

```
$ echo abcdef | grep abc
```

### process-substitution
[`process-substitution`](http://mywiki.wooledge.org/ProcessSubstitution)(進程替換)是bash/zsh的擴展功能。
作用類似`command1 | command2`形式的管道操作，但可於避免管道操作引起的子Shell問題
(在循環中使用管道會創建大量子Shell，產生較大開銷，例如經典的fork炸彈)。

process substitution存在兩種形式：

- `<(command...)` 將指定進程的執行結果重定向到臨時FD中作為其它進程的輸入
- `>(command...)` 將其它進程的執行結果作為指定進程的輸入

兩種操作均會在`/tmp`或`/var/tmp`下創建`named pipes`(FIFO，命名管道)或`named file descriptor`(FD，命名文件描述)，
實際差異取決於操作系統的實現。

process substitution read語法可轉換為對FIFO或FD的操作。
有如下語法：

```
$ command1 <(command2) <(command3)
```

近似等價於：

```
$ mkfifo /var/tmp/fifo1 /var/tmp/fifo2
$ command2 > /var/tmp/fifo1 &
$ command3 > /var/tmp/fifo2 &
$ command1 /var/tmp/fifo1 /var/tmp/fifo2
$ rm /var/tmp/fifo1 /var/tmp/fifo2
```

以macOS下的zsh為例，使用`md5`計算兩個文件的md5值：

```c
// 文件內容：
// abc.txt: abc\n
// cde.txt: cde\n
$ md5 <(cat abc.txt) <(cat cde.txt)
MD5 (/dev/fd/11) = 0bee89b07a248e27c83fc3d5951213c1
MD5 (/dev/fd/12) = 7f4d13d9b0b61c086fd68637067435c5
```

可以看到，macOS下使用process substitution語法在`/dev/fd`下創建了兩個臨時FD，
從臨時FD中讀取了數據。

process substitution read常搭配標準重定向操作，構成類似雙括號的語法：

```
$ command1 > >(command2)
```

功能為先執行commnad1指令，command2讀取command1的執行結果作為輸入並執行；
功能近似於`command1 | command2`，但避免了子Shell的創建。

process substitution write常見用法如下所示：

```
$ commnad1 > >(command2)
```

功能為先執行commnad1指令，command2讀取command1的執行結果作為輸入並執行。

## 標準輸入輸出
Shell環境下標準輸入輸出存在默認編號：

| 輸入輸出類型 | 編號 |
| :- | :-: |
| `STDIN_FILENO`(標準輸入) | 0 |
| `STDOUT_FILENO`(標準輸出) | 1 |
| `STDERR_FILENO`(標準錯誤輸出) | 2 |

使用編號搭配重定向操作符可實現重定向指定類型的輸出。
僅重定向錯誤輸出到目標文件：

```sh
$ 指令 2> 目標文件
```

使用`>&`操作符可連接兩個描述符，如連接標準錯誤輸出至標準輸出：

```sh
$ 指令 2>&1
```

連接描述符的`>&`操作符應置於整條指令的**末尾**。

示例：

以`ls`指令爲例，假設當前路徑下**不存在**`xxx`文件，
使用`ls xxx`指令時會得到錯誤輸出，提示文件不存在：

```sh
$ ls xxx
ls: xxx: No such file or directory
```

- 重定向指定類型輸出：

	可將錯誤輸出到`error.txt`文件中：

	```sh
	$ ls xxx 2> error.txt # 指令在終端無輸出
	$ cat error.txt # 錯誤信息被重定向到 error.txt 文件中
	ls: xxx: No such file or directory
	```

	錯誤信息在標準錯誤輸出中生成，重定向標準輸出到文件`error.txt`，終端依舊會出現錯誤信息，
	而`error.txt`文件內容爲空：

	```sh
	$ ls xxx 1> error.txt # 重定向標準輸出
	ls: xxx: No such file or directory # 錯誤信息依舊輸出到終端，error.txt 文件中內容爲空
	```

- 連接描述符：

	將標準錯誤輸出連接到標準輸出，則重定向標準輸出終端不會出現錯誤信息：

	```sh
	$ ls xxx 1> error.txt 2>&1 # 終端無輸出
	$ cat error.txt # 錯誤信息被重定向到 error.txt 文件中
	ls: xxx: No such file or directory
	```



# Shell 語法
Unix中，Shell腳本通常以`sh`作爲後綴名(`bash/zsh`等)。
fish由於不兼容bash語法，通常使用`fish`作爲腳本後綴。

腳本首行需要聲明使用的解析器，以zsh爲例：

```sh
#! /bin/zsh
...
```

使用`./***.sh`執行腳本時，已指定解析器的腳本會調用指定的解析器進行介些，
未指定解析器的腳本會使用默認的Shell解析。

## 變量
bash/zsh變量相關語法基本相同，fish與其有較大差異。

定義、修改變量：

- `變量名=值` 定義變量，`bash/zsh`語法，但等號兩邊**不能**帶有空格
- `set 變量名 內容` 定義變量，`fish`語法
- `變量名+=內容` 向變量添加內容，`bash/zsh`語法，`fish`不支持該操作

示例：

```sh
# bash/zsh
$ num=233 # 定義變量 num
$ echo $num # 訪問變量 num
233 # 輸出變量內容 233
$ num+=1 # 拼接文本 233 和 1
$ echo $num
2331 # 輸出 2331

# fish
$ set num 233
$ echo $num # 輸出 233
$ num+=1
$ echo $num
233 # fish 不支持 += 操作，輸出結果未發生改變
```

查看、刪除已定義的變量：

- `$變量名` 獲取變量內容
- `set` 列出已定義的變量
- `unset 變量名` 刪除指定名稱的變量(bash/zsh語法)
- `set -e 變量名` 刪除指定名稱的變量(fish語法)

### 本地變量
Shell中修改變量與定義變量語法相同，需要使用額外的作用域關鍵字區分訪問外部變量或是新定義本地變量。

bash/zsh中使用`local`關鍵字定義**本地變量**。
本地變量與外部變量重名時，本地變量僅在作用域內部生效：

```sh
num=1

setValue() {
	num=2 # 直接使用變量名相當於修改外部變量
}

setLocalValue() {
	local num=3 # 使用 local 關鍵字修飾，創建本地變量，不影響外部變量的值
}

echo $num
setValue
echo $num
setLocalValue
echo $num
```

輸出結果：

```
1
2
2
```

bash中本地變量僅能在函數中定義。
zsh擴展了local關鍵字的用法，可以在任意區域使用local關鍵字定義變量，
使用local定義的變量之前若存在非local形式的定義，則隱藏之前的定義而非改寫其值。

fish中使用`set`函數定義變量，使用`set -l`定義**本地變量**。

### 環境變量
**環境變量**(environment variable)是Unix系統中的一類全局配置，部分程序會通過讀取環境變量改變自身行為。
在bash/zsh/fish中，均可使用`export`指令設置環境變量：

```sh
$ export [key]=[value]
```

export指令由對應的Shell提供，以fish為例，fish中的export指令實際上是一個函數，
對應代碼在macOS下位於`/usr/local/Cellar/fish/[version]/share/fish/functions/export.fish`。

```fish
function export --description 'Set env variable. Alias for `set -gx` for bash compatibility.'
	if not set -q argv[1]
		set -x
		return 0
	end
	for arg in $argv
		set -l v (string split -m 1 "=" -- $arg)
		switch (count $v)
			case 1
				set -gx $v $$v
			case 2
				if contains -- $v[1] PATH CDPATH MANPATH
					set -l colonized_path (string replace -- "$$v[1]" (string join ":" -- $$v[1]) $v[2])
					set -gx $v[1] (string split ":" -- $colonized_path)
				else
					# status is 1 from the contains check, and `set` does not change the status on success: reset it.
					true
					set -gx $v[1] $v[2]
				end
		end
	end
end
```

由源碼可知，fish中的export函數實際上最終使用了`set -gx`指令設置環境變量。

### 文本轉義
在bash/zsh中使用單引號語法`'`包裹的文本中`$變量`語法不會被解析為對應變量的取值，
而是直接被作為純文本處理：

```sh
$ arg=123
$ echo 'arg: $arg'
arg: $arg
```

使用雙引號`"`語法包裹的文本中，`$變量`語法會被解析對應變量的取值：

```sh
$ arg=123
$ echo "abc: $arg"
abc: 123
```

## 指令
執行指令，語法如下：

- `$(指令)` 執行指令(`bash/zsh`語法)
- `(指令)` 執行指令(`fish`語法)

## 數組
`bash/zsh/fish`數組相關語法均存在一定差異。

定義數組：

- `數組名=(內容1 內容2 內容3 ...)` 定義數組，多個數組內容間使用**空格**隔開(`bash/zsh`語法)
- `set 數組名 內容1 內容2 內容3 ...` 定義數組，多個數組內容間使用**空格**隔開(`fish`語法)

示例：

```sh
# bash/zsh
$ nums=(1 2 3) # 定義數組，包含3個元素： 1 2 3

# fish
$ set nums 1 2 3
```

訪問數組內容：

- `$數組名` 訪問數組名返回數組內**首個**元素(bash語法)，或返回**整個**數組(zsh/fish語法)
- `$數組名[索引]` 訪問數組指定索引的內容，支持**逆序**索引(zsh/fish語法)
- `$數組名[起始索引..結束索引]` 數組切片，訪問從起始索引到結束索引之間的內容(fish特性)
- `$((數組名[索引]))`/`$[數組名[索引]]`/`${數組名[索引]}` 訪問數組指定索引的內容(bash/zsh語法)

bash中，數組索引從`0`開始；zsh/fish中，數組索引從`1`開始。

獲取數組長度：

- `${#數組名[@]}` 數組長度(bash/zsh語法)
- `$[#數組名[@]]` 數組長度(bash/zsh語法)
- `count 數組名` 數組長度(fish語法)

向數組添加內容：

- `數組名[${#數組名[@]}]=取值`（bash/zsh語法）
- `set -a 數組名 內容` 向數組尾部添加內容（fish語法）
- `set -p 數組名 內容` 向數組頭部添加內容（fish語法）

從數組內移除內容（從指定索引開始，生成原數組的子集）：

- `${數組名[@]:索引}`（bash/zsh語法）
- `$數組名[索引..]`（fish語法）

示例：

```sh
# bash
$ nums=(1 2 3)
$ echo $nums
1 # bash中數組名代表數組內首個元素
$ echo $((nums[0]))
1
$ echo $[nums[1]]
2
$ echo ${nums[2]}
3
$ echo ${nums[3]}
 # 無輸出內容(數組越界)
$ echo $nums[2]
1[2] # bash不支持直接使用數組名後添加索引訪問數組內容，"$數組名"被解析爲數組首個元素

# zsh
$ nums=(1 2 3)
$ echo $nums
1 2 3 # zsh中數組名代表數組內所有內容
$ echo $((nums[0]))
0 # zsh數組下標從1開始，數組越界
$ echo $[nums[1]]
1
$ echo ${nums[2]}
2
$ echo $nums[3]
3
$ echo $nums[-1]
3 # zsh支持逆序索引

# fish
$ set nums 1 2 3
$ echo $nums
1 2 3 # fish中數組名代表數組內所有內容
$ echo $nums[-1]
3 # fish支持逆序索引
$ echo $nums[2..3]
2 3 # fish支持數組切片
$ echo $nums[0] # fish數組下標從1開始，數組越界
fish: Array index out of bounds
echo $nums[0]
		   ^
$ echo $nums[1]
1
$ echo $[nums[1]] # 報錯，fish不支持bash/zsh中的數組訪問語法
fish: $[ is not a valid variable in fish.
echo $[nums[1]]
	  ^
$ echo ${nums[1]} # 報錯，fish不支持bash/zsh中的數組訪問語法
fish: ${ is not a valid variable in fish.
echo ${nums[1]}
	  ^
```

## 數值計算
對於算術表達式，`bash/zsh`默認作爲文本處理。
即`echo 2+3`爲輸出內容爲`2+3`的文本。

示例：

```sh
# bash/zsh
$ num=233
$ echo $num+1
233+1 # 輸出文本 233+1

# fish
$ set num 233
$ echo $num+1
233+1
```

求值計算表達式，語法如下：

- `$((表達式))`/`$[表達式]` (`bash/zsh`語法)
- `expr 表達式` (`bash/zsh`語法)
- `math 表達式` (`fish`語法)

```sh
# bash/zsh
$ num=233
$ echo $(($num+1))
234 # 輸出 234
$ echo $[$num+1]
234
$ echo $[$num*10]
2330

# fish
$ set num 233
$ echo (math $num+1)
234
$ echo (math $num\*10) # fish 中乘法運算需要使用反斜槓轉義 * 符號
2330
$ echo (math "$num * 10") # 亦可將計算表達式以文本形式傳入，則不需要轉義字符
2330
```

## 條件語法
`test`函數用於條件檢驗，使用`test 條件`來檢驗一個條件是否成立。

`[ 條件 ]`語法是`test 條件`的語法糖，作用類似。
`[ 條件 ]`語法中，條件內容需要與`[]`符號兩邊各保持一個空格以上的間距，否則語法解析出錯。

示例：

```sh
if [ 條件 ]; then # 正確
	...
fi

if [條件]; then # 錯誤
	...
fi
```

否定條件的語法是在條件運算符之前添加感嘆號`!`，
與條件語法類似，否定語法同樣需要與條件語法保持一個空格以上的間距，否則語法解析出錯。

示例：

```sh
if ! [ 條件 ]; then # 正確
	...
fi

if ![ 條件 ]; then # 錯誤
	...
fi
```

`[ 條件 ]`用於**字符**判斷：

- `[ 字符1 = 字符2 ]` 字符相同
- `[ 字符1 != 字符2 ]` 字符不同
- `[ -z 字符 ]` 字符爲空
- `[ -n 字符 ]` 字符非空

`[ 條件 ]`用於**數值**比較：

- `[ 數值1 -lt 數值2 ]` 數值1**小於**數值2
- `[ 數值1 -le 數值2 ]` 數值1**小於等於**數值2
- `[ 數值1 -gt 數值2 ]` 數值1**大於**數值2
- `[ 數值1 -ge 數值2 ]` 數值1**大於等於**數值2
- `[ 數值1 -eq 數值2 ]` 數值1**等於**數值2
- `[ 數值1 -ne 數值2 ]` 數值1**不等於**數值2

`[ 條件 ]`用於**文件**判斷：

- `[ -e 文件 ]` 文件已經存在
- `[ -f 文件 ]` 文件是普通文件
- `[ -s 文件 ]` 文件大小不爲零
- `[ -d 文件 ]` 文件是一個目錄
- `[ -r 文件 ]` 文件對當前用戶可以讀取
- `[ -w 文件 ]` 文件對當前用戶可以寫入
- `[ -x 文件 ]` 文件對當前用戶可以執行
- `[ -g 文件 ]` 文件的`GID`標誌被設置
- `[ -u 文件 ]` 文件的`UID`標誌被設置
- `[ -O 文件 ]` 文件是屬於當前用戶的
- `[ -G 文件 ]` 文件的組`ID`和當前用戶相同
- `[ 文件1 -nt 文件2 ]` **文件1**比**文件2**更**新**
- `[ 文件1 -ot 文件2 ]` **文件1**比**文件2**更**老**

## if/switch/case (分支語法)
分支語法包括：

- `if`語句(`bash/zsh/fish`語法)
- `case`語句(`bash/zsh`語法)
- `switch`語句(`fish`語法)

`if`分支結構語法：

```sh
# bash/zsh 分支語法
if [ 條件1 ]
then
	...
elif [ 條件2 ]
then
	...
else
	...
fi

# 多個條件可以使用邏輯運算符連接
if [ 條件1 ] && [ 條件2 ] || [ 條件3 ]; then
fi

# fish 分支語法更近似現代語言
if [ 條件1 ]
	...
else if [ 條件2 ]
	...
else
	...
end
```

模式匹配語法：

```sh
# bash/zsh 使用 case 語句進行模式匹配
case ... in
	xxx1) # 匹配內容則跳轉到指定分支
		... ;; # 語句塊結束使用雙分號 ;;
	xxx1 | xxx2) # 多條件使用 | 操作符連接，滿足匹配內容的其中一個即可
		... ;;
	*) # 沒有匹配到內容跳轉到默認分支
		... ;;
esac

# fish 使用 switch 語句進行模式匹配
switch ...
	case xxx1
		...
	case xxx2 xxx3
		...
	case '*'
		...
end
```

## for/while (循環語法)
`for/while`用於重複執行某段邏輯。

bash/zsh的`for`語法：

```sh
# 傳統C風格循環
for ((變量名=數值; 變量名<=數值; 變量名++)); do
	...
done

# 基於列表遍歷的循環
for 變量名 in {起始值..結束值}; do
	...
done

# zsh 支持列表遍歷語法
# bash 4.0 之後支持設定遍歷間隔
for 變量名 in {起始值..結束值..間隔}; do
	...
done

# 使用 seq 函數列表進行遍歷
for 變量名 in $(seq 起始值 結束值); do
	...
done

for 變量名 in $(seq 起始值 間隔 結束值); do
	...
done

# 無限循環
for ((;;)); do
	...
done
```

`macOS 10.12.6`默認的`bash`版本爲`3.2.57`，使用列表遍歷語法時不支持設定間隔(`zsh`支持此語法)。

fish的`for`語法：

```fish
# fish 僅支持列表遍歷循環，使用 seq 函數構建列表
for 變量 in (seq 起始值 結束值)
	...
end

# seq 函數可構建帶有間隔的循環
for 變量 in (seq 起始值 間隔 結束值)
	...
end
```

除了`for`語句，亦可使用`while`構建循環。
`while`語句語法：

```sh
# bash/zsh
while [ 條件 ]; do
	...
done

# fish
while [ 條件 ]
	...
end

# fish 無限循環
while true
	...
end
```

實例，打印`1~10`範圍的數值：

```sh
# bash/zsh C風格
for ((i=0; i<=10; i++)); do
	echo $i
done

# bash/zsh 列表遍歷
for i in {1..10}; do
	echo $i
done

# bash/zsh while語句
i=1
while [ i -le 10 ]; do
	echo $i
	i=$[$i+1]
done

# fish for語句
for i in (seq 1 10)
	echo $i
end

# fish while語句
set i 1
while [ $i -le 10 ]
	echo $i
	set i (math $i+1)
end
```

## select 語句
`select`語句用於在Shell環境中提供選擇菜單。
bash/zsh中select結構語法：

```sh
select $xxx in "xxx1" "xxx2"; do # 提供選單，提示用戶在選項 xxx1 xxx2 中進行選擇
	...
	break # 執行邏輯後需要使用 break 終止 select 結構，否則會一直循環出現選單
done
```

fish中沒有提供select結構同等的語法。

## 輸出內容
Shell中使用`echo`函數用於向標準輸出(`stdout`)打印文本，
類似於高級語言中的`print()`函數。

echo函數可選參數：

- `-e` 轉義文本
- `-n` 不打印換行符

不同Shell對於轉義字符的默認處理方式不同。
對於使用**引號**(`'`或`"`)包含的文本：

- bash/fish默認不處理轉義字符，將轉義字符作爲普通文本輸出
- zsh默認處理轉義字符，相當於使用`echo -e`指令

對於普通文本(文本不使用引號包含，直接作爲參數)：

- bash/zsh默認忽略轉義字符，並且輸出的文本中不包含轉義符號`\`
- fish默認處理轉義字符，相當於使用`-e`參數

示例：

```sh
# bash
$ echo abc\n
abcn # bash 普通文本轉義字符被忽略
$ echo 'abc\n'
abc\n # bash 使用引號轉義字符被作爲普通文本輸出
$ echo -e 'abc\n'
abc
 # 轉義字符有效，正常輸出換行符

# zsh
$ echo abc\n
abcn # 忽略、隱藏轉義字符
$ echo 'abc\n'
abc
 # zsh 使用引號正常輸出轉義字符
$ echo -e 'abc\n'
abc
 # 轉義字符有效，正常輸出換行符

# fish
$ echo abc\n
abc
 # 轉義字符有效，正常輸出換行符
$ echo 'abc\n'
abc\n # fish 使用引號，轉義字符被視爲普通文本輸出
$ echo -e 'abc\n'
abc
 # 轉義字符有效，正常輸出換行符
```

## 自定義函數
函數用於封裝一段需要重複調用的邏輯。

定義函數語法：

```sh
# bash/zsh
function 函數名() {
	...
	return 返回值
}

# bash/zsh 定義函數 function 關鍵字可以省略
函數名() {
	...
	return 返回值
}

# fish
function 函數名
	...
	return 返回值
end
```

## 函數參數處理
bash/zsh/fish調用函數語法類似：

```sh
函數名 參數1 參數2 參數3 ... # 調用函數傳參不使用括號
```

bash/zsh的函數參數處理：

- `$#` 獲取參數的數目
- `$@` 獲取參數列表
- `$1 ~ $9` 獲取函數參數內容，最大支持9個參數
- `$?` 獲取上一個執行函數的返回值
- `shift` 對於數量超過9個的參數表，使用shift指令從左邊移走參數，以訪問更多參數

示例：

```sh
show() {
	echo "Args count: " $#
	echo "Arg 1:" $1
	echo "Arg 2:" $2 "\n"
	echo "All args:"
	for arg in $@; do
		echo $arg
	done
}

# 調用函數
show 1 2 3 4 5 6 7 8
```

輸出結果：(`macOS 10.12.6` && `bash 3.2.57` && `zsh 5.2`)

```
Args count:  8
Arg 1: 1
Arg 2: 2

All args:
1
2
3
4
5
6
7
8
```

bash/zsh的參數獲取語法與序列生成語法組合使用時，參數獲取語法不會被解析：

```sh
test() {
	for i in {$1..$2}; do
		echo i: $i
	done
}

test 1 10
# 輸出結果：
# i: {1..10}
```

若需要函數參數獲取與序列生成語法正確搭配，應使用`seq`函數：

```sh
test() {
	for i in $(seq $1 $2); do
		echo i: $i
	done
}

test 1 10
# 輸出結果：
# i: 1
# i: 2
# i: 3
# i: 4
# i: 5
# i: 6
# i: 7
# i: 8
# i: 9
# i: 10
```

fish的函數參數處理：

- `argv` fish使用列表`argv`保存傳入函數的參數
- `count argv` 獲取參數的數目
- `$argv[索引]` 獲取指定索引的參數

示例：

```fish
function show
	echo "Args count: " (count argv)
	echo "Arg 1:" $argv[1]
	echo "Arg 2:" $argv[2] \n
	echo "All args:"
	for arg in $argv
		echo $arg
	end
end

# 調用函數
show 1 2 3 4 5 6 7 8
```

輸出結果：(`macOS 10.12.6` && `fish 2.6.0`)

```
Args count:  8
Arg 1: 1
Arg 2: 2

All args:
1
2
3
4
5
6
7
8
```

## 函數返回值
在bash/zsh中，函數可以使用`return`關鍵字返回一個範圍在`0~255`範圍的值。
使用函數執行語法得到的得到的結果並不是函數的返回值，而是函數執行期間輸出的內容：

```sh
$ show() { echo "abc"; echo "cde"; return 1; }
$ show
abc
cde
$ result=`show`
$ echo $result
abc cde
```

獲取函數的返回值需要使用`$?`語法，該語法會獲取最近一次執行的函數的返回值：

```sh
$ show
abc
cde
$ echo $?
1
```

在fish中，函數返回值規則類似，但fish中使用`$status`語法訪問最近執行函數的返回值：

```sh
$ function show
    echo abc
    echo cde
    return 1
end
$ set result (show)
$ echo $result
abc cde
$ show
abc
cde
$ echo $status
1
```



# 其它 Shell 特性
Shell中的一些常用功能。

## 隨機數
bash/zsh/fish均內置了生成隨機數的功能。

- bash/zsh中通過訪問`RANDOM`變量獲取隨機數：

	```sh
	$ $[$RANDOM%隨機數範圍]
	```

	`$RANDOM`返回**0~32767**，執行取餘計算可得到指定範圍範圍的隨機數。

- fish通過`random`函數獲取隨機數：

	```fish
	$ random 隨機數起始範圍 隨機數結束範圍
	```

	`random`函數輸入隨機數的起止範圍作爲參數。

## Fork Bomb
`Fork Bomb`(**Fork炸彈**)是bash/zsh中存在的經典惡意腳本：

```sh
:(){ :|:& };:
```

或者：

```sh
.(){ .|.& };.
```

Fork炸彈利用bash/zsh中簡短的函數語法，使用符號`:`或`.`作爲函數名，在函數體中遞歸調用自身。
函數正常的寫法如下：

```sh
:() { # 定義函數
	: | :& # 函數體內部遞歸併通過管道創建新進程在後台運行
};
: # 調用函數
```

函數體中使用了**管道**特性，在每次遞歸時會同時創建新的進程在後臺運行。
隨着遞歸次數的增加，進程數會以指數級增加，最終消耗光所有的系統資源。

Fork炸彈在其它Shell中並不有效，如fish中函數需要使用`function/end`關鍵字定義，代碼不具有迷惑性；
而csh/tcsh中不支持函數。
