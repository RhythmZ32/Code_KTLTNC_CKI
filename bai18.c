#include <pthread.h>
#include <stdio.h>

long long counter = 0;
pthread_mutex_t lock;

typedef struct {
    int id;
    long long inc;
    long long dec;
} ThreadArgs;

void *thread_routine(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;

    if (args->id % 2 != 0) {
        for (long long i = 0; i < args->inc; i++) {
            pthread_mutex_lock(&lock);
            counter++;
            pthread_mutex_unlock(&lock);
        }
    } else {
        for (long long i = 0; i < args->dec; i++) {
            pthread_mutex_lock(&lock);
            counter--;
            pthread_mutex_unlock(&lock);
        }
    }
    return NULL;
}

int main() {
    int k;
    long long inc, dec;

    scanf("%d %lld %lld", &k, &inc, &dec);

    pthread_mutex_init(&lock, NULL);

    pthread_t threads[16];
    ThreadArgs args[16];

    for (int i = 0; i < k; i++) {
        args[i].id = i + 1;
        args[i].inc = inc;
        args[i].dec = dec;
        pthread_create(&threads[i], NULL, thread_routine, &args[i]);
    }

    for (int i = 0; i < k; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("%lld\n", counter);

    return 0;
}
