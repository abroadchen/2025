//
// Created by Psy.C on 2025/12/10.
//
/*
*f[i]: i! mod mod
g[i]: (i!)^(-1) mod mod
 *用于后续组合数计算
 *计算组合数C(m,n) = m! / (n! * (m-n)!)
 *
*dp[N]: 动态规划数组，dp[i]表示某种状态下的方案数
p[105][2]: 预处理的幂次值
dp[0] = 1: 初始状态
预计算：
p[i][0] = C(n,i)^(m/n)
p[i][1] = C(n,i)^(m/n+1)
 *
*外层循环i从1到n
内层循环j从k到0（倒序，避免重复计算）
x = min(j, n): 当前状态的限制
内内层循环l从1到x：
根据条件选择p[l][0]或p[l][1]
状态转移：dp[j] = (dp[j] + dp[j-l] * t) % mod
 *
*dp[j]: 选择j个某种元素的方案数
l: 本次操作选择的元素个数
t: 选择l个元素的权重或概率
dp[j-l] * t: 从选择(j-l)个元素的状态，通过再选择l个元素到达选择j个元素状态的方案数
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 50005
#define M 10000
using namespace std;

constexpr ll mod = 1000000007;

ll pw(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return res % mod;
}

ll inv(const ll x) { return pw(x, mod - 2); }

ll f[N], g[N];
void init() {
    f[0] = g[0] = 1;
    for (int i = 1; i < M; ++i) {
        f[i] = f[i-1] * i % mod;
        g[i] = g[i-1] * inv(i) % mod;
    }
}

ll c(const ll m, const ll n) {
    return 1ll * f[m] * g[m-n] % mod * g[n] % mod;
}

int main() {
    fast;
    init();
    ll n, m, k; cin >> n >> m >> k;
    ll dp[N], p[105][2]; dp[0] = 1;//达到状态0有1种方案（什么都不做）
    for (ll i = 0; i <= n; ++i) {
        p[i][0] = pw(c(n,i), m/n);
        p[i][1] = pw(c(n,i), m/n+1);
    }
    for (int i = 1; i <= n; ++i) for (int j = static_cast<int>(k); j >= 0; --j) {
        const int x = static_cast<int>(min(1ll * j, n));
        for (int l = 1; l <= x; ++l) {
            ll t;
            if (m % n >= i) t = p[l][1];//前i个选择可以享受到额外的"1份"
            else t = p[l][0];
            dp[j] = (dp[j] + dp[j-l] * t % mod) % mod;
        }
    }
    cout << dp[k];
    return 0;
}