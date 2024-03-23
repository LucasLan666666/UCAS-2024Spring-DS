/**
 * 编写算法，实现串的基本操作 StrCompare(S,T)
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
    while ((c = getchar()) != EOF && !isspace(c)) {
        p->next = (Node *)malloc(sizeof(Node));
        p = p->next;
        p->data = c;
        p->next = NULL;
    }
    return head;
}

Status StrCompare(String S, String T) {
    NodePtr ps, pt;
    Status status;
    ps = S->next;
    pt = T->next;
    while (ps != NULL && pt != NULL) {
        if (ps->data < pt->data) {
            status = -1;
            break;
        } else if (ps->data > pt->data) {
            status = 1;
            break;
        }
        ps = ps->next;
        pt = pt->next;
    }
    if (ps == NULL && pt == NULL) {
        status = 0;
    }
    return status;
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
    String s, t;
    s = CreateString();
    t = CreateString();
    printf("%d\n", StrCompare(s, t));
    FreeString(s);
    FreeString(t);
    return 0;
}
