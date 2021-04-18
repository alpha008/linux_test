/************************************************************
访问者模式可以将数据结构封装起来 操作这些数据的函数类
改变操作这些数据的函数，即添加新的类别
不用改变其中的数据结构。
 
把数据结构和作用于数据结构上的操作进行解耦合
适用于数据结构比较稳定的场合
总结：  访问者模式有点是增加新的操作很容易，因为增加新的操作就意味着增加一个新的访问者
访问者模式将有关的行为集中到一个访问者对象中
	那访问者模式的缺点是增加新的数据结构变得困难了
*************************************************************/
#include<iostream>
#include<string>
#include<list>
using namespace std;
class person
{
public:
	char *action;
	virtual void getconclusion()
	{}
};
class man :public person
{
public:
	void getconclusion()
	{
		if (action == "成功")
		{
			cout << "男人成功时，背后多半有一个伟大的女人"<< endl;
		}
		else if (action=="恋爱")
		{
			cout << "男人恋爱时，凡是不懂装懂" << endl;
		}
	}
};
class women :public person
{
public:
	void getconclusion()
	{
		if (action == "成功")
		{
			cout << "女人成功时，背后多半有个失败的男人" << endl;
		}
		else if (action=="恋爱")
		{
			cout << "女人恋爱时，遇到事懂也装不懂" << endl;
		}

	}
};
int  main()
{
	list<person *>persons;
	person*man1 = new man();
	man1->action = "成功";
	persons.push_back(man1);

	person*woman1 = new women();
	woman1->action = "成功";
	persons.push_back(woman1);

	person*man2 = new man();
	man2->action = "恋爱";
	persons.push_back(man2);

	person *women2 = new women();
	women2->action = "恋爱";
	persons.push_back(women2);

	list<person*>::iterator iter = persons.begin();
	while (iter != persons.end())
	{
		(*iter)->getconclusion();//容器中放的是指向男人或者女人的指针
		++iter;//通过遍历容器从而遍历指针指向子类函数实现不同的功能
	}
	return 0;
}