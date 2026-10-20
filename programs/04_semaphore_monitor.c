#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#include<sched.h>

int philNo[5] = { 0, 1, 2, 3, 4 };
/* my_semaphore structure -- a semaphore built using a mutex + condition
variable (this is what makes it a "monitor style" semaphore) */
typedef struct {
    /* Semaphore mutual exclusion variable */
    pthread_mutex_t mutex;
    /* Semaphore count variable */
    int cnt;
    /* Semaphore condition variable */
    pthread_cond_t conditional_variable;
} my_semaphore;

/* Function to initialise the semaphore variables */
int init(my_semaphore *sema, int pshared, int val) {
    /* The case when pshared == 1 is not implemented because it is not
    required here -- the semaphore is only shared between threads
    of the same process */
    if (pshared == 1) {
        printf("Cannot handle semaphores shared between processes!!! Exiting\n");
        return -1;
    }
    /* Initialising the mutex */
    pthread_mutex_init(&sema->mutex, NULL);
    /* Initialising the semaphore condition variable */
    pthread_cond_init(&sema->conditional_variable, NULL);
    /* Initialising the semaphore count variable */
    sema->cnt = val;
    return 0;
}

/* wait() (P operation) on the semaphore */
void my_wait(my_semaphore *sema) {
    pthread_mutex_lock(&sema->mutex);
    while (sema->cnt <= 0) {
        pthread_cond_wait(&sema->conditional_variable, &sema->mutex);
    }
    sema->cnt--;
    pthread_mutex_unlock(&sema->mutex);
}

/* signal() (V operation) on the semaphore */
void my_signal(my_semaphore *sema) {
    pthread_mutex_lock(&sema->mutex);
    sema->cnt++;
    pthread_cond_signal(&sema->conditional_variable);
    pthread_mutex_unlock(&sema->mutex);
}

#define N 5
my_semaphore fork_sem[N];   /* one semaphore per fork */
my_semaphore room_sem;      /* limits the dining room to N-1 philosophers
-- classic trick to avoid deadlock */

void* philosopher(void* num) {
    int id = *(int*)num;
    int left  = id;
    int right = (id + 1) % N;

    while (1) {
        /* think for a bit */
        usleep((rand() % 500) * 1000);

        /* only N-1 philosophers are allowed to try to sit down at once,
        which guarantees at least one philosopher can always get both
        forks -- this prevents the circular-wait deadlock */
        my_wait(&room_sem);

        my_wait(&fork_sem[left]);
        my_wait(&fork_sem[right]);

        printf("Philosopher %d with ID %lu eats using forks %d and %d\n",
            id, (unsigned long)pthread_self(), left + 1, right + 1);

        usleep((rand() % 300) * 1000); /* eating */

        my_signal(&fork_sem[right]);
        my_signal(&fork_sem[left]);

        my_signal(&room_sem);
    }
    return NULL;
}

int main() {
    pthread_t tid[N];

    for (int i = 0; i < N; i++)
        init(&fork_sem[i], 0, 1);
    init(&room_sem, 0, N - 1);

    for (int i = 0; i < N; i++)
        pthread_create(&tid[i], NULL, philosopher, (void*)&philNo[i]);

    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
