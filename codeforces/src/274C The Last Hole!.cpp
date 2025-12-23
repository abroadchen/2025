//
// Created by Psy.C on 2025/12/22.
//
/*
*1 & 1 = 1 (条件满足)
1 & 0 = 0 (条件不满足，flag变为0)
0 & 1 = 0 (之前已失败，保持0)
0 & 0 = 0 (之前已失败，保持0)
 *
 */
#include <iostream>
#include <map>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define db double
#define N 103
#define eps 1e-10
#define rep(i,n) for(int i=1;i<=n;++i)
#define Vector Point
#define S(a) ((a)*(a))
using namespace std;

struct Point {
    db x, y;
    explicit Point(const db x=0, const db y=0) : x(x), y(y) {}
} p[N], q[N*N*N];
Vector operator-(const Vector a, const Vector b) { return Vector(a.x-b.x, a.y-b.y); }
db cross(const Vector a, const Vector b) { return a.x * b.y - a.y * b.x; }
int sgn(const db a) { return a < -eps ? -1 : a > eps ? 1 : 0; }//小于-eps返回-1，大于eps返回1，否则返回0
int pinline(const Point x, const Point a, const Point b) { return !sgn(cross(x-a, b-a)); }//点x是否在直线ab上
db dot(const Vector a, const Vector b) { return a.x * b.x + a.y * b.y; }

struct Circle {
    Point o; db r;
    explicit Circle(const Point o, const db r=0) : o(o), r(r) {}
};
Circle get(const Point A, const Point B, const Point C) {//三个点确定一个圆
    const db x1 = A.x, y1 = A.y, x2 = B.x, y2 = B.y, x3 = C.x, y3 = C.y,//提取三点坐标 圆心x坐标的系数D 圆心y坐标的系数E 常数项F
    D = ((S(x2)+S(y2)-S(x3)-S(y3))*(y1-y2)-(S(x1)+S(y1)-S(x2)-S(y2))*(y2-y3))/((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2)),
    E = sgn(y2-y1)!=0?(S(x1)+S(y1)-S(x2)-S(y2)+D*(x1-x2))/(y2-y1):(S(x2)+S(y2)-S(x3)-S(y3)+D*(x2-x3))/(y3-y2),
    F = -(S(x1)+S(y1)+D*x1+E*y1);
    return Circle(Point(-D/2.,-E/2.), sqrt((S(D)+S(E)-4.*F)/4.));
}

int cnt;//有效圆的数量
db t[N*N*N];//存储圆的半径
void tria(const Point A, const Point B, const Point C) {//三角形三点构成的圆
    if (sgn(dot(A-B, C-B))<=0||sgn(dot(A-C,B-C))<=0||sgn(dot(B-A, C-A))<=0) return;//任意一角为钝角或直角
    const Circle x = get(A, B, C);//外接圆
    q[++cnt] = x.o; t[cnt] = x.r;
}

db len(const Vector a) { return sqrt(dot(a, a)); }//向量长度
int X[N], Y[N];
map<pair<int, int>, int> vis;
void ok(const int i, const int j, const int k) {//特定矩形配置
    if (X[i] == X[j] && Y[i] < Y[j] && Y[i] == Y[k] && X[i] < X[k]) {
        if (vis[{X[k], Y[j]}]) q[++cnt] = Point((X[i]+X[k])/2., (Y[i]+Y[j])/2.),
            t[cnt] = len(p[j]-p[k])/2.;
    }
}

void react(const int i, const int j, const int k) {//三个点的所有排列
    ok(i, j, k), ok(j, i, k), ok(k, i, j);
    ok(i, k, j), ok(j, k, i), ok(k, j, i);
}

int main() {
    fast;
    int n; cin>>n;
    rep(i,n) {
        cin>>X[i]>>Y[i];
        vis[{X[i],Y[i]}] = 1;
        p[i] = Point{static_cast<db>(X[i]),static_cast<db>(Y[i])};
    }
    rep(i,n) for (int j = i+1;j<=n;++j) for (int k = j+1;k<=n;++k) {
        if (!pinline(p[i], p[j], p[k])) tria(p[i], p[j], p[k]),
            react(i, j, k);
    }
    db ans = -1;
    rep(i,cnt) {
        int flag = 1;
        for (int j = 1; j <= n && flag; ++j) flag &= sgn(len(q[i]-p[j])-t[i])>=0;//每个圆是否包含所有输入点
        if (flag) ans = max(ans, t[i]);
    }
    cout<<ans<<'\n';
    return 0;
}