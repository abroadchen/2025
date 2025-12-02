//
// Created by Psy.C on 2025/12/2.
//
/*
 *n为节点数，m为边数
*nxt: 下一条边的索引
to: 邻接点
e数组大小为2*N（因为是无向图）
*ele: 边计数器，初始为1（因为使用异或操作）
head[N]: 邻接表头数组
deg[N]: 每个节点的度数
 *使用ele自增确保相邻的边索引相差1，便于异或操作
*dfn[N]: 时间戳数组
low[N]: 能够回溯到的最小时间戳
tim: 时间戳计数器
 *
*如果v无法回到u或u的祖先，则边(u,v)是桥
使用异或操作同时标记两条有向边
 *
*vis[N]: 访问标记数组
cnt: 连通分量计数器
ans: 答案计数器
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define sz(x) (static_cast<int>((x).size()))
using namespace std;

constexpr int N = 5e5+5;
int n, m;
struct edge { int nxt, to; } e[N<<1];

int ele=1, head[N], deg[N];
void add(const int u, const int v) {
    e[++ele] = {head[u], v}, head[u] = ele;
    e[++ele] = {head[v], u}, head[v] = ele;
    deg[u]++, deg[v]++;
}

int dfn[N], low[N], tim;
bool bd[N<<1];
void tarjan(const int u, const int fa) {//寻找桥边
    dfn[u] = low[u] = ++tim;
    for (int i = head[u], v; v = e[i].to, i; i = e[i].nxt) {
        if (!dfn[v]) {//如果v未被访问过
            tarjan(v, u), low[u] = min(low[u], low[v]);//递归访问v，更新u的low值
            if (low[v] > dfn[u]) bd[i] = bd[i^1] = true;//bridge数组，用于标记桥边
        } else if (v^fa) low[u] = min(low[u], dfn[v]);//如果v已访问且不是父节点
    }
}

bool vis[N]; int cnt, ans;
vector<int> c[N];//存储每个连通分量的节点
void dfs(const int u) {//找出连通分量
    vis[u] = true; c[cnt].push_back(u);//加入当前连通分量
    for (int i = head[u], v; v = e[i].to, i; i = e[i].nxt) {
        if (!bd[i] && !vis[v]) dfs(v);
    }
}


int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v; add(u, v);
    }
    if (!m) return cout << "0 0" << '\n', 0;
    rep(i,n) tarjan(i, 0);//对每个节点运行tarjan算法找桥
    rep(i,n) if (!vis[i]) cnt++, dfs(i);//找出所有连通分量
    if (cnt == 1) return cout << "1 " << m << '\n', 0;//如果只有一个连通分量，输出"1"和边数
    rep(i,n) ans += deg[i] & 1; ans >>= 1;//统计奇度节点数并除以2（每条边贡献两个度数）
    for (int i = 1, t; t = 0, i <= cnt; ++i) {//遍历每个连通分量
        if (sz(c[i]) != 1) {//连通分量不止一个节点
            for (int j = 0; j < sz(c[i]); ++j)
                t += deg[c[i][j]] >= 3;
            ans += t <= 1;//统计度数>=3的节点数，如果<=1则ans加1
        }
    }
    cout << ans << ' ' << m << '\n';
    return 0;
}