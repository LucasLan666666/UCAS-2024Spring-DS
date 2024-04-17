/**
 * 顺序表比较
 */

#include <stdio.h>
#define MAXLEN 1000

void Input2Array(char *arr);
int cmp(char *a, char *b);

int main() {
    char a[MAXLEN];
    char b[MAXLEN];

    Input2Array(a);
    Input2Array(b);
    printf("%d\n", cmp(a, b));

    return 0;
}

void Input2Array(char *arr) {
    char c;
    for (int i = 0;;i++) {
        scanf("%c", &arr[i]);
        scanf("%c", &c);
        if (c == '\n') {
            arr[i + 1] = '\0';
            break;
        }
    }
}

int cmp(char *a, char *b) {
    int i = 0;
    while (a[i] == b[i] && a[i] != '\0') {
        i++;
    }
    if (a[i] == b[i]) {
        return 0;
    } else if (a[i] < b[i]) {
        return 1;
    } else {
        return 2;
    }
}
