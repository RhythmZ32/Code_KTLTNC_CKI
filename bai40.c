#include <stdio.h>
#include <stdlib.h>

typedef struct { long long s, f, p; } Job;

Job a[10005];
long long dp[10005];

int cmp(const void *x, const void *y) {
    long long diff = ((Job*)x)->f - ((Job*)y)->f;
    return (diff > 0) - (diff < 0);
}

int find(int i) {
    int l = 0, r = i - 1, res = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m].f <= a[i].s) res = m, l = m + 1;
        else r = m - 1;
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &a[i].s, &a[i].f, &a[i].p);
    }
    qsort(a, n, sizeof(Job), cmp);

    for (int i = 0; i < n; i++) {
        int idx = find(i);
        long long inc = a[i].p + (idx != -1 ? dp[idx + 1] : 0);
        dp[i + 1] = inc > dp[i] ? inc : dp[i];
    }

    printf("%lld\n", dp[n]);
    return 0;
}
