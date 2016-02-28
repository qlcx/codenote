#include <iostream>
using namespace std;
//mutable关键字 被mutable修饰的变量将永远处于可变状态，即使在一个const函数中

class Clx
{
public:
	Clx(int i) : data(i) {}
	~Clx() {}
	void output() const
	{
		cout << ++data << endl;
	}
private:
	mutable int data;
};

int main()
{
	Clx lx(1);
	lx.output();
	return 0;
}

