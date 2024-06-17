#include <stdio.h>
#include <stdlib.h>

/*
** 设被管理空间的上下界地址分别由变量 highbound 和 lowbound 给出，形成一个由同样大小的块
** 组成的“堆”。试写一个算法，将所有 tag 域为 0 的块按始址递增顺序链接成一个可利用空间表
*/



typedef struct BlockNode {
    int flag;  /* 标志位，0 表示空闲，1 表示已分配 */
    int start; /* 起始地址 */
    int size;  /* 块空间大小 */
    struct BlockNode *prev, *next;
} BlockNode;



/* 初始化 */
void
InitList(BlockNode *head)
{
    head->flag = 0;
    head->start = 0;
    head->size = 0;
    head->prev = head->next = head;
}



/* 插入块，按起始地址排序 */
void
InsertBlock(BlockNode *head, int flag, int start, int size)
{
    BlockNode *newNode = (BlockNode *)malloc(sizeof(BlockNode));
    newNode->flag = flag;
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
    int flag, start, size, begin, end;

    scanf("%d%d%d", &begin, &end, &size);
    start = begin;

    while (scanf("%d", &flag) != EOF) {
        InsertBlock(head, flag, start, size);
        start += size;
    }
}



/* 合并相邻的空闲块 */
void
MergeFreeBlocks(BlockNode *head)
{
    BlockNode *current = head->next;
    while (current->next != head) {
        if (current->flag == 0 &&
            current->flag == current->next->flag &&
            current->start + current->size == current->next->start)
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
    int full = 1;
    while (current != head) {
        if (current->flag == 0) {
            full = 0;
            printf("%d %d %d\n", current->flag, current->start, current->size);
        }
        current = current->next;
    }
    if (full)
        printf("0 0 0\n");
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
