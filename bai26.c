#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n, T;
long long *a;
long long *partial;

typedef struct {
    int tid;
} ThreadArgs;

void *compute_partial_sum(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int tid = args->tid;

    // Phân hoạch tĩnh (Static Mapping)
    int base = n / T;
    int rem = n % T;

    int start, count;
    if (tid < rem) {
        start = tid * (base + 1);
        count = base + 1;
    } else {
        start = rem * (base + 1) + (tid - rem) * base;
        count = base;
    }

    int end = start + count;

    long long local_sum = 0;
    for (int i = start; i < end; i++) {
        local_sum += a[i] * a[i];
    }

    partial[tid] = local_sum;

    pthread_exit(NULL);
}

int main() {
    scanf("%d %d", &n, &T);

    // Cấp phát bộ nhớ cho mảng dữ liệu và mảng kết quả từng luồng
    a = (long long *)malloc(n * sizeof(long long));
    partial = (long long *)malloc(T * sizeof(long long));

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    pthread_t *threads = (pthread_t *)malloc(T * sizeof(pthread_t));
    ThreadArgs *t_args = (ThreadArgs *)malloc(T * sizeof(ThreadArgs));

    // Tạo các luồng với pthread_create
    for (int i = 0; i < T; i++) {
        t_args[i].tid = i;
        pthread_create(&threads[i], NULL, compute_partial_sum, (void *)&t_args[i]);
    }

    for (int i = 0; i < T; i++) {
        pthread_join(threads[i], NULL);
    }

    // Luồng chính cộng tổng các kết quả partial
    long long total_sum = 0;
    for (int i = 0; i < T; i++) {
        total_sum += partial[i];
    }

    printf("%lld\n", total_sum);

    free(a);
    free(partial);
    free(threads);
    free(t_args);

    return 0;
}
