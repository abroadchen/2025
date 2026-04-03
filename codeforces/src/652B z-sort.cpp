//
// Created by Psy.C on 2026/4/2.
//
/**
n: 数组长度
a[N]: 输入数组
ans[N]: 结果数组
i, j: 循环变量
m: 分界点
op[N]: 较大值数组
s[N]: 较小值数组
奇数情况：m = n/2 + 2 = ⌊n/2⌋ + 2
偶数情况：m = n/2 + 1 = n/2 + 1
将较大的元素（从a[n]到a[m]）放入op数组
将较小的元素（从a[1]到a[m-1]）放入s数组
交替放置元素
奇数位置放s数组的元素（较小值）
偶数位置放op数组的元素（较大值）
时间复杂度：O(n log n)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;
int n, a[N], ans[N], i, j, m, op[N], s[N];
int main() {
    fast;
    cin >> n;
    for (i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1); m = n/2;
    if (n&1) m += 2; else m++;
    j = 1;
    for (i = n; i >= m; --i) op[j++] = a[i];
    for (i = 1; i < m; ++i) s[i] = a[i];
    int l = 1, o = 1;
    for (i = 1; i <= n; ++i) {
        if (i&1) ans[i] = s[l++];
        else ans[i] = op[o++];
    }
    for (i = 1; i <= n; ++i) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}