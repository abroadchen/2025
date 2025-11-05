//
// Created by Psy.C on 2025/11/5.
//
/*
*nx: 目标节点
back: 反向边在邻接表中的索引
c: 边的容量
*n: 节点数
adjlist: 邻接表存储图
lev: 层次数组（用于分层图）
u2c: 当前弧优化数组
*添加从u到v容量为c的边
同时添加反向边，容量为0
*BFS构建分层图：

从源点s开始广度优先搜索
为可达节点分配层次（距离）
用于Dinic算法的分层图构建
*增广路径搜索：

从节点u寻找到汇点t的增广路径
使用当前弧优化避免重复搜索
找到路径后更新残量网络
*Dinic算法主函数：

重复构建分层图并寻找增广路径
直到无法找到增广路径为止
返回最大流值
 *
*N = 15: 网格大小
cnt[N][N]: 存储到达每个点的最短时间
fx[2][4]: 四个方向的坐标偏移（上下左右）
a[N], b[N]: 两个网格图
vis[N][N]: 访问标记数组
*DFS1函数：计算从Z点出发到达各点的最短时间

边界检查和障碍检查
更新到达时间
向四个方向递归搜索
*DFS2函数：在时间限制内搜索可达的目标点

检查边界、障碍和访问状态
如果找到有效目标点，添加网络流边
继续向四个方向搜索
 *
 *
*对所有Z点运行DFS1计算最短时间
处理源点和汇点：
对于a图中的数字点，连接到源点S
对于b图中的数字点，连接到汇点T
运行Dinic算法计算最大流
输出结果
 *
 */
#include <ios>
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#define sz(x) ((int)(x).size())
#define rep(i,n) for (int i=1; i<=(n); ++i)
using namespace std;

typedef long long ll;
const ll inf = 1e18;

struct flow {
    struct edge {
        int nx, back;
        ll c;
    };
    int n;
    vector<vector<edge>> adjlist;
    vector<int> lev, u2c;
    flow(int _n) : n(_n) {
        adjlist.resize(n);
        lev.resize(n);
        u2c.resize(n);
    }
    void add_edge(int u, int v, ll c) {
        adjlist[u].push_back({v, sz(adjlist[v]), c});
        adjlist[v].push_back({u, sz(adjlist[u]) - 1, 0});
    }
    bool bfs(int s, int t) {
        fill(lev.begin(), lev.end(), -1);
        queue<int> q;
        q.push(s);
        lev[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            u2c[u] = 0;
            for (edge& e : adjlist[u]) {
                if (lev[e.nx] == -1 && e.c > 0) {
                    lev[e.nx] = lev[u] + 1;
                    q.push(e.nx);
                }
            }
        }
        return lev[t] != -1;
    }
    ll augment(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = u2c[u]; i < sz(adjlist[u]); ++i) {
            edge& e = adjlist[u][i];
            if (lev[e.nx] == lev[u] + 1 && e.c > 0) {
                ll rf = augment(e.nx, t, min(f, e.c));
                if (rf > 0) {
                    e.c -= rf;
                    adjlist[e.nx][e.back].c += rf;
                    return rf;
                }
            }
        }
        lev[u] = -1;
        return 0;
    }
    ll dinic(int s, int t) {
        ll res(0);
        while (bfs(s, t)) {
            while (ll x = augment(s, t, inf)) res += x;
        }
        return res;
    }
};

const int N = 15, INF = 1e9;
int n, t, cnt[N][N],
fx[2][4] = {
    {1,-1,0,0},
    {0,0,1,-1}
};
string a[N], b[N];
bool vis[N][N];

void dfs1(int x, int y, int tm) {
    if (x < 1 || y < 1 || x > n || y > n || a[x][y] == 'Y' ||
        tm > cnt[x][y]) return;
    cnt[x][y] = tm;
    for (int i = 0; i < 4; ++i) dfs1(x + fx[0][i], y + fx[1][i], tm + 1);
}

void dfs2(int id, int x, int y, int tm, flow& fn) {
    if (x < 1 || y < 1 || x > n || y > n || a[x][y] == 'Y' ||
        a[x][y] == 'Z' || vis[x][y]) return;
    if ('1' <= b[x][y] && b[x][y] <= '9' &&
        tm <= cnt[x][y] && tm <= t) {
        int target = x * n + y + n * n;
        fn.add_edge(id, target, inf);
    }
    if (tm >= cnt[x][y] || tm >= t) return;
    vis[x][y] = true;
    for (int i = 0; i < 4; ++i) dfs2(id, x + fx[0][i], y + fx[1][i], tm + 1, fn);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> t; t++;
    const int S = 0, T = 1e4;
    flow fn(T + 1);
    rep(i,n) { cin >> a[i]; a[i] = ' ' + a[i]; }
    rep(i,n) {
        cin >> b[i]; b[i] = ' ' + b[i];
        rep(j,n) cnt[i][j] = INF;
    }
    rep(i,n) rep(j,n) if (a[i][j] == 'Z') dfs1(i, j, 1);
    rep(i,n) rep(j,n) {
        if ('1' <= a[i][j] && a[i][j] <= '9') {
            int val = a[i][j] - '0', from = i * n + j;
            fn.add_edge(S, from, val);
            memset(vis, 0, sizeof(vis));
            dfs2(from, i, j, 1, fn);
        }
        if ('1' <= b[i][j] && b[i][j] <= '9') {
            int val = b[i][j] - '0', to = i * n + j + n * n;
            fn.add_edge(to, T, val);
        }
    }
    ll ans = fn.dinic(S, T);
    cout << ans << '\n';
    return 0;
}