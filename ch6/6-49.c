/**
 * 编写算法判定给定二叉树是否为完全二叉树。
 */

#include <stdio.h>
#define MAXSIZE 20

/* 树的结点 */
typedef struct {
    char Elem;
    int lchild, rchild;
    int order;
} TNode;

TNode T[MAXSIZE];

int max(int a, int b, int c) {
    int max_val;
    max_val = (a >= b) ? a : b;
    max_val = (max_val >= c) ? max_val : c;
    return max_val;
}

int main(){
    int len = 0;
    int max_order = 1;

    // 读取输入到树中，并设置好顺序
    T[1].order = 1;
    for (int i = 1; i < MAXSIZE; i++) {
        if ((scanf("%c %d %d\n", &T[i].Elem, &T[i].lchild, &T[i].rchild)) != 3) {
            break;
        }
        if (T[i].lchild != -1) {
            T[T[i].lchild].order = 2 * T[i].order;
        }
        if (T[i].rchild != -1) {
            T[T[i].rchild].order = 2 * T[i].order + 1;
        }
        max_order = max(max_order, T[T[i].lchild].order, T[T[i].rchild].order);
        len++;
    }


    // 打印结果
    printf((max_order == len) ? "Yes\n" : "No\n");
    return 0;
}
