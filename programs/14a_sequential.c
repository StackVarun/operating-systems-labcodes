#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_DISK_BLOCKS 32
#define TOTAL_DISK_INODES 8
#define MAX_FILES (TOTAL_DISK_BLOCKS - TOTAL_DISK_INODES)
#define MAX_NAME 20

static int blockStatus[TOTAL_DISK_BLOCKS];

/* Returns start block on success, -1 if no contiguous region is available. */
static int allocateBlocks(int size) {
    if (size <= 0 || size > MAX_FILES) return -1;
    for (int start = TOTAL_DISK_INODES;
    start + size <= TOTAL_DISK_BLOCKS; ++start) {
        int freeBlocks = 1;
        for (int b = start; b < start + size; ++b) {
            if (blockStatus[b]) { freeBlocks = 0; break; }
        }
        if (freeBlocks) {
            for (int b = start; b < start + size; ++b) blockStatus[b] = 1;
            return start;
        }
    }
    return -1;
}

int main(void) {
    int n;
    printf("File allocation method: SEQUENTIAL\n");
    printf("Total blocks: %d\n", TOTAL_DISK_BLOCKS);
    printf("File allocation starts at block: %d\n", TOTAL_DISK_INODES);
    printf("File allocation ends at block: %d\n", TOTAL_DISK_BLOCKS - 1);
    printf("Size (kB) of each block: 1\n\n");

    printf("Enter no. of files: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_FILES) {
        printf("Invalid number of files.\n");
        return 1;
    }

    struct File { char name[MAX_NAME]; int size; int start; } files[MAX_FILES];
    for (int i = 0; i < n; ++i) {
        printf("\nEnter the name of file #%d: ", i + 1);
        if (scanf("%19s", files[i].name) != 1) return 1;
        printf("Enter the size (kB) of file #%d: ", i + 1);
        if (scanf("%d", &files[i].size) != 1 || files[i].size <= 0) {
            printf("Invalid file size.\n");
            return 1;
        }
        files[i].start = allocateBlocks(files[i].size);
        if (files[i].start < 0) {
            printf("Insufficient contiguous free blocks for %s.\n", files[i].name);
            return 1;
        }
    }

    printf("\n%-15s %-10s %s\n", "FILE", "SIZE", "BLOCKS OCCUPIED");
    for (int i = 0; i < n; ++i) {
        printf("%-15s %-10d ", files[i].name, files[i].size);
        for (int b = 0; b < files[i].size; ++b) {
            printf("%d%s", files[i].start + b,
                b == files[i].size - 1 ? "" : "-");
        }
        printf("\n");
    }
    printf("\nFile allocation completed.\n");
    return 0;
}
