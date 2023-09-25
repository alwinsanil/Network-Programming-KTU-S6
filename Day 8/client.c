#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main(void)
{
    int socket_desc,src;
    struct sockaddr_in server_addr;
    char temp,server_message[65530], client_message[65530],fname[30],pass[30],ch[65530],opt[65530];
   
    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
   
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
   
    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
   
    printf("Socket created successfully\n");
   
   
    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(65530);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   
    // Send connection request to server:
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
   {
printf("Unable to connect\n");
return -1;
   }
   printf("Connected with server successfully\n");
   
       
    // Get input from the user:
    while(1)
    {
    printf("Enter command: ");
    gets(opt);
    if(strcmp(opt,"HELO")==0)
    //strcpy(client_message,"Client wants to start coversation");
    printf("Connection Established\n");
    else if(strcmp(opt,"PUT")==0)
    {
    printf("Enter File name: ");
    gets(ch);
    strcat(client_message,"");
    strcat(client_message,ch);
    }
 
    else if(strcmp(opt,"SEND")==0)
    break;
    else
    printf("Wrong command");
    }
    // Send the message to server:
    if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
        printf("Unable to send message\n");
        return -1;
    }
   
    // Receive the server's response:
    if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }
   
    //printf("Server's response: %s\n",server_message);
   src=open(server_message,O_RDONLY);
    if(src<0)
    	printf("END OF CODE");
    else{
    	printf("opening file\n");
    	while(read(src,&temp,1)){
    		printf("%s",&temp);
    	}
    }
   
    // Close the socket:
    close(socket_desc);
   
    return 0;
}

