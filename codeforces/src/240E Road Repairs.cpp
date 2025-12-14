//
// Created by Psy.C on 2025/12/13.
//
/*
*u: 起点
v: 终点
w: 当前权重（会随着算法进行而变化）
ww: 原始权重
p: 父边索引
*used[N*20]{}: 记录使用的边信息，初始化为0
n=0, m=0, tot=0: 节点数、边数、总边数计数器，初始化为0
in[N]{}: 每个节点的最小入边权重，初始化为0
pre[N]{}: 每个节点的前驱节点，初始化为0
pre2[N]{}: 每个节点的前驱边索引，初始化为0
vis[N]{}: 访问标记数组，初始化为0
id[N]{}: 缩点后的节点ID，初始化为0
us[N*20]{}: 边使用计数器，初始化为0
 *
*rt是根节点
ret存储结果，tot初始化为原始边数
*初始化所有节点的最小入边为无穷大
寻找每个节点的最小入边（除自环外）
 *检查除根节点外是否有节点没有入边，如果没有则返回-1（无解）
*初始化访问标记和缩点ID数组
cnt记录环的数量
根节点的最小入边设为0
*累加最小入边权重到结果
标记前驱边的使用
寻找环结构：如果在访问过程中回到已标记的节点且不是根节点，则形成环
对环中的节点分配相同的缩点ID
 *如果没有环则算法结束
*为未分配ID的节点分配新ID
更新边信息，进行缩点操作
调整边权重：减去目标节点的最小入边权重
记录边的父子关系用于后续回溯
*更新节点数为缩点后的数量
更新根节点为其对应的缩点ID
*回溯更新边的使用情况：如果某条合成边被使用，则标记其构成边的使用
返回最小树形图的总权重
 *
 *u,v为端点，w为当前权重，ww为原始权重，p为边索引
 *
 *O(VE)，其中V是节点数，E是边数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define inf 0x3f3f3f3f
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;


struct edge { int u, v, w, ww, p; } e[N];
struct mst {
    struct node { int pre, p; } used[N*20]{};
    int tot=0, in[N]{}, pre[N]{}, pre2[N]{}, vis[N]{}, id[N]{}, us[N*20]{};
    int f(int rt, int n, const int m) {
        int ret = 0; tot = m;
        while (true) {
            rep(i,n) in[i] = inf;
            rep(i,m) {
                const int u = e[i].u, v = e[i].v, w = e[i].w, p = e[i].p;
                if (w < in[v] && u != v) in[v] = w, pre[v] = u, pre2[v] = p;
            }
            rep(i,n) if (i != rt && in[i] == inf) return -1;
            rep(i,n) vis[i] = id[i] = 0;
            int cnt = 0; in[rt] = 0;
            rep(i,n) {
                int v = i; ret += in[v];
                if (v != rt) ++us[pre2[v]];
                while (vis[v] != i && v != rt && !id[v]) vis[v] = i, v = pre[v];
                if (v != rt && !id[v]) {
                    ++cnt;
                    for (int u = pre[v]; u != v; u = pre[u]) id[u] = cnt;
                    id[v] = cnt;
                }
            }
            if (!cnt) break;
            rep(i,n) if (!id[i]) id[i] = ++cnt;
            rep(i,m) {
                const int v = e[i].v;
                e[i].u = id[e[i].u]; e[i].v = id[e[i].v];
                if (e[i].u != e[i].v) {
                    e[i].w -= in[v], ++tot;
                    used[tot].pre = pre2[v];
                    used[tot].p = e[i].p;
                    e[i].p = tot;
                }
            }
            n = cnt;
            rt = id[rt];
        }
        for (int i = tot; i > m; --i) if (us[i]) {
            ++us[used[i].p], --us[used[i].pre];
        }
        return ret;
    }
} d;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    int n, m; cin>>n>>m;
    rep(i,m) {
        int u, v, w; cin>>u>>v>>w;
        e[i] = {u,v,w,w,i};
    }
    const int ret = d.f(1, n, m);
    if (ret == 0 || ret == -1) return cout << ret << '\n', 0;
    cout << ret << '\n';
    rep(i,m) if (d.us[i] && e[i].ww) cout << i << ' ';
    return 0;
}