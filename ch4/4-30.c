#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int Status;
typedef char *String;


/**
 * 取主串 S 第 i 个位置
 * 长度为 len 的子串给sub
 */
Status SubString(String sub, String S, int i, int len) {
    if (i < 1 || i + len - 1 > S[0]) {
        return ERROR;
    }
    strncpy(sub + 1, S + i, len);
    sub[0] = len;
    sub[len + 1] = '\0';
    return OK;
}

/**
 * 求模式串 T 的 next 函数修正值并存入数组 nextval
 */
void get_nextval(String T, int *nextval) {
    int i, j;
    i = 1;
    j = 0;
    nextval[1] = 0;
    while (i < T[0]) // 此处 T[0] 表示 T 的长度
    {
        if (j == 0 || T[i] == T[j]) // T[i] 和 T[j] 分别表示后缀、前缀的单个字符
        {
            ++i;
            ++j;
            if (T[i] != T[j]) { // 若当前字符与前缀字符不同
                nextval[i] = j; // 则当前的 j 为 nextval 在 i 位置的值
            } else {
                nextval[i] = nextval[j]; //如果与前缀字符相同，则将前缀字符的 nextval 值赋值给 nextval 在 i 位置的值
            }
        }
        else
        {
            j = nextval[j]; // 若字符不相同，则 j 回溯
        }
    }
}

/**
 * KMP 模式匹配算法
 * 返回子串 T 在主串 S 中第 pos 个字符之后的位置。若不存在，则函数返回值为 0
 * T 非空，1 <= pos <= StrLength(S)
 */
int Index_KMP(String S, String T, int pos) {
    int i = pos; // i 用于主串 S 中当前位置下标，若 pos 不为 1，则从 pos 位置开始匹配
    int j = 1; // j 用于子串 T 中当前位置下标值
    int next[255];

    get_nextval(T, next); // 对串 T 分析，得到 next 数组
    while (i <= S[0] && j <= T[0]) {
        if (j == 0 || S[i] == T[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    if (j > T[0]) {
        return i - T[0] - 1;
    } else {
        return -1;
    }
}

int main() {
    char S[MAXSIZE];
    char T[MAXSIZE];
    int *next;
    int base;
    scanf("%s", &S[1]);
    S[0] = strlen(&S[1]);
    for (int len = S[0] - 1; len >= 1; len--) {
        for (int i = 1; i + len - 1 <= S[0]; i++) {
            SubString(T, S, i, len);
            base = Index_KMP(S, T, i + 1);
            if (base != -1) {
                printf("%s %d\n", &T[1], i - 1);
                return 0;
            }
        }
    }
    printf("-1\n");
    return 0;
}
