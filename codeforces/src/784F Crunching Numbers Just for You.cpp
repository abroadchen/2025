//
// Created by Psy.C on 2026/9/13.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+1;
int a[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1, less<>());
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}