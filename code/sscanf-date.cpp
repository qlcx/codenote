#include <string>
#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;

int main() {

	char formname[40];
	memset(formname, 0, sizeof(formname));

	int f1, f2, f3, f4, f5, f6;
	string dustart = "2015-10-20T15:01:01";
	sscanf(dustart.c_str(), "%d-%d-%dT%d:%d:%d", &f1, &f2, &f3, &f4, &f5, &f6);
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f3: " << f3 << endl;
	cout << "f4: " << f4 << endl;
	cout << "f5: " << f5 << endl;
	cout << "f6: " << f6 << endl;

	sprintf(formname, "s_exit%04d%02d%02d, %02d:%02d:%02d", f1, f2, f3, f4, f5, f6);
	cout << "formname: " << formname << endl;
	
	cout << ---------------------------------- << endl;
	
	char buf1[100] = {};
    char buf2[100] = {};
    char buf3[100] = {};
    char *p = "zhidao.baidu.com/link?url@sdfjdlks";
    sscanf(p, "%[^/]%[^@]%s", buf1, buf2, buf3);
    printf("%s\n", p);
    printf("buf1 = %s, buf2 = %s, buf3 = %s\n", buf1, buf2, buf3);
	return 0;
}
