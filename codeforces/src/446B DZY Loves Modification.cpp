//
// Created by Psy.C on 2026/2/9.
//
/**
N, M: 数组大小常量
n, m, k, p: 矩阵维度、操作次数、惩罚值
a[N][N]: 输入矩阵
mxc[M], mxr[M]: 列和行的前缀最大值数组
r, c: 行和列的优先队列

i: 表示用i次操作处理列
k-i: 表示用(k-i)次操作处理行
mxc[i] + mxr[k-i]: 列操作收益 + 行操作收益
i*(k-i)*p: 交叉重复减去的惩罚值（因为行列操作都会影响交叉点）

时间复杂度: O(k log(max(n,m)))
 */
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for (i = 1; i <= n; ++i)
using namespace std;

constexpr int N = 2005, M = 1000005;
ll n, m, k, p, a[N][N], i, j, mxc[M], mxr[M];
priority_queue<ll> r, c;

int main() {
    fast;
    cin >> n >> m >> k >> p;
    rep(i,n) {
        ll sumr = 0;
        rep(j,m) { cin >> a[i][j]; sumr += a[i][j]; }//行和
        r.push(sumr);
    }
    rep(i,m) {
        ll sumc = 0;
        rep(j,n) sumc += a[j][i];//列和
        c.push(sumc);
    }
    rep(i,k) {
        const ll q = r.top(); r.pop();//行和的最大值
        mxr[i] = mxr[i-1] + q;//累积最大行和
        r.push(q - m * p);//每列元素减p，总共减m*p
    }
    rep(i,k) {
        const ll q = c.top(); c.pop();
        mxc[i] = mxc[i-1] + q;
        c.push(q - n * p);
    }
    ll res = -1e15;
    for (i = 0; i <= k; ++i) {
        ll t = mxc[i] + mxr[k-i] - i*(k-i)*p;
        res = max(res, t);
    }
    cout << res << '\n';
    return 0;
}