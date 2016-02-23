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
		func(data);	//�����ܱ���������
	}
	mutex m;
	some_data data;
};

some_data* unprotected;
data_wrapper x;

void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;	//ȡ���ܱ��������ݵ�����
}

int main()
{
	x.data.a = 0;
	x.process_data(malicious_function); 
	cout << "protected data: " << x.data.a << endl;		//0
	//��Ҫ�����ܱ��������ݵ�ָ������ô��ݵ����ķ�Χ֮�⣬
	//������ͨ���Ӻ����з������ǡ����������ⲿ�ɼ����ڴ��У�
	//������Ϊ�������ݸ��û��ṩ�ĺ���
	unprotected->do_something();	//�޸��ܱ���������
	return 0;
}