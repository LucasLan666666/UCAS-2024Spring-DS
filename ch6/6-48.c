/**
 * 求距离两个二叉树节点最近的共同祖先
 */

#include <stdio.h>
#include <stdlib.h>

// 结点结构
typedef struct BiTNode {
    char Elem;
    struct BiTNode *lchild, *rchild, *parent;
} BiTNode, *BiTree;

// 二叉树的建立
void CreateBiTree (BiTree *T, BiTNode *parent) { // 按前序输入结点，^ 表示空树
    char ch;
    scanf("%c", &ch);
    if (ch == '^') {
        *T = NULL;
    } else {
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->Elem = ch; // 生成根结点
        (*T)->parent = parent; // 生成父结点
        CreateBiTree(&(*T)->lchild, *T); // 构造左子树
        CreateBiTree(&(*T)->rchild, *T); // 构造右子树
    }
}

// 在二叉树 T 中寻找数据为 c 的子结点，有则返回指向该结点指针，没有则返回 NULL
BiTNode *FindDescendant(char c, BiTree T) {
    if (T == NULL) {
        return NULL;
    } else {
        BiTNode *a, *b;
        if (T->lchild != NULL) {
            if (T->lchild->Elem == c) {
                return T->lchild;
            }
            a = FindDescendant(c, T->lchild);
            if (a != NULL && a->Elem == c) {
                return a;
            }
        }
        if (T->rchild != NULL) {
            if (T->rchild->Elem == c) {
                return T->rchild;
            }
            b = FindDescendant(c, T->rchild);
            if (b != NULL && b->Elem == c) {
                return b;
            }
        }
        return NULL;
    }
}

// 寻找共同祖先（指针表示）
BiTNode *FindAncestor_ptr(BiTNode *a, BiTNode *b, BiTree T) {
    BiTNode *a_anc, *b_anc;
    a_anc = a->parent;
    while (a_anc != NULL) {
        b_anc = b->parent;
        while (b_anc != NULL) {
            if (a_anc == b_anc) {
                return a_anc;
            }
            b_anc = b_anc->parent;
        }
        a_anc = a_anc->parent;
    }
    return NULL;
}

// 寻找共同祖先（字符表示）
char FindAncestor_char(char p, char q, BiTree T) {
    if (p == T->Elem) { // p 为根结点
        return p;
    } else if (q == T->Elem) { // q 为根结点
        return q;
    } else { // 二者都不是根节点
        BiTNode *a, *b, *c;
        a = FindDescendant(p, T);
        b = FindDescendant(q, T);
        c = FindAncestor_ptr(a, b, T);
        return c->Elem;
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
    char p, q;
    CreateBiTree(&T, NULL);
    getchar(); // 跳过 '\n'
    scanf("%c %c", &p, &q);
    printf("%c\n", FindAncestor_char(p, q, T));
    FreeBiTree(&T);
    return 0;
}