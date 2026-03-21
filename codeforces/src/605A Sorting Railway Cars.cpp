//
// Created by Psy.C on 2026/3/22.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, dp[N];
int main() {
    fast;
    cin >> n;
    int ans = 0;
    for (int i = 0, j; i < n; ++i) {
        cin >> j;
        dp[j] = dp[j-1] + 1;
        ans = max(ans, dp[j]);
    }
    cout << n - ans;
    return 0;
}