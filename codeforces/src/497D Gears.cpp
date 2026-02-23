//
// Created by Psy.C on 2026/2/21.
//
/**
A * B = |A| * |B| * cos(θ)
用于计算向量长度的平方
A ^ B = |A| * |B| * sin(θ)
用于判断点相对于直线的位置关系

点o到线段cd的距离的平方
mn: 点o到线段端点的最小距离平方
oh = (d-c).rotate(): 线段cd的法向量
sgn(oh^oc)*sgn(oh^od) != -1: 判断点o是否在线段cd的延长线上
如果点o在延长线上，返回到端点的最小距离
否则计算到线段的垂直距离平方

以点o为圆心、半径为√r的圆是否与线段cd相交
mx: 到线段端点的最大距离平方
mn: 到线段的最小距离平方
r: 平移向量的长度平方
相交条件：mn ≤ r ≤ mx

pq: 从p到q的平移向量
r: 平移距离的平方

将多边形A按向量pq平移
检查平移后的A的每个顶点是否与多边形B的边相交
将多边形B按向量-pq平移（即反向平移）
检查平移后的B的每个顶点是否与多边形A的边相交

O(n×m)，其中n和m分别是两个多边形的顶点数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1001;
struct Point {
    double x, y;
    Point() = default;
    Point(const int _x, const int _y) : x(_x), y(_y) {}
    void input() { cin >> x >> y; }
    Point operator+(const Point a) const { return Point(x + a.x, y + a.y); }
    Point operator-(const Point a) const { return Point(x - a.x, y - a.y); }
    double operator*(const Point a) const { return x * a.x + y * a.y; }
    double operator^(const Point a) const { return x * a.y - y * a.x; }
    Point rotate() const { return Point(-y, x); }
    double len() const { return *this * *this; }
} p, q, a[N], b[N];
int sgn(const double x) {
    if (x == 0) return 0;
    if (x < 0) return -1;
    return 1;
}
double get(const Point o, const Point c, const Point d) {
    const double mn = min((o-c).len(), (o-d).len());
    const Point oc = c - o, od = d - o;
    if (const Point oh = (d - c).rotate(); sgn(oh^oc)*sgn(oh^od) != -1) return mn;
    const double s = fabs(oc^od), h2 = s*s/(c-d).len();
    return h2;
}

double r;
bool ok(const Point o, const Point c, const Point d) {
    if (const double mx = max((o-c).len(),
        (o-d).len()), mn = get(o, c, d); mn <= r && r <= mx) return true;
    return false;
}

int n, m;
bool ans;
int main() {
    fast;
    p.input(); cin >> n;
    for (int i = 0; i < n; ++i) a[i].input();
    q.input(); cin >> m;
    for (int i = 0; i < m; ++i) b[i].input();
    const Point pq = q - p; r = pq.len();
    for (int i = 0; i < n; ++i) {
        const Point o = a[i] + pq;
        for (int j = 0; j < m; ++j)
            ans |= ok(o, b[j], b[(j+1)%m]);
    }
    for (int i = 0; i < m; ++i) {
        const Point o = b[i] - pq;
        for (int j = 0; j < n; ++j)
            ans |= ok(o, a[j], a[(j+1)%n]);
    }
    if (ans) cout << "YES\n"; else cout << "NO\n";
    return 0;
}