/**********************
定义一个一对多的依赖关系，使用多个对象同时监听一个对象。
此对象发生便会会挨个通知其它对象
*************************/
#include<iostream>
#include<string>
#include<list>
using namespace std;
class subject;
class Observer  //观察者观察者的名字，以及监听的对象，抽象类
{           //此处定义的是一对多的依赖关系
public:     //让多个观察者同时监听一个主题对象
	string name; 
	subject *sub;
public:
	Observer(string name, subject *sub)
	{
		this->name = name;
		this->sub = sub;    
	}
	virtual void update() = 0; //预留接口，监听动作
};
class stockobserver :public Observer//股票观察者
{
public:
	stockobserver(string name, subject *sub) :Observer(name, sub)
	{}
	void update(); //在类内声明在类外进行定义
};
class nbaobserver :public Observer
{
public:
	nbaobserver(string name, subject *sub):Observer(name, sub)
	{}
	void update(); //在类内部声明，在类外定义
};
class subject  //消息管理器，将消息放入容器，抽象主题类
{
protected:
	list<Observer*>observers;
public:
	string action;
	virtual void attach(Observer*) = 0;
	virtual void detach(Observer*) = 0;
	virtual void notify() = 0;
};
class secretary :public subject //将消息管理器实例化成秘书对象
{
	void attach(Observer *observer)
	{
		observers.push_back(observer);
	}
	void detach(Observer*observer)//遍历这个消息管理器，
		                          //调用容器内指向的不同的对象
	{
		list<Observer *>::iterator iter = observers.begin();
		while (iter!=observers.end())
		{
			if ((*iter) == observer)
			{
				observers.erase(iter);
			}
			++iter;
		}
	}
	void notify()//消息管理器通知所有的对象
	{
		list<Observer*>::iterator iter = observers.begin();
		while (iter != observers.end())
		{
			(*iter)->update();//这里如果根据自己去拿的话，那么就要自己去拿，或者被动的全部接收
			++iter;
		}
	}
};
void  stockobserver::update()
{
	cout << name << "收到消息：" << sub->action << endl;
	if (sub->action == "赵所长来了！")
	{
		cout << "我马上关闭股票，装作很认真工作的样子" << endl;
	}
	if (sub->action == "去喝酒")
	{
		cout << "我马上走" << endl;
	}
}
void nbaobserver::update()
{
	cout << name << "收到消息:" << sub->action << endl;
	if (sub->action == "赵所长来了！")
	{
		cout << "我马上关闭nba，装作很认真工作的样子" << endl;
	}
	if (sub->action == "去喝酒")
	{
		cout << "我马上走起来" << endl;
	}
}
int main()
{
	subject*dwq = new secretary();
	//dwq是指向主题的指针，
	Observer *xs = new nbaobserver("xiaoshuai",dwq);
	//这里派生类构造函数进行赋值，会拥有基类的所有属性。
	Observer *zy = new nbaobserver("zouyue",dwq);
	Observer *lm = new stockobserver("limin",dwq);

	dwq->attach(xs);
	dwq->attach(zy);
	dwq->attach(lm);
	dwq->action = "去吃饭了"; //进行消息的发送，对aciton进行赋值。
	dwq->notify(); //遍历对象容器，通知不同的对象。
	dwq->action = "去喝酒";
	dwq->notify();
	cout << endl;
	dwq->action = "赵所长来了";
	dwq->notify();
	return 0;
}