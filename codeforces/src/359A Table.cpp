//
// Created by Psy.C on 2026/1/18.
//
/*
i-1<0：上边缘
i+1>=n：下边缘
j-1<0：左边缘
j+1>=m：右边缘
*/
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < n; ++i)
using namespace std;


int main() {
    fast;
    int n, m, g[51][51]; cin >> n >> m;
    rep(i,n) rep(j,m) cin >> g[i][j];
    int res = 4;
    rep(i,n) rep(j,m) if (g[i][j] == 1 && (i-1<0||i+1>=n||j-1<0||j+1>=m)) {//当前单元格是否包含值1且位于网格边界上
        res = 2;
    }
    cout << res << '\n';
    return 0;
}