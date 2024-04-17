/**
 * 假设以二维数组g(1..m, 1..n)表示一个图像区域, g[i, j]表示该区域中点(i, j)所具颜色，其值为从0到k的整数。
 * 编写算法置换点(i_, j_)所在区域的颜色。约定和(i_, j_)同色的上、下、左、右的邻接点为同色区域的点。
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_HEIGHT 20
#define MAX_WIDTH 20

typedef struct {
    int color;
    int mark;
} status;

typedef struct {
    status tab[MAX_HEIGHT][MAX_WIDTH];
    int height, width;
} Image, *p_Image;

const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

p_Image ialloc(void) {
    return (p_Image)malloc(sizeof(p_Image));
}

void coloring(p_Image image, int row, int col) {
    int old_color;
    if (row >= 0 && row < image->height && col >= 0 && col < image->width && image->tab[row][col].mark == 0) {
        old_color = image->tab[row][col].color;
        image->tab[row][col].color = 2;
        image->tab[row][col].mark = 1;
        for (int i = 0; i < 4; i++) {
            if (   row + dir[i][0] >= 0 && row + dir[i][0] < image->height
                && col + dir[i][1] >= 0 && col + dir[i][1] < image->width
                && old_color == image->tab[row + dir[i][0]][col + dir[i][1]].color
                )
            {
                coloring(image, row + dir[i][0], col + dir[i][1]);
            }
        }
    }
}

void print(p_Image image) {
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            printf("%d", image->tab[i][j].color);
        }
        putchar('\n');
    }
}

int main() {
    int row, col, dir;
    p_Image image = ialloc();
    scanf("%d %d %d %d %d", &image->height, &image->width, &row, &col, &dir);
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            scanf("%d", &image->tab[i][j].color);
            image->tab[i][j].mark = 0;
        }
    }
    coloring(image, row, col);
    print(image);
    free(image);
    return 0;
}
