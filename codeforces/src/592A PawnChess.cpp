//
// Created by Psy.C on 2026/3/19.
//
/**
N = 109：定义数组最大行数（实际只需要M大小，这里是为了安全）
M = 9：定义棋盘边长（8×8棋盘，索引从1到8，所以用9作为边界）
m1：记录白棋(W)能移动的最短距离
m2：记录黑棋(B)能移动的最短距离
外层循环：j从1到7，遍历每一列
内层循环：i从M-1(8)到1，从下往上遍历每行
if (a[i][j] == 'W') break;：如果遇到白棋就停止向上搜索（白棋不能越过其他棋子）
if (a[i][j] == 'B') m1 = min(m1, M - i);：如果遇到黑棋，计算它到达顶部的距离(M-i)，更新最小值
逻辑：模拟白棋从底部(第8行)向上移动，看哪个黑棋离顶部最近

外层循环：j从1到7，遍历每一列
内层循环：i从1到7，从上往下遍历每行
if (a[i][j] == 'B') break;：如果遇到黑棋就停止向下搜索（黑棋不能越过其他棋子）
if (a[i][j] == 'W') m2 = min(m2, i - 1);：如果遇到白棋，计算它到达底部的距离(i-1)，更新最小值
逻辑：模拟黑棋从顶部(第1行)向下移动，看哪个白棋离底部最近

如果m2 < m1（黑棋能更快到达底部），输出'A'
否则输出'B'
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 109, M = 9, inf = 1e9;
char a[N][N];
int main() {
    fast;
    for (int i = 1; i < M; ++i)
        for (int j = 1; j < M; ++j) cin >> a[i][j];
    int m1 = inf, m2 = inf;
    for (int j = 1; j < M; ++j)
        for (int i = M-1; i >= 1; --i) {
            if (a[i][j] == 'W') break;
            if (a[i][j] == 'B') m1 = min(m1, M - i);
        }
    for (int j = 1; j < M; ++j)
        for (int i = 1; i < M; ++i) {
            if (a[i][j] == 'B') break;
            if (a[i][j] == 'W') m2 = min(m2, i - 1);
        }
    if (m2 < m1) cout << 'A'; else cout << 'B';
    return 0;
}