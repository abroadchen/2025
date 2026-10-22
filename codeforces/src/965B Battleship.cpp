//
// Created by Psy.C on 2026/10/21.
//
/**
n：网格边长；k：需要的连续格子长度（如船的长度）。
s[N][N]：字符网格（. 表示空位，# 表示障碍/已占用）。
a[N][N]：记录"能放下船的起始位置覆盖到每个格子的次数"（即每个格子作为船身被覆盖的可行方案数）。
ans：最大覆盖次数；x,y：最优位置。
读入 n、k。
逐行读入网格，s[i]+1 表示从第 i 行下标 1 开始存（1-based，下标 0 留空）
外层 rep(i,n)：遍历每一行 i。
rep(j, n-k+1)：j 取列起点，从 1 到 n-k+1，即每个可能的横向放置起点（保证长度为 k 的段不越界）。
内层判断：对这一行、起点 j、长度 k 的连续段，检查其中是否含 #（障碍）。
若含障碍 → ok=false，该段不可放，跳过。
若整段全为 .（ok==true）：说明在此横向能放下一条长 k 的船，于是把这段覆盖的每个格子 a[i][p+j]++，记录它们被一个可行方案覆盖
对称地处理纵向放置：
外层 rep(i, n-k+1)：行的起点 i，从 1 到 n-k+1。
内层 rep(j,n)：遍历每一列 j。
取列 j 上、行 i 到 i+k-1 的连续 k 个格子，检查是否全为 .（无 #）。
若可行，则对这 k 个格子 a[i+p][j]++，记录纵向方案覆盖它们
遍历所有格子，找到覆盖次数最大的格子：a[i][j] 最大者，记录在 ans 和起点 (x,y)。
这里 x,y 实际是"覆盖次数最大的那个格子"的坐标（即船的头/锚点尽量放在覆盖率最高的格子）。
如果 ans == 0：说明整个网格里无论横放竖放，任何长度为 k 的连续段都包含了 #，即放不下任何船。此时输出 n n（约定表示无可放置位置）。
否则输出最优格子坐标 x y
 */
#include <bits/stdc++.h>
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 105;

int n, k, a[N][N], ans, x, y;
char s[N][N];
int main() {
    scanf("%d %d", &n, &k);
    rep(i,n) scanf("%s", s[i]+1);
    rep(i,n) rep(j,n-k+1) {
        bool ok = true;
        for (int p = 0; p < k; p++)
            if (s[i][p+j] == '#') { ok = false; break; }
        if (ok == true) {
            for (int p = 0; p < k; p++)
                a[i][p+j]++;
        }
    }
    rep(i,n-k+1) rep(j,n) {
        bool ok = true;
        for (int p = 0; p < k; p++)
            if (s[i+p][j] == '#') { ok = false; break; }
        if (ok == true) {
            for (int p = 0; p < k; p++)
                a[i+p][j]++;
        }
    }
    rep(i,n) rep(j,n) if (ans < a[i][j]) {
        ans = a[i][j]; x = i, y = j;
    }
    if (ans == 0) cout << n << ' ' << n << '\n';
    else cout << x << ' ' << y << '\n';
    return 0;
}