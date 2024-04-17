/**
 * 试写一算法，在无头节点的动态单链表上实现线性表操作DELETE(L,i)。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode {
    int data;
    struct Lnode *next;
} Lnode;

Lnode *lalloc(void);
Lnode *delete(Lnode *plist, int base);
void printlist(Lnode *plist);

int main() {
    Lnode *p, *plist;
    int data;
    int base;
    char c;

    scanf("%d", &data);
    p = plist = lalloc();
    plist->data = data;
    plist->next = NULL;
    while (1) {
        scanf("%c", &c);
        if (c == '\n') {
            break;
        }
        p->next = lalloc();
        p = p->next;
        scanf("%d", &data);
        p->data = data;
        p->next = NULL;
    }

    scanf("%d", &base);
    plist = delete(plist, base);
    printlist(plist);
    return 0;
}

Lnode *lalloc(void) {
    return (Lnode *)malloc(sizeof(Lnode));
}

Lnode *delete(Lnode *plist, int base) {
    Lnode *pre = plist;
    if (base == 0) {
        free(plist);
        plist = plist->next;
    } else {
        for (int i = 1; i < base; i++) {
            pre = pre->next;
        }
        free(pre->next);
        pre->next = pre->next->next;
    }
    return plist;
}

void printlist(Lnode *plist) {
    Lnode *pnode;
    pnode = plist;
    if (plist == NULL) {
        printf("NULL\n");
        return;
    }
    while (pnode != NULL) {
        if (pnode == plist) {
            printf("%d", plist->data);
        } else {
            printf(" %d", pnode->data);
        }
        pnode = pnode->next;
    }
    printf("\n");
}
