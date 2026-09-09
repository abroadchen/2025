//
// Created by Psy.C on 2026/9/9.
//
/**
VI：二维整数向量。x{},y{} 默认零初始化。
+/-：向量加减。
&（叉积）：u.x*v.y - u.y*v.x，返回 long long 防溢出。叉积符号判断两向量相对方向。
!（逻辑非重载，此处表示 "half-plane"）：判断点是否在上半平面（y>0，或 y==0 且 x>=0）。
operator<：按极角排序。先按所在半平面分类，同半平面再按叉积正负（(u&v)>0 表示 u 的极角在 v 之前）。这是极角排序的标准比较器。
r[N]：存多边形顶点（相对原点），O 为某参考原点
VD：long double 的浮点向量，用于存储交点、做几何计算。
可从 VI 隐式构造（VD(VI P)）。
& 叉积、* 标量、/ 标量` 对应数乘和除。
p[] 数组存放半平面交点（凸多边形顶点）
Line：有向线段/半平面。存储端点 x,y 和方向向量 z = y - x。
Line&Line：两直线求交点，参数形式求交点坐标（UX + UZ * ((VZ&(UX-VX))/(UZ&VZ))）。
Line&点：判断点 v 是否在该半平面内（在直线左侧或线上，叉积 ≤ 0 不取右侧
|（判断是否共线平行同向）：两方向向量等价（既不小于也不大于对方）。
operator<：半平面排序比较器。若共线，比较"v 起点相对 u 的位置"（同向平移取舍，保留更靠前的）；否则按方向向量极角排序。
/：判断两直线是否平行（叉积为 0）
标准鞋带公式：对多边形顶点 p[0..x-1] 求和相邻叉积，取绝对值的一半得面积

先按极角排序所有半平面，队列 q 维护栈/队，p 存相邻半平面交点。
遍历每条半平面：跳过共线重复的（l[i]|l[i-1]）；检测平行矛盾（平行不相交则无解返回 0）；从队尾、队头剔除被新半平面"切掉"（不在半平面内）的交点；压入新半平面并计算新交点。
最后清理队首队尾，若剩余 ≤2 条（无法形成多边形）返回 0。
否则求相邻交点为多边形顶点，用 area() 求面积。
返回半平面交（凸多边形）的面积；无解（交集为空或退化为线/空）返回 0

输入是多边形沿逆时针给出的各边 r[i]。为保证半平面方向一致（左侧为内），通过叉积符号决定线段方向，把每条边规约为"内部在其左侧"的有向线段，加入 l[]
读入点数 m、参考原点 O，然后把所有顶点相对 O 平移（r[i] - O）并做极角排序。
遍历每个顶点：先加它的下一条半平面 insert(i,(i+1)%m)；再用双指针 j 找"与 r[i] 叉积为正的下一个顶点"（处理凸包化/可见区域的边），也插入对应半平面。出现共线平行（!(r[i]&...)）则交集为空输出 0。
最后加四个大矩形边界（无穷远边框 A-B-C-D），把半平面交限制在有限区域内。
调用 inters() 输出面积

 */
#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

constexpr int N = 2e5+1e2, M = 6e5+1e2, inf = 1e6;
struct VI {
    int x{}, y{};
    VI() = default;
    VI(int x, int y) : x(x), y(y) {}
    friend VI operator+(const VI& u, const VI& v) { return {u.x + v.x, u.y + v.y}; }
    friend VI operator-(const VI& u, const VI& v) { return {u.x - v.x, u.y - v.y}; }
    void read() { scanf("%d%d",&x,&y); }
    void print() const { printf("(%d,%d)",x,y); }
    friend ll operator&(const VI& u, const VI& v) { return 1ll*u.x*v.y-1ll*u.y*v.x; }
    bool operator!() const { return x > 0 || x == 0 && y >= 0; }
    friend bool operator<(const VI& u, const VI& v) {
        if ((!u) != (!v)) return (!u) < (!v);
        return (u&v) > 0;
    }
} r[N], O;

