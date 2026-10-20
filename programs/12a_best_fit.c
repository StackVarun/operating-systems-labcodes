#include <stdio.h>

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int i, j, bestIdx;

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++)
    {
        bestIdx = -1;

        for (j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1 ||
                    blockSize[j] < blockSize[bestIdx])
                {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t",
            i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int m, n, i;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int blockSize[m];

    printf("Enter size of each memory block:\n");
    for (i = 0; i < m; i++)
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processSize[n];

    printf("Enter size of each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    bestFit(blockSize, m, processSize, n);

    return 0;
}
