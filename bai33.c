#include <stdio.h>
#include <stdlib.h>

long long min(long long a, long long b) { return (a < b) ? a : b; }

int main() {
    long long n;
    scanf("%lld", &n);

    long long *cost = (long long *)calloc(n + 1, sizeof(long long));
    long long *dp = (long long *)calloc(n + 1, sizeof(long long));

    for (long long i = 1; i <= n; i++) {
        scanf("%lld", &cost[i]);
    }

    if (n == 1) {
        printf("%lld\n", cost[1]);
        free(cost);
        free(dp);
        return 0;
    }

    dp[1] = cost[1];
    dp[2] = cost[2];

    for (long long i = 3; i <= n; i++) {
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    }

    printf("%lld\n", dp[n]);

    free(cost);
    free(dp);
    return 0;
}
