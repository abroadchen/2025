//
// Created by Psy.C on 2026/10/17.
//
/**
链式前向星存图（数组模拟邻接表）。
add(x,y,z)：加一条从 x 到 y、权值 z 的有向边，头插法。
边数组开到 N<<1（2倍）以容纳双向边
优先队列存 pair<距离, 节点>，小顶堆让距离最小的节点先出。
vis 记录节点是否已确定最短路，dis 存最短路
标准 Dijkstra：每次弹出距离最小的未确定节点，标记并 dis[x]=v，然后把它所有邻接点以 w+v 压入堆。
这里用 vis + 懒惰删除（重复入堆的旧距离节点被 continue 跳过）。
结束后输出 1..n 每个点的最短路。
注意：这是不判负权的最短路；且它不以固定起点开始——起点靠堆里预置的初始项决定（见 main），即多源 Dijkstra
读入 n 个点、m 条边；每条无向边两端加边，权值 ×2。
随后读入每个点的一个初始值 v[i]，把 (v[i], i) 全部压入堆作为初始起点（多源）。
dijkstra() 从这些多起点同时扩展，求每个点最终的最短路
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;

constexpr int N = 2e5+7;

ll head[N<<1], to[N<<1], w[N<<1], nxt[N<<1];
int tot;
void add(ll x, ll y, ll z) {
    to[++tot] = y; w[tot] = z; nxt[tot] = head[x]; head[x] = tot;
}

priority_queue<pll, vector<pll>, greater<>> q;
ll vis[N<<1], dis[N<<1];
int n;
void dijkstra() {
    while (!q.empty()) {
        auto [fst, snd] = q.top(); q.pop();
        ll x = snd, v = fst;//fst=距离, snd=节点
        if (vis[x]) continue;//已确定，跳过（懒惰删除）
        vis[x] = 1; dis[x] = v;//确定 x 的最短路
        for (ll i = head[x]; ~i; i = nxt[i]) {
            ll y = to[i];
            q.emplace(w[i]+v, y);//松弛：新距离=当前距离+边权
        }
    }
    for (int i = 1; i <= n; ++i) cout << dis[i] << ' ';
}

int m;
int main() {
    fast;
    tot = 0; memset(head, -1, sizeof head);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        ll x, y, z; cin >> x >> y >> z;
        add(x, y, z*2); add(y, x, z*2);
    }
    for (int i = 1; i <= n; ++i) {
        ll v; cin >> v;
        q.emplace(v, i);
    }
    dijkstra();
    return 0;
}