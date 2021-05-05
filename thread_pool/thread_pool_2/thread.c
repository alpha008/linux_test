#include "thread_pool.hpp"
#include <unistd.h>
int main()
{
  ThreadPool* tp = new ThreadPool();
  tp->ThreadPoolInit();
  int x = 3;
  while(1)
  {
    Task t(x);
    tp->Put(t);
    x++;
    if(x==10)//当10时退出线程池
    {
      tp->ThreadPoolQuit();
      //break;
    }
    sleep(1);
  }
  return 0;
}
