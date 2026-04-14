//
// Created by Psy.C on 2026/4/14.
//
/**
du[N]: 度数数组
head[N]: 邻接表头
a[N][N]: 邻接矩阵
add: 添加无向边，更新度数和邻接表
n: 节点数
nn[N]: 每个距离的节点数
b[N][N]: 按距离分组的节点
p[N], q[N]: 概率数组

初始化概率数组：p[i] = 0
计算邻居概率：对距离为x的每个节点，向其邻居传播概率
筛选有效概率：只保留大于eps的概率值
贪心计算：对每个节点，选择不冲突的最大概率和

计算所有节点对之间的最短路径
对每个起始节点i：
按距离分组：将节点按到i的距离分组
计算贡献：对每组节点计算概率贡献
如果组大小为1，贡献为1/n
如果组大小>1，使用get函数计算最大贡献

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-9
using namespace std;
constexpr int N = 405;

struct node { double p; int x; } A[N];///概率和索引
struct edge { int s, n; } e[N*N];///终点、下一条边
int du[N], head[N], cnt, a[N][N];
void add(int x, int y) {
    du[x]++, du[y]++;
    a[x][y] = a[y][x] = 1;
    e[++cnt] = {y, head[x]}, head[x] = cnt;
    e[++cnt] = {x, head[y]}, head[y] = cnt;
}
double max(double x, double y) {
    if (x > y) return x;
    return y;
}

int n, nn[N], b[N][N];
double p[N], q[N];
double get(int x) {
    int i, j, k, tot = 0;
    for (i = 1; i <= n; ++i) p[i] = 0.;
    for (i = 1; i <= nn[x]; ++i)
        for (k = head[b[x][i]]; k; k = e[k].n)
            p[e[k].s] += 1./(1.*n*du[b[x][i]]);
    for (i = 1; i <= n; ++i) if (p[i] > eps) {
        A[++tot].p = p[i];
        A[tot].x = i;
    }
    double ans = 0., now;
    for (i = 1; i <= n; ++i) {
        now = 0.;
        for (j = 1; j <= tot; ++j) q[a[i][A[j].x]] = 0.;
        for (j = 1; j <= tot; ++j) if (A[j].p > q[a[i][A[j].x]]) {
            now += A[j].p - q[a[i][A[j].x]];
            q[a[i][A[j].x]] = A[j].p;
        }
        ans = max(ans, now);
    }
    return ans;
}

int m, i, j, x, y, k;
double now, ans;
int main() {
    fast;
    memset(a, 60, sizeof(a));
    cin >> n >> m;
    for (i = 1; i <= n; ++i) a[i][i] = 0;
    for (i = 1; i <= m; ++i) {
        cin >> x >> y; add(x, y);
    }
    for (k = 1; k <= n; ++k)
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= n; ++j)
                if (a[i][k] + a[k][j] < a[i][j])
                    a[i][j] = a[i][k] + a[k][j];
    for (i = 1; i <= n; ++i) {
        now = 0.;
        for (j = 0; j < n; ++j) nn[j] = 0;
        for (j = 1; j <= n; ++j) {
            k = a[i][j];
            b[k][++nn[k]] = j;
        }
        for (j = 0; j < n; ++j) if (nn[j]) {
            if (nn[j] == 1) now += 1./(1.*n);
            else now += max(1./(1.*n), get(j));
        }
        ans = max(ans, now);
    }
    printf("%.9lf\n", ans);
    return 0;
}