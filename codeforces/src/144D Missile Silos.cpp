//
// Created by Psy.C on 2025/11/21.
//
/*
 *head:邻接表头数组, id:边的编号计数器
 *dis:距离数组, ans:答案计数器
 *vis:访问标记数组
 *fm:起点, to:终点, w:权重, ne:下一条边的索引
 *
 *时间复杂度：O((n+m)log n)（主要是Dijkstra算法的复杂度）
 */
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int N = 2e5+5, inf = 0x3f3f3f3f;
int n, m, s,//n:节点数, m:边数, s:起始节点
head[N], id, dis[N], ans;
bool vis[N];

struct Node { int fm, to, w, ne; } e[N];
void add(int u, int v, int w) {
    e[++id].fm = u; e[id].to = v; e[id].w = w;//创建新边
    e[id].ne = head[u]; head[u] = id;//插入到邻接表头部
}

struct Node2 {
    int pos{}, c{};//pos:节点位置, c:距离
    Node2() = default;
    Node2(const int pos, const int c) : pos(pos), c(c) {}
    bool operator<(const Node2& b) const { return c > b.c; }//实现小根堆
};

void dijkstra(int u) {
    memset(dis, inf, sizeof(dis));
    dis[u] = 0;//起点距离为0
    memset(vis, 0, sizeof(vis));
    priority_queue<Node2> q; q.emplace(u, 0);
    while (!q.empty()) {
        const Node2 cur = q.top(); q.pop();//取出距离最小的节点
        if (vis[cur.pos] == 1) continue;
        vis[cur.pos] = true;
        for (int i = head[cur.pos]; ~i; i = e[i].ne) {
            if (vis[e[i].to]) continue;
            if (dis[e[i].to] > dis[cur.pos] + e[i].w) {
                dis[e[i].to] = dis[cur.pos] + e[i].w;
                q.emplace(e[i].to, dis[e[i].to]);//更新节点入队
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> s;
    memset(head, -1, sizeof(head));
    for (int i = 1, a, b, w; i <= m; ++i) {
        cin >> a >> b >> w;
        add(a, b, w); add(b, a, w);
    }
    int L; cin >> L;//读取目标距离L
    dijkstra(s);//计算从s到各点的最短距离
    for (int i = 1; i <= n; ++i) if (dis[i] == L) ans++;//统计原图中距离恰好为L的节点数
    for (int i = 1; i <= id; i += 2) {//检查每条边上有多少个新增点距离恰好为L
        int u = e[i].fm, v = e[i].to, w = e[i].w;//获取边的信息
        if (dis[u] >= L && dis[v] >= L) continue;//两个端点距离都≥L
        if (dis[u] >= L && dis[v] < L) { if (dis[v]+w>L) ans++; }//检查v到u方向是否有满足条件的点
        else if (dis[v] >= L && dis[u] < L) { if (dis[u]+w>L) ans++; }//检查u到v方向是否有满足条件的点
        else {
            int u1 = L - dis[u], v1 = L - dis[v];//计算到L还需要的距离
            if (u1 + v1 == w) ans++;//恰好在中点
            else {//检查两个方向是否各有满足条件的点
                if (u1 < w && dis[v]+(w-u1)>L) ans++;
                if (v1 < w && dis[u]+(w-v1)>L) ans++;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}