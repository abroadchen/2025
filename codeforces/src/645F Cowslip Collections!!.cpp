//
// Created by Psy.C on 2026/4/2.
//
/**
获取x的所有因数
只需遍历到√x，然后同时添加i和x/i
避免重复添加（当i = √x时）
x^(-1) ≡ x^(mod-2) (mod mod)
J[i]: i! (阶乘)
计算所有阶乘值
C[i]: C(i,k) 组合数
当i<k时，C(i,k)=0
否则使用公式：C(i,k) = i! / (k! * (i-k)!)
计算g函数，这是莫比乌斯函数的变种
g[i] = i - Σ(g[d])，其中d是i的真因数
这实际上是在计算每个数的"独立贡献"
对x的所有因数进行处理
f[v[i]]++: 统计因数v[i]出现的次数
C[f[v[i]]++]*g[v[i]]: 计算贡献
使用组合数C(f[v[i]], k-1)表示从f[v[i]]个相同因数中选k-1个的方式数

时间复杂度大约是 O((n+q)√M + (n+q)log(n+q))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5, M = 1e6+5, mod = 1e9+7;

vector<int> v;
void get(int x) {
    v.clear();
    int ma = (int)sqrt(x + 0.5);
    for (int i = 1, j; i <= ma; ++i)
        if (x % i == 0) {
            v.push_back(i); j = x/i;
            if (j != i) v.push_back(j);
        }
}

ll ksm(ll x) {
    ll res = 1, y = mod - 2;
    while (y) {
        if (y&1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}

ll ans, J[N<<1], C[N<<1];
int g[M+2];
void init(int n, int k) {
    ans = 0; J[0] = 1;
    for (int i = 1; i <= n; ++i)
        J[i] = J[i-1]*i%mod;
    for (int i = 0; i <= n; ++i) {
        if (i < k) C[i] = 0;
        else C[i] = J[i]*ksm(J[k]*J[i-k]%mod)%mod;
    }
    for (int i = 1, ma; i <= M; ++i) {
        g[i] = i; get(i); ma = v.size();
        for (int j = 0; j < ma; ++j) {
            if (v[j] == i) continue;
            g[i] -= g[v[j]];
        }
    }
}

int f[M];
void query(int x) {
    get(x);
    int ma = v.size();
    for (int i = 0; i < ma; ++i)
        (ans += C[f[v[i]]++]*g[v[i]]%mod)%=mod;
}

void out(int n, int k, int q) {
    init(n + q, k - 1);
    for (int i = 1, a; i <= n; ++i) {
        cin >> a; query(a);
    }
    for (int i = 1, a; i <= q; ++i) {
        cin >> a; query(a);
        cout << ans << '\n';
    }
}

int n, k, q;
int main() {
    fast;
    cin >> n >> k >> q; out(n, k, q);
    return 0;
}