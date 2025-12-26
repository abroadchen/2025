//
// Created by Psy.C on 2025/12/26.
//
/*
* v1, v2：两种收益值
t1, t2：两种时间消耗
p：成功概率
*n：任务数量
t：总时间限制
 *
*f[i]：时间为i时的最大期望收益
g[i]：额外的计算参数（可能与方差或风险相关）
初始化f数组为-1（表示不可达），g数组为0
 *
*从后往前遍历时间（避免重复使用）
尝试执行任务的第一部分（获得v1收益，消耗t1时间）
如果新的方案更优，或者收益相同但风险更小，则更新状态
*尝试执行任务的完整流程（第一部分+第二部分）
期望收益：f[j] + v1 + p * v2（v2收益只在成功时获得）
如果新的方案更优，则更新状态
 *
*遍历所有可能的时间状态
ans1：最大期望收益
ans2：在最大收益下最优的附加指标
如果收益相同，选择i - g[i]更小的方案
 *
 */
#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1565;
struct node { int v1, v2, t1, t2; long double p; } a[N];
//比较两个长双精度浮点数是否相等
bool same(const long double x, const long double y) { return fabs(x - y) < 1e-15; }

int main() {
    fast;
    int n, t; cin >> n >> t;
    for (int i = 1, v1, v2, t1, t2; i <= n; ++i) {
        double p;
        cin >> v1 >> v2 >> t1 >> t2 >> p; p = 1. - p;//将失败概率转换为成功概率
        a[i] = {v1, v2, t1, t2, p};
    }
    sort(a + 1, a + n + 1, [](const node& x, const node& y) {
        return (1. - x.p) * x.t2 / x.p < (1. - y.p) * y.t2 / y.p;
    });
    long double f[N], g[N];
    for (int i = 1; i <= t; ++i) f[i] = -1., g[i] = 0.;
    for (int i = 1; i <= n; ++i) {
        const int v1 = a[i].v1, v2 = a[i].v2, t1 = a[i].t1, t2 = a[i].t2;
        const long double p = a[i].p;
        for (int j = t; j >= 0; --j) {
            if (j + t1 <= t) {
                if (f[j+t1] < f[j] + v1 || (same(f[j+t1], f[j]+v1) &&
                    g[j] > g[j+t1])) {
                    f[j+t1] = f[j] + v1; g[j+t1] = g[j];
                }
            }
            if (j + t1 + t2 <= t) {
                if (f[j+t1+t2] < f[j]+v1+p*v2 || (same(f[j+t1+t2], f[j]+v1+p*v2) &&
                    (1. - p) * (g[j]+t2) > g[j+t1+t2])) {
                    f[j+t1+t2] = f[j] + v1 + p * v2;
                    g[j+t1+t2] = (1. - p) * (g[j] + t2);
                }
            }
        }
    }
    long double ans1 = -1., ans2 = 0.;
    for (int i = 0; i <= t; ++i) {
        if (f[i] > ans1 || (same(f[i], ans1) &&
            1. * i - g[i] < ans2)) {
            ans1 = f[i];
            ans2 = 1. * i - g[i];
        }
    }
    cout << fixed << setprecision(10) <<
        static_cast<double>(ans1) << ' ' <<
            static_cast<double>(ans2) << '\n';
    return 0;
}