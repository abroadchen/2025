//
// Created by Psy.C on 2026/2/19.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    if (n&1) cout << "black\n";
    else cout << "white\n1 2\n";
    return 0;
}