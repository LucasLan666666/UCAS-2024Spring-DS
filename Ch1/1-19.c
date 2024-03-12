/**
 * 阶乘
 */
#include <stdio.h>
#define  MAXARR 20
#define  MAXINT 4294967295
#define MAXLINE 1000

int main() {
    int n, arrsize;
    long a[MAXARR];
    int error;

    for (int i = 0; i < MAXARR; i++) {
        a[i] = 0;
    }
    error = 0;

    scanf("%d %d", &n, &arrsize);

    if (n > arrsize) {
        error = 1;
    } else {
        a[0] = 1;
        for (int i = 1; i < n; i++) {
            a[i] = a[i-1] * 2 * i;
            if (a[i] > MAXINT) {
                error = 1;
                break;
            }
        }
    }
    if (error) {
        printf("-1\n");
    } else {
        for (int i = 0; i < n - 1; i++) {
            printf("%ld ", a[i]);
        }
        printf("%ld\n", a[n-1]);
    }
    return 0;
}
