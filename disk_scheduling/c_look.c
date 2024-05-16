#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 200

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void CLOOK(int arr[], int n, int head)
{
    int seek_count = 0;
    int distance, cur_track;

    // Sort requests
    qsort(arr, n, sizeof(int), cmpfunc);

    // Finding the index of the head in the sorted requests
    int start = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= head)
        {
            start = i;
            break;
        }
    }

    printf("Seek Sequence is:\n");

    // Scanning right from the head
    for (int i = start; i < n; i++)
    {
        printf("%d ", arr[i]);
        seek_count += abs(head - arr[i]);
        head = arr[i];
    }
    
    // Scanning left from the end to the head
    for (int i = 0; i < start; i++)
    {
        printf("%d ", arr[i]);
        seek_count += abs(head - arr[i]);
        head = arr[i];
    }
    printf("\nTotal head movement: %d\n", seek_count);
}

int main()
{
    int arr[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(arr) / sizeof(arr[0]);
    int initial_head = 53;

    printf("Initial position of head: %d\n", initial_head);
    CLOOK(arr, n, initial_head);

    return 0;
}
