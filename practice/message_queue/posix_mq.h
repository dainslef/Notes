#include <stdio.h>
#include <string.h>
#include <mqueue.h>

#define PATH_NAME "/tmp"
#define FLAG (O_CREAT | O_RDWR)
#define MODE (S_IRUSR | S_IWUSR)

struct
{
	char text[20];
	int num;
} data;
