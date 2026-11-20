//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
前向星邻接表，nxt、to、w
vis[u]==-1：u 在当前递归栈上（灰），再遇到 = 有环。
vis[u]>0：已处理完毕（黑），跳过。
从每个未访问点出发做 DFS，若发现环则返回真。
这是标准的三色标记判环（DFS 无向回边检测）
二分阈值 lim。若存在环（dfs 返回 1），说明阈值偏小（权重大于 lim 的边仍足以形成环）→ l = mid+1 提高阈值；否则 r = mid。
目标是找到"恰好破坏/保留"的临界阈值 l
仅对 w>lim 的边做拓扑排序，给每个点 dfn[u]（拓扑序号）。
若环存在，则环上节点无法出队（总有入度>0），dfn 会缺失
值得注意的是最终输出用的是 e[i].w <= l（权小于等于阈值 l 的边），且要求 dfn[to] < dfn[u]（目标点拓扑序在源点前面 → 形成反向边/回边）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

struct edge { int nxt, to, w; } e[N];

int cnt, head[N];
void add(int x, int y, int w) {
    e[++cnt] = {head[x], y, w}; head[x] = cnt;
}

int vis[N], lim;
bool dfs(int u, int id) {
    vis[u] = -1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int to = e[i].to;
        if (e[i].w <= lim) continue;//只走权重 > lim 的边
        if (vis[to] != -1 && vis[to]) continue;//已完成的点跳过
        if (vis[to] == -1 || dfs(to,id)) return 1;//遇"正在访问"=环 → 有环
    }
    vis[u] = id;//完成标记
    return 0;
}

int m, ct[N], n, dfn[N];
bool in[N];
void solve(int x) {
    queue<int> q;
    rep(i,m) if (e[i].w > lim) ct[e[i].to]++;
    rep(i,n) if (!ct[i]) q.push(i), in[i] = 1;
    int c = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        dfn[u] = ++c;
        for (int i = head[u]; i; i = e[i].nxt) {
            int to = e[i].to;
            if (e[i].w > lim) {
                ct[to]--;
                if (!ct[to] && !dfn[to] && !in[to])
                    in[to] = 1, q.push(to);
            }
        }
    }
}

int mx, ans[N], tot;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) {
        int x, y, w; cin >> x >> y >> w; add(x,y,w); mx = max(mx, w);
    }
    int l = 0, r = mx;
    while (l + 1 <= r) {
        int mid = (l+r)>>1; lim = mid; memset(vis,0, sizeof vis);
        rep(i,n) if (!vis[i] && dfs(i,i)) { l = mid+1; goto end; }
        r = mid;
        end:;
    }
    lim = l; solve(l);
    rep(u,n) for (int i = head[u]; i; i = e[i].nxt) {
        int to = e[i].to;
        if (e[i].w <= l) if (dfn[to] < dfn[u]) ans[++tot] = i;
    }
    cout << l << ' ' << tot << '\n';
    rep(i,tot) cout << ans[i] << ' ';
    return 0;
}