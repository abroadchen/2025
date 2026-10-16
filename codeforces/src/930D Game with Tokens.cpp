//
// Created by Psy.C on 2026/10/16.
//
/**
对偶数族：新坐标 (u, v) = ((x+y)/2, (x-y)/2)，并整体偏移 P（=100001，避免下标出现负数）。
对奇数族：用 (x+y+1)/2, (x-y+1)/2，这是为了防止除以 2 时出现 .5 造成的不对称，往往让奇数族也能对齐到同一套格子。
为什么要这样变换？
曼哈顿距离 |x1-x2|+|y1-y2| 通过旋转 45° 并缩放 √2/2 会变成切比雪夫距离 max(|du|, |dv|)。把点和点之间的"距离关系"从曼哈顿变为切比雪夫，通常能简化"给定距离内的点 / 求覆盖计数"类问题。奇偶分开是因为经过 ÷2 后奇偶点落在不同的整数格点上（交错棋盘），必须分别处理

参数 o 表示处理第 0 族还是第 1 族
按变换后的第一维（即 u 坐标）排序
d[i] = "第一维 ≤ i"的点中，第二维的最小值和最大值（(min, max)）。
u[i] = "第一维 ≥ i"的点中，第二维的最小值和最大值（(min, max)）
把第一维 ≤ i 的所有点的第二维 min/max 累积进 d[i]
把第一维 ≥ i 的所有点的第二维 min/max 累积进 u[i]
用一条竖直分割线把点分成左、右两组，分别记录两组的第二维范围 [min,max]
对每个分割位置 i：

左边组第二维区间 = [d[i].first, d[i].second]。
右边组第二维区间 = [u[i+1].first, u[i+1].second]。
交叠长度为 max(0, min(right) - max(left)) = 两区间的公共覆盖长度。
把所有 i 的公共覆盖长度累加

对每组点：排序 O(k log k)，三段扫描各 O(M)，M≈2e5，总 O(k log k + M)。
总体 O(n log n + M)，可以应付 1e5 点、2e5 坐标范围
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5, M = 2e5+5, inf = 5e5+5, P = 1e5+1;

ii p[2][N], u[M], d[M];
int cnt[2];
ll f(int o) {
    sort(p[o]+1, p[o]+cnt[o]+1);
    d[0] = u[0] = d[M-2] = u[M-2] = {inf, 0};
    for (int i = 1, j = 1; i <= M-3; ++i) {
        d[i] = d[i-1];
        while (j <= cnt[o] && p[o][j].first <= i) {
            d[i].first = min(d[i].first, p[o][j].second);
            d[i].second = max(d[i].second, p[o][j].second);
            j++;
        }
    }
    for (int i = M-3, j = cnt[o]; i >= 1; --i) {
        u[i] = u[i+1];
        while (j > 0 && p[o][j].first >= i) {
            u[i].first = min(u[i].first, p[o][j].second);
            u[i].second = max(u[i].second, p[o][j].second);
            j--;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= M-3; ++i) {
        int l = max(d[i].first, u[i+1].first), r = min(d[i].second, u[i+1].second);
        ans += max(0, r-l);
    }
    return ans;
}


int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        if ((x+y)%2 == 0) p[0][++cnt[0]] = {(x+y)/2+P, (x-y)/2+P};
        else p[1][++cnt[1]] = {(x+y+1)/2+P, (x-y+1)/2+P};
    }
    ll ans = f(0) + f(1);
    cout << ans << '\n';
    return 0;
}