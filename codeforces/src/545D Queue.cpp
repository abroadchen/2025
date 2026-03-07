//
// Created by Psy.C on 2026/3/7.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
int n;
ll a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int ans = 0; ll sum = 0;
    for (int i = 1; i <= n; ++i) if (sum <= a[i]) {
        sum += a[i]; ans++;
    }
    cout << ans << '\n';
    return 0;
}