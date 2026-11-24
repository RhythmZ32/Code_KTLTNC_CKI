#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int k;
    scanf("%d", &k);

    int pipefd[2];
    pipe(pipefd);

    pid_t pids[20];

    for (int i = 1; i <= k; i++) {
        pids[i - 1] = fork();
        
        if (pids[i - 1] < 0) {
            return 1;
        }

        if (pids[i - 1] == 0) {
            close(pipefd[0]);
            
            long long val = (long long)i * i * i;
            
            write(pipefd[1], &val, sizeof(val));
            close(pipefd[1]);
            
            // Thoát ngay bằng _exit(0) để không sinh tiến trình cháu
            _exit(0);
        }
    }

    close(pipefd[1]);

    long long total_sum = 0;
    for (int i = 0; i < k; i++) {
        long long val = 0;
        read(pipefd[0], &val, sizeof(val));
        total_sum += val;
    }
    close(pipefd[0]);

    // Thu gom toàn bộ k tiến trình con bằng waitpid()
    for (int i = 0; i < k; i++) {
        waitpid(pids[i], NULL, 0);
    }

    printf("%lld\n", total_sum);

    return 0;
}