struct VD {
    ld x, y;
    VD() = default;
    VD(ld x, ld y) : x(x), y(y) {}
    VD(VI P) { x = P.x; y = P.y; }
    void read() { scanf("%Lf%Lf",&x,&y); }
    void print() const { printf("(%Lf,%Lf)",x,y); }
    friend VD operator+(const VD& u, const VD& v) { return {u.x + v.x, u.y + v.y}; }
    friend VD operator-(const VD& u, const VD& v) { return {u.x - v.x, u.y - v.y}; }
    friend ld operator&(const VD& u, const VD& v) { return u.x * v.y - u.y * v.x; }
    friend VD operator*(const VD& u, const ld& v) { return {u.x * v, u.y * v}; }
    friend VD operator/(const VD& u, const ld& v) { return {u.x / v, u.y / v}; }
} p[M];

typedef VI PI;
typedef VD PD;

constexpr ld eps = 1e-9;
int cmp(ld x) {
    if (x > eps) return 1;
    if (x < -eps) return -1;
    return 0;
}

struct Line {
    PI x, y; VI z;
    Line() = default;
    Line(PI x, PI y) : x(x), y(y), z(y-x) {}
    friend PD operator&(const Line& u, const Line& v) {
        VD UX(u.x), UZ(u.z), VX(v.x), VZ(v.z);
        return UX+UZ*(VZ&(UX-VX)/(UZ&VZ));
    }
    friend bool operator&(const Line& u, const PD& v) {
        return cmp((v-u.x)&u.z) != 1;
    }
    friend bool operator|(const Line& u, const Line& v) {
        return !(u.z<v.z)&&!(v.z<u.z);
    }
    friend bool operator<(const Line& u, const Line& v) {
        if (u|v) return (u.z&(v.y-u.x)) < 0;
        return u.z<v.z;
    }
    friend bool operator/(const Line& u, const Line& v) {
        return !(u.z&v.z);
    }
    void print() const { x.print(), y.print(), z.print(), puts(""); }
} l[M];

ld area(int x) {
    ld ret = 0;
    for (int i = 0; i < x; ++i)
        ret += p[i]&p[(i+1)%x];
    return fabs(ret)/2;
}

int n, q[M], L, R;
ld inters() {
    sort(l, l+n); q[L=R=0] = 0;
    for (int i = 1; i < n; ++i) {
        if (l[i]|l[i-1]) continue;
        if (L < R && ((l[q[L]]/l[q[L+1]])||(l[q[R]]/l[q[R-1]]))) return 0;
        while (L < R && !(l[i]&p[R-1])) R--;
        while (L < R && !(l[i]&p[L])) L++;
        q[++R] = i;
        if (L != R) p[R-1] = l[q[R]]&l[q[R-1]];
    }
    while (L < R && !(l[q[L]]&p[R-1])) R--;
    while (L < R && !(l[q[R]]&p[L])) L++;
    if (R-L+1 <= 2) return 0;
    int x = 0;
    for (int i = L; i < R; ++i) p[x++] = l[q[i]]&l[q[i+1]];
    p[x++] = l[q[R]]&l[q[L]];
    return area(x);
}

void insert(int i, int j) {
    if ((r[i]&r[j]) > 0) l[n++] = Line(r[i]+O, r[j]+O);
    else l[n++] = Line(r[j]+O, r[i]+O);
}

int m;
void solve() {
    cin >> m, n = 0, O.read(), m--;
    for (int i = 0; i < m; ++i) r[i].read(), r[i] = r[i] - O;
    sort(r, r+m);
    for (int i = 0, j = 1; i < m; ++i) {
        if (!(r[i]&r[(i+1)%m])) { puts("0"); return; }
        insert(i, (i+1)%m);
        while ((r[i]&r[j]) > 0) (++j)%=m;
        if (i == j) continue;
        if (!(r[i]&r[j])) { puts("0"); return; }
        insert(i, j);
    }
    PI A(inf ,inf), B(-inf, inf), C(-inf, -inf), D(inf, -inf);
    l[n++] = Line(A, B); l[n++] = Line(B, C);
    l[n++] = Line(C, D); l[n++] = Line(D, A);
    printf("%Lf\n", inters());
}

int T;
int main() {
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}