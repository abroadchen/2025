//
// Created by Psy.C on 2026/3/22.
//
/**
以p[1]为基准点进行极角排序
如果三点共线，按距离远近排序
否则按极角大小排序（利用叉积判断

计算直线ab与直线cd的交点
使用参数方程求解两直线交点
n: 点的数量
sum: 栈顶指针
st[N]: 用作栈存储凸包上的点
P, Q: 目标点坐标
t: 目标点
mxx, mxy: x和y坐标的最大值
ans: 最终答案

读入所有点并维护最大x和y值
添加原点(0,0)并将其作为基准点p[1]
添加点(0,mxy)和(mxx,0)构成边界
对除p[1]外的所有点按极角排序
使用Graham扫描算法构建凸包
利用叉积判断转向，维护凸包性质
遍历凸包边，寻找从p[1]出发经过目标点t的射线与凸包边的交点
检查交点是否在线段上
如果找到交点，计算比例因子作为答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-7
using namespace std;
constexpr int N = 1e5+5;

struct node { double x, y; } p[N];
double operator*(node a, node b) { return a.x * b.y - b.x * a.y; }
node operator+(node a, node b) { return node(a.x + b.x, a.y + b.y); }
node operator-(node a, node b) { return node(a.x - b.x, a.y - b.y); }
node operator*(node a, double b) { return node(a.x * b, a.y * b); }
double dis(node a, node b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
bool cmp(node a, node b) {
    if (abs((a - p[1])*(b - p[1])) < eps) {
        return dis(p[1], a) < dis(p[1], b);
    }
    return (a - p[1]) * (b - p[1]) > 0;
}
node add(node a, node b, node c, node d) {
    auto x = a - c;
    double y = d*x/(b*d);
    return a + b*y;
}

int n, sum, st[N];
double P, Q, mxx, mxy, ans;
int main() {
    fast;
    cin >> n >> P >> Q; node t = {P, Q};
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
        mxx = max(mxx, p[i].x);
        mxy = max(mxy, p[i].y);
    }
    p[++n].x = 0., p[n].y = 0.; swap(p[1], p[n]);
    p[++n].x = 0., p[n].y = mxy, p[++n].x = mxx, p[n].y = 0.;
    sort(p + 2, p + n + 1, cmp);
    for (int i = 1; i <= n; ++i) {
        while (sum > 1 && (p[st[sum]] - p[st[sum-1]])*(p[i] - p[st[sum]]) < eps)
            sum--;
        st[++sum] = i;
    }
    for (int i = 2; i < sum; ++i) {
        auto it = add(p[1], t, p[st[i]], p[st[i+1]]-p[st[i]]);
        double x1 = p[st[i]].x, y1 = p[st[i]].y, x2 = p[st[i+1]].x, y2 = p[st[i+1]].y;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        if (it.x >= x1 - eps && it.x <= x2 + eps && it.y >= y1 - eps && it.y <= y2 + eps) {
            ans = sqrt(dis(p[1], t)/dis(p[1], it));
            break;
        }
    }
    printf("%.15lf\n", ans);
    return 0;
}