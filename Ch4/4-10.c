/**
 * 编写对串求逆的递推算法
 */

#include <stdio.h>
#include <string.h>
#define MAXLEN 100

int main() {
    char c[MAXLEN];
    fgets(c, MAXLEN, stdin);
    int len = strlen(c);
    if (c[len - 1] == '\n') {
        c[len - 1] = '\0';
        len--;
    }
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        c[i] = c[i] ^ c[j];
        c[j] = c[i] ^ c[j];
        c[i] = c[i] ^ c[j];
    }
    printf("%s\n", c);
    return 0;
}
