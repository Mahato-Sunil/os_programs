/*
Test CAses :

 Enter the number of Pages : 14

 Enter the Pages :      7 0 1 2 0 3 0 4 2 3 0 3 2 3

 Enter the Available Memory Slots :      4

 Total Page Faults :     6
 Total Page Hits :       8
*/
#include <stdio.h>
#include <limits.h>

// Function to find the index of the least recently used page in memory
int findLRUPage(int pages[], int memory[], int n, int capacity, int index)
{
    int res = -1, leastUsed = INT_MAX;
    for (int i = 0; i < capacity; i++)
    {
        int j;
        for (j = index - 1; j >= 0; j--)
        {
            if (memory[i] == pages[j])
            {
                if (j < leastUsed)
                {
                    leastUsed = j;
                    res = i;
                }
                break;
            }
        }

        // If a page is never referenced in past, return its index
        if (j == -1)
            return i;
    }
    return (res == -1) ? 0 : res;
}

// Function to find the number of page faults using LRU page replacement algorithm
void checkPageFault(int pages[], int n, int capacity)
{
    int memory[capacity]; // Memory slots
    int pageFaults = 0;   // Counter for page faults
    int pageHits = 0;     // Counter for page hits

    for (int i = 0; i < capacity; i++)
        memory[i] = -1; // Initialize memory slots with -1

    for (int i = 0; i < n; i++)
    {
        int currentPage = pages[i];
        int found = 0; // Flag to check if page is already in memory

        // Check if the current page is already in memory
        for (int j = 0; j < capacity; j++)
        {
            if (memory[j] == currentPage)
            {
                found = 1;
                ++pageHits;
                break;
            }
        }

        if (!found)
        {
            // Replace the least recently used page
            int index = findLRUPage(pages, memory, n, capacity, i);
            memory[index] = currentPage;
            ++pageFaults;
        }
    }

    printf("\n Total Page Faults : \t %d", pageFaults);
    printf("\n Total Page Hits : \t %d", pageHits);
}

int main()
{
    int n, capacity;
    printf("\n Enter the number of Pages : ");
    scanf("%d", &n);

    int pages[n];

    printf("\n Enter the Pages :\t");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("\n Enter the Available Memory Slots : \t ");
    scanf("%d", &capacity);

    checkPageFault(pages, n, capacity);
    printf("\n");
    return 0;
}
