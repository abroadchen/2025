//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
sq(x)：平方。
P：点（x,y）。
C：圆（圆心 o、半径平方 r2）。用半径平方避免开方、提高精度。
两点距离平方
读入每个点，同时统计是否有点的 y>0（f1）和有点 y<0（f2）。
若两类的点都存在（上下都有点），则无法用圆心在 x 轴上的圆覆盖全部 → 输出 -1 直接结束。这是本题的核心限制
用梅森旋转随机数生成器把点数组打乱。这是"增量法求最小圆"的标准优化——随机顺序能保证期望 O(n)（否则最坏 O(n³)）
初始圆：圆心 (0,0)、半径 0。
增量遍历每个点：若点 a[i] 在现有圆外，则需要把圆扩大到包含它，进入内层重建
先设一个"以该点为直径上端"的候选圆：圆心 (a[i].x, a[i].y/2)（即该点正下方、x 轴上方的中点），半径 |a[i].y/2|——这个圆是该点"最小且圆心在 x 轴的圆"（x 轴上圆心、该点恰在圆顶）
内层遍历此前已处理的点 a[j]：若 a[j] 也不在当前圆外则不管；若在外，则当前圆必须同时覆盖 a[i] 和 a[j]：
先判断以 a[j] 的"最小圆"（圆心 (a[j].x, a[j].y/2)、半径 |a[j].y/2|）能否覆盖 a[i]：若能（dist < sq），则以 a[j] 为准（把 c 设为 a[j] 的最小圆）。
否则，a[i] 和 a[j] 需要由一个"同时过两点的圆"来确定 → 调用 get(a[i], a[j])
给定两点 p、q，求一个圆心 (X,0) 在 x 轴上的圆，同时过这两点（若有多个，取恰当的那个），返回该圆。

推导起点：点 (x,y) 在圆心 (X,0)、半径 R 的圆上 ⇔ (x-X)² + y² = R²。

展开：
(x-X)² + y² = R²
把 p、q 代入并相减消去 R²：

对 p：(p.x-X)² + p.y² = R² … ①
对 q：(q.x-X)² + q.y² = R² … ②
①-②：(p.x-X)² - (q.x-X)² + p.y² - q.y² = 0

展开平方差：

(p.x-X)² - (q.x-X)² = [(p.x-X)-(q.x-X)]·[(p.x-X)+(q.x-X)]
                    = (p.x-q.x)·(p.x+q.x-2X)
于是：

(p.x-q.x)(p.x+q.x-2X) + p.y² - q.y² = 0
化简求 X：

(p.x-q.x)(p.x+q.x) - 2X(p.x-q.x) = q.y² - p.y²
解出 X：

X = [ (p.x-q.x)(p.x+q.x) + p.y² - q.y² ] / [ 2(p.x-q.x) ]
这里代码的做法是把上面的方程重新整理为关于 X 的一元二次，并解出 X 的两个根，再选取落在 p、q 之间的那个 X，从而确定圆心。
a = p.y/2 - q.y/2                      // 一元二次的二次项系数（来自 y² 项系数差）
b = p.x*q.y - q.x*p.y                  // 一次项系数（来自交叉项）
c = (sq(q.x)+sq(q.y))*p.y/2 - (sq(p.x)+sq(p.y))*q.y/2   // 常数项
d = b² - 4ac
然后解一元二次方程 a*X² + b*X + c = 0 得到两个根 x1、x2，选落在 [min(p.x,q.x), max(p.x,q.x)] 之间的那个根作为圆心横坐标 x1（或 x2）。有了 X，圆心 y 坐标（因为圆心在 x 轴，应取 X 对应抛物线上合适值，公式里用 sq(X)/(2*p.y) - p.x/p.y*X + (sq(p.x)+sq(p.y))/(2*p.y) 反算出 o 的坐标，实际是取圆心的 y 位置使 p、q 到 o 等距）。

特殊分支：if (abs(a) < eps) 处理二次项系数≈0（即 p.y≈q.y，两点等高）时，退化为一元一次情形，直接返回以两点中点为基准的圆。
最终：
以 p 到圆心 o 的距离平方作为该圆半径平方返回
最终得到最小圆后，sqrt(c.r2) 输出半径，固定 10 位小数。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define ld long double
#define sq(x) ((x)*(x))
using namespace std;

constexpr int N = 1e5+2;
constexpr ld eps = 1e-12;

struct P { double x, y; } a[N];
struct C { P o; ld r2; };

inline ld dist2(P a, P b) { return sq(a.x-b.x) + sq(a.y-b.y); }
inline ld min(ld x, ld y) { return x < y ? x : y; }
inline ld max(ld x, ld y) { return x > y ? x : y; }
inline C get(P p, P q) {
    ld a = p.y/2-q.y/2, b = p.x*q.y-q.x*p.y, c = (sq(q.x)+sq(q.y))*p.y/2-(sq(p.x)+sq(p.y))*q.y/2;
    ld d = sq(b) - 4*a*c;
    P o;
    if (abs(a) < eps) return o = {
        (p.x+q.x)/2, sq((p.x+q.x)/2)/(2*p.y)-p.x/p.y*(p.x+q.x)/2+(sq(p.x)+sq(p.y))/(2*p.y)
    }, (C){o, dist2(p,o)};
    ld t = sqrt(d); double x1 = (-b+t)/(2*a), x2 = (-b-t)/(2*a);
    if (min(p.x,q.x)-eps < x1 && x1 < max(p.x,q.x)+eps)
        return o = {x1,sq(x1)/(2*p.y)-p.x/p.y*x1+(sq(p.x)+sq(p.y))/(2*p.y)}, (C){o, dist2(p,o)};
    if (min(p.x,q.x)-eps < x2 && x2 < max(p.x,q.x)+eps)
        return o = {x2,sq(x2)/(2*p.y)-p.x/p.y*x2+(sq(p.x)+sq(p.y))/(2*p.y)}, (C){o, dist2(p,o)};
}

int n;
int main() {
    fast;
    cin >> n;
    bool f1 = 0, f2 = 0;
    rep(i,n) cin >> a[i].x >> a[i].y, f1 |= a[i].y > 0, f2 |= a[i].y < 0;
    if (f1 && f2) { cout << "-1"; return 0; }
    mt19937 rnd(random_device{}());
    shuffle(a+1, a+n+1, rnd);
    C c = {{0,0},0};
    rep(i,n) if (dist2(c.o, a[i]) > c.r2 + eps) {
        c = {{a[i].x,a[i].y/2}, sq(a[i].y/2)};
        rep(j,i-1) if (dist2(c.o,a[j]) > c.r2 + eps) {
            if (dist2({a[j].x,a[j].y/2}, a[i]) < sq(a[j].y/2))
                c = {{a[j].x,a[j].y/2}, sq(a[j].y/2)};
            else c = get(a[i], a[j]);
        }
    }
    cout << fixed << setprecision(10) << (double)sqrt(c.r2) << '\n';
    return 0;
}