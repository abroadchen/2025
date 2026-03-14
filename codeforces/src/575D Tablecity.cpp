//
// Created by Psy.C on 2026/3/14.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3;

int main() {
    fast;
    cout << "2000\n";
    for (int x = 1; x <= N; ++x)
        cout << x << ' ' << 1 << ' ' << x << ' ' << 2 << '\n';
    for (int x = N; x >= 1; --x)
        cout << x << ' ' << 1 << ' ' << x << ' ' << 2 << '\n';
    return 0;
}