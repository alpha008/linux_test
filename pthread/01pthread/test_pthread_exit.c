/*
所需头文件：
#include <pthread.h>
void pthread_exit(void *retval);
功能：
退出调用线程。一个进程中的多个线程是共享该进程的数据段，因此，通常线程退出后所占用的资源并不会释放。
参数：retval：存储线程退出状态的指针。
返回值：
无
*/
#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>  
void *thread(void *arg)  
{  
    static int num = 456; //静态变量  
    int i = 0;  
    while(1)  
    {  
        printf("I am runing\n");  
        sleep(1);  
        i++;  
        if(i==3)  
        {  
            pthread_exit( (void *)&num ); 
        }  
    }  
    return NULL;  
}  
int main(int argc, char *argv[])  
{  
    int ret  = 0;  
    pthread_t tid;  
    void *value  = NULL;  
      
    ret = pthread_create(&tid, NULL, thread, NULL);    
    if(ret!=0)
    {  
        perror("pthread_create");  
    }  
      
    pthread_join(tid, &value);  
      
    printf("value = %d\n", *(int *)value );  
      
    return 0;  
}  
 