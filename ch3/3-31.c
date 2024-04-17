/**
 * 试写一个算法判别读入的一个以'@'为结束符的字符序列是否为回文。
 */

#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 1
#define FRONT 1
#define REAR 0

typedef int QElemType;
typedef int Status;
typedef int direction;

/* 结点结构 */
typedef struct QNode {
    QElemType data;
    struct QNode *prior;
    struct QNode *next;
} QNode, *QueuePtr;

/* 队列的链式存储结构 */
typedef struct {
    QueuePtr front, rear;
} LinkQueue;

/* 队列初始化 */
Status InitQueue(LinkQueue *Q) {
    Q->front = (QNode *)malloc(sizeof(QNode));
    Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->prior = NULL;
    Q->front->next = Q->rear;
    Q->rear->prior = Q->front;
    Q->rear->next = NULL;
    return OK;
}

/* 入队列 */
Status EnQueue(LinkQueue *Q, QElemType e, direction d) {
    QueuePtr s = (QNode *)malloc(sizeof(QNode));
    if (!s) {
        exit(OVERFLOW);
    }
    if (d == FRONT) {
        s->data = e;
        s->prior = Q->front;
        s->next = Q->front->next;
        Q->front->next->prior = s;
        Q->front->next = s;
    } else if (d == REAR) {
        s->data = e;
        s->prior = Q->rear->prior;
        s->next = Q->rear;
        Q->rear->prior->next = s;
        Q->rear->prior = s;
    } else {
        return ERROR;
    }
    return OK;
}

/* 出队列 */
Status DeQueue(LinkQueue *Q, QElemType *e, direction d) {
    QNode *p;
    if (Q->front->next == Q->rear) {
        return ERROR;
    }
    if (d == FRONT) {
        p = Q->front->next;
        *e = p->data;
        Q->front->next = p->next;
        p->next->prior = Q->front;
    } else if (d == REAR) {
        p = Q->rear->prior;
        *e = p->data;
        Q->rear->prior = p->prior;
        p->prior->next = Q->rear;
    }
    free(p);
    return OK;
}

/* 清除队列 */
void ClearQueue(LinkQueue *Q) {
    QNode *p_1, *p_2;
    p_1 = Q->front;
    p_2 = p_1->next;
    while (p_2 != NULL) {
        free(p_1);
        p_1 = p_2;
        p_2 = p_2->next;
    }
    free(p_1);
}

int main() {
    int c;
    int status = OK;
    QElemType *pc_front, *pc_rear;
    pc_front = (QElemType *)malloc(sizeof(QElemType));
    pc_rear = (QElemType *)malloc(sizeof(QElemType));
    LinkQueue *Q = (LinkQueue *)malloc(sizeof(LinkQueue));
    InitQueue(Q);
    while ((c = getchar()) != '@' && c != '\n' && c != EOF) {
        EnQueue(Q, c, REAR);
    }
    while (DeQueue(Q, pc_front, FRONT) != ERROR) {
        if (DeQueue(Q, pc_rear, REAR) == ERROR) {
            break;
        }
        if (*pc_front != *pc_rear) {
            status = ERROR;
            break;
        }
    }
    ClearQueue(Q);
    free(Q);
    printf("%d\n", status);
    return 0;
}
