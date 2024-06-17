#include <stdio.h>
#include <stdlib.h>

/*
**  试完成边界标志法和依首次适配策略进行分配相应的回收释放块的算法
*/



typedef struct BlockNode {
    int start; /* 起始地址 */
    int size;  /* 块空间大小 */
    struct BlockNode *prev, *next;
} BlockNode;



/* 初始化 */
void
InitList(BlockNode *head)
{
    head->start = 0;
    head->size = 0;
    head->prev = head->next = head;
}



/* 插入块，按起始地址排序 */
void
InsertBlock(BlockNode *head, int start, int size)
{
    BlockNode *newNode = (BlockNode *)malloc(sizeof(BlockNode));
    newNode->start = start;
    newNode->size = size;

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
    int flag, start, size;

    while (scanf("%d%d%d", &flag, &start, &size) == 3) {
        InsertBlock(head, start, size);
    }
}



/* 合并相邻的空闲块 */
void
MergeFreeBlocks(BlockNode *head)
{
    BlockNode *current = head->next;
    while (current->next != head) {
        if (current->start + current->size == current->next->start)
        {
            current->size += current->next->size;
            BlockNode *temp = current->next;
            current->next = temp->next;
            temp->next->prev = current;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

/* 打印空闲块的状态 */
void
PrintFreeBlocks(BlockNode *head)
{
    BlockNode *current = head->next;
    while (current != head) {
        printf("0 %d %d\n", current->start, current->size);
        current = current->next;
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
