//
// Created by Psy.C on 2025/11/12.
//
/*
*to: 目标节点
r: 反向边在目标节点邻接表中的索引
c: 边的容量
 *
*g: 图的邻接表表示
lev: 节点层次数组（用于分层图）
it: 当前弧优化数组
n: 节点总数
 *初始化函数：设置节点数并分配内存空间
*添加边函数：
从u到v添加容量为w的边
同时添加反向边，容量为0
反向边索引用于后续增广路更新
*BFS构建分层图：
计算从源点s到各点的最短距离（层次）
只考虑还有容量的边
返回是否能到达汇点t
*DFS寻找增广路：
从节点u到汇点t寻找流量为f的增广路
只在分层图中前进（lev[e.to] == lev[u] + 1）
找到增广路后更新正向边和反向边的容量
*重复构建分层图并寻找增广路
累计最大流值
 *
 *设置源点st和汇点ed
 *
*读入每个节点的权值
构建源点到各节点的边，容量为inf-x
构建各节点到汇点的边，容量为inf
累计ans值用于后续计算
 *
*将每个节点i拆分为入点i和出点i+n
源点连接到每个入点，容量为inf-点权
每个出点连接到汇点，容量为inf
根据依赖关系连接入点和出点
*通过最大流最小割定理，将最小点权覆盖转化为最大流问题
最终答案 = 最大流 - Σ(inf - 点权)
 *
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define sz(x) ((int)(x).size())
using namespace std;

const int inf = 1e9, inf2 = 1e18;

struct Edge { int to, r, c; };
namespace Dinic {
    vector<vector<Edge>> g;
    vector<int> lev, it;
    int n = 0;

    void clear(int tot) {
        n = tot;
        g.assign(n + 5, {});
        lev.assign(n + 5, -1);
        it.assign(n + 5, 0);
    }
    void add(int u, int v, int w) {
        g[u].push_back({v, sz(g[v]), w});
        g[v].push_back({u, sz(g[u]) - 1, 0});
    }
    bool bfs(int s, int t) {
        fill(lev.begin(), lev.end(), -1);
        queue<int> q;
        lev[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& e : g[u]) {
                if (e.c > 0 && lev[e.to] < 0) {
                    lev[e.to] = lev[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return lev[t] >= 0;
    }
    int dfs(int u, int t, int f) {
        if (u == t) return f;
        for (int& i = it[u]; i < sz(g[u]); ++i) {
            Edge& e = g[u][i];
            if (e.c > 0 && lev[e.to] == lev[u] + 1) {
                int ret = dfs(e.to, t, min(f, e.c));
                if (ret > 0) {
                    e.c -= ret;
                    g[e.to][e.r].c += ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    int dinic(int s, int t) {
        int flow = 0, f;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while ((f = dfs(s, t, inf)) > 0) flow += f;
        }
        return flow;
    }
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, st, ed; cin >> n;
    st = n * 2 + 1; ed = st + 1;
    Dinic::clear(ed);
    for (int i = 1, cnt, x; i <= n; ++i) {
        cin >> cnt;
        while (cnt--) {
            cin >> x;
            Dinic::add(i, x + n, inf2);//从节点i向节点x+n添加大容量边
        }
    }
    int ans(0);
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        ans += inf - x;
        Dinic::add(st, i, inf - x);
        Dinic::add(i + n, ed, inf);
    }
    cout << Dinic::dinic(st, ed) - ans << '\n';
    return 0;
}