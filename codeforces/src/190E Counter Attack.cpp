//
// Created by Psy.C on 2025/12/2.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) (static_cast<int>((x).size()))
using namespace std;

constexpr int N = 5e5+5;
vector<int> v;//存储节点
unordered_map<int, bool> mp[N];//存储图的邻接关系
vector<vector<int>> ans;

vector<int> bfs(const int x) {//接受一个起始节点x，返回连通分量中的所有节点
    vector<int> res;
    queue<int> q; q.push(x);
    while (!q.empty()) {
        int t = q.front(); q.pop();
        res.push_back(t);
        for (int i = 0; i < sz(v); ++i) {//遍历当前剩余的节点v中的每个节点
            int u = v[i];//获取当前检查的节点u
            if (mp[t].count(u) == 0) {//如果节点t和u之间没有边（在补图中相连）
                swap(v[i], v.back()); v.pop_back();//将节点u从v中移除（通过交换到最后一个位置并弹出）
                i--;//调整循环索引
                q.push(u);//将节点u加入队列继续BFS
            }
        }
    }
    return res;
}

int main() {
    fast;
    int n, m; cin>>n>>m;
    for (int i = 1; i <= n; ++i) v.push_back(i);
    for (int i = 1, x, y; i <= m; ++i) {
        cin>>x>>y;
        mp[x][y] = true; mp[y][x] = true;
    }
    while (!v.empty()) {//当还有未访问的节点时继续
        const int u = v.back(); v.pop_back();//取出最后一个节点u作为新的起始点
        vector<int> cnt = bfs(u);
        ans.push_back(cnt);
    }
    sort(ans.begin(), ans.end());
    cout << sz(ans) << '\n';
    for (int i = 0; i < sz(ans); ++i) {
        cout << sz(ans[i]) << ' ';
        for (int j = 0; j < sz(ans[i]); ++j) cout << ans[i][j] << ' ';//输出当前连通分量中的所有节点
        cout << '\n';
    }
    return 0;
}