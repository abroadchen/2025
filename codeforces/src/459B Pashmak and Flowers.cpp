//
// Created by Psy.C on 2026/2/11.
//
/**
时间复杂度
排序：O(n log n)
遍历统计：O(n)
总体：O(n log n)
空间复杂度
O(n)：存储输入数组
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200010
using namespace std;

ll f[N], n;

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> f[i];
    sort(f, f+n);
    ll mn, mx, d, a = 0, b = 0;
    mn = f[0], mx = f[n-1], d = mx - mn;
    for (int i = 0; i < n; ++i)
        if (f[i] == mn) a++;//最小值出现的次数
    for (ll i = n - 1; i >= 0; --i)
        if (f[i] == mx) b++;
    //所有元素都相等
    if (mx == mn) cout << d << ' ' << n*(n-1)/2;//任选两个元素的组合数
    else cout << d << ' ' << a*b;//最大值和最小值之间的配对数
    return 0;
}