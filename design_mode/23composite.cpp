#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Component
{
public:
	string name;
	Component(string name)
	{
		this->name = name;
	}
	virtual void add(Component *) = 0;
	virtual void remove(Component *) = 0;
	virtual void display(int) = 0;
};
class Leaf :public Component
{
public:
	Leaf(string name) :Component(name)
	{}
	void add(Component *c)
	{
		cout << "leaf cannot add" << endl;
	}
	void remove(Component *c)
	{
		cout << "leaf cannot remove" << endl;
	}
	void display(int depth)
	{
		string str(depth, '-');
		str += name;
		cout << str << endl;
	}
};
class Composite :public Component
{
private:
	vector<Component*> component;
public:
	Composite(string name) :Component(name)
	{}
	void add(Component *c)
	{
		component.push_back(c);
	}
	void remove(Component *c)
	{
		vector<Component*>::iterator iter = component.begin();
		while (iter != component.end())
		{
			if (*iter == c)
			{
				component.erase(iter);
			}
			iter++;
		}
	}
	void display(int depth)
	{
		string str(depth, '-');//这个我喜欢，来几个，有几层就把里面放几个-，非常好
		str += name;
		cout << str << endl;

		vector<Component*>::iterator iter = component.begin();
		while (iter != component.end())  //就是在这里形成了广度搜索遍历
		{
			(*iter)->display(depth + 1);
			iter++;
		}
	}
};
int main()
{
	Component *p = new Composite("小李");
	p->add(new Leaf("小王"));
	p->add(new Leaf("小强"));

	Component *sub = new Composite("小虎");
	sub->add(new Leaf("小王"));
	sub->add(new Leaf("小明"));
	sub->add(new Leaf("小柳"));

	p->add(sub);
	p->display(0);

	cout << "*******" << endl;
	sub->display(2);
	return 0;
}
