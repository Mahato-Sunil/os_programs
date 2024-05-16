#include <stdio.h>
#include <stdlib.h>

void FCFS(int arr[], int head, int size)
{
    int seek_count = 0;
    int distance, cur_track;

    for (int i = 0; i < size; i++)
    {
        cur_track = arr[i];
        distance = abs(cur_track - head);
        seek_count += distance;
        head = cur_track;
    }

    printf("Total number of seek operations = %d\n", seek_count);
    printf("Seek Sequence is:\n");

    for (int i = 0; i < size; i++)
    {
        printf("%d   >>  ", arr[i]);
    }
}

int main()
{
    int size;
    int head;

    printf("\nEnter the Number  of processes :\t");
    scanf("%d", &size);

    int arr[size];

    printf("\n Enter the process queue  :\t");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    printf("\n Enter the position of Head  :\t");
    scanf("%d", &head);

    FCFS(arr, head, size);
    return 0;
}
