#include <stdio.h>
#include <stdlib.h>
#include "head.h"
#define MAX_TREE_SIZE 100



// 双亲表示法

typedef struct PTNode { // 结点结构
    TElemType data;
    int parent;
} PTNode;

typedef struct { // 树结构
    PTNode nodes[MAX_TREE_SIZE];
    int r, n; // 根的位置和结点数
} PTree;



// 孩子表示法

typedef struct CTNode { // 孩子结构
    int child;
    struct CTNode *next;
} *ChildPtr;

typedef struct { // 表头结构
    TElemType data;
    ChildPtr firstchild;
} CTBox;

typedef struct { // 树结构
    CTBox nodes[MAX_TREE_SIZE]; // 结点数组
    int r, n; // 根的位置和结点数
} CTree;



// 孩子兄弟表示法

typedef struct CSNode {
    TElemType data;
    struct CSNode *firstchild, *rightchild;
} CSNode, *CSTree;



// 二叉树的二叉树链表结点结构定义

typedef struct BiTNode { // 结点结构
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;



// 二叉树的遍历

void PreOrderTraverse(BiTree T) { // 二叉树的前序遍历递归算法
    if (T == NULL) {
        return;
    }
    printf("%c", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

void InOrderTraverse(BiTree T) { // 二叉树的中序遍历递归算法
    if (T == NULL) {
        return;
    }
    InOrderTraverse(T->lchild);
    printf("%c", T->data);
    InOrderTraverse(T->rchild);
}

void PostOrderTraverse(BiTree T) { // 二叉树的后序遍历递归算法
    if (T == NULL) {
        return;
    }
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c", T->data);
}



// 二叉树的建立

void CreateBiTree (BiTree *T) { // 按前序输入结点，# 表示空树
    char ch;
    scanf("%c", &ch);
    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (*T == NULL) {
            exit(OVERFLOW);
        }
        (*T)->data = ch; // 生成根节点
        CreateBiTree(&(*T)->lchild); // 构造左子树
        CreateBiTree(&(*T)->rchild); // 构造右子树
    }
}



// 线索二叉树

typedef enum {Link, Thread} PointerTag; // Link：指向左右孩子；Thread：指向前驱后继纤索

typedef struct BiThrNode { // 二叉线索存储结点结构
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;

BiThrTree pre; // 全局变量，始终指向刚刚访问过的结点

void InThreading(BiThrTree p) { // 中序遍历进行中序线索化
    if (p != NULL) {
        InThreading(p->lchild); // 递归左子树线索化

        if (p->lchild == NULL) { // 没有左孩子
            p->LTag = Thread; // 前驱线索
            p->lchild = pre; // 左孩子指针指向前驱
        }
        if (pre->rchild) { // 前驱没有右孩子
            pre->RTag = Thread; // 后继线索
            pre->rchild = p; // 前驱右孩子指针指向后继（当结点 p）
        }
        pre = p; // 保持 pre 指向 p 的前驱

        InThreading(p->rchild); // 递归右子树线索化
    }
}

void InOrderTraverse_Thr(BiThrTree T) { // 中序遍历二叉线索链表表示的二叉树 T
// T 指向头结点，头结点 lchild 指向根结点，rchild 指向中序遍历的最后一个结点
    BiThrTree p;
    p = T->lchild; // p 指向根节点
    while (p != T) { // 空树或遍历结束时，p==T
        while (p->LTag == Link) { // LTag==0 时循环到中序序列第一个结点
            p = p->lchild;
        }
        printf("%c", p->data); // 显示结点数据，可更改为其他操作
        while (p->RTag == Thread && p->rchild != T) {
            p = p->rchild;
            printf("%c", p->data);
        }
        p = p->rchild; // p 进至其右子树根
    }
}
