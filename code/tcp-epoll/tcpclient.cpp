//基于TCP协议的一对多客户端
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
using namespace std;

int main(void)
{
	//1.创建socket,使用socket函数
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	//2.准备通信地址，服务器地址
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//3.连接socket和通信地址,connect
	int res = connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if(-1 == res)
	{
		perror("connect"),exit(-1);
	}
	printf("连接服务器成功\n");
	//4.不断地和服务器进行通信
	while(1)
	{
		char buf[100] = {0};
		printf("请输入要发送的内容：");
		scanf("%s",buf);
		res = send(sockfd,buf,sizeof(buf), 0);
		if(-1 == res)
		{
			perror("send"),exit(-1);
		}

		char buf2[100] = {0};
		res = recv(sockfd,buf2,sizeof(buf2), 0);
		if(-1 == res)
		{
			perror("recv"),exit(-1);
		}
		printf("服务器发来的消息是：%s\n",buf2);
	}
	//5.关闭socket,使用close函数
	close(sockfd);
	return 0;
}
