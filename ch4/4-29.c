/**
 * 假设以结点大小为1（带头结点）的链表结构表示串，则在利用next函数值进行串匹配时，
 * 在每个结点中需设三个域：数据域chdata、指针域succ和指针域next。
 * 其中chdata域存放一个字符；succ域存放指向同一链表中后继结点的指针；next域在主串中存放指向同一链表中前驱结点的指针；
 * 在模式串中，存放指向当该结点的字符与主串中的字符不等时，在模式串中下一个应进行比较的字符结点（即与该字符的next函数值相对应的字符结点）的指针，
 * 若该节点字符的next函数值为0，则其next域的值应指向头结点。试按上述定义的结构改写串匹配的改进算法（KMP算法）。
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char chdata;
    struct Node *succ;
    struct Node *next;
} Node, *NodePtr, *String;


String CreateString(int len) {
    NodePtr front, pre, p;
    front = (NodePtr)malloc(sizeof(Node));
    front->chdata = len;
    front->succ = NULL;
    front->next = NULL;
    pre = front;
    while (len > 0) {
        p = (NodePtr)malloc(sizeof(Node));
        p->chdata = 0;
        p->next = NULL;
        p->succ = NULL;
        pre->succ = p;
        pre = p;
        len--;
    }
    return front;
}

void Fulfill(String str) {
    int i = 0;
    int c;
    NodePtr p = str->succ;
    while ((c = getchar()) != '\n' && c != EOF) {
        p->chdata = c;
        p = p->succ;
    }
}

void get_next_for_main(String S) {
    NodePtr pre, p;
    pre = S;
    p = S->succ;
    while (p != NULL) {
        p->next = pre;
        p = p->succ;
        pre = pre->succ;
    }
}

void get_next_for_pattern(String T) {
    NodePtr pi, pj;
    pi = T->succ;
    pj = T;
    T->succ->next = T;
    while (pi->succ != NULL)
    {
        if (pj == T || pi->chdata == pj->chdata) {
            pi = pi->succ;
            pj = pj->succ;
            pi->next = pj;
        } else {
            pj = pj->next;
        }
    }
}

void ClearString(String str) {
    NodePtr p, tmp;
    tmp = str;
    p = str;
    while (p != NULL) {
        p = str->next;
        free(tmp);
        tmp = p;
    }
}

int Index_KMP(String S, String T) {
    NodePtr pi = S->succ;
    NodePtr pj = T->succ;
    int base = 0;

    while (pi != NULL && pj != NULL) {
        if (pj == T || pi->chdata == pj->chdata) {
            pi = pi->succ;
            pj = pj->succ;
            base++;
        } else {
            pj = pj->next;
        }
    }
    if (pj == NULL) {
        return base - T->chdata;
    } else {
        return -1;
    }
}

int main() {
    String S, T;
    int len_S, len_T;
    scanf("%d %d", &len_S, &len_T);
    int c = getchar();
    S = CreateString(len_S);
    T = CreateString(len_T);
    Fulfill(S);
    Fulfill(T);
    get_next_for_main(S);
    get_next_for_pattern(T);
    printf("%d\n", Index_KMP(S, T));
    ClearString(S);
    ClearString(T);
    return 0;
}
