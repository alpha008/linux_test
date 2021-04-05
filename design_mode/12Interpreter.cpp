#include<iostream>
#include<string>
#include<list>
using namespace std;
class Context;
class abstractexpression  //抽象类（纯虚函数） 提供接口的功能
{
public:
	virtual void interpret(Context *) = 0;
};
class terminalexpression :public abstractexpression
{
public:
	void interpret(Context *context)
	{
		cout << "终端解释器" << endl;
	}
};
class nonterminalexpression :public abstractexpression
{
public:
	void interpret(Context*context)
	{
		cout << "非终端解释器" << endl;
	}
};
class Context
{
public:
	 string input, output;
};
int main()
{
	Context *context = new Context;
	list<abstractexpression*>it;
	it.push_back(new terminalexpression);
	it.push_back(new nonterminalexpression);
	it.push_back(new terminalexpression);
	it.push_back(new terminalexpression);
	for (list<abstractexpression*>::iterator iter = it.begin(); iter != it.end(); iter++)
	{
		(*iter)->interpret(context);//这里的context是指针传递
	}
	return 0;
}