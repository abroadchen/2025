//
// Created by Psy.C on 2026/9/13.
//
/**
inv(b)：递归求 b 模 mod 的乘法逆元，用的是费马小定理/欧拉递归式 inv(b) = -(mod/b) * inv(mod% b) % mod。因 mod 是质数，任意 b<mod 且有逆；b==1 时返回 1
预处理 阶乘数组 f[i] = i! mod mod
组合数 C(n,m) = n! / (m!(n-m)!)，用逆元做模除法
C(l+r-1, l) 的 -1 是把当前这个左括号固定下来，再对剩下 l-1 个左括号和 r 个右括号做排列组合
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5, mod = 1e9+7;
ll inv(ll b) { return b == 1 ? 1 : (mod-mod/b)*inv(mod%b)%mod; }

ll f[N] = {1};
ll C(ll n, ll m) {
    if (n < m) return 0;
    return f[n]*inv(f[m])%mod*inv(f[n-m])%mod;
}

char s[N];
int main() {
    fast;
    for (int i = 1; i <= N-5; ++i) f[i] = i*f[i-1]%mod;
    while (~scanf("%s", s+1)) {
        int len = strlen(s+1), cnt = 0;
        for (int i = 1; i <= len; ++i)
            if (s[i] == ')') cnt++;
        ll ans = 0, l = 0, r = cnt;
        for (int i = 1; i <= len; ++i) {
            if (s[i] == '(') {
                l++;//已见左括号数 +1
                ans = (ans + C(l+r-1, l))%mod;//累加组合数
            } else r--;//见右括号，剩余右括号数 -1
        }
        cout << ans << '\n';
    }
    return 0;
}