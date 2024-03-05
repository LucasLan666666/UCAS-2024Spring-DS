/**
 * 假设有A,B,C,D,E 五个高等院校进行田径对抗赛，各院校的单项成绩均已存入计算机，并构成一张表，表中每一行的形式为
 * 项目名称 - 性别 - 校名 - 成绩
 * 编写算法，处理上述表格，以统计个院校的男、女总分和团体总分，并输出
 */

#include <stdio.h>
#include <string.h>
#define    NUM  5 // 5 个学校
#define MAXLEN 15 // 读取一行最大长度为 15

typedef struct Score {
    char name;
    int M;
    int F;
} Score;

int main() {
    Score school[NUM]; // 五个学校记录男女生成绩的结构体数组
    char event, gender, name;
    int score;

    // 初始化学校名，同时设置分数为 0
    for (int i = 0; i < NUM; i++) {
        memset(&school[i], 0, sizeof(school[i]));
        school[i].name = 'A' + i;
    }
    // 算分
    while (scanf("%c %c %c %d\n", &event, &gender, &name, &score) == 4) {
        for (int i = 0; i < NUM; i++) {
            if (school[i].name == name) {
                if (gender == 'M') {
                    school[i].M += score;
                } else {
                    school[i].F += score;
                }
            }
        }
    }
    // 打印结果
    for (int i = 0; i < NUM; i++) {
        if (school[i].M != 0) {
            printf("%c M %d\n", school[i].name, school[i].M);
        }
        if (school[i].F != 0) {
            printf("%c F %d\n", school[i].name, school[i].F);
        }
        if (school[i].M + school[i].F != 0) {
            printf("%c %d\n", school[i].name, school[i].M + school[i].F);
        }
    }

    return 0;
}
