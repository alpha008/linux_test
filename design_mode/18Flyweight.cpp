#include<iostream>
#include<string>
#include<list>
#include<map>
using namespace std;
class website
{
public:
	virtual void use() = 0;
};
class concretewebsite :public website
{
private:
	string name;
public:
	concretewebsite(string name)
	{
		this->name = name;
	}
	void use()
	{
		cout << "网站分类" << name << endl;
	}
};
class websitefactory
{
private:
	map<string, website*>wf;
public:
	website *getwebsitecategory(string key)
	{
		if (wf.find(key) == wf.end())
		{
			wf[key] = new concretewebsite(key);
		}
		return wf[key];
	}
	int getwebsitecount()
	{
		return wf.size();
	}
};
int main()
{
	websitefactory *wf = new websitefactory();

	website *fx = wf->getwebsitecategory("good");
	fx->use();
	website*fy = wf->getwebsitecategory("产品展示");
	fy->use();
	website*fz = wf->getwebsitecategory("产品展示");
	fz->use();
	website *f1 = wf->getwebsitecategory("博客");
	f1->use();
	website *f2 = wf->getwebsitecategory("博客");
	f2->use();
	cout << wf->getwebsitecount()<< endl;
	return 0;
}