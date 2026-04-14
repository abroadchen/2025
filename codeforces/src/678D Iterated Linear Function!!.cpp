//
// Created by Psy.C on 2026/4/14.
//
/**
重载乘法运算符
实现2×2矩阵乘法
模mod运算
重载幂运算符
快速幂算法计算矩阵的x次方
cur: 单位矩阵，结果矩阵
res: 当前矩阵
模运算函数，确保结果非负

a, b: 递推关系的系数
x: 初始值
n: 要计算的项数
转移矩阵A：
[a  0]
[1  1]
初始状态F：
[x  b]

这个算法解决的是形如 f(i) = a*f(i-1) + b 的递推关系：
通过矩阵乘法 [f(n), 1] = [f(0), 1] * A^n
其中 A = [[a,0],[1,1]]
A^n 通过快速幂计算

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;
constexpr int mod = 1e9+7;
struct node {
    int a[15][15]{};
    node() { memset(a, 0, sizeof(a)); }
    node operator*(const node& o) const {
        node cur;
        int r;
        rep(i,2) rep(k,2) {
            r = a[i][k];
            rep(j,2) cur.a[i][j] += o.a[k][j]*r, cur.a[i][j] %= mod;
        }
        return cur;
    }
    node operator^(int x) const {
        node cur, res;
        rep(i,2) cur.a[i][i] = 1;
        rep(i,2) rep(j,2) res.a[i][j] = a[i][j]%mod;
        while (x) {
            if (x&1) cur = cur*res;
            res = res*res;
            x >>= 1;
        }
        return cur;
    }
} A, F;

int mode(int x, int m) { return (x + m) % m; }
int a, x, b, n;
void init() {
    A.a[1][1] = a, A.a[1][2] = 0;
    A.a[2][1] = 1, A.a[2][2] = 1;
    F.a[1][1] = x, F.a[1][2] = b;
    F = F*(A^n);
}

signed main() {
    fast;
    cin >> a >> b >> n >> x; init();
    cout << mode(F.a[1][1], mod);
    return 0;
}