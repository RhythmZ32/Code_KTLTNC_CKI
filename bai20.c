#include <pthread.h>
#include <stdio.h>

int n;
int count = 1;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *print_odd(void *arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        while (count <= n && count % 2 == 0) {
            pthread_cond_wait(&cond, &lock);
        }
        if (count > n) {
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&lock);
            break;
        }
        printf("%d ", count);
        count++;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *print_even(void *arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        while (count <= n && count % 2 != 0) {
            pthread_cond_wait(&cond, &lock);
        }
        if (count > n) {
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&lock);
            break;
        }
        printf("%d ", count);
        count++;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    scanf("%d", &n);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, print_odd, NULL);
    pthread_create(&t2, NULL, print_even, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\n");

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
