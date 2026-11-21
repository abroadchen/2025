//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
to[tot]：第 tot 条边的终点。
nxt[tot]：同一起点的下一条边在数组中的下标（链指针）。
head[x]：以 x 为起点的头边下标。
add(x,y)：在 x 的链头插入一条指向 y 的边
n 顶点数、m 边数。
vis[] 访问标记、ans[] 存遍历顺序、sum 已访问顶点计数。
小顶堆优先队列（greater<>），堆顶是最小值
读入 m 条无向边，每条边双向各加一次（add(x,y) + add(y,x)）
从顶点 1 出发的优先队列 BFS（类 Dijkstra 式的"每次取编号最小的待访问点"）：

压入起点 1。
循环：q.top() 弹出当前队列中编号最小的顶点 h，标记访问并记录进 ans。
遍历 h 的所有邻接点 p，若未访问则标记并压入队列。
因为用的是小顶堆，所以每次弹出的总是"队列里编号最小"的那个 → 得到的访问顺序 ans[] 是按顶点编号增序的字典序最小的 BFS/DFS 变体结果
按遍历顺序输出所有顶点（间以空格）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 5e5;

int to[N], tot, nxt[N], head[N];
void add(int x, int y) { to[++tot] = y; nxt[tot] = head[x]; head[x] = tot; }

int n, m, sum, vis[N], ans[N];
priority_queue<int, vector<int>, greater<>> q;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) { int x, y; cin >> x >> y; add(x, y); add(y, x); }
    q.push(1);
    while (!q.empty()) {
        int h = q.top(); q.pop();
        vis[h] = 1; ans[++sum] = h;
        for (int i = head[h]; i; i = nxt[i]) {
            int p = to[i];
            if (!vis[p]) { vis[p] = 1; q.push(p); }
        }
    }
    rep(i,n) cout << ans[i] << ' ';
    return 0;
}