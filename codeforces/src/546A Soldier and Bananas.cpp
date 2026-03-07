//
// Created by Psy.C on 2026/3/7.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int k, n, w;
int main() {
    fast;
    cin >> k >> n >> w;
    int sum = 0;
    for (int i = 1; i <= w; ++i) sum += k*i;
    if (sum >= n) cout << sum-n << '\n';
    else cout << "0\n";
    return 0;
}