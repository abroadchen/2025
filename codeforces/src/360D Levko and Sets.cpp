//
// Created by Psy.C on 2026/1/19.
//
/**
* 计算 (a^n) % mod
递归实现：a^n = (a^(n/2))^2 当n为偶数
当n为奇数时：a^n = (a^(n/2))^2 * a
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10010
#define M 100010
#define rep(i,n) for (int i = 1; i <= n; ++i)
using namespace std;

int dfs(const int a, const int n, const int mod=998244353) {
    if (!n) return 1;
    int t = dfs(a, n/2, mod); t = static_cast<int>(1ll * t * t % mod);
    if (n&1) t = static_cast<int>(1ll * t * a % mod);
    return t;
}

int gcd(const int a, const int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    fast;
    int n, m, p, a[N], b[M]; cin >> n >> m >> p; int g = p - 1;//p（质数）
    rep(i,n) cin >> a[i];
    rep(i,m) cin >> b[i], g = gcd(g, b[i]);
    vector<int> d;
    rep(i,p-1) {//找p-1的所有因数
        if (i*i > p-1) break;
        if (i*i == p-1) { if ((p-1)%i == 0) d.push_back(i); }
        else { if ((p-1)%i == 0) d.push_back(i), d.push_back((p-1)/i); }
    }
    ranges::sort(d);//排序因数
    int s[N];
    rep(i,n) {
        a[i] = dfs(a[i], g, p);
        int c = 0;
        for (const auto u : d) {//对每个因数u，找到最小的使得 a[i]^u ≡ 1 (mod p) 的u，即阶(order)
            if (dfs(a[i], u, p) == 1) { c = u; break; }
        }
        if (a[i] == 1) c = 1;//已经是1
        s[i] = (p-1)/c;
    }
    sort(s + 1, s + n + 1);
    const int tot = static_cast<int>(unique(s + 1, s + n + 1) - s - 1),
    sz = static_cast<int>(d.size());
    int tag[N], ans = 0;
    for (int i = 0; i <= sz-1; ++i) rep(j,tot) if (d[i] % s[j] == 0) {//s[j]是d[i]的因数
        tag[i] = 1; break;
    }
    for (int i = sz-1, f[N]; i >= 0; --i) {
        if (!tag[i]) continue;
        f[i] = (p-1)/d[i];
        for (int j = i + 1; j <= sz-1; ++j) if (d[j] % d[i] == 0) {
            f[i] -= f[j];//减去所有d[j]是d[i]倍数的f[j]值
        }
        ans += f[i];
    }
    cout << ans << '\n';
    return 0;
}