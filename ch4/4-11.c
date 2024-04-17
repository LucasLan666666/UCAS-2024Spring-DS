/**编写算法，求得所有包含在串s中而不包含在串t中的字符（s中重复的字符只选一个）构成的新串r，
 * 以及r中每个字符在s中第一次出现的位置
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    int index;
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
        p->index = index;
        p->next = NULL;
        index++;
    }
    head->data = index;
    return head;
}

void DeleteNode(String s, NodePtr pc) {
    NodePtr pre = s;
    while (pre->next != NULL && pre->next != pc) {
        pre = pre->next;
    }
    if (pre->next == NULL) {
        return;
    }
    pre->next = pc->next;
    free(pc);
}

void SimplifyString(String s) {
    NodePtr pi, pj;
    pi = s->next;
    while (pi != NULL && pi->next != NULL) {
        pj = pi->next;
        while (pj != NULL) {
            if (pi->data == pj->data) {
                NodePtr tmp = pj;
                pj = pj->next;
                DeleteNode(s, tmp);
            } else {
                pj = pj->next;
            }
        }
        pi = pi->next;
    }
}

void DeleteChar(String s, String t) {
    NodePtr pi, pj;
    pi = s->next;
    while (pi != NULL) {
        pj = t->next;
        while (pj != NULL) {
            if (pi->data == pj->data) {
                break;
            }
            pj = pj->next;
        }
        if (pj != NULL) {
            NodePtr tmp = pi;
            pi = pi->next;
            DeleteNode(s, tmp);
        } else {
            pi = pi->next;
        }
    }
}

void PrintString(String s) {
    NodePtr p = s->next;
    if (p == NULL) {
        printf("-1\n");
        return;
    }
    while (p != NULL) {
        printf("%c", p->data);
        p = p->next;
    }
    putchar(' ');
    p = s->next;
    while (p != NULL) {
        printf("%d", p->index);
        p = p->next;
    }
    putchar('\n');
}

void FreeString(String s) {
    NodePtr p = s;
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
    SimplifyString(s);
    t = CreateString();
    DeleteChar(s, t);
    PrintString(s);
    FreeString(s);
    FreeString(t);
    return 0;
}