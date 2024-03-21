#include "head.h"
#include <stdlib.h>

/* 栈的链式存储结构 */
typedef struct StackNode {
    SElemType data;
    struct StackNode *next;
} StackNode, *LinkStackPtr;

typedef struct LinkStack {
    LinkStackPtr top;
    int count;
} LinkStack;

/**
 * 进栈操作
 */
Status Push(LinkStack *S, SElemType e) {
    LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
    s->data = e;
    s->next = S->top;
    S->top = s;
    S->count++;
    return OK;
}

/**
 * 检测是否栈空
 */
int StackEmpty(LinkStack *S) {
    if (S->count == 0) {
        return 1;
    } else {
        return 0;
    }
}


/**
 * 出栈操作
 */
Status Pop(LinkStack *S, SElemType *e) {
    LinkStackPtr p;
    if (StackEmpty(S)) {
        return ERROR;
    }
    *e = S->top->data;
    p = S->top;
    S->top = S->top->next;
    free(p);
    S->count--;
    return OK;
}
