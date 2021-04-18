//原型模式允许动态的增加或者减少产品类，
//通过一个原型对象指明所要创建的对象的类型
//然后复制这个模型对象的方法创建出更多同类型的对象
/*************************************************************
原型模式允许动态的增减减少产品类，缺点是每个类都要配备一个克隆方法
通过一个给定的原型对象， 然后复制这个对象的方法创建出更多同类型的对象
***************************************************************/
#include<iostream>
#include<string>
using namespace std;
class resume
{
private:
	string name, sex, age, timearea, company;
public:
	resume(string s)
	{
		name = s;
	}
	void setpersonalinfo(string s, string a)
	{
		sex = s;
		age = a;
	}
	void setworkexperience(string t, string c)
	{
		timearea = t;
		company = c;
	}
	void display()
	{
		cout << name << " " << sex << " "<<age << endl;
		cout << "工作经历： " << timearea << "" << company << endl << endl;
	}
	resume *clone()
	{
		resume*b = new resume(name);
		b->setpersonalinfo(sex, age);
		b->setworkexperience(timearea,company);
		return b;
	}
};
int  main()
{
	resume *r = new resume("李彦宏");
	r->setpersonalinfo("男", "30");
	r->setworkexperience("2007-2010","读研究生");
	r->display();

	resume *r2 = r->clone();
	r2->setpersonalinfo("男","50");
	r2->setworkexperience("2003-2007", "读本科");
	r2->display();
	return 0;
}