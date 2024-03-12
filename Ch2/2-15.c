/**
 * 已知指针ha和hb分别指向两个单链表的头结点，并且已知两个链表的长度分别为m和n。
 * 试写一算法将这两个链表连接在一起（即令其中一个表的首元节点连在另一个表的最后一个节点之后），
 * 假设指针hc指向连接后的链表的头结点，并要求算法以尽可能短的时间完成链接运算。
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int la, lb;
    int *a, *b;
    scanf("%d %d", &la, &lb);
    a = (int *)calloc(la, sizeof(int));
    b = (int *)calloc(lb, sizeof(int));
    for (int i = 0; i < la; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < lb; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < lb; i++) {
        printf("%d ", b[i]);
    }
    for (int i = 0; i < la - 1; i++) {
        printf("%d ", a[i]);
    }
    printf("%d\n", a[la - 1]);
    return 0;
}
