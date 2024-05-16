#include <stdio.h>
#include <stdlib.h>

#define DISK_SIZE 200

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void cscan(int request[], int n, int head)
{
    int seek_count = 0;
    int distance, cur_track;

    // Sort requests
    qsort(request, n, sizeof(int), cmpfunc);

    // Finding the index of the head in the sorted requests
    int start = 0;
    for (int i = 0; i < n; i++)
    {
        if (request[i] >= head)
        {
            start = i;
            break;
        }
    }

    printf("Seek Sequence is:\n");

    // Scanning right from the head
    for (int i = start; i < n; i++)
    {
        printf("%d ", request[i]);
        seek_count += abs(head - request[i]);
        head = request[i];
    }

    // If head is at the maximum position, move it to the other end
    if (head != DISK_SIZE - 1)
    {
        printf("%d ", DISK_SIZE - 1);
        seek_count += abs(head - (DISK_SIZE - 1));
        head = DISK_SIZE - 1;
    }

    printf("0 ");
    seek_count += head;
    head = 0;

    // Scanning left from the end to the head
    for (int i = 0; i < start; i++)
    {
        printf("%d ", request[i]);
        seek_count += abs(head - request[i]);
        head = request[i];
    }

    printf("\nTotal head movement: %d\n", seek_count);
}

int main()
{
    int request[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(request) / sizeof(request[0]);
    int initial_head = 53;

    printf("Initial position of head: %d\n", initial_head);
    cscan(request, n, initial_head);

    return 0;
}
