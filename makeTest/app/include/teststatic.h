#ifndef FBC_CPP_BASE_TEST_STATIC_HPP_
#define FBC_CPP_BASE_TEST_STATIC_HPP_
#include <iostream>
/************************************************************************************************
1. 函数内static局部变量：变量在程序初始化时被分配，直到程序退出前才被释放，也就是static是按照程序的生命周期来分配释放变量的，
	而不是变量自己的生命周期。多次调用，仅需一次初始化。
2. cpp内的static全局变量：只在cpp内有效。在不同的cpp文件中定义同名变量，不必担心命名冲突。保持变量内容的持久。
3. 头文件内的static全局变量：在每个包含该头文件的cpp文件中都是独立的。不推荐使用。
4. static函数：仅在当前文件内有效。在不同的cpp文件中定义同名函数，不必担心命名冲突。对其它源文件隐藏。在现代C++中被无名namespace取代。
5. 类的static数据成员：必须在class的外部初始化。
6. 类的static函数：不能访问类的私有成员，只能访问类的static成员，不需要类的实例即可调用。可以继承和覆盖，但无法是虚函数。属于整个类而非类的对象，没有this指针。
	静态成员之间可以相互访问，包括静态成员函数访问静态数据成员和访问静态成员函数。
	非静态成员函数可以任意地访问静态成员函数和静态数据成员。静态成员函数不能访问非静态成员函数和非静态数据成员。
7. 单例模式(Singleton)中使用static：保证一个类仅有一个实例，并提供一个访问它的全局访问点。
************************************************************************************************/
static int xx = 3;
namespace static_ {
	
	class A {
	public:
		static int func(); // 只能调用静态成员
		int func2();

	public:
		static int val;
	private:
		int val2 = 5;
		static int val3; // 必须在类外进行初始化
	};

	struct X {
	private:
		int i;
		static int si;
	public:
		void set_i(int arg) { i = arg; }
		static void set_si(int arg) { si = arg; }
		void print_i() {
			std::cout << "Value of i = " << i << std::endl;
			std::cout << "Again, value of i = " << this->i << std::endl;
		}
		static void print_si() {
			std::cout << "Value of si = " << si << std::endl;
			// A static member function does not have a this pointer
			//std::cout << "Again, value of si = " << this->si << std::endl; // error
		}
	};

	class C {
		// A static member function cannot be declared with the keywords virtual, const, volatile, or const volatile.
		// A static member function can access only the names of static members, enumerators, and nested types of the class in which it is declared.
		static void f() {
			std::cout << "Here is i: " << i << std::endl;
		}
		static int i;
		int j;
	public:
		C(int firstj) : j(firstj) { }
		void printall();
	};

	class Singleton {
	public:
		static Singleton& Instance();
	private:
		Singleton(); // Singleton不可以被实例化，因此将其构造函数声明为protected或者直接声明为private
	};
	/*
	int test_static_1();
	int test_static_2();
	int test_static_3();
	int test_static_4();
	int test_static_5();
	int test_static_6();
	int test_static_7();
	*/
} // namespace static_
#endif

