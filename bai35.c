#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int M, N;
    scanf("%d %d", &M, &N);

    int **grid = (int **)malloc(M * sizeof(int *));
    int **dp = (int **)malloc(M * sizeof(int *));
    for (int i = 0; i < M; i++) {
        grid[i] = (int *)malloc(N * sizeof(int));
        dp[i] = (int *)calloc(N, sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Kiểm tra nếu ô xuất phát (0, 0) hoặc ô đích (M-1, N-1) bị chặn
    if (grid[0][0] == 1 || grid[M - 1][N - 1] == 1) {
        printf("0\n");
        for (int i = 0; i < M; i++) {
            free(grid[i]);
            free(dp[i]);
        }
        free(grid);
        free(dp);
        return 0;
    }

    // Khởi tạo điểm xuất phát
    dp[0][0] = 1;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 1) {
                dp[i][j] = 0;
                continue;
            }
            // Đi từ ô phía trên xuống
            if (i > 0) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
            // Đi từ ô bên trái sang
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
        }
    }

    printf("%d\n", dp[M - 1][N - 1]);

    for (int i = 0; i < M; i++) {
        free(grid[i]);
        free(dp[i]);
    }
    free(grid);
    free(dp);

    return 0;
}
