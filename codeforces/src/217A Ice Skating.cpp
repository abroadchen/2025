//
// Created by Psy.C on 2025/12/7.
//
/*
*v：存储点坐标的向量，每个元素是一个pair<int,int>表示(x,y)坐标
vis：访问标记向量，记录每个点是否已被访问
 *
*查找连通分量：
u：当前访问的点的索引
n：总点数
将当前点标记为已访问
遍历所有点，如果找到未访问且与当前点在同一行或同一列的点，则递归访问
*v[u].first == v[i].first：两点x坐标相同（同一垂直线）
v[u].second == v[i].second：两点y坐标相同（同一水平线）
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

vector<pair<int, int> > v;
vector<bool> vis;

void dfs(const int u, const int n) {
    vis[u] = true;
    for (int i = 0; i < n; ++i) {
        if (!vis[i] && (v[u].first == v[i].first ||
            v[u].second == v[i].second)) dfs(i, n);
    }
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y;
        v.emplace_back(x, y);
    }
    int cnt = 0; vis.resize(n, false);
    for (int i = 0; i < n; ++i) if (!vis[i]) {
        dfs(i, n); cnt++;
    }
    cout << cnt - 1 << '\n';
    return 0;
}