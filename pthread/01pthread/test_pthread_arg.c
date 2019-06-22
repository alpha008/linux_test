/*
	向线程传入参数
*/
#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>  
  
// 回调函数   空指针  根据需要将其转换成需要的地址大小
void *thread_fun(void * arg)  
{  
    sleep(1);  
    int num = *( (int *)arg );  
    printf("int the new thread: num = %d\n", num);  
      
    return NULL;  
}  
  
int main(int argc, char *argv[])  
{  
    pthread_t tid;  
    int test = 100;  
      
    // 创建线程, 把 &test 传给回调函数 thread_fun()  回调函数传递的是地址，并将其转换成空指针
    pthread_create(&tid, NULL, thread_fun, (void *)&test);    
  
    while(1);  
      
    return 0;  
}  
