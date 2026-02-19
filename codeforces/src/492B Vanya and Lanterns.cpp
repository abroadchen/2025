//
// Created by Psy.C on 2026/2/19.
//
/**
n: 现有灯泡数, l: 线段总长度
//照亮到最近灯泡的距离
左边界：如果第一个灯泡不在0位置，新灯泡可以放在0处，照亮距离为a[0]
右边界：如果最后一个灯泡不在l位置，新灯泡可以放在l处，照亮距离为l - a[n-1]
时间复杂度：O(n log n)，主要是排序的时间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1001;
int n, l;
double a[N];///现有灯泡位置
int main() {
    fast;
    cin >> n >> l;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    double ans = -1;
    for (int i = 1; i < n; ++i)
        ans = max(ans, (a[i] - a[i-1])/2.);
    if (a[0] != 0) ans = max(ans, a[0]);
    if (a[n-1] != l) ans = max(ans, l - a[n-1]);
    printf("%.10lf\n", ans);
    return 0;
}