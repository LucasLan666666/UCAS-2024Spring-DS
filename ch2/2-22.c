/**
 * 试写一算法，实现单链表的就地逆置。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode {
    char c;
    struct Lnode *last;
    struct Lnode *next;
} Lnode;

Lnode *lalloc(void);
void printlist(Lnode *plist);

int main() {
    Lnode *plast, *plist, *tmp;
    char c;

    scanf("%c", &c);
    plast = plist = lalloc();
    plist->c = c;
    plist->last = NULL;
    plist->next = NULL;

    while (1) {
        scanf("%c", &c);
        if (c == '\n') {
            break;
        }
        tmp = plast;
        plast->next = lalloc();
        plast = plast->next;
        scanf("%c", &c);
        plast->c = c;
        plast->last = tmp;
        plast->next = NULL;
    }
    printlist(plast);
    return 0;
}

Lnode *lalloc(void) {
    return (Lnode *)malloc(sizeof(Lnode));
}

void printlist(Lnode *plast) {
    Lnode *pnode;
    pnode = plast;
    if (plast == NULL) {
        printf("NULL\n");
        return;
    }
    while (pnode != NULL) {
        if (pnode == plast) {
            printf("%c", plast->c);
        } else {
            printf(",%c", pnode->c);
        }
        pnode = pnode->last;
    }
    printf("\n");
}
