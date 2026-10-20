#include <stdio.h>

int main()
{
    int frames[20], recent[20];
    int n, f;
    int i, j, k;
    int page, found, pos;
    int faults = 0, hits = 0;
    int time = 0, min_time;

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    printf("Enter the number of pages in reference string: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
        recent[i] = -1;
    }

    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        page = pages[i];
        found = 0;

        /* Check whether page is already present */
        for (j = 0; j < f; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                hits++;
                time++;
                recent[j] = time;
                break;
            }
        }

        /* Page fault */
        if (!found)
        {
            faults++;
            time++;

            /* Check for empty frame */
            pos = -1;

            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            /* If no empty frame, find least recently used page */
            if (pos == -1)
            {
                min_time = recent[0];
                pos = 0;

                for (k = 1; k < f; k++)
                {
                    if (recent[k] < min_time)
                    {
                        min_time = recent[k];
                        pos = k;
                    }
                }
            }
            frames[pos] = page;
            recent[pos] = time;
        }

        printf("%d\t", page);

        for (j = 0; j < f; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found)
            printf("\tHit\n");
        else
            printf("\tPage Fault\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
    printf("Total Page Hits = %d\n", hits);

    return 0;
}
