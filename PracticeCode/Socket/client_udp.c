/*
 * 代码完成时间： 2015-4-11 02：46 AM
 * Unix Socket通信，采用UDP方式
 * 客户端程序
 */

/**
 *
 * @author dainslef
 */

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv)
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
	addr.sin_port = 8888;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("发送的内容：%s\n", str);

	if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		perror("The wrong is: ");
	else
	{
		if (send(sock_fd, str, 50, 0) == -1)
			perror("发送失败：");
	}

	close(sock_fd);
	return 0;
}
