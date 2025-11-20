//
// Created by Psy.C on 2025/11/20.
//
/*
*s[N][N]: 存储游戏棋盘状态
dp[N][N][N][N]: 记忆化搜索的状态数组，存储SG值
f: 标志位，用于区分不同的玩家回合
 *
 *计算给定矩形区域[lx,rx]×[ly,ry]的SG值(Sprague-Grundy值)
 *~i等价于i != -1，检查是否已经计算过该状态
*v[]: 标记数组，记录所有可能的下一步状态的SG值
遍历当前区域内的所有位置(i,j)
(i&1) == f: 只考虑特定奇偶性的行，这与游戏规则有关
*'L': 水平分割，将区域分为上下两部分，SG值为两部分SG值的异或
'R': 垂直分割，将区域分为左右两部分，SG值为两部分SG值的异或
'X': 十字分割，将区域分为四个象限，SG值为四部分SG值的异或
*寻找最小的未出现的非负整数(Mex操作)
这就是当前状态的SG值
 *
 *特殊的坐标变换s[i+j]+i-j+m
*先计算f=0时的SG值
再计算f=1时的SG值并与之前的结果异或
如果最终SG值非0，则先手必胜(WIN)，否则后手必胜(LOSE)
 */
#include <cstdio>
#include <cstring>
using namespace std;

const int N = 43;
char s[N][N];
int dp[N][N][N][N];
bool f;

int dfs(int lx, int rx, int ly, int ry) {
    int i = dp[lx][rx][ly][ry];
    if (~i) return i;
    bool v[N*5]={};
    int j;
    for (i = lx; i <= rx; ++i) {
        for (j = ly; j <= ry; ++j) if ((i&1) == f) {
            if (s[i][j]=='L') v[dfs(lx,i-1,ly,ry)^dfs(i+1,rx,ly,ry)] = 1;
            else if (s[i][j]=='R') v[dfs(lx,rx,ly,j-1)^dfs(lx,rx,j+1,ry)] = 1;
            else if (s[i][j]=='X') v[dfs(lx,i-1,ly,j-1)^dfs(lx,i-1,j+1,ry)^
                dfs(i+1,rx,ly,j-1)^dfs(i+1,rx,j+1,ry)] = 1;
        }
    }
    for (i = 0; ; ++i) if (!v[i]) return dp[lx][rx][ly][ry] = i;
}

int main() {
    int n, m, i, j; scanf("%d%d",&n,&m);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) scanf(" %c", s[i+j]+i-j+m);
    }
    memset(dp,-1,sizeof dp); f = 0;
    i = dfs(2,n+m,1,n+m-1);
    memset(dp,-1,sizeof dp); f = 1;
    i ^= dfs(2,n+m,1,n+m-1), puts(i ? "WIN" : "LOSE");
    return 0;
}