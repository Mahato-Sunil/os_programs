#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
pid_t pid  = fork();
if(pid ==-1)
{
perror("Fork Failed");
return 1;
}
else
if(pid > 0)
{
printf("Parent Process with  PPID %d \n", getpid());
printf("Childs PID is %d \n", pid);
}
else
printf("Child Process: pid is %d \n", getpid());
return 0;
}
