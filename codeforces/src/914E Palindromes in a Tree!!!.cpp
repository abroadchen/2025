//
// Created by Psy.C on 2026/10/12.
//
/**
树上的每条路径，把它经过的节点字符看成 bitmask（每个字符一位，共 20 位），路径的两端 u、v 之间整条路径的奇偶集合 = a[u] XOR a[v]，其中

a[x] = 从根 1 到 x 的路径上所有节点字符的异或和（bitmask）‍。

一条路径能重排成回文 ⟺ 路径上最多只有 1 种字符出现奇数次 ⟺ popcount(a[u] ^ a[v]) ≤ 1。
因此对每个 u，要找子树 sub[u] 中满足 popcount(a[u]^a[v]) ≤ 1 的 v 的个数。

计数公式：记 sum[t] = 当前已加入维护集合里、a[x]==t 的节点数。则对端点 a[u]：

ans += sum[a[u]]                    // 相同异或值 ⇒ popcount=0
      + Σ_{i=0..19} sum[a[u] ^ (1<<i)]   // 恰一个 bit 不同 ⇒ popcount=1

用 dfn 序把子树映射成连续区间 [dfn[u], dfn[u]+sz[u])，方便按区间遍历轻子树。
son[u] 记录重儿子（sz 最大的儿子），DSU on tree 的关键
calc 把"一个具有某 a[x]=val 的节点 x"，对端点 u 的贡献更新到 vc 表里，同时从 ans[u] 扣掉（因为轻子树贡献要断开）
val 表示某节点 x 的异或值；端点 u 的异或值是 a[u]。要求 popcount(a[u]^a[x]) ≤ 1：

恒等：a[u] == val，即 sum[val] 里的那些。
差一个 bit：a[u] == val ^ (1<<i)。
注意这里多异或了 tp（u 自己字符的 bit）。为什么？ 因为当路径一端是 u 本身（端点 u 到 x），a[u]^a[x] 中 u 自己的字符被算了两次抵消；但当 x 恰是子孙走向时 u 被算进 a[x]... 这里的 tp 处理的是"路径中的 LCA 或端点"带来的细节。实际上这段代码是经典 CF 风格题目，vc 机制用于把贡献暂存、在 dfs3 里统一累加（因为 DSU 过程中 sum 会被反复清空/恢复，不能立即加到答案）
三个很相似，都是：对端点 u，统计集合 sum 里满足 popcount(a[u]^a[x])≤1 的数量（tp 那两堆），然后把这个量从一个答案累加到另一个答案（用于轻子树加进/移出时的增量维护）
以 a[x] 为参考值，统计 sum 中与之相差 ≤1 bit 的数量 tp；把 x 收到的这批贡献加入 ans[x]，同时从 ans[u] 扣掉（保持总贡献守恒），add22 相反方向，add222 作用到 f[u]。这些是为了增量地、不重不漏地维护轻子树合并
这正是 DSU on tree 的核心：轻儿子算完即弃（清空 sum），重儿子算完保留，从而每个点只被处理 O(log n) 次。加上 calc/add 的增量统计与回滚（vc 表 + dfs3），最终做到对每个端点 u 统计其子树内所有合法路径
dfs3 是后处理：由于 DSU 过程中 sum 被反复清空/恢复，轻子树与 u 的配对贡献先暂存在 vc[son[u]]（或各节点），最后统一回溯累加，得到每个 u 的最终 ans。ans[u]+1（+1 表示 u 到 u 自己的长度为 0 的平凡路径也回文）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

int to[N<<1], nxt[N<<1], head[N], tot;
inline void add(int u, int v) {
    to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
}

struct node { ll cnt, val; };

int f[N], dfn[N], tim, sz[N], a[N], b[N], son[N];
char s[N];
void dfs(int u, int v) {
    f[u] = v; dfn[u] = ++tim; sz[u] = 1;
    a[u] = a[v]^(1<<(s[u]-'a')); //根到 u 的字符异或和
    b[tim] = u;//dfn 序 → 节点
    for (int i = head[u]; i; i = nxt[i]) {
        int y = to[i];
        if (y == v) continue;
        dfs(y, u);
        if (sz[son[u]] < sz[y]) son[u] = y;
        sz[u] += sz[y];
    }
}

ll sum[(1<<20)+5], ans[N];
vector<node> vc[N];
inline void calc(int u, int val) {
    if (!son[u]) return;
    int tp = 1<<(s[u]-'a');
    for (int i = 0; i < 20; ++i) {
        if (!sum[(val^(1<<i)^tp)]) continue;
        vc[son[u]].push_back({.cnt = 1, .val = val^(1<<i)^tp});
        ans[u] -= sum[val^(1<<i)^tp];
    }
    if (!sum[val^tp]) return;
    vc[son[u]].push_back({.cnt = 1, .val = val^tp});
    ans[u] -= sum[val^tp];
}

inline void add2(int u, int x) {
    ll tp = 0, tp2 = 1<<(s[u]-'a');
    for (int i = 0; i < 20; ++i) tp += sum[a[x]^(1<<i)^tp2];
    tp += sum[a[x]^tp2];
    ans[x] += tp; ans[u] -= tp;
}
inline void add22(int u, int x) {
    ll tp = 0, tp2 = 1<<(s[u]-'a');
    for (int i = 0; i < 20; ++i) tp += sum[a[x]^(1<<i)^tp2];
    tp += sum[a[x]^tp2];
    ans[x] -= tp; ans[u] += tp;
}
inline void add222(int u, int x) {
    ll tp = 0, tp2 = 1<<(s[u]-'a');
    for (int i = 0; i < 20; ++i) tp += sum[a[x]^(1<<i)^tp2];
    tp += sum[a[x]^tp2];
    ans[x] += tp; ans[f[u]] -= tp;
}


void dfs2(int u, int v, int op) {
    for (int i = head[u]; i; i = nxt[i]) {
        int y = to[i];
        if (y == v || y == son[u]) continue;
        dfs2(y, u, 0);
    }
    if (son[u]) dfs2(son[u], u, 1);
    calc(u, a[u]);
    for (int i = head[u]; i; i = nxt[i]) {
        int y = to[i];
        if (y == son[u] || y == v) continue;
        for (int j = dfn[y]; j < dfn[y]+sz[y]; ++j)
            calc(u, a[b[j]]), add22(u, b[j]);
    }
    add2(u, u); sum[a[u]]++;
    for (int i = head[u]; i; i = nxt[i]) {
        int y = to[i];
        if (y == v || y == son[u]) continue;
        for (int j = dfn[y]; j < dfn[y]+sz[y]; ++j) add2(u, b[j]);
        for (int j = dfn[y]; j < dfn[y]+sz[y]; ++j) sum[a[b[j]]]++;
    }
    sum[a[u]]--; add222(u, u);
    for (int i = head[u]; i; i = nxt[i]) {
        int y = to[i];
        if (y == v || y == son[u]) continue;
        for (int j = dfn[y]; j < dfn[y]+sz[y]; ++j) sum[a[b[j]]]--;
        for (int j = dfn[y]; j < dfn[y]+sz[y]; ++j) add222(u, b[j]);
    }
    if (!op) {
        for (int i = dfn[son[u]]; i < dfn[son[u]]+sz[son[u]]; ++i)
            sum[a[b[i]]]--;
    } else {
        sum[a[u]]++;
        for (int i = head[u]; i; i = nxt[i]) {
            int y = to[i];
            if (y == v || y == son[u]) continue;
            for (int j = dfn[y]; j < dfn[y]+sz[y]; ++j) sum[a[b[j]]]++;
        }
    }
}

void dfs3(int u, int v) {
    for (auto [cnt, val] : vc[u]) sum[val] += cnt;//恢复暂存
    ans[u] += sum[a[u]];//补重重儿子方向贡献
    for (int i = head[u]; i; i = nxt[i]) {//累加子树答案
        int y = to[i];
        if (y == v) continue;
        dfs3(y, u);
        ans[u] += ans[y];
    }
    for (auto [cnt, val] : vc[u]) sum[val] -= cnt;//回滚
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    int n = rd();
    for (int i = 1; i < n; ++i) { int u = rd(), v = rd(); add(u, v); add(v, u); }
    scanf("%s", s + 1);//节点字符，只用于映射 bit
    dfs(1, 0); dfs2(1, 0, 0);//预处理 DSU on tree
    memset(sum, 0, sizeof(sum)); dfs3(1, 0);//统一累加
    for (int i = 1; i <= n; ++i) cout << ans[i]+1 << ' ';
    cout << '\n';
    return 0;
}