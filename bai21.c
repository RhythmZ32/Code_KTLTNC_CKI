#include <pthread.h>
#include <stdio.h>

#define MAX_K 16
int k;
long long a[MAX_K];
long long b[MAX_K];

pthread_mutex_t barrier_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t barrier_cond = PTHREAD_COND_INITIALIZER;
int count;

void custom_barrier_wait() {
    pthread_mutex_lock(&barrier_mutex);
    count++;
    if (count == k) {
        pthread_cond_broadcast(&barrier_cond);
    } else {
        while (count < k) {
            pthread_cond_wait(&barrier_cond, &barrier_mutex);
        }
    }
    pthread_mutex_unlock(&barrier_mutex);
}

void *thread_routine(void *arg) {
    int i = *(int *)arg;
    a[i] = a[i] * a[i];
    custom_barrier_wait();
    b[i] = a[i] + a[(i + 1) % k];
    return NULL;
}

int main() {
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%lld", &a[i]);
    }

    pthread_t threads[MAX_K];
    int thread_id[MAX_K];

    for (int i = 0; i < k; i++) {
        thread_id[i] = i;
        pthread_create(&threads[i], NULL, thread_routine, &thread_id[i]);
    }

    for (int i = 0; i < k; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < k; i++) {
        printf("%lld ", b[i]);
        if (i == k - 1) {
            printf("\n");
        }
    }
    pthread_mutex_destroy(&barrier_mutex);
    pthread_cond_destroy(&barrier_cond);

    return 0;
}
