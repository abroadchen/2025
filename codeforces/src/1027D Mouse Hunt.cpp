//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
邻接表（前向星），head[u] 为 u 的第一条边下标，nxt 指向下一条。
clear() 用 memset 重置 head 和 e
标准 Tarjan：

dfn 访问次序，low 可达祖先的最小 dfn。
弹栈得到一个 SCC，编号 scc，并同时记录 该 SCC 内节点的最小代价 c[top]
缩点后，对原图每条边检查两端 SCC 是否相同；不同则起点 SCC 出度 +1。out[scc] 表示各 SCC 的出度
出度为 0 的 SCC（图的终点）‍内部代价最小的点必选，累加。这就是答案。

为什么只加出度为 0 的 SCC？

函数图中，从任何点出发不断走，最终必然落进某个入环/终点 SCC（出度为 0 的 SCC）。
每个出度为 0 的 SCC 是"终点集合"，若里面不选点，则这个 SCC 内所有点都无法到达任何关键点 → 不满足条件。
出度不为 0 的 SCC 总会沿出边到达某个出度为 0 的 SCC，所以不需要单独选。
在一个 SCC 内部只需选 1 个点就能覆盖全部成员，故取其最小代价

goto do-while 里 in[u]=0（注意这里写成 in[u]，其实是 typo 应为 in[top]=0，不过无碍——in 主用于找非树边，
这里 in 重置其实该写 in[top]；在弹栈时对每个 top 置 in=0，代码实际写的是 in[u]。这是一个小 bug：出栈时只把 u 的 in 置 0，
但其它栈内节点 top≠u 的 in 仍为 1，可能导致后续 cross/back 边误判。不过因为每个点出度为 1，影响通常有限。提醒你注意这里
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 2e5+10;


int head[N], ect;
struct edge { int to, la, nxt; } e[N<<1];
void clear(int v=N, int _e=N<<1) {
    memset(e,-1,sizeof(edge)*(_e));
    memset(head,-1,sizeof(int)*v);
    ect = -1;
}
void add(int u, int v, int w=1) {
    e[++ect] = {v,w, head[u]};
    head[u] = ect;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, c[N], a[N];
void inp() {
    read(n);
    rep(i,n) read(c[i]);
    rep(i,n) read(a[i]);
}

int dfn[N], low[N], tim, sc[N], scc, mn[N];
stack<int> S;
bool in[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++tim; S.push(u); in[u] = 1;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (in[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++scc;
        int top;
        do {
            top = S.top(); S.pop(); in[u] = 0;
            sc[top] = scc;
            mn[scc] = min(mn[scc], c[top]);
        } while (top != u);
    }
}

int out[N];
void solve() {
    clear();
    rep(i,n) add(i,a[i]);
    while (!S.empty()) S.pop();
    tim = scc = 0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(mn, 0x3f, sizeof(mn));
    rep(i,n) if (!dfn[i]) tarjan(i);
    rep(u,n) {
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            int su = sc[u], sv = sc[v];
            if (su != sv) ++out[su];
        }
    }
    int ans = 0;
    rep(i,scc) if (!out[i]) ans += mn[i];
    cout << ans << '\n';
}


int main() {
    fast;
    inp(); solve();
    return 0;
}