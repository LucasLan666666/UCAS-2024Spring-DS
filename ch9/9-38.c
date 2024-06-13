/*
** 试写一算法，将两棵二叉排序树合并成一棵二叉排序树
*/

#include <stdio.h>

#define MAX_SIZE 50

/* 开摆！！！！！ */



void
BuildArray(int *arr, int *len_ptr)
{
    int data;
    int mark;
    int i;

    while (scanf("%d", &data) != EOF) {
        mark = 0;
        if (data == -1)
            continue;
        for (i = 0; i < *len_ptr; i++) {
            if (data == arr[i]) {
                mark = 1;
                continue;
            }
        }
        if (!mark)
            arr[(*len_ptr)++] = data;
    }
}



void
Swap(int *a, int *b)
{
    if (*a != *b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}



int
Partition(int *arr, int low, int high)
{
    int pivot = arr[low];
    int last, i;

    last = low;
    for (i = low + 1; i <= high; i++) {
        if (arr[i] < pivot) {
            Swap(&arr[i], &arr[++last]);
        }
    }
    Swap(&arr[low], &arr[last]);
    return last;
}



void
QuickSort(int *arr, int low, int high)
{
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}



void
PrintArray(int *arr, int len)
{
    int i;
    printf("%d", arr[0]);
    for (i = 1; i < len; i++)
        printf(" %d", arr[i]);
    printf("\n");
}



int
main(void)
{
    int arr[MAX_SIZE];
    int len;

    BuildArray(arr, &len);
    QuickSort(arr, 0, len - 1);
    PrintArray(arr, len);
    return 0;
}