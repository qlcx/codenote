#include <iostream>
#include <string>
#include <mutex>

using namespace std;

class some_data
{
public:
	void do_something();
	int a;
	string b;
};

void some_data::do_something()
{
	cout << "unprotected data: " << ++a << endl;		//1
}

class data_wrapper
{
public:
	template<typename F>
	void process_data(F func)
	{
		lock_guard<mutex> guard(m);
		func(data);	//传递受保护的数据
	}
	mutex m;
	some_data data;
};

some_data* unprotected;
data_wrapper x;

void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;	//取得受保护的数据的引用
}

int main()
{
	x.data.a = 0;
	x.process_data(malicious_function); 
	cout << "protected data: " << x.data.a << endl;		//0
	//不要将对受保护的数据的指针或引用传递到锁的范围之外，
	//无论是通过从函数中返回它们、将其存放在外部可见的内存中，
	//还是作为参数传递给用户提供的函数
	unprotected->do_something();	//修改受保护的数据
	return 0;
}