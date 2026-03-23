//
// Created by Psy.C on 2026/3/23.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;
int n, m, a[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n, [](int i, int j) {
        return i > j;
    });
    int ans = 0;
    for (int i = 0, sum = 0; i < n; ++i) {
        sum += a[i];
        ans++;
        if (sum >= m) break;
    }
    cout << ans;
    return 0;
}