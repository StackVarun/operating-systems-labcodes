#include <stdio.h>
int m, n, i, j, al[10][10], max[10][10], av[10], need[10][10], z, y, p, k;

int main() {
    printf("\n Enter no of processes : ");
    scanf("%d", &m);
    printf("\n Enter no of resources : ");
    scanf("%d", &n);

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("\n Enter instances for al[%d][%d] = ", i, j);
            scanf("%d", &al[i][j]);      // FIX: keep the value the user entered
        }                                 // (the extra "al[i][j] = temp;" line
    }                                     // that zeroed this out has been removed)

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("\n Enter instances for max[%d][%d] = ", i, j);
            scanf("%d", &max[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
        printf("\n Available Resource for av[%d] = ", i);
        scanf("%d", &av[i]);
    }

    printf("\nAllocation Values :\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf(" \t %d", al[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    printf("Max Values :\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf(" \t %d", max[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    printf("Need Values :\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            need[i][j] = max[i][j] - al[i][j];
            printf("\t %d", need[i][j]);
        }
        printf("\n");
    }

    p = 1;   // used for terminating while loop
    y = 0;   // number of processes found safe so far
    int safe_order[10];

    while (p != 0) {
        int progress = 0;   // FIX: detect when NO process can proceed
        // further this pass, so we can break out
        // instead of looping forever
        for (i = 0; i < m; i++) {
            if (need[i][0] == -1) continue;   // already marked done
            z = 0;
            for (j = 0; j < n; j++) {
                if (need[i][j] <= av[j]) {
                    z++;
                }
            }
            if (z == n) {
                for (k = 0; k < n; k++) {
                    av[k] += al[i][k];
                }
                safe_order[y] = i;
                printf("\n SS process %d", i);
                need[i][0] = -1;   // mark process i as finished
                y++;
                progress = 1;
            }
        }
        if (y == m) {
            p = 0;   // all processes finished -> safe state found
        } else if (!progress) {
            printf("\n\nSystem is NOT in a safe state (deadlock/unsafe request).\n");
            p = 0;   // FIX: stop instead of looping forever when no
            // process can make progress
            break;
        }
    }

    if (y == m) {
        printf("\n\nSystem is in a SAFE state.\nSafe sequence: ");
        for (i = 0; i < m; i++) {
            printf("P%d ", safe_order[i]);
        }
        printf("\n");
    }
    return 0;
}
