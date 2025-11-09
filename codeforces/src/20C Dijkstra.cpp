//
// Created by Psy.C on 2025/9/18.
//
/*
*n, m: 图的节点数和边数
g: 邻接表表示的图，g[i]存储从节点i出发的所有边，每条边用pair<目标节点, 权重>表示
*读取m条边的信息
由于是无向图，每条边添加两次（u→v和v→u）
每条边的权重都是w
 *
*source=1, target=n: 源节点为1，目标节点为n
q: 优先队列，存储pair<距离, 节点>，按距离排序
dist: 存储从源节点到每个节点的最短距离，初始为-1表示未访问
from: 存储最短路径中每个节点的前驱节点，用于重构路径
visited: 标记节点是否已处理完毕
 *
*从优先队列中取出距离最小的节点
如果该节点已访问过，则跳过
标记该节点为已访问
 *
*遍历当前节点的所有邻接边
对于未访问的邻接节点u：
如果u还未被访问过，或者找到了更短的路径到u
更新dist[u]为新的最短距离
将pair<新距离, u>插入优先队列
记录u的前驱节点为当前节点vertex
 *
*如果dist[n] < 0，说明无法从节点1到达节点n，输出-1
否则重构并输出最短路径：
使用栈来逆序存储路径
从目标节点n开始，通过from数组向前追溯到源节点
当st.top() == from[st.top()]时停止（即到达源节点1）
依次弹出栈中元素，得到正序的路径
 *
 *
 *
 *
 *使用set作为优先队列来维护待处理节点。时间复杂度为O((V+E)logV)，其中V是节点数，E是边数。算法不仅能计算最短距离，还能重构出具体的最短路径
 *
 *
 *
 *
 */
#include <cstdio>
#include <set>
#include <stack>
#include <vector>
#include <cstdint>
using namespace std;

int main() {

    int64_t n, m; scanf("%lld %lld\n", &n, &m);
    vector<vector<pair<int64_t, int64_t>>> g(n + 1);

    while (m--) {
        int64_t u, v, w; scanf("%lld %lld %lld", &u, &v, &w);
        g[u].push_back(pair<int64_t, int64_t>(v, w));
        g[v].push_back(pair<int64_t, int64_t>(u, w));
    }

    int64_t source(1), target(n);
    set<pair<int64_t, int64_t>> q;
    q.insert(pair<int64_t, int64_t>(0, source));
    vector<int64_t> dist(n + 1, -1);
    vector<int64_t> from(n + 1, -1); from[0] = 0; from[1] = 1;
    vector<bool> visited(n + 1, 0);

    while (!q.empty()) {
        pair<int64_t, int64_t> cur = *q.begin(); q.erase(q.begin());
        int64_t distance = cur.first, vertex = cur.second;
        if (visited[vertex]) continue;
        visited[vertex] = true;

        for (int64_t i = 0; i < g[vertex].size(); ++i) {
            pair<int64_t, int64_t> edge = g[vertex][i];
            int64_t u = edge.first, w = edge.second;
            if (visited[u]) continue;
            if (dist[u] < 0 || dist[u] > distance + w) {
                dist[u] = distance + w;
                q.insert(pair<int64_t, int64_t>(dist[u], u));
                from[u] = vertex;
            }
        }
    }

    if (dist[n] < 0) puts("-1");
    else {
        stack<int64_t> st; st.push(n);
        do {
            st.push(from[st.top()]);
        } while (st.top() != from[st.top()]);
        while (!st.empty()) {
            printf("%lld ", st.top());
            st.pop();
        }
        puts("");
    }
    
    return 0;
}