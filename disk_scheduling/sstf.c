#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void SSTF(int arr[], int head, int size)
{
    int seek_count = 0;
    int distance, cur_track;
    int visited[size]; // Keeps track of visited tracks
    int min_distance, min_index;

    // Initialize visited array
    for (int i = 0; i < size; i++)
        visited[i] = 0;

    printf("\nSeek Sequence is:\n");

    // Find the nearest track in each iteration
    for (int i = 0; i < size; i++)
    {
        min_distance = INT_MAX; // Initialize to maximum value
        min_index = -1;

        for (int j = 0; j < size; j++)
        {
            if (!visited[j])
            {
                distance = abs(arr[j] - head);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }

        visited[min_index] = 1; // Mark as visited
        seek_count += min_distance;
        head = arr[min_index];
        printf("%d   >>  ", arr[min_index]);
    }

    printf("\nTotal number of seek operations = %d\n", seek_count);
}

int main()
{
    int size;
    int head;

    printf("\nEnter the number of processes:\t");
    scanf("%d", &size);

    int arr[size];

    printf("\nEnter the process queue:\t");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    printf("\nEnter the position of Head:\t");
    scanf("%d", &head);

    SSTF(arr, head, size);
    return 0;
}
