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
	
	unsigned prio;
	
	//循环取出队列中所有消息
	while (1)
	{
		memset(&data, 0, sizeof(data));
		
		if (mq_receive(mqdes, (char*)&data, attr.mq_msgsize, &prio) == -1)
		{
			perror("mq_receive");
			break;
		}
		else
			printf("Num: %d\nMessage type: %u\nReceive: %s\n\n", data.num, prio, data.text);
	}
	
	mq_unlink(PATH_NAME);

	return 0;
}
