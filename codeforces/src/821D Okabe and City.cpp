//
// Created by Psy.C on 2026/9/23.
//
/**
读入网格尺寸 n, m 和特殊点数量 k。
读入 k 个特殊点的坐标 (a[i], b[i])。
记录是否有点恰好位于终点 (n, m)，记为 lst。
若没有点正好在终点 (n,m)，则追加一个虚拟点 (n+1, m+1)（右下方越界一格）作为新的终点，这也解释了为什么要 n+1,m+1

从点 1（起点，对应 (1,1) 大致）出发跑 SPFA 最短路。
对每个点 now，遍历其它每个点 i，计算两点间距离：
dx = |x - a[i]|, dy = |y - b[i]|。
边权判定：
dx + dy == 1（曼哈顿距离为 1，相邻）→ 边权 w = 0（免费/无需步数）。
dx <= 2 || dy <= 2（某一方向距离不超过 2）→ 边权 w = 1（可一步到达）。
否则 w = inf（无法直接到达，需其它中转）。
用松弛更新 f[i]，标准 SPFA 队列优化
到终点 lst 的最短路若为无穷，则不可达，输出 -1；否则输出最短路值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e4+5, inf = 1e15;

int k, f[N];
void init() { for (int i = 1; i <= k; ++i) f[i] = inf; }

bool vis[N];
queue<int> q;
int a[N], b[N];
void spfa() {
    init(); f[1] = 0, vis[1] = 1; q.push(1);
    while (!q.empty()) {
        int now = q.front(), x = a[now], y = b[now]; q.pop(); vis[now] = 0;
        for (int i = 1; i <= k; ++i) {
            if (i == now) continue;
            int dx = abs(x-a[i]), dy = abs(y-b[i]), w = 0;
            if (dx + dy == 1) w = 0;
            else if (dx <= 2 || dy <= 2) w = 1;
            else w = inf;
            if (f[i] > f[now] + w) {
                f[i] = f[now] + w;
                if (vis[i] == 0) { vis[i] = 1; q.push(i); }
            }
        }
    }
}

int n, m, lst;
signed main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= k; ++i) {
        cin >> a[i] >> b[i];
        if (a[i] == n && b[i] == m) lst = i;
    }
    if (lst == 0) k++, a[k] = n+1, b[k] = m+1, lst = k;
    spfa();
    if (f[lst] == inf) cout << "-1\n";
    else cout << f[lst] << '\n';
    return 0;
}