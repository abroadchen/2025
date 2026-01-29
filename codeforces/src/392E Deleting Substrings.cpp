//
// Created by Psy.C on 2026/1/29.
//
/**
* f[i][j]：区间 [i,j] 的最大价值
g[i][j]：某种特殊状态下的最大价值（w[i]+1=w[k] 的转移）
h[i][j]：另一种特殊状态下的最大价值（w[i]-1=w[k] 的转移）
最后通过 a 数组进行分段决策
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 404
#define inf 1e8
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;


int main() {
    fast;
    int n, v[N], w[N]; cin >> n;
    rep(i,n) cin >> v[i];//价值数组
    rep(i,n) cin >> w[i];//权重
    int f[N][N], g[N][N], h[N][N];
    rep(i,n) {
        f[i][i] = v[1];
        g[i][i] = h[i][i] = 0;
    }
    //l：区间长度 i：区间起始位置
    rep(l,n) rep(i,n+1-l) {
        const int j = i + l - 1;//区间结束位置
        if (i == j) continue;//单个元素
        f[i][j] = g[i][j] = h[i][j] = -inf;//当前区间的 DP 值
        for (int k = i + 1; k <= j; ++k) {//k：分割点
            //权重连续
            if (w[i]+1==w[k]) g[i][j] = max(g[i][j], f[i+1][k-1]+g[k][j]);
            //权重递减
            if (w[i]-1==w[k]) h[i][j] = max(h[i][j], f[i+1][k-1]+h[k][j]);
            f[i][j] = max(f[i][j], f[i][k-1]+f[k][j]);
        }
        for (int k = i; k <= j; ++k) {
            if (const ll len = 2ll*w[k] - w[i] - w[j] + 1; 0 <= len && len <= n)
                f[i][j] = max(f[i][j], g[i][k]+h[k][j]+v[len]);
        }
    }
    int a[N]; a[0] = 0;
    rep(j,n) {
        a[j] = a[j-1];//继承前一个状态
        rep(i,j) a[j] = max(a[j], a[i-1]+f[i][j]);
    }
    cout << a[n] << '\n';
    return 0;
}