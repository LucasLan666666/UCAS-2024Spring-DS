/**
 * 试写出求递归函数Ｆ(n)的递归算法，并消除递归:
 * F(n ) = n + 1 (n = 0)
 * F(n) = n * F(n / 2) (n > 0)
 */

#include <stdio.h>

int F(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * F(n/2);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", F(n));
    return 0;
}
