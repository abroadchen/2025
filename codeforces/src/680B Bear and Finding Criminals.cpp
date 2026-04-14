//
// Created by Psy.C on 2026/4/14.
//
/**
n: 数组长度
m: 中心位置
a[105]: 输入数组
ans: 结果计数器
如果中心位置m的值非零，计数器+1
情况1：m - i > 0 && m + i <= n
左右两侧都在数组范围内
如果a[m-i]和a[m+i]都非零，ans += 2
情况2：m-i <= 0 && m+i <= n
左侧超出左边界，右侧在范围内
如果a[m+i]非零，ans += 1
情况3：m-i > 0 && m + i > n
右侧超出右边界，左侧在范围内
如果a[m-i]非零，ans += 1
情况4：else break
两侧都超出边界，退出循环

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, a[105], ans;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    if (a[m]) ans++;
    for (int i = 1; ; ++i) {
        if (m - i > 0 && m + i <= n) {
            if (a[m-i] && a[m+i]) ans += 2;
        } else if (m-i <= 0 && m+i <= n) {
            if (a[m+i]) ans++;
        } else if (m-i > 0 && m + i > n) {
            if (a[m-i]) ans++;
        } else break;
    }
    cout << ans;
    return 0;
}