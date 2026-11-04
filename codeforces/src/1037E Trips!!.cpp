//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
a[i] 保存第 i 条边的两端点 u,v 以及该边在被删 之前 对应时刻的答案 ans。
d[] 当前每个节点的度数。
e[] 用 set 存邻边，方便 O(log) 删除。
f[] 标记节点是否已被剔除（不再属于活跃子图）
无向图，边双加。
c 记录当前仍活跃（未剔除）的节点数。
初始把所有度数 < k 的节点标记为剔除并入队，同时活跃数减 1
每轮先用队列把所有当前度 < k 的节点剔除，剔除一个节点会使其每个邻居度数 -1，可能引发邻居也跌破 k，循环处理，直到没有新的可剔除节点。c 记录精确的活跃节点总数。
此时 c 就是"删除第 i 条边之前"对应的 k-core 规模，存入 a[i].ans
相当于题目中"删除第 i 条边"，删掉后两端点度数 -1；若某端跌破 k 则并入剔除队列（下一轮 while 会处理）
从邻接集合中真正移除该边
按正序（第1条到第m条）输出每次删除前的 k-core 节点数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 3e5+5;

struct { int u, v, ans; } a[N];

int n, m, k, d[N];
set<int> e[N];
queue<int> q;
bool f[N];
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        e[u].insert(v); e[v].insert(u);
        a[i].u = u; a[i].v = v;
        d[u]++, d[v]++;
    }
    int c = n;
    for (int i = 1; i <= n; i++) if (d[i] < k) { q.push(i); f[i] = 1; c--; }
    for (int i = m; i >= 1; i--) {
        while (!q.empty()) {
            for (auto x : e[q.front()]) {
                d[x]--;
                if (d[x] == k-1) { q.push(x); f[x] = 1; c--; }
            }
            q.pop();
        }
        a[i].ans = c;
        if (f[a[i].u] == 0 && f[a[i].v] == 0) {
            d[a[i].u]--;
            if (d[a[i].u] == k-1) { q.push(a[i].u); f[a[i].u] = 1; c--; }
            d[a[i].v]--;
            if (d[a[i].v] == k-1) { q.push(a[i].v); f[a[i].v] = 1; c--; }
        }
        e[a[i].u].erase(a[i].v); e[a[i].v].erase(a[i].u);
    }
    for (int i = 1; i <= m; i++) cout << a[i].ans << '\n';
    return 0;
}