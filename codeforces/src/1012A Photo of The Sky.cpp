//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
n：读入的"组数"，但实际要处理 2n 个数。
a[N]：存这 2n 个数。
ans：答案（最小面积）
把排序后分两半：前半 a[1..n]、后半 a[n+1..2n]。
宽 = a[n] - a[1]（前半的最大减最小）。
高 = a[2n] - a[n+1]（后半的最大减最小）。
两者相乘得到一种矩形的面积
宽恒为 a[2n] - a[1]（全体最大值减最小值，即总跨度）‍。
高取区间 [a[i], a[i+n-1]]，即从第 i 个数到第 i+n-1 个数（一个长度为 n 的连续窗口）的跨度 a[i+n-1] - a[i]。
枚举 i = 2..n+1，尝试用不同位置的连续 n 个作为高度区间，让部分点集中在一个窄区间内
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

int n;
ll a[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n<<1; i++) cin >> a[i];
    sort(a+1, a+(n<<1)+1);
    ans = (a[n]-a[1])*(a[n<<1]-a[n+1]);
    for (int i = 2; i <= n+1; i++)
        ans = min(ans, (a[n<<1]-a[1])*(a[i+n-1]-a[i]));
    cout << ans;
    return 0;
}