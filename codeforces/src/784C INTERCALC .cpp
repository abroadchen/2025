//
// Created by Psy.C on 2026/9/13.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[20];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int x = a[n];
    sort(a+1, a+n+1);
    int y = a[n], ans = x^y;
    cout << ans;
    return 0;
}