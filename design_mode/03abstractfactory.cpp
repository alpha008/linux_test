/*********************************************************************************
抽象工厂就是有弄出一个抽象工厂类，先去实例化不同的工厂，每个工厂都可以创建很对产品
在创造产品的时候，返回一个指针指向产品对象，这个指针是抽象产品类指针
产品也弄出一个抽象类在其中定义接口，去实现不同的产品

*********************************************************************************/
#include<iostream>
#include<string>
using namespace std;
class iuser  //设置用户类，有两个子类
{
public:
	virtual void getuser() = 0;
	virtual void setuser() = 0;
};
class sqluser :public iuser
{
public:
	void getuser()
	{
		cout << "在SQL中返回user" << endl;
	}
	void setuser()
	{
		cout << "在SQL中设置user" << endl;
	}
};
class accessuser :public iuser
{
public:
	void getuser()
	{
		cout << "在ACESS中返回user" << endl;
	}
	void setuser()
	{
		cout << "在ACESS中设置user" << endl;
	}
};
class idepartment
{
public:
	virtual void getdepartment() = 0;
	virtual void setdepartment() = 0;
};
class sqldepartment :public idepartment
{
public:
	void getdepartment()
	{
		cout << "在sql中返回department" << endl;
	}
	void setdepartment()
	{
		cout << "在sql中设置department" << endl;
	}
};
class accessdepartment :public idepartment
{
public:
	void getdepartment()
	{
		cout << "在acess中返回department" << endl;
	}
	void setdepartment()
	{
		cout << "在acess中设置department" << endl;
	}
};
class ifactory
{
public:
	virtual iuser *createuser() = 0;
	virtual idepartment *createdepartment() = 0;
};
class sqlfactory :public ifactory
{
public:
	iuser* createuser()
	{
		return new sqluser;
	}
	idepartment *createdepartment()
	{
		return new sqldepartment;
	}
};
class accessfactory :public ifactory
{
public:
	iuser*createuser()
	{
		return new accessuser;
	}
	idepartment *createdepartment()
	{
		return new accessdepartment();
	}
};
class dataaccess
{
private:
	static string db;//静态成员函数，在类内生命，在类外进行定义
public:
	static iuser *createuser()
	{
		if (db == "acess")
		{
			return new accessuser;
		}
		else if (db == "sql")
		{
			return new sqluser();
		}
	}
	static idepartment*createdepartment()
	{
		if (db == "access")
		{
			return new accessdepartment;
		}
		else if (db == "sql")
		{
			return new sqldepartment;
		}
	}
};
string dataaccess::db = "sql";
int main()
{
	ifactory *factory;
	iuser *user;
	idepartment *department;

	factory = new accessfactory;//创建一个工厂
	user = factory->createuser(); //调用工厂中创建产品对象的函数，返回一个产品对象
	department = factory->createdepartment();//调用工厂中创建产品对象的函数，返回一个产品对象

	user->getuser();
	user->setuser();
	department->getdepartment();
	department->setdepartment(); //以上都来自acess工厂
	//此处使用到了类中定义的静态成员函数，静态成员函数只要使用类作用域运算符即可调用成功
	//在工厂中定义成员函数创建对象的时候，成员函数的返回值是一个抽象产品类型的指针
	//这样就把一个具体产品给传出来了，这是一个传出参数。
	//传入传出参数是，值传递，地址传递。
	user = dataaccess::createuser();
	department = dataaccess::createdepartment();
	user->getuser();
	user->setuser();
	department->getdepartment();
	department->setdepartment();
	return 0;
}