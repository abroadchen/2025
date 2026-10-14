//
// Created by Psy.C on 2026/10/14.
//
/**
(i^j) <= n —— 第三边（即 i 与 j 的按位异或值）不能超过 n。

因为"第三边 = i^j"是一个实际数值，必须落在题目规定的范围内。
(i^j) >= j —— 第三边不小于 j（与第二层循环 j>=i 配合，保证三边有序 i ≤ j ≤ (i^j)，避免重复计数）。

有了这个条件，配合外循环 i 与内循环 j，可以保证每个三角形按 i ≤ j ≤ i^j 的有序唯一形式计数，不重复。
(i+j) > (i^j) —— 这是三角形不等式的关键一条。

要构成三角形，需要两边之和大于第三边。由于三边已按大小排好 i ≤ j ≤ (i^j)，第三边是最大的，所以只要验证两条较小边之和 ≥（实际 >）最大边即可——
i + j > (i^j) 即：两条较小边 i、j 之和必须大于最大边 i^j。
（因为 i ≤ j、且第三边 i^j ≥ j，最大边就是 i^j，故只需检查这一条。）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            if ((i^j) <= n && (i^j) >= j && (i+j) > (i^j))
                ans++;
    cout << ans << '\n';
    return 0;
}