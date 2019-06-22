/*
创建一个线程后应回收其资源，但使用 pthread_join() 函数会使调用者阻塞，Linux 还提供了非阻塞函数 pthread_detach() 来回收线程的资源。
所需头文件：
#include <pthread.h>
int pthread_detach(pthread_t thread);
功能：
使调用线程与当前进程分离，分离后不代表此线程不依赖与当前进程，
线程分离的目的是将线程资源的回收工作交由系统自动来完成，
也就是说当被分离的线程结束之后，系统会自动回收它的资源。所以，此函数不会阻塞。
参数：thread：线程号。
返回值：
成功：0
失败：非 0
注意，调用 pthread_detach() 后再调用 pthread_join() , pthread_join() 会立马返回，调用失败。
*/
#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>  
void *thead(void *arg)  
{  
    int i;  
    for(i=0; i<5; i++)  
    {  
        printf("I am runing\n");  
        sleep(1);  
    }    
    return NULL;  
}  
int main(int argc, char *argv[])  
{  
    int ret  = 0;  
    pthread_t tid;  
      
    ret = pthread_create(&tid, NULL, thead, NULL);  
    if(ret!=0)
    {  
        perror("pthread_create");  
    }  
    pthread_detach(tid); // 线程分离，不阻塞 将线程的回收工装交给系统来完成 
      
    // 立马返回，调用失败  
    int flag = pthread_join(tid, NULL);  
    if(flag != 0)
    {  
        printf("join not working\n");  
    }  
    printf("after join\n");  
    sleep(10);  
    printf("I am leaving\n");  
      
    return 0;  
}  
