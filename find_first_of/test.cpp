#include "str2char.h"

int main() {
	/*
	string input_data;
	cout << "Please type some string: ";
	cin >> input_data;
	cout << "input_data: " << input_data << endl;
	*/
	string input_data = "  afsdsf 123214324 fdsfds 4324";
	str2char convert_data;
	string char_only = convert_data.onlygetchar(input_data);
	string num_only = convert_data.onlygetnum(input_data);

	cout << "char_only: " << char_only << endl;
	cout << "num_only: " << num_only << endl;
	return 0;
}
