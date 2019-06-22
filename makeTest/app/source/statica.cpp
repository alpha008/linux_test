#include <iostream>
#include "teststatic.h"
using namespace std;
namespace static_ {

	static size_t count_calls()
	{
		// 局部静态对象(local static object)在程序的执行路径第一次经过对象定义
		// 语句时初始化,并且直到程序终止才被销毁，在此期间即使对象所在的函数结
		// 束执行也不会对它有影响。
		static size_t ctr = 0; // 调用结束后，这个值仍然有效
		return ++ctr;
	}
	int test_static_1()
	{
		for (int i = 0; i < 10; ++i) {
			fprintf(stdout, "ctr: %d\n", count_calls());
		}

		return 0;
	}
	/////////////////////////////////////////////////////////////
	int A::val = 10;             //int val2 = 5;
	int A::val3 = 15;            //静态成员变量必须在类外初始化
	int A::func() //静态成员函数                     
	{
		return ++val3;
	}
	int A::func2()//非静态成员函数    
	{
		return (val3 + val2 + func());
	}
	int test_static_2()
	{
		fprintf(stdout, "static A::val: %d\n", A::val);
		for (int i = 0; i < 5; ++i)
			fprintf(stdout, "static A::func:val3 = %d\n", A::func());

		A a;
		fprintf(stdout, "a.func2: val3 + val2 + func() =  %d\n", a.func2());

		return 0;
	}
	////////////////////////////////////////////////////////////////
	static int xx = 5;
	int test_static_3()
	{
		fprintf(stdout, "xx: %d\n", xx);
		return 0;
	}
	int X::si = 77; // Initialize static data member
	int test_static_4()
	{
		X xobj;
		xobj.set_i(11);
		xobj.print_i();
		// static data members and functions belong to the class and
		// can be accessed without using an object of class X
		X::print_si();
		X::set_si(22);
		X::print_si();
		return 0;
	}
	void C::printall() {
		std::cout << "Here is j: " << this->j << std::endl;
		// You can call a static member function using the this pointer of a nonstatic member function
		this->f();
	}
	int C::i = 3;
	int test_static_5()
	{
		C obj_C(2);
		obj_C.printall();
		return 0;
	}
	void showstat(int curr)
	{
		static int nStatic; // Value of nStatic is retained between each function call
		nStatic += curr;
		std::cout << "nStatic is " << nStatic << std::endl;
	}
	int test_static_6()
	{
		for (int i = 0; i < 5; i++)
			showstat(i);
		return 0;
	}
	Singleton::Singleton()
	{
		std::cout << "constructor Singleton ..." << std::endl;
	}

	Singleton& Singleton::Instance()
	{
		static Singleton _instance;
		return _instance;
	}
	int test_static_7()
	{
		Singleton& sgn1 = Singleton::Instance();
		Singleton& sgn2 = Singleton::Instance();
		if (&sgn1 == &sgn2) std::cout << "ok" << std::endl;
		else std::cout << "no" << std::endl;
		return 0;
	}
} 
void TestStatic()
{
	//1.局部静态变量的声明周期伴随程序开始到结束
	//static_::test_static_1();
	//static_::test_static_1();
	/*2.静态类成员变量需要在类外初始化
		静态成员函数  静态成员变量   不可以调用非静态成员函数
		非静态成员函数可以调用静态成员函数*/
	//static_::test_static_2();
	//3.命名空间   不同文件内的static同名变量
	//cout << xx << endl;
	//static_::test_static_3();
	//4.静态成员变量无this指针    在类内声明   类外初始化
	//static_::test_static_4();
	//5.通过非静态成员函数，间接使用this指针去调用静态成员函数
	//static_::test_static_5();
	//6.局部静态变量在每次调用期间都是存在的
	//static_::test_static_6();
	//7.类的静态成员为所有对象共有   只初始化一次
	static_::test_static_7();
}
