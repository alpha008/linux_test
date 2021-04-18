#include<iostream>
#include<string>
using namespace std;
class schoolgirl
{
public:
	string name;
};
class igivegift
{
public:
	virtual void givedolls() = 0;
	virtual void giveflowers() = 0;
};
class pursuit :public igivegift
{
private:
	schoolgirl mm; //私有的成员变量，通过构造函数传递参数进行赋值
public:
	pursuit(schoolgirl m) //两个对象一模一样可以进行赋值操作
	{
		mm = m;
	}
	void givedolls()
	{
		cout << mm.name <<"送你娃娃"<< endl;
	}
	void giveflowers()
	{
		cout << mm.name << "送你鲜花" << endl;
	}
};
class proxy :public igivegift
{
private:
	pursuit gg;
public:
	proxy(schoolgirl mm) :gg(mm)//类中包含其它对象，使用参数化列表进行赋值
	{}                           
	void givedolls()
	{
		gg.givedolls();
	}
	void giveflowers()
	{
		gg.giveflowers();
	}
};
int main()
{
	schoolgirl lijiaojiao;
	lijiaojiao.name = "李娇娇";
	pursuit zhuojiayi(lijiaojiao);
	proxy daili(lijiaojiao);
	daili.givedolls();
	return 0;
}

//在代理中定义和生命被代理的那个类对象，使用参数化传参数，然后进行操作。
//定义一个抽象类，从这个抽象类中派生出两个 不同的类别
// 一个是代理类（在此类中定义被代理的对象，。并通过对象.成员函数的形式进行调用）  
//一个是被代理类 ，在这个类中定义函数的实现；
//在代理类中调用，被代理类中的实现函数。