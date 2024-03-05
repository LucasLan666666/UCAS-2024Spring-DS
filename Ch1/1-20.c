/**
 * 编写算法求一元多项式的值
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    int x, n;
    int *a;
    int result;

    scanf("%d %d\n", &x, &n);
    a = (int *)calloc(n + 1, sizeof(int));
    for (int i = 0; i <= n; i++) {
        scanf("%d ", &a[i]);
    }
    result = 0;

    // 用霍纳规则高效求多项式的值
    for (int i = n; i >= 0; i--) {
        result = result*x + a[i];
    }

    printf("%d\n", result);
    return 0;
}