//
// Created by Psy.C on 2026/3/23.
//
/**
判断总和能否被n整除，即是否能平均分配到每个位置：

sum/n 是整数除法
(double)sum/(double)n 是浮点数除法
如果两者相等，说明可以完全平均分配

情况1：可以完全平均分配
t是目标值（平均值）
只需统计小于目标值的元素需要增加多少才能达到目标值
因为总的增加量等于总的减少量，所以只需计算一边
情况2：不能完全平均分配
t = sum/n（向下取整）是基础平均值
mx = t + 1是较高层的目标值
有些元素要达到t，有些元素要达到t+1
ans统计小于t的元素需要增加的总量
res统计大于mx的元素需要减少的总量
输出较大的那个值作为答案

时间复杂度：
O(n)，只需要遍历数组两次。
空间复杂度：
O(n)，主要是存储输入数组的空间。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int n, a[N];
int main() {
    fast;
    cin >> n;
    int sum = 0, ans = 0, t;
    for (int i = 1; i <= n; ++i) { cin >> a[i]; sum += a[i]; }
    if (sum/n == (double)sum/(double)n) {
        t = sum/n;
        for (int i = 1; i <= n; ++i)
            if (a[i] < t) ans += t - a[i];
        cout << ans << '\n';
    } else {
        t = sum/n;
        int mx = t + 1, res = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i] < t) ans += t - a[i];
            if (a[i] > mx) res += a[i] - mx;
        }
        if (res > ans) cout << res << '\n';
        else cout << ans << '\n';
    }
    return 0;
}