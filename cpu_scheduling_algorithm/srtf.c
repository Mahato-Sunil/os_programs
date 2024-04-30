/*
SHORTEST REMAINING TIME NEXT CPU SCHEDULING ALGORITHM
SCHEDULING ALGORITHM FOR PROCESSES HAVING DIFFERENT ARRIVAL TIMES 

## Developed by Sunil Mahato 
-------------------------------------------
TEST CASE : 1
--------------------------------------------

Output : 

Enter the number of Processes: 4
Enter arrival time and burst time for each process:
Process 1: 1 4
Process 2: 0 2
Process 3: 3 4
Process 4: 5 6
Process  Arrival Time    Completion Time         Burst Time      Waiting Time    Turnaround Time
2        0               2                       2               0               2
1        1               6                       4               1               5
3        3               10                      4               3               7
4        5               16                      6               5               11

Average Waiting Time: 2.25
Average Turnaround Time: 6.25
---------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdbool.h>

// declaring the structure
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

// function to sort the process in ascending order based on remaining time
void rem_process_sort(struct Process process[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (process[i].remaining_time > process[j].remaining_time)
            {
                struct Process temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
}

void SRTF(struct Process process[], int n)
{
    int current_time = 0;
    bool isCompleted[n]; // Array to track completion of processes
    int waiting_time[n];
    int turnaround_time[n];
    int completion_time[n];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int completed = 0;

    // Initialize isCompleted array
    for (int i = 0; i < n; i++)
        isCompleted[i] = false;

    while (completed != n)
    {
        int shortest = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && process[i].arrival_time <= current_time)
            {
                if (shortest == -1 || process[i].remaining_time < process[shortest].remaining_time)
                {
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            current_time++;
            continue;
        }

        process[shortest].remaining_time--;

        if (process[shortest].remaining_time == 0)
        {
            completion_time[shortest] = current_time + 1;
            turnaround_time[shortest] = completion_time[shortest] - process[shortest].arrival_time;
            waiting_time[shortest] = turnaround_time[shortest] - process[shortest].burst_time;
            isCompleted[shortest] = true;
            completed++;
        }

        current_time++;
    }

    // Calculate total waiting and turnaround time
    for (int i = 0; i < n; i++)
    {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // printing the output
   
    printf("Process\t Arrival Time\t Completion Time\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++)
        printf("%d\t %d\t\t %d \t\t\t %d\t\t %d\t\t %d\n", process[i].id, process[i].arrival_time, completion_time[i], process[i].burst_time, waiting_time[i], turnaround_time[i]);

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

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

        // ASSIGNING THE REMAINING TIME
        process[i].remaining_time = process[i].burst_time;
    }

    rem_process_sort(process, n); // sort the process based on the shortest remaining time
    SRTF(process, n);
    return 0;
}
