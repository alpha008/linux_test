#include<iostream>
#include<string>
using namespace std;
class operation
{
public:
	double numbera, numberb;
	virtual double getresult()
	{
		return 0;
	}
};
class addoperation :public operation
{
	double getresult()
	{
		return numbera + numberb;
	}
};
class suboperation :public operation
{
	double getresult()
	{
		return numbera - numberb;
	}
};
class muloperation :public operation
{
	double getresult()
	{
		return numbera * numberb;
	}
};
class divoperation :public operation
{
	double getresult()
	{
		return numbera / numberb;
	}
};
class factory
{
public:
	virtual operation *createopration() = 0;
};
class addfactory :public factory
{
public:
	static operation *createoperation()
	{
		return new addoperation();
	}
};
class subfactory :public factory
{
public:
	static operation *createoperation()
	{
		return new suboperation();
	}
};
class mulfactory :public factory
{
public:
	static operation *createoperation()
	{
		return new muloperation();
	}
};
class divfactory :public factory
{
public:
	static operation *createoperation()
	{
		return new divoperation();
	}
};
int main()
{	
	operation *oper = addfactory::createoperation();
	oper->numbera = 100;
	oper->numberb = 50;
	cout << oper->getresult() << endl;
	return 0;
}
//总结：
//抽象工厂就是在简单工厂的基础上，将所有的产品的创建不是由单一的某一个工厂创建而是由
//抽象工厂类派生出不同的工厂去实现不同的工厂类，去实现创建不同的产品

//简单工厂：  一个工厂负责很多产品的创建  根据客户需求去创建产品
//特点：一个工厂实现创建很多产品


//工厂方法：  将工厂抽象出来—>将产品的创建去交给不同的工厂去创建  
	        //通过不同的工厂中定义静态成员函数，从而实现调用
//特点：由一个抽象工厂类 派生出很多工厂   但是每个工厂只生产一个对象

//抽象工厂： 将工厂和产品的创建同时抽象出来，从而在一个工厂中可以创建多个产品
		//工厂由抽象类继承   产品由抽象类来继承   
//特点：就是一个工厂中可以创建此系列产品，即可以创建多个对象

//共同点:都使用到了静态成员函数
		