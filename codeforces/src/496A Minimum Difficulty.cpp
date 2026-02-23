//
// Created by Psy.C on 2026/2/20.
//
/**
删除第i个元素后，a[i-1]和a[i+1]会相邻
原来的间隔a[i]-a[i-1]和a[i+1]-a[i]会合并为a[i+1]-a[i-1]

如果删除的元素与其前一个元素的差值正好是原来的最大差值
删除后，原来的最大差值消失
新的最大差值是：max(原来第二大差值, 合并后的新差值)
如果删除的元素对应的差值不是最大差值
删除后，原来的最大差值仍然存在
新的最大差值是：max(原来最大差值, 合并后的新差值)

O(n log n)：主要是排序的时间复杂度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101, inf = 1e6;
int n, a[N], b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i <= n; ++i) b[i-1] = a[i] - a[i-1];
    sort(b + 1, b + n);
    int mn = inf;
    for (int i = 2; i < n; ++i) {
        if (a[i] - a[i-1] == b[n - 1])
            mn = min(mn, max(b[n-2], a[i+1]-a[i-1]));
        else
            mn = min(mn, max(b[n-1], a[i+1]-a[i-1]));
    }
    cout << mn;
    return 0;
}