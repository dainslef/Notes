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

#define USER_MAX 10						//定义最大用户数量
#define MSG_SIZE 50						//定义单次发送字符串最大长度

pthread_t thread_fd;
int sock_fd = 0;
int msg_count = 0;						//记录接收数据次数
int user_count = 0;						//用户数量计数
int client_fd[USER_MAX];				//用一个数组来保存所有用户的连接socket描述符

void* get_accept(void* arg)
{
	if ((client_fd[user_count] = accept(sock_fd, NULL, NULL)) == -1)
	{
		perror("接收请求失败");
		return NULL;		//BSD系统上client关闭socket会产生新的请求，创建失败直接退出
	}
	else 					//每次成功接受新请求就新开启一个线程，让新线程来阻塞继续等待请求
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
				for (int i = 0; i < user_count; i++)		//收到关闭信息之后向所有客户端发送关闭消息
					send(client_fd[i], message, MSG_SIZE, 0);
				break;
			}
			else if (!strcmp(message, ""))					//应对用户关闭socket时可能产生的空消息
				break;
			printf("第%d次接收，接收到来自用户[%d]的消息：%s\n", ++msg_count, user_id, message);
		}
	}

	close(client_fd[user_id]);
	return NULL;
}

int main(void)
{
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("初始化socket失败");
		return 0;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = 9999;					//当主机端与客户端数据类型兼容时，端口号可以不做转换
	addr.sin_addr.s_addr = INADDR_ANY;		//代表接收任意地址的数据

	if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("绑定端口失败");
		close(sock_fd);
		return 0;
	}

	if (listen(sock_fd, USER_MAX) == -1)
	{
		perror("监听端口失败");
		close(sock_fd);
		return 0;
	}

	get_accept(NULL);

	close(sock_fd);
	return 0;
}