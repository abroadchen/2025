//
// Created by Psy.C on 2026/2/2.
//
/**
* N：节点最大数量
M：边的最大数量
*u：边的起点
v：边的终点
nxt：指向同一起点的下一条边
*e[M]：存储图的边
cnt：边的计数器
head[M]：head[u] 指向以 u 为起点的第一条边
*nxt 指向原来以 a 为起点的第一条边
更新 head[a] 指向这条新边
 *sum：已访问的节点数量
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 30010
#define M 100010
using namespace std;

struct node { int u, v, nxt; } e[M];

int cnt, head[M];
void add(const int a, const int b) {
    e[cnt].u = a; e[cnt].v = b; e[cnt].nxt = head[a]; head[a] = cnt++;
}

int sum, n;
bool vis[N];
void dfs(const int a) {
    if (vis[a]) return; vis[a] = true;
    for (int i = head[a]; i > -1; i = e[i].nxt) dfs(e[i].v);
    if (sum < n-1) cout << a << ' ';
    else cout << a << '\n';
    sum++;
}

int main() {
    fast;
    int m; cin >> n >> m; cnt = sum = 0;
    memset(vis, 0, sizeof vis);
    memset(head, -1, sizeof head);
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b; add(a, b);
    }
    for (int i = 1; i <= n; ++i) dfs(i);
    return 0;
}