//
// Created by Psy.C on 2026/9/19.
//
/**
输入 n（矩阵大小 n×n）和 k（要放置的 1 的个数）。
vis[n][n] 用来标记矩阵
如果要求放的总数 k 超过了整个矩阵格子数 n²，显然不可能 → 输出 -1
遍历矩阵，对每个未访问格子 (i,j)：

主对角线 i==j：如果可以（k>0），放 1 个主对角元素，k 减 1。
对称的非对角线：如果可以放 2 个（k>=2），把 (i,j) 和其对称格 (j,i) 一起置 1，k 减 2。
关键点：因为会同时填 (i,j) 和 (j,i) 两个对称格，所以需要 k 为偶数（非对角部分）。这也是为什么单独处理主对角线——主对角每个占 1 个，非对角每个"配对"占 2 个。
最终如果 k 没被减完（if (k) flag=false）说明无法恰好构造
可行 → 输出 n×n 的 0/1 矩阵。
不可行 → 输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e3;
int vis[N][N];
int main() {
    fast;
    int n, k; cin >> n >> k;
    memset(vis, 0, sizeof(vis));
    bool flag = true;
    if (n*n < k) flag = false;
    else {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (vis[i][j]) continue;
                if (i == j && k != 0) {
                    vis[i][j] = 1; k--;
                } else if (k >= 2) {
                    vis[i][j] = vis[j][i] = 1;
                    k -= 2;
                }
            }
        if (k) flag = false;
    }
    if (flag) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == 0) cout << vis[i][j];
                else cout << ' ' << vis[i][j];
            }
            cout << '\n';
        }
    } else cout << "-1\n";
    return 0;
}