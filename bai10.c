#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int n;
    scanf("%d", &n);

    long long *arr = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    int p[2];
    if (pipe(p) < 0) {
        free(arr);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        free(arr);
        return 1;
    }

    if (pid > 0) {
        close(p[0]);
        write(p[1], &n, sizeof(n));
        write(p[1], arr, n * sizeof(long long));
        close(p[1]);
        free(arr);
        waitpid(pid, NULL, 0);
    } else {
        free(arr);
        close(p[1]);

        int child_n = 0;
        read(p[0], &child_n, sizeof(child_n));

        long long sum = 0;
        long long val;

        for (int i = 0; i < child_n; i++) {
            read(p[0], &val, sizeof(val));
            sum += val;
        }

        close(p[0]);
        printf("%lld\n", sum);
    }

    return 0;
}
