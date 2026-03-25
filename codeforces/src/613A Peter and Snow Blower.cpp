//
// Created by Psy.C on 2026/3/24.
//
/**
a为x坐标，b为y坐标
p[N]: 多边形的顶点数组
T: 特定点（圆心）
计算两点之间的欧几里得距离
d1: x坐标差的平方
d2: y坐标差的平方
计算点C到线段AB的距离
a, b, c: 三角形ABC的三条边长
x = max(a, b): 将最长边（AC或BC）存储到引用参数x中
余弦定理判断：
if (a*a >= b*b + c*c): 角B是钝角或直角，返回b（BC长度）
if (b*b >= a*a + c*c): 角A是钝角或直角，返回a（AC长度）
海伦公式计算面积：s = sqrt((m-a)(m-b)(m-c)m)
d = s*2/c: 用面积公式计算点到线段的距离（面积×2/底边）

读入多边形顶点数n
读入圆心T的坐标
读入n个多边形顶点的坐标
mx = -inf, mn = inf: 初始化最大值和最小值
t: 引用参数，接收get函数计算出的最大距离
遍历多边形的每条边（p[i]到p[(i+1)%n]）
get(p[i], p[(i+1)%n], T, t): 计算点T到边i的距离
mn = min(...): 更新到边的最小距离
mx = max(mx, t): 更新最大距离（t是到顶点的最大距离）
ans = mx*mx - mn*mn: 计算圆环面积的系数（外圆半径² - 内圆半径²）
ans *= pi: 乘以π得到圆环面积

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;
const double pi = acos(-1.), inf = 1e7;

struct node { double a, b; } p[N], T;

double get(node x, node y) {
    double d1 = (x.a - y.a)*(x.a - y.a),
    d2 = (x.b - y.b)*(x.b - y.b);
    return sqrt(d1 + d2);
}
double get(node A, node B, node C, double &x) {
    double a = get(A, C), b = get(B, C), c = get(A, B);
    x = max(a, b);
    if (a*a >= b*b + c*c) return b;
    if (b*b >= a*a + c*c) return a;
    double m = (a + b + c)/2, s = (m-a)*(m-b)*(m-c)*m;
    s = sqrt(s);
    double d = s*2/c;
    return d;
}

int n;
int main() {
    fast;
    cin >> n;
    cin >> T.a >> T.b;
    for (int i = 0; i < n; ++i)
        cin >> p[i].a >> p[i].b;
    double mx = -inf, mn = inf, t;
    for (int i = 0; i < n; ++i) {
        mn = min(mn, get(p[i], p[(i+1)%n], T, t));
        mx = max(mx, t);
    }
    double ans = mx*mx - mn*mn; ans *= pi;
    printf("%.10lf\n", ans);
    return 0;
}