//
// Created by Psy.C on 2026/2/1.
//
/**
* 排序：O(m log m)
DP计算：O(m)
答案统计：O(m)
总体：O(m log m)

复制前一项中不同类型的数据到当前位置
!tp：逻辑非，0变1，1变0
memcpy：内存复制函数
sizeof f[1][1]：复制整个状态数组

f[1][1]  // 指向 f[1][1][0] 的指针
f[1][1]本身是一个一维数组node[3]
等价于 &f[1][1][0]

g[tp][i+1][0].v：从位置i+1到末尾，类型tp的最大值
f[tp][i-1][1].v：从开头到位置i-1，类型tp的最小值
v1 = 2*max - 2*min：最大化差值（乘2是为了整数化）

2*n：常数项
-2*x：当前位置值的影响
+2*f[!tp][i-1][0].v：前缀中不同类型的最大值
g[tp][i+1][2].n：后缀中同类型元素的数量

v1 = 2*n：固定价值
n1 = 前缀不同类数量 * 后缀不同类数量：方案数

2*n：常数项
-2*g[!tp][i+1][1].v：减去后缀中不同类型的最小值
+2*x：加上当前位置值
f[tp][i-1][2].n：前缀中同类型的数量
g[!tp][i+1][1].n：后缀中不同类型最小值的数量


 */
#include <algorithm>
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+10, inf = 1e9+7;
struct node {
    int v; ll n;//价值和方案数
    explicit node(const int a=0, const ll b=0) : v(a), n(b) {}//禁止隐式类型转换
} f[2][N][3], g[2][N][3], ans;//前缀 后缀  2种类型，N个位置，3种状态(最大值 最小值 计数)

inline void update(const int v, const ll n) {
    if (!n) return;//数量为0
    if (v > ans.v) ans = node{v, n};//按价值最大原则更新答案
    else if (v == ans.v) ans = node(v, n + ans.n);//价值相同时累加方案数
}

int main() {
    fast;
    int n, m, i; cin >> n >> m;
    ii a[N];
    for (i = 1; i <= m; ++i) cin >> a[i].second >> a[i].first;
    sort(a + 1, a + m + 1);
    f[0][0][1].v = f[1][0][1].v = g[0][m+1][1].v = g[1][m+1][1].v = inf;//边界条件
    for (i = 1; i <= m; ++i) {
        const int tp = a[i].second, x = a[i].first;//当前项的类型 值
        memcpy(f[!tp][i], f[!tp][i-1], sizeof f[1][1]);//不变类型继承
        //当前值比之前最大值大，更新最大值，数量为1
        if (x > f[tp][i-1][0].v) f[tp][i][0] = node{x, 1};
        //等于之前最大值，更新最大值，数量加1
        else if (x == f[tp][i-1][0].v) f[tp][i][0] = node{x, f[tp][i-1][0].n+1};
        //保持之前的值不变
        else f[tp][i][0] = f[tp][i-1][0];//最大值更新
        //当前值比之前最小值小，更新最小值，数量为1
        if (x < f[tp][i-1][1].v) f[tp][i][1] = node{x, 1};
        //等于之前最小值，更新最小值，数量加1
        else if (x == f[tp][i-1][1].v) f[tp][i][1] = node{x, f[tp][i-1][1].n+1};
        //保持之前的最小值不变
        else f[tp][i][1] = f[tp][i-1][1];//最小值更新
        f[tp][i][2].n = f[tp][i-1][2].n+1;//计数更新
    }
    for (i = m; i; --i) {
        const int tp = a[i].second, x = a[i].first;
        memcpy(g[!tp][i], g[!tp][i+1], sizeof g[1][1]);//复制后一项中不同类型的数据
        if (x > g[tp][i+1][0].v) g[tp][i][0] = node{x, 1};
        else if (x == g[tp][i+1][0].v) g[tp][i][0] = node{x, g[tp][i+1][0].n+1};
        else g[tp][i][0] = g[tp][i+1][0];
        if (x < g[tp][i+1][1].v) g[tp][i][1] = node{x, 1};
        else if (x == g[tp][i+1][1].v) g[tp][i][1] = node{x, g[tp][i+1][1].n+1};
        else g[tp][i][1] = g[tp][i+1][0];
        g[tp][i][2].n = g[tp][i+1][2].n+1;
    }
    for (i = 2; i <= m-1; ++i) {
        const int tp = a[i].second, x = a[i].first;
        //第一种配对方案的价值和数量
        int v1 = 2*g[tp][i+1][0].v - 2*f[tp][i-1][1].v;
        ll n1 = g[tp][i+1][0].n * f[tp][i-1][1].n;
        update(v1, n1);
        v1 = 2*n - 2*x + 2*f[!tp][i-1][0].v, n1 = f[!tp][i-1][0].n * g[tp][i+1][2].n;
        update(v1, n1);
        v1 = 2*n, n1 = f[!tp][i-1][2].n * g[!tp][i+1][2].n;
        update(v1, n1);
        v1 = 2*n - 2*g[!tp][i+1][1].v + 2*x, n1 = f[tp][i-1][2].n * g[!tp][i+1][1].n;
        update(v1, n1);
    }
    cout << ans.n << '\n';
    return 0;
}