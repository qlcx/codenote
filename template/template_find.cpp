#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

namespace findstr {
	template<typename Iterator, typename Value> 
	auto find(Iterator first, Iterator end, Value const& value) 
	{
		for(; first != end && *first != value; ++first);
		return first;
	}
}

int main() {
    vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto is_in_vector = v.cend() != findstr::find(v.cbegin(), v.cend(), 5);
    cout << (is_in_vector ? "found\n" : "not found\n") << endl;

    list<std::string> l = { "aa", "bb", "cc", "dd", "ee", "ff", "gg" };
    auto is_in_list = l.cend() != findstr::find(l.cbegin(), l.cend(), "zz");
    cout << (is_in_list ? "found\n" : "not found\n") << endl;
	return 0;
}