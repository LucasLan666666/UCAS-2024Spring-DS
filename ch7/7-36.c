/**
 * 在图的邻接表存储结构中，为每个顶点增加一个 MPL 域。试写一算法，求有向无环图G的每个顶点出发的最长路径的长度。
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 10

// 边表结点
typedef struct EdgeNode {
    int adjvex; // 邻接点域，存储该顶点对应下标
    struct EdgeNode *next; // 链域，指向下一个邻接点
} EdgeNode;

// 顶点表结点
typedef struct VertexNode {
    int MPL_set; // 该点出发最长路径长度是否已经设置
    int MPL; // 该点出发最长路径长度
    EdgeNode *firstedge; // 边表头指针
} VertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int numVertexes; // 图中当前顶点数和边数
} GraphAdjList;

// 建立图的邻接表结构
void CreateALGraph(GraphAdjList *G) {
    int i, j;
    int c;
    EdgeNode *e;

    scanf("%d", &G->numVertexes);

    for (i = 0; i <= G->numVertexes; i++) {
        G->adjList[i].MPL_set = 0; // MPL 均未设置
        G->adjList[i].firstedge = NULL; // 将边表置为空表
    }

    // 建立边表
    do {
        scanf("%d-%d", &i, &j);

        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e;

        c = getchar();
    } while (c != '\n');
}

// 计算 MPL
void SetMPL(GraphAdjList *G, int index) {
    int max_len = 0;
    int len = 0;
    EdgeNode *p;

    if (G->adjList[index].MPL_set == 1)
        return;

    p = G->adjList[index].firstedge;
    while (p != NULL) {
        SetMPL(G, p->adjvex);
        len = G->adjList[p->adjvex].MPL + 1;
        max_len = (max_len > len) ? max_len : len;
        p = p->next;
    }
    G->adjList[index].MPL = max_len;
    G->adjList[index].MPL_set = 1;
}

// 打印 MPL
void PrintMPL(GraphAdjList *G) {
    for (int i = 1; i < G->numVertexes; i++)
        printf("%d,", G->adjList[i].MPL);
    printf("%d\n", G->adjList[G->numVertexes].MPL);
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
    for (int i = 1; i <= G.numVertexes; i++)
        SetMPL(&G, i);
    PrintMPL(&G);
    FreeALGraph(&G);
    return 0;
}
