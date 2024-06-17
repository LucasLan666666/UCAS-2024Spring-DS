#include <stdlib.h>
#define MAX_SIZE 100



typedef enum {
    false,
    true
} Status;



/* 顺序查找 */
int
Sequential_Search(int *a, int n, int key)
{
    int i;

    for (i = 1; i <= n; i++) {
        if (a[i] == key)
            return i;
    }

    return 0; /* 返回 0 说明查找失败，注意数组元素下标从 1 开始 */
}



/* 折半查找，针对有序数组 */
int
Binary_Search(int *a, int n, int key)
{
    int low, high, mid;
    low = 1;
    high = n;

    while (low <= high) {
        mid = (low + high) / 2;
        if (key < a[mid])
            high = mid - 1;
        else if (key > a[mid])
            low = mid + 1;
        else
            return mid;
    }
    return 0; /* 返回 0 说明查找失败 */
}



/*
** ======================================
** 斐波那契数列：
** 下标：  0  1  2  3  4  5  6  7  8  9
** 元素：  0  1  1  2  3  5  8 13 21 34
** ======================================
*/


/* 斐波那契查找 */
int
Fibonacci_Search(int *a, int n, int key)
{
    extern int F[MAX_SIZE];
    int low, high, mid;
    int i, k;
    low = 1, high = n, k = 0;

    while (n > F[k] - 1)            /* 计算 n 位于斐波那契数列的位置 */
        k++;
    for (i = n; i < F[k] - 1; i++)  /* 将不满的数值补全 */
        a[i] = a[n];

    while (low <= high) {
        mid = low + F[k - 1] - 1;   /* 计算当前分隔下标 */

        if (key < a[mid]) {         /* 若查找记录小于当前分割记录 */
            high = mid - 1;         /* 最高下标调整到分隔下标 mid-1 处*/
            k = k - 1;              /* 斐波那契数列下标减一位 */
        }
        else if (k > a[mid]) {      /* 若查找记录大于当前分割记录 */
            low = mid + 1;          /* 最低下标调整到分隔下标 mid+1 处*/
            k = k - 2;              /* 斐波那契数列下标减两位 */
        }
        else {
            if (mid <= n)
                return mid;         /* 若相等则说明 mid 即为查找到的位置 */
            else
                return n;           /* 若 mid > n 说明是补全数值，返回 n */
        }
    }
    return 0;
}



/* 二叉树的二叉链表结点结构定义 */
typedef struct BiTNode
{
    int data;
    int bf;     /* 平衡因子，二叉排序树用 */
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/*
** 递归查找二叉排序树中是否存在 key，
** 指针 f 指向 T 的双亲，其初始调用值为 NULL
** 若查找成功，则指针 p 指向该数据元素结点，并返回 true
** 否则指针p指向查找路径上访问的最后一个结点并返回 false
*/
Status
SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
    if (!T) {                                       /* 查找不成功 */
        *p = f;
        return false;
    }
    else if (key == T->data) {                      /* 查找成功 */
        *p = f;
        return true;
    }
    else if (key < T->data)                         /* 在左子树继续查找 */
        return SearchBST(T->lchild, key, T, p);
    else                                            /* 在右子树继续查找 */
        return SearchBST(T->rchild, key, T, p);
}

/*
** 当二叉排序树 T 中不存在关键字等于 key 的数据元素时，
** 插入 key 并返回 true，否则返回 false
*/
Status
InsertBST(BiTree *T, int key)
{
    BiTree p, s;

    /* 查找不成功，说明可以插入 */
    if (!SearchBST(*T, key, NULL, &p)) {
        /* 初始化待插入结点 s */
        s = (BiTree)malloc(sizeof(BiTree));
        s->data = key;
        s->lchild = s->rchild = NULL;

        if (!p)                     /* p 为空，说明 T 为空树 */
            *T = s;                 /* 插入 s 为新的根节点 */
        else if (key < p->data)
            p->lchild = s;          /* 插入 s 为左孩子 */
        else
            p->rchild = s;          /* 插入 s 为右孩子 */
        return true;
    }
    /* 已经有相同结点，无需插入*/
    else {
        return false;
    }
}

/*
** 若二叉排序树 T 中存在关键字等于 key 的数据元素时，删除该结点，返回 true；
** 否则返回 false
*/
Status
DeleteBST(BiTree *T, int key)
{
    Status Delete(BiTree *p);

    /* 不存在该数据元素 */
    if (!*T) {
        return false;
    }
    /* 存在该数据元素，删除它 */
    else {
        if (key == (*T)->data)                      /* 找到力！就是 T */
            return Delete(T);
        else if (key < (*T)->data)                  /* 在左子树找找 */
            return DeleteBST(&(*T)->lchild, key);
        else                                        /* 在右子树找找 */
            return DeleteBST(&(*T)->rchild, key);
    }
}

