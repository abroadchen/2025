//
// Created by Psy.C on 2026/3/3.
//
/**
计算直线ab与直线cd的交点
使用参数方程方法：P = A + t*(B-A)，其中t为参数
返回交点坐标
ok(): 判断点a是否在向量lr的左侧（叉积>0）
起点a、终点b和角度k
先按角度排序，角度相同时按位置排序
计算两条线段所在直线的交点

读入n条直线的系数（ax+by=c形式）
根据直线方程确定线段的两个端点：
当a=0时（平行于x轴）：y=c/b，构造两点(0,c/b)和(1,c/b)
当b=0时（平行于y轴）：x=c/a，构造两点(c/a,0)和(c/a,1)
一般情况：构造两点(0,c/b)和(1,(c-a)/b)

对每条线段i，与其他所有线段计算交点
i<n ? i+1 : 1: 循环遍历，到达末尾后回到开头
计算线段i与所有其他线段的交点
使用叉积累加多边形面积（鞋带公式）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
#define Vector node
#define eps 1e-8
using namespace std;
constexpr int N = 3001;

struct node { db x, y; };
inline db cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
inline Vector operator+(Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
inline Vector operator-(Vector a, Vector b) { return Vector(a.x - b.x, a.y - b.y); }
inline Vector operator*(Vector a, db b) { return Vector(a.x * b, a.y * b); }
inline node jd(node a, node b, node c, node d) {
    Vector x = b - a, y = d - c, z = a - c;
    return a + x*(cross(y, z)/cross(x, y));
}
inline int sgn(db a) { return a < -eps ? -1 : (a > eps ? 1 : 0); }
inline int ok(node a, node l, node r) {
    return sgn(cross(l - a, r - a)) > 0;
}

struct node2 {
    node a, b; db k;
    node2(node a={0,0}, node b={0,0}) : a(a), b(b) {
        k = atan2(b.y - a.y, b.x - a.x);
    }
    bool operator<(const node2& o) const {
        return sgn(k-o.k) ? sgn(k-o.k)<0 : ok(o.a, o.b, a);
    }
} x[N];
inline node jd(const node2 &l1, const node2 &l2) {
    return jd(l1.a, l1.b, l2.a, l2.b);
}

int n;
db ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1, a, b, c; i <= n; ++i) {
        cin >> a >> b >> c;
        if (!sgn(a)) x[i] = node2({0,1.*c/b}, {1,1.*c/b});
        else if (!sgn(b)) x[i] = node2({1.*c/a, 0}, {1.*c/a, 1});
        else x[i] = node2({0,1.*c/b}, {1,1.*(c-a)/b});
    }
    sort(x + 1, x + n + 1);
    for (int i = 1; i <= n; ++i) {
        node s = {}, p{};
        for (int j = i<n ? i+1 : 1; j != i; j = j<n ? j+1 : 1)
            p = jd(x[i], x[j]), ans += cross(s, p), s = s + p;
    }
    printf("%lf\n", ans*3/n/(n-1)/(n-2));
    return 0;
}