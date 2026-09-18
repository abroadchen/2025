//
// Created by Psy.C on 2026/9/18.
//
/**
q 组测试，每组读 250 个整数，累加进 sum。
sum /= N：算出均值
s += (a[i]-sum)^2：累加离均差的平方和。
s = sqrt(s/N)：这就是总体标准差（σ）。
再除以 *ranges::max_element(a)（队伍的最大值）——得到一个纯量纲的、归一化到最大值的"相对离散度"
严格来说"变异系数"通常定义成 σ / μ（标准差除以均值）。这里分母用的是 max 而非均值，所以它是**"相对离散度的一种变体"
（用最大值做归一化）。但对泊松分布**而言，它依然体现同一种直觉：泊松分布 σ = √μ，其相对离散度相对固定；而均匀分布的相对离散度更大
若归一化离散度 s > 0.52 → 判 uniform（均匀分布）‍；
否则 → 判 poisson（泊松分布）‍。
阈值 0.52 是经验常数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 250;
vector<int> a(N);
int main() {
    fast;
    int q; cin >> q;
    while (q--) {
        double sum = 0, s = 0;
        for (int i = 0; i < N; ++i) {
            cin >> a[i];
            sum += a[i];
        }
        sum /= N;
        for (int i = 0; i < N; ++i)
            s += (a[i]-sum)*(a[i]-sum);
        s = sqrt(s/N)/(*ranges::max_element(a));
        cout << (s > 0.52 ? "uniform\n" : "poisson\n");
    }
    return 0;
}