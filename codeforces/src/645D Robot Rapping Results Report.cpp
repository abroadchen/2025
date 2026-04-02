//
// Created by Psy.C on 2026/4/1.
//
/**
n: 节点数
d[N]: 入度数组
u[N], v[N]: 边的起点和终点
G[N]: 邻接表存储图
检查前x条边构成的图是否有多于一种拓扑排序
重置入度数组和邻接表
添加前x条边到图中
更新相应节点的入度
将所有入度为0的节点加入队列
c: 已处理的节点数
如果队列中有多个入度为0的节点，说明拓扑排序不唯一
返回false表示存在多种拓扑排序
遍历当前节点的所有邻居，减少它们的入度
如果邻居入度变为0，加入队列
如果处理的节点数不等于n，说明存在环
否则返回true（拓扑排序唯一）
ok(mid)返回true意味着拓扑排序是唯一的（还没到不唯一的点）
所以要继续向右搜索
时间复杂度：O(m * n * log m)，其中每次拓扑排序需要O(n)，二分搜索需要O(log m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int n, d[N], u[N], v[N];
vector<int> G[N];
bool ok(int x) {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        d[i] = 0; G[i].clear();
    }
    for (int i = 1; i <= x; ++i) {
        G[u[i]].push_back(v[i]);
        d[v[i]]++;
    }
    int c = 0;
    for (int i = 1; i <= n; ++i)
        if (!d[i]) {
            q.push(i); c++;
        }
    while (!q.empty()) {
        if (q.size() > 1) return false;
        int now = q.front(); q.pop();
        for (auto it : G[now])
            if (!--d[it]) {
                c++; q.push(it);
            }
    }
    if (c != n) return false;
    return true;
}

int m, ans = -1;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> u[i] >> v[i];
    int l = 1, r = m;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (ok(mid)) { r = mid - 1; ans = mid; }
        else l = mid + 1;
    }
    cout << ans;
    return 0;
}