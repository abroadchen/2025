//
// Created by Psy.C on 2025/11/15.
//
/*
*检查当前位置的四个相邻方向：
k=0：上方(i-1,j)
k=1：左方(i,j-1)
k=2：右方(i,j+1)
k=3：下方(i+1,j)
如果任意相邻位置是'P'字符，通过按位或运算将f设为true
f |= (condition)等价于f = f || (condition)
 *
*将标志f的值加到计数器s上
如果f为true(1)，说明这个'W'有相邻的'P'，计数器加1
如果f为false(0)，说明这个'W'没有相邻的'P'，计数器不变
 *
*网格索引从1开始，避免了边界检查的复杂性
使用方向数组简化了相邻位置的计算
按位或运算|=高效地实现了"存在性"检查
 *
 *
 */
#include <cstdio>
#define rep(i,n) for(i=1;i<=(n);++i)
using namespace std;

const int N = 15,
dx[] = {-1, 0, 0, 1},
dy[] = {0, -1, 1, 0};
char a[N][N];

int main() {
    int n, m, i, j, k, s(0); bool f;
    scanf("%d%d", &n, &m);
    rep(i,n) scanf("%s", a[i] + 1);
    rep(i,n) rep(j,m) if (a[i][j] == 'W') {
        f = 0;
        for (k = 0; k < 4; ++k) f |= (a[i+dx[k]][j+dy[k]] == 'P');
        s += f;
    }
    printf("%d\n", s);
    return 0;
}