//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
find(x) 是标准带路径压缩的并查集查找。
fa[x] 初始为 i，即每个点自成一个集合
n：点数。
a[i]：点 i 的出边指向（每个点恰好有一条出边，指向 a[i]）。
in[i]：点 i 的入度。
q：BFS 队列
读入每个点的出边 a[i]，同时给目标点累加入度
每个点只有一条出边，所以整个图是由若干环和挂在其上的树/链组成（环基树森林）。

入度为 0 的点必然不在环上，把它们作为 BFS 起点逐层删除。
对每个出队的点 cur，记录 fa[cur] = a[cur]（把 cur 并入它指向的点），再减少 a[cur] 的入度；当 a[cur] 入度变为 0 时继续入队。
这样循环结束后，所有非环点都被并入了环上的点
由于拓扑排序只删除了非环点，环上的点在 BFS 中入度始终 ≥1，不会被出队，所以 fa[环上点] 仍然等于它自己（初始值）
对非环点：find(i) 会沿 fa 链最终找到该点指向的那个环上的代表点（即"终点"）。
对环上点：find(i) == i（自环代表）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
using namespace std;

constexpr int N = 2e5+5;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int n, a[N], in[N];
queue<int> q;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i], in[a[i]]++;
    rep(i,n) fa[i] = i;
    rep(i,n) if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        in[a[cur]]--;
        fa[cur] = a[cur];
        if (in[a[cur]] == 0) q.push(a[cur]);
    }
    rep(i,n) cout << find(i) << ' ';
    return 0;
}