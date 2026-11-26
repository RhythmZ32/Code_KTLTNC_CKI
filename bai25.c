#include <pthread.h>
#include <stdio.h>

#define MAX_THREADS 16

typedef struct {
    int id;
    long long L, R, d;
} ThreadArg;

long long counts[MAX_THREADS];

void *worker(void *arg) {
    ThreadArg *data = (ThreadArg *)arg;
    long long local_count = 0;
    for (long long i = data->L; i <= data->R; i++) {
        if (i % 2 != 0 && i % data->d == 0) {
            local_count++;
        }
    }
    counts[data->id] = local_count;
    pthread_exit(NULL);
}

int main() {
    long long L, R, d;
    int T;
    scanf("%lld %lld %lld %d", &L, &R, &d, &T);

    pthread_t threads[MAX_THREADS];
    ThreadArg thread_data[MAX_THREADS];

    long long n = R - L + 1;
    long long chunk_size = n / T;
    long long remainder = n % T;

    long long current = L;
    for (int i = 0; i < T; i++) {
        long long count = chunk_size + (i < remainder ? 1 : 0);
        thread_data[i].id = i;
        thread_data[i].L = current;
        thread_data[i].R = current + count - 1;
        thread_data[i].d = d;
        current += count;
        pthread_create(&threads[i], NULL, worker, &thread_data[i]);
    }

    long long total_count = 0;
    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
        total_count += counts[i];
    }
    printf("%lld\n", total_count);
    return 0;
}
