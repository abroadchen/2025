//
// Created by Psy.C on 2026/2/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;

bool ok(const int x, const int y) {
    return x - y >= -1 && x - y <= 1;
}

int n, a[N], m, b[N];
void get() {
    for (int i = 0; i < n; ++i) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> b[i];
    sort(a, a + n);
    sort(b, b + m);
    int ans = 0;
    for (int i = 0, j = 0; i < n && j < m; ) {
        if (ok(a[i], b[j])) ans++, i++, j++;
        else if (a[i] < b[j]) i++;
        else j++;
    }
    cout << ans << '\n';
}

int main() {
    fast;
    cin >> n; get();
    return 0;
}