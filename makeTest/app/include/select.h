#include <stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
void TestSwitch()
{
	int a = 0;
	int b = 17;
	cin >> a;
	switch (a)
	{
		case 0:
		{
			int b = 0;  
			cout << b << endl; 
			break;
		}
		/*此处加上括号来限制分支内的作用域是十分有必要的,，如果不加大括号进行限制，那么就会出现
		局部变量的初始化操作由于case标签而跳过，不过要注意，一旦加上了大括号，在case 0后面便不能访问到变量b了。*/
		case 1:
		{
			cout << 1 << endl;
			break;
		}
		case 2:
		{
			cout << 2 << endl;
			break;
		}
		case 3:		
		{
			cout << 3 << endl;
			break;
		}
		case 4:		
		{
			cout << 4 << endl;
			break;
		}
		case 5:		
		{
			cout << 5 << endl;
			break;
		}
		default:
			cout << "不符合标准" << endl;
	}
}



