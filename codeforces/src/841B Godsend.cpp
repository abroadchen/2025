//
// Created by Psy.C on 2026/9/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+10;
int n;
ll a[N], sum;
int main() {
    fast;
    cin >> n;
    bool ok = false;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; sum += a[i];
        if (a[i]%2) ok = true;
    }
    if (sum%2) cout << "First\n";
    else {
        if (ok) cout << "First\n";
        else cout << "Second\n";
    }
    return 0;
}