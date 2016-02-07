#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
using namespace std;

int main()
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	struct timeval timeout;
	fd_set reads, cpy_reads;

	socklen_t adr_sz;

	int fd_max, str_len, fd_num, i;
	char buf[1024];

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_adr.sin_port = htons(8888);

	//解决地址被占用的问题
	int reuseaddr = 1;
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
	
	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		perror("bind");
	if (listen(serv_sock, 5) == -1)
		perror("listen");

	FD_ZERO(&reads);
	FD_SET(serv_sock, &reads);
	fd_max = serv_sock;

	while (1)
	{
		cpy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
			break;
		if (fd_num == 0)
			continue;
		
		for (i = 0; i<fd_max + 1; i++)
		{
			if (FD_ISSET(i, &cpy_reads))
			{
				if (i == serv_sock)
				{
					adr_sz = sizeof(clnt_adr);
					clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
					FD_SET(clnt_sock, &reads);
					if (fd_max<clnt_sock)
						fd_max = clnt_sock;
					printf("connected client: %d \n", clnt_sock);
				}
				else
				{
					str_len = recv(i, buf, sizeof(buf), 0);
					if (str_len == 0)
					{
						FD_CLR(i, &reads);
						close(i);
						printf("close client: %d \n", i);
					}
					else
					{
						cout << "发送来的数据为：" << buf << endl;
					}	
					int send_len = send(i, "ok!", 3, 0);
					cout << "send_len: " << send_len << endl;
					//半关闭连接(关闭套接字下一次的send操作)
					//shutdown(i, SHUT_WR);
					//shutdown(i, SHUT_RD);//(关闭套接字下一次的recv操作)
				}
			}
		}
	}
	close(serv_sock);
	return 0;
}
