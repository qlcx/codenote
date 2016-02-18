//线程在异常环境下的等待
//主要考虑join加入的位置(两种方法try...catch和RALL资源获取即初始化两种方式)
#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

struct func
{
	int& i;
	func(int& i_) : i(i_) {}
	void operator()()
	{
		for(unsigned j=0; j < 100000000;++j)
		{
			//cout << i++ << endl;
		}
		cout << "thread over" << endl;
	}
};

class thread_guard
{
public:
	explicit thread_guard(thread& t_) : t(t_) { }
	~thread_guard() 
	{
		if(t.joinable())	//一旦调用过join后joinable就会返回false
		{
			cout << 222 << endl;
			t.join();
		}
	}
	thread_guard(thread_guard const&)=delete;	//delete禁止由编译器自动提供
	thread_guard operator=(thread_guard const&)=delete;
private:
	thread& t;
};

int main() {
	int some_local_state = 0;
	func my_func(some_local_state);
	thread my_thread(my_func);
	
	/*
	//1、try...catch
	try
	{
		//do_something_in_current_thread();
	}
	catch(...)
	{
		my_thread.join();//保证线程在程序中断前退出
		throw;
	}
	my_thread.join();
	*/
	
	//2、RALL
	//输出：111   222    thread over
	thread_guard g(my_thread);
	usleep(500);
	cout << 111 << endl;
	//get_expection();  //引发异常的函数
	//主函数需要结束或者get_expection引发异常时，都需要先销毁g，触发析构函数
	//t.join()函数执行对子线程函数运行的等待
	
	return 0;
}