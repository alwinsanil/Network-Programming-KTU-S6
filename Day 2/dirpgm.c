#include<stdio.h>
#include<dirent.h>

void main()
{
struct dirent *de;
DIR *d=opendir(".");
while(de=readdir(d))
{
printf("%s\n",de->d_name);
}
closedir(d);
}
