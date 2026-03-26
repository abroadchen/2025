//
// Created by Psy.C on 2026/3/26.
//
/**
mul()：模乘函数，防止溢出
inv[i]：i在模mod下的逆元
inv[i] = mul(mod-mod/i, inv[mod-mod/i*i])：利用递推公式计算逆元
fac[i]：计算阶乘的逆元

如果x较小，直接返回预计算值
否则使用拉格朗日插值公式计算
ksm(x-i, mod-2)：计算(x-i)的逆元（费马小定理）
(k+2-i)&1?(mod-fac[k+2-i]):fac[k+2-i]：处理符号变化

y[i] = 1^k + 2^k + ... + i^k（模mod意义下）
预计算前k+2项的幂次和
时间复杂度：O(k) 空间复杂度：O(k)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5, mod = 1e9+7;

int mul(int x, int y) { return 1ll*x*y%mod; }
int ksm(int a, int b, int ans=1) {
    for (; b; b>>=1, a=mul(a,a))
        if (b&1) ans=mul(ans,a);
    return ans;
}
int inv[N], fac[N], k;
void init() {
    inv[1] = 1, fac[0] = fac[1] = 1;
    for (int i = 2; i <= k+2; ++i)
        inv[i] = mul(mod-mod/i, inv[mod-mod/i*i]);
    for (int i = 2; i <= k+2; ++i)
        fac[i] = mul(fac[i-1], inv[i]);
}

int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
int y[N];
int get(int x) {
    if (x <= k+2) return y[x];
    int ans = 0;
    for (int i = 1; i <= k+2; ++i) {
        int t = mul(y[i], ksm(x-i, mod-2));
        t = mul(t, mul(fac[i-1], (k+2-i)&1?(mod-fac[k+2-i]):fac[k+2-i]));
        ans = add(ans, t);
    }
    for (int i = 1; i <= k+2; ++i)
        ans = mul(ans, x-i);
    return ans;
}

int n;
int main() {
    fast;
    cin >> n >> k; init();
    for (int i = 1; i <= k+2; ++i)
        y[i] = add(y[i-1], ksm(i, k));
    cout << get(n) << '\n';
    return 0;
}