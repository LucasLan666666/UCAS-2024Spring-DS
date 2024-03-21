#include "head.h"

/* 栈的顺序存储结构 */
typedef struct {
    SElemType data[MAXSIZE];
    int top;
} SqStack;

/* 进栈操作 */
Status Push(SqStack *S, SElemType e) {
    if (S->top == MAXSIZE - 1) {
        return ERROR;
    }
    S->data[++S->top] = e;
    return OK;
}

/* 出栈操作 */
Status Pop(SqStack *S, SElemType *e) {
    if (S->top == -1) {
        return ERROR;
    }
    *e = S->data[S->top--];
    return OK;
}
