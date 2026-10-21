//
// Created by Psy.C on 2026/10/21.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e3;

int n, m, a[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, k; i <= m; ++i) {
        cin >> k; a[k]++;
    }
    sort(a + 1, a + n + 1);
    cout << a[1] << '\n';
    return 0;
}