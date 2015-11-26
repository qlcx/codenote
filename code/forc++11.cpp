#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	string str = "hello, world";
	for(auto ch : str)
	{
		cout << ch << endl; 
	}
	
	vector<string> str_vec = {"i", "like", "google"};
	for(auto& it : str_vec)
	{
		it = "c++";
	}
	
	cout << "str_vec: " << endl;
	for(auto it = str_vec.begin(); it != str_vec.end(); ++it)
	{
		cout << *it << endl;	//c++ c++ c++
	}
	
	int ia[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	size_t cnt = 0;
	for(const auto &row : ia)
		for(auto col : row)
			cout << col << endl;// 0~11
	return 0;
}

