//
// Created by Psy.C on 2026/9/24.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a, b;
int main() {
    fast;
    cin >> a >> b;
    ll c = a/b;
    if (c % 2 == 0) cout << "NO"; else cout << "YES";
    return 0;
}