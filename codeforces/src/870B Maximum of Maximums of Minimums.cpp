//
// Created by Psy.C on 2026/10/5.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int a[N];
int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    if (k == 1) cout << *min_element(a, a+n) << '\n';
    else if (k == 2) cout << max(a[0], a[n-1]) << '\n';//首尾较大者
    else cout << *max_element(a, a+n) << '\n';
    return 0;
}