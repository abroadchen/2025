//
// Created by Psy.C on 2026/4/28.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, m, a[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int res = 0;
    while (m--) {
        int s, e; cin >> s >> e;
        int sum = 0;
        for (int i = s; i <= e; ++i) sum += a[i];
        if (sum > 0) res += sum;
    }
    cout << res;
    return 0;
}