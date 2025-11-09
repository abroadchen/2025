//
// Created by Psy.C on 2025/9/25.
//
/*
 *定义宏in(x,y)：检查坐标(x,y)是否在棋盘范围内（1-8之间）
*dx[8]和dy[8]：8个方向的坐标偏移量，表示上下左右和四个对角线方向
s[5][5]：存储输入字符串的二维字符数组
b[9][9]：棋盘状态数组，用于标记棋盘格子的状态
 *
*参数：k-棋子索引，n-方向数，f-标志位
对于前n个方向：
计算起始位置：s[k][0]-96将字母转为数字(如'a'=1)，s[k][1]-48将字符数字转为数字
如果f为真且坐标有效且该位置不是其他棋子位置，则沿该方向标记为可攻击区域(值为2)
最后一个位置也标记为可攻击区域
 *
*检查位置(x,y)是否被将军：
如果该位置未被标记为可攻击区域，返回false
检查8个相邻位置，如果有任何一个位置未被攻击，则不是将军状态
如果所有相邻位置都被攻击，则返回true（将军）
 *
*读入4个字符串（应该是棋子位置）
前3个字符串表示己方棋子位置，在棋盘上标记为1
 *
*处理前3个棋子的攻击范围：
第1个棋子：4个方向，可以连续移动
第2个棋子：4个方向，可以连续移动
第3个棋子：8个方向，只能移动一步
 *
*检查第4个位置（对方王的位置）是否被将军
如果是将军则输出"CHECKMATE"，否则输出"OTHER"
 *
 *
 */


#include <cstdio>

#define in(x,y) ((x) && (x)<9 && (y) && (y)<9)
using namespace std;

const int dx[8] = {-1,0,0,1,-1,-1,1,1}, dy[8] = {0,-1,1,0,-1,1,-1,1};

char s[5][5];
int b[9][9];


void solve(int k, int n, int f) {
    for (int i = 0, x, y; i < n; ++i) {
        x = s[k][0] - 96 + dx[i];
        y = s[k][1] - 48 + dy[i];
        for (; f && in(x, y) && b[x][y]^1; x = x + dx[i], y += dy[i])
            b[x][y] = 2;
        if (in(x, y)) b[x][y] = 2;
    }
}

bool check(int x, int y) {
    if (b[x][y] < 2) return 0;
    for (int i,j,k=0; k < 8; ++k) {
        i = x + dx[k];
        j = y + dy[k];
        if (in(i, j) && b[i][j] < 2) return 0;
    }
    return 1;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        scanf("%s", s[i]);
        if (i < 3) b[s[i][0]-96][s[i][1]-48]=1;
    }
    solve(0,4,1);
    solve(1,4,1);
    solve(2,8,0);

    if (check(s[3][0]-96, s[3][1]-48))
        puts("CHECKMATE");
    else
        puts("OTHER");
    return 0;
}