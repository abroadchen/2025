//
// Created by Psy.C on 2026/4/23.
//
/**
v：边指向的节点
w：边的权重
nxt：链表指针，指向同一起点的下一条边
tot：边的编号计数器
head[N]：每个节点的第一条边的编号
dp[i][j]：从起点到节点i，经过j步的最小距离
t：时间限制
path[i][j]：记录到达节点i的第j步时的前驱节点
从节点u开始，当前步数为k，父节点为fa
如果当前距离已经超过时间限制t，则剪枝返回
遍历u的所有邻接点v
如果通过u→v的路径更优（距离更小）：
更新dp[v][k+1]为更小的距离
记录路径path[v][k+1] = u
继续DFS搜索

输出最大步数ans
从终点n开始，利用path数组回溯路径
保存路径到数组a中
反向输出路径（从起点到终点）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5007, inf = 0x3f3f3f3f;
struct node { int v, w, nxt; } e[N<<1];

int tot, head[N];
void add(int u, int v, int w) {
    e[tot] = {v, w, head[u]}, head[u] = tot++;
}

int dp[N][N], t, path[N][N];
void dfs(int u, int fa, int k) {
    if (dp[u][k] >= t) return;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if (dp[v][k+1] > dp[u][k] + e[i].w) {
            dp[v][k+1] = dp[u][k] + e[i].w;
            path[v][k+1] = u;
            dfs(v, u, k+1);
        }
    }
}

int n, m, a[N];
int main() {
    fast;
    cin >> n >> m >> t;
    memset(head, -1, sizeof(head));
    memset(dp, inf, sizeof dp);
    for (int i = 0, u, v, w; i < m; ++i) {
        cin >> u >> v >> w; add(u, v, w);
    }
    dp[1][1] = 0; dfs(1, 1, 1);//从节点1开始，第一步的距离为0
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (dp[n][i] <= t) ans = i;//能到达终点n且时间不超过t的最大步数
    cout << ans << '\n';
    int p = n, cnt = 0;
    while (true) {
        a[cnt++] = p;
        if (p == 1) break;
        p = path[p][ans--];
    }
    for (int i = cnt-1; i >= 0; --i)
        cout << a[i] << (i==0?'\n':' ');
    return 0;
}