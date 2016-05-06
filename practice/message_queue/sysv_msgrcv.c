#include "my_msg.h"

int main(int argc, char** argv)
{
	key_t key = ftok(PATH, PROJECT_ID);
	struct my_msg msg;
	int msg_id = 0;

	if ((msg_id = msgget(key, 0)) == -1)
		perror("msgget");

	while (1)
	{
		if (msgrcv(msg_id, &msg, sizeof(msg.data), -300, IPC_NOWAIT) == -1)
		{
			perror("msgrcv");
			break;
		}
		else
			printf("Num: %d\nMessage type: %ld\nRecevie: %s\n\n", msg.data.num, msg.type, msg.data.text);
	}

	if (msgctl(msg_id, IPC_RMID, NULL) == -1)
		perror("msgctl");

	return 0;
}