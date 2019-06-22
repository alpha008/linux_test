#include<vector>
#include<iostream>
using namespace std;
void PrintVector(vector<int> vec)
{
	for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		static std::size_t i = 0;
		cout << *iter << " ";
		i++;
	}
	cout << endl;
}
/*
assign函数原型及功能：
void assign(const_iterator first,const_iterator last); //功能：将区间[first,last)的元素赋值到当前的vector中，当前vector会清除掉容器中之前的内容。
void assign(size_type n,const T& x = T()); //功能：赋n个值为x的元素到当前vector中，当前vector会清除掉容器中之前的内容。

vec.rbegin()//传回一个vector的最后一个数据的指针。
vec.rend()// 传回一个vector的第一个数据前一个位置的指针。

vec.resize(num)//重新指定vector的长度。
vec.resize(num,value)//重新指定vector的长度。并设定新增的元素的值

vec.swap(vec1)//
swap(vec,vec1)//
<algorithm>中的函数swap()，只是交换两个vector中的内容，其原本的size和capacity均不做改变！
*/

void TestAssign()
{
	vector<int> v1, v2, v3;
    vector<int>::iterator iter;
    for(int i=10; i<60; i+=10)
    {
        v1.push_back(i);
    }
    v2.push_back(1);
    v2.push_back(2);
    cout << "v1 = " ;
	PrintVector(v1);
    cout << "v2 = ";
	PrintVector(v2);
	//将区间[first,last)的元素赋值到当前的vector中，当前vector会清除掉容器中之前的内容。
    v1.assign(v2.begin(), v2.end());
    cout << "v2 = ";
	PrintVector(v1);
    v3=v1;
	//赋n个值为x的元素到当前vector中，当前vector会清除掉容器中之前的内容。
    v3.assign(4,3) ;
    cout << "v3 = ";
	PrintVector(v3);
}
void TestAssign01()
{
	TestAssign();
	vector<int> vec(3, 0);
	PrintVector(vec);

	cout << "size:" << vec.size() << endl;               //返回容器中数据个数
	cout << "capacity:" << vec.capacity() << endl;       //返回容器可用空间的大小
	vec.push_back(1);                    //在尾部加入一个元素
	vec.push_back(2);
	cout << "push back 1 and 2 based on above;vec:" << endl;
	PrintVector(vec);
	vec.pop_back();                      //删除最后一个元素
	cout << "pop ones element based on above;vec:" << endl;
	PrintVector(vec);
	if (vec.empty())                     //判断容器是否为空
	{
		cout << "vec is empty" << endl;
	}
	else
	{
		cout << "vec is not empty" << endl;
	}

	cout << "based on the above:" << endl;
	cout << "vec.front():" << vec.front() << endl;   //取出容器中的第一个元素
	cout << "vec.back():" << vec.back() << endl;     //取出容器中的最后一个元素
	PrintVector(vec);
	cout << "call at(),based on the above:" << endl;
	cout << "vec.at(3):" << vec.at(3) << endl;       //传回索引为index的元素，如果不存在抛出异常
	PrintVector(vec);
	cout << "call clear(),based on the above:" << endl;
	vec.clear();                                     //清空容器
	cout << "call clear() after print" << endl;
	PrintVector(vec);
	for (int i = 1; i<8; i++)
	{
		vec.push_back(i);
	}
	cout << "push_back 1,2,3,4,5,6,7 based on above vec:" << endl;

	vec.erase(vec.begin() + 2);                      //根据迭代器位置来删除元素  
	cout << "call vec.erase(3),vec:" << endl; 
	PrintVector(vec);

	vec.erase(vec.begin() + 1, vec.begin() + 3);     //根据迭代器的区间来删除元素  
	cout << "call vec.erase(1,3),vec:" << endl;
	PrintVector(vec);

}
