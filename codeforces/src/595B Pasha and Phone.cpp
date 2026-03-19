//
// Created by Psy.C on 2026/3/20.
//
/**
预计算f[i] = M^i，即f[i] = 10^i（当M=10时）
k：分组大小

f[k] = 10^k，f[k-1] = 10^(k-1)
n1 = (f[k] - 1)/a[i] + 1：
表示区间[0, 10^k-1]中能被a[i]整除的数的个数
f[k] - 1 = 10^k - 1，即k位数的最大值
n2 = (f[k-1] - 1)/a[i] + 1：
表示区间[0, 10^(k-1)-1]中能被a[i]整除的数的个数
n3 = (f[k-1]*(b[i] + 1) - 1)/a[i] - (f[k-1]*b[i] - 1)/a[i]：
计算区间[f[k-1]b[i], f[k-1](b[i]+1)-1]中能被a[i]整除的数的个数

if (b[i] == 0)：当b[i]为0时
ans *= n1 - n2：计算区间[10^(k-1), 10^k-1]中满足条件的数的个数
else：当b[i]不为0时
ans *= n1 - n3：从总数中减去特定区间内的数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5, M = 10, mod = 1e9+7;

ll f[M];
void get() {
    f[0] = 1;
    for (int i = 1; i < M; ++i)
        f[i] = f[i-1]*M;
}

int n, k;
ll a[N], b[N];
int main() {
    fast;
    get();
    cin >> n >> k;
    for (int i = 0; i < n/k; ++i) cin >> a[i];
    for (int i = 0; i < n/k; ++i) cin >> b[i];
    ll ans = 1;
    for (int i = 0; i < n/k; ++i) {
        ll n1 = (f[k] - 1)/a[i] + 1, n2 = (f[k-1] - 1)/a[i] + 1,
        n3 = (f[k-1]*(b[i] + 1) - 1)/a[i] - (f[k-1]*b[i] - 1)/a[i];
        if (b[i] == 0) ans *= n1 - n2;
        else ans *= n1 - n3;
        ans %= mod;
    }
    cout << ans << '\n';
    return 0;
}