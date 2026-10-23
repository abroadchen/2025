//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
使用链式前向星（数组模拟邻接表）存储无向图。
add(u,v)：头插法，把边 u→v 挂到 u 的邻接链上。由于无向，主函数里会调两次（u→v 和 v→u）
sz[u] 记录以 u 为根的子树节点数（以 1 为整棵树根）。
初始 sz[now]=1（自身）。
遍历邻接边，跳过父节点 fa，递归处理每个儿子，并把儿子子树大小累加进来。
标准树形 DFS
读入 n。
if (n%2) 输出 -1：若节点总数为奇数则直接判无解（偶数棵子树无法两两配对，推测题意为"能否把树切成若干大小为偶数的部分"之类，奇数必然不行，故特判）。
读入 n-1 条边，双向建边。
dfs(1,0)：从根 1 出发求所有子树大小。
遍历所有节点，统计子树大小为偶数（sz[i]%2==0）的节点个数 ans。
输出 ans - 1
最多切分成的偶数大小连通块数 =（偶数子树节点数）- 1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5;

int cnt, head[N], nxt[N], to[N];
void add(int u, int v) {
    to[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}

int sz[N];
void dfs(int now, int fa) {
    sz[now] = 1;
    for (int i = head[now]; i; i = nxt[i]) {
        if (to[i] != fa) {
            dfs(to[i], now);
            sz[now] += sz[to[i]];
        }
    }
}

int n, ans;
int main() {
    fast;
    cin >> n;
    if (n%2) { cout << "-1"; return 0; }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v; add(u, v); add(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        if (sz[i]%2 == 0) ans++;
    cout << ans-1;
    return 0;
}