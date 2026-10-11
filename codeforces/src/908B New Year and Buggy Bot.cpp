//
// Created by Psy.C on 2026/10/11.
//
/**
定义四个方向的位移向量：右、左、下、上（顺序固定）。
d[0]=(0,1) 右、d[1]=(0,-1) 左、d[2]=(1,0) 下、d[3]=(-1,0) 上
sx, sy：起点坐标。
ex, ey：终点坐标。
n, m：棋盘大小。
a[4]：一个排列，表示映射关系。a[k] = 数字 k 实际对应的方向编号（0-3）。
c：棋盘字符。
从起点 (sx,sy) 出发。
对指令串中每个字符 s[i]：s[i]-'0' 得到数字，通过排列 a[] 映射到方向编号，然后按 d[...] 的位移走一步。
途中若越界或落在墙 # 上，立即返回 0（失败）。
若某一刻到达终点 E，返回 1（成功）。
走完全部指令仍未到终点，返回 0。
注意细节：这里是移动后立刻判断是否越界/撞墙/到终点，即每走一步检查一次
读入 n, m 和网格，用 cin >> c[i][j] 逐字符读，同时记录 S 起点、E 终点。
读入指令串 s。
初始化 a = {0,1,2,3}，代表初始映射（数字 i 对应方向 i）。
do { ans += check(); } while(next_permutation(a,a+4));
生成 a 的全部 24 种排列，对每种排列调用 check()，若这种映射能走到终点则 ans 加 1。
输出 ans（累计 4! 种排列中成功的方案数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
using namespace std;

constexpr int N = 64;

struct dir { int dx, dy; } d[4] = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
};

int sx, sy, a[4], n, m, ex, ey;
string s;
char c[N][N];
int check() {
    int x = sx, y = sy;
    rep(i,0,s.size()-1) {
        x += d[a[s[i]-'0']].dx, y += d[a[s[i]-'0']].dy;
        if (!(1 <= x && x <= n && 1 <= y && y <= m)) return 0;
        if (c[x][y] == '#') return 0;
        if (x == ex && y == ey) return 1;
    }
    return 0;
}

int ans;
int main() {
    fast;
    cin >> n >> m;
    rep(i,1,n) rep(j,1,m) {
        cin >> c[i][j];
        if (c[i][j] == 'S') sx = i, sy = j;
        if (c[i][j] == 'E') ex = i, ey = j;
    }
    cin >> s; a[0] = 0, a[1] = 1, a[2] = 2, a[3] = 3;
    do {
        ans += check();
    } while (next_permutation(a, a+4));
    cout << ans << '\n';
    return 0;
}