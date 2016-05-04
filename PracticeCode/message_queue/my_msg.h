struct my_msg
{
	long type;

	struct
	{
		char text[20];
		int num;
	} data;
};
