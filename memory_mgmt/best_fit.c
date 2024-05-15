#include <stdio.h>

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
}

int main()
{
    int nblock, nprocess;
    printf("Enter the number of memory blocks : \t");
    scanf("%d", &nblock);

    printf("Enter the number of process :\t");
    scanf("%d", &nprocess);

    // declaring the array of blocks and sizes
    int blockSize[nblock];
    int processSize[nprocess];

    printf("Enter the sizes of the memory block :\t");
    for (int i = 0; i < nblock; i++)
        scanf("%d", &blockSize[i]);
 
    printf("Enter the Process Sizes :\t");
    for (int i = 0; i < nprocess; i++)
        scanf("%d", &processSize[i]);

    bestFit(blockSize, nblock, processSize, nprocess);
    return 0;
}
