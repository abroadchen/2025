//
// Created by Psy.C on 2025/12/9.
//
/*
*r/x 表示[1,r]中x的倍数个数
(l-1)/x 表示[1,l-1]中x的倍数个数
相减得到[l,r]中x的倍数个数
如果大于等于k返回true
 *
*二维数组s[N][N]存储矩阵元素
默认构造函数使用memset将矩阵初始化为0
声明全局变量e作为单位矩阵
 *
*枚举因子优化：只需检查到√r：
如果i满足条件，更新ans
如果r/i满足条件，也更新ans
这样可以在O(√r)时间内找到所有因子中的最大满足条件者
 *
 *构造斐波那契矩阵
*[1 1]
 [1 0]
*计算该矩阵的(ans-2)次幂
输出结果矩阵第一行元素之和模p
 *
*因子查找：O(√r)
矩阵快速幂：O(log ans)
总体：O(√r + log ans)
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 55
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

int n = 35;
ll p, l, r, k;

bool ok(const ll x) { return r / x - (l - 1) / x >= k; }

struct node {
    ll s[N][N]{};
    node() { memset(s, 0, sizeof(s)); }
} e;

node mul(const node& a, const node& b) {
    node t;
    rep(i,n) rep(j,n) rep(x,n) {
        t.s[i][j] = (t.s[i][j] + a.s[i][x] * b.s[x][j] % p) % p;
    }
    return t;
}

node pw(node a, ll b) {
    auto ans = e;
    for (; b; b >>= 1) {
        if (b & 1) ans = mul(ans, a);
        a = mul(a, a);
    }
    return ans;
}


int main() {
    fast;
    rep(i,n) e.s[i][i] = 1;
    cin >> p >> l >> r >> k;
    ll ans = 0;
    for (ll i = 1; i * i <= r; ++i) {
        if (ok(i)) ans = max(ans, i);
        if (ok(r / i)) ans = max(ans, r / i);
    }
    if (ans == 1) { ans = 1 % p; cout << ans; return 0; }
    if (ans == 2) { ans = 1 % p; cout << ans; return 0; }
    node a;
    a.s[0][0] = 1; a.s[0][1] = 1; a.s[1][0] = 1; a.s[1][1] = 0;
    const node b = pw(a, ans - 2);
    cout << (b.s[0][0] + b.s[0][1]) % p;
    return 0;
}