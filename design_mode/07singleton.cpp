/*****************************************
懒汉式  在定义的时候就已经创建好了
饿汉式  在需要的时候才会创建
****************************************/
#include<iostream>
#include<string>
using namespace std;
class single
{
private:
	single()
	{}
	static single*singel;
public:
	static single*getinstance()
	{
		if (singel == NULL)
		{
			singel = new single();
		}
		return singel;
	}
};
single*single::singel = NULL;
int main()
{
	single *s1 = single::getinstance();
	single *s2 = single::getinstance();//单例模式就是创建对象是唯一的，也就是地址唯一，那么指向此对象的
	if (s1 == s2)					   //指针也是唯一的，那么使用两个指针指向同一个对象的时候就会出现两个
		cout << "ok" << endl;          //两个指针相同的情况
	else
		cout << "erro" << endl;
	return 0;
}