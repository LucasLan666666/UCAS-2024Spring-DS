#include "head.h"
#include <string.h>

/**
 * 取主串 S 第 i 个位置
 * 长度为 len 的子串给sub
 */
Status SubString(String sub, String S, int i, int len) {
    if (i < 1 || i + len - 1 > S[0]) {
        return ERROR;
    }
    strncpy(sub, S + i, len);
    sub[0] = len;
    sub[len + 1] = '\0';
    return OK;
}

/**
 * 查找子串位置(用串的其他操作实现)
 * T 为非空串。若主串 S 中第 pos 个字符之后存在与 T 相等的子串，
 * 则返回第一个这样的子串在 S 中的位置，否则返回 0
 */
int Index_1(String S, String T, int pos) {
    int n, m, i;
    String sub;
    if (pos > 0) {
        n = strlen(S);
        m = strlen(T);
        i = pos;
        while (i <= n - m + 1) {
            SubString(sub, S, i, m);
            if (strcmp(sub, T) != 0) {
                ++i;
            } else {
                return i;
            }
        }
    }
    return 0;
}

/**
 * 查找子串位置(用数组实现)
 * T 为非空串。若主串 S 中第 pos 个字符之后存在与 T 相等的子串，
 * 则返回第一个这样的子串在 S 中的位置，否则返回 0
 * 1 <= pos <= StrLength(S)
 */
int Index_2(String S, String T, int pos) {
    int i = pos; // i 用于主串 S 中当前位置下标，若 pos 不为 1，则从 pos 位置开始匹配
    int j = 1; // j 用于子串 T 中当前位置下标值

    while (i <= S[0] && j <= T[0]) // 若 i 小于 S 长度且 j 小于 T 的长度时循环
    {
        if (S[i] == T[j]) { // 两字母相等则继续
            ++i;
            ++j;
        } else { // 指针后退重新开始匹配
            i = i - j + 2; // i 退回到上次匹配首位的下一位
            j = 1; // j 退回到子串 T 的首位
        }
    }
    if (j > T[0]) {
        return i - T[0];
    } else {
        return 0;
    }
    return 0;
}

/**
 * 通过计算返回子串 T 的 next 数组
 */
void get_next(String T, int *next) {
    int i, j;
    i = 1;
    j = 0;
    next[1] = 0;
    while (i < T[0]) // 此处 T[0] 表示 T 的长度
    {
        if (j == 0 || T[i] == T[j]) // T[i] 和 T[j] 分别表示后缀、前缀的单个字符
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
        {
            j = next[j]; // 若字符不相同，则 j 回溯
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

    get_next(T, next); // 对串 T 分析，得到 next 数组
    while (i <= S[0] && j <= T[0]) {
        if (j == 0 || S[i] == T[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    if (j > T[0]) {
        return i - T[0];
    } else {
        return 0;
    }
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
