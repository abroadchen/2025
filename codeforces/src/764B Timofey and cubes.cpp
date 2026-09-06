//
// Created by Psy.C on 2026/9/6.
//
/**
双指针遍历：初始化 i = 1（指向数组左端）和 j = n（指向数组右端），每次循环 i 增大 1，j 减小 1。
循环次数：理论上应该循环到数组中间位置，即 i <= (n + 1) / 2（确保左指针不越过右指针）。
奇偶判断：只有当 i 为奇数时才执行 swap(a[i], a[j])。
这意味着只会交换第 1、3、5... 个位置与其对应的右侧元素，而第 2、4、6... 个位置保持不变
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, j = n; i <= ceil(n/2.); ++i, --j)
        if (i%2) swap(a[i], a[j]);
    for (int i = 1; i <= n; ++i)
        cout << a[i] << ' ';
    return 0;
}