//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
链式前向星存有向图：head[u] 是 u 的第一条边下标，e[i] 是边终点，nxt[i] 是下一条边的下标
dfs(s) 标记所有从 s 出发可达的点，vis[]=1。这些点已经满足条件，无需处理
in[] 记录某次扫描的访问标记（用 now 作为本轮戳，避免清空数组），vis[] 表示已可达 s 的点，跳过。
dfs2(u) 从某个未可达点 u 出发，沿有向边扩展，统计这块区域里尚未被 s 到达的点个数，返回块大小 sum
对所有还没 reachable 的点，分别 dfs2 统计其所在游离块大小 cur，记住最大块的大小 mx 和代表点 num。
若 mx==0（没有更多可处理的未达点）→ 结束。
否则 ans++（新增一条边连入这块），然后 dfs(num) 把这块整体标记为可达（模拟新加的这条边让 s 能到达全部该块）
输出 ans，即最少新增有向边数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 5e3+7;

int e[N<<1], nxt[N<<1], head[N], cnt;
void add(int l, int r) {
    e[++cnt] = r; nxt[cnt] = head[l]; head[l] = cnt;
}

int vis[N];
void dfs(int u) {
    vis[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = e[i];
        if (vis[v] == 1) continue;
        dfs(v);
    }
}

int in[N], now;
int dfs2(int u) {
    int sum = 1; in[u] = now;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = e[i];
        if (in[v] == now || vis[v]) continue;
        sum += dfs2(v);
    }
    return sum;
}

int n, m, s;
int main() {
    fast;
    cin >> n >> m >> s;
    for (int i = 0, l, r; i < m; i++) {
        cin >> l >> r; add(l, r);
    }
    int ans = 0, mx = 0, num = -1; dfs(s);
    while (true) {
        for (int i = 1; i <= n; i++) {
            if (vis[i] == 1) continue;
            now++;
            int cur = dfs2(i);
            if (num == -1 || mx < cur) { mx = cur; num = i; }
        }
        if (mx == 0) break;
        ans++;
        dfs(num); mx = 0;
    }
    cout << ans << '\n';
    return 0;
}