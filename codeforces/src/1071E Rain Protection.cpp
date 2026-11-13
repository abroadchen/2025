//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
Andrew 凸包算法：最低点为基准，按极角排序后单调栈维护逆时针凸包（叉积判断转向，> -eps 即需弹栈，去掉凹点）。返回值是凸包顶点数（含闭合的重复起点，所以数组末尾是 bs）
对多边形每个顶点，用 (±t, ±t) 四个方向加偏置生成 4 个点（一个边长为 2t 的"方盘"），把这 4n 个点合并 → 再求凸包。效果：把多边形沿"切比雪夫(L∞)范数"膨胀距离 t，即生成"多边形在 L∞ 度量下偏移 t 的 Minkowski 和"。几何上是把原框变"圆角方形"的膨胀
对每个边 (a[i],a[i+1])，叉积 (边)×(v-起点) 若 < -eps 说明点在边的右侧（外侧）‍→ 不在多边形内。全部在内→返回真。要求多边形逆时针且闭合（a[n] 存在）
c[] 代表当前可达区域多边形。每过一个事件时间步 (t[i]-t[i-1])，点以速度 × mid 移动，把可行区域做 L∞ 膨胀（Minkowski 和），得到新时刻点的可达区域
遍历多边形每条边 (c[j], c[j+1]) 与**当前时刻的障碍线段 (a[i],b[i])**求交，收集交点 d[0..p-1]（去重）
p==0：多边形与障碍线段无交点。若障碍起点在多边形外，说明点已被障碍切到/移出边界 → 返回失败（0）。否则障碍完全在多边形内，可移动区域应被"切掉"成障碍线段，c 变为 [a[i],b[i]]。
p==1：交点为单个。根据障碍端点 <code>a[i]</code>/<code>b[i] 在多边形内外的组合，把 c 收缩成一个线段（保留多边形内部分的边界点）。
p≥2：障碍线与多边形交于两点，用 d[0],d[1] 作为新的"可移动区间端点"。
最终 c[0],c[1] 表示当前时刻仅剩的可移动区域（可退化成一个点或一条线段）‍。返回 1（可行性成立）。

核心思想：点拥有一定速度，障碍（竖直线段）在 x 方向匀速扫过。算法用逆时间推进：每步做可达域膨胀，再用障碍线段"裁剪"可达域；若可达域被裁空或点在障碍外 → 该速度(mid)下必撞
一个 w×h 的矩形（屏幕/画布），e 为起点（摄像机/点位置）‍。对每个事件（时间 tt，位置 (x,y)）做透视/投影变换：把位于透视逃逸点的障碍（射线）投影到矩形左右/上下边界，得到线段端点 u,v（这两行在做点 (x,y) 通过起点 e 的直线与宽/高边界的交点）
若时间 tt 和前一条不同 → 新的一段障碍（用线段 (u,v)）。
若同一时刻线段已退化（a[q]==b[q]）→ 检查与当前点是否共线等一致性，否则 err 报错。
若同一时刻但坐标不同 → 把当前这条与上一条线段求交合并成新点到当前线段 (a[q],b[q])（裁剪/求交后继续维护障碍段）。若求交为 NaN（不相交的平行线段）→ err。
这一步在做同一时刻多障碍的归并：同一时刻多线程射线通过交点合成一条有效的遮挡边
在 [0, w] 上二分速度（或 time 缩放系数）mid。check(q,mid) 可行为真 → 说明能更快（或刚好），右界收窄；失败 → 提高速度 l=mid。最终输出收敛值。

二分的是"点的最大允许速度（缩放 t）‍"，即求解 "恰好能让点逃过所有移动障碍的最小速度"——答案即临界速度
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<k; ++i)
#define eps 1e-8
#define db double
using namespace std;

constexpr int N = 1e5+5;
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar())(x*=10) += ch&15;
    if (f) x = -x;
    return x;
}

//判断是否为 0（考虑 eps=1e-8 误差）
inline bool is0(db x) { return fabs(x) < eps; }
struct Vec {
    db x, y;
    Vec() { x = y = 0; }//默认零向量
    Vec(db a) { x = a; y = 0; }//从标量构造 (a,0)
    Vec(db a, db b) { x = a; y = b; }
    friend istream& operator>>(istream &cin, Vec &o) {
        return o.x = rd(), o.y = rd(), cin;
    }
    Vec operator-() const { return {-x, -y}; }//取反
    Vec operator+(Vec o) const { return {x+o.x, y+o.y}; }//加减
    Vec operator-(Vec o) const { return {x-o.x, y-o.y}; }
    Vec operator*(db o) const { return {x*o, y*o}; }//数乘/数除
    Vec operator/(db o) const { return {x/o, y/o}; }
    friend Vec operator*(db a, Vec b) { b.x *= a; b.y *= a; return b; }//标量在左的数乘
    Vec& operator+=(Vec o) { x += o.x; y += o.y; return *this; }//复合赋值
    Vec& operator-=(Vec o) { x -= o.x; y -= o.y; return *this; }
    db operator*(Vec o) const { return x*o.x + y*o.y; }//点积 (⋅)
    db operator^(Vec o) const { return x*o.y - y*o.x; }//叉积 (×) 二维
    //比较按"极角 + 长度"：先按叉积判断方向角（逆时针更小），同向按长度。这是极角排序的比较器
    bool operator==(Vec o) const { return is0(x-o.x) && is0(y-o.y); }
    friend bool operator<(Vec a, Vec b) {
        return (a^b) > 0 || (is0(a^b) && Len(a) < Len(b));
    }
    friend db Len(Vec o) { return sqrt(o.x*o.x + o.y*o.y); }//向量模长。
} a[N], b[N], c[9], d[9], e;

