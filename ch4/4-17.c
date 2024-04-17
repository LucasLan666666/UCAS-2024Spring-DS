/**
 * 编写算法，实现串的基本操作Replace(&S, T, V)，替换
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int Status;

typedef struct Node {
    char data;
    struct Node *next;
} Node, *NodePtr, *String;

String CreateString(void) {
    NodePtr p, head;
    p = head = (Node *)malloc(sizeof(Node));
    head->next = NULL;

    int c;
    int index = 0;
    while ((c = getchar()) != EOF && !isspace(c)) {
        p->next = (Node *)malloc(sizeof(Node));
        p = p->next;
        p->data = c;
        p->next = NULL;
        index++;
    }
    head->data = index;
    return head;
}

Status StrCompare(NodePtr pre, String T) {
    NodePtr ps, pt;
    Status status;
    ps = pre->next;
    pt = T->next;
    while (ps != NULL && pt != NULL) {
        if (ps->data != pt->data) {
            status = ERROR;
            break;
        }
        ps = ps->next;
        pt = pt->next;
    }
    if (pt == NULL) {
        status = OK;
    }
    return status;
}

void Delete(NodePtr pre, int len) {
    NodePtr tmp;
    for (int i = 0; i < len; i++) {
        tmp = pre->next;
        pre->next = tmp->next;
        free(tmp);
    }
}

NodePtr Insert(NodePtr pre, String V) {
    NodePtr p, pv;
    pv = V->next;
    for (int i = 0; i < V->data; i++) {
        p = (NodePtr)malloc(sizeof(Node));
        p->data = pv->data;
        p->next = pre->next;
        pre->next = p;
        pre = p;
        pv = pv->next;
    }
    return pre;
}

void Replace(String S, String T, String V) {
    NodePtr pre;
    pre = S;
    while (pre != NULL && pre->next != NULL) {
        if (StrCompare(pre, T) == OK) {
            Delete(pre, T->data);
            pre = Insert(pre, V);
        } else {
            pre = pre->next;
        }
    }
}

void PrintString(String S) {
    NodePtr p = S->next;
    while (p != NULL) {
        printf("%c", p->data);
        p = p->next;
    }
    putchar('\n');
}

void FreeString(String S) {
    NodePtr p = S;
    NodePtr tmp;
    while (p != NULL) {
        tmp = p;
        p = p->next;
        free(tmp);
    }
}

int main() {
    String s, t, v;
    s = CreateString();
    t = CreateString();
    v = CreateString();
    Replace(s, t, v);
    PrintString(s);
    FreeString(s);
    FreeString(t);
    FreeString(v);
    return 0;
}
