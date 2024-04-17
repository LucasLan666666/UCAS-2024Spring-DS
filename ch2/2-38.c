/**
 * 设有一双向循环链表，每个节点中除有prior,data和next三个域外，还增设了一个访问频度域freq。
 * 在链表被启用之前，频度域freq的值均初始化为0，而每当对链表进行一次LOCATE(L,x)的操作后，被访问的节点（即元素值等于x的节点）中的频度域freq的值便增1，
 * 同时调整链表中节点之间的次序，使其按访问频度非递增的次序顺序排列，以便始终保持被频繁访问的节点总是靠近表头结点。
 * 编写符合上述要求的LOCATE操作的算法。
 */

#include <stdio.h>
#include <stdlib.h>

int seq;

typedef struct Lnode {
    int data;
    int seq;
    int freq;
    struct Lnode *prior;
    struct Lnode *next;
} Lnode;

Lnode *lalloc(void);
Lnode *buildlist();
Lnode *locate(Lnode *plist, int data);
void insert(Lnode *pa, Lnode *pb);
void printlist(Lnode *plist);

int main() {
    Lnode *plist;
    int len;
    int data;
    char c;

    scanf("%d", &len);
    plist = buildlist();
    do {
        scanf("%d", &data);
        plist = locate(plist, data);
        scanf("%c", &c);
    } while (c != '\n');
    printlist(plist);
    return 0;
}

Lnode *lalloc(void) {
    return (Lnode *)malloc(sizeof(Lnode));
}

Lnode *buildlist() {
    Lnode *p, *plist;
    char c;
    int data;

    scanf("%d", &data);
    plist = lalloc();
    plist->data = data;
    plist->freq = 0;
    plist->seq = 0;
    plist->prior = NULL;
    plist->next = NULL;
    p = plist;

    while (1) {
        scanf("%c", &c);
        if (c == '\n') {
            break;
        }
        scanf("%d", &data);
        p->next = lalloc();
        p->next->prior = p;
        p = p->next;
        p->data = data;
        p->freq = 0;
        p->seq = 0;
        p->next = NULL;
    }
    return plist;
}

Lnode *locate(Lnode *plist, int data) {
    Lnode *pd, *ptail;
    pd = NULL;

    // 获取待移动节点
    for (Lnode *p = plist; p != NULL; p = p->next) {
        if (p->data == data) {
            if (p->freq == 0) {
                p->seq = ++seq;
            }
            p->freq++;
            pd = p;
        }
        ptail = p;
    }
    if (pd == NULL) {
        return plist;
    }

    // 删除待移动结点
    if (pd != plist) {
        pd->prior->next = pd->next;
    } else {
        plist = pd->next;
    }
    if (pd != ptail) {
        pd->next->prior = pd->prior;
    } else {
        ptail = pd->prior;
    }

    // 将结点插入到新位置
    /**
     * 插入到头部
     * 1. 比最大频数还大
     * 2. 和表头频数相同且优先级最高
     */
    if (pd->freq > plist->freq || plist->freq == pd->freq && pd->seq < plist->seq) {
        pd->prior = NULL;
        pd->next = plist;
        plist->prior = pd;
        plist = pd;
    }
    /**
     * 插入到尾部
     * 1. 比最小频数还小
     * 2. 和尾部频数相同且优先级最低
     */
    else if (pd->freq < ptail->freq || ptail->freq == pd->freq && pd->seq > ptail->seq) {
        insert(ptail, pd);
        ptail = pd;
    }
    /**
     * 插入到中间
     * 1. 与所有结点频数都不同，夹在中间
     * 2. 和某个结点频数相同
     */
    else {
        for (Lnode *p = ptail->prior; p != NULL; p = p->prior) {
            // 1
            if (p->freq > pd->freq && p->next->freq < pd->freq) {
                insert(p, pd);
                break;
            }
            // 2
            else if (p->freq == pd->freq) {
                while (p->freq == pd->freq && p->seq > pd->seq) {
                    p = p->prior;
                }
                insert(p, pd);
                break;
            }
        }
    }
    return plist;
}

void insert(Lnode *pa, Lnode *pb) {
    pb->prior = pa;
    pb->next = pa->next;
    if (pa->next != NULL) {
        pa->next->prior = pb;
    }
    pa->next = pb;
}

void printlist(Lnode *plist) {
    Lnode *pnode;
    pnode = plist;
    if (plist == NULL) {
        printf("NULL\n");
        return;
    }
    while (pnode != NULL) {
        if (pnode == plist) {
            printf("%d", plist->data);
        } else {
            printf(" %d", pnode->data);
        }
        pnode = pnode->next;
    }
    printf("\n");
}
