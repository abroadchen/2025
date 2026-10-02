//
// Created by Psy.C on 2026/10/2.
//
/**
h[u] = 从 u 出发向下最长链的高度（含自己）；
dep[u] = 深度（根的 dep 初始为 0？注意 dep[fa[rt]] = dep[0]=0，所以根 rt 的 dep=1）；
对每个子节点 v 递归，更新 h[u]，并选出高度最大的子节点作为重儿子 son[u] —— 这就是长链剖分（按高度剖，不是按子树大小）
用两个大静态数组 buf 和 buf2 做内存池，指针 p1/p2 依次分配。
每条长链的链头 u==tp 一次性分配 h[u] 长度的两块连续内存（p[u] 和 cnt[u]），这就是长链剖分省内存的核心
p[u][k]：u 的第 k 层子孙（即深度相差 k 的那个代表节点）；
cnt[u][k]：u 子树中深度恰好加 k 的节点数。
这是经典长链 DP：每次把轻儿子 v 的 cnt[v]（每层节点数）按距离合并进父链的 cnt[u]。
合并时对每层 i 计算距离贡献，累加进 ans[]，并记录一条"差值边"进邻接表 E[]（用于后续整体传播）。
ans[p[u][i+1]] += dep[u] * cnt[v][i]：所有"距 v 内节点 i+1 层"的组合，贡献 dep[u] 倍。
E[a].push_back({b, 差值}) 记录一个带权边，供 dfs3 做链上的差分配对
dfs3 只沿重链一直往下走（flg 控制），把 E[] 里记录的加权边逐点"摊平"到各节点：ans[cur[0]] = ans[u] + cur[1]。
这一步把"按距离差"的贡献通过链上线性传播，转化为每个节点的最终 ans
第二次全树 DFS：每个子节点 v 的答案再累加 ans[u] + dep[u]，把聚合好的链上值向整棵子树广播。
最终 ans[i] 就是点 i 的答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e5+5;

int h[N], dep[N], fa[N], son[N];
vector<int> e[N];
void dfs(int u) {
    h[u] = 1; dep[u] = dep[fa[u]] + 1;
    for (auto v : e[u]) {
        dfs(v);
        h[u] = max(h[u], h[v]+1);
        if (h[v] > h[son[u]]) son[u] = v;
    }
}

int buf[N], *p1 = buf, *p[N];
int buf2[N], *p2 = buf2, *cnt[N];
ll ans[N];
vector<array<ll, 2>> E[N];
void dfs2(int u, int tp) {
    if (u == tp) {
        p[u] = p1; p1 += h[u]; cnt[u] = p2; p2 += h[u];
    }
    if (son[u]) {
        p[son[u]] = p[u] + 1;//重儿子复用父指针偏移 1
        cnt[son[u]] = cnt[u] + 1;
        dfs2(son[u], tp);//深入重链
    }
    p[u][0] = u, cnt[u][0] = 1;//自己距离为 0
    for (auto v : e[u]) {
        if (v == son[u]) continue;//跳过重儿子
        dfs2(v, v);//轻儿子开新链
        for (int i = 0; i < h[v]; ++i) {
            ans[p[u][i+1]] += 1ll*dep[u]*cnt[v][i];
            ans[p[v][i]] += 1ll*dep[u]*cnt[u][i+1];
            E[p[u][i+1]].push_back({p[v][i], ans[p[v][i]]-ans[p[u][i+1]]});
            cnt[u][i+1] += cnt[v][i];//合并轻儿子统计
        }
    }
}

void dfs3(int u, bool flg) {
    if (flg && son[u]) dfs3(son[u], flg);
    for (auto cur : E[u]) {
        ans[cur[0]] = ans[u] + cur[1];
        dfs3(cur[0], false);
    }
}

void dfs4(int u) {
    for (auto v : e[u]) {
        ans[v] += ans[u] + dep[u];
        dfs4(v);
    }
}

int rt;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> fa[i];
        if (fa[i] > 0) e[fa[i]].push_back(i);
        else rt = i;
    }
    dfs(rt); dfs2(rt, rt); dfs3(rt, true); dfs4(rt);
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " \n"[i==n];
    return 0;
}