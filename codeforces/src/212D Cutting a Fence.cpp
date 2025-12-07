//
// Created by Psy.C on 2025/12/6.
//
/*
*n：数组长度
a[N]：输入数组
r[N]：每个位置右边第一个小于等于它的位置
l[N]：每个位置左边第一个小于它的位置
s1[N], s2[N]：差分数组
v1：单调栈
 *
*lo, h：操作区间[lo, h]
x：增加值
f：标志位，决定使用哪个差分数组
当f=0时：在s1上进行标准差分操作
当f=1时：在s2上进行二阶差分操作
 *
*使用单调递增栈
r[i]表示位置i右边第一个≤ a[i]的位置
*使用单调递增栈（从右往左）
l[i]表示位置i左边第一个< a[i]的位置
 *
*x = i - l[i]：以a[i]为最小值的左半区间长度
y = r[i] - i：以a[i]为最小值的右半区间长度
保证x ≤ y
进行三次差分操作来统计贡献
*第一遍：计算一阶前缀和
第二遍：计算二阶前缀和
 *
*对于每个查询x，计算平均值
(s1[x] + s2[x])是累积贡献
除以(n - x + 1)得到平均值
 *
 *时间复杂度：O(n) 空间复杂度：O(n)
 *
 *在区间[lo, h]上加上首项为x、公差为-x的等差数
*s2[lo] += x：在位置lo开始，每个位置都增加x
s2[h + 1] -= (h - lo + 2) * x：从位置h+1开始，抵消过多的增加
s2[h + 2] += (h - lo + 1) * x：进一步调整，形成正确的等差数列
 *
*如果 b[] 是 a[] 的一阶差分数组 (b[i] = a[i] - a[i-1])
那么 a[] 就是 b[] 的一阶前缀和
*如果 c[] 是 a[] 的二阶差分数组 (c[i] = a[i] - 2*a[i-1] + a[i-2])
那么 a[] 就是 c[] 的二阶前缀和
 *从差分数组恢复出原始的累积贡献值，用于后续的查询计算
 */
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 1000010
using namespace std;

int n, a[N], r[N], l[N], s1[N], s2[N];
vector<int> v1;

void add(const int lo, const int h, const int x, const int f) {
    if (h < lo) return;
    if (f) s2[h + 1] -= (h - lo + 2) * x,
        s2[lo] += x, s2[h + 2] += (h - lo + 1) * x;
    else s1[lo] += x, s1[h + 1] -= x;
}

signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        while (!v1.empty() && a[v1.back()] >= a[i])
            r[v1.back()] = i, v1.pop_back();
        v1.push_back(i);
    }
    while (!v1.empty()) r[v1.back()] = n + 1, v1.pop_back();
    for (int i = n; i >= 1; --i) {
        while (!v1.empty() && a[v1.back()] > a[i])
            l[v1.back()] = i, v1.pop_back();
        v1.push_back(i);
    }
    while (!v1.empty()) l[v1.back()] = 0, v1.pop_back();
    for (int i = 1, x, y; i <= n; ++i) {
        x = i - l[i], y = r[i] - i;
        if (x > y) swap(x, y);
        add(1, x, a[i], 1);
        add(x + 1, x + y - 1, x * a[i], 0);
        add(y + 1, x + y - 1, -a[i], 1);
    }
    for (int i = 1; i <= n; ++i) s1[i] += s1[i - 1], s2[i] += s2[i - 1];
    for (int i = 1; i <= n; ++i) s2[i] += s2[i - 1];
    int q, x; cin >> q;
    while (q--) {
        cin >> x;
        cout << fixed << setprecision(9) <<
            static_cast<double>((s1[x] + s2[x])) * 1. /
                static_cast<double>((n - x + 1)) << '\n';
    }
    return 0;
}