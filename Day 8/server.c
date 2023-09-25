#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
 #include <unistd.h>
#include<fcntl.h>
int main(void)
{
    int socket_desc, client_sock, client_size,len,i=0,j,src;
    struct sockaddr_in server_addr, client_addr;
    char server_message[65530], client_message[65530],temp,fname[65530],cmd[65530];
// Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
// Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_desc < 0)
    {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
// Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(65530);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
// Bind to the set port and IP:
    if(bind(socket_desc, (struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");
// Listen for clients:
    if(listen(socket_desc, 1) < 0)
    {
        printf("Error while listening\n");
        return -1;
    }
    printf("\nListening for incoming connections.....\n");
// Accept an incoming connection:
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
    if (client_sock < 0)
    {
        printf("Can't accept\n");
        return -1;
    }
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
// Receive client's message:
    if (recv(client_sock, client_message, sizeof(client_message), 0) < 0)
    {
        printf("Couldn't receive\n");
        return -1;
    }

    printf("file name is: %s\n", client_message);
    
    src=open(client_message,O_RDONLY);
    if(src<0)
    	printf("Invalid file");
    else{
    	printf("opening file\n");
    	while(read(src,&temp,1)){
    		printf("%s",&temp);
    	}
    }
// Respond to client:
    
    printf("Type GET to send file to client: ");
    gets(cmd);
    if(strcmp(cmd,"GET")==0){
    	printf("Enter filename: ");
    	gets(server_message);
    	if (send(client_sock, server_message, strlen(server_message), 0) < 0)
   	 {
        	printf("Can't send\n");
       	 return -1;
    	}
    }
    else{
    	strcpy(server_message, "-------");
    	if (send(client_sock, server_message, strlen(server_message), 0) < 0)
   	 {
        	printf("Can't send\n");
       	 return -1;
    	}
    }
// Closing the socket:
    close(client_sock);
    close(socket_desc);
    return 0;
}

