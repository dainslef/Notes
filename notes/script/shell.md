<!-- TOC -->

- [简介](#简介)
- [切换默认 *Shell*](#切换默认-shell)
- [*Shell* 交互](#shell-交互)
	- [匹配规则](#匹配规则)
	- [任务管理](#任务管理)
	- [管道](#管道)
	- [重定向](#重定向)
	- [标准输入输出](#标准输入输出)
- [*Shell* 语法](#shell-语法)
	- [变量](#变量)
	- [指令](#指令)
	- [数组](#数组)
	- [条件语法](#条件语法)
	- [*if* / *switch* / *case* 语句 (分支语法)](#if--switch--case-语句-分支语法)
	- [*for* / *while* 语句 (循环语法)](#for--while-语句-循环语法)
	- [*select* 语句](#select-语句)
	- [*echo* 函数](#echo-函数)
	- [函数定义](#函数定义)
- [其它 *Shell* 特性](#其它-shell-特性)
	- [随机数](#随机数)
	- [*Fork Bomb*](#fork-bomb)

<!-- /TOC -->



## 简介
`Unix`系统中的`Shell`一般指`CLI Shell`，提供了`CLI`方式的系统交互接口。  
`Shell`本身是**指令解释器**，将用户输入的指令转化为对`OS`的实际操作。

`Unix`系统中默认`Shell`可更换，不同的`Unix`使用的默认`Shell`亦不相同。  
传统`Shell`：

- `sh`(`Bourne Shell`) 在`Version 7 Unix`中引入，其特性被作为后续其它`Shell`的基础
- `bash`(`Bourne-Again Shell`) `GNU`项目的一部分，特性是`Bourne Shell`的超集，被广泛使用，是`Linux`和`macOS`的默认`Shell`
- `csh`(`C Shell`) `BSD Unix`的默认`Shell`，采用类似`C`语言风格的语法
- `tcsh`(`TENEX C Shell`) 基于`csh`，兼容`csh`，在`csh`基础上添加了命令补全等特性，是`FreeBSD`的默认`Shell`

现代`Shell`：

- `zsh`(`Z Shell`) 兼容`bash`语法，同时提供更多强大功能
- `fish` 智能、用户友好的现代`Shell`，相比`zsh`拥有更多的内置特性与更现代化的设计。放弃了`bash`兼容性，使用全新设计的语法，更加简洁、优雅



## 切换默认 *Shell*
更换`Shell`使用`chsh`指令，不同`Unix`中`chsh`指令参数、效果不同。

- `Linux`中使用`chsh`会提示输入新的默认`Shell`路径
- `FreeBSD/macOS`中使用`chsh`会进入`Shell`配置编辑界面

在`/etc/shells`文件记录了本机安装的所有`Shell`，需要保证使用的`Shell`路径已添加入该文件中。  
`macOS`下使用`Homebrew`安装`fish`不会更新`/etc/shells`文件，需要手动将`fish`的路径`/usr/local/bin/fish`添加到该文件中才能正常使用`fish`作为默认`Shell`。



## *Shell* 交互
`Shell`中的常用组合键：

- `Ctrl + C` 停止当前指令(发送中断信号`SIGINT`)
- `Ctrl + \` 停止当前指令(发送退出信号`SIGQUIT`)
- `Ctrl + D` 停止当前指令
- `Crtl + W` 删除一段已输入内容(到前一个空格为止)
- `Ctrl + U` 清除所有已输入内容

使用`!!`指令可以还原上一条输入的指令(`bash/zsh`中支持该指令，`fish`不支持)：

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

使用`$?`可以获取**上一条**指令的**执行结果**(`bash/zsh`中支持该指令，`fish`不支持)：

```sh
$ ls
Applications	Documents	Library		Music		Public
Desktop		Downloads	Movies		Pictures
$ echo $?
0 # 指令执行成功，返回 0
$ abc # 执行一条不存在的指令，执行失败
bash: abc: command not found
$ echo $?
127 # 指令执行失败，返回 127
```

### 匹配规则
`Shell`中可使用以下**通配符**：

- `*` 匹配任意长度的字符串
- `?` 匹配任意单个字符
- `[]` 匹配一定范围内的单个字符

如下所示：

```
*test* 匹配 xxxxtestxxxx 或 xtestxxxx 或 xxxxtestx 或 xtestx 等
?test? 匹配 xtestx ，但无法匹配 xxxxtestxxxx
test[1-9] 匹配 test1, test2 ... test9
```

对于一些需要输入通配符原始字符的情形，需要使用`\`符号避免转义。

### 任务管理
指令后添加`&`操作符可以让指令在后台运行：

```
$ [指令名称] &
```

对于正在指令的指令，使用`Ctrl + Z`组合键可将指令暂停，并回到控制台。  
在后台运行的指令与被暂停的指令可以使用`jobs`指令查看：

```
$ jobs
```

输出结果(后台运行`top`，`vim &`指令)：

```
Job	Group	State	Command
2	4099	stopped	top
1	4085	stopped	vim &
```

在后台运行的任务会被分配任务编号。  
使用`fg/bg`指令使在后台挂起的指令恢复执行：

- `$ fg %[Job ID]` 恢复后台指定编号的任务到前台执行
- `$ bg %[Job ID]` 令指定编号的任务继续在后台执行

### 管道
`Shell`中的**管道**操作符`|`用于将一个进程的输出作为另一进程的输入。  
语法如下所示：

```sh
$ 指令1 | 指令2 | 指令3 | ...
```

管道操作符符`|`可多次连接指令。

使用`grep`指令过滤其它指令的输出文本是最常见的管道应用：

```sh
$ ls | grep *abc* # 列出当前路径下文件/路径名称中带有 abc 字符的内容
```

`ls`指令的输出作为输入内容传入`grep`中。

### 重定向
默认情形下，进程执行的标准输出、标准错误输出均在终端内显示。  
使用`>`或`>>`操作符可以重定向输出内容到文件中：

```sh
$ 指令 > 目标文件
$ 指令 >> 目标文件
```

- `>` 重定向输出会覆盖目标文件原有内容
- `>>` 重定向输出以追加的形式添加到目标文件末尾

标准输入同样支持重定向操作。  
对于需要接收输入内容的指令，使用`<`操作符可将输入由标准输入重定向到文件中：

```sh
$ 指令 < 目标文件
```

### 标准输入输出
`Shell`环境下标准输入输出存在默认编号：

| 输入输出类型 | 编号 |
|:----------:|:----:|
| `STDIN_FILENO`(标准输入) | 0 |
| `STDOUT_FILENO`(标准输出) | 1 |
| `STDERR_FILENO`(标准错误输出) | 2 |

使用编号搭配重定向操作符可实现重定向指定类型的输出。  
仅重定向错误输出到目标文件：

```sh
$ 指令 2> 目标文件
```

使用`>&`操作符可连接两个描述符，如连接标准错误输出至标准输出：

```sh
$ 指令 2>&1
```

连接描述符的`>&`操作符应置于整条指令的末尾。

实例：

以`ls`指令为例，假设当前路径下**不存在**`xxx`文件，使用`ls xxx`指令时会得到错误输出，提示文件不存在：

```sh
$ ls xxx
ls: xxx: No such file or directory
```

- 重定向指定类型输出：
	
	可将错误输出到`error.txt`文件中：
	
	```sh
	$ ls xxx 2> error.txt # 指令在终端无输出
	$ cat error.txt # 错误信息被重定向到 error.txt 文件中
	ls: xxx: No such file or directory
	```
	
	错误信息在标准错误输出中生成，重定向标准输出到文件`error.txt`，终端依旧会出现错误信息，而`error.txt`文件内容为空：
	
	```sh
	$ ls xxx 1> error.txt # 重定向标准输出
	ls: xxx: No such file or directory # 错误信息依旧输出到终端，error.txt 文件中内容为空
	```

- 连接描述符：

	将标准错误输出连接到标准输出，则重定向标准输出终端不会出现错误信息：

	```sh
	$ ls xxx 2>&1 1> error.txt # 终端无输出
	$ cat error.txt # 错误信息被重定向到 error.txt 文件中
	ls: xxx: No such file or directory
	```



## *Shell* 语法
`Unix`中，`Shell`脚本通常以`sh`作为后缀名(`bash/zsh`等)。  
`fish`由于不兼容`bash`语法，通常使用`fish`作为脚本后缀。

脚本首行需要声明使用的解析器，以`zsh`为例：

```sh
#! /bin/zsh
...
```

使用`./***.sh`执行脚本时，已指定解析器的脚本会调用指定的解析器进行介些，未指定解析器的脚本会使用默认的`Shell`解析。

### 变量
`bash/zsh`变量相关语法基本相同，`fish`与其有较大差异。  
定义、修改变量：

- `变量名=值` 定义变量，`bash/zsh`语法，但等号两边**不能**带有空格
- `set 变量名 内容` 定义变量，`fish`语法
- `变量名+=内容` 向变量添加内容，`bash/zsh`语法，`fish`不支持该操作

如下所示：

```sh
# bash/zsh
$ num=233 # 定义变量 num
$ echo $num # 访问变量 num
233 # 输出变量内容 233
$ num+=1 # 拼接文本 233 和 1
$ echo $num
2331 # 输出 2331

# fish
$ set num 233
$ echo $num # 输出 233
$ num+=1
$ echo $num
233 # fish 不支持 += 操作，输出结果未发生改变
```

查看、删除已定义的变量：

- `$变量名` 获取变量内容
- `set` 列出已定义的变量
- `unset 变量名` 删除指定名称的变量(`bash/zsh`语法)
- `set -e 变量名` 删除指定名称的变量(`fish`语法)

### 指令
执行指令，语法如下：

- `$(指令)` 执行指令(`bash/zsh`语法)
- `(指令)` 执行指令(`fish`语法)

对于算术表达式，`bash/zsh`默认作为文本处理。  
即`echo 2+3`为输出内容为`2+3`的文本。  
如下所示：

```sh
# bash/zsh
$ num=233
$ echo $num+1 
233+1 # 输出文本 233+1

# fish
$ set num 233
$ echo $num+1
233+1
```

求值计算表达式，语法如下：

- `$((表达式))`/`$[表达式]` (`bash/zsh`语法)
- `expr 表达式` (`bash/zsh`语法)
- `math 表达式` (`fish`语法)

```sh
# bash/zsh
$ num=233
$ echo $(($num+1))
234 # 输出 234
$ echo $[$num+1]
234
$ echo $[$num*10]
2330

# fish
$ set num 233
$ echo (math $num+1)
234
$ echo (math $num\*10) # fish 中乘法运算需要使用反斜杠转义 * 符号
2330
```

### 数组
`bash/zsh/fish`数组相关语法均存在一定差异。  
定义数组：

- `数组名=(内容1 内容2 内容3 ...)` 定义数组，多个数组内容间使用**空格**隔开(`bash/zsh`语法)
- `set 数组名 内容1 内容2 内容3 ...` 定义数组，多个数组内容间使用**空格**隔开(`fish`语法)

如下所示：

```sh
# bash/zsh
$ nums=(1 2 3) # 定义数组，包含3个元素： 1 2 3

# fish
$ set nums 1 2 3
```

访问数组内容：

- `$数组名` 访问数组名返回数组内**首个**元素(`bash`语法)，或返回**整个**数组(`zsh/fish`语法)
- `$数组名[索引]` 访问数组指定索引的内容，支持**逆序**索引(`zsh/fish`语法)
- `$数组名[起始索引..结束索引]` 数组切片，访问从起始索引到结束索引之间的内容(`fish`特性)
- `$((数组名[索引]))`/`$[数组名[索引]]`/`${数组名[索引]}` 访问数组指定索引的内容(`bash/zsh`语法)

`bash`中，数组索引从`0`开始。  
`zsh/fish`中，数组索引从`1`开始。  
如下所示：

```sh
# bash
$ nums=(1 2 3)
$ echo $nums
1 # bash中数组名代表数组内首个元素
$ echo $((nums[0]))
1
$ echo $[nums[1]]
2
$ echo ${nums[2]}
3
$ echo ${nums[3]}
 # 无输出内容(数组越界)
$ echo $nums[2]
1[2] # bash不支持直接使用数组名后添加索引访问数组内容，"$数组名"被解析为数组首个元素

# zsh
$ nums=(1 2 3)
$ echo $nums
1 2 3 # zsh中数组名代表数组内所有内容
$ echo $((nums[0]))
0 # zsh数组下标从1开始，数组越界
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
1 2 3 # fish中数组名代表数组内所有内容
$ echo $nums[-1]
3 # fish支持逆序索引
$ echo $nums[2..3]
2 3 # fish支持数组切片
$ echo $nums[0] # fish数组下标从1开始，数组越界
fish: Array index out of bounds
echo $nums[0]
           ^
$ echo $nums[1]
1
$ echo $[nums[1]] # 报错，fish不支持bash/zsh中的数组访问语法
fish: $[ is not a valid variable in fish.
echo $[nums[1]]
      ^
$ echo ${nums[1]} # 报错，fish不支持bash/zsh中的数组访问语法
fish: ${ is not a valid variable in fish.
echo ${nums[1]}
      ^
```

获取数组长度：

- `${#数组名[@]}` 数组长度(`bash/zsh`语法)
- `$[#数组名[@]]` 数组长度(`bash/zsh`语法)
- `count 数组名` 数组长度(`fish`语法)

### 条件语法
`test`函数用于条件检验，使用`test 条件`来检验一个条件是否成立。  
`[ 条件 ]`语法是`test 条件`的语法糖，作用类似。  
`[ 条件 ]`语法中，条件内容需要与`[]`符号两边各保持一个空格以上的间距，否则语法解析出错：

```sh
if [ 条件 ]; then # 正确
	...
fi

if [条件]; then # 错误
	...
fi
```

`[ 条件 ]`用于**字符**判断：

- `[ 字符1 = 字符2 ]` 字符相同
- `[ 字符1 != 字符2 ]` 字符不同
- `[ -z 字符 ]` 字符为空
- `[ -n 字符 ]` 字符非空

`[ 条件 ]`用于**数值**比较：

- `[ 数值1 -lt 数值2 ]` 数值1**小于**数值2
- `[ 数值1 -le 数值2 ]` 数值1**小于等于**数值2
- `[ 数值1 -gt 数值2 ]` 数值1**大于**数值2
- `[ 数值1 -ge 数值2 ]` 数值1**大于等于**数值2
- `[ 数值1 -eq 数值2 ]` 数值1**等于**数值2
- `[ 数值1 -ne 数值2 ]` 数值1**不等于**数值2

`[ 条件 ]`用于**文件**判断：

- `[ -e 文件 ]` 文件已经存在
- `[ -f 文件 ]` 文件是普通文件
- `[ -s 文件 ]` 文件大小不为零
- `[ -d 文件 ]` 文件是一个目录
- `[ -r 文件 ]` 文件对当前用户可以读取
- `[ -w 文件 ]` 文件对当前用户可以写入
- `[ -x 文件 ]` 文件对当前用户可以执行
- `[ -g 文件 ]` 文件的`GID`标志被设置
- `[ -u 文件 ]` 文件的`UID`标志被设置
- `[ -O 文件 ]` 文件是属于当前用户的
- `[ -G 文件 ]` 文件的组`ID`和当前用户相同
- `[ 文件1 -nt 文件2 ]` **文件1**比**文件2**更**新**
- `[ 文件1 -ot 文件2 ]` **文件1**比**文件2**更**老**

### *if* / *switch* / *case* 语句 (分支语法)
分支语法包括：

- `if`语句(`bash/zsh/fish`语法)
- `case`语句(`bash/zsh`语法)
- `switch`语句(`fish`语法)

`if`分支结构语法：

```sh
# bash/zsh 分支语法
if [ 条件1 ]
then
	...
elif [ 条件2 ]
then
	...
else
	...
fi

# 多个条件可以使用逻辑运算符连接
if [ 条件1 ] && [ 条件2 ] || [ 条件3 ]; then
fi

# fish 分支语法更近似现代语言
if [ 条件1 ]
	...
else if [ 条件2 ]
	...
else
	...
end
```

模式匹配语法：

```sh
# bash/zsh 使用 case 语句进行模式匹配
case ... in
	xxx1) # 匹配内容则跳转到指定分支
		... ;; # 语句块结束使用双分号 ;;
	xxx1 | xxx2) # 多条件使用 | 操作符连接，满足匹配内容的其中一个即可
		... ;;
	*) # 没有匹配到内容跳转到默认分支
		... ;;
esac

# fish 使用 switch 语句进行模式匹配
switch ...
	case xxx1
		...
	case xxx2 xxx3
		...
	case '*'
		...
end
```

### *for* / *while* 语句 (循环语法)
`for/while`用于重复执行某段逻辑。

`bash/zsh`中的`for`语句：

```sh
# 传统C风格循环
for ((变量名=数值; 变量名<=数值; 变量名++)); do
	...
done

# 基于列表遍历的循环
for 变量名 in {起始值..结束值}; do
	...
done

# zsh 支持列表遍历语法
# bash 4.0 之后支持设定遍历间隔
for 变量名 in {起始值..结束值..间隔}; do
	...
done

# 无限循环
for ((;;)); do
	...
done
```

`macOS 10.12.6`默认的`bash`版本为`3.2.57`，使用列表遍历语法时不支持设定间隔(`zsh`支持此语法)。

`fish`中的`for`语句：

```fish
# fish 仅支持列表遍历循环，使用 seq 函数构建列表
for 变量 in (seq 起始值 结束值)
	...
end

# seq 函数可构建带有间隔的循环
for 变量 in (seq 起始值 间隔 结束值)
	...
end
```

除了`for`语句，亦可使用`while`构建循环。  
`while`语句语法：

```sh
# bash/zsh
while [ 条件 ]; do
	...
done

# fish
while [ 条件 ]
	...
end

# fish 无限循环
while true
	...
end
```

实例，打印`1~10`范围的数值，如下所示：

```sh
# bash/zsh C风格
for ((i=0; i<=10; i++)); do
	echo $i
done

# bash/zsh 列表遍历
for i in {1..10}; do
	echo $i
done

# bash/zsh while语句
i=1
while [ i -le 10 ]; do
	echo $i
	i=$[$i+1]
done

# fish for语句
for i in (seq 1 10)
	echo $i
end

# fish while语句
set i 1
while [ $i -le 10 ]
	echo $i
	set i (math $i+1)
end
```

### *select* 语句
`select`语句用于在`Shell`环境中提供选择菜单。  
`bash/zsh`中`select`结构语法：

```sh
select $xxx in "xxx1" "xxx2"; do # 提供选单，提示用户在选项 xxx1 xxx2 中进行选择
	...
	break # 执行逻辑后需要使用 break 终止 select 结构，否则会一直循环出现选单
done
```

`fish`中没有提供`select`结构同等的语法。

### *echo* 函数
`echo`函数用于向标准输出(`stdout`)打印文本，类似于高级语言中的`print()`函数。  
`echo`函数可选参数：

- `-e` 转义文本
- `-n` 不打印换行符

不同`Shell`对于转义字符的默认处理方式不同。  
对于使用**引号**(`'`或`"`)包含的文本：

- `bash/fish`默认不处理转义字符，将转义字符作为普通文本输出
- `zsh`默认处理转义字符，相当于使用`echo -e`指令

对于普通文本(文本不使用引号包含，直接作为参数)：

- `bash/zsh`默认忽略转义字符，并且输出的文本中不包含转义符号`\`
- `fish`默认处理转义字符，相当于使用`-e`参数

如下所示：

```sh
# bash
$ echo abc\n
abcn # bash 普通文本转义字符被忽略
$ echo 'abc\n'
abc\n # bash 使用引号转义字符被作为普通文本输出
$ echo -e 'abc\n'
abc
 # 转义字符有效，正常输出换行符

# zsh
$ echo abc\n
abcn # 忽略、隐藏转义字符
$ echo 'abc\n'
abc
 # zsh 使用引号正常输出转义字符
$ echo -e 'abc\n'
abc
 # 转义字符有效，正常输出换行符

# fish
$ echo abc\n
abc
 # 转义字符有效，正常输出换行符
$ echo 'abc\n'
abc\n # fish 使用引号，转义字符被视为普通文本输出
$ echo -e 'abc\n'
abc
 # 转义字符有效，正常输出换行符
```

### 函数定义
函数用于封装一段需要重复调用的逻辑。

定义函数语法：

```sh
# bash/zsh
function 函数名() {
	...
	return 返回值
}

# bash/zsh 定义函数 function 关键字可以省略
函数名() {
	...
	return 返回值
}

# fish
function 函数名
	...
	return 返回值
end
```

`bash/zsh/fish`调用函数语法类似：

```sh
函数名 参数1 参数2 参数3 ... # 调用函数传参不使用括号
```

`bash/zsh`函数参数处理：

- `$#` 获取参数的数目
- `$@` 获取参数列表
- `$1 ~ $9` 获取函数参数内容，最大支持9个参数

实例：

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

# 调用函数
show 1 2 3 4 5 6 7 8
```

输出结果：(`macOS 10.12.6` && `bash 3.2.57` && `zsh 5.2`)

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

`fish`函数参数处理：

- `fish`使用列表`argv`保存传入函数的参数
- `count argv` 获取参数的数目
- `$argv[索引]` 获取指定索引的参数

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

# 调用函数
show 1 2 3 4 5 6 7 8
```

输出结果：(`macOS 10.12.6` && `fish 2.6.0`)

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



## 其它 *Shell* 特性
`Shell`中的一些常用功能。

### 随机数
`bash/zsh/fish`均内置了生成随机数的功能。

- `bash/zsh`中通过访问`RANDOM`变量获取随机数：

	```sh
	$ $[$RANDOM%随机数范围]
	```
	
	`$RANDOM`返回**0~32767**，执行取余计算可得到指定范围范围的随机数。

- `fish`通过`random`函数获取随机数：

	```fish
	$ random 随机数起始范围 随机数结束范围
	```

	`random`函数输入随机数的起止范围作为参数。

### *Fork Bomb*
`Fork Bomb`(**Fork炸弹**)是`bash/zsh`中存在的经典恶意脚本：

```sh
:(){ :|:& };:
```

或者：

```sh
.(){ .|.& };.
```

**Fork炸弹**利用`bash/zsh`中简短的函数语法，使用符号`:`或`.`作为函数名，在函数体中递归调用自身。  
函数正常的写法如下：

```sh
:() { # 定义函数
	: | :& # 函数体内部递归并通过管道创建新进程在后台运行
};
: # 调用函数
```

函数体中使用了**管道**特性，在每次递归时会同时创建新的进程在后台运行。  
随着递归次数的增加，进程数会以指数级增加，最终消耗光所有的系统资源。

**Fork炸弹**在其它`Shell`中并不能执行，如`fish`中函数语法带有`end`关键字，并不简短；而`csh/tcsh`中不支持函数。
