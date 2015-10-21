/*
 * 代码完成时间： 2015-4-11 03：07 AM
 * Unix Socket通信，采用TCP方式
 * 服务端程序
 * 主要功能：用多线程实现同时接受多个用户请求，为每一个用户开辟一个线程。
 * 每登录一个用户，系统会给予提示。
 * 每一个用发送的消息都能够显示在服务端并注明发送者。
 * 当用户发送close消息时关闭服务端和其它所有与服务端相连的客户端。
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

#define USER_MAX 10			//定义最大用户数量

pthread_t thread_fd = 0;
int sock_fd = 0;
int num = 0;				//记录接收数据次数	
int user_count = 0;			//用户数量计数
int client_fd[USER_MAX] = {0};		//用一个数组来保存所有用户的连接socket描述符

void* getAccpet(void* arg)
{
	if ((client_fd[user_count] = accept(sock_fd, NULL, NULL)) == -1)
		perror("接受服务失败：\n");
	else 		//每次成功接受新请求就新开启一个线程，让新线程来阻塞继续等待请求
		pthread_create(&thread_fd, NULL, getAccpet, NULL);
	
	int user_id = user_count++;			//定义用户id
	printf("有用户加入socket！当前用户数量为：%d人。\n", user_count);
	send(client_fd[user_id], &user_id, 10, 0);
	
	while (1)		//即使没有循环结构，函数运行到accpet()时会停下等待连接或是请求(阻塞线程)，但只会接收一次请求(即TCP模式下无法接收多个用户发送的数据，只会与第一个用户交互)，之后函数就会结束，要想让服务端一直监听下去则需要一直运行recv()接收数据，循环accpet()尽管能结接收多个请求但会阻塞当前线程导致无法继续执行代码，合理的方式是采用多个线程，每个线程接受一个请求。
	{
		char message[50];
		memset(message, 0, 50);
		
		if (recv(client_fd[user_id], message, 50, 0) == -1)
			perror("接收消息失败：\n");
		else
		{
			if (!strcmp(message, "close"))
			{
				printf("收到关闭命令！\n关闭socket端口监听！\n");
				for (int i = 0; i < user_count; i++)		//收到关闭信息之后向所有客户端发送关闭消息
					send(client_fd[i], message, 10, 0);
				break;
			}
			else if (!strcmp(message, ""))		//应对用户关闭socket时可能产生的空消息
				break;
			printf("第%d次接收，接收到来自用户[%d]的消息：%s\n", ++num, user_id, message);
		}
	}
	close(client_fd[user_id]);
}

int main(void)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = 9999;					//当主机端与客户端数据类型兼容时，端口号可以不做转换
	addr.sin_addr.s_addr = INADDR_ANY;		//代表接收任意地址的数据
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		perror("绑定端口失败！\n");
	
	if (listen(sock_fd, USER_MAX) == -1)
		perror("监听端口失败！\n");
	
	pthread_create(&thread_fd, NULL, getAccpet, &sock_fd);
	pthread_join(thread_fd, NULL);
	
	close(sock_fd);
	return 0;
}
