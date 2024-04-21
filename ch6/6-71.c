/**
 * 凹入表打印树结构
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20

typedef struct CSNode {
    char data;
    struct CSNode *firstchild, *rightsibling;
} CSNode, *CSTree;

typedef struct {
    char data;
    int firstchild, rightsibling;
} CSLNode;

void GetList(CSLNode *L) {
    for (int i = 1; i < MAXSIZE; i++) {
        if ((scanf("%c %d %d\n", &L[i].data, &L[i].firstchild, &L[i].rightsibling)) != 3) {
            break;
        }
    }
}

void CreateCSTree(CSTree *T, CSLNode *L, int base) {
    (*T) = (CSTree)malloc(sizeof(CSLNode));
    (*T)->data = L[base].data;
    if (L[base].firstchild != -1) {
        CreateCSTree(&(*T)->firstchild, L, L[base].firstchild);
    }
    if (L[base].rightsibling != -1) {
        CreateCSTree(&(*T)->rightsibling, L, L[base].rightsibling);
    }
}

void PrintCSTree(CSTree T, int level) {
    if (T == NULL) {
        return;
    }
    for (int i = 1; i < level; i++) {
        printf("-");
    }
    printf("%c\n", T->data);
    CSNode *p;
    p = T->firstchild;
    while (p != NULL) {
        PrintCSTree(p, level + 1);
        p = p->rightsibling;
    }
}

void FreeCSTree(CSTree *T) {
    CSNode *p;
    p = (*T)->firstchild;
    while (p != NULL) {
        FreeCSTree(&p);
        p = p->rightsibling;
    }
    free(*T);
}

int main() {
    CSLNode L[MAXSIZE];
    CSTree T;
    GetList(L);
    CreateCSTree(&T, L, 1);
    PrintCSTree(T, 1);
    FreeCSTree(&T);
    return 0;
}
