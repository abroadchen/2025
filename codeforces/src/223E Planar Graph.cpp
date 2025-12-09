//
// Created by Psy.C on 2025/12/9.
//
/*
*v: 目标节点
w: 边的权重/流量
rk: 排名/序号
nxt: 链式前向星的下一个边
tt: 角度值
*tot初始化为1（用于链式前向星，从2开始编号）
head数组存储每个节点的第一条边的索引
 *声明映射，用于存储边(u,v)对应的边索引
*tot自增，为新边分配编号
设置边的目标节点为v
设置边的next指针指向当前head[u]
更新head[u]为新边的编号
在id映射中记录边{u,v}对应的编号
 *
*标记节点u为已访问，初始化flow为1
遍历u的所有邻接边
如果目标节点未访问，则递归调用dfs
更新正向边和反向边的权重（利用异或操作i^1获取反向边）
累加流量并返回
 *
*pre数组存储每个节点的边信息
b数组用于临时存储查询点
sum数组存储每个节点的总权重
 *
*读入查询点数量k
初始化答案ans为k（至少包含k个点）
初始化面积计算变量mm为0
 *读入k个查询点的编号
*使用叉积公式计算多边形的有向面积：
利用鞋带公式计算多边形面积的两倍
1ll用于防止整数溢出
 *如果面积为负（说明点的顺序是顺时针），则反转点的顺序
 *
*对于多边形的每条边：
l获取当前点到下一点的边的排名
r获取当前点到上一点的边的排名
计算在角度范围内的权重和并加到答案中
如果l>r（跨越了角度0），则加上总的权重和
 *
 *寻找x坐标最小的节点作为根节点
 *从根节点开始DFS构建流量网络
*对每个节点u：
在pre[u]中添加初始值0
遍历u的所有邻接边：
将边索引添加到pre[u]
累加边权重到sum[u]
计算该边的角度值
 *按角度值对pre[u]进行排序，0元素排在最后
 *
*为每条边分配排名rk
计算pre数组的前缀和
 *
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100007
#define M 200007
#define ii pair<int,int>
using namespace std;

int n, m;
struct vec { int x, y; } a[N];
struct edge { int v, w, rk, nxt; double tt; } e[M];

int tot=1, head[N];
map<ii, int> id;
void add(int u, int v) {
    e[++tot].v = v; e[tot].nxt = head[u]; head[u] = id[{u, v}] = tot;
}

int vis[N];
int dfs(const int u) {
    int flow = vis[u] = 1;
    for (int i = head[u], f; i; i = e[i].nxt) if (!vis[e[i].v]) {
        f = dfs(e[i].v);
        e[i].w += f; e[i^1].w -= f;
        flow += f;
    }
    return flow;
}


vector<int> pre[N];
int b[N], sum[N];
void f() {
    int k; cin >> k; int ans = k; ll mm = 0;
    for (int i = 0; i < k; ++i) cin >> b[i];
    for (int i = 0; i < k; ++i) mm += 1ll * a[b[i]].x * a[b[(i+1)%k]].y -
        1ll * a[b[i]].y * a[b[(i+1)%k]].x;
    if (mm < 0) reverse(b, b + k);
    for (int i = 0, l, r; i < k; ++i) {
        l = e[id[{b[i], b[(i+1)%k]}]].rk;
        r = e[id[{b[i], b[(i+k-1)%k]}]].rk;
        ans += pre[b[i]][r] - pre[b[i]][l-1];
        if (l > r) ans += sum[b[i]];
    }
    cout << ans << '\n';
}

int q;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) cin >> u >> v, add(u, v), add(v, u);
    for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
    int root;
    for (int i = root = 1; i <= n; ++i) if (a[i].x < a[root].x) root = i;
    dfs(root);
    for (int u = 1; u <= n; ++u) {
        pre[u].push_back(0);
        for (int i = head[u]; i; i = e[i].nxt) {
            pre[u].push_back(i);
            sum[u] += e[i].w;
            e[i].tt = atan2(a[e[i].v].y - a[u].y,
                a[e[i].v].x - a[u].x);
        }
        sort(pre[u].begin(), pre[u].end(), [](const int i, const int j) {
            return !i ? 1 : !j ? 0 : e[i].tt < e[j].tt;
        });
        for (int i = 1; i < static_cast<int>(pre[u].size()); ++i) {
            e[pre[u][i]].rk = i;
            pre[u][i] = pre[u][i-1] + e[pre[u][i]].w;
        }
    }
    for (cin >> q; q; --q) f();
    return 0;
}