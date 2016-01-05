#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template<typename T, unsigned size>
T* first(T (&arr)[size]) {
	return arr;
}

template<typename T, unsigned size>
T* last(T (&arr)[size]) {
	return arr + size;
}

int main() {

	string s[] = { "first","middle","last" };
    cout << *first(s) << endl;
    cout << *(last(s) - 1) << endl;
	return 0;
}