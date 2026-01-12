//
// Created by Psy.C on 2026/1/12.
//
/**
* 点积：a·b = |a||b|cosθ
叉积：a×b = |a||b|sinθ，可用于判断点相对于直线的位置
 *
*枚举所有点对 (i,j)
使用map避免重复处理同一对点
*对于每对点 (i,j)，遍历其他所有点 k
(p[j]-p[i]).cross(p[k]-p[i]) 计算向量 ij 与向量 ik 的叉积
叉积为正：点k在直线ij的左侧
叉积为负：点k在直线ij的右侧
fabs(cross) * 0.5：三角形ijk的面积（底×高÷2）
*s1：直线一侧的最大三角形面积
s2：直线另一侧的最大三角形面积
s1 + s2：由直线ij分割的两个三角形面积之和
只有两侧都有点时才考虑这对点
 *
 *O(n³)，其中n是点的数量
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-10
using namespace std;
//用于浮点数比较
int sgn(const double x) {
    if (fabs(x) < eps) return 0;
    return x > 0 ? 1 : -1;
}

class Point {
public:
    double x, y;
    explicit Point(const double x=0, const double y=0) : x(x), y(y) {}
    void input() { cin >> x >> y; }
    bool operator<(const Point & o) const {
        return !sgn(x - o.x) ? sgn(y - o.y) < 0 : x < o.x;
    }
    bool operator==(const Point & o) const {
        return sgn(x - o.x) == 0 && sgn(y - o.y) == 0;
    }
    [[nodiscard]] double dis2(const Point o) const {
        return pow(x - o.x, 2) + pow(y - o.y, 2);
    }
    [[nodiscard]] double dis(const Point o) const { return sqrt(dis2(o)); }
    [[nodiscard]] double dis2() const { return x * x + y * y; }
    [[nodiscard]] double dis() const { return sqrt(dis2()); }
    Point operator+(const Point o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point o) const { return Point(x - o.x, y - o.y); }
    Point operator*(const double o) const { return Point(x * o, y * o); }
    Point operator/(const double o) const { return Point(x / o, y / o); }
    [[nodiscard]] double dot(const Point o) const { return x * o.x + y * o.y; }
    [[nodiscard]] double cross(const Point o) const { return x * o.y - y * o.x; }
};
vector<Point> p;
map<pair<int, int>, int> mp;

int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        Point t; t.input(); p.push_back(t);
    }
    sort(p.begin(), p.end());
    double ans = 0;
    for (int i = 0; i < p.size(); ++i) for (int j = i + 1; j < p.size(); ++j) {
        if (!mp[{i,j}]) {
            mp[{i,j}] = 1;
            double s1 = 0, s2 = 0;
            for (int k = 0; k < p.size(); ++k) {
                if (k == i || k == j) continue;
                if (sgn((p[j]-p[i]).cross(p[k]-p[i])) > 0) {
                    s1 = max(s1, fabs((p[j]-p[i]).cross(p[k]-p[i])) * 0.5);
                } else {
                    s2 = max(s2, fabs((p[j]-p[i]).cross(p[k]-p[i])) * 0.5);
                }
            }
            if (sgn(s1) == 0 || sgn(s2) == 0) continue;
            ans = max(ans, s1 + s2);
        }
    }
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}