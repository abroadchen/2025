//
// Created by Psy.C on 2025/12/18.
//
/*
*n：网格大小（n×n）
x, y：中心点坐标
c：需要覆盖的最少格子数
*L：左边界，最小半径为0
R：右边界，最大半径设为100000
ans：答案，初始化为-1
 *在曼哈顿距离为mid的菱形区域内，格子数公式为：2×(mid+1)² - 2×(mid+1) + 1
 *如果完整菱形内的格子数少于需要的c个，则增大半径，继续查找
*r：右边界 = x + mid
l：左边界 = x - mid
u：上边界 = y + mid
d：下边界 = y - mid
 *
*右边超出 (r > n)：
减去右上角三角形区域：(r-n)²
左边超出 (l < 1)：
减去左上角三角形区域：(1-l)²
上边超出 (u > n)：
减去顶部正方形区域：(u-n)²
加上可能的补偿三角形区域
下边超出 (d < 1)：
减去底部正方形区域：(1-d)²
加上可能的补偿三角形区域
 *
*如果t >= c，说明当前半径足够，记录答案并尝试更小的半径
否则需要更大的半径
 *
 *时间复杂度：O(log(1e5)) 空间复杂度：O(1)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll sqr(const ll x) { return x * x; }

int main() {
    fast;
    ll n, x, y, c; cin >> n >> x >> y >> c;
    ll L = 0, R = 1e5, ans = -1;
    while (L <= R) {
        const ll mid = (L + R) >>1;
        ll t = 2 * sqr(mid + 1) - 2 * (mid + 1) + 1;
        if (t < c) { L = mid + 1; continue; }
        const ll r = x + mid, l = x - mid, u = y + mid, d = y - mid;
        if (r > n) t -= 1ll * (r - n) * (r - n);
        if (l < 1) t -= 1ll * (1 - l) * (1 - l);
        if (u > n) {
            t -= sqr(u - n);
            ll t2 = u - n; t2--;
            if (x + t2 > n) t += (x + t2 - n + 1) * (x + t2 - n) / 2;
            if (x - t2 < 1) t += (1 - x + t2) * (1 - x + t2 + 1) / 2;
        }
        if (d < 1) {
            t -= sqr(1 - d);
            ll t2 = 1 - d; t2--;
            if (x + t2 > n) t += (x + t2 - n + 1) * (x + t2 - n) / 2;
            if (x - t2 < 1) t += (1 - x + t2) * (1 - x + t2 + 1) / 2;
        }
        if (t >= c) { ans = mid; R = mid - 1;} else L = mid + 1;
    }
    cout << ans << '\n';
    return 0;
}