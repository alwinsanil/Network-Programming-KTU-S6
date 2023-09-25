#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdio.h>

int main(void)
{
    int n, send[10];
    printf("Enter no. of frames to be sent: ");
    scanf("%d", n);
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[65534], client_message[65534],name[30],pass[30];
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);to
    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
    printf("\nUsername:");
    gets(name);
    printf("\nPassword:");
    gets(pass);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(65534);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if((strcmp(name,"admin")==0) && (strcmp(pass,"123")==0))
    {
   if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
   {
printf("Unable to connect\n");
return -1;
   }
   printf("Connected with server successfully\n");
    }
    else
    {
    printf("Incorrect username or password...\nUnable to connect\n");
       close(socket_desc);
return -1;
    }
   
    // Get input from the user:
    printf("Enter message: ");
    gets(client_message);
   
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
   
    printf("Server's response: %s\n",server_message);
   
    // Close the socket:
    close(socket_desc);
   
    return 0;
}

