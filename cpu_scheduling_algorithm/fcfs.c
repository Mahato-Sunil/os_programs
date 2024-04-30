/*
FIRST COME FIRST SERVE CPU SCHEDULING ALGORITHM
SCHEDULING ALGORITHM FOR PROCESSES HAVING DIFFERENT ARRIVAL TIMES

## Developed by Sunil Mahato
-------------------------------------------
TEST CASE : 1
--------------------------------------------

Output :

Enter the number of processes: 5
Enter arrival time and burst time for each process:
Process 1: 3 4
Process 2: 5 3
Process 3: 0 2
Process 4: 5 1
Process 5: 4 3
Process  Arrival Time    Response Time   Completion Time         Burst Time      Waiting Time    Turnaround Time
3        0               0                2                      2               0               2
1        3               0                7                      4               0               4
5        4               3                10                     3               3               6
4        5               5                11                     1               5               6
2        5               6                14                     3               6               9

Average Waiting Time: 2.80
Average Turnaround Time: 5.40
---------------------------------------------------------------------------------------
*/
#include <stdio.h>

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
};

void process_sort(struct Process Processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (Processes[i].arrival_time > Processes[j].arrival_time)
            {
                struct Process temp = Processes[i];
                Processes[i] = Processes[j];
                Processes[j] = temp;
            }
        }
    }
}

void FCFS(struct Process processes[], int n)
{
    int current_time = 0;

    int waiting_time[n]; // Array initialization moved inside function
    int turnaround_time[n];
    int completion_time[n];
    int response_time[n];

    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("Process\t Arrival Time\t Response Time\t Completion Time\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        // Adjust current_time if necessary (FCFS principle)
        if (current_time < processes[i].arrival_time)
        {
            current_time = processes[i].arrival_time;
        }

        // Waiting time
        waiting_time[i] = current_time - processes[i].arrival_time;
        total_waiting_time += waiting_time[i];

        // response time
        response_time[i] = waiting_time[i]; // non-pre-emptive process

        // Turnaround time
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];
        total_turnaround_time += turnaround_time[i];

        // Completion time
        completion_time[i] = current_time + processes[i].burst_time;
        printf("%d\t %d\t\t %d \t\t  %d\t\t\t %d\t\t %d\t\t %d\n", processes[i].id, processes[i].arrival_time, response_time[i], completion_time[i], processes[i].burst_time, waiting_time[i], turnaround_time[i]);

        current_time += processes[i].burst_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1; // Assign process IDs automatically
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    }

    process_sort(processes, n);
    FCFS(processes, n);

    return 0;
}
