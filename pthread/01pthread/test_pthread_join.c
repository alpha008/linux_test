/*
回收线程资源
所需头文件：
	#include <pthread.h>
	int pthread_join(pthread_t thread, void * *retval);
	功能：
	等待线程结束（此函数会阻塞），并回收线程资源，类似进程的 wait() 函数。如果线程已经结束，那么该函数会立即返回。
	参数：
	thread：被等待的线程号。
	retval：用来存储线程退出状态的指针的地址。
	返回值：
	成功：0
	失败：非 0
1.linux线程执行和windows不同，pthread有两种状态joinable状态和unjoinable状态，如果线程是joinable状态，
当线程函数自己返回退出时或pthread_exit时都不会释放线程所占用堆栈和线程描述符（总计8K多）。
只有当你调用了pthread_join之后这些资源才会被释放。若是unjoinable状态的线程，这些资源在线程函数退出时或pthread_exit时自动会被释放。
2.unjoinable属性可以在pthread_create时指定，或在线程创建后在线程中pthread_detach自己
如：pthread_detach(pthread_self())，将状态改为unjoinable状态，确保资源的释放。或者将线程置为 joinable,然后适时调用pthread_join.
3.其实简单的说就是在线程函数头加上 pthread_detach(pthread_self())的话，线程状态改变，在函数尾部直接 pthread_exit线程就会自动退出。
省去了给线程擦屁股的麻烦。

*/
#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>  
  
void *thead(void *arg)  
{  
    static int num = 123; //静态变量  
      
    printf("after 2 seceonds, thread will return\n");  
    sleep(2);  
    /*此处很关键
     先转换为整形指针,count为int类型，那么&count为int*类型，同样为了保持匹配，这里本人使用显式的调用，直接写作为
     &num,其实这个表明了现在变成了一个int的指针，这个时候与void*匹配的话，需要进行强制转换，也就是代码中的
     (void*)(&num);    
    */
    return (void *)(&num);  
}
void* thread_main(void* pmax)
{
	int i;
	int max=*((int*)pmax);
	for(i=0;i<max;i++)
	{
		puts("child thread called...");
		sleep(1);
	}
	return "Tread ended ...";
}
int test()
{
		pthread_t pid;
		void* rst;
		int max=10;
		pthread_create(&pid,NULL,(void*)thread_main,(void*)&max);
		pthread_join(pid,(void*)&rst);
		printf("the child return: %s\n",(char*)rst);
		return 0;
}

int main(int argc, char *argv[])  
{  
    pthread_t tid;  
    int ret = 0;  
    void *value = NULL;  
      
    // 创建线程  
    ret = pthread_create(&tid, NULL, thead, NULL);  
    if(ret != 0)
    { //创建失败
    		printf("回收失败");  
        perror("pthread_create");  
    }  
    // 等待线程号为 tid 的线程，如果此线程结束就回收其资源  
    // &value保存线程退出的返回值 
    pthread_join(tid, (void *)&value );   
    // 将其转换成二级指针后，然后取其内容，里面存的是函数返回值

    printf("value = %d\n", *((int*)value));   
    return 0;  
}  
