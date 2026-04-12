//
// Created by Psy.C on 2026/4/12.
//
/**
使用费马小定理计算模逆：a^(-1) ≡ a^(p-2) (mod p)
反向计算逆阶乘
v[N]: 用于对不同字符串长度的记忆化向量数组
mp: 映射，存储每个字符串长度的最大查询长度
mx: 跟踪最大值的变量

C(i-1, n-1)*25^(i-n): 在i个位置放置n个特定字符的方法数
v[n][i-1]*26: 前一状态乘以26个可能的字符

C(i-1, n-1) - 组合数
C(i-1, n-1) = 从 (i-1) 个位置中选择 (n-1) 个位置的方案数
这是在 i 个位置中固定 n 个字符位置的组合方式
25^(i-n) - 幂运算
25 表示除了原字符串中的字符外，其他25个字母
(i-n) 表示剩余的位置数量
25^(i-n) 表示这些位置可以填入任意其他字符的方式数

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+5, mod = 1e9+7;
int fac[N], ifc[N];
ll C(ll m, ll n) {
    return m < n ? 0 : 1ll*fac[m]*ifc[n]%mod*ifc[m-n]%mod;
}
int ksm(ll a, int k) {
    if (k < 0) return 0;
    ll res = 1;
    while (k) {
        if (k&1) res = 1ll*res*a%mod;
        a = 1ll*a*a%mod;
        k >>= 1;
    }
    return res;
}

void init() {
    fac[0] = ifc[0] = 1;
    for (int i = 1; i < N; ++i)
        fac[i] = 1ll*fac[i-1]*i%mod;
    ifc[N-1] = ksm(fac[N-1], mod-2);
    for (int i = N-2; i >= 0; --i)
        ifc[i] = 1ll*ifc[i+1]*(i+1)%mod;
}

vector<int> v[N];
map<int, int> mp;
int mx;
int get(int n, int len) {
    if (v[n].size()) return v[n][len];
    mx = mp[n]; v[n].push_back(0);
    for (int i = 1; i <= mx; ++i) {
        ll x = 1ll*C(i-1, n-1)*ksm(25, i-n)%mod +
               v[n][i-1]*26ll%mod; x %= mod;
        v[n].push_back(x);
    }
    return v[n][len];
}

int q;
string s;
vector<ii> vq;
int main() {
    fast;
    init(); cin >> q >> s;
    int len = s.length(), op, tl;
    while (q--) {
        cin >> op;
        if (op == 1) {
            cin >> s; len = s.length();
        } else {
            cin >> tl; vq.push_back({len, tl});
            mx = max(mx, tl);
            if (!mp.contains(len)) mp[len] = tl;
            else mp[len] = max(mp[len], tl);
        }
    }
    for (auto [u, tv] : vq)
        cout << get(u, tv) << '\n';
    return 0;
}