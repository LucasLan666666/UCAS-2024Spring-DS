/**
 * 编写算法，由依次输入的顶点数目、弧的数目、各顶点的信息和各条弧的信息建立有向图的邻接表。
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
    EdgeNode *firstedge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int numVertexes, numEdges; // 图中当前顶点数和边数
} GraphAdjList;

// 建立图的邻接表结构
void CreateALGraph(GraphAdjList *G) {
    int i, j, k;
    EdgeNode *e;
    EdgeNode *p;

    scanf("%d,%d", &G->numVertexes, &G->numEdges);

    for (i = 0; i <= G->numVertexes; i++) {
        G->adjList[i].firstedge = NULL; // 将边表置为空表
    }

    // 建立边表
    for (k = 0; k < G->numEdges; k++) {
        int c;
        scanf("%d-%d", &i, &j);
        c = getchar(); // 获取逗号或换行符，不重要

        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->next = NULL;

        if (G->adjList[i].firstedge == NULL || G->adjList[i].firstedge->adjvex < e->adjvex) {
            e->next = G->adjList[i].firstedge;
            G->adjList[i].firstedge = e;
        } else {
            p = G->adjList[i].firstedge;
            while (p->next != NULL && p->next->adjvex > e->adjvex) {
                p = p->next;
            }
            e->next = p->next;
            p->next = e;
        }
    }
}

// 打印
void PrintALGraph(GraphAdjList G) {
    int base;
    if (G.adjList[0].firstedge != NULL) {
        base = 0;
    } else {
        base = 1;
    }
    for (int i = 0; i < G.numVertexes; i++) {
        printf("%d", base + i);
        if (G.adjList[base + i].firstedge != NULL) {
            printf(" ");
            EdgeNode *p = G.adjList[base + i].firstedge;
            while (p->next != NULL) {
                printf("%d,", p->adjvex);
                p = p->next;
            }
            printf("%d", p->adjvex);
        }
        printf("\n");
    }
}

// 释放
void FreeALGraph(GraphAdjList *G) {
    EdgeNode *p, *q;
    for (int i = 0; i <= G->numVertexes; i++) {
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
    PrintALGraph(G);
    FreeALGraph(&G);
    return 0;
}