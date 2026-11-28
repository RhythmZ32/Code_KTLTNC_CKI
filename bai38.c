#include <stdio.h>
#include <string.h>

#define MAX_LEN 1005

int dp[MAX_LEN][MAX_LEN];
char X[MAX_LEN];
char Y[MAX_LEN];
char lcs[MAX_LEN];

int main() {
    scanf("%s", X);
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                if (dp[i - 1][j] > dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
    }

    int len = dp[m][n];

    // Trường hợp không có ký tự chung
    if (len == 0) {
        printf("0\nEMPTY\n");
        return 0;
    }

    // Truy vết từ (m, n)
    lcs[len] = '\0';
    int k = len - 1;
    int i = m, j = n;

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[k--] = X[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--; // Giảm i (đi lên)
        } else {
            j--; // Giảm j (đi sang trái)
        }
    }

    printf("%d\n%s\n", len, lcs);

    return 0;
}
