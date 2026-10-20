#include <stdio.h>
#include <stdlib.h>

#define END_CYLINDER 200
#define MIN_CYLINDER 0
#define MAX_REQUESTS 100

static int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

static void print_order(const int *order, int n) {
    for (int i = 0; i < n; ++i) {
        if (i > 0) printf(" -> ");
        printf("%d", order[i]);
    }
    printf("\n");
}

static void print_result(const char *name, int *order, int n, int total) {
    printf("\n%s\n", name);
    printf("Seek order: ");
    print_order(order, n);
    printf("Total seek time: %d\n", total);
    printf("Average seek time: %.2f\n", (double)total / n);
}

static void fcfs(int hp, const int req[], int n) {
    int order[MAX_REQUESTS], total = 0, pos = hp;
    for (int i = 0; i < n; ++i) {
        total += abs_diff(req[i], pos);
        pos = req[i];
        order[i] = req[i];
    }
    print_result("FCFS", order, n, total);
}

static void sstf(int hp, const int req[], int n) {
    int order[MAX_REQUESTS], used[MAX_REQUESTS] = {0};
    int total = 0, pos = hp;
    for (int k = 0; k < n; ++k) {
        int best = -1;
        for (int i = 0; i < n; ++i) {
            if (!used[i] && (best == -1 ||
                abs_diff(req[i], pos) < abs_diff(req[best], pos) ||
                (abs_diff(req[i], pos) == abs_diff(req[best], pos) && req[i] < req[best]))) {
                best = i;
            }
        }
        used[best] = 1;
        total += abs_diff(req[best], pos);
        pos = req[best];
        order[k] = req[best];
    }
    print_result("SSTF", order, n, total);
}

static void scan(int hp, const int req[], int n) {
    int order[MAX_REQUESTS], count = 0, served[MAX_REQUESTS] = {0};
    int total = 0, pos = hp;

    for (int cylinder = hp; cylinder < END_CYLINDER; ++cylinder) {
        for (int i = 0; i < n; ++i) {
            if (!served[i] && req[i] == cylinder) {
                total += abs_diff(pos, cylinder);
                pos = cylinder;
                order[count++] = cylinder;
                served[i] = 1;
            }
        }
    }
    total += abs_diff(pos, END_CYLINDER);
    pos = END_CYLINDER;

    for (int cylinder = END_CYLINDER - 1; cylinder >= MIN_CYLINDER; --cylinder) {
        for (int i = 0; i < n; ++i) {
            if (!served[i] && req[i] == cylinder) {
                total += abs_diff(pos, cylinder);
                pos = cylinder;
                order[count++] = cylinder;
                served[i] = 1;
            }
        }
    }
    print_result("SCAN", order, n, total);
}

static void cscan(int hp, const int req[], int n) {
    int order[MAX_REQUESTS], count = 0;
    int total = 0, pos = hp;

    for (int cylinder = hp; cylinder < END_CYLINDER; ++cylinder) {
        for (int i = 0; i < n; ++i) {
            if (req[i] == cylinder) {
                total += abs_diff(pos, cylinder);
                pos = cylinder;
                order[count++] = cylinder;
            }
        }
    }
    total += abs_diff(pos, END_CYLINDER);
    pos = END_CYLINDER;
    if (count < n) {
        total += END_CYLINDER; /* return to cylinder 0 without servicing */
        pos = MIN_CYLINDER;
        for (int cylinder = MIN_CYLINDER; cylinder < hp; ++cylinder) {
            for (int i = 0; i < n; ++i) {
                if (req[i] == cylinder) {
                    total += abs_diff(pos, cylinder);
                    pos = cylinder;
                    order[count++] = cylinder;
                }
            }
        }
    }
    print_result("C-SCAN", order, n, total);
}

