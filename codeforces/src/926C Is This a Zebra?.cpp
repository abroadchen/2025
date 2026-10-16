//
// Created by Psy.C on 2026/10/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;
constexpr int N = 1e5+1;
int a[N], len[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int cur = a[1], cnt = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i] == cur) len[cnt]++;
        else cur = a[i], cnt++;
    }
    for (int i = 1; i < cnt; ++i)
        if (len[i] != len[i+1])
            return cout << "NO\n", 0;
    return cout << "YES\n", 0;
}