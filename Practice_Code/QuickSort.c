/*
 * 代码完成时间： 2014-12-03 07：15 AM
 * 本代码实现快速排序算法。
 * 算法采用递归实现。
 */

/**
 *
 * @author dainslef
 */

#include <stdio.h>

int Partition(int *a, int start, int end) 		//将数列的第一个数作为example，并以example为中间值划分，example左边的元素都比example小，右边的元素都比example大
{
	int example = a[start];
	do
	{
		for (int i = end; i >= start; i--)		//从右往左依次比较，直到找到比example小的元素，然后将example交换过去
		{
			if (a[i] < example)
			{
				a[start] = a[i];
				a[i] = example; 		//交换数字立即赋值，放到最后赋值可能会产生错误
				start += 1;		//交换数值后，start位置的数值肯定比example小(呵呵，废话)，所以下次比较就从start的下一个位置开始了
				end = i;		//i位置之后的数字肯定比example大，也不用再比较了，所以把i作为end就好了
				break;
			}
			if (i == start) 		//如果到了最后也没右找到比example小的元素，说明example是最小的元素了，则分割序列成功
				end = start;
		}
		for (int i = start; i <= end; i++)		//从左往右以此比较，直到找到比example大的元素，然后将example交换过去
		{
			if (a[i] > example)
			{
				a[end] = a[i];
				a[i] = example;
				start = i + 1;
				end -= 1;
				break;
			}
			if (i == end)
				start = end;
		}
	} while (start < end);		//当start和end位置相同或大于end(不能取start != end作为条件，有时会出现start > end的情况，此时会造成无限循环。。。，比如输入 4 3 1 2)，就表明example的位置已经确定下来了
	return start;		//将example的位置作为返回值
}

void QuickSort(int *a, int start, int end)
{
	if (start < end)		//递归退出条件
	{
		int mid = Partition(a, start, end);
		QuickSort(a, start, mid);		//注意参数不能写成mid-1，会使得部分情况下比较不完整(mid与mid-1大小不按顺序时)
		QuickSort(a, mid + 1, end);
	}
}

int main(void)
{
	int count;
	printf("请输入数组中元素的个数：\n");
	scanf("%d", &count);
	int a[count];
	printf("请依次输入数组的内容：\n");
	for (int i = 0; i < count; i++)
		scanf("%d", a + i);
	QuickSort(a, 0, count - 1);
	for (int i = 0; i < count; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
