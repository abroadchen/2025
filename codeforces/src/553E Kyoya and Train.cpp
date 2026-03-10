//
// Created by Psy.C on 2026/3/10.
//
/**
N: 最大节点数
M: 最大边数
K: 辅助数组大小
L: 时间维度最大值
定义复数结构体及其基本运算（加、减、乘）
用于FFT算法的复数运算
标准Dijkstra算法实现
计算从终点到其他所有点的最短距离
dft: 离散傅里叶变换（正变换f=1，逆变换f=-1）
fft: 完整的FFT过程：正变换→点乘→逆变换→归一化

t: 时间限制
cost: 固定成本
g[i][j]: 边i在时间j的辅助DP值
f[i][j]: 节点i在时间j的最短期望距离
sum[i][j]: 边i前j时刻的概率前缀和
p[i][j]: 边i在时刻j成功的概率

分治处理时间区间[l,r]
先处理右半部分[mid+1, r]
计算FFT所需的长度和位逆序置换
对每条边进行卷积计算
A数组：概率序列
B数组：f值序列（翻转）
通过FFT加速卷积运算
递归处理左半部分

读入图的基本信息和每条边在各时刻的成功概率
计算最短路
初始化DP数组
从终点开始反向DP
输出起点在时间0的最优期望值

不使用FFT：O(m×t²)
使用FFT优化：O(m×t×log t)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pi acos(-1.)
using namespace std;
constexpr int N = 51, M = 105, K = 1e5, L = 2e4+5, inf = 1e9;

struct node { double x, y; } A[K], B[K];
node operator+(node a, node b) { return node(a.x + b.x, a.y + b.y); }
node operator-(node a, node b) { return node(a.x - b.x, a.y - b.y); }
node operator*(node a, node b) { return node(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }

int n, m, dis[N], vis[N], v[M], u[M], w[M];
void dijkstra() {
    for (int i = 0; i < n; ++i) dis[i] = inf;
    for (int i = 1; i < n; ++i) {
        int x = 0;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && dis[j] < dis[x]) x = j;
        vis[x] = 1;
        for (int j = 1; j <= m; ++j)
            if (v[j] == x) dis[u[j]] = min(dis[u[j]], dis[x] + w[j]);
    }
}

int Q, rev[K];
void dft(node *a, double f) {
    for (int i = 0; i < Q; ++i)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int len = 2; len <= Q; len <<= 1) {
        int mid = len>>1;
        double ang = 2.*pi/(double)len;
        node e(cos(ang), f*sin(ang));
        for (auto *p = a; p != a + Q; p += len) {
            node t(1., 0.);
            for (int i = 0; i < mid; ++i) {
                node tmp = t*p[mid+i];
                p[mid+i] = p[i] - tmp;
                p[i] = p[i] + tmp;
                t = t*e;
            }
        }
    }
}

void fft() {
    dft(A, 1.); dft(B, 1.);
    for (int i = 0; i < Q; ++i) A[i] = A[i]*B[i];
    dft(A, -1.);
    for (int i = 0; i < Q; ++i) A[i].x /= (double)Q;
}

int t, cost, lg;
double g[M][L], f[N][L], sum[M][L], p[M][L];
void dfs(int l, int r) {
    if (l == r) {
        for (int i = 1; i <= m; ++i) {
            g[i][l] += (1.-sum[i][t-l])*(double)(dis[v[i]] + cost);
            f[u[i]][l] = min(f[u[i]][l], g[i][l] + (double)w[i]);
        }
        return;
    }
    int mid = (l + r) >> 1;
    dfs(mid + 1, r);
    Q = 1, lg = 0;
    while (Q < 2*r - l - mid) Q <<= 1, lg++;
    for (int i = 0; i < Q; ++i) rev[i] = 0;
    for (int i = 0; i < Q; ++i)
        for (int j = 0; j < lg; ++j)
            if (i&1<<j) rev[i] |= 1<<(lg-j-1);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= r-l; ++j) A[j-1] = {p[i][j], 0.};
        for (int j = 1; j <= r-mid; ++j) B[j-1] = {f[v[i]][mid+j], 0.};
        for (int j = 0; r-mid-1-j > j; ++j) swap(B[j], B[r-mid-1-j]);
        for (int j = r-l; j < Q; ++j) A[j] = {0., 0.};
        for (int j = r-mid; j < Q; ++j) B[j] = {0., 0.};
        fft();
        for (int j = l; j <= mid; ++j) g[i][j] += A[r-j-1].x;
    }
    dfs(l, mid);
}


int main() {
    fast;
    cin >> n >> m >> t >> cost;
    for (int i = 1; i <= m; ++i) {
        cin >> u[i] >> v[i] >> w[i];
        sum[i][0] = 0.;
        for (int j = 1, x; j <= t; ++j) {
            cin >> x;
            p[i][j] = (double)x/100000.;
            sum[i][j] = sum[i][j-1] + p[i][j];
        }
    }
    dijkstra();
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= t; ++j) f[i][j] = 6e7;
    for (int j = 0; j <= t; ++j) f[n][j] = 0.;
    dfs(0, t);
    printf("%.10lf\n", f[1][0]);
    return 0;
}