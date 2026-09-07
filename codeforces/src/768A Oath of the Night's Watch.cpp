//
// Created by Psy.C on 2026/9/7.
//
/**
l 从 1 开始，只要 a[l+1] == a[1]（仍等于最小值）就一直右移 l。
效果：l 被推到最后一个等于最小值 a[1] 的位置。即把"所有等于最小值的数"全部从左边划掉。
例子：a = [2,2,3,3,5]，最小值 2 出现在下标 1、2，循环后 l=2
r 从 n 开始，只要 r-l >= 1（还有中间段）且 a[r-1] == a[n]（前一个仍等于最大值）就左移 r。
效果：r 被推到第一个等于最大值 a[n] 的位置。即把"所有等于最大值的数"从右边全部划掉。
承上例：最大值 5 只在下标 5，r-l=3≥1、a[4]=3≠5，循环不执行，r=5。若 a=[2,2,5,5,5]：r 会从 5 → 4 → 3，停在 r=3（第一个 5）
循环统计下标 [l+1, r-1] 的元素个数。
这些是既不等于最小值、也不等于最大值的"中间元素"。
输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+1e2;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+n+1);
    int l = 1, r = n;
    while (l+1 <= n && a[l+1] == a[1]) l++;
    while (r-l >= 1 && a[r-1] == a[n]) r--;
    int ans = 0;
    for (int i = l+1; i <= r-1; ++i) ans++;
    cout << ans << '\n';
    return 0;
}