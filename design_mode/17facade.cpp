//外部与一个子系统进行通信必须通过一个统一的门面对象进行，
//每一个子系统都只有一个门面类，而且此门面类只有一个实例
//也就说它是一个单例模式，但是整个系统可以有多个门面类。就是说子系统的门面类上一层只有一个门面。
#include<iostream>
#include<string>
using namespace std;
class sub1
{
public:
	void f1()
	{
		cout << "子系统的方法1" << endl;
	}
};
class sub2
{
public:
	void f2()
	{
		cout << "子系统的方法2" << endl;
	}
};
class sub3
{
public:
	void f3()
	{
		cout << "子系统的方法3" << endl;
	}
};
class facade  //子系统在门面中是私有的。
{
private:
	sub1*s1;
	sub2*s2;
	sub3*s3;
public:
	facade()
	{
		s1 = new sub1();
		s2 = new sub2();
		s3 = new sub3();
	}
	void method()
	{
		s1->f1();
		s2->f2();
		s3->f3();
	}

};
int  main()
{
	facade*f = new facade;
	f->method();
	return 0;
}