//
// Created by Psy.C on 2026/9/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, t, k, d; cin >> n >> t >> k >> d;
    if (k >= n) return cout << "NO\n", 0;
    int x = n%k == 0 ? n/k : n/k+1;
    if ((x-1)*t > d) return cout << "YES\n", 0;
    cout << "NO\n";
    return 0;
}