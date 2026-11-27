#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int tid;
    int start;
    int end;
} ThreadData;

long long *A;
long long *B;
long long *partial;

void* compute_dot_product(void* arg) {
    ThreadData *data = (ThreadData*) arg;
    long long local_sum = 0;

    for (int i = data->start; i < data->end; i++) {
        local_sum += A[i] * B[i];
    }

    partial[data->tid] = local_sum;
    pthread_exit(NULL);
}

int main() {
    int n, T;
    scanf("%d %d", &n, &T);

    A = (long long*) malloc(n * sizeof(long long));
    B = (long long*) malloc(n * sizeof(long long));
    partial = (long long*) malloc(T * sizeof(long long));

    for (int i = 0; i < n; i++) {
        scanf("%lld", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &B[i]);
    }

    pthread_t threads[T];
    ThreadData thread_data[T];

    int base = n / T;
    int rem = n % T;
    int current_start = 0;

    for (int i = 0; i < T; i++) {
        int count = base + (i < rem ? 1 : 0);
        thread_data[i].tid = i;
        thread_data[i].start = current_start;
        thread_data[i].end = current_start + count;
        current_start += count;

        pthread_create(&threads[i], NULL, compute_dot_product, (void*)&thread_data[i]);
    }

    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    long long total_sum = 0;
    for (int i = 0; i < T; i++) {
        total_sum += partial[i];
    }

    printf("%lld\n", total_sum);

    free(A);
    free(B);
    free(partial);

    return 0;
}
