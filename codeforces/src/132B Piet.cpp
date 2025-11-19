//
// Created by Psy.C on 2025/11/19.
//
/*
 *n(行数)、t(步数)、m(列数)
 *右(0,1)、下(1,0)、左(0,-1)、上(-1,0)
 *c用于记录状态
 *a存储网格数据
 *
*当前位置(x,y) = (0,0)
方向索引i = 0（初始向右）
转向标志j = 0
x1,y1：侧向移动方向
x2,y2：前进方向
 *
 *
 *沿着当前方向前进，直到遇到不同字符或边界
 *沿着侧向方向移动，寻找同一字符区域的边缘
*检查是否到达过相同状态：
如果是，则计算循环周期d
快进到接近终点的位置
如果否，则记录当前状态和步数
 *
*检查前方是否可走：
如果不可走（越界或遇到'0'）：
改变转向状态j
如果需要转方向，则更新方向索引i
重新计算前进和侧向方向
如果可走，则向前移动一步
 *输出最终位置的字符
 *
 */
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 55;
int n, t, m, dx[] = {
    0, 1, 0, -1
}, dy[] = {
    1, 0, -1, 0
}, c[N][N][4][2] = {};
char a[N][N];

int ok(int x, int y) { return x >= 0 && y >= 0 && x < n && y < m; }

int main() {
    scanf("%d%d", &n, &t);
    for (int i = 0; i < n; ++i) scanf("%s", a[i]);
    m = strlen(a[0]);
    int x(0), y(0), i(0), j(0),
    x1 = -dy[i] * (j ? -1 : 1), y1 = dx[i] * (j ? -1 : 1),
    x2 = dx[i], y2 = dy[i];
    for (int step = 1; step <= t; ++step) {
        while (ok(x+x2,y+y2) && a[x+x2][y+y2]==a[x][y]) x+=x2, y+=y2;
        while (ok(x+x1,y+y1) && a[x+x1][y+y1]==a[x][y]) x+=x1, y+=y1;
        if (c[x][y][i][j]) {
            int d = step - c[x][y][i][j];
            while (step + d <= t) step += d;
        } else c[x][y][i][j] = step;
        if (!ok(x+x2,y+y2) || a[x+x2][y+y2] == '0') {
            if (j == 0) j = 1;
            else if (j == 1) i = (i + 1) % 4, j = 0;
            x1 = -dy[i] * (j ? -1 : 1), y1 = dx[i] * (j ? -1 : 1);
            x2 = dx[i], y2 = dy[i];
        } else x += x2, y += y2;
    }
    printf("%c\n", a[x][y]);
    return 0;
}