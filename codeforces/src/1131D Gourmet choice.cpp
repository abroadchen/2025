//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
邻接表存边：to 终点、w 权值（这里恒为 1，意义是"差值至少为 1"）、pre 链式前向星。
并查集，fa[1..n+m]：前 n 个代表行，后 m 个代表列（n+j 表示第 j 列）。
用于把 = 的两方合并成一个"等价类"
把矩阵先读一遍。凡是 = 的格子，将对应行、列并查集合并，代表它们"值必须相同"
遍历每个格子，取两个端点所在等价类的代表元 x（行）、y（列）。
x == y 却要求 < 或 > → 自相矛盾（同一等价类必须相等），直接 No。
建有向边，方向是小→大，边权 1（表示差值至少 1），同时统计入度 deg
把所有入度为 0 的等价类入队，初始值 = 1（最小正整数）。
BFS/拓扑：每次取出 u，赋权 val；遍历其出边，把入度减到 0 的 v 入队，赋值 val + w = val+1（比前驱至少大 1）。
若拓扑能走完，说明无环，可行；若有环，会有节点永远入度>0 没被访问
每个等价类都赋到了值，则把 ans[find(i)] 回填到每个行/列节点。
只要有节点 ans[] 仍为 0，说明它属于的等价类没入过队（在环里）→ 无解输出 No。
否则输出 Yes，并按要求输出每行一列的值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1005;

struct node { int to, w, pre; } e[N*N];

int tot, head[N*N];
void add(int fr, int to, int w) {
    e[++tot].to = to; e[tot].w = w; e[tot].pre = head[fr]; head[fr] = tot;
}

int fa[N<<1];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void uni(int x, int y) { fa[find(x)] = find(y); }

int n, m, deg[N<<1], ans[N<<1];
char ch[N][N];
queue<ii> q;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n+m) fa[i] = i;
    rep(i,n) rep(j,m) {
        cin >> ch[i][j];
        int x = find(i), y = find(n+j);
        if (ch[i][j] == '=') uni(x,y);
    }
    rep(i,n) rep(j,m) {
        int x = find(i), y = find(n+j);
        if (ch[i][j] == '<') {
            if (x == y) { cout << "No\n"; return 0; }
            add(x,y,1); ++deg[y];
        }
        if (ch[i][j] == '>') {
            if (x == y) { cout << "No\n"; return 0; }
            add(y,x,1); ++deg[x];
        }
    }
    rep(i,n+m) if (i == find(i) && !deg[find(i)]) q.emplace(find(i),1);
    while (!q.empty()) {
        int u = q.front().first, val = q.front().second; q.pop();
        ans[u] = val;
        for (int i = head[u]; i; i = e[i].pre) {
            int v = e[i].to, w = e[i].w; --deg[v];
            if (!deg[v]) q.emplace(v,val+w);
        }
    }
    rep(i,n+m) ans[i] = ans[find(i)];
    rep(i,n+m) if (!ans[i]) { cout << "No\n"; return 0; }
    cout << "Yes\n";
    rep(i,n) cout << ans[i] << ' ';
    cout << '\n';
    for (int i = n+1; i <= n+m; ++i) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}