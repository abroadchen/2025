//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
add / mul：支持多参数的模加、模乘（对 998244353 取模）。
作用：方便地写 mul(a,b,c) = a*b*c%mod 等
快速幂：用于求模逆元（下面 iv = ksm(?, mod-2)）。
读入 n×m 网格高度 h，并记录每个点的坐标 (x,y)。
展开为一维数组 a[1..n*m]。
按高度 h 升序排序，将瓶颈类问题按"最低高度优先"处理（类似 0-1 BFS / 最小瓶颈路径思路）
对排序后的坐标建前缀和：
x1[i] = Σ x，x2[i] = Σ x²
y_[i] = Σ y，y2[i] = Σ y²
用于后续快速计算"一组点两两间距离平方和"。
把所有高度相同的点作为一层一起处理（a[j].h == a[i].h 的一段）。

对层内每个点 j，计算 f[j]：

f[j] = (1/(i-1)) * [ sf[i-1]
       + (i-1)*(x_j² + y_j²)
       + Σx²(前面) + Σy²(前面)
       - 2*x_j*Σx(前面) - 2*y_j*Σy(前面) ]
这是经典的 "点到点集欧氏距离平方和的批量计算" 公式：

Σ_k [(x_j - x_k)² + (y_j - y_k)²]   (k 遍历前面 i-1 个点)
= (i-1)(x_j²+y_j²) + Σx²+Σy² - 2x_j·Σx - 2y_j·Σy
除以 (i-1)（即逆元 iv）得到平均值/期望，即当前点"从前面对应更高/更远点转移过来的候选值"。

sf[j] 是对 f 的前缀和，供下一层使用。

本质：类似 "每个高度层内，从所有更小高度点转移到本层点的(期望/最小)值，利用距离平方和公式 O(1) 计算"。
读入目标坐标，在排序后数组中线性查找该坐标，输出它的 f 值（即该点的 DP 结果）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1e6+10, mod = 998244353;

struct node { int x, y, h; } a[N];

int add(int x, int y) {
    x += y;
    if (x >= mod) x -= mod;
    return x;
}

template <typename T, typename ...Args>
int add(T a, T b, Args ...args) { return add(a, add(b, args...)); }
template <typename T>
int mul(T x, T y) { return 1ll * x * y % mod; }
template <typename T, typename ...Args>
int mul(T a, T b, Args ...args) { return mul(a, mul(b, args...)); }

int ksm(int x, int y) {
    int ans = 1;
    for (; y; y>>=1, x=mul(x,x))
        if (y&1) ans=mul(ans,x);
    return ans;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}

int n, m, x1[N], x2[N], y_[N], y2[N], f[N], sf[N], ex, ey;
int main() {
    fast;
    read(n, m);
    rep(i,n) rep(j,m) read(a[i*m-m+j].h), a[i*m-m+j].x = i, a[i*m-m+j].y = j;
    sort(a+1,a+n*m+1,[=](node a, node b) { return a.h < b.h; });
    for (int i = 1, x, y; i <= n*m; ++i) {
        x = a[i].x, y = a[i].y;
        x1[i] = add(x1[i-1], x); x2[i] = add(x2[i-1], mul(x,x));
        y_[i] = add(y_[i-1], y); y2[i] = add(y2[i-1], mul(y,y));
    }
    for (int i = 1, j, iv; i <= n*m; ++i) {
        iv = ksm(i-1, mod-2);
        for (j = i; j <= n*m && a[j].h == a[i].h; ++j)
            f[j] = mul(iv, add(sf[i-1],
                mul(i-1, add(mul(a[j].x, a[j].x), mul(a[j].y, a[j].y))),
                x2[i-1], y2[i-1], mul(mod-2, a[j].x, x1[i-1]),
                mul(mod-2, a[j].y, y_[i-1]))), sf[j] = add(sf[j-1], f[j]);
        i = j - 1;
    }
    read(ex, ey);
    rep(i,n*m) if (a[i].x == ex && a[i].y == ey) cout << f[i] << '\n';
    return 0;
}