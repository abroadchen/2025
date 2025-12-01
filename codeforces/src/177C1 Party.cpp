//
// Created by Psy.C on 2025/11/30.
//
/*
*x: 当前节点
g: 图的邻接表表示
vis: 访问标记数组
e: 存储连通分量的向量
 */
#include <iostream>
#include <set>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vector<int>>
#define ii pair<int,int>
using namespace std;

void dfs(const int x, const vvi& g, vb& vis, vi& e) {
    if (vis[x]) return;
    vis[x] = true; e.push_back(x);//将节点x加入当前连通分量
    for (int i = 0; i < static_cast<int>(g[x].size()); ++i) {//遍历节点x的所有邻居节点
        const int u = g[x][i];//获取当前邻居节点u
        if (vis[u]) continue;
        dfs(u, g, vis, e);
    }
}


int main() {
    fast;
    int n; cin>>n;//读取节点数量n
    vvi g(n); int k; cin>>k;//读取边的数量k
    for (int i = 0, x, y; i < k; ++i) {
        cin>>x>>y; --x; --y;
        g[x].push_back(y); g[y].push_back(x);//在邻接表中添加无向边
    }
    int m; cin>>m;//读取禁止边的数量m
    set<ii> h;//存储禁止的节点对
    for (int i = 0, x, y; i < m; ++i) {
        cin>>x>>y; --x; --y;
        h.insert({x, y}); h.insert({y, x});//无向图，需要插入两个方向
    }
    vb vis(n, false); int mx = 0;//最大连通分量
    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        vi cmp; dfs(i, g, vis, cmp);//创建新的连通分量向量cmp 找出完整的连通分量
        bool flag = true;//表示当前连通分量是否有效
        for (int a = 0; a < static_cast<int>(cmp.size()); ++a) {//遍历连通分量中的每个节点
            if (!flag) break;//如果已经发现无效边
            for (int b = a + 1; b < static_cast<int>(cmp.size()); ++b) {//检查该节点与其他所有节点之间是否有禁止边
                ii t = {cmp[a], cmp[b]};//创建节点对
                if (h.count(t) > 0) { flag = false; break; }//如果该节点对在禁止集合中
            }
        }
        //如果当前连通分量有效且大小大于等于当前最大值，更新最大值
        if (flag && static_cast<int>(cmp.size()) >= mx) mx = static_cast<int>(cmp.size());
    }
    cout << mx << '\n';
    return 0;
}