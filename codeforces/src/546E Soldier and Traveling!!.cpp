//
// Created by Psy.C on 2026/3/7.
//
/**
e[N]：边的目标节点
cnt：边计数器
nxt[N]：链式前向星的next指针
f[N]：边的容量
head[N]：每个节点的第一条边
d[N]：分层图的层次
q[N]：BFS队列
cur[N]：当前弧优化
s, t：源点和汇点
BFS建立分层图，寻找增广路径
DFS寻找增广路径
lim：当前路径的流量限制
flow：累计流量
当前弧优化：记录下次搜索的起始位置
更新正向边和反向边的流量
重复BFS+DFS直到无法找到增广路径
累计最大流
从源点向左半部分节点连边，容量为a[i]
从右半部分节点向汇点连边，容量为b[i]
左右对应的节点间连边，容量为无穷大
处理m条约束边，允许在不同节点间传递流量

计算最大流
如果最大流不等于s1或s1不等于s2，无解
输出"YES"
从残余网络中提取答案矩阵
通过反向边的剩余容量构造答案

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

constexpr int N = 2e5+5, M = 200, inf = 0x3f3f3f3f;

int e[N], cnt, nxt[N], f[N], head[N];
void add(int x, int y, int z) {
    e[cnt] = y, nxt[cnt] = head[x], f[cnt] = z, head[x] = cnt++;
    e[cnt] = x, nxt[cnt] = head[y], f[cnt] = 0, head[y] = cnt++;
}

int d[N], q[N], cur[N], s, t;
bool bfs() {
    int l = 0, r = 0;
    memset(d, -1, sizeof(d));
    q[0] = s, d[s] = 0, cur[s] = head[s];
    while (l <= r) {
        int x = q[l++];
        for (int i = head[x]; ~i; i = nxt[i]) {
            int j = e[i];
            if (d[j] == -1 && f[i]) {
                d[j] = d[x] + 1;
                cur[j] = head[j];
                if (j == t) return true;
                q[++r] = j;
            }
        }
    }
    return false;
}

int dfs(int u, int lim) {
    if (u == t) return lim;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < lim; i = nxt[i]) {
        cur[u] = i;
        int j = e[i];
        if (d[j] == d[u] + 1 && f[i]) {
            int x = dfs(j, min(f[i], lim - flow));
            if (!x) d[j] = -1;
            f[i] -= x, f[i^1] += x, flow += x;
        }
    }
    return flow;
}

int dinic() {
    int res = 0, flow;
    while (bfs())
        while ((flow = dfs(s, inf))) res += flow;
    return res;
}

int n, m, a[N], b[N], ans[M][M];
int main() {
    fast;
    read(n), read(m);
    memset(head, -1, sizeof(head));
    int s1 = 0, s2 = 0;
    for (int i = 1; i <= n; ++i) read(a[i]), s1 += a[i];
    for (int i = 1; i <= n; ++i) read(b[i]), s2 += b[i];
    s = 0, t = 2*n+1;
    for (int i = 1; i <= n; ++i) add(s, i, a[i]);
    for (int i = 1; i <= n; ++i) add(i + n, t, b[i]);
    for (int i = 1; i <= n; ++i) add(i, i + n, inf);
    while (m--) {
        int u, v; read(u), read(v);
        add(u, v + n, inf), add(v, u + n, inf);
    }
    if (int res = dinic(); res != s1 || s1 != s2) {
        cout << "NO\n"; return 0;
    }
    cout << "YES\n";
    for (int i = n+1; i <= n*2; ++i)
        for (int j = head[i]; ~j; j = nxt[j]) {
            if (int x = e[j]; x >= 1 && x <= n)
                ans[x][i-n] = f[j];
        }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) cout << ans[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}