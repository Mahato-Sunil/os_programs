#include <stdio.h>

void bankers_algo(int processes, int resources, int allocation_matrix[processes][resources], int max_matrix[processes][resources], int aval_resource[resources])
{
    int f[processes], ans[processes], ind = 0;
    int need_matrix[processes][resources];

    // Initialize f array to keep track of processed processes
    for (int i = 0; i < processes; i++)
        f[i] = 0;

    // Calculate need matrix
    for (int i = 0; i < processes; i++)
        for (int j = 0; j < resources; j++)
            need_matrix[i][j] = max_matrix[i][j] - allocation_matrix[i][j];

    // Banker's Algorithm
    for (int k = 0; k < processes; k++)
    {
        for (int i = 0; i < processes; i++)
        {
            if (f[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < resources; j++)
                {
                    if (need_matrix[i][j] > aval_resource[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    ans[ind++] = i;
                    // Update available resources
                    for (int y = 0; y < resources; y++)
                        aval_resource[y] += allocation_matrix[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    // Check for deadlock
    int flag = 1;
    for (int i = 0; i < processes; i++)
    {
        if (f[i] == 0)
        {
            flag = 0;
            printf("DEADLOCK: The system is not safe\n");
            return;
        }
    }

    // Print safe sequence
    printf("SAFE Sequence processes:\n");
    for (int i = 0; i < processes; i++)
    {
        printf("Process [%d]", ans[i]);
        if (i < processes - 1)
            printf(" -> ");
    }
    printf("\n");
}

int main()
{
    int processes, resources;

    printf("Enter the number of Processes: ");
    scanf("%d", &processes);

    printf("Enter the number of Resources: ");
    scanf("%d", &resources);

    int allocation_matrix[processes][resources];
    int max_matrix[processes][resources];
    int aval_resource[resources];

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        printf("Matrix Row [%d]: ", i);
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &allocation_matrix[i][j]);
        }
    }

    printf("\nEnter the Maximum Need Matrix:\n");
    for (int i = 0; i < processes; i++)
    {
        printf("Matrix Row [%d]: ", i);
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &max_matrix[i][j]);
        }
    }

    printf("\nEnter the Available Resources :\t");
    for (int i = 0; i < resources; i++)
        scanf("%d", &aval_resource[i]);

    bankers_algo(processes, resources, allocation_matrix, max_matrix, aval_resource);
    return 0;
}
