/**
 * 若矩阵A(m*n)中的某个元素a是第i行中的最小值，同时又是第j列中的最大值，则称此元素为该矩阵中的一个马鞍点。
 * 假设以二维数组存储矩阵Ａ(m*n)，试编写求出矩阵中所有马鞍点的算法，并分析你的算法在最坏情况下的时间复杂度。
 */

#include <stdio.h>
#define YES 1
#define NO 0
#define MAXSIZE 20

int main() {
    int matrix[MAXSIZE][MAXSIZE];
    int row_size, col_size;

    scanf("%d %d", &row_size, &col_size);
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            int is_min_row = YES;
            int is_max_col = YES;

            for (int k = 0; k < row_size; k++) {
                if (matrix[i][j] < matrix[k][j]) {
                    is_max_col = NO;
                }
            }
            for (int k = 0; k < col_size; k++) {
                if (matrix[i][j] > matrix[i][k]) {
                    is_min_row = NO;
                }
            }

            if (is_max_col && is_min_row) {
                printf("%d ", matrix[i][j]);
            }
        }
    }
    return 0;
}
