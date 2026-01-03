//
// Created by Psy.C on 2026/1/3.
//
/**
* lev: 记录节点层次的数组
bfs函数：构建层次图，使用BFS算法
初始化层次数组为-1，源点层次为0
遍历当前节点的所有邻接节点，如果容量大于0且未访问过
设置邻接节点的层次为当前节点层次+1
如果找到汇点则返回true
最终返回是否能到达汇点
 *
*cur: 当前弧优化数组，记录每个节点当前访问的边
dfs函数：在层次图中寻找增广路径
如果到达汇点或流量限制为0，返回限制值
遍历当前节点的所有邻接边，只考虑容量大于0且满足层次条件的边
递归调用dfs，流量限制为当前限制和边容量的最小值
找到增广路径后更新边容量和反向边容量
使用异或操作i^1快速访问反向边
 *
*dinic函数：实现Dinic最大流算法
只要还能构建层次图就继续循环
每次BFS后复制head数组到cur数组（当前弧优化）
在当前层次图中不断寻找增广路径直到无法找到
累计所有找到的流量
 *
 *初始化head数组为-1（表示没有邻接边）
 *n节点数，m边数，k参数，col颜色数组，ans结果
*定义源点s和汇点t
读入每个节点的颜色
根据颜色添加边：颜色为0的节点从源点连入，颜色为1的节点连向汇点
 *
*遍历每条边
读入x（方向）、w（权重）、q（连接数量）
累加权重到答案
根据方向添加边（x=0表示从中间节点到普通节点，否则相反）
读入f标志，根据f和x的值决定向源点或汇点添加边
 *
 */
#include <iostream>
#include <cstring>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int inf = 1e9;

struct node { int to, cap, nxt; } g[N<<5];
int head[N], tot;
void add(const int u, const int v, const int cap) {
    g[tot] = {v, cap, head[u]}; head[u] = tot++;
    g[tot] = {u, 0, head[v]}; head[v] = tot++;
}

int lev[N];
bool bfs(const int s, const int t) {
    memset(lev, -1, sizeof(lev));
    queue<int> q; lev[s] = 0; q.push(s);
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = g[i].nxt) {
            int v = g[i].to;
            if (lev[v] == -1 && g[i].cap > 0) {
                lev[v] = lev[u] + 1;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return lev[t] != -1;
}

int cur[N];
int dfs(const int u, const int t, int lo) {
    if (u == t || lo <= 0) return lo;
    int fl = 0;
    for (int& i = cur[u]; ~i; i = g[i].nxt) {
        const int v = g[i].to;
        if (g[i].cap > 0 && lev[v] == lev[u] + 1) {
            const int d = dfs(v, t, min(lo, g[i].cap));
            if (d > 0) {
                lo -= d; fl += d;
                g[i].cap -= d; g[i^1].cap += d;
                if (lo <= 0) return fl;
            }
        }
    }
    return fl;
}


int dinic(const int s, const int t) {
    int fl = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        int f;
        while ((f = dfs(s, t, inf))) fl += f;
    }
    return fl;
}

int main() {
    fast;
    memset(head, -1, sizeof(head));
    int n, m, k, col[N], ans = 0;
    cin >> n >> m >> k;
    const int s = n + m + 1, t = s + 1;
    rep(i,n) cin >> col[i];
    rep(i,n) {
        int c; cin >> c;
        if (col[i] == 0) add(s, i, c); else add(i, t, c);
    }
    rep(i,m) {
        int x, w, q, f; cin >> x >> w >> q;
        ans += w;
        while (q--) {
            int y; cin >> y;
            if (x == 0) add(i + n, y, inf); else add(y, i + n, inf);
        }
        cin >> f;
        if (x == 0) add(s, i + n, w + (f ? k : 0)); else {
            add(i + n, t, w + (f ? k : 0));
        }
    }
    ans -= dinic(s, t);
    cout << ans;
    return 0;
}