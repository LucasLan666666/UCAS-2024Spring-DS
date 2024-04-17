/**
 * 稀疏矩阵加法
 */

#include <stdio.h>
#define MAXSIZE 10

// 写入矩阵的 V 数组，返回长度
void write_V(int *V, int *len) {
    int c;
    *len = 0;
    c = getchar(); // 跳过前一行结尾的 \n
    if ((c = getchar()) == '\n') { // 判断 V 是否为空
        return;
    } else {
        ungetc(c, stdin);
    }
    while (1) {
        scanf("%d", &V[*len]);
        (*len)++;
        if ((c = getchar()) == '\n' || c == EOF) {
            break;
        }
    }
}

// 写入矩阵
void write_M(int M[MAXSIZE][MAXSIZE], int row_size, int col_size) {
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            scanf("%d", &M[i][j]);
        }
    }
}

int main() {
    int row_size, col_size;
    int A[MAXSIZE][MAXSIZE];
    int VA[MAXSIZE*MAXSIZE];
    int B[MAXSIZE][MAXSIZE];
    int VB[MAXSIZE*MAXSIZE];
    int C[MAXSIZE][MAXSIZE];
    int VC[MAXSIZE*MAXSIZE];
    int pa, pb;
    int ele_num_A, ele_num_B, ele_num_C;

    // 写入矩阵行数和列数
    scanf("%d %d", &row_size, &col_size);
    // 写入 A 矩阵相关信息
    write_V(VA, &ele_num_A);
    write_M(A, row_size, col_size);
    // 写入 B 矩阵相关信息
    write_V(VB, &ele_num_B);
    write_M(B, row_size, col_size);

    // 相加，时间复杂度 O(m*n)
    pa = pb = ele_num_C = 0;
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size; j++) {
            if (A[i][j] == 1 && B[i][j] == 1) {
                if (VA[pa] + VB[pb] != 0) {
                    C[i][j] = 1;
                    VC[ele_num_C] = VA[pa] + VB[pb];
                    ele_num_C++;
                } else {
                    C[i][j] = 0;
                }
                pa++, pb++;
            } else if (A[i][j] == 1 && B[i][j] == 0) {
                C[i][j] = 1;
                VC[ele_num_C] = VA[pa];
                pa++, ele_num_C++;
            } else if (A[i][j] == 0 && B[i][j] == 1) {
                C[i][j] = 1;
                VC[ele_num_C] = VB[pb];
                pb++, ele_num_C++;
            } else {
                C[i][j] = 0;
            }
        }
    }

    // 打印 VC
    for (int i = 0; i < ele_num_C - 1; i++) {
        printf("%d ", VC[i]);
    }
    if (ele_num_C == 0) {
        printf("\n");
    } else {
        printf("%d\n", VC[ele_num_C - 1]);
    }
    // 打印 C
    for (int i = 0; i < row_size; i++) {
        for (int j = 0; j < col_size - 1; j++) {
            printf("%d ", C[i][j]);
        }
        printf("%d\n", C[i][col_size - 1]);
    }

    return 0;
}