/*
** 从二叉排序树中删除结点 p，并重接它的左或右子树
*/
Status
Delete(BiTree *p)
{
    BiTree q, s;

    /* 右子树为空，只用重接左子树 */
    if ((*p)->rchild == NULL) {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    /* 左子树为空，只用重接右子树 */
    else if ((*p)->lchild == NULL) {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    /* 左右均非空 */
    else {
        q = *p;
        s = (*p)->lchild;

        while (s->rchild) {             /* 左转，然后向右到尽头（待删除节点前驱结点） */
            q = s;
            s = s->rchild;
        }
        (*p)->data = s->data;           /* s 指向被删结点直接前驱，代替被删结点 */
        if (q != *p)
            q->rchild = s->lchild;      /* 重接 q 的右子树 */
        else
            q->lchild = s->lchild;      /* 重接 q 的左子树 */
        free(s);
    }
    return true;
}



/*
** 对以 p 为根的二叉排序树作右旋处理
** 处理之后 p 指向新的树根结点，即旋转处理之前的左子树的根结点
*/
void
R_Rotate(BiTree *p)
{
    BiTree L;
    L = (*p)->lchild;                   /* L 指向 p 的左子树根结点 */
    (*p)->lchild = L->rchild;           /* L 的右子树挂接为 p 的左子树 */
    L->rchild = (*p);
    *p = L;                             /* p 指向新的根节点 */
}

/*
** 对以 p 为根的二叉排序树作左旋处理
** 处理之后 p 指向新的树根结点，即旋转处理之前的右子树的根结点
*/
void
L_Rotate(BiTree *p)
{
    BiTree R;
    R = (*p)->rchild;                   /* L 指向 p 的右子树根结点 */
    (*p)->rchild = R->lchild;           /* L 的左子树挂接为 p 的右子树 */
    R->lchild = (*p);
    *p = R;                             /* p 指向新的根节点 */
}



#define LH +1      /* 左高 */
#define EH  0      /* 等高 */
#define RH -1      /* 右高 */

/*
** 对以指针 T 所指结点为根的二叉树作左平衡旋转处理
** 本算法结束时，指针 T 指向新的根节点
*/
void
LeftBalance(BiTree *T)
{
    BiTree L, Lr;
    L = (*T)->lchild;   /* L 指向 T 的左子树根节点 */

    switch (L->bf) {
        case LH:    /* 新结点插入在 T 的左孩子的左子树上，要做单右旋处理 */
            (*T)->bf = L->bf = EH;
            R_Rotate(T);
            break;
        case RH:    /* 新结点插入在 T 的左孩子的右子树上，要做双旋处理 */
            Lr = L->rchild;
            switch (Lr->bf) {   /* 修改 T 以及左孩子平衡因子 */
                case LH:
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                case EH:
                    (*T)->bf = EH;
                    L->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(&(*T)->lchild);    /* 对 T 的左子树作左旋平衡处理 */
            R_Rotate(T);                /* 对 T 作右旋平衡处理 */
    }
}

/*
** 对以指针 T 所指结点为根的二叉树作右平衡旋转处理
** 本算法结束时，指针 T 指向新的根节点
*/
void
RightBalance(BiTree *T)
{
    BiTree R, Rl;
    R = (*T)->rchild;   /* R 指向 T 的右子树根节点 */

    switch (R->bf) {
        case LH:    /* 新结点插入在 T 的右孩子的左子树上，要做双旋处理 */
            Rl = R->lchild;
            switch (Rl->bf) {   /* 修改 T 以及右孩子平衡因子 */
                case LH:
                    (*T)->bf = EH;
                    R->bf = RH;
                    break;
                case EH:
                    (*T)->bf = EH;
                    R->bf = EH;
                    break;
                case RH:
                    (*T)->bf = LH;
                    R->bf = EH;
                    break;
            }
            Rl->bf = EH;
            R_Rotate(&(*T)->rchild);    /* 对 T 的右子树作右旋平衡处理 */
            L_Rotate(T);                /* 对 T 作左旋平衡处理 */
        case RH:    /* 新结点插入在 T 的右孩子的右子树上，要做单左旋处理 */
            (*T)->bf = R->bf = EH;
            L_Rotate(T);
            break;
    }
}



/*
** 若在平衡的二叉排序树 T 中不存在和 e 有相同关键字的结点，
** 则插入一个数据元素为 e 的新结点并返回 1，否则返回 0。
** 若因插入而使二叉排序树失去平衡，则作平衡旋转处理，
** 布尔变量 taller 反应 T 长高与否。
*/
Status
InsertAVL(BiTree *T, int e, Status *taller)
{
    if (!*T) {
        /* 插入新结点，树“长高”，置 taller 为 true */
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = true;
    }
    else {
        /* 树中已存在和 e 有相同关键字结点，不再插入 */
        if (e == (*T)->data) {
            *taller = false;
            return false;
        }
        /* 应继续在 T 左子树中搜索 */
        if (e < (*T)->data) {
            if (!InsertAVL(&(*T)->lchild, e, taller)) /* 未插入 */
                return false;
            if (taller) { /* 已插入到 T 的左子树中且左子树长高 */
                switch ((*T)->bf) { /* 检查 T 的平衡度 */
                    case LH: /* 原本左子树更高，需要左平衡 */
                        LeftBalance(T);
                        *taller = false;
                        break;
                    case EH: /* 原本左右子树等高，现在因为左子树增高而树增高 */
                        (*T)->bf = LH;
                        *taller = true;
                        break;
                    case RH: /* 原本右子树更高，现在左右子树等高 */
                        (*T)->bf = EH;
                        *taller = false;
                        break;
                }
            }
        }
        /* 应继续在 T 右子树中搜索 */
        else {
            if (!InsertAVL(&(*T)->rchild, e, taller)) /* 未插入 */
                return false;
            if (taller) { /* 已插入到 T 的右子树中且右子树长高 */
                switch ((*T)->bf) { /* 检查 T 的平衡度 */
                    case LH: /* 原本左子树更高，现在左右子树等高 */
                        (*T)->bf = EH;
                        *taller = false;
                        break;
                    case EH: /* 原本左右子树等高，现在因为右子树增高而树增高 */
                        (*T)->bf = RH;
                        *taller = true;
                        break;
                    case RH: /* 原本右子树更高，需要右平衡 */
                        RightBalance(T);
                        *taller = false;
                        break;
                }
            }
        }
    }
    return true;
}
