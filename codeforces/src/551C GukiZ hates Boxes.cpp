//
// Created by Psy.C on 2026/3/10.
//
/**
n, m：数组长度和操作数
a[N], b[N]：原数组和工作数组
m2：最大非零元素位置
c2：数组总和

复制数组a到b
执行m次操作：
每次操作有x单位时间
减去mx（最大位置数）
从最大位置开始分配时间给元素
如果时间够，完全消耗该位置
如果时间不够，部分消耗该位置
检查是否能完全处理所有元素

二分搜索：O(log(2e14))
每次检查：O(m×n)
总体：O(log(2e14) × m × n)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e5+5;

int n, m, a[N], b[N], m2, c2;
bool check(int x) {
    int mx = m2, cnt = c2;
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    for (int i = 1; i <= m; ++i) {
        int t = x; t -= mx;
        if (t < 0) return false;
        for (int& j = mx; j; --j) {
            if (t >= b[j]) {
                t -= b[j];
                cnt -= b[j];
                b[j] = 0;
            } else {
                b[j] -= t;
                cnt -= t;
                break;
            }
        }
    }
    if (cnt != 0) return false;
    return true;
}

signed main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = n; i; --i) {
        c2 += a[i];
        if (!m2 && a[i] != 0) m2 = i;//找到最大的非零元素位置m2
    }
    int l = 1, r = 2e14;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}