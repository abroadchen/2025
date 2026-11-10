//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
用前向星存树边，add(u,v) 表示从 u 连到 v（有向，父→子）。
head[u] 是 u 的第一条边的链表头，e[i].nxt 指向下一条边。这是常见的 O(1) 加边、O(度数) 遍历的存图方式
叶子结点（无子边，head[u]==0）sz[u]=1。
非叶子结点：先递归每个儿子，把所有儿子子树大小累加到 sz[u]
对 i=2..n 读入父结点 p，建边 p → i。其中 1 是根，之后依次作为 2..n 的父
从根 1 触发整个 DFS。
把 sz[1..n]（所有子树大小）‍升序排序后全部输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

struct edge { int v, nxt; } e[N];

int cnt, head[N];
void add(int u, int v) {
    e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt;
}

int sz[N];
void dfs(int u) {
    if (head[u] == 0) sz[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        dfs(e[i].v);
        sz[u] += sz[e[i].v];
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 2, p; i <= n; i++) { cin >> p; add(p, i); }
    dfs(1);
    sort(sz+1, sz+n+1);
    for (int i = 1; i <= n; i++) cout << sz[i] << ' ';
    return 0;
}