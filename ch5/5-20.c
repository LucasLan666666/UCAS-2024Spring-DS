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
    int is_first;

    scanf("%d %d", &row_size, &col_size);
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    is_first = YES;
    for (int i = row_size - 1; i >= 0; i--) {
        for (int j = col_size - 1; j >= 0; j--) {
            if (matrix[i][j] == 0) {
                continue;
            } else {
                if (is_first == NO) {
                    printf("+");
                }
                if (matrix[i][j] != 1) {
                    printf("%d", matrix[i][j]);
                }
                if (i != 0) {
                    printf("xE%d", i);
                }
                if (j != 0) {
                    printf("yE%d", j);
                }
                is_first = NO;
            }
        }
    }
    printf("\n");

    return 0;
}
