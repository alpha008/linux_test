#include<iostream>
#include<string>
#include<vector>
using	namespace std;
class Memo  //记录状态的结点
{
public:
	string state;
	Memo(string state)
	{
		this->state = state;
	}
};
class orignator  //存储结点，将结点全部放在一个容器中
{
public:
	string state;
	void setmemo(Memo *memo)
	{
		state = memo->state;
	}
	Memo*creatememo()
	{
		return new Memo(state);
	}
	void show()
	{
		cout << state << endl;
	}
};
class caretaker
{
public:
	vector<Memo*>memo; //使用容器将状态装起来
	void save(Memo * memo)  //保存状态放入容器
	{
		(this->memo).push_back(memo); //this->memo 此处所指的是这个容器对象
	}
	Memo*getstate(int i)  
	{
		return memo[i];
	}
};
int main()
{
	orignator *og = new orignator; //创建一个对象og->对象
	caretaker *ct = new caretaker; //创建一个对象ot->对象
	og->state = "on"; //给成员变量赋值
	og->show(); //显示成员变量
	ct->save(og->creatememo()); //将刚才创建的on状态放进容器存储起来，传递的是一个指针，将指针放进了容器
	
	og->state = "off";
	og->show();
	ct->save(og->creatememo());
	
	og->state = "middle";
	og->show();
	ct->save(og->creatememo());
	
	og->setmemo(ct->getstate(0));
	og->show();

	og->setmemo(ct->getstate(1));
	og->show();

	og->setmemo(ct->getstate(2));
	og->show();

	return 0;
}
