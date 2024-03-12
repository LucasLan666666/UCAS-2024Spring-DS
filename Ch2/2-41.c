/**
 * 试以循环链表作稀疏多项式的存储结构，编写求其导函数的算法，要求利用原多项式中的节点空间存放其导函数（多项式），同时释放所有无用（被删）节点。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct PolyTerm {
    int coef; // 系数
    int exp; // 指数
} PolyTerm;

typedef struct PolyNode {
    PolyTerm data;
    struct PolyNode *next;
} PolyNode, *PolyLink;

typedef PolyLink LinkedPoly;

LinkedPoly palloc(void); // 创建结点
LinkedPoly buildpoly(void); // 读取输入，构建多项式
LinkedPoly derivation(LinkedPoly poly); // 求导
LinkedPoly modify(LinkedPoly poly); // 整理多项式
void printpoly(LinkedPoly poly); // 打印多项式
void quicksort(LinkedPoly poly); // 根据 x 的指数进行快排

int main() {
    LinkedPoly poly;
    poly = buildpoly();
    poly = derivation(poly);
    poly = modify(poly);
    printpoly(poly);
    return 0;
}

LinkedPoly palloc(void) {
    return (LinkedPoly)malloc(sizeof(PolyNode));
}

LinkedPoly buildpoly(void) {
    LinkedPoly p, plist;
    int c;
    int coef_u, sign, exp;

    // 创建头节点
    plist = p = palloc();
    // 读入系数符号
    c = getchar();
    if (c == '-') {
        sign = -1;
    } else {
        sign = 1;
        ungetc(c, stdin);
    }
    // 读入系数绝对值
    if (scanf("%d", &coef_u) != 1) {
        coef_u = 1;
    }
    // x 是否指数为 0
    if ((c = getchar()) == 'x') {
        // 读入指数
        c = getchar();
        if (c == '^') {
            scanf("%d", &exp);
        } else {
            exp = 1;
            ungetc(c, stdin);
        }
    } else {
        exp = 0;
        ungetc(c, stdin);
    }

    // 补充头结点内容
    plist->data.coef = sign * coef_u;
    plist->data.exp = exp;
    plist->next = NULL;

    while ((c = getchar()) != '\n') {
        // 创建节点
        p->next = palloc();
        p = p->next;
        // 读入系数符号
        if ((c = getchar()) == '-') {
            sign = -1;
        } else {
            sign = 1;
        }
        // 读入系数绝对值
        if (scanf("%d", &coef_u) != 1) {
            coef_u = 1;
        }
        // x 是否指数为 0
        if ((c = getchar()) == 'x') {
            // 读入指数
            c = getchar();
            if (c == '^') {
                scanf("%d", &exp);
            } else {
                exp = 1;
                ungetc(c, stdin);
            }
        } else {
            exp = 0;
            ungetc(c, stdin);
        }
        // 补充结点内容
        p->data.coef = sign * coef_u;
        p->data.exp = exp;
        p->next = NULL;
    }
    return plist;
}

LinkedPoly derivation(LinkedPoly poly) {
    LinkedPoly p = poly;
    while (p != NULL) {
        p->data.coef = p->data.coef * p->data.exp;
        p->data.exp--;
        p = p->next;
    }
    return poly;
}

LinkedPoly modify(LinkedPoly poly) {
    LinkedPoly p, pre;
    // 首先按照降幂排序
    quicksort(poly);
    // 合并同类项
    p = poly;
    while (p != NULL) {
        while (p->next != NULL && p->data.exp == p->next->data.exp) {
            LinkedPoly tmp = p->next;
            p->data.coef += p->next->data.coef;
            p->next = p->next->next;
            free(tmp);
        }
        p = p->next;
    }
    // 消除 0 项
    // 检查最高项是否系数为零
    while (poly != NULL) {
        if (poly->data.coef == 0) {
            LinkedPoly tmp = poly;
            poly = poly->next;
            free(tmp);
        } else {
            break;
        }
    }
    // 检查剩下项是否系数为零，有则删去
    pre = poly;
    while (pre != NULL && pre->next != NULL) {
        if (pre->next->data.coef == 0) {
            pre->next = pre->next->next;
            free(pre->next);
        } else {
            pre = pre->next;
        }
    }
    return poly;
}

void printpoly(LinkedPoly poly) {
    LinkedPoly p = poly;
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    while (p != NULL) {
        // 打印符号
        if (p == poly) {
            if (p->data.coef < 0) {
                printf("- ");
            }
        } else {
            if (p->data.coef < 0) {
                printf(" - ");
            } else {
                printf(" + ");
            }
        }
        // 打印系数
        printf("%d", (p->data.coef < 0) ? - p->data.coef : p->data.coef);
        // 打印 x 的幂
        switch (p->data.exp) {
            case 0:
                break;
            case 1:
                printf("x");
                break;
            default:
                printf("x^%d", p->data.exp);
                break;
        }
        p = p->next;
    }
    putchar('\n');
}

void quicksort(LinkedPoly poly) {
    LinkedPoly p, q, r, s;
    int temp_coef;
    int temp_exp;
    if (poly == NULL || poly->next == NULL) {
        return;
    }
    p = poly;
    q = p->next;
    while (q != NULL) {
        if (q->data.exp > p->data.exp) {
            temp_exp = q->data.exp;
            temp_coef = q->data.coef;
            q->data.exp = p->data.exp;
            q->data.coef = p->data.coef;
            p->data.exp = temp_exp;
            p->data.coef = temp_coef;
        }
        q = q->next;
    }
    quicksort(poly->next);
    r = poly->next;
    s = poly;
    while (r != NULL) {
        if (r->data.exp > poly->data.exp) {
            temp_exp = r->data.exp;
            temp_coef = r->data.coef;
            r->data.exp = s->data.exp;
            r->data.coef = s->data.coef;
            s->data.exp = temp_exp;
            s->data.coef = temp_coef;
        }
        r = r->next;
    }
    quicksort(poly->next);
}
