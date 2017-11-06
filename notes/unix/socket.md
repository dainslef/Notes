<!-- TOC -->

- [*Socket* 通信](#socket-通信)
	- [*Socket* 函数](#socket-函数)
	- [*Scoket* 通信主要步骤](#scoket-通信主要步骤)
		- [服务端](#服务端)
		- [客户端](#客户端)
	- [*socket()* 函数](#socket-函数)
	- [*bind()* 函数](#bind-函数)
	- [*connect()* 函数](#connect-函数)
	- [*listen()* 函数](#listen-函数)
	- [*accpet()* 函数](#accpet-函数)
	- [*send()* 函数](#send-函数)
	- [*recv()* 函数](#recv-函数)
	- [注意事项](#注意事项)
	- [实例代码(UDP)](#实例代码udp)
		- [客户端](#客户端-1)
		- [服务端](#服务端-1)
	- [实例代码(TCP)](#实例代码tcp)
		- [客户端](#客户端-2)
		- [服务端(使用多线程)](#服务端使用多线程)
		- [服务端(使用select()轮询)](#服务端使用select轮询)

<!-- /TOC -->



# *Socket* 通信
`socket`源于**BSD Unix**，是现今网络通信的**事实标准**。



## *Socket* 函数
包括`socket()`、`bind()`、`listen()`、`connect()`、`accpet()`、`recv()`、`send()`等函数。

相关函数的定义在`/usr/include/sys/socket.h`头文件中。



## *Scoket* 通信主要步骤

### 服务端
1. `socket()`初始化套接字描述符。
1. `bind()`绑定端口和IP地址。
1. `listen()`监听端口并设置最大同时连接数，`UDP`模式下**无需**此步骤。
1. `accept()`阻塞，直到接受客户端的连接请求返回通信描述符，`UDP`模式下**无需**此步骤。
1. `recv()/send()`使用通信描述符与客户端进行交互。
1. `close()`关闭打开的描述符。

### 客户端
1. `socket()`初始化套接字描述符。
1. `bind()`绑定端口和IP地址。(可选)
1. `connect()`连接指定地址和端口的服务端，`TCP`模式下会进行三次握手，`UDP`模式下不会。
1. `recv()/send()`使用通信描述符与服务端进行交互。
1. `close()`关闭打开的描述符。



## *socket()* 函数
用于初始化一个**socket**，函数定义为：

```c
int socket(int domain, int type, int protocol);
```

- `domain`参数表示使用的**域**，使用`TCP/IP`协议应取值`AF_INET`。
- `type`参数表示连接的类型，可取值`SOCK_STREAM`或`SOCK_DGRAM`，前者代表`TCP`可靠连接，后者代表`UDP`连接。
- `protocol`参数表示使用的协议，一般取`0`。

`socket()`函数为**非阻塞**函数。  
成功时函数返回**套接字描述符**，失败时返回`-1`，并置`errno`。



## *bind()* 函数
`bind()`函数将**套接字描述符**与指定的**端口**、**IP地址**绑定。  
函数定义为：

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

- `sockfd`参数为`socket()`函数返回的套接字描述符。
- `addrlen`参数用于设置`addr`结构体中所能容纳的**最大字节数**。
- `addr`参数表示**IP地址**，传入结构体`sockaddr`的地址。

`bind()`函数通常用于服务端程序，客户端使用服务端`bind()`绑定的IP地址和端口号来连接服务端。  
`bind()`函数亦可用于客户端程序，客户端向服务端发送数据包时默认情况下会由操作系统随机选择空闲端口发送，使用`bind()`函数可指定客户端进程从特定端口发送数据包。

`bind()`函数为非阻塞函数。  
函数成功返回`0`，失败时返回`-1`，并置`errno`。

结构体`sockaddr`定义如下所示：

```c
struct sockaddr {
	sa_family_t sa_family; //协议簇
	char sa_data[14]; //地址 + 端口号
}
```

通常情况下，并不直接创建`sockaddr`结构体，而是将IP地址和端口号信息写入与`sockaddr`大小**相同**的`sockaddr_in`这个结构体中，然后在将其强制类型转换为`sockaddr`类型。

`sockaddr_in`结构体定义在`<netinet/in.h>`中，定义如下：

```c
struct sockaddr_in {
	sa_family_t sin_family; /* 协议族，address family: AF_INET */
	in_port_t sin_port; /* 端口号，port in network byte order */
	struct in_addr sin_addr; /* IP地址，internet address */
};
```

结构成员`sin_port`赋值端口号时需要使用`<arpa/inet.h>`中定义的`htons()`函数进行转换：

- `sin_port`成员接收的端口号应为`网络字节顺序`(**大尾顺序**，`big-endian`，地址的低位存储值的高位
)。
- 在`x86/x64`体系的计算机上，存储顺序为**小尾顺序**(`little-endian`，地址的低位存储值的低位
)。
- 直接将端口号赋值到`sin_port`上并不会直接产生错误，当客户端/服务端都没有使用`htons()`函数进行端口转换时，通信能够正常执行，但实际通信使用的端口并不是赋值的数值。
- 当端口号没有使用`htons()`函数转换时，使用其它编程语言的以正确的端口号进行访问时会出现连接被拒绝的情况，因为实际的通信端口并不是传入的数值。

`sockaddr_in`成员结构体`in_addr`的定义为：

```c
typedef uint32_t in_addr_t;
struct in_addr {
	in_addr_t s_addr;
};
```

将IP地址赋值给`in_addr`结构体的`s_addr`成员，需要通过定义在头文件`<arpa/inet.h>`中的`inet_addr()`函数进行转换。

初始化`sockaddr_in`结构的样板代码如下所示：

```cpp
// C
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = htons(端口号);
addr.sin_addr.s_addr = inet_addr("IP地址");

// C99
struct sockaddr_in addr =
{
	.sin_family = AF_INET,
	.sin_port = htons(端口号),
	.sin_addr.s_addr = inet_addr("IP地址")
};

// C++11
sockaddr_in addr { AF_INET, 端口号, { inet_addr("IP地址") }, { 0 } };
```



## *connect()* 函数
`connect()`函数用于**客户端**程序，让客户端程序与要与之通信的服务器建立连接，函数定义为：

```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

- `sockfd`参数为`socket()`函数返回的套接字描述符。
- `addr`为需要连接的服务器的地址。

函数执行成功返回`0`，执行失败返回`-1`并置`errno`。

`connect()`为**阻塞**函数。  
若连接未立即建立且`socket`未设置`O_NONBLOCK`标识时，`connect()`函数会阻塞等待一段时间。  
超过等待时间后，`connect()`函数会终止并置`errno`。



## *listen()* 函数
`listen()`函数用于**服务端**程序，当创建了套接字描述符并使用`bind()`函数将其与端口关联起来之后，服务器端需要调用`listen()`开始监听指定端口的客户端连接，函数定义为：

```c
int listen(int sockfd, int backlog);
```

- `sockfd`参数为`socket()`函数返回的套接字描述符。
- `backlog`参数用于设置接入队列的大小(可同时并发接受的连接数)。

`listen()`函数为**非阻塞**函数。  
函数执行成功返回`0`，执行失败返回`-1`并置`errno`。



## *accpet()* 函数
当有新客户端连接到服务端时，它们会排入队列，直到服务端准备处理好它们为止，`accept()`会返回一个新的套接字描述符，新的套接字描述符用来进行通信，函数定义为：

```c
int accpet(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

- `sockfd`参数为`socket()`函数返回的套接字描述符。
- `addr`参数为接收客户的地址(如果对客户的地址不感兴趣，该参数可填**NULL**)。
- `addrlen`参数为接收客户地址的长度(对客户地址不感兴趣则同样可以填**NULL**)。

函数执行成功返回值为**连接套接字**，通过该套接字描述符进行**通信**(连接套接字与`socket()`函数生成的监听套接字并不相同！服务端使用`send()`或是`recv()`等函数发送消息时应该使用连接套接字！)。

`accept()`为**阻塞**函数。  
若`socket`未设置`O_NONBLOCK`标识，`accept()`函数会**阻塞线程**，直到有新的客户加入。  
若`socket`设置了`O_NONBLOCK`标识，`accept()`会立即返回，无新客户加入时执行失败，置`error`为`EAGAIN/EWOULDBLOCK`。



## *send()* 函数
当客户端与服务端成功建立了连接，就可以相互传送数据，发送数据使用`send()`函数，函数定义为：

```c
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
```

`msghdr`结构体定义为：

```c
msghdr {
	void *msg_name;				/* optional address */
	socklen_t msg_namelen;		/* size of address */
	struct iovec *msg_iov;		/* scatter/gather array */
	size_t msg_iovlen;			/* # elements in msg_iov */
	void *msg_control;			/* ancillary data, see below */
	size_t msg_controllen;		/* ancillary data buffer len */
	int msg_flags;				/* flags (unused) */
};
```

其中，成员结构体`iovec`的定义为：

```c
struct iovec {					/* Scatter/gather array items */
	void  *iov_base;			/* Starting address */
	size_t iov_len;				/* Number of bytes to transfer */
};
```

- 对于**UDP**协议而言`sockfd`参数是`socket()`函数返回的套接字描述符。
- 对于**TCP**协议而言`sockfd`参数是`accept()`函数返回的连接套接字描述符。
- `buf`参数是接收数据内存`buffer`地址指针。
- `len`参数指明`buffer`的大小，单位**字节**。
- `flag`参数为标识位，用于开启一些特性。

成功发送数据返回**发送的字节数**，失败时返回**-1**，并置**ernno**。  
当缓冲区空间不足时，若未设置`O_NONBLOCK`标识，则该函数阻塞直至缓冲区可用。

可以使用系统调用`write()`来向套接字描述符中写入数据，作用与使用`send()`函数发送数据相同。



## *recv()* 函数
`recv()`函数用于接收数据，函数定义为：

```c
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
```

参数的定义类似与`send()`函数。

可以使用系统调用`read()`读取套接字描述符中的数据，作用与使用`recv()`函数接收数据相同。



## 注意事项
- `accept()`、`recv()`、`send()`函数默认**阻塞**(阻塞当前线程)，可以通过设置标志位使其变为非阻塞。
- **UDP**协议是**无连接**的，因此服务端不需要使用`listen()`和`accpet()`函数，也**不需要**使用多线程来接收多个客户请求。
- 等号赋值`=`的优先级比`==`符号要低，因此不要直接将`socket()`、`accpet()`、`send()`等socket相关函数的赋值和比较操作同时进行(不要写成 `if (client_fd = accpet(sockfd, NULL, NULL) == -1)`这样的)，应该注意**运算优先级**(需要给赋值操作加上小括号)。
- 服务端使用`accept()`函数之后会产生新的连接套接字描述符，所有的服务端的`send()`、`recv()`应该使用该连接套接字描述符。
- 需要同时多个用户保持通信连接则需要循环`accpet()`函数，只运行一次`accept()`函数则服务端只会与第一个用户通信，后面的用户都会被忽略。
- `recv()`函数的参数中注意正确填写收到字符串的大小(不要写成`recv(client_fd, str, strlen(str), 0)`这样的)，不能使用`strlen(str)`函数计算接收到字符数组大小，因为`recv()`函数结束后才会改变接收字符数组`str`中的内容。
- 在`Unix`系统中，一切皆文件，因而使用`send()/recv()`发送/接收数据的场景也可以直接使用系统调用`write()/read()`读写套接字描述符，效果类似。



## 实例代码(UDP)
**UDP**协议是**无连接**的，因此服务端**不需要**使用`listen()`和`accpet()`函数，直接使用`socket()`函数生成套接字描述符，然后使用`bind()`函数将套接字描述符绑定一个空闲的端口，然后就可以使用`recv()`函数来接受数据了。

由于**UDP**是无链接的，**不需要**针对不同用户生成不同的通信套接字，**不需要**使用多线程或是`select()`函数来处理不同用户的数据。

需要注意的是，即使是**UDP**连接，客户端依然需要使用`connect()`函数来确定发送数据的地址(服务端地址、端口)，但UDP协议的`connect()`函数**不进行**三次握手操作。

### 客户端

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
	char* str = NULL;
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	if (argc != 2)
	{
		printf("指令参数错误！\n");
		_exit(0);
	}
	else
		str = argv[1];

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("发送的内容：%s\n", str);

	if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		perror("连接失败");
	else
	{
		if (send(sock_fd, str, 50, 0) == -1)
			perror("发送消息失败");
	}

	close(sock_fd);
	return 0;
}
```

### 服务端

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MSG_SIZE 50 //定义单次发送字符串最大长度

int main(void)
{
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("绑定端口失败");
		close(sock_fd);
		return -1;
	}

	char message[MSG_SIZE];
	while (1)
	{
		memset(message, 0, MSG_SIZE);
		if (recv(sock_fd, message, MSG_SIZE, 0) == -1)
		{
			perror("接收失败");
			close(sock_fd);
			return -1;
		}
		else
			printf("接收到消息：%s\n", message);
	}

	close(sock_fd);
	return 0;
}
```



## 实例代码(TCP)
**TCP**协议要求拥有稳定的连接，因此需要使用`listen()`函数来监听套接字端口并设置最大并发数，用`accept()`函数来为每个请求用户的用户生成不同的连接套接字。

同时并行处理多个用户的请求需要使用**多线程**机制或是`select()`轮询。

###客户端

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //inet_addr()函数

#define MSG_SIZE 50 //定义单次发送字符串最大长度

int sock_fd = 0;

//线程函数用于处理接收的消息
void* get_response(void* arg)
{
	char message[MSG_SIZE];
	memset(message, 0, MSG_SIZE);

	if (recv(sock_fd, message, MSG_SIZE, 0) == -1)
		perror("接收消息失败");
	else
		if (!strcmp(message, "close"))
		{
			printf("\n收到来自服务端的关闭指令，关闭客户端！\n");
			close(sock_fd);
			_exit(0);
		}

	return NULL;
}

int main(int argc, char **argv)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //向本机发送数据

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (sock_fd == -1)
	{
		perror("初始化socket失败");
		return 0;
	}

	if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("连接socket失败");
		return 0;
	}

	int user_id = 0;
	recv(sock_fd, &user_id, 4, 0);
	printf("登录为用户：[%d]\n", user_id);

	pthread_t thread_fd;
	pthread_create(&thread_fd, NULL, get_response, NULL); //开辟一个线程用于接收服务端的关闭通知

	int count = 0;
	while (1) //使用循环连续发送消息
	{
		char message[MSG_SIZE];
		memset(message, 0, MSG_SIZE);

		printf("请输入要发送的内容： ");
		fgets(message, MSG_SIZE, stdin);

		char* str = message;
		while (*str++) if (*str == '\n') *str = 0;

		printf("发送第%d次。\n", ++count);

		if (send(sock_fd, message, MSG_SIZE, 0) == -1)
			perror("发送消息失败");
	}

	return 0;
}
```

### 服务端(使用多线程)

```c
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define USER_MAX 10 //定义最大用户数量
#define MSG_SIZE 50 //定义单次发送字符串最大长度

pthread_t thread_fd;
int sock_fd = 0;
int msg_count = 0; //记录接收数据次数
int user_count = 0; //用户数量计数
int client_fd[USER_MAX]; //用一个数组来保存所有用户的连接socket描述符

void* get_accept(void* arg)
{
	if ((client_fd[user_count] = accept(sock_fd, NULL, NULL)) == -1)
	{
		perror("接收请求失败");
		return NULL; //BSD系统上client关闭socket会产生新的请求，创建失败直接退出
	}
	else //每次成功接受新请求就新开启一个线程，让新线程来阻塞继续等待请求
		pthread_create(&thread_fd, NULL, get_accept, NULL);

	int user_id = user_count++;			//定义用户id
	printf("有用户加入socket！当前用户数量为：%d人。\n", user_count);
	send(client_fd[user_id], &user_id, sizeof(user_id), 0);

	while (1)
	{
		char message[MSG_SIZE];
		memset(message, 0, MSG_SIZE);

		if (recv(client_fd[user_id], message, MSG_SIZE, 0) == -1)
			perror("接收消息失败");
		else
		{
			if (!strcmp(message, "close"))
			{
				printf("收到关闭命令！\n关闭socket端口监听！\n");
				for (int i = 0; i < user_count; i++) //收到关闭信息之后向所有客户端发送关闭消息
					send(client_fd[i], message, MSG_SIZE, 0);
				break;
			}
			else if (!strcmp(message, "")) //应对用户关闭socket时可能产生的空消息
				break;
			printf("第%d次接收，接收到来自用户[%d]的消息：%s\n", ++msg_count, user_id, message);
		}
	}

	close(client_fd[user_id]);
	return NULL;
}

int main(void)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = INADDR_ANY; //代表接收任意地址的数据
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("绑定端口失败");
		return 0;
	}

	if (listen(sock_fd, USER_MAX) == -1)
	{
		perror("监听端口失败");
		return 0;
	}

	get_accept(NULL);

	close(sock_fd);
	return 0;
}
```

### 服务端(使用select()轮询)

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

#define USER_MAX 10 //定义最大用户数量
#define MSG_SIZE 50 //定义单次发送字符串最大长度

int sock_fd = 0;
int max_fd = 0; //设置最大描述符大小
int user_count = 0; //用户数量计数
int client_fd[USER_MAX]; //用一个数组来保存所有用户的连接socket描述符

void* get_accept(void* arg)
{
	while (1)
	{
		if ((client_fd[user_count] = accept(sock_fd, NULL, NULL)) == -1)
			break; //BSD系列在关闭socket时可能会产生新的请求
		else
		{
			//最大文件描述符值为监听文件描述符集合中的最大值加1
			if (client_fd[user_count] >= max_fd)
				max_fd = client_fd[user_count] + 1;

			write(client_fd[user_count], &user_count, 4);
			printf("有用户加入socket！当前用户数量为：%d人。\n", ++user_count);
		}
	}

	return NULL;
}

int main(void)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	addr.sin_addr.s_addr = INADDR_ANY; //代表接收任意地址的数据
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("绑定端口失败");
		return 0;
	}

	if (listen(sock_fd, USER_MAX) == -1)
	{
		perror("监听端口失败");
		return 0;
	}

	//记录接收数据次数
	int msg_count = 0;
	//描述符集合
	fd_set read_set;

	//创建独立线程来接收请求
	pthread_t thread_fd = 0;
	pthread_create(&thread_fd, NULL, get_accept, NULL);

	while (1)
	{
		//select()调用每次运行前都需要置空，之后重设需要监听的文件描述符
		FD_ZERO(&read_set);
		for (int i = 0; i < user_count; i++)
			FD_SET(client_fd[i], &read_set);

		//设置select()超时时间，全部为0则不阻塞
		struct timeval time;
		time.tv_sec = 2;
		time.tv_usec = 0;

		//select()返回变动的文件描述符数目
		if (select(max_fd, &read_set, NULL, NULL, &time) > 0)
			for (int i = 0; i < user_count; i++)
				if (FD_ISSET(client_fd[i], &read_set))
				{
					char message[MSG_SIZE];
					memset(message, 0, MSG_SIZE);

					if (read(client_fd[i], message, MSG_SIZE) == -1)
						perror("接收消息失败");
					else
					{
						if (!strcmp(message, ""))
							continue;
						if (!strcmp(message, "close"))
						{
							printf("收到关闭命令！\n关闭socket端口监听！\n");
							for (int i = 0; i < user_count; i++)		//收到关闭信息之后向所有客户端发送关闭消息
								write(client_fd[i], message, MSG_SIZE);
							goto END;
						}
						printf("第%d次接收，接收到来自用户[%d]的消息：%s\n", ++msg_count, i, message);
					}
				}
	}

END:
	for (int i = 0; i < user_count; i++)
		close(client_fd[i]);
	close(sock_fd);
	return 0;
}
```
