/**
 * 线索二叉树插入
 */

#include <stdio.h>
#define MAXSIZE 20

typedef struct {
    int L;
    int R;
} TNode;

int GetTree(TNode *T) {
    int c;
    int len = 0;
    for (int i = 0; i < MAXSIZE; i++) {
        scanf("%d", &T[i].L);
        len++;
        if ((c = getchar()) == '\n') {
            break;
        }
    }
    for (int i = 0; i < len; i++) {
        scanf("%d", &T[i].R);
    }
    return len;
}

void Insert(TNode *T_1, TNode *T_2, int p, int len_1, int len_2) {
    int offset = T_2[0].L - 1;
    int temp = T_1[p].L;
    T_1[p].L = T_2[0].L;
    T_2[1].R = temp;
    for (int i = 1; i < len_2; i++) {
        T_1[offset + i].L = T_2[i].L;
        T_1[offset + i].R = T_2[i].R;
    }
}

// 中序遍历，但不打印第一个
void InOrderTraverse(TNode *T, int base, int first) {
    if (T[base].L != 0) {
        InOrderTraverse(T, T[base].L, first);
    }
    if (base != first) {
        printf(" %d", base);
    }
    if (T[base].R != 0) {
        InOrderTraverse(T, T[base].R, first);
    }
}

int main() {
    TNode T_1[MAXSIZE];
    TNode T_2[MAXSIZE];
    int p;

    int len_1 = 0;
    int len_2 = 0;

    // 获取 T_1 数组
    len_1 = GetTree(T_1);
    // 获得 *p
    scanf("%d", &p);
    // 获取 T_2 数组
    len_2 = GetTree(T_2);

    // 将 T_2 接入 T_1
    Insert(T_1, T_2, p, len_1, len_2);

    // 中序遍历
    int first = 1;
    while(T_1[first].L != 0) {
        first = T_1[first].L;
    }
    printf("%d", first);
    InOrderTraverse(T_1, 1, first);
    printf("\n");

    return 0;
}
