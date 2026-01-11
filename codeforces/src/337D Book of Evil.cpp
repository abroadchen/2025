//
// Created by Psy.C on 2026/1/11.
//
/**
* vis：标记哪些节点是特殊节点
dp[u][0]：未使用（初始化时被设为负无穷）
`dp[u][1]：从节点u向下延伸的最长路径长度
`dp[u][2]：从节点u向下延伸的次长路径长度
 *
*从根节点开始进行树形DP
如果当前节点是特殊节点，将其dp值设为0
遍历所有子节点，更新当前节点的最长和次长路径
这样计算出每个节点向下能达到的最远距离
 *
*dis[v]：从节点v向上（通过父节点）能达到的最远距离
如果子节点v参与了父节点u的最长路径，则使用次长路径更新
否则使用最长路径更新
这样计算出每个节点向上能达到的最远距离
 *
*要求找出树中有多少个节点，使得从这些节点出发，到任意特殊节点的距离都不超过d
通过两次DFS，分别计算向下和向上的最远距离，然后判断每个节点是否满足条件
算法时间复杂度为O(n)，空间复杂度为O(n)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100011
using namespace std;

struct node { int v, nxt; } e[N<<1];//邻接点和下一个边的索引
int cnt=1, head[N];
void add(const int u, const int v) {
    e[cnt] = {v, head[u]};
    head[u] = cnt++;
}

int vis[N], dp[N][3];
void dfs(const int fa, const int u) {
    if (vis[u]) dp[u][1] = dp[u][0] = 0;
    for (int i = head[u]; i; i = e[i].nxt) if (fa != e[i].v) {
        const int v = e[i].v;
        dfs(u, v);
        if (dp[v][1] + 1 > dp[u][1]) {
            dp[u][2] = dp[u][1];
            dp[u][1] = dp[v][1] + 1;
        } else dp[u][2] = max(dp[u][2], dp[v][1] + 1);
    }
}

int dis[N];
void dfs2(const int fa, const int u) {
    for (int i = head[u]; i; i = e[i].nxt) if (fa != e[i].v) {
        const int v = e[i].v;
        if (dp[u][1] == dp[v][1] + 1) dis[v] = max(dis[u] + 1, dp[u][2] + 1); else {
            dis[v] = max(dis[u] + 1, dp[u][1] + 1);
        }
        dfs2(u, v);
    }
}

int main() {
    fast;
    memset(head, 0, sizeof(head));
    memset(dp, 128, sizeof(dp));//设置为负无穷
    memset(dis, 128, sizeof(dis));
    int n, m, d; cin >> n >> m >> d;
    for (int i = 1, x; i <= m; ++i) { cin >> x; vis[x] = 1; }//标记特殊节点
    for (int i = 1, u, v; i <= n - 1; ++i) { cin >> u >> v; add(u, v); add(v, u); }
    dfs(0, 1); dfs2(0, 1);
    int ans = 0;
    for (int i = 1; i <= n; ++i) if (dp[i][1] <= d && dis[i] <= d) ans++;
    cout << ans << '\n';
    return 0;
}