/**
 * 试写一个判别表达式中开,闭括号是否配对出现的算法。
 */

#include <stdio.h>
#define     OK 1
#define  ERROR 0

int main() {
    int top = -1;
    int c;
    int status;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == '(') {
            top++;
        } else if (c == ')') {
            top--;
        }
        if (top < -1) {
            status = ERROR;
            break;
        }
    }
    status = (top == -1) ? OK : ERROR;
    printf("%d\n", status);
    return 0;
}
