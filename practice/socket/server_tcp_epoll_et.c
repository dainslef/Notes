/*
 * 代码完成时间： 2015-4-15 03：07 AM
 * Unix Socket通信，采用TCP方式
 * 服务端程序
 * 主要功能：使用IO复用(epoll)同时接受多个用户请求。
 * epoll使用ET非阻塞IO模式。
 * 每登录一个用户，系统会给予提示。
 * 每一个用发送的消息都能够显示在服务端并注明发送者。
 * 当用户发送close消息时关闭服务端和其它所有与服务端相连的客户端。
 */

/**
 *
 * @author dainslef
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>

#define USER_MAX 10 //定义最大用户数量
#define MSG_SIZE 10 //定义单次发送字符串最大长度

int main(void)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);			//当主机端与客户端数据类型兼容时，端口号可以不做转换
	addr.sin_addr.s_addr = INADDR_ANY;		//代表接收任意地址的数据

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		perror("初始化socket失败");
		return 0;
	}

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

	int msg_count = 0; //记录接收数据次数
	int user_count = 0; //用户数量计数
	int client_fd[USER_MAX]; //描述符数组

	//创建epoll描述符
	int epfd = epoll_create(1);

	struct epoll_event epev;
	epev.data.fd = sock_fd;
	epev.events = EPOLLIN;

	if (epoll_ctl(epfd, EPOLL_CTL_ADD, sock_fd, &epev) == -1)
	{
		perror("epoll_ctl()出错");
		goto END;
	}

	while (1)
	{
		int re = 0; //记录epoll_wait()返回值
		struct epoll_event events[user_count + 1];

		// maxevents参数为要监听的所有事件数目之和，包括用户描述符数量(user_count)加上一个sock_fd
		switch (re = epoll_wait(epfd, events, user_count + 1, -1))
		{
		case -1:
			perror("epoll_wait()出错");
			break;
		case 0:
			printf("epoll_wait()超时");
			break;
		default:
			for (int i = 0; i < re; i++)
			{
				if (events[i].data.fd == sock_fd)
				{
					if ((client_fd[user_count] = accept(sock_fd, NULL, NULL)) == -1)
						break; //BSD系列在关闭socket时可能会产生新的请求
					else
					{
						//最大文件描述符值为监听文件描述符集合中的最大值加1
						struct epoll_event epev;
						epev.data.fd = client_fd[user_count];
						epev.events = EPOLLIN | EPOLLET;
						epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd[user_count], &epev);

						//设置监听描述符为非阻塞
						int flags = fcntl(client_fd[user_count], F_GETFL, 0);
						if (flags == -1)
							perror("fnctl() F_GETFL 出错");
						else
						{
							flags |= O_NONBLOCK;
							if (fcntl(client_fd[user_count], F_SETFL, flags) == -1)
								perror("fnctl() F_SETFL 出错");
						}

						write(client_fd[user_count], &user_count, sizeof(user_count));
						printf("有用户加入socket！当前用户数量为：%d人。\n", ++user_count);
						continue;
					}
				}
				if (events[i].events & EPOLLIN)
				{
					char message[MSG_SIZE];

					// 查找用户id
					int user_id = 0;
					for (int j = 0; j < user_count; j++)
					{
						if (client_fd[j] == events[i].data.fd)
							user_id = j;
					}

					// 重复循环读取数据，直到数据读尽
					while (1)
					{
						memset(message, 0, MSG_SIZE);

						if (read(events[i].data.fd, message, MSG_SIZE) == -1)
						{
							if (errno == EAGAIN)
								break;
							else
								perror("接收消息失败");
						}
						else
						{
							if (!strcmp(message, ""))
								continue; //防止Ctrl+C退出产生空字符串造成无限循环
							if (!strcmp(message, "close"))
							{
								printf("收到关闭命令！\n关闭socket端口监听！\n");
								for (int i = 0; i < user_count; i++) //收到关闭信息之后向所有客户端发送关闭消息
									write(client_fd[i], message, MSG_SIZE);
								goto END;
							}
							// %s后的空格不能少，否则可能造成输出字符串结尾出现"口"字符
							printf("第%d次接收，接收到来自用户[%d]的消息：%s \n", ++msg_count, user_id, message);
						}
					}
				}
			}
		}
	}

END:
	for (int i = 0; i < user_count; i++)
		close(client_fd[i]);
	close(sock_fd);
	close(epfd);
	return 0;
}
