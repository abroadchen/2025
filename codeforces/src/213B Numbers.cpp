//
// Created by Psy.C on 2025/12/6.
//
/*
*fac[]：阶乘数组
inv[]：逆元数组
*计算 0! 到 N!
使用费马小定理计算 N! 的逆元
从后往前递推计算其他逆元
 *计算组合数 C(n,m) = n! / (m! * (n-m)!) mod p
 *a（表示数字0-9各自的最少使用次数）
*f[i] 表示使用数字9构成长度为i的方案数
当长度≥a[9]时，方案数为1（只使用数字9）
*从数字8到数字1进行DP：
f[j]：使用数字i到数字9构成长度为j的方案数
枚举使用数字i的次数k（从a[i]到j）
f[j-k] * C(j,k)：从j个位置中选k个放数字i，其余用更大数字填充
 *由于第一位不能是0，所以使用 C(j-1, k) 而不是 C(j, k)
 *O(n² × 10) = O(n²)
 *
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100
using namespace std;

constexpr int p = 1e9+7;

int fac[N+1], inv[N+1];

int pw(ll a, ll b) {//计算逆元
    int res = 1;
    for (; b; a = a * a % p, b >>= 1) {
        if (b & 1) res = static_cast<int>(res * a % p);
    }
    return res;
}

auto init = [] {
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= N; ++i)
        fac[i] = static_cast<int>(1ll * fac[i-1] * i % p);
    inv[N] = pw(fac[N], p - 2);
    for (int i = N - 1; i; --i)
        inv[i] = static_cast<int>((i + 1ll) * inv[i + 1] % p);
    return 0;
}();


int C(const int n, const int m) {
    if (n < m) return 0;
    return static_cast<int>(1ll * fac[n] * inv[m] % p * inv[n - m] % p);
}


int main() {
    fast;
    int n; cin >> n;
    array<int, 10> a{};
    for (int i = 0; i < 10; ++i) cin >> a[i];
    vector<int> f(n + 1);
    for (int i = a[9]; i <= n; ++i) f[i] = 1;
    for (int i = 8; i; --i) {
        for (int j = n; ~j; --j) {
            int res = 0;
            for (int k = a[i]; k <= j; ++k) {
                res += static_cast<int>(1ll * f[j - k] * C(j, k) % p);
                if (res >= p) res -= p;
            }
            f[j] = res;
        }
    }
    int res = 0;
    for (int j = n; ~j; --j) {
        for (int k = a[0]; k <= j; ++k) {
            res += static_cast<int>(1ll * f[j - k] * C(j - 1, k) % p);
            if (res >= p) res -= p;
        }
    }
    cout << res;
    return 0;
}