/**
 * 已知线性表中的元素以递增有序排列，并以单链表为存储结构。试写一高效算法，删除表中所有值大于mink且小于maxk的元素（若表中存在这样的元素），同时释放被删节点的空间。
 * 注意：mink和maxk是给定的两个参变量，他们的值可以和表中的元素相同，也可以不同。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode {
    int data;
    struct Lnode *next;
} Lnode;

Lnode *lalloc(void);
Lnode *delete(Lnode *plist, int min, int max);
void printlist(Lnode *plist);

int main() {
    Lnode *p, *plist;
    int min, max;
    int data;
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

    scanf("%d %d", &min, &max);
    plist = delete(plist, min, max);
    printlist(plist);
    return 0;
}

Lnode *lalloc(void) {
    return (Lnode *)malloc(sizeof(Lnode));
}

Lnode *delete(Lnode *plist, int min, int max) {
    Lnode *pre;
    Lnode *tmp;
    while (plist->data > min && plist->data < max) {
        free(plist);
        plist = plist->next;
    }
    if (plist->next != NULL) {
        pre = plist;
        while (pre->next != NULL && (pre->next->data <= min || pre->next->data >= max)) {
            pre = pre->next;
        }
        while (pre->next != NULL && pre->next->data > min && pre->next->data < max) {
            tmp = pre->next;
            pre->next = pre->next->next;
            free(tmp);
        }
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
