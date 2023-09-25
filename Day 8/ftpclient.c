#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<stdio.h>
#include<string.h>






   

   
   
int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[65534], client_message[65534],c;
    FILE*fp;
    
    int server_struct_length = sizeof(server_addr);
    // Clean buffers:
    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
   
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
   
    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
   
  
    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(65534);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   
    // Send connection request to server:
    
   if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
   {
printf("Unable to connect\n");
return -1;
   }
   printf("Connected with server successfully\n");
    
    
   
 
    printf("Insert File: ");
    scanf("%s",client_message);
  
    if (sendto(socket_desc, client_message, strlen(client_message), 0,(struct sockaddr*)&server_addr, server_struct_length) < 0){
        printf("Can't send\n");
        return -1;
    }
   printf("File sent.\n"); 
  
  if (recvfrom(socket_desc, server_message, sizeof(server_message), 0,(struct sockaddr*)&server_addr, &server_struct_length) < 0)
    {
        printf("Couldn't receive\n");
        return -1;
    }

    printf("Msg from server: %s\n\n", server_message); 

 memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    
   if (recvfrom(socket_desc, server_message, sizeof(server_message), 0,(struct sockaddr*)&server_addr, &server_struct_length) < 0)
    {
        printf("Couldn't receive\n");
        return -1;
    }

    printf("File from server: %s\n\n", server_message); 
    
    fp=fopen(server_message,"r");
    if(fp == NULL)
   {
      strcpy(client_message,"Unable to open file");
               
   }
   else{
    strcpy(client_message,"File opened successfully");
    printf("FILE CONTENT :\n");
    c = fgetc(fp);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fp);
    }
  
    fclose(fp);
    printf("\n");
    }
    
     if (sendto(socket_desc, client_message, strlen(client_message), 0,(struct sockaddr*)&server_addr, server_struct_length) < 0){
        printf("Can't send\n");
        return -1;
    }
   
  
    // Close the socket:
    close(socket_desc);
    return 0;
}



