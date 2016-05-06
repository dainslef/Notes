#include <string.h>

#include "my_msg.h"

int main(int argc, char** argv)
{
	key_t key = ftok(PATH, PROJECT_ID);
	struct my_msg msg;
	int msg_id = 0;
	int flag = IPC_CREAT | 0600;

	if ((msg_id = msgget(key, flag)) == -1)
		perror("msgget");

	strcpy(msg.data.text, "Hello");
	msg.data.num = 1;

	//以非阻塞形式发送消息
	if (msgsnd(msg_id, &msg, sizeof(msg.data), IPC_NOWAIT) == -1)
		perror("msgsnd");
	else
		printf("Num: %d\nMessage type: %ld\nRecevie: %s\n\n", msg.data.num, msg.type, msg.data.text);

	strcpy(msg.data.text + 5, " World");

	for (int i = 1; i < 5; i++)
	{
		msg.type = 100 * i;
		msg.data.num += 1;

		if (msgsnd(msg_id, &msg, sizeof(msg.data), IPC_NOWAIT) == -1)
			perror("msgsnd");
		else
			printf("Num: %d\nMessage type: %ld\nRecevie: %s\n\n", msg.data.num, msg.type, msg.data.text);
	}

	//获取进程信息
	struct msqid_ds buf;
	if (msgctl(msg_id, IPC_STAT, &buf) == -1)
		perror("msgctl");
	else
	{
		printf("Message privileges info:\n");

		//打印进程权限信息
		printf("msg_perm.uid: %u\n", buf.msg_perm.uid);
		printf("msg_perm.cuid: %u\n", buf.msg_perm.cuid);
		printf("msg_perm.gid: %u\n", buf.msg_perm.gid);
		printf("msg_perm.cgid: %u\n", buf.msg_perm.cgid);
		printf("msg_perm.mode: %o\n", buf.msg_perm.mode);
	}

	return 0;
}