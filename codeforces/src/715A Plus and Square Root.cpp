//
// Created by Psy.C on 2026/4/21.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    cout << "2\n";
    for (int k = 2; k <= n; ++k)
        cout << 1ll*k*(k+1)*(k+1)-(k-1) << '\n';
    return 0;
}