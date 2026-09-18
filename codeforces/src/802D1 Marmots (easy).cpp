//
// Created by Psy.C on 2026/9/18.
//
/**
有 q 组测试。
每组读入 250 个整数 a[1..250]，同时把它们的和累进 sum。
所以输入是 q 组、每组 250 个数值
x = sum / 250：这 250 个数的算术平均值。
统计 cnt：这 250 个数中，有多少个落在均值 x 的半个均值之内，即满足 |a[i] - x| <= x/2（与均值的偏差不超过均值的一半）。
也就是说，统计"在 [x - x/2, x + x/2] = [x/2, 3x/2] 区间内"的元素个数（只对正的场景有意义，因为下面判分布通常假设非负计数）
eps = 0.75（宏定义在顶部）。
计算 cnt/250：即"贴近均值的元素占比"。
若该占比 ≥ 0.75 → 判定为 "poisson"（泊松分布）‍；
否则 → 判定为 "uniform"（均匀分布）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 0.75
using namespace std;

constexpr int N = 250;
int a[N+1];
int main() {
    fast;
    int q; cin >> q;
    while (q--) {
        int sum = 0;
        for (int i = 1; i <= N; ++i) {
            cin >> a[i]; sum += a[i];
        }
        double x = (double)sum/250.0;
        int cnt = 0;
        for (int i = 1; i <= N; ++i) {
            if (fabs((double)a[i]-x) <= x/2)
                cnt++;
        }
        if ((double)cnt/250.0 >= eps) cout << "poisson\n";
        else cout << "uniform\n";
    }
    return 0;
}