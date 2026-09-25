//
// Created by Psy.C on 2026/9/24.
//
/**
a[N][N]：存网格。
n, m ：行数、列数。
sum：'B' 的总个数。
mnx, mny：最小行、最小列（'B' 出现的边界）。
mxx, mxy：最大行、最大列（'B' 出现的边界）
遍历整个棋盘，每次遇到 'B' 就更新：
最小行 mnx、最大行 mxx（所有 B 覆盖的行范围）。
最小列 mny、最大列 mxy（所有 B 覆盖的列范围）。
sum 统计 B 的总数量。
情况 1：没有 B
棋盘里一个 'B' 都没有 → 按题意输出 1（此时"最小正方形"取默认值如 1×1）。
情况 2：能构成正方形
所有 B 横向跨度为 mxx - mnx + 1，纵向跨度为 mxy - mny + 1。
要用正方形同时覆盖横纵两个跨度，正方形边长必须 ≥ max(两个跨度)，故 mx = max(...) 是能覆盖所有 B 的最小正方形边长
若这个必要边长 mx 超过了棋盘的行数 n 或列数 m → 棋盘内放不下这么大的正方形 → 输出 -1（无解）。
否则输出 mx*mx - sum：正方形共 mx*mx 格，其中已有 sum 格是 'B'，其余 mx*mx - sum 格需要被补涂成 'B'。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 111;
int n, m, sum;
char a[N][N];
int main() {
    fast;
    cin >> n >> m;
    int mnx = INT_MAX, mny = INT_MAX, mxx = 0, mxy = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            if (a[i][j] == 'B') {
                mnx = min(mnx, i); mxx = max(mxx, i);
                mny = min(mny, j); mxy = max(mxy, j);
                sum++;
            }
        }
    }
    int mx = 0;
    if (!sum) { cout << "1"; return 0; }
    mx = max(mxx-mnx+1, mxy-mny+1);
    if (mx > n || mx > m) cout << "-1"; else cout << mx*mx-sum;
    return 0;
}