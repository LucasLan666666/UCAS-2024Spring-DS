#include "head.h"

/* 结点结构 */
typedef struct QNode {
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

/* 队列的链式存储结构 */
typedef struct {
    QueuePtr front, rear;
} LinkQueue;

/* 入队列 */
Status EnQueue(LinkQueue *Q, QElemType e) {
    QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
    if (!s) {
        exit(OVERFLOW);
    }
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
    return OK;
}

/* 出队列 */
Status DeQueue(LinkQueue *Q, QElemType *e) {
    QueuePtr p;
    if (Q->front == Q->rear) {
        return ERROR;
    }
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    free(p);
    return OK;
}
