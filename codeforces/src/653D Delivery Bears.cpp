//
// Created by Psy.C on 2026/4/7.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4+5, M = 2e4+5, inf = 0x3f3f3f3f;

struct edge { int to, cap, rev; };///目标节点，容量，反向边索引
vector<edge> G[M];
void add(int fr, int to, int cap) {
    G[fr].push_back(edge(to, cap, G[to].size()));
    G[to].push_back(edge(fr, 0, G[fr].size() - 1));
}

int d[M], s, t;
void bfs() {
    memset(d, -1, sizeof(d));
    queue<int> q; d[s] = 0; q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int i = 0; i < G[v].size(); ++i) {
            if (auto& e = G[v][i]; e.cap > 0 && d[e.to] < 0) {//边有容量且未访问
                d[e.to] = d[v] + 1;//设置距离
                q.push(e.to);//加入队列
            }
        }
    }
}

int iter[M];
int dfs(int v, int f) {//当前节点，当前路径最小容量
    if (v == t) return f;//到达汇点，返回流量
    for (int& i = iter[v]; i < G[v].size(); ++i) {//使用引用，避免重复访问
        if (auto&[to, cap, rev] = G[v][i]; cap > 0 && d[v] < d[to]) {
            if (int tf = dfs(to, min(f, cap)); tf > 0) {//递归找增广路径
                cap -= tf;//减少正向边容量
                G[to][rev].cap += tf;//增加反向边容量
                return tf;//返回实际流量
            }
        }
    }
    return 0;//没有找到增广路径
}

int get() {
    int flow = 0;
    for (;;) {
        bfs();//构建层次图
        if (d[t] < 0) return flow;//汇点不可达
        memset(iter, 0, sizeof(iter));//重置迭代器
        int f;
        while ((f = dfs(s, inf)) > 0) flow += f;//不断寻找增广路径
    }
}

int a[N], b[N], c[N], x, m, n;
bool judge(double mid) {
    for (int i = 0; i < N; ++i) G[i].clear();
    for (int i = 0; i < m; ++i)
        add(a[i], b[i], min(1.*x, (double)c[i]/mid));//添加边，容量受mid限制
    add(n, t, x); add(s, 1, x);//添加源汇连接
    return get() == x;//是否能满流
}

int main() {
    fast;
    cin >> n >> m >> x;//节点数、边数、目标流量
    for (int i = 0; i < m; ++i) cin >> a[i] >> b[i] >> c[i];
    s = 0, t = n + 1; add(n, t, inf), add(s, 1, x);//添加超级源汇连接
    double l = 0, r = 1000005;
    for (int i = 0; i < 100; ++i) {
        if (double mid = (l+r)/2; judge(mid)) l = mid; else r = mid;
    }
    printf("%.10f", l*x);
    return 0;
}