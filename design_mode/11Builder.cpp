#include<iostream>
#include<string>
#include<vector>
using namespace std;
class person
{ 
public: //建造模式将建造过程步骤进行，从而对实现产品的重新组合
	virtual void createhead() = 0;
	virtual void createhand() = 0;
	virtual void createbody() = 0;
	virtual void createfoot() = 0;
};      //建造模式将分步骤进行建造，然后按照将组合的步骤交给一个指挥者进行指挥
		//统一建造，客户端不必知道内部实现过程，交给指挥官去指挥建造。
		//虚函数实现函数接口，在继承的过程中逐步实现不同的功能
        //抽象类提供建造的步骤，派生类中将接口的步骤分步实现
class thinperson :public person
{
	void createhead()
	{
		cout << "thin head" << endl;
	}
	void createhand()
	{
		cout << "thin hand" << endl;
	}
	void createbody()
	{
		cout << "thin body" << endl;
	}
	void createfoot()
	{
		cout << "thin foot" << endl;
	}
};
class fatperson :public person
{
	void createhead()
	{
		cout << "fat head" << endl;
	}
	void createhand()
	{
		cout << "fat hand" << endl;
	}
	void createbody()
	{
		cout << "fat body" << endl;
	}
	void createfoot()
	{
		cout << "fat foot" << endl;
	}
};
class director
{
private:
	person *p;
public:
	director(person*temp)
	{
		p = temp;
	}
	void create()
	{
		p->createhead();
		p->createhand();
		p->createbody();
		p->createfoot();
	}
};
int main()
{
	person *p = new fatperson;
	director *d = new director(p);
	d->create();
	delete d;
	delete p;
	return 0;
}