//
// Created by Psy.C on 2026/2/14.
//
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2001
#define rep(i,n) for (i = 0; i < n; ++i)
using namespace std;

int n, a[N][N], ans;

int main() {
    fast;
    cin >> n; int i, j;
    rep(i,n) {
        rep(j,n) cin >> a[i][j];
        if (a[i][j]) ans = 1;//矩阵中有非零元素
    }
    rep(i,n) for (j = i+1; j < n; ++j)//遍历上三角矩阵（不包括对角线）
        //矩阵是否对称 非对角线元素是否为0
        if (a[i][j] != a[j][i] || (a[i][j] == 0 && j != i))
            ans = 1;
    rep(i,n) {
        int r = 0;
        //不是对角线元素自己和自己比较
        rep(j,n) if (a[i][j] < a[i][r] && i != j) r = j;//最小值位置
        rep(j,n) if (abs(a[i][j] - a[j][r]) != a[i][r]) ans = 1;
    }
    cout << (ans ? "NO" : "YES") << '\n';
    return 0;
}