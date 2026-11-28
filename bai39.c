#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    long long *p = (long long *)malloc((n + 1) * sizeof(long long));
    long long *r = (long long *)malloc((n + 1) * sizeof(long long));
    int *s = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &p[i]);
    }

    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        long long q = -1;
        for (int i = 1; i <= j; i++) {
            long long val = p[i] + r[j - i];
            // So sánh nghiêm ngặt (>) để ưu tiên i nhỏ nhất khi trùng doanh thu
            if (val > q) {
                q = val;
                s[j] = i;
            }
        }
        r[j] = q;
    }

    // Dòng 1: Doanh thu tối đa r[n]
    printf("%lld\n", r[n]);

    // Dòng 2: Truy vết thứ tự các đoạn cắt
    int temp_n = n;
    int first = 1;
    while (temp_n > 0) {
        if (!first) {
            printf(" ");
        }
        printf("%d", s[temp_n]);
        first = 0;
        temp_n -= s[temp_n];
    }
    printf("\n");

    free(p);
    free(r);
    free(s);

    return 0;
}
