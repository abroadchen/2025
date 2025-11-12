//
// Created by Psy.C on 2025/11/12.
//
/*
*e：二维向量，用于表示图的邻接表
vis：布尔向量，用于在深度优先搜索过程中跟踪已访问的节点
tot：计数器，初始化为0，用于统计访问过的节点数量
 *
*如果节点x已经被访问过，直接返回
标记节点x为已访问状态（vis[x] = 1）
计数器加1（++tot）
遍历节点x的所有邻居节点
对每个未访问的邻居节点递归调用DFS函数
 *
 *对于一个连通图要有且仅有一个环，必须满足节点数等于边数
 *如果不是所有节点都被访问过（tot < n），说明图不连通
 *
 *
 *n（节点数）、m（边数）、f数组（并查集的父节点数组）
*处理m条边：
读入边的两个端点x和y
找到x和y所在的集合的根节点
如果它们不在同一集合（根节点不同），则将其中一个集合合并到另一个集合中
 *
*遍历所有节点，检查相邻节点是否在同一连通分量中
实际上是在验证所有节点是否属于同一个连通分量
如果发现有任何两个节点不属于同一连通分量，则图不连通，输出"NO"并结束
 *
 *时间复杂度接近O(m×α(n))，其中α是阿克曼函数的反函数
 */
#include <iostream>
using namespace std;

const int N = 105;
int n, m, f[N];

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]);}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        x = find(x); y = find(y);
        if (x != y) f[y] = x;
    }
    if (n != m) { cout << "NO"; return 0; }
    for (int i = 2; i <= n; ++i) {
        if (find(i) != find(i - 1)) {
            cout << "NO";
            return 0;
        }
    }
    cout << "FHTAGN!";
    return 0;
}


#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int>> e;
vector<bool> vis;
int tot(0);

void dfs(int x) {
    if (vis[x]) return;
    vis[x] = 1;
    ++tot;
    for (int i = 0; i < e[x].size(); ++i) {
        dfs(e[x][i]);
    }
}

int main() {
    int n, m; scanf("%d %d\n", &n, &m);
    if (n != m) { puts("NO"); return 0; }
    e.resize(n + 1); vis.resize(n + 1);

    for (int i = 0, a, b; i < m; ++i) {
        scanf("%d %d\n", &a, &b);
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs(1);
    if (tot < n) puts("NO");
    else puts("FHTAGN!");
    return 0;
}