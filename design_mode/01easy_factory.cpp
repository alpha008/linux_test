#include<iostream>
#include<string>
using namespace std;
class operation //定义基类，在基类中定义数�?
{               //定义函数接口，预留接�?
public:
	double numbera, numberb;
	virtual double getresult() //虚函数是实现设计模式的核�?
	{                          //虚函数在继承的时候不会出现起�?
		return 0;              //虚函数可以在继承的时候，实现接口重写
	}                          //就是说函数名称一样，但是实现功能不一样�?
};
class addopertion :public operation
{
public:
	double getresult()
	{
		return numbera + numberb;
	}
};
class suboperation :public operation
{
public:
	double getresult()
	{
		return numbera - numberb;
	}
};
class muloperation :public operation
{
public:
		double getresult()
	{
		return numbera*numberb;
	}
};
class divoperation :public operation
{
public:
	double getresult()
	{
		return numbera / numberb;
	}
};
class operfactory
{
public:
	static operation *createoperation(char c)
	{
		switch (c)
		{
		case '+':
			return new addopertion;
			break;
		case'-':
			return new suboperation;
			break;
		case'*':
			return new muloperation;
			break;
		case'/':
			return new divoperation;
			break;
		}
	}
};
int main()
{	//使用类的静态成员函数实现工厂创建工厂
	operation *oper1 = operfactory::createoperation('+');
	oper1->numbera = 100;//根据客户需求创建，符合要求的产品
	oper1->numberb = 50;//返回一个基类指针，这个基类指针指向子类
	cout << oper1->getresult() << endl;
	operation *oper2 = operfactory::createoperation('-');
	oper2->numbera = 100;
	oper2->numberb = 50;
	cout << oper2->getresult() << endl;
	operation *oper3 = operfactory::createoperation('*');
	oper3->numbera = 100;
	oper3->numberb = 50;
	cout << oper3->getresult() << endl;
	operation *oper4 = operfactory::createoperation('/');
	oper4->numbera = 100;
	oper4->numberb = 50;
	cout << oper4->getresult() << endl;
	return 0;
}
