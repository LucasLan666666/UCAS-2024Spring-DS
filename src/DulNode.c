#include "head.h"

typedef struct DulNode {
    QElemType data;
    struct DulNode *prior;
    struct DulNode *next;
} DulNode, *DuLinkList;
