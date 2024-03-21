/**
 * 假设表达式由单字母变量和双目四则运算符构成.试写一个算法,将一个通常书写形式且书写正确的表达式转换为逆波兰式.
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0

typedef int Status;

typedef struct {
    int sign[MAXSIZE];
    int top;
} SqStack;

SqStack *salloc(void) {
    return (SqStack *)malloc(sizeof(SqStack));
}

Status Push(SqStack *S, int e) {
    if (S->top == MAXSIZE - 1) {
        return ERROR;
    }
    S->top++;
    S->sign[S->top] = e;
    return OK;
}

Status Pop(SqStack *S, int *e) {
    if (S->top == -1) {
        return ERROR;
    }
    *e = S->sign[S->top];
    S->top--;
    return OK;
}

int main() {
    int cin, cout;
    SqStack *S = salloc();
    S->top = -1;
    while ((cin = getchar()) != '\n' && cin != EOF) {
        if (isalpha(cin)) {
            putchar(cin);
        } else if (cin == '+' || cin == '-') {
            while (S->top != -1 && S->sign[S->top] != '(') {
                Pop(S, &cout);
                putchar(cout);
            }
            Push(S, cin);
        } else if (cin == '*' || cin == '/') {
            if (S->top != -1 && (S->sign[S->top] == '*' || S->sign[S->top] == '/')) {
                Pop(S, &cout);
                putchar(cout);
            }
            Push(S, cin);
        } else if (cin == '(') {
            Push(S, cin);
        } else if (cin == ')') {
            while (S->sign[S->top] != '(') {
                Pop(S, &cout);
                putchar(cout);
            }
            Pop(S, &cout);
        }
    }
    while (Pop(S, &cout) == OK) {
        putchar(cout);
    }
    putchar('\n');
    return 0;
}
