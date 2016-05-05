/*
 * 代码完成时间： 2015-4-11 02：48 AM
 * Unix Socket通信，采用UDP方式
 * 服务端程序
 * UDP方式传输数据不建立稳定连接，无需多线程，无需listen()函数监听端口，也不需要accept()函数生成连接套接字
 */

/**
 *
 * @author dainslef
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MSG_SIZE 50						//定义单次发送字符串最大长度

int main(void)
{
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		perror("初始化socket失败");
		return 0;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = 8888;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("绑定端口失败");
		close(sock_fd);
		return 0;
	}

	char message[MSG_SIZE];
	while (1)
	{
		memset(message, 0, MSG_SIZE);
		if (recv(sock_fd, message, MSG_SIZE, 0) == -1)
			perror("接收失败");
		else
			printf("接收到消息：%s\n", message);
	}

	close(sock_fd);
	return 0;
}