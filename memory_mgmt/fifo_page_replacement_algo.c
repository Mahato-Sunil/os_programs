/* Test Cases :

 Enter the number of Pages : 10

 Enter the Pages :      2 4 1 2 3 6 1 8 9 2

 Enter the Available Memory Slots :      3

 Total Page Faults :     8
 Total Page Hits :       2

*/

#include <stdio.h>

// Function to find the number of page faults
void checkPageFault(int pages[], int n, int capacity)
{
    int memory[capacity]; // Memory slots
    int pageFaults = 0;   // Counter for page faults
    int pageHits = 0;     // counter for page hits

    for (int i = 0; i < n; ++i)
    {
        int currentPage = pages[i];
        int found = 0; // Flag to check if page is already in memory

        // Check if the current page is already in memory
        for (int j = 0; j < capacity; ++j)
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
            // Replace the oldest page (front of the queue)
            for (int j = capacity - 1; j > 0; --j)
            {
                memory[j] = memory[j - 1];
            }
            memory[0] = currentPage;
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
