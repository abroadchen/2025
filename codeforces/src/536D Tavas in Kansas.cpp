//
// Created by Psy.C on 2026/3/4.
//
/**
n, m, s, t: 节点数、边数、起点、终点
val[N]: 每个节点的价值
f[N][N]: 邻接矩阵存储图
dis[N]: 从起点s到各点的最短距离
Dis[N]: 从终点t到各点的最短距离（反向）
vis[N]: Dijkstra算法中的访问标记
X, Y: 存储dis和Dis数组的离散化结果
S[N][N]: 二维前缀和，存储价值总和
T[N][N]: 二维前缀和，存储节点数量
dp[N][N][2]: 动态规划数组

读入m条边，构建无向图（f[x][y] = f[y][x]）
取最小值确保是最短边权
初始化距离数组
实现朴素Dijkstra算法找最短路径
找到未访问节点中距离最小的节点k
更新其他节点的最短距离
同样使用Dijkstra算法计算从t到所有点的最短距离
清空并填入dis和Dis数组的值
对X、Y进行排序
去除重复元素（离散化）

清零S、T、dp数组
将原始距离值映射到离散化后的索引
在对应位置累加价值和计数
计算S和T的二维前缀和数组
用于后续区间查询

从右下角向左上角进行动态规划
dp[i][j][0]: 表示第一个玩家在状态(i,j)下的最优分数
dp[i][j][1]: 表示第二个玩家在状态(i,j)下的最优分数
根据是否有节点存在决定转移方式

如果先手得分大于0，输出"Break a heart"
如果先手得分小于0，输出"Cry"
如果得分为0，输出"Flowers"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2009, inf = 0x3f;
constexpr ll INF = 1e18;

ll n, m, s, t, val[N], f[N][N], dis[N], Dis[N], vis[N];
vector<ll> X, Y;
ll S[N][N], T[N][N], dp[N][N][2];
int main() {
    fast;
    cin >> n >> m >> s >> t;
    for (ll i = 1; i <= n; ++i) cin >> val[i];
    memset(f, inf, sizeof(f));
    for (ll i = 1, x, y, z; i <= m; ++i) {
        cin >> x >> y >> z;
        f[x][y] = f[y][x] = min(z, f[x][y]);
    }
    memset(dis, inf, sizeof(dis));
    memset(Dis, inf, sizeof(Dis));
    dis[s] = Dis[t] = 0;
    memset(vis, 0, sizeof vis);
    for (ll i = 1; i <= n; ++i) {
        ll k = -1;
        for (ll j = 1; j <= n; ++j)
            if (!vis[j] && (dis[j] < dis[k] || k == -1)) k = j;
        vis[k] = 1;
        for (ll j = 1; j <= n; ++j)
            if (!vis[j] && f[k][j] < INF && dis[k]+f[k][j] < dis[j])
                dis[j] = dis[k] + f[k][j];
    }
    memset(vis, 0, sizeof vis);
    for (ll i = 1; i <= n; ++i) {
        ll k = -1;
        for (ll j = 1; j <= n; ++j)
            if (!vis[j] && (Dis[j] < Dis[k] || k == -1)) k = j;
        vis[k] = 1;
        for (ll j = 1; j <= n; ++j)
            if (!vis[j] && f[k][j] < INF && Dis[k]+f[k][j] < Dis[j])
                Dis[j] = Dis[k] + f[k][j];
    }
    X.clear(); Y.clear();
    for (ll i = 1; i <= n; ++i) X.push_back(dis[i]), Y.push_back(Dis[i]);
    ranges::sort(X), ranges::sort(Y);
    X.resize(ranges::unique(X).begin() - X.begin());
    Y.resize(ranges::unique(Y).begin() - Y.begin());
    memset(S, 0, sizeof S); memset(T, 0, sizeof T);
    memset(dp, 0, sizeof dp);
    for (ll i = 1; i <= n; ++i) {
        dis[i] = ranges::lower_bound(X, dis[i]) - X.begin() + 1;
        Dis[i] = ranges::lower_bound(Y, Dis[i]) - Y.begin() + 1;
        S[dis[i]][Dis[i]] += val[i], T[dis[i]][Dis[i]]++;
    }
    n++;
    for (ll i = 1; i <= n; ++i)
        for (ll j = 1; j <= n; ++j) {
            S[i][j] += S[i-1][j] + S[i][j-1] - S[i-1][j-1];
            T[i][j] += T[i-1][j] + T[i][j-1] - T[i-1][j-1];
        }
    for (ll i = n-1; i >= 0; --i)
        for (ll j = n-1; j >= 0; --j) {
            if (T[i+1][n] - T[i][n] - T[i+1][j] + T[i][j] == 0)
                dp[i][j][0] = dp[i+1][j][0];
            else
                dp[i][j][0] = max(dp[i+1][j][0], dp[i+1][j][1]) +
                    S[i+1][n] - S[i][n] - S[i+1][j] + S[i][j];
            if (T[n][j+1] - T[n][j] - T[i][j+1] + T[i][j] == 0)
                dp[i][j][1] = dp[i][j+1][1];
            else
                dp[i][j][1] = min(dp[i][j+1][1], dp[i][j+1][0]) -
                    S[n][j+1] + S[n][j] + S[i][j+1] - S[i][j];
        }
    if (dp[0][0][0] > 0) cout << "Break a heart\n";
    else if (dp[0][0][0] < 0) cout << "Cry\n";
    else cout << "Flowers\n";
    return 0;
}