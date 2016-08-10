/*
 * 代码完成时间： 2015-4-11 03：06 AM
 * Unix Socket通信，采用TCP方式
 * 客户端程序
 * 用户登录后会显示自己的ID，用户向服务端发送消息会显示在服务端。
 * 如果用户发送消息"close"，则服务端以及与该服务端相连的所有客户端都会关闭
 */

/**
 *
 * @author dainslef
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>					//inet_addr()函数

#define MSG_SIZE 50						//定义单次发送字符串最大长度

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
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");		//向本机发送数据

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		perror("初始化socket失败");
		return 0;
	}

	if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("连接socket失败");
		close(sock_fd);
		return 0;
	}

	int user_id = 0;
	recv(sock_fd, &user_id, 4, 0);
	printf("登录为用户：[%d]\n", user_id);

	pthread_t thread_fd;
	pthread_create(&thread_fd, NULL, get_response, NULL);		//开辟一个线程用于接收服务端的关闭通知

	int count = 0;
	while (1)			//使用循环连续发送消息
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
