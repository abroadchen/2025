//
// Created by Psy.C on 2026/2/16.
//
/**
时间复杂度：
O(n log n)，主要是排序的时间复杂度
空间复杂度：
O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 5005;
int n;
ii p[N];

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first >> p[i].second;
    }
    sort(p, p + n);
    int pre = min(p[0].first, p[0].second);//第一个数对的较小值
    for (int i = 1; i < n; ++i) {
        const int t = min(p[i].first, p[i].second);//当前数对的较小值
        pre = t < pre ? max(p[i].first, p[i].second) : t;
    }
    cout << pre << '\n';
    return 0;
}