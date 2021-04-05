#include<iostream>
#include<cmath>
#include<string>
using namespace std;
class cashsuper
{
public: //定义一个抽象类，预留接口在继承的时候实现不同的功能
	virtual double acceptmoney(double money) = 0;
};
class cashnomal :public cashsuper
{
public:
	double acceptmoney(double money)
	{
		return money;
	}
};
class cashrebat :public cashsuper
{
private:
	double discount;
public:
	cashrebat(double dis)
	{
		discount = dis;
	}
	double acceptmoney(double money)
	{
		return money*discount;
	}
};
class cashreturn :public cashsuper
{
private:
	double moneycondition;
	double moneyreturn;
public:
	cashreturn(double mc, double mr)
	{
		moneycondition = mc;
		moneyreturn = mr;
	}
	double acceptmoney(double money)
	{
		double result = money;
		if (money >= moneycondition)
		{
			return money - floor(money / moneycondition)*moneyreturn;
		}
		return result;
	}
};
class cashcontext
{
private:
	cashsuper *cs;
public:
	cashcontext(string str)
	{
		if (str == "正常收费")
		{
			cs = new cashnomal;
		}
		else if (str == "打9折")
		{
			cs = new cashrebat(0.9);
		}
		else if (str == "满1000送200")
		{
			cs = new cashreturn(1000,200);
		}
	}
	double getresult(double money)
	{
		return cs->acceptmoney(money);
	}            
};	 //定义策略目录，通过创建目录对象传递策略	
	 //在目录对象的成员函数中，实现不同的策略（）    
int main()
{
	double money = 1000;
	cashcontext *cc = new cashcontext("满1000送200"); 
	cout << cc->getresult(money)<<endl; //两层函数的嵌套，实际上操作的是策略中的函数
	return 0;
}