#include "head.h"
#include <stdlib.h>
#include <time.h>

/* 线性表的单链表存储结构 */
typedef struct Node {
    ElemType data;
    struct Node *next;
} Node, *LinkList;

/**
 * 单链表的读取
 * 初始条件：顺序线性表 L 已存在，1<=i<=ListLength(L)
 * 操作结果：用 e 返回 L 中第 i 个数据元素的值
 */
Status GetElem(LinkList L, int i, ElemType *e) {
    int j;
    LinkList p;
    p = L->next;
    for (j = 1; j < i; j++) {
        if (p != NULL) {
            p = p->next;
        } else {
            break;
        }
    }
    if (p == NULL || j > i) {
        return ERROR;
    }
    *e = p->data;
    return OK;
}

/**
 * 单链表的插入
 * 初始条件：顺序线性表 L 已存在，1<=i<=ListLength(L)
 * 操作结果：在 L 中第 i 个位置之前插入新的数据元素 e，L 的长度加 1
 */
Status ListInsert(LinkList L, int i, ElemType e) {
    int j;
    LinkList p, s;
    p = L;
    for (j = 1; j < i; j++) {
        if (p != NULL) {
            p = p->next;
        } else {
            break;
        }
    }
    if (p == NULL || j > i) {
        return ERROR;
    }
    s = (LinkList)malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

/**
 * 单链表的删除
 * 初始条件：顺序线性表 L 已存在，1<=i<=ListLength(L)
 * 操作结果：删除 L 的第 i 个数据元素，并用 e 返回其值，L 的长度减 1
 */
Status ListDelete(LinkList L, int i, ElemType *e) {
    int j;
    LinkList p, q;
    p = L;
    for (j = 1; j < i; j++) {
        if (p != NULL) {
            p = p->next;
        } else {
            break;
        }
    }
    if (p->next == NULL || j > i) {
        return ERROR;
    }
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

/**
 * 单链表的整表创建-1
 * 随机产生 n 个元素的值，建立带表头结点的单链线性表 L（头插法）
 */
void CreateListHead(LinkList L, int n) {
    LinkList p;
    srand(time(0)); // 初始化随机数种子
    L = (LinkList)malloc(sizeof(Node));
    L->next = NULL;
    for (int i = 0; i < n; i++) {
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand()% + 1;
        p->next = L->next;
        L->next = p;
    }
}

/**
 * 单链表的整表创建-2
 * 随机产生 n 个元素的值，建立带表头结点的单链线性表 L（尾插法）
 */
void CreateListHTail(LinkList L, int n) {
    LinkList p, r;
    srand(time(0)); // 初始化随机数种子
    L = (LinkList)malloc(sizeof(Node));
    r = L;
    for (int i = 0; i < n; i++) {
        p = (Node *)malloc(sizeof(Node));
        p->data = rand()% + 1;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}

/**
 * 单链表的整表删除
 * 初始条件：顺序线性表 L 已存在
 * 操作结果：将 L 重置为空表
 */

Status ClearList(LinkList L) {
    LinkList p, q;
    p = L->next;
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
    return OK;
}
