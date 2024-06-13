/*
** 编写递归算法，从大到小输出给定二叉排序树中所有关键字不小于 x 的数据元素
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
Print(int *arr, int len, int key)
{
    int i;
    printf("%d", arr[len - 1]);
    for (i = len - 2; arr[i] >= key; i--)
        printf(" %d", arr[i]);
    printf("\n");
}



int
main(void)
{
    int arr[MAX_SIZE];
    int len;
    int key;
    ReadArray(arr, &len);
    scanf("%d", &key);
    Print(arr, len, key);
    return 0;
}