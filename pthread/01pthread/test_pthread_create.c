/*
#include <pthread.h>
int pthread_create( pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine)(void *),void *arg );
功能：
创建一个线程。
参数：
thread：线程标识符地址。 
attr：线程属性结构体地址，通常设置为 NULL。
start_routine：线程函数的入口地址。
arg：传给线程函数的参数。
返回值：
成功：0
失败：非 0
pthread_create() 创建的线程从指定的回调函数开始运行，该函数运行完后，该线程也就退出了。
线程依赖进程存在的，共享进程的资源，如果创建线程的进程结束了，线程也就结束了。
*/
#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>  
int var  = 8;  
void *thread_1(void *arg)  
{  
    while(1)  
    {  
        printf("this is my new thread1: var++\n");  
        var++;  
        sleep(1);  
    }  
    return NULL;  
}
void *thread_2(void * arg)  
{  
    while(1)
    {  
        printf("this is my new thread2: var = %d\n", var);  
        sleep(1);  
    } 
    return NULL;  
}   
int main(int argc, char *argv[])  
{  
    pthread_t tid1,tid2;    
    //创建两个线程  
    pthread_create(&tid1, NULL, thread_1, NULL);    
    pthread_create(&tid2, NULL, thread_2, NULL);  
    while(1)
    {  
        printf("the main thread: var = %d\n", var);  
        sleep(1);  
    }    
    return 0;  
}  