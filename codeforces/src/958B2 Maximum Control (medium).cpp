//
// Created by Psy.C on 2026/10/20.
//
/**
从节点 1 出发，d[u] 记录深度。遍历所有叶子节点，把深度最大的叶子记为 rt（根）。这样 rt 是"最长的一条从根到叶子路径的末端"，目的是让从它出发的那条链覆盖尽量多的点
从 rt 重新求深度 d。
h[u] = 以 u 为根的子树中，最深叶子到根的深度。
son[u] = 所有儿子中，h 值最大（子树最深）的那个，即重儿子。这是"长链剖分"的核心：每个点只保留一条最深的链作为重链
沿重链一直往下走，直到叶子；走到叶子时，把 d[u] - d[tp]（这条链从链顶到叶子的长度，即覆盖的节点数）加入 val。
对每个轻儿子，递归时把它作为新链的链顶 tp。
所以 val 收集的是"按长链剖分切分后，每条链的长度"，也就是每次新增一条链能多覆盖的节点数。
关键点：链长度按 d[u] - d[tp] 计算，从链顶（非根节点）到叶子，覆盖的节点数 = 深度差
输出 1 ：k=1 时，从根 rt 出发的长链至少覆盖根节点 1 个点（若根是叶子，覆盖从根到……实际上 k=1 覆盖 1 个起点）。
val 从大到小排序——贪心：每次新增支撑，选当前最长的未被覆盖链，能最大化新增覆盖节点数。
从 k=2 开始：i-2 当作"已经用了第 i-2 条链之后的下一链"，ans += val[i-2]，累加每条新增链长度。
输出 ans[2], ans[3], ..., ans[n]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

struct edge { int to, nxt; } e[N<<1];
int head[N], cnt;
void add(int u, int v) {
    e[++cnt].to = v; e[cnt].nxt = head[u]; head[u] = cnt;
}

int d[N], rt;
void dfs(int u, int fa) {
    d[u] = d[fa] + 1;
    int num = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u);
        num++;
    }
    if (!num) {
        if (!rt || d[u] >= d[rt])
            rt = u;//记录深度最大的叶子
    }
}

int h[N], son[N];
void dfs2(int u, int fa) {
    d[u] = d[fa] + 1; h[u] = d[u];
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs2(v, u);
        h[u] = max(h[u], h[v]);// h[u] = 子树中最深深度
        if (!son[u]) son[u] = v;
        else if (h[son[u]] < h[v]) son[u] = v;//选子树最深的重儿子
    }
}

vector<int> val;
void dfs3(int u, int fa, int tp) {
    if (!son[u]) { val.push_back(d[u] - d[tp]); return; }
    dfs3(son[u], u, tp);//沿重链往下，tp 不变（同一条链）
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        if (v == son[u]) continue;
        dfs3(v, u, u);//轻儿子：新开一条链，tp = 该儿子
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v; add(u, v); add(v, u);
    }
    rt = 0; ll ans = 0; dfs(1, 0); dfs2(rt, 0); dfs3(rt, 0, 0);
    cout << "1 ";
    ranges::sort(val, greater());
    for (int i = 2; i <= n; ++i) {
        if (i-2 < val.size()) ans += val[i-2];
        cout << ans << ' ';
    }
    return 0;
}