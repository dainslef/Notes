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

#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>		//inet_addr()函数

int sock_fd = 0;

void* get_response(void* arg)
{
	char message[10] = {0};
	if (recv(sock_fd, message, 10, 0) == -1)
		perror("获取客户端响应失败：");
	else
		if (!strcmp(message, "close"))
		{
			printf("\n收到来自服务端的关闭指令，关闭客户端！\n");
			close(sock_fd);
			_exit(0);
		}
}

int main(int argc, char **argv)
{
	int user_id = 0;
	pthread_t thread_fd = 0;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = 9999;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");		//向本机发送数据
	
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sock_fd == -1)
		perror("初始化Socket失败：\n");
		
	if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		perror("连接socket失败：\n");
		
	recv(sock_fd, &user_id, 10, 0);
	printf("登录为用户：[%d]\n", user_id);
	pthread_create(&thread_fd, NULL, get_response, NULL);		//开辟一个线程用于接收服务端的关闭通知
	
	int num = 0;
	char str[50];
	memset(str, 0, 50);			//将字符串置空
	
	while (1)			//使用循环连续发送消息 
	{
		printf("请输入要发送的内容： ");
		scanf("%s", str);
		printf("发送第%d次。\n", ++num);
		if (send(sock_fd, str, 50, 0) == -1)
			perror("发送失败：\n");
		else if (!strcmp(str, "close"))
		{
			printf("关闭socket发送！\n");
			break;
		}
	}
	
	close(sock_fd);
	return 0;
}
