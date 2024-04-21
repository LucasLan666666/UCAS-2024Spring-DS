/**
 * 编写一个算法，输出以二叉树表示的算术表达式，若该表达式中含有括号，则在输出时应添上。
 */

#include <stdio.h>
#include <stdlib.h>

// 结点结构
typedef struct BiTNode {
    char Elem;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 二叉树的建立
void CreateBiTree (BiTree *T) { // 按前序输入结点，# 表示空树
    char ch;
    scanf("%c", &ch);
    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->Elem = ch; // 生成根结点
        CreateBiTree(&(*T)->lchild); // 构造左子树
        CreateBiTree(&(*T)->rchild); // 构造右子树
    }
}

// 表达式中序遍历输出
void PrintBiTree(BiTree T) {
    if (T == NULL) {
        return;
    } else if (T->lchild == NULL) {
        printf("%c", T->Elem);
        return;
    }

    if (   (T->Elem == '*' || T->Elem == '/')
        && (T->lchild->Elem == '+' || T->lchild->Elem == '-')
        )
    {
        printf("(");
    }
    PrintBiTree(T->lchild);
    if (   (T->Elem == '*' || T->Elem == '/')
        && (T->lchild->Elem == '+' || T->lchild->Elem == '-')
        )
    {
        printf(")");
    }

    printf("%c", T->Elem);

    if (   (T->Elem == '+' || T->Elem == '-') && (T->rchild->Elem == '+' || T->rchild->Elem == '-')
        || (T->Elem == '*' || T->Elem == '/') && (T->rchild->Elem == '+' || T->rchild->Elem == '-' || T->rchild->Elem == '*' || T->rchild->Elem == '/')
        )
    {
        printf("(");
    }
    PrintBiTree(T->rchild);
    if (   (T->Elem == '+' || T->Elem == '-') && (T->rchild->Elem == '+' || T->rchild->Elem == '-')
        || (T->Elem == '*' || T->Elem == '/') && (T->rchild->Elem == '+' || T->rchild->Elem == '-' || T->rchild->Elem == '*' || T->rchild->Elem == '/')
        )
    {
        printf(")");
    }
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
    BiTree T;
    CreateBiTree(&T);
    PrintBiTree(T);
    printf("\n");
    FreeBiTree(&T);
    return 0;
}
