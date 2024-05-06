/**
 * 以邻接表作为存储结构实现求源点到其余各顶点最短路径的 Dijkstra 算法
 * https://www.bilibili.com/video/BV1zz4y1m7Nq/
 */


#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 20
#define INFTY 666666

typedef enum {false, true} bool;

// 边表结点
typedef struct EdgeNode {
    int adjvex; // 邻接点域，存储该顶点对应下标
    int weight; // 用于存储权值
    struct EdgeNode *next; // 链域，指向下一个邻接点
} EdgeNode;

// 顶点表结点
typedef struct VertexNode {
    EdgeNode *firstedge; // 边表头指针
    int src_len; // 从源点出发到该点的最短距离
    int pre; // 路径中该结点的前一个点
    bool mark; // Dijkstra 中的标记
} VertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int numVertexes; // 图中当前顶点数
    int src_ver; // 源点
} GraphAdjList;

// 建立图的邻接表结构
void CreateALGraph(GraphAdjList *G) {
    int i, j, w;
    EdgeNode *e_1, *e_2;

    scanf("%d %d", &G->numVertexes, &G->src_ver);

    for (i = 1; i <= G->numVertexes; i++) {
        G->adjList[i].firstedge = NULL; // 将边表置为空表
        G->adjList[i].src_len = INFTY; // 设置源点到该点距离默认为无穷大
        G->adjList[i].mark = false; // 所有点开始都没有标记
    }

    // 建立边表
    while (1) {
        if (scanf("%d-%d %d", &i, &j, &w) != 3)
            break;

        e_1 = (EdgeNode *)malloc(sizeof(EdgeNode));
        e_1->adjvex = j;
        e_1->weight = w;
        e_1->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e_1;

        e_2 = (EdgeNode *)malloc(sizeof(EdgeNode));
        e_2->adjvex = i;
        e_2->weight = w;
        e_2->next = G->adjList[j].firstedge;
        G->adjList[j].firstedge = e_2;
    }
}

// Dijkstra 算法找最短路径
void Shortest_Dijkstra(GraphAdjList *G) {
    G->adjList[G->src_ver].src_len = 0; // 源点到自己距离为 0

    while (1) {
        // 先找到第一个未标记的点
        int i;
        for (i = 1; i <= G->numVertexes; i++)
            if (G->adjList[i].mark == false)
                break;
        if (i == G->numVertexes + 1) // 如果都标记过，返回
            return;

        // 遍历所有未标记顶点后，标记 mark_ver 为当前距离源点最近的点
        int mark_ver = i;
        for(; i <= G->numVertexes; i++)
            if (   G->adjList[i].mark == false
                && G->adjList[i].src_len <= G->adjList[mark_ver].src_len
            )
                mark_ver = i;
        G->adjList[mark_ver].mark = true;

        // 更新 mark_ver 的邻接点
        EdgeNode *p = G->adjList[mark_ver].firstedge; // p 用于对 mark_ver 的邻接顶点进行遍历
        while (p != NULL) {
            // 更新最短距离和前顶点
            if (p->weight + G->adjList[mark_ver].src_len < G->adjList[p->adjvex].src_len) {
                G->adjList[p->adjvex].src_len = p->weight + G->adjList[mark_ver].src_len;
                G->adjList[p->adjvex].pre = mark_ver;
            }
            // 下一个邻接点
            p = p->next;
        }
    }
}

// 按顶点序号打印最短距离
void PrintShortestPath(GraphAdjList *G) {
    if (G->src_ver == 1) {
        printf("%d", G->adjList[2].src_len);
        for (int i = 3; i <= G->numVertexes; i++)
            printf(",%d", G->adjList[i].src_len);
    } else {
        printf("%d", G->adjList[1].src_len);
        for (int i = 2; i <= G->numVertexes; i++)
            if (i != G->src_ver)
                printf(",%d", G->adjList[i].src_len);
    }
    printf("\n");
}

// 释放
void FreeALGraph(GraphAdjList *G) {
    EdgeNode *p, *q;
    for (int i = 1; i <= G->numVertexes; i++) {
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
    Shortest_Dijkstra(&G);
    PrintShortestPath(&G);
    FreeALGraph(&G);
    return 0;
}
