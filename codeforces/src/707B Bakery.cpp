//
// Created by Psy.C on 2026/4/19.
//
/**
v[N]: 边的终点
nxt[N]: 链式前向星的next指针
w[N]: 边的权重
head[N]: 邻接表头节点
cnt: 边的计数器
add: 添加无向边（添加双向边）
vis[N]: 标记数组，标记特殊点
head初始化为-1（表示无邻接点）
cnt = 1: 从1开始计数（便于判断边界）
n: 节点数
m: 边数
k: 特殊点数
输入k个特殊点
标记这些点为特殊点

遍历每个特殊点:
遍历特殊点的所有邻接边:
检查邻接点是否为非特殊点
v[j]: 邻接点
!vis[v[j]]: 如果不是特殊点
更新最小边权
如果没找到连接，输出-1
否则输出最小边权
O(M): 遍历所有边一次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+7;

int v[N], nxt[N], w[N], head[N], cnt;
void add(int fr, int to, int cost) {
    v[cnt] = to; nxt[cnt] = head[fr]; w[cnt] = cost; head[fr] = cnt++;
}

bool vis[N];
void init() {
    memset(head, -1, sizeof(head));
    cnt = 1;
    memset(vis, 0, sizeof(vis));
}

int n, m, k, st[N];
int main() {
    fast;
    cin >> n >> m >> k; init();
    for (int i = 0, a, b, c; i < m; ++i) {
        cin >> a >> b >> c;
        add(a, b, c); add(b, a, c);
    }
    for (int i = 0; i < k; ++i) {
        cin >> st[i]; vis[st[i]] = 1;
    }
    ll ans = INT_MAX;
    for (int i = 0; i < k; ++i)
        for (int j = head[st[i]]; j != -1; j = nxt[j])
            if (!vis[v[j]])
                ans = min(ans, (ll)w[j]);
    cout << (ans == INT_MAX ? -1 : ans) << '\n';
    return 0;
}