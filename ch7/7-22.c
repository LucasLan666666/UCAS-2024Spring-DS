/**
 * 基于图的深度优先搜索策略写一算法，判别以邻接表方式存储的有向图中是否存在由定点 v_i
 * 到 定点 v_j 的路径（i != j）
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

    scanf("%d", &G->numVertexes);
    G->numEdges = 0;

    for (i = 0; i <= G->numVertexes; i++) {
        G->adjList[i].firstedge = NULL; // 将边表置为空表
    }

    // 建立边表
    int c;
    do {
        scanf("%d-%d", &i, &j);
        G->numEdges++;

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
        c = getchar(); // 获取逗号或换行符
    } while (c != '\n');
}

// 判断是否存在路径
int JudgePath(GraphAdjList *G, int v, int w) {
    EdgeNode *p;
    p = G->adjList[v].firstedge;
    while (p != NULL) {
        if (w == p->adjvex) {
            return 1;
        } else if (JudgePath(G, p->adjvex, w)) {
            return 1;
        }
        p = p->next;
    }
    return 0;
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
    int v, w;
    int res;
    GraphAdjList G;
    CreateALGraph(&G);
    scanf("%d,%d", &v, &w);
    res = JudgePath(&G, v, w);
    printf(res ? "yes\n" : "no\n");
    FreeALGraph(&G);
    return 0;
}