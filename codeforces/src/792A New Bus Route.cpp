//
// Created by Psy.C on 2026/9/15.
//
/**
读入 n 个数 a[1..n]。
sort 升序排序。
第一个循环：遍历相邻元素，取最小相邻差值 mn（mn 初始为极大值 inf）。
第二个循环：统计有多少对相邻元素差值恰好等于 mn，计为 cnt。
输出 mn 和 cnt（空格隔开）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+7, inf = 2147483647;

int a[N], mn(inf), cnt;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+n+1);
    for (int i = 1; i < n; ++i)
        mn = min(mn, abs(a[i]-a[i+1]));
    cout << mn << ' ';
    for (int i = 1; i < n; ++i)
        if (mn == abs(a[i]-a[i+1])) cnt++;
    cout << cnt;
    return 0;
}