//适配器模式： 把一个类的接口变换成客户端期待的另外一种接口
//从而使得原本不能在一起工作得类在一起工作
//适配器根据参数返回一个合适的实例给客户端
#include<iostream>
#include<string>
using namespace std;
class player
{
public:
	string name;
	player(string name)
	{
		this->name = name;
		cout << 11<<name << endl;
		cout <<22<< this->name << endl;
	}
	virtual void attack() = 0;
	virtual void defence() = 0;
};
class forwars :public player
{
public:
	forwars(string name):player(name){}
	void attack()
	{
		cout << name << "前锋进攻" << endl;
	}
	void defence()
	{
		cout << name << "前锋防守" << endl;
	}
};
class center :public player
{
public:
	center(string name) :player(name){}
	void attack()
	{
		cout << name << "中锋进攻" << endl;
	}
	void defence()
	{
		cout << name << "中锋防守" << endl;
	}
};
class backwards :public player
{
public:
	backwards(string name) :player(name){}
	void attack()
	{
		cout << name<<"后卫进攻" << endl;
	}
	void denfence()
	{
		cout << name << "后卫防守" << endl;
	}
};
class foreigncenter
{
public:
	string name;
	foreigncenter(string name)
	{
		this->name = name;
	}
	void myattack()
	{
		cout << name << "外籍中锋进攻" << endl;
	}
	void mydefence()
	{
		cout << name << "外籍中锋防守" << endl;
	}
};
class translator :public player
{
private:
	foreigncenter *fc; //次处是关联关系，在我的地盘，建别的对象的指针，指向别人对象的成员函数
public:
	translator(string name) :player(name)//基类和派生类进行赋值的时候使用：参数化表达式进行赋值
	{
		fc = new foreigncenter(name);
	}
	void attack()
	{
		fc->myattack();
	}
	void defence()
	{
		fc->mydefence();
	}
};
int main()
{
	player *p1 = new center("李俊宏");
	p1->attack();
	p1->defence();

	translator*t1 = new translator("姚明");
	t1->attack();
	t1->defence();

	return 0;
}










