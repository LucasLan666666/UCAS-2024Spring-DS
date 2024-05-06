/**
 * 采用邻接表存储结构，编写一个判别无向图中任意给定的两个顶点之间是否存在一条长度为k的简单路径的算法。
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 10

typedef enum {false, true} bool;

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
    struct {
        int len; // 所求路径的长度
        int head, tail; // 所求路径的开头和结尾
    } path;
    int numVertexes; // 图中当前顶点数
} GraphAdjList;

// 建立图的邻接表结构
void CreateALGraph(GraphAdjList *G) {
    int i, j, k;
    EdgeNode *e_1, *e_2;

    scanf("%d,%d", &G->numVertexes, &G->path.len);
    scanf("%d,%d", &G->path.head, &G->path.tail);

    for (i = 0; i <= G->numVertexes; i++)
        G->adjList[i].firstedge = NULL; // 将边表置为空表

    // 建立边表
    int c;
    do {
        scanf("%d-%d", &i, &j);

        e_1 = (EdgeNode *)malloc(sizeof(EdgeNode));
        e_1->adjvex = j;
        e_1->next = G->adjList[i].firstedge;
        G->adjList[i].firstedge = e_1;

        e_2 = (EdgeNode *)malloc(sizeof(EdgeNode));
        e_2->adjvex = i;
        e_2->next = G->adjList[j].firstedge;
        G->adjList[j].firstedge = e_2;

        c = getchar(); // 获取逗号或换行符
    } while (c != '\n');
}

// 检查数组 arr[0:len-1] 中是否有某元素 elem
bool CheckElem(int *arr, int len, int elem) {
    for (int i = 0; i < len; i++)
        if (arr[i] == elem)
            return true;
    return false;
}

/**
 * 判断路径
 * path 为路径开头的地址
 * cur_len 为目前路径的长度
 */
bool JudgePath(GraphAdjList G, int *path, int cur_len) {
    if (cur_len == G.path.len) // 如果长度已满，检查是否和路径结尾相同
        return (path[cur_len] == G.path.tail) ? true : false;

    EdgeNode *p = G.adjList[path[cur_len]].firstedge;
    cur_len++;
    // 遍历下一个顶点的所有情况
    while (p != NULL) {
        if (CheckElem(path, cur_len, p->adjvex) == false) {  // 如果该顶点没有出现过，考虑能否构成所求路径
            path[cur_len] = p->adjvex;
            if (JudgePath(G, path, cur_len) == true)
                return true;
        }
        p = p->next;
    }
    // 遍历完毕，都不能构成所求路径，返回 false
    return false;
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
    int path[MAXVEX];
    int result;

    CreateALGraph(&G);
    path[0] = G.path.head;
    result = JudgePath(G, path, 0);
    printf((result == true) ? "yes\n" : "no\n");
    FreeALGraph(&G);
    return 0;
}
