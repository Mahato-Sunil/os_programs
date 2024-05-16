#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 200

void SCAN(int arr[], int head, int size, int direction)
{
    int seek_count = 0;
    int distance, cur_track;
    int visited[size]; // Keeps track of visited tracks
    int min_distance, min_index;

    // Initialize visited array
    for (int i = 0; i < size; i++)
        visited[i] = 0;

    printf("\nSeek Sequence is:\n");

    // Sort the process queue in ascending order
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Find the nearest track in each iteration
    if (direction == 0)
    { // Left SCAN
        for (int i = head; i >= 0; i--)
        {
            for (int j = 0; j < size; j++)
            {
                if (arr[j] == i && !visited[j])
                {
                    visited[j] = 1; // Mark as visited
                    seek_count += abs(head - arr[j]);
                    head = arr[j];
                    printf("%d \t", arr[j]);
                }
            }
        }
        // Continue to the leftmost track
        seek_count += head;
        // seek_count += abs(head - arr[j]);
        printf("0 \t");
        head = 0;
        // Continue to the rightmost track
        for (int i = 0; i < size; i++)
        {
            if (!visited[i])
            {
                visited[i] = 1; // Mark as visited
                seek_count += abs(head - arr[i]);
                head = arr[i];
                printf("%d \t", arr[i]);
            }
        }
    }
    else
    { // Right SCAN
        for (int i = head; i <= DISK_SIZE - 1; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (arr[j] == i && !visited[j])
                {
                    visited[j] = 1; // Mark as visited
                    seek_count += abs(head - arr[j]);
                    head = arr[j];
                    printf("%d \t", arr[j]);
                }
            }
        }
        // Continue to the rightmost track
        seek_count += DISK_SIZE - 1 - head;
        printf("%d \t", DISK_SIZE - 1);
        head = DISK_SIZE - 1;
        // Continue to the leftmost track
        for (int i = size - 1; i >= 0; i--)
        {
            if (!visited[i])
            {
                visited[i] = 1; // Mark as visited
                seek_count += abs(head - arr[i]);
                head = arr[i];
                printf("%d \t", arr[i]);
            }
        }
    }

    printf("\nTotal number of seek operations = %d\n", seek_count);
}

int main()
{
    int size = 8;
    int head = 53;
    int direction = 0;
    int arr[10] = {98, 183, 37, 122, 14, 124, 65, 67};
    SCAN(arr, head, size, direction);
    return 0;
}
