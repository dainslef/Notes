/*
 * 代码完成时间： 2014-11-26 06：38 AM
 * 2012年硕士研究生计算机入学考试 第42题
 * 有两个字符串存储单词，当这两个单词有相同的后缀时，共享后缀的存储空间，找出重叠的起始位置。
 * 标准答案，时间复杂度为O(n)，空间复杂度为O(1)。
 * 通过计算两个链表的长度差来同步对齐，再一一比较节点的data值，找到data值相等的节点。
 */

/**
 *
 * @author dainslef
 */

#include <stdio.h>
#include <stdlib.h>

struct Node			//定义链表的数据结构
{
	char data;
	struct Node *next;
} *Head1, *Head2, *temp, *temp0;

void scanning(struct Node *temp)		//扫描链表的内容
{
	do
	{
		printf("%c ", temp->data);
		temp = temp->next;
	} while (temp != NULL);
}

char find(struct Node *head1, struct Node *head2)		//查找首个重复字符
{
	int n, num1, num2;
	for (num1 = 0, temp = head1; temp != NULL; temp = temp->next)
		num1++;			//计算链表Head1的长度
	for (num2 = 0, temp0 = head2; temp0 != NULL; temp0 = temp0->next)
		num2++;			//计算链表Head2的长度
	if (num2 > num1)
	{
		n = num2 - num1;
		temp = head2;
		temp0 = head1;
	}
	else
	{
		n = num1 - num2;
		temp = head1;
		temp0 = head2;
	}
	for (int i = 0; i < n; i++)
		temp = temp->next;		//将两张表长度对齐
	for (; temp != NULL; temp = temp->next, temp0 = temp0->next)
		if (temp->data == temp0->data)
			break;		//找到内容相同的字符时跳出循环
	return temp->data;
}

int main(int argc, char *argv[])
{
	char *str1 = "loading";
	char *str2 = "be";
	temp = Head1 = (struct Node*)malloc(sizeof(struct Node));
	Head2 = (struct Node*)malloc(sizeof(struct Node));
	
	for (int i = 0; i < 7; i++)
	{
		struct Node *change = (struct Node*)malloc(sizeof(struct Node));		//分配内存创建新的节点
		temp->next = change;
		if (str1[i] == 'i')
			temp0 = change;			//记录重复字符出现的位置
		change->data = str1[i];
		temp = temp->next;
	}
	temp->next = NULL;		//字符串1的录入结束，将最后一个节点的next指针置为空
	
	temp = Head2;
	for (int i = 0; i < 2; i++)
	{
		struct Node *change = (struct Node*)malloc(sizeof(struct Node));
		temp->next = change;
		change->data = str2[i];
		temp = temp->next;
	}
	temp->next = temp0;		//字符串的前2个字符录入之后，后面的字符链接到temp0位置上
	
	temp = Head1;
	printf("字符串1中的内容为：");
	scanning(temp);
	printf("\n");
	temp = Head2;
	printf("字符串2中的内容为：");
	scanning(temp);
	printf("\n");

	printf("两个字符串的相同起始位置为： %c \n", find(Head1, Head2));
	return 0;
}
