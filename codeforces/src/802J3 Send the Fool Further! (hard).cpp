//
// Created by Psy.C on 2026/9/18.
//
/**
k[i]：节点 i 的度数（连了几条边）。
b[i]：节点 i 关联边权 c 的总和。
注意 ++u, ++v：输入是 0 基，转成 1 基。
in[i] = k[i]：保存初始度数副本（后面会改）
从根 1 出发做 DFS，q[1..n] 是前序（父先子后）‍序列，fa[u] 记录父子关系。
用于后面倒序处理
高斯消元在树上的特化（叶子向根消元）‍思路。对每个节点 i（倒序，即从叶子到根）：
算出 k[i] 的模逆元 inv = k[i]^(mod-2)（费马小定理）。
把以 i 的状态方程消到父节点 fa[i] 上：父的 k 减 inv，父的 b 加 b[i]*inv。
in[i] != 1 即非叶子节点才做（叶子没有子方程可消，或度数为1直接是边界
最后根节点 1 的方程被消成只剩自身：k[1] * X = b[1]（模意义），解 X = b[1] * k[1]^{-1}。
输出这个值，就是要求的期望值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, mod = 1e9+7;

struct node { int to, nxt; } e[N<<1];

int top, head[N];
void add(int u, int v) {
    e[++top] = {.to = v, .nxt = head[u]}, head[u] = top;
}

int ksm(int a, int b) {
    int ans = 1;
    while (b) {
        if (b&1) ans = 1ll*ans*a%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return ans;
}

int q[N], tl, fa[N];
void dfs(int u) {
    q[++tl] = u;
    for (int i = head[u]; i; i = e[i].nxt)
        if (e[i].to != fa[u])
            fa[e[i].to] = u, dfs(e[i].to);
}

int n, k[N], b[N], in[N];
void solve() {
    cin >> n;
    for (int i = 1, u, v, c; i < n; ++i) {
        cin >> u >> v >> c; ++u, ++v;
        add(u, v); add(v, u);
        ++k[u], ++k[v], b[u] += c, b[v] += c;
    }
    for (int i = 1; i <= n; ++i) in[i] = k[i];
    dfs(1);
    for (int i = n; i >= 1; --i)
        if (in[i] != 1) {
            int inv = ksm(k[i], mod-2);
            (k[fa[i]] -= inv) %= mod;
            (b[fa[i]] += 1ll*b[i]*inv%mod) %= mod;
        }
    cout << (1ll*b[1]*ksm(k[1], mod-2)%mod+mod)%mod << '\n';
}

int main() {
    fast;
    solve();
    return 0;
}