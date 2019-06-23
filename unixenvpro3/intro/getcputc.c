#include "apue.h"
int main(void)
{
	int		c;
	while ((c = getc(stdin)) != EOF)
    {
        if (putc(c, stdout) == EOF)
        {
            err_sys("output error");
        }              
    }   
	if (ferror(stdin))
		err_sys("input error");
	exit(0);
/*
1. return返回函数值，是关键字；  exit 是一个函数。
2. return是语言级别的，它表示了调用堆栈的返回；而exit是系统调用级
别的，它表示了一个进程的结束。
3. return是函数的退出(返回)；exit是进程的退出。
4. return是C语言提供的，exit是操作系统提供的（或者函数库中给出的）。
5. return用于结束一个函数的执行，将函数的执行信息传出个其他调用函数
使用；exit函数是退出应用程序，删除进程使用的内存空间，并将应用程序的一个状态返回给OS，这个状态标识了应用程序的一些运行信息，这个信息和机器和操作系统有关，
一般是 0 为正常退出，非0 为非正常退出。
6. 非主函数中调用return和exit效果很明显，但是在main函数中调用return和exit的现象就很模糊，多数情况下现象都是一致的。
*/
}
