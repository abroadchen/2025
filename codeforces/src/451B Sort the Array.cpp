//
// Created by Psy.C on 2026/2/10.
//
/**
a[N]：存储原始数组
b[N]：用于排序的副本数组

时间复杂度：O(n log n)，主要消耗在排序
空间复杂度：O(n)，需要额外数组存储副本
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

ll a[N], b[N];
bool ok(const int l, const int r) {//区间[l,r]内的a数组是否是b数组的逆序
    for (int i = 0; i + l < r; ++i)
        if (a[l+i] != b[r-i]) return false;
    return true;
}

int n;

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i], b[i] = a[i];
    sort(b, b + n);
    int l = 0, r = n - 1;
    //找到左边匹配的边界：从左往右找第一个a[i] ≠ b[i]的位置
    while (l < n && b[l] == a[l]) l++;
    //找到右边匹配的边界：从右往左找第一个a[i] ≠ b[i]的位置
    while (r >= 0 && b[r] == a[r]) --r;//此时[l,r]是需要翻转的区间
    if (ok(l, r)) {
        if (r < l) l = r = 0;//整个数组已经有序
        cout << "yes" << '\n' << l + 1 << ' ' << r + 1 << '\n';
    } else cout << "no" << '\n';
    return 0;
}