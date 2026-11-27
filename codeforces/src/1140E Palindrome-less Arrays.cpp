//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
标准快速幂，计算 a^q mod 998244353。
用于"无外部约束时的自由组合"计数（如整段为空时 k × (k-1)^(len-1)）
dp[i][0]：长度为 i 的未定段，首尾颜色相同的方案数。
dp[i][1]：长度为 i 的未定段，首尾颜色不同的方案数。
转移：
首尾相同：上一段首尾不同 × (k-1)。
首尾不同：上一段首尾不同 × (k-2) + 上一段首尾相同 ×1。
⚠️ 注：这个 dp 需要配合"相邻不能同色"的限制递推（是给相邻染色计数）
剪枝：相邻已定且颜色相同 → 返回 0。
分段枚举：把连续的 -1（未定连续块）切出来，逐块处理。
对每个未定块，分三种情况：
整段都未定 → 自由组合：k × (k-1)^(n-1)（首色 k 种，后续逐位避免与前一位同色）。
只被一端固定（在开头或末尾）→ 用 dp 组合：固定端颜色 → 一个已知锚点。
两端都被固定 → 看两端颜色是否相同，用对应 dp[j-i+1][same?]
把原数组按奇偶下标拆成两条链分别独立求解，是因为题目限制是对角/步长方向相邻不能同色（而非普通相邻），拆分后每条链内部满足普通相邻约束。
两链方案数相乘得总答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+5, mod = 998244353;
inline int ksm(int a, int q) {
    int r = 1;
    for (; q; q>>=1,a=1ll*a*a%mod)
        if (q&1) r=1ll*r*a%mod;
    return r%mod;
}

int k, dp[N][2];
inline int solve(int n, int a[]) {
    int ret = 1;
    rep(i,n-1) if (a[i] != -1 && a[i] == a[i+1]) return 0;//剪枝：相邻已定且同色 → 0
    //找每一段连续 -1（未定区间），分段统计
    for (int i = 1, j; i <= n; i = j+1) {
        while (i <= n && a[i] != -1) i++;//跳过已定，找到第一个 -1
        j = i;
        while (j <= n && a[j] == -1) j++;
        j--;//让 j 落在最后一个 -1
        if (i > j || i < 1 || j > n) continue;
        //全段未定
        if (i == 1 && j == n) ret = 1ll*ret*ksm(k-1,n-1)%mod*k%mod;
        //只贴一段边界
        else if (i == 1 || j == n) ret = 1ll*(dp[j-i][0]+1ll*(k-1)*dp[j-i][1]%mod)%mod*ret%mod;
        else ret = 1ll*ret*dp[j-i+1][a[i-1]!=a[j+1]]%mod;//两端都被已定颜色夹住
    }
    return ret;
}

int n, ans, a[N], b[N], m;
signed main() {
    fast;
    cin >> n >> k; dp[0][0] = 0, dp[0][1] = 1, ans = 1;
    rep(i,n) cin >> a[i];
    rep(i,n) dp[i][0] = 1ll*dp[i-1][1]*(k-1)%mod, dp[i][1] = (1ll*dp[i-1][1]*(k-2)%mod+dp[i-1][0])%mod;
    for (int i = 1; i <= n; i += 2) b[++m] = a[i];//奇位
    ans = 1ll*ans*solve(m,b)%mod; m = 0;
    for (int i = 2; i <= n; i += 2) b[++m] = a[i];//偶位
    ans = 1ll*ans*solve(m,b)%mod;
    cout << ans << '\n';
    return 0;
}