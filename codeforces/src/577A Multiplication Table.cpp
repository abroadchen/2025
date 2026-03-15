//
// Created by Psy.C on 2026/3/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
int main() {
    fast;
    cin >> n >> m;
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (m%i == 0 && m/i <= n) cnt++;
    cout << cnt << '\n';
    return 0;
}