/*
** 试写一个判定给定二叉树是否为二叉排序树的算法，设词二叉树以二叉链表为存储结构，且树中节点的
** 关键字均不同
*/

#include <stdio.h>

#define MAX_SIZE 20

typedef struct BiTNode {
    int data;
    int lchild, rchild;
} BiTNode;



void
InitBiTree(BiTNode *T, int max_size)
{
    int i;
    for (i = 0; i < max_size; i++) {
        T[i].data = 0;
        T[i].lchild = 0;
        T[i].rchild = 0;
    }
}



void
BuildBiTree(BiTNode *T, int *size_ptr)
{
    int i = 0;
    int data, lchild, rchild;

    while (scanf("%d%d%d", &data, &lchild, &rchild) == 3 &&
           i < MAX_SIZE)
    {
        T[i].data   = data;
        T[i].lchild = lchild;
        T[i].rchild = rchild;
        i++;
    }
    *size_ptr = i;
}



void
InOrderTraverse(BiTNode *T, int i, int *seq, int *j_ptr)
{
    if (i == -1)
        return;

    InOrderTraverse(T, T[i].lchild, seq, j_ptr);
    seq[*j_ptr] = T[i].data;
    (*j_ptr)++;
    InOrderTraverse(T, T[i].rchild, seq, j_ptr);
}



int
JudgeInOrder(BiTNode *T, int size)
{
    int seq[MAX_SIZE];
    int i = 0, j = 0;   /* i for T, j for seq */
    InOrderTraverse(T, i, seq, &j);

    int k;
    for (k = 0; k < size - 1; k++) {
        if (seq[k] > seq[k + 1])
            return 0;
    }
    return 1;
}



int
main(void)
{
    BiTNode T[MAX_SIZE];
    int size;
    InitBiTree(T, MAX_SIZE);
    BuildBiTree(T, &size);
    printf("%d\n", JudgeInOrder(T, size));
    return 0;
}
