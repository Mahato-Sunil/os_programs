#include<stdio.h>
#include<unistd.h>

int main(){
int processId, parentPid;
processId = getpid();
parentPid = getppid();
printf("Child Process Id is : %d \n ", processId);
printf("Parent process Id is : %d \n", parentPid);

return 0;
}
