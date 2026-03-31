//
// Created by Psy.C on 2026/3/31.
//
/**
n：元素数量
mx[N]：最大值数组
mn[N]：最小值数组
a1[N], a2[N]：结果数组
z1, z2：累积和变量
s1, s2：前缀和变量

累积更新：
z1 += mx[i]：累加最大值前缀和
z2 -= mn[i]：减少最小值（从后往前减）
方程求解：
a = z2, b = z1：设置方程系数
t = b - a + 1.：计算中间值
s = sqrt(max(t*t-4.*b, (ld)0.))：判别式（防止负数开方）
x = (t+s)/2., y = (t-s)/2.：求解二次方程的两根
结果更新：
a1[i] = x - s1：计算当前差值
a2[i] = y - s2：计算当前差值
s1 = x, s2 = y：更新前缀和

设 x, y 为某二次方程的两根
x + y = b - a + 1（韦达定理之和）
xy = b（韦达定理之积）
通过 x² - (x+y)x + xy = 0 求解

输出 a1 数组和 1-s1（最后一项）
输出 a2 数组和 1-s2（最后一项）
时间复杂度：O(n)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
using namespace std;
constexpr int N = 1e5+5;
ld n, mx[N], mn[N], a1[N], a2[N], z1, z2, s1, s2;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> mx[i];
    for (int i = 1; i <= n; ++i) cin >> mn[i], z2 += mn[i];
    for (int i = 1; i < n; ++i) {
        z1 += mx[i], z2 -= mn[i];
        ld a = z2, b = z1, t = b - a + 1., s = sqrt(max(t*t-4.*b, (ld)0.)),
        x = (t+s)/2., y = (t-s)/2.;
        a1[i] = x - s1, a2[i] = y - s2, s1 = x, s2 = y;
    }
    cout << fixed << setprecision(15);
    for (int i = 1; i < n; ++i) cout << a1[i] << ' ';
    cout << 1.-s1 << '\n';
    for (int i = 1; i < n; ++i) cout << a2[i] << ' ';
    cout << 1.-s2 << '\n';
    return 0;
}