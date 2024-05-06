/**
 * 试在邻接矩阵存储结构上实现图的基本操作：InsertVex(G, v), InsertArc(G, v, w), DeleteVex(G,v)和DeleteArc(G,v,w)
 */

#include <stdio.h>
#include <string.h>
#define MAXVEX 20 // 最大顶点数
#define MAXLEN 10 // 指令长度

typedef struct {
    int arc[MAXVEX][MAXVEX]; // 邻接矩阵，可看作边表
    int numVertexes; // 图中当前顶点数
} MGraph;

// 建立无向网图的邻接矩阵表示
void CreateMGraph(MGraph *G) {
    int i, j, k, w;
    scanf("%d", &G->numVertexes);

    for (i = 0; i < G->numVertexes; i++) {
        for (j = 0; j < G->numVertexes; j++) {
            scanf("%d", &G->arc[i][j]);
        }
    }
}

void InsertVex(MGraph *G, int v) {
    G->numVertexes++;
    for (int i = G->numVertexes - 1; i >= 0; i--) {
        for (int j = G->numVertexes - 1; j >= 0; j--) {
            if (i < v && j > v) {
                G->arc[i][j] = G->arc[i][j - 1];
            } else if (j < v && i > v) {
                G->arc[i][j] = G->arc[i - 1][j];
            } else if (i > v && j > v) {
                G->arc[i][j] = G->arc[i - 1][j - 1];
            } else if (i == v || j == v) {
                G->arc[i][j] = 0;
            }
        }
    }
}

void InsertArc(MGraph *G, int v, int w) {
    G->arc[v][w] = 1;
    G->arc[w][v] = 1;
}

void DeleteVex(MGraph *G, int v) {
    for (int i = 0; i < G->numVertexes; i++) {
        for (int j = 0; j < G->numVertexes; j++) {
            if (i < v && j >= v) {
                G->arc[i][j] = G->arc[i][j + 1];
            } else if (j < v && i >= v) {
                G->arc[i][j] = G->arc[i + 1][j];
            } else if (i >= v && j >= v) {
                G->arc[i][j] = G->arc[i + 1][j + 1];
            }
        }
    }
    G->numVertexes--;
}

void DeleteArc(MGraph *G, int v, int w) {
    G->arc[v][w] = 0;
    G->arc[w][v] = 0;
}

void PrintMGraph(MGraph *G) {
    for (int i = 0; i < G->numVertexes; i++) {
        for (int j = 0; j < G->numVertexes - 1; j++) {
            printf("%d ", G->arc[i][j]);
        }
        printf("%d\n", G->arc[i][G->numVertexes - 1]);
    }
}

int main() {
    MGraph G;
    char func[MAXLEN];
    int v, w;
    CreateMGraph(&G);
    while ((scanf("%s", func)) != -1) {
        if (!strcmp(func, "IV")) {
            scanf("%d", &v);
            InsertVex(&G, v);
        } else if (!strcmp(func, "IA")) {
            scanf("%d %d", &v, &w);
            InsertArc(&G, v, w);
        } else if (!strcmp(func, "DV")) {
            scanf("%d", &v);
            DeleteVex(&G, v);
        } else if (!strcmp(func, "DA")) {
            scanf("%d %d", &v, &w);
            DeleteArc(&G, v, w);
        }
    }
    PrintMGraph(&G);
    return 0;
}
