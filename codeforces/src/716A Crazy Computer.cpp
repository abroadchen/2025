//
// Created by Psy.C on 2026/4/21.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7;
int n, k, num[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> num[i];
    int ans = 1;
    for (int i = 2; i <= n; ++i) {
        if (num[i] - num[i-1] <= k) ans++;
        else ans = 1;
    }
    cout << ans << '\n';
    return 0;
}