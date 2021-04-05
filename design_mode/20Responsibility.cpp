//责任链模式：在责任链模式中，很多对象由每一个对象对其下家的引用而连接起来形成
//一条链，请求在这个链上进行传递，直到链上的某一个对象处理此请求。
//客户端并不知道哪一个对象最终处理这个请求，系统可以在不影响客户端的情况下
//重新组织链和分配责任。处理者有两个选择：承担责任或者把责任推给下家，一个请求可以不被任何接收端对象所接受
#include<iostream>
#include<string>
using	namespace std;
class Request //请求类中存放请求的信息
{
public:
	string requestype;
	string requestcontent;
	int number;
};
class manager  //设置经理名字
{
protected:
	string name;
	manager *superior; 
public:
	manager(string name)
	{
		this->name = name;
	}
	void setsuperior(manager *superior)//通过指针进行对象传递
	{								   //对象注入技术
		this->superior = superior;
	}
	virtual void requestapplications(Request*request) = 0; //虚函数预留接口
};
class commonmanager :public manager//普通经理
{
public:
	commonmanager(string name) :manager(name)
	{}
	void requestapplications(Request *request) //虚函数多态继承实现
	{
		if (request->requestype == "请假"&&request->number <= 2)
		{
			cout << name << "" << request->requestcontent << "数量：" << request->number << "请批准" << endl;
		}
		else
		{
			if (superior != NULL)
			{
				superior->requestapplications(request);
			}
		}
	}
};
class majordomo :public manager  //总监去处理
{
public:
	majordomo(string name) :manager(name)
	{}
	void requestapplications(Request *request)
	{
		if (request->requestype == "请假" && request->number <= 5)
		{
			cout << name << " " << request->requestcontent << " 数量: " << request->number << "被批准" << endl;
		}
		else
		{
			if (superior != NULL)
			{
				superior->requestapplications(request);
			}
		}
	}
};

class generalmanager :public manager // 最终老板去处理
{
public:
	generalmanager(string name) :manager(name)
	{}
	void requestapplications(Request*request)
	{
		if (request->requestype == "请假")
		{
			cout << name << "" << request->requestcontent << "数量:" << request->number << "被批准" << endl;
		}
	}
};
int main()
{
	commonmanager *jinli = new commonmanager("经理");
	majordomo *zongjian = new majordomo("总监");
	generalmanager *zhongjingli = new generalmanager("总经理");

	jinli->setsuperior(zongjian);
	zongjian->setsuperior(zhongjingli);

	Request *request = new Request();

	request->requestype = "请假";
	request->requestcontent = "李俊宏请假";
	request->number = 1;
	jinli->requestapplications(request); //经理去处理

	request->requestype = "请假";
	request->requestcontent = "李俊宏请假";
	request->number = 4;
	jinli->requestapplications(request); 


	request->requestype = "请假";
	request->requestcontent = "李俊宏请假";
	request->number = 10;
	jinli->requestapplications(request);
	return 0;
}