//
// Created by Psy.C on 2026/1/29.
//
/**
* dp[i][3-i-j][k-1]：从 i 到 (3-i-j) 的 k-1 步最优解
mat[i][j]：直接从 i 到 j 的一步代价
dp[3-i-j][j][k-1]：从 (3-i-j) 到 j 的 k-1 步最优解

k-1：前一步的状态
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for (int i=0;i<n;++i)
using namespace std;


int main() {
    fast;
    int mat[3][3];//每步转移有不同的代价（由 mat 矩阵给出）
    for (auto& i : mat) for (int& j : i) cin >> j;
    int n; cin >> n;
    ll dp[3][3][45]={};//从状态 i 到状态 j，经过 k 步的最小代价
    for (int k = 1; k <= n; ++k) {
        rep(i,3) rep(j,3) if (i != j) {//遍历所有不同的 i, j 状态
            ll a = dp[i][3-i-j][k-1] + mat[i][j] + dp[3-i-j][j][k-1],
            b = dp[i][j][k-1] + mat[i][3-i-j] + dp[j][i][k-1] + mat[3-i-j][j] + dp[i][j][k-1];
            dp[i][j][k] = min(a, b);
        }
    }
    cout << dp[0][2][n] << '\n';
    return 0;
}