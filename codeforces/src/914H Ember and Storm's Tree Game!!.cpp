//
// Created by Psy.C on 2026/10/13.
//
/**
度数上限为 1 时，只能是一条"链"（最多 2 个点的树）。所以 n>2 时答案为 0
c[i][j] = 组合数 C(i,j)
w[i][j]：把 j 个大小相同的组（每组 i 个点）挂到同一父节点下的标号合并方案数。递推用组合数累乘，是经典的"多棵树合并计数"技巧（Cayley 递推式）
树上背包：

dp[j][l] 表示：用了 j 个点、根节点度数为 l 的组合森林方案数；
外层 i 枚举子树大小（从小到大），内层做多重背包合并（选 o 棵大小为 i 的子树）；
w[i][o]：合并权重；c[j][o*i]：标号选择；pw = s[i-1][d-1]^o：每棵子树再往下的结构方案数；
s[i][l] = Σ_{k≤l} dp[i][k]：前缀和，表示"大小为 i、根度≤l"的方案数。
这个 dp 记录以某点为根、所有子树都合法（每个点度≤d）且有根树的方案数
无根树的一种基本情形：根度数为 1 的树（两棵子树型）。2*s[n-1][d] 表示两种"从某点出发"的计数，减 1 修正对称
f[j]：一棵"部分树"的计数（递归拆分子树）；
g[]：两棵子树组合（根度数为 2 的链式结构）
根度数为 2、左右两棵 g 子树
h[i][x]：把一棵 f 树和一棵 dp 树组合起来的辅助结构；
最后再把两个 h 拼成根度数为 deg 的树（x+y 部分），覆盖"根度数 ≥3"的情形
末尾乘 n*(n-1)*2：选定根及其"方向/旋转"的标号展开，得到完整的有标号无根树计数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 205;
int n, d;
ll mod, c[N][N], w[N][N], dp[N][N], s[N][N], f[N], g[N], h[N][N];
int main() {
    fast;
    cin >> n >> d >> mod;
    if (d == 1 && n > 2) return cout << "0\n", 0;
    rep(i,0,n) {
        c[i][0] = 1;
        rep(j,1,i) c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
    }
    rep(i,1,n) {
        w[i][0] = 1;
        for (int j = 1; j*i <= n; ++j)
            w[i][j] = 1ll*w[i][j-1]*c[i*j-1][i-1] % mod;
    }
    dp[0][0] = 1;
    rep(i,0,d) s[0][i] = 1;
    rep(i,1,n-1) {
        static ll t[N][N];
        rep(j,0,n) rep(k,0,d) t[j][k] = dp[j][k];
        rep(j,i,n) rep(l,1,d)
            for (int o=1,pw=s[i-1][d-1];o*i<=j&&o<=l;++o,pw=1ll*pw*s[i-1][d-1]%mod)
                t[j][l] = (t[j][l]+1ll*dp[j-o*i][l-o]*w[i][o]%mod*c[j][o*i]%mod*pw)%mod;
        rep(j,0,n) rep(k,0,d) dp[j][k] = t[j][k];
        rep(l,1,d) s[i][l] = (s[i][l-1]+dp[i][l])%mod;
    }
    ll res = (2*s[n-1][d]+mod-1)%mod; f[0] = 1;
    rep(j,1,n-2) rep(k,1,j)
        f[j] = (f[j]+1ll*f[j-k]*s[k-1][d-2]%mod*c[j-1][k-1])%mod;
    rep(j,0,n-2) rep(k,2,n-2-j)
        g[k+j] = (g[k+j]+1ll*f[j]*s[k-1][d-2]%mod*c[k+j-1][k-1])%mod;
    rep(i,1,n-2) rep(j,1,n-2) if (i+j <= n-2) res=(res+1ll*g[i]*g[j])%mod;
    rep(i,0,n-2) rep(j,1,n-2-i) rep(k,1,d-2)
        h[i+j][k] = (h[i+j][k]+1ll*f[i]*c[i+j][i]%mod*dp[j][k])%mod;
    rep(x,1,d-2) rep(y,1,d-2) if (x+y <= d-2) rep(i,1,n-3)
        res = (res+1ll*h[i][x]*h[n-3-i][y])%mod;
    cout << res*n*(n-1)*2%mod << '\n';
    return 0;
}