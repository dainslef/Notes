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
	
	attr.mq_flags = O_NONBLOCK;			//设置消息队列非阻塞
	
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
	
	//进程结束。消息队列描述符自动关闭
	mq_close(mqdes);
	
	return 0;
}
