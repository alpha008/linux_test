#include <iostream>
#include <string>
using namespace std;
class Work;
class State;
class ForenonnState;
class State
{
public:
	virtual void writeProgram(Work*) = 0;//准柜台的基类，抽象类
};
class Work   //实施工作的类，根据状态执行不同的操作
{
public:
	int hour;
	State *current;
	Work();
	void writeProgram()
	{
		current->writeProgram(this);
	}
};
class EveningState :public State  //晚上状态
{
public:
	void writeProgram(Work *w)
	{
		cout << "当前时间: " << w->hour << "心情很好，在看《明朝那些事儿》，收获很大！" << endl;
	}
};
class AfternoonState :public State //中午状态
{
public:
	void writeProgram(Work *w)
	{
		if (w->hour < 19)
		{
			cout << "当前时间: " << w->hour << "下午午睡后，工作还是精神百倍!" << endl;
		}
		else
		{
			w->current = new EveningState();
			w->writeProgram();
		}
	}
};
class ForenonnState :public State
{
public:
	void writeProgram(Work *w)
	{
		if (w->hour < 12)
		{
			cout << "当前时间: " << w->hour << "上午工作精神百倍!" << endl;
		}
		else
		{
			w->current = new AfternoonState();
			w->writeProgram();
		}
	}
};
Work::Work()
{
	current = new ForenonnState();
}
int main()
{
	Work *w = new Work();
	w->hour = 21;
	w->writeProgram();
	return 0;
}