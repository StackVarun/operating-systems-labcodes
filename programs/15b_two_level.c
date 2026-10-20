#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRS 10
#define MAX_FILES 10
#define MAX_NAME 20

struct Directory {
    char dname[MAX_NAME];
    char fname[MAX_FILES][MAX_NAME];
    int fcnt;
};

static struct Directory dir[MAX_DIRS];
static int dcnt = 0;

static int findDir(const char *name) {
    for (int i = 0; i < dcnt; ++i)
        if (strcmp(name, dir[i].dname) == 0) return i;
    return -1;
}

static void createDirectory(void) {
    if (dcnt >= MAX_DIRS) { printf("Maximum number of directories reached.\n"); return; }
    printf("Enter name of directory: ");
    scanf("%19s", dir[dcnt].dname);
    dir[dcnt].fcnt = 0;
    dcnt++;
    printf("Directory created.\n");
}

static void createFile(void) {
    char d[MAX_NAME];
    printf("Enter name of the directory: ");
    scanf("%19s", d);
    int di = findDir(d);
    if (di < 0) { printf("Directory %s not found.\n", d); return; }
    if (dir[di].fcnt >= MAX_FILES) { printf("Directory is full.\n"); return; }
    printf("Enter name of the file: ");
    scanf("%19s", dir[di].fname[dir[di].fcnt]);
    dir[di].fcnt++;
    printf("File created.\n");
}

static void deleteFile(void) {
    char d[MAX_NAME], f[MAX_NAME];
    printf("Enter name of the directory: "); scanf("%19s", d);
    int di = findDir(d);
    if (di < 0) { printf("Directory %s not found.\n", d); return; }
    printf("Enter name of the file: "); scanf("%19s", f);
    for (int k = 0; k < dir[di].fcnt; ++k) {
        if (strcmp(f, dir[di].fname[k]) == 0) {
            printf("File %s is deleted.\n", f);
            dir[di].fcnt--;
            strcpy(dir[di].fname[k], dir[di].fname[dir[di].fcnt]);
            return;
        }
    }
    printf("File %s not found.\n", f);
}

static void searchFile(void) {
    char d[MAX_NAME], f[MAX_NAME];
    printf("Enter name of the directory: "); scanf("%19s", d);
    int di = findDir(d);
    if (di < 0) { printf("Directory %s not found.\n", d); return; }
    printf("Enter the name of the file: "); scanf("%19s", f);
    for (int k = 0; k < dir[di].fcnt; ++k) {
        if (strcmp(f, dir[di].fname[k]) == 0) {
            printf("File %s is found.\n", f); return;
        }
    }
    printf("File %s not found.\n", f);
}

static void display(void) {
    if (dcnt == 0) { printf("No directories.\n"); return; }
    printf("\nDirectory\tFiles\n");
    for (int i = 0; i < dcnt; ++i) {
        printf("%s\t\t", dir[i].dname);
        for (int k = 0; k < dir[i].fcnt; ++k) printf("%s ", dir[i].fname[k]);
        printf("\n");
    }
}

int main(void) {
    int ch;
    while (1) {
        printf("\n1. Create Directory\t2. Create File\t3. Delete File\n");
        printf("4. Search File\t\t5. Display\t6. Exit\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: createDirectory(); break;
            case 2: createFile(); break;
            case 3: deleteFile(); break;
            case 4: searchFile(); break;
            case 5: display(); break;
            case 6: return 0;
            default: printf("Invalid choice.\n");
        }
    }
}
