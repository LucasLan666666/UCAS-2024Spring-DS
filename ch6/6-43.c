/**
 * 编写递归算法，将二叉树中所有节点的左、右子树相互交换。
 */

#include <stdio.h>
#define MAXSIZE 20

int main() {
    int L[MAXSIZE];
    int R[MAXSIZE];
    int len;
    int c;

    // 获取 L 数组和长度
    for (int i = 0; i < MAXSIZE; i++) {
        scanf("%d", &L[i]);
        len++;
        if ((c = getchar()) == '\n') {
            break;
        }
    }
    // 获取 R 数组
    for (int i = 0; i < len; i++) {
        scanf("%d", &R[i]);
    }

    // 交换左右子树
    for (int i = 0; i < len; i++) {
        L[i] = L[i] ^ R[i];
        R[i] = L[i] ^ R[i];
        L[i] = L[i] ^ R[i];
    }

    // 打印左右子树
    printf("%d", L[0]);
    for (int i = 1; i < len; i++) {
        printf(" %d", L[i]);
    }
    printf("\n");
    printf("%d", R[0]);
    for (int i = 1; i < len; i++) {
        printf(" %d", R[i]);
    }
    printf("\n");

    return 0;
}