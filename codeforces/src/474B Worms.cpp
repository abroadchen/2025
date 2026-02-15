//
// Created by Psy.C on 2026/2/14.
//
/**
预处理：O(n)
每次查询：O(log n)
总时间复杂度：O(n + m log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int n, a[N], m, x;

int main() {
    fast;
    cin>>n;
    for (int i = 1; i <= n; ++i) cin>>a[i];
    for (int i = 2; i <= n; ++i) a[i] += a[i-1];
    cin>>m;
    while (m--) {
        cin>>x;
        cout << lower_bound(a, a + n, x) - a << '\n';
    }
    return 0;
}