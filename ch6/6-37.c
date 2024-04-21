/**
 * 使用栈的基本操作写出二叉树先序遍历的非递归形式的算法。
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_SIZE  20

/* 树的结点 */
typedef struct {
    char Elem;
    int lchild, rchild;
} TNode;

/* 栈的链式存储结构 */
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode, *LinkStackPtr;

typedef struct LinkStack {
    LinkStackPtr top;
    int count;
} LinkStack;

LinkStack *L;
int *pbase;

/**
 * 进栈操作
 */
void Push(LinkStack *S, int e) {
    LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
    s->data = e;
    s->next = S->top;
    S->top = s;
    S->count++;
}

/**
 * 出栈操作
 */
void Pop(LinkStack *S, int *e) {
    LinkStackPtr p;
    *e = S->top->data;
    p = S->top;
    S->top = S->top->next;
    free(p);
    S->count--;
}

/**
 * 先序遍历
 */
void PreOrderTraverse(int i, TNode *T) {
    // 先打印结点
    if (i == 1) {
        printf("%c", T[1].Elem);
    } else {
        printf(" %c", T[i].Elem);
    }
    // 查看左右孩子
    if (T[i].lchild == -1) {
        if (T[i].rchild != -1) {
            PreOrderTraverse(T[i].rchild, T);
        }
    } else {
        if (T[i].rchild == -1) {
            PreOrderTraverse(T[i].lchild, T);
        } else {
            Push(L, T[i].rchild);
            PreOrderTraverse(T[i].lchild, T);
            Pop(L, pbase);
            PreOrderTraverse(*pbase, T);
        }
    }
}

int main() {
    TNode T[MAX_TREE_SIZE];
    int c;

    pbase = (int *)malloc(sizeof(int));
    L = (LinkStack *)malloc(sizeof(LinkStack));

    // 读取输入到树中
    for (int i = 1; i < MAX_TREE_SIZE; i++) {
        if ((scanf("%c %d %d\n", &T[i].Elem, &T[i].lchild, &T[i].rchild)) != 3) {
            break;
        }
    }

    // 先序遍历
    PreOrderTraverse(1, T);

    // 打印换行符
    printf("\n");

    // 释放内存
    free(pbase);
    return 0;
}