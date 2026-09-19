//
// Created by Psy.C on 2026/9/19.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int ans = n%2 ? n/2 : n/2-1;
    cout << ans << '\n';
    return 0;
}