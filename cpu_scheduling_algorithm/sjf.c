/*
SHORTEST JOB FIRST CPU SCHEDULING ALGORITHM
SCHEDULING ALGORITHM FOR PROCESSES HAVING DIFFERENT ARRIVAL TIMES 

## Developed by Sunil Mahato 
-------------------------------------------
TEST CASE : 1
--------------------------------------------

Output : 

Enter the number of Processes: 5
Enter arrival time and burst time for each process:
Process 1: 3 1
Process 2: 1 4
Process 3: 4 2
Process 4: 0 6
Process 5: 2 3
Process  Arrival Time    Response Time   Completion Time         Burst Time      Waiting Time    Turnaround Time
4        0               0               6                       6               0               6
1        3               3               7                       1               3               4
3        4               3               9                       2               3               5
5        2               7               12                      3               7               10
2        1               11              16                      4               11              15

Average Waiting Time: 4.80
Average Turnaround Time: 8.00
---------------------------------------------------------------------------------------
*/

#include <stdio.h>

int current_time = 0;

int waiting_time[100]; // Array size adjusted (consider dynamic allocation)
int turnaround_time[100];
int completion_time[100];
int response_time[100];

int total_waiting_time = 0;
int total_turnaround_time = 0;

int P_INDEX = 0;
int executed = 0;

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
};

struct Process first_process;

// FUNCTION TO FIND THE FIRST PROCESS THAT ARRIVED
void execute_first_process(struct Process Processes[], int n)
{

    // finding the first arrival time
    for (int i = 0; i < n; i++)
    {
        if (Processes[i].arrival_time < Processes[P_INDEX].arrival_time)
        {
            P_INDEX = i;
        }
        first_process = Processes[P_INDEX];
    }

    current_time = first_process.arrival_time;
    // executing the first process
    // Waiting time
    waiting_time[P_INDEX] = current_time - first_process.arrival_time;
    total_waiting_time += waiting_time[P_INDEX];

    // Response time (non-preemptive process)
    response_time[P_INDEX] = waiting_time[P_INDEX];

    // Turnaround time
    turnaround_time[P_INDEX] = first_process.burst_time + waiting_time[P_INDEX];
    total_turnaround_time += turnaround_time[P_INDEX];

    // Completion time
    completion_time[P_INDEX] = current_time + first_process.burst_time;

    printf("%d\t %d\t\t %d \t\t %d\t\t\t %d\t\t %d\t\t %d\n", first_process.id, first_process.arrival_time, response_time[P_INDEX], completion_time[P_INDEX], first_process.burst_time, waiting_time[P_INDEX], turnaround_time[P_INDEX]);

    current_time += first_process.burst_time;

    executed = 1;
}

// function to sort the process in ascending order
void process_sort(struct Process Processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (Processes[i].burst_time > Processes[j].burst_time)
            {
                struct Process temp = Processes[i];
                Processes[i] = Processes[j];
                Processes[j] = temp;
            }
        }
    }
}

// sjf algorithm
void SJF(struct Process Processes[], int n)
{
    printf("Process\t Arrival Time\t Response Time\t Completion Time\t Burst Time\t Waiting Time\t Turnaround Time\n");

    execute_first_process(Processes, n); // executing the first processs

    // Schedule remaining processes (excluding the first one)
    for (int i = 0; i < n; i++)
    {
        if (Processes[i].arrival_time == Processes[P_INDEX].arrival_time)
            continue;
        else
        {
            if (Processes[i].arrival_time > current_time)
                current_time = Processes[i].arrival_time; // Adjust for FCFS

            // Waiting time
            waiting_time[i] = current_time - Processes[i].arrival_time;
            total_waiting_time += waiting_time[i];

            // Response time (non-preemptive process)
            response_time[i] = waiting_time[i];

            // Turnaround time
            turnaround_time[i] = Processes[i].burst_time + waiting_time[i];
            total_turnaround_time += turnaround_time[i];

            // Completion time
            completion_time[i] = current_time + Processes[i].burst_time;

            printf("%d\t %d\t\t %d \t\t %d\t\t\t %d\t\t %d\t\t %d\n", Processes[i].id, Processes[i].arrival_time, response_time[i], completion_time[i], Processes[i].burst_time, waiting_time[i], turnaround_time[i]);

            current_time += Processes[i].burst_time;
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main()
{
    int n;
    printf("Enter the number of Processes: ");
    scanf("%d", &n);

    struct Process Processes[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        Processes[i].id = i + 1; // Assign process IDs automatically
        printf("Process %d: ", i + 1);
        scanf("%d %d", &Processes[i].arrival_time, &Processes[i].burst_time);
    }

    process_sort(Processes, n); // sorting the process based on burst time
    SJF(Processes, n);
    return 0;
}
