/**
 * 1.16
 * 写一个算法，自大到小依次输出顺序读入的三个整数，x，y和z的值
 */

#include <stdio.h>
#define NUM 3

int main() {
    int seq[3];

    scanf("%d %d %d", &seq[0], &seq[1], &seq[2]);
    for (int i = 0; i < NUM; i++) {
        for (int j = i + 1; j < NUM; j++) {
            if (seq[i] < seq[j]) {
                seq[i] = seq[i] ^ seq[j];
                seq[j] = seq[i] ^ seq[j];
                seq[i] = seq[i] ^ seq[j];
            }
        }
    }
    printf("%d %d %d\n", seq[0], seq[1], seq[2]);
    return 0;
}
