//
// Created by Psy.C on 2026/2/7.
//
/**

F[i]: i! (阶乘)
Finv[i]: (i!)^(-1) (阶乘的模逆元)
inv[i]: i^(-1) (i的模逆元)
C(n,m) = n!/(m!(n-m)!)

mul[]: 存储莫比乌斯函数值
对于每个i的倍数j，减去mu(i)

对于每个i，将其添加到所有i的倍数的因数列表中
公式：ans = Σ μ(d) * C(m/d-1, n-1)，其中d是m的因数
时间复杂度：预处理O(N log N)，查询O(d(m))，其中d(m)是m的因数个数
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100007
#define mod 1000000007
using namespace std;

int F[N], Finv[N], inv[N];
int C(const int n, const int m) {
    if (n < 0 || n < m) return 0;
    return 1ll*F[n]*Finv[m]%mod*Finv[n-m]%mod;
}

inline int get(const int n, const int m) {
    if (m < n) return 0;
    return C(m-1, n-1);
}


int main() {
    fast;
    int mul[N];
    inv[1] = F[0] = Finv[0] = 1, mul[1] = 1;
    for (int i = 1; i < N; ++i)
        for (int j = i + i; j < N; j += i)
            mul[j] -= mul[i];
    for (int i = 2; i < N; ++i) inv[i] = 1ll*(mod-mod/i)*inv[mod%i]%mod;
    for (int i = 1; i < N; ++i) F[i] = 1ll*F[i-1]*i%mod;
    for (int i = 1; i < N; ++i) Finv[i] = 1ll*Finv[i-1]*inv[i]%mod;
    vector<int> fac[N];
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; j += i)
            fac[j].push_back(i);
    int q, m, n; cin >> q;
    while (q--) {
        cin >> m >> n;
        int ans = 0;
        for (int i = 0; i < fac[m].size(); ++i)
            ans = (ans + 1ll*mul[fac[m][i]]*get(n, m/fac[m][i])%mod+mod)%mod;
        cout << ans << '\n';
    }
    return 0;
}