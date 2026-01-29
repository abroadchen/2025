//
// Created by Psy.C on 2026/1/29.
//
/**
* a：1×(2k+3) 的行向量
dp：(2k+3)×(2k+3) 的转移矩阵
 *
*设置行向量 a 的初始值
前 k+1 个位置：2 * 2^(k-i+1)
后 k+1 个位置：值为 1
最后一个位置：值为 1
 *
*构建转移矩阵 dp
根据组合数和幂函数填充矩阵元素
设置特定位置为 1
 *
*计算 a * dp^(n-1)，即经过 n-1 次转移
输出结果 a[1][2k+3]
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 45
#define rep(i,n) for (int i = 1; i <= n; ++i)
#define mod 1000000007
using namespace std;

struct node {
    ll a[N<<1][N<<1]{}, n{}, m{};
    node() = default;
    node(const int n, const int m) : n(n), m(m) {
        rep(i,n) rep(j,m) a[i][j] = 0;
    }
    void dw(const int _n, const int _m) {//创建单位矩阵
        n = _n; m = _m;
        rep(i,n) rep(j,m) a[i][j] = i == j ? 1 : 0;
    }
    //可以修改矩阵元素
    ll& operator()(const int i, const int j) { return a[i][j]; }//方便矩阵访问
};

node operator*(node a, node b) {
    node res(static_cast<int>(a.n), static_cast<int>(b.m));
    rep(i,a.n) rep(j,b.m) rep(k,a.m) (res(i, j) += a(i, k) * b(k, j)) %= mod;
    return res;
}
node operator^(node a, ll x) {//矩阵快速幂
    node res; res.dw(static_cast<int>(a.n), static_cast<int>(a.m));
    for (; x; a = a*a, x >>= 1) if (x & 1) res = res * a;
    return res;
}

ll c[N<<1][N<<1], p2[N<<1];//2^i
void get(const int x) {//组合数 C(i,j)
    c[0][0] = 1; p2[0] = 1;
    rep(i,x) {
        c[i][0] = 1; p2[i] = (p2[i-1]*2)%mod;//2^i = 2^(i-1) * 2
        rep(j,i) c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
    }
}

int main() {
    fast;
    ll n, k; cin >> n >> k; get(static_cast<int>(k));
    node a(1, static_cast<int>(2*k+3)),
    dp(static_cast<int>(2*k+3), static_cast<int>(2*k+3));
    rep(i,k+1) a(1,i) = 2*p2[k-i+1];//a[1][i] = 2 * 2^(k-i+1)
    for (int i = static_cast<int>(k) + 2; i <= 2*k+2; ++i) a(1, i) = 1;//a[1][i] = 1
    a(1, static_cast<int>(2*k+3)) = 1;//a[1][2k+3] = 1
    rep(i,k+1) rep(j,i) dp(i, j) = c[k-j+1][k-i+1];//dp[i][j] = C(k-j+1, k-i+1)
    for (int i = static_cast<int>(k) + 2; i <= 2*k+2; ++i) rep(j,i-(k+1))
        dp(i, j) = p2[i-(k+1)-1-(j-1)]*c[k-j+1][k-(i-(k+1))+1]%mod;
    for (int i = static_cast<int>(k) + 2; i <= 2*k+2; ++i) dp(static_cast<int>(i-(k+1)), i) = 1;
    dp(1, static_cast<int>(2*k+3)) = dp(static_cast<int>(2*k+3), static_cast<int>(2*k+3)) = 1;
    a = a*(dp^(n-1));
    cout << a(1, static_cast<int>(2*k+3)) << '\n';
    return 0;
}