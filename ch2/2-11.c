/**
 * 设顺序表va中的数据为递增有序。写一个算法，将x插入到顺序表的适当位置，保证有序性。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode {
    int data;
    struct Lnode *next;
} Lnode;

Lnode *lalloc(void);
void printlist(Lnode *plist);

int main() {
    Lnode *plist;
    Lnode *p;
    int data;

    // 头结点
    scanf("%d", &data);
    p = lalloc();
    p->data = data;
    p->next = NULL;
    plist = p;

    // 中间结点和尾结点
    while (scanf("%d", &data)) {
        int c = getchar();
        p->next = lalloc();
        p->next->data = data;
        p->next->next = NULL;
        p = p->next;
        if (c == '\n') {
            break;
        }
    }
    p = plist;

    // 插入结点
    Lnode *np = lalloc();
    scanf("%d", &data);
    np->data = data;

    if (plist->data > data) {
        np->next = plist;
        plist = np;
    } else {
        while (p->next != NULL && p->next->data < data) {
            p = p->next;
        }
        np->next = p->next;
        p->next = np;
    }
    printlist(plist);
    return 0;
}

Lnode *lalloc(void) {
    return (Lnode *)malloc(sizeof(Lnode));
}

void printlist(Lnode *plist) {
    Lnode *pnode;
    pnode = plist;
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
