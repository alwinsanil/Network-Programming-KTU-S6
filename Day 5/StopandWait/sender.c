#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd,int nf,int ws)
{
	char buff[MAX];
	int ack,i=0;
	
	while(1)
	{
		bzero(buff, sizeof(buff));
		snprintf (buff, sizeof(buff), "%d",i);
		write(sockfd, buff, sizeof(buff));
		printf("Frame %d sent\n",i);
		bzero(buff, sizeof(buff));
  		read(sockfd, buff, sizeof(buff));
  		ack=atoi(buff);
  		if(ack==-1)
  		{
  			printf("Acknowledgement not received. Resending frame %d\n",i);
  			continue;
  		}
  		else if(ack==i+1)
  		{
  			printf("Acknowlegement received: %d\n",ack);
  			i++;
  		}
  		if(i==nf)
  		{
  			bzero(buff, sizeof(buff));
  			strcpy(buff,"Exit");
			write(sockfd, buff, sizeof(buff));
			break;
		}
	}
}

int main()
{
	int sockfd, connfd, f, w;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket creation failed\n");
		exit(0);
	}
	else
		printf("Socket successfully created\n");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection with the reciever failed\n");
		exit(0);
	}
	else
		printf("Connected to the reciever\n");
		
	printf("Enter the number of frames: ");
	scanf("%d",&f);

	func(sockfd,f,1);

	close(sockfd);
}

