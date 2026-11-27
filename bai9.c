#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    pid_t pid = fork();

    if (pid < 0) {
        return 1;
    } 
    
    if (pid == 0) {
        long long sum = 0;
        for (long long i = a; i <= b; i++) {
            sum = (sum + i) % 200;
        }
        exit((int)sum);
    } else {
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            int result = WEXITSTATUS(status);
            printf("%d\n", result);
        }
    }

    return 0;
}
