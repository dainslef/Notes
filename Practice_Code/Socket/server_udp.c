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

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = 8888;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		perror("The wrong is: ");
	
	char str[50];
	while (1)
	{
		memset(str, 0, 50);
		if (recv(sock_fd, str, 50, 0) == -1)
			perror("接收失败：");
		else 
			printf("接收到消息：%s\n", str);
	}
	
	close(sock_fd);
	return 0;
}
