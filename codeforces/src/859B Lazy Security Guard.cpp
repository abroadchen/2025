//
// Created by Psy.C on 2026/10/2.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int l = sqrt(n), w = n/l;
    if (n%l == 0) cout << (l+w)*2;
    else cout << (l+w+1)*2;
    return 0;
}