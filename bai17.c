#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int n;
    int *arr;
} ArrayData;

void* calculate_sum(void *arg) {
    ArrayData *data = (ArrayData*)arg;
    
    long long *sum = (long long*)malloc(sizeof(long long));
    if (sum == NULL) {
        pthread_exit(NULL);
    }
    
    *sum = 0;
    for (int i = 0; i < data->n; i++) {
        *sum += data->arr[i];
    }
    
    return (void*)sum;
}

int main() {
    int n;
    scanf("%d", &n);

    int *arr = (int*)malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    ArrayData data;
    data.n = n;
    data.arr = arr;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, calculate_sum, &data);

    long long *result = NULL;
    pthread_join(thread_id, (void**)&result);

    if (result != NULL) {
        printf("%lld\n", *result);
        free(result);
    }

    free(arr);
    return 0;
}
