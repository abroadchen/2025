//
// Created by Psy.C on 2026/2/17.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n;
int main() {
    fast;
    cin >> n;
    if (n%2 == 0) cout << n/2;
    else cout << -n/2-1;
    return 0;
}