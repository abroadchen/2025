//
// Created by Psy.C on 2025/12/21.
//
/*
*dist[N][N]：二维距离数组，存储任意两点间最短距离
tot：边计数器，初始为0
*a, b：边的两个端点（输入为1-indexed，转换为0-indexed）
w：边的权重
更新距离矩阵：dist[a][b] = dist[b][a] = w（无向图）
将边信息存储到边数组中
*枚举中间点k，起点i，终点j
如果i==j，距离为0
更新最短距离：dist[i][j] = min(原距离, i到k距离+k到j距离)
 *
 *x[N]：临时数组，用于存储距离信息
*遍历每一条边：
u, v：当前边的两个端点
*对于每个节点j，计算其到u和v的距离
存储在x[j]中：first是到u的距离，second是到v的距离
*t初始化为n-1（最后一个元素索引）
对x数组按first（到u的距离）进行排序
 *考虑以u为根的生成树直径：2倍最远点到u的距离
*从后往前遍历排序后的数组：
如果当前点到v的距离大于之前记录点到v的距离：
计算直径：max(到u距离, 到v距离)的最小值
更新答案
更新t为当前索引
 *考虑以v为根的生成树直径：2倍最远点到v的距离
 *
 *时间复杂度为O(n³)，适用于节点数较少的图。
 *
 *
*1. x[t].second
节点t到节点v的距离
这里的t是满足某种条件的最优节点索引
2. x[j].first
节点j到节点u的距离
j是从后往前遍历的当前节点
3. e[i].val
边(u,v)的权重
即节点u到节点v的距离
 *
 */
#include <iomanip>
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 205
#define inf 0x3f3f3f3f
#define ii pair<int, int>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

struct edge { int fr, to, val; } e[N*N];//起点(fr)、终点(to)、权重(val)

int main() {
    fast;
    int n, m; cin >> n >> m;//节点数n和边数m
    int dist[N][N], tot = 0;
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 0, a, b, w; i < m; ++i) {
        cin >> a >> b >> w; a--; b--;
        dist[a][b] = dist[b][a] = w;
        e[tot++] = { a, b, w };
    }
    rep(k,n) rep(i,n) rep(j,n) {
        if (i == j) dist[i][j] = 0;
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
    int ans = inf;
    ii x[N];
    rep(i,tot) {
        const int u = e[i].fr, v = e[i].to;
        rep(j,n) x[j] = {dist[j][u], dist[j][v]};
        int t = n - 1;
        sort(x, x + n);
        ans = min(ans, x[n-1].first * 2);
        for (int j = n - 2; j >= 0; --j) if (x[j].second > x[t].second) {
            ans = min(ans, x[t].second + x[j].first + e[i].val);
            t = j;
        }
        ans = min(ans, x[t].second * 2);
    }
    cout << fixed << setprecision(10) << ans / 2. << '\n';//除以2是因为直径是往返距离
    return 0;
}