//
// Created by Psy.C on 2026/3/29.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5005;

struct node { char c; int l, r; } a[N];
int n, m[N], w[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].c >> a[i].l >> a[i].r;
        if (a[i].c == 'M')
            for (int j = a[i].l; j <= a[i].r; ++j)
                m[j]++;
        else
            for (int j = a[i].l; j <= a[i].r; ++j)
                w[j]++;
    }
    int res = 0;
    for (int i = 1; i < 367; ++i)
        res = max(res, min(m[i], w[i]));
    cout << res*2 << '\n';
    return 0;
}