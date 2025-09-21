//
// Created by Psy.C on 2025/9/21.
//时间复杂度：O(n) - 每个节点和边只访问一次 空间复杂度：O(n) - 存储图和辅助数组

#include <cstdio>
#include <vector>
using namespace std;
// DFS遍历函数，构建以r2为根的树结构
void dfs(long node, const vector<vector<long>>& g, vector<long>& from, vector<bool>& vis) {
    if (vis[node]) return;
    vis[node] = 1;

    for (long i = 0; i < g[node].size(); ++i) {// 遍历当前节点的所有邻接节点
        long u = g[node][i];// 获取邻接节点
        if (vis[u]) continue;
        from[u] = node;// 设置u的父节点为当前节点
        dfs(u, g, from, vis);// 递归访问邻接节点
    }
}

int main() {

    long n, r1, r2; scanf("%ld %ld %ld\n", &n, &r1, &r2);// 读取节点数n，原根r1，新根r2
    vector<vector<long>> g(n + 1);// 构建邻接表表示的无向图
    for (long i = 1; i <= n; ++i) {// 读取原始树结构（除了根节点r1）
        if (i == r1) continue;
        long x; scanf("%ld", &x);// 读取节点i的父节点
        g[i].push_back(x);
        g[x].push_back(i);
    }

    vector<long> from(n + 1, 0);// from[i]表示节点i的父节点
    vector<bool> vis(n + 1, 0);
    dfs(r2, g, from, vis);

    // 输出除新根外每个节点的父节点
    for (long i = 1; i <= n; ++i) {
        if (i == r2) continue;
        printf("%ld ", from[i]);
    }
    puts("");// 输出换行
    return 0;
}