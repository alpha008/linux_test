#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>  
/*
线程的常用函数
1）获取线程号
	所需头文件：
	#include <pthread.h>
	pthread_t pthread_self(void);
	功能：获取线程号。
	参数：无
	返回值：
	调用线程的线程 ID 。
2）线程号的比较
	所需头文件：
	#include <pthread.h>
	int pthread_equal(pthread_t t1, pthread_t t2);
	功能：判断线程号 t1 和 t2 是否相等。为了方便移植，尽量使用函数来比较线程 ID。
	参数：t1，t2：待判断的线程号。
	返回值：
	相等：  非 0
	不相等：0
*/
int main(int argc, char *argv[])  
{  
    pthread_t thread_id;  
  
    thread_id = pthread_self(); // 返回调用线程的线程ID  
    printf("Thread ID = %lu \n",thread_id);  
  
    if( 0 != pthread_equal( thread_id, pthread_self() ) )
    {  
        printf("Equal!\n");  
    }else
    {  
        printf("Not equal!\n");  
    }       
    return 0;  
}  