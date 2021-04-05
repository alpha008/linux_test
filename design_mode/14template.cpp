//模板模式将定义模版将实现函数由其子类去实现完成
#include<iostream>
#include<string>
#include<vector>
using namespace std; 
class abstractclass
{
public:
	void show()
	{
		cout << "我是" <<getname()<< endl;
	}
protected:
	virtual string getname() = 0;
};
class naruto :public abstractclass
{
protected:
	virtual string getname()
	{
		return "火影";
	}
};
class onpice :public abstractclass
{
protected:
	virtual string getname()
	{
		return "压缩";
	}
};
int main()
{
	naruto *man = new naruto;
	man->show();
	onpice *man2 = new onpice;
	man2->show();
	return 0;
}