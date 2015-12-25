#include "str2char.h"

str2char::str2char() {};
str2char::~str2char() {};

//保留英文字符
string str2char::onlygetchar(const string &c_str)
{
	string out_data;
	for(int pos = 0; (pos = c_str.find_first_of(s_alphabet, pos)) != string::npos; ++pos) {
		out_data += c_str[pos];		
	}
	return out_data;
}

//保留数字
string str2char::onlygetnum(const string &c_str)
{
	string out_data;
	for(int pos = 0; (pos = c_str.find_first_of(s_numbers, pos)) != string::npos; ++pos ) {
		out_data += c_str[pos];
	}
	return out_data;
}
