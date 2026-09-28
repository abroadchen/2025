//
// Created by Psy.C on 2026/9/28.
//
/**
读入 n。
先读 b[1..n]，再读 a[1..n]。
c[i] = b[i] - a[i]：每个点存储一个"差值"（b 减 a）。后面 DFS 用 c 做聚合
对每个节点 i (u=i)（i=2..n），输入其父节点 v 和边权 w。
建无向边：父 v 连到子 u，权 w；子 u 连到父 v，权 1。
也就是说，树的"父子方向"用不同边权表达：向下（父→子）权 w，向上（子→父）权 1。这为后面 DFS 的聚合公式所用

dfs(u, fa, w)：u 为当前节点，fa 为父节点，w 为从父到 u 的边权（父→子方向权）。
遍历 u 的所有邻居：
若 v != fa（是子节点），递归 dfs(v, u, ww)，把返回的贡献累加到 c[u] ——子树聚合到当前节点。
若 v == fa（是父节点），记录 w2 = ww，即从 u 到父方向的边权（按照建树规则，这个值应是 1）。
对非根节点 u != 1：
若聚合后的 c[u] < 0（偏负），返回 c[u] * w（乘"向下"边权 w）。
否则（c[u] >= 0），返回 c[u] / w2（除以"向上"边权 w2）。
→ 即叶子向根聚合时，根据正负用不同边权做缩放（负值乘 w，正值除以 w2）。这是某种"按边权折半/放大"的决策。
根节点 u == 1 直接返回 0，c[1] 在循环里已经累积了所有子树的贡献。
从根 1 出发 DFS（fa=0 表示无父，w=1）。
聚合完成后，若根 c[1] >= 0 输出 YES，否则 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5;

vector<ii> g[N];
double c[N];
double dfs(int u, int fa, int w) {
    int w2;
    for (auto [fst, snd] : g[u]) {
        int v = fst, ww = snd;
        if (v != fa) c[u] += dfs(v, u, ww);
        else w2 = ww;
    }
    if (u != 1) {
        if (c[u] < 0) return 1.00000*c[u]*w;
        return 1.00000*c[u]/w2;
    }
    return 0;
}

int b[N], a[N];
signed main() {
    fast;
    int n, i, u, v, w; cin >> n;
    for (i = 1; i <= n; ++i) cin >> b[i];
    for (i = 1; i <= n; ++i) {
        cin >> a[i]; c[i] = b[i] - a[i];
    }
    for (i = 2; i <= n; ++i) {
        u = i; cin >> v >> w;
        g[v].emplace_back(u, w);
        g[u].emplace_back(v, 1);
    }
    dfs(1, 0, 1);
    if (c[1] >= 0) cout << "YES\n"; else cout << "NO\n";
    return 0;
}