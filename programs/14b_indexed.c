#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 12

static int used[MAX_BLOCKS];

static int is_valid_block(int block) {
    return block >= 0 && block < MAX_BLOCKS;
}

int main(void) {
    int indexBlock, n, choice;
    int blocks[MAX_BLOCKS];

    for (int i = 0; i < MAX_BLOCKS; ++i)
        used[i] = 0;

    printf("Simulation of Indexed Allocation\n");

    while (1) {
        printf("\nEnter the index block number (0-%d): ", MAX_BLOCKS - 1);
        if (scanf("%d", &indexBlock) != 1) return EXIT_FAILURE;

        if (!is_valid_block(indexBlock)) {
            printf("Invalid index block.\n");
            continue;
        }

        if (used[indexBlock]) {
            printf("Index block is already allocated.\n");
            continue;
        }

        printf("Enter number of blocks needed for the file: ");
        if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_BLOCKS - 1) {
            printf("Invalid number of data blocks.\n");
            continue;
        }

        printf("Enter the data block numbers: ");
        int valid = 1;
        for (int i = 0; i < n; ++i) {
            if (scanf("%d", &blocks[i]) != 1) return EXIT_FAILURE;
            if (!is_valid_block(blocks[i]) ||
                used[blocks[i]] || blocks[i] == indexBlock) {
                valid = 0;
            }
            for (int j = 0; j < i; ++j) {
                if (blocks[i] == blocks[j]) valid = 0;
            }
        }

        if (!valid) {
            printf("Allocation failed: one or more blocks are invalid/already allocated.\n");
        } else {
            used[indexBlock] = 1;
            for (int i = 0; i < n; ++i) used[blocks[i]] = 1;
            printf("\nAllocated and file indexed.\n");
            printf("Index Block\tData Blocks\n");
            printf("%d\t\t", indexBlock);
            for (int i = 0; i < n; ++i) {
                if (i > 0) printf(" ");
                printf("%d", blocks[i]);
            }
            printf("\n");
        }

        printf("Do you want to enter more files? (1-Yes / 0-No): ");
        if (scanf("%d", &choice) != 1 || choice != 1)
            break;
    }

    return EXIT_SUCCESS;
}
