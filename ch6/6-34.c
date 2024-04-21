/**
 * 二叉树父子结点判断
 */

#include <stdio.h>
#define MAXSIZE 20

int main() {
    int T[MAXSIZE];
    int L[MAXSIZE];
    int R[MAXSIZE];
    int u, v;
    int c;
    int len = 0;
    int result = 0;

    // 获取 T 数组和长度
    for (int i = 0; i < MAXSIZE; i++) {
        scanf("%d", &T[i]);
        len++;
        if ((c = getchar()) == '\n') {
            break;
        }
    }
    // 获取 L 数组
    for (int i = 0; i < len; i++) {
        scanf("%d", &L[i]);
    }
    // 获取 R 数组
    for (int i = 0; i < len; i++) {
        scanf("%d", &R[i]);
    }
    // 获取 u 和 v
    scanf("%d %d", &u, &v);

    // 判断 u 是否为 v 的子孙
    for (int i = u; i != 0; i = T[i]) {
        if (i == v) {
            result = 1;
        }
    }

    // 打印结果
    printf("%d\n", result);

    return 0;
}