/**
 * 试编写递归算法，删除广义表中所有值等于x的原子项。
 * 如果子表中不包含元素则删除该子表。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 30

typedef char AtomType;
typedef enum{ATOM, LIST} ElemTag; // ATOM==0：原子 ；LIST==1：子表

// 广义表定义
typedef struct GLNode {
    ElemTag tag;
    // 公共部分，用于区分原子节点和表节点
    union { // 原子节点和表节点的联合部分
        AtomType atom; //atom 是原子节点的值域，AtomType 由用户定义
        struct {
            struct GLNode *hp; // 指向子表的指针
            struct GLNode *tp; // 指向同一层下一个表元素结点的指针
        } ptr;
    };
} GLNode;

// 判断字符串是否为空
int IsStrEmpty(char *S) {
    return (S[0] == '\0');
}

// 清除字符串
void StrClear(char *S) {
    S[0] = '\0';
}

// 获取子串
void StrSubStr(char *tar, char *src, int base, int len) {
    for (int i = 0; i < len; i++) {
        tar[i] = src[base + i];
    }
    tar[len] = '\0';
}

// 分割字符串
void Sever(char *str, char *hstr) { // 将非空串 str 分割为两部分：hstr 为第一个逗号之前的子串，str 为之后的子串
    int n, i, k;
    char ch[2];
    n = strlen(str);
    i = k = 0; // k：尚未配对的左括号个数
    do {
        StrSubStr(ch, str, i, 1); // 取一个字符
        ++i;
        if (ch[0] == '(') {
            ++k;
        } else if (ch[0] == ')'){
            --k;
        }
    } while (i < n && (ch[0] != ',' || k != 0));

    if (i < n) { // 遇到逗号或括号
        StrSubStr(hstr, str, 0, i - 1);
        StrSubStr(str, str, i, n - i);
    } else {
        strcpy(hstr, str);
        StrClear(str);
    }
}

// 创建广义表
GLNode *Create_GL(char *S) {
    GLNode *L, *p, *q;
    char sub[MAXSIZE];
    char hsub[MAXSIZE];

    if (!strcmp(S,"()")) // 创建空表
    {
        L = NULL;
    }
    else // 生成表结点
    {
        L = (GLNode *)malloc(sizeof(GLNode));
        if (strlen(S) == 1) { // 建立单原子广义表
            L->tag = ATOM;
            L->atom = S[0];
        } else {
            L->tag = LIST;
            p = L;
            StrSubStr(sub, S, 1, strlen(S) - 2); // 设 sub 为 脱去串 S 最外层括弧的子串
            // 为 sub 中所含 n 个子串建立 n 个子表
            do { // 重复建 n 个子表
                Sever(sub, hsub); // 分离出子表串 hsub
                p->ptr.hp = Create_GL(hsub); // 创建由串 hsub 定义的广义表 p->ptr.hp
                q = p;
                if (!IsStrEmpty(sub)) { //余下的表不为空
                    p = (GLNode *)malloc(sizeof(GLNode));
                    //建下一个子表的表结点*(p->ptr.tp)
                    p->tag = LIST;
                    q->ptr.tp = p;
                }
            } while (!IsStrEmpty(sub));
            q->ptr.tp = NULL; // 表尾为空表
        }
    }
    return L;
}

// 删除广义表 L 中所有值为 x 的原子结点
GLNode *Delete_GL(GLNode *L, AtomType x) {
    if (L == NULL) {
        return NULL;  // 广义表为空，直接返回
    }
    if (L->tag == ATOM) { // L 是原子结点
        if (L->atom == x) {
            free(L);  // 释放匹配的原子节点
            return NULL;
        }
    } else if (L->tag == LIST) { // L 是表
        GLNode *p, *pre;
        int isDeleteHead = 0;
        // 考虑表头被删掉的情况
        do {
            if (L == NULL) { // 如果 L 为空，直接返回
                return NULL;
            }
            if (L->ptr.hp->tag == ATOM) { // L 表中第一个元素是原子结点
                if (L->ptr.hp->atom == x) { // 如果第一个原子结点为 x，删除
                    free(L->ptr.hp);
                    L->ptr.hp = NULL;
                }
            } else { // L 表中第一个元素是表
                L->ptr.hp = Delete_GL(L->ptr.hp, x); // 删除子表中所有 x
            }
            if (L->ptr.hp == NULL) { // 如果 L 表第一个元素被删除，L 向后移动
                p = L;
                L = L->ptr.tp;
                free(p);
                isDeleteHead = 1;
            } else {
                isDeleteHead = 0;
            }
        } while (isDeleteHead);
        // 考虑剩余情况，此时 L 的第一个元素必然非空
        if (L->ptr.tp != NULL) {
            p = L->ptr.tp;
            p = Delete_GL(p, x);
            L->ptr.tp = p;
        }
    }
    return L;
}

// 打印广义表
void Print_GL(GLNode *L) {
    if (L == NULL) {
        printf("-1");
        return;
    }
    if (L->tag == ATOM) {
        printf("%c", L->atom);
        return;
    } else {
        GLNode *p;
        printf("(");
        Print_GL(L->ptr.hp);
        p = L->ptr.tp;
        while (p != NULL) {
            printf(",");
            Print_GL(p->ptr.hp);
            p = p->ptr.tp;
        }
        printf(")");
    }
}

// 释放内存空间
void Free_GL(GLNode *L) {
    if (L == NULL) {
        return;
    }

    if (L->ptr.hp->tag == ATOM) {
        free(L->ptr.hp);
    } else {
        Free_GL(L->ptr.hp);
    }

    GLNode *p;
    while (L->ptr.tp != NULL) {
        p = L;
        L = L->ptr.tp;
        free(p);
    }
}

int main() {
    char S[MAXSIZE];
    char x;
    GLNode *L;
    scanf("%s %c", S, &x);
    L = Create_GL(S);
    L = Delete_GL(L, x);
    Print_GL(L);
    printf("\n");
    Free_GL(L);
    return 0;
}

