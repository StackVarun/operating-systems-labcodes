#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 1000
#define MAX_THREAD 4
int array[1000];
int sum[4] = { 0 };

void* sum_array(void* arg)
{
    int thread_part = *(int*)arg;   /* each thread gets its OWN id safely */
    for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++)
    {
        sum[thread_part] += array[i];
    }
    return NULL;
}
void testSum()
{
    pthread_t threads[MAX_THREAD];
    int thread_ids[MAX_THREAD];
    for (int i = 0; i < MAX_THREAD; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, sum_array, (void*)&thread_ids[i]);
    }
    for (int i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < MAX_THREAD; i++)
    {
        printf("Thread %d Sum is : %d \n", i, sum[i]);
    }
    int total_sum = 0;
    for (int i = 0; i < MAX_THREAD; i++)
        total_sum += sum[i];
    printf("\nTotal Sum is : %d\n", total_sum);
}
int main(int argc, char* argv[])
{
    if (argc != 2) { printf("Usage: %s <inputfile>\n", argv[0]); return 1; }
    printf("Reading file: %s\n", argv[1]);
    FILE* fp = fopen(argv[1], "r");
    if (!fp) { perror("fopen"); return 1; }
    int i = 0;
    while (i < MAX && fscanf(fp, "%d", &array[i]) == 1) i++;
    fclose(fp);
    printf("Reading file Complete, integers stored in array.\n\n");
    testSum();
    return 0;
}
