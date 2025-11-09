//
// Created by Psy.C on 2025/9/20.
//
/*
 *
*DFS函数用于遍历图并标记连通分量
参数说明：
node: 当前访问的节点
g: 图的邻接表表示
visited: 访问标记数组
group: 连通分量标记数组
root: 当前连通分量的根节点
如果节点已访问则返回
标记当前节点为已访问，并将其归入以root为根的连通分量
递归访问所有未访问的邻接节点
 *
*创建目标数组target，大小为n+1（使用1-indexed）
读取目标排列，target[i]表示位置i应该放置的值
 *
*对每个位置i读取跳跃距离d
从位置i可以跳到位置i-d和i+d（如果在有效范围内）
在这些位置之间建立无向边
 *
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

void dfs(long node, const vector<vector<long>>& g, vector<bool>& visited, vector<long>& group, long root) {
    if (visited[node]) return;
    visited[node] = 1;
    group[node] = root;

    for (long i = 0; i < g[node].size(); ++i) {
        long u = g[node][i];
        if (visited[u]) continue;
        dfs(u, g, visited, group, root);
    }
}

int main() {

    long n; scanf("%ld", &n);
    vector<long> target(n + 1);
    for (long i = 1; i <= n; ++i) scanf("%ld", &target[i]);

    vector<vector<long>> g(n + 1);
    for (long i = 1; i <= n; ++i) {
        long d; scanf("%ld", &d);
        long u = i - d;
        if ((u > 0) && (u <= n)) {
            g[i].push_back(u);
            g[u].push_back(i);
        }
        long v = i + d;
        if ((v > 0) && (v <= n)) {
            g[i].push_back(v);
            g[v].push_back(i);
        }
    }

    vector<bool> mark(n + 1, 0);
    vector<long> group(n + 1, 0);
    for (long i = 1; i <= n; ++i) {
        if (mark[i]) continue;
        dfs(i, g, mark, group, i);
    }

    bool ok = true;
    for (long i = 1; i <= n; ++i) {
        if (group[i] != group[target[i]]) {
            ok = false;
            break;
        }
    }
    puts(ok ? "YES" : "NO");

    return 0;
}