#ifndef STR2CHAR_H
#define STR2CHAR_H

#include <iostream>
#include <string>
using namespace std;

//设置静态变量用来查询数字或者字母
const static string s_numbers("1234567890");
const static string s_alphabet("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

class str2char {
public:
	str2char();
	~str2char();
public:

	//保留英文字符
	string onlygetchar(const string &);

	//保留数字
	string onlygetnum(const string &);

protected:

private:
};

#endif
