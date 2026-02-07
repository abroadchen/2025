//
// Created by Psy.C on 2026/2/7.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

constexpr int N = 2005, M = 10005;

int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    char c[N][N];
    int ans[M]{}, i, j;
    rep(i,n) rep(j,m) cin >> c[i][j];//读取整个网格
    rep(i,n) rep(j,m) {//分类计数
        if (c[i][j] == 'R') ans[i+j-1]++;//映射到和坐标 (i+j-1) 相同的对角线上
        if (c[i][j] == 'L' && j-i+1 >= 1) ans[j-i+1]++;//映射到差值 (j-i+1) 相同的反对角线上
        if (c[i][j] == 'U' && i&1) ans[j]++;//映射到第 j 列
    }
    rep(i,m) cout << ans[i] << ' ';
    return 0;
}