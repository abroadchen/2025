//
// Created by Psy.C on 2026/9/12.
//
/**
node：事件点 x 与权值 w。
按位置排序，用于扫描线
对每个物体 i，在时间 m 内它能到达的区间是 [x[i]-y[i]*m, x[i]+y[i]*m]。
把区间左端点作为 +1 事件、右端点作为 -1 事件推入 v（右端点加 eps 处理边界闭区间）。
扫描事件，t 为当前覆盖区间数：
当 t == n，说明存在一个位置同时被所有 n 个区间覆盖 → 时间 m 可行，返回 true
二分时间 m：可行就缩小上界，不可行就扩大下界。
收敛精度 eps2 = 1e-7。
输出最小可行时间，保留 12 位小数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-20
#define eps2 1e-7
using namespace std;
constexpr int N = 6e4+5, inf = 1e9;

struct node {
    double x; int w;
};
bool cmp(node a, node b) { return a.x < b.x; }
vector<node> v;
int n;
double x[N], y[N];
bool check(double m) {
    v.clear();
    for (int i = 1; i <= n; ++i) {
        v.push_back({.x = x[i]-y[i]*m, .w = 1});
        v.push_back({.x = x[i]+y[i]*m+eps, .w = -1});
    }
    ranges::sort(v, cmp);
    int t = 0;
    for (auto [_, w] : v) {
        t += w;
        if (t == n) return true;
    }
    return false;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i];
    for (int i = 1; i <= n; ++i) cin >> y[i];
    double l = eps2, r = inf;
    while (r - l > eps2) {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid - eps2;
        else l = mid + eps2;
    }
    cout << fixed << setprecision(12) << l << '\n';
    return 0;
}