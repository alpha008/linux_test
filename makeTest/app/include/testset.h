#include <iostream>
#include <set>
using namespace std;
struct People
{
	People(string name,int age)
	{
		this->name = name;
		this->age = age;
	}
	bool operator <(const People p) const  //运算符重载   
	{
		return age < p.age;       //按照年龄由小到大进行排序   
	}
public:
	string name;
	int age;
};
void TestInsertWithCompare()
{
	set<People>s;
	People people1("张三",14);
	People people2("李四", 15);
	People people3("王二麻子", 16);
	s.insert(people1);
	s.insert(people2);
	s.insert(people3);
	set<People>::iterator it;
	for (it = s.begin(); it != s.end(); it++)  //使用迭代器进行遍历   
	{
		printf("姓名：%s 年龄：%d\n", (*it).name.c_str(), (*it).age);  //转换成c语言的字符串
	}
}
void PrintVector(set<int> s)
{
	for (set<int>::iterator it = s.begin(); it != s.end(); it++)  //使用迭代器进行遍历   
	{
		cout << *it << " ";
	}
	cout << endl;
}
void PrintVectorAuto(set<int> s)
{
	for (auto i : s)               //自动推导遍历
	{
		cout << i << " ";
	}
}
/*****************************************************************************************
	测试insert函数，返回值为pair<set<int>::iterator, bool>
*****************************************************************************************/
void TestInsert()
{
	cout << "TestInsert" << endl;
	int a[] = { 1, 2, 3 };
	set<int> s;
	set<int>::iterator iter;
	s.insert(a, a + 3);
	for (iter = s.begin(); iter != s.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;
	pair<set<int>::iterator, bool> pr;
	pr = s.insert(5);
	if (pr.second)
	{
		cout << *pr.first << endl;
	}
}
/*****************************************************************************************
lower_bound(key_value) ，返回第一个大于等于key_value的定位器
upper_bound(key_value)，返回最后一个大于等于key_value的定位器
*****************************************************************************************/
void TestLowUpperBound()
{
	cout << "TestLowUpperBound" << endl;
	set<int> s;
	s.insert(1);
	s.insert(3);
	s.insert(4);
	cout << *s.lower_bound(2) << endl;
	cout << *s.lower_bound(3) << endl;
	cout << *s.upper_bound(3) << endl;
}
void TestVector()
{
	set<int> s;
	for (int i = 1; i <= 10; ++i)
	{
		s.insert(i);           //插入元素
	}
	PrintVector(s);
	cout << "set 的 size 值为 ：" << s.size() << endl;        //求集合所含值的大小
	cout << "set 的 maxsize的值为 ：" << s.max_size() << endl;//返回set容器可能包含的元素最大个数
	cout << "set 中 1 出现的次数是 ：" << s.count(1) << endl; //求集合中1出现的次数
	/*
	返回一对定位器，分别表示第一个大于或等于给定关键值的元素和 第一个大于给定关键值的元素，
	这个返回值是一个pair类型，如果这一对定位器中哪个返回失败，就会等于end()的值，会抛出异常
	*/
	pair<set<int>::const_iterator, set<int>::const_iterator> pr;
	pr = s.equal_range(3);
	cout << "第一个大于等于 3 的数是 ：" << *pr.first << endl;
	cout << "第一个大于 3的数是 ： " << *pr.second << endl;
	//第一种删除,删除首位置
	s.erase(s.begin());
	cout << "第一种删除,删除首位置" << endl;
	PrintVector(s);
	//第二种删除，删除首尾区间内的元素
	cout << "第二种删除，删除首尾区间内的元素" << endl;
	s.erase(s.begin(), s.end());
	PrintVector(s);
	for (int i = 1; i <= 10; ++i)
	{
		s.insert(i);           //插入元素
	}
	//第三种删除，指定删除的内容
	cout << "第三种删除，指定删除的内容" << endl;
	s.erase(8);
	PrintVector(s);
	set<int>::iterator iter ;
	if ((iter = s.find(2)) != s.end())      //查找到值为2，返回迭代器位置
	{
		cout << *iter << endl;
	}
	s.clear();                                                //清空集合中的元素
	if (s.empty())                                            //判断集合是否为空
	{
		cout << "set 为空 ！！！" << endl;
	}
	TestInsert();
	TestLowUpperBound();
	TestInsertWithCompare();
	system("pause");

}

