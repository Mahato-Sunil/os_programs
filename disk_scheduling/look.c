#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define DISK_SIZE 200
#define DIRECTION 0

int seek_count = 0;
int head = 53;
// function to print the sequence and find the seek time
void printQueue(int i, int visited[], int arr[])
{
    visited[i] = 1; // Mark as visited
    seek_count += abs(head - arr[i]);
    head = arr[i];
    printf("%d \t", arr[i]);
}

void LOOK(int arr[])
{
    int distance, cur_track;
    int visited[SIZE]; // Keeps track of visited tracks

    // Initialize visited array
    for (int i = 0; i < SIZE; i++)
        visited[i] = 0;

    printf("\nSeek Sequence is:\n");

    // Find the nearest track in each iteration
    if (DIRECTION == 0)
    { // Left LOOK
        for (int i = head; i > 0; i--)
            for (int j = SIZE - 1; j >= 0; j--)
                if (arr[j] == i && !visited[j])
                    printQueue(j, visited, arr);

        // Move to the rightmost track
        for (int i = head; i <= DISK_SIZE - 1; i++)
            for (int j = 0; j < SIZE; j++)
                if (arr[j] == i && !visited[j])
                    printQueue(j, visited, arr);
    }
    else
    { // Right LOOK
        for (int i = head; i <= DISK_SIZE - 1; i++)
            for (int j = 0; j < SIZE; j++)
                if (arr[j] == i && !visited[j])
                    printQueue(j, visited, arr);

        // Move to the leftmost track
        for (int i = head; i > 0; i--)
            for (int j = SIZE - 1; j >= 0; j--)
                if (arr[j] == i && !visited[j])
                    printQueue(j, visited, arr);
    }
    printf("\nTotal number of seek operations = %d\n", seek_count);
}

int main()
{
    int arr[SIZE] = {98, 183, 41, 122, 14, 124, 65, 67};
    LOOK(arr);
    return 0;
}
