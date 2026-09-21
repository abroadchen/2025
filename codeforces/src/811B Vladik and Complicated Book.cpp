//
// Created by Psy.C on 2026/9/20.
//
/**
n：数组长度；a[1..n]：数组元素（下标从 1 开始）。
m：查询次数
选择 a[x] 作为"锚定值"。
在区间 [l, r] 内，统计值严格小于 a[x] 的元素个数 → sum。
排序后，值比 a[x] 小的元素会排到 a[x] 前面；如果 a[x] 排序后的位置就是原位置 x，需要满足：
排序后位置 = l + (比 a[x] 小的个数) = l + sum
要等于原位置 x
所以判断条件：l + sum == x

为什么只统计严格小于而不统计 ≤ ？ 因为值相等的元素排序后相对顺序不变（稳定排序），a[x] 只会被"严格更小"的元素挤到后面；等于它的不会越过它。所以只需要数 < a[x] 的个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, m, a[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    while (m-- > 0) {
        int l, r, x; cin >> l >> r >> x;
        int sum = 0;
        for (int i = l; i <= r; ++i) sum += a[i] < a[x];
        cout << (l + sum == x ? "Yes\n" : "No\n");
    }
    return 0;
}