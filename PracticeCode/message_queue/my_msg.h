#define PROJECT_ID 0
#define PATH "/home/dainslef"

#include <stdio.h>
#include <sys/msg.h>

struct my_msg
{
	long type;

	struct
	{
		char text[20];
		int num;
	} data;
};