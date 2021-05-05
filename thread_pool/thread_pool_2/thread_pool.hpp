#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
using namespace std;

struct Task//任务
{
private:
  int _val;
public:
  Task(){}
  Task(int val):_val(val)
  {}
  void work()//获得任务后在这里进行判断
  {
    for(int j=2;j < _val;j++)
    {
      if(_val%j==0)
      {
        cout<<"thread:"<<pthread_self()<<"   "<<_val<<"不是素数"<<endl;
        return;
      }
    }
     cout<<"thread:"<<pthread_self()<<"   "<<_val<<"是素数"<<endl;
    return;
  }
};

class ThreadPool//线程池
{
private:
  bool _thread_quit_flag;//线程退出标志，如果主线程发送了信号，就将其置为true
  int _thread_num;//线程池线程数量
  queue<Task*> q;//任务队列,存放指针
  pthread_mutex_t lock;//保护任务队列的锁
  pthread_cond_t cond;//条件变量，当没有任务时线程池的线程挂起，当有任务时唤醒线程池线程

public:
  void ThreadLock(){//锁
    pthread_mutex_lock(&lock);
  }
  void ThreadUnlock(){//解锁
    pthread_mutex_unlock(&lock);
  }
  bool IsEmpty(){//判断任务队列为空
    return q.size()==0;
  }
  void Threadwait(){//没有任务线程池的线程挂起
    pthread_cond_wait(&cond,&lock);
  }
  void Threadwakeup(){//当主线程添加了任务就唤醒线程池线程
    pthread_cond_signal(&cond);
  }
  void ThreadWakeAll(){//最后发送退出信号时，将所有线程唤醒，然后让其退出
    pthread_cond_broadcast(&cond);//唤醒所有线程
  }

  void ThreadQuit(){//线程退出函数
    pthread_exit(nullptr);
  }

public:

  ThreadPool(int thread_num=5):_thread_quit_flag(false),_thread_num(thread_num)//flag默认设置为flase，不退出
  {
    pthread_mutex_init(&lock,nullptr);
    pthread_cond_init(&cond,nullptr);
  }

  ~ThreadPool()
  {
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
  }

  static void* Route(void* arg)//所有的线程都要执行这样的流程：先判断是否有任务，有就执行，没有就挂起
  {
    pthread_detach(pthread_self());//线程 
    ThreadPool* this_p=(ThreadPool*)arg;//某个线程的this指针
    while(1)
    {
      this_p->ThreadLock();//锁定任务队列
      while(this_p->_thread_quit_flag==false && this_p->IsEmpty())
      //如果没有发出退出信号并且队列为空，那么就让线程挂起
      {
        this_p->Threadwait();
        //当线程苏醒时（可能接收到了广播信号或者位于线程队列它被下一个唤醒了），就会从挂起的地方醒来，继续向下执行
      }
        if((this_p->_thread_quit_flag==false && !this_p->IsEmpty()) || (this_p->_thread_quit_flag==true && !this_p->IsEmpty()))
          //醒来的原因不管是否是因为接收到了退出信号，反正只要有任务就得先执行完
      {
        Task t;
        this_p->Get(t);
        this_p->ThreadUnlock();//注意不要在临界资源内做任务，效率很低
        t.work();//获得任务后进行计算
      }
      //如果接受到信号且队列已经Wie空了，那么就退出线程
      else if(this_p->_thread_quit_flag==true && this_p->IsEmpty())
        //如果醒来的原因是因为接受到了退出信号，而且任务队列中已经没有任务了，那么就退出线程
      {
        this_p->ThreadUnlock();
        this_p->ThreadQuit();//退出时不要忘记解锁，否则将来只有一个线程能推出，其余线程无法退出
      }
  }
}

  void ThreadPoolInit()//风险操作不要在构造函数中写，该函数用于创建线程池线程，并让线程执行Route流程
  {
    pthread_t t;
    for(int i=0;i < _thread_num;i++)
    {
      pthread_create(&t,nullptr,Route,this);
      //这里最后一个参数传入了this指针，相应的Route函数也是静态成员函数
      //如果不传入this指针，那么当这个参数就会和非静态成员函数抢this指针的位置，因此会造成参数过多的问题
      //所以在这里传入this，然后在形参中使用this调用自己的成员函数即可
    }
  }

  void ThreadPoolQuit()//线程池退出
  {
      _thread_quit_flag=true;//将结束标志置为true
      ThreadWakeAll();//唤醒所有线程
  }

  void Get(Task& t)//线程获取任务
  {
    Task* out=q.front();//注意是指针
    q.pop();
    t=*out;//这是解引用
  }

  void Put(Task& t)//主线程放任务
  {
    ThreadLock();
    q.push(&t);//注意这是取地址
    ThreadUnlock();
    Threadwakeup();//当放了一个任务后立马唤醒线程，这里一般情况下不要唤醒所有线程，会产生掠群效应，影响稳定性
  }
};
