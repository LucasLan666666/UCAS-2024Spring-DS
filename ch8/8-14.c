#include <stdio.h>
#include <stdlib.h>

/*
**  试完成伙伴管理系统的存储回收算法
*/



typedef struct BlockNode {
    int k;     /* 块空间大小为 2^k */
    int start; /* 起始地址 */
    struct BlockNode *prev, *next;
} BlockNode;



/* 初始化 */
void
InitList(BlockNode *head)
{
    head->k = 0;
    head->start = 0;
    head->prev = head->next = head;
}



/* 插入块，按起始地址排序 */
void
InsertBlock(BlockNode *head, int k, int start)
{
    BlockNode *newNode = (BlockNode *)malloc(sizeof(BlockNode));
    newNode->k = k;
    newNode->start = start;

    BlockNode *current = head;

    while (current->next != head && current->next->start < start)
        current = current->next;

    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
}



/* 根据空闲块和待回收块创建链表 */
void
CreateList(BlockNode *head)
{
    int k, start, c;

    while (scanf("%d", &k) != EOF) { /* 先读取每一行开头的 k */
        while ((c = getchar()) != EOF && c != '\n') {
            scanf("%d", &start); /* 再读取每个块的起始地址 */
            InsertBlock(head, k, start);
        }
    }
}



/* 求 2 的 k 次方 */
#define PowerOfTwo(k) (1 << (k))



/* 合并 */
void
MergeFreeBlocks(BlockNode *head)
{
    int mergeOK = 0; /* 判断是否全部合并完成 */

    while (!mergeOK) {
        mergeOK = 1;
        BlockNode *current = head->next;
        while (current->next != head) {
            int power_curr = PowerOfTwo(current->k);
            int power_next = PowerOfTwo(current->k + 1);
            if (current->start % power_next == 0 &&
                current->start + power_curr == current->next->start &&
                current->k == current->next->k)
            {
                mergeOK = 0;
                current->k++;
                BlockNode *temp = current->next;
                current->next = temp->next;
                temp->next->prev = current;
                free(temp);
            } else {
                current = current->next;
            }
        }
    }
}



#define max(a,b) ((a) > (b)) ? (a) : (b)



/* 获取所有块中 k 的最大值 */
int
GetMaxK(BlockNode *head)
{
    int maxK = 0;
    BlockNode *current = head->next;
    while (current != head) {
        maxK = max(maxK, current->k);
        current = current->next;
    }
    return maxK;
}



/* 打印空闲块的状态 */
void
PrintFreeBlocks(BlockNode *head)
{
    int maxK = GetMaxK(head);
    int i;
    for (i = 0; i <= maxK; i++) {
        BlockNode *current = head->next;
        int appear = 0;
        while (current != head) {
            if (current->k == i) {
                if (!appear) {
                    appear = 1;
                    printf("%d", i);
                }
                printf(" %d", current->start);
            }
            current = current->next;
        }
        if (appear)
            printf("\n");
    }
}



/* 释放链表 */
void
ClearList(BlockNode *head)
{
    BlockNode *current = head->next;
    do {
        BlockNode *temp = current;
        current = current->next;
        free(temp);
    } while (current != head);
}




int
main(void)
{
    BlockNode *head; /* 指向首结点的指针 */
    head = (BlockNode *)malloc(sizeof(BlockNode));
    InitList(head);
    CreateList(head);
    MergeFreeBlocks(head);
    PrintFreeBlocks(head);
    ClearList(head);
    return 0;
}
