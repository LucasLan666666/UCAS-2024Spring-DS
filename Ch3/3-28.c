/**
 * 假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾元素结点(注意不设头指针)，试编写相应的队列初始化、入队列和出队列的算法
 */

#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;

typedef struct Node {
    ElemType data;
    struct Node *next;
} Node, *NodePtr;

typedef struct {
    NodePtr rear;
} Queue;

Status CreateQueue(Queue *Q) {
    Q->rear = NULL;
    return OK;
}

Status EnQueue(Queue *Q, ElemType data) {
    if (Q->rear == NULL) {
        Q->rear = (Node *)malloc(sizeof(Node));
        Q->rear->next = (Node *)malloc(sizeof(Node));
        Q->rear->data = data;
        Q->rear->next->next = Q->rear;
    } else {
        Node *p = (Node *)malloc(sizeof(Node));
        p->data = data;
        p->next = Q->rear->next;
        Q->rear->next = p;
        Q->rear = p;
    }
    return OK;
}

Status DeQueue(Queue *Q, ElemType *pdata) {
    if (Q->rear == NULL) {
        return ERROR;
    } else {
        Node *p = Q->rear->next->next;
        *pdata = p->data;
        if (p != Q->rear) {
            Q->rear->next->next = p->next;
            free(p);
        } else {
            free(p->next);
            free(p);
            Q->rear = NULL;
        }
    }
    return OK;
}

int main() {
    Queue *Q;
    ElemType data, *pdata;
    int len;
    int c;

    scanf("%d", &len);
    if (len == 0) {
        char s[10];
        scanf("%s", s);
        printf("%s\n", s);
        return 0;
    }
    Q = (Queue *)malloc(sizeof(Queue));
    pdata = (ElemType *)malloc(sizeof(ElemType));
    CreateQueue(Q);
    while (1) {
        scanf("%d", &data);
        EnQueue(Q, data);
        if ((c = getchar()) == '\n' || c == EOF) {
            break;
        }
    }
    while (Q->rear->next->next != Q->rear) {
        DeQueue(Q, pdata);
        printf("%d,", *pdata);
    }
    DeQueue(Q, pdata);
    printf("%d\n", *pdata);
    free(Q);
    free(pdata);
    return 0;
}
