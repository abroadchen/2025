//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
对每个格子 (i,j) 作为中心点判断：它本身是 'X'，并且四个对角方向也是 'X'，即
X       (i-1,j-1)         (i-1,j+1)
      \       |       /
       \      |      /
        \     |     /
   X ---- X ---- X     ← 中心 (i,j)
        /     |     \
       /      |      \
      /       |       \
    X       (i+1,j-1)      (i+1,j+1)
也就是检查以 (i,j) 为中心的 X 形四条对角线（四个对角点）是否全是 'X'。

因为数组下标从 1 开始，i-1、j-1 最小为 0（对应数组第 0 行/列，初始化的空字符 '\0'），不会读到 c[-1] 导致越界崩溃。这也是上面用 rep(i,n)（1-n）读入、且 N=510 留余量的原因。
若五个位置全为 'X'，ans++
输出满足条件的中心点个数。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
using namespace std;

constexpr int N = 510;
char c[N][N];
int ans;
int main() {
    fast;
    int n; cin >> n;
    rep(i,n) rep(j,n) cin >> c[i][j];
    rep(i,n) rep(j,n)
        if (c[i][j]=='X'&&c[i-1][j-1]=='X'&&c[i-1][j+1]=='X'&&
            c[i+1][j-1]=='X'&&c[i+1][j+1]=='X') ans++;
    cout << ans;
    return 0;
}