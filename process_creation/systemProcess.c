#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main() {
printf("Initialization of the process \n ");
int returncode = system("ls");

if(returncode == 0)
{
printf("Command Executed Successfully \n");
printf("The process id is : %d \n ", getpid());
}
else 
printf("Command Failed with return code %d \n", returncode);
printf("System Call Executed \n");
return 0;
}
