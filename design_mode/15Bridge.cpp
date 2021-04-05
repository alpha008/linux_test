//将抽象化与实例化拖耦，使得两者可以独立变化
#include<iostream>
#include<string>
using namespace std;
class handsetsoft
{
public:
	virtual void run() = 0;
};
class handsetgame :public handsetsoft
{
public:
	void run()
	{
		cout << "运行手机游戏" << endl;
	}
};
class handsetaddresslist :public handsetsoft
{
public:
	void run()
	{
		cout << "运行手机通讯录" << endl;
	}
};
class handsetbrand
{
protected:
	handsetsoft*soft;
public:
	void sethandsetsoft(handsetsoft*soft)
	{
		this->soft = soft;
	}
	virtual void run() = 0;
};
class handsetbrandn :public handsetbrand
{
public:
	void run()
	{
		soft->run();
	}
};
class hansetbrandm :public handsetbrand
{
public:
	void run()
	{
		soft->run();
	}
};
int main()
{
	handsetbrand *hb;
	hb = new hansetbrandm();
	hb->sethandsetsoft(new handsetgame);//对象注入技术
	hb->run();
	hb->sethandsetsoft(new handsetaddresslist);
	hb->run();
	return 0;
}