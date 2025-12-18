//
// Created by Psy.C on 2025/12/17.
//
/*
*n: 第一类点的数量；
m: 第二类点的数量；
x1, x2: 代表路径上的两个横坐标位置；
初始化结果索引变量 ans1 和 ans2 为 0
*a[]: 存储第一类点的纵坐标；
b[]: 存储第二类点的纵坐标；
l[]: 存储从某一点出发所需的额外代价
 *v，存储每一对 <纵坐标值, 对应原始索引> 的组合
 *
*遍历每一个第二类点；
计算斜率 k = b[i]/x2；
利用相似三角形原理得到中间点纵坐标 y = k * x1
 *找出第一个大于等于 y 的元素在已排序数组 a 中的位置 p
 *
*如果存在这样的点，则计算路径总长度加上附加成本；
若当前路径比之前找到的最佳路径更好（差值大于 eps），则更新最佳答案
*检查前一个相邻点是否存在；
同样计算路径总长度加附加成本；
更新最优解（若当前更优）
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define di pair<double,int>
#define eps 1e-10
using namespace std;

double f(const double x1, const double y1, const double x2, const double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    fast;
    int n, m, ans1 = 0, ans2 = 0; double x1, x2; cin >> n >> m >> x1 >> x2;
    double a[N], b[N], l[N];
    vector<di> v;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        v.emplace_back(a[i], i);
    }
    for (int i = 0; i < m; ++i) cin >> b[i];
    for (int i = 0; i < m; ++i) cin >> l[i];
    sort(a, a + n);
    sort(v.begin(), v.end());
    double mn = 1e18;
    for (int i = 0; i < m; ++i) {
        const double k = b[i] / x2, y = k * x1;
        const int p = static_cast<int>(lower_bound(a, a + n, y) - a);
        if (p < n) {
            const double t = f(0, 0, x1, a[p]) +
                f(x1, a[p], x2, b[i]) + l[i];
            if (mn - t > eps) { mn = t; ans1 = v[p].second; ans2 = i; }
        }
        if (p - 1 >= 0) {
            const double t = f(0, 0, x1, a[p-1]) +
                f(x1, a[p-1], x2, b[i]) + l[i];
            if (mn - t > eps) { mn = t; ans1 = v[p-1].second; ans2 = i; }
        }
    }
    cout << ans1 + 1 << ' ' << ans2 + 1 << "\n";
    return 0;
}