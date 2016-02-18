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
		for(unsigned j=0; j<1000000;++j)
		{
			cout << i++ << endl;
		}
	}
};

int main() {
	int some_local_state = 0;
	//func my_func(some_local_state);
	//thread my_thread(my_func);
	thread my_thread(
		[some_local_state]
		{
			for(unsigned j=0; j<1000000;++j)
			{
				cout << some_local_state << endl;
			}
		}
	);
	my_thread.detach();
	sleep(2);
	return 0;
}