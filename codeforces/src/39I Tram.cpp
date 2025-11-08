//
// Created by Psy.C on 2025/9/24.
//
/*
*n：节点数
m：边数
a[N]：存储每个节点的距离标记
t：用于存储计算出的最大公约数
g[N]：邻接表表示的图
ans：存储结果节点的向量
 *
*从节点u开始进行深度优先搜索
遍历u的所有邻接节点v
如果v未被访问过（a[v] == -1），则标记v的距离为a[u] + 1，并递归搜索v
 *
*遍历所有边(u,v)
如果u和v都可达（距离不为-1），则计算它们距离差的绝对值
使用最大公约数更新t值
输出计算出的最大公约数t
 *
 *
 */
#include <cctype>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e5+5;


inline int read() {
    int x(0), f(1);
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x * f;
}

int n, m, a[N], t;
vector<int> g[N], ans;

void dfs(int u) {
    for (auto v : g[u]) {
        if (a[v] == -1) {
            a[v] = a[u] + 1;
            dfs(v);
        }
    }
}

int main() {
    n = read(), m = read();

    for (int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        g[u].emplace_back(v);
    }
    memset(a, -1, sizeof(a));
    a[1] = 0;//设置起点1的距离为0
    dfs(1);//从节点1开始进行DFS，计算所有可达节点到起点的距离

    for (int u = 1; u <= n; ++u) {
        for (auto v : g[u]) {
            if (a[u] != -1 && a[v] != -1)
                t = __gcd(t, abs(a[u] + 1 - a[v]));
        }
    }
    printf("%d\n", t);

    for (int i = 1; i <= n; ++i) {
        if (a[i] != -1 && a[i] % t == 0)
            ans.emplace_back(i);
    }
    printf("%d\n", ans.size());

    for (auto i : ans) printf("%d ", i);
    return 0;
}