//lncr 求两条无限直线的交点。b2^a2 是方向叉积（分母），非零则交；(b2^(b1-a1))/(b2^a2) 是交点参数。
Vec lncr(Vec a1, Vec a2, Vec b1, Vec b2) {
    a2 -= a1; b2 -= b1;
    return b2^a2 ? a1+(b2^(b1-a1))/(b2^a2)*a2 : Vec{NAN, NAN};
}
//sgcr 求两条线段的交点：先求直线交点，再用点积判断交点在两条线段上（(a1-c)·(a2-c) > 0 说明 c 不在 a1,a2 之间 → 不在线段上 → NaN）。即"两线段所在直线交点不在线段内部则返回 NaN"
Vec sgcr(Vec &a1, Vec &a2, Vec &b1, Vec &b2) {
    Vec c = lncr(a1, a2, b1, b2);
    return (a1-c)*(a2-c) > eps || (b1-c)*(b2-c) > eps ? Vec{NAN, NAN} : c;
}

int st[N];
int convex(Vec *a, int n) {
    int k = 0, p = 0; Vec bs;
    rep(i,1,n) if (a[i].y < a[k].y || (a[i].y == a[k].y && a[i].x < a[k].x)) k = i;
    swap(a[0], a[k]); bs = a[0];//找最低点（最左下）为起点
    rep(i,0,n) a[i] -= bs;//平移到原点
    sort(a+1, a+n);//按极角排序
    for (int i = 1; i < n; st[++p] = i++)//叉积 > -eps 表示非严格左转 → 弹栈（去掉左凹）
        while (p && ((a[i]-a[st[p-1]])^(a[st[p]]-a[st[p-1]])) > -eps) --p;
    rep(i,0,p+1) a[i] = a[st[i]] + bs;//还原坐标，栈内点即为凸包顶点
    return a[p+1] = bs, p+1;//闭包（末尾补起点），返回顶点数
}
int Minkowski(Vec *a, int n, db t) {
    for (int i = n-1, j = 4*n; j; --i) {
        a[--j] = a[i] + Vec(-t, -t); a[--j] = a[i] + Vec(t, -t);
        a[--j] = a[i] + Vec(t, t); a[--j] = a[i] + Vec(-t, t);
    }
    return convex(a, 4*n);
}
bool in(Vec *a, int n, Vec v) {
    rep(i,0,n) if (((a[i+1]-a[i])^(v-a[i])) < -eps) return 0;
    return 1;
}

int t[N];
bool check(int q, db mid) {
    int n = 1, p; c[0] = e;
    rep(i,1,q+1) {
        n = Minkowski(c, n, (t[i]-t[i-1])*mid);
        for (int j = p = 0; j < n; ++j) {
            d[p] = sgcr(a[i], b[i], c[j], c[j+1]);
            p += !(isnan(d[p].x) || (p && d[p-1] == d[p]));//去重：非 NaN 且不与上一点重复才计数
        }
        if (p == 0) {
            if (!in(c, n, a[i])) return 0;//无交点且障碍起点在多边形外 → 已被撞 → 失败
            c[0] = a[i], c[1] = b[i];//障碍在多边形内 → 可达区域直接缩小为障碍线段
        } else if (p == 1) {
            if (in(c, n, a[i])) c[1] = in(c,n,b[i])?(d[0]==b[i]?a[i]:b[i]):a[i];
            else c[1] = in(c, n, b[i]) ? b[i] : d[0];
            c[0] = d[0];
        } else c[0] = d[0], c[1] = d[1];//两个交点 → 用两交点切割
        n = 1 + !(c[0] == c[1]);//若两端点重合则退化为单点
    }
    return 1;
}
void err(bool f) { if (f) cout << "-1\n", exit(0); }



int main() {
    fast;
    int n = rd(), q = 0, w = rd(), h = rd(), lx = 0, ly = 0;
    cin >> e;
    rep(i,1,n+1) {
        int tt = rd(), x = rd(), y = rd();
        Vec u = 0, v = 0;
        if ((u.x=(db)x*h/(h-y)) > w) u = Vec(w,(db)(x*h-(h-y)*w)/y);//透视投影水平线到右边界
        if ((v.y=(db)x*h/y) > w) v = Vec((db)(x*h-y*w)/(h-y), w);//竖线在 y 处被 w 截断
        if (tt != t[q]) ++q, a[q] = u, b[q] = v;
        else if (a[q] == b[q]) {
            if (u == v) err(!(u==a[q]));
            else err(!is0((u-a[q])^(v-a[q])));
        } else if (x != lx || y != ly) {
            if (u == v) err(!is0((u-a[q])^(u-b[q])));
            else err(isnan((u=sgcr(a[q],b[q],u,v)).x));
            a[q] = b[q] = u;
        }
        t[q] = tt; lx = x; ly = y;
    }
    db l = 0, r = w, mid;
    while ((r-l)/max(1.0,l) > 1e-4)
        mid = (l+r)/2, (check(q,mid) ? r : l) = mid;
    cout << fixed << setprecision(6) << (l+r)/2 << '\n';
    return 0;
}