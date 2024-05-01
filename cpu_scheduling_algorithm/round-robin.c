#include <stdio.h>

// Structure to store process details
struct Process
{
    int id;
    int burst_time;
    int arrival_time;
    int remaining_time;
};

// Function to schedule the processes using round robin algorithm

void roundRobin(struct Process processes[], int N, int quantum_time)
{
    int waiting_time[N];
    int turnaround_time[N];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("\n Process No \t\t Burst Time \t\t Turnaround Time \t\t Waiting Time ");

    int remaining_processes = N;
    int current_time = 0;

    while (remaining_processes > 0)
    {
        for (int i = 0; i < N; i++)
        {
            if (processes[i].remaining_time > 0)
            {
                int execute_time = (processes[i].remaining_time <= quantum_time) ? processes[i].remaining_time : quantum_time;
                processes[i].remaining_time -= execute_time;
                current_time += execute_time;

                if (processes[i].remaining_time == 0)
                {
                    remaining_processes--;

                    turnaround_time[i] = current_time - processes[i].arrival_time;
                    waiting_time[i] = turnaround_time[i] - processes[i].burst_time;

                    printf("\nProcess No[%d] \t\t %d \t\t\t\t %d \t\t\t\t %d", processes[i].id, processes[i].burst_time, turnaround_time[i], waiting_time[i]);

                    total_waiting_time += waiting_time[i];
                    total_turnaround_time += turnaround_time[i];
                }
            }
        }
    }

    printf("\n\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / N);
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / N);
}

int main()
{
    int N;
    printf("Total number of processes in the system: ");
    scanf("%d", &N);

    struct Process processes[N];

    printf("\nEnter the Arrival and Burst time of each Process :\n");

    for (int i = 0; i < N; i++)
    {
        printf("Process %d : ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].id = i + 1;
    }

    int quantum_time;
    printf("\nEnter the Time Quantum for the process: ");
    scanf("%d", &quantum_time);

    roundRobin(processes, N, quantum_time);
    return 0;
}
