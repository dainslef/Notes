<!-- TOC -->

- [System Call & Library Call](#system-call--library-call)
	- [System Call（系統調用）](#system-call系統調用)
	- [Library Call（庫函數）](#library-call庫函數)
	- [errno](#errno)
- [Time API](#time-api)
	- [獲取當前系統時間](#獲取當前系統時間)
	- [讀取時間](#讀取時間)
	- [時間轉換文本](#時間轉換文本)
- [IO](#io)
	- [創建/打開文件](#創建打開文件)
	- [文件讀取](#文件讀取)
	- [文件寫入](#文件寫入)
	- [文件信息](#文件信息)
	- [標準輸入/輸出](#標準輸入輸出)
- [Dup（描述符複製）](#dup描述符複製)
	- [dup()](#dup)
	- [dup3()](#dup3)
- [Log（日誌）](#log日誌)
	- [日誌服務](#日誌服務)
	- [打開日誌](#打開日誌)
	- [輸出日誌](#輸出日誌)
	- [關閉日誌連接](#關閉日誌連接)
	- [實例代碼](#實例代碼)
- [Process（進程）](#process進程)
	- [查看進程信息](#查看進程信息)
	- [進程控制函數](#進程控制函數)
	- [等待進程](#等待進程)
	- [Daemon（守護進程）](#daemon守護進程)
- [Signal（信號）](#signal信號)
	- [信號處理](#信號處理)
	- [信號發送](#信號發送)
	- [信號觸發](#信號觸發)
	- [可靠信號/不可靠信號](#可靠信號不可靠信號)
	- [信號屏蔽](#信號屏蔽)
	- [屏蔽線程信號](#屏蔽線程信號)
	- [信號相關的進程控制函數](#信號相關的進程控制函數)
	- [多線程信號處理](#多線程信號處理)
- [pthread（POSIX線程）](#pthreadposix線程)
	- [Linux下的線程實現](#linux下的線程實現)
	- [線程創建](#線程創建)
	- [線程等待](#線程等待)
	- [線程取消](#線程取消)
	- [線程終止](#線程終止)
	- [互斥量](#互斥量)
	- [互斥量用於進程同步](#互斥量用於進程同步)
- [XSI IPC](#xsi-ipc)
	- [IPC 標誌](#ipc-標誌)
	- [XSI IPC 特點](#xsi-ipc-特點)
	- [SystemV 共享內存](#systemv-共享內存)
		- [創建/獲取共享內存](#創建獲取共享內存)
		- [共享內存獲取](#共享內存獲取)
		- [共享內存分離](#共享內存分離)
	- [共享內存控制](#共享內存控制)
	- [Semaphore（SystemV 信號量）](#semaphoresystemv-信號量)
		- [信號量創建/獲取](#信號量創建獲取)
		- [改變信號量值](#改變信號量值)
		- [信號量信息設置](#信號量信息設置)
	- [XSI Message Queue (SystemV 消息隊列)](#xsi-message-queue-systemv-消息隊列)
		- [創建/獲取消息隊列](#創建獲取消息隊列)
		- [向消息隊列中添加消息](#向消息隊列中添加消息)
		- [從消息隊列中獲取消息](#從消息隊列中獲取消息)
		- [消息隊列控制](#消息隊列控制)
		- [實例代碼](#實例代碼-1)
	- [POSIX 消息隊列](#posix-消息隊列)
		- [創建/獲取消息隊列](#創建獲取消息隊列-1)
		- [關閉/移除消息隊列](#關閉移除消息隊列)
		- [設置獲取消息隊列的屬性](#設置獲取消息隊列的屬性)
		- [打印消息隊列的系統限制](#打印消息隊列的系統限制)
		- [向消息隊列發送消息](#向消息隊列發送消息)
		- [從消息隊列獲取消息](#從消息隊列獲取消息)
		- [消息隊列通知](#消息隊列通知)
		- [實例代碼](#實例代碼-2)
- [IO多路複用（POSIX）](#io多路複用posix)
	- [select()](#select)
	- [pselect()](#pselect)
- [IO多路複用（epoll）](#io多路複用epoll)
	- [epoll_create()](#epoll_create)
	- [epoll_ctl()](#epoll_ctl)
	- [epoll_wait()](#epoll_wait)
	- [注意事項](#注意事項)
	- [LT/ET](#ltet)

<!-- /TOC -->



# System Call & Library Call
對開發者而言，系統調用與庫函數在Unix中都是一組C語言接口，但內部有很大區別。

## System Call（系統調用）
**系統調用**（`System calls`）是操作系統提供的服務入口點，程序由這些服務入口點向內核請求服務。

Unix系統爲大多數的系統調用提供了同名的C函數接口，
封裝在標準C庫（libc）中，在用戶進程中調用這些C函數來發起系統調用。
使用系統調用會在**用戶態**與**內核態**之間進行環境切換（內核發現`trap`之後進入內核態），有較大開銷。

在Linux和BSD中，部分系統函數沒有提供C庫的封裝（比如Linux中的`gettid()`），
需要使用`syscall()`函數進行調用，syscall()最初由BSD引入，
Linux在`Linux Kernel 2.6.19`之後引入該函數。

一般而言，系統調用是系統服務的直接入口點。
一些庫函數也會用到系統調用，但這些庫函數**不是**系統入口點，
如C語言標準庫中的printf()函數在Unix系統中的實現通常會使用系統調用`write()`。

man手冊**卷2**中的函數皆爲系統調用。

## Library Call（庫函數）
**庫函數**（`Library calls`）是編程語言的一部分，與操作系統無關，
Windows系統中，例如`printf()`、`scanf()`等庫函數依然可用，
但Unix系統調用如`read()`、`write()`便不再存在。

一些庫函數內部會使用系統調用（如`printf()`）。
在不同的操作系統中，庫函數會使用對應操作系統的系統調用。
輔助功能性庫函數(如`memcpy()`、`atoi()`之類)是純粹的用戶態函數，
不涉及系統調用，不會造成系統在用戶態與內核態之間切換。

C標準庫函數可在`man`手冊**卷3**中查閱。

## errno
幾乎所有系統調用均會提供外部變量`errno`：

```c
extern int errno
```

當系統調用產生錯誤時，函數返回指示失敗的整型數值(通常為`-1`)，並設置對應的errno值。
成功的系統調用不會設置該值，一旦該值被一個失敗的系統調用設置，值將一直保留到下一個系統調用錯誤，
檢查errno值應該僅在錯誤產生後進行。

errno可能的取值以宏定義的形式寫在頭文件`<sys/errno.h>`中，
具體每個取值的含義可參考對應man手冊中對應章節。

errno是**線程安全**的，不同線程中產生的錯誤值相互獨立而非相互覆蓋，
相關標準定義在[Thread-safety and POSIX.1](https://unix.org/whitepapers/reentrant.html)中：

> Redefinition of errno
> In POSIX.1, errno is defined as an external global variable. But this definition is unacceptable in a multithreaded environment, because its use can result in nondeterministic results. The problem is that two or more threads can encounter errors, all causing the same errno to be set. Under these circumstances, a thread might end up checking errno after it has already been updated by another thread.
>
> To circumvent the resulting nondeterminism, POSIX.1c redefines errno as a service that can access the per-thread error number as follows (ISO/IEC 9945:1-1996, §2.4):
>
> Some functions may provide the error number in a variable accessed through the symbol errno. The symbol errno is defined by including the header <errno.h>, as specified by the C Standard ... For each thread of a process, the value of errno shall not be affected by function calls or assignments to errno by other threads.
> In addition, all POSIX.1c functions avoid using errno and, instead, return the error number directly as the function return value, with a return value of zero indicating that no error was detected. This strategy is, in fact, being followed on a POSIX-wide basis for all new functions.

C標準庫中的`<stdio.h>`/`<string.h>`提供了errno相關函數：

```c
// stdio.h

void
perror(const char *s);

extern const char * const sys_errlist[];
extern const int sys_nerr;



// string.h

char *
strerror(int errnum);

int
strerror_r(int errnum, char *strerrbuf, size_t buflen);
```

使用`perror()`函數會讀取errno值查找對應錯誤信息寫入參數地址中。
使用`strerror()/strerror_r()`函數將錯誤碼轉換為錯誤信息文本。

錯誤信息亦可通過外部變量`sys_errlist`（錯誤信息數組）、`sys_nerr`（錯誤信息數組大小）進行訪問，
但該方法已被**廢棄**，不推薦使用。



# Time API
Unix環境下的時間獲取相關函數定義在`time.h`頭文件之中。

## 獲取當前系統時間
使用`time()`函數獲取當前系統時間。

```c
time_t time(time_t *t);
```

`t`參數爲`time_t`類型變量的地址，函數會返回當前系統的時間，同時將當前系統的時間寫入傳入的地址中。
如果只是從返回值獲取當前時間，不需要將時間寫入傳入參數中，則參數可以填NULL，函數正常運行。
返回值time_t保存的是`1970-01-01 00:00:00 +0000 (UTC)`開始到**當前時間**的秒數的數值，一般不直接使用。

## 讀取時間
使用`localtime()`函數輸出時間結構體`tm`類型。

```c
struct tm *localtime(const time_t *timep);
```

函數接受參數爲time()返回的標準時間秒數，
將其轉換返回對應的可讀時間結構體指針`tm*`類型。
結構體`tm`的定義爲：

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

可以從tm結構體的對應成員中讀取對應的時間信息。

時間信息中部分信息需要處理才能對應真實時間：

- **年份**爲當前年份減去`1900`的值，實際年份需要加`1900`。
- **月份**範圍爲`0 ~ 11`，實際月份需要加`1`。

## 時間轉換文本
使用`asctime()`函數可將tm時間結構轉換為`char*`時間文本。

```c
char *asctime(const struct tm *tm);
```

對於`localtime()`函數獲得的當前時間，可以使用該函數轉化爲可讀的字符串形式，返回值爲標準時間字符串的地址。
注意，該函數返回的地址指向的字符串內容中已經包含了換行符，不需要再額外添加。

一個典型的時間輸出如：`Wed Jul 29 01:04:10 2015`

實例代碼：

```c
#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t now = time(NULL);
	struct tm *tm_now = localtime(&now);
	printf("當前的時間是：%d點%d分%d秒。\n", tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
	printf("標準的時間輸出：%s", asctime(tm_now));
	return 0;
}
```

運行結果：

```
當前的時間是：1點15分39秒。
標準的時間輸出：Wed Jul 29 01:15:39 2015
```



# IO
Unix環境下基本的文件操作爲`open()`、`read()`、`write()`、`close()`、`ioctl()`等。
相關的頭文件在`unistd.h`、`fcntl.h`、`sys/ioctl.h`之中。

## 創建/打開文件
創建/打開文件涉及的系統調用定義在文件`fcntl.h`中。

```c
int creat(const char *pathname, mode_t mode);
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
int openat(int dirfd, const char *pathname, int flags);
int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```

`creat()`函數用於創建文件；`open()`函數既可用於創建文件(**flags**取`O_CREAT`)，
也可用於打開文件，打開的對象可以是**目錄**。

- `pathname`參數：

	對於`create()`和`open()`函數，參數`pathname`指向的字符數組爲文件所在路徑（路徑可爲絕對路徑或相對路徑）。
	`dirfd`文件描述符表示的路徑爲**父目錄**，參數`pathname`指向的字符數組爲相對路徑。

- `mode`參數：

	mode代表創建的文件文件帶有的默認權限，可以用邏輯或操作符連接以下參數：

	- `S_IRUSR` 擁有者讀權限
	- `S_IWUSR` 擁有者寫權限
	- `S_IXUSR` 擁有者執行權限
	- `S_IRGRP` 同組用戶讀權限
	- `S_IWGRP` 同組用戶寫權限
	- `S_IXGRP` 同組用戶執行權限
	- `S_IROTH` 其它用戶讀權限
	- `S_IWOTH` 其它用戶寫權限
	- `S_IXOTH` 其它用戶執行權限

- `flag`參數

	flags參數表示文件打開時的參數，參數可取**多個**，以**邏輯或**操作符連接，常用的有：

	- `O_RDONLY` 只讀打開文件
	- `O_WRONLY` 只寫打開文件
	- `O_RDWR` 讀寫打開文件
	- `O_APPEND` 寫入數據時在原文件的末尾追加數據，而不是清楚原有數據
	- `O_CREAT | O_EXECL` 創建原先**不存在**的文件，若文件已經存在了，則調用**失敗**

`openat()`函數作用與open()函數類似，openat()函數允許使用多種路徑表示方式：

- `dirfd`文件描述符表示的路徑爲父目錄，而`pathname`中包含的字符串爲相對路徑。
- `dirfd`取特殊值`AT_FDCWD`，則父目錄爲**當前路徑**。
- `dirfd`取值**忽略**，`pathname`參數爲**絕對路徑**。

以上函數在執行成功時返回新的文件描述符，失敗時返回**-1**並置`errno`。

## 文件讀取
使用`read()`函數讀取文件，函數定義在`unistd.h`中。

```c
ssize_t read(int fd, void *buf, size_t count);
```

- `fd`參數爲要讀取的文件描述符。
- `buf`參數爲讀取的內容的首地址。
- `count`參數爲設定讀取的字節數。

返回值爲實際讀取了的字節數。失敗時返回`-1`。

## 文件寫入
使用`write()`向文件中寫入數據，函數定義在`unistd.h`中。

```c
ssize_t write(int fd, const void *buf, size_t count);
```

- `fd`參數爲要寫入的文件描述符。
- `buf`參數爲要寫入內容的首地址。
- `count`參數指定寫入數據的長度。

`buf`指向的內容中超過`count`長度的內容**不會**被寫入。
返回值爲**實際寫入內容的大小**。

對於同一個文件描述符，連續進行讀寫操作，每一次函數調用都會在上一次結束的位置進行，
因此想要重複讀取某個文件的內容，需要創建新的文件描述符。
同一個文件可以同時擁有多個文件描述符，且各個文件描述符之間的文件讀取是相互獨立的。

## 文件信息
使用`stat()`獲取文件的信息，函數定義在`sys/stat.h`中。

```c
int stat(const char *pathname, struct stat *buf);
```

- `pathname`參數爲要獲取文件的路徑。
- `buf`參數爲指向文件屬性結構體的指針。

函數執行成功返回`0`，失敗時返回`-1`並置`errno`。

文件屬性結構體`stat`定義如下：

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

在`stat`結構中，定義了文件的文件的**大小**、**文件種類**、**所屬用戶/用戶組**、**文件的訪問/修改時間**等信息。

## 標準輸入/輸出
在Unix哲學中，秉承**一切皆文件**思想，
在終端中進行輸入/輸出與讀寫文件操作類似，使用`read()/write()`調用即可。

- **標準輸入**對應的文件描述符爲`0`。
- **標準輸出**對應的文件描述符爲`1`。
- **標準錯誤輸出**對應的文件描述符爲`2`。

使用`read()/write()`調用對這些特殊的文件描述符進行讀寫操作即可實現**終端輸入/輸出**的效果。

在頭文件`unistd.h`中，分別爲這3個特殊的文件描述符創建了宏定義：

```c
/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */
```



# Dup（描述符複製）
使用`dup()`系列函數進行描述符複製操作，函數定義在頭文件`unistd.h`中。

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

- `oldfd`參數爲舊的文件描述符。
- `newfd`參數爲新的文件描述符。

`dup()`接收舊的文件描述符參數，並複製舊描述符到當前未被使用的最小描述符編號上，返回該描述符。
`dup2()`接收舊的文件描述符和新文件描述符參數，並將舊文件描述符複製到新文件描述符上。

函數執行成功返回新的文件描述符，失敗時返回`-1`。
函數執行成功則新舊文件描述符可以交替使用，新文件描述符擁有**相同**的文件偏移量和文件狀態標誌，
當一個文件描述符的偏移量發生改變時，另一個文件描述符也將同步改變。

新舊文件描述符之間**不**共享`FD_CLOEXEC`描述符標誌。

## dup()
`dup()`系列函數最常見的用途之一就是重定向標準、錯誤輸出到指定文件。

示例：

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_PATH "out_file"

int main(int argc, char** argv)
{
	// 輸出"ERROR0"到標準錯誤輸出
	write(STDERR_FILENO, "ERROR0\n", 7);

	// 打開輸出文件
	int error_fd = open(FILE_PATH, O_CREAT | O_RDWR, 0600);

	// 備份標準錯誤輸出
	int stderror_back = dup(STDERR_FILENO);

	// 將輸出文件描述符複製到標準錯誤輸出上
	dup2(error_fd, STDERR_FILENO);

	// 輸出"ERROR1"到標準錯誤輸出，此時的標準錯誤輸出實際爲先前打開的文件
	write(STDERR_FILENO, "ERROR1\n", 7);

	// 恢復標準錯誤輸出的功能
	dup2(stderror_back, STDERR_FILENO);

	// 測試標準錯誤輸出
	write(STDERR_FILENO, "ERROR2\n", 7);

	// 打印各個描述符的數值
	printf("The STDERR is %d.\n", STDERR_FILENO);
	printf("The error_fd is %d.\n", error_fd);
	printf("The stderror_back is %d.\n", stderror_back);

	return 0;
}
```

運行結果：(GCC 6.1.1 && ArchLinux x64)

```
ERROR0
ERROR2
The STDERR is 2.
The error_fd is 3.
The stderror_back is 4.
```

輸出文件`out_file`中的內容：

```
ERROR1
```

## dup3()
Linux下還提供了獨有的函數`dup3()`，
dup3()函數需要定義`_GNU_SOURCE`宏並引用`fcntl.h`頭文件才能使用。

```c
#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>

int dup3(int oldfd, int newfd, int flags);
```

- `flags`參數可以取`O_CLOEXEC`標誌，設置了該標誌之後，複製的新描述符將帶有`FD_CLOEXEC`標誌。

對於新舊文件描述符相同的情況，
`dup2()`函數正常執行完畢並返回`newfd`，
`dup3()`函數執行失敗並置`error`爲`EINVAL`。



# Log（日誌）
Unix日誌相關的函數定義在頭文件`syslog.h`中。

## 日誌服務
在使用`SysVinit`作爲init系統的Linux中，
日誌服務爲`rsyslog`或`syslog-ng`，主要日誌爲`/var/log/syslog`文件。
syslog文件爲純文本，可以直接使用編輯器查看。

在現代Linux中，init系統採用`systemd`，
日誌服務也由systemd的子模塊`systemd-journald`提供，
日誌文件位於`/var/log/journal`目錄下。
systemd-journald記錄的日誌爲**二進制**格式，
使用編輯器查看顯示爲**亂碼**，應使用`journalctl`指令查看：

```html
$ journalctl <!-- 查看所有日誌 -->
$ journalctl -e <!-- 查看近期日誌（最近的1000條日誌） -->
```

使用journalctl指令會進入交互式日誌查看界面，跳轉翻頁快捷鍵等與vim編輯器類似。

## 打開日誌
在開始記錄日誌之前，使用`openlog()`打開一個日誌連接。

```c
void openlog(const char *ident, int option, int facility);
void closelog(void);
```

- `ident`參數爲日誌前綴，使用該連接輸出的日誌都將以該字符串作爲前綴，傳入值爲NULL時，將使用程序名稱做爲前綴
- `option`參數爲日誌選項，多個選項之間可以使用邏輯或`|`操作符相連接：
	- `LOG_CONS` 當寫入系統日誌出錯時直接向終端輸出錯誤
	- `LOG_NDELAY` 立即打開日誌連接（普通情況下，連接將在打印首個日誌時被打開）
	- `LOG_NOWAIT` 輸出日誌時不等待子進程創建完畢（GNU C庫不會創建子進程，該選項在Linux下無效）
	- `LOG_ODELAY` 與LOG_NDELAY相反，日誌連接將被延遲到首個syslog()被調用（默認）
	- `LOG_PERROR` 同時將日誌輸出到stderr，實際開發中，可將輸出到`stderr`的日誌**重定向**到指定文件來實現日誌文件轉儲
	- `LOG_PID` 輸出日誌時包含PID信息
- `facility`參數用於標記日誌的類型：
	- `LOG_AUTH` 安全/權限消息
	- `LOG_AUTHPRIV` 安全/權限消息（私有）
	- `LOG_CRON` 時鐘服務
	- `LOG_DAEMON` 不帶有facility值的系統服務
	- `LOG_FTP` ftp文件服務
	- `LOG_KERN` 內核信息（不能由用戶進程生成）
	- `LOG_LOCAL0 ~ LOG_LOCAL7` 爲本地用戶預留
	- `LOG_LPR` 行顯示子系統
	- `LOG_MAIL` 郵件子系統
	- `LOG_NEWS` USENET新聞子系統
	- `LOG_SYSLOG` 由syslogd(8)創建的日誌消息
	- `LOG_USER (default)` 普通的用戶級別消息
	- `LOG_UUCP` UUCP子系統

標準的日誌格式如下：

```
日誌時間 主機名稱或主機IP [ident] [facility]: 消息內容
```

在使用純文本日誌的發行版中，默認日誌輸出到文件`/var/log/syslog`，
但一些日誌服務如`rsyslog`，可以根據日誌的類型（`facility`參數）將日誌轉儲到不同的日誌文件中。

`openlog()`函數是**可選**的，即使不調用openlog()函數，
在首次調用syslog()函數打印日誌時也會**自動**打開日誌連接。
不使用openlog()直接使用`syslog()`函數輸出日誌時自動創建的日誌連接會使用默認配置，
若需**自定義日誌前綴**、**輸出日誌到stderr**等額外功能，
則仍然需要**手動**打開日誌連接並配置參數。

## 輸出日誌
使用`syslog()`函數輸出日誌：

```c
void syslog(int priority, const char *format, ...);
```

- `priority`參數爲日誌的重要級別，取值如下：
	- `LOG_EMERG` 系統不可用
	- `LOG_ALERT` 動作必須立即產生
	- `LOG_CRIT` 危險狀態
	- `LOG_ERR` 錯誤狀態
	- `LOG_WARNING` 警告狀態
	- `LOG_NOTICE` 普通但是重要的狀態
	- `LOG_INFO` 信息消息
	- `LOG_DEBUG` 調試消息
- `format`參數指向日誌的格式化字符數組，格式化語法與`printf()`函數相同。

在使用systemd作爲init系統的發行版中，使用`journalctl`指令查看日誌時，
對特定級別的日誌會有不同的顯示方式，令日誌更加醒目：

- `LOG_EMERG`、`LOG_ALERT`、`LOG_CRIT`、`LOG_ERR`級別的日誌以**紅色**字體顯示。
- `LOG_WARNING`、`LOG_NOTICE`級別的日誌以**粗體**字顯示。

## 關閉日誌連接
使用`closelog()`函數立即關閉日誌連接：

```
void closelog(void);
```

使用closelog()會關閉用於寫入日誌的描述符，closelog()同樣是**可選**的操作。

## 實例代碼
打印各個級別的日誌，並將日誌轉儲到日誌文件`test.log`中，示例：

```c
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	openlog("Test_log", LOG_PID | LOG_PERROR, LOG_USER); // 打開日誌連接

	int log_fd = open("test.log", O_CREAT | O_APPEND | O_RDWR, 0600);

	// 使用dup2()調用，重定向標準錯誤輸出到打開的文件
	dup2(log_fd, STDERR_FILENO);

	// 輸出日誌
	syslog(LOG_EMERG, "The msg is: %s.", "LOG_EMERG");
	syslog(LOG_ALERT, "The msg is: %s.", "LOG_ALERT");
	syslog(LOG_CRIT, "The msg is: %s.", "LOG_CRIT");
	syslog(LOG_ERR, "The msg is: %s.", "LOG_ERR");
	syslog(LOG_WARNING, "The msg is: %s.", "LOG_WARNING");
	syslog(LOG_NOTICE, "The msg is: %s.", "LOG_NOTICE");
	syslog(LOG_INFO, "The msg is: %s.", "LOG_INFO");
	syslog(LOG_DEBUG, "The msg is: %s.", "LOG_DEBUG");

	closelog(); // 關閉日誌連接
	return 0;
}
```

運行結果，在日誌文件`test.log`中：（GCC 6.1.1 && ArchLinux x64）

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



# Process（進程）
Process（**進程**）是資源調度與分配的基本單位。
在Unix中，進程具有以下概念：

- `PID`（進程ID）

	PID是一個用於標誌進程的非負整數，具有唯一性，且無法被用戶修改。
	PID爲`1`的進程爲`init`進程。

	獲取進程ID使用`getpid()`函數：

	```c
	pid_t getpid(void);
	```

- `PPID`（父進程ID）

	除了`init`進程外，其它進程都由先前存在的進程創建。
	創建進程的進程稱爲**父進程**，被創建的進程稱爲**子進程**。

	獲取父進程ID使用`getppid()`函數：

	```c
	pid_t getppid(void);
	```

- `PGID`（進程組ID）

	**進程組**是一個或多個進程的集合，PGID等於組長進程的PID。

	進程組相關函數：

	```c
	/*
		設置指定PID進程的PGID。
		pid參數取0時，設置當前進程的PGID。
		pgid參數取0時，指定進程的PGID會被設置爲與PID相同。
		被設置進程組的進程原有PGID與新設置的PGID需要位於同一個會話(Session)中。
	*/
	int setpgid(pid_t pid, pid_t pgid);

	// 得到指定PID進程的PGID，pid參數取0時獲取當前進程PGID
	pid_t getpgid(pid_t pid);
	```

- `SID`（會話ID）

	`Session`（**會話**）是一個或多個進程組的集合。
	獲取SID使用`getsid()`函數：

	```c
	// 獲取指定PID進程的SID，pid參數取0時獲取當前進程的SID
	pid_t getsid(pid_t pid);
	```

	創建會話使用`setsid()`函數：

	```c
	pid_t setsid(void);
	```

	關於`setsid()`函數，需要注意：

	- 若調用進程不是進程組的組長，則創建新的會話。
	- 調用進程將成爲新會話中的會話首進程(Session Leader)。
	- 調用進程將成爲新會話的新進程組中的組長進程。
	- 新的會話ID、進程組ID都將等於調用進程的PID。
	- 新創建的會話將沒有控制終端，無論原有會話是否有控制終端。

- `Control Terminal`（控制終端）

	控制終端用於與系統交互，在用戶登陸時系統會自動爲用戶分配控制終端。
	控制終端相關函數：

	```c
	// 返回指定文件描述符的控制終端的前臺進程組ID
	pid_t tcgetpgrp(int fd);
	// 設置指定文件描述符的控制終端的前臺進程組ID
	int tcsetpgrp(int fd, pid_t pgrp);
	```

	控制終端與進程組、會話是密切相關的概念：

	- 會話可以擁有控制終端。
	- 建立與控制終端連接的會話首進程被稱爲控制進程。
	- 帶有控制終端的會話擁有前臺進程組，其餘進程組爲後臺進程組。
	- 在控制終端中輸入的中斷鍵（`Ctrl + C`）、退出鍵會將中斷信號（`SIGINT`）、
	退出信號（`SIGQUIT`）發送給前臺進程組中的所有進程。

## 查看進程信息
在Linux下，一切皆文件，進程相關信息可在`/proc`文件系統中看到，
每個進程的`pid`會在`/proc`路徑下存在對應的路徑。

以現代發行版的初始化進程`systemd`為例，進程信息位於`/proc/1`路徑下：

```
$ ls
attr        comm             fd        map_files   net            pagemap      setgroups     status
autogroup   coredump_filter  fdinfo    maps        ns             personality  smaps         syscall
auxv        cpuset           gid_map   mem         numa_maps      projid_map   smaps_rollup  task
cgroup      cwd              io        mountinfo   oom_adj        root         stack         timerslack_ns
clear_refs  environ          limits    mounts      oom_score      schedstat    stat          uid_map
cmdline     exe              loginuid  mountstats  oom_score_adj  sessionid    statm         wchan
```

該路徑中提供了許多進程內部的關鍵信息，
如`fd`（進程使用的文件描述符）、`net`（進程的網絡棧信息）、`limits`（進程的資源限制）等。

## 進程控制函數
常見的進程控制函數如下：

- 終止進程

	使用`exit()`系列函數退出進程：

	```c
	#include <stdlib.h>

	void exit(int status);
	void _Exit(int status);
	int atexit(void (*function)(void));

	#include <unistd.h>

	void _exit(int status);
	```

	`exit()/_exit()/_Exit()`之間的區別：

	- `exit()`爲C標準庫函數，是最常見進程退出函數，進程結束前會進行一些清理操作：
		1. 調用`atexit()`註冊的清理函數。
		1. 刷新輸出流，關閉已打開的流。
		1. 刪除通過標準I/O函數`tmpfile()`創建的臨時文件。
	- `_exit()`爲系統調用，函數定義在`unistd.h`中，使用`_exit()`會立即結束進程，並且不會執行清理操作。
	- `_Exit()`爲C標準庫函數，定義在`stdlib.h`中，作用等價於系統調用`_exit()`。

- 創建進程

	C語言標準庫中提供了`system()`函數用於創建進程：

	```c
	#include <stdlib.h>

	int system(const char *command);
	```

	system()函數的特點：

	- system()函數運行以字符串參數的形式傳遞給它的命令，
	並等待該命令完成（效果類似於在Shell中使用對應命令）。
	- 與exec()函數不同，system()函數會創建Shell來執行命令。
	- 若無法啓動Shell來運行這個命令，system()函數將返回錯誤代碼`127`；
	其它錯誤返回`-1`，否則system()函數將返回該命令的退出碼（通常為`0`）。
	- 實際開發中，system()函數使用較少，該函數會啓動Shell執行指令，**效率低下**。

實際開發中，`fork() + exec()`是最常用的進程創建方式。

- `fork()` 函數

	在Unix環境下，`fork()`系統調用是最常見的創建進程方式，函數定義在`unistd.h`中，函數原型爲：

	```c
	#include <unistd.h>

	pid_t fork(void);
	```

	fork()函數爲當前進程創建一個相同的**拷貝**，原進程爲**父進程**，新進程爲**子進程**。
	原進程的fork()函數返回子進程的`pid`，新進程的fork()函數返回`0`。

	新進程與原進程有着相同的**運行狀態**和**代碼**，
	即從fork()函數開始（包括fork()函數自身）接下來的代碼原進程和新進程將會各執行一遍。
	新的進程有**獨立**的數據空間、環境、和文件描述符。
	父進程中已經打開的文件描述符在子進程中依然會存在，父進程註冊的信號處理函數在子進程依然有效。

	子進程不繼承父進程的文件鎖，父進程中未處理的信號集在子進程中被置爲空集。
	多進程並行執行時，各個進程是**異步亂序**執行的，因此不能確定各個進程各段代碼的執行先後順序，
	**不要**嘗試編寫依賴於其它進程執行結果的代碼。

	實例代碼：

	```c
	#include <stdlib.h> // 包含system()系統調用
	#include <stdio.h>
	#include <unistd.h> // 包含fork()、sleep()系統調用

	int main(void)
	{
		/*
			system()函數只執行了一次，
			可知在fork()函數拷貝的是fork()運行此刻運行狀態，
			但fork()函數之前的內容依然只執行一次。
		*/
		if (!system("whoami"))
			printf("Run the system call successful!\n");

		/*
			fork()系統調用對於父進程返回子進程的pid，對於子進程返回0，
			fork()有可能執行失敗，失敗返回-1，並且不創建子進程。
		*/
		pid_t num = fork();

		if (num)
		{
			printf("This is parent process!\n");
			printf("The PID is %d\n", getpid());
			printf("The PPID is %d\n", getppid());
			sleep(2); // 程序運行到此暫停2秒
			system("ps");
		}
		else
		{
			printf("This is child process!\n");
			printf("The PID is %d\n", getpid());
			printf("Ths PPID is %d\n", getppid());
		}
		printf("End!\n"); // fork()之後的內容父進程子進程各執行一次
		return 0;
	}
	```

	運行結果：

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

	由結果可知，fork()函數之前的`system("whoami")`函數只執行了一遍，
	因此shell指令whoami也只執行一遍。但在fork()函數之後的代碼都執行了兩遍，
	分別來自父進程和子進程的`printf()`函數向屏幕打印了兩次`End!`。
	由`system("ps")`函數中執行的Shell指令ps向屏幕中輸出的結果可以看出，
	父進程的`ppid`是啓動這個進程的Shell的`pid`，而**子進程**的`ppid`就是**父進程**的`pid`。

- `vfork()` 函數

	`vfork()`作用與fork()類似，函數定義在`unistd.h`中，示例：

	```c
	pid_t vfork(void);
	```

	相比fork()調用，`vfork()`有以下不同之處：

	- fork()子進程拷貝父進程中的數據段和代碼段，vfork()中子進程與父進程共享數據段。
	- fork()調用之後父子進程執行順序是**隨機**的，
	vfork()中子進程在調用exec()或exit()之前與父進程數據共享，
	而父進程在子進程調用了exec()或exit()之前會一直**阻塞**。

	在Linux中，fork()與vfork()最終的內部實現都使用`do_fork()`。

- `exec()` 函數

	`exec()`系統調用，由一系列的相關函數組成，函數定義在`unistd.h`中，函數原型爲：

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

	- exec()系列函數爲**系統調用**，執行後，
	會將當前的進程**完全替換**爲執行新程序的進程
	（即這個進程exec()調用成功之後的代碼都不再運行），但`PID`不變。
	- exec()系統調用比system()函數要**高效**，
	exec()與fork()搭配是Unix系統中最**常用**的系統進程創建組合。
	- 通常exec()不會返回，除非發生了錯誤。
	出錯時，exec()返回-1並且置errno，同時繼續執行餘下的代碼。
	- 在exec()函數組中，只有execve()函數是真正的系統調用，
	其它的幾個函數都是execve()封裝而成的庫函數。
	- 參數`path`爲絕對路徑，`file`爲命令名稱。
	- execl()、execlp()、execle()三個函數接收的參數個數是可變的，
	參數以一個空指針結束（`(char*)0`或NULL），
	用多個字符數組`*arg`來傳遞要執行的程序的參數。
	- execv()、execp()、execve()等函數參數個數是固定的，
	將要傳遞給要執行的程序的參數放在二維字符數組`*argv[]`中
	（對應main函數參數中的`*argv[]`），
	而二維字符數組`*envp[]`中保存exec()函數要運行的程序的環境變量，
	無論是傳遞給被執行程序的參數字符數組`*argv[]`，
	或是環境變量字符數組`*envp[]`都要以一個空指針結尾。

	實例代碼：

	```c
	#include <stdio.h>
	#include <unistd.h>

	int main(void)
	{
		char* envp[] = { "LC_ALL=zh_CN.UTF-8", NULL };

		/*
			不要想當然地認爲*argv[]的第一個參數是沒用的，
			第一個參數不能爲NULL，否則exec()系統調用執行失敗，
			而且exec()執行新指令時如果指令參數不正確時，
			指令在終端上顯示的錯誤信息會將argv[0]作爲輸入的程序名！
		*/
		char* argv[] = { "ls", "-l", NULL };

		printf("The PID is %d\n", getpid());

		/*
			execve()系統調用的envp如果不需要設置可以填NULL。

			與system()函數不同，用exec系統調用在執行程序時，
			如果參數中的envp爲NULL，則程序就在無環境變量的狀態運行，
			即系統當前的環境變量不會對exec()系統調用產生影響，但會對依賴shell的system()函數產生影響。

			在這段代碼中，如果用戶爲中文環境且exec()系統調用沒有設置環境變量，
			則ls命令顯示的中文目錄會爲問號，但system()函數執行ls命令則能正常顯示。
		*/
		execve("/usr/bin/ls", argv, envp);
		/*
			上一句代碼等價於
			execle("/usr/bin/ls", "ls", "-l", NULL, envp);

			如果運行一些不需要環境變量的程序，可以有更簡單的方式，比如：
			execlp("ps", "ps", "-l", NULL);
		*/
		return 0;
	}
	```

子進程默認會繼承父進程已打開的文件描述符。
當父進程持有描述符爲`Socket`描述符時，
子進程會繼承對應描述符代表的**監聽端口**、**監聽地址**等信息，
當父進程結束時，端口不會被釋放，而是由子進程繼續佔用。
避免子進程繼承`Socket`描述符，創建`Socket`時應設置`SOCK_CLOEXEC/FD_CLOEXEC`屬性：

```c
// 在創建Socket描述符時使用 SOCK_CLOEXEC 屬性
int sock_fd = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC);

// 使用 fcntl() 調用對已創建的描述符追加 FD_CLOEXEC 屬性
fcntl(fd, F_SETFD, fcntl(fd, F_GETFD) | FD_CLOEXEC);
```

## 等待進程
可以在父進程中調用`wait()`函數讓父進程等待子進程結束，
還可以使用`waitpid()`函數來等待某個**特定進程**結束。

函數定義在`sys/wait.h`中，函數原型爲：

```c
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
```

- `status`參數爲指向進程狀態信息的指針，`wait()/waitpid()`函數都將狀態信息寫到status所指向的內容。
- `pid`參數爲要等待的進程的pid，如果該參數爲-1，則返回任一子進程的信息。
- `options`參數可用來改變函數的行爲。

wait()函數返回子進程的pid。
waitpid()運行成功返回等待進程的pid，失敗返回-1並置errno。

`/sys/wait.h`頭文件中定義了宏來解釋狀態信息：

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

實例代碼：

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
		int child_pid = waitpid(pid, &status, 0); // 等效於 int child_pid = wait(&status);

		printf("This is the parent process!\n");
		printf("The PID is %d\n", getpid());

		if (pid == child_pid)
			printf("The child's PID is %d\n", child_pid);

		/*
			若等待進程正常結束， WIFEXITED 宏返回非0值
			若 WIFEXITED 非0，打印等待進程的退出碼
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

運行結果：

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

## Daemon（守護進程）
**守護進程**是一類具有較長生存週期的進程，守護進程在後臺運行，並且沒有控制終端。

編寫守護進程一般有如下幾個步驟：

1. 調用`fork()`函數，同時退出**父進程**。

	使用了fork()函數之後父進程退出，則子進程成爲孤兒進程，由`init系統`接管。
	子進程雖然脫離了父進程，但仍然處於父進程的進程組中和會話中，與控制終端的聯繫依然存在。

1. 調用`setsid()`函數，爲子進程創建新的會話。

	使用了setsid()函數，子進程脫離了原先父進程的進程組與會話，並且不再與原先的控制終端相關聯。
	子進程在創建了會話之後成爲了會話和新進程組的**首進程**，依然有可能被系統分配控制終端。

1. 再次調用`fork()`函數，再次退出**父進程**。

	再次fork()退出父進程之後，新的子進程不再是進程組和會話的首進程，不再有被分配控制終端的可能。

實例代碼：

```c
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

// 打印進程的PID、PPID、SID、PGID、控制終端等信息
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

	// fork()並退出父進程
	if (fork())
		_exit(0);
	print_process_info("After fork once");

	// 若正常fork()，則此時父進程已退出，子進程由init系統接管
	// 使用setsid()創建新的會話(New Session)，同時使當前進程爲新會話的進程組組長
	setsid();
	print_process_info("After setsid");

	// fork()並退出父進程，之後子進程不再是會話的組長進程
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

運行結果：(GCC 6.1.1 && ArchLinux x64)

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



# Signal（信號）
信號是Unix系統響應某些條件而產生的的一個事件，進程接收到信號會採取一些相應的行動。
信號的相關函數定義在頭文件`signal.h`中。

使用`fork()`時，子進程會繼承父進程註冊的信號處理函數。

常用的信號有`SIGINT`(中斷信號，使用`CTRL + C`組合鍵觸發)，`SIGQUIT`(退出信號，使用`CTRL + \`組合鍵觸發)。
使用`kill`指令發送信號，默認發送信號爲`SIGTERM`。

終端連結斷開時，會產生`SIGHUP`信號。
不同運行時的進程對信號的默認處理規則不同，例如Java進程在收到SIGHUP信號會退出程序，但C/C++程序則不會。

## 信號處理
使用`signal()`或`sigaction()`函數將需要處理的信號與信號處理函數的函數指針綁定。

- `signal()` 函數

	signal()函數是傳統Unix的信號處理方式。函數原型爲：

	```c
	#include <signal.h>

	void (*signal(int sig, void (*func)(int)))(int);
	```

	- `sig`參數爲要處理的信號。
	- `func`參數爲要綁定的信號處理函數。

	對於信號處理函數函數指針參數`func`，存在兩個特殊值：

	- `SIG_IGN` 將其綁定到一個信號上則表示**忽略信號**
	- `SIG_DFL` 將信號的處理方式恢復爲**默認動作**

- `sigaction()` 函數

	現代Unix中，使用更加健壯的信號編程接口`sigaction()`函數，函數的原型爲：

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

	- 參數`act`指向包含信號處理函數的結構體。
	- 參數`oact`會被寫入原先的信號處理結構體(可以取`NULL`)。

	其中，結構體`sigaction`成員：

	- `sa_handler` 指向信號處理函數的函數指針
	- `sa_mask` 屏蔽信號字，可以使用`sigemptyset(*sigset_t)`函數將信號集置空
	- `sa_flags` 設置信號處理選項，沒有特別要求可以設爲`NULL`

## 信號發送
使用`kill()`函數可以向**指定進程**發送信號，使用`raise()`可以向**當前進程**發送信號。
函數定義在`signal.h`中，示例：

```c
int raise(int sig);
int kill(pid_t pid, int sig);
```

- `pid`參數爲目標進程的進程id。
- `sig`爲信號值。

使用kill()、raise()發送信號，接收信號的是**整個**目標進程。

在**多線程**環境下，使用kill()、raise()發送信號，進程內包含的**所有線程**都會接收到信號。
如果需要發送信號給**指定線程**，需要使用`pthread_kill()`，函數定義在`signal.h`中：

```c
int pthread_kill(pthread_t thread, int sig);
```

- `thread`參數爲目標線程的描述符。
- `sig`參數爲信號值。

函數成功返回`0`，失敗時返回錯誤代碼。

## 信號觸發
信號機制實質上是**軟件中斷**，信號處理函數**不會**運行在獨立的線程，
而是**中斷**現有的代碼運行信號處理函數。
一個進程觸發了信號處理函數，則在信號處理函數結束返回之後纔會繼續運行先前的代碼。

如下代碼所示：

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

通過循環中的打印的耗時可以看出，每次觸發信號處理函數`deal_signal()`，
循環便會**暫停**，直到`deal_signal()`運行完畢返回。
在BSD和Linux中，運行信號處理函數期間再次收到信號會**阻塞**此信號，直到信號處理函數返回。
在部分Unix中，運行信號處理函數時可能會將此信號**重置**爲默認操作，
在此類情況下，需要在信號處理函數中重新綁定信號。

## 可靠信號/不可靠信號
可靠信號機制最初來自於`BSD`。

在Linux中，**不可靠**信號範圍爲`1(SIGHUP) ~ 31(SIGSYS)`，
**可靠信號**的範圍爲`34(SIGRTMIN) ~ 64(SIGRTMAX)`。
**不可靠**信號**不支持**信號隊列，當同類信號在短時間內**多次**觸發，
不可靠信號只會觸發信號處理函數**一次**，其餘的同類信號被**忽略**。

## 信號屏蔽
直接在**進程**中屏蔽指定信號可以使用下列函數，函數定義在`signal.h`中：

```c
#include <signal.h>

int sigsetmask(int mask); // 設定屏蔽信號爲mask
int sigblock(int mask); // 向現有屏蔽信號中添加mask
```

- `mask`參數爲要屏蔽的信號**mask**，由`sigmask(signum)`宏根據輸入的信號值生成。

函數返回之前設定的**mask**值。
實例代碼如下：

```c
// 多個信號可以使用邏輯或操作符相連
int mask = sigmask(SIGINT) | sigmask(QUIT);
// 設置當前的信號屏蔽爲SIGINT和SIGQUIT
sigsetmask(mask);
// 添加屏蔽SIGALRM信號
sigblock(sigmask(SIGALRM));
```

也可以使用`sigprocmask()`來完成信號屏蔽/解除屏蔽等操作，函數定義在`signal.h`中：

```c
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
```

- `how`參數定義函數的行爲，取值如下：

	1. `SIG_BLOCK` 向已有的屏蔽信號集合中**添加**`set`參數中的信號
	1. `SIG_UNBLOCK` 向已有的屏蔽信號集合中**移除**`set`參數中的信號
	1. `SIG_SETMASK` 將當前的屏蔽信號集合**替換**爲`set`參數中的信號

- `set`參數爲輸入的信號集合。
- `oset`參數爲輸出信號集合，函數運行結束會將新的信號集合寫入`oset`參數中，不需要該參數可設爲`NULL`。

函數執行成功返回`0`。執行失敗返回`-1`，並置`errno`。

示例：

```c
// 創建信號集合，置空後添加SIGINT信號
sigset_t set;
sigemptyset(&set);
sigaddset(&set, SIGINT);

// 屏蔽SIGINT信號
sigprocmask(SIG_SETMASK, &set, NULL);

// 信號集加入SIGQUIT信號
sigaddset(&set, SIGQUIT);

// 添加屏蔽SIGUQUIT信號
sigprocmask(SIG_BLOCK, &set, NULL);

// 取消SIGINT和SIGQUIT的信號屏蔽
sigprocmask(SIG_UNBLOCK, &set, NULL);
```

## 屏蔽線程信號
`sigsetmask()`和`sigprocmask()`等函數設置的屏蔽信號對於**整個進程**有效。
在**多線程**環境下，使用sigprocmask()則進程內包含的**所有線程**的屏蔽信號集都會被修改。
創建新的線程時，新的線程會**繼承**原有線程的**屏蔽信號集**。

需要設置**指定線程**的屏蔽信號集，可以使用`pthread_sigmask()`函數，函數定義在`signal.h`中：

```c
int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
```

`pthread_sigmask()`函數參數與作用與`sigprocmask()`類似，有兩點區別：

- 設置的屏蔽信號集僅對**當前線程**生效。
- 調用失敗時直接返回錯誤代碼，而不是像`sigprocmask()`那樣返回`-1`並置`errno`。

## 信號相關的進程控制函數
`pause()`、`sleep()`等函數在多線程情況下的觸發機制。

- `pause()` 函數

	使用pause()可以掛起線程，直到當前進程捕捉到了一個**信號**，函數定義在`unistd.h`中，示例：

	```c
	int pause(void);
	```

	只有進程捕獲了信號，執行了信號處理程序並從其返回時，pause()函數才返回。
	pause()函數**不存在**成功返回值，當進程捕捉到信號並從信號處理函數返回時，
	pause()返回-1，並置errno爲`ENTER`。

	在**多線程**環境中，在未設置`pthread_sigmask()`的情況下，
	信號優先級使得只有**主線程**的pause()會在信號處理函數結束後返回。
	在主線程以外的線程中，除非使用`pthread_kill()`發送消息到指定線程，否則無法觸發pause()函數。

- `sleep()` 函數

	使用`sleep()`可以**掛起**線程（阻塞），函數定義在`unistd.h`中，函數原型爲：

	```c
	unsigned int sleep(unsigned int seconds);
	```

	- `seconds`參數爲需要休眠的時間，單位爲**秒**。

	若線程在設定的時間中正常休眠，返回值爲`0`。
	若在掛起期間進程捕獲到一個**信號**，
	並從信號處理函數返回，則無論休眠時間是否滿足，休眠不再繼續，
	sleep()立即函數結束，返回值爲**尚未休眠**的時間。

	在**多線程**環境中，在未設置`pthread_sigmask()`的情況下，捕獲信號，並從信號處理函數返回，
	只會結束進程**主線程**中正在運行的sleep()函數，對其它線程中的sleep()無影響。

	在Solaris中sleep()內部實現採用alarm()，
	在BSD和Linux中sleep()由`nanosleep()`實現，與信號無關。

- `alarm()` 函數

	使用alarm()可以使當前進程在指定時間之後收到`SIGALRM`信號，函數定義在`unistd.h`中，示例：

	```c
	unsigned alarm(unsigned seconds);
	```

	- `seconds`參數爲發送信號的延遲時間，取`0`時表示清除原有alarm()設置。

	一個進程同時只能存在一個alarm()，調用alarm()時若之前已經設置了alarm()且尚未觸發，
	則返回上一個alarm()的剩餘等待時間，同時以當前alarm()的設置**替換**上一個。
	默認情況下，若沒有設置SIGALRM的信號處理函數，系統收到SIGALRM會終止進程。

## 多線程信號處理
在多線程的環境下，信號處理需要考慮更多的情況：

- 默認情況下，Unix中的信號機制是對於**整個進程**而言的，
使用`kill()`發送信號，則**整個進程**都將收到信號。
- 使用`signal()`綁定信號處理函數會對**整個進程**生效。
- 在多線程的程序中，若不做特殊處理，則發送給進程的信號會由系統選擇一個線程來處理信號。
- 系統會在**沒有**屏蔽此信號的線程中選擇**pid最小**的那個線程來處理信號。
- 在未設置屏蔽信號的情況下，主線程的pid最小，因而一般會選擇**主線程**來響應信號。
這使得**默認情況**下只有**主線程**的`pause()`、`sleep()`函數能夠被信號中斷。

多線程環境下的信號處理一般有兩種方式：

- 在指定線程中處理信號：

	除目標線程外，其它線程全部使用`pthread_sigmask()`在線程中屏蔽指定信號，
	讓信號只能被**指定線程**處理。示例：

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

		// 解除SIGINT的信號屏蔽，讓當前線程能夠處理SIGINT信號
		pthread_sigmask(SIG_UNBLOCK, &set, NULL);

		while (1)
			printf("Pthread sleep surplus time: %d seconds.\n", sleep(3));
		return NULL;
	}

	int main(void)
	{
		signal(SIGINT, deal_signal);

		// 整個進程屏蔽SIGINT信號
		sigemptyset(&set);
		sigaddset(&set, SIGINT);
		sigprocmask(SIG_BLOCK, &set, NULL);

		pthread_t pfd;
		pthread_create(&pfd, NULL, thread_func, NULL);

		pthread_join(pfd, NULL);

		return 0;
	}
	```

	默認情況下，`SIGINT`信號會被主線程處理(不會中斷子線程中的`sleep()`)。
	通過設置屏蔽信號，讓`SIGINT`被主線程屏蔽而由子線程處理，
	使得`SIGINT`能夠中斷子線程的sleep()函數，讓sleep()提前結束。

- 以同步的方式處理異步信號：

	使用`sigwait()`函數等待指定信號。sigwait()函數定義在`signal.h`中：

	```c
	int sigwait(const sigset_t *restrict set, int *restrict sig);
	```

	- `set`參數爲要等待的信號集合。
	- `sig`參數指向等待到的信號值，函數會將等待到的信號值寫入傳入的地址中。

	運行sigwait()會阻塞所處線程，直到所處線程接受到`set`信號集中的信號。
	函數執行成功返回0，失敗時返回錯誤代碼。
	使用sigwait()需要保證等待的信號至少被sigwait()**所處線程**之外的線程屏蔽。

	對於sigwait()所處的線程，在macOS和Linux等Unix系統上，
	sigwait()的優先級比默認的信號處理行爲以及綁定的信號處理函數要高，
	接受到信號時，優先結束sigwait()的阻塞而不是執行設定/默認的信號處理行爲。

	在**多個**sigwait()共存的情況下，系統會**隨機**選取一個線程中的sigwait()進行響應。

	示例：

	```c
	#include <stdio.h>
	#include <signal.h>
	#include <pthread.h>

	sigset_t set;
	int thread_count = 0;
	pthread_mutex_t mutex;

	// 由於sigwait()優先級更高，deal_signal()函數並未觸發
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

		// 子線程即便使用pthread_sigmask()解除SIGINT信號屏蔽，依舊會優先響應sigwait()
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
			設置主線程信號屏蔽。
			若主線程不屏蔽SIGINT信號，則按照信號處理優先級，信號會被主線程處理。
			信號被主線程處理，子線程沒有處理信號的機會，則sigwait()會一直阻塞。
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

	運行結果：(OS X 10.11.3)

	```
	Run thread 1!
	Run thread 2!
	^C
	Thread 2 receive signal SIGINT.
	^C
	Thread 1 receive signal SIGINT.
	```

	多個sigwait()存在時，選取的處理線程是隨機的，運行結果也可能是1號線程先響應信號。



# pthread（POSIX線程）
在Unix系統中，多線程開發相關函數定義在頭文件`pthread.h`中。
在Linux中編譯使用了線程庫的程序時，需要鏈接`pthread`庫，編譯指令如下：

```
$ cc -lpthread 源碼文件
```

在`FreeBSD`以及`macOS`中，編譯使用了線程庫的程序**無需**鏈接`pthread`庫。

## Linux下的線程實現
`Linux Kernel 2.6`之後，線程的實現爲`NPTL`，全稱`Native POSIX Thread Library`（**本地POSIX線程庫**）。

- 在Linux內核中，線程和進程都使用`task_struct`結構體表示，
線程僅是一類特殊的進程(創建時使用不同的clone標識組合)。
- Linux提供了`clone()`調用，使用clone()創建子進程時，
可以選擇性地共享父進程的資源，創建出的子進程被稱爲`LWP, Low Weight Process`（**輕量級進程**）。
- 早期的Linux（Linux Kernel 2.6之前）使用Linux Threads線程庫，即通過**輕量級進程**來實現線程。
- Linux Threads庫沒有實現POSIX的線程定義，每個線程在ps指令下顯示爲進程，
並且不同線程使用`getpid()`返回的進程pid也不相同，
現代Linux（採用NPTL之後的Linux）**不會**出現此類情況。
- Linux Kernel 2.6之後，內核中存在**線程組**的概念，
`task_struct`結構中增加了`tgid(thread group id)`字段，
若某個task_struct是**主線程**, 則它的tgid等於pid，
否則tgid等於進程的pid（即主線程pid）。
此外，每個線程依舊是一個task_struct，依然有自己的pid。
- 在Linux Kernel 2.6之後，使用`getpid()`獲取的是tgid，
因而進程中的每個線程使用getpid()返回值相同（主線程pid）。
獲取線程自身的pid需要用到系統調用`gettid()`，
gettid()是Linux特有的系統調用，在其它Unix中並不存在，
glibc沒有提供gettid()的封裝，使用gettid()需要通過syscall()調用。
- NPTL的實現依賴於Linux Kernel 2.6內核的task_struct改動，
因此在`2.4`、`2.2`等舊版本的內核上無法使用NPTL，
在採用了NPTL的Linux上，線程的行爲與其它Unix更爲相似。

## 線程創建
創建線程使用`pthread_create()`函數。

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

- `thread`參數爲將新建線程的線程標誌符寫入所給的地址
（注意線程標識符的類型爲`pthread_t`，使用int型編譯器會提示**不兼容**）。
- `attr`參數爲啓動線程時設置**特殊屬性**（一般情況下用不到，填`NULL`即可）。
- `start_routine`參數爲一個指向返回值和參數都爲void*類型的函數的函數指針，該指針指向的函數即爲新線程要執行的函數。
- `arg`參數爲要傳遞到`start_routine`所指向函數的值（若無傳遞的參數，可置**NULL**）。

`thread`參數必須要填入**有效**的地址，填`NULL`會引起程序崩潰。
創建新線程成功則返回`0`，未創建成功返回**錯誤代碼**，可根據手冊查看錯誤代碼判斷錯誤類型。

## 線程等待
等待線程使用`pthread_join()`函數。

```c
int pthread_join(pthread_t thread, void **retval);
```

- `thread`參數爲要等待的線程的**線程描述符**。
- `retval`參數爲要等待的線程的返回值的地址（不使用線程返回值可置`NULL`）。

該函數爲**阻塞**函數。
`pthread_join()`函數只會等待指定線程標識符對應的線程，對其它線程不會造成影響，依然是併發執行。

默認情況下，主程序是不會等待線程執行的，無論線程是否執行完畢，主程序都會依次執行直到結束。
由於線程資源共享，一旦主程序結束，該程序創建的線程無論是否執行完畢都會立即被關閉。
如果需要主程序等待某個線程執行完畢，即可以使用`pthread_join()`函數。

## 線程取消
取消線程使用`pthread_cacnel()`函數。

```c
int pthread_cancel(pthread_t thread);
```

- `thread`參數爲需要取消的線程的**線程描述符**。

取消線程成功返回值爲`0`，取消線程失敗返回一個非`0`的**錯誤代碼**。

## 線程終止
退出、終止一個線程使用`pthread_exit()`函數。

```c
void pthread_exit(void *retval);
```

線程調用該函數終止自身，如同進程的`exit(num)`函數一樣。

`pthread_exit()`函數的參數爲線程的返回內容，不要將`retval`指向一個**局部變量**，
因爲調用`pthread_exit()`函數之後線程會結束，線程函數內的局部變量（棧變量）將會被**刪除**。
與其它函數類似，線程也可以使用`return`提供返回值。

## 互斥量
pthread同樣提供了**互斥量**進行線程同步。
互斥量相關的函數也定義在頭文件`pthread.h`文件中，常用的函數有：

```c
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

互斥量可以讓程序員鎖住某個對象，使得每次只有一個線程能對其進行訪問。
`pthread_mutex_lock()`在未成功加鎖時會一直阻塞線程。
使用`pthread_mutex_init()`函數初始化一個互斥量，`mutex`參數爲要初始化的互斥量，
`attr`參數爲互斥量屬性，沒有特殊要求可以設置爲`NULL`(默認爲**線程同步**)。

實例代碼：

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define MYMES1 SIGUSR1 + 1 // 自定義信號，不能設置太大，Linux中32～64信號爲用戶可用
#define MYMES2 SIGUSR1 + 2

pthread_t thread_fd = 0;
pthread_t thread_fd1 = 0;
pthread_mutex_t mutex;

void deal_signal(int signal)
{
	switch(signal)
	{
	case SIGQUIT: // 捕獲SIGQUIT信號，用 "ctrl+\" 組合鍵觸發
		pthread_cancel(thread_fd); // 取消一號線程
		pthread_cancel(thread_fd1); // 取消二號線程
		printf("結束一、二號線程，接下來三、四號線程沒有互斥量，輸出內容會相互交錯！\n");
		if (pthread_mutex_destroy(&mutex) == -1) // 刪除鎖
			printf("刪除失敗！\n");
		break;
	case MYMES1:
		printf("有互斥變量的時候，內容不會交錯。\n");
		break;
	case MYMES2:
		printf("沒有互斥變量的時候，內容會相互交錯。\n");
		break;
	}
}

void* thread_func(void* arg)
{
	while (1)
	{
		if (!strcmp(arg, "三號線程") || !strcmp(arg, "四號線程"))
			kill(getpid(), MYMES2); // 三號、四號線程發送自定義信號MYMES2
		else if (pthread_mutex_lock(&mutex) == -1)
			printf("加鎖失敗！\n");
		else
			kill(getpid(), MYMES1); // 一號、二號線程發送自定義信號MYMES1

		printf("%s開始。\n", (char*)arg);

		int num = 0;
		while (num++ < 3)
		{
			sleep(2);
			printf("%s循環第%d次\n", (char*)arg, num);
		}

		if (pthread_mutex_unlock(&mutex) == -1)
			printf("解鎖失敗！\n");

		sleep(2); // 線程休眠一秒，否則資源會一直被一個線程佔有
	}
}

int main(void)
{
	char* str1 = "一號線程";
	char* str2 = "二號線程";
	char* str3 = "三號線程";
	char* str4 = "四號線程";

	struct sigaction sig;
	sig.sa_handler = deal_signal;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGQUIT, &sig, 0); // 現代Unix信號捕捉函數

	signal(MYMES1, deal_signal); // 傳統Unix信號捕捉函數
	signal(MYMES2, deal_signal);

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread_fd, NULL, thread_func, str1);
	pthread_create(&thread_fd1, NULL, thread_func, str2);
	pthread_join(thread_fd1, NULL); //等待二號線程結束
	pthread_create(&thread_fd, NULL, thread_func, str3); // 創建三號線程
	pthread_create(&thread_fd, NULL, thread_func, str4); // 創建四號線程
	pthread_join(thread_fd1, NULL);

	return 0;
}
```

## 互斥量用於進程同步
互斥量用於**進程同步**時，會用到下列函數，頭文件同樣在`pthread.h`中：

```c
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict attr, int *restrict pshared);
```

通過設置`pthread_mutex_init()`函數的參數`attr`來實現**進程間互斥**。
使用以下方式初始化`pthread_mutexattr_t`結構體。

```c
pthread_mutexattr_t attr;
pthread_mutexattr_init(&attr);
pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED); // 第二個參數如果取PTHREAD_PROCESS_PRIVATE則互斥量僅爲進程內部所使用，這是默認情況，即pthread_mutex_init()函數的第二個參數取NULL時的情況
```

需要注意，由於每個進程的地址空間是獨立的，每個進程定義的變量無法被其它進程所訪問。

若需要使用互斥量進行進程間的同步，不僅需要設置其共享屬性，還需要使用Unix的**共享內存**機制。
創建一塊共享內存，將互斥量定義在**共享內存**中，以此來保證一個互斥量能被多個進程訪問，實現進程互斥。

實例代碼：

文件 `process_mutex_parent.c`：

```c
#define PROJECT_ID 0
#define PATH "/home/dainslef"

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/shm.h> //包含共享內存的相關函數

int shm_id; //共享內存標誌，類似於文件標識符
pthread_mutexattr_t attr;

void dealSignal(int signal)
{
	if (signal == SIGQUIT
			&& !pthread_mutex_unlock((pthread_mutex_t*)shmat(shm_id, NULL, 0)))
	{
		printf("解鎖互斥量成功！\n父進程即將結束！\n");

		for (int i = 5; i > 0; i--)
		{
			printf("倒數計時：%d\n", i);
			sleep(1);
		}

		printf("父進程結束！\n");
		_exit(0);
	}
}

int main(void)
{
	shm_id = shmget(ftok(PATH, PROJECT_ID), sizeof(pthread_mutex_t), IPC_CREAT | 0600);
	pthread_mutex_t *mutex = (pthread_mutex_t*)shmat(shm_id, NULL, 0);

	pthread_mutexattr_init(&attr); // 初始化權限結構體attr
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

	if (!pthread_mutex_init(mutex, &attr))
		printf("成功創建了互斥量！\n"); // 創建了一個進程互斥的互斥量

	signal(SIGQUIT, dealSignal);
	printf("父進程啓動：\n");

	if (!pthread_mutex_lock((pthread_mutex_t*)shmat(shm_id, NULL, 0)))
		printf("父進程互斥量加鎖成功！");

	while (1)
	{
		printf("父進程在執行！\n");
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

	printf("子進程啓動：\n");

	if (!pthread_mutex_lock((pthread_mutex_t*)shmat(shm_id, NULL, 0)))
		printf("子進程互斥量加鎖成功！");

	while (1)
	{
		printf("子進程在執行！\n");
		sleep(2);
	}

	return 0;
}
```

運行結果：（文字描述）

`Process_Mutex_Parent`先運行，創建互斥量並鎖住，然後一直循環。
`Process_Mutex_Child`後執行，進程阻塞在`pthread_mutex_lock()`函數上。
在`Process_Mutex_Parent`中觸發`SIGQUIT`信號，由信號處理函數釋放鎖，倒數計時後結束進程。
`Process_Mutex_Child`在`Process_Mutex_Parent`釋放互斥量鎖之後立即加鎖成功，開始循環。



# XSI IPC
`XSI IPC`包括**消息隊列**、**共享內存**、**信號量**。
`XSI IPC`來自`SystemV`，三類`XSI IPC`擁有相似的API，包括如下的一組函數：

```c
int xxxget(key_t key, ...); // 創建/獲取IPC文件描述符
int xxxctl(int ipc_fd, ...); // 添加IPC設定
...
```

## IPC 標誌
`XSI IPC`都使用類型爲`key_t`的`key`值來區分不同的IPC。`key`值可以通過以下函數生成：

```c
#include <sys/types.h>
#include <sys/ipc.h>
key_t ftok(const char *pathname, int proj_id);
```

- `pathname`參數爲約定的路徑。
- `proj_id`參數爲約定的項目編號。

通過指定**路徑**和**項目編號**能夠得到唯一的`key`值。
函數執行成功返回生成的`key`值，執行失敗返回`-1`。

## XSI IPC 特點
`XSI IPC`並沒有遵循Unix中**一切皆文件**的思想，`XSI IPC`在文件系統中沒有名字，
不能使用文件描述符進行表示，不能使用`open()`、`write()`等文件操作對其進行控制，
亦不能對其使用`select()`、`epoll()`、`kqueue()`等IO複用機制。

`XSI IPC`不能使用傳統的shell指令進行管理，不能使用`ls`查看，不能使用`rm`刪除。

查看`XSI IPC`使用`ipcs`指令：

```
$ ipcs
```

刪除`XSI IPC`使用`ipcrm`指令：

```
$ ipcrm { shm | msg | sem } id
```

## SystemV 共享內存
共享內存是一種`IPC, Inter-Process Communication`（進程間通信）機制，屬於三類`XSI IPC`之一。
相比信號量等IPC機制，共享內存有着最高的效率，因爲共享內存不涉及複製操作。

共享內存的相關函數定義在`sys/shm.h`中。

### 創建/獲取共享內存
使用`shmget()`函數創建共享內存或獲取已經存在的**key值**的共享內存。

```c
int shmget(key_t key, size_t size, int shmflg);
```

- `key`參數爲`ftok()`函數生成的**共享內存**標誌。
- `size`參數爲共享內存的大小。
- `shmflg`參數爲特殊標識，取`0`時獲取**key值**對應的共享內存，
若傳入的**key值**對應的共享內存**未創建**，則調用**失敗**。

創建共享內存使用`IPC_CREAT`標識，創建的同時可以手動設定共享內存的讀寫權限如`IPC_CREAT | 0660`。
使用IPC_CREAT標識時，若傳入**key值**對應的共享內存已經存在，
不會調用失敗，而是忽略該標識，返回已存在的共享內存的描述符。

若需要創建一塊**唯一**的共享內存，則使用`IPC_CREAT | IPC_EXCL`。
使用`IPC_CREAT | IPC_EXCL`標識時，若傳入`key`參數對應的共享內存已存在，則創建**失敗**。

`IPC_PRIVATE`標誌用於創建一個只屬於創建進程的共享內存。
共享內存創建成功時返回**共享內存描述符**（非負整數），失敗時返回`-1`。

### 共享內存獲取
使用`shmat()`函數獲取共享內存的**地址**。

```c
void *shmat(int shmid, const void *shmaddr, int shmflg);
```

- `shmid`參數爲目標共享內存描述符。
- `shmaddr`參數爲將共享連接到當前進程中的地址，
若不需要指定共享內存連接到進程中的**指定地址**，則該參數可以爲`NULL`(讓系統分配可用的地址)。
- `shmflg`參數爲一組標誌位，如果`shmaddr`參數手動指定了地址，則搭配`shmflg`參數取`SHM_RND`，
若**只讀**共享內存則設定`SHM_RDONLY`，不使用此參數可設爲`0`。

函數運行成功返回**共享內存**的**首地址**，運行失敗返回數值`-1`。

### 共享內存分離
使用`shmdt()`函數分離共享內存。

```c
int shmdt(const void *shmaddr);
```

- `shmaddr`參數爲共享內存的**首地址**，
運行成功之後共享內存在調用此函數的進程中將**不再可用**（但其它進程中依然**正常**）。

調用成功時返回`0`，失敗返回`-1`。

## 共享內存控制
使用`shmctl()`函數設置共享內存的**標識**。

```c
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

- `shmid`參數爲共享內存描述符。
- `command`參數爲要對共享內存發出的指令，常用的指令爲`IPC_RMID`，
用於**刪除**共享內存，執行刪除操作時- `buf`參數可以取值NULL。

函數調用成功返回`0`，失敗返回`-1`。

與信號量機制類似，若`shmget()`函數以`IPC_CREAT | IPC_EXCL`的形式創建**唯一**共享內存，
若沒有在進程結束前將共享內存刪除，則下次程序執行時將**不能**再以该形式創建**key值**相同的共享內存。

## Semaphore（SystemV 信號量）
信號量是一種進程間通信(`IPC, Inter-Process Communication`)機制，屬於三類`XSI IPC`之一。
信號量用於控制進程對資源的訪問，但信號量也可以用於線程。
在進程開發中，常用的信號量函數定義在`sys/sem.h`文件中。

### 信號量創建/獲取
使用`semget()`函數創建一個新的信號量或獲取一個已經存在的信號量。

```c
int semget(key_t key, int num_sems, int sem_flags);
```

- `key`參數爲`ftok()`函數生成的**信號量**標誌。
- `num_sems`參數爲需要的信號量數目，一般爲`1`。
- `sem_flags`參數爲信號量標誌位，多個標誌通過邏輯或操作符`|`相連。

函數調用成功時返回信號量描述符，失敗時返回`-1`。
`sem_flags`參數上常用的信號標識有`IPC_CREAT`，用於**創建**新的信號量，
若**key值**對應的信號量已被創建，並不會調用失敗，而是**忽略**該標誌。
`IPC_CREAT | IPC_EXCL`標識，用於創建一個**新的**、**唯一**的信號量，
若**key值**對應的信號量已被創建，則調用**失敗**。
使用`IPC_CREAT | IPC_EXCL`標識需要注意，
使用此種方式創建信號量在使用完畢後需要調用`semctl()`函數釋放，
否則下次運行同樣的程序會由於信號量已經存在（未被釋放）而造成調用失敗。
`IPC_CRAET | 0666`標識，用於創建有**讀寫權限**的信號量。

### 改變信號量值
使用`semop()`函數修改信號量的值。

```c
int semop(int sem_id, struct sembuf *sem_ops, size_t num_sem_ops);
```

- `sem_id`參數爲信號描述符，由`semget()`函數得到。
- `sem_ops`參數爲指向`sembuf`結構體的指針（多個信號量時可以指向sembuf結構體數組）。
- `num_sem_ops`參數爲`sembuf`結構體的數量，一般爲`1`。

`sembuf`結構體的定義爲：

```c
struct sembuf
{
	unsigned short sem_num; // 信號量的編號，在沒有使用多個信號量的情況下，一般爲0
	short sem_op; // 信號量操作，一般可以取-1或是+1，分別對應P(請求)、V(釋放)操作
	short sem_flg; // 操作標誌符，一般取SEM_UNDO
};
```

函數調用成功返回`0`，調用失敗返回`-1`並置**errno**。

### 信號量信息設置
使用`semctl()`函數來執行信號量集上的控制操作。

```c
int semctl(int sem_id, int sem_num, int command, ...);
```

- `sem_id`參數爲信號量描述符。
- `sem_num`參數爲信號量編號，一般沒有多個信號量時取`0`。
- `command`參數爲要執行的操作的標誌位。

`command`參數可以有很多不同的值，常用的有`IPC_RMID`，
用於刪除一個信號量（若信號創建方式是`IPC_CREAT | IPC_EXCL`，則務必要在程序結束時刪除信號量）。
`command`設置爲`SETVAL`，則用於**初始化**一個信號量，此時函數需要有第四個參數，聯合體`union semun`，
通過設置`semun`的`val`成員的值來初始化信號量。

`semun`聯合體的定義爲：

```c
union semun
{
	int val; /* value for SETVAL */
	struct  semid_ds *buf; /* buffer for IPC_STAT & IPC_SET */
	u_short *array; /* array for GETALL & SETALL */
};
```

函數失敗時返回`-1`，成功時有多種返回值，參數爲`SETVAL`或`IPC_RMID`時運行成功返回`0`。

實例代碼：

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
	semop(sem_id, &sem_ok, 1); // 將信號量+1,釋放資源
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
		printf("信號量創建成功！\n");

	sem_wait.sem_num = sem_ok.sem_num = 0;
	sem_wait.sem_op = -1; // 設置操作數，等待時-1
	sem_ok.sem_op = 1; // 等待完畢+1
	sem_wait.sem_flg = sem_ok.sem_flg = SEM_UNDO;

	semctl(sem_id, 0, SETVAL, 1); // 初始化信號量時可以不自定義聯合體直接賦值
	semop(sem_id, &sem_wait, 1); // 信號量-1，鎖住資源

	while (1) // 由於信號量被鎖，因此A在執行此段代碼時，B在等待
	{
		sleep(3);
		printf("正在執行\n");
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
	semctl(sem_id, 0, IPC_RMID); // 刪除信號量
	_exit(0);
}

int main(void)
{
	signal(SIGINT, deal_signal);

	sem_id = semget(ftok(PATH, PROJECT_ID), 1, 0600); // 需要保證進程有讀寫信號量的權限
	if (sem_id == -1)
	{
		perror("semget");
		return 0;
	}
	else
		printf("信號量獲取成功！\n");

	struct sembuf sem_wait;
	sem_wait.sem_num = 0;
	sem_wait.sem_op = -1;
	sem_wait.sem_flg = SEM_UNDO;

	semop(sem_id, &sem_wait, 1);

	while (1)
	{
		sleep(3);
		printf("正在執行\n");
	}

	return 0;
}
```

運行結果：(文字描述)

`Semaphore_Before`先運行，創建信號量成功(一直循環)。
`Semaphore_After`後運行，獲取信號量成功，然後進程阻塞在`semop()`函數上，等待`Semaphore_Before`釋放資源。
向`Semaphore_Before`發送`SIGINT`信號，讓其釋放資源，結束進程，然後`Semaphore_After`獲得資源，
`semop()`函數不再阻塞，也開始循環。
最後向`Semphore_After`發送`SIGINT`信號，讓其刪除信號量並結束進程。

## XSI Message Queue (SystemV 消息隊列)
消息隊列是一種`IPC, Inter-Process Communication`（進程間通信）機制，屬於三類`XSI IPC`之一。
以下描述引用自`<<Unix網絡編程 卷2>>`：

消息隊列是一個**消息鏈表**，有足夠**寫權限**的線程可以向消息隊列中添加消息，
有足夠**讀權限**的線程可以從消息隊列中獲取消息。消息隊列具有**隨內核的持續性**。

消息隊列相關函數定義在`sys/msg.h`中。

### 創建/獲取消息隊列
使用`msgget()`函數創建一個新的消息隊列/獲取一個已經存在的SystemV消息隊列：

```c
int msgget(key_t key, int msgflg);
```

- `key`參數爲`ftok()`函數生成的**消息隊列**標誌。
- `msgflg`參數爲消息隊列的標誌位，多個標誌間使用`|`操作符相連。

函數執行成功返回**消息隊列描述符**（非負數），執行失敗返回`-1`並置`errno`。

`key`參數的取值可以爲宏`IPC_PRIVATE`（實際值爲`0`），此時該消息隊列爲**私有**，
用於`fork()`調用之後的**父子進程**間通信（打開的消息隊列描述符在`fork()`之後依然存在）。

`msgflg`取`IPC_CREAT`創建一個消息隊列（消息隊列已存在則忽略此標誌位），
取`IPC_CREAT | IPC_EXCL`創建一個新的消息隊列（消息隊列已存在則函數執行失敗）。
創建消息隊列時，若需要對消息隊列進行**讀寫操作**，
需要在`msgflg`參數後追加讀寫權限，如`0600`（等價於`S_IRUSR | S_IWUSR`），
但打開消息隊列時不需要設定（打開的消息隊列由創建者決定訪問權限）。

### 向消息隊列中添加消息
使用`msgsnd()`向消息隊列中添加消息：

```c
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
```

- `msqid`參數爲`msgget()`函數返回的消息隊列文件描述符。
- `msgp`參數爲指向要發送消息的指針。
- `msgsz`參數爲發送消息的大小（不包括消息類型大小）。
- `msgflg`參數爲消息標誌位，默認情況下以阻塞方式發送消息，
消息隊列已滿時`msgsnd()`函數會阻塞線程，
取值`IPC_NOWAIT`表示以非阻塞形式發送消息，
隊列已滿則直接返回錯誤。

函數執行成功返回`0`，執行失敗返回`-1`並置`errno`。

發送的消息樣例結構如下：

```c
struct mymsg
{
	long mtype; /* Message type. */
	char mtext[1]; /* Message text. */
};
```

消息結構中的首個成員需要爲`long`型，用於指示消息的**類型**（之後的`msgrcv()`函數會用到），
之後才爲消息的數據區。`msgsz`參數傳入的消息大小**不包括**消息類型的大小。
在實際開發中，消息數據不一定是簡單的字符數組，可以是**任意類型**（包括**結構體**）。

### 從消息隊列中獲取消息
使用`msgrcv()`函數從消息隊列中獲取消息：

```c
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
```

- `msqid`、`msgsz`參數作用與`msgsnd()`函數中類似。
- `msgp`參數指向用戶緩衝區，
成功收到消息後會將消息從隊列中拷貝到用戶緩衝區，之後移除隊列中被接收的消息。
- `msgtyp`參數爲目標接受消息的類型。
默認情況下，取值`0`表示接受消息隊列中的第一個消息（任意類型）；
取值爲**正數**時表示接受第一個**類型與`msgtyp`相同**的消息；
取**負值**表示接受**絕對值**小於等於`msgtyp`的消息。
- `msgflg`參數爲消息標誌位，默認以阻塞方式接受消息（若消息隊列爲空，則函數阻塞），
使用`IPC_NOWAIT`標誌表示以非阻塞形式接收消息，隊列爲空則直接返回錯誤；
使用`MSG_EXCEPT`標誌時排除接收類型等於`msgtyp`的消息；
使用`MSG_NOERROR`標誌複製消息時捨棄大於`msgsz`參數值的消息。

函數執行成功返回獲取消息的大小，失敗時返回`-1`並置`errno`。

### 消息隊列控制
使用`msgctl()`函數控制消息隊列：

```c
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

- `msqid`參數爲消息隊列描述符。
- `cmd`參數爲具體操作：
	- `IPC_STAT` 取此隊列的`msqid_ds`結構, 並將它存放在`buf`指向的結構中
	- `IPC_SET` 設置隊列的`msqid_ds`爲`buf`指向的值
	- `IPC_RMID` 從系統中**刪除**該消息隊列以及仍在該隊列中的所有數據，執行權限同上
- `buf`參數爲指向消息結構體的指針。

函數執行成功返回`0`，執行失敗返回`-1`並置`errno`。

參數`buf`的類型`msqid_ds`結構用於設置消息隊列的一些屬性，該結構的定義根據具體實現略有不同，
在`Linux x64`中的定義如下：

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

其中，定義了操作權限的結構`ipc_perm`的定義如下：

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

`msqid_ds`結構中的`msg_perm.uid`、`msg_perm.gid`、`msg_perm.mode`以及`msg_qbytes`成員可以**手動指定**。
`msgctl`函數的`IPC_SET`操作只有下列兩種進程可以執行:

1. 進程執行用戶的用戶ID等於`msg_perm.cuid`或`msg_per.uid`。
1. 具有超級用戶特權的進程。

### 實例代碼
定義消息結構頭`my_msg.h`：

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

發送消息進程：

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

	// 以非阻塞形式發送消息
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

	// 獲取進程信息
	struct msqid_ds buf;
	if (msgctl(msg_id, IPC_STAT, &buf) == -1)
		perror("msgctl");
	else
	{
		printf("Message privileges info:\n");

		//打印進程權限信息
		printf("msg_perm.uid: %u\n", buf.msg_perm.uid);
		printf("msg_perm.cuid: %u\n", buf.msg_perm.cuid);
		printf("msg_perm.gid: %u\n", buf.msg_perm.gid);
		printf("msg_perm.cgid: %u\n", buf.msg_perm.cgid);
		printf("msg_perm.mode: %o\n", buf.msg_perm.mode);
	}

	return 0;
}
```

接受消息進程：

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

運行結果：(Clang 3.7.1 && ArchLinux x64)

先執行消息發送進程：

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

之後執行消息接受進程，消息類型絕對值小於等於`300`的數據：

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



## POSIX 消息隊列
POSIX消息隊列相關函數定義在`mqueue.h`頭文件中。
使用POSIX消息隊列，編譯時需要鏈接`librt`庫。

POSIX消息隊列與SystemV消息隊列的差異：

- 讀取POSIX消息隊列，返回的總是**最高優先級**的**最早**消息。
- 讀取SytemV消息隊列，返回的是**任意指定優先級**的消息。

### 創建/獲取消息隊列
使用`mq_open()`函數創建一個新的消息隊列/獲取一個已經存在的POSIX消息隊列：

```c
mqd_t mq_open(const char *name, int oflag);
mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
```

- `name`參數爲POSIX IPC名稱。
- `oflag`參數爲標誌位，類似於`open()`調用中的`flags`參數。
	1. 可取`O_RDONLY`、`O_WRONLY`、`O_RDWR`（三選一），
	分別表示以**只讀**、**只寫**、**讀寫**的方式打開POSIX消息隊列。
	1. 可取`O_CREAT`，表示不存在消息隊列時創建，可追加`O_EXCL`標誌，
	若消息隊列已存在函數返回`EEXIST`錯誤。
	1. 可取`O_NONBLOCK`，表示以**非阻塞**的形式打開消息隊列。
- `mode`參數僅當`oflag`參數中使用了`O_CREAT`標誌時需要使用，
參數內容爲創建的消息隊列的權限，格式與文件權限相同（八進制，如`0600`）。
- `attr`參數僅當`oflag`參數中使用了`O_CREAT`標誌時需要使用，用於設置消息隊列的屬性，

函數執行成功返回POSIX消息隊列的描述符，失敗時返回`(mqd_t)-1`，並置`errno`。
類型`mqd_t`在不同的Unix實現中實際類型可能不同，在Linux中爲`int`。

### 關閉/移除消息隊列
使用`mq_close()`關閉消息隊列，使用`mq_unlink()`移除消息隊列：

```c
int mq_close(mqd_t mqdes);
int mq_unlink(const char *name);
```

- `mqdes`參數爲POSIX消息隊列描述符。
- `name`參數爲消息隊列的IPC名稱。

函數執行成功返回`0`，失敗時返回`-1`並置`errno`。

使用mq_close()關閉消息隊列後消息隊列不會被刪除，刪除消息隊列需要使用mq_unlink()。
一個進程結束後，所有該進程中打開的消息隊列都將被自動關閉。
調用mq_unlink()時若被刪除的消息隊列已被其它進程打開則不會立即刪除，
直到最後一個打開該消息隊列的進程結束或主動關閉該消息隊列時纔會被刪除。

### 設置獲取消息隊列的屬性
使用`mq_getattr()`獲取消息隊列的屬性，使用`mq_setattr()`設置消息隊列的屬性：

```c
int mq_getattr(mqd_t mqdes, struct mq_attr *attr);
int mq_setattr(mqd_t mqdes, const struct mq_attr *newattr, struct mq_attr *oldattr);
```

消息屬性結構`mq_attr`在Linux中的定義如下：

```c
struct mq_attr
{
	long mq_flags; /* Flags: 0 or O_NONBLOCK */
	long mq_maxmsg; /* Max. # of messages on queue (最大允許的消息數量) */
	long mq_msgsize; /* Max. message size (bytes) (消息長度最大大小) */
	long mq_curmsgs; /* # of messages currently in queue */
};
```

函數執行成功返回`0`，失敗時返回`-1`並置`errno`。

### 打印消息隊列的系統限制
`mq_attr`結構中的成員`mq_maxmsg`、`mq_msgsize`在不同Unix系統中擁有不同的系統上限，
可以使用`sysconf()`函數獲取：

```c
#include <unistd.h>
long sysconf(int name);
```

打印消息數目以及消息大小的系統上限：

```c
printf("MQ_OPEN_MAX: %ld\n", sysconf(_SC_MQ_OPEN_MAX));
printf("MQ_RPIO_MAX: %ld\n", sysconf(_SC_MQ_PRIO_MAX));
```

### 向消息隊列發送消息
使用`mq_send()`和`mq_timedsend()`向POSIX消息隊列中發送消息：

```c
int mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
int mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len,
		unsigned int msg_prio, const struct timespec *abs_timeout);
```

- `mqdes`參數爲消息隊列描述符。
- `msg_ptr`參數爲要加入消息隊列的數據。
- `msg_len`參數爲消息數據的大小，
該值必須**小於等於**`mq_msgsize`（消息長度最大大小），
否則函數返回`-1`並置`errno`爲`EMSGSIZE`。
- `msg_prio`參數爲消息數據的優先級，數值越大優先級越高。
- `abs_timeout`參數爲指向超時時間的指針，
mq_timedsend()函數等待超時後返回`-1`並置`errno`值爲`ETIMEDOUT`。

當消息隊列沒有設置`O_NONBLOCK`時，mq_send()函數會一直阻塞到有消息來到，
mq_timedsend()函數阻塞到超時時間等待完畢或有消息來到。
mq_send()/mq_timedsend()函數的阻塞狀態會被信號處理函數中斷，
觸發信號處理函數時，mq_send()/mq_timedsend()函數立即返回`-1`並置`errno`爲`EINTR`。

當消息隊列設置了`O_NONBLOCK`時，若消息隊列中的消息數量已經達到`mq_msgsize`（消息數目上限），
函數返回`-1`並置`errno`值爲`EAGAIN`。

### 從消息隊列獲取消息
使用`mq_receive()`和`mq_timedreceive()`從POSIX消息隊列中獲取消息：

```c
ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
ssize_t mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len,
	unsigned int *msg_prio, const struct timespec *abs_timeout);
```

- `mqdes`參數爲消息隊列描述符。
- `msg_ptr`參數爲要加入消息隊列的數據。
- `msg_len`參數爲消息數據的大小，
該值必須**大於等於**`mq_msgsize`（消息長度最大大小），否則函數返回`-1`並置`errno`爲`EMSGSIZE`。
- `msg_prio`參數爲指向消息優先級數據的指針，在隊列中有多個消息時，首先獲取優先級高的消息。
- `abs_timeout`參數爲指向超時時間的指針，
mq_timedreceive()函數等待超時後返回`-1`並置`errno`值爲`ETIMEDOUT`。

當消息隊列沒有設置`O_NONBLOCK`時，mq_receive()函數會一直阻塞到消息能被接收，
mq_timdreceive()函數阻塞到超時時間等待完畢或消息能被接收。
mq_receive()/mq_timedreceive()函數的阻塞狀態會被信號處理函數中斷，觸發信號處理函數時，
mq_receive()/mq_timedreceive()函數立即返回`-1`並置`errno`爲`EINTR`。

當消息隊列設置了`O_NONBLOCK`時，若消息隊列中的消息數量爲`0`，函數返回`-1`並置`errno`值爲`EAGAIN`。

### 消息隊列通知
使用`mq_notify()`爲消息隊列綁定或刪除異步通知：

```c
int mq_notify(mqd_t mqdes, const struct sigevent *sevp);
```

- `mqdes`參數爲消息隊列描述符。
- `sevp`參數爲指向具體的信號通知內容的指針，若取`NULL`，則清除原有的通知註冊。

`sigevent`結構的定義如下：

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

1. 消息隊列阻塞的優先級比信號通知更高，只有指定消息隊列的所有描述符都以`O_NONBLOCK`標誌打開時，信號纔會發出。
1. 任何時刻只能有一個進程被註冊到指定的消息隊列中。
1. 信號成功發送之後，註冊即被取消，在此發出信號需要重新註冊。

### 實例代碼
定義消息結構頭`posix_mq.h`：

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

發送消息進程：

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

	attr.mq_flags = O_NONBLOCK; // 設置消息隊列非阻塞

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

	// 進程結束。消息隊列描述符自動關閉
	mq_close(mqdes);

	return 0;
}
```

接收消息進程：

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

	attr.mq_flags = O_NONBLOCK; // 設置消息隊列非阻塞

	if (mq_setattr(mqdes, &attr, NULL) == -1)
		perror("mq_setattr");

	unsigned prio;

	// 循環取出隊列中所有消息
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

運行結果：(Clang 3.7.1 && ArchLinux x64)

先執行消息發送進程：

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

之後運行消息接受進程，type（優先級）高的消息先被接收：

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



# IO多路複用（POSIX）
在Unix中，POSIX定義了一系列IO多路複用機制，如`select()`、`pselect()`、`poll()`等調用。
Linux和BSD還分別提供了增強的IO複用機制，在Linux中爲`epoll`，在BSD中爲`kqueue`。

## select()
在Unix環境下，`select()`是常用的IO多路複用機制之一，函數定義在`sys/select.h`中。
select()函數定義示例：

```c
int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout);
```

- `nfds`參數爲需要監視的文件描述符的最大值加`1`。
- `readfds`參數爲要監視的可讀檢測文件描述符集合。
- `writefds`參數爲要監視的可寫檢測文件描述符集合。
- `errorfds`參數爲要監視的錯誤檢測文件描述符集合。
- `timeout`參數爲超時等待的時間，可以精確到**微秒**，
取`NULL`時爲select()爲阻塞函數，超時爲`0`時立即返回(非阻塞)。

結構`timeval`的定義爲：

```c
struct timeval {
	time_t tv_sec;			/* seconds */
	suseconds_t tv_usec;	/* microseconds */
};
```

描述符集合`fd_set`可以使用下列宏進行操作：

```c
void FD_ZERO(fd_set *fdset);
void FD_SET(fd, fd_set *fdset);
void FD_CLR(fd, fd_set *fdset);
int FD_ISSET(fd, fd_set *fdset);
```

- 使用`FD_ZERO`初始化描述符集合。
- 使用`FD_SET`向描述符集合中添加描述符。
- 使用`FD_CLR`從描述符集合中移除描述符。
- 使用`FD_ISSET`檢測描述符，若`fd`參數在描述符集合參數`fdset`中，返回非零值，否則返回`0`。

函數執行成功返回變化的描述符數量，監視的描述符無變化則返回`0`，調用失敗返回`-1`。

基本的select()函數代碼框架爲（以檢測文件描述符可讀爲例）：

```c
int fd[fdcount];
fd_set readset;
struct timeval timeout;

while(1)
{
	// 初始化並設置描述符集合，每次調用select()前都需要類似操作
	FD_ZERO(&readset);
	FD_SET(fd[0], &readset);
	... // 設置需要監視的描述符

	// timeval結構體在每次select()調用會被修改，需要重複設定超時結構體
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
			// 使用宏FD_ISSET判斷文件描述符是否發生變化
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

使用select()的一些注意事項：

- select()處於阻塞狀態時會被信號中斷（當select()所處線程是信號處理線程時）。
- 每次調用select()前都需要重設描述符集合（執行`FD_ZERO`和`FD_SET`宏）。
- `timeval`結構體會在select()運行時被修改，因此，在需要設置超時時間的情況下，
循環中每次調用select()之前都需要重新設置`timeval`結構體。
- 對於**普通文件**描述符，無論**讀、寫、異常狀態**，都是**始終準備好**的，
因此在監控的描述符中如果存在**普通文件**，無論`timeout`參數取何值，select()都將**立即返回**。

## pselect()
`pselect()`函數由**POSIX**定義，是`select()`的完善版本，在早期的Unix中並不存在。
pselect()監聽描述符的功能以及使用方式與select()相同。
pselect()在select()基礎上添加了等待期間**阻塞**信號的功能。

pselect()函數定義示例：

```c
int pselect(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, const struct timespec *restrict timeout, const sigset_t *restrict sigmask);
```

- 前**4個**參數與select()中含義完全相同。
- `sigmask`參數爲需要屏蔽信號的集合。
- `timeout`參數爲超時等待的時間，類型爲`timespec`，
精確到**納秒**，與select()函數中精確到毫秒的`timeval`不同。

信號集合參數`sigmask`使用前需要兩個步驟：

1. 首先使用`sigemptyset()`函數清空信號集合：

	```c
	int sigemptyset(sigset_t *set);
	```

1. 之後使用`sigaddset()`向清空後的信號集合中添加信號：

	```c
	int sigaddset(sigset_t *set, int signo);
	```

信號集合只需要設置一次，就可以在之後的pselect()中一直使用。

- 在pselect()處於**阻塞**狀態時，會暫時屏蔽信號集中的信號，
在pselect()阻塞期間若發出了被屏蔽的信號，則信號處理函數會在pselect()結束時觸發。
- 在pselect()**阻塞**期間多次發出了信號，
在pselect()結束時**同類信號**只觸發信號處理函數**一次**，不會多次觸發。
- 在pselect()**阻塞**期間，
發出的不同種類信號都會在pselect()結束時觸發(即使信號處理函數是**同一個**)，
但**每類信號**只會觸發**一次**信號處理函數。

示例：

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
	// 初始化時間結構體timespec，需要注意的是tv_nsec成員爲納秒數
	struct timespec time;
	time.tv_sec = 5;
	time.tv_nsec = 0;

	signal(SIGINT, deal_signal);
	signal(SIGQUIT, deal_signal);

	// sigmask參數設置一次即可，不需要每次調用pselect前都設置
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	// pselect與select的不同之處在於設置sigmask防止超時等待時被信號打斷
	// 信號會在pselect等待後觸發
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

在上述代碼中，`timespec`結構設置了**5秒**的超時等待時間，
屏蔽信號集中加入了`SIGINT`和`SIGQUIT`兩個信號，
在pselect()啓動後的超時等待時間中，發送這兩個信號並不會立即得到響應，
而是在**5秒**的超時時間過後，`deal_signal`纔會觸發。
在等待期間，無論發送多少次`SIGINT`和`SIGQUIT`信號，
`SIGINT`和`SIGQUIT`的信號處理函數只會**分別觸發**一次。

在**多線程**環境下，只有pselect()所處的線程是信號處理線程時，
pselect()才能起到阻塞信號的效果，在其它線程中，即使使用pselect()並設置屏蔽信號，
信號處理函數依然會**立即**觸發。

示例：

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
	// 初始化時間結構體timespec，需要注意的是tv_nsec成員爲納秒數
	struct timespec time;
	time.tv_sec = 5;
	time.tv_nsec = 0;

	signal(SIGINT, deal_signal);
	signal(SIGQUIT, deal_signal);

	// sigmask參數設置一次即可，不需要每次調用pselect前都設置
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	// 在非主線程中的pselect不再具有屏蔽信號的作用
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

在上述代碼中，`pselect()`代碼塊被轉移到了主線程之外，儘管依舊設置了`sigmask`，
但由於信號由**主線程**而非`pselect()`所處線程處理，因而阻塞信號沒有在`pselect()`等待期間阻塞，
發送`SIGINT`和`SIGQUIT`等信號會**立即觸發**信號處理函數。



# IO多路複用（epoll）
`epoll`是`Linux`環境下**獨有**的IO多路複用機制，在`Linux Kernel 2.6`之後被引入。
傳統的select()在描述符變化事件產生時需要使用`FD_ISSET`宏遍歷測試所有描述符，
因此隨着監聽描述符數量的增加性能會出現線性下降，而使用epoll則能直接獲取到變化的描述符。

epoll相關API定義在`sys/epoll.h`頭文件中。

## epoll_create()
使用`epoll_create()`初始化一個epoll描述符：

```c
int epoll_create(int size);
```

- `size`參數爲支持的最大句柄數，從`Linux Kernel 2.6.8`之後，這個參數不再被要求。

函數執行成功返回epoll描述符。執行失敗返回`-1`，並置errno。

## epoll_ctl()
使用`epoll_ctl()`添加、修改或刪除監聽描述符：

```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

- `epfd`參數爲`epoll_create()`得到的epoll描述符。
- `op`參數爲要執行的操作，可取宏`EPOLL_CTL_ADD`（添加監聽描述符）、
`EPOLL_CTL_MOD`（修改描述符操作）、`EPOLL_CTL_DEL`（刪除監聽描述符）。
- `fd`參數爲被操作的描述符。
- `event`參數爲描述符`fd`對應的事件，不能取值`NULL`。

函數執行成功返回`0`，執行失敗返回`-1`並置`errno`。

- `epoll_event` 結構

	`event`參數的類型`epoll_event`結構體定義如下：

	```c
	struct epoll_event {
		uint32_t events;		/* Epoll events */
		epoll_data_t data;		/* User data variable */
	};
	```

	其中，`events`成員爲文件描述符觸發的條件，是一組標誌，使用邏輯或操作符`|`相連，常用的有：

	- `EPOLLIN` 描述符**可讀**
	- `EPOLLOUT` 描述符**可寫**
	- `EPOLLPRI` 描述符有緊急的數據可讀
	- `EPOLLET` `Edge Triggered`(ET，邊緣觸發)模式，不設置此標誌時默認爲`Level Triggered`(LT，水平觸發)
	- `EPOLLONESHOT` 只監聽**一次**事件

- `epoll_data_t` 類型

	`epoll_event`結構體成員`data`的類型`epoll_data_t`聯合體定義如下：

	```c
	typedef union epoll_data {
		void *ptr;
		int fd;
		uint32_t u32;
		uint64_t u64;
	} epoll_data_t;
	```

	`data`用來存放事件的對應數據。

## epoll_wait()
完整監聽描述符的設置之後，使用`epoll_wait()`函數等待事件觸發：

```c
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

- `epfd`參數爲`epoll_create()`得到的epoll描述符。
- `events`參數爲產生的事件集合，不能取`NULL`，函數會將產生的事件數據寫入該地址中。
- `maxevents`參數爲最大事件數目，這個值不大於監聽的描述符的數量。
- `timeout`參數爲超時時間，取`0`時立即返回(非阻塞)，取`-1`時永久阻塞直到事件產生或被信號中斷。

函數執行成功返回變化的描述符數量，返回值爲`0`則等待超時。執行失敗返回`-1`並置`errno`。

## 注意事項
- `epoll_create()`創建的epoll描述符需要使用`close()`關閉。
- epoll**不能**監聽普通文件描述符，
對於`read()`、`write()`調用而言，普通文件是**始終準備好**(always ready)的。
在`epoll_ctl()`函數中嘗試添加一個普通文件描述符則會得到`Operation not permitted`錯誤。
- `epoll_create()`中的`size`參數雖然是被忽略的，但不要取`0`和**負值**，會得到`Bad file desriptor`錯誤。

## LT/ET
epoll擁有兩種工作模式，分別爲`Level Triggered`（LT，水平觸發）和`Edge Triggered`（ET，邊緣觸發）模式。

- `LT`模式爲epoll的默認工作模式，在該模式下，只要有數據可讀/寫，使用`epoll_wait()`都會返回。
- `ET`模式只有描述符狀態變化（從不可讀/寫變爲可讀/寫）時纔會另`epoll_wait()`返回，相比之下，ET模式更爲高效。

LT模式下，由於只要有數據讀寫就會觸發事件，因此**不必**在一次epoll循環中嘗試讀盡所有的數據，
有數據未讀會繼續觸發觸發事件，在下次觸發的事件中讀盡數據即可。
LT模式下可以使用阻塞式IO也可以使用非阻塞IO。

LT模式下基本的代碼框架爲：

```c
int epfd = epoll_create(size);

struct epoll_event event;
event.events = ... /* events type */;
event.data = ... /* data */;

if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event) == -1)
	perror("epoll_ctl()出錯");
/*
	添加其它需要監聽的描述符...
*/

while (1)
{
	int count = 0, timeout = /* timeout */, maxevents = /* listen_fd_count */;
	struct epoll_event events[maxevents];
	switch (count = epoll_wait(epfd, events, maxevents, timeout))
	{
	case -1:
		perror("epoll_wait()出錯");
		break;
	case 0:
		printf("epoll_wait()超時");
		break;
	default:
		// epoll相比select的高效之處就是能直接處理變化的描述符無需遍歷整個監聽集合
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

ET模式下，只有描述符在可讀寫狀態發生改變時纔會觸發事件，
因此，在ET模式下，必須**一次讀盡**所有的數據，否則會造成數據丟失。
ET模式下，IO需要放在一個無限循環中進行，直到數據全部讀出，IO操作置`ernno`爲`EAGAIN`才終止。

相比LT模式，ET模式觸發epoll次數減少，效率更高，但ET模式下必須使用**非阻塞IO**。

ET模式下的基本代碼框架爲：

```c
int epfd = epoll_create(size);

struct epoll_event event;
event.events = EPOLLET | ... /* events type */; // 默認爲LT模式，需要顯式使用EPOLLET標誌才能設置爲ET模式
event.data = ... /* data */;

if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event) == -1)
	perror("epoll_ctl()出錯");
/*
	添加其它需要監聽的描述符...
*/

while (1)
{
	int count = 0, timeout = /* timeout */, maxevents = /* listen_fd_count */;
	struct epoll_event events[maxevents];
	switch (count = epoll_wait(epfd, events, maxevents, timeout))
	{
	case -1:
		perror("epoll_wait()出錯");
		break;
	case 0:
		printf("epoll_wait()超時");
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
