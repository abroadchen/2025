//
// Created by Psy.C on 2025/11/7.
//
/*
 *BFS遍历整个图：对于队列中的每个节点u，遍历其所有邻居v，
 *如果v未被访问，则标记v为已访问，设置v的父节点为u，设置v的容量为边权重c，并将v加入队列
 *创建两个二维向量cur和nxt用于存储当前和下一轮的节点信息。
 *如果节点数大于1，则将每个节点(除了根节点1)作为Node对象加入到对应的cur数组中
 *
 *当处理的节点数小于总数时，遍历所有节点，将nxt中的节点移到cur中或记录答案(如果是根节点)
 *如果所有节点都已处理完毕，则跳出循环。
 *对于每个非根节点，如果当前节点有等待处理的节点，则按优先级排序，
 *取前cap[i]个节点传递给父节点，并从当前节点中删除这些节点
 *天数增加1，继续下一轮处理
 *
 */
#include <algorithm>
#include <vector>
#include <iostream>
#define rep(i,n) for(int i=1;i<=(n);++i)
#define sz(n) ((int)(n).size())
using namespace std;

typedef pair<int,int> pii;

struct Node {
    int id, p;
    bool operator<(const Node& x) const { return p < x.p; }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    vector<int> a(n + 1);
    rep(i,n) cin >> a[i];
    vector<vector<pii>> g(n + 1);
    if (n > 1) {
        for (int i = 0; i < n - 1; ++i) {
            int u, v, c; cin >> u >> v >> c;
            g[u].push_back({v, c});
            g[v].push_back({u, c});
        }
    }
    vector<int> fa(n + 1), cap(n + 1);
    if (n > 1) {//bfs
        vector<bool> vis(n + 1);
        vector<int> q;
        q.push_back(1);
        vis[1] = true;
        for (int i = 0; i < q.size(); ++i) {
            int u = q[i];
            for (auto [v, c] : g[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    fa[v] = u;
                    cap[v] = c;
                    q.push_back(v);
                }
            }
        }
    }
    vector<vector<Node>> cur(n + 1), nxt(n + 1);
    if (n > 1) {
        for (int i = 2; i <= n; ++i) cur[i].push_back({i, a[i]});
    }
    vector<int> ans(n + 1);
    int cnt(0), day(0), tot = n > 1 ? n - 1 : 0;
    if (n > 1) {
        while (cnt < tot) {
            rep(i,n) {
                for (auto [id, p] : nxt[i]) {
                    if (i == 1) { if (!ans[id]) ans[id] = day, cnt++; }
                    else cur[i].push_back({id, p});
                }
                nxt[i].clear();
            }
            if (cnt == tot) break;
            for (int i = 2; i <= n; ++i) {
                if (cur[i].empty()) continue;
                sort(cur[i].begin(), cur[i].end());
                int size = min(sz(cur[i]), cap[i]);
                for (int j = 0; j < size; ++j) nxt[fa[i]].push_back(cur[i][j]);
                cur[i].erase(cur[i].begin(), cur[i].begin() + size);
            }
            day++;
        }
    }
    rep(i,n) cout << ans[i] << " \n"[i==n];
    return 0;
}