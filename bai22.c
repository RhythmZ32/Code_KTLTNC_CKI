#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int B, n;
int *x;
int *buffer;
int head = 0;
int tail = 0;
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    for (int i = 0; i < n; i++) {
        pthread_mutex_lock(&mutex);
        while (count == B) {
            pthread_cond_wait(&not_full, &mutex);
        }
        buffer[tail] = x[i];
        tail = (tail + 1) % B;
        count++;
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    long long total_sum = 0;
    for (long long i = 1; i <= n; i++) {
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }
        int val = buffer[head];
        head = (head + 1) % B;
        count--;
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);

        total_sum += i * val;
    }
    long long *result = malloc(sizeof(long long));
    *result = total_sum;
    return result;
}

int main() {
    scanf("%d %d", &B, &n);

    x = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }

    buffer = (int *)malloc(sizeof(int) * B);

    pthread_t prod_thread, cons_thread;

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);

    long long *ans;
    pthread_join(cons_thread, (void **)&ans);

    printf("%lld\n", *ans);

    free(ans);
    free(buffer);
    free(x);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}
