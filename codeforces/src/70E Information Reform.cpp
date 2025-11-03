//
// Created by Psy.C on 2025/11/3.
//
/*
*n: 节点数量
k: 常数k
dis[N][N]: 节点间距离矩阵
d[N]: 距离数组
to[N<<1]: 链式前向星的终点数组
cnt(1): 边的计数器，初始为1
nxt[N<<1]: 链式前向星的下一条边
head[N]: 链式前向星的头指针数组
dp[N][N]: 动态规划数组
f[N]: 结果数组
 *
 *三维数组，用于存储动态规划的前驱节点信息
 *
*添加无向边的函数，使用链式前向星存储图结构
将边b添加到a的邻接表中
 *
 *深度优先搜索函数，s为当前节点，f为父节点
 *初始化dp数组：对于节点s选择颜色x的代价是k加上与节点x的距离代价
 *遍历当前节点s的所有子节点
 *递归处理子节点
*对于每个颜色x，计算子节点y的最小贡献
如果子节点选择与当前节点相同的颜色，可以节省k的代价
记录最优选择的前驱节点
 *
*第二次DFS，根据pre数组构建最终解
将节点s的颜色设置为t，并递归处理子节点
 *
*找到根节点选择每种颜色的最小代价
根据最优解进行第二次DFS构建完整解
 *输出最小代价和每个节点的颜色选择
 */
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 210, inf = 1e18;
int n, k, dis[N][N], d[N],
to[N<<1], cnt(1), nxt[N<<1], head[N],
dp[N][N], f[N];
vector<array<int, 2>> pre[N][N];

void add(int a, int b) {
    to[cnt] = b;
    nxt[cnt] = head[a];
    head[a] = cnt++;
}


void dfs(int s, int f) {
    for (int x = 1; x <= n; ++x) dp[s][x] = k + d[dis[s][x]];
    for (int i = head[s]; i; i = nxt[i]) {
        int y = to[i];
        if (y == f) continue;
        dfs(y, s);
        for (int x = 1; x <= n; ++x) {
            int tp = inf, u, v;
            for (int j = 1; j <= n; ++j) {
                int tk = dp[y][j];
                if (x == j) tk -= k;
                if (tk < tp) {
                    tp = tk;
                    u = y;
                    v = j;
                }
            }
            dp[s][x] += tp;
            pre[s][x].push_back({u, v});
        }
    }
}

void dfs2(int s, int t) {
    f[s] = t;
    for (auto [x, y] : pre[s][t]) {
        dfs2(x, y);
    }
}


void solve() {
    cin >> n >> k;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n; ++i) dis[i][i] = 0;//设置对角线距离为0（自己到自己的距离）
    for (int i = 1; i < n; ++i) cin >> d[i];
    for (int i = 1; i < n; ++i) {
        int a, b; cin >> a >> b;
        add(a, b); add(b, a);
        dis[a][b] = dis[b][a] = 1;//设置相邻节点间距离为1
    }
    for (int x = 1; x <= n; ++x) {//计算所有节点对之间的最短距离
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dis[i][j] = min(dis[i][j], dis[i][x] + dis[x][j]);
            }
        }
    }
    dfs(1, 0);
    int ans(inf);
    for (int i = 1; i <= n; ++i) ans = min(ans, dp[1][i]);
    for (int i = 1; i <= n; ++i) if (ans == dp[1][i]) {
        dfs2(1, i);
        break;
    }
    cout << ans << endl;
    for (int i = 1; i <= n; ++i) cout << f[i] << ' ';
    cout << endl;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
    return 0;
}