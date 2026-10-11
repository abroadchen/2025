//
// Created by Psy.C on 2026/10/11.
//
/**
n：球的数量。
r：球的半径。
x[i]：第 i 个球的水平位置（整数）。
y[i]：第 i 个球最终静止时圆心的 y 坐标（输出目标）
先把第 i 个球的圆心初始化为 r（贴着地面，上一步球落地的位置）。这是它的"下界"
对每个前面已落好的球 j，判断两球在水平方向是否可能"相遇"（即两圆水平投影是否有重叠）。
两圆圆心水平距离如果超过 2r，则水平投影不相交，球 i 不可能落在球 j 上，直接跳过。
条件等价于 |x[i]-x[j]| > 2r 就跳过。
若球 i 与球 j 相切（相触），两圆心距离为 2r（两半径之和）。
设两球圆心水平距离为 dx = |x[i]-x[j]|，则竖直距离满足勾股定理：
(竖直距离)² + dx² = (2r)²
所以 竖直距离 = sqrt((2r)² - dx²) = sqrt(4r² - dx²)。
这就是 t。
因此若球 i 停在球 j 上方相切，则 y[i] = y[j] + t。
因为球可能依次叠在多个球上，取所有可能候选中的最大值：
y[i] = max(y[i], y[j] + t)。
为什么要取 max？因为球落下的过程中，它会被"最高"的那个支撑点托住——即它接触到的最高的球决定了它的最终高度。取 max 符合物理实际。
依次输出每个球最终圆心的 y 坐标，%.8lf 保留 8 位小数，空格分隔
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
using namespace std;

constexpr int N = 1e3+5;

int n, r, x[N];
double y[N];
int main() {
    fast;
    cin >> n >> r;
    rep(i,1,n) {
        cin >> x[i]; y[i] = r;
        rep(j,1,i-1) {
            if (x[j]+r < x[i]-r || x[j]-r > x[i]+r) continue;
            double t = sqrt(4*r*r-(x[j]-x[i])*(x[j]-x[i]));
            y[i] = max(y[i], y[j]+t);
        }
        printf("%.8lf ", y[i]);
    }
    return 0;
}