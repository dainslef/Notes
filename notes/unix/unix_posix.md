<!-- TOC -->

- [系统调用与库函数](#系统调用与库函数)
	- [系统调用](#系统调用)
	- [库函数](#库函数)
- [时间API](#时间api)
	- [获取当前的系统时间](#获取当前的系统时间)
	- [将时间转化为可读格式](#将时间转化为可读格式)
	- [将时间转化为标准字符串表示](#将时间转化为标准字符串表示)
- [文件与基本IO](#文件与基本io)
	- [创建/打开一个文件](#创建打开一个文件)
	- [读取文件中的内容](#读取文件中的内容)
	- [向文件中写入内容](#向文件中写入内容)
	- [获取文件信息](#获取文件信息)
	- [标准输入/输出](#标准输入输出)
- [复制文件描述符](#复制文件描述符)
	- [*dup3()* 函数](#dup3-函数)
	- [使用 *dup()* 重定向输出](#使用-dup-重定向输出)
- [Unix日志](#unix日志)
- [日志服务](#日志服务)
	- [打开日志](#打开日志)
	- [输出日志](#输出日志)
	- [关闭日志连接](#关闭日志连接)
	- [实例代码](#实例代码)
- [Unix进程](#unix进程)
	- [进程控制函数](#进程控制函数)
	- [等待进程](#等待进程)
	- [*Daemon* (守护进程)](#daemon-守护进程)
- [*signal* (信号)](#signal-信号)
	- [处理信号](#处理信号)
	- [发送信号](#发送信号)
	- [信号触发](#信号触发)
	- [可靠信号与不可靠信号](#可靠信号与不可靠信号)
	- [屏蔽信号](#屏蔽信号)
	- [屏蔽线程信号](#屏蔽线程信号)
	- [信号相关的进程控制函数](#信号相关的进程控制函数)
	- [多线程信号处理](#多线程信号处理)
- [POSIX 线程(pthread)](#posix-线程pthread)
	- [Linux下的线程实现](#linux下的线程实现)
	- [创建线程](#创建线程)
	- [等待线程](#等待线程)
	- [取消线程](#取消线程)
	- [终止线程](#终止线程)
	- [用互斥量进行线程同步](#用互斥量进行线程同步)
	- [使用互斥量进行进程同步](#使用互斥量进行进程同步)
- [*XSI IPC*](#xsi-ipc)
	- [IPC标志](#ipc标志)
	- [XSI IPC特点](#xsi-ipc特点)
- [*SystemV* 共享内存](#systemv-共享内存)
	- [创建/获取共享内存](#创建获取共享内存)
	- [获得共享内存地址](#获得共享内存地址)
	- [分离共享内存](#分离共享内存)
	- [控制共享内存](#控制共享内存)
- [SystemV 信号量(Semaphore)](#systemv-信号量semaphore)
	- [创建/获取信号量](#创建获取信号量)
	- [改变信号量的值](#改变信号量的值)
	- [设置信号量信息](#设置信号量信息)
- [SystemV 消息队列(XSI Message Queue)](#systemv-消息队列xsi-message-queue)
	- [创建/获取消息队列](#创建获取消息队列)
	- [向消息队列中添加消息](#向消息队列中添加消息)
	- [从消息队列中获取消息](#从消息队列中获取消息)
	- [控制消息队列](#控制消息队列)
	- [实例代码](#实例代码-1)
- [POSIX 消息队列](#posix-消息队列)
	- [创建/获取消息队列](#创建获取消息队列-1)
	- [关闭/移除消息队列](#关闭移除消息队列)
	- [设置获取消息队列的属性](#设置获取消息队列的属性)
	- [打印消息队列的系统限制](#打印消息队列的系统限制)
	- [向消息队列发送消息](#向消息队列发送消息)
	- [从消息队列获取消息](#从消息队列获取消息)
	- [消息队列通知](#消息队列通知)
	- [实例代码](#实例代码-2)
- [IO多路复用(POSIX)](#io多路复用posix)
	- [*select()* 调用](#select-调用)
	- [*pselect()* 调用](#pselect-调用)
- [IO多路复用(Epoll)](#io多路复用epoll)
	- [*epoll_create()* 函数](#epoll_create-函数)
	- [*epoll_ctl()* 函数](#epoll_ctl-函数)
	- [*epoll_wait()* 函数](#epoll_wait-函数)
	- [注意事项](#注意事项)
	- [*LT* 与 *ET* 模式](#lt-与-et-模式)

<!-- /TOC -->



## 系统调用与库函数
对开发者而言，系统调用与库函数在Unix中都是一组C语言接口，但内部有很大区别。

### 系统调用
**系统调用**(`System calls`)是操作系统提供的服务入口点，程序由这些服务入口点向内核请求服务。

Unix系统为大多数的系统调用提供了同名的C函数接口，封装在标准C库(libc)中，在用户进程中调用这些C函数来发起系统调用。  
使用系统调用会在**用户态**与**内核态**之间进行环境切换(内核发现`trap`之后进入内核态)，有较大开销。

在Linux和BSD中，部分系统函数没有提供C库的封装(比如Linux中的`gettid()`)，需要使用`syscall()`函数进行调用，`syscall()`最初由BSD引入，Linux在`Linux Kernel 2.6.19`之后引入该函数。

一般而言，系统调用是系统服务的直接入口点。一些库函数也会用到系统调用，但这些库函数**不是**系统入口点(典型的例子是C语言标准库中的`printf()`函数使用了系统调用`write()`)。

`man`手册卷`2`中的函数皆为系统调用。

### 库函数
**库函数**(`Library calls`)是编程语言的一部分，与操作系统无关，`Windows`系统中，例如`printf()`、`scanf()`等库函数依然可用，但Unix系统调用如`read()`、`write()`便不再存在。

一些库函数内部会使用系统调用(如`printf()`)，在不同的操作系统中，库函数会使用对应操作系统的系统调用。  
辅助功能性库函数(如`memcpy()`、`atoi()`之类)是纯粹的用户态函数，不涉及系统调用，不会造成系统在用户态与内核态之间切换。

C标准库函数可在`man`手册卷`3`中查阅。



## 时间API
Unix环境下的时间获取相关函数定义在`time.h`头文件之中。

### 获取当前的系统时间
使用`time()`函数获取当前系统时间。

```c
time_t time(time_t *t);
```

`t`参数为`time_t`类型变量的地址，函数会返回当前系统的时间，同时将当前系统的时间写入传入的地址中。  
如果只是从返回值获取当前时间，不需要将时间写入传入参数中，则参数可以填`NULL`，函数正常运行。  
返回值`time_t`保存的是`1970-01-01 00:00:00 +0000 (UTC)`开始到**当前时间**的秒数的数值，一般不直接使用。

### 将时间转化为可读格式
使用`localtime()`函数输出时间结构体`tm`类型。

```c
struct tm *localtime(const time_t *timep);
```

函数接受参数为`time()`返回的标准时间秒数，将其转换返回对应的可读时间结构体指针`tm*`类型。
结构体`tm`的定义为：

```c
struct tm {
	int tm_sec;    /* Seconds (0-60) */
	int tm_min;    /* Minutes (0-59) */
	int tm_hour;   /* Hours (0-23) */
	int tm_mday;   /* Day of the month (1-31) */
	int tm_mon;    /* Month (0-11) */
	int tm_year;   /* Year - 1900 */
	int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
	int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
	int tm_isdst;  /* Daylight saving time */
};
```

可以从`tm`结构体的对应成员中读取对应的时间信息。

时间信息中部分信息需要处理才能对应真实时间：

- **年份**为当前年份减去`1900`的值，实际年份需要加`1900`。
- **月份**范围为`0 ~ 11`，实际月份需要加`1`。

### 将时间转化为标准字符串表示

```c
char *asctime(const struct tm *tm);
```

对于`localtime()`函数获得的当前时间，可以使用该函数转化为可读的字符串形式，返回值为标准时间字符串的地址。  
需要注意的是，该函数返回的地址指向的字符串内容中已经包含了换行符，不需要再额外添加。

一个典型的时间输出如：`Wed Jul 29 01:04:10 2015`

实例代码：

```c
#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t now = time(NULL);
	struct tm *tm_now = localtime(&now);
	printf("当前的时间是：%d点%d分%d秒。\n", tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
	printf("标准的时间输出：%s", asctime(tm_now));
	return 0;
}
```

运行结果：

```
当前的时间是：1点15分39秒。
标准的时间输出：Wed Jul 29 01:15:39 2015
```



## 文件与基本IO
Unix环境下基本的文件操作为`open()`、`read()`、`write()`、`close()`、`ioctl()`等。  
相关的头文件在`unistd.h`、`fcntl.h`、`sys/ioctl.h`之中。

### 创建/打开一个文件
创建/打开文件涉及的系统调用定义在文件`fcntl.h`中。

```c
int creat(const char *pathname, mode_t mode);
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```

`creat()`函数用于创建文件；  
`open()`函数既可用于创建文件(**flags**取`O_CREAT`)，也可用于打开文件，打开的对象也可以是**目录**。

- `pathname`参数：

	对于`create()`和`open()`函数，参数`pathname`指向的字符数组为文件所在路径(路径可为绝对路径或相对路径)。  
	`dirfd`文件描述符表示的路径为**父目录**，参数`pathname`指向的字符数组为相对路径。

- `mode`参数：

	`mode`代表创建的文件文件带有的默认权限，可以用逻辑或操作符连接以下参数：

	- `S_IRUSR` 拥有者读权限
	- `S_IWUSR` 拥有者写权限
	- `S_IXUSR` 拥有者执行权限
	- `S_IRGRP` 同组用户读权限
	- `S_IWGRP` 同组用户写权限
	- `S_IXGRP` 同组用户执行权限
	- `S_IROTH` 其它用户读权限
	- `S_IWOTH` 其它用户写权限
	- `S_IXOTH` 其它用户执行权限

- `flag`参数

	`flags`参数表示文件打开时的参数，参数可取**多个**，以**逻辑或**操作符连接，常用的有：

	- `O_RDONLY` 只读打开文件
	- `O_WRONLY` 只写打开文件
	- `O_RDWR` 读写打开文件
	- `O_APPEND` 写入数据时在原文件的末尾追加数据，而不是清楚原有数据
	- `O_CREAT | O_EXECL` 创建原先**不存在**的文件，若文件已经存在了，则调用**失败**

- `openat()`函数

	函数作用与`open()`函数类似，`openat()`函数允许使用多种路径表示方式：

	- `dirfd`文件描述符表示的路径为父目录，而`pathname`中包含的字符串为相对路径。
	- `dirfd`取特殊值`AT_FDCWD`，则父目录为**当前路径**。
	- `dirfd`取值**忽略**，`pathname`参数为**绝对路径**。

以上函数在执行成功时返回新的文件描述符，失败时返回**-1**并置`errno`。

### 读取文件中的内容
使用`read()`函数读取文件，函数定义在`unistd.h`中。

```c
ssize_t read(int fd, void *buf, size_t count);
```

- `fd`参数为要读取的文件描述符。
- `buf`参数为读取的内容的首地址。
- `count`参数为设定读取的字节数。

返回值为实际读取了的字节数。  
失败时返回`-1`。

### 向文件中写入内容
使用`write()`向文件中写入数据，函数定义在`unistd.h`中。

```c
ssize_t write(int fd, const void *buf, size_t count);
```

- `fd`参数为要写入的文件描述符。
- `buf`参数为要写入内容的首地址。
- `count`参数指定写入数据的长度。

`buf`指向的内容中超过`count`长度的内容**不会**被写入。  
返回值为**实际写入内容的大小**。

对于同一个文件描述符，连续进行读写操作，每一次函数调用都会在上一次结束的位置进行，因此想要重复读取某个文件的内容，需要创建新的文件描述符。  
同一个文件可以同时拥有多个文件描述符，且各个文件描述符之间的文件读取是相互独立的。

### 获取文件信息
使用`stat()`获取文件的信息，函数定义在`sys/stat.h`中。

```c
int stat(const char *pathname, struct stat *buf);
```

- `pathname`参数为要获取文件的路径。
- `buf`参数为指向文件属性结构体的指针。

函数执行成功返回`0`，失败时返回`-1`并置`errno`。

文件属性结构体`stat`定义如下：

```c
struct stat {
	dev_t     st_dev;         /* ID of device containing file */
	ino_t     st_ino;         /* inode number */
	mode_t    st_mode;        /* file type and mode */
	nlink_t   st_nlink;       /* number of hard links */
	uid_t     st_uid;         /* user ID of owner */
	gid_t     st_gid;         /* group ID of owner */
	dev_t     st_rdev;        /* device ID (if special file) */
	off_t     st_size;        /* total size, in bytes */
	blksize_t st_blksize;     /* blocksize for filesystem I/O */
	blkcnt_t  st_blocks;      /* number of 512B blocks allocated */

	/* Since Linux 2.6, the kernel supports nanosecond
		precision for the following timestamp fields.
		For the details before Linux 2.6, see NOTES. */
	struct timespec st_atim;  /* time of last access */
	struct timespec st_mtim;  /* time of last modification */
	struct timespec st_ctim;  /* time of last status change */

	#define st_atime st_atim.tv_sec      /* Backward compatibility */
	#define st_mtime st_mtim.tv_sec
	#define st_ctime st_ctim.tv_sec
};
```

在`stat`结构中，定义了文件的文件的**大小**、**文件种类**、**所属用户/用户组**、**文件的访问/修改时间**等信息。

### 标准输入/输出
在Unix哲学中，秉承**一切皆文件**思想，因而，在终端中进行输入/输出与读写文件操作类似，使用`read()/write()`调用即可。

- **标准输入**对应的文件描述符为`0`。
- **标准输出**对应的文件描述符为`1`。 
- **标准错误输出**对应的文件描述符为`2`。

使用`read()/write()`调用对这些特殊的文件描述符进行读写操作即可实现**终端输入/输出**的效果。

在头文件`unistd.h`中，分别为这3个特殊的文件描述符创建了宏定义：

```c
/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */
```



## 复制文件描述符
使用`dup()`系列函数进行描述符复制操作，函数定义在头文件`unistd.h`中。

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

- `oldfd`参数为旧的文件描述符。
- `newfd`参数为新的文件描述符。

`dup()`接收旧的文件描述符参数，并复制旧描述符到当前未被使用的最小描述符编号上，返回该描述符。  
`dup2()`接收旧的文件描述符和新文件描述符参数，并将旧文件描述符复制到新文件描述符上。

函数执行成功返回新的文件描述符，失败时返回`-1`。  
函数执行成功则新旧文件描述符可以交替使用，新文件描述符拥有**相同**的文件偏移量和文件状态标志，当一个文件描述符的偏移量发生改变时，另一个文件描述符也将同步改变。

新旧文件描述符之间**不**共享`FD_CLOEXEC`描述符标志。

### *dup3()* 函数
`Linux`下还提供了独有的函数`dup3()`，`dup3()`函数需要定义`_GNU_SOURCE`宏并引用`fcntl.h`头文件才能使用。

```c
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>

int dup3(int oldfd, int newfd, int flags);
```

- `flags`参数可以取`O_CLOEXEC`标志，设置了该标志之后，复制的新描述符将带有`FD_CLOEXEC`标志。

对于新旧文件描述符相同的情况，`dup2()`函数正常执行完毕并返回`newfd`，`dup3()`函数执行失败并置`error`为`EINVAL`。

### 使用 *dup()* 重定向输出
`dup()`系列函数最常见的用途之一就是重定向标准、错误输出到指定文件。  
如下所示：

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_PATH "out_file"

int main(int argc, char** argv)
{
	// 输出"ERROR0"到标准错误输出
	write(STDERR_FILENO, "ERROR0\n", 7);

	// 打开输出文件
	int error_fd = open(FILE_PATH, O_CREAT | O_RDWR, 0600);

	// 备份标准错误输出
	int stderror_back = dup(STDERR_FILENO);

	// 将输出文件描述符复制到标准错误输出上
	dup2(error_fd, STDERR_FILENO);

	// 输出"ERROR1"到标准错误输出，此时的标准错误输出实际为先前打开的文件
	write(STDERR_FILENO, "ERROR1\n", 7);

	// 恢复标准错误输出的功能
	dup2(stderror_back, STDERR_FILENO);

	// 测试标准错误输出
	write(STDERR_FILENO, "ERROR2\n", 7);

	// 打印各个描述符的数值
	printf("The STDERR is %d.\n", STDERR_FILENO);
	printf("The error_fd is %d.\n", error_fd);
	printf("The stderror_back is %d.\n", stderror_back);

	return 0;
}
```

运行结果：(GCC 6.1.1 && ArchLinux x64)

```
ERROR0
ERROR2
The STDERR is 2.
The error_fd is 3.
The stderror_back is 4.
```

输出文件`out_file`中的内容：

```
ERROR1
```



## Unix日志
日志相关的函数定义在头文件`syslog.h`中。

## 日志服务
在使用`SysVinit`作为init系统的Linux中，日志服务为`rsyslog`或`syslog-ng`，主要日志为`/var/log/syslog`文件。  
`/var/log/syslog`文件为纯文本，可以直接使用编辑器查看。

在现代Linux中，init系统采用`systemd`，日志服务也由`systemd`的子模块`systemd-journald`提供，日志文件位于`/var/log/journal`目录下。  
`systemd-journald`记录的日志为**二进制**格式，使用编辑器查看显示为**乱码**，应使用`journalctl`指令查看：

```
$ journalctl //查看所有日志
$ journalctl -e //查看近期日志(最近的1000条日志)
```

使用`journalctl`指令会进入交互式日志查看界面，跳转翻页快捷键等与`vim`编辑器类似。

### 打开日志
在开始记录日志之前，使用`openlog()`打开一个日志连接。

```c
void openlog(const char *ident, int option, int facility);
void closelog(void);
```

- `ident`参数为日志前缀，使用该连接输出的日志都将以该字符串作为前缀，传入值为`NULL`时，将使用程序名称做为前缀。
- `option`参数为日志选项，多个选项之间可以使用逻辑或`|`操作符相连接：
	- `LOG_CONS` 当写入系统日志出错时直接向终端输出错误
	- `LOG_NDELAY` 立即打开日志连接(普通情况下，连接将在打印首个日志时被打开)
	- `LOG_NOWAIT` 输出日志时不等待子进程创建完毕(`GNU C`库不会创建子进程，这个选项在Linux下无效)
	- `LOG_ODELAY` 与LOG_NDELAY相反，日志连接将被延迟到首个`syslog()`被调用(默认)
	- `LOG_PERROR` 同时将日志输出到`stderr`，实际开发中，可将输出到`stderr`的日志**重定向**到指定文件来实现日志文件转储
	- `LOG_PID` 输出日志时包含`PID`信息
- `facility`参数用于标记日志的类型：
	- `LOG_AUTH` 安全/权限消息
	- `LOG_AUTHPRIV` 安全/权限消息(私有)
	- `LOG_CRON` 时钟服务
	- `LOG_DAEMON` 不带有facility值的系统服务
	- `LOG_FTP` ftp文件服务
	- `LOG_KERN` 内核信息(不能由用户进程生成)
	- `LOG_LOCAL0 ~ LOG_LOCAL7` 为本地用户预留
	- `LOG_LPR` 行显示子系统
	- `LOG_MAIL` 邮件子系统
	- `LOG_NEWS` USENET新闻子系统
	- `LOG_SYSLOG` 由syslogd(8)创建的日志消息
	- `LOG_USER (default)` 普通的用户级别消息
	- `LOG_UUCP` UUCP子系统

标准的日志格式如下：

`[日志时间] [主机名称/主机ip] [ident] [facility]: [消息内容]`

在使用纯文本日志的发行版中，默认日志输出到文件`/var/log/syslog`，但一些日志服务如`rsyslog`，可以根据日志的类型(`facility`参数)将日志转储到不同的日志文件中。

`openlog()`函数是**可选**的，即使不调用`openlog()`函数，在首次调用`syslog()`函数打印日志时也会**自动**打开日志连接。  
不使用`openlog()`直接使用`syslog()`函数输出日志时自动创建的日志连接会使用默认配置，若需**自定义日志前缀**、**输出日志到stderr**等额外功能，则仍然需要**手动**打开日志连接并配置参数。

### 输出日志
使用`syslog()`函数输出日志：

```c
void syslog(int priority, const char *format, ...);
```

- `priority`参数为日志的重要级别，取值如下：
	- `LOG_EMERG` 系统不可用
	- `LOG_ALERT` 动作必须立即产生
	- `LOG_CRIT` 危险状态
	- `LOG_ERR` 错误状态
	- `LOG_WARNING` 警告状态
	- `LOG_NOTICE` 普通但是重要的状态
	- `LOG_INFO` 信息消息
	- `LOG_DEBUG` 调试消息
- `format`参数指向日志的格式化字符数组，格式化语法与`printf()`函数相同。

在使用`systemd`作为init系统的发行版中，使用`journalctl`指令查看日志时，对特定级别的日志会有不同的显示方式，令日志更加醒目：

- `LOG_EMERG`、`LOG_ALERT`、`LOG_CRIT`、`LOG_ERR`级别的日志以**红色**字体显示。
- `LOG_WARNING`、`LOG_NOTICE`级别的日志以**粗体**字显示。

### 关闭日志连接
使用`closelog()`函数立即关闭日志连接：

```
void closelog(void);
```

使用`closelog()`会关闭用于写入日志的描述符，`closelog()`同样是**可选**的操作。

### 实例代码
打印各个级别的日志，并将日志转储到日志文件`test.log`中，如下所示：

```c
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	openlog("Test_log", LOG_PID | LOG_PERROR, LOG_USER); //打开日志连接

	int log_fd = open("test.log", O_CREAT | O_APPEND | O_RDWR, 0600);

	//使用dup2()调用，重定向标准错误输出到打开的文件
	dup2(log_fd, STDERR_FILENO);

	//输出日志
	syslog(LOG_EMERG, "The msg is: %s.", "LOG_EMERG");
	syslog(LOG_ALERT, "The msg is: %s.", "LOG_ALERT");
	syslog(LOG_CRIT, "The msg is: %s.", "LOG_CRIT");
	syslog(LOG_ERR, "The msg is: %s.", "LOG_ERR");
	syslog(LOG_WARNING, "The msg is: %s.", "LOG_WARNING");
	syslog(LOG_NOTICE, "The msg is: %s.", "LOG_NOTICE");
	syslog(LOG_INFO, "The msg is: %s.", "LOG_INFO");
	syslog(LOG_DEBUG, "The msg is: %s.", "LOG_DEBUG");

	closelog(); //关闭日志连接
	return 0;
}
```

运行结果，在日志文件`test.log`中：(GCC 6.1.1 && ArchLinux x64)

```
Test_log[28381]: The msg is: LOG_EMERG.
Test_log[28381]: The msg is: LOG_ALERT.
Test_log[28381]: The msg is: LOG_CRIT.
Test_log[28381]: The msg is: LOG_ERR.
Test_log[28381]: The msg is: LOG_WARNING.
Test_log[28381]: The msg is: LOG_NOTICE.
Test_log[28381]: The msg is: LOG_INFO.
Test_log[28381]: The msg is: LOG_DEBUG.
```



## Unix进程
进程是资源调度与分配的基本单位。  
在Unix中，进程具有以下概念：

`PID`(进程ID)
> PID是一个用于标志进程的非负整数，具有唯一性，且无法被用户修改。
> PID为`1`的进程为`init`进程。
> 获取进程ID使用`getpid()`函数：
>
>	```c
>	pid_t getpid(void);
>	```

`PPID`(父进程ID)
> 除了`init`进程外，其它进程都由先前存在的进程创建。
> 创建进程的进程称为**父进程**，被创建的进程称为**子进程**。
> 获取父进程ID使用`getppid()`函数：
>
>	```c
>	pid_t getppid(void);
>	```

`PGID`(进程组ID)
> **进程组**是一个或多个进程的集合，PGID等于组长进程的PID。
> 进程组相关函数：
>
>	```c
>	/*
>		设置指定PID进程的PGID。
>		pid参数取0时，设置当前进程的PGID。
>		pgid参数取0时，指定进程的PGID会被设置为与PID相同。
>		被设置进程组的进程原有PGID与新设置的PGID需要位于同一个会话(Session)中。
>	*/
>	int setpgid(pid_t pid, pid_t pgid);
>
>	// 得到指定PID进程的PGID，pid参数取0时获取当前进程PGID
>	pid_t getpgid(pid_t pid);
>	```

`SID`(会话ID)
> **会话**(`Session`)是一个或多个进程组的集合。
> 获取SID使用`getsid()`函数：
>
>	```c
>	// 获取指定PID进程的SID，pid参数取0时获取当前进程的SID
>	pid_t getsid(pid_t pid);
>	```
>
> 创建会话使用`setsid()`函数：
>
>	```c
>	pid_t setsid(void);
>	```
>
> 关于`setsid()`函数，需要注意：
>
>	- 如果调用进程不是进程组的组长，则创建新的会话。
>	- 调用进程将成为新会话中的会话首进程(Session Leader)。
>	- 调用进程将成为新会话的新进程组中的组长进程。
>	- 新的会话ID、进程组ID都将等于调用进程的PID。
>	- 新创建的会话将没有控制终端，无论原有会话是否有控制终端。

`Control Terminal`(控制终端)
> 控制终端用于与系统交互，在用户登陆时系统会自动为用户分配控制终端。
> 控制终端相关函数：
>
>	```c
>	// 返回指定文件描述符的控制终端的前台进程组ID
>	pid_t tcgetpgrp(int fd);
>	// 设置指定文件描述符的控制终端的前台进程组ID
>	int tcsetpgrp(int fd, pid_t pgrp);
>	```
>
> 控制终端与进程组、会话是密切相关的概念：
>
>	- 会话可以拥有控制终端。
>	- 建立与控制终端连接的会话首进程被称为控制进程。
>	- 带有控制终端的会话拥有前台进程组，其余进程组为后台进程组。
>	- 在控制终端中输入的中断键(`Ctrl + C`)、退出键会将中断信号(`SIGINT`)、退出信号(`SIGQUIT`)发送给前台进程组中的所有进程。

### 进程控制函数
常见的进程控制函数如下：

- 终止进程

	使用`exit()`系列函数退出进程：

	```c
	#include <stdlib.h>

	void exit(int status);
	void _Exit(int status);
	int atexit(void (*function)(void));

	#include <unistd.h>

	void _exit(int status);
	```

	`exit()/_exit()/_Exit()`之间的区别：

	- `exit()`为C标准库函数，是最常见进程退出函数，进程结束前会进行一些清理操作：
		1. 调用`atexit()`注册的清理函数。
		1. 刷新输出流，关闭已打开的流。
		1. 删除通过标准I/O函数`tmpfile()`创建的临时文件。
	- `_exit()`为系统调用，函数定义在`unistd.h`中，使用`_exit()`会立即结束进程，并且不会执行清理操作。
	- `_Exit()`为C标准库函数，定义在`stdlib.h`中，作用等价于系统调用`_exit()`。

- 创建进程

	C语言标准库中提供了`system()`函数用于创建进程：

	```c
	#include <stdlib.h>

	int system(const char *command);
	```

	`system()`函数的特点：

	- `system()`函数运行以字符串参数的形式传递给它的命令，并等待该命令的完成(效果类似于在Shell中使用对应命令)。
	- 与`exec()`函数不同，`system()`函数会新建一个Shell来执行命令。
	- 如果无法启动Shell来运行这个命令，`system()`函数将返回错误代码`127`；其它错误返回`-1`，否则`system()`函数将返回该命令的退出码(一般命令都是`0`)。
	- 在实际开发中，`system()`函数往往是很少被使用的，使用`system()`函数必须启动`Shell`执行指令，**效率不高**。

实际开发中，`fork() + exec()`是最常用的进程创建方式。

- `fork()` 函数

	在Unix环境下，`fork()`系统调用是最常见的创建进程方式，函数定义在`unistd.h`中，函数原型为：

	```c
	#include <unistd.h>

	pid_t fork(void);
	```

	`fork()`函数为当前进程创建一个相同的**拷贝**，原进程为**父进程**，新进程为**子进程**。  
	原进程的`fork()`函数返回子进程的`pid`，新进程的`fork()`函数返回`0`。
	
	新进程与原进程有着相同的**运行状态**和**代码**，即从`fork()`函数开始(包括`fork()`函数本身)接下来的代码原进程和新进程将会各执行一遍。  
	新的进程有**独立**的数据空间、环境、和文件描述符。  
	父进程中已经打开的文件描述符在子进程中依然会存在，父进程注册的信号处理函数在子进程依然有效。

	子进程不继承父进程的文件锁，父进程中未处理的信号集在子进程中被置为空集。  
	多进程并行执行时，各个进程是**异步乱序**执行的，因此不能确定各个进程各段代码的执行先后顺序，**不要**尝试编写依赖于其它进程执行结果的代码。

	实例代码：

	```c
	#include <stdlib.h>		//包含system()系统调用
	#include <stdio.h>
	#include <unistd.h>		//包含fork()、sleep()系统调用

	int main(void)
	{
		/*
			system()函数只执行了一次，
			可知在fork()函数拷贝的是fork()运行此刻运行状态，
			但fork()函数之前的内容依然只执行一次。
		*/
		if (!system("whoami"))
			printf("Run the system call successful!\n");

		/*
			fork()系统调用对于父进程返回子进程的pid，对于子进程返回0，
			fork()有可能执行失败，失败返回-1，并且不创建子进程。
		*/
		pid_t num = fork();

		if (num)
		{
			printf("This is parent process!\n");
			printf("The PID is %d\n", getpid());
			printf("The PPID is %d\n", getppid());
			sleep(2);		//程序运行到此暂停2秒
			system("ps");
		}
		else
		{
			printf("This is child process!\n");
			printf("The PID is %d\n", getpid());
			printf("Ths PPID is %d\n", getppid());
		}
		printf("End!\n");	//fork()之后的内容父进程子进程各执行一次
		return 0;
	}
	```

	运行结果：

	```
	dainslef
	Run the system call successful!
	This is parent process!
	The PID is 13722
	The PPID is 10480
	This is child process!
	The PID is 13724
	Ths PPID is 13722
	End!
	PID TTY          TIME CMD
	10480 pts/0    00:00:00 zsh
	13722 pts/0    00:00:00 a.out
	13724 pts/0    00:00:00 a.out <defunct>
	13725 pts/0    00:00:00 ps
	End!
	```

	由结果可知，`fork()`函数之前的`system("whoami")`函数只执行了一遍，因此shell指令`whoami`也只执行一遍。但在`fork()`函数之后的代码都执行了两遍，分别来自父进程和子进程的`printf()`函数向屏幕打印了两次`End!`。  
	由`system("ps")`函数中执行的shell指令`ps`向屏幕中输出的结果可以看出，父进程的`ppid`是启动这个进程的shell的`pid`，而**子进程**的`ppid`就是**父进程**的`pid`。

- `vfork()` 函数

	`vfork()`作用与`fork()`类似，函数定义在`unistd.h`中，如下所示：

	```c
	pid_t vfork(void);
	```

	相比`fork()`调用，`vfork()`有以下不同之处：

	- `fork()`子进程拷贝父进程中的数据段和代码段，`vfork()`中子进程与父进程共享数据段。
	- `fork()`调用之后父子进程执行顺序是**随机**的，`vfork()`中子进程在调用`exec()`或`exit()`之前与父进程数据共享，而父进程在子进程调用了`exec()`或`exit()`之前会一直**阻塞**。

	在Linux中，`fork()`与`vfork()`最终的内部实现都使用`do_fork()`。

- `exec()` 函数

	`exec()`系统调用，由一系列的相关函数组成，函数定义在`unistd.h`中，函数原型为：

	```c
	extern char **environ;
	int execl(const char *path, const char *arg0, ... /*, (char *)0 */);
	int execle(const char *path, const char *arg0, ... /*, (char *)0, char *const envp[]*/);
	int execlp(const char *file, const char *arg0, ... /*, (char *)0 */);
	int execv(const char *path, char *const argv[]);
	int execve(const char *path, char *const argv[], char *const envp[]);
	int execvp(const char *file, char *const argv[]);
	int fexecve(int fd, char *const argv[], char *const envp[]);
	```

	- `exec()`系列函数为**系统调用**，执行后，会将当前的进程**完全替换**为执行新程序的进程(即这个进程`exec()`调用成功之后的代码都不再运行)，但`PID`不变。
	- `exec()`系统调用比`system()`函数要**高效**，`exec()`与`fork()`搭配是Unix系统中最**常用**的系统进程创建组合。
	- 通常`exec()`不会返回，除非发生了错误。出错时，`exec()`返回`-1`并且置`errno`，同时继续执行余下的代码。
	- 在`exec()`函数组中，只有`execve()`函数是真正的系统调用，其它的几个函数都是`execve()`封装而成的库函数。
	- 参数`path`为绝对路径，`file`为命令名称。
	- `execl()`、`execlp()`、`execle()`三个函数接收的参数个数是可变的，参数以一个空指针结束(`(char*)0`或`NULL`)，用多个字符数组`*arg`来传递要执行的程序的参数。
	- `execv()`、`execp()`、`execve()`等函数参数个数是固定的，将要传递给要执行的程序的参数放在二维字符数组`*argv[]`中(对应main函数参数中的`*argv[]`)，而二维字符数组`*envp[]`中保存`exec()`函数要运行的程序的环境变量无论是传递给被执行程序的参数字符数组`*argv[]`或是环境变量字符数组`*envp[]`都要以一个空指针结尾。

	实例代码：

	```c
	#include <stdio.h>
	#include <unistd.h>

	int main(void)
	{
		char* envp[] = { "LC_ALL=zh_CN.UTF-8", NULL };

		/*
			不要想当然地认为*argv[]的第一个参数是没用的，
			第一个参数不能为NULL，否则exec()系统调用执行失败，
			而且exec()执行新指令时如果指令参数不正确时，
			指令在终端上显示的错误信息会将argv[0]作为输入的程序名！
		*/
		char* argv[] = { "ls", "-l", NULL };

		printf("The PID is %d\n", getpid());

		/*
			execve()系统调用的envp如果不需要设置可以填NULL。

			与system()函数不同，用exec系统调用在执行程序时，
			如果参数中的envp为NULL，则程序就在无环境变量的状态运行，
			即系统当前的环境变量不会对exec()系统调用产生影响，但会对依赖shell的system()函数产生影响。

			在这段代码中，如果用户为中文环境且exec()系统调用没有设置环境变量，
			则ls命令显示的中文目录会为问号，但system()函数执行ls命令则能正常显示。
		*/
		execve("/usr/bin/ls", argv, envp);
		/*
			上一句代码等价于
			execle("/usr/bin/ls", "ls", "-l", NULL, envp);

			如果运行一些不需要环境变量的程序，可以有更简单的方式，比如：
			execlp("ps", "ps", "-l", NULL);
		*/
		return 0;
	}
	```

子进程默认会继承父进程已打开的文件描述符。  
当父进程持有描述符为`Socket`描述符时，子进程会继承对应描述符代表的**监听端口**、**监听地址**等信息，当父进程结束时，端口不会被释放，而是由子进程继续占用。  
避免子进程继承`Socket`描述符，创建`Socket`时应设置`SOCK_CLOEXEC/FD_CLOEXEC`属性：

```c
// 在创建Socket描述符时使用 SOCK_CLOEXEC 属性
int sock_fd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC);

// 使用 fcntl() 调用对已创建的描述符追加 FD_CLOEXEC 属性
fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);
```

### 等待进程
可以在父进程中调用`wait()`函数让父进程等待子进程结束，还可以使用`waitpid()`函数来等待某个**特定进程**结束，函数定义在`sys/wait.h`中，函数原型为：

```c
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
```

- `status`参数为指向进程状态信息的指针，`wait()/waitpid()`函数都将状态信息写到`status`所指向的内容。
- `pid`参数为要等待的进程的`pid`，如果该参数为`-1`，则返回任一子进程的信息。
- `options`参数可用来改变函数的行为。

`wait()`函数返回子进程的`pid`。
`waitpid()`运行成功返回等待进程的`pid`，失败返回`-1`并置`errno`。

`/sys/wait.h`头文件中定义了宏来解释状态信息：

```c
/*
	Returns true if the child terminated normally,
	that is, by calling exit(3) or _exit(2), or by returning from main().
*/
WIFEXITED(status);

/*
	Returns  the  exit  status  of  the  child.

	This consists of the least significant 8 bits of the status argument
	that the child specified in a call to exit(3) or _exit(2)
	or as the argument for a return statement in main().

	This macro should be employed only if WIFEXITED returned true.
*/
WEXITSTATUS(status);

/*
	Returns true if the child process was terminated by a signal.
*/
WIFSIGNALED(status);

/*
	Returns the number of the signal that caused the child process to terminate.
	This macro should be employed only if WIFSIGNALED returned true.
*/
WTERMSIG(status);
...
```

实例代码：

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	printf("The PID is %d\n\n", getpid());
	pid_t pid = fork();

	if (pid)
	{
		int status;
		int child_pid = waitpid(pid, &status, 0);	//等效于 int child_pid = wait(&status);

		printf("This is the parent process!\n");
		printf("The PID is %d\n", getpid());

		if (pid == child_pid)
			printf("The child's PID is %d\n", child_pid);

		/*
			若等待进程正常结束， WIFEXITED 宏返回非0值
			若 WIFEXITED 非0，打印等待进程的退出码
		*/
		if (WIFEXITED(status))
			printf("The child process's exit_code is %d\nParent process END!\n", WEXITSTATUS(status));
		_exit(0);
	}

	if (!pid)
	{
		printf("This is the child process!\n");
		sleep(3);
		printf("The PID is %d\nChild process END!\n\n", getpid());
		_exit(100);
	}
}
```

运行结果：

```
The PID is 9411

This is the child process!
The PID is 9412
Child process END!

This is the parent process!
The PID is 9411
The child's PID is 9412
The child process's exit_code is 100
Parent process END!
```

### *Daemon* (守护进程)
**守护进程**是一类具有较长生存周期的进程，守护进程在后台运行，并且没有控制终端。

编写守护进程一般有如下几个步骤：

1. 调用`fork()`函数，同时退出**父进程**。

	使用了`fork()`函数之后父进程退出，则子进程成为孤儿进程，由`init系统`接管。  
	子进程虽然脱离了父进程，但仍然处于父进程的进程组中和会话中，与控制终端的联系依然存在。

1. 调用`setsid()`函数，为子进程创建新的会话。

	使用了`setsid()`函数，子进程脱离了原先父进程的进程组与会话，并且不再与原先的控制终端相关联。  
	子进程在创建了会话之后成为了会话和新进程组的**首进程**，依然有可能被系统分配控制终端。

1. 再次调用`fork()`函数，再次退出**父进程**。

	再次`fork()`退出父进程之后，新的子进程不再是进程组和会话的首进程，不再有被分配控制终端的可能。

实例代码：

```c
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

// 打印进程的PID、PPID、SID、PGID、控制终端等信息
void print_process_info(char* msg)
{
	char cmd[50] = { 0 };
	sprintf(cmd, "ps --pid %d -o cmd,stat,pid,ppid,pgid,sid,tpgid,tty", getpid());

	printf("%s:\n", msg);
	system(cmd);
	printf("\n");
}

void create_daemon()
{
	print_process_info("Before fork");

	// fork()并退出父进程
	if (fork())
		_exit(0);
	print_process_info("After fork once");

	// 若正常fork()，则此时父进程已退出，子进程由init系统接管
	// 使用setsid()创建新的会话(New Session)，同时使当前进程为新会话的进程组组长
	setsid();
	print_process_info("After setsid");

	// fork()并退出父进程，之后子进程不再是会话的组长进程
	if (fork())
		_exit(0);
	print_process_info("After fork twice");

	pause();
}

int main(int argc, char *argv[])
{
	create_daemon();
	return 0;
}
```

运行结果：(GCC 6.1.1 && ArchLinux x64)

```
Before fork:
CMD                         STAT   PID  PPID  PGID   SID TPGID TT
./a.out                     S+   10091  1918 10091  1918 10091 pts/1

After fork once:
CMD                         STAT   PID  PPID  PGID   SID TPGID TT
./a.out                     S    10093   613 10091  1918  1918 pts/1

After setsid:
CMD                         STAT   PID  PPID  PGID   SID TPGID TT
./a.out                     Ss   10093   613 10093 10093    -1 ?

After fork twice:
CMD                         STAT   PID  PPID  PGID   SID TPGID TT
./a.out                     S    10103   613 10093 10093    -1 ?
```



## *signal* (信号)
信号是Unix系统响应某些条件而产生的的一个事件，进程接收到信号会采取一些相应的行动。  
信号的相关函数定义在头文件`signal.h`中。

使用`fork()`时，子进程会继承父进程注册的信号处理函数。

常用的信号有`SIGINT`(中断信号，用`CTRL + C`触发)，`SIGQUIT`(退出信号)。  
使用`kill`指令发送信号，默认发送信号为`SIGTERM`。

### 处理信号
使用`signal()`或`sigaction()`函数将需要处理的信号与信号处理函数的函数指针绑定。

- `signal()` 函数

	`signal()`函数是传统Unix的信号处理方式。函数原型为：

	```c
	#include <signal.h>

	void (*signal(int sig, void (*func)(int)))(int);
	```

	- `sig`参数为要处理的信号。
	- `func`参数为要绑定的信号处理函数。

	对于信号处理函数函数指针参数`func`，存在两个特殊值：

	- `SIG_IGN` 将其绑定到一个信号上则表示**忽略信号**
	- `SIG_DFL` 将信号的处理方式恢复为**默认动作**

- `sigaction()` 函数

	现代Unix中，使用更加健壮的信号编程接口`sigaction()`函数，函数的原型为：

	```c
	#include <signal.h>

	struct sigaction
	{
		union __sigaction_u __sigaction_u; /* signal handler */
		sigset_t sa_mask; /* signal mask to apply */
		int sa_flags; /* see signal options below */
	};

	union __sigaction_u
	{
		void (*__sa_handler)(int);
		void (*__sa_sigaction)(int, siginfo_t *, void *);
	};

	#define sa_handler __sigaction_u.__sa_handler
	#define sa_sigaction __sigaction_u.__sa_sigaction

	int sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);
	```

	- 参数`act`指向包含信号处理函数的结构体。
	- 参数`oact`会被写入原先的信号处理结构体(可以取`NULL`)。

	其中，结构体`sigaction`成员：

	- `sa_handler` 指向信号处理函数的函数指针
	- `sa_mask` 屏蔽信号字，可以使用`sigemptyset(*sigset_t)`函数将信号集置空
	- `sa_flags` 设置信号处理选项，没有特别要求可以设为`NULL`
	```

### 发送信号
使用`kill()`函数可以向**指定进程**发送信号，使用`raise()`可以向**当前进程**发送信号。函数定义在`signal.h`中，如下所示：

```c
int raise(int sig);
int kill(pid_t pid, int sig);
```

- `pid`参数为目标进程的进程id。
- `sig`为信号值。

使用`kill()`、`raise()`发送信号，接收信号的是**整个**目标进程。

在**多线程**环境下，使用`kill()`、`raise()`发送信号，进程内包含的**所有线程**都会接收到信号。  
如果需要发送信号给**指定线程**，需要使用`pthread_kill()`，函数定义在`signal.h`中：

```c
int pthread_kill(pthread_t thread, int sig);
```

- `thread`参数为目标线程的描述符。
- `sig`参数为信号值。

函数成功返回`0`，失败时返回错误代码。

### 信号触发
信号机制实质上是**软件中断**，信号处理函数**不会**运行在独立的线程，而是**中断**现有的代码运行信号处理函数。  
一个进程触发了信号处理函数，则在信号处理函数结束返回之后才会继续运行先前的代码。

如下代码所示：

```c
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

void deal_signal(int sig)
{
	printf("\nRun deal_signal().\n");
	sleep(5);
}

int main(void)
{
	signal(SIGINT, deal_signal);

	int count = 0;
	while (1)
	{
		time_t before = time(NULL);

		sleep(1);
		printf("Loop %d\n", ++count);

		time_t cost = time(NULL) - before;
		struct tm* t = localtime(&cost);
		printf("Cost time: %d seconds.\n\n", t->tm_sec);
	}

	return 0;
}
```

通过循环中的打印的耗时可以看出，每次触发信号处理函数`deal_signal()`，循环便会**暂停**，直到`deal_signal()`运行完毕返回。  
在`BSD`和`Linux`中，运行信号处理函数期间再次收到信号会**阻塞**此信号，直到信号处理函数返回。  
在部分Unix中，运行信号处理函数时可能会将此信号**重置**为默认操作，在此类情况下，需要在信号处理函数中重新绑定信号。

### 可靠信号与不可靠信号
可靠信号机制最初来自于`BSD`。

在`Linux`中，**不可靠**信号范围为`1(SIGHUP) ~ 31(SIGSYS)`，**可靠信号**的范围为`34(SIGRTMIN) ~ 64(SIGRTMAX)`。  
**不可靠**信号**不支持**信号队列，当同类信号在短时间内**多次**触发，不可靠信号只会触发信号处理函数**一次**，其余的同类信号被**忽略**。

### 屏蔽信号
直接在**进程**中屏蔽指定信号可以使用下列函数，函数定义在`signal.h`中：

```c
#include <signal.h>

int sigsetmask(int mask); //设定屏蔽信号为mask
int sigblock(int mask); //向现有屏蔽信号中添加mask
```

- `mask`参数为要屏蔽的信号**mask**，由`sigmask(signum)`宏根据输入的信号值生成。

函数返回之前设定的**mask**值。  
实例代码如下：

```c
//多个信号可以使用逻辑或操作符相连
int mask = sigmask(SIGINT) | sigmask(QUIT);
//设置当前的信号屏蔽为SIGINT和SIGQUIT
sigsetmask(mask);
//添加屏蔽SIGALRM信号
sigblock(sigmask(SIGALRM));
```

也可以使用`sigprocmask()`来完成信号屏蔽/解除屏蔽等操作，函数定义在`signal.h`中：

```c
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
```

- `how`参数定义函数的行为，取值如下：

	1. `SIG_BLOCK` 向已有的屏蔽信号集合中**添加**`set`参数中的信号
	1. `SIG_UNBLOCK` 向已有的屏蔽信号集合中**移除**`set`参数中的信号
	1. `SIG_SETMASK` 将当前的屏蔽信号集合**替换**为`set`参数中的信号

- `set`参数为输入的信号集合。
- `oset`参数为输出信号集合，函数运行结束会将新的信号集合写入`oset`参数中，不需要该参数可设为`NULL`。

函数执行成功返回`0`。执行失败返回`-1`，并置`errno`。  
实例代码如下：

```c
//创建信号集合，置空后添加SIGINT信号
sigset_t set;
sigemptyset(&set);
sigaddset(&set, SIGINT);

//屏蔽SIGINT信号
sigprocmask(SIG_SETMASK, &set, NULL);

//信号集加入SIGQUIT信号
sigaddset(&set, SIGQUIT);

//添加屏蔽SIGUQUIT信号
sigprocmask(SIG_BLOCK, &set, NULL);

//取消SIGINT和SIGQUIT的信号屏蔽
sigprocmask(SIG_UNBLOCK, &set, NULL);
```

### 屏蔽线程信号
`sigsetmask()`和`sigprocmask()`等函数设置的屏蔽信号对于**整个进程**有效。  
在**多线程**环境下，使用`sigprocmask()`则进程内包含的**所有线程**的屏蔽信号集都会被修改。  
创建新的线程时，新的线程会**继承**原有线程的**屏蔽信号集**。

需要设置**指定线程**的屏蔽信号集，可以使用`pthread_sigmask()`函数，函数定义在`signal.h`中：

```c
int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
```

`pthread_sigmask()`函数参数与作用与`sigprocmask()`类似，有两点区别：

- 设置的屏蔽信号集仅对**当前线程**生效。
- 调用失败时直接返回错误代码，而不是像`sigprocmask()`那样返回`-1`并置`errno`。

### 信号相关的进程控制函数
`pause()`、`sleep()`等函数在多线程情况下的触发机制。

- `pause()` 函数
	
	使用`pause()`可以挂起线程，直到当前进程捕捉到了一个**信号**，函数定义在`unistd.h`中，如下所示：

	```c
	int pause(void);
	```

	只有进程捕获了信号，执行了信号处理程序并从其返回时，`pause()`函数才返回。
	`pause()`函数**不存在**成功返回值，当进程捕捉到信号并从信号处理函数返回时，`pause()`返回`-1`，并置`errno`为`ENTER`。

	在**多线程**环境中，在未设置`pthread_sigmask()`的情况下，信号优先级使得只有**主线程**的`pause()`会在信号处理函数结束后返回。  
	在主线程以外的线程中，除非使用`pthread_kill()`发送消息到指定线程，否则无法触发`pause()`函数。

- `sleep()` 函数

	使用`sleep()`可以**挂起**线程(阻塞)，函数定义在`unistd.h`中，函数原型为：

	```c
	unsigned int sleep(unsigned int seconds);
	```

	- `seconds`参数为需要休眠的时间，单位为**秒**。

	若线程在设定的时间中正常休眠，返回值为`0`。  
	若在挂起期间进程捕获到一个**信号**，并从信号处理函数返回，则无论休眠时间是否满足，休眠不再继续，`sleep()`立即函数结束，返回值为**尚未休眠**的时间。

	在**多线程**环境中，在未设置`pthread_sigmask()`的情况下，捕获信号，并从信号处理函数返回，只会结束进程**主线程**中正在运行的`sleep()`函数，对其它线程中的`sleep()`无影响。

	在`Solaris`中`sleep()`内部实现采用`alarm()`，在`BSD`和`Linux`中`sleep()`由`nanosleep()`实现，与信号无关。

- `alarm()` 函数

	使用`alarm()`可以使当前进程在指定时间之后收到`SIGALRM`信号，函数定义在`unistd.h`中，如下所示：

	```c
	unsigned alarm(unsigned seconds);
	```

	- `seconds`参数为发送信号的延迟时间，取`0`时表示清除原有`alarm()`设置。

	一个进程同时只能存在一个`alarm()`，调用`alarm()`时若之前已经设置了`alarm()`且尚未触发，则返回上一个`alarm()`的剩余等待时间，同时以当前`alarm()`的设置**替换**上一个。  
	默认情况下，若没有设置`SIGALRM`的信号处理函数，系统收到`SIGALRM`会终止进程。

### 多线程信号处理
在多线程的环境下，信号处理需要考虑更多的情况：

- 默认情况下，Unix中的信号机制是对于**整个进程**而言的，使用`kill()`发送信号，则**整个进程**都将收到信号。
- 使用`signal()`绑定信号处理函数会对**整个进程**生效。
- 在多线程的程序中，若不做特殊处理，则发送给进程的信号会由系统选择一个线程来处理信号。
- 系统会在**没有**屏蔽此信号的线程中选择`pid`**最小**的那个线程来处理信号。
- 在未设置屏蔽信号的情况下，主线程的`pid`最小，因而一般会选择**主线程**来响应信号。  
	这使得**默认情况**下只有**主线程**的`pause()`、`sleep()`函数能够被信号中断。

多线程环境下的信号处理一般有两种方式：

- 在指定线程中处理信号：

	除目标线程外，其它线程全部使用`pthread_sigmask()`在线程中屏蔽指定信号，让信号只能被**指定线程**处理。如下所示：

	```c
	#include <stdio.h>
	#include <unistd.h>
	#include <signal.h>
	#include <pthread.h>

	sigset_t set;

	void deal_signal(int sig)
	{
		printf("Run deal_signal.\n");
	}

	void* thread_func(void* arg)
	{
		printf("Run thread!\n");

		//解除SIGINT的信号屏蔽，让当前线程能够处理SIGINT信号
		pthread_sigmask(SIG_UNBLOCK, &set, NULL);

		while (1)
			printf("Pthread sleep surplus time: %d seconds.\n", sleep(3));
		return NULL;
	}

	int main(void)
	{
		signal(SIGINT, deal_signal);

		//整个进程屏蔽SIGINT信号
		sigemptyset(&set);
		sigaddset(&set, SIGINT);
		sigprocmask(SIG_BLOCK, &set, NULL);

		pthread_t pfd;
		pthread_create(&pfd, NULL, thread_func, NULL);

		pthread_join(pfd, NULL);

		return 0;
	}
	```

	默认情况下，`SIGINT`信号会被主线程处理(不会中断子线程中的`sleep()`)。  
	通过设置屏蔽信号，让`SIGINT`被主线程屏蔽而由子线程处理，使得`SIGINT`能够中断子线程的`sleep()`函数，让`sleep()`提前结束。

- 以同步的方式处理异步信号：

	使用`sigwait()`函数等待指定信号。`sigwait()`函数定义在`signal.h`中：

	```c
	int sigwait(const sigset_t *restrict set, int *restrict sig);
	```

	- `set`参数为要等待的信号集合。
	- `sig`参数指向等待到的信号值，函数会将等待到的信号值写入传入的地址中。

	运行`sigwait()`会阻塞所处线程，直到所处线程接受到`set`信号集中的信号。  
	函数执行成功返回`0`，失败时返回错误代码。  
	使用`sigwait()`需要保证等待的信号至少被`sigwait()`**所处线程**之外的线程屏蔽。

	对于`sigwait()`所处的线程，在`OS X`和`Linux`等Unix系统上，`sigwait()`的优先级比默认的信号处理行为以及绑定的信号处理函数要高，接受到信号时，优先结束`sigwait()`的阻塞而不是执行设定/默认的信号处理行为。

	在**多个**`sigwait()`共存的情况下，系统会**随机**选取一个线程中的`sigwait()`进行响应。

	实例如下所示：

	```c
	#include <stdio.h>
	#include <signal.h>
	#include <pthread.h>

	sigset_t set;
	int thread_count = 0;
	pthread_mutex_t mutex;

	//由于sigwait()优先级更高，deal_signal()函数并未触发
	void deal_signal(int sig)
	{
		printf("Run deal_signal.\n");
	}

	void* thread_func(void* arg)
	{
		pthread_mutex_lock(&mutex);
		int thread_id = ++thread_count;
		pthread_mutex_unlock(&mutex);

		printf("Run thread %d!\n", thread_id);

		//子线程即便使用pthread_sigmask()解除SIGINT信号屏蔽，依旧会优先响应sigwait()
		int signum;
		sigwait(&set, &signum);

		if (signum == SIGINT)
			printf("\nThread %d receive signal SIGINT.\n", thread_id);

		return NULL;
	}

	int main(void)
	{
		signal(SIGINT, deal_signal);

		/*
			设置主线程信号屏蔽。
			若主线程不屏蔽SIGINT信号，则按照信号处理优先级，信号会被主线程处理。
			信号被主线程处理，子线程没有处理信号的机会，则sigwait()会一直阻塞。
		*/
		sigemptyset(&set);
		sigaddset(&set, SIGINT);
		sigprocmask(SIG_BLOCK, &set, NULL);

		pthread_mutex_init(&mutex, NULL);

		pthread_t pfd;
		pthread_create(&pfd, NULL, thread_func, NULL);
		pthread_create(&pfd, NULL, thread_func, NULL);

		pthread_join(pfd, NULL);

		pthread_mutex_destroy(&mutex);

		return 0;
	}
	```

	运行结果：(OS X 10.11.3)

	```
	Run thread 1!
	Run thread 2!
	^C
	Thread 2 receive signal SIGINT.
	^C
	Thread 1 receive signal SIGINT.
	```

	多个`sigwait()`存在时，选取的处理线程是随机的，运行结果也可能是1号线程先响应信号。



## POSIX 线程(pthread)
在Unix系统中，多线程开发相关函数定义在头文件`pthread.h`中。  
在`Linux`中编译使用了线程库的程序时，需要链接`pthread`库，编译指令如下：

```sh
$ cc -lpthread [源码文件]
```

在`FreeBSD`以及`OS X`中，编译使用了线程库的程序**无需**链接`pthread`库。

### Linux下的线程实现
`Linux Kernel 2.6`之后，线程的实现为`NPTL`，即**本地POSIX线程库**`Native POSIX Thread Library`。

- 在Linux内核中，线程和进程都使用`task_struct`结构体表示，线程仅是一类特殊的进程(创建时使用不同的`clone`标识组合)。
- Linux提供了`clone()`调用，使用`clone()`创建子进程时，可以选择性地共享父进程的资源，创建出的子进程被称为**轻量级进程**(`LWP, Low Weight Process`)。
- 早期的Linux(`Linux Kernel 2.6`之前)使用`Linux Threads`线程库，即通过**轻量级进程**来实现线程。
- `Linux Threads`库没有实现`POSIX`的线程定义，每个线程在`ps`指令下显示为进程，并且不同线程使用`getpid()`返回的进程`pid`也不相同，在现代Linux(采用`NPTL`之后的Linux)已经**不会**出现此类情况。
- 在`Linux Kernel 2.6`之后，内核中有了**线程组**的概念，`task_struct`结构中增加了`tgid(thread group id)`字段，如果一个`task_struct`是一个**主线程**, 则它的`tgid`等于`pid`, 否则`tgid`等于进程的`pid`(即主线程的`pid`),此外，每个线程依旧是一个`task_struct`，依然有自己的`pid`。
- 在`Linux Kernel 2.6`之后，使用`getpid()`获取的是`tgid`，因而进程中的每个线程使用`getpid()`返回值相同(主线程`pid`)。获取线程自身的`pid`需要用到系统调用`gettid()`，`gettid()`是Linux特有的系统调用，在其它Unix中并不存在，`glibc`没有提供`gettid()`的封装，使用`gettid()`需要通过`syscall()`调用。
- `NPTL`的实现依赖于`Linux Kernel 2.6`内核的`task_struct`改动，因此在`2.4`、`2.2`等旧版本的内核上无法使用`NPTL`，在采用了`NPTL`的Linux上，线程的行为与其它Unix更为相似。

### 创建线程
创建线程使用`pthread_create()`函数。

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

- `thread`参数为将新建线程的线程标志符写入所给的地址(注意线程标识符的类型为`pthread_t`，使用`int`型编译器会提示**不兼容**)。
- `attr`参数为启动线程时设置**特殊属性**(一般情况下用不到，填`NULL`即可)。
- `start_routine`参数为一个指向返回值和参数都为void*类型的函数的函数指针，该指针指向的函数即为新线程要执行的函数。
- `arg`参数为要传递到`start_routine`所指向函数的值(如果没有需要传递的参数，可以填**NULL**)。

需要注意的是，`thread`参数必须要填入**有效**的地址，填`NULL`会引起程序崩溃。
创建新线程成功则返回`0`，未创建成功返回**错误代码**(**不一定**是`-1`)，可根据man手册查看错误代码判断错误类型。

### 等待线程
等待线程使用`pthread_join()`函数。

```c
int pthread_join(pthread_t thread, void **retval);
```

- `thread`参数为要等待的线程的**线程描述符**。
- `retval`参数为要等待的线程的返回值的地址(不使用线程返回值则可以填`NULL`)。

该函数为**阻塞**函数。
需要注意的是，`pthread_join()`函数只会等待指定线程标识符对应的线程，对其它线程不会造成影响，依然是并发执行。

默认情况下，主程序是不会等待线程执行的，无论线程是否执行完毕，主程序都会依次执行直到结束。由于线程是共享资源的，一旦主程序结束了，该程序创建的线程无论是否执行完毕都会立即被关闭。如果需要主程序等待某个线程执行完毕，即可以使用`pthread_join()`函数。

### 取消线程
取消线程使用`pthread_cacnel()`函数。

```c
int pthread_cancel(pthread_t thread);
```

- `thread`参数为需要取消的线程的**线程描述符**。

取消线程成功返回值为`0`，取消线程失败返回一个非`0`的**错误代码**(不一定是-1)。

### 终止线程
退出、终止一个线程使用`pthread_exit()`函数。

```c
void pthread_exit(void *retval);
```

线程调用该函数终止自身，如同进程的`exit(num)`函数一样。

`pthread_exit()`函数的参数为线程的返回内容，需要注意的是，不要将`retval`指向一个**局部变量**，因为调用`pthread_exit()`函数之后线程会结束，线程函数内的局部变量(栈变量)将会被**删除**。
与其它函数一样，线程也可以使用`return`提供返回值。

### 用互斥量进行线程同步
互斥量相关的函数也定义在头文件`pthread.h`文件中，常用的函数有：

```c
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

互斥量可以让程序员锁住某个对象，使得每次只有一个线程能对其进行访问。
`pthread_mutex_lock()`在未成功加锁时会一直阻塞线程。
使用`pthread_mutex_init()`函数初始化一个互斥量，`mutex`参数为要初始化的互斥量，`attr`参数为互斥量属性，没有特殊要求可以设置为`NULL`(默认为**线程同步**)。

实例代码：

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define MYMES1 SIGUSR1 + 1			//自定义信号，不能设置太大，Linux中32～64信号为用户可用
#define MYMES2 SIGUSR1 + 2

pthread_t thread_fd = 0;
pthread_t thread_fd1 = 0;
pthread_mutex_t mutex;

void deal_signal(int signal)
{
	switch(signal)
	{
	case SIGQUIT:		//捕获SIGQUIT信号，用 "ctrl+\" 组合键触发
		pthread_cancel(thread_fd);					//取消一号线程
		pthread_cancel(thread_fd1);					//取消二号线程
		printf("结束一、二号线程，接下来三、四号线程没有互斥量，输出内容会相互交错！\n");
		if (pthread_mutex_destroy(&mutex) == -1)		//删除锁，实际删除锁没什么用。。。
			printf("删除失败！\n");
		break;
	case MYMES1:
		printf("有互斥变量的时候，内容不会交错。\n");
		break;
	case MYMES2:
		printf("没有互斥变量的时候，内容会相互交错。\n");
		break;
	}
}

void* thread_func(void* arg)
{
	while (1)
	{
		if (!strcmp(arg, "三号线程") || !strcmp(arg, "四号线程"))
			kill(getpid(), MYMES2);		//三号、四号线程发送自定义信号MYMES2
		else if (pthread_mutex_lock(&mutex) == -1)
			printf("加锁失败！\n");
		else
			kill(getpid(), MYMES1);		//一号、二号线程发送自定义信号MYMES1

		printf("%s开始。\n", (char*)arg);

		int num = 0;
		while (num++ < 3)
		{
			sleep(2);
			printf("%s循环第%d次\n", (char*)arg, num);
		}

		if (pthread_mutex_unlock(&mutex) == -1)
			printf("解锁失败！\n");

		sleep(2);			//线程休眠一秒，否则资源会一直被一个线程占有
	}
}

int main(void)
{
	char* str1 = "一号线程";
	char* str2 = "二号线程";
	char* str3 = "三号线程";
	char* str4 = "四号线程";

	struct sigaction sig;
	sig.sa_handler = deal_signal;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGQUIT, &sig, 0);		//现代Unix信号捕捉函数

	signal(MYMES1, deal_signal);		//传统Unix信号捕捉函数
	signal(MYMES2, deal_signal);

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread_fd, NULL, thread_func, str1);
	pthread_create(&thread_fd1, NULL, thread_func, str2);
	pthread_join(thread_fd1, NULL);			//等待二号线程结束
	pthread_create(&thread_fd, NULL, thread_func, str3);		//创建三号线程
	pthread_create(&thread_fd, NULL, thread_func, str4);		//创建四号线程
	pthread_join(thread_fd1, NULL);

	return 0;
}
```

### 使用互斥量进行进程同步
互斥量用于**进程同步**时，会用到下列函数，头文件同样在`pthread.h`中：

```c
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict attr, int *restrict pshared);
```

通过设置`pthread_mutex_init()`函数的参数`attr`来实现**进程间互斥**。  
使用以下方式初始化`pthread_mutexattr_t`结构体。

```c
pthread_mutexattr_t attr;
pthread_mutexattr_init(&attr);
pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED); //第二个参数如果取PTHREAD_PROCESS_PRIVATE则互斥量仅为进程内部所使用，这是默认情况，即pthread_mutex_init()函数的第二个参数取NULL时的情况
```

需要注意的是，由于每个进程的地址空间是独立的，每个进程定义的变量无法被其它进程所访问。

若需要使用互斥量进行进程间的同步，不仅需要设置其共享属性，还需要使用Unix的**共享内存**机制，开辟一块共享内存，将互斥量定义在**共享内存**中，以此来保证一个互斥量能被多个进程访问，实现进程互斥。

实例代码：

文件 `process_mutex_parent.c`：

```c
#define PROJECT_ID 0
#define PATH "/home/dainslef"

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/shm.h>				//包含共享内存的相关函数

int shm_id;							//共享内存标志，类似于文件标识符
pthread_mutexattr_t attr;

void dealSignal(int signal)
{
	if (signal == SIGQUIT
			&& !pthread_mutex_unlock((pthread_mutex_t*)shmat(shm_id, NULL, 0)))
	{
		printf("解锁互斥量成功！\n父进程即将结束！\n");
		for (int i = 5; i > 0; i--)
		{
			printf("倒数计时：%d\n", i);
			sleep(1);
		}
		printf("父进程结束！\n");
		_exit(0);
	}
}

int main(void)
{
	shm_id = shmget(ftok(PATH, PROJECT_ID), sizeof(pthread_mutex_t), IPC_CREAT | 0600);
	pthread_mutex_t *mutex = (pthread_mutex_t*)shmat(shm_id, NULL, 0);

	pthread_mutexattr_init(&attr); //初始化权限结构体attr
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

	if (!pthread_mutex_init(mutex, &attr))
		printf("成功创建了互斥量！\n"); //创建了一个进程互斥的互斥量

	signal(SIGQUIT, dealSignal);
	printf("父进程启动：\n");

	if (!pthread_mutex_lock((pthread_mutex_t*)shmat(shm_id, NULL, 0)))
		printf("父进程互斥量加锁成功！");

	while (1)
	{
		printf("父进程在执行！\n");
		sleep(2);
	}

	return 0;
}
```

文件 `process_mutex_child.c`：

```c
#define PROJECT_ID 0
#define PATH "/home/dainslef"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>

int shm_id;
pthread_mutexattr_t attr;

int main(void)
{
	shm_id = shmget(ftok(PATH, PROJECT_ID), sizeof(pthread_mutex_t), 0);
	pthread_mutex_t *mutex = (pthread_mutex_t*)shmat(shm_id, NULL, 0);

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

	printf("子进程启动：\n");

	if (!pthread_mutex_lock((pthread_mutex_t*)shmat(shm_id, NULL, 0)))
		printf("子进程互斥量加锁成功！");

	while (1)
	{
		printf("子进程在执行！\n");
		sleep(2);
	}

	return 0;
}
```

运行结果：(文字描述)

`Process_Mutex_Parent`先运行，创建互斥量并锁住，然后一直循环。  
`Process_Mutex_Child`后执行，进程阻塞在`pthread_mutex_lock()`函数上。  
在`Process_Mutex_Parent`中触发`SIGQUIT`信号，由信号处理函数释放锁，倒数计时后结束进程。  
`Process_Mutex_Child`在`Process_Mutex_Parent`释放互斥量锁之后立即加锁成功，开始循环。



## *XSI IPC*
`XSI IPC`包括**消息队列**、**共享内存**、**信号量**。
`XSI IPC`来自`SystemV`，三类`XSI IPC`拥有相似的API，包括如下的一组函数：

```c
int xxxget(key_t key, ...);			//创建/获取IPC文件描述符
int xxxctl(int ipc_fd, ...);		//添加IPC设定
...
```

### IPC标志
`XSI IPC`都使用类型为`key_t`的`key`值来区分不同的IPC。`key`值可以通过以下函数生成：

```c
#include <sys/types.h>
#include <sys/ipc.h>
key_t ftok(const char *pathname, int proj_id);
```

- `pathname`参数为约定的路径。
- `proj_id`参数为约定的项目编号。

通过指定**路径**和**项目编号**能够得到唯一的`key`值。  
函数执行成功返回生成的`key`值，执行失败返回`-1`。

### XSI IPC特点
`XSI IPC`并没有遵循Unix中`一切皆文件`的思想，`XSI IPC`在文件系统中没有名字，不能使用文件描述符进行表示，不能使用`open()`、`write()`等文件操作对其进行控制，亦不能对其使用`select()`、`epoll()`、`kqueue()`等IO复用机制。

`XSI IPC`不能使用传统的shell指令进行管理，不能使用`ls`查看，不能使用`rm`删除。

查看`XSI IPC`使用`ipcs`指令：

```
$ ipcs
```

删除`XSI IPC`使用`ipcrm`指令：

```
$ ipcrm { shm | msg | sem } id
```



## *SystemV* 共享内存
共享内存是一种进程间通信(IPC, Inter-Process Communication)机制，属于三类`XSI IPC`之一。

相比信号量等IPC机制，共享内存有着最高的效率，因为共享内存不涉及复制操作。

共享内存的相关函数定义在`sys/shm.h`中。

### 创建/获取共享内存
使用`shmget()`函数创建共享内存或获取已经存在的**key值**的共享内存。

```c
int shmget(key_t key, size_t size, int shmflg);
```

- `key`参数为`ftok()`函数生成的**共享内存**标志。
- `size`参数为共享内存的大小。
- `shmflg`参数为特殊标识，取`0`时获取**key值**对应的共享内存，若传入的**key值**对应的共享内存**未创建**，则调用**失败**。

创建共享内存使用`IPC_CREAT`标识，创建的同时可以手动设定共享内存的读写权限如`IPC_CREAT | 0660`。  
使用`IPC_CREAT`标识时，若传入**key值**对应的共享内存已经存在，不会调用失败，而是忽略该标识，返回已存在的共享内存的描述符。  
如果需要创建一块**唯一**的共享内存，则使用`IPC_CREAT | IPC_EXCL`。  
使用`IPC_CREAT | IPC_EXCL`标识时，若传入`key`参数对应的共享内存已存在，则创建**失败**。  
`IPC_PRIVATE`标志用于创建一个只属于创建进程的共享内存。  
共享内存创建成功时返回**共享内存描述符**(非负整数)，失败时返回`-1`。

### 获得共享内存地址
使用`shmat()`函数获取共享内存的**地址**。

```c
void *shmat(int shmid, const void *shmaddr, int shmflg);
```

- `shmid`参数为目标共享内存描述符。
- `shmaddr`参数为将共享连接到当前进程中的地址，如果不需要指定共享内存连接到进程中的**指定地址**，则该参数可以为`NULL`(让系统分配可用的地址)。
- `shmflg`参数为一组标志位，如果`shmaddr`参数手动指定了地址，则搭配`shmflg`参数取`SHM_RND`，如果**只读**共享内存则设定`SHM_RDONLY`，不使用此参数可设为`0`。

函数运行成功返回**共享内存**的**首地址**，运行失败返回数值`-1`。

### 分离共享内存
使用`shmdt()`函数分离共享内存。

```c
int shmdt(const void *shmaddr);
```

- `shmaddr`参数为共享内存的**首地址**，运行成功之后共享内存在调用此函数的进程中将**不再可用**(但其它进程中依然**正常**)。

调用成功时返回`0`，失败返回`-1`。

### 控制共享内存
使用`shmctl()`函数设置共享内存的**标识**。

```c
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

- `shmid`参数为共享内存描述符。
- `command`参数为要对共享内存发出的指令，常用的指令为`IPC_RMID`，用于**删除**共享内存，执行删除操作时- `buf`参数可以取值`NULL`。

函数调用成功返回`0`，失败返回`-1`。

与信号量机制类似，如果`shmget()`函数以`IPC_CREAT | IPC_EXCL`的形式创建**唯一**共享内存的话，如果没有在进程结束前将共享内存删除，则下次程序执行时将**不能**够再以`IPC_CREAT | IPC_EXCL`的形式创建**key值**相同的共享内存！



## SystemV 信号量(Semaphore)
信号量是一种进程间通信(`IPC, Inter-Process Communication`)机制，属于三类`XSI IPC`之一。  
信号量用于控制进程对资源的访问，但信号量也可以用于线程。  
在进程开发中，常用的信号量函数定义在`sys/sem.h`文件中。

### 创建/获取信号量
使用`semget()`函数创建一个新的信号量或获取一个已经存在的信号量。

```c
int semget(key_t key, int num_sems, int sem_flags);
```

- `key`参数为`ftok()`函数生成的**信号量**标志。
- `num_sems`参数为需要的信号量数目，一般为`1`。
- `sem_flags`参数为信号量标志位，多个标志通过逻辑或操作符`|`相连。

函数调用成功时返回信号量描述符，失败时返回`-1`。  
`sem_flags`参数上常用的信号标识有`IPC_CREAT`，用于**创建**新的信号量，但如果**key值**对应的信号量已被创建，并不会调用失败，而是**忽略**该标志。  
`IPC_CREAT | IPC_EXCL`标识，用于创建一个**新的**、**唯一**的信号量，如果**key值**对应的信号量已被创建，则调用**失败**。  
使用`IPC_CREAT | IPC_EXCL`标识需要注意，使用此种方式创建信号量在使用完毕后需要调用`semctl()`函数释放，否则下次运行同样的程序会由于信号量已经存在(没被释放)而造成调用失败。  
`IPC_CRAET | 0666`标识，用于创建有**读写权限**的信号量。

### 改变信号量的值
使用`semop()`函数修改信号量的值。

```c
int semop(int sem_id, struct sembuf *sem_ops, size_t num_sem_ops);
```

- `sem_id`参数为信号描述符，由`semget()`函数得到。
- `sem_ops`参数为指向`sembuf`结构体的指针(有多个信号量时可以指向`sembuf`结构体数组)。
- `num_sem_ops`参数为`sembuf`结构体的数量，一般为`1`。

`sembuf`结构体的定义为：

```c
struct sembuf
{
	unsigned short sem_num; //信号量的编号，在没有使用多个信号量的情况下，一般为0
	short sem_op; //信号量操作，一般可以取-1或是+1，分别对应P(请求)、V(释放)操作
	short sem_flg; //操作标志符，一般取SEM_UNDO
}
```

函数调用成功返回`0`，调用失败返回`-1`并置**errno**。

### 设置信号量信息
使用`semctl()`函数来执行信号量集上的控制操作。

```c
int semctl(int sem_id, int sem_num, int command, ...);
```

- `sem_id`参数为信号量描述符。
- `sem_num`参数为信号量编号，一般没有多个信号量时取`0`。
- `command`参数为要执行的操作的标志位。

`command`参数可以有很多不同的值，常用的有`IPC_RMID`，用于删除一个信号量(如果信号创建方式是`IPC_CREAT | IPC_EXCL`，则务必要在程序结束时删除信号量)。  
`command`设置为`SETVAL`，则用于**初始化**一个信号量，此时函数需要有第四个参数，联合体`union semun`，通过设置`semun`的`val`成员的值来初始化信号量。

`semun`联合体的定义为：

```c
union semun
{
	int val; /* value for SETVAL */
	struct  semid_ds *buf; /* buffer for IPC_STAT & IPC_SET */
	u_short *array; /* array for GETALL & SETALL */
};
```

函数失败时返回`-1`，成功时有多种返回值，参数为`SETVAL`或`IPC_RMID`时运行成功返回`0`。

实例代码：

文件 `semaphore_before.c`：

```c
#define PROJECT_ID 0
#define PATH "/home/dainslef"

#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int sem_id = 0;
struct sembuf sem_wait;
struct sembuf sem_ok;

void deal_signal(int sig)
{
	semop(sem_id, &sem_ok, 1); //将信号量+1,释放资源
	_exit(0);
}

int main(void)
{
	signal(SIGINT, deal_signal);

	sem_id = semget(ftok(PATH, PROJECT_ID), 1, IPC_CREAT | IPC_EXCL | 0600);
	if (sem_id == -1)
	{
		perror("semget");
		return 0;
	}
	else
		printf("信号量创建成功！\n");

	sem_wait.sem_num = sem_ok.sem_num = 0;
	sem_wait.sem_op = -1; //设置操作数，等待时-1
	sem_ok.sem_op = 1; //等待完毕+1
	sem_wait.sem_flg = sem_ok.sem_flg = SEM_UNDO;

	semctl(sem_id, 0, SETVAL, 1); //初始化信号量时可以不自定义联合体直接赋值
	semop(sem_id, &sem_wait, 1); //信号量-1，锁住资源

	while (1) //由于信号量被锁，因此A在执行此段代码时，B在等待
	{
		sleep(3);
		printf("正在执行\n");
	}

	return 0;
}
```

文件 `semaphore_after.c`：

```c
#define PROJECT_ID 0
#define PATH "/home/dainslef"

#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int sem_id = 0;

void deal_signal(int sig)
{
	semctl(sem_id, 0, IPC_RMID); //删除信号量
	_exit(0);
}

int main(void)
{
	signal(SIGINT, deal_signal);

	sem_id = semget(ftok(PATH, PROJECT_ID), 1, 0600); //需要保证进程有读写信号量的权限
	if (sem_id == -1)
	{
		perror("semget");
		return 0;
	}
	else
		printf("信号量获取成功！\n");

	struct sembuf sem_wait;
	sem_wait.sem_num = 0;
	sem_wait.sem_op = -1;
	sem_wait.sem_flg = SEM_UNDO;

	semop(sem_id, &sem_wait, 1);

	while (1)
	{
		sleep(3);
		printf("正在执行\n");
	}

	return 0;
}
```

运行结果：(文字描述)

`Semaphore_Before`先运行，创建信号量成功(一直循环)。  
`Semaphore_After`后运行，获取信号量成功，然后进程阻塞在`semop()`函数上，等待`Semaphore_Before`释放资源。  
向`Semaphore_Before`发送`SIGINT`信号，让其释放资源，结束进程，然后`Semaphore_After`获得资源，`semop()`函数不再阻塞，也开始循环。  
最后向`Semphore_After`发送`SIGINT`信号，让其删除信号量并结束进程。



## SystemV 消息队列(XSI Message Queue)
消息队列是一种进程间通信(IPC, Inter-Process Communication)机制，属于三类`XSI IPC`之一。
以下描述引用自`<<Unix网络编程 卷2>>`：

消息队列是一个**消息链表**，有足够**写权限**的线程可以向消息队列中添加消息，有足够**读权限**的线程可以从消息队列中获取消息。  
消息队列具有**随内核的持续性**。

消息队列相关函数定义在`sys/msg.h`中。

### 创建/获取消息队列
使用`msgget()`函数创建一个新的消息队列/获取一个已经存在的SystemV消息队列：

```c
int msgget(key_t key, int msgflg);
```

- `key`参数为`ftok()`函数生成的**消息队列**标志。
- `msgflg`参数为消息队列的标志位，多个标志间使用`|`操作符相连。

函数执行成功返回**消息队列描述符**(非负数)，执行失败返回`-1`并置`errno`。

`key`参数的取值可以为宏`IPC_PRIVATE`(实际值为`0`)，此时该消息队列为**私有**，用于`fork()`调用之后的**父子进程**间通信(打开的消息队列描述符在`fork()`之后依然存在)。

`msgflg`取`IPC_CREAT`创建一个消息队列(消息队列已存在则忽略此标志位)，取`IPC_CREAT | IPC_EXCL`创建一个新的消息队列(消息队列已存在则函数执行失败)。  
创建消息队列时，若需要对消息队列进行**读写操作**需要在`msgflg`参数后追加读写权限如`0600`(等价于`S_IRUSR | S_IWUSR`)，但打开消息队列时不需要设定(打开的消息队列由创建者决定访问权限)。

### 向消息队列中添加消息
使用`msgsnd()`向消息队列中添加消息：

```c
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
```

- `msqid`参数为`msgget()`函数返回的消息队列文件描述符。
- `msgp`参数为指向要发送消息的指针。
- `msgsz`参数为发送消息的大小(不包括消息类型大小)。
- `msgflg`参数为消息标志位，默认情况下以阻塞方式发送消息(消息队列已满时`msgsnd()`函数会阻塞线程)，取值`IPC_NOWAIT`表示以非阻塞形式发送消息，队列已满则直接返回错误。

函数执行成功返回`0`，执行失败返回`-1`并置`errno`。

发送的消息样例结构如下：

```c
struct mymsg
{
	long mtype; /* Message type. */
	char mtext[1]; /* Message text. */
}
```

消息结构中的首个成员需要为`long`型，用于指示消息的**类型**(之后的`msgrcv()`函数会用到)，之后才为消息的数据区。  
`msgsz`参数传入的消息大小**不包括**消息类型的大小。  
在实际开发中，消息数据不一定是简单的字符数组，可以是**任意类型**(包括**结构体**)。

### 从消息队列中获取消息
使用`msgrcv()`函数从消息队列中获取消息：

```c
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
```

- `msqid`、`msgsz`参数作用与`msgsnd()`函数中类似。
- `msgp`参数指向用户缓冲区，成功收到消息后会将消息从队列中拷贝到用户缓冲区，之后移除队列中被接收的消息。
- `msgtyp`参数为目标接受消息的类型。默认情况下，取值`0`表示接受消息队列中的第一个消息(任意类型)；取值为**正数**时表示接受第一个**类型与`msgtyp`相同**的消息；取**负值**表示接受**绝对值**小于等于`msgtyp`的消息。
- `msgflg`参数为消息标志位，默认以阻塞方式接受消息(若消息队列为空，则`msgrcv()`函数阻塞)，使用`IPC_NOWAIT`标志表示以非阻塞形式接收消息，队列为空则直接返回错误；使用`MSG_EXCEPT`标志时排除接收类型等于`msgtyp`的消息；使用`MSG_NOERROR`标志复制消息时舍弃大于`msgsz`参数值的消息。

函数执行成功返回获取消息的大小，失败时返回`-1`并置`errno`。

### 控制消息队列
使用`msgctl()`函数控制消息队列：

```c
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

- `msqid`参数为消息队列描述符。
- `cmd`参数为具体操作：
	- `IPC_STAT` 取此队列的`msqid_ds`结构, 并将它存放在`buf`指向的结构中
	- `IPC_SET` 设置队列的`msqid_ds`为`buf`指向的值
	- `IPC_RMID` 从系统中**删除**该消息队列以及仍在该队列中的所有数据，执行权限同上
- `buf`参数为指向消息结构体的指针。

函数执行成功返回`0`，执行失败返回`-1`并置`errno`。

参数`buf`的类型`msqid_ds`结构用于设置消息队列的一些属性，该结构的定义根据具体实现略有不同，在`Linux x64`中的定义如下：

```c
/* Structure of record for one message inside the kernel.
   The type `struct msg' is opaque.  */
struct msqid_ds
{
	struct ipc_perm msg_perm; /* structure describing operation permission */
	__time_t msg_stime; /* time of last msgsnd command */
#ifndef __x86_64__
	unsigned long int __glibc_reserved1;
#endif
	__time_t msg_rtime; /* time of last msgrcv command */
#ifndef __x86_64__
	unsigned long int __glibc_reserved2;
#endif
	__time_t msg_ctime; /* time of last change */
#ifndef __x86_64__
	unsigned long int __glibc_reserved3;
#endif
	__syscall_ulong_t __msg_cbytes; /* current number of bytes on queue */
	msgqnum_t msg_qnum; /* number of messages currently on queue */
	msglen_t msg_qbytes; /* max number of bytes allowed on queue */
	__pid_t msg_lspid; /* pid of last msgsnd() */
	__pid_t msg_lrpid; /* pid of last msgrcv() */
	__syscall_ulong_t __glibc_reserved4;
	__syscall_ulong_t __glibc_reserved5;
};
```

其中，定义了操作权限的结构`ipc_perm`的定义如下：

```c
/* Data structure used to pass permission information to IPC operations.  */
struct ipc_perm
{
	__key_t __key; /* Key.  */
	__uid_t uid; /* Owner's user ID.  */
	__gid_t gid; /* Owner's group ID.  */
	__uid_t cuid; /* Creator's user ID.  */
	__gid_t cgid; /* Creator's group ID.  */
	unsigned short int mode; /* Read/write permission.  */
	unsigned short int __pad1;
	unsigned short int __seq; /* Sequence number.  */
	unsigned short int __pad2;
	__syscall_ulong_t __glibc_reserved1;
	__syscall_ulong_t __glibc_reserved2;
};
```

`msqid_ds`结构中的`msg_perm.uid`、`msg_perm.gid`、`msg_perm.mode`以及`msg_qbytes`成员可以**手动指定**。  
`msgctl`函数的`IPC_SET`操作只有下列两种进程可以执行:

0. 进程执行用户的用户ID等于`msg_perm.cuid`或`msg_per.uid`。
0. 具有超级用户特权的进程。

### 实例代码
定义消息结构头`my_msg.h`：

```c
#define PROJECT_ID 0
#define PATH "/home/dainslef"

struct my_msg
{
	long type;

	struct
	{
		char text[20];
		int num;
	} data;
};
```

发送消息进程：

```c
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

#include "my_msg.h"

int main(int argc, char** argv)
{
	key_t key = ftok(PATH, PROJECT_ID);
	struct my_msg msg;
	int msg_id = 0;
	int flag = IPC_CREAT | 0600;

	if ((msg_id = msgget(key, flag)) == -1)
		perror("msgget");

	strcpy(msg.data.text, "Hello");
	msg.data.num = 1;

	//以非阻塞形式发送消息
	if (msgsnd(msg_id, &msg, sizeof(msg.data), IPC_NOWAIT) == -1)
		perror("msgsnd");
	else
		printf("Num: %d\nMessage type: %ld\nSend: %s\n\n", msg.data.num, msg.type, msg.data.text);

	strcpy(msg.data.text + 5, " World");

	for (int i = 1; i < 5; i++)
	{
		msg.type = 100 * i;
		msg.data.num += 1;

		if (msgsnd(msg_id, &msg, sizeof(msg.data), IPC_NOWAIT) == -1)
			perror("msgsnd");
		else
			printf("Num: %d\nMessage type: %ld\nSend: %s\n\n", msg.data.num, msg.type, msg.data.text);
	}

	//获取进程信息
	struct msqid_ds buf;
	if (msgctl(msg_id, IPC_STAT, &buf) == -1)
		perror("msgctl");
	else
	{
		printf("Message privileges info:\n");

		//打印进程权限信息
		printf("msg_perm.uid: %u\n", buf.msg_perm.uid);
		printf("msg_perm.cuid: %u\n", buf.msg_perm.cuid);
		printf("msg_perm.gid: %u\n", buf.msg_perm.gid);
		printf("msg_perm.cgid: %u\n", buf.msg_perm.cgid);
		printf("msg_perm.mode: %o\n", buf.msg_perm.mode);
	}

	return 0;
}
```

接受消息进程：

```c
#include <stdio.h>
#include <sys/msg.h>

#include "my_msg.h"

int main(int argc, char** argv)
{
	key_t key = ftok(PATH, PROJECT_ID);
	struct my_msg msg;
	int msg_id = 0;

	if ((msg_id = msgget(key, 0)) == -1)
		perror("msgget");

	while (1)
	{
		if (msgrcv(msg_id, &msg, sizeof(msg.data), -300, IPC_NOWAIT) == -1)
		{
			perror("msgrcv");
			if (msgctl(msg_id, IPC_RMID, NULL) == -1)
				perror("msgctl");
			break;
		}
		else
			printf("Num: %d\nMessage type: %ld\nRecevie: %s\n\n", msg.data.num, msg.type, msg.data.text);
	}

	return 0;
}
```

运行结果：(Clang 3.7.1 && ArchLinux x64)

先执行消息发送进程：

```
Num: 1
Message type: 4196797
Send: Hello

Num: 2
Message type: 100
Send: Hello World

Num: 3
Message type: 200
Send: Hello World

Num: 4
Message type: 300
Send: Hello World

Num: 5
Message type: 400
Send: Hello World


Message privileges info:
msg_perm.uid: 1000
msg_perm.cuid: 1000
msg_perm.gid: 1000
msg_perm.cgid: 1000
msg_perm.mode: 600
```

之后执行消息接受进程，消息类型绝对值小于等于`300`的数据：

```
Num: 2
Message type: 100
Recevie: Hello World

Num: 3
Message type: 200
Recevie: Hello World

Num: 4
Message type: 300
Recevie: Hello World

msgrcv: No message of desired type
```



## POSIX 消息队列
POSIX消息队列相关函数定义在`mqueue.h`头文件中。  
使用POSIX消息队列，编译时需要链接`librt`库。

POSIX消息队列与SystemV消息队列的差异：

- 读取POSIX消息队列，返回的总是**最高优先级**的**最早**消息。
- 读取SytemV消息队列，返回的是**任意指定优先级**的消息。

### 创建/获取消息队列
使用`mq_open()`函数创建一个新的消息队列/获取一个已经存在的POSIX消息队列：

```c
mqd_t mq_open(const char *name, int oflag);
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
```

- `name`参数为POSIX IPC名称。
- `oflag`参数为标志位，类似于`open()`调用中的`flags`参数。
	0. 可取`O_RDONLY`、`O_WRONLY`、`O_RDWR`(三选一)，分别表示以**只读**、**只写**、**读写**的方式打开POSIX消息队列。
	0. 可取`O_CREAT`，表示不存在消息队列时创建，可追加`O_EXCL`标志，若消息队列已存在函数返回`EEXIST`错误。
	0. 可取`O_NONBLOCK`，表示以**非阻塞**的形式打开消息队列。
- `mode`参数仅当`oflag`参数中使用了`O_CREAT`标志时需要使用，参数内容为创建的消息队列的权限，格式与文件权限相同(八进制，如`0600`)。
- `attr`参数仅当`oflag`参数中使用了`O_CREAT`标志时需要使用，用于设置消息队列的属性，

函数执行成功返回POSIX消息队列的描述符，失败时返回`(mqd_t)-1`，并置`errno`。
类型`mqd_t`在不同的Unix实现中实际类型可能不同，在Linux中为`int`。

### 关闭/移除消息队列
使用`mq_close()`关闭消息队列，使用`mq_unlink()`移除消息队列：

```c
int mq_close(mqd_t mqdes);
int mq_unlink(const char *name);
```

- `mqdes`参数为POSIX消息队列描述符。
- `name`参数为消息队列的IPC名称。

函数执行成功返回`0`，失败时返回`-1`并置`errno`。

使用`mq_close()`关闭消息队列后消息队列不会被删除，删除消息队列需要使用`mq_unlink()`。
一个进程结束后，所有该进程中打开的消息队列都将被自动关闭。
调用`mq_unlink()`时若被删除的消息队列已被其它进程打开则不会立即删除，直到最后一个打开该消息队列的进程结束或主动关闭该消息队列时才会被删除。

### 设置获取消息队列的属性
使用`mq_getattr()`获取消息队列的属性，使用`mq_setattr()`设置消息队列的属性：

```c
int mq_getattr(mqd_t mqdes, struct mq_attr *attr);
int mq_setattr(mqd_t mqdes, const struct mq_attr *newattr, struct mq_attr *oldattr);
```

消息属性结构`mq_attr`在Linux中的定义如下：

```c
struct mq_attr
{
	long mq_flags; /* Flags: 0 or O_NONBLOCK */
	long mq_maxmsg; /* Max. # of messages on queue (最大允许的消息数量) */
	long mq_msgsize; /* Max. message size (bytes) (消息长度最大大小) */
	long mq_curmsgs; /* # of messages currently in queue */
};
```

函数执行成功返回`0`，失败时返回`-1`并置`errno`。

### 打印消息队列的系统限制
`mq_attr`结构中的成员`mq_maxmsg`、`mq_msgsize`在不同Unix系统中拥有不同的系统上限，可以使用`sysconf()`函数获取：

```c
#include <unistd.h>
long sysconf(int name);
```

打印消息数目以及消息大小的系统上限：

```c
printf("MQ_OPEN_MAX: %ld\n", sysconf(_SC_MQ_OPEN_MAX));
printf("MQ_RPIO_MAX: %ld\n", sysconf(_SC_MQ_PRIO_MAX));
```

### 向消息队列发送消息
使用`mq_send()`和`mq_timedsend()`向POSIX消息队列中发送消息：

```c
int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
int mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len,
		unsigned int msg_prio, const struct timespec *abs_timeout);
```

- `mqdes`参数为消息队列描述符。
- `msg_ptr`参数为要加入消息队列的数据。
- `msg_len`参数为消息数据的大小，该值必须**小于等于**`mq_msgsize`(消息长度最大大小)，否则函数返回`-1`并置`errno`为`EMSGSIZE`。
- `msg_prio`参数为消息数据的优先级，数值越大优先级越高。
- `abs_timeout`参数为指向超时时间的指针，`mq_timedsend()`函数等待超时后返回`-1`并置`errno`值为`ETIMEDOUT`。

当消息队列没有设置`O_NONBLOCK`时，`mq_send()`函数会一直阻塞到有消息来到，`mq_timedsend()`函数阻塞到超时时间等待完毕或有消息来到。
`mq_send()/mq_timedsend()`函数的阻塞状态会被信号处理函数中断，触发信号处理函数时，`mq_send()/mq_timedsend()`函数立即返回`-1`并置`errno`为`EINTR`。

当消息队列设置了`O_NONBLOCK`时，若消息队列中的消息数量已经达到`mq_msgsize`(消息数目上限)，函数返回`-1`并置`errno`值为`EAGAIN`。

### 从消息队列获取消息
使用`mq_receive()`和`mq_timedreceive()`从POSIX消息队列中获取消息：

```c
ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
ssize_t mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len,
	unsigned int *msg_prio, const struct timespec *abs_timeout);
```

- `mqdes`参数为消息队列描述符。
- `msg_ptr`参数为要加入消息队列的数据。
- `msg_len`参数为消息数据的大小，该值必须**大于等于**`mq_msgsize`(消息长度最大大小)，否则函数返回`-1`并置`errno`为`EMSGSIZE`。
- `msg_prio`参数为指向消息优先级数据的指针，在队列中有多个消息时，首先获取优先级高的消息。
- `abs_timeout`参数为指向超时时间的指针，`mq_timedreceive()`函数等待超时后返回`-1`并置`errno`值为`ETIMEDOUT`。

当消息队列没有设置`O_NONBLOCK`时，`mq_receive()`函数会一直阻塞到消息能被接收，`mq_timdreceive()`函数阻塞到超时时间等待完毕或消息能被接收。
`mq_receive()/mq_timedreceive()`函数的阻塞状态会被信号处理函数中断，触发信号处理函数时，`mq_receive()/mq_timedreceive()`函数立即返回`-1`并置`errno`为`EINTR`。

当消息队列设置了`O_NONBLOCK`时，若消息队列中的消息数量为`0`，函数返回`-1`并置`errno`值为`EAGAIN`。

### 消息队列通知
使用`mq_notify()`为消息队列绑定或删除异步通知：

```c
int mq_notify(mqd_t mqdes, const struct sigevent *sevp);
```

- `mqdes`参数为消息队列描述符。
- `sevp`参数为指向具体的信号通知内容的指针，若取`NULL`，则清除原有的通知注册。

`sigevent`结构的定义如下：

```c
union sigval {          /* Data passed with notification */
	int     sival_int;         /* Integer value */
	void   *sival_ptr;         /* Pointer value */
};

struct sigevent {
	int          sigev_notify; /* Notification method */
	int          sigev_signo;  /* Notification signal */
	union sigval sigev_value;  /* Data passed with
									notification */
	void       (*sigev_notify_function) (union sigval);
						/* Function used for thread
						notification (SIGEV_THREAD) */
	void        *sigev_notify_attributes;
						/* Attributes for notification thread
						(SIGEV_THREAD) */
	pid_t        sigev_notify_thread_id;
						/* ID of thread to signal (SIGEV_THREAD_ID) */
};
```

注意：

0. 消息队列阻塞的优先级比信号通知更高，只有指定消息队列的所有描述符都以`O_NONBLOCK`标志打开时，信号才会发出。
0. 任何时刻只能有一个进程被注册到指定的消息队列中。
0. 信号成功发送之后，注册即被取消，在此发出信号需要重新注册。

### 实例代码
定义消息结构头`posix_mq.h`：

```c
#include <stdio.h>
#include <string.h>
#include <mqueue.h>

#define PATH_NAME "/tmp"
#define FLAG (O_CREAT | O_RDWR)
#define MODE (S_IRUSR | S_IWUSR)

struct
{
	char text[20];
	int num;
} data;
```

发送消息进程：

```c
#include <unistd.h>

#include "posix_mq.h"

int main(int argc, char** argv)
{
	mqd_t mqdes;

	if ((mqdes = mq_open(PATH_NAME, FLAG, MODE, NULL)) == -1)
		perror("mq_open");

	struct mq_attr attr;

	if (mq_getattr(mqdes, &attr) == -1)
		perror("mq_getattr");

	attr.mq_flags = O_NONBLOCK; //设置消息队列非阻塞

	if (mq_setattr(mqdes, &attr, NULL) == -1)
		perror("mq_setattr");

	strcpy(data.text, "Hello");
	data.num = 1;

	unsigned prio = 1000;

	if (mq_send(mqdes, (char*)&data, sizeof(data), prio) == -1)
		perror("mq_send");
	else
		printf("Num: %d\nMessage type: %u\nRecevie: %s\n\n", data.num, prio, data.text);

	strcpy(data.text + 5, " World");

	for (int i = 1; i < 5; i++)
	{
		prio = 100 * i;
		data.num += 1;

		if (mq_send(mqdes, (char*)&data, sizeof(data), prio) == -1)
			perror("msgsnd");
		else
			printf("Num: %d\nMessage type: %u\nSend: %s\n\n", data.num, prio, data.text);
	}

	printf("\nMessage type info:\n");
	printf("Maxmsg: %ld\n", attr.mq_maxmsg);
	printf("Msgsize: %ld\n", attr.mq_msgsize);

	printf("MQ_OPEN_MAX: %ld\n", sysconf(_SC_MQ_OPEN_MAX));
	printf("MQ_RPIO_MAX: %ld\n", sysconf(_SC_MQ_PRIO_MAX));

	//进程结束。消息队列描述符自动关闭
	mq_close(mqdes);

	return 0;
}
```

接收消息进程：

```c
#include "posix_mq.h"

int main(int argc, char** argv)
{
	mqd_t mqdes;

	if ((mqdes = mq_open(PATH_NAME, FLAG, MODE, NULL)) == -1)
		perror("mq_open");

	struct mq_attr attr;

	if (mq_getattr(mqdes, &attr) == -1)
		perror("mq_getattr");

	attr.mq_flags = O_NONBLOCK; //设置消息队列非阻塞

	if (mq_setattr(mqdes, &attr, NULL) == -1)
		perror("mq_setattr");

	unsigned prio;

	//循环取出队列中所有消息
	while (1)
	{
		memset(&data, 0, sizeof(data));

		if (mq_receive(mqdes, (char*)&data, attr.mq_msgsize, &prio) == -1)
		{
			perror("mq_receive");
			break;
		}
		else
			printf("Num: %d\nMessage type: %u\nReceive: %s\n\n", data.num, prio, data.text);
	}

	mq_unlink(PATH_NAME);

	return 0;
}
```

运行结果：(Clang 3.7.1 && ArchLinux x64)

先执行消息发送进程：

```
Num: 1
Message type: 1000
Recevie: Hello

Num: 2
Message type: 100
Send: Hello World

Num: 3
Message type: 200
Send: Hello World

Num: 4
Message type: 300
Send: Hello World

Num: 5
Message type: 400
Send: Hello World


Message type info:
Maxmsg: 10
Msgsize: 8192
MQ_OPEN_MAX: -1
MQ_RPIO_MAX: 32768
```

之后运行消息接受进程，优先级(type)高的消息先被接收：

```
Num: 1
Message type: 1000
Receive: Hello

Num: 5
Message type: 400
Receive: Hello World

Num: 4
Message type: 300
Receive: Hello World

Num: 3
Message type: 200
Receive: Hello World

Num: 2
Message type: 100
Receive: Hello World

mq_receive: Resource temporarily unavailable
```



## IO多路复用(POSIX)
在Unix中，POSIX定义了一系列IO多路复用机制，如`select()`、`pselect()`、`poll()`等调用。  
Linux和BSD还分别提供了增强的IO复用机制，在Linux中为`epoll`，在BSD中为`kqueue`。

### *select()* 调用
在Unix环境下，`select()`是常用的IO多路复用机制之一，函数定义在`sys/select.h`中。  
`select()`函数定义如下所示：

```c
int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout);
```

- `nfds`参数为需要监视的文件描述符的最大值加`1`。
- `readfds`参数为要监视的可读检测文件描述符集合。
- `writefds`参数为要监视的可写检测文件描述符集合。
- `errorfds`参数为要监视的错误检测文件描述符集合。
- `timeout`参数为超时等待的时间，可以精确到**微秒**，取`NULL`时为`select()`为阻塞函数，超时为`0`时立即返回(非阻塞)。

结构`timeval`的定义为：

```c
struct timeval {
	time_t tv_sec;			/* seconds */
	suseconds_t tv_usec;	/* microseconds */
};
```

描述符集合`fd_set`可以使用下列宏进行操作：

```c
void FD_ZERO(fd_set *fdset);
void FD_SET(fd, fd_set *fdset);
void FD_CLR(fd, fd_set *fdset);
int FD_ISSET(fd, fd_set *fdset);
```

- 使用`FD_ZERO`初始化描述符集合。
- 使用`FD_SET`向描述符集合中添加描述符。
- 使用`FD_CLR`从描述符集合中移除描述符。
- 使用`FD_ISSET`检测描述符，若`fd`参数在描述符集合参数`fdset`中，返回非零值，否则返回`0`。

函数执行成功返回变化的描述符数量，监视的描述符无变化则返回`0`，调用失败返回`-1`。

基本的`select()`函数代码框架为(以检测文件描述符可读为例)：

```c
int fd[fdcount];
fd_set readset;
struct timeval timeout;

while(1)
{
	//初始化并设置描述符集合，每次调用select()前都需要类似操作
	FD_ZERO(&readset);
	FD_SET(fd[0], &readset);
	... //设置需要监视的描述符

	//timeval结构体在每次select()调用会被修改，需要重复设定超时结构体
	timeout.tv_sec = /* seconds */;
	timeout.tv_usec = /* microseconds */;

	switch (select(maxfd, &readset, NULL, NULL, timeout))
	{
	case -1:
		/* error... */
		break;
	case 0:
		/* timeout... */
		break;
	default:
		for (int i = 0; i < fdcount; i++)
		{
			//使用宏FD_ISSET判断文件描述符是否发生变化
			if (FD_ISSET(fd[i], &readset))
			{
				/* do something */
			}
			else
			{
				/* do something */
			}
		}
	}
}
```

使用 *select()* 的一些注意事项：

- `select()`处于阻塞状态时会被信号中断(当`select()`所处线程是信号处理线程时)。
- 每次调用`select()`前都需要重设描述符集合(执行`FD_ZERO`和`FD_SET`宏)。
- `timeval`结构体会在`select()`运行时被修改，因此，在需要设置超时时间的情况下，循环中每次调用`select()`之前都需要重新设置`timeval`结构体。
- 对于**普通文件**描述符，无论**读、写、异常状态**，都是**始终准备好**的，因此在监控的描述符中如果存在**普通文件**，无论`timeout`参数取何值，`select()`都将**立即返回**。

### *pselect()* 调用
`pselect()`函数由**POSIX**定义，是`select()`的完善版本，在早期的Unix中并不存在。  
`pselect()`监听描述符的功能以及使用方式与`select()`相同。  
`pselect()`在`select()`基础上添加了等待期间**阻塞**信号的功能。

`pselect()`函数定义如下所示：

```c
int pselect(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, const struct timespec *restrict timeout, const sigset_t *restrict sigmask);
```

- 前**4个**参数与`select()`中含义完全相同。
- `sigmask`参数为需要屏蔽信号的集合。
- `timeout`参数为超时等待的时间，类型为`timespec`，精确到纳秒，与`select()`函数中精确到毫秒的`timeval`不同。

信号集合参数`sigmask`使用前需要两个步骤：

1. 首先使用`sigemptyset()`函数清空信号集合：

	```c
	int sigemptyset(sigset_t *set);
	```

1. 之后使用`sigaddset()`向清空后的信号集合中添加信号：

	```c
	int sigaddset(sigset_t *set, int signo);
	```

信号集合只需要设置一次，就可以在之后的`pselect()`中一直使用。

- 在`pselect()`处于**阻塞**状态时，会暂时屏蔽信号集中的信号，在`pselect()`阻塞期间若发出了被屏蔽的信号，则信号处理函数会在`pselect()`结束时触发。
- 在`pselect()`**阻塞**期间多次发出了信号，在`pselect()`结束时**同类信号**只触发信号处理函数**一次**，不会多次触发。
- 在`pselect()`**阻塞**期间发出的不同种类信号都会在`pselect()`结束时触发(即使信号处理函数是**同一个**)，但**每类信号**只会触发**一次**信号处理函数。

如下代码所示：

```c
#include <signal.h>
#include <sys/select.h>
#include <stdio.h>

int sigint_count = 0;
int sigquit_count = 0;
int is_changed = 0;

void deal_signal(int sig)
{
	if (sig == SIGINT)
		printf(is_changed ? "SIGINT: %d\n" : "\nSIGINT: %d\n", ++sigint_count);
	else if (sig == SIGQUIT)
		printf(is_changed ? "SIGQUIT: %d\n" : "\nSIGQUIT: %d\n", ++sigquit_count);

	is_changed = 1;
}

int main(void)
{
	//初始化时间结构体timespec，需要注意的是tv_nsec成员为纳秒数
	struct timespec time;
	time.tv_sec = 5;
	time.tv_nsec = 0;

	signal(SIGINT, deal_signal);
	signal(SIGQUIT, deal_signal);

	//sigmask参数设置一次即可，不需要每次调用pselect前都设置
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	//pselect与select的不同之处在于设置sigmask防止超时等待时被信号打断
	//信号会在pselect等待后触发
	while (1)
	{
		is_changed = 0;
		printf("Start pselect!\n");
		pselect(1, NULL, NULL, NULL, &time, &set);
		printf("End pselect!\n\n");
	}

	return 0;
}
```

在上述代码中，`timespec`结构设置了**5秒**的超时等待时间，屏蔽信号集中加入了`SIGINT`和`SIGQUIT`两个信号，在`pselect()`启动后的超时等待时间中，发送这两个信号并不会立即得到响应，而是在**5秒**的超时时间过后，`deal_signal`才会触发。  
在等待期间，无论发送多少次`SIGINT`和`SIGQUIT`信号，`SIGINT`和`SIGQUIT`的信号处理函数只会**分别触发**一次。

在**多线程**环境下，只有`pselect()`所处的线程是信号处理线程时，`pselect()`才能起到阻塞信号的效果，在其它线程中，即使使用`pselect()`并设置屏蔽信号，信号处理函数依然会**立即**触发。

如下代码所示：

```c
#include <signal.h>
#include <sys/select.h>
#include <stdio.h>
#include <pthread.h>

int sigint_count = 0;
int sigquit_count = 0;
int is_changed = 0;

void deal_signal(int sig)
{
	if (sig == SIGINT)
		printf(is_changed ? "SIGINT: %d\n" : "\nSIGINT: %d\n", ++sigint_count);
	else if (sig == SIGQUIT)
		printf(is_changed ? "SIGQUIT: %d\n" : "\nSIGQUIT: %d\n", ++sigquit_count);

	is_changed = 1;
}

void* pthread_func(void* arg)
{
	//初始化时间结构体timespec，需要注意的是tv_nsec成员为纳秒数
	struct timespec time;
	time.tv_sec = 5;
	time.tv_nsec = 0;

	signal(SIGINT, deal_signal);
	signal(SIGQUIT, deal_signal);

	//sigmask参数设置一次即可，不需要每次调用pselect前都设置
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	//在非主线程中的pselect不再具有屏蔽信号的作用
	while (1)
	{
		is_changed = 0;
		printf("Start pselect!\n");
		pselect(1, NULL, NULL, NULL, &time, &set);
		printf("End pselect!\n\n");
	}
}

int main(void)
{
	pthread_t pfd;
	pthread_create(&pfd, NULL, pthread_func, NULL);

	pthread_join(pfd, NULL);

	return 0;
}
```

在上述代码中，`pselect()`代码块被转移到了主线程之外，尽管依旧设置了`sigmask`，但由于信号由**主线程**而非`pselect()`所处线程处理，因而阻塞信号没有在`pselect()`等待期间阻塞，发送`SIGINT`和`SIGQUIT`等信号会**立即触发**信号处理函数。



## IO多路复用(Epoll)
`epoll`是`Linux`环境下**独有**的IO多路复用机制，在`Linux Kernel 2.6`之后被引入。  
传统的`select()`在描述符变化事件产生时需要使用`FD_ISSET`宏遍历测试所有描述符，因此随着监听描述符数量的增加性能会出现线性下降，而使用`epoll`则能直接获取到变化的描述符。
`epoll`相关API定义在`sys/epoll.h`头文件中。

### *epoll_create()* 函数
使用`epoll_create()`初始化一个`epoll`描述符：

```c
int epoll_create(int size);
```

- `size`参数为支持的最大句柄数，从`Linux Kernel 2.6.8`之后，这个参数不再被要求。

函数执行成功返回`epoll`描述符。执行失败返回`-1`，并置`errno`。

### *epoll_ctl()* 函数
使用`epoll_ctl()`添加、修改或删除监听描述符：

```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

- `epfd`参数为`epoll_create()`得到的`epoll`描述符。
- `op`参数为要执行的操作，可取宏`EPOLL_CTL_ADD`(添加监听描述符)、`EPOLL_CTL_MOD`(修改描述符操作)、`EPOLL_CTL_DEL`(删除监听描述符)。
- `fd`参数为被操作的描述符。
- `event`参数为描述符`fd`对应的事件，不能取值`NULL`。

函数执行成功返回`0`，执行失败返回`-1`并置`errno`。

*epoll_event* 结构
> `event`参数的类型`epoll_event`结构体定义如下：
>
>	```c
>	struct epoll_event {
>		uint32_t events;		/* Epoll events */
>		epoll_data_t data;		/* User data variable */
>	};
>	```
>
> 其中，`events`成员为文件描述符触发的条件，是一组标志，使用逻辑或操作符`|`相连，常用的有：
>
>	- `EPOLLIN` 描述符**可读**
>	- `EPOLLOUT` 描述符**可写**
>	- `EPOLLPRI` 描述符有紧急的数据可读
>	- `EPOLLET` `Edge Triggered`(ET，边缘触发)模式，不设置此标志时默认为`Level Triggered`(LT，水平触发)
>	- `EPOLLONESHOT` 只监听**一次**事件

*epoll_data_t* 类型
> `epoll_event`结构体成员`data`的类型`epoll_data_t`联合体定义如下：
>
>	```c
>	typedef union epoll_data {
>		void *ptr;
>		int fd;
>		uint32_t u32;
>		uint64_t u64;
>	} epoll_data_t;
>	```
>
> `data`用来存放事件的对应数据。

### *epoll_wait()* 函数
完整监听描述符的设置之后，使用`epoll_wait()`函数等待事件触发：

```c
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

- `epfd`参数为`epoll_create()`得到的`epoll`描述符。
- `events`参数为产生的事件集合，不能取`NULL`，函数会将产生的事件数据写入该地址中。
- `maxevents`参数为最大事件数目，这个值不大于监听的描述符的数量。
- `timeout`参数为超时时间，取`0`时立即返回(非阻塞)，取`-1`时永久阻塞直到事件产生或被信号中断。

函数执行成功返回变化的描述符数量，返回值为`0`则等待超时。执行失败返回`-1`并置`errno`。

### 注意事项
- `epoll_create()`创建的`epoll`描述符需要使用`close()`关闭。
- `epoll`**不能**监听普通文件描述符，对于`read()`、`write()`调用而言，普通文件是**始终准备好**(always ready)的。在`epoll_ctl()`函数中尝试添加一个普通文件描述符则会得到`Operation not permitted`错误。
- `epoll_create()`中的`size`参数虽然是被忽略的，但不要取`0`和**负值**，会得到`Bad file desriptor`错误。

### *LT* 与 *ET* 模式
`epoll`拥有两种工作模式，分别为`Level Triggered`(LT，水平触发)和`Edge Triggered`(ET，边缘触发)模式。

- `LT`模式为`epoll`的默认工作模式，在该模式下，只要有数据可读/写，使用`epoll_wait()`都会返回。
- `ET`模式只有描述符状态变化(从不可读/写变为可读/写)时才会另`epoll_wait()`返回，相比之下，`ET`模式更为高效。

`LT`模式下，由于只要有数据读写就会触发事件，因此**不必**在一次`epoll`循环中尝试读尽所有的数据，有数据未读会继续触发触发事件，在下次触发的事件中读尽数据即可。`LT`模式下可以使用阻塞式IO也可以使用非阻塞IO。

`LT`模式下基本的代码框架为：

```c
int epfd = epoll_create(size);

struct epoll_event event;
event.events = /* events type */;
event.data = /* data */;

if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event) == -1)
	perror("epoll_ctl()出错");
/*
	添加其它需要监听的描述符...
*/

while (1)
{
	int count = 0, timeout = /* timeout */, maxevents = /* listen_fd_count */;
	struct epoll_event events[maxevents];
	switch (count = epoll_wait(epfd, events, maxevents, timeout))
	{
	case -1:
		perror("epoll_wait()出错");
		break;
	case 0:
		printf("epoll_wait()超时");
		break;
	default:
		//epoll相比select的高效之处就是能直接处理变化的描述符无需遍历整个监听集合
		for (int i = 0; i < count; i++)
		{
			if (events[i].events & EPOLLIN)
			{
				read(...);
			}
			else if (events[i].events & EPOLLOUT)
			{
				write(...);
			}
			/*
				...
			*/
		}
	}
}
```

`ET`模式下，只有描述符在可读写状态发生改变时才会触发事件，因此，在`ET`模式下，必须**一次读尽**所有的数据，否则会造成数据丢失。`ET`模式下，IO需要放在一个无限循环中进行，直到数据全部读出，IO操作置`ernno`为`EAGAIN`才终止。

相比`LT`模式，`ET`模式触发`epoll`次数减少，效率更高，但`ET`模式下必须使用**非阻塞IO**。

`ET`模式下的基本代码框架为：

```c
int epfd = epoll_create(size);

struct epoll_event event;
event.events = EPOLLET | /* events type */; //默认为LT模式，需要显式使用EPOLLET标志才能设置为ET模式
event.data = /* data */;

if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event) == -1)
	perror("epoll_ctl()出错");
/*
	添加其它需要监听的描述符...
*/

while (1)
{
	int count = 0, timeout = /* timeout */, maxevents = /* listen_fd_count */;
	struct epoll_event events[maxevents];
	switch (count = epoll_wait(epfd, events, maxevents, timeout))
	{
	case -1:
		perror("epoll_wait()出错");
		break;
	case 0:
		printf("epoll_wait()超时");
		break;
	default:
		for (int i = 0; i < count; i++)
		{
			while (1)
			{
				if (events[i].events & EPOLLIN)
				{
					if (read(...) == -1 && ernno == EAGAIN)
						break;
				}
				else if (events[i].events & EPOLLOUT)
				{
					if (write(...) == -1 && ernno == EAGAIN)
						break;
				}
			}
			/*
				...
			*/
		}
	}
}
```
