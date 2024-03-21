#include "head.h"

/* 线性表的顺序存储结构 */
typedef struct {
    ElemType data[MAXSIZE];
    int length;
} SqList;

/**
 * 获得元素
 * Status 是函数的类型，其值是函数结果状态代码，如 OK 等
 * 初始条件：顺序线性表 L 已存在，1<=i<=ListLength(L)
 * 操作结果：用 e 返回 L 中第 i 个数据元素的值
 */
Status GetElem(SqList L, int i, ElemType *e) {
    if (L.length == 0 || i < 1 || i > L.length) {
        return ERROR;
    }
    *e = L.data[i - 1];
    return OK;
}

/**
 * 插入操作
 * 初始条件：顺序线性表 L 已存在，1<=i<=ListLength(L)
 * 操作结果：在 L 中第 i 个位置之前插入新的数据元素 e，L 的长度加 1
 */
Status ListInsert(SqList *L, int i, ElemType e) {
    if (L->length == MAXSIZE) {
        return ERROR;
    }
    if (i < 1 || i > L->length + 1) {
        return ERROR;
    }
    if (i <= L->length) {
        for (int k = L->length - 1; k >= i - 1; k--) {
            L->data[k + 1] = L->data[k];
        }
    }
    L->data[i - 1] = e;
    L->length++;
    return OK;
}

/**
 * 删除操作
 * 初始条件：顺序线性表 L 已存在，1<=i<=ListLength(L)
 * 操作结果：删除 L 的第 i 个数据元素，并用 e 返回其值，L 的长度减 1
 */
Status ListDelete(SqList *L, int i, ElemType *e) {
    if (L->length == 0) {
        return ERROR;
    }
    if (i < 1 || i > L->length) {
        return ERROR;
    }
    *e = L->data[i - 1];
    if (i < L->length) {
        for (int k = i; k < L->length; k++) {
            L->data[k - 1] = L->data[k];
        }
    }
    L->length--;
    return OK;
}
