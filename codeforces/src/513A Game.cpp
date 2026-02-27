//
// Created by Psy.C on 2026/2/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, k, l;
int main() {
    fast;
    cin >> n >> m >> k >> l;
    if (n <= m) cout << "Second\n";
    else cout << "First\n";
    return 0;
}