static void look(int hp, const int req[], int n) {
    int order[MAX_REQUESTS], count = 0;
    int total = 0, pos = hp;
    int max_req = -1;

    for (int i = 0; i < n; ++i)
        if (req[i] >= hp && (max_req == -1 || req[i] > max_req)) max_req = req[i];

    if (max_req != -1) {
        for (int cylinder = hp; cylinder <= max_req; ++cylinder) {
            for (int i = 0; i < n; ++i) {
                if (req[i] == cylinder) {
                    total += abs_diff(pos, cylinder);
                    pos = cylinder;
                    order[count++] = cylinder;
                }
            }
        }
    }

    int min_req = END_CYLINDER;
    for (int i = 0; i < n; ++i)
        if (req[i] < hp && req[i] < min_req) min_req = req[i];

    if (min_req != END_CYLINDER) {
        for (int cylinder = (max_req == -1 ? hp : max_req); cylinder >= min_req; --cylinder) {
            for (int i = 0; i < n; ++i) {
                if (req[i] == cylinder && req[i] < hp) {
                    total += abs_diff(pos, cylinder);
                    pos = cylinder;
                    order[count++] = cylinder;
                }
            }
        }
    }
    print_result("LOOK", order, n, total);
}

static void clook(int hp, const int req[], int n) {
    int order[MAX_REQUESTS], count = 0;
    int total = 0, pos = hp;
    int max_req = -1, min_req = END_CYLINDER;

    for (int i = 0; i < n; ++i) {
        if (req[i] >= hp && (max_req == -1 || req[i] > max_req)) max_req = req[i];
        if (req[i] < hp && req[i] < min_req) min_req = req[i];
    }
    if (max_req != -1) {
        for (int cylinder = hp; cylinder <= max_req; ++cylinder) {
            for (int i = 0; i < n; ++i) {
                if (req[i] == cylinder) {
                    total += abs_diff(pos, cylinder);
                    pos = cylinder;
                    order[count++] = cylinder;
                }
            }
        }
    }

    if (min_req != END_CYLINDER) {
        total += abs_diff(pos, min_req); /* circular jump to lowest request */
        pos = min_req;
        for (int cylinder = min_req; cylinder < hp; ++cylinder) {
            for (int i = 0; i < n; ++i) {
                if (req[i] == cylinder && req[i] != min_req) {
                    total += abs_diff(pos, cylinder);
                    pos = cylinder;
                    order[count++] = cylinder;
                }
            }
        }
        /* include the minimum request in service order if it was not already */
        if (count == 0 || order[count - 1] != min_req) {
            for (int i = n - 1; i >= 0; --i) {
                if (req[i] == min_req) {
                    /* Move it to the front of the lower portion by rebuilding order. */
                    int lower[MAX_REQUESTS], lc = 0;
                    lower[lc++] = min_req;
                    for (int c = min_req + 1; c < hp; ++c)
                        for (int j = 0; j < n; ++j)
                        if (req[j] == c) lower[lc++] = c;
                    int start = 0;
                    while (start < count && order[start] >= hp) start++;
                    count = start;
                    for (int j = 0; j < lc; ++j) order[count++] = lower[j];
                    break;
                }
            }
        }
    }
    print_result("C-LOOK", order, n, total);
}

int main(void) {
    int n, hp, req[MAX_REQUESTS];

    printf("DISK SCHEDULING\n");
    printf("Enter number of I/O requests (1-%d): ", MAX_REQUESTS);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_REQUESTS) {
        fprintf(stderr, "Invalid number of requests.\n");
        return EXIT_FAILURE;
    }

    printf("Enter initial disk arm position (0-199): ");
    if (scanf("%d", &hp) != 1 || hp < 0 || hp >= END_CYLINDER) {
        fprintf(stderr, "Invalid head position.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; ++i) {
        printf("Enter request %d (0-199): ", i + 1);
        if (scanf("%d", &req[i]) != 1 || req[i] < 0 || req[i] >= END_CYLINDER) {
            fprintf(stderr, "Invalid request position.\n");
            return EXIT_FAILURE;
        }
    }

    fcfs(hp, req, n);
    sstf(hp, req, n);
    scan(hp, req, n);
    cscan(hp, req, n);
    look(hp, req, n);
    clook(hp, req, n);

    return EXIT_SUCCESS;
}
