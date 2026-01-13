/**
 * num = 1：边的编号，从1开始（0用于空指针）
 *nxt[M]：链式前向星的next数组
 *head[N]：链式前向星的head数组 存储每个节点的第一条边
 *to[M]：边的终点
 *dis[M]：边的容量 残量网络
 *add：添加双向边（用于最大流算法）
 *另一套邻接表用于存储最小割树
 *dep[N]：层次图深度
 *s, t：源点和汇点
 *m是边数，id是节点ID，ans是答案，b是辅助数组
 */
#include <iostream>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;

constexpr int N = 205, M = 4005, inf = 2e8;
struct node { int x, y, z; } e[M];//起点、终点、容量

int num = 1, nxt[M], head[N], to[M], dis[M];
void add(const int x, const int y, const int z) {
    nxt[++num] = head[x]; to[num] = y; head[x] = num; dis[num] = z;
    nxt[++num] = head[y]; to[num] = x; head[y] = num; dis[num] = z;
}
int NUM = 1, NXT[M], TO[M], DIS[M]={inf}, HEAD[N];
void Add(const int x, const int y, const int z) {
    NXT[++NUM] = HEAD[x]; TO[NUM] = y; HEAD[x] = NUM; DIS[NUM] = z;
    NXT[++NUM] = HEAD[y]; TO[NUM] = x; HEAD[y] = NUM; DIS[NUM] = z;
}

int dep[N], s, t;
bool bfs() {//建立层次图
    queue<int> q;
    memset(dep, 0, sizeof(dep));
    dep[s] = 1; q.push(s);
    while (!q.empty()) {
        const int x = q.front(); q.pop();
        for (int i = head[x]; i; i = nxt[i]) {//遍历x的所有邻接边
            int u = to[i];//获取边的终点
            if (dep[u] || dis[i] <= 0) continue;//跳过已访问节点或残量为0的边
            dep[u] = dep[x] + 1;//设置u的深度
            q.push(u);//将u加入队列
        }
    }
    return dep[t];//返回汇点是否可达
}

int dfs(const int x, int flow) {
    if (x == t || !flow) return flow;//到达汇点或流量为0
    int tot = 0;//累计增广流量
    for (int i = head[x]; i; i = nxt[i]) {
        const int u = to[i];
        if (dep[u] != dep[x] + 1 || dis[i] <= 0) continue;//只走层次图中的边
        const int fl = dfs(u, min(flow, dis[i]));//递归增广
        dis[i] -= fl; dis[i^1] += fl;//更新正向边和反向边容量
        flow -= fl; tot += fl;//更新剩余流量和总增广量
        if (!flow) break;//流量用完则跳出
    }
    if (!tot) dep[x] = -1;//如果没有增广到，标记该点不可达
    return tot;//返回增广总量
}

int mx_flow(const int tx, const int ty) {//从tx到ty的最大流
    s = tx; t = ty;
    int tot = 0;//累计最大流
    while (bfs()) {//直到无法建立层次图
        int x = dfs(s, inf);//进行一次增广
        while (x) tot += x, x = dfs(s, inf);//重复增广直到无法增广
    }
    return tot;
}


int m, id[N], ans, b[N];
void dfs2(const int l, const int r) {//构建Gomory-Hu Tree
    if (l == r) return;
    memset(head, 0, sizeof head); num = 1;//重建邻接表
    for (int i = 1; i <= m; ++i) add(e[i].x, e[i].y, e[i].z);//添加所有原始边
    const int x = mx_flow(id[l], id[r]);//等于最小割 id[l]到id[r]的最大流
    int L = l-1, R = r+1; ans += x; Add(id[l], id[r], x);//更新答案并在最小割树中添加边
    for (int i = l; i <= r; ++i) {//可达的放左边，不可达的放右边
        if (dep[id[i]]) b[++L] = id[i]; else b[--R] = id[i];//分组
    }
    reverse(b + L + 1, b + R + 1);//反转右半部分
    for (int i = l; i <= r; ++i) id[i] = b[i];//更新id数组
    dfs2(l, L); dfs2(R, r);
}

bool vis[M];
int idx;//最小边的索引
void bfs2(const int x, const int pre) {
    for (int i = HEAD[x]; i; i = NXT[i]) {
        if (TO[i] == pre || vis[i]) continue;
        if (DIS[i] < DIS[idx]) idx = i;//找最小容量边
        bfs2(TO[i], x);
    }
}

void dfs3(const int x) {//遍历最小割树
    idx = 0; bfs2(x, x);//找当前节点的最小边
    if (idx == 0) { cout << x << ' '; return; }//如果没有边，输出节点
    vis[idx] = vis[idx^1] = true;//标记边已访问
    const int u = TO[idx], v = TO[idx^1];//获取边的两端点
    dfs3(u), dfs3(v);//递归遍历两端
}

int main() {
    fast;
    int n; cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> e[i].x >> e[i].y >> e[i].z;
    for (int i = 1; i <= n; ++i) id[i] = i;//初始化节点ID数组
    dfs2(1, n);
    cout << ans << '\n';//输出最小割的和
    dfs3(1);//遍历并输出最小割树
    return 0;
}