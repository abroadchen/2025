//
// Created by Psy.C on 2026/9/12.
//
/**
N 存储点/边数组，M 存二次函数节点（线段
二维点，支持加法（用于 walk 平移）。
a 存每个顶点
s=起点, t=终点, len=边长, agl=单位方向向量。
pre：前缀周长
一条"配对线段"的临时二次方程 a t² + b t + c，用判别式与求根公式判断交点区间。这里参数 t 表示沿某段边走多少长度时，两点的距离恰好等于 mid
每个事件：wh=位置（沿周长/段内的坐标），col=属于哪一段索引，typ=1（起点）+1 / 0（终点）-1。
排序：位置小的在前，若相同则起点(typ=1)排在终点(typ=0)后...（x.typ > y.typ）
把全局周长参数区间 [L,R] 切分成落在各段（col）内的子区间，并在每个子区间首尾打上 +/- 事件。用于后面扫描线判断"是否整段被覆盖"。
对每条"边界线段配对"（表示相邻两段的端点之间距离），求解其与"距离 = mid"的交点参数区间；若当前 mid 下这段可能产生 ≤mid 的距离，则把对应圆周/段参数区间插入。
扫描线统计：某段被覆盖的深度 cnt。若所有 m 段同时被覆盖（sz==m），说明存在一个"点把所有段都连通到距离≤mid 内"——返回可行

// 构造当前配对的 st/ed 两点（在边 s[j] 与 s[i] 上）
        // 用 walk 沿方向移动得到两个具体点 st、ed
        // 建立二次方程：|st(t)-ed|² 关于 t 的系数 a,b,c
        // b[tot].l / .r 是该配对的参数范围
 */
#include <bits/stdc++.h>
#define db double
#define eps 1e-9
using namespace std;
constexpr int N = 2e5+5, M = 4e5+5;
struct point {
    db x, y;
    point() { x = y = 0; }
    point(db x, db y) { this->x = x; this->y = y; }
    point operator+(const point &o) const { return {x + o.x, y + o.y}; }
} a[N];

//平方、两点欧氏距离
db sqr(db x) { return x * x; }
db dist(point x, point y) { return sqrt(sqr(x.x - y.x) + sqr(x.y - y.y)); }

struct line {
    point s, t, agl;
    db len, pre{};
    line() { len = pre = 0; }
    line(point S, point T) {
        s = S; t = T; len = dist(s, t);
        agl = {(t.x-s.x)/len, (t.y-s.y)/len};
    }
} s[N];

struct node {
    db l, r, a, b, c{};
    node() { l = r = a = b = 0; }
    node(db L, db R, db A, db B, db C) { l = L; r = R; a = A; b = B; c = C; }
    db delta() { return sqr(b) - 4.0*a*c; }
    db lrt() { return (-b-sqrt(delta()))/(2.0*a); }
    db rrt() { return (-b+sqrt(delta()))/(2.0*a); }
} b[M];

template<typename T>
T fabs(T x) { return x < 0 ? -x : x; }

struct range {
    db wh; int col; bool typ;
    range() { wh = 0; col = 0; typ = 0; }
    range(db X, int Y, bool Z) { wh = X; col = Y; typ = Z; }
    bool friend operator<(const range& x, const range& y) {
        if (fabs(x.wh - y.wh) < eps)
            return x.typ > y.typ;
        return x.wh < y.wh;
    }
} d[M<<2];

db alen, summ;
int m, idx;
void insert(db L, db R) {
    if (L > R) return;
    int l = (int)floor(L/alen), r = (int)floor(R/alen);
    if (l > m) l -= m, L -= summ;
    if (r > m) r -= m, R -= summ;
    if (l == r) {
        d[++idx] = {L-alen*l, l, 1};
        d[++idx] = {R-alen*l, l, 0};
    } else {
        d[++idx] = {L-alen*l, l, 1};
        d[++idx] = {alen, l, 0};
        int id = l;
        while (id != r) {
            id++;
            if (id > m) id -= m;
            if (id == r) break;
            d[++idx] = {0.0, id, 1};
            d[++idx] = {alen, id, 0};
        }
        d[++idx] = {0.0, r, 1};
        d[++idx] = {R-alen*r, r, 0};
    }
}

int tot, cnt[N];
bool check(db mid) {
    idx = 0;
    for (int i = 1; i <= tot; ++i) {
        auto tmp = b[i]; tmp.c -= sqr(mid);//方程改为 |...|² ≤ mid²
        if (tmp.delta() < 0 || (fabs(tmp.a) < eps && tmp.c > 0)) continue;//无解
        insert(tmp.l+max(0.0, tmp.lrt()), min(tmp.r, tmp.l+tmp.rrt()));
    }
    sort(d+1, d+idx+1);//按位置排序事件
    int sz = 0;
    for (int i = 1; i <= m; ++i) cnt[i] = 0;
    for (int i = 1; i <= idx; ++i) {
        if (d[i].typ == 1) cnt[d[i].col]++; else cnt[d[i].col]--;
        if (d[i].typ == 1 && cnt[d[i].col] == 1) sz++;
        if (d[i].typ == 0 && cnt[d[i].col] == 0) sz--;
        if (sz == m) return 1;//所有 m 段都被覆盖 => 可行
    }
    return 0;
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

point walk(point p, db len, point agl) {
    return p + point{agl.x*len, agl.y*len};
}

int n;
int main() {
    rd(n), rd(m);
    for (int i = 1; i <= n; ++i) scanf("%lf %lf", &a[i].x, &a[i].y);
    for (int i = 1; i < n; ++i) s[i] = {a[i], a[i+1]};
    s[n] = {a[n], a[1]};//构成多边形
    for (int i = n+1; i <= 2*n; ++i) s[i] = s[i-n];
    for (int i = 1; i <= n; ++i) summ += s[i].len;
    alen = summ/(1.0*m);//把周长分成 m 段，每段长度 alen
    for (int i = 1; i <= 2*n; ++i) s[i].pre = s[i-1].pre + s[i].len;
    for (int i = n+1, j = 1; i <= 2*n; ++i) {
        while (s[i-1].pre - s[j].pre >  alen) j++;
        while (s[i].pre - s[j-1].pre > alen) {
            auto st = s[j].s, ed = s[i].s;
            if (s[i-1].pre - s[j-1].pre > alen)
                st = walk(st, s[i-1].pre-s[j-1].pre-alen, s[j].agl);
            if (s[i-1].pre - s[j-1].pre < alen)
                ed = walk(ed, alen-s[i-1].pre+s[j-1].pre, s[i].agl);
            b[++tot].a = sqr(s[i].agl.x - s[j].agl.x) + sqr(s[i].agl.y - s[j].agl.y);
            b[tot].b = 2.0*(st.x-ed.x)*(s[j].agl.x-s[i].agl.x) +
                2.0*(st.y-ed.y)*(s[j].agl.y-s[i].agl.y);
            b[tot].c = sqr(st.x-ed.x) + sqr(st.y-ed.y);
            b[tot].l = dist(s[i].s, ed) + s[i-1].pre;
            b[tot].r = b[tot].l + min(dist(ed, s[i].t), dist(st, s[j].t));
            if (fabs(b[tot].r - s[i].pre) < eps) break;
            j++;
        }
    }
    db l = 0, r = alen;
    int T = 50;
    while (T--) {
        db mid = (l+r)/2.0;
        if (check(mid)) r = mid; else l = mid;
    }
    printf("%.7f\n", l);
    return 0;
}