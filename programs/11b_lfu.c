#include <stdio.h>

int main()
{
    int frames[20], freq[20], age[20];
    int n, f;
    int pages[100];
    int i, j, k;
    int page, found, pos;
    int faults = 0, hits = 0;
    int time = 0;

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    printf("Enter the number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
        freq[i] = 0;
        age[i] = 0;
    }
    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        page = pages[i];
        found = 0;
        time++;

        /* Check whether page is already present */
        for (j = 0; j < f; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                freq[j]++;
                age[j] = time;
                hits++;
                break;
            }
        }

        /* Page fault */
        if (!found)
        {
            faults++;
            pos = -1;

            /* Find an empty frame */
            for (j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            /* Find LFU page if no empty frame */
            if (pos == -1)
            {
                pos = 0;

                for (k = 1; k < f; k++)
                {
                    if (freq[k] < freq[pos] ||
                        (freq[k] == freq[pos] && age[k] < age[pos]))
                    {
                        pos = k;
                    }
                }
            }

            frames[pos] = page;
            freq[pos] = 1;
            age[pos] = time;
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
