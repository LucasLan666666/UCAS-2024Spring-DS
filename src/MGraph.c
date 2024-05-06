// 邻接矩阵实现图的创建

#include <stdio.h>
#define MAXVEX 100 // 最大顶点数
#define INFINITY 65535 // 无穷

typedef char VertexType; // 顶点类型
typedef int EdgeType; // 权值类型

typedef struct {
    VertexType vsxs[MAXVEX]; // 顶点表
    EdgeType arc[MAXVEX][MAXVEX]; // 邻接矩阵，可看作边表
    int numVertexes, numEdges; // 图中当前顶点数和边数
} MGraph;

// 建立无向网图的邻接矩阵表示

void CreateMGraph(MGraph *G) {
    int i, j, k, w;
    printf("输入顶点数和边数：\n");
    scanf("%d, %d", &G->numVertexes, &G->numEdges);

    for (i = 0; i < G->numVertexes; i++) { // 读入顶点信息，建立顶点表
        scanf("%c",&G->vsxs[i]);
    }
    for (i = 0; i < G->numVertexes; j++) {
        for (j = 0; j < G->numVertexes; j++) {
            G->arc[i][j] = INFINITY; // 邻接矩阵初始化
        }
    }
    for (k = 0; k < G->numEdges; k++) {
        printf("输入边（vi，vj）上的下标 i，下标 j 和权 w：\n");
        scanf("%d,%d,%d", &i, &j, &w); //输入边（vi，vj）上的权 w
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j]; //无向图，矩阵对称
    }
}
