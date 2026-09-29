//
// Created by Psy.C on 2026/9/29.
//
/**
读入 n 个元素到 a[]。
b[] 初始为 0..n-1（即下标 0 到 n-1），后面会用它保存"按下标"
d[i] = 第 i 个元素与其后一个（环形，越界回到 0）‍元素之和。这就是每个下标的"邻项和"
对 b[]（里面存的是下标 0..n-1）按 d 值升序排序。
当 d 值相等时，按下标 x < y 字典序排（保证稳定、可预测的顺序）
遍历排好序的 b[]：c[b[i]] = i 表示"下标为 b[i] 的那个元素，其排名是 i（0-based）"。
也就是把每个下标映射到它在排序中的名次
按原始下标 0..n-1 的顺序输出每个位置的排名
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

int n, a[N], b[N], d[N], c[N];
static void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) { cin >> a[i]; b[i] = i; }
    for (int i = 0; i < n; ++i) d[i] = a[i] + a[(i+1)%n];
    sort(b, b+n, [&](const int& x, const int& y) {
        return d[x] < d[y] || (d[x] == d[y] && x < y);
    });
    for (int i = 0; i < n; ++i) c[b[i]] = i;
    for (int i = 0; i < n; ++i) cout << c[i] << ' ';
}


int main() {
    fast;
    int T = 1;
    while (T--) solve();
    return 0;
}