#include <stdio.h>

#define INF 1000000000

int dp[100005];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n, S;
    scanf("%d %d", &n, &S);

    int c[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }

    dp[0] = 0;
    for (int i = 1; i <= S; i++) {
        dp[i] = INF;
    }

    for (int i = 1; i <= S; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= c[j] && dp[i - c[j]] != INF) {
                dp[i] = min(dp[i], dp[i - c[j]] + 1);
            }
        }
    }

    if (dp[S] == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", dp[S]);
    }

    return 0;
}
