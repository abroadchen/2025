//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
dfn/low/tim/st/tp/ins：Tarjan 标准量（访问序、回溯最小序、栈、栈顶、在栈标记）。
dep[u]：u 在本次深度优先搜索树中的深度（从 1 起）。
scc：当前强连通分量个数计数。
bel[u]：u 所属 SCC 编号。
G：原图邻接表。
T：每个 SCC 内的节点列表（T[scc] 存该分量包含的所有点）
标准的 Tarjan：未访问的子节点递归，并用 low[v] 更新 low[u]。
已访问且在栈中的（回边/横边指向栈中）用 dfn[v] 缩 low[u]。
low[u] == dfn[u] 时把栈内到 u 为止的元素全部弹出，归为一个新 SCC：编号 ++scc，记录每个点的归属 bel，并把它们顺序加入 T[scc]
读入 n 个点、m 条边、每单位周期长度 d；建图；对每个未被访问的点设 dep=1 后跑 Tarjan。
初始化 per[i] = d（每个分量周期默认取 d）。
遍历所有边 u→v，若 u、v 同属一个 SCC（bel 相同），则以 abs(dep[u]-dep[v]+1) 对 per 取 gcd。
per[id] 表示该 SCC 内在状态沿边前进时，时刻变化的"稳定周期"（通过 gcd 把所有环长折叠成能整除的总周期）
直观：在同一 SCC 内，沿某条边 u→v 会让"当前时刻"前进 1（对应 +1），经历 d 个时刻周期循环。dep 差分 + 取 gcd 得到该分量中所有可能 step 的公共周期 per，用来把时刻压缩到 [0, per) 内做 DP
tc[i] = dep[i] mod per[bel[i]]：把深度（时刻）压缩到分量周期内。
itc[i] = "补偿"：若 tc != 0，则 per - tc 才是能回到起点（时刻 0）所需的步数，否则为 0。这是为跨分量转移准备的"重整时刻偏移"
每个点给一个长度为 d 的 0/1 串：w[i][j]=1 表示时刻 j 时该点"有价值"（可被贡献一次）。这是定义"在某时刻经过某点能收获的奖励"
分两阶段（都用当前分量 id、周期 pr 遍历 j ∈ [0, pr) 作为"时刻状态"）：

阶段 A：统计 cnt[j] —— 该 SCC 在"起点时刻 j"下能收获的奖励数
对每个时刻 j、分量内每个点 u，若存在某个有效整数 k（按分量周期步进）使得点 u 在时刻 (k+tc[u]+j) mod d 有意义（w=1），则该分量在此 j 下贡献 +1。
break（去重）‍：同一点只计一次，即使多个 k 都命中。这就是"每个点在一轮内只能被计数一次"的奖励上限。
阶段 B：DP 状态转移，算 f[id][j]
初始 f[id][j] = cnt[j]：只在本分量内时的收益。
对分量内每个点 u 的每条出边 u→v（v 属于别的 SCC）‍，把状态转移到目标分量的对应时刻 (itc[v]+k+x)%per[...]，从而把目标分量的最优值累加上来。
由于 bel[v] != id，这里只做跨分量的正向转移（SCC 被缩成 DAG，天然无环），因此按 id 顺序计算 f 能保证依赖成立。
本质上 f[id][j] = "从该 SCC 以时刻 j 为起始，沿 DAG 一路走，能累计的最大奖励数（包括进入子分量后继续走）"
从节点 1 所在 SCC、以时刻 itc[1] 为起点，取 DP 值。bel[1] 是 1 号点的分量，itc[1] 是 1 号点应有的起点时刻偏移。这是整条（最优路径从点 1 出发）的最大累计奖励
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1e5+10, M = 55;

int dfn[N], low[N], tim, st[N], tp, ins[N], dep[N], scc, bel[N];
vector<int> G[N], T[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st[++tp] = u, ins[u] = 1;
    for (auto v : G[u]) {
        if (!dfn[v]) {
            dep[v] = dep[u] + 1, tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++scc;
        for (int x = 0; x != u; --tp) {
            x = st[tp]; bel[x] = scc; T[scc].push_back(x);
            ins[x] = 0;
        }
    }
}


int n, m, d, per[N], tc[N], itc[N], w[N][M], f[N][M];
char s[M];
int main() {
    fast;
    cin >> n >> m >> d;
    rep(i,m) { int u, v; cin >> u >> v; G[u].push_back(v); }
    rep(i,n) if (!dfn[i]) dep[i] = 1, tarjan(i);
    rep(i,scc) per[i] = d;
    rep(u,n) for (auto v : G[u]) if (bel[u] == bel[v])
        per[bel[u]] = __gcd(per[bel[u]], abs(dep[u]-dep[v]+1));
    rep(i,n) tc[i] = dep[i]%per[bel[i]], itc[i] = tc[i]?per[bel[i]]-tc[i]:0;
    rep(i,n) {
        cin >> s;
        for (int j = 0; j < d; ++j) w[i][j] = s[j]-'0';
    }
    rep(id,scc) {
        int pr = per[id];
        static int cnt[M];
        for (int j = 0; j < pr; ++j) cnt[j] = 0;
        for (int j = 0; j < pr; ++j)
            for (auto u : T[id]) for (int k = 0; k < d; k += pr)
                if (w[u][(k+tc[u]+j)%d]) { ++cnt[j]; break; }
        for (int j = 0; j < pr; ++j) {
            f[id][j] = cnt[j];
            for (auto u : T[id]) {
                int x = (j+tc[u]+1)%pr;
                for (auto v : G[u]) if (bel[v] != id)
                    for (int k = 0; k < d; k += pr)
                        f[id][j] = max(f[id][j],cnt[j]+f[bel[v]][(itc[v]+k+x)%per[bel[v]]]);
            }
        }
    }
    cout << f[bel[1]][itc[1]] << '\n';
    return 0;
}