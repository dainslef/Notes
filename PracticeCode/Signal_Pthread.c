/*
 * 代码完成时间： 2015-4-11 03：02 AM
 * Unix线程以及信号操作练习
 * 创建执行同一个函数的1、2号线程，让其拥有互斥量而不能同时运行一段代码，发送SIGQUIT信号让1、2号线程结束，新建3号、4号线程，3号、4号线程没有互斥量，能并发执行。
 */

/**
 *
 * @author dainslef
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define MYMES1 SIGUSR1 + 1			//自定义信号，不能设置太大，Linux中32～64信号为用户可用
#define MYMES2 SIGUSR1 + 2

pthread_t thread_fd = 0;
pthread_t thread_fd1 = 0;
pthread_mutex_t mutex;

void dealSignal(int signal)
{
	switch(signal)
	{
	case SIGQUIT:		//捕获SIGQUIT信号，用 "ctrl+\" 组合键触发
		pthread_cancel(thread_fd);					//取消一号线程
		pthread_cancel(thread_fd1);					//取消二号线程
		printf("结束一、二号线程，接下来三、四号线程没有互斥量，输出内容会相互交错！\n");
		if (pthread_mutex_destroy(&mutex) == -1)		//删除锁
			printf("删除失败！\n");
		break;
	case MYMES1:
		printf("有互斥变量的时候，内容不会交错。\n");
		break;
	case MYMES2:
		printf("没有互斥变量的时候，内容会相互交错。\n");
		break;
	}
}

void* thread_func(void* arg)
{
	while (1)
	{
		if (!strcmp(arg, "三号线程") || !strcmp(arg, "四号线程"))
			kill(getpid(), MYMES2);		//三号、四号线程发送自定义信号MYMES2
		else if (pthread_mutex_lock(&mutex) == -1)
			printf("加锁失败！\n");
		else
			kill(getpid(), MYMES1);		//一号、二号线程发送自定义信号MYMES1
		
		printf("%s开始。\n", (char*)arg);
		
		int num = 0;
		while (num++ < 3)
		{
			sleep(2);
			printf("%s循环第%d次\n", (char*)arg, num);
		}
				
		if (pthread_mutex_unlock(&mutex) == -1)
			printf("解锁失败！\n");
		
		sleep(2);			//线程休眠一秒，否则资源会一直被一个线程占有
	}
}

int main(void)
{
	char *str1 = "一号线程";
	char *str2 = "二号线程";
	char *str3 = "三号线程";
	char *str4 = "四号线程";
	
	struct sigaction sig;
	sig.sa_handler = dealSignal;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGQUIT, &sig, 0);		//现代Unix信号捕捉函数
	
	signal(MYMES1, dealSignal);			//传统Unix信号捕捉函数
	signal(MYMES2, dealSignal);

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread_fd, NULL, thread_func, str1);
	pthread_create(&thread_fd1, NULL, thread_func, str2);
	pthread_join(thread_fd1, NULL);			//等待二号线程结束
	pthread_create(&thread_fd, NULL, thread_func, str3);		//创建三号线程
	pthread_create(&thread_fd, NULL, thread_func, str4);		//创建四号线程
	pthread_join(thread_fd1, NULL);
	
	return 0;
}
