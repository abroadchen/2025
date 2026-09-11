//
// Created by Psy.C on 2026/9/11.
//
/**
读入 n 以及两个字符串/数组 a、b（长度 n，每个元素是字符）。
对 a 和 b 分别升序排序——贪心匹配的前提

双指针 i（扫 a）、j（扫 b），都从最小（升序头）开始。
若 a[i] <= b[j]：说明 a 当前最小牌不占优，直接配对消耗一个 b（++i;++j），不计数。
否则（a[i] > b[j]）：a 能赢 b 当前最小牌，a1++，只消耗一个 b（++j），a 的这张强牌留着继续打更大的 b。
循环结束时，a1 = a 中最少能赢 b 的场数（当 a 的牌不匹配 b 时以最小代价取胜）
指针从两端（最大）‍开始：i 指向 a 中最大、j 指向 b 中最大。
若 a[i] < b[j]：说明 a 当前最大牌打不过 b 当前最大牌，a2++（b 赢一把），同时消耗两端最大各一（--i;--j）。
否则（a[i] >= b[j]）：说明 a 的当前最大牌能赢 b 的最大牌（b 输），不计入 a2，只消耗 a 的最大牌（--i），j 不动（留着这张更弱的 b 最大牌继续被更小的 a 尝试）。
循环结束时，a2 = b 最多能赢 a 的场数（用最大牌硬碰硬贪心）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e4;
char a[N], b[N];
int main() {
    fast;
    int n; cin >> n >> a >> b;
    sort(a, a + n); sort(b, b + n);
    int a1(0), a2(0), i(0), j(0);
    while (i < n && j < n) {
        if (a[i] <= b[j]) { ++i; ++j; }
        else { ++a1; ++j; }
    }
    i = n-1, j = n-1;
    while (i >= 0 && j >= 0) {
        if (a[i] < b[j]) { a2++; --i; --j; }
        else --i;
    }
    cout << a1 << '\n' << a2 << '\n';
    return 0;
}