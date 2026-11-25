#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int a[MAX_N];

typedef struct {
    int left;
    int right;
    int local_max;
} ThreadData;

void *find_local_max(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int max_val = a[data->left];
    for (int i = data->left + 1; i <= data->right; i++) {
        if (a[i] > max_val) {
            max_val = a[i];
        }
    }
    data->local_max = max_val;
    return NULL;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // Số luồng thực tế sử dụng là min(n, k)
    int num_threads = (k < n) ? k : n;

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    // Chia đều mảng cho num_threads luồng
    int base_size = n / num_threads;
    int remainder = n % num_threads;
    int current_left = 0;

    for (int i = 0; i < num_threads; i++) {
        int chunk_size = base_size + (i < remainder ? 1 : 0);
        thread_data[i].left = current_left;
        thread_data[i].right = current_left + chunk_size - 1;
        current_left += chunk_size;

        // Truyền con trỏ struct riêng biệt &thread_data[i] cho từng luồng
        pthread_create(&threads[i], NULL, find_local_max, &thread_data[i]);
    }

    // Chờ tất cả các luồng hoàn tất
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Luồng chính duyệt các local_max để tìm global max
    int global_max = thread_data[0].local_max;
    for (int i = 1; i < num_threads; i++) {
        if (thread_data[i].local_max > global_max) {
            global_max = thread_data[i].local_max;
        }
    }

    printf("%d\n", global_max);

    return 0;
}
