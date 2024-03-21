/**
 * 试写一算法，识别依次读入的一个以@为结束符的字符序列是否为形如“序列1&序列2”模式的字符序列。
 * 其中序列1和序列2中都不包含字符“&”，且序列2是序列1的逆序列。例如，“a+b&b+a”是属于该模式的字符序列，而“1+3&3-1”则不是。
 */

#include <stdio.h>
#define MAXLEN 1000

int main() {
    char str[MAXLEN];
    int top = -1;
    int c;
    while ((c = getchar()) != '&' && c != '@') {
        top++;
        str[top] = c;
    }
    while ((c = getchar()) != '@' && str[top] == c) {
        top--;
    }
    printf("%d\n", (top == -1) ? 1 : 0);
    return 0;
}
