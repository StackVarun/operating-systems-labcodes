#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 15
#define MAX_NAME 20

struct Directory {
    char fileName[MAX_FILES][MAX_NAME];
    char dirName[MAX_NAME];
    int fno;
};

static struct Directory dir;

static void insertFile(void) {
    if (dir.fno >= MAX_FILES) { printf("Directory is full.\n"); return; }
    printf("Enter the file name: ");
    scanf("%19s", dir.fileName[dir.fno]);
    dir.fno++;
    printf("File inserted.\n");
}

static void displayFiles(void) {
    printf("\nDirectory: %s\n", dir.dirName);
    if (dir.fno == 0) { printf("No files.\n"); return; }
    for (int i = 0; i < dir.fno; ++i) printf("%d. %s\n", i + 1, dir.fileName[i]);
}

static void deleteFile(void) {
    char name[MAX_NAME];
    printf("Enter the file to be deleted: ");
    scanf("%19s", name);
    for (int i = 0; i < dir.fno; ++i) {
        if (strcmp(dir.fileName[i], name) == 0) {
            printf("%s is deleted.\n", dir.fileName[i]);
            strcpy(dir.fileName[i], dir.fileName[dir.fno - 1]);
            dir.fno--;
            return;
        }
    }
    printf("File %s not found.\n", name);
}

static void searchFile(void) {
    char name[MAX_NAME];
    printf("Enter the file to be searched: ");
    scanf("%19s", name);
    for (int i = 0; i < dir.fno; ++i) {
        if (strcmp(dir.fileName[i], name) == 0) {
            printf("The file is found at position %d.\n", i + 1);
            return;
        }
    }
    printf("The file is not found.\n");
}

int main(void) {
    int op;
    dir.fno = 0;
    printf("Enter the directory name: ");
    scanf("%19s", dir.dirName);
    while (1) {
        printf("\n1. Insert a file\n2. Display files\n3. Delete a file\n4. Search for a file\n5. Exit\nChoose:");
        scanf("%d", &op);
        switch (op) {
            case 1: insertFile(); break;
            case 2: displayFiles(); break;
            case 3: deleteFile(); break;
            case 4: searchFile(); break;
            case 5: return 0;
            default: printf("Invalid option.\n");
        }
    }
}
