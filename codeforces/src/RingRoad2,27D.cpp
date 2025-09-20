//
// Created by Psy.C on 2025/9/20.
//
/*
 *创建数组a存储边的信息，最多N条边
*h[N]: 邻接表，用于存储图的连接关系
vis[N]: 访问标记数组，记录节点是否被访问过
flag: 标记是否存在奇环（非二分图标志）
col[N]: 颜色数组，用于二分图染色
 *
*参数：u(当前节点)、fa(父节点)、color(当前颜色)
如果已检测到非二分图(flag=1)，直接返回
标记当前节点已访问，并设置颜色
遍历当前节点的所有邻接点：
跳过父节点
如果邻接点已访问且颜色相同，说明存在奇环，标记flag=1
如果邻接点已访问但颜色不同，继续
如果邻接点未访问，递归调用DFS，颜色取反(color^1)
 *
 *
*相交条件：
第一种情况：边i的左端点在边j内部，右端点在边j右侧
第二种情况：边i的右端点在边j内部，左端点在边j左侧
在相交的边之间建立无向连接
 *
 *
 *对所有未访问的节点进行DFS，进行二分图染色判断
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 2e5+10;

struct edge {
    int l, r;
} a[N];

vector<int> h[N];
int vis[N], flag = 0, col[N];

void dfs(int u, int fa, int color) {
    if (flag == 1) return;
    vis[u] = 1;
    col[u] = color;
    for (auto v : h[u]) {
        if (v == fa) continue;
        if (vis[v] && col[v] == col[u]) { flag = 1; return ; }
        if (vis[v]) continue;
        dfs(v, u, color ^ 1);
    }
}

void solve() {
    int n, m; cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        if (u > v) swap(u, v);
        a[i].l = u; a[i].r = v;
    }

    for (int i = 1; i < m; ++i)
        for (int j = i + 1; j <= m; ++j) {
            if ((a[i].l > a[j].l && a[i].l < a[j].r && a[i].r > a[j].r) ||
                (a[i].r > a[j].l && a[i].r < a[j].r && a[i].l < a[j].l)) {
                h[i].push_back(j);
                h[j].push_back(i);
            }
        }

    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i, 0, 1);

    if (flag) { cout << "Impossible" << endl; return ; }
    for (int i = 1; i <= m; ++i) {
        if (col[i] == 0) cout << "o";
        else cout << "i";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int T = 1;
    while (T--) solve();
    
    return 0;
}