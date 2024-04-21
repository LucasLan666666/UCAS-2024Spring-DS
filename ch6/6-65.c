/**
 * 已知一棵二叉树的前序序列和中序序列分别存于两个一维数组中，试编写算法建立该二叉树的二叉链表，然后输出该二叉链表的后序序列。
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20

typedef struct TNode {
    char data;
    struct TNode *lchild, *rchild;
} BiTNode, *BiTree;

// 构建二叉树
void CreateBiTree(BiTree *T, char *pre, char *in, int len) {
    // 如果为空，退出
    if (len == 0) {
        return;
    }
    // 将根结点数据填入
    char root = pre[0];
    *T = (BiTree)malloc(sizeof(BiTNode));
    (*T)->data = root;

    // 考虑当前 pre 数组和 in 数组，填充左右子树
    int len_l, len_r;
    for (int i = 0; i < len; i++) {
        if (in[i] == root) {
            len_l = i;
            break;
        }
    }
    len_r = len - len_l - 1;
    // 构建左子树
    if (len_l == 0) {
        (*T)->lchild = NULL;
    } else {
        CreateBiTree(&(*T)->lchild, &pre[1], in, len_l);
    }
    // 构建右子树
    if (len_r == 0) {
        (*T)->rchild = NULL;
    } else {
        CreateBiTree(&(*T)->rchild, &pre[len_l + 1], &in[len_l + 1], len_r);
    }
}

// 后序遍历打印二叉树
void Print_PostOrder(BiTree T) {
    if (T == NULL) {
        return;
    }
    if (T->lchild != NULL) {
        Print_PostOrder(T->lchild);
    }
    if (T->rchild != NULL) {
        Print_PostOrder(T->rchild);
    }
    printf("%c", T->data);
}

// 释放二叉树
void FreeBiTree(BiTree *T) {
    if ((*T)->lchild != NULL) {
        free((*T)->lchild);
    }
    if ((*T)->rchild != NULL) {
        free((*T)->rchild);
    }
    free(*T);
}

int main() {
    char PreOrder_Array[MAXSIZE];
    char  InOrder_Array[MAXSIZE];
    int len = 0;
    BiTree T;
    int c;

    // 读取前序遍历的输入
    for (int i = 0; i < MAXSIZE; i++) {
        if ((c = getchar()) != EOF && c != '\n') {
            PreOrder_Array[i] = c;
            len++;
        } else {
            break;
        }
    }
    // 读取中序遍历的输入
    for (int i = 0; i < MAXSIZE; i++) {
        if ((c = getchar()) != EOF && c != '\n') {
            InOrder_Array[i] = c;
        } else {
            break;
        }
    }

    // 构建二叉树
    CreateBiTree(&T, PreOrder_Array, InOrder_Array, len);

    // 后序遍历并打印
    Print_PostOrder(T);
    printf("\n");

    // 释放二叉树
    FreeBiTree(&T);

    return 0;
}