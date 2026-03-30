//
// Created by Psy.C on 2026/3/30.
//
/**
mx[i][j]: 从位置i开始长度为2^j的区间的最大值
mn[i][j]: 从位置i开始长度为2^j的区间的最小值
v[i]: 价值数组（乘以100）
c[i]: 成本数组
l2[i]: log₂(i)的整数部分
构建稀疏表用于O(1)区间最值查询
预计算log₂值用于查询
O(1)查询区间[l,r]的最大价值和最小成本
寻找从位置x开始的最大价值 ≤ 最小成本的最长区间
mv: 区间[x,m]的最大价值
mc: 区间[x,m]的最小成本
当 mv <= mc 时，可以继续扩展区间
q[x] = min(mv, mc): 在区间[x,l]内能得到的最优值
如果还能扩展：min(max(mv, v[l+1]), min(mc, c[l+1]))
q[i]是第i小的值（已排序）
选择k个元素时，第i小的元素成为第1小的概率是： P = C(k-1, n-i) / C(k, n)
f = k/n: 第1小元素的概率
f *= (n-k-i+1)/(n-i): 递推到下一个概率
时间复杂度约为O(n log n + n²)，其中RMQ构建O(n log n)，二分搜索O(n²)，排序O(n log n)
C(n-i, k-1) / C(n, k) = [C(n-i+1, k-1) / C(n, k)] × [(n-k-i+1)/(n-i+1)]

mx[i][0]: 从位置i开始，长度为2⁰=1的区间的最大值
mn[i][0]: 从位置i开始，长度为2⁰=1的区间的最小值
本质上就是单个元素的值
j: 当前处理的区间长度指数（区间长度为2^j）
D: 区间长度（D = 2^j）
H: 区间长度的一半（H = 2^(j-1)）
mx[i][j]: 从位置i开始，长度为2^j的区间的最大值
这个区间可以分为两半：
左半：[i, i+H-1]，长度为H=2^(j-1)，最大值是mx[i][j-1]
右半：[i+H, i+D-1]，长度为H=2^(j-1)，最大值是mx[i+H][j-1]
整个区间的最大值 = max(左半最大值, 右半最大值)

l2[i]存储floor(log₂(i))的值
在循环中，当D=2^j时，对所有i ∈ [H, D) = [2^(j-1), 2^j)，设置l2[i] = j-1
在查询时，对于长度为L的区间，我们需要找到最大的k使得2^k ≤ L，即k = floor(log₂(L))。
循环结束后，处理剩余的i值（当D > n时循环停止）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
using namespace std;
constexpr int N = 1e6+5, M = 21;

int n, mx[N][M], mn[N][M], v[N], c[N], l2[N];
void build() {
    for (int i = 1; i <= n; ++i)
        mx[i][0] = v[i], mn[i][0] = c[i];
    int j, D, H;
    for (j=1, D=2, H=1; D <= n; ++j, D<<=1, H<<=1) {
        for (int i = 1; i+D-1 <= n; ++i) {
            mx[i][j] = max(mx[i][j-1], mx[i+H][j-1]);
            mn[i][j] = min(mn[i][j-1], mn[i+H][j-1]);
        }
        for (int i = H; i < D; ++i) l2[i] = j-1;
    }
    for (int i = H; i <= n; ++i) l2[i] = j-1;
}

void query(int l, int r, int &mv, int &mc) {
    int k = l2[r-l+1];
    mv = max(mx[l][k], mx[r-(1<<k)+1][k]);
    mc = min(mn[l][k], mn[r-(1<<k)+1][k]);
}

int q[N];
void get(int x) {
    int l = x, r = n + 1, m, mv, mc;
    while ((l+1)^r) {//等价于 (l+1) != r
        m = (l+r)>>1;
        query(x, m, mv, mc);
        if (mv <= mc) l = m; else r = m;
    }
    query(x, l, mv, mc);
    q[x] = min(mv, mc);
    if (l < n)
        q[x] = max(q[x], min(max(mv, v[l+1]),
            min(mc, c[l+1])));
}

int k;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> v[i], v[i] *= 100;
    for (int i = 1; i <= n; ++i) cin >> c[i];
    build();
    for (int i = 1; i <= n; ++i) get(i);
    sort(q + 1, q + n + 1);
    ld ans = 0, f = (ld)k/n;
    for (int i = 1; i <= n-k+1; ++i) {
        ans += f*q[i];
        f *= (ld)(n-k-i+1)/(n-i);
    }
    cout << fixed << setprecision(7) << ans << '\n';
    return 0;
}