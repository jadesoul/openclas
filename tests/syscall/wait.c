/**
 * File: wait.cpp
 * Description:
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 *
 * Date: 2012-06-26 12:47:32.239000
 * Written In: Peking University, beijing, China
 */

// 系统中的僵尸进程都要由wait系统调用来回收，下面就通过实战看一看wait的具体用法：
// wait的函数原型是：
// #include <sys/types.h> /* 提供类型pid_t的定义 */
// #include <sys/wait.h>
// pid_t wait(int *status);
// 进程一旦调用了wait，就立即阻塞自己，由wait自动分析是否当前进程的某个子进程已经退出，如果让它找到了这样一个已经变成僵尸的子进程， wait就会收集这个子进程的信息，并把它彻底销毁后返回；如果没有找到这样一个子进程，wait就会一直阻塞在这里，直到有一个出现为止。
// 参数status用来保存被收集进程退出时的一些状态，它是一个指向int类型的指针。但如果我们对这个子进程是如何死掉的毫不在意，只想把这个僵尸进程消灭掉，（事实上绝大多数情况下，我们都会这样想），我们就可以设定这个参数为NULL，就象下面这样：
// pid = wait(NULL);
// 如果成功，wait会返回被收集的子进程的进程ID，如果调用进程没有子进程，调用就会失败，此时wait返回-1，同时errno被置为ECHILD。
// 下面就让我们用一个例子来实战应用一下wait调用:

/* wait1.c */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	char buf[10]="jadesoul";
	buf[8]=0;
	char *s=buf;
	printf("init, in parent, s=%s\n", s);
	pid_t pc, pr;
	pc = fork();
	if ( pc < 0 ) {
		printf("create child prcocess error: %s \n", strerror(errno));
		exit(1);
	} else if ( pc == 0) { /* 如果是子进程 */
		printf("in child, s=%s\n", s);
		printf("I am child process with pid %d \n", getpid());
		sleep(3);/* 睡眠3秒钟 */
		exit(0);
	} else { /* 如果是父进程 */
		s[0]='a';
		printf("in parent, s=%s\n", s);
		printf("Now in parent process, pid = %d\n", getpid());
		printf("I am waiting child process to exit.\n");
		pr = wait(NULL); /* 在这里等待子进程结束 */
		
		/*子进程正常返回*/
		if ( pr > 0 ) printf("I catched a child process with pid of %d\n", pr);
		else printf("error: %s \n", strerror(errno));
	}
	exit(0);
}


// 编译并运行：
// $ gcc wait1.c -o wait1
// $ ./wait1
// I am child process with pid 2351
// Now in parent process, pid = 2350
// I am waiting child process to exit.
// I catched a child process with pid of 2351
// 可以明显注意到，在第2行结果打印出来前有10秒钟的等


