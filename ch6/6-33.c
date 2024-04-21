/**
 * 二叉树子孙结点判断
 */

#include <stdio.h>
#define MAXSIZE 20

int isChild(int u, int v, int *L, int *R) {
    if (u == L[v] || u == R[v]) { // u 恰好为 v 子结点
        return 1;
    } else if (L[v] == R[v] == 0) { // v 没有子节点
        return 0;
    } else { // v 有至少一个子节点，检查 u 是否为其子节点的子孙结点
        return (   L[v] != 0 && isChild(u, L[v], L, R)
                || R[v] != 0 && isChild(u, R[v], L, R)
                );
    }
}

int main() {
    int L[MAXSIZE];
    int R[MAXSIZE];
    int u, v;
    int c;
    int len = 0;
    int result = 0;

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
    // 获取 u 和 v
    scanf("%d %d", &u, &v);

    // 判断 u 是否为 v 的子孙
    result = isChild(u, v, L, R);

    // 打印结果
    printf("%d\n", result);

    return 0;
}