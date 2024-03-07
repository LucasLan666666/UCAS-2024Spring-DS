/**
 * 已知k阶斐波那契序列的定义为
 * f_0 = ... = f_{k-2} = 0, f_{k-1} = 1
 * f_n = f_{n-1} + ... + f_{n-k}, n = k, k+1, ...
 * 试编写求k阶裴波那契序列的第m项值的函数算法，k和m均以值调用的形式在函数参数表中出现。
 */

#include <stdio.h>
#include <stdlib.h>

int main () {
    int k, m;
    int num;

    scanf("%d %d", &k, &m);

    if (m < k - 1) {
        num = 0;
    }
    else if (m == k - 1) {
        num = 1;
    } else {
        int *seq;
        seq = (int *)calloc(m + 1, sizeof(int));
        seq[k - 1] = 1;

        // 递归求出前 m 项的值
        for (int i = k; i <= m ; i++) {
            for (int j = 1; j <= k; j++) {
                seq[i] += seq[i - j];
            }
        }

        num = seq[m];
    }

    printf("%d\n", num);
    return 0;
}
