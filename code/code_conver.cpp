#include <stdlib.h>
#include <iostream>
#include <iconv.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <locale.h>
using namespace std;

//字符转换
int code_convert(char* from_charset, char* to_charset, char* inbuf, size_t inlen, char* outbuf, size_t outlen)
{
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;
	memset(outbuf,0,outlen);
	if (iconv(cd, pin, (size_t *)&inlen, pout, (size_t *)&outlen)==-1) return -1;
	iconv_close(cd);
	return 0;
}

int main() {
	//转换编码两种方式
	/*
	1.修改文件编码为utf-8，并将数据字符也从utf-8转换到utf-8
	2.文件编码为euc-an，解决字符编码不同导致的字符长度不同，设置一个较大的缓冲区，存放转换后的数据
	*/
	//euc-an编码文件无法将宽字符赋值给wchar_t
	char *astring = "是否就是减肥";
	int len = strlen(astring) + 1;

	char data[len];
	code_convert("utf-8", "utf-8", astring, len, data, len);

	cout << "astring = " << astring << endl;
	cout << "data = " << data << endl;
}
