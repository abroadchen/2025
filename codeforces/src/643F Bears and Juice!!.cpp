//
// Created by Psy.C on 2026/4/1.
//
/**
求解 ax + by = gcd(a,b) 的解
递归实现：先求解 bx' + (a%b)y' = gcd(b,a%b)
然后根据 x = y', y = x' - (a/b)*y' 得到原方程的解
计算w在模mod下的逆元
使用扩展欧几里得算法求解 wx ≡ 1 (mod mod)
(x+mod)%mod 确保结果为正数

计算组合数 C(n,m) = n! / (m! * (n-m)!)
__builtin_ctz(i): 计算i末尾连续0的个数（即i中因子2的个数）
cnt: 统计总的因子2的个数
res: 计算去除因子2后的结果
第一个循环：计算 n*(n-1)...(n-m+1)
第二个循环：除以 m!
cnt -= len: 减去分母中因子2的个数
inv(i>>len): 计算去除因子2后的i的模逆元
最后乘以2^cnt，得到完整的组合数

限制p不超过n-1
预计算C(n,0), C(n,1), ..., C(n,p)
外层循环i从1到q
res: 计算多项式求值：∑(j=0 to p) w^j * val[j]
w: i的幂次（初始为i^0=1，每次乘以i）
ans ^= i*res: 异或累积结果

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int unsigned int
#define ll long long
using namespace std;
constexpr ll mod = 1ll<<32;

void egcd(ll a, ll b, ll& x, ll& y) {
    if (!b) { x = 1, y = 0; return; }
    egcd(b, a % b, y, x);
    y -= a / b * x;
}
int inv(ll w) {
    ll x, y;
    egcd(w, mod, x, y);
    return (int)((x+mod)%mod);
}

int n;
int get(int m) {
    int cnt = 0, res = 1;
    for (int i = n; i >= n-m+1; --i) {
        int len = __builtin_ctz(i); cnt += len;
        res *= i>>len;
    }
    for (int i = 1; i <= m; ++i) {
        int len = __builtin_ctz(i); cnt -= len;
        res *= inv(i>>len);
    }
    return res*(1u<<cnt);
}

int p, q, val[201], ans;
signed main() {
    fast;
    cin >> n >> p >> q; p = min(p, n-1);
    for (int i = 0; i <= p; ++i) val[i] = get(i);
    for (int i = 1; i <= q; ++i) {
        int res = 0, w = 1;
        for (int j = 0; j <= p; ++j) {
            res += w*val[j];
            w *= i;
        }
        ans ^= i*res;
    }
    cout << ans << '\n';
    return 0;
}