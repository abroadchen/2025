//
// Created by Psy.C on 2026/10/12.
//
/**
边读入边维护 mn（整个数组的最小值）
x 记录上一个值等于 mn 的下标，初始为 -1。
每遇到一个 a[i] == mn，若已有上一个（x != -1），就用 i - x 更新 ans（取最小），然后 x = i。
这样 ans 就是相邻两个最小值之间的最小下标差
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5, inf = 1e9;

int n, a[N];
int main() {
    fast;
    cin >> n;
    int mn = inf;
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; mn = min(mn,a[i]);
    }
    int ans = inf;
    for (int i = 0, x = -1; i < n; ++i) {
        if (a[i] == mn) {
            if (x != -1) ans = min(ans, i-x);
            x = i;
        }
    }
    cout << ans << '\n';
    return 0;
}