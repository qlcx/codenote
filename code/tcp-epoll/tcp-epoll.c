#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 4
#define EPOLL_SIZE 50

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t adr_sz;
	int str_len, i;
	char buf[BUF_SIZE];
	
	struct epoll_event *ep_events;
	struct epoll_event event;
	int epfd, event_cnt;
	
	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_adr.sin_port = htons(8888);
	
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
	{
		perror("bind() error");
	}
	if(listen(serv_sock, 5) == -1)
	{
		perror("listen() error");
	}
	
	epfd = epoll_create(EPOLL_SIZE);
	ep_events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
	
	event.events = EPOLLIN;
	event.data.fd = serv_sock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);
	
	printf("serv_sock: %d\n", serv_sock);
	while(1)
	{
		printf("stop\n");
		event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
		if(event_cnt == -1)
		{
			perror("epoll_wait() error");
			break;
		}
		printf("go\n");
		
		for(i = 0; i < event_cnt; i++)
		{
			if(ep_events[i].data.fd == serv_sock)
			{
				adr_sz = sizeof(clnt_adr);
				if((clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz)) == -1)
				{
					perror("accept() error");
				}
				event.events = EPOLLIN;
				event.data.fd = clnt_sock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
				printf("connected client: %d \n", clnt_sock);
			}
			else
			{
				if((str_len = recv(ep_events[i].data.fd, buf, BUF_SIZE, 0)) == -1)
				{
					perror("recv() error");
				}
				
				printf("recv data is: %s\n", buf);
				
				if(str_len == 0)	//close request!
				{
					epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
					close(ep_events[i].data.fd);
					printf("closed client: %d \n", ep_events[i].data.fd);	
				}
				else
				{
					send(ep_events[i].data.fd, buf, str_len, 0);	//echo!
				}
			}
		}
	}
	close(serv_sock);
	close(epfd);
	return 0;
}