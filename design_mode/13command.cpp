//一个对象调用另一个对象，但是现在将这个对象封装起来去专门去实现调用
//请求越来越多的时候就会弄出一个发起者。
//在面向对象的程序设计中，一个对象调用另一个对象，一般情况下的调用过程是：创建目标对象的实力，调用参数，调用目标的方法
// 但是在有些情况下，有必要设计一个专门的类对这个调用过程加以封装，我们把这种专门封装的类成为Command类
#include<iostream>
#include<string>
#include<list>
using namespace std;
class barbecuer //接收者执行命令
{
public:
	void bakemutton()
	{
		cout << "烤羊肉串" << endl;
	}
	void bakechickenwing()
	{
		cout << "烤鸡翅" << endl;
	}
};
class Command   //命令基类
{
protected:
	barbecuer *receiver;//类的包含
public:
	Command(barbecuer*receiver) //命令接受 对象注入技术，然后将这个变量私有化
	{
		this->receiver = receiver;
	}
	virtual void executecommand() = 0;
};
class bakermuttoncommand :public Command //命令传送者
{
public:
	bakermuttoncommand(barbecuer*receiver) :Command(receiver)
	{}
	void executecommand()
	{
		receiver->bakemutton();
	}
};
class bakechikenwingcommand :public Command //命令传送者
{
public:
	bakechikenwingcommand(barbecuer*receiver) :Command(receiver)
	{}
		void executecommand()
		{
			receiver->bakechickenwing();
		}
};
class waiter //服务员
{
private:
	Command *command;
public:
	void setorder(Command*command) //对象注入技术，对象的赋值
	{
		this->command = command;
	}
	void notify()
	{
		command->executecommand();
	}
};
class waiter2  //给多个对象下达命令
{
private:
	list<Command*>orders;
public:
	void setorder(Command*command)
	{
		orders.push_back(command);
	}
	void cancelorder(Command *command)
	{}
	void notify()
	{
		list<Command*>::iterator iter = orders.begin();
		while (iter != orders.end())
		{
			(*iter)->executecommand();
			iter++;
		}
	}
};
int main()
{
	barbecuer *boy = new barbecuer;
	Command *bm1 = new bakermuttoncommand(boy);
	Command *bm2 = new bakermuttoncommand(boy);
	Command *bc1 = new bakechikenwingcommand(boy);

	waiter2 *girl = new waiter2();
	girl->setorder(bm1);
	girl->setorder(bm2);
	girl->setorder(bc1);

	girl->notify();
	return 0;
}