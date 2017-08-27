<!-- TOC -->

- [简介](#简介)
- [切换默认 *Shell*](#切换默认-shell)
- [*Shell* 交互](#shell-交互)
	- [匹配规则](#匹配规则)
	- [任务管理](#任务管理)
- [*bash/zsh* 脚本](#bashzsh-脚本)

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

```
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

### 匹配规则
`Shell`中可使用以下**通配符**：

- `*` 匹配任意长度的字符串
- `?` 匹配任意单个字符
- `[]` 匹配一定范围内的单个字符

如下所示：

```
*test* 匹配 xxxxtestxxxx
?test? 匹配 xtestx ，但无法匹配 xxxxtestxxxx
test[1-9] 匹配 test1, test2 ... test9
```

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



## *bash/zsh* 脚本
`Unix`中，`Shell`脚本以`sh`作为后缀名，脚本首行需要声明使用的解析器，以`zsh`为例：

```sh
#! /bin/zsh
...
```

使用`./***.sh`执行脚本时，已指定解析器的脚本会调用指定的解析器进行介些，未指定解析器的脚本会使用默认的`Shell`解析。
