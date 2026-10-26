//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
对节点 x：

初始化 f[x][i] = 1（i=1..n+1）。
对每个子节点 y 递归处理：
维护 sum = Σ_{k≤i} f[y][k];
f[x][i] *= sum。
含义：f[x][i] 表示以 x 为根的子树、在"每种颜色有 i 种选择"（或高度/深度 ≤ i）时的方案数。

父节点方案 = 各子树方案的前缀和连乘。
叶子节点全是 1。
这类 DP 常见背景：树上染色，「深度不超过限制 d / 颜色数 ≤ i」，得到关于 i 的多项式，次数最高 ≤ 树高，通常 ≤ n
这段是标准 O(n) 拉格朗日插值（对次数 ≤ n 的多项式，由 n+1 个点 (i, num[i])，i=1..n+1，求 num 对应多项式在 x=d 处的值）：

fac/inv：阶乘和逆元。
pre[i] = ∏_{k=1}^{i} (x-k)：前缀连乘。
suf[i] = ∏_{k=i}^{n+1} (x-k)：后缀连乘。
对每个插值点 i：
cur = num[i] * pre[i-1] * suf[i+1] * inv[i-1] * inv[n+1-i]
分母符号由 (n+1-i) 的奇偶决定正负。
累加得到 res，即 get(d) 的值。
这是拉格朗日插值一个截面点 x=d 的标准公式，O(n) 而非 O(n²)
读入 n、d，建树（每个点 i 的父节点为 x）。
dfs(1) 递推得到 f[1][i]。
num[i] = f[1] 在通道 i 的前缀和。
用插值在 d 处求值输出。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define per(i,n) for (int i = n; i >= 1; i--)
#define ll long long
using namespace std;

constexpr int N = 3005, mod = 1e9+7;

ll ksm(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}

int n;
ll f[N][N];
vector<int> G[N];
void dfs(int x) {
    rep(i,n+1) f[x][i] = 1;
    for (int y : G[x]) {
        dfs(y);
        ll sum = 0;
        rep(i,n+1) {
            sum = (sum+f[y][i])%mod;
            f[x][i] = f[x][i]*sum%mod;
        }
    }
}

ll fac[N<<1], inv[N<<1], pre[N], suf[N], num[N];
ll get(int x) {
    fac[0] = inv[0] = 1;
    rep(i,n+1) fac[i] = fac[i-1]*i%mod;
    inv[n+1] = ksm(fac[n+1], mod-2);
    per(i,n) inv[i] = inv[i+1]*(i+1)%mod;
    pre[0] = 1; suf[n+2] = 1;
    rep(i,n+1) pre[i] = pre[i-1]*(x-i)%mod;
    per(i,n+1) suf[i] = suf[i+1]*(x-i)%mod;
    ll res = 0;
    rep(i,n+1) {
        ll cur = num[i]*pre[i-1]%mod*suf[i+1]%mod*inv[i-1]%mod*inv[n+1-i]%mod;
        if ((n+1-i)&1) res=(res-cur+mod)%mod;
        else res=(res+cur)%mod;
    }
    return res;
}


int d;
int main() {
    fast;
    cin >> n >> d;
    for (int i = 2, x; i <= n; i++) {
        cin >> x; G[x].push_back(i);
    }
    dfs(1);
    rep(i,n+1) num[i] = (num[i-1]+f[1][i])%mod;
    cout << get(d) << '\n';
    return 0;
}