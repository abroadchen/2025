//
// Created by Psy.C on 2025/11/24.
//
/*
*N = 210：网格最大尺寸
M = 1<<7：状态数最大值（最多7个关键点）
inf = 1<<30：无穷大值
K = 1e3：用于编码pre数组的基数
*n, m, k：网格行数、列数、关键点数量
maz[N][N]：存储网格权值
nn, mm：nn=n*m（总格子数），mm=1<<k（状态总数）
hsh[N]：存储每个格子的关键点状态
vis[N][M]：访问标记数组
dp[N][M]：动态规划数组，dp[i][state]表示到达位置i且收集状态为state的最小代价
pre[N][M]：前驱数组，用于路径回溯
dx[], dy[]：四个方向的坐标偏移（左、右、上、下）
g[N][N]：输出网格
 *
*更新函数：如果找到更优解则更新dp值并加入队列
x：当前位置
dis：当前状态
w：新的权重值
fa：前驱状态编码
 *
*DFS回溯函数：根据pre数组重构路径
t：当前位置编码
dis：当前状态
 *
 *SPFA算法主体：处理队列中的节点
 *四个方向的移动：向相邻格子扩展
 *状态合并操作：枚举所有子集进行状态转移
 *输出结果：找到最优解并回溯路径
 *
 *时间复杂度：O(n×m×2^k×(n×m+k))
 *
*状态A：已经收集了关键点集合i
状态B：已经收集了关键点集合dis
现在想要得到状态i|dis（两个集合的并集
 *
 *cur * K + dis 是一个状态编码的技术，
 *用于将两个整数信息编码成一个唯一的整数
 *mm - 1 = 2^k - 1 的二进制表示为 111...1（k个1）
 *这表示所有k个关键点都已被收集
 *
 *diss - dis 表示前驱状态中有但当前状态中没有的关键点集合
 *是否 diss 包含了比 dis 更多的关键点
 *dis - diss 实际上是在计算 dis & (~diss)（dis中有但diss中没有的位）
 *
 */
#include <queue>
#include <iostream>
#include <cstring>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

constexpr int N = 210, M = 1 << 7, inf = 1 << 30, K = 1e3;
int n, m, k, maz[N][N], nn, mm,
hsh[N], vis[N][M], dp[N][M], pre[N][M],
dx[] = {0,0,-1,1}, dy[] = {-1,1,0,0};
char g[N][N];

struct node { int x, dis; };//位置x和状态dis
queue<node> q;
void change(const int x, const int dis, const int w, const int fa) {
    if (dp[x][dis] > w) {
        dp[x][dis] = w; pre[x][dis] = fa;
        if (!vis[x][dis]) {
            q.push({x, dis});
            vis[x][dis] = 1;
        }
    }
}

bool ok(const int x, const int y) {
    if (x >= 0 && x < n && y >= 0 && y < m) return true;
    return false;
}

void dfs(const int t, const int dis) {
    const int x = t / m, y = t % m;
    g[x][y] = 'X';
    if (pre[t][dis] == -1) return;
    const int to = pre[t][dis] / K, diss = pre[t][dis] % K;
    dfs(to, diss);
    if (diss - dis) dfs(to, dis - diss);
}

void get() {
    while (!q.empty()) {
        const node p = q.front(); q.pop();
        const int cur = p.x, x = p.x / m, y = p.x % m, dis = p.dis;
        vis[cur][dis] = false;
        rep(i,4) {
            const int tx = x + dx[i], ty = y + dy[i];
            if (!ok(tx, ty)) continue;
            const int to = tx * m + ty;
            change(to, dis,
                dp[cur][dis] + maz[tx][ty],
                cur * K + dis);
        }
        const int t = mm - dis - 1;
        for (int i = t; i; i = (i - 1) & t) change(cur, i|dis,
            dp[cur][i] + dp[cur][dis] - maz[x][y],
            cur * K + dis);
    }
    int ans = inf, now = 0;
    rep(i,nn) if (ans > dp[i][mm-1]) { ans = dp[i][mm-1], now = i; }
    dfs(now, mm - 1);
    cout << ans << '\n';
    rep(i,n) { rep(j,m) cout << g[i][j]; cout << '\n'; }
}

int main() {
    ostream::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> k;
    rep(i,n) rep(j,m) { cin >> maz[i][j]; g[i][j] = '.'; }
    nn = n * m; mm = 1 << k;
    memset(hsh, 0, sizeof(hsh)); memset(vis, 0, sizeof(vis));
    rep(i,nn) rep(j,mm) dp[i][j] = inf;
    rep(i,k) {
        int u, v; cin >> u >> v; u--; v--;
        const int id = u * m + v;
        hsh[id] = 1 << i;
        change(id, hsh[id], maz[u][v], -1);
    }
    get();
    return 0;
}