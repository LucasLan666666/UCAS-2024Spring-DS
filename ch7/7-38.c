/**
 * 一个四则运算算术表达式以有向无环图的邻接表方式存储，每个操作数原子都由单个字母表示。写一个算法输出其逆波兰表达式。
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 100

// 边表结点
typedef struct EdgeNode {
    int adjvex; // 邻接点域，存储该顶点对应下标
    struct EdgeNode *next; // 链域，指向下一个邻接点
} EdgeNode;

// 顶点表结点
typedef struct VertexNode {
    char data; // 顶点域，存储顶点信息
    EdgeNode *firstedge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int numVertexes; // 图中当前顶点数
} GraphAdjList;

// 建立图的邻接表结构
void CreateALGraph(GraphAdjList *G) {
    int a, b;
    EdgeNode *el, *er;
    int c;

    scanf("%d\n", &G->numVertexes);

    for (int k = 0; k < G->numVertexes; k++) {
        scanf("%c", &G->adjList[k].data); // 输入顶点信息
        G->adjList[k].firstedge = NULL; // 将边表置为空表

        if ((c = getchar()) == ' ') {
            scanf("%d %d\n", &b, &a);
            el = (EdgeNode *)malloc(sizeof(EdgeNode));
            er = (EdgeNode *)malloc(sizeof(EdgeNode));
            el->adjvex = a;
            er->adjvex = b;
            G->adjList[k].firstedge = el;
            el->next = er;
            er->next = NULL;
        }
    }
}

// 后序遍历并打印
void PrintPostOrder(GraphAdjList *G, int index) {
    if (G->adjList[index].firstedge != NULL) {
        PrintPostOrder(G, G->adjList[index].firstedge->adjvex);
        PrintPostOrder(G, G->adjList[index].firstedge->next->adjvex);
    }
    printf("%c", G->adjList[index].data);
    if (index == 0)
        printf("\n");
}

// 释放
void FreeALGraph(GraphAdjList *G) {
    EdgeNode *p, *q;
    for (int i = 0; i < G->numVertexes; i++) {
        p = G->adjList[i].firstedge;
        while (p != NULL) {
            q = p;
            p = p->next;
            free(q);
        }
    }
}

int main() {
    GraphAdjList G;
    CreateALGraph(&G);
    PrintPostOrder(&G, 0);
    FreeALGraph(&G);
    return 0;
}