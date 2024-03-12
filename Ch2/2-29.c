/**c
 * 已知A，B和C为三个递增有序的线性表，现要求对A表做如下操作：删去那些既在B表中出现又在C表中出现的元素。
 * 试对顺序表编写实现上述操作的算法。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode {
    char c;
    struct Lnode *next;
} Lnode;

Lnode *lalloc(void);
Lnode *buildlist();
void printlist(Lnode *plist);

int main() {
    Lnode *pa, *pb, *pc, *pre;
    Lnode *tmp;

    pa = buildlist();
    pb = buildlist();
    pc = buildlist();

    for (Lnode *pi = pb; pi != NULL; pi = pi->next) {
        for (Lnode *pj = pc; pj != NULL; pj = pj->next) {
            if (pi->c != pj->c) {
                continue;
            } else {
                if (pa != NULL && pa->c == pi->c) {
                    tmp = pa;
                    pa = pa->next;
                    free(tmp);
                }
                if (pa == NULL) {
                    printlist(pa);
                    return 0;
                }
                pre = pa;
                while (pre->next != NULL) {
                    if (pre->next->c == pi->c) {
                        tmp = pre->next;
                        pre->next = pre->next->next;
                        free(tmp);
                    } else {
                        pre = pre->next;
                    }
                }
            }
        }
    }
    printlist(pa);
    return 0;
}

Lnode *buildlist() {
    Lnode *p, *plist;
    char c;

    scanf("%c", &c);
    plist = lalloc();
    plist->c = c;
    plist->next = NULL;
    p = plist;

    while (1) {
        scanf("%c", &c);
        if (c == '\n') {
            break;
        }
        scanf("%c", &c);
        p->next = lalloc();
        p = p->next;
        p->c = c;
        p->next = NULL;
    }
    return plist;
}

Lnode *lalloc(void) {
    return (Lnode *)malloc(sizeof(Lnode));
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
            printf("%c", plist->c);
        } else {
            printf(",%c", pnode->c);
        }
        pnode = pnode->next;
    }
    printf("\n");
}
