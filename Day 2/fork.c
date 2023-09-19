#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <limits.h>
int main()
{
	pid_t pid;
	pid = fork();
	if(pid==0)
	{
		printf("It is the child process and pid is %d\n",getpid());
		exit(0);
	}
	else if(pid > 0)
	{
		printf("It is the parent process and pid is %d\n",getpid());
		wait(NULL);
		printf("Current Working Directory: \n");
		execlp("/bin/pwd", "pwd", (char *)NULL);
		exit(0);
	}
	else
	{
		printf("Error while forking\n");
		exit(0);
	}   
	return 0;
}
