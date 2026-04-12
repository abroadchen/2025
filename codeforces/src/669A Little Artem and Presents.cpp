//
// Created by Psy.C on 2026/4/12.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    if (n%3 == 0) cout << n/3*2 << '\n';
    else cout << n/3*2+1 << '\n';
    return 0;
}