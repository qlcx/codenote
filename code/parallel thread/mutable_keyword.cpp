#include <iostream>
using namespace std;
//mutable�ؼ��� ��mutable���εı�������Զ���ڿɱ�״̬����ʹ��һ��const������

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

