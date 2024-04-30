#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid, pid1, pid2, pid3;      // child pids
    pid_t ppid1, ppid2, ppid3;        // parent pids
    int p1, p2, p3;                   // for fork

    pid = getpid();
    printf("Parent's pid = %d \n", pid);

    // Child 1
    p1 = fork();
    if (p1 == -1) {
        perror("fork");
        return 1;
    } else if (p1 == 0) {
        pid1 = getpid();
        printf("\nChild 1 pid =  %d \n", pid1);
        ppid1 = getppid();
        printf("Child 1 parent's pid = %d \n", ppid1);

        // Child 2
        p2 = fork();
        if (p2 == -1) {
            perror("fork");
            return 1;
        } else if (p2 == 0) {
            pid2 = getpid();
            printf("Child 2 pid = %d \n", pid2);
            ppid2 = getppid();
            printf("Child 2 parent's pid = %d \n", ppid2);

            // Child 3
            p3 = fork();
            if (p3 == -1) {
                perror("fork");
                return 1;
            } else if (p3 == 0) {
                pid3 = getpid();
                printf("Child 3 pid = %d \n", pid3);
                ppid3 = getppid();
                printf("Child 3 parent pid = %d \n", ppid3);
            }
        }
    }

    // Wait for all child processes to complete
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}

