/*
** 已知一非空有序表，表中记录按关键字递增排列，以不带头结点的单循环链表作存储结构，外设两个指
** 针 h 和 t，其中h始终指向关键字最小的节点，t 则在表中浮动，其初始位置和 h 相同，在每次查找
** 之后指向刚查到的节点。查找算法的策略是：首先将给定值 K 和 t->key 进行比较，若相等，则查找
** 成功；否则 因 K 小于或大于 t->key 而从 h 所指节点或 t 所指节点的后继节点进行查找，按上述
** 过程编写查找算法。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node, *NodePtr, *LinkList;



void
CreateLinkList(LinkList *L)
{
    int data;
    int c;
    NodePtr ptail, p;

    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = *L;
    ptail = *L;

    scanf("%d", &data);
    (*L)->data = data;

    while ((c = getchar()) != '\n' && c != EOF) {
        scanf("%d", &data);
        p = (Node *)malloc(sizeof(Node));
        p->data = data;
        p->next = *L;
        ptail->next = p;
        ptail = p;
    }
}



void
ClearLinkList(LinkList *L)
{
    NodePtr p, q;
    p = (*L)->next;     /* 首节点最后单独释放 */

    while (p->next != *L) {
        q = p;
        p = p->next;
        free(q);
    }

    free(*L);   /* 释放头结点 */
    *L = NULL;
}



int
Search(LinkList *L, int key, NodePtr *t)
{
    Node *p;

    /* 循环链表只有一个结点，只用判断这一个是不是就行 */
    if ((*L)->next == *L) {
        if (key == (*t)->data) {
            return 1;
        }
        else {
            return 0;
        }
    }

    /* 从 L 到 t */
    if (key <= (*t)->data) {
        for (p = *L; key <= (*t)->data; p = p->next) {
            if (p == (*t)->next) /* 超范围了 */
                return 0;
            if (key == p->data) {
                *t = p;
                return 1;
            }
        }
    }
    /* 从 t 的下一个结点到 L 的前一个结点 */
    else {
        for (p = (*t)->next; key > (*t)->data; p = p->next) {
            if (p == *L) /* 超范围了 */
                return 0;
            if (key == p->data) {
                *t = p;
                return 1;
            }
        }
    }
    *t = *L;
    return 0;
}



void
SearchAll(LinkList *L)
{
    int key, c;
    NodePtr t = *L;

    scanf("%d", &key);
    printf("%d", Search(L, key, &t));

    while ((c = getchar()) != EOF && c != '\n') {
        scanf("%d", &key);
        printf(" %d", Search(L, key, &t));
    }
    printf("\n");
}



int
main(void)
{
    LinkList h;
    CreateLinkList(&h);
    SearchAll(&h);
    ClearLinkList(&h);
    return 0;
}
