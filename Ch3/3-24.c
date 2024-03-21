/**
 * 试编写如下定义的递归函数的递归算法，并根据算法画出求 ｇ(5, 2) 时栈的变化过程。
 * g(m, n)  = 0 (m = 0, n >= 0)   g(m, n) = g(m-1, 2n) + n (m>0, n>=0)
 */

#include <stdio.h>

int g(int m, int n) {
    int result;
    if (m > 0 && n >= 0) {
        result = g(m-1, 2*n) + n;
    } else {
        result = 0;
    }
    return result;
}

int main() {
    int m, n;
    scanf("%d,%d", &m, &n);
    printf("%d\n", g(m, n));
    return 0;
}