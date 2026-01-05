#include <iostream>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 100010
#define inf 0x3f3f3f3f
using namespace std;

struct node {
    int to, fl, nxt, c;//目标节点、流量、下一条边索引、费用
    explicit node(const int to=0, const int fl = 0, const int c=0, const int nxt=-1)
        : to(to), fl(fl), nxt(nxt), c(c) {}
} g[1000010];

int tot, head[N];
void add(const int u, const int v, const int fl, const int c) {
    g[tot] = node(v, fl, c, head[u]);
    head[u] = tot++;
    g[tot] = node(u, 0, -c, head[v]);//用于增广路径
    head[v] = tot++;
}

int p[N], d[N];//p: 记录路径的前驱节点 d: 记录最短距离
bool vis[N];//是否在队列中
bool spfa(const int s, const int t) {
    for (int i = 0; i < N; ++i) { p[i] = -1; d[i] = inf; vis[i] = false; }
    d[s] = 0; queue<int> q; q.push(s);
    while (!q.empty()) {
        const int u = q.front(); q.pop(); vis[u] = false;//标记为不在队列中
        for (int i = head[u]; ~i; i = g[i].nxt) {
            if (g[i].fl && d[g[i].to] > d[u] + g[i].c) {//边有流量且可以松弛，则更新距离和前驱
                d[g[i].to] = d[u] + g[i].c;
                p[g[i].to] = i;
                if (!vis[g[i].to]) {
                    q.push(g[i].to);
                    vis[g[i].to] = true;
                }
            }
        }
    }
    return p[t] > -1;
}

//不断寻找最短增广路径直到无法找到
int calc(const int s, const int t) {
    int ans = 0;
    while (spfa(s, t)) {
        int mx = inf;
        for (int i = p[t]; ~i; i = p[g[i^1].to]) mx = min(mx, g[i].fl);
        for (int i = p[t]; ~i; i = p[g[i^1].to]) {
            g[i].fl -= mx;
            g[i^1].fl += mx;
            ans += g[i].c * mx;
        }
    }
    return ans;
}

int main() {
    fast;
    int n, m, mp[120][120]; cin >> n >> m;
    memset(head, -1, sizeof head);
    for (int i = tot = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> mp[i][j];
    const int s = n * m, t = s + 1;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if ((i + j) & 1) {//奇数坐标和黑色节点连接源点
            add(s, i*m+j, 1, 0);
            if (i) add(i*m+j, (i-1)*m+j, 1, mp[i][j] != mp[i-1][j]);//费用为值是否不同
            if (j) add(i*m+j, i*m+j-1, 1, mp[i][j] != mp[i][j-1]);
            if (i+1 < n) add(i*m+j, (i+1)*m+j, 1, mp[i][j] != mp[i+1][j]);
            if (j+1 < m) add(i*m+j, i*m+j+1, 1, mp[i][j] != mp[i][j+1]);
        } else add(i*m+j, t, 1, 0);
    }
    cout << calc(s, t) << '\n';
    return 0;
}