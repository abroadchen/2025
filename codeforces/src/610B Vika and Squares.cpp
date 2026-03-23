//
// Created by Psy.C on 2026/3/23.
//
/**
找到左右两端第一个等于最小值的位置：
l：从左边开始第一个等于mn的位置
r：从右边开始第一个等于mn的位置
计算左右两边连续大于mn的元素个数之和（这些元素都可以被"吃掉"）
在中间区域找到最长的连续大于mn的子数组长度
最终的最大值 = 吞噬的元素数量 + n×mn（因为每个元素都被计入一次）
时间复杂度：
O(n)，只需要遍历数组几次。
空间复杂度：
O(n)，用于存储输入数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, inf = 1e9;
ll n, mn = inf, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (mn > a[i]) mn = a[i];
    }
    int l = 0, r = n - 1;
    while (l < n && a[l] > mn) l++;
    while (r >= 0 && a[r] > mn) r--;
    ll mx = l + n - 1 - r;
    for (int j = l + 1, len = 0; j < r; ++j) {
        if (a[j] > mn) len++; else len = 0;
        if (mx < len) mx = len;
    }
    mx += n*mn;
    cout << mx << "\n";
    return 0;
}