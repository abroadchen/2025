//
// Created by Psy.C on 2026/4/12.
//
/**
创建队列，将起始节点加入队列
遍历队列直到为空
对当前节点的每条出边，创建新的节点v
如果目标节点未访问过，则标记访问，更新相关信息，加入队列

对每个节点执行BFS，计算最短路径并更新lt、lf数组
枚举所有可能的四元组(a,b,c,d)，寻找最长路径
输出找到的四个节点
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5005, M = 3005, inf = 0x3f3f3f3f;

struct edge { int v, nxt; } e[N];///邻接表存储图

struct node {
    int idx, len;
    bool operator<(const node& o) const {
        if (len == o.len) return idx < o.idx;
        return len < o.len;
    }
} lt[M][3], lf[M][3];///每个位置存储3个节点

void update(node u, node v) {
    lf[u.idx][0] = v;
    sort(lf[u.idx], lf[u.idx] + 3);
}

void update2(node u, node v) {
    v.len = u.len;
    lt[u.idx][0] = v;
    sort(lt[u.idx], lt[u.idx] + 3);
}

bool inq[M];
int head[M], dis[M][M];
void bfs(int x) {
    queue<node> q; node st(x, 0); q.push(st);
    inq[x] = true;
    while (!q.empty()) {
        node u = q.front(); q.pop();
        for (int i = head[u.idx]; ~i; i = e[i].nxt) {
            node v(e[i].v, u.len+1);
            if (!inq[v.idx]) {
                inq[v.idx] = true;
                update(st, v); update2(v, st);
                dis[st.idx][v.idx] = v.len;
                q.push(v);
            }
        }
    }
}

int len;
void add(int u, int v) {
    e[len] = {v, head[u]}, head[u] = len++;
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    memset(head, -1, sizeof head);
    memset(dis, inf, sizeof dis);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        if (u == v) continue;
        add(u, v);
    }
    for (int i = 1; i <= n; ++i) {
        memset(inq, false, sizeof inq);
        bfs(i);
    }
    int ans[4] = {}, tot = 0;
    for (int b = 1; b <= n; ++b)
        for (int c = 1; c <= n; ++c)
            for (int i = 2; ~i; --i)
                for (int j = 2; ~j; --j) {
                    int a = lt[b][i].idx, d = lf[c][j].idx;
                    if (a == b || a == c || a == d || b == c || b == d || c == d) continue;
                    if (dis[a][b] == inf || dis[b][c] == inf || dis[c][d] == inf) continue;
                    int t = dis[a][b] + dis[b][c] + dis[c][d];
                    if (t > tot) {
                        tot = t;
                        ans[0] = a; ans[1] = b; ans[2] = c; ans[3] = d;
                    }
                }
    for (int i = 0; i < 4; ++i) cout << ans[i] << ' ';
    return 0;
}