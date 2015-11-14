#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _cis_packet 
{
    int length;
} cis_packet;

int main() 
{
	char *data = "hello world";
	cis_packet buf; /*长度包*/
	buf.length = strlen(data) + 1; /*数据包长度*/
	
	char x[1024];
	memset(x, 0, 1024);  /*把字符串都重置为0*/
	memcpy(x, &buf, sizeof(buf));	/*封包*/
	memcpy(x + sizeof(buf), data, buf.length);	/*封包*/
	
	cis_packet* z = (cis_packet*)x; 	/*解包*/
	printf("%d\n", z->length);
	printf("%s\n", x + sizeof(buf));
	
	return 0;
}
