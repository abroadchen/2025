//
// Created by Psy.C on 2025/11/21.
//
/*
 *fac:阶乘数组, inv:逆元数组, f:动态规划数组
 *num:符合条件的数字种类数, b:存储符合条件的数字
 *
 *
 *从前i种数中选j个 = (选第i种数)*(从前i-1种数中选j-1个) +
 *(不选第i种数)*(从前i-1种数中选j个)
 *枚举从符合条件的数字中选取i个，从不符合条件的数字中选取k-i个
 *
*cnt[i]：第i种数字（即b[i]）在原数组中出现的次数
f[i-1][1]：从前i-1种数字中选取1个数字的方案数
*f[i-1][j-1] * cnt[i]：选择第i种数字的方案数（从前i-1种中选j-1个，再从第i种的cnt[i]个中选1个）
f[i-1][j]：不选择第i种数字的方案数（从前i-1种中选j个）

 *O(M + n log M + k² + k)，其中M是预处理范围，k是选取数量
 */
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;
const int N = 1e5+10, mod = 1e9+7, M = 1e5, K = 2e3;
ll fac[N], inv[N], f[K][K];
int n, k, a[N], b[N], num, cnt[N], tot;

ll pw(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}

ll C(int n, int m) {//C(n,m) = n!/(m!(n-m)!)
    if (m > n) return 0;
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    fac[0] = 1;
    for (int i = 1; i <= M; ++i) fac[i] = fac[i-1] * i % mod;
    inv[M] = pw(fac[M], mod - 2);//(M!)^(p-2) ≡ (M!)^(-1) (mod p)
    for (int i = M - 1; i >= 0; --i) inv[i] = inv[i+1] * (i+1) % mod;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+n+1);
    num = 0; b[num] = -1;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == b[num]) { cnt[num]++; continue; }//如果当前数字与前一个相同，增加计数
        int t = a[i]; bool f = 1;
        while (t) {//检查当前数字是否只包含4和7
            int tmp = t % 10; t /= 10;
            if (tmp != 4 && tmp != 7) { f = 0; tot++; break; }
        }
        if (f) { b[++num] = a[i]; cnt[num] = 1; }//如果符合条件，加入b数组并计数
    }
    memset(f, 0, sizeof f);
    for (int i = 1; i <= num; ++i) f[i][0] = 1;//从前i种数中选0个的方案数为1
    for (int i = 1; i <= num; ++i) f[i][1] = cnt[i] + f[i-1][1];// 选1个的方案数
    for (int j = 2; j <= num; ++j) {
        for (int i = j; i <= num; ++i)
            f[i][j] = (f[i-1][j-1]*cnt[i] + f[i-1][j]) % mod;
    }
    ll ans = 0; f[0][0] = 1;
    for (int i = 0; i <= num; ++i) ans = (ans + f[num][i]*C(tot, k-i)) % mod;
    cout << ans << '\n';
    return 0;
}