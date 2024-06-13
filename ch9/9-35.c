/*
** 假设二叉排序树以后继线索链表作存储结构，编写输出该二叉排序树中所有大于 a 且小于 b 的关键
** 字的算法。
*/

#include <stdio.h>
#define MAX_SIZE 20

/* 受不鸟了，摆了摆了 */



void
ReadArray(int *arr, int *len_ptr)
{
    int i, c;

    i = 0;
    while (1) {
        scanf("%d", &arr[i++]);
        if ((c = getchar()) == '\n')
            break;
    }
    *len_ptr = i;
}



void
Print(int *arr, int len, int a, int b)
{
    int i;
    int first = 1;
    for (i = 1; arr[i] < b; i++) {
        if (arr[i] > a) {
            if (!first) {
                printf(" ");
            }
            printf("%d", arr[i]);
            first = 0;
        }
    }
    printf("\n");
}



int
main(void)
{
    int arr[MAX_SIZE];
    int len;
    int a, b;
    ReadArray(arr, &len);
    scanf("%d%d", &a, &b);
    Print(arr, len, a, b);
    return 0;
}