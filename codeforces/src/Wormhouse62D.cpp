//
// Created by Psy.C on 2025/10/29.
//
/*
 *
*n, m: 图中的节点数和边的数量。
a[N]: 存储路径序列。
vis[N]: 标记访问状态的数组。
g[N]: 每个节点的邻接表，存储的是 {相邻节点, 边编号} 对。
t: 临时存储DFS遍历结果的向量。
 *
*DFS函数用于深度优先搜索图结构：
参数 v 是当前访问的节点，x 是限制条件（只有当邻居节点大于 x 才能继续搜索）。
遍历当前节点的所有邻居 (u, i)，其中 u 是邻居节点，i 是连接它们的边编号。
如果满足 u > x 并且该边未被访问过，则标记该边已访问并递归进入下一个节点。
最后将当前节点压入栈 t 中（逆序记录访问顺序）
 *
 *
*逆序尝试不同的起点 a[i] 来构造完整路径：
清空访问标记数组，并初始化前 i-1 条边为已访问。
清空临时路径 t，然后从 a[i] 开始执行一次受限的 DFS。
判断是否能够形成完整的路径（总长度等于原始路径长度）。
若成功则反转 t 得到正确顺序，并输出组合后的完整路径。
 *
 */
#include <cstring>
#include <iostream>
#include <vector>
#define rep(i,n) for(int i=1;i<=(n);++i)
#define rep1(i,n) for(int i=1;i<(n);++i)
#define repd(i,n) for(int i=(n);i>=1;--i)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const ll N = 2009;
int n, m, a[N], vis[N];
vector<pii> g[N];
vector<int> t;

void dfs(int v, int x) {
    for (auto [u, i] : g[v]) {
        if (u > x && !vis[i]) {
            vis[i] = 1;
            dfs(u, 0);
        }
    }
    t.push_back(v);
}


int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;
    rep(i,m+1) cin >> a[i];
    rep(i,m) {//将路径上的每两个连续节点之间建立双向连接，并记录对应的边编号
        int u = a[i], v = a[i+1];
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    //对每个节点的邻接链表进行排序，确保后续遍历时按顺序处理
    rep(i,n) sort(g[i].begin(), g[i].end());
    repd(i,m) {
        memset(vis, 0, sizeof(vis));
        rep1(j,i) vis[j] = 1;
        t.clear();
        dfs(a[i], a[i + 1]);
        if (i + t.size() - 1 == m + 1) {
            reverse(t.begin(), t.end());
            rep1(j,i) cout << a[j] << ' ';
            for (int u : t) cout << u << ' ';
            cout << '\n';
            return 0;
        }
    }
    cout << "No solution\n";
    return 0;
}