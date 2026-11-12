//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
N：最大节点数规模。
mod = 998244353：常用的 NTT 友好大质数。
inv2 = 499122177：2 的模逆元（满足 2×inv2 ≡ 1 (mod mod)），代码用它代替除法 /2
G[u]：u 的邻居列表。
f[u]：[推] 表示以 u 为根、在子树内的某种合法方案数 / 期望，累加到答案
ret = 1：初始化"往下返回的计数"为 1（单位元，累乘起点）。

for (v : G[u]) if (v != fa)：遍历所有儿子（跳过父节点）。

int t = dfs(v, u)：递归先算儿子子树的返回值 t（即儿子那棵子树的 ret）。

更新公式①：

f[u] += ret * t * inv2
ret 是之前已处理儿子的累积 ret，t 是当前儿子子树的返回计数，inv2 即 /2。这像是在累计"经过 u 的组合贡献"。

更新公式②：

ret *= (f[v]+1) * inv2
把当前儿子整合进 ret，f[v]+1 表示"选 or 不选 v 子树"两类情况（+1 表示不选）。

return ret：该子树向上返回的计数。

综合看，这是树上"匹配/覆盖/独立集"类计数的经典形态：f[v]+1 表示在 v 子树上可"取或不取"，乘法累积方案；inv2 频繁出现，说明概率式期望（每步 1/2 概率）或对称计数。
cin >> n：读节点数。
rep(i, n-1)：读 n-1 条边，加到邻接表（无向边，两边都 push）。
dfs(1, 0)：从根 1 开始 DFS，父节点用 0 表示不存在。
rep(i,n) ans += f[i]：把每个节点的 f[i] 累加。
ans *= 2：翻倍一次。
rep(i,n-1) ans*=2：再翻倍 n-1 次，即总乘数为 2^n。
输出 ans。
最终 ans = (Σ f[i]) × 2^n (mod 998244353)

因为 DP 里每次用 inv2（即 /2）来计数，所以最后整体要补回 2^n 个因子（dfs 里每个节点造成了 /2），main 里恰好乘了 n 次 2——把 /2 全部抵消，还原成整数方案数。

一句话核对：

inv2 出现的地方 → 模块里每次除以 2；
main 里 ×2 出现 n 次 → 补回 n 个因子；
净效果：ans = (Σ f[i]) （在没有模逆元干扰下的整数）`，再约去所有 1/2 后得到整数答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define ll long long
using namespace std;

constexpr int N = 5e5+10, mod = 998244353, inv2 = (mod+1)/2;

vector<int> G[N];
int f[N];
int dfs(int u, int fa) {
    int ret = 1;
    for (int v : G[u]) if (v != fa) {
        int t = dfs(v, u);
        f[u] = (f[u] + (ll)ret*t%mod*inv2)%mod;
        ret = (ll)ret*(f[v]+1)%mod*inv2%mod;
    }
    return ret;
}

int n, u, v, ans;
int main() {
    fast;
    cin >> n;
    rep(i,n-1) { cin >> u >> v; G[u].push_back(v); G[v].push_back(u); }
    dfs(1, 0);
    rep(i,n) ans = (ans + f[i]) % mod;
    ans = (ll)ans*2%mod;
    rep(i,n-1) ans = ans*2%mod;
    cout << ans << '\n';
    return 0;
}