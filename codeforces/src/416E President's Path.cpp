//
// Created by Psy.C on 2026/2/3.
//
/**
 *
 *
* f[i][j]：最短路径距离矩阵
g[i][j]：原始边权矩阵
初始化：所有距离设为无穷大，对角线保持0
*更新矩阵：双向边，取最小值
复制矩阵：g保存原始边权
 *
*外层循环：以s为源点
tmp[t]：统计从s出发经过邻边到达t的路径数
第一内层：if (f[s][k] + g[k][t] == f[s][t])，检查是否是最短路径
第二内层：累加所有可能的中转点的路径数
 *
*时间复杂度：O(n³)
空间复杂度：O(n²)
 *
*[1,2] [1,3] [1,4]  (i=1时)
      [2,3] [2,4]  (i=2时)
            [3,4]  (i=3时)
                   (i=4时，j从5开始>n，不输出)
这就是矩阵的上三角区域，也称为严格上三角区域（不包含对角线
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
#define N 505
#define M 125005
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

constexpr ull inf = 1e17;

struct node { int x, y, l; } e[M];//起点x、终点y、长度l

int main() {
    fast;
    int n, m, i, j, k, s, t; cin >> n >> m;//节点数n和边数m
    ull f[N][N], g[N][N];
    rep(i,n) rep(j,n) {
        g[i][j] = inf;
        if (i == j) continue;
        f[i][j] = inf;
    }
    rep(i,m) {
        cin >> e[i].x >> e[i].y >> e[i].l;
        f[e[i].x][e[i].y] = min(f[e[i].x][e[i].y], static_cast<ull>(e[i].l));
        f[e[i].y][e[i].x] = min(f[e[i].y][e[i].x], static_cast<ull>(e[i].l));
        g[e[i].x][e[i].y] = f[e[i].x][e[i].y];
        g[e[i].y][e[i].x] = f[e[i].y][e[i].x];
    }
    rep(k,n) rep(i,n) rep(j,n) f[i][j] = min(f[i][j], f[i][k]+f[k][j]);
    int ans[N][N];
    rep(s,n) {
        static int tmp[N];
        rep(i,n) tmp[i] = 0;
        rep(t,n) rep(k,n) if (f[s][k] + g[k][t] == f[s][t]) tmp[t]++;
        rep(t,n) rep(i,n) if (f[s][i] + f[i][t] == f[s][t]) ans[s][t] += tmp[i];
    }
    rep(i,n) for (j = i + 1; j <= n; ++j) {//输出上三角矩阵（i < j）
        if (f[i][j] >= inf) cout << "0 ";
        else cout << ans[i][j] << ' ';
    }
    cout << '\n';
    return 0;
}