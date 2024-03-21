#include "head.h"

/* 线性表的静态链表存储结构 */
typedef struct {
    ElemType data;
    int cur; // 游标
} Compoment, StaticLinkList[MAXSIZE];

/**
 * 静态链表的初始化
 * 将一维数组 space 中各分量链成一备用链表
 * space[0].cur 为头指针，“0”表示空指针
 */
Status InitList(StaticLinkList space) {
    for (int i = 0; i < MAXSIZE - 1; i++) {
        space[i].cur = i + 1;
    }
    space[MAXSIZE - 1].cur = 0;
    return OK;
}

/**
 * 注意！
 * 未被使用的数组元素称为备用链表。
 * 数组第一个元素，即下标为 0 的元素的 cur，就存放备用链表的第一一个结点的下标
 * 数组的最后一个元素的 cur，则存放第一个有数值的元素的下标，相当于单链表中的头结点作用，当整个链表为空时，则为 0。
 */

/**
 * 静态链表的插入操作
 * 1. 若备用空间链表非空，则返回分配的结点下标，否则返回 0
 * 2. 在 L 中第 i 个元素之前插入新的数据元素 e
 */
int Malloc_SLL(StaticLinkList space) {
    int i = space[0].cur; // 当前数组第一个元素的cur存的值，就是要返回的第一个备用空闲的下标
    if (space[0].cur != 0) {
        space[0].cur = space[i].cur;
    }
    return i;
}
// Status ListInsert(StaticLinkList L, int i, ElemType e) {
//     int j, k, l;
//     k = MAXSIZE - 1; // 注意k首先是最后一个元素的下标
//     if(i < 1 || i > ListLength(L) + 1) {
//         return ERROR;
//     }
//     j = Malloc_SLL(L); // 获得空闲分量的下标
//     if (j != 0)
//     L[j].data= e; /* 将数据赋值給此分量的data*/
//     for(1- 1;1<= 1- 1; 1++) /找到第i个元素之前的位置*/
//     k = L[k].cur;
//     L[j].cur = L[k].cur;/*把第i个元素之前的cur赋值给新元素的cur*/
//     L[k].cur - j; /*把新元素的下标赋值給第 i个元素之前元素的cur*/
//     return OK;
//     return ERROR;
// }