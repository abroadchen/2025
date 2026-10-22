//
// Created by Psy.C on 2026/10/22.
//
/**
dfn：每个节点的 dfs 时间戳。
low：每个节点能回溯到的最早时间戳。
tot：时间戳计数器。
st：栈；now：栈顶。
cnt：连通分量编号。
sz：每个连通分量的点数。
dcc：每个点属于哪个连通分量。
ind：每个点的度数（无向图中连的边数）。
in：点是否在栈中。
vis：每个连通分量是否"仍然可能是一个纯环"。
e：邻接表
初始化 dfn/low 为新的时间戳，入栈。
遍历邻接点 y：
未访问则递归，更新 low；
已在栈中则用 dfn[y] 更新 low（无向图这里用 in 判断，若按有向则需 parent 处理，但代码是按无向加边）。
强连通/双连通判断：当 low[x] == dfn[x]（!(low[x]^dfn[x]) 即 low == dfn）时，x 是连通分量的根，弹栈得到一个连通分量。
弹出时：
计数 sz[cnt]++（点数）。
记录归属 dcc[tmp]=cnt。
关键：if (ind[tmp] != 2) vis[cnt] = false; —— 若该分量中任一节点度数不为 2，则这个分量不是"纯环"，把 vis 置 false
读入 n、m 及 m 条无向边，双向建邻接表，并累加各自度数 ind。
vis 初始全 true。
对每个未访问节点递归跑 tarjan，得到所有连通分量。
遍历所有连通分量：统计 vis[i] && sz[i] >= 3（即是纯环且点数 ≥ 3）的个数作为答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+10;

int dfn[N], low[N], tot, st[N], now, cnt, sz[N], dcc[N], ind[N];
bool in[N], vis[N];
vector<int> e[N];
inline void tarjan(int x) {
    dfn[x] = low[x] = ++tot; in[x] = true; st[++now] = x;
    for (const auto y : e[x]) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (in[y]) low[x] = min(low[x], dfn[y]);
    }
    if (!(low[x]^dfn[x])) {
        int tmp; cnt++;
        do {
            tmp = st[now--];
            in[tmp] = false;
            sz[cnt]++; dcc[tmp] = cnt;
            if (ind[tmp] != 2) vis[cnt] = false;
        } while (tmp != x);
    }
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
    int n = rd(), m = rd();
    for (int i = 1, u, v; i <= m; ++i) {
        u = rd(), v = rd();
        e[u].push_back(v); e[v].push_back(u);
        ind[u]++, ind[v]++;
    }
    memset(vis, true, sizeof vis);
    for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);
    int ans = 0;
    for (int i = 1; i <= cnt; ++i) if (vis[i] && sz[i] >= 3) ans++;
    cout << ans << '\n';
    return 0;
}