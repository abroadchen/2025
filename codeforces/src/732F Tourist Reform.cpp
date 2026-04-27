//
// Created by Psy.C on 2026/4/26.
//
/**
dfn[N]: DFS访问时间戳
low[N]: 能回溯到的最早祖先的时间戳
cnt: 时间戳计数器
bel[N]: 节点所属的双连通分量编号
bcc: 双连通分量计数器
b[N]: 每个双连通分量的节点数
st: 用于Tarjan算法的栈
通过DFS遍历，维护low值，当发现割点时弹出栈中元素形成BCC
在双连通分量上进行深度优先搜索
vis数组记录边的方向，用于输出定向后的边
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 4e5+7;

struct node { int fr, to, nxt; } e[N<<1];

int now, head[N];
void add(int u, int v) {
    e[now].fr = u, e[now].to = v; e[now].nxt= head[u], head[u] = now++;
}

int dfn[N], low[N], cnt, bel[N], bcc, b[N];
stack<int> st;
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++cnt; st.push(x);
    for (int i = head[x]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        if (!dfn[v]) {
            tarjan(v, x);
            low[x] = min(low[x], low[v]);
        } else if (!bel[v])
            low[x] = min(low[x], low[v]);
    }
    if (dfn[x] == low[x]) {
        bcc++; b[bcc] = 0;
        while (true) {
            int u = st.top(); st.pop();
            bel[u] = bcc; b[bcc]++;
            if (u == x) break;
        }
    }
}

bool flag[N];
int vis[N<<1];
void dfs(int x) {
    flag[x] = true;
    for (int i = head[x]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (vis[i] != 0) continue;
        if (bel[v] == bel[x]) {
            vis[i] = 1; vis[i^1] = -1;
        } else vis[i^1] = 1, vis[i] = -1;
        if (!flag[v]) dfs(v);
    }
}


void init() {
    memset(head, -1, sizeof(head));
    now = 0, cnt = 0, bcc = 0;
    memset(flag, 0, sizeof(flag));
    memset(dfn, 0, sizeof(dfn));
    memset(vis, 0, sizeof(vis));
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    if (n == 0 && m == 0) return 0;
    init();
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v; add(u, v); add(v, u);
    }
    tarjan(1, 1);
    int rt = 1;
    for (int i = 2; i <= n; ++i) {
        if (b[bel[i]] > b[bel[rt]]) rt = i;//找到最大的双连通分量中的一个节点作为根
    }
    dfs(rt);//进行DFS遍历确定边的方向
    cout << b[bel[rt]] << '\n';
    for (int i = 0; i < now; i += 2) {
        if (vis[i] == 1)
            cout << e[i].fr << ' ' << e[i].to << '\n';
        else cout << e[i^1].fr << ' ' << e[i^1].to << '\n';
    }
    return 0;
}