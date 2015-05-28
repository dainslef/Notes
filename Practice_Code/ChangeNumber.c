/*
 * 代码完成时间： 2014-12-04 07：15 AM
 * 《c语言程序设计-谭浩强》 P291 第3题
 */

/**
 *
 * @author dainslef
 */

#include <stdio.h>

void Input(int *a)
{
	printf("请输入10个数：\n");
	for (int i = 0; i < 10; i++)
		scanf("%d", &a[i]);
}

void Deal(int *a)
{
	int max = 0, min = 0;
	for (int i = 0; i < 10; i++)
	{
		if (a[i] > a[max])
			max = i;
		else if (a[i] < a[min])
			min = i;
	}
	printf("你输入的数字中，最大的是%d，最小的是%d\n", a[max], a[min]);
	int temp = a[max];
	a[max] = a[9];
	a[9] = temp;
	if (min == 9)
	{
		temp = a[max];
		a[max] = a[0];
	}
	else
	{
		temp = a[min];
		a[min] = a[0];
	}
	a[0] = temp;
}

void Output(int *a)
{
	printf("经过处理后的序列为：\n");
	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");
}

int main(void)
{
	int a[10] = {0};
	Input(a);
	Deal(a);
	Output(a);
	return 0;
}
