//
// Created by Psy.C on 2026/3/20.
//
/**
N = 1e3+5：最大点数
sgn(x)：返回x的绝对值
eq(x, y)：判断两个浮点数是否相等（考虑精度误差）
node：表示二维点
p[N]：存储多边形的顶点
dist(u, v)：计算两点间距离
line：表示直线（y = ax + b）
calc(u, v)：根据两点计算直线方程
pos(u)：判断点u相对于直线的位置
0：点在直线上
1：点在直线上方
-1：点在直线下方
node2：交点结构，包含点坐标和类型标识
cnt：交点计数器
push(u, id)：添加交点
cmp：按x坐标排序

out(u, v)：计算直线uv与多边形的交线长度
遍历多边形的每条边
p1, p2, p3：前一个、当前、后一个点相对于直线的位置
if (!p2)：当前点在直线上
if (p1 != p3)：前后点在直线两侧，添加交点
else if (p2 + p3 == 0)：当前点和后一个点分别在直线两侧，计算交点
按x坐标排序所有交点
计算直线在多边形内部的总长度
f1：标记是否在多边形内部
f2：标记特殊处理状态

设置边界条件（循环连接）
if (eq(x1, x2))：如果是垂直线，通过坐标变换转换为非垂直线
out：计算交线长度
时间复杂度：O(mn log n)，其中m是查询次数，n是多边形顶点数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
#define eps 1e-7
using namespace std;
constexpr int N = 1e3+5;

inline ld sgn(ld x) { return x < 0 ? -x : x; }
inline bool eq(ld x, ld y) { return sgn(x - y) <= eps; }

struct node { ld x, y; } p[N];
inline ld dist(const node& u, const node& v) {
    return sqrt((u.x - v.x)*(u.x - v.x) + (u.y - v.y)*(u.y - v.y));
}
struct line {
    ld a{}, b{};
    void calc(node u, node v) {
        a = (u.y - v.y) / (u.x - v.x);
        b = u.y - a*u.x;
    }
    int pos(node u) const {
        ld y = a*u.x + b;
        if (eq(y, u.y)) return 0;
        if (y < u.y) return 1;
        return -1;
    }
    line(node u, node v) { calc(u, v); }
};

struct node2 { node u; int id; } q[N];
int cnt;
inline void push(node u, int id) {
    q[++cnt].u = u; q[cnt].id = id;
}
inline bool cmp(const node2 &u, const node2 &v) {
    return u.u.x < v.u.x;
}

int n;
inline void out(node u, node v) {
    line l(u, v); cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int p1 = l.pos(p[i-1]), p2 = l.pos(p[i]), p3 = l.pos(p[i+1]);
        if (!p2) {
            if (p1 != p3) push(p[i], p1 + p3);
        } else if (p2 + p3 == 0) {
            if (eq(p[i].x, p[i+1].x))
                push({p[i].x, l.a*p[i].x + l.b}, 0);
            else {
                line l2(p[i], p[i+1]);
                ld x = (l.b - l2.b)/(l2.a - l.a);
                push({x, l.a*x + l.b}, 0);
            }
        }
    }
    sort(q + 1, q + cnt + 1, cmp);
    ld ans = 0; int f1 = 0, f2 = 0;
    for (int i = 1; i < cnt; ++i) {
        if (q[i].id && !f2) {
            f2 = 1;
            ans += dist(q[i].u, q[i+1].u);
            if (q[i].id == q[i+1].id) f1 ^= 1;
            continue;
        }
        f2 = 0;
        f1 ^= 1;
        if (f1) ans += dist(q[i].u, q[i+1].u);
    }
    printf("%.20lf\n", (double)ans);
}

int m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        double x, y; cin >> x >> y;
        p[i] = {x, y};
    }
    p[0] = p[n]; p[n+1] = p[1];
    while (m--) {
        double x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if (eq(x1, x2)) {
            swap(x1, y1); swap(x2, y2);
            for (int i = 0; i <= n+1; ++i) swap(p[i].x, p[i].y);
            out({x1, y1}, {x2, y2});
            for (int i = 0; i <= n+1; ++i) swap(p[i].x, p[i].y);
        } else out({x1, y1}, {x2, y2});
    }
    return 0;
}