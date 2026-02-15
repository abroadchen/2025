//
// Created by Psy.C on 2026/2/14.
//
/**
从最大值开始每隔k个元素选择一个
对每个选中的元素计算(f[i]-1)*2
将所有结果累加
排序：O(n log n)
循环：O(n/k)
总体：O(n log n)
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2100
using namespace std;

int n, k, f[N], ans;

int main() {
    fast;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> f[i];
    sort(f, f + n); ans = 0;
    for (int i = n - 1; i >= 0; ) {
        ans += (f[i]-1)<<1;
        i -= k;
    }
    cout << ans << '\n';
    return 0;
}