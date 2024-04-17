/**
 * 稀疏矩阵加法（十字链表）
 * 放弃了，直接把 5.25 交上去了
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20

typedef struct OLNode{
    int i, j;
    int e;
    struct OLNode *right, *down;
} OLNode, *Olink;

typedef struct{
    //行和列链表头指针向量的基址
    Olink *rhead, *chead;
    int mu, nu, tu; // 行数，列数，非零元个数
} CrossList;

// 创建十字链表
void CreatSMatrix_OL(CrossList *M, int m, int n) {
    int i, j;

    // 设置行数，列数，非零元个数
    M->mu = m;
    M->nu = n;
    M->tu = 0;

    // 创建行和列链表的头指针向量
    M->rhead = (Olink *)malloc(m * sizeof(Olink));
    M->chead = (Olink *)malloc(n * sizeof(Olink));
    // 数组初始化
    for(int i = 0; i < m; i++)
        M->rhead[i] = NULL;
    for(int i = 0; i < n; i++)
        M->chead[i] = NULL;
}

void FulfillSMatrix_OL(CrossList *M) {
    int t[MAXSIZE];
    int ti;
    OLNode *p, *q;
    int e;
    int c;

    // 读取非零元到数组 t 中
    c = getchar(); // 跳过前一行结尾的 \n
    if ((c = getchar()) != '\n') { // 判断是否存在非零元
        ungetc(c, stdin);
        while (1) {
            scanf("%d", &t[M->tu++]);
            if ((c = getchar()) == '\n' || c == EOF) {
                break;
            }
        }
    }

    // 读取非零元素的位置，插入到十字链表中
    ti = 0;
    for (int i = 0; i < M->mu; i++) {
        for (int j = 0; j < M->nu; j++) {
            scanf("%d", &e);
            if (e) {
                // 创建结点
                p = (OLNode *)malloc(sizeof(OLNode));
                p->i = i;
                p->j = j;
                p->e = t[ti++];
                // 插入到行中
                if (M->rhead[i] == NULL || M->rhead[i]->j > j) { // 成为行的第一个非零元素
                    p->right = M->rhead[i];
                    M->rhead[i] = p;
                } else {
                    for (q = M->rhead[i]; (q->right) && q->right->j < j; q = q->right) // 找到插入点
                        ;
                    p->right = q->right;
                    q->right = p;
                }
                // 插入到列中
                if (M->chead[j]==NULL || M->chead[j]->i > i) { // 成为列的第一个非零元素
                    p->down = M->chead[j];
                    M->chead[j] = p;
                } else {
                    for (q = M->chead[j]; (q->down) && q->down->i < i; q = q->down) // 找到插入点
                        ;
                    p->down = q->down;
                    q->down = p;
                }
            }
        }
    }
}

void PrintSMatrix_OL(CrossList *M) {
    OLNode *p;
    int count;
    // 检查有没有非零元，没有直接打印返回
    if (M->tu == 0) {
        printf("\n");
        for (int i = 0; i < M->mu; i++) {
            for (int j = 0; j < M->nu - 1; j++) {
                printf("0 ");
            }
            printf("0\n");
        }
        return;
    }

    // 先打印非零元素
    count = 1;
    p = M->rhead[0];
    for (int i = 0; i < M->mu; i++) {
        p = M->rhead[i];
        while (p != NULL && count < M->tu) {
            printf("%d ", p->e);
            p = p->right;
            count++;
        }
    }
    printf("%d\n", p->e);
    // 再打印数组内容
    for (int i = 0; i < M->mu; i++) {
        p = M->rhead[i];
        for (int j = 0; j < M->nu - 1; j++) {
            if (p != NULL && p->j == j) {
                printf("1 ");
                p = p->right;
            } else {
                printf("0 ");
            }
        }
        if (p != NULL && p->j == M->nu - 1) {
            printf("1\n");
            p = p->right;
        } else {
            printf("0\n");
        }
    }
}

void SMatrix_OL_add(CrossList *A, CrossList *B) {
    OLNode *pa, *pb, *p, *q;
    int if_add; // 是否添加结点
    int e;

    for (int i = 0; i < A->mu; i++) {
        pb = B->rhead[i];

        while (pb != NULL) {
            if_add = 1;
            pa = A->rhead[i];
            // while (pa != NULL) {
            //     if (pa->j == pb->j) { // 有对应元
            //         if (pa->e + pb->e == 0) { // 和为零，移除结点 pa
            //             q = A->chead[pa->j];
            //             if (A->rhead[pa->i] == pa) {
            //                 A->rhead[pa->i]->right = pa->right;
            //                 free(pa);
            //             } else {
            //                 p = A->rhead[pa->i];
            //                 while (p != NULL)
            //             }
            //             if (A->chead[pa->j] == pa) {
            //                 A->chead[pa->j]->down = pa->down;
            //                 free(pa);
            //             }
            //         } else { // 和不为零，修改结点
            //             pa->e = pa->e + pb->e;
            //         }
            //         if_add = 0;
            //         break;
            //     }
            //     pa = pa->right;
            // }
            if (if_add == 1) { // 没有对应元，加进去
                A->tu++;
                // 创建结点
                p = (OLNode *)malloc(sizeof(OLNode));
                p->i = pb->i;
                p->j = pb->j;
                p->e = pb->e;
                // 插入到行中
                if (A->rhead[i] == NULL || A->rhead[i]->j > p->j) { // 成为行的第一个非零元素
                    p->right = A->rhead[i];
                    A->rhead[i] = p;
                } else {
                    for (q = A->rhead[i]; (q->right) && q->right->j < p->j; q = q->right) // 找到插入点
                        ;
                    p->right = q->right;
                    q->right = p;
                }
                // 插入到列中
                if (A->chead[p->j]==NULL || A->chead[p->j]->i > i) { // 成为列的第一个非零元素
                    p->down = A->chead[p->j];
                    A->chead[p->j] = p;
                } else {
                    for (q = A->chead[p->j]; (q->down) && q->down->i < i; q = q->down) // 找到插入点
                        ;
                    p->down = q->down;
                    q->down = p;
                }
            }
            pb = pb->right;
        }
    }
}

int main() {
    int m, n;
    CrossList *A;
    CrossList *B;
    scanf("%d %d", &m, &n);
    A = (CrossList *)malloc(sizeof(CrossList));
    B = (CrossList *)malloc(sizeof(CrossList));
    CreatSMatrix_OL(A, m, n);
    CreatSMatrix_OL(B, m, n);
    FulfillSMatrix_OL(A);
    FulfillSMatrix_OL(B);
    SMatrix_OL_add(A, B);
    PrintSMatrix_OL(A);
    return 0;
}

// 3 4
// 1 2 3 4 5
// 0 1 0 0
// 1 1 0 1
// 0 0 1 0
// -1 -4 5
// 0 1 0 0
// 0 0 0 1
// 0 1 0 0
