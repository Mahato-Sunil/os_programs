#include <stdio.h>

// Global declaration
int quantum_time;

int waiting_time[100];
int turnaround_time[100];
int completion_time[100];

int total_waiting_time = 0;
int total_turnaround_time = 0;

// Declare the process structure
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_burst;
};

// Function to carry out the scheduling using Round Robin algorithm
void roundRobin(struct Process process[], int n)
{
    int time = 0;
    int remaining_processes = n;

    // Loop until all processes are completed
    while (remaining_processes > 0)
    {
        // Iterate through each process
        for (int i = 0; i < n; i++)
        {
            // Check if the process still has remaining burst time
            if (process[i].remaining_burst > 0)
            {
                // Execute the process for the time quantum or until completion
                if (process[i].remaining_burst <= quantum_time)
                {
                    time += process[i].remaining_burst;
                    process[i].remaining_burst = 0;
                    completion_time[i] = time;
                    turnaround_time[i] = completion_time[i] - process[i].arrival_time;
                    waiting_time[i] = turnaround_time[i] - process[i].burst_time;
                    total_waiting_time += waiting_time[i];
                    total_turnaround_time += turnaround_time[i];
                    remaining_processes--;
                }
                else
                {
                    time += quantum_time;
                    process[i].remaining_burst -= quantum_time;
                }
            }
        }
    }

    // Printing the results
    printf("Process\t Arrival Time\t Completion Time\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t %d\t\t %d \t\t\t %d\t\t %d\t\t %d\n", process[i].id, process[i].arrival_time, completion_time[i], process[i].burst_time, waiting_time[i], turnaround_time[i]);

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

// Driver code
int main()
{
    int n;
    printf("Enter the number of Processes: ");
    scanf("%d", &n);

    struct Process process[n];
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        process[i].id = i + 1; // Assign process IDs automatically
        printf("Process %d: ", i + 1);
        scanf("%d %d", &process[i].arrival_time, &process[i].burst_time);
        process[i].remaining_burst = process[i].burst_time;
    }

    printf("\nEnter the Time Quantum: ");
    scanf("%d", &quantum_time);

    roundRobin(process, n);
    return 0;
}
