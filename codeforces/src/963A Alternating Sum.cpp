//
// Created by Psy.C on 2026/10/21.
//
/**
读入 n, a, b, k 和一个长度为 k 的字符串 s（由 +/- 组成）。
sum 用于累计一个周期的部分和
对 i 从 0 到 k-1：
计算 t = a^(n-i) * b^i mod mod。
若 s[i]=='+'：sum += t。
否则（'-'）：sum = sum - t + mod（加 mod 后取模，避免负数）。
即 sum 是"首项按位 a^(n-i)·b^i 带正负号求和"的前 k 项值。
可确证：sum = Σ_{i=0}^{k-1} (±) a^(n-i)·b^i mod mod，符号由 s[i] 决定
计算 d = b^k / a^k = (b/a)^k mod mod。
ksm(a,k) 是 a^k，再用 ^(mod-2) 求其模逆（费马小定理，因 mod 为质数），即除以 a^k。
可确证：d = b^k · (a^k)^(mod-2) mod mod = (b/a)^k，即相邻周期项的公比（周期长 k，每过 k 项 a、b 指数各减/加 k，故公比为 (b/a)^k）
题目实际要求的是 Σ_{i=0}^{n} (±) a^(n-i)·b^i 共 n+1 项，其中符号按长度 k 的字符串 s 循环。
由于每 k 项组成一个完整周期，且相邻周期公比为 d，总共有 (n+1)/k 个周期（要求 n+1 能被 k 整除，即去掉首尾无完整周期的情况）。
若 d == 1：等比数列各项相同，总和 = sum × 周期数 = sum × (n+1)/k，即 sum*(n+1)%mod*ksm(k,mod-2)%mod。其中 ksm(k,mod-2) 是 k 的模逆，即除以 k。
否则：等比数列前 m=(n+1)/k 项和 = sum × (d^m - 1)/(d-1)，即 sum * (d^((n+1)/k)-1) * inv(d-1)。
可确证：按 d 是否等于 1，用等比数列求和公式输出；d==1 时用周期数乘法，否则用 (d^m-1)/(d-1) 公式，两处都正确使用模逆（÷k 或 ÷(d-1)）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+10, mod = 1e9+9;

int ksm(int a, int b) {
    a %= mod;
    int res = 1;
    while (b) {
        if (b&1) res=1ll*res*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return res;
}

int n, a, b, k, sum;
char s[N];
int main() {
    fast;
    cin>>n>>a>>b>>k>>s;
    for (int i = 0; i < k; i++) {
        if (s[i] == '+') sum = 1ll*(sum+1ll*ksm(a,n-i)*ksm(b,i)%mod)%mod;
        else sum = 1ll*(sum+mod-1ll*ksm(a,n-i)*ksm(b,i)%mod)%mod;
    }
    int d = 1ll*ksm(b,k)*ksm(ksm(a,k), mod-2)%mod;
    if (d == 1) cout << 1ll*sum*(n+1)%mod*ksm(k,mod-2)%mod;
    else cout << 1ll*sum*(ksm(d,(n+1)/k)+mod-1)%mod*ksm(d-1,mod-2)%mod;
    return 0;
}