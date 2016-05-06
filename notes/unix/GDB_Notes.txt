GDB默认情况下是一个纯CLI调试器，可以使用-tui参数使gdb提供一个基于CLI的简单的交互式界面：
$ gdb -tui [需要被调试的可执行文件]

gdb的一些基本操作 >>
	r(run)			开始执行程序
	n(next)			执行下一条语句(不会进入子函数)
	s(step)			单步调试(会进入子函数内部)
	c(continue)		继续执行程序(直到下一个断点)
	l(list)			查看当前程序运行位置附近的代码片段
	b(break)		设置断点
	p(print)		显示变量/函数等信息
	i(info)			可搭配不同指令显示具体的状态信息(断点,显示等)
	d(delete)		删除设置(断点,显示信息等)
	q(quit)			退出gdb
	bt(backtrace)	显示函数堆栈

break >>
	break用于下断点：
	break [行号]
	break [函数名]
	break [地址]
	如果存在多个源码文件，则需要使用源码文件名显式指定要下断点的文件：
	break [源码文件名:行号/函数名/地址]
	gdb支持条件断点：
	break [行号/函数名/地址] if [条件]
	在判断条件中甚至可以直接调用标准库内的函数。

display >>
	让每次运行暂停时都显示指定的信息。可显示变量/函数等信息。

delete >>
	删除已经存在的设置信息。
	delete [数据类型] [号码]
	举例：
		delete breakpoint 1			//删除1号断点

一次显示多个变量的信息 >>
	display/print {变量1, 变量2, 变量3......}

info >>
	info可以用于查看一些信息，常见的有：
	info b			显示断点信息
	info locals 	显示当前函数的局部变量信息
	info threads	显示线程信息

until/finish >>
	until用于跳出循环，finish用于结束当前函数。

ptype >>
	ptype用于输出变量类型信息，对于结构类型(类)变量，能够显示出整个结构体/类的定义。

checkpoint >>
	使用checkpoint指令可以在调试过程中将当前位置添加为检查点。
	当需要多次调试同一段代码时，调试器能够从检查点位置恢复运行，而不必重启整个进程。
	查看当前检查点信息：
	info checkpoints
	从指定的检查点恢复运行：
	restart [检查点编号]

调试子进程 >>
	默认情况下，gdb在程序调用fork()之后调试的是父进程，如果需要手动指定调试的进程，使用：
	set follow-fork-mode [parent | child]

设置源码目录 >>
	在调试时使用dir指令可以添加临时的源码目录：
	dir [路径]