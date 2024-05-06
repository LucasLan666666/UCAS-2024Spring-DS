/**
 * 判断有向图是否存在回路
 */

#include <stdio.h>
#define MAXSIZE 20

int ver_num;
int s[MAXSIZE];
int fst[MAXSIZE];
int lst[MAXSIZE];

int JudgeCircuit(int head, int current) {
    if (fst[current] <= lst[current]) {
        for (int i = fst[current]; i < lst[current] && i < MAXSIZE; i++) {
            if (s[i] == head) {
                return 1;
            } else if (JudgeCircuit(head, s[i])) {
                return 1;
            }
        }
    }
    return 0;
}

int CircuitExist(void) {
    for (int i = 1; i <= ver_num; i++) {
        if (JudgeCircuit(i, i)) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int result;
    int c;

    scanf("%d", &ver_num);
    for (int i = 0; i < MAXSIZE; i++) {
        scanf("%d", &s[i]);
        if ((c = getchar()) == '\n') {
            break;
        }
    }
    for (int i = 0; i <= ver_num; i++) {
        scanf("%d", &fst[i]);
    }
    for (int i = 0; i <= ver_num; i++) {
        scanf("%d", &lst[i]);
    }

    result = CircuitExist();
    printf(result ? "yes\n" : "no\n");
    return 0;
}
